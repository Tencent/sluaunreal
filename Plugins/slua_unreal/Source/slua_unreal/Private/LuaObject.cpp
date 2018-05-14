// The MIT License (MIT)

// Copyright 2015 Siney/Pangweiwei siney@yeah.net
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#include "LuaObject.h"
#include "LuaDelegate.h"
#include "UObject/UObjectGlobals.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"
#include "UObject/Stack.h"
#include "Blueprint/WidgetTree.h"
#include "LuaWidgetTree.h"
#include "LuaArray.h"
#include "Log.h"
#include "LuaCppBinding.h"
#include "LuaState.h"
#include "LuaWrapper.h"
#include "LuaEnums.h"


ULuaObject::ULuaObject(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

void ULuaObject::AddRef(UObject* obj)
{
    Cache.Add(obj);
}

void ULuaObject::Remove(UObject* obj)
{
    Cache.Remove(obj);
}


namespace slua { 

    typedef int (*PushPropertyFunction)(lua_State* L,UProperty* prop,uint8* parms);
    typedef int (*CheckPropertyFunction)(lua_State* L,UProperty* prop,uint8* parms,int i);

	TMap<UClass*,PushPropertyFunction> pusherMap;
	TMap<UClass*,CheckPropertyFunction> checkerMap;
    #if !PLATFORM_WINDOWS
    #define sprintf_s snprintf
    #endif 
    

    // construct lua struct
    LuaStruct::LuaStruct(uint8* buf,uint32 size,UScriptStruct* uss)
        :buf(buf),size(size),uss(uss) {
    }

    LuaStruct::~LuaStruct() {
        FMemory::Free(buf);
        buf = nullptr;
    }

	int LuaObject::classIndex(lua_State* L) {
		lua_getmetatable(L, 1);
		const char* name = checkValue<const char*>(L, 2);
		if (lua_getfield(L, -1, name) != 0) {
			return 1;
		} else if (lua_getfield(L, lua_upvalueindex(1)/*.get*/, name) != 0) {
			lua_pushvalue(L, 1);
			lua_call(L, 1, 1);
			return 1;
		} else {
			lua_pushnil(L);
			return 1;
		}
	}

	int LuaObject::classNewindex(lua_State* L) {
		lua_getmetatable(L, 1);
		const char* name = checkValue<const char*>(L, 2);
		if (lua_getfield(L, lua_upvalueindex(1)/*.set*/, name) != 0) {
			lua_pushvalue(L, 1);
			lua_pushvalue(L, 3);
			lua_call(L, 2, 1);
			return 1;
		} else {
			lua_pushnil(L);
			return 1;
		}
	}

	static void setMetaMethods(lua_State* L) {
		lua_newtable(L);
		lua_pushvalue(L, -1);
		lua_setfield(L, -3, ".get"); // upvalue
		lua_pushcclosure(L, LuaObject::classIndex, 1);
		lua_setfield(L, -2, "__index");
		lua_newtable(L);
		lua_pushvalue(L, -1);
		lua_setfield(L, -3, ".set"); // upvalue
		lua_pushcclosure(L, LuaObject::classNewindex, 1);
		lua_setfield(L, -2, "__newindex");
	}

	void LuaObject::newType(lua_State* L, const char* tn) {
		lua_pushglobaltable(L);					// _G
		lua_newtable(L);							// local t = {}
		lua_pushvalue(L, -1);
		lua_setfield(L, -3, tn);					// _G[tn] = t
		lua_remove(L, -2);						// remove global table;

		luaL_newmetatable(L, tn);				// local mt = {}; _G[tn] = mt
		lua_pushvalue(L, -1);
		lua_setmetatable(L, -3);					// setmetatable(t, mt)
		setMetaMethods(L);
		
		char _inst[64];
		sprintf_s(_inst, 64, "%s_inst", tn);
		luaL_newmetatable(L, _inst);
		setMetaMethods(L);
	}

	void LuaObject::addMethod(lua_State* L, const char* name, lua_CFunction func, bool isInstance) {
		lua_pushcfunction(L, func);
		lua_setfield(L, isInstance ? -2 : -3, name);
	}

	void LuaObject::addField(lua_State* L, const char* name, lua_CFunction getter, lua_CFunction setter, bool isInstance) {
		lua_getfield(L, isInstance ? -1 : -2, ".get");
		lua_pushcfunction(L, getter);
		lua_setfield(L, -2, name);
		lua_pop(L, 1);
		lua_getfield(L, isInstance ? -1 : -2, ".set");
		lua_pushcfunction(L, setter);
		lua_setfield(L, -2, name);
		lua_pop(L, 1);
	}

	void LuaObject::addOperator(lua_State* L, const char* name, lua_CFunction func) {
		lua_pushcfunction(L, func);
		lua_setfield(L, -2, name);
	}

	void LuaObject::getStaticTypeTable(lua_State* L, const char* tn) {
		char _static[64];
		sprintf_s(_static, 64, "%s_static", tn);
		luaL_getmetatable(L, _static);
	}

	void LuaObject::getInstanceTypeTable(lua_State* L, const char* tn) {
		char _inst[64];
		sprintf_s(_inst, 64, "%s_inst", tn);
		luaL_getmetatable(L, _inst);
	}

	void LuaObject::finishType(lua_State* L, const char* tn, lua_CFunction ctor, lua_CFunction gc) {
		lua_pushcclosure(L, ctor, 0);
		lua_setfield(L, -3, "__call");

		// copy _inst table as _static table before add __gc method
		lua_newtable(L);
		lua_pushvalue(L, -2);
		lua_pushnil(L);
		while (lua_next(L, -2)) {
			lua_pushvalue(L, -2);
			lua_insert(L, -2);
			lua_settable(L, -5);
		}
		lua_pop(L, 1);

		char _static[64];
		sprintf_s(_static, 64, "%s_static", tn);
		lua_setfield(L, LUA_REGISTRYINDEX, _static);

		lua_pushcclosure(L, gc, 0);
		lua_setfield(L, -2, "__gc");

		lua_pop(L, 3); // type table and mt table
	}

    PushPropertyFunction getPusher(UClass* cls) {
        return *(pusherMap.Find(cls));
    }

    CheckPropertyFunction getChecker(UClass* cls) {
        return *(checkerMap.Find(cls));
    }

    PushPropertyFunction getPusher(UProperty* prop) {
        return getPusher(prop->GetClass());
    }

    CheckPropertyFunction getChecker(UProperty* prop) {
        return getChecker(prop->GetClass());        
    }

    void regPusher(UClass* cls,PushPropertyFunction func) {
		pusherMap.Add(cls, func);
    }

    void regChecker(UClass* cls,CheckPropertyFunction func) {
		checkerMap.Add(cls, func);
    }

    int classConstruct(lua_State* L) {
        UClass* cls = LuaObject::checkValue<UClass*>(L, 1);
        if(cls) {
            UObject* obj = NewObject<UObject>((UObject*)GetTransientPackage(),cls);
            if(obj) {
                LuaObject::push(L,obj);
                return 1;
            }
        }
        return 0;
    }

    int structConstruct(lua_State* L) {
        UScriptStruct* uss = LuaObject::checkValue<UScriptStruct*>(L, 1);
        if(uss) {
            uint32 size = uss->GetStructureSize() ? uss->GetStructureSize() : 1;
            
            uint8* buf = (uint8*)FMemory::Malloc(size);
            uss->InitializeStruct(buf);
            LuaStruct* ls=new LuaStruct{buf,size,uss};
            LuaObject::push(L,ls);
            return 1;
        }
        return 0;
    }

    int pushValueByPtr(lua_State* L,void* ptr,const TCHAR* tn) {
        if(wcscmp(tn,TEXT("bool"))==0) {
            bool* r = reinterpret_cast<bool*>(ptr);
            lua_pushboolean(L,*r);
            return 1;
        }
        else
            slua::Log::Log(TEXT("type of %s don't suppor to push"),tn);
        return 0;
    }

    int fillParamFromState(lua_State* L,UProperty* prop,uint8* params,int i) {
        auto checker = getChecker(prop);
        if(checker) {
            checker(L,prop,params,i);
            return prop->GetSize();
        }
        else {
            FString tn = prop->GetClass()->GetName();
            luaL_error(L,"unsupport param type %s at %d",TCHAR_TO_UTF8(*tn),i);
            return 0;
        }
        
    }

    void fillParam(lua_State* L,UFunction* func,uint8* params) {
        int i=2;
        for(TFieldIterator<UProperty> it(func);it && (it->PropertyFlags&CPF_Parm);++it) {
            UProperty* prop = *it;
            uint64 propflag = prop->GetPropertyFlags();
            if((propflag&CPF_ReturnParm))
                continue;

            fillParamFromState(L,prop,params,i);
            i++;
        }
    }

    // handle return value and out params
    int returnValue(lua_State* L,UFunction* func,uint8* params) {

        // check is function has return value
		const bool bHasReturnParam = func->ReturnValueOffset != MAX_uint16;

        int ret = 0;
        int offset= 0;
        if(bHasReturnParam) {
            UProperty* p = func->GetReturnProperty();
            ret += LuaObject::push(L,p,params);
        }

        // push out parms
        for(TFieldIterator<UProperty> it(func);it;++it) {
            UProperty* p = *it;
            uint64 propflag = p->GetPropertyFlags();
            // skit return param
            if(propflag&CPF_ReturnParm)
                continue;

            if((propflag&CPF_OutParm)) {
                ret += LuaObject::push(L,p,params+offset);
            }
            offset += p->GetSize();
        }
        
        return ret;
    }
    
    int ufuncClosure(lua_State* L) {
        lua_pushvalue(L,lua_upvalueindex(1));
        void* ud = lua_touserdata(L, -1);
        lua_pop(L, 1); // pop ud of func
        
        if(!ud)
            luaL_error(L, "Call ufunction error");
        
        //UE_LOG(LogClass, Log, TEXT("lua top %d"),lua_gettop(L));
        UObject* obj = LuaObject::checkValue<UObject*>(L, 1);
        
        UFunction* func = reinterpret_cast<UFunction*>(ud);
        
        uint8* params = (uint8*)FMemory_Alloca(func->ParmsSize);
        FMemory::Memzero( params, func->ParmsSize );
        //UE_LOG(LogClass, Log, TEXT("fill params %d"),func->ParmsSize);
        fillParam(L,func,params);

        // call function with params
        obj->ProcessEvent(func,params);
        // return value to push lua stack
        return returnValue(L,func,params);
    }
    
    int instanceIndex(lua_State* L) {
        UObject* obj = LuaObject::checkValue<UObject*>(L, 1);
        const char* name = LuaObject::checkValue<const char*>(L, 2);
        
        UClass* cls = obj->GetClass();
        TCHAR* wname = UTF8_TO_TCHAR(name);
        UFunction* func = cls->FindFunctionByName(wname);
        if(!func) {
            UProperty* up = cls->FindPropertyByName(wname);
            if(!up)
                return 0;
            return LuaObject::push(L,up,(uint8*)obj);
        }
        else   
            return LuaObject::push(L,func);
    }

    int newinstanceIndex(lua_State* L) {
        UObject* obj = LuaObject::checkValue<UObject*>(L, 1);
        const char* name = LuaObject::checkValue<const char*>(L, 2);
        TCHAR* wname = UTF8_TO_TCHAR(name);
        UClass* cls = obj->GetClass();
        UProperty* up = cls->FindPropertyByName(wname);
        auto checker = getChecker(up);
        if(!up)
            luaL_error(L,"Can't find property named %s",name);
        
        // set property value
        checker(L,up,(uint8*)obj,3);
        return 0;
    }

    int instanceStructIndex(lua_State* L) {
        LuaStruct* ls = LuaObject::checkValue<LuaStruct*>(L, 1);
        const char* name = LuaObject::checkValue<const char*>(L, 2);
        
        auto* cls = ls->uss;
        TCHAR* wname = UTF8_TO_TCHAR(name);
        UProperty* up = cls->FindPropertyByName(wname);
        if(!up)
            return 0;
        return LuaObject::push(L,up,ls->buf);
    }

    int instanceIndexSelf(lua_State* L) {
        lua_getmetatable(L,1);
        const char* name = LuaObject::checkValue<const char*>(L, 2);
        
        lua_getfield(L,-1,name);
        lua_remove(L,-2); // remove mt of ud
        return 1;
    }

	int pushEnumProperty(lua_State* L, UProperty* prop, uint8* parms) {
		auto p = Cast<UEnumProperty>(prop);
		ensure(p);
		auto p2 = p->GetUnderlyingProperty();
		ensure(p2);
		int i = p2->GetSignedIntPropertyValue(parms);
		return LuaObject::push(L, i);
	}

    int pushUIntProperty(lua_State* L,UProperty* prop,uint8* parms) {
        auto ip=Cast<UIntProperty>(prop);
        ensure(ip);
        int i = ip->GetPropertyValue_InContainer(parms);
        return LuaObject::push(L,i);
    }

    int pushFloatProperty(lua_State* L,UProperty* prop,uint8* parms) {
        auto ip=Cast<UFloatProperty>(prop);
        ensure(ip);
        float i = ip->GetPropertyValue_InContainer(parms);
        return LuaObject::push(L,i);
    }

    int pushUBoolProperty(lua_State* L,UProperty* prop,uint8* parms) {
        auto bp=Cast<UBoolProperty>(prop);
        ensure(bp);
        bool b = bp->GetPropertyValue_InContainer(parms);
        return LuaObject::push(L,b);
    }

    int pushUArrayProperty(lua_State* L,UProperty* prop,uint8* parms) {
        auto p = Cast<UArrayProperty>(prop);
        ensure(p);
        FScriptArray* v = p->GetPropertyValuePtr_InContainer(parms);
        return LuaArray::push(L,p,v);
    }

    int pushUTextProperty(lua_State* L,UProperty* prop,uint8* parms) {
        auto p = Cast<UTextProperty>(prop);
        ensure(p);
        FText* text = p->GetPropertyValuePtr_InContainer(parms);
        return LuaObject::push(L,*text);
    }    

    int pushUStrProperty(lua_State* L,UProperty* prop,uint8* parms) {
        auto p = Cast<UStrProperty>(prop);
        ensure(p);
        FString* str = p->GetPropertyValuePtr_InContainer(parms);
        return LuaObject::push(L,*str);
    }

    int pushUStructProperty(lua_State* L,UProperty* prop,uint8* parms_) {
        auto p = Cast<UStructProperty>(prop);
        ensure(p);
        auto uss = p->Struct;
        uint8* parms = parms_+p->GetOffset_ForInternal();

        uint32 size = uss->GetStructureSize() ? uss->GetStructureSize() : 1;

		if (LuaWrapper::pushValue(L, p, uss, parms))  
			return 1;

		uint8* buf = (uint8*)FMemory::Malloc(size);
		FMemory::Memcpy(buf, parms, size);
		//p->CopyValuesInternal(buf,parms,1);
		return LuaObject::push(L, new LuaStruct{buf,size,uss});
    }  

    int pushUMulticastDelegateProperty(lua_State* L,UProperty* prop,uint8* parms) {
        auto p = Cast<UMulticastDelegateProperty>(prop);
        ensure(p);   
        FMulticastScriptDelegate* delegate = p->GetPropertyValuePtr_InContainer(parms);
        return LuaDelegate::push(L,delegate,p->SignatureFunction);
    }
	 
    int pushUObjectProperty(lua_State* L,UProperty* prop,uint8* parms) {
        auto p = Cast<UObjectProperty>(prop);
        ensure(p);   
        UObject* o = p->GetPropertyValue_InContainer(parms);
        if(auto tr=Cast<UWidgetTree>(o))
            return LuaWidgetTree::push(L,tr);
        else
            return LuaObject::push(L,o);
    }

    int checkUIntProperty(lua_State* L,UProperty* prop,uint8* parms,int i) {
        auto p = Cast<UIntProperty>(prop);
        ensure(p);
        p->SetPropertyValue_InContainer(parms,LuaObject::checkValue<int>(L,i));
        return 0;
    }

    int checkUBoolProperty(lua_State* L,UProperty* prop,uint8* parms,int i) {
        auto p = Cast<UBoolProperty>(prop);
        ensure(p);
        p->SetPropertyValue_InContainer(parms,LuaObject::checkValue<bool>(L,i));
        return 0;
    }

    int checkUFloatProperty(lua_State* L,UProperty* prop,uint8* parms,int i) {
        auto p = Cast<UFloatProperty>(prop);
        ensure(p);
        p->SetPropertyValue_InContainer(parms,LuaObject::checkValue<float>(L,i));
        return 0;
    }
    

    int checkUStructProperty(lua_State* L,UProperty* prop,uint8* parms,int i) {
        auto p = Cast<UStructProperty>(prop);
        ensure(p);
        auto uss = p->Struct;

		if (LuaWrapper::checkValue(L, p, uss, parms, i))
			return 0;

		LuaStruct* ls = LuaObject::checkValue<LuaStruct*>(L, i);
		if (p->GetSize() != ls->size)
			luaL_error(L, "expect struct size == %d, but got %d", p->GetSize(), ls->size);
		p->CopyCompleteValue_InContainer(parms, ls->buf);
		return 0;
    }

    int checkUTextProperty(lua_State* L,UProperty* prop,uint8* parms,int i) {
        auto p = Cast<UTextProperty>(prop);
        ensure(p);
        p->SetPropertyValue_InContainer(parms,LuaObject::checkValue<FText>(L,i));
        return 0;
    }

	int checkEnumProperty(lua_State* L, UProperty* prop, uint8* parms, int i) {
		auto p = Cast<UEnumProperty>(prop);
		ensure(p);
		auto p2 = p->GetUnderlyingProperty();
		ensure(p2);
		auto v = LuaObject::checkValue<int>(L, i);
		if (p2->ElementSize == sizeof(int8)) {
			auto v2 = (int8)v;
			p2->CopyCompleteValue_InContainer(parms, &v2);
		} else if (p2->ElementSize == sizeof(int16)) {
			auto v2 = (int16)v;
			p2->CopyCompleteValue_InContainer(parms, &v2);
		} else if (p2->ElementSize == sizeof(int32)) {
			auto v2 = (int32)v;
			p2->CopyCompleteValue_InContainer(parms, &v2);
		} else if (p2->ElementSize == sizeof(int64)) {
			auto v2 = (int64)v;
			p2->CopyCompleteValue_InContainer(parms, &v2);
		} else {
			luaL_error(L, "unexcept enum size %d", p2->ElementSize);
		}
		return 0;
	}

    int checkUStrProperty(lua_State* L,UProperty* prop,uint8* parms,int i) {
        auto p = Cast<UStrProperty>(prop);
        ensure(p);
        p->SetPropertyValue_InContainer(parms,LuaObject::checkValue<FString>(L,i));
        return 0;
    }

    int checkUObjectProperty(lua_State* L,UProperty* prop,uint8* parms,int i) {
        auto p = Cast<UObjectProperty>(prop);
        ensure(p);
        p->SetPropertyValue_InContainer(parms,LuaObject::checkValue<UObject*>(L,i));
        return 0;
    }


    // search obj from registry, push cached obj and return true if find it
    bool LuaObject::getFromCache(lua_State* L,void* obj) {
        LuaState* ls = LuaState::get(L);
        ensure(ls->cacheObjRef!=LUA_NOREF);
        lua_geti(L,LUA_REGISTRYINDEX,ls->cacheObjRef);
        // should be a table
        ensure(lua_type(L,-1)==LUA_TTABLE);
        // push obj as key
        lua_pushlightuserdata(L,obj);
        // get key from table
        lua_rawget(L,-2);
        bool ret = true;
        lua_remove(L,-2); // remove cache table
        
        if(lua_isnil(L,-1)) {
            ret = false;
            lua_pop(L,1);
        }
        return ret;
    }

    void LuaObject::addRef(lua_State* L,UObject* obj) {
        auto sl = LuaState::get(L);
        sl->addRef(obj);
    }


    void LuaObject::removeRef(lua_State* L,UObject* obj) {
        auto sl = LuaState::get(L);
        sl->removeRef(obj);
    }

    void LuaObject::cacheObj(lua_State* L,void* obj) {
        LuaState* ls = LuaState::get(L);
        lua_geti(L,LUA_REGISTRYINDEX,ls->cacheObjRef);
        lua_pushlightuserdata(L,obj);
        lua_pushvalue(L,-3); // obj userdata
        lua_rawset(L,-3);
        lua_pop(L,1); // pop cache table        
    }

    int LuaObject::removeFromCacheGC(lua_State* L) {
        int p = lua_upvalueindex(1);
        // get real gc function
        lua_CFunction gc = lua_tocfunction(L,p);
        gc(L);
        // get cache table
        LuaState* ls = LuaState::get(L);
        lua_geti(L,LUA_REGISTRYINDEX,ls->cacheObjRef);
        ensure(lua_type(L,-1)==LUA_TTABLE);
        // check UD as light userdata
        UserData<void*>* ud = reinterpret_cast<UserData<void*>*>(lua_touserdata(L,1));
        lua_pushlightuserdata(L,ud->ud);
        lua_pushnil(L);
        // cache[obj] = nil
        lua_rawset(L,-3);
        // pop cache table;
        lua_pop(L,1);
        return 0;
    }


    int LuaObject::pushClass(lua_State* L,UClass* cls) {
        if(!cls) {
            lua_pushnil(L);
            return 1;
        }
        return pushObject(L,cls,"UClass",setupClassMT);
    }

    int LuaObject::pushStruct(lua_State* L,UScriptStruct* cls) {
        if(!cls) {
            lua_pushnil(L);
            return 1;
        }          
        return pushObject(L,cls,"UScriptStruct",setupStructMT);
    }

    int LuaObject::gcObject(lua_State* L) {
        CheckUD(UObject,L,1);
        removeRef(L,UD);
        return 0;
    }

    int LuaObject::gcClass(lua_State* L) {
        CheckUD(UClass,L,1);
        removeRef(L,UD);
        return 0;
    }

    int LuaObject::gcStructClass(lua_State* L) {
        CheckUD(UScriptStruct,L,1);
        removeRef(L,UD);
        return 0;
    }

	int LuaObject::gcStruct(lua_State* L) {
		CheckUD(LuaStruct, L, 1);
		delete UD;
		return 0;
	}

    int LuaObject::push(lua_State* L, UObject* obj) {
        if(!obj) {
            lua_pushnil(L);
            return 1;
        }
        return pushGCObject<UObject*>(L,obj,"UObject",setupInstanceMT,gcObject);
    }

    void LuaObject::init(lua_State* L) {
        regPusher(UIntProperty::StaticClass(),pushUIntProperty);
        regPusher(UFloatProperty::StaticClass(),pushFloatProperty);
        regPusher(UTextProperty::StaticClass(),pushUTextProperty);
        regPusher(UMulticastDelegateProperty::StaticClass(),pushUMulticastDelegateProperty);
        regPusher(UObjectProperty::StaticClass(),pushUObjectProperty);
        regPusher(UBoolProperty::StaticClass(),pushUBoolProperty);
        regPusher(UArrayProperty::StaticClass(),pushUArrayProperty);
        regPusher(UStrProperty::StaticClass(),pushUStrProperty);
        regPusher(UStructProperty::StaticClass(),pushUStructProperty);
		regPusher(UEnumProperty::StaticClass(), pushEnumProperty);

        regChecker(UIntProperty::StaticClass(),checkUIntProperty);
        regChecker(UBoolProperty::StaticClass(),checkUBoolProperty);
        regChecker(UFloatProperty::StaticClass(),checkUFloatProperty);
        regChecker(UStructProperty::StaticClass(),checkUStructProperty);
        regChecker(UTextProperty::StaticClass(),checkUTextProperty);
        regChecker(UObjectProperty::StaticClass(),checkUObjectProperty);
        regChecker(UStrProperty::StaticClass(),checkUStrProperty);
		regChecker(UEnumProperty::StaticClass(), checkEnumProperty);

		LuaWrapper::init(L);
		LuaEnums::init(L);
    }

    int LuaObject::push(lua_State* L,UFunction* func)  {
        lua_pushlightuserdata(L, func);
        lua_pushcclosure(L, ufuncClosure, 1);
        return 1;
    }

    int LuaObject::push(lua_State* L,UProperty* prop,uint8* parms) {
        auto pusher = getPusher(prop);
        if (pusher)
            return pusher(L,prop,parms);
        else {
            FString name = prop->GetClass()->GetName();
            luaL_error(L,"unsupport type %s to push",TCHAR_TO_UTF8(*name));
            return 0;
        }
    }

	int LuaObject::push(lua_State* L, FScriptDelegate* obj) {
		return pushType<FScriptDelegate*>(L, obj, "FScriptDelegate");
	}

	int LuaObject::push(lua_State* L, LuaStruct* ls) {
		return pushType<LuaStruct*>(L, ls, "LuaStruct", setupInstanceMT, gcStruct);
	}

	int LuaObject::push(lua_State* L, double v) {
		lua_pushnumber(L, v);
		return 1;
	}

	int LuaObject::push(lua_State* L, float v) {
		lua_pushnumber(L, v);
		return 1;
	}

	int LuaObject::push(lua_State* L, int v) {
		lua_pushinteger(L, v);
		return 1;
	}

	int LuaObject::push(lua_State* L, uint32 v) {
		lua_pushnumber(L, v);
		return 1;
	}

	int LuaObject::push(lua_State* L, const FText& v) {
		FString str = v.ToString();
		lua_pushstring(L, TCHAR_TO_UTF8(*str));
		return 1;
	}

	int LuaObject::push(lua_State* L, const FString& str) {
		lua_pushstring(L, TCHAR_TO_UTF8(*str));
		return 1;
	}

    int LuaObject::setupMTSelfSearch(lua_State* L) {
        lua_pushcfunction(L,instanceIndexSelf);
        lua_setfield(L, -2, "__index");
        return 0;
    }


    int LuaObject::setupClassMT(lua_State* L) {
        lua_pushcfunction(L,classConstruct);
        lua_setfield(L, -2, "__call");
        return 0;
    }

    int LuaObject::setupStructMT(lua_State* L) {
        lua_pushcfunction(L,structConstruct);
        lua_setfield(L, -2, "__call");
        return 0;
    }

    int LuaObject::setupInstanceMT(lua_State* L) {
        lua_pushcfunction(L,instanceIndex);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L,newinstanceIndex);
        lua_setfield(L, -2, "__newindex");
        return 0;
    }

    int LuaObject::setupInstanceStructMT(lua_State* L) {
        lua_pushcfunction(L,instanceStructIndex);
        lua_setfield(L, -2, "__index");
        return 0;
    }
}
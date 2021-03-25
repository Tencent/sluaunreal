// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#ifdef _WIN32
#pragma warning (push)
#pragma warning (disable : 4018)
#endif

#include "LuaObject.h"
#include "LuaVar.h"
#include "LuaDelegate.h"
#include "LatentDelegate.h"
#include "UObject/StructOnScope.h"
#include "UObject/Class.h"
#include "UObject/UnrealType.h"
#include "UObject/Stack.h"
#include "Blueprint/WidgetTree.h"
#include "LuaWidgetTree.h"
#include "LuaArray.h"
#include "LuaMap.h"
#include "LuaSet.h"
#include "Log.h"
#include "LuaState.h"
#include "LuaWrapper.h"
#include "SluaUtil.h"
#include "LuaReference.h"
#include "LuaBase.h"
#include "Engine/UserDefinedEnum.h"

namespace NS_SLUA { 
	static const FName NAME_LatentInfo = TEXT("LatentInfo");

	TMap<FFieldClass*,LuaObject::PushPropertyFunction> pusherMap;
	TMap<FFieldClass*,LuaObject::CheckPropertyFunction> checkerMap;

	struct ExtensionField {
		bool isFunction = true;
		union {
			struct {
				lua_CFunction getter;
				lua_CFunction setter;
			};
			lua_CFunction func;
		};

		ExtensionField(lua_CFunction funcf) : isFunction(true), func(funcf) {
			ensure(funcf);
		}
		ExtensionField(lua_CFunction getterf, lua_CFunction setterf) 
			: isFunction(false)
			, getter(getterf)
			, setter(setterf) {}
	};

    #if ENGINE_MINOR_VERSION >= 23 && (PLATFORM_MAC || PLATFORM_IOS)
    struct FNewFrame : public FOutputDevice
        {
        public:
            // Variables.
            UFunction* Node;
            UObject* Object;
            uint8* Code;
            uint8* Locals;
            
            FProperty* MostRecentProperty;
            uint8* MostRecentPropertyAddress;
            
            /** The execution flow stack for compiled Kismet code */
            FlowStackType FlowStack;
            
            /** Previous frame on the stack */
            FFrame* PreviousFrame;
            
            /** contains information on any out parameters */
            FOutParmRec* OutParms;
            
            /** If a class is compiled in then this is set to the property chain for compiled-in functions. In that case, we follow the links to setup the args instead of executing by code. */
            FField* PropertyChainForCompiledIn;
            
            /** Currently executed native function */
            UFunction* CurrentNativeFunction;
            
            bool bArrayContextFailed;
        public:
            
            // Constructors.
            FNewFrame( UObject* InObject, UFunction* InNode, void* InLocals, FFrame* InPreviousFrame = NULL, FField* InPropertyChainForCompiledIn = NULL )
            : Node(InNode)
            , Object(InObject)
            , Code(InNode->Script.GetData())
            , Locals((uint8*)InLocals)
            , MostRecentProperty(NULL)
            , MostRecentPropertyAddress(NULL)
            , PreviousFrame(InPreviousFrame)
            , OutParms(NULL)
            , PropertyChainForCompiledIn(InPropertyChainForCompiledIn)
            , CurrentNativeFunction(NULL)
            , bArrayContextFailed(false)
            {
        #if DO_BLUEPRINT_GUARD
                FBlueprintExceptionTracker::Get().ScriptStack.Push((FFrame *)this);
        #endif
            }
            
            virtual ~FNewFrame()
            {
                #if DO_BLUEPRINT_GUARD
                    FBlueprintExceptionTracker& BlueprintExceptionTracker = FBlueprintExceptionTracker::Get();
                    if (BlueprintExceptionTracker.ScriptStack.Num())
                    {
                        BlueprintExceptionTracker.ScriptStack.Pop(false);
                    }
                #endif
            }
            
            virtual void Serialize( const TCHAR* V, ELogVerbosity::Type Verbosity, const class FName& Category ) {};
        };
    #endif
    
    TMap< UClass*, TMap<FString, ExtensionField> > extensionMMap;
    TMap< UClass*, TMap<FString, ExtensionField> > extensionMMap_static;

    namespace ExtensionMethod{
        void init();
    }

    DefTypeName(LuaStruct)

    // construct lua struct
    LuaStruct::LuaStruct(uint8* b,uint32 s,UScriptStruct* u)
        :buf(b),size(s),uss(u) {
    }

    LuaStruct::~LuaStruct() {
		if (buf) {
			uss->DestroyStruct(buf);
			FMemory::Free(buf);
			buf = nullptr;
		}
    }

	void LuaStruct::AddReferencedObjects(FReferenceCollector& Collector) {
		Collector.AddReferencedObject(uss);
		LuaReference::addRefByStruct(Collector, uss, buf);
	}

    void LuaObject::addExtensionMethod(UClass* cls,const char* n,lua_CFunction func,bool isStatic) {
        if(isStatic) {
            auto& extmap = extensionMMap_static.FindOrAdd(cls);
            extmap.Add(n, ExtensionField(func));
        }
        else {
            auto& extmap = extensionMMap.FindOrAdd(cls);
            extmap.Add(n, ExtensionField(func));
        }
    }

	void LuaObject::addExtensionProperty(UClass * cls, const char * n, lua_CFunction getter, lua_CFunction setter, bool isStatic)
	{
		if (isStatic) {
			auto& extmap = extensionMMap_static.FindOrAdd(cls);
			extmap.Add(n, ExtensionField(getter,setter));
		}
		else {
			auto& extmap = extensionMMap.FindOrAdd(cls);
			extmap.Add(n, ExtensionField(getter, setter));
		}
	}

    static int findMember(lua_State* L,const char* name) {
       int popn = 0;
        if ((++popn, lua_getfield(L, -1, name) != 0)) {
			lua_remove(L, -2); // remove mt
            return 1;
        } else if ((++popn, lua_getfield(L, -2, ".get")) && (++popn, lua_getfield(L, -1, name))) {
            lua_pushvalue(L, 1);
            lua_call(L, 1, 1);
			lua_remove(L, -2); // remove .get
            return 1;
        } else {
            // find base
            lua_pop(L, popn);
            lua_getfield(L,-1, "__base");
			luaL_checktype(L, -1, LUA_TTABLE);
			// for each base
            {
                size_t cnt = lua_rawlen(L,-1);
                int r = 0;
                for(size_t n=0;n<cnt;n++) {
                    lua_geti(L,-1,n+1);
                    const char* tn = lua_tostring(L,-1);
                    lua_pop(L,1); // pop tn
                    luaL_getmetatable(L,tn);
					luaL_checktype(L, -1, LUA_TTABLE);
					if (findMember(L, name)) return 1;
                }
                lua_remove(L,-2); // remove __base
                return r;
            }
        }
    }

	static bool setMember(lua_State* L, const char* name) {
		int popn = 0;
		if ((++popn, lua_getfield(L, -1, ".set")) && (++popn, lua_getfield(L, -1, name))) {
			// push ud
			lua_pushvalue(L, 1);
			// push value
			lua_pushvalue(L, 3);
			// call setter
			lua_call(L, 2, 0);
			lua_pop(L, 1); // pop .set
			return true;
		}
		else {
			// find base
			lua_pop(L, popn);
			lua_getfield(L, -1, "__base");
			luaL_checktype(L, -1, LUA_TTABLE);
			// for each base
			{
				size_t cnt = lua_rawlen(L, -1);
				for (size_t n = 0; n < cnt; n++) {
					lua_geti(L, -1, n + 1);
					const char* tn = lua_tostring(L, -1);
					lua_pop(L, 1); // pop tn
					luaL_getmetatable(L, tn);
					luaL_checktype(L, -1, LUA_TTABLE);
					if (setMember(L, name)) return true;
				}
			}
			// pop __base
			lua_pop(L, 1);
			return false;
		}
	}

	int LuaObject::classIndex(lua_State* L) {
		lua_getmetatable(L, 1);
		const char* name = checkValue<const char*>(L, 2);
		if (!findMember(L, name))
			luaL_error(L, "can't get %s", name);
		lua_remove(L, -2);
		return 1;
	}

	int LuaObject::classNewindex(lua_State* L) {
		lua_getmetatable(L, 1);
		const char* name = checkValue<const char*>(L, 2);
		if(!setMember(L, name))
			luaL_error(L, "can't set %s", name);
		lua_pop(L, 1);
		return 0;
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
		lua_pushglobaltable(L);				    // _G
		lua_newtable(L);							// local t = {}
		lua_pushvalue(L, -1);
		lua_setfield(L, -3, tn);					// _G[tn] = t
		lua_remove(L, -2);						// remove global table;

        lua_newtable(L);
		lua_pushvalue(L, -1);
		lua_setmetatable(L, -3);					// setmetatable(t, mt)
		setMetaMethods(L);

		luaL_newmetatable(L, tn);
		setMetaMethods(L);
	}

    void LuaObject::newTypeWithBase(lua_State* L, const char* tn, std::initializer_list<const char*> bases) {
		newType(L,tn);

        // create base table
        lua_newtable(L);
        lua_pushvalue(L,-1);
        lua_setfield(L,-3,"__base");
        
        for(auto base:bases) {
            if(strlen(base)>0) {
                lua_pushstring(L,base);
                size_t p = lua_rawlen(L,-2);
                lua_seti(L,-2,p+1);
            }
        }
        // pop __base table
        lua_pop(L,1);
	}

	int LuaObject::push(lua_State * L, const LuaLString& lstr)
	{
		lua_pushlstring(L, lstr.buf, lstr.len);
		return 1;
	}

	bool LuaObject::isBaseTypeOf(lua_State* L,const char* tn,const char* base) {
        AutoStack as(L);
        int t = luaL_getmetatable(L,tn);
        if(t!=LUA_TTABLE)
            return false;

        if(lua_getfield(L,-1,"__base")==LUA_TTABLE) {
            size_t len = lua_rawlen(L,-1);
            for(int n=0;n<len;n++) {
                if(lua_geti(L,-1,n+1)==LUA_TSTRING) {
                    const char* maybeBase = lua_tostring(L,-1);
                    if(strcmp(maybeBase,base)==0) return true;
                    else return isBaseTypeOf(L,maybeBase,base);
                }
            }
            return false;
        }
        return false;
    }

	void LuaObject::addMethod(lua_State* L, const char* name, lua_CFunction func, bool isInstance) {
		lua_pushcfunction(L, func);
		lua_setfield(L, isInstance ? -2 : -3, name);
	}

    void LuaObject::addGlobalMethod(lua_State* L, const char* name, lua_CFunction func) {
		lua_pushcfunction(L, func);
        lua_setglobal(L,name);
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

	void LuaObject::finishType(lua_State* L, const char* tn, lua_CFunction ctor, lua_CFunction gc, lua_CFunction strHint) {
        if(ctor) {
		    lua_pushcclosure(L, ctor, 0);
		    lua_setfield(L, -3, "__call");
        }
        if(gc) {
		    lua_pushcclosure(L, gc, 0); // t, mt, _instance, __gc
    		lua_setfield(L, -2, "__gc"); // t, mt, _instance
        }
        if(strHint) {
            lua_pushcfunction(L, strHint);
            lua_setfield(L, -2, "__tostring");
        }
        lua_pop(L,3);
	}

	bool LuaObject::matchType(lua_State* L, int p, const char* tn, bool noprefix) {
		AutoStack autoStack(L);
		if (!lua_isuserdata(L, p)) {
			return false;
		}
		lua_getmetatable(L, p);
		if (lua_isnil(L, -1)) {
			return false;
		}
		lua_getfield(L, -1, "__name");
		if (lua_isnil(L, -1)) {
			return false;
		}
		auto name = luaL_checkstring(L, -1);
		// skip first prefix "F" or "U" or "A"
		if(noprefix) return strcmp(name+1, tn) == 0;
		else return strcmp(name,tn)==0;
	}

    LuaObject::PushPropertyFunction LuaObject::getPusher(FFieldClass* cls) {
        auto it = pusherMap.Find(cls);
        if(it!=nullptr)
            return *it;
        return nullptr;
    }

    LuaObject::CheckPropertyFunction LuaObject::getChecker(FFieldClass* cls) {
        auto it = checkerMap.Find(cls);
        if(it!=nullptr)
            return *it;
        return nullptr;
    }

    LuaObject::PushPropertyFunction LuaObject::getPusher(FProperty* prop) {
        return getPusher(prop->GetClass());
    }

    LuaObject::CheckPropertyFunction LuaObject::getChecker(FProperty* prop) {
        return getChecker(prop->GetClass());        
    }

    

    void regPusher(FFieldClass* cls,LuaObject::PushPropertyFunction func) {
		pusherMap.Add(cls, func);
    }

    void regChecker(FFieldClass* cls,LuaObject::CheckPropertyFunction func) {
		checkerMap.Add(cls, func);
    }

    int classConstruct(lua_State* L) {
        UClass* cls = LuaObject::checkValue<UClass*>(L, 1);
		UObject* outter = LuaObject::checkValueOpt<UObject*>(L, 2, (UObject*)GetTransientPackage());
		if (cls && !outter->IsA(cls->ClassWithin)) {
			luaL_error(L, "Can't create object in %s", TCHAR_TO_UTF8(*outter->GetClass()->GetName()));
		}
		FName name = LuaObject::checkValueOpt<FName>(L, 3, FName(NAME_None));
        if(cls) {
            UObject* obj = NewObject<UObject>(outter,cls,name);
            if(obj) {
                LuaObject::push(L,obj,false,true);
                return 1;
            }
        }
        return 0;
    }

    int searchExtensionMethod(lua_State* L,UClass* cls,const char* name,bool isStatic=false) {

        // search class and its super
        TMap<FString,ExtensionField>* mapptr=nullptr;
        while(cls!=nullptr) {
            mapptr = isStatic?extensionMMap_static.Find(cls):extensionMMap.Find(cls);
            if(mapptr!=nullptr) {
                // find field
                auto fieldptr = mapptr->Find(name);
				if (fieldptr != nullptr) {
					// is function
					if (fieldptr->isFunction) {
						lua_pushcfunction(L, fieldptr->func);
						return 1;
					} 
					// is property
					else {
						if (!fieldptr->getter) luaL_error(L, "Property %s is set only", name);
						lua_pushcfunction(L, fieldptr->getter);
						if (!isStatic) {
							lua_pushvalue(L, 1); // push self
							lua_call(L, 1, 1);
						} else 
							lua_call(L, 0, 1);
						return 1;
					}
				}
            }
            cls=cls->GetSuperClass();
        }   
        return 0;
    }

    int searchExtensionMethod(lua_State* L,UObject* o,const char* name,bool isStatic=false) {
        auto cls = o->GetClass();
        return searchExtensionMethod(L,cls,name,isStatic);
    }

    int classIndex(lua_State* L) {
        UClass* cls = LuaObject::checkValue<UClass*>(L, 1);
        const char* name = LuaObject::checkValue<const char*>(L, 2);
        
        UFunction* func = LuaObject::findCacheFunction(L, cls, name);;
		if (func) {
			return LuaObject::push(L, func, cls);
		}

		// get blueprint member
		func = cls->FindFunctionByName(UTF8_TO_TCHAR(name));
    	if (func) {
			LuaObject::cacheFunction(L, cls, name, func);
			return LuaObject::push(L, func, cls);
    	}
        return searchExtensionMethod(L,cls,name,true);
    }

    int structConstruct(lua_State* L) {
        UScriptStruct* uss = LuaObject::checkValue<UScriptStruct*>(L, 1);
        if(uss) {
            uint32 size = uss->GetStructureSize() ? uss->GetStructureSize() : 1;
            
            uint8* buf = (uint8*)FMemory::Malloc(size);
            uss->InitializeStruct(buf);
            LuaStruct* ls=new LuaStruct(buf,size,uss);
            LuaObject::push(L,ls);
            return 1;
        }
        return 0;
    }

    int fillParamFromState(lua_State* L,FProperty* prop,uint8* params,int i) {

        // if is out param, can accept nil
        uint64 propflag = prop->GetPropertyFlags();
        if(propflag&CPF_OutParm && lua_isnil(L,i))
            return prop->GetSize();

        auto checker = LuaObject::getChecker(prop);
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

    void LuaObject::fillParam(lua_State* L,int i,UFunction* func,uint8* params) {
		auto funcFlag = func->FunctionFlags;
        for(TFieldIterator<FProperty> it(func);it && (it->PropertyFlags&CPF_Parm);++it) {
            FProperty* prop = *it;
            uint64 propflag = prop->GetPropertyFlags();
			if (funcFlag & EFunctionFlags::FUNC_Native) {
				if ((propflag&CPF_ReturnParm))
					continue;
			}
			else if (IsRealOutParam(propflag))
				continue;

			if (prop->GetFName() == NAME_LatentInfo) {
				// bind a callback to the latent function
				lua_State *mainThread = G(L)->mainthread;

				ULatentDelegate *obj = LuaObject::getLatentDelegate(mainThread);
				int threadRef = obj->getThreadRef(L);
				FLatentActionInfo LatentActionInfo(threadRef, GetTypeHash(FGuid::NewGuid()), *ULatentDelegate::NAME_LatentCallback, obj);

				prop->CopySingleValue(prop->ContainerPtrToValuePtr<void>(params), &LatentActionInfo);
			}
			else {
				fillParamFromState(L, prop, params + prop->GetOffset_ForInternal(), i);
				i++;
			}
        }
    }

	void LuaObject::callRpc(lua_State* L, UObject* obj, UFunction* func, uint8* params) {
		//// call rpc without outparams
		const bool bHasReturnParam = func->ReturnValueOffset != MAX_uint16;
		uint8* ReturnValueAddress = bHasReturnParam ? ((uint8*)params + func->ReturnValueOffset) : nullptr;
        
        #if ENGINE_MINOR_VERSION >= 23 && (PLATFORM_MAC || PLATFORM_IOS)
            FNewFrame NewStack(obj, func, params, NULL, func->ChildProperties);
        #else
            FFrame NewStack(obj, func, params, NULL, func->ChildProperties);
        #endif
        
        #if ENGINE_MINOR_VERSION < 25
            if (func->ReturnValueOffset != MAX_uint16) {
                FProperty* ReturnProperty = func->GetReturnProperty();
                if (ensure(ReturnProperty)) {
                    FOutParmRec* RetVal = (FOutParmRec*)FMemory_Alloca(sizeof(FOutParmRec));

                    /* Our context should be that we're in a variable assignment to the return value, so ensure that we have a valid property to return to */
                    RetVal->PropAddr = (uint8*)FMemory_Alloca(ReturnProperty->GetSize());
                    RetVal->Property = ReturnProperty;
                    NewStack.OutParms = RetVal;
                }
            }

            NewStack.Locals = params;
            FOutParmRec** LastOut = &NewStack.OutParms;

            for (FProperty* Property = (FProperty*)func->Children; Property!=nullptr; Property = (FProperty*)Property->Next){
                if (Property->PropertyFlags & CPF_OutParm){

                    CA_SUPPRESS(6263)
                        FOutParmRec* Out = (FOutParmRec*)FMemory_Alloca(sizeof(FOutParmRec));
                    // set the address and property in the out param info
                    // warning: Stack.MostRecentPropertyAddress could be NULL for optional out parameters
                    // if that's the case, we use the extra memory allocated for the out param in the function's locals
                    // so there's always a valid address
                    Out->PropAddr = Property->ContainerPtrToValuePtr<uint8>(NewStack.Locals);
                    Out->Property = Property;

                    // add the new out param info to the stack frame's linked list
                    if (*LastOut) {
                        (*LastOut)->NextOutParm = Out;
                        LastOut = &(*LastOut)->NextOutParm;
                    } else {
                        *LastOut = Out;
                    }
                } else {
                    // copy the result of the expression for this parameter into the appropriate part of the local variable space
                    uint8* Param = Property->ContainerPtrToValuePtr<uint8>(NewStack.Locals);
                    Property->InitializeValue_InContainer(NewStack.Locals);
                }
            }
        #else
            NewStack.OutParms = nullptr;
        #endif
    
        #if ENGINE_MINOR_VERSION >= 23 && (PLATFORM_MAC || PLATFORM_IOS)
            FFrame *frame = (FFrame *)&NewStack;
    		obj->CallRemoteFunction(func, params, NewStack.OutParms, frame);
        #else
    		obj->CallRemoteFunction(func, params, NewStack.OutParms, &NewStack);
        #endif
	}

	void LuaObject::callUFunction(lua_State* L, UObject* obj, UFunction* func, uint8* params) {
		auto ff = func->FunctionFlags;
		// it's an RPC function
		if (ff&FUNC_Net)
			LuaObject::callRpc(L, obj, func, params);
		else
		// it's a local function
			obj->ProcessEvent(func, params);
	}

    // handle return value and out params
    int LuaObject::returnValue(lua_State* L,UFunction* func,uint8* params,NewObjectRecorder* objRecorder) {

        // check is function has return value
		const bool bHasReturnParam = func->ReturnValueOffset != MAX_uint16;

		// put return value as head
        int ret = 0;
        if(bHasReturnParam) {
            FProperty* p = func->GetReturnProperty();
            ret += LuaObject::push(L,p,params+p->GetOffset_ForInternal(),objRecorder);
        }

		bool isLatentFunction = false;
        // push out parms
        for(TFieldIterator<FProperty> it(func);it;++it) {
            FProperty* p = *it;
            uint64 propflag = p->GetPropertyFlags();
            // skip return param
            if(propflag&CPF_ReturnParm)
                continue;

			if (p->GetFName() == NAME_LatentInfo) {
				isLatentFunction = true;
			}
			else if (IsRealOutParam(propflag)) { // out params should be not const and not readonly
                ret += LuaObject::push(L,p,params+p->GetOffset_ForInternal(),objRecorder);
			}
        }
        
		if (isLatentFunction) {
			return lua_yield(L, ret);
		}
		else {
			return ret;
		}
    }
   
    int ufuncClosure(lua_State* L) {
        lua_pushvalue(L,lua_upvalueindex(1));
        void* ud = lua_touserdata(L, -1);
        lua_pop(L, 1); // pop ud of func
        
        if(!ud) luaL_error(L, "Call ufunction error");

        lua_pushvalue(L,lua_upvalueindex(2));
        UClass* cls = reinterpret_cast<UClass*>(lua_touserdata(L, -1));
        lua_pop(L,1); // pop staticfunc flag
        
        UObject* obj;
        int offset=1;
        // use ClassDefaultObject if is static function call 
        if(cls) obj = cls->ClassDefaultObject;
        // use obj instance if is member function call
        // and offset set 2 to skip self
        else {
            obj = LuaObject::checkValue<UObject*>(L, 1);
            offset++;
        }
        
        UFunction* func = reinterpret_cast<UFunction*>(ud);
        
		NewObjectRecorder objectRecorder(L);

		uint8* params = (uint8*)FMemory_Alloca(func->ParmsSize);
		FMemory::Memzero(params, func->ParmsSize);
		for (TFieldIterator<FProperty> it(func); it && it->HasAnyPropertyFlags(CPF_Parm); ++it)
		{
			FProperty* localProp = *it;
			checkSlow(localProp);
			if (!localProp->HasAnyPropertyFlags(CPF_ZeroConstructor))
			{
				localProp->InitializeValue_InContainer(params);
			}
		}
    	
		LuaObject::fillParam(L, offset, func, params);
		{
			// call function with params
			LuaObject::callUFunction(L, obj, func, params);
		}
		// return value to push lua stack
		int outParamCount = LuaObject::returnValue(L, func, params, &objectRecorder);

		for (TFieldIterator<FProperty> it(func); it && (it->HasAnyPropertyFlags(CPF_Parm)); ++it)
		{
			it->DestroyValue_InContainer(params);
		}

		return outParamCount;
    }

    // find ufunction from cache
    UFunction* LuaObject::findCacheFunction(lua_State* L, UClass* cls,const char* fname) {
        auto state = LuaState::get(L);
		return state->classMap.findFunc(cls, fname);
    }

    // cache ufunction for reuse
    void LuaObject::cacheFunction(lua_State* L,UClass* cls,const char* fname,UFunction* func) {
        auto state = LuaState::get(L);
        state->classMap.cacheFunc(cls,fname,func);
    }

    FProperty* LuaObject::findCacheProperty(lua_State* L, UClass* cls, const char* pname)
    {
		auto state = LuaState::get(L);
		return state->classMap.findProp(cls, pname);
    }

    void LuaObject::cacheProperty(lua_State* L, UClass* cls, const char* pname, FProperty* property)
    {
		auto state = LuaState::get(L);
		state->classMap.cacheProp(cls, pname, property);
    }

	// cache class property's
	void cachePropertys(lua_State* L, UClass* cls) {
		auto PropertyLink = cls->PropertyLink;
		for (FProperty* Property = PropertyLink; Property != NULL; Property = Property->PropertyLinkNext) {
			LuaObject::cacheProperty(L, cls, TCHAR_TO_UTF8(*(Property->GetName())), Property);
		}
	}

    int instanceIndex(lua_State* L) {
        UObject* obj = LuaObject::checkValue<UObject*>(L, 1);
        const char* name = LuaObject::checkValue<const char*>(L, 2);

		UClass* cls = obj->GetClass();
        FProperty* up = LuaObject::findCacheProperty(L, cls, name);
        if (up)
        {
            return LuaObject::push(L, up, obj, nullptr);
        }

        UFunction* func = LuaObject::findCacheFunction(L, cls, name);
        if (func)
        {
            return LuaObject::push(L, func);
        }

        // get blueprint member
		FName wname(UTF8_TO_TCHAR(name));
        func = cls->FindFunctionByName(wname);
        if(!func) {
			cachePropertys(L, cls);

			up = LuaObject::findCacheProperty(L, cls, name);
            if (up) {
                return LuaObject::push(L, up, obj, nullptr);
            }
            
            // search extension method
            return searchExtensionMethod(L, obj, name);
        }
        else {   
			LuaObject::cacheFunction(L, cls, name, func);
            return LuaObject::push(L,func);
        }
    }

    int newinstanceIndex(lua_State* L) {
        UObject* obj = LuaObject::checkValue<UObject*>(L, 1);
        const char* name = LuaObject::checkValue<const char*>(L, 2);
        UClass* cls = obj->GetClass();
		FProperty* up = LuaObject::findCacheProperty(L, cls, name);
		if (!up)
		{
			cachePropertys(L, cls);
			up = LuaObject::findCacheProperty(L, cls, name);
		}
		if (!up) luaL_error(L, "Property %s not found", name);
        if(up->GetPropertyFlags() & CPF_BlueprintReadOnly)
            luaL_error(L,"Property %s is readonly",name);

        auto checker = LuaObject::getChecker(up);
        if(!checker) luaL_error(L,"Property %s type is not support",name);
        // set property value
        checker(L,up,up->ContainerPtrToValuePtr<uint8>(obj),3);
        return 0;
    }

	FProperty* FindStructPropertyByName(UScriptStruct* scriptStruct, const char* name)
	{
		if (scriptStruct->IsNative())
		{
			return scriptStruct->FindPropertyByName(UTF8_TO_TCHAR(name));
		}

		FString propName = UTF8_TO_TCHAR(name);
		for (FProperty* Property = scriptStruct->PropertyLink; Property != nullptr; Property = Property->PropertyLinkNext)
		{
			FString fieldName = Property->GetName();
			if (fieldName.StartsWith(propName, ESearchCase::CaseSensitive))
			{
				int index = fieldName.Len();
				for (int i = 0; i < 2; ++i)
				{
					int findIndex = fieldName.Find(TEXT("_"), ESearchCase::CaseSensitive, ESearchDir::FromEnd, index);
					if (findIndex != INDEX_NONE)
					{
						index = findIndex;
					}
				}
				if (propName.Len() == index)
				{
					return Property;
				}
			}
		}

		return nullptr;
	}

    int instanceStructIndex(lua_State* L) {
        LuaStruct* ls = LuaObject::checkValue<LuaStruct*>(L, 1);
        const char* name = LuaObject::checkValue<const char*>(L, 2);
        
        auto* cls = ls->uss;
        FProperty* up = FindStructPropertyByName(cls, name);
        if(!up) return 0;
        return LuaObject::push(L,up,ls->buf+up->GetOffset_ForInternal(),nullptr);
    }

    int newinstanceStructIndex(lua_State* L) {
        LuaStruct* ls = LuaObject::checkValue<LuaStruct*>(L, 1);
        const char* name = LuaObject::checkValue<const char*>(L, 2);

        auto* cls = ls->uss;
        FProperty* up = FindStructPropertyByName(cls, name);
        if (!up) luaL_error(L, "Can't find property named %s", name);
        if (up->GetPropertyFlags() & CPF_BlueprintReadOnly)
            luaL_error(L, "Property %s is readonly", name);

        auto checker = LuaObject::getChecker(up);
        if(!checker) luaL_error(L,"Property %s type is not support",name);

        checker(L, up, ls->buf + up->GetOffset_ForInternal(), 3);
        return 0;
    }

    int instanceIndexSelf(lua_State* L) {
        lua_getmetatable(L,1);
        const char* name = LuaObject::checkValue<const char*>(L, 2);
        
        lua_getfield(L,-1,name);
        lua_remove(L,-2); // remove mt of ud
        return 1;
    }

	int LuaObject::objectToString(lua_State* L)
	{
        const int BufMax = 128;
        static char buffer[BufMax] = { 0 };
		UObject* obj = LuaObject::testudata<UObject>(L, 1);
		if (obj) {
			auto clsname = obj->GetClass()->GetFName().ToString();
			auto objname = obj->GetFName().ToString();
			snprintf(buffer, BufMax, "%s: %s %p",TCHAR_TO_UTF8(*clsname),TCHAR_TO_UTF8(*objname), obj);
		}
        else {
            // if ud isn't a uobject, get __name of metatable to cast it to string
            const void* ptr = lua_topointer(L,1);
            int tt = luaL_getmetafield(L,1,"__name");
            // should have __name field
            if(tt==LUA_TSTRING) {
                const char* metaname = lua_tostring(L,-1);
                snprintf(buffer, BufMax, "%s: %p", metaname,ptr);
            }
            if(tt!=LUA_TNIL)
                lua_pop(L,1);
        }

		lua_pushstring(L, buffer);
		return 1;
	}

	void LuaObject::setupMetaTable(lua_State* L, const char* tn, lua_CFunction setupmt, lua_CFunction gc)
	{
		if (luaL_newmetatable(L, tn)) {
			if (setupmt)
				setupmt(L);
			if (gc) {
				lua_pushcfunction(L, gc);
				lua_setfield(L, -2, "__gc");
			}
		}
		lua_setmetatable(L, -2);
	}

	void LuaObject::setupMetaTable(lua_State* L, const char* tn, lua_CFunction setupmt, int gc)
	{
		if (luaL_newmetatable(L, tn)) {
			if (setupmt)
				setupmt(L);
			if (gc) {
				lua_pushvalue(L, gc);
				lua_setfield(L, -2, "__gc");
			}
		}
		lua_setmetatable(L, -2);
	}

	void LuaObject::setupMetaTable(lua_State* L, const char* tn, lua_CFunction gc)
	{
		luaL_getmetatable(L, tn);
		if (lua_isnil(L, -1))
			luaL_error(L, "Can't find type %s exported", tn);

		lua_pushcfunction(L, gc);
		lua_setfield(L, -2, "__gc");
		lua_setmetatable(L, -2);
	}

    template<typename T>
    int pushUProperty(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto p= CastFieldChecked<T>(prop);
        ensure(p);
        return LuaObject::push(L,p->GetPropertyValue(parms));
    }

	// treat uint8* as string
	int pushUByteProperty(lua_State* L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
		auto p = CastFieldChecked<FByteProperty>(prop);
		ensure(p);
		if (p->ArrayDim > 1 ) {
			uint8* ptr = p->GetPropertyValuePtr(parms);
			lua_pushlstring(L, (char*) ptr, p->ArrayDim);
			return 1;
		}
		else
			return LuaObject::push(L, p->GetPropertyValue(parms));
	}

	int pushEnumProperty(lua_State* L, FProperty* prop, uint8* parms,NewObjectRecorder* objRecorder) {
		auto p = CastFieldChecked<FEnumProperty>(prop);
		ensure(p);
		auto p2 = p->GetUnderlyingProperty();
		ensure(p2);
		int i = p2->GetSignedIntPropertyValue(parms);
		return LuaObject::push(L, i);
	}

    int pushUArrayProperty(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto p = CastFieldChecked<FArrayProperty>(prop);
        ensure(p);
        FScriptArray* v = p->GetPropertyValuePtr(parms);
		return LuaArray::push(L, p->Inner, v);
    }

    int pushUMapProperty(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto p = CastFieldChecked<FMapProperty>(prop);
        ensure(p);
		FScriptMap* v = p->GetPropertyValuePtr(parms);
		return LuaMap::push(L, p->KeyProp, p->ValueProp, v);
    }

	int pushUSetProperty(lua_State* L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
		auto p = CastFieldChecked<FSetProperty>(prop);
		ensure(p);
		return LuaSet::push(L, p->ElementProp, p->GetPropertyValuePtr(parms));
	}

	int pushUWeakProperty(lua_State* L, FProperty* prop, uint8* parms,NewObjectRecorder* objRecorder) {
		auto p = CastFieldChecked<FWeakObjectProperty>(prop);
		ensure(p);
		FWeakObjectPtr v = p->GetPropertyValue(parms);
		return LuaObject::push(L, v);
	}

    int checkUArrayProperty(lua_State* L,FProperty* prop,uint8* parms,int i) {
        auto p = CastFieldChecked<FArrayProperty>(prop);
        ensure(p);
		if (lua_istable(L, i)) {
			int arraySize = lua_rawlen(L, i);
			if (arraySize <= 0)
				return 0;
			int tableIndex = i;
			if (i < 0 && i > LUA_REGISTRYINDEX) {
				tableIndex = i - 1;
			}

			FScriptArrayHelper arrayHelper(p, parms);
			arrayHelper.AddValues(arraySize);

			auto checker = LuaObject::getChecker(p->Inner);

			int index = 0;

			lua_pushnil(L);
			while (index < arraySize && lua_next(L, tableIndex) != 0) {
				checker(L, p->Inner, arrayHelper.GetRawPtr(index++), -1);
				lua_pop(L, 1);
			}
			return 0;
		}

        CheckUD(LuaArray,L,i);
        LuaArray::clone((FScriptArray*)parms,p->Inner,UD->get());
        return 0;
    }

	int checkUMapProperty(lua_State* L, FProperty* prop, uint8* parms, int i) {
		auto p = CastFieldChecked<FMapProperty>(prop);
		ensure(p);

		if (lua_istable(L, i)) {
			int tableIndex = i;
			if (i < 0 && i > LUA_REGISTRYINDEX) {
				tableIndex = i - 1;
			}
			
			FScriptMapHelper mapHelper(p, parms);

			lua_pushnil(L);
			while (lua_next(L, tableIndex) != 0) {
				FDefaultConstructedPropertyElement tempKey(p->KeyProp);
				FDefaultConstructedPropertyElement tempValue(p->ValueProp);
				auto keyPtr = tempKey.GetObjAddress();
				auto valuePtr = tempValue.GetObjAddress();
				auto keyChecker = LuaObject::getChecker(p->KeyProp);
				auto valueChecker = LuaObject::getChecker(p->ValueProp);
				keyChecker(L, p->KeyProp, (uint8*)keyPtr, -2);
				valueChecker(L, p->ValueProp, (uint8*)valuePtr, -1);
				mapHelper.AddPair(keyPtr, valuePtr);
				lua_pop(L, 1);
			}
			return 0;
		}

		CheckUD(LuaMap, L, i);
        LuaMap::clone((FScriptMap*)parms,p->KeyProp,p->ValueProp,UD->get());
		return 0;
	}

	int checkUSetProperty(lua_State* L, UProperty* prop, uint8* params, int i) {
		auto p = CastFieldChecked<FSetProperty>(prop);
		ensure(p);
 
    	if (lua_istable(L, i)) {
			int tableIndex = i;
    		if (i <0 && i > LUA_REGISTRYINDEX) {
				tableIndex = i - 1;
    		}
 
			FScriptSetHelper SetHelper(p, params);
    		
			lua_pushnil(L);

    		const auto ElementChecker = LuaObject::getChecker(p->ElementProp);

			while (lua_next(L, tableIndex) != 0) {
				FDefaultConstructedPropertyElement TempInElement(p->ElementProp);
				const auto ElementPtr = TempInElement.GetObjAddress();
				ElementChecker(L, p->ElementProp, static_cast<uint8*>(ElementPtr), -1);
				SetHelper.AddElement(ElementPtr);
				lua_pop(L, 1);
			}
			return 0;
    	}
		CheckUD(LuaSet, L, i);
		LuaSet::clone(reinterpret_cast<FScriptSet*>(params), p->ElementProp, UD->get());
		return 0;
    }

    int pushUStructProperty(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto p = CastFieldChecked<FStructProperty>(prop);
        ensure(p);
        auto uss = p->Struct;

		if (LuaWrapper::pushValue(L, p, uss, parms))
			return 1;

		if (uss->GetName() == "LuaBPVar") {
			((FLuaBPVar*)parms)->value.push(L);
			return 1;
		}

		uint32 size = uss->GetStructureSize() ? uss->GetStructureSize() : 1;
		uint8* buf = (uint8*)FMemory::Malloc(size);
		uss->InitializeStruct(buf);
		uss->CopyScriptStruct(buf, parms);
		return LuaObject::push(L, new LuaStruct(buf,size,uss));
    }  

	int pushUDelegateProperty(lua_State* L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
		auto p = CastFieldChecked<FDelegateProperty>(prop);
		ensure(p);
		FScriptDelegate* delegate = p->GetPropertyValuePtr(parms);
		return LuaDelegate::push(L, delegate, p->SignatureFunction, prop->GetNameCPP());
	}

    int pushUMulticastDelegateProperty(lua_State* L,FProperty* prop,uint8* parms, NewObjectRecorder* objRecorder) {
        auto p = CastFieldChecked<FMulticastDelegateProperty>(prop);
        ensure(p);
		FMulticastScriptDelegate* delegate = const_cast<FMulticastScriptDelegate*>(p->GetMulticastDelegate(parms));
		return LuaMultiDelegate::push(L, delegate, p->SignatureFunction, prop->GetNameCPP());
    }

	int pushUMulticastInlineDelegateProperty(lua_State* L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
		auto p = CastFieldChecked<FMulticastInlineDelegateProperty>(prop);
		ensure(p);
		FMulticastScriptDelegate* delegate = const_cast<FMulticastScriptDelegate*>(p->GetMulticastDelegate(parms));
		return LuaMultiDelegate::push(L, delegate, p->SignatureFunction, prop->GetNameCPP());
	}

	int pushUMulticastSparseDelegateProperty(lua_State* L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
		auto p = CastFieldChecked<FMulticastSparseDelegateProperty>(prop);
		ensure(p);
		FMulticastScriptDelegate* delegate = const_cast<FMulticastScriptDelegate*>(p->GetMulticastDelegate(parms));
		return LuaMultiDelegate::push(L, delegate, p->SignatureFunction, prop->GetNameCPP());
	}

    int checkUDelegateProperty(lua_State* L,FProperty* prop,uint8* parms,int i) {
        auto p = CastFieldChecked<FDelegateProperty>(prop);
        ensure(p);
        CheckUD(UObject,L,i);
        // bind SignatureFunction
        if(auto dobj=Cast<ULuaDelegate>(UD)) dobj->bindFunction(p->SignatureFunction);
        else luaL_error(L,"arg 1 expect an UDelegateObject");

        FScriptDelegate d;
        d.BindUFunction(UD, TEXT("EventTrigger"));

        p->SetPropertyValue(parms,d);
        return 0;
    }
	 
    int pushUObjectProperty(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto p = CastFieldChecked<FObjectProperty>(prop);
        ensure(p);   
        UObject* o = p->GetPropertyValue(parms);
        if(auto tr=Cast<UWidgetTree>(o))
            return LuaWidgetTree::push(L,tr);
		else {
			return LuaObject::push(L, o, false, true, objRecorder);
		}
    }

    template<typename T>
    int checkUProperty(lua_State* L,FProperty* prop,uint8* parms,int i) {
        auto p = CastFieldChecked<T>(prop);
        ensure(p);
        p->SetPropertyValue(parms,LuaObject::checkValue<typename T::TCppType>(L,i));
        return 0;
    }

    template<>
	int checkUProperty<FEnumProperty>(lua_State* L, FProperty* prop, uint8* parms, int i) {
		auto p = CastFieldChecked<FEnumProperty>(prop);
		ensure(p);
		auto v = (int64)LuaObject::checkValue<int>(L, i);
		p->CopyCompleteValue(parms, &v);
		return 0;
	}

	template<>
	int checkUProperty<FObjectProperty>(lua_State* L, FProperty* prop, uint8* parms, int i) {
		auto p = CastFieldChecked<FObjectProperty>(prop);
		ensure(p);
		UObject* arg = LuaObject::checkValue<UObject*>(L, i);
    	if (arg && !LuaObject::isUObjectValid(arg))
			luaL_error(L, "arg %d is invalid UObject!", i);
    	
		if (arg && arg->GetClass() != p->PropertyClass && !arg->GetClass()->IsChildOf(p->PropertyClass))
			luaL_error(L, "arg %d expect %s, but got %s", i,
				p->PropertyClass ? TCHAR_TO_UTF8(*p->PropertyClass->GetName()) : "", 
				arg->GetClass() ? TCHAR_TO_UTF8(*arg->GetClass()->GetName()) : "");

		p->SetPropertyValue(parms, arg);
		return 0;
	}

	FString getPropertyFriendlyName(FProperty* prop, bool isNative) {
		if (isNative) {
			return prop->GetName();
		}

		FString fieldName = prop->GetName();

		int index = fieldName.Len();
		for (int i = 0; i < 2; ++i) {
			int findIndex = fieldName.Find(TEXT("_"), ESearchCase::CaseSensitive, ESearchDir::FromEnd, index);
			if (findIndex != INDEX_NONE) {
				index = findIndex;
			}
		}

		return fieldName.Left(index);
	}
	
	bool fillUStructWithTable(lua_State* L, FStructProperty* prop, uint8* params, int i) {
		check(lua_istable(L, i));

		auto* uss = prop->Struct;
		bool isNative = uss->IsNative();

		for (TFieldIterator<FProperty> it(uss); it; ++it) {
			AutoStack as(L);
			FString fieldName = getPropertyFriendlyName(*it, isNative);
			if (lua_getfield(L, i, TCHAR_TO_UTF8(*fieldName)) == LUA_TNIL) {
				continue;
			}
			
			auto checker = LuaObject::getChecker(*it);
			if (checker) {
				checker(L, *it, it->ContainerPtrToValuePtr<uint8>(params), -1);
			}
		}

		return true;
	}

    int checkUStructProperty(lua_State* L,FProperty* prop,uint8* parms,int i) {
        auto p = CastFieldChecked<FStructProperty>(prop);
        ensure(p);
		
		if (lua_istable(L, i)) {
			fillUStructWithTable(L, p, parms, i);
			return 0;
		}
		
        auto uss = p->Struct;

		// if it's LuaBPVar
		if (uss->GetName() == "LuaBPVar")
			return FLuaBPVar::checkValue(L, p, parms, i);

		// skip first char to match type
		if (LuaObject::matchType(L, i, TCHAR_TO_UTF8(*uss->GetName()),true)) {
			if (LuaWrapper::checkValue(L, p, uss, parms, i))
				return 0;
		}

		LuaStruct* ls = LuaObject::checkValue<LuaStruct*>(L, i);
		if(!ls)
			luaL_error(L, "expect struct but got nil");

		if (p->GetSize() != ls->size)
			luaL_error(L, "expect struct size == %d, but got %d", p->GetSize(), ls->size);
		p->CopyCompleteValue(parms, ls->buf);
		return 0;
    }
	
	int pushUClassProperty(lua_State* L, FProperty* prop, uint8* parms, NewObjectRecorder* objRecorder) {
		auto p = CastFieldChecked<FClassProperty>(prop);
		ensure(p);
		UClass* cls = Cast<UClass>(p->GetPropertyValue(parms));
		return LuaObject::pushClass(L, cls);
	}

	int checkUClassProperty(lua_State* L, FProperty* prop, uint8* parms, int i) {
		auto p = CastFieldChecked<FClassProperty>(prop);
		ensure(p);
		p->SetPropertyValue(parms, LuaObject::checkValue<UClass*>(L, i));
		return 0;
	}

	bool checkType(lua_State* L, int p, const char* tn) {
		if (!lua_isuserdata(L, p)) {
			lua_pop(L, 1);
			return false;
		}
		int tt = luaL_getmetafield(L, p, "__name");
		if (tt==LUA_TSTRING && strcmp(tn, lua_tostring(L, -1)) == 0)
		{
			lua_pop(L, 1);
			return true;
		}
		if(tt!=LUA_TNIL)
            lua_pop(L, 1);
		return false;
	}

    // search obj from registry, push cached obj and return true if find it
    bool LuaObject::getObjCache(lua_State* L,void* obj,const char* tn,bool check) {
        LuaState* ls = LuaState::get(L);
        ensure(ls->cacheObjRef!=LUA_NOREF);
        lua_geti(L,LUA_REGISTRYINDEX,ls->cacheObjRef);
        // should be a table
        ensure(lua_type(L,-1)==LUA_TTABLE);
        // push obj as key
        lua_pushlightuserdata(L,obj);
        // get key from table
        lua_rawget(L,-2);
        lua_remove(L,-2); // remove cache table
        
        if(lua_isnil(L,-1)) {
            lua_pop(L,1);
			return false;
        }
		if (!check)
			return true;
		// check type of ud matched
		return checkType(L, -1, tn);
    }

    void LuaObject::addRef(lua_State* L,UObject* obj,void* ud,bool ref) {
        auto sl = LuaState::get(L);
        sl->addRef(obj,ud,ref);
    }


    void LuaObject::removeRef(lua_State* L,UObject* obj,void* ud/*=nullptr*/) {
        auto sl = LuaState::get(L);
        sl->unlinkUObject(obj,ud);
    }

	void LuaObject::releaseLink(lua_State* L, void* prop) {
		LuaState* ls = LuaState::get(L);
		ls->releaseLink(prop);
	}

	void LuaObject::linkProp(lua_State* L, void* parent, void* prop) {
		LuaState* ls = LuaState::get(L);
		ls->linkProp(parent,prop);
	}

    void LuaObject::cacheObj(lua_State* L,void* obj) {
		LuaState* ls = LuaState::get(L);
		LuaObject::addCache(L, obj, ls->cacheObjRef);
    }

	void LuaObject::removeObjCache(lua_State * L, void* obj)
	{
		// get cache table
		LuaState* ls = LuaState::get(L);
		LuaObject::removeCache(L, obj, ls->cacheObjRef);
	}

	bool LuaObject::getFuncCache(lua_State* L, const UFunction* func)
	{
		LuaState* ls = LuaState::get(L);
		ensure(ls->cacheFuncRef != LUA_NOREF);
		lua_geti(L, LUA_REGISTRYINDEX, ls->cacheFuncRef);
		// should be a table
		ensure(lua_type(L, -1) == LUA_TTABLE);
		// push obj as key
		lua_pushlightuserdata(L, (void*)func);
		// get key from table
		lua_rawget(L, -2);
		lua_remove(L, -2); // remove cache table

		if (lua_isnil(L, -1)) {
			lua_pop(L, 1);
			return false;
		}
    	
		return 1;
	}

	void LuaObject::cacheFunc(lua_State* L, const UFunction* func)
	{
		LuaState* ls = LuaState::get(L);
		LuaObject::addCache(L, (void*)func, ls->cacheFuncRef);
	}

	void LuaObject::removeFuncCache(lua_State* L, const UFunction* func)
	{
		LuaState* ls = LuaState::get(L);
		LuaObject::removeCache(L, (void*)func, ls->cacheFuncRef);
	}

	void LuaObject::addCache(lua_State* L, void* obj, int ref)
	{
		LuaState* ls = LuaState::get(L);
		lua_geti(L, LUA_REGISTRYINDEX, ref);
		lua_pushlightuserdata(L, obj);
		lua_pushvalue(L, -3); // obj userdata
		lua_rawset(L, -3);
		lua_pop(L, 1); // pop cache table
	}

	void LuaObject::removeCache(lua_State* L, void* obj, int ref)
	{
		// get cache table
		LuaState* ls = LuaState::get(L);
		lua_geti(L, LUA_REGISTRYINDEX, ref);
		ensure(lua_type(L, -1) == LUA_TTABLE);
		lua_pushlightuserdata(L, obj);
		lua_pushnil(L);
		// cache[obj] = nil
		lua_rawset(L, -3);
		// pop cache table;
		lua_pop(L, 1);
	}

	void LuaObject::deleteFGCObject(lua_State* L, FGCObject * obj)
	{
		auto ls = LuaState::get(L);
		ensure(ls);
		ls->deferDelete.Add(obj);
	}
	
	ULatentDelegate* LuaObject::getLatentDelegate(lua_State* L)
	{
		LuaState* ls = LuaState::get(L);
		return ls->getLatentDelegate();
	}

	void LuaObject::createTable(lua_State* L, const char * tn)
	{
		auto ls = LuaState::get(L);
		ensure(ls);
		LuaVar t = ls->createTable(tn);
		t.push(L);
	}


    int LuaObject::pushClass(lua_State* L,UClass* cls) {
        if(!cls) {
            lua_pushnil(L);
            return 1;
        }
		return pushGCObject<UClass*>(L, cls, "UClass", setupClassMT, gcClass, true);
    }

    int LuaObject::pushStruct(lua_State* L,UScriptStruct* cls) {
        if(!cls) {
            lua_pushnil(L);
            return 1;
        }    
        return pushGCObject<UScriptStruct*>(L,cls,"UScriptStruct",setupStructMT,gcStructClass,true);
    }

	int LuaObject::pushEnum(lua_State * L, UEnum * e)
	{
		bool isbpEnum = Cast<UUserDefinedEnum>(e) != nullptr;
		// return a enum as table
		lua_newtable(L);
		int num = e->NumEnums();
		for (int i = 0; i < num; i++) {
			FString name;
			// if is bp enum, can't get name as key
			if(isbpEnum)
				name = e->GetDisplayNameTextByIndex(i).ToString();
			else
				name = e->GetNameStringByIndex(i);
			int64 value = e->GetValueByIndex(i);
			lua_pushinteger(L, value);
			lua_setfield(L, -2, TCHAR_TO_UTF8(*name));
		}
		return 1;
	}

    int LuaObject::gcObject(lua_State* L) {
		void* userdata = lua_touserdata(L, 1);
		CheckUDGC(UObject,L,1);
        removeRef(L,UD,userdata);
        return 0;
    }

    int LuaObject::gcClass(lua_State* L) {
		void* userdata = lua_touserdata(L, 1);
		CheckUDGC(UClass,L,1);
        removeRef(L,UD,userdata);
        return 0;
    }

    int LuaObject::gcStructClass(lua_State* L) {
		void* userdata = lua_touserdata(L, 1);
		CheckUDGC(UScriptStruct,L,1);
        removeRef(L,UD,userdata);
        return 0;
    }

	int LuaObject::gcStruct(lua_State* L) {
		CheckUDGC(LuaStruct, L, 1);
		deleteFGCObject(L,UD);
		return 0;
	}
	
	int LuaObject::push(lua_State* L, UObject* obj, bool rawpush, bool ref, NewObjectRecorder* objRecorder) {
		if (!obj) return pushNil(L);
		if (!rawpush) {
			if (auto it = Cast<ILuaTableObjectInterface>(obj)) {
				return ILuaTableObjectInterface::push(L, it);
			}
		}
		if (auto e = Cast<UEnum>(obj))
			return pushEnum(L, e);
		else if (auto c = Cast<UClass>(obj))
			return pushClass(L, c);
		else if (auto s = Cast<UScriptStruct>(obj))
			return pushStruct(L, s);
		else {
			ref = objRecorder ? objRecorder->hasObject(obj) : ref;
			return pushGCObject<UObject*>(L, obj, "UObject", setupInstanceMT, gcObject, ref);
		}
    }

	int LuaObject::push(lua_State* L, FWeakObjectPtr ptr) {
		if (!ptr.IsValid()) {
			lua_pushnil(L);
			return 1;
		}
		UObject* obj = ptr.Get();
		if (getObjCache(L, obj, "UObject")) return 1;
		int r = pushWeakType(L, new WeakUObjectUD(ptr));
		if (r) cacheObj(L, obj);
		return r;
	}
    
    template<typename T>
    inline void regPusher() {
		pusherMap.Add(T::StaticClass(), pushUProperty<T>);
    }

    template<typename T>
    inline void regChecker() {
		checkerMap.Add(T::StaticClass(), checkUProperty<T>);
    }

    void LuaObject::init(lua_State* L) {
		regPusher<FIntProperty>();
		regPusher<FUInt32Property>();
        regPusher<FInt64Property>();
        regPusher<FUInt64Property>();
		regPusher<FInt16Property>();
		regPusher<FUInt16Property>();
		regPusher<FInt8Property>();
		// regPusher<FByteProperty>(); // uint8
		regPusher<FFloatProperty>();
		regPusher<FDoubleProperty>();
        regPusher<FBoolProperty>();
        regPusher<FTextProperty>();
        regPusher<FStrProperty>();
        regPusher<FNameProperty>();

		regPusher(FByteProperty::StaticClass(), pushUByteProperty);
		
		regPusher(FDelegateProperty::StaticClass(), pushUDelegateProperty);
        regPusher(FMulticastDelegateProperty::StaticClass(),pushUMulticastDelegateProperty);
		regPusher(FMulticastInlineDelegateProperty::StaticClass(), pushUMulticastInlineDelegateProperty);
		regPusher(FMulticastSparseDelegateProperty::StaticClass(), pushUMulticastSparseDelegateProperty);
        regPusher(FObjectProperty::StaticClass(),pushUObjectProperty);
        regPusher(FArrayProperty::StaticClass(),pushUArrayProperty);
        regPusher(FMapProperty::StaticClass(),pushUMapProperty);
        regPusher(FSetProperty::StaticClass(), pushUSetProperty);
        regPusher(FStructProperty::StaticClass(),pushUStructProperty);
		regPusher(FEnumProperty::StaticClass(), pushEnumProperty);
		regPusher(FClassProperty::StaticClass(), pushUClassProperty);
		regPusher(FWeakObjectProperty::StaticClass(), pushUWeakProperty);
		
		regChecker<FIntProperty>();
		regChecker<FUInt32Property>();
        regChecker<FInt64Property>();
        regChecker<FUInt64Property>();
		regChecker<FInt16Property>();
		regChecker<FUInt16Property>();
		regChecker<FInt8Property>();
		regChecker<FByteProperty>(); // uint8
		regChecker<FFloatProperty>();
		regChecker<FDoubleProperty>();
		regChecker<FBoolProperty>();
        regChecker<FNameProperty>();
        regChecker<FTextProperty>();
		regChecker<FObjectProperty>();
        regChecker<FStrProperty>();
        regChecker<FEnumProperty>();

        regChecker(FArrayProperty::StaticClass(),checkUArrayProperty);
        regChecker(FMapProperty::StaticClass(),checkUMapProperty);
        regChecker(FSetProperty::StaticClass(), checkUSetProperty);
        regChecker(FDelegateProperty::StaticClass(),checkUDelegateProperty);
        regChecker(FStructProperty::StaticClass(),checkUStructProperty);
		regChecker(FClassProperty::StaticClass(), checkUClassProperty);
		
		LuaWrapper::init(L);
        ExtensionMethod::init();
    }

    int LuaObject::push(lua_State* L,UFunction* func,UClass* cls)  {
		if (LuaObject::getFuncCache(L, func))
		{
			return 1;
		}
    	
        lua_pushlightuserdata(L, func);
        if(cls) {
            lua_pushlightuserdata(L, cls);
            lua_pushcclosure(L, ufuncClosure, 2);
        }
        else
            lua_pushcclosure(L, ufuncClosure, 1);

		LuaObject::cacheFunc(L, func);
        return 1;
    }

    int LuaObject::push(lua_State* L,FProperty* prop,uint8* parms,NewObjectRecorder* objRecorder) {
        auto pusher = getPusher(prop);
        if (pusher)
            return pusher(L,prop,parms,objRecorder);
        else {
            FString name = prop->GetClass()->GetName();
            Log::Error("unsupport type %s to push",TCHAR_TO_UTF8(*name));
            return 0;
        }
    }

	int LuaObject::push(lua_State* L, FProperty* up, UObject* obj, NewObjectRecorder* objRecorder) {
		auto cls = up->GetClass();
		// if it's an FArrayProperty
		if (cls==FArrayProperty::StaticClass())
			return LuaArray::push(L, CastFieldChecked<FArrayProperty>(up), obj);
        // if it's an FMapProperty
        else if(cls==FMapProperty::StaticClass())
            return LuaMap::push(L, CastFieldChecked<FMapProperty>(up),obj);
        // if it's an FSetProperty (the else is redundant)
        else if(cls == FSetProperty::StaticClass())
			return LuaSet::push(L, CastFieldChecked<FSetProperty>(up), obj);
        else
			return push(L, up, up->ContainerPtrToValuePtr<uint8>(obj), objRecorder);
	}

	int LuaObject::push(lua_State* L, LuaStruct* ls) {
		return pushType<LuaStruct*>(L, ls, "LuaStruct", setupInstanceStructMT, gcStruct);
	}

	int LuaObject::push(lua_State* L, double v) {
		lua_pushnumber(L, v);
		return 1;
	}

	int LuaObject::push(lua_State* L, float v) {
		lua_pushnumber(L, v);
		return 1;
	}

    int LuaObject::push(lua_State* L, int64 v) {
		lua_pushinteger(L, v);
		return 1;
	}

    int LuaObject::push(lua_State* L, uint64 v) {
		lua_pushinteger(L, v);
		return 1;
	}

	int LuaObject::push(lua_State* L, int v) {
		lua_pushinteger(L, v);
		return 1;
	}

    int LuaObject::push(lua_State* L, bool v) {
		lua_pushboolean(L, v);
		return 1;
	}

	int LuaObject::push(lua_State* L, uint32 v) {
		lua_pushinteger(L, v);
		return 1;
	}

    int LuaObject::push(lua_State* L, int16 v) {
		lua_pushinteger(L, v);
		return 1;
	}

    int LuaObject::push(lua_State* L, uint16 v) {
		lua_pushinteger(L, v);
		return 1;
	}

    int LuaObject::push(lua_State* L, int8 v) {
		lua_pushinteger(L, v);
		return 1;
	}

    int LuaObject::push(lua_State* L, uint8 v) {
		lua_pushinteger(L, v);
		return 1;
	}

    int LuaObject::push(lua_State* L, const LuaVar& v) {
        return v.push(L);
	}

    int LuaObject::push(lua_State* L, void* ptr) {
		lua_pushlightuserdata(L,ptr);
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

    int LuaObject::push(lua_State* L, const FName& name) {
		lua_pushstring(L, TCHAR_TO_UTF8(*name.ToString()));
		return 1;
	}

    int LuaObject::push(lua_State* L, const char* str) {
		lua_pushstring(L, str);
		return 1;
	}

    int LuaObject::setupMTSelfSearch(lua_State* L) {
        lua_pushcfunction(L,instanceIndexSelf);
		lua_setfield(L, -2, "__index");
		lua_pushcfunction(L, objectToString);
		lua_setfield(L, -2, "__tostring");
        return 0;
    }


    int LuaObject::setupClassMT(lua_State* L) {
        lua_pushcfunction(L,classConstruct);
        lua_setfield(L, -2, "__call");
        lua_pushcfunction(L,NS_SLUA::classIndex);
		lua_setfield(L, -2, "__index");
		lua_pushcfunction(L, objectToString);
		lua_setfield(L, -2, "__tostring");
        return 0;
    }

    int LuaObject::setupStructMT(lua_State* L) {
        lua_pushcfunction(L,structConstruct);
		lua_setfield(L, -2, "__call");
		lua_pushcfunction(L, objectToString);
		lua_setfield(L, -2, "__tostring");
        return 0;
    }

    int LuaObject::setupInstanceMT(lua_State* L) {
        lua_pushcfunction(L,instanceIndex);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L,newinstanceIndex);
        lua_setfield(L, -2, "__newindex");
		lua_pushcfunction(L, objectToString);
		lua_setfield(L, -2, "__tostring");
        return 0;
    }

    int LuaObject::setupInstanceStructMT(lua_State* L) {
        lua_pushcfunction(L,instanceStructIndex);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, newinstanceStructIndex);
		lua_setfield(L, -2, "__newindex");
		lua_pushcfunction(L, objectToString);
		lua_setfield(L, -2, "__tostring");
        return 0;
    }
}

#ifdef _WIN32
#pragma warning (pop)
#endif

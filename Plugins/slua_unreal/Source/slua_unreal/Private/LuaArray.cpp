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

#include "LuaArray.h"
#include "LuaObject.h"
#include "LuaCppBinding.h"
#include <string>


namespace slua {

    LuaArray::LuaArray(UArrayProperty* prop,FScriptArray* buf)
        :prop(prop) 
    {
        // why FScriptArray can't be copy constructed or MoveToEmpty?
        // just hack it, TODO
        // array.MoveToEmpty(*buf);
        prop->AddToRoot();
        FMemory::Memcpy(&array,buf,sizeof(FScriptArray));
    }

    LuaArray::~LuaArray() {
        prop->RemoveFromRoot();
    }

    int LuaArray::push(lua_State* L,UArrayProperty* prop,FScriptArray* data) {
        LuaArray* array = new LuaArray(prop,data);
        return LuaObject::pushType(L,array,"LuaArray",setupMT,gc);
    }

    int LuaArray::Num(lua_State* L) {
        CheckUD(LuaArray,L,1);
        return LuaObject::push(L,UD->array.Num());
    }

    int LuaArray::Get(lua_State* L) {
        CheckUD(LuaArray,L,1);
        int i = LuaObject::checkValue<int>(L,2);
        UProperty* element = UD->prop->Inner;
        int32 es = element->ElementSize;
        return LuaObject::push(L,element,((uint8*)UD->array.GetData())+i*es);
    }

    int LuaArray::setupMT(lua_State* L) {
        LuaObject::setupMTSelfSearch(L);

        RegMetaMethod(L,Num);
        RegMetaMethod(L,Get);
        return 0;
    }

    int LuaArray::gc(lua_State* L) {
        CheckUD(LuaArray,L,1);
        delete UD;
        return 0;   
    }
}
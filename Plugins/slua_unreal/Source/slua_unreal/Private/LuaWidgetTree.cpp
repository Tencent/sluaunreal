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

#include "LuaWidgetTree.h"
#include "Blueprint/WidgetTree.h"
#include "LuaObject.h"
#include "Blueprint/WidgetTree.h"

namespace slua {

    int LuaWidgetTree::push(lua_State* L,UWidgetTree* tree) {
        return LuaObject::pushType(L,tree,"UWidgetTree",setupMT);
    }

    int LuaWidgetTree::FindWidget(lua_State* L) {
        CheckUD(UWidgetTree,L,1);
        const char* name = luaL_checkstring(L,2);
        FName fname(UTF8_TO_TCHAR(name));
        auto w = UD->FindWidget(fname);
        return LuaObject::push(L,w);
    }

    int LuaWidgetTree::RemoveWidget(lua_State* L) {
        CheckUD(UWidgetTree,L,1);
        CheckUDEX(UWidget,widget,L,2);
        bool ret = UD->RemoveWidget(widget->ud);
        return LuaObject::push(L,ret);
    }

    int LuaWidgetTree::setupMT(lua_State* L) {
        LuaObject::setupMTSelfSearch(L);

        RegMetaMethod(L,FindWidget);
        RegMetaMethod(L,RemoveWidget);
        return 0;
    }

}
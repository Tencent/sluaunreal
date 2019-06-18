// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaWidgetTree.h"
#include "Blueprint/WidgetTree.h"
#include "LuaObject.h"

namespace NS_SLUA {

    int LuaWidgetTree::push(lua_State* L,UWidgetTree* tree) {
        return LuaObject::pushType(L,tree,"UWidgetTree",setupMT);
    }

    // deprecated function, use GetWidgetFromName
    int LuaWidgetTree::FindWidget(lua_State* L) {
        CheckUD(UWidgetTree,L,1);
        const char* name = luaL_checkstring(L,2);
        FName fname(UTF8_TO_TCHAR(name));
        auto w = UD->FindWidget(fname);
        return LuaObject::push(L,w);
    }

    // deprecated function, use RemoveWidgetFromName
    int LuaWidgetTree::RemoveWidget(lua_State* L) {
        CheckUD(UWidgetTree,L,1);
        auto widget = LuaObject::checkUD<UWidget>(L,2);
        bool ret = UD->RemoveWidget(widget);
        return LuaObject::push(L,ret);
    }

    int LuaWidgetTree::GetAllWidgets(lua_State* L) {
        CheckUD(UWidgetTree,L,1);
        TArray<UWidget*> Widgets;
        UD->GetAllWidgets(Widgets);
        lua_newtable(L);
        for (int i=0; i<Widgets.Num(); i++) {
            LuaObject::push(L,Widgets[i]);
            lua_seti(L,-2,i+1);
        }
        return 1;
    }

    int LuaWidgetTree::setupMT(lua_State* L) {
        LuaObject::setupMTSelfSearch(L);

        RegMetaMethod(L,FindWidget);
        RegMetaMethod(L,RemoveWidget);
        RegMetaMethod(L,GetAllWidgets);
        return 0;
    }

}
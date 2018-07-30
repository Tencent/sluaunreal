// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaObject.h"
#include "LuaCppBinding.h"
#include "Blueprint/WidgetTree.h"

namespace slua {

    namespace ExtensionMethod {

        #define REG_EXTENSION_METHOD(U,N,M) { \
            LuaObject::addExtensionMethod(U::StaticClass(),N,LuaCppBinding<decltype(M),M>::LuaCFunction); }

        #define REG_EXTENSION_METHOD_IMP(U,N,BODY) { \
            LuaObject::addExtensionMethod(U::StaticClass(),N,[](lua_State* L)->int BODY); }

        void init() {
            REG_EXTENSION_METHOD(UUserWidget,"FindWidget",&UUserWidget::GetWidgetFromName);
            REG_EXTENSION_METHOD_IMP(UUserWidget,"RemoveWidget",{
                CheckUD(UUserWidget,L,1);
                CheckUDEX(UWidget,widget,L,2);
                bool ret = UD->WidgetTree->RemoveWidget(widget->ud);
                return LuaObject::push(L,ret);
            });
        }
    }
}
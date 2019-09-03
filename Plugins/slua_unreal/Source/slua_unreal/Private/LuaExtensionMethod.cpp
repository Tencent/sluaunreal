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
#include "Log.h"
#include "LuaActor.h"

namespace NS_SLUA {

    namespace ExtensionMethod {

        void init() {
            REG_EXTENSION_METHOD(UUserWidget,"FindWidget",&UUserWidget::GetWidgetFromName);
            REG_EXTENSION_METHOD_IMP(UUserWidget,"RemoveWidget",{
                CheckUD(UUserWidget,L,1);
                auto widget = LuaObject::checkUD<UWidget>(L,2);
                bool ret = UD->WidgetTree->RemoveWidget(widget);
                return LuaObject::push(L,ret);
            });

			REG_EXTENSION_METHOD(AActor, "GetWorld", &AActor::GetWorld);
			REG_EXTENSION_METHOD_IMP(UObject, "GetClass", {
                CheckUD(UObject,L,1);
                if(!UD) luaL_error(L,"arg 1 expect UObject");
                return LuaObject::push(L,UD->GetClass());
            });

            // resolve overloaded member function
            REG_EXTENSION_METHOD_WITHTYPE(UWorld,"SpawnActor",&UWorld::SpawnActor,AActor* (UWorld::*)( UClass*, FVector const*,FRotator const*, const FActorSpawnParameters&));

			// disable __luaPart
			// REG_EXTENSION_PROPERTY(ALuaActor, "__luaPart", &ALuaActor::getSelfTable, nullptr);

        }
    }
}
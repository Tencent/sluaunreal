// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.


#include "LuaSimulate.h"
#if WITH_EDITOR
#include "Editor.h"
#include "LuaOverrider.h"
#include "Misc/FileHelper.h"

namespace NS_SLUA {
    LuaState::LoadFileDelegate LuaSimulate::Delegate = nullptr;

    void LuaSimulate::OnStartupModule()
    {
        PIEHandle = FEditorDelegates::PreBeginPIE.AddRaw(this, &LuaSimulate::OnPreBeginPIE);
    }

    void LuaSimulate::SetLuaFileLoader(LuaState::LoadFileDelegate InDelegate)
    {
        Delegate = InDelegate;
    }

    void LuaSimulate::OnPreBeginPIE(const bool bIsSimulating)
    {
        StopSimulateLua();
    }

    void LuaSimulate::NotifyUObjectCreated(const class UObjectBase* Object, int32 Index)
    {
        UObjectBaseUtility* Obj = (UObjectBaseUtility*)Object;
        UObject* Outer = Obj->GetOuter();
        if (!Outer)
        {
            return;
        }
        UWorld* World = Outer->GetWorld();
        if (!World)
        {
            return;
        }
        bool Preview = World->WorldType == EWorldType::EditorPreview;
        if (!Preview)
        {
            return;
        }
        if (!LuaOverrider::isHookable(Obj))
        {
            return;
        }
        bool BegunPlay = World->bBegunPlay;
        if (!BegunPlay)
        {
            if (SimulatingObj && SimulatingObj->GetClass() == Obj->GetClass())
            {
                StopSimulateLua();
            }
            return;
        }
        if (!Obj->HasAnyFlags(RF_ClassDefaultObject | RF_ArchetypeObject))
        {
            StartSimulateLua();
            NS_SLUA::LuaState::hookObject(SluaState, Obj, true);
            SimulatingObj = Obj;
        }
    }

    void LuaSimulate::NotifyUObjectDeleted(const class UObjectBase* Object, int32 Index)
    {
        if (Object == SimulatingObj)
        {
            StopSimulateLua();
        }
    }
    
#if !((ENGINE_MINOR_VERSION<23) && (ENGINE_MAJOR_VERSION==4))
    void LuaSimulate::OnUObjectArrayShutdown()
    {
        GUObjectArray.RemoveUObjectCreateListener(this);
        GUObjectArray.RemoveUObjectDeleteListener(this);
    }
#endif
    
    void LuaSimulate::StartSimulateLua()
    {
        if (Delegate == nullptr)
        {
            Log::Error("lua Simulation Error. LoadFileDelegate not set.");
            return;
        }
        StopSimulateLua();
        SluaState = new NS_SLUA::LuaState("", nullptr);
        SluaState->setLoadFileDelegate(Delegate);
        SluaState->init();
    }

    void LuaSimulate::StopSimulateLua()
    {
        if (SluaState != nullptr)
        {
            SluaState->close();
            delete SluaState;
            SluaState = nullptr;
            SimulatingObj = nullptr;
        }
    }

    void LuaSimulate::OnShutdownModule()
    {
        FEditorDelegates::PreBeginPIE.Remove(PIEHandle);
    }
}
#endif
// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "UObject/UObjectArray.h"
#include "LuaState.h"

namespace NS_SLUA {
    class LuaState;

    class SLUA_UNREAL_API LuaSimulate : public FUObjectArray::FUObjectCreateListener, public FUObjectArray::FUObjectDeleteListener
    {
    public:
        void OnStartupModule();
        void OnShutdownModule();
        static void SetLuaFileLoader(LuaState::LoadFileDelegate Delegate);

        void OnPreBeginPIE(const bool bIsSimulating);

        void NotifyUObjectCreated(const class UObjectBase* Object, int32 Index) override;
        void NotifyUObjectDeleted(const UObjectBase* Object, int32 Index) override;
#if !((ENGINE_MINOR_VERSION<23) && (ENGINE_MAJOR_VERSION==4))
        void OnUObjectArrayShutdown();
#endif

        void StartSimulateLua();
        void StopSimulateLua();

        LuaState* SluaState = nullptr;
        FDelegateHandle PIEHandle;
        UObjectBaseUtility* SimulatingObj = nullptr;
    private:
        static LuaState::LoadFileDelegate Delegate;
    };
}
// Fill out your copyright notice in the Description page of Project Settings.

#include "LuaComponent.h"

slua::LuaVar ULuaComponent::metatable;

// Sets default values for this component's properties
ULuaComponent::ULuaComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void ULuaComponent::BeginPlay()
{
    init();
    Super::BeginPlay();

    PrimaryComponentTick.SetTickFunctionEnable(false);

    if (!luaComponentTable.isTable())
        return;

    slua::LuaVar beginFunction = luaComponentTable.getFromTable<slua::LuaVar>("BeginPlay");
    if (beginFunction.isValid() && beginFunction.isFunction())
        beginFunction.call(luaComponentTable);

    bool tickEnabled = luaComponentTable.getFromTable<bool>("bCanEverTick");
    PrimaryComponentTick.SetTickFunctionEnable(tickEnabled);

    if (tickEnabled)
    {
        tickFunction = luaComponentTable.getFromTable<slua::LuaVar>("Tick");
        if (!tickFunction.isValid() || !tickFunction.isFunction())
            slua::Log::Error("LuaComponent can't find Tick function");
    }

}

void ULuaComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);

    if (!luaComponentTable.isTable())
        return;

    slua::LuaVar endPlayFunction = luaComponentTable.getFromTable<slua::LuaVar>("EndPlay");
    if (endPlayFunction.isValid() && endPlayFunction.isFunction())
        endPlayFunction.call(luaComponentTable);
}

void ULuaComponent::ProcessEvent(UFunction * func, void * params)
{
    if (luaImplemented(func, params))
        return;
    Super::ProcessEvent(func, params);
}

bool ULuaComponent::luaImplemented(UFunction * func, void * params)
{
    if (!luaComponentTable.isTable())
        return false;

    if (!func->HasAnyFunctionFlags(EFunctionFlags::FUNC_BlueprintEvent))
        return false;

    slua::LuaVar lfunc = luaComponentTable.getFromTable<slua::LuaVar>(
        (const char *)TCHAR_TO_UTF8(*func->GetDisplayNameText().ToString()));

    if (!lfunc.isValid() || !lfunc.isFunction())
        return false;

    return lfunc.callByUFunction(func, (uint8*)params, &luaComponentTable);
}


// Called every frame
void ULuaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    if (!tickFunction.isValid())
        return;

    tickFunction.call(luaComponentTable, DeltaTime);
}

int ULuaComponent::__index(slua::lua_State* L)
{                                                       // Stack status
                                                        // t
    lua_pushstring(L, "__cppinst");                     // t, "__cppinst"
    lua_rawget(L, 1);                                   // t, this
    if (!lua_isuserdata(L, -1))
        luaL_error(L, "expect LuaComponent table at arg 1");

    lua_pushvalue(L, 2);                                // t, this, key
    lua_gettable(L, -2);                                // t, this, value

    return 1;
}

void ULuaComponent::init()
{
    auto ls = slua::LuaState::get();
    if (LuaStateName.Len() != 0)
        ls = slua::LuaState::get(LuaStateName);

    if (!ls)
        return;

    luaComponentTable = ls->doFile(TCHAR_TO_UTF8(*LuaFilePath));
    if (!luaComponentTable.isTable())
        return;

    auto L = ls->getLuaState();                         // Stack status
    luaComponentTable.push(L);                          // t

    slua::LuaObject::push(L, this);                     // t, this
    lua_setfield(L, -2, "__cppinst");                   // t

    if (!metatable.isValid())
    {
        luaL_newmetatable(L, "LuaComponent");           // t, metatable
        lua_pushcfunction(L, __index);                  // t, metatable, __index
        lua_setfield(L, -2, "__index");                 // t, metatable
        metatable.set(L, -1);                           // t, metatable
        lua_pop(L, 1);                                  // t
    }

    metatable.push(L);                                  // t, metatable
    lua_setmetatable(L, -2);                            // t

    lua_pop(L, 1);                                      // 
}


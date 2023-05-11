// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaStatProfile.h"
#include "FLuaCycleCounter.h"
#include "lstate.h"
#include "lobject.h"
#include "LuaState.h"
#include "LuaProfiler.h"
#include "Log.h"
#include "Misc/Paths.h"
#include "Misc/ConfigCacheIni.h"

namespace NS_SLUA {
    LuaStatProfile::LuaStatProfile()
    {
    }

    LuaStatProfile::~LuaStatProfile()
    {
    }

    TArray<FString> LuaStatProfile::blackScripts;
    TArray<LuaStatProfile::LuaStackInfo> LuaStatProfile::luaStateStack;
    int LuaStatProfile::coroutineStack = 0;
    int LuaStatProfile::mainStack = 0;
    int LuaStatProfile::coroutine = 0;
    int LuaStatProfile::level = 2;
    bool LuaStatProfile::switcher = false;
    FDelegateHandle LuaStatProfile::errorHandle;

    void LuaStatProfile::profile_coroutine_hook(lua_State* L, lua_Debug* ar)
    {
        if (!switcher)
        {
            lua_sethook(L, nullptr, 0, 0);
            UE_LOG(LogTemp, Log, TEXT("[FLuaCycleCounter_Record] LuaStat stop"));
            return;
        }

        checkCoroutine();

        lua_getinfo(L, "nSl", ar);
        int event = ar->event;
        int stateYield = -1;
        int resumeEvent = 0;
        // we don't care about LUA_HOOKLINE, LUA_HOOKCOUNT
        if (ar->event > LUA_HOOKRET && event != LUA_HOOKTAILCALL)
            return;

        if (strstr(ar->short_src, LuaProfiler::ChunkName))
            return;

        if (ar->what && strcmp(ar->what, "C") == 0) {
            StkId o = L->ci ? L->ci->func : nullptr;
#if LUA_VERSION_NUM > 503
            if (ttislcf(s2v(o)) && fvalue(s2v(o)) == LuaProfiler::yieldFunc) {
                stateYield = event;
            }
            else if (ttislcf(s2v(o)) && fvalue(s2v(o)) == LuaProfiler::resumeFunc) {
                if (lua_isthread(L, 1)) {
                    // coroutine enter/exit
                    resumeEvent = event + ENTER;
                }
            }
#else
            if (ttislcf(o) && fvalue(o) == LuaProfiler::yieldFunc) {
                stateYield = event;
            }
            else if (ttislcf(o) && fvalue(o) == LuaProfiler::resumeFunc) {
                if (lua_isthread(L, 1)) {
                    // coroutine enter/exit
                    resumeEvent = event + ENTER;
                }
            }
#endif
        }

        FString counterName = generateCounterName(ar);
        LuaStackInfo* curInfo = nullptr;
        int index = -1;
        //协程堆栈处理完毕之后，并不一定退出协程
        for (int i = 0; i < luaStateStack.Num(); i++)
        {
            if (luaStateStack[i].luaState == L)
            {
                curInfo = &luaStateStack[i];
                index = i;
                break;
            }
        }

        if (curInfo == nullptr)
        {
            LuaStackInfo stackInfo(L, 0);
            luaStateStack.Add(stackInfo);
            curInfo = &luaStateStack.Top();
            index = luaStateStack.Num() - 1;
        }
        //尾调用特殊处理（因为尾调用后，函数不会再return到调用函数，相当于goto
        //所以当遇到尾调用时，也就是event=4要把之前函数调用的栈清理掉）
        if (event == LUA_HOOKTAILCALL)
        {
            FLuaCycleCounter::counterStop(1, luaStateStack.Num(), counterName);
            curInfo->stackNum--;
        }

        //yield函数调用，退出协程
        if (stateYield == LUA_HOOKCALL)
        {
            while (curInfo->stackNum > 0)
            {
                FLuaCycleCounter::counterStop(2, luaStateStack.Num(), counterName);
                curInfo->stackNum--;
            }
        }
        else if (stateYield == LUA_HOOKRET)
        {
            FLuaCycleCounter::counterStart(counterName, 1, luaStateStack.Num());
            curInfo->stackNum++;
            //yield函数返回不统计
            return;
        }
        else
        {
            //保留协程函数
            if (resumeEvent < ENTER && checkHookSuc(ar) == false)
                return;

            if (event == LUA_HOOKCALL)
            {
                FLuaCycleCounter::counterStart(counterName, 2, luaStateStack.Num());
                curInfo->stackNum++;
            }
            else if (event == LUA_HOOKRET)
            {
                if (curInfo->stackNum > 0)
                {

                    FLuaCycleCounter::counterStop(3, luaStateStack.Num(), counterName);
                    curInfo->stackNum--;
                }
            }
            else if (ar->event == LUA_HOOKTAILCALL)
            {
                FLuaCycleCounter::counterStart(counterName, 3, luaStateStack.Num());
                curInfo->stackNum++;
            }
        }

        if (curInfo->stackNum <= 0)
        {
            luaStateStack.RemoveAt(index);
        }

        if (resumeEvent == ENTER)
        {
            lua_State* co = lua_tothread(L, 1);
            LuaStackInfo stackInfo(co, 0);
            luaStateStack.Add(stackInfo);
            lua_sethook(co, profile_coroutine_hook, LUA_MASKRET | LUA_MASKCALL, 0);

        }
        else if (resumeEvent == EXIT)
        {

        }
    }

    void LuaStatProfile::profile_hook(lua_State* L, lua_Debug* ar)
    {
        checkCoroutine();
        lua_getinfo(L, "nSl", ar);
        int event = ar->event;
        // we don't care about LUA_HOOKLINE, LUA_HOOKCOUNT
        if (event > LUA_HOOKRET && event != LUA_HOOKTAILCALL)
        {
            return;
        }

        if (strstr(ar->short_src, LuaProfiler::ChunkName))
            return;
        lua_Debug* co_debug = NULL;
        lua_State* co = NULL;
        lua_Debug co_ar;

        int resumeEvent = 0;
        if (ar->what && strcmp(ar->what, "C") == 0) {
            StkId o = L->ci ? L->ci->func : nullptr;
#if LUA_VERSION_NUM > 503
            if (ttislcf(s2v(o)) && fvalue(s2v(o)) == LuaProfiler::resumeFunc) {
#else
            if (ttislcf(o) && fvalue(o) == LuaProfiler::resumeFunc) {
#endif
                if (lua_isthread(L, 1)) {
                    // coroutine enter/exit
                    resumeEvent = event + ENTER;

                    co = lua_tothread(L, 1);
                    switch (lua_status(co))
                    {
                    case LUA_YIELD:
                        break;
                    case LUA_OK: 
                        if (lua_getstack(co, 1, &co_ar) > 0)
                        {
                            lua_getinfo(co, "nSl", &co_ar);
                            co_debug = &co_ar;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }
        const FString counterName = generateCounterName(ar);
        //尾调用特殊处理（因为尾调用后，函数不会再return到调用函数，相当于goto
        //所以当遇到尾调用时，也就是event=4要把之前函数调用的栈清理掉）
        //同时还需要模拟一个进栈操作
        if (event == LUA_HOOKTAILCALL)
        {
            FLuaCycleCounter::counterStop(4, luaStateStack.Num(), counterName);
        }

        //保留协程函数
        if (resumeEvent < ENTER && checkHookSuc(ar) == false)
            return;

        if (resumeEvent == ENTER)
        {
            //coroutine++;
            LuaStackInfo stackInfo(co, 0);
            luaStateStack.Add(stackInfo);
            lua_sethook(co, profile_coroutine_hook, LUA_MASKRET | LUA_MASKCALL, 0);
        }
        else if (resumeEvent == EXIT)
        {
            if (co_debug && co)
            {
                FLuaCycleCounter::counterStop(5, luaStateStack.Num(), generateCounterName(co_debug));
            }
        }

        if (ar->event == LUA_HOOKCALL)
        {
            FLuaCycleCounter::counterStart(counterName, 4, luaStateStack.Num());
        }
        else if (ar->event == LUA_HOOKRET)
        {
            FLuaCycleCounter::counterStop(5, luaStateStack.Num(), counterName);
        }
        //模拟一个进栈操作
        else if (ar->event == LUA_HOOKTAILCALL)
        {
            FLuaCycleCounter::counterStart(counterName, 5, luaStateStack.Num());
        }

        if (resumeEvent == ENTER && co_debug && co)
        {
            FLuaCycleCounter::counterStart(generateCounterName(co_debug), 5, luaStateStack.Num());
        }
    }

    void LuaStatProfile::checkCoroutine()
    {
        int luastateStackNum = luaStateStack.Num();
        int index = 0;
        if (luastateStackNum > 0)
        {
            for (int i = 1; i < luastateStackNum; i++)
            {
                if (luaStateStack[i].luaState->status > LUA_YIELD)
                {
                    index = i;
                    break;
                }
            }
        }

        if (index > 0)
        {
            while (luaStateStack[index].stackNum > 0)
            {
                FLuaCycleCounter::counterStop(6);
                luaStateStack[index].stackNum--;
            }

            luaStateStack.RemoveAt(index);
        }
    }

    FString LuaStatProfile::generateCounterName(lua_Debug* ar)
    {
        const char* functionName = ar->name ? ar->name : "";
        FString counterName = FString::Printf(TEXT("[Lua Trace]:%s [Script]:%s [Line]:%d"),
            UTF8_TO_TCHAR(functionName), UTF8_TO_TCHAR(ar->short_src), ar->linedefined);
        return MoveTemp(counterName);
    }

    void LuaStatProfile::clearSetHookData(lua_State* L)
    {
        UE_LOG(LogTemp, Log, TEXT("[FLuaCycleCounter_Record] Clear Data"));
        const int luaStateStackNum = luaStateStack.Num();
        if (luaStateStackNum > 0)
        {
            LuaStackInfo stackInfo = luaStateStack.Pop();
            lua_sethook(stackInfo.luaState, nullptr, 0, 0);
            //取消hook
            while (luaStateStack.Num() > 0)
            {
                stackInfo = luaStateStack.Pop();
                lua_sethook(stackInfo.luaState, nullptr, 0, 0);
            }
            //去掉错误监听
            LuaState* ls = LuaState::get(stackInfo.luaState);
            if (ls)
            {
                auto errorDelegate = ls->getErrorDelegate();
                errorDelegate->Remove(errorHandle);
            }
        }

        luaStateStack.Empty();
        coroutineStack = 0;
        coroutine = 0;
        FLuaCycleCounter::clearCounter();
    }

    void LuaStatProfile::onError(const char* err)
    {
        clearSetHookData();
        switcher = false;
        Log::Error("%s", err);
    }
    void LuaStatProfile::setHook(lua_State* L, bool enable)
    {
        blackScripts.Empty();
        const FString BlackListFileName = FPaths::ProjectConfigDir() / TEXT("LuaStatProfileBlackList.ini");
        GConfig->GetArray(TEXT("ScriptBlackList"), TEXT("+BlackList"), blackScripts, BlackListFileName);
        switcher = enable;
        if (enable) {
            //已经监听
            if (luaStateStack.Num() > 0)
                return;

            lua_sethook(L, profile_hook, LUA_MASKRET | LUA_MASKCALL, 0);
            LuaState* ls = LuaState::get(L);
            if (ls)
            {
                auto Del = ls->getErrorDelegate();
                errorHandle = Del->AddStatic(&LuaStatProfile::onError);
            }

            const LuaStackInfo stackInfo(L, 0);
            luaStateStack.Add(stackInfo);
        }
        else
        {
            clearSetHookData(L);
        }
        UE_LOG(LogTemp, Log, TEXT("Lua Profile SetHook"));
    }

    void LuaStatProfile::setHookLevel(int Level)
    {
        LuaStatProfile::level = Level;
        UE_LOG(LogTemp, Log, TEXT("Lua Profile SetHookLevel"));
    }

    bool LuaStatProfile::checkHookSuc(lua_Debug* ar)
    {
        if (level > 0)
        {
            for (const FString& src : blackScripts)
            {
                if (strstr(ar->short_src, TCHAR_TO_UTF8(*src)))
                    return false;
            }
        }
        if (level > 1)
        {
            if (ar->linedefined == -1)
                return false;
        }
        if (level > 2)
        {
            if (ar->name == nullptr)
                return false;
        }
        return true;
    }
}
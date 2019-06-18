// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.
#include "Log.h"
#include "Logging/LogVerbosity.h"
#include "Logging/LogMacros.h"
#include <stdio.h>
#include <stdarg.h>

DECLARE_LOG_CATEGORY_EXTERN(Slua, Log, All);
DEFINE_LOG_CATEGORY(Slua);

namespace {
    enum LogLevel {LL_Log,LL_Debug,LL_Warning,LL_Error};

    void output(LogLevel level,const char* buf) {
        switch(level) {
        case LogLevel::LL_Log:
            UE_LOG(Slua, Log, TEXT("%s"), UTF8_TO_TCHAR(buf));
            break;
        case LogLevel::LL_Error:
            UE_LOG(Slua, Error, TEXT("%s"), UTF8_TO_TCHAR(buf));
            break;
        default:
            UE_LOG(Slua, Log, TEXT("%s"), UTF8_TO_TCHAR(buf));
            break;
        }
    }

    void output(LogLevel level,const wchar_t* buf) {
        switch(level) {
        case LogLevel::LL_Log:
            UE_LOG(Slua, Log, TEXT("%s"), buf);
            break;
        case LogLevel::LL_Error:
            UE_LOG(Slua, Error, TEXT("%s"), buf);
            break;
        default:
            UE_LOG(Slua, Log, TEXT("%s"), buf);
        }
    }
}

namespace NS_SLUA {
    namespace Log {
        #define LogBufDeclareWithFmt(buf,fmt) \
            char buf[10240];\
            va_list args;\
            va_start(args, fmt);\
            vsnprintf(buf,10240,fmt,args);\
            va_end(args);\

        #define LogWBufDeclareWithFmt(buf,fmt) \
            wchar_t buf[10240];\
            va_list args;\
            va_start(args, fmt);\
            vswprintf(buf,10240,fmt,args);\
            va_end(args);\

        void Error(const char* fmt,...) {
            LogBufDeclareWithFmt(buf,fmt);
            output(LogLevel::LL_Error,buf);
        }

        void Log(const char* fmt,...) {
            LogBufDeclareWithFmt(buf,fmt);
            output(LogLevel::LL_Log,buf);
        }

        void Error(const wchar_t* fmt,...) {
            LogWBufDeclareWithFmt(buf,fmt);
            output(LogLevel::LL_Error,buf);
        }

        void Log(const wchar_t* fmt,...) {
            LogWBufDeclareWithFmt(buf,fmt);
            output(LogLevel::LL_Log,buf);
        }
    }
}
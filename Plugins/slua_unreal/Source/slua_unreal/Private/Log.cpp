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
        }
    }

    void output(LogLevel level,TCHAR* buf) {
        switch(level) {
        case LogLevel::LL_Log:
            UE_LOG(Slua, Log, TEXT("%s"), buf);
            break;
        case LogLevel::LL_Error:
            UE_LOG(Slua, Error, TEXT("%s"), buf);
            break;
        }
    }
}

namespace slua {
    namespace Log {
        #define LogBufDeclareWithFmt(buf,fmt) \
            char buf[10240];\
            va_list args;\
            va_start(args, fmt);\
            vsnprintf(buf,10240,fmt,args);\
            va_end(args);\

        #define LogWBufDeclareWithFmt(buf,fmt) \
            TCHAR buf[10240];\
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

        void Error(const TCHAR* fmt,...) {
            LogWBufDeclareWithFmt(buf,fmt);
            output(LogLevel::LL_Error,buf);
        }

        void Log(const TCHAR* fmt,...) {
            LogWBufDeclareWithFmt(buf,fmt);
            output(LogLevel::LL_Log,buf);
        }
    }
}
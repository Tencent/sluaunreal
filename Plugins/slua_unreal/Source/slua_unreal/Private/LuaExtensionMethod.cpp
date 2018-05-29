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

#include "LuaObject.h"
#include "LuaCppBinding.h"
#include "Blueprint/WidgetTree.h"

namespace slua {

    #define MetaMap(U,N) \
        template<>\
        struct TypeName<U> {\
            static const char* value() {\
                return #N;\
            }\
        };\

    MetaMap(UUserWidget,UObject)

    namespace ExtensionMethod {

        #define REG_EXTENSION_METHOD(U,N,M) { \
            LuaObject::addExtensionMethod(U::StaticClass(),N,LuaCppBinding<decltype(M),M>::LuaCFunction); }

        #define REG_EXTENSION_METHOD_IMP(U,N,BODY) { \
            LuaObject::addExtensionMethod(U::StaticClass(),N,[](lua_State* L)->int BODY); }

        void init() {
            REG_EXTENSION_METHOD(UUserWidget,"GetWidgetFromName",&UUserWidget::GetWidgetFromName);
            REG_EXTENSION_METHOD_IMP(UUserWidget,"RemoveWidgetFromName",{
                CheckUD(UUserWidget,L,1);
                CheckUDEX(UWidget,widget,L,2);
                bool ret = UD->WidgetTree->RemoveWidget(widget->ud);
                return LuaObject::push(L,ret);
            });
        }
    }
}
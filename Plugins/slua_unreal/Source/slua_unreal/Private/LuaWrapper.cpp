// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.

#include "LuaWrapper.h"
#include "LuaObject.h"

#define SLUA_GCSTRUCT(typeName) auto flag = udptr->flag; \
                    if (udptr->parent) { \
                        LuaObject::unlinkProp(L, udptr); \
                    } \
                    else if (!(flag & UD_HADFREE) && (flag & UD_AUTOGC)) { \
                        LuaObject::releaseLink(L, self); \
                    } \
                    if ((flag & UD_AUTOGC) && !(flag & UD_HADFREE)) delete self


namespace NS_SLUA {
    UScriptStruct* StaticGetBaseStructureInternal(const TCHAR* Name)
    {
	    static UPackage* CoreUObjectPkg = FindObjectChecked<UPackage>(nullptr, TEXT("/Script/CoreUObject"));
	    return FindObjectSafe<UScriptStruct>(CoreUObjectPkg, Name);
    }

#if ((ENGINE_MINOR_VERSION<25) && (ENGINE_MAJOR_VERSION==4))
    #include "LuaWrapper4.18.inc"
#elif ((ENGINE_MINOR_VERSION>=25) && (ENGINE_MAJOR_VERSION==4))
    #include "LuaWrapper4.25.inc"
#elif ((ENGINE_MINOR_VERSION==1) && (ENGINE_MAJOR_VERSION==5))
    #include "LuaWrapper5.1.inc"
#elif ((ENGINE_MINOR_VERSION>=2) && (ENGINE_MAJOR_VERSION==5))
    #include "LuaWrapper5.2.inc"
#endif
}
// Tencent is pleased to support the open source community by making sluaunreal available.

// Copyright (C) 2018 THL A29 Limited, a Tencent company. All rights reserved.
// Licensed under the BSD 3-Clause License (the "License"); 
// you may not use this file except in compliance with the License. You may obtain a copy of the License at

// https://opensource.org/licenses/BSD-3-Clause

// Unless required by applicable law or agreed to in writing, 
// software distributed under the License is distributed on an "AS IS" BASIS, 
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. 
// See the License for the specific language governing permissions and limitations under the License.


const char* LuaClassSource = R"code(
local setmetatable = setmetatable
local getmetatable = getmetatable
local rawset = rawset
local CBase

function Class(base, static, classImplement)
    if base == nil then
        base = CBase
    end
    classImplement = classImplement or {}
    classImplement.__super_impl = base.__inner_impl
    classImplement.__super = base

    local base_mt = getmetatable(base)
    local class = static or {}
    class.__inner_impl = classImplement

    local class_index = function (t, k, cache)
        local impl = classImplement
        local ret
        while impl do
            ret = impl[k]
            if ret ~= nil then
                if cache ~= false then
                    rawset(t, k, ret)
                end
                return ret
            end
            impl = impl.__super_impl
        end
        return nil
    end

    local instance_metatable =
    {
        __index = class_index,
    }

    setmetatable(class,
        {
            __index = class_index,

            __newindex = function ()
                error("Prevent __newindex with class!")
            end,

            __call = function(...)
                local r = base_mt.__call(...)
                setmetatable(r, instance_metatable)

                if classImplement.ctor then
                    classImplement.ctor(r, ...)
                end

                return r
            end,
        }
    )
    return class
end

local base = {}
setmetatable(base, {__call = function () return {} end})

CBase = Class(base, nil, nil)

)code";

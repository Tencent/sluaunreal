# Tencent is pleased to support the open source community by making xLua available.
# Copyright (C) 2016 THL A29 Limited, a Tencent company. All rights reserved.
# Licensed under the MIT License (the "License"); you may not use this file except in compliance with the License. You may obtain a copy of the License at
# http://opensource.org/licenses/MIT
# Unless required by applicable law or agreed to in writing, software distributed under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the License for the specific language governing permissions and limitations under the License.

cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE Debug)

project(lua)

set(SLUA_SRC_ROOT Source/slua_unreal)
set(LUA_INC_PATH ${SLUA_SRC_ROOT}/Public/lua)
set(LUA_SRC_PATH ${SLUA_SRC_ROOT}/Private/lua)

set(LUA_SRC_FILES 
    ${LUA_SRC_PATH}/lapi.cpp
    ${LUA_SRC_PATH}/lauxlib.cpp
    ${LUA_SRC_PATH}/lbaselib.cpp
    ${LUA_SRC_PATH}/lbitlib.cpp
    ${LUA_SRC_PATH}/lcode.cpp
    ${LUA_SRC_PATH}/lcorolib.cpp
    ${LUA_SRC_PATH}/lctype.cpp
    ${LUA_SRC_PATH}/ldblib.cpp
    ${LUA_SRC_PATH}/ldebug.cpp
    ${LUA_SRC_PATH}/ldo.cpp
    ${LUA_SRC_PATH}/ldump.cpp
    ${LUA_SRC_PATH}/lfunc.cpp
    ${LUA_SRC_PATH}/lgc.cpp
    ${LUA_SRC_PATH}/linit.cpp
    ${LUA_SRC_PATH}/liolib.cpp
    ${LUA_SRC_PATH}/llex.cpp
    ${LUA_SRC_PATH}/lmathlib.cpp
    ${LUA_SRC_PATH}/lmem.cpp
    ${LUA_SRC_PATH}/loadlib.cpp
    ${LUA_SRC_PATH}/lobject.cpp
    ${LUA_SRC_PATH}/lopcodes.cpp
    ${LUA_SRC_PATH}/loslib.cpp
    ${LUA_SRC_PATH}/lparser.cpp
    ${LUA_SRC_PATH}/lstate.cpp
    ${LUA_SRC_PATH}/lstring.cpp
    ${LUA_SRC_PATH}/lstrlib.cpp
    ${LUA_SRC_PATH}/ltable.cpp
    ${LUA_SRC_PATH}/ltablib.cpp
    ${LUA_SRC_PATH}/ltm.cpp
    ${LUA_SRC_PATH}/lundump.cpp
    ${LUA_SRC_PATH}/lutf8lib.cpp
    ${LUA_SRC_PATH}/lvm.cpp
    ${LUA_SRC_PATH}/lzio.cpp
)

set(THIRDPART_INC_PATH "")
set(THIRDPART_SRC_FILES "")

#being third-party

#being lua socket
set(LUA_SOCKET_INC_PATH ${SLUA_SRC_ROOT}/Private/luasocket)
set(LUA_SOCKET_SRC_PATH ${SLUA_SRC_ROOT}/Private/luasocket)
set (LUA_SOCKET_SRC_FILES
    ${LUA_SOCKET_SRC_PATH}/auxiliar.cpp
    ${LUA_SOCKET_SRC_PATH}/auxiliar.h
    ${LUA_SOCKET_SRC_PATH}/buffer.cpp
    ${LUA_SOCKET_SRC_PATH}/buffer.h
    ${LUA_SOCKET_SRC_PATH}/except.cpp
    ${LUA_SOCKET_SRC_PATH}/except.h
    ${LUA_SOCKET_SRC_PATH}/ftp.lua.inc
    ${LUA_SOCKET_SRC_PATH}/headers.lua.inc
    ${LUA_SOCKET_SRC_PATH}/http.lua.inc
    ${LUA_SOCKET_SRC_PATH}/inet.cpp
    ${LUA_SOCKET_SRC_PATH}/inet.h
    ${LUA_SOCKET_SRC_PATH}/io.cpp
    ${LUA_SOCKET_SRC_PATH}/io.h
    ${LUA_SOCKET_SRC_PATH}/ltn12.lua.inc
    ${LUA_SOCKET_SRC_PATH}/luasocket.cpp
    ${LUA_SOCKET_SRC_PATH}/luasocket.h
    ${LUA_SOCKET_SRC_PATH}/mbox.lua.inc
    ${LUA_SOCKET_SRC_PATH}/mime.cpp
    ${LUA_SOCKET_SRC_PATH}/mime.h
    ${LUA_SOCKET_SRC_PATH}/mime.lua.inc
    ${LUA_SOCKET_SRC_PATH}/options.cpp
    ${LUA_SOCKET_SRC_PATH}/options.h
    ${LUA_SOCKET_SRC_PATH}/select.cpp
    ${LUA_SOCKET_SRC_PATH}/select.h
    ${LUA_SOCKET_SRC_PATH}/serial.cpp
    ${LUA_SOCKET_SRC_PATH}/smtp.lua.inc
    ${LUA_SOCKET_SRC_PATH}/socket.h
    ${LUA_SOCKET_SRC_PATH}/socket.lua.inc
    ${LUA_SOCKET_SRC_PATH}/tcp.cpp
    ${LUA_SOCKET_SRC_PATH}/tcp.h
    ${LUA_SOCKET_SRC_PATH}/timeout.cpp
    ${LUA_SOCKET_SRC_PATH}/timeout.h
    ${LUA_SOCKET_SRC_PATH}/tp.lua.inc
    ${LUA_SOCKET_SRC_PATH}/udp.cpp
    ${LUA_SOCKET_SRC_PATH}/udp.h
    ${LUA_SOCKET_SRC_PATH}/unix.cpp
    ${LUA_SOCKET_SRC_PATH}/unix.h
    ${LUA_SOCKET_SRC_PATH}/url.lua.inc
    ${LUA_SOCKET_SRC_PATH}/usocket.cpp
    ${LUA_SOCKET_SRC_PATH}/usocket.h
    ${LUA_SOCKET_SRC_PATH}/wsocket.cpp
    ${LUA_SOCKET_SRC_PATH}/wsocket.h
)
#end lua socket

set(THIRDPART_INC_PATH ${THIRDPART_INC_PATH} ${LUA_SOCKET_INC_PATH})
set(THIRDPART_SRC_FILES ${THIRDPART_SRC_FILES} ${LUA_SOCKET_SRC_FILES})
#end third-party

include_directories(
    ${LUA_INC_PATH}
    ${THIRDPART_INC_PATH}
)

ADD_LIBRARY(lua STATIC
    ${LUA_SRC_FILES}
    ${THIRDPART_SRC_FILES}
)

# if ( WIN32 AND NOT CYGWIN )
#     list (APPEND LUA_SOCKET luasocket/wsocket.c)
# else ( )
#     list (APPEND LUA_SOCKET luasocket/usocket.c)
# endif ( )

# set ( XLUA_CORE
#     i64lib.c
#     perflib.c
#     xlua.c
# )

# macro(source_group_by_dir proj_dir source_files)
#     if(MSVC OR APPLE)
#         get_filename_component(sgbd_cur_dir ${proj_dir} ABSOLUTE)
#         foreach(sgbd_file ${${source_files}})
#             get_filename_component(sgbd_abs_file ${sgbd_file} ABSOLUTE)
#             file(RELATIVE_PATH sgbd_fpath ${sgbd_cur_dir} ${sgbd_abs_file})
#             string(REGEX REPLACE "\(.*\)/.*" \\1 sgbd_group_name ${sgbd_fpath})
#             string(COMPARE EQUAL ${sgbd_fpath} ${sgbd_group_name} sgbd_nogroup)
#             string(REPLACE "/" "\\" sgbd_group_name ${sgbd_group_name})
#             if(sgbd_nogroup)
#                 set(sgbd_group_name "\\")
#             endif(sgbd_nogroup)
#             source_group(${sgbd_group_name} FILES ${sgbd_file})
#         endforeach(sgbd_file)
#     endif(MSVC OR APPLE)
# endmacro(source_group_by_dir)

# source_group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} LUA_SOCKET)
# source_group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} LUA_CORE)
# source_group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} LUA_LIB)
# source_group_by_dir(${CMAKE_CURRENT_SOURCE_DIR} XLUA_CORE)

# if (APPLE)
#     if (IOS)
#         set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD)")
#         add_library(xlua STATIC
#            ${LUA_CORE}
#            ${LUA_LIB}
#            ${LUA_SOCKET}
#            ${XLUA_CORE}
#            ${THIRDPART_SRC}
#         )
#         set_xcode_property (xlua IPHONEOS_DEPLOYMENT_TARGET "7.0")
#     else ()
#         set(CMAKE_OSX_ARCHITECTURES "$(ARCHS_STANDARD_32_64_BIT)")
#         add_library(xlua MODULE
#             ${LUA_CORE}
#             ${LUA_LIB}
#             ${LUA_SOCKET}
#             ${XLUA_CORE}
#             ${THIRDPART_SRC}
#         )
#         set_target_properties ( xlua PROPERTIES BUNDLE TRUE )
#         add_executable(run_xlua 
#             "main.c"
#             ${LUA_CORE}
#             ${LUA_LIB}
#             ${XLUA_CORE}
#             ${THIRDPART_SRC}
#         )
#     endif ()
# else ( )
#     add_library(xlua SHARED
#         ${LUA_CORE}
#         ${LUA_LIB}
#         ${LUA_SOCKET}
#         ${XLUA_CORE}
#         ${THIRDPART_SRC}
#     )
# endif ( )

# if ( WIN32 AND NOT CYGWIN )
#     target_compile_definitions (xlua PRIVATE LUA_BUILD_AS_DLL)
# endif ( )

# set_property(
# 	SOURCE ${LUA_SOCKET}
# 	APPEND
# 	PROPERTY COMPILE_DEFINITIONS
# 	LUA_COMPAT_APIINTCASTS LUA_LIB _CRT_SECURE_NO_WARNINGS _WINSOCK_DEPRECATED_NO_WARNINGS
# )

# if(UINT_ESPECIALLY)
#     ADD_DEFINITIONS(-DUINT_ESPECIALLY)
# endif()
	
# if ( WIN32 AND NOT CYGWIN )
#         target_link_libraries(xlua
#             ws2_32
#             ${THIRDPART_LIB} 
#         )
# else ( )
#         target_link_libraries(xlua
#             m
#             ${THIRDPART_LIB} 
#         )
# endif ( )

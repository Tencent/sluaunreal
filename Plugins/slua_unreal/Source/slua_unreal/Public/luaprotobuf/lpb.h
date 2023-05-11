#ifndef lpb_h
#define lpb_h

#include "lua.h"
#include "Containers/Array.h"

class FString;

namespace NS_SLUA {
    int luaopen_pb_conv(lua_State *L);
    int luaopen_pb_buffer(lua_State *L);
    int luaopen_pb_slice(lua_State *L);
    int luaopen_pb(lua_State *L);

    class SLUA_UNREAL_API ProtobufUtil
    {
    public:
        typedef TArray<uint8>(*LoadFileDelegate) (const FString& filepath);

        static LoadFileDelegate loadFileDelegate;
    };
} // end NS_SLUA

#endif

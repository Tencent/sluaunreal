#include "LuaObject.h"
#include "LuaSocket/luasocket.h"

namespace slua {

    int luasocket(lua_State *L){
        luaopen_socket_core(L);
        return 1;
    }

    void initDebugExtension(lua_State *L){
		AutoStack autoStack(L);
		//初始化Debug插件
		lua_pushglobaltable(L); // _G
		lua_newtable(L);		// _G, t
		lua_pushvalue(L, -1);	// _G, t, t 拷贝一个t
		lua_setfield(L, -3, "lua_extension"); // _G, t
		//引入luasocket
        lua_pushcfunction(L, luasocket);   // _G, t, f
		lua_setfield(L, -2, "luasocket");  // _G, t
    }
}
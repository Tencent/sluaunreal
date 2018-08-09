#pragma once
#include "CoreMinimal.h"
#include "lua/lua.hpp"
#include "UObject/UnrealType.h"

namespace slua {

	class SLUA_UNREAL_API LuaMap {

	public:
		static void reg(lua_State* L);
		static int push(lua_State* L, UProperty* keyProp, UProperty* valueProp, FScriptMap* buf);

		LuaMap(UProperty* keyProp, UProperty* valueProp, FScriptMap* buf);
		~LuaMap();

		const FScriptMap* get() {
			return &map;
		}

	protected:
		static int __ctor(lua_State* L);
        static int Num(lua_State* L);
        static int Get(lua_State* L);
        static int Add(lua_State* L);
        static int Remove(lua_State* L);
        static int Clear(lua_State* L);

	private:
		FScriptMap map;
		UProperty* keyProp;
		UProperty* valueProp;

		static int setupMT(lua_State* L);
		static int gc(lua_State* L);

		uint8* getKeyPtr(uint8* pairPtr);
		uint8* getValuePtr(uint8* pairPtr);
		void Clear();

	};
	
}

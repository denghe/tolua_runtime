#include <lua.hpp>
#ifdef _WIN64
#pragma comment(lib, "..\\lualib\\x64\\lua51.lib")
#else
#pragma comment(lib, "..\\lualib\\x86\\lua51.lib")
#endif
#include <stdint.h>
#include <assert.h>
#include <iostream>

extern "C"
{
	void tolua_openint64(lua_State* L);
	int  tolua_newint64(lua_State* L);
	void tolua_pushint64(lua_State* L, int64_t n);

	void tolua_openuint64(lua_State* L);
	int  tolua_newuint64(lua_State* L);
	//void tolua_pushuint64(lua_State* L, uint64_t n);	// tolua.h 中没这句
}

int TestInt64(lua_State *L)
{
	luaL_openlibs(L);
	tolua_openint64(L);
	if (luaL_dostring(L, R"--(

local a = int64.new()
print( a )
a = 10
a = a * 2
local b = a
b = b + 1
print( a, b )

)--")) return lua_error(L);
	return 0;
}

int main()
{
	auto L = luaL_newstate();
	assert(L);
	lua_pushcfunction(L, TestInt64);
	auto rtv = lua_pcall(L, 0, 0, 0);
	if (rtv != LUA_OK)
	{
		std::cout << "pcall rtv = " << rtv << ", errmsg = " << lua_tostring(L, -1) << std::endl;
		lua_pop(L, 1);
	}
	lua_close(L);
	return 0;
}

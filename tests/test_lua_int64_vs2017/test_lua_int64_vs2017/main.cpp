#include <stdint.h>
#include <assert.h>
#include <iostream>
#include "lua_xx.h"

int TestInt64(lua_State *L)
{
	luaL_openlibs(L);
	tolua_openint64(L);
	tolua_openuint64(L);
	xxlua_openxx(L);
	if (luaL_dostring(L, R"--(

local a = uint64.new()
a = 1
local b = a
a = 2
print( a, b )

local bb = BBuffer.Create()
bb:WriteUInt64( a, b )
print( bb )

print( bb:ReadUInt64( 2 ) )

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
		std::cout << "pcall rtv = " << rtv
			<< ", errmsg = " << lua_tostring(L, -1) 
			<< std::endl;
		lua_pop(L, 1);
	}
	lua_close(L);
	return 0;
}

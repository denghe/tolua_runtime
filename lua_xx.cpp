#include <lua.hpp>
#include <stdint.h>
// 当前所有 luaL_checkstack 都被省略掉了. 料想堆栈深度不会超过 20


// 在 ud ( -1 ) 上附加数据类型标记. 需求 T::name 指针
template<typename T>
inline static void AttachTypeTag(lua_State* L)
{
#if LUA_VERSION_NUM >= 503
	lua_pushlightuserdata(L, (void*)T::name);	// ..., ud, name
	lua_setuservalue(L, -2);					// ..., ud
#endif
}


// userdata 转 T*. 检查数据类型标记
template<typename T>
inline static T* GetPointer(lua_State* L, int idx)
{
	auto p = (T*)lua_touserdata(L, idx);
	if (!p) return nullptr;
#if LUA_VERSION_NUM >= 503
	auto t = lua_getuservalue(L, idx);			// ..., name
	if (t != LUA_TLIGHTUSERDATA || lua_touserdata(L, -1) != T::name)
	{
		lua_pop(L, 1);							// ...
		return nullptr;
	}
	return p;
#else
	// 判断 metatable 是否一致
	if (!lua_getmetatable(L, idx))				// ..., mt
	{
		return nullptr;
	}
	lua_getglobal(L, T::name);					// ..., mt, mt
	auto e = lua_rawequal(L, -1, -2);
	lua_pop(L, 2);
	return e ? p : nullptr;
#endif
}


extern "C"
{
	void tolua_openint64(lua_State* L);
	int  tolua_newint64(lua_State* L);
	void tolua_pushint64(lua_State* L, int64_t n);
	int64_t tolua_toint64(lua_State* L, int pos);

	void tolua_openuint64(lua_State* L);
	int  tolua_newuint64(lua_State* L);
	void tolua_pushuint64(lua_State* L, uint64_t n);
	uint64_t tolua_touint64(lua_State* L, int pos);
}


#include "lua_xxbbuffer.h"
#include "lua_xxnbsocket.h"
#include "lua_xxudpsocket.h"


extern "C" void xxlua_openxx(lua_State* L)
{
	Lua_XxBBuffer::LuaInit(L);
	Lua_XxNBSocket::LuaInit(L);
}

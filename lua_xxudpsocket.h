#pragma execution_character_set("utf-8")
#pragma once
#include "xxudpsocket.h"
#include <deque>

struct Lua_XxUdpSocket : XxUdpSocket
{
	Lua_XxUdpSocket(lua_State* L) : XxUdpSocket() {}
	// ~Lua_XxUdpSocket() {} 析构不需要写

	Lua_XxUdpSocket(Lua_XxUdpSocket const&) = delete;
	Lua_XxUdpSocket& operator=(Lua_XxUdpSocket const&) = delete;

	// 注册到 lua 中的全局名
	constexpr static const char* name = "UdpSocket";

	// 向 lua 映射全局的 BBuffer 表/元表
	inline static void LuaInit(lua_State *L)
	{
		luaL_Reg funcs[] =
		{
			{ "__gc", __gc },
			{ "Create", Create },
			{ "__tostring", __tostring },

			{ "SetAddress", SetAddress_ },
			{ "Connect", Connect_ },
			{ "Disconnect", Disconnect_ },
			{ "Update", Update_ },
			{ "Send", Send_ },
			{ "GetTicks", GetTicks_ },
			{ "GetState", GetState_ },
			{ "PopRecv", PopRecv_ },

			// 顺便集成一个 queue<pair<int, uint>> 在这 for RPC
			{ "PushSerial", PushSerial_ },
			{ "PeekSerial", PeekSerial_ },
			{ "PopSerial", PopSerial_ },

			{ nullptr, nullptr }
		};
		lua_createtable(L, 0, _countof(funcs));	// mt
		luaL_setfuncs(L, funcs, 0);				// mt

		// 设成自查找 for metatable
		lua_pushvalue(L, -1);					// mt, mt
		lua_setfield(L, -2, "__index");			// mt

		// 设置保护元表
		lua_pushvalue(L, -1);					// mt, mt
		lua_setfield(L, -2, "__metatable");		// mt

		lua_setglobal(L, name);					// 

		// 在全局造一个 UdpSocketStates 的表 以方便 判断 当前状态
		lua_createtable(L, 0, 4);				// t
		lua_pushinteger(L, 0);					// t, 0
		lua_setfield(L, -2, "Disconnected");	// t
		lua_pushinteger(L, 1);					// t, 1
		lua_setfield(L, -2, "Connecting");		// t
		lua_pushinteger(L, 2);					// t, 2
		lua_setfield(L, -2, "Connected");		// t
		lua_pushinteger(L, 3);					// t, 3
		lua_setfield(L, -2, "Disconnecting");	// t
		lua_setglobal(L, "UdpSocketStates");	// 

		// 初始化网络环境
		XxUdpSocket::SockInit();
	}

	/**************************************************************************************************/
	// 下面是各种映射函数的具体实现
	/**************************************************************************************************/


	// 析构
	inline static int __gc(lua_State* L)
	{
		auto& self = *(Lua_XxUdpSocket*)lua_touserdata(L, -1);
		self.~Lua_XxUdpSocket();
		return 0;
	}

	// 创建, 无参数
	inline static int Create(lua_State* L)
	{
		auto& self = *(Lua_XxUdpSocket*)lua_newuserdata(L, sizeof(Lua_XxUdpSocket));	//	出异常: 无副作用
		lua_getglobal(L, name);					// ..., ud, mt						出异常: self 被 LUA gc 回收
		new (&self) Lua_XxUdpSocket(L);			//									出异常: 因为未绑元表, 不会执行 __gc
		AttachTypeTag<Lua_XxBBuffer>(L);		// ..., ud							出异常：因为未绑元表, 不会执行 __gc
		lua_setmetatable(L, -2);				// ..., ud							不出异常, 绑上元表
		return 1;
	}

	inline static Lua_XxUdpSocket& GetSelf(lua_State* L, int top)
	{
		if (lua_gettop(L) < top)
		{
			luaL_error(L, "less arg nums. expect %d+", top);
		}
		auto p = GetPointer<Lua_XxUdpSocket>(L, 1);
		if (!p)
		{
			luaL_error(L, "first arg isn't UdpSocket( forget \":\" ? )");
		}
		return *p;
	}

	inline static int __tostring(lua_State* L)
	{
		static std::array<char const*, 4> ss =
		{
			"Disconnected",
			"Connecting",
			"Connected",
			"Disconnecting"
		};
		auto& self = GetSelf(L, 1);
		std::string s;
		s += "{ \"state\" : ";
		s += ss[(int)self.state];
		s += ", \"ticks\" : " + std::to_string(self.ticks) + "}";
		lua_pushlstring(L, s.c_str(), s.size());
		return 1;
	}

	// 设置目标地址, 成功返回 0. 失败返回错误码
	// inline int SetAddress(char const* const& ip, uint16_t const& port)
	inline static int SetAddress_(lua_State* L)
	{
		auto& self = GetSelf(L, 3);

		static auto em_ip = "args[2]: ipv4  must be a valid string. like  127.0.0.1 ";
		if (!lua_isstring(L, 2))
		{
			return luaL_error(L, em_ip);
		}

		size_t sLen;
		auto s = lua_tolstring(L, 2, &sLen);
		if (sLen == 0)
		{
			return luaL_error(L, em_ip);
		}

		int isnum;
		auto n = (uint32_t)lua_tointegerx(L, 3, &isnum);
		if (!isnum || n <= 0 || n > 65535)
		{
			luaL_error(L, "the args[ 3 ]: ipv4's port 's type must be a integer, range 1 ~ 65535.");
		}

		auto r = self.SetAddress(s, (uint16_t)n);
		lua_pushinteger(L, r);
		return 1;
	}

	// 返回非0 表示出错. 0 表示成功
	// inline int Connect(int const& sec = 0, int const& usec = 0)
	inline static int Connect_(lua_State* L)
	{
		auto& self = GetSelf(L, 1);
		int top = lua_gettop(L);
		if (top > 3)
		{
			luaL_error(L, "the args's count must be 1 ~ 3: self, int sec = 0, int usec = 0");
		}

		int isnum, n1 = 0, n2 = 0;
		if (top >= 2)
		{
			n1 = (int)lua_tointegerx(L, 2, &isnum);
			if (!isnum)
			{
				luaL_error(L, "the args[ 2 ]: sec 's type must be a integer");
			}
		}
		if (top >= 3)
		{
			n2 = (int)lua_tointegerx(L, 3, &isnum);
			if (!isnum)
			{
				luaL_error(L, "the args[ 3 ]: usec 's type must be a integer");
			}
		}

		int r = self.Connect(n1, n2);
		lua_pushinteger(L, r);
		return 1;
	}

	// 断开连接
	// inline void Disconnect(int delayTicks = 0)
	inline static int Disconnect_(lua_State* L)
	{
		auto& self = GetSelf(L, 1);
		int top = lua_gettop(L);
		if (top > 3)
		{
			luaL_error(L, "the args's count must be 1 ~ 2: self, int delayTicks = 0");
		}

		int isnum, n1 = 0;
		if (top >= 2)
		{
			n1 = (int)lua_tointegerx(L, 2, &isnum);
			if (!isnum)
			{
				luaL_error(L, "the args[ 2 ]: delayTicks 's type must be a integer");
			}
		}

		self.Disconnect(n1);
		return 0;
	}


	// 返回负数表示出错. 0 表示没发生错误
	//inline int Update(int const& sec = 0, int const& usec = 0)
	inline static int Update_(lua_State* L)
	{
		auto& self = GetSelf(L, 1);
		int top = lua_gettop(L);
		if (top > 3)
		{
			luaL_error(L, "the args's count must be 1 ~ 3: self, int sec = 0, int usec = 0");
		}

		int isnum, n1 = 0, n2 = 0;
		if (top >= 2)
		{
			n1 = (int)lua_tointegerx(L, 2, &isnum);
			if (!isnum)
			{
				luaL_error(L, "the args[ 2 ]: sec 's type must be a integer");
			}
		}
		if (top >= 3)
		{
			n2 = (int)lua_tointegerx(L, 3, &isnum);
			if (!isnum)
			{
				luaL_error(L, "the args[ 3 ]: usec 's type must be a integer");
			}
		}

		int r = self.Update(n1, n2);
		lua_pushinteger(L, r);
		return 1;
	}



	// 返回负数表示出错. 0 表示成功放入待发送队列或无数据可发. > 0 表示已立刻发送成功的长度. 
	// 如果有剩下部分, 会放入待发送队列, 在下次 Update 时继续发
	// inline int Send(char const* const& buf, int const& dataLen)		// 实参: Lua_XxBBuffer* bb
	inline static int Send_(lua_State* L)
	{
		auto& self = GetSelf(L, 2);
		auto bb = GetPointer<Lua_XxBBuffer>(L, 2);
		if (!bb)
		{
			luaL_error(L, "arg[ 2 ] isn't BBuffer( forget \":\" ? )");
		}

		int r = self.Send(bb->buf, bb->dataLen);
		lua_pushinteger(L, r);
		return 1;
	}

	// 返回当前状态持续帧数
	// this.ticks
	inline static int GetTicks_(lua_State* L)
	{
		auto& self = GetSelf(L, 1);
		lua_pushinteger(L, self.ticks);
		return 1;
	}

	// 返回当前连接状态
	// this.state
	inline static int GetState_(lua_State* L)
	{
		auto& self = GetSelf(L, 1);
		lua_pushinteger(L, (int)self.state);
		return 1;
	}

	// 返回 Lua_XxBBuffer ( 如果有收到包 ) 或 nil
	// this.recvBufs.front
	inline static int PopRecv_(lua_State* L)
	{
		auto& self = GetSelf(L, 1);
		if (self.recvBufs.empty()) return 0;
		decltype(auto) bb = self.recvBufs.front();
		Lua_XxBBuffer::Create(L);
		auto& rtv = *(Lua_XxBBuffer*)lua_touserdata(L, -1);
		rtv.buf = bb.buf;
		rtv.dataLen = bb.dataLen;
		bb.buf = nullptr;
		bb.dataLen = 0;
		self.recvBufs.pop_front();
		return 1;
	}

	
	std::deque<std::pair<int, uint32_t>> serials;
	inline static int PushSerial_(lua_State* L)
	{
		auto& self = GetSelf(L, 3);

		int isnum;
		auto k = (int)lua_tointegerx(L, 2, &isnum);
		if (!isnum)
		{
			luaL_error(L, "the args[ 2 ]: sec 's type must be a integer");
		}
		auto v = (uint32_t)lua_tointegerx(L, 3, &isnum);
		if (!isnum)
		{
			luaL_error(L, "the args[ 3 ]: usec 's type must be a integer");
		}

		self.serials.push_back(std::make_pair(k, v));
		return 0;
	}

	inline static int PeekSerial_(lua_State* L)
	{
		auto& self = GetSelf(L, 1);
		if (self.serials.empty()) return 0;
		auto& kv = self.serials.front();
		lua_pushinteger(L, kv.first);
		lua_pushinteger(L, kv.second);
		return 2;
	}

	inline static int PopSerial_(lua_State* L)
	{
		auto& self = GetSelf(L, 1);
		if (!self.serials.empty())
		{
			self.serials.pop_front();
		}
		return 0;
	}
};

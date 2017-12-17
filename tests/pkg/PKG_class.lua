
--[[
玩家
]]
PKG_Player = {
    typeName = "PKG_Player",
    typeId = 5,
    Create = function()
        local o = {}
        o.__proto = PKG_Player
        o.__index = o
        o.__newindex = o

        --[[
        玩家id
        ]]
        o.playerId = 0 -- Int32
        --[[
        当前金币数
        ]]
        o.coin = 0 -- Int64
        --[[
        玩家座次
        ]]
        o.pos = 0 -- Int32
        return o
    end,
    FromBBuffer = function( bb, o )
        local ReadInt32 = bb:ReadInt32
        o.playerId = ReadInt32( bb )
        o.coin = bb:ReadInt64()
        o.pos = ReadInt32( bb )
    end,
    ToBBuffer = function( bb, o )
        local WriteInt32 = bb:WriteInt32
        WriteInt32( bb, o.playerId )
        bb:WriteInt64( o.coin )
        WriteInt32( bb, o.pos )
    end
}
BBuffer.Register( PKG_Player )
--[[
鱼
]]
PKG_Fish = {
    typeName = "PKG_Fish",
    typeId = 6,
    Create = function()
        local o = {}
        o.__proto = PKG_Fish
        o.__index = o
        o.__newindex = o

        o.id = 0 -- Int32
        o.typeId = 0 -- Int32
        o.ticks = 0 -- Int32
        o.x = 0 -- Single
        o.y = 0 -- Single
        return o
    end,
    FromBBuffer = function( bb, o )
        local ReadInt32 = bb:ReadInt32
        local ReadSingle = bb:ReadSingle
        o.id = ReadInt32( bb )
        o.typeId = ReadInt32( bb )
        o.ticks = ReadInt32( bb )
        o.x = ReadSingle( bb )
        o.y = ReadSingle( bb )
    end,
    ToBBuffer = function( bb, o )
        local WriteInt32 = bb:WriteInt32
        local WriteSingle = bb:WriteSingle
        WriteInt32( bb, o.id )
        WriteInt32( bb, o.typeId )
        WriteInt32( bb, o.ticks )
        WriteSingle( bb, o.x )
        WriteSingle( bb, o.y )
    end
}
BBuffer.Register( PKG_Fish )
--[[
子弹
]]
PKG_Bullet = {
    typeName = "PKG_Bullet",
    typeId = 7,
    Create = function()
        local o = {}
        o.__proto = PKG_Bullet
        o.__index = o
        o.__newindex = o

        --[[
        玩家id
        ]]
        o.playerId = 0 -- Int32
        --[[
        自增流水号
        ]]
        o.serial = 0 -- Int32
        --[[
        时间戳
        ]]
        o.ticks = 0 -- Int32
        --[[
        武器类型id( 根据配置来, 决定了类型和倍率啥的 )
        ]]
        o.typeId = 0 -- Int32
        --[[
        矢量 / 坐标
        ]]
        o.vecX = 0 -- Single
        --[[
        矢量 / 坐标
        ]]
        o.vecY = 0 -- Single
        return o
    end,
    FromBBuffer = function( bb, o )
        local ReadInt32 = bb:ReadInt32
        local ReadSingle = bb:ReadSingle
        o.playerId = ReadInt32( bb )
        o.serial = ReadInt32( bb )
        o.ticks = ReadInt32( bb )
        o.typeId = ReadInt32( bb )
        o.vecX = ReadSingle( bb )
        o.vecY = ReadSingle( bb )
    end,
    ToBBuffer = function( bb, o )
        local WriteInt32 = bb:WriteInt32
        local WriteSingle = bb:WriteSingle
        WriteInt32( bb, o.playerId )
        WriteInt32( bb, o.serial )
        WriteInt32( bb, o.ticks )
        WriteInt32( bb, o.typeId )
        WriteSingle( bb, o.vecX )
        WriteSingle( bb, o.vecY )
    end
}
BBuffer.Register( PKG_Bullet )
--[[
开奖 / 命中 / 杀死
]]
PKG_Draw = {
    typeName = "PKG_Draw",
    typeId = 8,
    Create = function()
        local o = {}
        o.__proto = PKG_Draw
        o.__index = o
        o.__newindex = o

        local null = _G.null
        --[[
        玩家id
        ]]
        o.playerId = 0 -- Int32
        --[[
        子弹 自增流水号
        ]]
        o.serial = 0 -- Int32
        --[[
        杀死了哪些鱼的 id
        ]]
        o.killFishIds = null -- List_Int32_
        --[[
        打中了哪些鱼 id
        ]]
        o.hitFishIds = null -- List_Int32_
        return o
    end,
    FromBBuffer = function( bb, o )
        local ReadInt32 = bb:ReadInt32
        local ReadObject = bb:ReadObject
        o.playerId = ReadInt32( bb )
        o.serial = ReadInt32( bb )
        o.killFishIds = ReadObject( bb )
        o.hitFishIds = ReadObject( bb )
    end,
    ToBBuffer = function( bb, o )
        local WriteInt32 = bb:WriteInt32
        local WriteObject = bb:WriteObject
        WriteInt32( bb, o.playerId )
        WriteInt32( bb, o.serial )
        WriteObject( bb, o.killFishIds )
        WriteObject( bb, o.hitFishIds )
    end
}
BBuffer.Register( PKG_Draw )
List_Int32_ = {
    typeName = "List_Int32_",
    typeId = 9,
    Create = function()
        local o = {}
        o.__proto = List_Int32_
        o.__index = o
        o.__newindex = o
        return o
    end,
    FromBBuffer = function( bb, o )
		local len = bb:ReadUInt32()
        local f = BBuffer.ReadInt32
		for i = 1, len do
			o[ i ] = f( bb )
		end
    end,
    ToBBuffer = function( bb, o )
        local len = #o
		bb:WriteUInt32( len )
        local f = BBuffer.WriteInt32
        for i = 1, len do
			f( bb, o[ i ] )
		end
    end
}
BBuffer.Register( List_Int32_ )
--[[
登录
]]
PKG_Client_Server1_Join = {
    typeName = "PKG_Client_Server1_Join",
    typeId = 3,
    Create = function()
        local o = {}
        o.__proto = PKG_Client_Server1_Join
        o.__index = o
        o.__newindex = o

        --[[
        告诉服务器自己是谁
        ]]
        o.id = 0 -- Int32
        return o
    end,
    FromBBuffer = function( bb, o )
        o.id = bb:ReadInt32()
    end,
    ToBBuffer = function( bb, o )
        bb:WriteInt32( o.id )
    end
}
BBuffer.Register( PKG_Client_Server1_Join )
--[[
发射 / 付款
]]
PKG_Client_Server1_Fire = {
    typeName = "PKG_Client_Server1_Fire",
    typeId = 10,
    Create = function()
        local o = {}
        o.__proto = PKG_Client_Server1_Fire
        o.__index = o
        o.__newindex = o

        local null = _G.null
        --[[
        有可能瞬间发出不止一发子弹, 故 List
        ]]
        o.bullets = null -- List_PKG_Bullet_
        return o
    end,
    FromBBuffer = function( bb, o )
        o.bullets = bb:ReadObject()
    end,
    ToBBuffer = function( bb, o )
        bb:WriteObject( o.bullets )
    end
}
BBuffer.Register( PKG_Client_Server1_Fire )
List_PKG_Bullet_ = {
    typeName = "List_PKG_Bullet_",
    typeId = 11,
    Create = function()
        local o = {}
        o.__proto = List_PKG_Bullet_
        o.__index = o
        o.__newindex = o
        return o
    end,
    FromBBuffer = function( bb, o )
		local len = bb:ReadUInt32()
        local f = BBuffer.ReadObject
		for i = 1, len do
			o[ i ] = f( bb )
		end
    end,
    ToBBuffer = function( bb, o )
        local len = #o
		bb:WriteUInt32( len )
        local f = BBuffer.WriteObject
        for i = 1, len do
			f( bb, o[ i ] )
		end
    end
}
BBuffer.Register( List_PKG_Bullet_ )
--[[
命中检测 / 抽奖
]]
PKG_Client_Server1_Hit = {
    typeName = "PKG_Client_Server1_Hit",
    typeId = 12,
    Create = function()
        local o = {}
        o.__proto = PKG_Client_Server1_Hit
        o.__index = o
        o.__newindex = o

        local null = _G.null
        --[[
        子弹流水号
        ]]
        o.serial = 0 -- Int32
        --[[
        客户端自认为打中了哪些鱼的 id
        ]]
        o.fishIds = null -- List_Int32_
        return o
    end,
    FromBBuffer = function( bb, o )
        o.serial = bb:ReadInt32()
        o.fishIds = bb:ReadObject()
    end,
    ToBBuffer = function( bb, o )
        bb:WriteInt32( o.serial )
        bb:WriteObject( o.fishIds )
    end
}
BBuffer.Register( PKG_Client_Server1_Hit )
--[[
加入成功
]]
PKG_Server1_Client_JoinSuccess = {
    typeName = "PKG_Server1_Client_JoinSuccess",
    typeId = 4,
    Create = function()
        local o = {}
        o.__proto = PKG_Server1_Client_JoinSuccess
        o.__index = o
        o.__newindex = o

        local null = _G.null
        --[[
        房间内所有玩家
        ]]
        o.players = null -- List_PKG_Player_
        --[[
        当前玩家id
        ]]
        o.selfId = 0 -- Int32
        --[[
        同步显示当前房间里所有活着的鱼的情况
        ]]
        o.fishs = null -- List_PKG_Fish_
        --[[
        同步帧编号
        ]]
        o.ticks = 0 -- Int32
        return o
    end,
    FromBBuffer = function( bb, o )
        local ReadObject = bb:ReadObject
        local ReadInt32 = bb:ReadInt32
        o.players = ReadObject( bb )
        o.selfId = ReadInt32( bb )
        o.fishs = ReadObject( bb )
        o.ticks = ReadInt32( bb )
    end,
    ToBBuffer = function( bb, o )
        local WriteObject = bb:WriteObject
        local WriteInt32 = bb:WriteInt32
        WriteObject( bb, o.players )
        WriteInt32( bb, o.selfId )
        WriteObject( bb, o.fishs )
        WriteInt32( bb, o.ticks )
    end
}
BBuffer.Register( PKG_Server1_Client_JoinSuccess )
List_PKG_Player_ = {
    typeName = "List_PKG_Player_",
    typeId = 15,
    Create = function()
        local o = {}
        o.__proto = List_PKG_Player_
        o.__index = o
        o.__newindex = o
        return o
    end,
    FromBBuffer = function( bb, o )
		local len = bb:ReadUInt32()
        local f = BBuffer.ReadObject
		for i = 1, len do
			o[ i ] = f( bb )
		end
    end,
    ToBBuffer = function( bb, o )
        local len = #o
		bb:WriteUInt32( len )
        local f = BBuffer.WriteObject
        for i = 1, len do
			f( bb, o[ i ] )
		end
    end
}
BBuffer.Register( List_PKG_Player_ )
List_PKG_Fish_ = {
    typeName = "List_PKG_Fish_",
    typeId = 18,
    Create = function()
        local o = {}
        o.__proto = List_PKG_Fish_
        o.__index = o
        o.__newindex = o
        return o
    end,
    FromBBuffer = function( bb, o )
		local len = bb:ReadUInt32()
        local f = BBuffer.ReadObject
		for i = 1, len do
			o[ i ] = f( bb )
		end
    end,
    ToBBuffer = function( bb, o )
        local len = #o
		bb:WriteUInt32( len )
        local f = BBuffer.WriteObject
        for i = 1, len do
			f( bb, o[ i ] )
		end
    end
}
BBuffer.Register( List_PKG_Fish_ )
--[[
加入失败
]]
PKG_Server1_Client_JoinFail = {
    typeName = "PKG_Server1_Client_JoinFail",
    typeId = 13,
    Create = function()
        local o = {}
        o.__proto = PKG_Server1_Client_JoinFail
        o.__index = o
        o.__newindex = o

        local null = _G.null
        o.errMsg = null -- String
        return o
    end,
    FromBBuffer = function( bb, o )
        o.errMsg = bb:ReadObject()
    end,
    ToBBuffer = function( bb, o )
        bb:WriteObject( o.errMsg )
    end
}
BBuffer.Register( PKG_Server1_Client_JoinFail )
--[[
广播成功加入的玩家
]]
PKG_Server1_Client_PushJoin = {
    typeName = "PKG_Server1_Client_PushJoin",
    typeId = 14,
    Create = function()
        local o = {}
        o.__proto = PKG_Server1_Client_PushJoin
        o.__index = o
        o.__newindex = o

        local null = _G.null
        o.players = null -- List_PKG_Player_
        return o
    end,
    FromBBuffer = function( bb, o )
        o.players = bb:ReadObject()
    end,
    ToBBuffer = function( bb, o )
        bb:WriteObject( o.players )
    end
}
BBuffer.Register( PKG_Server1_Client_PushJoin )
--[[
广播离开房间的玩家
]]
PKG_Server1_Client_PushLeave = {
    typeName = "PKG_Server1_Client_PushLeave",
    typeId = 16,
    Create = function()
        local o = {}
        o.__proto = PKG_Server1_Client_PushLeave
        o.__index = o
        o.__newindex = o

        local null = _G.null
        o.playerIds = null -- List_Int32_
        return o
    end,
    FromBBuffer = function( bb, o )
        o.playerIds = bb:ReadObject()
    end,
    ToBBuffer = function( bb, o )
        bb:WriteObject( o.playerIds )
    end
}
BBuffer.Register( PKG_Server1_Client_PushLeave )
--[[
鱼流数据推送
]]
PKG_Server1_Client_PushFish = {
    typeName = "PKG_Server1_Client_PushFish",
    typeId = 17,
    Create = function()
        local o = {}
        o.__proto = PKG_Server1_Client_PushFish
        o.__index = o
        o.__newindex = o

        local null = _G.null
        o.fishs = null -- List_PKG_Fish_
        return o
    end,
    FromBBuffer = function( bb, o )
        o.fishs = bb:ReadObject()
    end,
    ToBBuffer = function( bb, o )
        bb:WriteObject( o.fishs )
    end
}
BBuffer.Register( PKG_Server1_Client_PushFish )
--[[
子弹数据广播
]]
PKG_Server1_Client_PushFire = {
    typeName = "PKG_Server1_Client_PushFire",
    typeId = 19,
    Create = function()
        local o = {}
        o.__proto = PKG_Server1_Client_PushFire
        o.__index = o
        o.__newindex = o

        local null = _G.null
        o.bullets = null -- List_PKG_Bullet_
        return o
    end,
    FromBBuffer = function( bb, o )
        o.bullets = bb:ReadObject()
    end,
    ToBBuffer = function( bb, o )
        bb:WriteObject( o.bullets )
    end
}
BBuffer.Register( PKG_Server1_Client_PushFire )
--[[
中奖数据推送
]]
PKG_Server1_Client_PushDraw = {
    typeName = "PKG_Server1_Client_PushDraw",
    typeId = 20,
    Create = function()
        local o = {}
        o.__proto = PKG_Server1_Client_PushDraw
        o.__index = o
        o.__newindex = o

        local null = _G.null
        o.draws = null -- List_PKG_Draw_
        return o
    end,
    FromBBuffer = function( bb, o )
        o.draws = bb:ReadObject()
    end,
    ToBBuffer = function( bb, o )
        bb:WriteObject( o.draws )
    end
}
BBuffer.Register( PKG_Server1_Client_PushDraw )
List_PKG_Draw_ = {
    typeName = "List_PKG_Draw_",
    typeId = 21,
    Create = function()
        local o = {}
        o.__proto = List_PKG_Draw_
        o.__index = o
        o.__newindex = o
        return o
    end,
    FromBBuffer = function( bb, o )
		local len = bb:ReadUInt32()
        local f = BBuffer.ReadObject
		for i = 1, len do
			o[ i ] = f( bb )
		end
    end,
    ToBBuffer = function( bb, o )
        local len = #o
		bb:WriteUInt32( len )
        local f = BBuffer.WriteObject
        for i = 1, len do
			f( bb, o[ i ] )
		end
    end
}
BBuffer.Register( List_PKG_Draw_ )
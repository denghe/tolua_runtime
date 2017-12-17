
PKG_Client_Server1_Join = {
    typeName = "PKG_Client_Server1_Join",
    typeId = 3,
    Create = function()
        local o = {}
        o.__proto = PKG_Client_Server1_Join
        o.__index = o
        o.__newindex = o

        return o
    end,
    FromBBuffer = function( bb, o )
    end,
    ToBBuffer = function( bb, o )
    end
}
BBuffer.Register( PKG_Client_Server1_Join )
PKG_Client_Server1_Logout = {
    typeName = "PKG_Client_Server1_Logout",
    typeId = 4,
    Create = function()
        local o = {}
        o.__proto = PKG_Client_Server1_Logout
        o.__index = o
        o.__newindex = o

        return o
    end,
    FromBBuffer = function( bb, o )
    end,
    ToBBuffer = function( bb, o )
    end
}
BBuffer.Register( PKG_Client_Server1_Logout )
PKG_Server1_Client_JoinSuccess = {
    typeName = "PKG_Server1_Client_JoinSuccess",
    typeId = 5,
    Create = function()
        local o = {}
        o.__proto = PKG_Server1_Client_JoinSuccess
        o.__index = o
        o.__newindex = o

        return o
    end,
    FromBBuffer = function( bb, o )
    end,
    ToBBuffer = function( bb, o )
    end
}
BBuffer.Register( PKG_Server1_Client_JoinSuccess )
PKG_Server1_Client_PushMessage = {
    typeName = "PKG_Server1_Client_PushMessage",
    typeId = 6,
    Create = function()
        local o = {}
        o.__proto = PKG_Server1_Client_PushMessage
        o.__index = o
        o.__newindex = o

        local null = _G.null
        o.id = 0 -- Int64
        o.text = null -- String
        return o
    end,
    FromBBuffer = function( bb, o )
        o.id = bb:ReadInt64()
        o.text = bb:ReadObject()
    end,
    ToBBuffer = function( bb, o )
        bb:WriteInt64( o.id )
        bb:WriteObject( o.text )
    end
}
BBuffer.Register( PKG_Server1_Client_PushMessage )
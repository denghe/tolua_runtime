#include <xx_mempool.h>
#include <xx_bbuffer.h>

namespace PKG
{
namespace Client_Server1
{
    struct Join;
    using Join_p = xx::Ptr<Join>;
    using Join_v = xx::Dock<Join>;

    struct Logout;
    using Logout_p = xx::Ptr<Logout>;
    using Logout_v = xx::Dock<Logout>;

}
namespace Server1_Client
{
    struct JoinSuccess;
    using JoinSuccess_p = xx::Ptr<JoinSuccess>;
    using JoinSuccess_v = xx::Dock<JoinSuccess>;

    struct PushMessage;
    using PushMessage_p = xx::Ptr<PushMessage>;
    using PushMessage_v = xx::Dock<PushMessage>;

}
namespace Client_Server1
{
    struct Join : xx::Object
    {

        typedef Join ThisType;
        typedef xx::Object BaseType;
	    Join();
	    Join(xx::BBuffer *bb);
		Join(Join const&) = delete;
		Join& operator=(Join const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
    struct Logout : xx::Object
    {

        typedef Logout ThisType;
        typedef xx::Object BaseType;
	    Logout();
	    Logout(xx::BBuffer *bb);
		Logout(Logout const&) = delete;
		Logout& operator=(Logout const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
}
namespace Server1_Client
{
    struct JoinSuccess : xx::Object
    {

        typedef JoinSuccess ThisType;
        typedef xx::Object BaseType;
	    JoinSuccess();
	    JoinSuccess(xx::BBuffer *bb);
		JoinSuccess(JoinSuccess const&) = delete;
		JoinSuccess& operator=(JoinSuccess const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
    struct PushMessage : xx::Object
    {
        int64_t id = 0;
        xx::String_p text;

        typedef PushMessage ThisType;
        typedef xx::Object BaseType;
	    PushMessage();
	    PushMessage(xx::BBuffer *bb);
		PushMessage(PushMessage const&) = delete;
		PushMessage& operator=(PushMessage const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
}
namespace Client_Server1
{
	inline Join::Join()
	{
	}
	inline Join::Join(xx::BBuffer *bb)
	{
	}
    inline void Join::ToBBuffer(xx::BBuffer &bb) const
    {
    }
    inline int Join::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        return rtv;
    }

    inline void Join::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"Join\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void Join::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
    }


	inline Logout::Logout()
	{
	}
	inline Logout::Logout(xx::BBuffer *bb)
	{
	}
    inline void Logout::ToBBuffer(xx::BBuffer &bb) const
    {
    }
    inline int Logout::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        return rtv;
    }

    inline void Logout::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"Logout\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void Logout::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
    }


}
namespace Server1_Client
{
	inline JoinSuccess::JoinSuccess()
	{
	}
	inline JoinSuccess::JoinSuccess(xx::BBuffer *bb)
	{
	}
    inline void JoinSuccess::ToBBuffer(xx::BBuffer &bb) const
    {
    }
    inline int JoinSuccess::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        return rtv;
    }

    inline void JoinSuccess::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"JoinSuccess\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void JoinSuccess::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
    }


	inline PushMessage::PushMessage()
	{
	}
	inline PushMessage::PushMessage(xx::BBuffer *bb)
	{
	    int rtv = 0;
        if (rtv = bb->Read(id)) throw rtv;
        bb->readLengthLimit = 0;
        if (rtv = bb->Read(text)) throw rtv;
	}
    inline void PushMessage::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->id);
        bb.Write(this->text);
    }
    inline int PushMessage::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        if (rtv = bb.Read(this->id)) return rtv;
        bb.readLengthLimit = 0;
        if (rtv = bb.Read(this->text)) return rtv;
        return rtv;
    }

    inline void PushMessage::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"PushMessage\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void PushMessage::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"id\" : ", this->id);
        str.Append(", \"text\" : ", this->text);
    }


}
}
namespace xx
{
	template<> struct TypeId<xx::String> { static const uint16_t value = 1; };
	template<> struct TypeId<xx::BBuffer> { static const uint16_t value = 2; };
	template<> struct TypeId<PKG::Client_Server1::Join> { static const uint16_t value = 3; };
	template<> struct TypeId<PKG::Client_Server1::Logout> { static const uint16_t value = 4; };
	template<> struct TypeId<PKG::Server1_Client::JoinSuccess> { static const uint16_t value = 5; };
	template<> struct TypeId<PKG::Server1_Client::PushMessage> { static const uint16_t value = 6; };
}
namespace PKG
{
	inline void AllTypesRegister()
	{
	    xx::MemPool::Register<xx::String, xx::Object>();
	    xx::MemPool::Register<xx::BBuffer, xx::Object>();
	    xx::MemPool::Register<PKG::Client_Server1::Join, xx::Object>();
	    xx::MemPool::Register<PKG::Client_Server1::Logout, xx::Object>();
	    xx::MemPool::Register<PKG::Server1_Client::JoinSuccess, xx::Object>();
	    xx::MemPool::Register<PKG::Server1_Client::PushMessage, xx::Object>();
	}
}

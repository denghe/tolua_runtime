#include <xx_mempool.h>
#include <xx_bbuffer.h>

namespace PKG
{
    // 玩家
    struct Player;
    using Player_p = xx::Ptr<Player>;
    using Player_v = xx::Dock<Player>;

    // 鱼
    struct Fish;
    using Fish_p = xx::Ptr<Fish>;
    using Fish_v = xx::Dock<Fish>;

    // 子弹
    struct Bullet;
    using Bullet_p = xx::Ptr<Bullet>;
    using Bullet_v = xx::Dock<Bullet>;

    // 开奖 / 命中 / 杀死
    struct Draw;
    using Draw_p = xx::Ptr<Draw>;
    using Draw_v = xx::Dock<Draw>;

namespace Client_Server1
{
    // 登录
    struct Join;
    using Join_p = xx::Ptr<Join>;
    using Join_v = xx::Dock<Join>;

    // 发射 / 付款
    struct Fire;
    using Fire_p = xx::Ptr<Fire>;
    using Fire_v = xx::Dock<Fire>;

    // 命中检测 / 抽奖
    struct Hit;
    using Hit_p = xx::Ptr<Hit>;
    using Hit_v = xx::Dock<Hit>;

}
namespace Server1_Client
{
    // 加入成功
    struct JoinSuccess;
    using JoinSuccess_p = xx::Ptr<JoinSuccess>;
    using JoinSuccess_v = xx::Dock<JoinSuccess>;

    // 加入失败
    struct JoinFail;
    using JoinFail_p = xx::Ptr<JoinFail>;
    using JoinFail_v = xx::Dock<JoinFail>;

    // 广播成功加入的玩家
    struct PushJoin;
    using PushJoin_p = xx::Ptr<PushJoin>;
    using PushJoin_v = xx::Dock<PushJoin>;

    // 广播离开房间的玩家
    struct PushLeave;
    using PushLeave_p = xx::Ptr<PushLeave>;
    using PushLeave_v = xx::Dock<PushLeave>;

    // 鱼流数据推送
    struct PushFish;
    using PushFish_p = xx::Ptr<PushFish>;
    using PushFish_v = xx::Dock<PushFish>;

    // 子弹数据广播
    struct PushFire;
    using PushFire_p = xx::Ptr<PushFire>;
    using PushFire_v = xx::Dock<PushFire>;

    // 中奖数据推送
    struct PushDraw;
    using PushDraw_p = xx::Ptr<PushDraw>;
    using PushDraw_v = xx::Dock<PushDraw>;

}
    // 玩家
    struct Player : xx::Object
    {
        // 玩家id
        int32_t playerId = 0;
        // 当前金币数
        int64_t coin = 0;
        // 玩家座次
        int32_t pos = 0;

        typedef Player ThisType;
        typedef xx::Object BaseType;
	    Player();
	    Player(xx::BBuffer *bb);
		Player(Player const&) = delete;
		Player& operator=(Player const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
    // 鱼
    struct Fish : xx::Object
    {
        int32_t id = 0;
        int32_t typeId = 0;
        int32_t ticks = 0;
        float x = 0;
        float y = 0;

        typedef Fish ThisType;
        typedef xx::Object BaseType;
	    Fish();
	    Fish(xx::BBuffer *bb);
		Fish(Fish const&) = delete;
		Fish& operator=(Fish const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
    // 子弹
    struct Bullet : xx::Object
    {
        // 玩家id
        int32_t playerId = 0;
        // 自增流水号
        int32_t serial = 0;
        // 时间戳
        int32_t ticks = 0;
        // 武器类型id( 根据配置来, 决定了类型和倍率啥的 )
        int32_t typeId = 0;
        // 矢量 / 坐标
        float vecX = 0;
        // 矢量 / 坐标
        float vecY = 0;

        typedef Bullet ThisType;
        typedef xx::Object BaseType;
	    Bullet();
	    Bullet(xx::BBuffer *bb);
		Bullet(Bullet const&) = delete;
		Bullet& operator=(Bullet const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
    // 开奖 / 命中 / 杀死
    struct Draw : xx::Object
    {
        // 玩家id
        int32_t playerId = 0;
        // 子弹 自增流水号
        int32_t serial = 0;
        // 杀死了哪些鱼的 id
        xx::List_p<int32_t> killFishIds;
        // 打中了哪些鱼 id
        xx::List_p<int32_t> hitFishIds;

        typedef Draw ThisType;
        typedef xx::Object BaseType;
	    Draw();
	    Draw(xx::BBuffer *bb);
		Draw(Draw const&) = delete;
		Draw& operator=(Draw const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
namespace Client_Server1
{
    // 登录
    struct Join : xx::Object
    {
        // 告诉服务器自己是谁
        int32_t id = 0;

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
    // 发射 / 付款
    struct Fire : xx::Object
    {
        // 有可能瞬间发出不止一发子弹, 故 List
        xx::List_p<PKG::Bullet_p> bullets;

        typedef Fire ThisType;
        typedef xx::Object BaseType;
	    Fire();
	    Fire(xx::BBuffer *bb);
		Fire(Fire const&) = delete;
		Fire& operator=(Fire const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
    // 命中检测 / 抽奖
    struct Hit : xx::Object
    {
        // 子弹流水号
        int32_t serial = 0;
        // 客户端自认为打中了哪些鱼的 id
        xx::List_p<int32_t> fishIds;

        typedef Hit ThisType;
        typedef xx::Object BaseType;
	    Hit();
	    Hit(xx::BBuffer *bb);
		Hit(Hit const&) = delete;
		Hit& operator=(Hit const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
}
namespace Server1_Client
{
    // 加入成功
    struct JoinSuccess : xx::Object
    {
        // 房间内所有玩家
        xx::List_p<PKG::Player_p> players;
        // 当前玩家id
        int32_t selfId = 0;
        // 同步显示当前房间里所有活着的鱼的情况
        xx::List_p<PKG::Fish_p> fishs;
        // 同步帧编号
        int32_t ticks = 0;

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
    // 加入失败
    struct JoinFail : xx::Object
    {
        xx::String_p errMsg;

        typedef JoinFail ThisType;
        typedef xx::Object BaseType;
	    JoinFail();
	    JoinFail(xx::BBuffer *bb);
		JoinFail(JoinFail const&) = delete;
		JoinFail& operator=(JoinFail const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
    // 广播成功加入的玩家
    struct PushJoin : xx::Object
    {
        xx::List_p<PKG::Player_p> players;

        typedef PushJoin ThisType;
        typedef xx::Object BaseType;
	    PushJoin();
	    PushJoin(xx::BBuffer *bb);
		PushJoin(PushJoin const&) = delete;
		PushJoin& operator=(PushJoin const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
    // 广播离开房间的玩家
    struct PushLeave : xx::Object
    {
        xx::List_p<int32_t> playerIds;

        typedef PushLeave ThisType;
        typedef xx::Object BaseType;
	    PushLeave();
	    PushLeave(xx::BBuffer *bb);
		PushLeave(PushLeave const&) = delete;
		PushLeave& operator=(PushLeave const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
    // 鱼流数据推送
    struct PushFish : xx::Object
    {
        xx::List_p<PKG::Fish_p> fishs;

        typedef PushFish ThisType;
        typedef xx::Object BaseType;
	    PushFish();
	    PushFish(xx::BBuffer *bb);
		PushFish(PushFish const&) = delete;
		PushFish& operator=(PushFish const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
    // 子弹数据广播
    struct PushFire : xx::Object
    {
        xx::List_p<PKG::Bullet_p> bullets;

        typedef PushFire ThisType;
        typedef xx::Object BaseType;
	    PushFire();
	    PushFire(xx::BBuffer *bb);
		PushFire(PushFire const&) = delete;
		PushFire& operator=(PushFire const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
    // 中奖数据推送
    struct PushDraw : xx::Object
    {
        xx::List_p<PKG::Draw_p> draws;

        typedef PushDraw ThisType;
        typedef xx::Object BaseType;
	    PushDraw();
	    PushDraw(xx::BBuffer *bb);
		PushDraw(PushDraw const&) = delete;
		PushDraw& operator=(PushDraw const&) = delete;
        virtual void ToString(xx::String &str) const override;
        virtual void ToStringCore(xx::String &str) const override;
        virtual void ToBBuffer(xx::BBuffer &bb) const override;
        virtual int FromBBuffer(xx::BBuffer &bb) override;
    };
}
	inline Player::Player()
	{
	}
	inline Player::Player(xx::BBuffer *bb)
	{
	    int rtv = 0;
        if (rtv = bb->Read(playerId)) throw rtv;
        if (rtv = bb->Read(coin)) throw rtv;
        if (rtv = bb->Read(pos)) throw rtv;
	}
    inline void Player::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->playerId);
        bb.Write(this->coin);
        bb.Write(this->pos);
    }
    inline int Player::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        if (rtv = bb.Read(this->playerId)) return rtv;
        if (rtv = bb.Read(this->coin)) return rtv;
        if (rtv = bb.Read(this->pos)) return rtv;
        return rtv;
    }

    inline void Player::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"Player\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void Player::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"playerId\" : ", this->playerId);
        str.Append(", \"coin\" : ", this->coin);
        str.Append(", \"pos\" : ", this->pos);
    }


	inline Fish::Fish()
	{
	}
	inline Fish::Fish(xx::BBuffer *bb)
	{
	    int rtv = 0;
        if (rtv = bb->Read(id)) throw rtv;
        if (rtv = bb->Read(typeId)) throw rtv;
        if (rtv = bb->Read(ticks)) throw rtv;
        if (rtv = bb->Read(x)) throw rtv;
        if (rtv = bb->Read(y)) throw rtv;
	}
    inline void Fish::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->id);
        bb.Write(this->typeId);
        bb.Write(this->ticks);
        bb.Write(this->x);
        bb.Write(this->y);
    }
    inline int Fish::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        if (rtv = bb.Read(this->id)) return rtv;
        if (rtv = bb.Read(this->typeId)) return rtv;
        if (rtv = bb.Read(this->ticks)) return rtv;
        if (rtv = bb.Read(this->x)) return rtv;
        if (rtv = bb.Read(this->y)) return rtv;
        return rtv;
    }

    inline void Fish::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"Fish\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void Fish::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"id\" : ", this->id);
        str.Append(", \"typeId\" : ", this->typeId);
        str.Append(", \"ticks\" : ", this->ticks);
        str.Append(", \"x\" : ", this->x);
        str.Append(", \"y\" : ", this->y);
    }


	inline Bullet::Bullet()
	{
	}
	inline Bullet::Bullet(xx::BBuffer *bb)
	{
	    int rtv = 0;
        if (rtv = bb->Read(playerId)) throw rtv;
        if (rtv = bb->Read(serial)) throw rtv;
        if (rtv = bb->Read(ticks)) throw rtv;
        if (rtv = bb->Read(typeId)) throw rtv;
        if (rtv = bb->Read(vecX)) throw rtv;
        if (rtv = bb->Read(vecY)) throw rtv;
	}
    inline void Bullet::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->playerId);
        bb.Write(this->serial);
        bb.Write(this->ticks);
        bb.Write(this->typeId);
        bb.Write(this->vecX);
        bb.Write(this->vecY);
    }
    inline int Bullet::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        if (rtv = bb.Read(this->playerId)) return rtv;
        if (rtv = bb.Read(this->serial)) return rtv;
        if (rtv = bb.Read(this->ticks)) return rtv;
        if (rtv = bb.Read(this->typeId)) return rtv;
        if (rtv = bb.Read(this->vecX)) return rtv;
        if (rtv = bb.Read(this->vecY)) return rtv;
        return rtv;
    }

    inline void Bullet::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"Bullet\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void Bullet::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"playerId\" : ", this->playerId);
        str.Append(", \"serial\" : ", this->serial);
        str.Append(", \"ticks\" : ", this->ticks);
        str.Append(", \"typeId\" : ", this->typeId);
        str.Append(", \"vecX\" : ", this->vecX);
        str.Append(", \"vecY\" : ", this->vecY);
    }


	inline Draw::Draw()
	{
	}
	inline Draw::Draw(xx::BBuffer *bb)
	{
	    int rtv = 0;
        if (rtv = bb->Read(playerId)) throw rtv;
        if (rtv = bb->Read(serial)) throw rtv;
        bb->readLengthLimit = 0;
        if (rtv = bb->Read(killFishIds)) throw rtv;
        bb->readLengthLimit = 0;
        if (rtv = bb->Read(hitFishIds)) throw rtv;
	}
    inline void Draw::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->playerId);
        bb.Write(this->serial);
        bb.Write(this->killFishIds);
        bb.Write(this->hitFishIds);
    }
    inline int Draw::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        if (rtv = bb.Read(this->playerId)) return rtv;
        if (rtv = bb.Read(this->serial)) return rtv;
        bb.readLengthLimit = 0;
        if (rtv = bb.Read(this->killFishIds)) return rtv;
        bb.readLengthLimit = 0;
        if (rtv = bb.Read(this->hitFishIds)) return rtv;
        return rtv;
    }

    inline void Draw::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"Draw\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void Draw::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"playerId\" : ", this->playerId);
        str.Append(", \"serial\" : ", this->serial);
        str.Append(", \"killFishIds\" : ", this->killFishIds);
        str.Append(", \"hitFishIds\" : ", this->hitFishIds);
    }


namespace Client_Server1
{
	inline Join::Join()
	{
	}
	inline Join::Join(xx::BBuffer *bb)
	{
	    int rtv = 0;
        if (rtv = bb->Read(id)) throw rtv;
	}
    inline void Join::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->id);
    }
    inline int Join::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        if (rtv = bb.Read(this->id)) return rtv;
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
        str.Append(", \"id\" : ", this->id);
    }


	inline Fire::Fire()
	{
	}
	inline Fire::Fire(xx::BBuffer *bb)
	{
	    int rtv = 0;
        bb->readLengthLimit = 10;
        if (rtv = bb->Read(bullets)) throw rtv;
	}
    inline void Fire::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->bullets);
    }
    inline int Fire::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        bb.readLengthLimit = 10;
        if (rtv = bb.Read(this->bullets)) return rtv;
        return rtv;
    }

    inline void Fire::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"Fire\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void Fire::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"bullets\" : ", this->bullets);
    }


	inline Hit::Hit()
	{
	}
	inline Hit::Hit(xx::BBuffer *bb)
	{
	    int rtv = 0;
        if (rtv = bb->Read(serial)) throw rtv;
        bb->readLengthLimit = 30;
        if (rtv = bb->Read(fishIds)) throw rtv;
	}
    inline void Hit::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->serial);
        bb.Write(this->fishIds);
    }
    inline int Hit::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        if (rtv = bb.Read(this->serial)) return rtv;
        bb.readLengthLimit = 30;
        if (rtv = bb.Read(this->fishIds)) return rtv;
        return rtv;
    }

    inline void Hit::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"Hit\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void Hit::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"serial\" : ", this->serial);
        str.Append(", \"fishIds\" : ", this->fishIds);
    }


}
namespace Server1_Client
{
	inline JoinSuccess::JoinSuccess()
	{
	}
	inline JoinSuccess::JoinSuccess(xx::BBuffer *bb)
	{
	    int rtv = 0;
        bb->readLengthLimit = 0;
        if (rtv = bb->Read(players)) throw rtv;
        if (rtv = bb->Read(selfId)) throw rtv;
        bb->readLengthLimit = 0;
        if (rtv = bb->Read(fishs)) throw rtv;
        if (rtv = bb->Read(ticks)) throw rtv;
	}
    inline void JoinSuccess::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->players);
        bb.Write(this->selfId);
        bb.Write(this->fishs);
        bb.Write(this->ticks);
    }
    inline int JoinSuccess::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        bb.readLengthLimit = 0;
        if (rtv = bb.Read(this->players)) return rtv;
        if (rtv = bb.Read(this->selfId)) return rtv;
        bb.readLengthLimit = 0;
        if (rtv = bb.Read(this->fishs)) return rtv;
        if (rtv = bb.Read(this->ticks)) return rtv;
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
        str.Append(", \"players\" : ", this->players);
        str.Append(", \"selfId\" : ", this->selfId);
        str.Append(", \"fishs\" : ", this->fishs);
        str.Append(", \"ticks\" : ", this->ticks);
    }


	inline JoinFail::JoinFail()
	{
	}
	inline JoinFail::JoinFail(xx::BBuffer *bb)
	{
	    int rtv = 0;
        bb->readLengthLimit = 0;
        if (rtv = bb->Read(errMsg)) throw rtv;
	}
    inline void JoinFail::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->errMsg);
    }
    inline int JoinFail::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        bb.readLengthLimit = 0;
        if (rtv = bb.Read(this->errMsg)) return rtv;
        return rtv;
    }

    inline void JoinFail::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"JoinFail\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void JoinFail::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"errMsg\" : ", this->errMsg);
    }


	inline PushJoin::PushJoin()
	{
	}
	inline PushJoin::PushJoin(xx::BBuffer *bb)
	{
	    int rtv = 0;
        bb->readLengthLimit = 0;
        if (rtv = bb->Read(players)) throw rtv;
	}
    inline void PushJoin::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->players);
    }
    inline int PushJoin::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        bb.readLengthLimit = 0;
        if (rtv = bb.Read(this->players)) return rtv;
        return rtv;
    }

    inline void PushJoin::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"PushJoin\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void PushJoin::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"players\" : ", this->players);
    }


	inline PushLeave::PushLeave()
	{
	}
	inline PushLeave::PushLeave(xx::BBuffer *bb)
	{
	    int rtv = 0;
        bb->readLengthLimit = 0;
        if (rtv = bb->Read(playerIds)) throw rtv;
	}
    inline void PushLeave::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->playerIds);
    }
    inline int PushLeave::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        bb.readLengthLimit = 0;
        if (rtv = bb.Read(this->playerIds)) return rtv;
        return rtv;
    }

    inline void PushLeave::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"PushLeave\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void PushLeave::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"playerIds\" : ", this->playerIds);
    }


	inline PushFish::PushFish()
	{
	}
	inline PushFish::PushFish(xx::BBuffer *bb)
	{
	    int rtv = 0;
        bb->readLengthLimit = 0;
        if (rtv = bb->Read(fishs)) throw rtv;
	}
    inline void PushFish::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->fishs);
    }
    inline int PushFish::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        bb.readLengthLimit = 0;
        if (rtv = bb.Read(this->fishs)) return rtv;
        return rtv;
    }

    inline void PushFish::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"PushFish\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void PushFish::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"fishs\" : ", this->fishs);
    }


	inline PushFire::PushFire()
	{
	}
	inline PushFire::PushFire(xx::BBuffer *bb)
	{
	    int rtv = 0;
        bb->readLengthLimit = 0;
        if (rtv = bb->Read(bullets)) throw rtv;
	}
    inline void PushFire::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->bullets);
    }
    inline int PushFire::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        bb.readLengthLimit = 0;
        if (rtv = bb.Read(this->bullets)) return rtv;
        return rtv;
    }

    inline void PushFire::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"PushFire\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void PushFire::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"bullets\" : ", this->bullets);
    }


	inline PushDraw::PushDraw()
	{
	}
	inline PushDraw::PushDraw(xx::BBuffer *bb)
	{
	    int rtv = 0;
        bb->readLengthLimit = 0;
        if (rtv = bb->Read(draws)) throw rtv;
	}
    inline void PushDraw::ToBBuffer(xx::BBuffer &bb) const
    {
        bb.Write(this->draws);
    }
    inline int PushDraw::FromBBuffer(xx::BBuffer &bb)
    {
        int rtv = 0;
        bb.readLengthLimit = 0;
        if (rtv = bb.Read(this->draws)) return rtv;
        return rtv;
    }

    inline void PushDraw::ToString(xx::String &str) const
    {
        if (tsFlags())
        {
        	str.Append("[ \"***** recursived *****\" ]");
        	return;
        }
        else tsFlags() = 1;

        str.Append("{ \"type\" : \"PushDraw\"");
        ToStringCore(str);
        str.Append(" }");
        
        tsFlags() = 0;
    }
    inline void PushDraw::ToStringCore(xx::String &str) const
    {
        this->BaseType::ToStringCore(str);
        str.Append(", \"draws\" : ", this->draws);
    }


}
}
namespace xx
{
	template<> struct TypeId<xx::String> { static const uint16_t value = 1; };
	template<> struct TypeId<xx::BBuffer> { static const uint16_t value = 2; };
	template<> struct TypeId<PKG::Player> { static const uint16_t value = 5; };
	template<> struct TypeId<PKG::Fish> { static const uint16_t value = 6; };
	template<> struct TypeId<PKG::Bullet> { static const uint16_t value = 7; };
	template<> struct TypeId<PKG::Draw> { static const uint16_t value = 8; };
	template<> struct TypeId<xx::List<int32_t>> { static const uint16_t value = 9; };
	template<> struct TypeId<PKG::Client_Server1::Join> { static const uint16_t value = 3; };
	template<> struct TypeId<PKG::Client_Server1::Fire> { static const uint16_t value = 10; };
	template<> struct TypeId<xx::List<PKG::Bullet_p>> { static const uint16_t value = 11; };
	template<> struct TypeId<PKG::Client_Server1::Hit> { static const uint16_t value = 12; };
	template<> struct TypeId<PKG::Server1_Client::JoinSuccess> { static const uint16_t value = 4; };
	template<> struct TypeId<xx::List<PKG::Player_p>> { static const uint16_t value = 15; };
	template<> struct TypeId<xx::List<PKG::Fish_p>> { static const uint16_t value = 18; };
	template<> struct TypeId<PKG::Server1_Client::JoinFail> { static const uint16_t value = 13; };
	template<> struct TypeId<PKG::Server1_Client::PushJoin> { static const uint16_t value = 14; };
	template<> struct TypeId<PKG::Server1_Client::PushLeave> { static const uint16_t value = 16; };
	template<> struct TypeId<PKG::Server1_Client::PushFish> { static const uint16_t value = 17; };
	template<> struct TypeId<PKG::Server1_Client::PushFire> { static const uint16_t value = 19; };
	template<> struct TypeId<PKG::Server1_Client::PushDraw> { static const uint16_t value = 20; };
	template<> struct TypeId<xx::List<PKG::Draw_p>> { static const uint16_t value = 21; };
}
namespace PKG
{
	inline void AllTypesRegister()
	{
	    xx::MemPool::Register<xx::String, xx::Object>();
	    xx::MemPool::Register<xx::BBuffer, xx::Object>();
	    xx::MemPool::Register<PKG::Player, xx::Object>();
	    xx::MemPool::Register<PKG::Fish, xx::Object>();
	    xx::MemPool::Register<PKG::Bullet, xx::Object>();
	    xx::MemPool::Register<PKG::Draw, xx::Object>();
	    xx::MemPool::Register<xx::List<int32_t>, xx::Object>();
	    xx::MemPool::Register<PKG::Client_Server1::Join, xx::Object>();
	    xx::MemPool::Register<PKG::Client_Server1::Fire, xx::Object>();
	    xx::MemPool::Register<xx::List<PKG::Bullet_p>, xx::Object>();
	    xx::MemPool::Register<PKG::Client_Server1::Hit, xx::Object>();
	    xx::MemPool::Register<PKG::Server1_Client::JoinSuccess, xx::Object>();
	    xx::MemPool::Register<xx::List<PKG::Player_p>, xx::Object>();
	    xx::MemPool::Register<xx::List<PKG::Fish_p>, xx::Object>();
	    xx::MemPool::Register<PKG::Server1_Client::JoinFail, xx::Object>();
	    xx::MemPool::Register<PKG::Server1_Client::PushJoin, xx::Object>();
	    xx::MemPool::Register<PKG::Server1_Client::PushLeave, xx::Object>();
	    xx::MemPool::Register<PKG::Server1_Client::PushFish, xx::Object>();
	    xx::MemPool::Register<PKG::Server1_Client::PushFire, xx::Object>();
	    xx::MemPool::Register<PKG::Server1_Client::PushDraw, xx::Object>();
	    xx::MemPool::Register<xx::List<PKG::Draw_p>, xx::Object>();
	}
}

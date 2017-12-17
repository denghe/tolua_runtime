using System;
using xx;
namespace PKG
{
    public static class PkgGenMd5
    {
        public const string value = "9766b30df473b079550fddde58d66800"; 
    }

    /// <summary>
    /// 玩家
    /// </summary>
    public partial class Player : IBBuffer
    {
        /// <summary>
        /// 玩家id
        /// </summary>
        public int playerId;
        /// <summary>
        /// 当前金币数
        /// </summary>
        public long coin;
        /// <summary>
        /// 玩家座次
        /// </summary>
        public int pos;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<Player>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.playerId);
            bb.Write(this.coin);
            bb.Write(this.pos);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.Read(ref this.playerId);
            bb.Read(ref this.coin);
            bb.Read(ref this.pos);
        }

    }
    /// <summary>
    /// 鱼
    /// </summary>
    public partial class Fish : IBBuffer
    {
        public int id;
        public int typeId;
        public int ticks;
        public float x;
        public float y;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<Fish>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.id);
            bb.Write(this.typeId);
            bb.Write(this.ticks);
            bb.Write(this.x);
            bb.Write(this.y);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.Read(ref this.id);
            bb.Read(ref this.typeId);
            bb.Read(ref this.ticks);
            bb.Read(ref this.x);
            bb.Read(ref this.y);
        }

    }
    /// <summary>
    /// 子弹
    /// </summary>
    public partial class Bullet : IBBuffer
    {
        /// <summary>
        /// 玩家id
        /// </summary>
        public int playerId;
        /// <summary>
        /// 自增流水号
        /// </summary>
        public int serial;
        /// <summary>
        /// 时间戳
        /// </summary>
        public int ticks;
        /// <summary>
        /// 武器类型id( 根据配置来, 决定了类型和倍率啥的 )
        /// </summary>
        public int typeId;
        /// <summary>
        /// 矢量 / 坐标
        /// </summary>
        public float vecX;
        /// <summary>
        /// 矢量 / 坐标
        /// </summary>
        public float vecY;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<Bullet>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.playerId);
            bb.Write(this.serial);
            bb.Write(this.ticks);
            bb.Write(this.typeId);
            bb.Write(this.vecX);
            bb.Write(this.vecY);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.Read(ref this.playerId);
            bb.Read(ref this.serial);
            bb.Read(ref this.ticks);
            bb.Read(ref this.typeId);
            bb.Read(ref this.vecX);
            bb.Read(ref this.vecY);
        }

    }
    /// <summary>
    /// 开奖 / 命中 / 杀死
    /// </summary>
    public partial class Draw : IBBuffer
    {
        /// <summary>
        /// 玩家id
        /// </summary>
        public int playerId;
        /// <summary>
        /// 子弹 自增流水号
        /// </summary>
        public int serial;
        /// <summary>
        /// 杀死了哪些鱼的 id
        /// </summary>
        public List<int> killFishIds;
        /// <summary>
        /// 打中了哪些鱼 id
        /// </summary>
        public List<int> hitFishIds;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<Draw>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.playerId);
            bb.Write(this.serial);
            bb.Write(this.killFishIds);
            bb.Write(this.hitFishIds);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.Read(ref this.playerId);
            bb.Read(ref this.serial);
            bb.readLengthLimit = 0;
            bb.Read(ref this.killFishIds);
            bb.readLengthLimit = 0;
            bb.Read(ref this.hitFishIds);
        }

    }
namespace Client_Server1
{
    /// <summary>
    /// 登录
    /// </summary>
    public partial class Join : IBBuffer
    {
        /// <summary>
        /// 告诉服务器自己是谁
        /// </summary>
        public int id;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<Join>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.id);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.Read(ref this.id);
        }

    }
    /// <summary>
    /// 发射 / 付款
    /// </summary>
    public partial class Fire : IBBuffer
    {
        /// <summary>
        /// 有可能瞬间发出不止一发子弹, 故 List
        /// </summary>
        public List<Bullet> bullets;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<Fire>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.bullets);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.readLengthLimit = 10;
            bb.Read(ref this.bullets);
        }

    }
    /// <summary>
    /// 命中检测 / 抽奖
    /// </summary>
    public partial class Hit : IBBuffer
    {
        /// <summary>
        /// 子弹流水号
        /// </summary>
        public int serial;
        /// <summary>
        /// 客户端自认为打中了哪些鱼的 id
        /// </summary>
        public List<int> fishIds;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<Hit>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.serial);
            bb.Write(this.fishIds);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.Read(ref this.serial);
            bb.readLengthLimit = 30;
            bb.Read(ref this.fishIds);
        }

    }
}
namespace Server1_Client
{
    /// <summary>
    /// 加入成功
    /// </summary>
    public partial class JoinSuccess : IBBuffer
    {
        /// <summary>
        /// 房间内所有玩家
        /// </summary>
        public List<Player> players;
        /// <summary>
        /// 当前玩家id
        /// </summary>
        public int selfId;
        /// <summary>
        /// 同步显示当前房间里所有活着的鱼的情况
        /// </summary>
        public List<Fish> fishs;
        /// <summary>
        /// 同步帧编号
        /// </summary>
        public int ticks;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<JoinSuccess>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.players);
            bb.Write(this.selfId);
            bb.Write(this.fishs);
            bb.Write(this.ticks);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.readLengthLimit = 0;
            bb.Read(ref this.players);
            bb.Read(ref this.selfId);
            bb.readLengthLimit = 0;
            bb.Read(ref this.fishs);
            bb.Read(ref this.ticks);
        }

    }
    /// <summary>
    /// 加入失败
    /// </summary>
    public partial class JoinFail : IBBuffer
    {
        public string errMsg;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<JoinFail>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.errMsg);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.readLengthLimit = 0;
            bb.Read(ref this.errMsg);
        }

    }
    /// <summary>
    /// 广播成功加入的玩家
    /// </summary>
    public partial class PushJoin : IBBuffer
    {
        public List<Player> players;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<PushJoin>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.players);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.readLengthLimit = 0;
            bb.Read(ref this.players);
        }

    }
    /// <summary>
    /// 广播离开房间的玩家
    /// </summary>
    public partial class PushLeave : IBBuffer
    {
        public List<int> playerIds;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<PushLeave>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.playerIds);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.readLengthLimit = 0;
            bb.Read(ref this.playerIds);
        }

    }
    /// <summary>
    /// 鱼流数据推送
    /// </summary>
    public partial class PushFish : IBBuffer
    {
        public List<Fish> fishs;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<PushFish>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.fishs);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.readLengthLimit = 0;
            bb.Read(ref this.fishs);
        }

    }
    /// <summary>
    /// 子弹数据广播
    /// </summary>
    public partial class PushFire : IBBuffer
    {
        public List<Bullet> bullets;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<PushFire>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.bullets);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.readLengthLimit = 0;
            bb.Read(ref this.bullets);
        }

    }
    /// <summary>
    /// 中奖数据推送
    /// </summary>
    public partial class PushDraw : IBBuffer
    {
        public List<Draw> draws;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<PushDraw>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.draws);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.readLengthLimit = 0;
            bb.Read(ref this.draws);
        }

    }
}
    public static class AllTypes
    {
        public static void Register()
        {
            // BBuffer.Register<string>(1);
            BBuffer.Register<BBuffer>(2);
            BBuffer.Register<Player>(5);
            BBuffer.Register<Fish>(6);
            BBuffer.Register<Bullet>(7);
            BBuffer.Register<Draw>(8);
            BBuffer.Register<List<int>>(9);
            BBuffer.Register<Client_Server1.Join>(3);
            BBuffer.Register<Client_Server1.Fire>(10);
            BBuffer.Register<List<Bullet>>(11);
            BBuffer.Register<Client_Server1.Hit>(12);
            BBuffer.Register<Server1_Client.JoinSuccess>(4);
            BBuffer.Register<List<Player>>(15);
            BBuffer.Register<List<Fish>>(18);
            BBuffer.Register<Server1_Client.JoinFail>(13);
            BBuffer.Register<Server1_Client.PushJoin>(14);
            BBuffer.Register<Server1_Client.PushLeave>(16);
            BBuffer.Register<Server1_Client.PushFish>(17);
            BBuffer.Register<Server1_Client.PushFire>(19);
            BBuffer.Register<Server1_Client.PushDraw>(20);
            BBuffer.Register<List<Draw>>(21);
        }
    }
}

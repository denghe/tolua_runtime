#pragma warning disable 0169, 0414
using TemplateLibrary;

// Server1 向 Client 发的包
namespace Server1_Client
{
    [Desc("加入成功")]
    class JoinSuccess
    {
        [Desc("房间内所有玩家")]
        List<Player> players;

        [Desc("当前玩家id")]
        int selfId;

        [Desc("同步显示当前房间里所有活着的鱼的情况")]
        List<Fish> fishs;

        [Desc("同步帧编号")]
        int ticks;

        // 如果要同步子弹就是做帧同步游戏的做法了. 当前不考虑
        //List<Bullet> bullets;
    }

    [Desc("加入失败")]
    class JoinFail
    {
        string errMsg;
    }

    [Desc("广播成功加入的玩家")]
    class PushJoin
    {
        List<Player> players;
    }

    [Desc("广播离开房间的玩家")]
    class PushLeave
    {
        List<int> playerIds;
    }

    [Desc("鱼流数据推送")]
    class PushFish
    {
        List<Fish> fishs;
    }

    [Desc("子弹数据广播")]
    class PushFire
    {
        List<Bullet> bullets;
    }

    [Desc("中奖数据推送")]
    class PushDraw
    {
        List<Draw> draws;
    }
}

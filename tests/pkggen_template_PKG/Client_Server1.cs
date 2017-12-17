#pragma warning disable 0169, 0414
using TemplateLibrary;

// Client 向 Server1 发的包
namespace Client_Server1
{
    [Desc("登录")]
    class Join
    {
        [Desc("告诉服务器自己是谁")]
        int id;
    }

    [Desc("发射 / 付款")]
    class Fire
    {
        [Desc("有可能瞬间发出不止一发子弹, 故 List"), Limit(10)]
        List<Bullet> bullets;
    }

    [Desc("命中检测 / 抽奖")]
    class Hit
    {
        [Desc("子弹流水号")]
        int serial;

        [Desc("客户端自认为打中了哪些鱼的 id"), Limit(30)]
        List<int> fishIds;
    }
}

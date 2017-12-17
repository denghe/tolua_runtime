#pragma warning disable 0169, 0414
using TemplateLibrary;

[Desc("玩家")]
class Player
{
    [Desc("玩家id")]
    int playerId;

    [Desc("当前金币数")]
    long coin;

    [Desc("玩家座次")]
    int pos;
}

[Desc("鱼")]
class Fish
{
    int id;
    int typeId;
    int ticks;
    float x, y;
}

[Desc("子弹")]
class Bullet
{
    [Desc("玩家id")]
    int playerId;

    [Desc("自增流水号")]
    int serial;

    [Desc("时间戳")]
    int ticks;

    [Desc("武器类型id( 根据配置来, 决定了类型和倍率啥的 )")]
    int typeId;

    [Desc("矢量 / 坐标")]
    float vecX, vecY;
}

[Desc("开奖 / 命中 / 杀死")]
class Draw
{
    [Desc("玩家id")]
    int playerId;

    [Desc("子弹 自增流水号")]
    int serial;

    [Desc("杀死了哪些鱼的 id")]
    List<int> killFishIds;

    [Desc("打中了哪些鱼 id")]
    List<int> hitFishIds;
}

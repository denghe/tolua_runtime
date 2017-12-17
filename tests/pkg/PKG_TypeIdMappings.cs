#pragma warning disable 0169, 0414
using TemplateLibrary;

[TypeIdMappings]
interface ITypeIdMappings
{
    Player _5 { get; }

    Fish _6 { get; }

    Bullet _7 { get; }

    Draw _8 { get; }

    List<int> _9 { get; }

    Client_Server1.Join _3 { get; }

    Client_Server1.Fire _10 { get; }

    List<Bullet> _11 { get; }

    Client_Server1.Hit _12 { get; }

    Server1_Client.JoinSuccess _4 { get; }

    Server1_Client.JoinFail _13 { get; }

    Server1_Client.PushJoin _14 { get; }

    List<Player> _15 { get; }

    Server1_Client.PushLeave _16 { get; }

    Server1_Client.PushFish _17 { get; }

    List<Fish> _18 { get; }

    Server1_Client.PushFire _19 { get; }

    Server1_Client.PushDraw _20 { get; }

    List<Draw> _21 { get; }

}

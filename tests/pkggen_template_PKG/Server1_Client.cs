#pragma warning disable 0169, 0414
using TemplateLibrary;

// Server 向 Client 发的包
namespace Server1_Client
{
    class JoinSuccess
    {
    }
    class PushMessage
    {
        long id;
        string text;
    }
}

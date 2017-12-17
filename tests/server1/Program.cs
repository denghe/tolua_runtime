using System;
using System.Diagnostics;
using System.Threading;
using System.Threading.Tasks;
using xx;

public static class Program
{
    static void Main(string[] args)
    {
        using (var loop = new UvLoop())
        {
            var listener = new UvTcpListener(loop);
            listener.OnAccept = peer =>
            {
                Console.WriteLine(peer.ip + " accepted");

                peer.OnRecvPkg = bb =>
                {
                    try
                    {
                        var pkgs = bb.ReadPackages();
                        if (pkgs.dataLen != 1)
                        {
                            peer.Dispose();
                            return;
                        }
                        switch (pkgs[0])
                        {
                            case PKG.Client_Server1.Join o:
                                {
                                    if (peer.alive)
                                    {
                                        peer.SendPackages(new PKG.Server1_Client.JoinFail { errMsg = "not impl yet" });
                                    }
                                    break;
                                }
                            case PKG.Client_Server1.Fire o:
                                {


                                    break;
                                }
                            case PKG.Client_Server1.Hit o:
                                {

                                    break;
                                }
                            // todo: more
                            default:
                                peer.Dispose();
                                return;
                        }
                    }
                    catch
                    {
                        peer.Dispose();
                    }
                };

                peer.OnDispose = () =>
                {
                    Console.WriteLine(peer.ip + " disposed");
                };
            };
            listener.Bind("0.0.0.0", 12345);
            listener.Listen();

            Console.WriteLine("listing...");
            loop.Run();
        }
    }
}

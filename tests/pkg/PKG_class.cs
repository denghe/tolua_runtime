using System;
using xx;
namespace PKG
{
    public static class PkgGenMd5
    {
        public const string value = "2dca39d593860684e9ced95fcd01f3d6"; 
    }

namespace Client_Server1
{
    public partial class Join : IBBuffer
    {

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<Join>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
        }

    }
    public partial class Logout : IBBuffer
    {

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<Logout>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
        }

    }
}
namespace Server1_Client
{
    public partial class JoinSuccess : IBBuffer
    {

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<JoinSuccess>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
        }

    }
    public partial class PushMessage : IBBuffer
    {
        public long id;
        public string text;

        public virtual ushort GetPackageId()
        {
            return TypeIdMaps<PushMessage>.typeId;
        }

        public virtual void ToBBuffer(BBuffer bb)
        {
            bb.Write(this.id);
            bb.Write(this.text);
        }

        public virtual void FromBBuffer(BBuffer bb)
        {
            bb.Read(ref this.id);
            bb.readLengthLimit = 0;
            bb.Read(ref this.text);
        }

    }
}
    public static class AllTypes
    {
        public static void Register()
        {
            // BBuffer.Register<string>(1);
            BBuffer.Register<BBuffer>(2);
            BBuffer.Register<Client_Server1.Join>(3);
            BBuffer.Register<Client_Server1.Logout>(4);
            BBuffer.Register<Server1_Client.JoinSuccess>(5);
            BBuffer.Register<Server1_Client.PushMessage>(6);
        }
    }
}

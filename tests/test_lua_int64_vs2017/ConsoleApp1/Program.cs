using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp1
{
    public static class Program
    {
        [DllImport("tolua", CallingConvention = CallingConvention.Cdecl)]
        public static extern void xxlua_openxx(IntPtr luaState);

        static void Main(string[] args)
        {
            xxlua_openxx(IntPtr.Zero);
        }
    }
}

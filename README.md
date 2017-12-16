# tolua_runtime ( fork & patch )
**Prepare**<br>
OS: windows x64 & macos 12.6+ with xcode9.2+<br>
LUAJIT: 最新( 2.1 beta3+ )<br>
NDK: 最新( 16+ )<br>
MSYS2: 最新( x64版 with gcc 7.2 )<br>

msys2 相关: http://msys2.github.io/<br>
根据官网先来一波更新之后, 依次执行安装下面的这些东西: <br>
pacman -S mingw-w64-i686-toolchain<br>
pacman -S mingw-w64-x86_64-toolchain<br>
pacman -S make<br>
最后将 git 项目放入 msys2 的用户目录( 例如 C:\msys64\home\名字\git项目目录 )<br>
下载期间 ss 加速不能, 估计只有 vpn 才可以( 没试过 )... 如果报错, 可反复执行上述脚本, 直至下载完成安装好为止. <br>

NDK 相关: <br>
build_arm.sh, build_x86.sh 这两个文件需要修改其中的第 4 行 NDK 路径指向实际路径.<br>

MAC 相关: <br>
如果 git 项目是从 windows 下面拉取的, 直接复制到 mac 中将导致 .sh 文件中的换行符 bash 不认. 并且编译 luajit 也可能出错. 通常需要直接从 mac 中 git clone 或转一下 CR 换行符.<br>
同时, 还需要执行 chmod 777 *.sh 来修改执行权限.<br>

**Build**<br>

编译 windows 需要的 .dll 和 android 需要的 .so 需要在 windows 下进行, 具体为:<br>

运行 msys2_32bit, 进入项目目录, 依次输入<br>
./build_arm.sh<br>
./build_win32.sh<br>

运行 msys2_64bit, 进入项目目录, 输入<br>
./build_win64.sh<br>

编译 ios:<br>
切到 macos 系统, 打开终端, 进入项目录, 输入<br>
./build_ios.sh<br>

最后别忘了提交 macos 下的 Plugins 的 .a 结果, 同步到 git. <br>

**Tips1**<br>
如果 luajit 需要重新编译( 当前环境为 gcc 7.2, ndk 16 ), 则以相同方式执行 ****luajit.sh, 再进行上述步骤.

**Tips2**<br>
u3d 打包 ios 时, ios 最低版本号填 8,  打包 android 时最低版本号填 14, 且打开 Internet Access 权限( auto 改为 Require )

# Libs
todo: 打算删掉一部分, 得看看 C# 中是否有用到<br>
**cjson**<br>
https://github.com/mpx/lua-cjson<br>
**protoc-gen-lua**<br>
https://github.com/topameng/protoc-gen-lua<br>
**LuaSocket** <br>
https://github.com/diegonehab/luasocket<br>
**struct**<br>
http://www.inf.puc-rio.br/~roberto/struct/<br>
**lpeg**<br>
http://www.inf.puc-rio.br/~roberto/lpeg/lpeg.html

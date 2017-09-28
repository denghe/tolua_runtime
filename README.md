# tolua_runtime ( fork & patch )
<br>
**Prepare**<br>
OS: windows & macos 12.6+ with xcode9+<br>
LUAJIT: 最新( 2.1 beta3+ )<br>
NDK: 最新( 15c+ )<br>
MSYS2: 最新( 运行在32bit )<br>
<br>
msys2 相关: http://msys2.github.io/<br>
根据官网先来一波更新之后, 依次执行安装下面的这些东西: <br>
pacman -S mingw-w64-i686-toolchain<br>
pacman -S mingw-w64-x86_64-toolchain<br>
pacman -S make<br>
最后将 git 项目放入 msys2 的用户目录( 例如 C:\msys64\home\名字\git项目目录 )<br>
下载期间 ss 加速不能, 估计只有 vpn 才可以( 没试过 )... 如果报错, 可反复执行上述脚本, 直至下载完成安装好为止. <br>
<br>
<br>
NDK 相关: <br>
build_arm.sh, build_x86.sh 这两个文件需要修改其中的第 4 行 NDK 路径指向实际路径.<br>
<br>
<br>
坑: <br>
如果 git 项目是从 windows 下面拉取的, 直接复制到 mac 中将导致 .sh 文件中的换行符 bash 不认. 通常需要直接从 mac 中 git clone 或转一下 CR.<br>
<br>
**Build**<br>
编译 windows 需要的 .dll 和 android 需要的 .so 需要在 windows 下进行, 具体为:<br>
运行 msys2_32bit, 进入项目目录, 依次输入<br>
./build_arm.sh<br>
./build_x86.sh<br>
./build_win32.sh<br>
运行 msys2_64bit, 进入项目目录, 输入<br>
./build_win64.sh<br>
<br>
编译 ios / osx:<br>
切到 macos 系统, 打开终端, 进入项目录, 输入<br>
./build_ios.sh<br>
./build_osx.sh<br>
<br>
最后, 将 macos 系统下的 git项目的 Plugins 下的 tolua.bundle, iOS 与 windows 下的 windows & android 生成物合并备用. <br>

# Libs( todo: 打算删掉一部分, 得看看 C# 中是否有用到 )
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

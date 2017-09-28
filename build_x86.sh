cd luajit-2.1/src

# Android/x86, x86 (i686 SSE3), Android 4.0+ (ICS)
NDK=C:/Users/dh/AppData/Local/Android/sdk/ndk-bundle
NDKABI=14
NDKVER=$NDK/toolchains/x86-4.9
NDKP=$NDKVER/prebuilt/windows-x86_64/bin/i686-linux-android-
NDKF="--sysroot $NDK/platforms/android-$NDKABI/arch-x86"
#NDKARCH

make clean
make HOST_CC="gcc -m32" CROSS=$NDKP TARGET_SYS=Linux TARGET_FLAGS="$NDKF"
cp ./libluajit.a ../../android/jni/libluajit.a
make clean

cd ../../android
$NDK/ndk-build.cmd clean APP_ABI="x86"
$NDK/ndk-build.cmd APP_ABI="x86"
cp libs/x86/libtolua.so ../Plugins/Android/libs/x86
$NDK/ndk-build.cmd clean APP_ABI="x86"
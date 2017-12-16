#NDK=C:/Users/用户名/AppData/Local/Android/sdk/ndk-bundle
NDK=E:/Android/sdk/ndk-bundle
cd android
$NDK/ndk-build.cmd clean
$NDK/ndk-build.cmd
cp libs/armeabi-v7a/libtolua.so ../Plugins/Android/libs/armeabi-v7a
$NDK/ndk-build.cmd clean

#!/bin/bash
# 64 Bit Version

gcc -m64 -O2 -std=gnu99 -std=gnu++1z -shared \
 tolua.c \
 int64.c \
 uint64.c \
 pb.c \
 lpeg.c \
 struct.c \
 cjson/strbuf.c \
 cjson/lua_cjson.c \
 cjson/fpconv.c \
 luasocket/auxiliar.c \
 luasocket/buffer.c \
 luasocket/except.c \
 luasocket/inet.c \
 luasocket/io.c \
 luasocket/luasocket.c \
 luasocket/mime.c \
 luasocket/options.c \
 luasocket/select.c \
 luasocket/tcp.c \
 luasocket/timeout.c \
 luasocket/udp.c \
 luasocket/wsocket.c \
 ikcp.cpp \
 lua_xx.cpp \
 ./window/x86_64/libuv.a \
 -o Plugins/x86_64/tolua.dll \
 -I./ \
 -I./libuv/ \
 -I./luajit-2.1/src/ \
 -I./luasocket/ \
 -lws2_32 \
 -lole32 \
 -lpsapi \
 -lIPHLPAPI \
 -luserenv \
 -Wl,--whole-archive window/x86_64/libluajit.a \
 -Wl,--no-whole-archive \
 -static-libgcc -static-libstdc++ -lstdc++
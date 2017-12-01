#!/bin/bash
# 64 Bit Version
mkdir -p window/x86_64

cd luajit-2.1
make clean

make BUILDMODE=static CC="gcc -m64 -O2" XCFLAGS=-DLUAJIT_ENABLE_GC64
cp src/libluajit.a ../window/x86_64/libluajit.a
make clean

cd ..

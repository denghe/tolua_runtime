#!/bin/bash
# 32 Bit Version
mkdir -p window/x86

cd luajit-2.1
make clean

make BUILDMODE=static CC="gcc -m32 -O2"
cp src/libluajit.a ../window/x86/libluajit.a
make clean

cd ..

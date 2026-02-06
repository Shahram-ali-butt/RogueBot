#!/usr/bin/env bash

set -e

mkdir -p build
cd build

cmake ..

if [ -f build.ninja ]; then
    echo "--- Building with Ninja ---"
    ninja
elif [ -f Makefile ]; then
    echo "--- Building with MinGW Makefiles ---"
    mingw32-make
else
    echo "Unknown build system!"
    exit 1
fi

cd ..

./build/RogueBot.exe

#!/usr/bin/env bash
set -e

cmake --build build
cmake --build build --target RogueBot

./build/RogueBot.exe

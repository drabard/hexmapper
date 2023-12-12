#!/usr/bin/env bash
set -e

mkdir -p bin/
clang++ -g3 -O0 -std=c++17 -c \
    -Isrc/hexmapper/include \
    -Isrc/ext/raylib \
    -Isrc/ext/imgui \
    -Isrc/ext/rlImGui \
    src/hexmapper/src/unity.cpp \
    -o bin/hexmapper.o
clang++ \
    bin/hexmapper.o \
    bin/ext/imgui_all.o \
    -Lbin/ext -lraylib -lpthread -ldl \
    -o bin/hexmapper
cp -rv src/resources bin/
pushd bin/
./hexmapper
popd

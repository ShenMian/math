#!/bin/bash
# Copyright 2021 ShenMian
# License(Apache-2.0)

# 切换到主目录
cd "$( cd "$( dirname "$0"  )" && pwd  )" || exit
cd ..

# 签出第三方库
echo Checkout third-party libraries...
if ! git submodule update --init >/dev/null
then
    echo Failed to checkout third-party libraries.
    exit 1
fi

# 生成 CMake 緩存
echo Generating CMake cache...
if ! cmake -B build >/dev/null
then
    echo Failed to generate CMake cache.
    cmake -B build
    exit 1
fi

# 构建
echo Building...
if ! cmake --build build >/dev/null
then
    echo Failed to build.
    cmake --build build
    exit 1
fi

echo Done.

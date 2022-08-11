#!/bin/bash
# Copyright 2021 ShenMian
# License(Apache-2.0)

if ! hash "cmake" &>/dev/null; then
    echo "=== Need cmake."
    exit 1
fi

if [ $# -eq 0 ]; then
  build_type="Debug"
else
  build_type=$1
fi

cd "$( cd "$( dirname "$0"  )" && pwd  )" || exit
cd .. || exit

mkdir build 2>/dev/null

echo "=== Checkout third-party libraries..."
if ! git submodule update --init >/dev/null
then
    echo Failed to checkout third-party libraries.
    exit 1
fi

echo "=== Generating CMake cache..."
if ! cmake -B build -Wno-dev >/dev/null
then
    echo "=== Failed to generate CMake cache."
    exit 1
fi

echo "=== Generating 'compile_commands.json'..."
cp build/compile_commands.json . &>/dev/null || echo "No 'compile_commands.json' was generated."

echo "=== Building..."
if ! cmake --build build --config "${build_type}" -- -j$(nproc) >/dev/null
then
    echo "=== Failed to build."
    exit 1
fi

echo "=== Done."

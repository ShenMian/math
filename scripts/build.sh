#!/bin/bash
# Copyright 2023 ShenMian
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

build_path=target/$build_type

cd "$( cd "$( dirname "$0"  )" && pwd  )" || exit
cd .. || exit

mkdir $build_path 2>/dev/null

echo "=== Checkout third-party libraries..."
git submodule update --init >/dev/null || {
    echo Failed to checkout third-party libraries.
    exit 1
}

echo "=== Generating CMake cache..."
cmake -B $build_path -Wno-dev -G Ninja -DCMAKE_BUILD_TYPE=$build_type -DCMAKE_EXPORT_COMPILE_COMMANDS=ON >/dev/null || {
  echo "=== Failed to generate CMake cache."
  exit 1
}

echo "=== Generating 'compile_commands.json'..."
cp $build_path/compile_commands.json . &>/dev/null || echo "No 'compile_commands.json' was generated."

echo "=== Building..."
cmake --build $build_path --config "$build_type" -- -j$(nproc) || {
  echo "=== Failed to build."
  exit 1
}

echo "=== Done."

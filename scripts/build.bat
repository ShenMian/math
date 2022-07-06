@echo off
REM Copyright 2021 ShenMian
REM License(Apache-2.0)


REM 切换到主目录
pushd %~dp0\..

REM 签出第三方库
echo Checkout third-party libraries...
if ! git submodule update --init >/dev/null
then
    echo Failed to checkout third-party libraries.
    exit 1
fi

REM 生成 CMake 緩存
echo Generating CMake cache...
cmake -B build >nul || (
    echo Failed to generate CMake cache.
    cmake -B build
    exit /b 1
)

REM 构建
echo Building...
cmake --build build >nul || (
    echo Failed to build.
    cmake --build build -j 8
    exit /b 1
)

echo Done.

popd


@echo off
REM Copyright 2021 ShenMian
REM License(Apache-2.0)

cmake --version >nul 2>&1 || (
    echo === Need cmake.
    exit /b 1
)

if "%~1"=="" (set "build_type=Debug") else (set "build_type=%~1")

cd %~dp0\.. || exit /b 1

mkdir build 2>nul

echo === Checkout third-party libraries...
if ! git submodule update --init >/dev/null
then
    echo Failed to checkout third-party libraries.
    exit 1
fi

echo === Generating CMake cache...
cmake -B build -Wno-dev >nul || (
    echo === Failed to generate CMake cache.
    exit /b 1
)

echo === Generating 'compile_commands.json'...
xcopy "build/compile_commands.json" "."

echo === Building...
cmake --build build --config %build_type% -j16 >nul || (
    echo === Failed to build.
    exit /b 1
)

echo === Done.

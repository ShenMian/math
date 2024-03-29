@echo off
REM Copyright 2023 ShenMian
REM License(Apache-2.0)

cmake --version >nul 2>&1 || (
    echo === Need cmake.
    exit /b 1
)

if "%~1"=="" (set "build_type=Debug") else (set "build_type=%~1")

set "build_path=target/%build_type%"

cd %~dp0\.. || exit /b 1

mkdir %build_path% 2>nul

echo === Checkout third-party libraries...
git submodule update --init >nul || (
    echo Failed to checkout third-party libraries.
    exit /b 1
)

echo === Generating CMake cache...
cmake -B %build_path% -Wno-dev -G Ninja -DCMAKE_build_type=%BUILD_TYPE% -DCMAKE_EXPORT_COMPILE_COMMANDS=ON >nul || (
    echo === Failed to generate CMake cache.
    exit /b 1
)

echo === Generating 'compile_commands.json'...
xcopy %build_path%\compile_commands.json . 2>nul || echo No 'compile_commands.json' was generated.

echo === Building...
cmake --build %build_path% --config "%build_type%" -j18 || (
    echo === Failed to build.
    exit /b 1
)

echo === Done.

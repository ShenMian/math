-- Copyright 2022 ShenMian
-- License(Apache-2.0)

include "deps/premake/solution_items.lua"

workspace "math"
    architecture "x86_64"
    startproject "tests"
    flags "MultiProcessorCompile"

    configurations {"Debug", "Release"}
  
    solution_items {
    "README.md",
    "premake5.lua"}

    filter "configurations:Debug"
    defines "DEBUG"
    runtime "Debug"
    symbols "on"

    filter "configurations:Release"
    defines "NDEBUG"
    runtime "Release"
    optimize "on"

    deps = {}
    deps["googletest"] = "%{wks.location}/deps/googletest/googletest"

    deps_inc = {}
    deps_inc["googletest"] = "%{deps.googletest}/include"

    output_dir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

    include "include/Math"
    include "tests"

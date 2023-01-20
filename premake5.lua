-- Copyright 2023 ShenMian
-- License(Apache-2.0)

-- include("deps/premake/solution_items.lua")

workspace("math")
    architecture("x86_64")
    startproject("tests")
    flags("MultiProcessorCompile")

    configurations({ "Debug", "Release" })

    -- solution_items({
    --     "README.md",
    --     "CMakeLists.txt",
    --     "premake5.lua",
    -- })

    filter("configurations:Debug")
        defines("DEBUG")
        runtime("Debug")
        symbols("on")

    filter("configurations:Release")
        defines("NDEBUG")
        runtime("Release")
        optimize("on")

    deps = {}
    deps["doctest"] = "%{wks.location}/deps/doctest"
    deps["gcem"] = "%{wks.location}/deps/gcem"

    deps_inc = {}
    deps_inc["doctest"] = "%{deps.doctest}/doctest"
    deps_inc["gcem"] = "%{deps.gcem}/include"

    output_dir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

    include("src/math")
    include("tests")

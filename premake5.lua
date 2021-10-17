-- Copyright 2021 SMS
-- License(Apache-2.0)

include "thirdparty/premake/solution_items.lua"

workspace "math"
  architecture "x86_64"
  startproject "tests"
  configurations {"Debug", "Release"}
  flags "MultiProcessorCompile"

  solution_items {
    ".clang-format",
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

  filter "system:linux"
      linkoptions "-pthread"

thirdparty = {}
thirdparty["googletest"] = "%{wks.location}/thirdparty/googletest/googletest"

outputdir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

include "tests"

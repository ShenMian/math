-- Copyright 2023 ShenMian
-- License(Apache-2.0)

include "deps/googletest.lua"

project "tests"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir("%{wks.location}/build/" .. output_dir .. "/%{prj.name}/bin")
	objdir("%{wks.location}/build/" .. output_dir .. "/%{prj.name}/obj")

	files {"**.cpp", "premake5.lua", "CMakeLists.txt"}

	includedirs "%{wks.location}/include"

	sysincludedirs {
		"%{wks.location}/include",
		"%{deps_inc.googletest}"}

	links "googletest"

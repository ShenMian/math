-- Copyright 2022 ShenMian
-- License(Apache-2.0)

project "googletest"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir("%{wks.location}/build/" .. output_dir .. "/%{prj.name}/lib")
	objdir ("%{wks.location}/build/" .. output_dir .. "/%{prj.name}/obj")

	files {"googletest/googletest/include/gtest/**.h", "googletest/googletest/src/**.cc"}

	includedirs {"googletest/googletest", "googletest/googletest/include"}

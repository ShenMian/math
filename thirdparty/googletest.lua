-- Copyright 2021 SMS
-- License(Apache-2.0)

project "googletest"
	kind "StaticLib"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"

	targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/bin")
	objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

	files {"googletest/googletest/include/gtest/**.h", "googletest/googletest/src/**.cc"}

	includedirs {"googletest/googletest", "googletest/googletest/include"}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"
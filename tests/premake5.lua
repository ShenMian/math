-- Copyright 2021 SMS
-- License(Apache-2.0)

include "thirdparty/googletest.lua"

project "tests"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"
	staticruntime "on"
  
	targetdir("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/bin")
	objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}/obj")

	files {"**.cpp", "premake5.lua"}

	includedirs {
		"%{wks.location}/include",
		"%{thirdparty.googletest}/include"}

	links {"googletest"}
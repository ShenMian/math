-- Copyright 2021 SMS
-- License(Apache-2.0)

project "Math"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++latest"

	files {"**.hpp", "**.inl", "premake5.lua"}

	includedirs "%{wks.location}/include"

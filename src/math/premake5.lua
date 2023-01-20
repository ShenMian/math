-- Copyright 2022 ShenMian
-- License(Apache-2.0)

project("Math")
	kind("ConsoleApp")
	language("C++")
	cppdialect("C++latest")

	files({ "**.hpp", "**.inl", "CMakeLists.txt", "premake5.lua" })

	includedirs("%{wks.location}/src")

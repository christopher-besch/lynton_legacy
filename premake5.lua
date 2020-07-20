workspace "Lynton"
	architecture "x64"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to solution directory
include_dir = {}
include_dir["GLFW"] = "Lynton/vendor/GLFW/include"

include "Lynton/vendor/GLFW"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"Lynton/vendor/spdlog/include",
		"Lynton/src"
	}
	
	links
	{
		"Lynton"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"LY_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "LY_DEBUG"
		symbols "On"
	
	filter "configurations:Release"
		defines "LY_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "LY_DIST"
		optimize "On"

project "Lynton"
	location "Lynton"
	kind "SharedLib"
	language "C++"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "lypch.h"
	pchsource "Lynton/src/lypch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{include_dir.GLFW}"
	}
	
	links
	{
		"GLFW",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"
		
		defines
		{
			"LY_PLATFORM_WINDOWS",
			"LY_BUILD_DLL"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "LY_DEBUG"
		defines "LY_ENABLE_ASSERTS"
		symbols "On"
	
	filter "configurations:Release"
		defines "LY_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "LY_DIST"
		optimize "On"

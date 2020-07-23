workspace "Lynton"
	architecture "x64"
	startproject "Sandbox"
	
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
include_dir["Glad"] = "Lynton/vendor/Glad/include"
include_dir["ImGui"] = "Lynton/vendor/imgui"

include "Lynton/vendor/GLFW"
include "Lynton/vendor/Glad"
include "Lynton/vendor/imgui"

project "Lynton"
	location "Lynton"
	kind "SharedLib"
	language "C++"
	staticruntime "off"
	
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
		"%{include_dir.GLFW}",
		"%{include_dir.Glad}",
		"%{include_dir.ImGui}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		
		defines
		{
			"LY_PLATFORM_WINDOWS",
			"LY_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}
	
	filter "configurations:Debug"
		defines "LY_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "LY_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "LY_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"
	
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
		systemversion "latest"
		
		defines
		{
			"LY_PLATFORM_WINDOWS"
		}
	
	filter "configurations:Debug"
		defines "LY_DEBUG"
		runtime "Debug"
		symbols "On"
	
	filter "configurations:Release"
		defines "LY_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "LY_DIST"
		runtime "Release"
		optimize "On"

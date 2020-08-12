workspace "Lynton"
	architecture "x64"
	startproject "Sandbox"
	
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- include directories relative to solution directory
include_dir = {}
include_dir["GLFW"] = "Lynton/vendor/GLFW/include"
include_dir["Glad"] = "Lynton/vendor/Glad/include"
include_dir["ImGui"] = "Lynton/vendor/imgui"
include_dir["glm"] = "Lynton/vendor/glm"
include_dir["stb_image"] = "Lynton/vendor/stb_image"

include "Lynton/vendor/GLFW"
include "Lynton/vendor/Glad"
include "Lynton/vendor/imgui"

project "Lynton"
	location "Lynton"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")
	
	pchheader "lypch.h"
	pchsource "Lynton/src/lypch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/stb_image/**.cpp",
		"%{prj.name}/vendor/stb_image/**.h",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{include_dir.GLFW}",
		"%{include_dir.Glad}",
		"%{include_dir.ImGui}",
		"%{include_dir.glm}",
		"%{include_dir.stb_image}"
	}
	
	links
	{
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}
	
	filter "system:windows"
		systemversion "latest"
		
		defines
		{
			"GLFW_INCLUDE_NONE"
		}
	
	filter "configurations:Debug"
		defines "LY_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "LY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LY_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"
	
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
		"Lynton/src",
		"Lynton/vendor",
		"%{include_dir.glm}"
	}
	
	links
	{
		"Lynton"
	}
	
	filter "system:windows"
		systemversion "latest"
	
	filter "configurations:Debug"
		defines "LY_DEBUG"
		runtime "Debug"
		symbols "on"
	
	filter "configurations:Release"
		defines "LY_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "LY_DIST"
		runtime "Release"
		optimize "on"

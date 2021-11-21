workspace "Hackathon"
	architecture "x86"
	configurations { "Debug", "Release" }
	startproject "Hackathon"
	flags
	{
		"MultiProcessorCompile"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["GLEW"] = "%{wks.location}/Hackathon/Vendor/GLEW/include"
	IncludeDir["GLFW"] = "%{wks.location}/Hackathon/Vendor/GLFW/include"
	IncludeDir["stb_image"] = "%{wks.location}/Hackathon/Vendor/stb_image"
	IncludeDir["imgui"] = "%{wks.location}/Hackathon/Vendor/imgui"
	IncludeDir["glm"] = "%{wks.location}/Hackathon/Vendor/glm"
	
	group "Dependencies"
	include "Hackathon/Vendor/GLEW"
	include "Hackathon/Vendor/GLFW"
	include "Hackathon/Vendor/imgui"
	group ""

	include "Hackathon"

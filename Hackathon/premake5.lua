project "Hackathon"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"

	targetdir ("%{wks.location}/bin/" .. outputdir.. "/%{prj.name}")
	objdir    ("%{wks.location}/bin-int/" .. outputdir.. "/%{prj.name}")
	
	includedirs
	{
		"%{wks.location}/Hackathon/Source",
		"%{wks.location}/Hackathon/Vendor",
		"%{IncludeDir.GLEW}",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.imgui}",
		"Vendor/stb_image",
		"Vendor/glm",
	}
	
	files
	{
		"Source/**.h",
		"Source/**.cpp",
		"Vendor/stb_image/**.h",
		"Vendor/stb_image/**.cpp",
		"Vendor/glm/glm/**.hpp",
		"Vendor/glm/glm/**.inl",
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS",
		"GLFW_INCLUDE_NONE",
		"GLEW_STATIC",
		"AL_LIBTYPE_STATIC"
	}

	links 
	{
		"GLFW",
		"GLEW",
		"opengl32.lib",
		"imgui",
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"

	filter "configurations:Debug"
		defines "DEBUG=1"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RELEASE=1"
		runtime "Release"
		optimize "on"


project "GLEW"
	kind "StaticLib"
	language "C"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	includedirs
	{
		"include;",
	}

	files
	{
		"include/GL/glew.h",
		"include/GL/eglew.h",
		"include/GL/glxew.h",
		"include/GL/wglew.h",
		"src/**.c"
	}

	defines
	{
		"GLEW_STATIC"
	}

	filter "system:linux"
		pic "on"

		systemversion "latest"

	filter "system:windows"
		systemversion "latest"
		staticruntime "on"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

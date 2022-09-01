workspace "Bubatsu"
	architecture "x64"

	startproject "Sandbox"

	configurations {
		"Debug",
		"Release",
		"Master"
	}

	outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

	IncludeDir = {}
	IncludeDir["bubatsu"] = "Bubatsu/src"
	IncludeDir["glad"] = "Bubatsu/extern/glad/include"
	IncludeDir["glfw"] = "Bubatsu/extern/glfw/include"
	IncludeDir["glm"] = "Bubatsu/extern/glm"
	IncludeDir["imgui"] = "Bubatsu/extern/imgui"
	IncludeDir["spdlog"] = "Bubatsu/extern/spdlog/include"
	IncludeDir["stb"] = "Bubatsu/extern/stb"

	group "Dependencies"
		include "Bubatsu/extern/glad" 
		include "Bubatsu/extern/glfw"
		include "Bubatsu/extern/imgui"
	group ""


	project "Bubatsu"
		location "Bubatsu"
		kind "StaticLib"
		language "C++"
		cppdialect "C++20"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

		pchheader "bbzpch.h"
		pchsource "Bubatsu/src/bbzpch.cpp"

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
			"%{prj.name}/extern/glm/glm/**.hpp",
			"%{prj.name}/extern/glm/glm/**.inl",
			"%{prj.name}/extern/stb/**.h",
			"%{prj.name}/extern/stb/**.cpp",
		}

		includedirs {
			"%{IncludeDir.bubatsu}",
			"%{IncludeDir.glad}",
			"%{IncludeDir.glfw}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.imgui}",
			"%{IncludeDir.spdlog}",
			"%{IncludeDir.stb}"
		}

		links {
			"Glad",
			"Glfw",
			"ImGui",
			"opengl32.lib"
		}

		filter "system:windows"
			systemversion "latest"

			defines {
				"BBZ_PLATFORM_WINDOWS",
                "GLFW_INCLUDE_NONE"
			}

			postbuildcommands {
				("{COPY} %{cfg.buildtarget.relpath} \"../bin/" .. outputdir .. "/Sandbox/\"")
			}

			filter "configurations:Debug"
				defines "BBZ_DEBUG"
				runtime "Debug"
				symbols "on"
				disablewarnings "4996"

			filter "configurations:Release"
				defines "BBZ_RELEASE"
				runtime "Release"
				symbols "on"
			
			filter "configurations:Master"
				defines "BBZ_MASTER"
				symbols "on"
				optimize "on"


	project "Sandbox"
		location "Sandbox"
		kind "ConsoleApp"
		language "C++"
		cppdialect "C++20"
		staticruntime "on"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

		files {
			"%{prj.name}/src/**.h",
			"%{prj.name}/src/**.cpp",
		}

		includedirs {
			"%{IncludeDir.bubatsu}",
			"%{IncludeDir.glm}",
			"%{IncludeDir.imgui}",
			"%{IncludeDir.spdlog}"
		}

		links {
			"Bubatsu",
			"ImGui"
		}

		linkoptions "-IGNORE:4098"

		filter "system:windows"
			systemversion "latest"

			defines {
				"BBZ_PLATFORM_WINDOWS"
			}

		filter "configurations:Debug"
			defines "BBZ_DEBUG"
            runtime "Debug"
			symbols "on"

		filter "configurations:Release"
			defines "BBZ_RELEASE"
            runtime "Release"
			symbols "on"

		filter "configurations:Master"
			defines "BBZ_MASTER"
			symbols "on"
			optimize "on"


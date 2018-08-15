-- Generate the 'Storm' workspace (a.k.a. Visual Studio solution)
workspace "Storm"
	configurations { "Debug", "Release" }
	location "Build"

	filter { 'system:windows' }
			platforms   { 'x86', 'x64' }
 
		-- Visual Studio 2005 special case:
		-- Premake requires the following instructions in order to build vc8 solutions and projects
			require "vstudio"
			premake.override(premake.vstudio.vc200x, "tools", function(oldfn, cfg)
			local toolset = premake.config.toolset(cfg)
			premake.callArray(premake.vstudio.vc200x.elements.tools, cfg, iif(toolset == premake.tools.msc, nil, toolset))
			end)

	filter "configurations:Debug"
		defines     "_DEBUG"
		symbols 	"On"

	filter "configurations:Release"
		defines     "NDEBUG"
		optimize    "Full"
		flags       { "NoBufferSecurityCheck", "NoRuntimeChecks" }

	filter "action:vs*"
		defines     { "_CRT_SECURE_NO_DEPRECATE", "_CRT_SECURE_NO_WARNINGS", "_CRT_NONSTDC_NO_WARNINGS" }

	filter { "system:windows", "configurations:Release" }
		flags       { "NoIncrementalLink", "LinkTimeOptimization" }
	
	filter "system:macosx"
		toolset "clang"

-- Generate the 'StormLib' project
-- This is the main library project, containing the preciouuus
project "StormLib"
	kind ("StaticLib")
	language "C++"

	-- Generic build steps
	-- This needs to be set before platform-specific steps or it will not run
	-- Possible Premake bug?
	files { "Source/*.cpp" }

	-- We include all files under Source/H to create the Visual Studio filter for header files
	files { "Source/H/*.h", "Source/H/*.inl" }

	-- We remove some files from the build steps:
	-- ConsoleStorm.cpp: Not needed as part of Storm
	-- SStr.cpp: Necessary to compile properly, due to in-lining
	removefiles {
		"Source/ConsoleStorm.cpp"
		}

	includedirs { "Source/H" }

	-- Windows ONLY build steps
	filter "system:windows"
		files { "Source/W32/*.cpp" }
		defines {
			"WIN32_LEAN_AND_MEAN",
			"_WIN32_WINNT 0x0501"
		}
	
	-- Linux ONLY build steps
	filter "system:linux"
		files { "Source/Linux/*.cpp" }
	
	-- MacOS ONLY build steps
	filter "system:macosx"
		files { "Source/Mac/*.cpp" }
		defines { "LUA_USE_MACOSX" }


-- Generate the 'ConsoleStorm' project
-- This project is used for testing the Storm library from within the IDE
project "ConsoleStorm"
	kind ("ConsoleApp")
	language "C++"

	files "Source/ConsoleStorm.cpp"
	includedirs { "Source/H" }
	links { "StormLib" }

	-- MacOS ONLY build steps
	-- CoreFoundation is used for SErr dialog boxes on Mac OS X
	filter "system:macosx"
		defines { "LUA_USE_MACOSX" }
		links { "CoreFoundation.framework" }

-- Generate the 'Storm' workspace (a.k.a. Visual Studio solution)
workspace "Storm"
	configurations { "Debug", "Release" }
	location "Build"

	filter { "system:windows" }
		require "vstudio"
		premake.override(premake.vstudio.vc200x, "tools", function(oldfn, cfg)
			local toolset = premake.config.toolset(cfg)
			premake.callArray(premake.vstudio.vc200x.elements.tools, cfg, iif(toolset == premake.tools.msc, nil, toolset))
		end)

		filter { "configurations:debug" }
			symbols "On"
		filter { }

-- Generate the 'ConsoleStorm' project
-- This project is used for testing the Storm library from within the IDE
project "ConsoleStorm"
	kind ("ConsoleApp")
	language "C++"

	files "Source/ConsoleStorm.cpp"
	includedirs { "Source/H" }
	links { "StormLib" }

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
	files { "Source/H/**" }
	removefiles { "Source/ConsoleStorm.cpp" }
	includedirs { "Source/H" }

	-- Windows ONLY build steps
	filter "system:windows"
		files { "Source/W32/*.cpp" }
	
	-- Linux ONLY build steps
	filter "system:linux"
		files { "Source/Linux/*.cpp" }
	
	-- MacOS ONLY build steps
	filter "system:macosx"
		files { "Source/Mac/*.cpp" }

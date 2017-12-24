-- Workaround for Premake issue #935 (1/3)
function os.winSdkVersion()
    local reg_arch = iif( os.is64bit(), "\\Wow6432Node\\", "\\" )
    local sdk_version = os.getWindowsRegistry( "HKLM:SOFTWARE" .. reg_arch .."Microsoft\\Microsoft SDKs\\Windows\\v10.0\\ProductVersion" )
    if sdk_version ~= nil then return sdk_version end
end

-- Generate the 'Storm' workspace (a.k.a. Visual Studio solution)
workspace "Storm"
	configurations { "Debug", "Release" }
	location "Build"

-- Generate the 'ConsoleStorm' project
-- This project is used for testing the Storm library from within the IDE
project "ConsoleStorm"
	kind ("ConsoleApp")
	language "C++"

	-- Workaround for Premake issue #935 (3/3)
	filter { "system:windows", "action:vs*" }
	systemversion(os.winSdkVersion() .. ".0")
	-- end Workaround

	files "Source/ConsoleStorm.cpp"
	links { "StormLib" }

-- Generate the 'StormLib' project
-- This is the main library project, containing the preciouuus
project "StormLib"
	kind ("StaticLib")
	language "C++"

	-- Workaround for Premake issue #935 (2/3)
	filter { "system:windows", "action:vs*" }
	systemversion(os.winSdkVersion() .. ".0")
	-- end Workaround

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

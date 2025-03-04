project "App"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "off"

    files { "Source/**.h", "Source/**.cpp" }

    includedirs
    {
        "Source",
	    "../Bingo/Source"
    }

    dependson
    {
        "Bingo"
    }

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")

    filter "system:windows"
        systemversion "latest"
        defines { "WINDOWS" }
        postbuildcommands
        {
            "{COPY} ../Binaries/" .. OutputDir .. "/Bingo/*.dll ../Binaries/" .. OutputDir .. "/App"
        }

    filter "system:linux"
        defines { "LINUX" }
        postbuildcommands
        {
            "{COPY} ../Binaries/" .. OutputDir .. "/Bingo/*.so ../Binaries/" .. OutputDir .. "/App"
        }


    filter "configurations:Debug"
        defines { "DEBUG" }
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        runtime "Release"
        optimize "On"
        symbols "Off"
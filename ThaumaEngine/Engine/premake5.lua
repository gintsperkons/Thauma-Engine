project "ThaumaEngineLib"
    kind "SharedLib"
    language "C++"
    targetdir "Binaries/%{cfg.buildcfg}"
    cppdialect "C++20"


    files {"src/**.h", "src/**.cpp"}

    includedirs
    {
        "src"
    }

    links 
    {
    }

    targetdir ("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
    


    postbuildcommands
    {   
        "{mkdir} %{wks.location}/Binaries/" .. OutputDir .. "/TestBed/",
        "{ECHO} %{cfg.longname}",
        "{COPYFILE} %{cfg.buildtarget.relpath} %{wks.location}/Binaries/" .. OutputDir .. "/TestBed/"
    }

    filter "system:windows"
        systemversion "latest"
        defines {"WINDOWS"}

    filter "configurations:Debug"
        defines {"DEBUG"}
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {"RELEASE"}
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines {"DIST"}
        runtime "Release"
        optimize "On"
        symbols "Off"

    
    
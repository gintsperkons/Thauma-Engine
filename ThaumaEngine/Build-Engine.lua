project "ThaumaEngine"
    kind "SharedLib"
    language "C++"
    targetdir "Binaries/%{cfg.buildcfg}"


    files {"Source/**.h", "Source/**.cpp"}

    includedirs
    {
        "Source"

    }

    targetdir ("../Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("../Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
    
    postbuildcommands
    {   
        "{mkdir} ../Binaries/" .. OutputDir .. "/TestBed/",
        "{mkdir} ../Binaries/" .. OutputDir .. "/Editor/",
        "{COPY} ../Binaries/" .. OutputDir .. "/ThaumaEngine/ThaumaEngine.dll ../Binaries/" .. OutputDir .. "/TestBed/",
        "{COPY} ../Binaries/" .. OutputDir .. "/ThaumaEngine/ThaumaEngine.dll ../Binaries/" .. OutputDir .. "/Editor/"
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

    
    


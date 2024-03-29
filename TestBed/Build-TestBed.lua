project "TestBed"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
    targetdir "Binaries/%{cfg.buildcfg}"
    staticruntime "off"


    files {"Source/**.h", "Source/**.cpp"}

    includedirs
    {
        "Source",
        "%{wks.location}/ThaumaEngine/Source"

    }

    links
    {
        "ThaumaEngine"
    }
    
   

    targetdir ("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")
    objdir ("%{wks.location}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
    


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

project "ThaumaEngineLib"
    kind "SharedLib"
    language "C++"
    targetdir "Binaries\\%{cfg.buildcfg}"
    cppdialect "C++20"


    files {"Source\\**.h", "Source\\**.cpp"}



    includedirs
    {
        "Source",
        IncludeDir["GLFW"],
        IncludeDir["GLM"],
        IncludeDir["VulkanSDK"]
    }

    links 
    {
        "GLFW",
        Library["Vulkan"]
    }

    targetdir ("%{wks.location}\\Binaries\\" .. OutputDir .. "\\%{prj.name}")
    objdir ("%{wks.location}\\Binaries\\Intermediates\\" .. OutputDir .. "\\%{prj.name}")
    debugdir("%{wks.location}\\Binaries\\" .. OutputDir .. "\\%{prj.name}")

    flags {
        "MultiProcessorCompile"
    }

    prebuildcommands {
        -- Check for the platform
        os.host() == "windows" and 'cmd /c "%{prj.location}\\Shaders\\CompileShaders.bat"' or
        os.host() == "linux" and 'bash "%{prj.location}/Shaders/CompileShaders.sh"'
    }

    postbuildcommands
    {   
        "{ECHO} %{prj.location}",
        "{mkdir} %{wks.location}\\Binaries\\" .. OutputDir .. "\\TestBed\\",
        "{COPYFILE} %{cfg.buildtarget.relpath} %{wks.location}\\Binaries\\" .. OutputDir .. "\\TestBed\\",
        "{mkdir} %{wks.location}\\Binaries\\" .. OutputDir .. "\\ThaumaEngineEditor\\",
        "{COPYFILE} %{cfg.buildtarget.relpath} %{wks.location}\\Binaries\\" .. OutputDir .. "\\ThaumaEngineEditor\\",
        "{mkdir} %{wks.location}\\Binaries\\" .. OutputDir .. "\\TestBed\\Shaders\\",
        "{COPYDIR} %{prj.location}\\Shaders %{wks.location}\\Binaries\\" .. OutputDir .. "\\TestBed\\Shaders\\",
        "{mkdir} %{wks.location}\\Binaries\\" .. OutputDir .. "\\ThaumaEngineEditor\\Shaders\\",
        "{COPYDIR} %{prj.location}\\Shaders %{wks.location}\\Binaries\\" .. OutputDir .. "\\ThaumaEngineEditor\\Shaders\\"
    }

    filter "system:windows"
        systemversion "latest"
        defines {"WINDOWS"}

    filter "configurations:Debug"
        defines {"TEXPORT","TDEBUG"}
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        defines {"TEXPORT","TRELEASE"}
        runtime "Release"
        optimize "On"
        symbols "On"

    filter "configurations:Dist"
        defines {"TEXPORT","TDIST"}
        runtime "Release"
        optimize "On"
        symbols "Off"

    
    
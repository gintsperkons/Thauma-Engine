project "TestBed"
kind "ConsoleApp"
language "C++"
cppdialect "C++20"
targetdir "Binaries/%{cfg.buildcfg}"
staticruntime "off"


targetdir("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")
objdir("%{wks.location}/Binaries/Intermediates/" .. OutputDir .. "/%{prj.name}")
debugdir("%{wks.location}/Binaries/" .. OutputDir .. "/%{prj.name}")

includedirs {"Source",
-- "%{wks.location}/ThaumaEngine/Engine/src"
}

links {
}



files {"Source/**.h", "Source/**.cpp"}

filter "system:windows"
systemversion "latest"
defines {"WINDOWS"}

filter "configurations:Debug"
defines {"TDEBUG"}
runtime "Debug"
symbols "On"

filter "configurations:Release"
defines {"TRELEASE"}
runtime "Release"
optimize "On"
symbols "On"

filter "configurations:Dist"
defines {"TDIST"}
runtime "Release"
optimize "On"
symbols "Off"

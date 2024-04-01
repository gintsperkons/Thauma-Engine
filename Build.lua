include "Dependencies.lua"

workspace "ThaumaEngine"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"}
    startproject "TestBed"
   

OutputDir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group "Dependencies"
    include "Vendor/Libraries/GLFW"
    include "Vendor/Libraries/GLAD"
group ""


group "Core"
    include "ThaumaEngine/Build-Engine.lua"
group ""

include "TestBed/Build-TestBed.lua"





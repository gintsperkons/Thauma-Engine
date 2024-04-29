include "Dependencies.lua"

workspace("ThaumaEngine")
architecture "x64"
configurations {"Debug", "Release", "Dist"}
startproject "TestBed"

OutputDir = "%{cfg.architecture}-%{cfg.system}-%{cfg.buildcfg}"



group "Dependencies"
include "Vendor/Libraries/GLFW"
group ""

group "ThaumaEngine"
group "ThaumaEngineLibrary"
include "ThaumaEngine/Engine"
group ""
group ""

include "TestBed"

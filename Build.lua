workspace "ThaumaEngine"
    architecture "x64"
    configurations {"Debug", "Release", "Dist"}
    startproject "TestBed"
   

OutputDir = "%{cfg.system}-%{cfg.architecture}-%{cfg.buildcfg}"

group "Engine"
    include "Engine/Build-Engine.lua"
group ""

include "TestBed/Build-TestBed.lua"





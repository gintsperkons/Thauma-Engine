include "Dependencies.lua"

workspace("ThaumaEngine")
architecture "x64"
configurations {"Debug", "Release", "Dist"}
startproject "TestBed"

OutputDir = "%{cfg.architecture}-%{cfg.system}-%{cfg.buildcfg}"

include "TestBed"

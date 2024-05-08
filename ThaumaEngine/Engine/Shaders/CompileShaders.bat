@echo off
setlocal enabledelayedexpansion

pushd %~dp0
if not exist Compiled mkdir Compiled

echo ---Compiling shaders---
for /r %%i in (Raw\*) do (
    set str=%%i 
    set str=!str:%~dp0=!
    set relativePath=!str!
    set str=!str:Raw\=Compiled\!
    set str=!str:.vert=-vert.spv!
    set str=!str:.frag=-frag.spv!
    set outputRelativePath=!str!
    echo !relativePath!--^> !outputRelativePath!
    %VULKAN_SDK%/bin/glslc.exe !relativePath! -o !outputRelativePath!

)
Echo ---Done---
popd



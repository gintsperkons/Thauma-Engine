@echo off
setlocal enabledelayedexpansion

pushd %~dp0
pushd ..

REM Remove .vxproj and .sln files from all subfolders
for /r %%i in (*) do (
    if "%%~xi"==".vcxproj" del /s /q "%%i"
    if "%%~xi"==".vcxproj.user" del /s /q "%%i"
    if "%%~xi"==".vcxproj.filters" del /s /q "%%i"
    if "%%~xi"==".sln" del /s /q "%%i"
)

REM Remove /Binaries/ directories from all subfolders
for /d /r %%i in (*) do (
    if "%%~nxi"=="Binaries" rmdir /s /q "%%i"
    if "%%~nxi"=="Vendor/Binaries" rmdir /s /q "%%i"
)

popd
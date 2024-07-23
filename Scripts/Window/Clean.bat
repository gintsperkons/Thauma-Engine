@echo off
setlocal enabledelayedexpansion
set directory=Vendor\Binary\

pushd %~dp0..\..\
echo !cd!
echo Cleaning Up Generated Files
echo !cd!\!directory!Python\python.exe
call !cd!\!directory!Python\python.exe !cd!\Scripts\Python\Clean.py

if "%~1"=="all" (
    echo Cleaning Up Downloads
    rmdir /s /q !directory!
)

popd
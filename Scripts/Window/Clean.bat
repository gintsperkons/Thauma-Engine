@echo off
setlocal enabledelayedexpansion
set directory=Vendor\Binary\

pushd %~dp0..\..\

echo Cleaning Up Files

if exist !directory! (
    echo Cleaning Up Generated Files
    echo !cd!\!directory!Python\python.exe
    call !cd!\!directory!Python\python.exe !cd!\Scripts\Python\Clean.py
)

if "%~1"=="all" (
    if exist !directory! (
    echo Cleaning !directory!
    rmdir /s /q !directory!
    )
)
echo Done
popd
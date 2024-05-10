@echo off
setlocal enabledelayedexpansion
set directory=Vendor\Binaries\

pushd %~dp0
pushd ..

echo Cleaning Up Generated Files
call !directory!Python\python.exe !%~dp0!Clean.py

if "%~1"=="all" (
    echo Cleaning Up Downloads
    rmdir /s /q !directory!
)

popd
popd
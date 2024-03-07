@echo off
setlocal enabledelayedexpansion

pushd %~dp0
if not exist "..\%~1" (
    echo Creating directory: "%~1"
    mkdir "..\%~1"
)
popd
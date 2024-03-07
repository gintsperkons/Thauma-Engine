@echo off
setlocal enabledelayedexpansion

SET buildElement=%1
SET buildType=%2

SET GlobalProgramName=ThaumaEngine
SET BaseCompilePath=bin
SET BaseLibPath=lib


call scripts\CreateDirectory.bat %BaseCompilePath%
call scripts\CreateDirectory.bat %BaseLibPath%



if "%buildElement%"=="all" (
    if "%buildType%"=="debug" (
        call :buildEngine
        call :buildEditor
        call :buildTestBed
    )
    if "%buildType%"=="release" (
        call :buildEngine
        call :buildEditor
        call :buildTestBed
    )
)
goto :eof

:buildEngine
    pushd Engine
    call build.bat %buildType% %GlobalProgramName% %BaseCompilePath% %BaseLibPath%
    popd
    goto :eof

:buildEditor
    pushd Editor
    call build.bat %buildType% %GlobalProgramName% %BaseCompilePath% %BaseLibPath%
    popd
    goto :eof

:buildTestBed
    pushd TestBed
    call build.bat %buildType% %GlobalProgramName% %BaseCompilePath% %BaseLibPath%
    popd
    goto :eof

@echo off
setlocal enabledelayedexpansion

set directory=Vendor\Binaries\Premake\Windows\
set executable=premake5.exe
set archiveLink=https://github.com/premake/premake-core/releases/download/v5.0.0-beta2/premake-5.0.0-beta2-windows.zip

if "%~1"=="" (
    echo Provide development environment example: vs2022.
) else (
pushd %~dp0
pushd ..



if not exist !directory!!executable! (
    set link=""
    set destination=""
    
    if not exist "Vendor\Binaries\Premake\Windows\Temp" (
        mkdir "Vendor\Binaries\Premake\Windows\Temp"
    ) else (
        echo Directory already exists
    )
    
    powershell.exe -Command "Invoke-WebRequest -Uri '!archiveLink!'  -OutFile !directory!Temp\temp.zip"
    powershell.exe -Command "Expand-Archive -Path '!directory!Temp\temp.zip' -DestinationPath '!directory!\Temp' -Force"
    copy "!directory!Temp\!executable!" "!directory!"
    rd /s /q "!directory!Temp"
) 


!directory!!executable! %1

if  "%~1"=="vs2022" (
    if "%~2"=="open" (
        
        for /f "delims=" %%i in ('dir /s /b *.sln') do (
            set "slnPath=%%i"
            goto :continue
        )

        :continue
        REM Print the path of the .sln file
        echo !slnPath!
        start devenv !slnPath!

    )
)



popd
)   
@echo off
setlocal enabledelayedexpansion
set directory=Vendor\Binaries\Python\
set archiveLink=https://www.python.org/ftp/python/3.12.0/python-3.12.0-embed-amd64.zip
set getpipLink=https://bootstrap.pypa.io/get-pip.py

pushd %~dp0
pushd ..

:: Call Python to execute a simple command
for /f "delims=" %%i in ('call "!directory!python.exe" -c "print(1+1)"') do set output=%%i

:: Check the output
if "%output%"=="2" (
    echo Python is working correctly.
) else (
    echo Python is not working correctly.
    if not exist !directory! (
        mkdir !directory!
    )
    echo Downloading python 
    powershell.exe -Command "Invoke-WebRequest -Uri '!archiveLink!'  -OutFile '!directory!python.zip'"
    echo Downloading get-pip.py 
    powershell.exe -Command "Invoke-WebRequest -Uri '!getpipLink!'  -OutFile '!directory!get-pip.py'"
    echo Extracting python 
    powershell.exe -Command "Expand-Archive -Path '!directory!python.zip' -DestinationPath '!directory!' -Force"
    echo Installing pip
    call "!directory!python.exe" "!directory!get-pip.py"
    echo Removing Python archive
    del "!directory!python.zip"
)

call "!directory!python.exe" "!%~dp0!Setup.py"

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
popd
@echo off
setlocal enabledelayedexpansion
set binaryDir=Vendor\Binary
set pythonVersion=3.12.4
set pythonVersionSmall=312
set archiveLink=https://www.python.org/ftp/python/!pythonVersion!/python-!pythonVersion!-embed-amd64.zip
set getpipLink=https://bootstrap.pypa.io/get-pip.py

pushd %~dp0..\..\

echo Setting Up Python
:: Call Python to execute a simple command
for /f "delims=" %%i in ('call "!binaryDir!\Python\python.exe" -c "print(1+1)"') do set output=%%i

:: Check the output
if "%output%"=="2" (
    echo Python is working correctly.
) else (
    echo Python is not working correctly.
    if not exist !binaryDir!\Temp (
        mkdir !binaryDir!\Temp
    )
    echo Downloading python 
    powershell.exe -Command "Invoke-WebRequest -Uri '!archiveLink!'  -OutFile '!binaryDir!\Temp\python.zip'"
    echo Downloading get-pip.py 
    powershell.exe -Command "Invoke-WebRequest -Uri '!getpipLink!'  -OutFile '!binaryDir!\Temp\get-pip.py'"
    echo Extracting python 
    powershell.exe -Command "Expand-Archive -Path '!binaryDir!\Temp\python.zip' -DestinationPath '!binaryDir!\Python\' -Force"
    echo Lib\site-packages>>"!binaryDir!\Python\python!pythonVersionSmall!._pth"
    echo ..\..\..\Scripts\Python>>"!binaryDir!\Python\python!pythonVersionSmall!._pth"
    echo Installing pip
    "!binaryDir!\Python\python.exe" "!binaryDir!\Temp\get-pip.py"
    echo Removing Python archive
    del "!directory!python.zip"
)



"!binaryDir!\Python\python.exe" "Scripts\Python\Setup.py" "%~1" "%~2" "%~3" 

if exist !binaryDir!\Temp (
    echo Removing Temp
    rmdir /s /q !binaryDir!\Temp
)


echo Done

popd
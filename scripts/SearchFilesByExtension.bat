@echo off
@REM This script will get all files in a directory with a specific extension
@REM It takes in two arguments
@REM The first argument is the directory to search
@REM The second argument is the extension to search for
@REM The script will search the directory and all subdirectories for files with the specified extension
pushd %~dp0
for /D %%d in (%~1\*) do (
    echo Searching Files in "%%d"
    call SearchFilesByExtension.bat %%d %~2
)
for %%f in (%~1\*%~2) do (
    echo AddingFile: "%%f"
    set "result=!result! %%f"
)
popd
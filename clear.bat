@echo off
setlocal enabledelayedexpansion

SET FoldersToClear=bin lib

for %%i in (%FoldersToClear%) do (
    if exist %%i\ (
        call :ClearFolders %%i
    )
)

goto :eof



:ClearFolders
    if exist %~1\ (
        @REM ECHO Checking Directory "%~1" For Directories
        for /D %%i in (%~1\*) do (
            if exist %%i\ (
                call :ClearFolders %%i
            )
        )
        @REM ECHO Checking Directory "%~1" For Files
        for %%i in (%~1\*) do (
            if exist %%i (
                ECHO Deleting File "%%i"
                del /F /Q "%%i"
            )
        )
        ECHO Deleting Directory "%~1\"
        rmdir /S /Q "%~1\"
    )
    goto :eof
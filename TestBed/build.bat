@echo off
setlocal enabledelayedexpansion




SET buildType=%1
SET ProgramName=%2
SET CompilePath=%3\%buildType%\testbed
SET LibPath=%4

SET compilerFlags=-g 
SET includeFlags=-Isrc -I..\Engine\src\
SET linkerFlags=-L..\lib\ -l%ProgramName%
SET defines=-DDEBUG -DTIMPORT


SET compiler=clang++
if "%buildType%"=="debug" (
    call :buildDebug
)
if "%buildType%"=="release" (
    call :buildRelease
)
goto :eof



:buildDebug
    call ..\scripts\CreateDirectory.bat %LibPath%
    call ..\scripts\CreateDirectory.bat %CompilePath%
    SET result =
    call ..\scripts\SearchFilesByExtension.bat ..\TestBed\src .cpp
    SET SourceFiles=!SourceFiles! !result!
    for %%f in (!SourceFiles!) do (
        SET inFilePath=%%f
        SET inFilePath=!inFilePath:..\TestBed\=!
        SET outFilePath=%CompilePath%\!inFilePath:.cpp=.o!
        for %%d in ("%CompilePath%\!inFilePath:.cpp=.o!") do (
            SET outFileDir=%%~dpd
            SET relativePath=%%~pd
        )
        SET outFileDir=!outFileDir:%CD%\=!
        call ..\scripts\CreateDirectory.bat !outFileDir!
        SET result=
        call ..\scripts\FileIsNewer.bat TestBed\!inFilePath! !outFilePath!
        if !result! EQU 1 (
            echo Compiling File "%%f"
            !compiler! -c -g -o ..\!outFilePath! !inFilePath! %includeFlags%
        )
    )   
    SET result=
    call ..\scripts\SearchFilesByExtension.bat ..\!CompilePath! .o
    SET ObjectFiles=!result!
    ECHO Building %ProgramName% testbed
    !compiler! %ObjectFiles% %compilerFlags% -o ..\!CompilePath!\%ProgramName%.exe %defines% %includeFlags% %linkerFlags%
    xcopy ..\%LibPath%\* ..\%CompilePath% /I /Y

    
    goto :eof

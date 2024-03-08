@echo off
setlocal enabledelayedexpansion




SET buildType=%1
SET ProgramName=%2
SET CompilePath=%3\%buildType%\testbed
SET LibPath=%4

SET compiler=clang++
SET includeFlags=-Isrc -I..\Engine\src\
SET linkerFlags=-L..\lib\ -l%ProgramName%


if "%buildType%"=="debug" (
    SET compilerFlags=-g -std=c++17 -Wall -Werror
    SET defines=-DTDEBUG -DTIMPORT
)
if "%buildType%"=="release" (
    SET compilerFlags=-std=c++17 -Wall -Werror
    SET defines=-DTRELEASE -DTIMPORT
)
call :buildTestBed

goto :eof

:buildTestBed
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
            !compiler! -c %compilerFlags% -o ..\!outFilePath! !inFilePath! %includeFlags%
        )
    )   
    SET result=
    call ..\scripts\SearchFilesByExtension.bat ..\!CompilePath! .o
    SET ObjectFiles=!result!
    ECHO Building %ProgramName% testbed
    !compiler! %ObjectFiles% %compilerFlags% -o ..\!CompilePath!\%ProgramName%.exe %defines% %linkerFlags%
    xcopy ..\%LibPath%\* ..\%CompilePath% /I /Y

    ECHO Done Building %ProgramName% testbed
    goto :eof

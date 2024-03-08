@echo off
setlocal enabledelayedexpansion

SET buildType=%1
SET ProgramName=%2
SET CompilePath=%3\%buildType%\engine
SET LibPath=%4

SET SourceFiles=

SET compiler=clang++
SET compilerLibData=-shared -o ..\%LibPath%\%ProgramName%.dll -Wl,--out-implib,..\%LibPath%\%ProgramName%.lib

SET includeFlags=-Isrc -I%VULKAN_SDK%/Include
SET linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib

if "%buildType%"=="debug" (
    SET definesDebug=-DTDEBUG -DTEXPORT -D_CRT_SECURE_NO_WARNINGS
    SET compilerFlags=-g -Wvarargs -Wall -Werror
)
if "%buildType%"=="release" (
    SET definesDebug=-DTRELEASE -DTEXPORT -D_CRT_SECURE_NO_WARNINGS
    SET compilerFlags=-Wvarargs -Wall -Werror
)

call :buildEngine
goto :eof


:buildEngine
    ECHO Building %ProgramName% Library
    call ..\scripts\CreateDirectory.bat %LibPath%
    call ..\scripts\CreateDirectory.bat %CompilePath%
    SET result =
    call ..\scripts\SearchFilesByExtension.bat ..\Engine\src .cpp
    SET SourceFiles=!SourceFiles! !result!
    for %%f in (!SourceFiles!) do (
        SET inFilePath=%%f
        SET inFilePath=!inFilePath:..\Engine\=!
        SET outFilePath=%CompilePath%\!inFilePath:.cpp=.o!
        for %%d in ("%CompilePath%\!inFilePath:.cpp=.o!") do (
            SET outFileDir=%%~dpd
            SET relativePath=%%~pd
        )
        SET outFileDir=!outFileDir:%CD%\=!
        call ..\scripts\CreateDirectory.bat !outFileDir!
        SET result=
        call ..\scripts\FileIsNewer.bat Engine\!inFilePath! !outFilePath!
        if !result! EQU 1 (
            echo Compiling File "%%f"
            !compiler! -c %compilerFlags% %includeFlags%  -o ..\!outFilePath! !inFilePath!
        )
    )   
    SET result=
    call ..\scripts\SearchFilesByExtension.bat ..\!CompilePath! .o
    SET ObjectFiles=!result!
    !compiler! %defines% %compilerLibData% %ObjectFiles% %linkerFlags%
    ECHO Done Building %ProgramName% Library
    goto :eof




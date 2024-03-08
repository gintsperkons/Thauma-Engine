@echo off
setlocal enabledelayedexpansion

SET compilerDebugFlags=-g -Wvarargs -Wall -Werror
SET linkingDebugFlags=-g -shared -Wvarargs -Wall -Werror
SET includeFlags=-Isrc -I%VULKAN_SDK%/Include
SET linkerFlags=-luser32 -lvulkan-1 -L%VULKAN_SDK%/Lib
SET definesDebug=-DDEBUG -DTEXPORT -D_CRT_SECURE_NO_WARNINGS



SET compilerReleaseFlags= -Wvarargs -Wall -Werror
SET linkingReleaseFlags=-shared -Wvarargs -Wall -Werror
SET definesRelease=-DTEXPORT -D_CRT_SECURE_NO_WARNINGS

SET buildType=%1
SET ProgramName=%2
SET CompilePath=%3\%buildType%\engine
SET LibPath=%4

SET SourceFiles=

SET compiler=clang++
SET compilerInfo=-shared -o ..\%LibPath%\%ProgramName%.dll -Wl,--out-implib,..\%LibPath%\%ProgramName%.lib

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
            echo !cd!
            !compiler! -c %compilerDebugFlags% %includeFlags%  -o ..\!outFilePath! !inFilePath!
        )
    )   
    SET result=
    call ..\scripts\SearchFilesByExtension.bat ..\!CompilePath! .o
    SET ObjectFiles=!result!
    ECHO Building %ProgramName% Library
    !compiler! %linkingDebugFlags% %includeFlags% %definesDebug% %compilerInfo% %ObjectFiles% %linkerFlags%

    goto :eof

:buildRelease
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
            echo !cd!
            !compiler! -c %compilerReleaseFlags%  %includeFlags% -o ..\!outFilePath! !inFilePath!
        )
    )   
    SET result=
    call ..\scripts\SearchFilesByExtension.bat ..\!CompilePath! .o
    SET ObjectFiles=!result!
    ECHO Building %ProgramName% Libraries
    !compiler! %linkingReleaseFlags% %includeFlags% %definesRelease% %compilerInfo% %ObjectFiles% %linkerFlags%

    goto :eof
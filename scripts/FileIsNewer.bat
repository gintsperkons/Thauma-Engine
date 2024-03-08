@echo off
@REM This script will check if a file has changed
@REM It takes in two arguments
@REM The first argument is the source file
@REM The second argument is the object file
@REM The script will compare the file times of the source and object files
@REM If the source file is newer than the object file the script will return 1
@REM If the source file is older than the object file the script will return 0
@REM If the source file is the same age as the object file the script will return 0

pushd %~dp0

if not exist ../%~2 (
    set result=1
    popd
    EXIT /B 0
)

for %%X in (../%~1) do (
    set filetimeSourceCode=%%~tX
)
for %%X in (../%~2) do (
    set filetimeObjectFile=%%~tX
)

Set /A SourceDay=1%filetimeSourceCode:~0,2%-100
Set /A SourceMonth=1%filetimeSourceCode:~3,2%-100
Set /A SourceYear=1%filetimeSourceCode:~6,4%-10000
Set /A SourceHour=1%filetimeSourceCode:~11,2%-100
Set /A SourceMinute=1%filetimeSourceCode:~14,2%-100
Set /A ObjectDay=1%filetimeObjectFile:~0,2%-100
Set /A ObjectMonth=1%filetimeObjectFile:~3,2%-100
Set /A ObjectYear=1%filetimeObjectFile:~6,4%-10000
Set /A ObjectHour=1%filetimeObjectFile:~11,2%-100
Set /A ObjectMinute=1%filetimeObjectFile:~14,2%-100


SET /A timeStampSourceCode=!SourceYear!*525600+!SourceMonth!*43800+!SourceDay!*1440+!SourceHour!*60+!SourceMinute!
SET /A timeStampObjectFile=!ObjectYear!*525600+!ObjectMonth!*43800+!ObjectDay!*1440+!ObjectHour!*60+!ObjectMinute!



if !timeStampSourceCode! GTR !timeStampObjectFile! (
    set result=1
) else (
    set result=0
)
popd
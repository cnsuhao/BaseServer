
@echo off 

for /f "delims=" %%a in ('dir /b/s/a-d *.cpp *.h') do ( 

    set "str=%%~nxa" 

    setlocal enabledelayedexpansion 

    copy /B "%%a"+,, "%%a"

    endlocal 

) 
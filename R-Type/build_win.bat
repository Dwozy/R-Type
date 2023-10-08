@echo off

if "%~1"=="fclean" (
    call:fclean
    exit /b
)

if "%~1"=="re" (
    call:fclean
    call:build
    exit /b
)

call:build

exit /b

:build
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build .\build --config Release --clean-first

for /R .\build %%f in (*.dll) do copy %%f .

set SCRIPT="%TEMP%\%RANDOM%-%RANDOM%-%RANDOM%-%RANDOM%.vbs"

echo Set oWS = WScript.CreateObject("WScript.Shell") >> %SCRIPT%
echo sLinkFile = "..\r-type_client.lnk" >> %SCRIPT%
echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%
echo oLink.TargetPath = "%cd%\r-type_client.exe" >> %SCRIPT%
echo oLink.WorkingDirectory = "%cd%" >> %SCRIPT%
echo oLink.Save >> %SCRIPT%

cscript /nologo %SCRIPT%
del %SCRIPT%
goto:eof

:fclean

echo -- Cleaning build folder
if exist ".\build" rmdir ".\build" /q /s
if exist ".\r-type_client.exe" del ".\r-type_client.exe"
echo -- Cleaning build folder - done
goto:eof

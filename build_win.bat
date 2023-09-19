@echo off

if "%~1"=="clean" (
    call:clean
    exit /b
)

if "%~1"=="rebuild" (
    call:clean
    call:build
    exit /b
)

call:build

exit /b

:build
cmake -S . -B build
cmake --build .\build --config Release --clean-first
goto:eof

:clean
echo -- Cleaning build folder
if exist ".\build" rmdir ".\build" /q /s
echo -- Cleaning build folder - done
goto:eof

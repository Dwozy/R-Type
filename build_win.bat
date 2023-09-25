
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
cmake -S . -B build
cmake --build .\build --config Release --clean-first
goto:eof

:fclean
echo -- Cleaning build folder
if exist ".\build" rmdir ".\build" /q /s
echo -- Cleaning build folder - done
echo -- Cleaning GameEngine folder
if exist ".\GameEngine" rmdir ".\GameEngine" /q /s
echo -- Cleaning GameEngine folder - done
echo -- Cleaning libGameEngine.lib
if exist ".\GameEngine.lib" del ".\GameEngine.lib"
echo -- Cleaning libGameEngine.lib - done
goto:eof

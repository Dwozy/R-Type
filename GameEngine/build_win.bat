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
set CONAN_BUILD_DIR=build\build\generators
set INCLUDES_DIR=%cd%\include
conan build . --output-folder=. --build=missing -g MSBuildDeps -s compiler.cppstd=17
goto:eof

:fclean

echo -- Cleaning build folder
if exist ".\build" rmdir ".\build" /q /s
echo -- Cleaning build folder - done
echo -- Cleaning GameEngine folder
if exist ".\GameEngine" rmdir ".\GameEngine" /q /s
echo -- Cleaning GameEngine folder - done
goto:eof

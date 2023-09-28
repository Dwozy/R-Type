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
conan install . --output-folder=build --build=missing -c tools.system.package_manager:mode=install -g visual_studio
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=%CONAN_BUILD_DIR%\conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .\build --config Release --clean-first
goto:eof

:fclean

echo -- Cleaning build folder
if exist ".\build" rmdir ".\build" /q /s
echo -- Cleaning build folder - done
echo -- Cleaning GameEngine folder
if exist ".\GameEngine" rmdir ".\GameEngine" /q /s
echo -- Cleaning GameEngine folder - done
goto:eof

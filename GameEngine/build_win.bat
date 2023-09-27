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
conan install . --output-folder=build --build=missing -c tools.system.package_manager:mode=install
dir
dir build
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=build\build\Release\generators\conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
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

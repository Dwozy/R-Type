@echo off
set version=%1

echo -- Cleaning build folder
rmdir /s /q "build"
echo -- Cleaning build folder - done

mkdir artifacts

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_CLIENT="" -DINSTALL=""
cmake --build .\build --config Release
cd build
cpack --config CPackConfig.cmake -G ZIP -C Release
cpack --config CPackConfig.cmake -G NSIS -C Release
set status=%ERRORLEVEL%
if %status% neq 0 (
    exit /b %status%
)
move "R-Type-client-0.1.1-win64.zip" "..\artifacts\r-type_client-%version%-windows_x86-64.zip"
move "R-Type-client-0.1.1-win64.exe" "..\artifacts\r-type_client-%version%-windows_x86-64.exe"
cd ..
del /f "build\CMakeCache.txt"

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_SERVER="" -DINSTALL=""
cmake --build .\build --config Release
cd build
cpack --config CPackConfig.cmake -G ZIP -C Release
cpack --config CPackConfig.cmake -G NSIS -C Release
set status=%ERRORLEVEL%
if %status% neq 0 (
    exit /b %status%
)
move "R-Type-server-0.1.1-win64.zip" "..\artifacts\r-type_server-%version%-windows_x86-64.zip"
move "R-Type-server-0.1.1-win64.exe" "..\artifacts\r-type_server-%version%-windows_x86-64.exe"
cd ..
del /f "build\CMakeCache.txt"

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_GAME_PLATFORMER="" -DINSTALL=""
cmake --build .\build --config Release
cd build
cpack --config CPackConfig.cmake -G ZIP -C Release
cpack --config CPackConfig.cmake -G NSIS -C Release
set status=%ERRORLEVEL%
if %status% neq 0 (
    exit /b %status%
)
move "SCP-Adventures-0.1.1-win64.zip" "..\artifacts\scp_adventures-%version%-windows_x86-64.zip"
move "SCP-Adventures-0.1.1-win64.exe" "..\artifacts\scp_adventures-%version%-windows_x86-64.exe"
cd ..
del /f "build\CMakeCache.txt"

cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DBUILD_GAME_ENGINE="" -DINSTALL=""
cmake --build .\build --config Release
cd build
cpack --config CPackConfig.cmake -G ZIP -C Release
cpack --config CPackConfig.cmake -G NSIS -C Release
set status=%ERRORLEVEL%
if %status% neq 0 (
    exit /b %status%
)
move "R-Type-Game-Engine-0.1.1-win64.zip" "..\artifacts\r-type_game_engine-%version%-windows_x86-64.zip"
move "R-Type-Game-Engine-0.1.1-win64.exe" "..\artifacts\r-type_game_engine-%version%-windows_x86-64.exe"
cd ..
del /f "build\CMakeCache.txt"

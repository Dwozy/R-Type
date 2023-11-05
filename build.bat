@echo off

del /q build\CMakeCache.txt

set debug=""
set target="%~1"
set build_type=Release

if "%~1" == "-d" (
    set debug=-"DDEBUG=On"
    set build_type=Release
    set target="%~2"
)

if %target%=="clean" (
    call:clean_all
    exit /b
)

if %target%=="fclean" (
    call:fclean_all
    exit /b
)

if %target%=="GameEngine" (
    call:build_game_engine
    exit /b
)

if %target%=="Client" (
    call:build_client
    exit /b
)

if %target%=="Server" (
    call:build_server
    exit /b
)

if %target%=="tests" (
    call:build_tests
    exit /b
)

if %target%=="platformer" (
    call:build_game_platformer
    exit /b
)

call:build_all

exit /b

:clean_all
    echo -- Cleaning build folder
    if exist ".\build" rmdir ".\build" /q /s
    echo -- Cleaning build folder - done
goto:eof

:fclean_all
    call:clean_all
    if exist ".\R-Type\r-type_client.exe" del ".\R-Type\r-type_client.exe"
    if exist ".\R-Type-server\r-type_server.exe" del ".\R-Type-server\r-type_server.exe"
    if exist ".\Platformer\platformer.exe" del ".\Platformer\platformer.exe"
    if exist "unit_tests.exe" del "unit_tests.exe"
    if exist ".\r-type_client.lnk" del ".\r-type_client.lnk"
    if exist ".\r-type_server.lnk" del ".\r-type_server.lnk"
goto:eof

:build_all
    cmake -S . -B build -DCMAKE_BUILD_TYPE=%build_type% %debug%
    cmake --build .\build --config %build_type%

    for /R .\build %%f in (*.dll) do copy %%f .\R-Type
    for /R .\build %%f in (*.dll) do copy %%f .\R-Type-server
    for /R .\build %%f in (*.dll) do copy %%f .\tests
    for /R .\build %%f in (*.dll) do copy %%f .\Platformer
goto:eof

:build_game_engine
    cmake -S . -B build -DCMAKE_BUILD_TYPE=%build_type% -DBUILD_GAME_ENGINE="" %debug%
    cmake --build .\build --config %build_type%
goto:eof

:build_client
    cmake -S . -B build -DCMAKE_BUILD_TYPE=%build_type% -DBUILD_CLIENT="" %debug%
    cmake --build .\build --config %build_type%

    for /R .\build %%f in (*.dll) do copy %%f .\R-Type
goto:eof

:build_server
    cmake -S . -B build -DCMAKE_BUILD_TYPE=%build_type% -DBUILD_SERVER="" %debug%
    cmake --build .\build --config %build_type%

    for /R .\build %%f in (*.dll) do copy %%f .\R-Type-server
goto:eof

:build_tests
    cmake -S . -B build -DCMAKE_BUILD_TYPE=%build_type% -DBUILD_TESTS="" %debug%
    cmake --build .\build --config %build_type%

    for /R .\build %%f in (*.dll) do copy %%f .\tests

:build_game_platformer
    cmake -S . -B build -DCMAKE_BUILD_TYPE=%build_type% -DBUILD_GAME_PLATFORMER="" %debug%
    cmake --build .\build --config %build_type%

    for /R .\build %%f in (*.dll) do copy %%f .\Platformer

goto:eof

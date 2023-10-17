@echo off

if "%~1"=="clean" (
    call:clean_all
    exit /b
)

if "%~1"=="fclean" (
    call:fclean_all
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
    if exist ".\r-type_client.lnk" del ".\r-type_client.lnk"
    if exist ".\r-type_server.lnk" del ".\r-type_server.lnk"
goto:eof

:build_all
    cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
    cmake --build .\build --config Release --clean-first

    for /R .\build %%f in (*.dll) do copy %%f .\R-Type
    for /R .\build %%f in (*.dll) do copy %%f .\R-Type-server
goto:eof

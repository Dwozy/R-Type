@echo off

if "%~1"=="fclean" (
    call:fclean_all
    exit /b
)

if "%~1"=="engine" (
    if "%~2"=="fclean" (
        call:fclean_game_engine
        exit /b
    )
    call:build_game_engine
    exit /b
)

call:build_all
type nul > r-type_server.exe
type nul > r-type_client.exe

exit /b

:build_game_engine
    cd .\GameEngine\
    call build_win.bat
    if %errorlevel% neq 0 exit /b %errorlevel%
    cd ..
goto:eof

:fclean_game_engine
    cd .\GameEngine\
    call build_win.bat fclean
    if %errorlevel% neq 0 exit /b %errorlevel%
    cd ..
goto:eof

:fclean_all
    call:fclean_game_engine
goto:eof

:build_all
    call:build_game_engine
goto:eof

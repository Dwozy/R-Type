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

if "%~1"=="r-type" (
    if "%~2"=="fclean" (
        call:fclean_r_type
        exit /b
    )
    call:build_r_type
    exit /b
)

call:build_all
type nul > r-type_server.lnk

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

:build_r_type
    cd .\R-Type\
    call build_win.bat
    if %errorlevel% neq 0 exit /b %errorlevel%
    cd ..
goto:eof

:fclean_r_type
    cd .\R-Type\
    call build_win.bat fclean
    if %errorlevel% neq 0 exit /b %errorlevel%
    cd ..
goto:eof

:fclean_all
    call:fclean_game_engine
    call:fclean_r_type
goto:eof

:build_all
    call:build_game_engine
    call:build_r_type
goto:eof

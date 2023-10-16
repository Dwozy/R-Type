@echo off

cmd /c build_win.bat

if not exist ".\artifacts" mkdir ".\artifacts" 2>nul
if not exist ".\artifacts\server" mkdir ".\artifacts\server" 2>nul
if not exist ".\artifacts\client" mkdir ".\artifacts\client" 2>nul
if not exist ".\artifacts\client\assets" mkdir ".\artifacts\client\assets" 2>nul

for /R .\build %%f in (*.dll) do (
	copy %%f .\artifacts\server
	copy %%f .\artifacts\client
)

xcopy .\R-Type\assets .\artifacts\client\assets /E

copy .\R-Type\r-type_client.exe .\artifacts\client
copy .\server\r-type_server.exe .\artifacts\server

(
	echo "set SCRIPT=^"%TEMP%\%RANDOM%-%RANDOM%-%RANDOM%-%RANDOM%.vbs^""

    echo "echo Set oWS = WScript.CreateObject(^"WScript.Shell^") >> %SCRIPT%"
    echo "echo sLinkFile = ^"%USERPROFILE%\Desktop\R-Type.lnk^" >> %SCRIPT%"
    echo "echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%"
    echo "echo oLink.TargetPath = ^"%cd%\r-type_client.exe^" >> %SCRIPT%"
    echo "echo oLink.WorkingDirectory = ^"%cd%^" >> %SCRIPT%"
    echo "echo oLink.Save >> %SCRIPT%"

    echo "cscript /nologo %SCRIPT%"
    echo "del %SCRIPT%"
) > .\artifacts\client\install.bat

(
	echo "set SCRIPT=^"%TEMP%\%RANDOM%-%RANDOM%-%RANDOM%-%RANDOM%.vbs^""

    echo "echo Set oWS = WScript.CreateObject(^"WScript.Shell^") >> %SCRIPT%"
    echo "echo sLinkFile = ^"%USERPROFILE%\Desktop\R-Type_Server.lnk^" >> %SCRIPT%"
    echo "echo Set oLink = oWS.CreateShortcut(sLinkFile) >> %SCRIPT%"
    echo "echo oLink.TargetPath = ^"%cd%\r-type_server.exe^" >> %SCRIPT%"
    echo "echo oLink.WorkingDirectory = ^"%cd%^" >> %SCRIPT%"
    echo "echo oLink.Save >> %SCRIPT%"

    echo "cscript /nologo %SCRIPT%"
    echo "del %SCRIPT%"
) > .\artifacts\server\install.bat

7z a ".\artifacts\r-type_client_windows_x86-64.zip" ".\artifacts\client\*"
7z a ".\artifacts\r-type_server_windows_x86-64.zip" ".\artifacts\server\*"

exit /b

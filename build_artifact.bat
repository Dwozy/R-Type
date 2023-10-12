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

7z a ".\artifacts\r-type_client_windows_x86-64.zip" ".\artifacts\client\*"
7z a ".\artifacts\r-type_server_windows_x86-64.zip" ".\artifacts\server\*"

exit /b
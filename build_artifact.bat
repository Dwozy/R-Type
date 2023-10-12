@echo off

cmd /c build_win.bat

if not exist ".\artifact" mkdir ".\artifact" 2>nul
if not exist ".\artifact\server" mkdir ".\artifact\server" 2>nul
if not exist ".\artifact\client" mkdir ".\artifact\client" 2>nul
if not exist ".\artifact\client\assets" mkdir ".\artifact\client\assets" 2>nul

for /R .\build %%f in (*.dll) do (
	copy %%f .\artifact\server
	copy %%f .\artifact\client
)

xcopy .\R-Type\assets .\artifact\client\assets /E

copy .\R-Type\r-type_client.exe .\artifact\client
copy .\server\r-type_server.exe .\artifact\server

7z a ".\artifact\r-type_client_windows_x86-64.zip" ".\artifact\client\*"
7z a ".\artifact\r-type_server_windows_x86-64.zip" ".\artifact\server\*"

exit /b
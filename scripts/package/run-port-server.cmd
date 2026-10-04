@echo off
rem Release package launcher (Windows): runs the desktop port (soa.exe) with its own network code
rem against the local game server as a separate program (soa-server.exe), which run-port-server.ps1
rem starts and stops. run-port.cmd (the server inside soa.exe) stays the usual way. README.txt.
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0run-port-server.ps1" %*
exit /b %ERRORLEVEL%

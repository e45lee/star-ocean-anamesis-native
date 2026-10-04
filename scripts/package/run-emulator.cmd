@echo off
rem Release package launcher (Windows): runs the original 3.7.0 client, unmodified, in the emulator
rem (soa-emu.exe) against soa-server.exe, which run-emulator.ps1 starts and stops. README.txt.
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0run-emulator.ps1" %*
exit /b %ERRORLEVEL%

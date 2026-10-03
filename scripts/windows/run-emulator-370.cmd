@echo off
rem Runs the original 3.7.0 online client, unmodified, in the emulator on Windows
rem (build-win\emulator\soa-emu.exe) against soa-server.exe, which run-emulator-370.ps1 starts and
rem stops. The Windows twin of scripts/run-emulator-370.sh; the options are its own (see the .ps1).
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0run-emulator-370.ps1" %*
exit /b %ERRORLEVEL%

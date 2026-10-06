@echo off
rem Release package launcher (Windows): run-emulator.cmd in English: soa-server.exe --english (it
rem builds and serves the English files: the master, the story, the UI art, from the English tables
rem in data\english\ and your game files) and soa-emu.exe --lang en (the client's language switch).
rem The same options as run-emulator.cmd; the same data folder.
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0run-emulator.ps1" --english --lang en %*
exit /b %ERRORLEVEL%

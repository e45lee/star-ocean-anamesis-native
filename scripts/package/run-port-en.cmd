@echo off
rem Release package launcher (Windows): runs the desktop port in English (soa.exe --lang en: the
rem client's language switch, and its built-in server serves the English files, which it builds on
rem the first start from the English tables in data\english\ and your game files). Otherwise as
rem run-port.cmd; options go to soa.exe (soa.exe --help), e.g. --fullscreen, --data DIR, --new-player.
"%~dp0soa.exe" --lang en %*
exit /b %ERRORLEVEL%

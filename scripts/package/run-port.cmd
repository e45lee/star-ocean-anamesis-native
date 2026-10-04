@echo off
rem Release package launcher (Windows): runs the desktop port (soa.exe: the 3.7.0 client with its
rem local server built in). It finds the game files beside it or in game\ (README.txt). Options go
rem to soa.exe (soa.exe --help), e.g. --fullscreen, --data DIR, --new-player.
"%~dp0soa.exe" %*
exit /b %ERRORLEVEL%

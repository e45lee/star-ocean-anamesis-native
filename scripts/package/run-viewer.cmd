@echo off
rem Release package launcher (Windows): runs soa-viewer.exe (the offline client, unmodified, in the
rem emulator). It finds the game's XAPK beside it or in game\ (README.txt). Options go to
rem soa-viewer.exe (soa-viewer.exe --help), e.g. --fullscreen, --data DIR.
"%~dp0soa-viewer.exe" %*
exit /b %ERRORLEVEL%

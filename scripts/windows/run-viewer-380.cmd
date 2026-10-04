@echo off
rem Runs the offline 3.8.0 client, unmodified, in the viewer on Windows
rem (build-win\emulator-viewer\soa-viewer.exe): the game as shipped after the service ended. No
rem server. The Windows twin of scripts/run-viewer-380.sh (README.md "Windows").
rem
rem Usage: scripts\windows\run-viewer-380.cmd [soa-viewer options...]
rem   saves in soa-viewer.exe's default %LOCALAPPDATA%\soa\viewer-380 unless --data DIR; e.g. --fullscreen
rem   (--xapk FILE / --apk-dir DIR name the game; without them soa-viewer.exe finds it)
rem Needs: build-win\ (scripts/build.sh --windows) and the 3.8.0 XAPK in apk\ (read in place), else
rem the unpacked one in work\extracted\xapk (README.md; scripts/windows-stage.sh --viewer stages the XAPK).
setlocal
set "REPO=%~dp0..\.."
set "VIEWER=%REPO%\build-win\emulator-viewer\soa-viewer.exe"
set "XDIR=%REPO%\work\extracted\xapk"
if /i "%~1"=="-h" goto help
if /i "%~1"=="--help" goto help
if not exist "%VIEWER%" (echo run-viewer-380: %VIEWER% isn't built; run scripts/build.sh --windows 1>&2 & exit /b 1)
rem the game: soa-viewer.exe finds apk\*.xapk itself; else the unpacked XAPK must be there
set "HAVE="
for %%f in ("%REPO%\apk\*.xapk") do set "HAVE=1"
echo. %* | findstr /c:" --xapk " /c:" --apk-dir " >nul && set "HAVE=1"
if not defined HAVE (
  for %%f in (com.square_enix.android_googleplay.StarOceanj.apk assetinstalltime.apk config.arm64_v8a.apk) do (
    if not exist "%XDIR%\%%f" (echo run-viewer-380: no apk\*.xapk and work\extracted\xapk\%%f is missing; see README.md 1>&2 & exit /b 1)
  )
)
cd /d "%REPO%"
"%VIEWER%" %*
exit /b %ERRORLEVEL%
:help
for /f "usebackq tokens=1,*" %%a in (`findstr /b /c:"rem" "%~f0"`) do echo.%%b
exit /b 0

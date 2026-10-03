@echo off
rem Runs the offline 3.8.0 client, unmodified, in the viewer on Windows
rem (build-win\emulator-viewer\soa-viewer.exe): the game as shipped after the service ended. No
rem server. The Windows twin of scripts/run-viewer-380.sh (README.md "Windows").
rem
rem Usage: scripts\windows\run-viewer-380.cmd [soa-viewer options...]
rem   saves in %LOCALAPPDATA%\soa-380\viewer unless --data DIR; e.g. --fullscreen
rem Needs: build-win\ (scripts/build.sh --windows) and the unpacked 3.8.0 XAPK in
rem work\extracted\xapk (README.md; scripts/windows-stage.sh --viewer stages it).
setlocal
set "REPO=%~dp0..\.."
set "VIEWER=%REPO%\build-win\emulator-viewer\soa-viewer.exe"
set "XAPK=%REPO%\work\extracted\xapk"
if /i "%~1"=="-h" goto help
if /i "%~1"=="--help" goto help
if not exist "%VIEWER%" (echo run-viewer-380: %VIEWER% isn't built; run scripts/build.sh --windows 1>&2 & exit /b 1)
for %%f in (com.square_enix.android_googleplay.StarOceanj.apk assetinstalltime.apk config.arm64_v8a.apk) do (
  if not exist "%XAPK%\%%f" (echo run-viewer-380: work\extracted\xapk\%%f is missing; see README.md 1>&2 & exit /b 1)
)
set "DATA=%LOCALAPPDATA%\soa-380\viewer"
echo. %* | findstr /c:"--data" >nul && set "DATA="
cd /d "%REPO%"
if defined DATA (
  if not exist "%DATA%" mkdir "%DATA%"
  "%VIEWER%" --apk-dir "%XAPK%" --data "%DATA%" %*
) else (
  "%VIEWER%" --apk-dir "%XAPK%" %*
)
exit /b %ERRORLEVEL%
:help
for /f "usebackq tokens=1,*" %%a in (`findstr /b /c:"rem" "%~f0"`) do echo.%%b
exit /b 0

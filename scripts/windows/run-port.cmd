@echo off
rem Runs the desktop port on Windows (build-win\port\soa.exe): the 3.7.0 client with the local
rem server built into it. The Windows twin of scripts/run-port.sh (README.md "Windows").
rem
rem Usage: scripts\windows\run-port.cmd [soa options...]
rem   saves in %LOCALAPPDATA%\soa-370\port unless --data DIR; --server HOST[:PORT] plays against a
rem   running soa-server.exe instead (scripts\windows\run-emulator-370.cmd shows how one is started);
rem   the other options as build-win\port\soa.exe --help lists them (client and server options).
rem Needs: build-win\ (scripts/build.sh --windows), data\basmaster-3.7.0.sqlite3 and
rem work\download-3.7.0 (README.md "Game files"), in this checkout or the staged copy
rem (scripts/windows-stage.sh).
setlocal
set "REPO=%~dp0..\.."
set "SOA=%REPO%\build-win\port\soa.exe"
if /i "%~1"=="-h" goto help
if /i "%~1"=="--help" goto help
if not exist "%SOA%" (echo run-port: %SOA% isn't built; run scripts/build.sh --windows 1>&2 & exit /b 1)
if not exist "%REPO%\data\basmaster-3.7.0.sqlite3" (echo run-port: data\basmaster-3.7.0.sqlite3 is missing; see README.md 1>&2 & exit /b 1)
if not exist "%REPO%\work\download-3.7.0\" (echo run-port: work\download-3.7.0 is missing; see README.md 1>&2 & exit /b 1)
set "DATA=%LOCALAPPDATA%\soa-370\port"
echo. %* | findstr /c:"--data" >nul && set "DATA="
cd /d "%REPO%"
if defined DATA (
  if not exist "%DATA%" mkdir "%DATA%"
  "%SOA%" --data "%DATA%" %*
) else (
  "%SOA%" %*
)
exit /b %ERRORLEVEL%
:help
for /f "usebackq tokens=1,*" %%a in (`findstr /b /c:"rem" "%~f0"`) do echo.%%b
exit /b 0

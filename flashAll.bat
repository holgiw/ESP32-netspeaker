@echo off
rem Prueft alle NetSpeaker-Geraete im Netz und bringt veraltete auf den Stand der Builds in build_netspeaker (gebaut mit buildAll.bat):
rem   per WLAN (OTA, Port 3232), Geraete am USB per Rueckfrage. Vor jedem Flash wird gefragt (Enter = Ja).
rem   flashAll.bat               pruefen, dann fragen und flashen
rem   flashAll.bat -CheckOnly    nur pruefen
rem   flashAll.bat -Yes          ohne Rueckfragen
rem   flashAll.bat -Force        auch aktuelle Geraete neu einspielen
rem Checks all NetSpeaker devices on the network and brings outdated ones to the state of the builds in build_netspeaker
rem (built with buildAll.bat): over WiFi (OTA, port 3232), devices on USB by question. It asks before every flash (Enter = yes).
rem   flashAll.bat               check, then ask and flash
rem   flashAll.bat -CheckOnly    only check
rem   flashAll.bat -Yes          without questions
rem   flashAll.bat -Force        also re-flash up-to-date devices
setlocal
cd /d "%~dp0"
if not exist "%~dp0flashAll.ps1" (
    echo flashAll.ps1 fehlt / is missing.
    pause
    exit /b 1
)
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0flashAll.ps1" %*
set "RESULT=%errorlevel%"
if not defined NOPAUSE (
    echo.
    set "ENTER="
    set /p "ENTER=Eingabetaste druecken zum Beenden / Press Enter to close . . . "
)
exit /b %RESULT%

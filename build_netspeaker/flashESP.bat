@echo off
rem Flasht die Sprachausgabe (ESP32-S3) per USB. Doppelklick: sucht den ESP, flasht ihn mit dem Build aus
rem dem Build aus dem Ordner esp32s3 neben dieser Datei (gebaut mit buildAll.bat, sonst Download vom neuesten GitHub-Release) und laesst
rem die Einstellungen (NVS) unberuehrt. Danach fragt es das WLAN ab
rem und sendet es per USB (Enter = WLAN nicht aendern).
rem Aufruf mit Parameter ohne Rueckfragen und ohne WLAN: flashESP.bat 3  (fuer COM3).
rem Flashes the voice output (ESP32-S3) via USB. Double-click: finds the ESP, flashes it with the build in
rem the build in the folder esp32s3 next to this file (built with buildAll.bat, otherwise downloaded from the newest GitHub release) and
rem leaves the settings (NVS) untouched. Afterwards it asks for the WiFi
rem and sends it via USB (Enter = leave the WiFi unchanged).
rem Usage with a parameter without questions and without WiFi: flashESP.bat 3  (for COM3).
setlocal
cd /d "%~dp0"
if not exist "%~dp0voicesetup.ps1" (
    echo voicesetup.ps1 fehlt. / voicesetup.ps1 is missing.
    pause
    exit /b 1
)
powershell -NoProfile -ExecutionPolicy Bypass -File "%~dp0voicesetup.ps1" -Port "%~1"
set "RESULT=%errorlevel%"
if not defined NOPAUSE (
    echo.
    set "ENTER="
    set /p "ENTER=Eingabetaste druecken zum Beenden / Press Enter to close . . . "
)
exit /b %RESULT%

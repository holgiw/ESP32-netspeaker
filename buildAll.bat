@echo off
rem Baut die Firmware mit arduino-cli (der Arduino IDE) fuer den ESP32-S3 (4 MB Flash, PSRAM).
rem   buildAll.bat           baut den ESP32-S3
rem Nach einem erfolgreichen Build werden die fertigen Dateien nach build_netspeaker\esp32s3 kopiert.
rem Der Zwischenstand liegt in %TEMP%\netspeaker-build\s3 (spaetere Laeufe sind schneller), das Protokoll in
rem %TEMP%\netspeaker-build\s3.log. Das Ziel nutzt das Partitionsschema "no_ota" (2 MB App, ca. 1,9 MB LittleFS fuer MP3, keine OTA-Partition).
rem Updates sind deshalb nur per USB moeglich (flashESP.bat), nicht per ArduinoOTA.
rem
rem Builds the firmware with arduino-cli (from the Arduino IDE) for the ESP32-S3 (4 MB Flash, PSRAM).
rem   buildAll.bat           builds the ESP32-S3
rem After a successful build the finished files are copied to build_netspeaker\esp32s3.
rem The intermediate state is in %TEMP%\netspeaker-build\s3 (later runs are faster), the log in
rem %TEMP%\netspeaker-build\s3.log. The target uses the partition scheme "no_ota" (2 MB app, about 1.9 MB LittleFS for MP3, no OTA partition).
rem Updates are therefore only possible via USB (flashESP.bat), not via ArduinoOTA.
setlocal EnableDelayedExpansion
cd /d "%~dp0"

set "CLI=%LOCALAPPDATA%\Programs\Arduino IDE\resources\app\lib\backend\resources\arduino-cli.exe"
set "CFG=%USERPROFILE%\.arduinoIDE\arduino-cli.yaml"
set "OUT=%TEMP%\netspeaker-build"

if not exist "%CLI%" (
    echo arduino-cli.exe nicht gefunden / not found: %CLI%
    echo Arduino IDE 2 installieren oder den Pfad in dieser Datei anpassen. / Install Arduino IDE 2 or adjust the path in this file.
    exit /b 1
)
if not exist "netspeaker.ino" (
    echo netspeaker.ino nicht gefunden - buildAll.bat gehoert in den Projektordner. / netspeaker.ino not found - buildAll.bat belongs in the project folder.
    exit /b 1
)
if not exist "%OUT%" mkdir "%OUT%"
rem Verkabelungsbild fuer die Doku der Weboberflaeche aus verkabelung.svg erzeugen / create the wiring picture for the doc of the web interface from verkabelung.svg
if exist "makeWiringHeader.ps1" powershell -NoProfile -ExecutionPolicy Bypass -File "makeWiringHeader.ps1" >nul

set "WANT="
for %%A in (%*) do set "WANT=!WANT! %%A"
if "!WANT!"=="" set "WANT=s3"

set "RESULT="
set "FAILED=0"
for %%C in (!WANT!) do (
    call :build %%C
    if errorlevel 1 set "FAILED=1"
)

echo.
echo ===== Ergebnis / Result =====
echo !RESULT!
if not defined NOPAUSE (
    echo.
    set "ENTER="
    set /p "ENTER=Eingabetaste druecken zum Beenden / Press Enter to close . . . "
)
exit /b !FAILED!


:build
set "CHIP=%~1"
set "FQBN="
set "DIR="
set "PROP="
if /i "%CHIP%"=="s3" (
    set "DIR=esp32s3"
    set "FQBN=esp32:esp32:esp32s3:FlashSize=4M,PartitionScheme=no_ota,PSRAM=enabled,CDCOnBoot=cdc,DebugLevel=none"
    rem Groessenpruefung fuer die App-Partition (0x200000) per Property setzen
    rem Set the size check for the app partition (0x200000) via property
    set "PROP=--build-property upload.maximum_size=2097152"
)
if not defined FQBN (
    echo Unbekannter Chip / unknown chip: %CHIP% ^(s3^)
    set "RESULT=!RESULT! %CHIP%=unbekannt/unknown"
    exit /b 1
)

echo.
echo [%TIME:~0,8%] Baue / building %CHIP% ... ^(Protokoll / log: %OUT%\%CHIP%.log^)
"%CLI%" compile --config-file "%CFG%" --fqbn "%FQBN%" %PROP% --library "%CD%\lib\ESP32-audioI2S" --build-path "%OUT%\%CHIP%" . > "%OUT%\%CHIP%.log" 2>&1
if errorlevel 1 (
    echo [%TIME:~0,8%] FEHLER / ERROR %CHIP%:
    findstr /i /c:"error" "%OUT%\%CHIP%.log"
    set "RESULT=!RESULT! %CHIP%=FEHLER/ERROR"
    exit /b 1
)
for %%F in ("%OUT%\%CHIP%\netspeaker.ino.bin") do echo [%TIME:~0,8%] %CHIP% fertig / done: %%~zF Bytes, %%~tF
set "RESULT=!RESULT! %CHIP%=OK"

if not exist "build_netspeaker\%DIR%" mkdir "build_netspeaker\%DIR%"
for %%F in (netspeaker.ino.bin netspeaker.ino.bootloader.bin netspeaker.ino.partitions.bin netspeaker.ino.merged.bin) do copy /y "%OUT%\%CHIP%\%%F" "build_netspeaker\%DIR%\" >nul

rem boot_app0.bin liegt im Arduino-Core und wird fuer den USB-Flash gebraucht
rem boot_app0.bin lives in the Arduino core and is needed for the USB flash
for /d %%D in ("%LOCALAPPDATA%\Arduino15\packages\esp32\hardware\esp32\*") do (
    if exist "%%D\tools\partitions\boot_app0.bin" copy /y "%%D\tools\partitions\boot_app0.bin" "build_netspeaker\%DIR%\" >nul
)
echo %CHIP%: nach build_netspeaker\%DIR% kopiert / copied to build_netspeaker\%DIR%
exit /b 0

# Prueft alle NetSpeaker-Geraete im Netz (checkDevices.ps1) und bringt veraltete auf den Stand der Builds in
# build_netspeaker:
#  - per WLAN (ArduinoOTA, Port 3232), ohne USB; Geraete mit aelterer Firmware ohne /api/version ("?") werden ebenfalls angeboten
#  - Geraete am USB werden nach Rueckfrage mit voicesetup.ps1 geflasht (Einstellungen bleiben); danach wird das WLAN abgefragt
#    (Netze zur Auswahl, WLAN des PCs mit gespeichertem Passwort zum Uebernehmen; mit -Yes entfaellt die Abfrage)
# Vor jedem Flash wird gefragt (Enter = Ja). Ein Geraet am USB kann seine Firmware-Version nicht melden, deshalb wird dort
# immer gefragt. Gebaut wird mit buildAll.bat.
#   .\flashAll.ps1               pruefen, dann fragen und flashen
#   .\flashAll.ps1 -CheckOnly    nur pruefen und anzeigen
#   .\flashAll.ps1 -Yes          ohne Rueckfragen (alle veralteten Geraete im Netz und alle am USB)
#   .\flashAll.ps1 -Force        auch aktuelle Geraete neu einspielen
#
# Checks all NetSpeaker devices on the network (checkDevices.ps1) and brings outdated ones to the state of the builds
# in build_netspeaker:
#  - over WiFi (ArduinoOTA, port 3232), no USB needed; devices with older firmware without /api/version ("?") are offered too
#  - devices on USB are flashed after a question with voicesetup.ps1 (settings stay); afterwards the WiFi is asked for
#    (networks to choose from, the WiFi of the PC with its stored password to take over; with -Yes the question is skipped)
# Before every flash it asks (Enter = yes). A device on USB cannot report its firmware version, so it is always asked
# for. Build with buildAll.bat.
#   .\flashAll.ps1               check, then ask and flash
#   .\flashAll.ps1 -CheckOnly    only check and show
#   .\flashAll.ps1 -Yes          without questions (all outdated devices on the network and all on USB)
#   .\flashAll.ps1 -Force        also re-flash up-to-date devices

param([switch]$CheckOnly, [switch]$Yes, [switch]$Force)

$root = $PSScriptRoot
function Ask([string]$question) {
    if ($Yes) { return $true }
    $a = Read-Host "$question [J/n, Y/n]"
    return ($a -eq '' -or $a -match '^[JjYy]')
}

# espota.exe aus dem ESP32-Core der Arduino IDE / espota.exe from the Arduino IDE's ESP32 core
function Find-Espota {
    $root = Join-Path $env:LOCALAPPDATA 'Arduino15\packages\esp32\hardware\esp32'
    $exe = Get-ChildItem -Path $root -Filter espota.exe -Recurse -ErrorAction SilentlyContinue | Sort-Object { $_.FullName } | Select-Object -Last 1
    if ($exe) { return $exe.FullName }
    return $null
}

# ---- 1. Geraete im Netz pruefen / check the devices on the network
Write-Host '=== Geraete im Netz / devices on the network ==='
$devices = @(& "$root\checkDevices.ps1" -PassThru)
if ($devices.Count -eq 0) {
    Write-Host 'Kein NetSpeaker-Geraet im Netz gefunden. / No NetSpeaker device found on the network.'
}
else {
    $devices | Sort-Object IP | Format-Table IP, Name, Chip, Firmware, Soll, Stand -AutoSize | Out-String -Width 200 | Write-Host
}

# ---- 2. Per OTA / via OTA
# Keine OTA-Partition (4 MB Flash, no_ota): Updates nur per USB. / No OTA partition (4 MB flash, huge_app): updates via USB only.
$bins = @{}
$failed = 0
$espota = Find-Espota
foreach ($d in ($devices | Where-Object { $bins.ContainsKey($_.Chip) -and ($_.Stand -eq 'aelter' -or $_.Stand -eq '?' -or $Force) })) {
    $bin = Join-Path $root $bins[$d.Chip]
    if ($CheckOnly) { Write-Host "$($d.Chip) $($d.Name) ($($d.IP)): veraltet oder unbekannt / outdated or unknown"; continue }
    if (-not $espota) { Write-Host 'espota.exe nicht gefunden - ESP32-Core in der Arduino IDE installieren. / espota.exe not found - install the ESP32 core in the Arduino IDE.'; $failed++; break }
    if (-not (Test-Path $bin)) { Write-Host "Build fehlt / missing: $bin"; $failed++; continue }
    if (-not (Ask "$($d.Chip) $($d.Name) ($($d.IP)) per WLAN aktualisieren / update via WiFi?")) { continue }
    Write-Host "Spiele ein / uploading: $($d.IP) ..."
    & $espota -i $d.IP -p 3232 -f $bin -t 60
    if ($LASTEXITCODE -ne 0) { Write-Host "  Fehler / error (espota Exitcode $LASTEXITCODE)"; $failed++; continue }
    $ok = $false
    for ($i = 0; $i -lt 40 -and -not $ok; $i++) {
        Start-Sleep -Seconds 3
        try {
            $v = (New-Object System.Net.WebClient).DownloadString("http://$($d.IP)/api/version")
            if ($v -and $v.Length -gt 0) { $ok = $true }
        } catch {}
    }
    if ($ok) { Write-Host "  $($d.Name) laeuft wieder / is running again" } else { Write-Host "  $($d.Name) meldet sich nicht / does not respond"; $failed++ }
}

# ---- 3. Geraete am USB / devices on USB
Write-Host ''
Write-Host '=== Geraete am USB / devices on USB ==='
$boards = @(Get-CimInstance Win32_PnPEntity | Where-Object { $_.Name -match '\(COM(\d+)\)' -and $_.DeviceID -match 'VID_303A|VID_1A86|VID_10C4|VID_0403' } | ForEach-Object {
    [pscustomobject]@{ Port = [int]([regex]::Match($_.Name, '\(COM(\d+)\)').Groups[1].Value) }
})
if ($boards.Count -eq 0) { Write-Host 'Kein Geraet am USB. / No device on USB.' }
foreach ($b in $boards) {
    if ($CheckOnly) { Write-Host "COM$($b.Port): ESP32"; continue }
    if (-not (Ask "COM$($b.Port) (ESP32-S3) mit dem Build aus build_netspeaker flashen / flash with the build from build_netspeaker?")) { continue }
    $wifiArg = @()
    if (-not $Yes) { $wifiArg = @('-AskWifi') }
    & powershell -NoProfile -ExecutionPolicy Bypass -File "$root\voicesetup.ps1" -Port $b.Port @wifiArg
    if ($LASTEXITCODE -ne 0) { Write-Host "  Flashen fehlgeschlagen / flashing failed (COM$($b.Port))"; $failed++ }
}

Write-Host ''
if ($failed) { Write-Host "$failed Fehler / error(s)."; exit 1 }
Write-Host 'Fertig. / Done.'

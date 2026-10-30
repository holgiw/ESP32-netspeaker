# Flasht die Sprachausgabe (ESP32-S3) per USB, Aufruf aus flashESP.bat.
#   Ohne -Port (Doppelklick auf flashESP.bat): sucht den ESP am USB und flasht die Dateien aus
#   build_netspeaker\esp32s3 (von buildAll.bat erzeugt). Bootloader, Partitionen und App werden
#   einzeln geschrieben, die Einstellungen (NVS) bleiben erhalten. Danach fragt das Skript das WLAN ab und sendet es per USB
#   ("WIFI:<SSID><Tab><Passwort>", siehe checkSerialWifi() in netspeaker.ino); Enter = WLAN nicht aendern.
#   Mit -Port (z. B. 3 fuer COM3) ohne Rueckfragen (dann ohne WLAN), ausser mit -AskWifi (so ruft flashAll.ps1 es auf): dann wird
#   nach dem Flashen auch das WLAN abgefragt.
#
# Flashes the voice output (ESP32-S3) via USB, called from flashESP.bat.
#   Without -Port (double-click on flashESP.bat): finds the ESP on USB and flashes the files
#   from build_netspeaker\esp32s3 (made by buildAll.bat). Bootloader, partitions and app are written
#   separately, the settings (NVS) stay. Afterwards the script asks for the WiFi and sends it via USB
#   ("WIFI:<SSID><Tab><password>", see checkSerialWifi() in netspeaker.ino); Enter = leave the WiFi unchanged.
#   With -Port (e.g. 3 for COM3) without questions (then without WiFi), except with -AskWifi (how flashAll.ps1 calls it): then the
#   WiFi is asked for after flashing as well.
param([string]$Port, [switch]$AskWifi)

# Chip des Projekts: Ordner, esptool-Name, Bootloader-Adresse / project chip: folder, esptool name, bootloader address
$c = @{ Dir = 'esp32s3'; Name = 'esp32s3'; Boot = '0x0' }

# Neuestes esptool.exe aus dem ESP32-Core der Arduino IDE / newest esptool.exe from the Arduino IDE's ESP32 core
function Find-Esptool {
    $root = Join-Path $env:LOCALAPPDATA 'Arduino15\packages\esp32\tools\esptool_py'
    $exe = Get-ChildItem -Path $root -Filter esptool.exe -Recurse -ErrorAction SilentlyContinue | Sort-Object { $_.Directory.Name } | Select-Object -Last 1
    if ($exe) { return $exe.FullName }
    $cmd = Get-Command esptool.exe -ErrorAction SilentlyContinue
    if ($cmd) { return $cmd.Source }
    return $null
}

# ESP am USB: native USB (303A) und gaengige USB-Seriell-Chips / ESP on USB: native USB (303A) and common USB-serial chips
function Get-EspPorts {
    Get-CimInstance Win32_PnPEntity | Where-Object { $_.Name -match '\(COM(\d+)\)' -and $_.DeviceID -match 'VID_303A|VID_1A86|VID_10C4|VID_0403' } | ForEach-Object {
        [pscustomobject]@{ Num = [int]([regex]::Match($_.Name, '\(COM(\d+)\)').Groups[1].Value) }
    }
}

# Frische WLAN-Suche anstossen: netsh zeigt sonst nur das Ergebnis der letzten Suche von Windows.
# Trigger a fresh WiFi scan: netsh otherwise only shows the result of Windows' last scan.
function Start-WifiScan {
    try {
        Add-Type -TypeDefinition @"
using System;
using System.Runtime.InteropServices;
public static class VoiceWlanScan {
    [DllImport("wlanapi.dll")] static extern int WlanOpenHandle(uint clientVersion, IntPtr reserved, out uint negotiated, out IntPtr handle);
    [DllImport("wlanapi.dll")] static extern int WlanCloseHandle(IntPtr handle, IntPtr reserved);
    [DllImport("wlanapi.dll")] static extern int WlanEnumInterfaces(IntPtr handle, IntPtr reserved, out IntPtr list);
    [DllImport("wlanapi.dll")] static extern int WlanScan(IntPtr handle, ref Guid iface, IntPtr ssid, IntPtr ie, IntPtr reserved);
    [DllImport("wlanapi.dll")] static extern void WlanFreeMemory(IntPtr memory);
    public static int Scan() {
        uint neg; IntPtr h;
        if (WlanOpenHandle(2, IntPtr.Zero, out neg, out h) != 0) return 0;
        int started = 0;
        IntPtr list;
        if (WlanEnumInterfaces(h, IntPtr.Zero, out list) == 0) {
            int count = Marshal.ReadInt32(list);
            for (int i = 0; i < count; i++) {
                IntPtr entry = new IntPtr(list.ToInt64() + 8 + i * 532);
                Guid g = (Guid)Marshal.PtrToStructure(entry, typeof(Guid));
                if (WlanScan(h, ref g, IntPtr.Zero, IntPtr.Zero, IntPtr.Zero) == 0) started++;
            }
            WlanFreeMemory(list);
        }
        WlanCloseHandle(h, IntPtr.Zero);
        return started;
    }
}
"@
        if ([VoiceWlanScan]::Scan() -gt 0) {
            Write-Host 'Suche WLANs ... / scanning for WiFi networks ...'
            Start-Sleep -Seconds 4
        }
    } catch {}
}

# Sichtbare 2,4-GHz-WLANs (Kanal 1-14), nach Signalstaerke sortiert
# Visible 2.4 GHz WiFis (channel 1-14), sorted by signal strength
function Get-WifiNetworks {
    $nets = @{}
    $ssid = $null
    $signal = 0
    try {
        foreach ($l in (netsh wlan show networks mode=bssid 2>$null)) {
            if ($l -match '^SSID \d+\s*:\s*(.*)$') {
                $ssid = $Matches[1].Trim()
                if ($ssid -and -not $nets.ContainsKey($ssid)) { $nets[$ssid] = -1 }
            }
            elseif ($ssid -and $l -match '^\s+Signal\s*:\s*(\d+)') { $signal = [int]$Matches[1] }
            elseif ($ssid -and $l -match '^\s+(Kanal|Channel)\s*:\s*(\d+)\s*$') {
                if ([int]$Matches[2] -le 14 -and $signal -gt $nets[$ssid]) { $nets[$ssid] = $signal }
            }
        }
    } catch {}
    return @($nets.Keys | Where-Object { $nets[$_] -ge 0 } | Sort-Object { -$nets[$_] })
}
function Get-CurrentWifi {
    try {
        foreach ($l in (netsh wlan show interfaces 2>$null)) {
            if ($l -match '^\s+SSID\s*:\s*(.+)$') { return $Matches[1].Trim() }
        }
    } catch {}
    return ''
}

# Gespeichertes WLAN-Passwort des PCs fuer ein Netz, leer wenn keins/nicht lesbar
# Stored WiFi password of the PC for a network, empty if none/not readable
function Get-WifiProfileKey([string]$ssid) {
    try {
        foreach ($l in (netsh wlan show profile "name=$ssid" key=clear 2>$null)) {
            if ($l -match '^\s*(Schl.sselinhalt|Key Content)\s*:\s*(.*)$') { return $Matches[2].Trim() }
        }
    } catch {}
    return ''
}

# Fragt das WLAN fuer die Sprachausgabe ab, Ergebnis in $script:wifiSsid/$script:wifiPass
# Asks for the WiFi for the voice output, result in $script:wifiSsid/$script:wifiPass
$wifiSsid = ''
$wifiPass = ''
function Read-Wifi {
    Write-Host ''
    Write-Host 'WLAN einrichten? Der ESP kann nur 2,4-GHz-Netze, nur diese werden gezeigt.'
    Write-Host 'Set up WiFi? The ESP only supports 2.4 GHz networks, only those are shown.'
    Start-WifiScan
    $nets = @(Get-WifiNetworks)
    $current = Get-CurrentWifi
    for ($i = 0; $i -lt $nets.Count; $i++) {
        $mark = if ($nets[$i] -eq $current) { '  (PC ist verbunden / PC connected)' } else { '' }
        Write-Host ('  {0} = {1}{2}' -f ($i + 1), $nets[$i], $mark)
    }

    $answer = ''
    if ($current -and ($nets -contains $current)) {
        $take = Read-Host "Der PC ist mit '$current' (2,4 GHz) verbunden - WLAN-Name und Passwort uebernehmen? / PC is connected to '$current' (2.4 GHz) - take over WiFi name and password? [J/n, Y/n]"
        if (-not $take -or $take -match '^[JjYy]') {
            $key = Get-WifiProfileKey $current
            if ($key -and $key.Length -ge 8 -and $key.Length -le 63) {
                $script:wifiSsid = $current
                $script:wifiPass = $key
                Write-Host "WLAN '$current' mit dem gespeicherten Passwort des PCs uebernommen / WiFi '$current' taken over with the PC's stored password."
                return
            }
            Write-Host 'Kein gespeichertes Passwort lesbar - bitte eingeben / no stored password readable - please enter it.'
            $answer = $current
        }
    }

    if (-not $answer) {
        if ($nets.Count -eq 0) {
            Write-Host '  Keine WLAN-Liste verfuegbar - WLAN-Name bitte eintippen oder Enter = ueberspringen'
            Write-Host '  No WiFi list available - please type the WiFi name or Enter = skip'
        } else {
            Write-Host '  Nummer, WLAN-Name eingeben oder Enter = ueberspringen (Einrichtung spaeter im Browser)'
            Write-Host '  number, WiFi name or Enter = skip (set up later in the browser)'
        }
        $answer = Read-Host 'WLAN / WiFi'
    }
    if (-not $answer) { return }

    $ssid = if ($answer -match '^\d+$' -and [int]$answer -ge 1 -and [int]$answer -le $nets.Count) { $nets[[int]$answer - 1] } else { $answer }
    while ($true) {
        $p1 = Read-Host "Passwort fuer / password for '$ssid' (Enter = offenes Netz / open network)" -AsSecureString
        $p2 = Read-Host 'Passwort wiederholen / repeat password' -AsSecureString
        $t1 = [Runtime.InteropServices.Marshal]::PtrToStringUni([Runtime.InteropServices.Marshal]::SecureStringToBSTR($p1))
        $t2 = [Runtime.InteropServices.Marshal]::PtrToStringUni([Runtime.InteropServices.Marshal]::SecureStringToBSTR($p2))
        if ($t1 -ne $t2) { Write-Host 'Die Passwoerter stimmen nicht ueberein / passwords do not match'; continue }
        if ($t1.Length -gt 0 -and ($t1.Length -lt 8 -or $t1.Length -gt 63)) { Write-Host 'WLAN-Passwoerter haben 8-63 Zeichen / WiFi passwords have 8-63 characters'; continue }
        $script:wifiSsid = $ssid
        $script:wifiPass = $t1
        return
    }
}

# Sendet "WIFI:<SSID><Tab><Passwort>" per USB, bis der ESP "[PROV] ok" antwortet (Firmware: checkSerialWifi()).
# Der ESP startet nach dem Flashen neu, der Port verschwindet und kommt wieder - daher wiederholt versuchen.
# Sends "WIFI:<SSID><Tab><password>" via USB until the ESP answers "[PROV] ok" (firmware: checkSerialWifi()).
# The ESP restarts after flashing, the port disappears and comes back - so retry.
function Send-Wifi([string]$ssid, [string]$pass) {
    Write-Host ''
    Write-Host 'WLAN wird per USB an den ESP gesendet - warte auf den Start ...'
    Write-Host 'Sending the WiFi to the ESP via USB - waiting for it to start ...'
    $start = Get-Date
    $hinted = $false
    while (((Get-Date) - $start).TotalSeconds -lt 90) {
        $found = Get-EspPorts | Select-Object -First 1
        if (-not $found) {
            if (-not $hinted -and ((Get-Date) - $start).TotalSeconds -gt 20) {
                Write-Host 'Startet der ESP nicht von selbst? Einmal die Reset-Taste druecken. / Does the ESP not start by itself? Press the Reset button once.'
                $hinted = $true
            }
            Start-Sleep -Milliseconds 500
            continue
        }
        $sp = $null
        try {
            $sp = New-Object System.IO.Ports.SerialPort ("COM$($found.Num)", 115200)
            $sp.DtrEnable = $false
            $sp.RtsEnable = $false
            $sp.ReadTimeout = 300
            $sp.WriteTimeout = 1000
            $sp.NewLine = "`n"
            $sp.Open()
            $untilNext = Get-Date
            while (((Get-Date) - $start).TotalSeconds -lt 90) {
                if ((Get-Date) -ge $untilNext) {
                    $sp.Write("WIFI:$ssid`t$pass`n")
                    $untilNext = (Get-Date).AddMilliseconds(1500)
                }
                try { $line = $sp.ReadLine() } catch { continue }
                if ($line -match '\[PROV\] ok') { return $true }
                if ($line -match '\[PROV\] error') { Write-Host 'Der ESP lehnt die Eingabe ab (Name 1-32 Zeichen, Passwort 8-63) / the ESP rejects the input (name 1-32 characters, password 8-63).'; return $false }
            }
        } catch {
        } finally {
            if ($sp -and $sp.IsOpen) { try { $sp.Close() } catch {} }
        }
        Start-Sleep -Milliseconds 500
    }
    return $false
}

# ---------------------------------------------------------------------------
# Ablauf / flow
$interactive = -not $Port
$esptool = Find-Esptool
if (-not $esptool) {
    Write-Host 'esptool.exe nicht gefunden - ESP32-Core in der Arduino IDE installieren. / esptool.exe not found - install the ESP32 core in the Arduino IDE.'
    exit 1
}

# 1) Port bestimmen / determine the port
$ports = @(Get-EspPorts)
if ($Port) { $num = [int]($Port -replace '\D', '') }
elseif ($ports.Count -eq 1) {
    $num = $ports[0].Num
    Write-Host "ESP auf / on COM$num"
}
else {
    Write-Host 'COM-Schnittstellen / COM ports:'
    Get-CimInstance Win32_PnPEntity | Where-Object { $_.Name -match '\(COM\d+\)' } | ForEach-Object { Write-Host "  $($_.Name)" }
    if ($ports.Count -gt 1) {
        Write-Host 'Mehrere ESP gefunden - bitte nur einen anschliessen oder die Nummer angeben.'
        Write-Host 'Several ESPs found - connect only one or enter the number.'
    }
    else {
        Write-Host 'Kein ESP erkannt. Datenkabel? Neuer Chip: Boot-Taste halten, USB einstecken, erneut starten.'
        Write-Host 'No ESP detected. Data cable? New chip: hold Boot, plug in USB, start again.'
    }
    $a = Read-Host 'COM-Port Nummer / number (z.B./e.g. 3 = COM3)'
    if (-not $a) { exit 1 }
    $num = [int]($a -replace '\D', '')
}

# 2) Dateien pruefen / check the files
$binDir = Join-Path $PSScriptRoot ('build_netspeaker\' + $c.Dir)
$files = @('netspeaker.ino.bootloader.bin', 'netspeaker.ino.partitions.bin', 'boot_app0.bin', 'netspeaker.ino.bin')
$missing = $files | Where-Object { -not (Test-Path (Join-Path $binDir $_)) }
if ($missing) {
    Write-Host "Fehlende Dateien / missing files in ${binDir}: $($missing -join ', ')"
    Write-Host 'Zuerst buildAll.bat ausfuehren. / Run buildAll.bat first.'
    exit 1
}

# 3) WLAN abfragen (im Doppelklick-Betrieb oder mit -AskWifi) / ask for the WiFi (in double-click mode or with -AskWifi)
if ($interactive -or $AskWifi) { Read-Wifi }

# 4) Flashen / flash
function Invoke-Flash([int]$comNum, [string]$before) {
    Write-Host ''
    Write-Host "Flashe / flashing COM$comNum ($($c.Name)) ..."
    Push-Location $binDir
    $global:LASTEXITCODE = 1
    try {
        & $esptool --chip $c.Name --port "COM$comNum" --baud 460800 --before $before --after hard-reset write-flash -z --flash-mode keep --flash-freq keep --flash-size keep $c.Boot netspeaker.ino.bootloader.bin 0x8000 netspeaker.ino.partitions.bin 0xe000 boot_app0.bin 0x10000 netspeaker.ino.bin | Out-Host
    }
    catch { Write-Host "esptool: $($_.Exception.Message)" }
    $ok = ($LASTEXITCODE -eq 0)
    Pop-Location
    return $ok
}
$flashOk = Invoke-Flash $num 'default-reset'

# Der S3 hat natives USB: der automatische Reset in den Bootloader laesst den COM-Port verschwinden. Dann den Bootloader von
# Hand starten (Taste 0 halten, RST druecken, Taste 0 loslassen), den neuen Port suchen und ohne Reset flashen.
# The S3 has native USB: the automatic reset into the bootloader makes the COM port disappear. Then start the bootloader
# by hand (hold button 0, press RST, release button 0), find the new port and flash without a reset.
if (-not $flashOk -and $interactive) {
    Write-Host ''
    Write-Host 'Bootloader von Hand starten: Taste 0 gedrueckt halten, kurz RST druecken, Taste 0 loslassen.'
    Write-Host 'Start the bootloader by hand: hold button 0, press RST briefly, release button 0.'
    Read-Host 'Dann Eingabetaste druecken / then press Enter' | Out-Null
    Start-Sleep -Seconds 1
    $ports = @(Get-EspPorts)
    if ($ports.Count -eq 1) {
        $num = $ports[0].Num
        Write-Host "ESP auf / on COM$num"
    }
    else {
        Get-CimInstance Win32_PnPEntity | Where-Object { $_.Name -match '\(COM\d+\)' } | ForEach-Object { Write-Host "  $($_.Name)" }
        $a = Read-Host 'COM-Port Nummer / number (z.B./e.g. 3 = COM3)'
        if ($a) { $num = [int]($a -replace '\D', '') }
    }
    $flashOk = Invoke-Flash $num 'no-reset'
}
if (-not $flashOk) {
    Write-Host ''
    Write-Host 'Flashen fehlgeschlagen - siehe Meldung von esptool. Haeufige Ursachen:'
    Write-Host '  * Boot-Taste halten, erst DANACH USB einstecken, dann erneut starten.'
    Write-Host '  * Port belegt: seriellen Monitor schliessen.  * Nur Ladekabel?'
    Write-Host 'Flashing failed - see the esptool message. Common causes:'
    Write-Host '  * Hold the Boot button, only THEN plug in USB, then start again.'
    Write-Host '  * Port in use: close the serial monitor.  * Charging-only cable?'
    exit 1
}
# 5) WLAN senden / send the WiFi
if ($wifiSsid) {
    $sent = Send-Wifi $wifiSsid $wifiPass
    $wifiPass = $null
    if ($sent) {
        Write-Host "WLAN '$wifiSsid' gespeichert, der ESP startet neu und verbindet sich. / WiFi '$wifiSsid' saved, the ESP restarts and connects."
    }
    else {
        Write-Host 'Keine Bestaetigung vom ESP. WLAN dann im Browser einrichten (Zugangspunkt netspeaker-setup-...). / No confirmation from the ESP. Set up the WiFi in the browser then (access point netspeaker-setup-...).'
        exit 1
    }
}
else {
    Write-Host ''
    Write-Host 'Fertig. WLAN einrichten: Zugangspunkt netspeaker-setup-... im Browser (http://192.168.4.1/) oder erneut flashESP.bat. / Done. Set up the WiFi via the access point netspeaker-setup-... in the browser (http://192.168.4.1/) or flashESP.bat again.'
}
exit 0

# Sucht alle NetSpeaker-Geraete (Sprachausgabe) im Netz und zeigt eine Tabelle: Adresse, Name, Chip, laufende Firmware
# (Build-Zeit) und ob sie dem neuesten Build in build_netspeaker entspricht.
#   .\checkDevices.ps1                       sucht im Netz des PCs (die ersten drei Zahlen seiner Adresse, z. B. 192.168.0.x)
#   .\checkDevices.ps1 -Subnet 192.168.1     anderes Netz
#   .\checkDevices.ps1 -Ip 192.168.0.169     nur diese Adressen (mehrere mit Komma)
#   .\checkDevices.ps1 -PassThru             gibt die Geraete als Objekte zurueck statt als Tabelle (fuer flashAll.ps1)
# Der Soll-Stand ist die Build-Zeit, die in der Datei build_netspeaker\esp32s3\netspeaker.ino.bin steht
# (Kennung VOICE_FW_BUILD=). Aeltere Firmware ohne /api/version zeigt "?".
#
# Finds all NetSpeaker devices (voice output) on the network and shows a table: address, name, chip, running
# firmware (build time) and whether it matches the newest build in build_netspeaker.
#   .\checkDevices.ps1                       searches the PC's network (the first three numbers of its address, e.g. 192.168.0.x)
#   .\checkDevices.ps1 -Subnet 192.168.1     another network
#   .\checkDevices.ps1 -Ip 192.168.0.169     only these addresses (several with comma)
#   .\checkDevices.ps1 -PassThru             returns the devices as objects instead of a table (for flashAll.ps1)
# The target is the build time stored in the file build_netspeaker\esp32s3\netspeaker.ino.bin (marker
# VOICE_FW_BUILD=). Older firmware without /api/version shows "?".

param([string]$Subnet, [string[]]$Ip, [switch]$PassThru)

$ErrorActionPreference = 'SilentlyContinue'

# Mit -File kommt "a,b" als ein Text an - trennen / with -File "a,b" arrives as one string - split it
if ($Ip) { $Ip = @($Ip | ForEach-Object { $_ -split '[,; ]+' } | Where-Object { $_ }) }

# "Oct 19 2026 09:15:00" (__DATE__ __TIME__) -> "2026-10-19 09:15:00"
function ConvertTo-BuildStamp([string]$text) {
    $stamp = ($text -replace '\s+', ' ').Trim()
    try { return [datetime]::ParseExact($stamp, 'MMM d yyyy HH:mm:ss', [System.Globalization.CultureInfo]::InvariantCulture).ToString('yyyy-MM-dd HH:mm:ss') }
    catch { return $null }
}

# Soll-Build je Chip aus den Binaerdateien lesen / read the target build per chip from the binaries
function Get-TargetBuild([string]$chip) {
    $file = Join-Path $PSScriptRoot "build_netspeaker\esp32$chip\netspeaker.ino.bin"
    if (-not (Test-Path $file)) { return $null }
    $text = [System.Text.Encoding]::GetEncoding(28591).GetString([System.IO.File]::ReadAllBytes($file))
    $at = $text.IndexOf('VOICE_FW_BUILD=')
    if ($at -lt 0) { return $null }
    $end = $text.IndexOf([char]0, $at)
    return ConvertTo-BuildStamp $text.Substring($at + 15, $end - $at - 15)
}
$target = @{ S3 = Get-TargetBuild 's3' }

# Netz des PCs bestimmen, falls kein -Subnet angegeben ist
# Determine the PC's network if no -Subnet is given
if (-not $Subnet -and -not $Ip) {
    $route = Get-NetRoute -DestinationPrefix '0.0.0.0/0' | Sort-Object RouteMetric | Select-Object -First 1
    $addr = Get-NetIPAddress -InterfaceIndex $route.InterfaceIndex -AddressFamily IPv4 | Select-Object -First 1
    if (-not $addr) { Write-Host 'Kein Netz gefunden - -Subnet 192.168.0 angeben. / No network found - give -Subnet 192.168.0.'; exit 1 }
    $Subnet = ($addr.IPAddress -split '\.')[0..2] -join '.'
}

# Kandidaten: offene Port-80-Adressen im Netz
# Candidates: addresses with an open port 80 on the network
if (-not $Ip) {
    Write-Host "Suche in / searching $Subnet.1 - $Subnet.254 ..."
    $attempts = 1..254 | ForEach-Object {
        $c = New-Object System.Net.Sockets.TcpClient
        [pscustomobject]@{ Ip = "$Subnet.$_"; Client = $c; Task = $c.ConnectAsync("$Subnet.$_", 80) }
    }
    Start-Sleep -Milliseconds 1500
    $Ip = @($attempts | Where-Object { $_.Task.IsCompleted -and -not $_.Task.IsFaulted -and $_.Client.Connected } | ForEach-Object { $_.Ip })
    $attempts | ForEach-Object { $_.Client.Close() }
}

function Get-Page([string]$url) {
    try {
        $wc = New-Object System.Net.WebClient
        $wc.Encoding = [System.Text.Encoding]::UTF8
        return $wc.DownloadString($url)
    } catch { return $null }
}

# Geraet erkennen am Seitentitel (kein Sonderzeichen im Regex) / recognize the device by the page title (no special character in the regex)
$rows = foreach ($ipAddr in $Ip) {
    $page = Get-Page "http://$ipAddr/"
    if (-not $page -or $page -notmatch '<title>(NetSpeaker|VoiceRSS Player)') { continue }
    $name = [regex]::Match($page, 'class=.host-link. href=.[^''"]*.>([^<]*)').Groups[1].Value
    $chip = [regex]::Match($page, '<td>Chip</td><td>ESP32-([A-Za-z0-9]+)').Groups[1].Value.ToUpper()
    $versionText = Get-Page "http://$ipAddr/api/version"
    $version = if ($versionText) { ConvertTo-BuildStamp $versionText } else { $null }
    $soll = $target[$chip]
    $state = if (-not $soll -or -not $version) { '?' } elseif ($version -eq $soll) { 'aktuell' } elseif ($version -lt $soll) { 'aelter' } else { 'neuer' }
    [pscustomobject]@{ IP = $ipAddr; Name = $name; Chip = $chip; Firmware = $version; Soll = $soll; Stand = $state }
}

if ($PassThru) { return @($rows) }
if (-not $rows) { Write-Host 'Kein NetSpeaker-Geraet gefunden. / No NetSpeaker device found.'; exit 1 }
$rows | Sort-Object IP | Format-Table -AutoSize
Write-Host ('Soll / target:  S3 {0}' -f $target.S3)

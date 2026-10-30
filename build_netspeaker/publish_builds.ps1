# Erzeugt die Pakete fuer das GitHub-Release, die flashESP.bat / voicesetup.ps1 beim Flashen laden:
#   netspeaker-esp32s3.zip      Bootloader, Partitionstabelle, boot_app0.bin und App (flach im Zip)
#   netspeaker-esp32s3.sha256   "<SHA-256>  netspeaker-esp32s3.zip"
#   netspeaker_flash.zip        nur die Werkzeuge: flashESP.bat, voicesetup.ps1, readme.txt und esptool.exe
# Quelle der Firmware ist der Ordner esp32s3 neben diesem Skript (von buildAll.bat erzeugt), esptool.exe liegt neben diesem Skript oder
# stammt aus dem ESP32-Core der Arduino IDE.
#   .\publish_builds.ps1                      Pakete in einen Ordner schreiben (Standard: Temp), nichts hochladen
#   .\publish_builds.ps1 -OutDir C:\test      Zielordner angeben
#   .\publish_builds.ps1 -Upload              zusaetzlich in das neueste Release hochladen (gh, ersetzt vorhandene Dateien)
#   .\publish_builds.ps1 -Upload -Tag v1.3.3  in das Release mit diesem Tag hochladen
# Zum Testen ohne Release: $env:NETSPEAKER_BUILD_URL = 'file:///C:/test' vor flashESP.bat bzw. voicesetup.ps1.
#
# Creates the packages for the GitHub release that flashESP.bat / voicesetup.ps1 download when flashing:
#   netspeaker-esp32s3.zip      bootloader, partition table, boot_app0.bin and app (flat in the zip)
#   netspeaker-esp32s3.sha256   "<SHA-256>  netspeaker-esp32s3.zip"
#   netspeaker_flash.zip        the tools only: flashESP.bat, voicesetup.ps1, readme.txt and esptool.exe
# The firmware comes from the folder esp32s3 next to this script (made by buildAll.bat); esptool.exe is next to this script or comes
# from the ESP32 core of the Arduino IDE.
#   .\publish_builds.ps1                      write the packages to a folder (default: temp), upload nothing
#   .\publish_builds.ps1 -OutDir C:\test      set the target folder
#   .\publish_builds.ps1 -Upload              also upload to the newest release (gh, replaces existing files)
#   .\publish_builds.ps1 -Upload -Tag v1.3.3  upload to the release with this tag
# To test without a release: $env:NETSPEAKER_BUILD_URL = 'file:///C:/test' before flashESP.bat or voicesetup.ps1.

param([string]$OutDir, [switch]$Upload, [string]$Tag)

$ErrorActionPreference = 'Stop'
$repo = 'holgiw/netspeaker'
Add-Type -AssemblyName System.IO.Compression.FileSystem
if (-not $OutDir) { $OutDir = Join-Path ([System.IO.Path]::GetTempPath()) 'netspeaker-packages' }
New-Item -ItemType Directory -Path $OutDir -Force | Out-Null

function New-FlatZip([string]$zipPath, [string[]]$paths) {
    $stage = Join-Path ([System.IO.Path]::GetTempPath()) ('netspeaker-stage-' + [guid]::NewGuid().ToString('N'))
    New-Item -ItemType Directory -Path $stage | Out-Null
    try {
        foreach ($p in $paths) { Copy-Item -LiteralPath $p -Destination $stage }
        if (Test-Path $zipPath) { Remove-Item $zipPath -Force }
        [System.IO.Compression.ZipFile]::CreateFromDirectory($stage, $zipPath)
    }
    finally { Remove-Item $stage -Recurse -Force -ErrorAction SilentlyContinue }
}

# 1) Firmware-Paket / firmware package
$src = Join-Path $PSScriptRoot 'esp32s3'
$parts = @('netspeaker.ino.bootloader.bin', 'netspeaker.ino.partitions.bin', 'boot_app0.bin', 'netspeaker.ino.bin')
$lack = $parts | Where-Object { -not (Test-Path (Join-Path $src $_)) }
if ($lack) { throw "Fehlende Dateien / missing files in ${src}: $($lack -join ', ') - zuerst buildAll.bat / run buildAll.bat first" }
$fwZip = Join-Path $OutDir 'netspeaker-esp32s3.zip'
New-FlatZip $fwZip ($parts | ForEach-Object { Join-Path $src $_ })
$hash = (Get-FileHash -Algorithm SHA256 $fwZip).Hash.ToLower()
$shaFile = Join-Path $OutDir 'netspeaker-esp32s3.sha256'
[System.IO.File]::WriteAllText($shaFile, "$hash  netspeaker-esp32s3.zip`n", (New-Object System.Text.UTF8Encoding($false)))
Write-Host "netspeaker-esp32s3.zip  $((Get-Item $fwZip).Length) Bytes, SHA-256 $hash"

# 2) Werkzeug-Paket / tools package
$esptool = Join-Path $PSScriptRoot 'esptool.exe'
if (-not (Test-Path $esptool)) {
    $core = Get-ChildItem "$env:LOCALAPPDATA\Arduino15\packages\esp32\tools\esptool_py\*\esptool.exe" -ErrorAction SilentlyContinue | Sort-Object FullName | Select-Object -Last 1
    if ($core) { $esptool = $core.FullName }
}
if (-not (Test-Path $esptool)) { throw 'esptool.exe nicht gefunden / not found' }
$toolsZip = Join-Path $OutDir 'netspeaker_flash.zip'
New-FlatZip $toolsZip @((Join-Path $PSScriptRoot 'flashESP.bat'), (Join-Path $PSScriptRoot 'voicesetup.ps1'), (Join-Path $PSScriptRoot 'readme.txt'), $esptool)
Write-Host "netspeaker_flash.zip    $((Get-Item $toolsZip).Length) Bytes (esptool.exe: $esptool)"

# 3) Hochladen / upload
if ($Upload) {
    if (-not $Tag) { $Tag = (& gh release view --repo $repo --json tagName -q .tagName).Trim() }
    if (-not $Tag) { throw 'Kein Release gefunden / no release found' }
    Write-Host "Lade in das Release $Tag hoch / uploading to release $Tag ..."
    & gh release upload $Tag $fwZip $shaFile $toolsZip --repo $repo --clobber
    if ($LASTEXITCODE -ne 0) { throw 'gh release upload fehlgeschlagen / failed' }
}
else {
    Write-Host "Pakete in / packages in $OutDir (nichts hochgeladen / nothing uploaded)"
}

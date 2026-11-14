# Erzeugt lang_en_json.h aus lang/en.json, damit die englische Uebersetzung in der Firmware steckt.
# Wird von buildAll.bat vor jedem Build aufgerufen; die Uebersetzung wird nur in lang/en.json gepflegt.
#
# Creates lang_en_json.h from lang/en.json so the English translation is part of the firmware.
# Called by buildAll.bat before every build; the translation is maintained only in lang/en.json.
Set-Location $PSScriptRoot

$json = [IO.File]::ReadAllText("$PSScriptRoot\lang\en.json", [Text.Encoding]::UTF8).Replace("`r`n", "`n").TrimEnd()
if ($json.Contains(')lang"')) { throw "lang/en.json contains the raw string terminator" }
$null = $json | ConvertFrom-Json   # muss gueltiges JSON sein / must be valid JSON
$head = "// Automatisch aus lang/en.json erzeugt (makeLangHeader.ps1, von buildAll.bat aufgerufen); nicht von Hand aendern.`n// Generated automatically from lang/en.json (makeLangHeader.ps1, called by buildAll.bat); do not edit by hand.`n`n#pragma once`n`n"
$text = $head + 'static const char LANG_EN_JSON[] PROGMEM = R"lang(' + $json + ')lang";' + "`n"
$path = "$PSScriptRoot\lang_en_json.h"
$old = if (Test-Path $path) { [IO.File]::ReadAllText($path) } else { '' }
if ($old -ne $text) { [IO.File]::WriteAllText($path, $text, (New-Object Text.UTF8Encoding($false))); "lang_en_json.h updated" } else { "lang_en_json.h up to date" }

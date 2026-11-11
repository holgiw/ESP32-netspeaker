# Erzeugt wiring_svg.h (aus verkabelung.svg) und wiring_view_svg.h (aus verkabelung_ansicht.svg), damit beide Verkabelungsbilder im Tab Doku der Weboberflaeche erscheinen.
# Wird von buildAll.bat vor jedem Build aufgerufen; die Bilder werden nur in den .svg-Dateien gepflegt.
#
# Creates wiring_svg.h (from verkabelung.svg) and wiring_view_svg.h (from verkabelung_ansicht.svg) so that both wiring pictures appear in the Doku tab of the web interface.
# Called by buildAll.bat before every build; the pictures are maintained only in the .svg files.
Set-Location $PSScriptRoot

function Convert-Svg([string]$source, [string]$target, [string]$name, [string]$style) {
    $svg = [IO.File]::ReadAllText("$PSScriptRoot\$source", [Text.Encoding]::UTF8).Replace("`r`n", "`n")

    # Feste Groesse entfernen, damit sich das Bild der Seitenbreite anpasst.
    # Remove the fixed size so the picture adapts to the page width.
    $svg = ([regex]::new('<svg ([^>]*?)width="\d+" height="\d+" ')).Replace($svg, '<svg $1style="' + $style + '" ', 1)
    if ($svg.Contains(')svg"')) { throw "$source contains the raw string terminator" }
    $head = "// Automatisch aus $source erzeugt (makeWiringHeader.ps1, von buildAll.bat aufgerufen); nicht von Hand aendern.`n// Generated automatically from $source (makeWiringHeader.ps1, called by buildAll.bat); do not edit by hand.`n`n#pragma once`n`n"
    $text = $head + "static const char $name[] PROGMEM = R`"svg(" + $svg.TrimEnd() + ')svg";' + "`n"
    $path = "$PSScriptRoot\$target"
    $old = if (Test-Path $path) { [IO.File]::ReadAllText($path) } else { '' }
    if ($old -ne $text) { [IO.File]::WriteAllText($path, $text, (New-Object Text.UTF8Encoding($false))); "$target updated" } else { "$target up to date" }
}

Convert-Svg 'verkabelung.svg' 'wiring_svg.h' 'WIRING_SVG' 'width:100%;height:auto;max-width:960px;display:block;margin:0 auto'
Convert-Svg 'verkabelung_ansicht.svg' 'wiring_view_svg.h' 'WIRING_VIEW_SVG' 'width:100%;min-width:900px;height:auto;max-width:1500px;display:block;margin:0 auto'

param(
    [Parameter(Mandatory=$true)]
    [string]$ARCH,

    [Parameter(Mandatory=$true)]
    [string]$RACKET
)

$ErrorActionPreference = "Stop"

$ROOT = Split-Path -Parent (Split-Path -Parent $MyInvocation.MyCommand.Path)

cp "$RACKET\include\chezscheme.h" "$ROOT\Lib\include\chezscheme-$ARCH.h"
cp "$RACKET\include\racketcsboot.h" "$ROOT\Lib\include\racketcsboot.h"
cp "$RACKET\include\racketcs.h" "$ROOT\Lib\include\racketcs.h"

# Copy DLL (Windows DLLs have version in filename, e.g., libracketcs8.10.dll)
$DLL = Get-ChildItem "$RACKET\lib\libracketcs*.dll" | Select-Object -First 1
if ($DLL) {
    cp $DLL.FullName "$ROOT\Lib\libracketcs-$ARCH.dll"
}

switch ($ARCH) {
    {$_ -in @("x86_64-windows", "arm64-windows")} {
        $DEST = "$ROOT\Sources\NoiseBoot.Windows\boot\$ARCH"
        mkdir -f $DEST | Out-Null
        cp "$RACKET\lib\petite.boot" "$DEST\petite.boot"
        cp "$RACKET\lib\scheme.boot" "$DEST\scheme.boot"
        cp "$RACKET\lib\racket.boot" "$DEST\racket.boot"
    }
    default {
        Write-Host "warning: boot files ignored for $ARCH"
    }
}

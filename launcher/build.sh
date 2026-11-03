#!/bin/sh
set -e
cd "$(dirname "$0")"
i686-w64-mingw32-windres launcher.rc -O coff -o launcher.res
i686-w64-mingw32-gcc -O2 -s -municode -mwindows -nostdlib -e _entry@0 \
    -o "RDWorksV8 Portable.exe" launcher.c launcher.res \
    -lshlwapi -ladvapi32 -luser32 -lkernel32

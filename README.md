# RDWorks V8 Portable

RDWorks V8 8.01.54 for Windows.

## Use

1. Download `RDWorksV8-Portable.zip` from [Releases](../../releases).
2. Unzip it anywhere except Program Files.
3. Run `RDWorksV8 Portable.exe`.

Over USB the controller needs the FTDI driver. Windows 10 and 11 usually install it when you plug the machine in. If they don't, run `DPInst64.exe` from `USB Driver (optional)` (this one asks for admin).

## Build

```sh
./launcher/build.sh
```

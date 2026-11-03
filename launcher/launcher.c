#include <windows.h>
#include <shlwapi.h>

static void set_str(const wchar_t *key, const wchar_t *name, const wchar_t *val)
{
    HKEY k;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, key, 0, NULL, 0, KEY_SET_VALUE, NULL, &k, NULL) != ERROR_SUCCESS)
        return;
    RegSetValueExW(k, name, 0, REG_SZ, (const BYTE *)val, (DWORD)((lstrlenW(val) + 1) * sizeof(wchar_t)));
    RegCloseKey(k);
}

int WINAPI wWinMain(HINSTANCE inst, HINSTANCE prev, PWSTR cmd, int show)
{
    wchar_t base[MAX_PATH], app_dir[MAX_PATH], exe[MAX_PATH], rdimage[MAX_PATH];
    wchar_t cmdline[MAX_PATH * 2 + 8];
    STARTUPINFOW si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    GetModuleFileNameW(NULL, base, MAX_PATH);
    PathRemoveFileSpecW(base);
    PathCombineW(app_dir, base, L"RDWorksV8");
    PathCombineW(exe, app_dir, L"RDWorksV8.exe");
    PathCombineW(rdimage, app_dir, L"RDImage\\");

    if (GetFileAttributesW(exe) == INVALID_FILE_ATTRIBUTES) {
        MessageBoxW(NULL, L"No se encuentra RDWorksV8\\RDWorksV8.exe al lado de este programa.",
                    L"RDWorksV8 Portable", MB_ICONERROR);
        return 1;
    }

    // The installer writes these under HKLM; HKCU\Software\Classes is merged into HKCR without admin
    set_str(L"Software\\Classes\\rdbfile\\shell\\open\\OtherPath\\OtherSoftPath", NULL, exe);
    set_str(L"Software\\Classes\\rdbfile\\shell\\open\\RDImagePath", L"RDImagePath", rdimage);
    set_str(L"Software\\RDSOFT", L"ExePath", exe);

    wsprintfW(cmdline, L"\"%s\" %s", exe, cmd ? cmd : L"");
    if (!CreateProcessW(exe, cmdline, NULL, NULL, FALSE, 0, NULL, app_dir, &si, &pi)) {
        MessageBoxW(NULL, L"No se pudo iniciar RDWorksV8.exe.", L"RDWorksV8 Portable", MB_ICONERROR);
        return 1;
    }
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return 0;
}

void __stdcall entry(void)
{
    ExitProcess(wWinMain(GetModuleHandleW(NULL), NULL, PathGetArgsW(GetCommandLineW()), SW_SHOWNORMAL));
}

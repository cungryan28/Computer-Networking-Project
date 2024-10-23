#pragma once

#include <windows.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "advapi32.lib")

namespace WinAPI {
    BOOL MySystemShutdown();
    BOOL MySystemRestart(LPWSTR lpMsg);
}
#include "LinkSwitcher.h"
#include <cstdio>

int wmain(int argc, wchar_t** argv) {
    std::optional<std::wstring> profile = std::nullopt;
    switch (argc) {
        case 2:
            break;
        case 3:
            profile = argv[2];
            break;
        default:
            wprintf_s(L"Usage: %s <key> [profile]\n", argv[0]);
            return 1;
    }
    LinkSwitcher switcher(profile);
    if (!switcher.SwitchTo(argv[1])) {
        wprintf_s(L"Failed to switch to %s\n", argv[1]);
        return 1;
    }
    return 0;
}

#include "Profile.h"
#include "PathUtil.h"
#include <Windows.h>

std::optional<std::wstring> Profile::InternalReadString(const std::wstring& fileName, const std::wstring* appName, const std::wstring* keyName) noexcept {
    std::optional<std::wstring> fullFileName = PathUtil::GetFullPath(fileName);
    if (!fullFileName) {
        return std::nullopt;
    }
    std::wstring buffer(0x1F, 0);
    for (uint32_t size = 0x20; size < 0x10000; size += 0x20) {
        buffer.resize(static_cast<size_t>(size) - 1);
        uint32_t result = ::GetPrivateProfileStringW(appName ? appName->data() : nullptr, keyName ? keyName->data() : nullptr, nullptr, buffer.data(), size, fullFileName->data());
        if (GetLastError() == ERROR_FILE_NOT_FOUND || buffer.empty()) {
            return std::nullopt;
        }
        if (appName && keyName) {
            if (result == size - 1) {
                continue;
            }
        } else {
            if (result == size - 2) {
                continue;
            }
        }
        buffer.resize(result);
        break;
    }
    return buffer;
}

std::optional<std::vector<std::wstring>> Profile::InternalReadNames(const std::wstring& fileName, const std::wstring* appName) noexcept {
    std::optional<std::wstring> sections = InternalReadString(fileName, appName, nullptr);
    if (!sections) {
        return std::nullopt;
    }
    std::vector<std::wstring> result;
    size_t size = 0;
    while (size < sections->size()) {
        wchar_t* data = sections->data() + size;
        size_t length = std::wcslen(data);
        size += length + 1;
        result.emplace_back(std::wstring(data, length));
    }
    return result;
}

std::optional<std::vector<std::wstring>> Profile::ReadSections(const std::wstring& fileName) noexcept {
    return InternalReadNames(fileName, nullptr);
}

std::optional<std::vector<std::wstring>> Profile::ReadKeys(const std::wstring& fileName, const std::wstring& appName) noexcept {
    if (appName.empty()) {
        return std::nullopt;
    }
    return InternalReadNames(fileName, &appName);
}

std::optional<std::wstring> Profile::ReadString(const std::wstring& fileName, const std::wstring& appName, const std::wstring& keyName) noexcept {
    if (appName.empty() || keyName.empty() || fileName.empty()) {
        return std::nullopt;
    }
    return InternalReadString(fileName, &appName, &keyName);
}

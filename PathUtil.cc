#include "PathUtil.h"
#include <Windows.h>
#include <Shlwapi.h>

std::wstring PathUtil::GetParent(const std::wstring& path) noexcept {
    std::wstring buffer(path);
    ::PathRemoveFileSpecW(buffer.data());
    buffer.resize(buffer.find((wchar_t) 0));
    return buffer;
}

std::optional<std::wstring> PathUtil::GetFullPath(const std::wstring& path) noexcept {
    DWORD bufferSize = ::GetFullPathNameW(path.data(), 0, nullptr, nullptr);
    if (bufferSize == 0) {
        return std::nullopt;
    }
    std::wstring buffer(bufferSize, 0);
    if (!::GetFullPathNameW(path.data(), bufferSize, buffer.data(), nullptr)) {
        return std::nullopt;
    }
    buffer.resize(buffer.size() - 1);
    return buffer;
}

std::optional<size_t> PathUtil::FindExtension(const std::wstring& path) noexcept {
    wchar_t* extension = ::PathFindExtensionW(path.data());
    if (!*extension) {
        return std::nullopt;
    }
    return extension - path.data();
}

std::optional<std::wstring> PathUtil::Combine(const std::wstring& pathIn, const std::wstring& pathMore) noexcept {
    std::wstring buffer(MAX_PATH, 0);
    if (!::PathCombineW(buffer.data(), pathIn.data(), pathMore.data())) {
        return std::nullopt;
    }
    buffer.resize(buffer.find((wchar_t) 0));
    return buffer;
}

std::optional<std::wstring> PathUtil::GetProgramFileName() noexcept {
    std::wstring buffer(MAX_PATH, 0);
    DWORD retSize = ::GetModuleFileNameW(nullptr, buffer.data(), MAX_PATH);
    if (retSize == 0 || retSize == MAX_PATH) {
        return std::nullopt;
    }
    buffer.resize(retSize);
    return buffer;
}

std::optional<std::wstring> PathUtil::GetProgramBasePath() noexcept {
    std::optional<std::wstring> programFileName = GetProgramFileName();
    if (!programFileName) {
        return std::nullopt;
    }
    return PathUtil::GetParent(*programFileName);
}

#pragma once
#include <optional>
#include <string>

class PathUtil {
public:
    static std::wstring GetParent(const std::wstring& path) noexcept;
    static std::optional<std::wstring> GetFullPath(const std::wstring& path) noexcept;
    static std::optional<size_t> FindExtension(const std::wstring& path) noexcept;
    static std::optional<std::wstring> Combine(const std::wstring& pathIn, const std::wstring& pathMore) noexcept;
    static std::optional<std::wstring> GetProgramFileName() noexcept;
    static std::optional<std::wstring> GetProgramBasePath() noexcept;
};

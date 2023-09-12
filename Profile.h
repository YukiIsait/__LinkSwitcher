#pragma once
#include <optional>
#include <vector>
#include <string>

class Profile {
private:
    static std::optional<std::wstring> InternalReadString(const std::wstring& fileName, const std::wstring* appName, const std::wstring* keyName) noexcept;
    static std::optional<std::vector<std::wstring>> InternalReadNames(const std::wstring& fileName, const std::wstring* appName) noexcept;

public:
    static std::optional<std::vector<std::wstring>> ReadSections(const std::wstring& fileName) noexcept;
    static std::optional<std::vector<std::wstring>> ReadKeys(const std::wstring& fileName, const std::wstring& appName) noexcept;
    static std::optional<std::wstring> ReadString(const std::wstring& fileName, const std::wstring& appName, const std::wstring& keyName) noexcept;

private:
    std::wstring fileName;

public:
    Profile() noexcept;
    Profile(const std::wstring& fileName) noexcept;
    Profile(std::wstring&& fileName) noexcept;
    Profile(const Profile& other) noexcept;
    Profile(Profile&& other) noexcept;

    Profile& operator=(const Profile& other) noexcept;
    Profile& operator=(Profile&& other) noexcept;

    std::wstring& operator*() noexcept;

    std::optional<std::vector<std::wstring>> ReadSections() const noexcept;
    std::optional<std::vector<std::wstring>> ReadKeys(const std::wstring& appName) const noexcept;
    std::optional<std::wstring> ReadString(const std::wstring& appName, const std::wstring& keyName) const noexcept;
};

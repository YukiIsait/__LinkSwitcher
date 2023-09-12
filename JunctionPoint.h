#pragma once
#include <optional>
#include <string>

class JunctionPoint {
public:
    static bool Mount(const std::wstring& junctionPoint, const std::wstring& targetDir) noexcept;
    static bool Create(const std::wstring& junctionPoint, const std::wstring& targetDir) noexcept;
    static bool Unmount(const std::wstring& junctionPoint) noexcept;
    static bool Delete(const std::wstring& junctionPoint) noexcept;
    static std::optional<bool> IsJunctionPoint(const std::wstring& path) noexcept;

private:
    std::wstring junctionPoint;

public:
    JunctionPoint() noexcept;
    JunctionPoint(const std::wstring& junctionPoint) noexcept;
    JunctionPoint(std::wstring&& junctionPoint) noexcept;
    JunctionPoint(const JunctionPoint& other) noexcept;
    JunctionPoint(JunctionPoint&& other) noexcept;

    JunctionPoint& operator=(const JunctionPoint& other) noexcept;
    JunctionPoint& operator=(JunctionPoint&& other) noexcept;

    std::wstring& operator*() noexcept;

    bool MountFor(const std::wstring& targetDir) const noexcept;
    bool CreateFor(const std::wstring& targetDir) const noexcept;
    bool Unmount() const noexcept;
    bool Delete() const noexcept;
    bool RemountFor(const std::wstring& targetDir) const noexcept;
};

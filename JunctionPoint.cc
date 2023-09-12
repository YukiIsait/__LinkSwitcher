#include "JunctionPoint.h"

JunctionPoint::JunctionPoint() noexcept {}

JunctionPoint::JunctionPoint(const std::wstring& junctionPoint) noexcept: junctionPoint(junctionPoint) {}

JunctionPoint::JunctionPoint(std::wstring&& junctionPoint) noexcept: junctionPoint(std::move(junctionPoint)) {}

JunctionPoint::JunctionPoint(const JunctionPoint& other) noexcept: junctionPoint(other.junctionPoint) {}

JunctionPoint::JunctionPoint(JunctionPoint&& other) noexcept: junctionPoint(std::move(other.junctionPoint)) {}

JunctionPoint& JunctionPoint::operator=(const JunctionPoint& other) noexcept {
    if (this == &other) {
        return *this;
    }
    junctionPoint = other.junctionPoint;
    return *this;
}

JunctionPoint& JunctionPoint::operator=(JunctionPoint&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    junctionPoint = std::move(other.junctionPoint);
    return *this;
}

std::wstring& JunctionPoint::operator*() noexcept {
    return junctionPoint;
}

bool JunctionPoint::MountFor(const std::wstring& targetDir) const noexcept {
    return JunctionPoint::Mount(junctionPoint, targetDir);
}

bool JunctionPoint::CreateFor(const std::wstring& targetDir) const noexcept {
    return JunctionPoint::Create(junctionPoint, targetDir);
}

bool JunctionPoint::Unmount() const noexcept {
    return JunctionPoint::Unmount(junctionPoint);
}

bool JunctionPoint::Delete() const noexcept {
    return JunctionPoint::Delete(junctionPoint);
}

bool JunctionPoint::RemountFor(const std::wstring& targetDir) const noexcept {
    if (!Unmount()) {
        return false;
    }
    return MountFor(targetDir);
}

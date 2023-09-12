#pragma once
#include "JunctionPoint.h"
#include "Profile.h"
#include <optional>
#include <string>

class LinkSwitcher {
private:
    Profile profile;
    JunctionPoint link;
    std::optional<std::wstring> basePath;

public:
    explicit LinkSwitcher() noexcept;
    explicit LinkSwitcher(const std::optional<std::reference_wrapper<const std::wstring>> profileName) noexcept;
    bool SwitchTo(const std::wstring& key) const noexcept;
};

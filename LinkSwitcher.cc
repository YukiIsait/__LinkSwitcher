#include "LinkSwitcher.h"
#include "PathUtil.h"

LinkSwitcher::LinkSwitcher() noexcept: LinkSwitcher(std::nullopt) {}

LinkSwitcher::LinkSwitcher(const std::optional<std::reference_wrapper<const std::wstring>> profileName) noexcept: basePath(PathUtil::GetProgramBasePath()) {
    if (!basePath) {
        return;
    }
    if (profileName) {
        std::optional<std::wstring> profileFullPath = PathUtil::Combine(*basePath, *profileName);
        if (profileFullPath) {
            *profile = std::move(*profileFullPath);
        }
    } else {
        std::optional<std::wstring> programFileName = PathUtil::GetProgramFileName();
        if (programFileName) {
            *profile = std::move(programFileName->replace(PathUtil::FindExtension(*programFileName).value_or(programFileName->size()), 4, L".ini"));
        }
    }
    std::optional<std::wstring> profileBasePath = profile.ReadString(L"App", L"Base");
    if (profileBasePath) {
        basePath = PathUtil::Combine(*basePath, *profileBasePath);
        if (!basePath) {
            return;
        }
    }
    std::optional<std::wstring> profileLinkPath = profile.ReadString(L"App", L"Link");
    std::optional<std::wstring> linkPath;
    if (profileLinkPath) {
        linkPath = PathUtil::Combine(*basePath, *profileLinkPath);
    } else {
        linkPath = PathUtil::Combine(*basePath, L"Current");
    }
    if (linkPath) {
        *link = std::move(*linkPath);
    }
}

bool LinkSwitcher::SwitchTo(const std::wstring& key) const noexcept {
    std::optional<std::wstring> target = profile.ReadString(L"Items", key);
    if (!target) {
        return false;
    }
    std::optional<std::wstring> targetFullPath = PathUtil::Combine(*basePath, *target);
    if (!targetFullPath) {
        return false;
    }
    if (!link.RemountFor(*targetFullPath)) {
        return link.CreateFor(*targetFullPath);
    }
    return true;
}

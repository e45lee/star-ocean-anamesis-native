#pragma once
// Guest (Android) path -> host path translation.
#include <string>

namespace soa {

constexpr const char* kPackageName = "com.square_enix.android_googleplay.StarOceanj";

struct VfsConfig {
    std::string root;  // host directory holding all per-user game data
};

void vfs_init(const VfsConfig& cfg);
const VfsConfig& vfs_config();

// Guest-visible directories (Android paths, as seen by the game).
std::string guest_internal_dir();  // /data/data/<pkg>/files
std::string guest_external_dir();  // /storage/emulated/0/Android/data/<pkg>/files
std::string guest_cache_dir();

// Host directory for the SharedPreferences XML files.
std::string host_shared_prefs_dir();

// Translates a guest path to the host path it's stored at. Paths outside the known
// Android prefixes map into <root>/rootfs so the game can't touch the host filesystem.
std::string host_path(const char* guest_path);

// mkdir -p
bool make_dirs(const std::string& host_dir);

}  // namespace soa

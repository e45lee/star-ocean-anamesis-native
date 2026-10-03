#include "core/vfs.h"

#include <sys/stat.h>

#include <cstdio>
#include <cstring>
#include <vector>

#include "core/device.h"
#include "core/log.h"

namespace soa {

namespace {
VfsConfig g_cfg;

struct Prefix {
    std::string guest, host;
};
std::vector<Prefix> g_prefixes;

bool starts_with(const std::string& s, const std::string& p) { return s.compare(0, p.size(), p) == 0; }
}  // namespace

void vfs_init(const VfsConfig& cfg) {
    g_cfg = cfg;
    std::string pkg = kPackageName;
    const std::string data = cfg.root + "/data";
    const std::string sd = cfg.root + "/sdcard";
    g_prefixes = {
        {"/data/data/" + pkg, data},
        {"/data/user/0/" + pkg, data},
        {"/storage/emulated/0", sd},
        {"/sdcard", sd},
        {"/mnt/sdcard", sd},
    };
    make_dirs(data + "/files");
    make_dirs(data + "/cache");
    make_dirs(data + "/shared_prefs");
    make_dirs(sd + "/Android/data/" + pkg + "/files");
    make_dirs(cfg.root + "/rootfs");
}

const VfsConfig& vfs_config() { return g_cfg; }

std::string guest_internal_dir() { return std::string("/data/data/") + kPackageName + "/files"; }
std::string guest_external_dir() { return std::string("/storage/emulated/0/Android/data/") + kPackageName + "/files"; }
std::string guest_cache_dir() { return std::string("/data/data/") + kPackageName + "/cache"; }
std::string host_shared_prefs_dir() { return g_cfg.root + "/data/shared_prefs"; }

std::string host_path(const char* gp) {
    if (!gp) return {};
    std::string p = gp;
    if (p.empty()) return p;
    if (p[0] != '/') return g_cfg.root + "/rootfs/" + p;
    for (auto& pre : g_prefixes) {
        if (starts_with(p, pre.guest) && (p.size() == pre.guest.size() || p[pre.guest.size()] == '/'))
            return pre.host + p.substr(pre.guest.size());
    }
    // The emulated device's CPU list (device_config().guest_cpus): android_getCpuCount reads it.
    if ((p == "/sys/devices/system/cpu/present" || p == "/sys/devices/system/cpu/possible") && device_config().guest_cpus > 0) {
        std::string dir = g_cfg.root + "/rootfs/sys/devices/system/cpu", hp = g_cfg.root + "/rootfs" + p;
        make_dirs(dir);
        if (FILE* f = fopen(hp.c_str(), "w")) {
            int n = device_config().guest_cpus;
            if (n == 1) fprintf(f, "0\n");
            else fprintf(f, "0-%d\n", n - 1);
            fclose(f);
        }
        return hp;
    }
    if (starts_with(p, "/proc/") || p == "/dev/urandom" || p == "/dev/random" || p == "/dev/null" || starts_with(p, "/sys/devices/system/cpu"))
        return p;
    return g_cfg.root + "/rootfs" + p;
}

bool make_dirs(const std::string& dir) {
    std::string cur;
    for (size_t i = 0; i < dir.size(); i++) {
        cur.push_back(dir[i]);
        if ((dir[i] == '/' && i > 0) || i + 1 == dir.size()) mkdir(cur.c_str(), 0755);
    }
    struct stat st;
    return stat(dir.c_str(), &st) == 0 && S_ISDIR(st.st_mode);
}

}  // namespace soa

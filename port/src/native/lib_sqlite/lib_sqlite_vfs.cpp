// The guest-path VFS: the host's default VFS ("unix" / "win32") with xFullPathname translating the
// guest's Android path (sqlite3_open's file name, ATTACH DATABASE '<path>') to the host path the
// guest's own file I/O uses (core/vfs.h host_path, as the HLE open / fopen do). Everything else is the
// default VFS's: the names SQLite derives (journals, WAL) are made from the translated full path.
#include <mutex>
#include <string>

#include "core/log.h"
#include "core/vfs.h"
#include "native/lib_sqlite/lib_sqlite.h"

namespace soa::native::lib_sqlite {
namespace {

sqlite3_vfs g_vfs;
sqlite3_vfs* g_base = nullptr;

int full_pathname(sqlite3_vfs*, const char* name, int n_out, char* out) {
    std::string host = host_path(name);
    return g_base->xFullPathname(g_base, host.c_str(), n_out, out);
}

}  // namespace

const char* guest_vfs_name() { return "soa-guest"; }

void register_guest_vfs() {
    static std::once_flag once;
    std::call_once(once, [] {
        g_base = sqlite3_vfs_find(nullptr);
        g_vfs = *g_base;
        g_vfs.zName = guest_vfs_name();
        g_vfs.pNext = nullptr;
        g_vfs.xFullPathname = full_pathname;
        int rc = sqlite3_vfs_register(&g_vfs, 0);
        if (rc != SQLITE_OK) LOGE("lib_sqlite", "sqlite3_vfs_register: %d", rc);
    });
}

}  // namespace soa::native::lib_sqlite

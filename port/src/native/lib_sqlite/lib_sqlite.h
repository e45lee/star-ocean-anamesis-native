// lib_sqlite.h: the `lib_sqlite` subsystem's public header. The game's bundled SQLite 3.13.0 is replaced
// by the host SQLite (vcpkg's sqlite3) at the API boundary the game calls (README.md: the boundary, the
// bridged arguments, the live check).
#pragma once

#include <sqlite3.h>

#include "core/abi.h"

namespace soa::native::lib_sqlite {

// The bound sqlite3_* API (every function the game's own code calls, plus sqlite3_free), in the order of
// the README's natives table. X(name) per function.
#define SOA_SQLITE_API(X)                                                                                           \
    X(open) X(close) X(exec) X(prepare_v2) X(errmsg) X(bind_parameter_count) X(bind_text) X(step) X(reset)        \
        X(finalize) X(column_count) X(column_name) X(column_value) X(value_type) X(value_int) X(value_int64)       \
            X(value_double) X(value_text) X(value_blob) X(value_bytes) X(free)

// Guest-callable addresses of the API: the guest's own SQLite (guest_api) or thunks to the natives
// (native_api). The differential tests drive both through the same code.
struct Api {
#define SOA_SQLITE_FIELD(n) u64 n = 0;
    SOA_SQLITE_API(SOA_SQLITE_FIELD)
#undef SOA_SQLITE_FIELD
};
Api guest_api();   // the guest's sqlite3_* symbols (the original code while natives aren't installed)
Api native_api();  // make_thunk()s of the natives (the guest ABI, the same HostFns the hooks install)

// The host VFS that maps the guest's Android paths to host paths (core/vfs.h host_path): every database the
// natives open uses it (an ATTACH inherits the connection's VFS). Registered on first use.
const char* guest_vfs_name();
void register_guest_vfs();

// The live check (soa --live-check lib_sqlite, lib_sqlite_api.cpp): its counters, and its switch (tests).
void live_counts(u64* checks, u64* mismatches, u64* skipped);
void live_switch(bool on);

}  // namespace soa::native::lib_sqlite

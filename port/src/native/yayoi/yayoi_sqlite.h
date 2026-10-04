// yayoi_sqlite.h: the `yayoi` subsystem's SQLite driver family (Aska::Yayoi::SQLiteDriver, its
// EntityObject and the column map): natives that call the host SQLite directly (README.md "The SQLite
// driver"). The classes are in yayoi_layout.h; this header has the family's shared helpers, the
// HostFns the hooks install (the differential tests call them through thunks) and the live check's
// switches.
#pragma once

#include "core/abi.h"
#include "native/yayoi/yayoi_layout.h"

namespace soa::native::yayoi {

// FCVTPU (float -> u64 toward +infinity, NaN / <= -1 -> 0, saturating): the maps' growth arithmetic
// ((size + deleted + n) / maxLoad, rounded up).
u64 fcvtpu(float f);
// The column map's guest vtable (_ZTVN4Aska8THashMapIPKci...EE + 0x10).
const void* column_map_vtable();

// The family's natives: guest symbol, the HostFn (guest ABI: x0 this, x8 the Status), its label.
struct DriverNative {
    const char* sym;
    HostFn fn;
    const char* label;
};
// Every bound function, in the README's table order.
const DriverNative* driver_natives(size_t* n);
// A thunk (make_thunk) of the native bound at `sym`: guest-callable, for the differential tests.
u64 driver_native_thunk(const char* sym);

// The live check (soa --live-check yayoi_sqlite; yayoi_sqlite_live.cpp): its counters and its switch.
void driver_live_counts(u64* checks, u64* mismatches, u64* skipped);
void driver_live_switch(bool on);

}  // namespace soa::native::yayoi

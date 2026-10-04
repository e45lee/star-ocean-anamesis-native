// yayoi_sqlite_live.h: the SQLite driver family's live check, a shadow run (soa --live-check
// yayoi_sqlite; yayoi_sqlite_live.cpp). Internal to the family: the hooks (yayoi_sqlite_hooks.cpp)
// describe each bound function here and call before() / after() around the native.
//
// Every SQLiteDriver and EntityObject the game constructs gets a shadow object driven by the guest's
// own code (the hooks' trampolines to the originals): each call to a native is repeated on the shadow
// with the same arguments (the family's objects and out-buffers swapped for the shadow's), and the
// results, the out-values and the objects' states must match. The shadow driver opens its own
// connection (through lib_sqlite's natives: the host SQLite), so it sees the same data; inside a shadow
// call the guest's calls to the family's functions (Find -> _Execute -> _Prepare, Get*(name) ->
// Rehash_ / Emplace_) run the originals (t_shadow).
#pragma once

#include <vector>

#include "core/cpu.h"

namespace soa::native::yayoi::live {

enum Fn : int {
    kDriverCtor, kDriverDtor, kOpen, kDoOpen, kClose, kBeginTransaction, k_BeginTransaction, kCommit, kRollback,
    kExecute, k_Execute, kFind, k_Prepare,
    kEntityCtor, kEntityDtor, kRelease, kClearCache, kCreateCacheBuffer, kGetCacheBuffer, kStore, kFetch,
    kGetTypeIndex, kGetTypeName, kGetFieldLength, kGetStringLength,
    kGetTimeIndex, kGetTimeName, kGetDataIndex, kGetDataName, kGetStringIndex, kGetStringName,
    kGetTinyIntIndex, kGetTinyIntName, kGetShortIndex, kGetShortName, kGetIntegerIndex, kGetIntegerName,
    kGetLongIndex, kGetLongName, kGetFloatIndex, kGetFloatName, kGetDoubleIndex, kGetDoubleName,
    kSerialize, kSerializeCache,
    kMapDtor, kMapDtorDelete, kMapEmplace, kMapInsert_, kMapRehash, kMapInsertRange,
    kFnCount
};

// What a function's x0 is, what it returns, which out-parameters it writes.
enum class Obj : u8 { Driver, Entity, Map };
enum class Ret : u8 { Status, Int, Ptr, U64, Void, Shared, InsertResult };
enum class Out : u8 {
    None,
    Value,      // x2: one value of `bytes` (the typed getters)
    U64At1,     // x1: a u64 (GetCacheBuffer)
    U64At2,     // x2: a u64 (GetStringLength)
    I32At2,     // x2: an int (_Prepare)
    Text,       // x2 buffer, x3 its size (u64*): GetString / GetTime (the buffer as it was, *size bytes)
    Data,       // x2 buffer, x3 size: GetData (writes the value's bytes whatever *size is)
    SizeAt1,    // x1: s64* (Serialize)
};
struct FnInfo {
    const char* sym;
    HostFn fn;
    const char* label;
    Obj obj;
    Ret ret;
    Out out = Out::None;
    u8 bytes = 0;  // Out::Value's size
};
const FnInfo& info(Fn k);

// Trampolines to the originals (set when the natives are installed).
extern u64 g_orig[kFnCount];

// Inside a shadow call: run the original instead (true: done).
bool forward(Cpu& c, Fn k);
// The check is on (--live-check yayoi_sqlite) and this thread isn't running a shadow.
bool on();

// The registers at entry and what before() saved of the out-parameters.
struct Call {
    Fn k;
    u64 x[8];
    u64 x8;
    std::vector<u8> out_before;  // the out-buffer's bytes before the native wrote them
    u64 size_before = 0;         // Text / Data: *size before
};
void before(Cpu& c, Fn k, Call* call);
// After the native ran (its results in `c` / x8 / the out-parameters): the shadow's turn.
void after(Cpu& c, Call& call);

}  // namespace soa::native::yayoi::live

// The SQLite driver family's hooks: the HostFns of Aska::Yayoi::SQLiteDriver, its EntityObject and the
// column map's THashMap members (the guest ABI: `this` in x0, an Aska::Status or a struct result
// through x8), registered with trampolines to the originals for the live check (yayoi_sqlite_live.h).
#include <cstring>
#include <mutex>
#include <string>
#include <unordered_map>

#include "native/common/native.h"
#include "native/yayoi/yayoi_layout.h"
#include "native/yayoi/yayoi_sqlite.h"
#include "native/yayoi/yayoi_sqlite_live.h"

namespace soa::native::yayoi {

namespace {

using live::Fn;
using live::Obj;
using live::Out;
using live::Ret;

SQLiteDriver* drv(Cpu& c) { return reinterpret_cast<SQLiteDriver*>(c.x(0)); }
EntityObject* ent(Cpu& c) { return reinterpret_cast<EntityObject*>(c.x(0)); }
ColumnMap* map(Cpu& c) { return reinterpret_cast<ColumnMap*>(c.x(0)); }
template <typename T>
T* xarg(Cpu& c, int i) { return reinterpret_cast<T*>(c.x(i)); }
const char* str(Cpu& c, int i) { return reinterpret_cast<const char*>(c.x(i)); }
void status(Cpu& c, s64 st) { *reinterpret_cast<s64*>(c.x(8)) = st; }
void ret_int(Cpu& c, s32 v) { c.set_x(0, (u64)(u32)v); }

// The hook around a native body: inside a shadow call the original runs; with the live check on, the
// shadow repeats the call after the native.
template <Fn K, void (*Body)(Cpu&)>
void hook(Cpu& c) {
    if (live::forward(c, K)) return;
    if (!live::on()) return Body(c);
    live::Call call;
    live::before(c, K, &call);
    Body(c);
    live::after(c, call);
}

// ---- the bodies ----

// SQLiteDriver
void b_DriverCtor(Cpu& c) { drv(c)->Ctor(); }
void b_DriverDtor(Cpu& c) { drv(c)->Dtor(); }
void b_Open(Cpu& c) { status(c, drv(c)->Open(xarg<void>(c, 1))); }
void b_DoOpen(Cpu& c) { status(c, drv(c)->DoOpen((u32)c.x(1), str(c, 2), xarg<const DBAddress>(c, 3))); }
void b_Close(Cpu& c) { drv(c)->Close(); }
void b_BeginTransaction(Cpu& c) { status(c, drv(c)->BeginTransaction()); }
void b__BeginTransaction(Cpu& c) { status(c, drv(c)->_BeginTransaction()); }
void b_Commit(Cpu& c) { status(c, drv(c)->Commit()); }
void b_Rollback(Cpu& c) { status(c, drv(c)->Rollback()); }
void b_Execute(Cpu& c) { status(c, drv(c)->Execute(str(c, 1), xarg<const QueryParam>(c, 2), c.x(3))); }
void b__Execute(Cpu& c) { status(c, drv(c)->_Execute(str(c, 1), xarg<const QueryParam>(c, 2), c.x(3), xarg<EntityObject>(c, 4))); }
void b_Find(Cpu& c) { status(c, drv(c)->Find(str(c, 1), xarg<const QueryParam>(c, 2), c.x(3), xarg<EntityObject>(c, 4))); }
void b__Prepare(Cpu& c) { status(c, drv(c)->_Prepare(str(c, 1), xarg<s32>(c, 2))); }

// EntityObject
void b_EntityCtor(Cpu& c) { ent(c)->Ctor(); }
void b_EntityDtor(Cpu& c) { ent(c)->Dtor(); }
void b_Release(Cpu& c) { ent(c)->Release(); }
void b_ClearCache(Cpu& c) { ent(c)->ClearCache(); }
void b_CreateCacheBuffer(Cpu& c) { status(c, ent(c)->CreateCacheBuffer(c.x(1))); }
void b_GetCacheBuffer(Cpu& c) { c.set_x(0, (u64)ent(c)->GetCacheBuffer(xarg<u64>(c, 1))); }
void b_Store(Cpu& c) { status(c, ent(c)->Store(xarg<void>(c, 1), xarg<void>(c, 2))); }
void b_Fetch(Cpu& c) { status(c, ent(c)->Fetch()); }
void b_GetTypeIndex(Cpu& c) { ret_int(c, ent(c)->GetType((s32)c.x(1), c.x(2))); }
void b_GetTypeName(Cpu& c) { ret_int(c, ent(c)->GetType(str(c, 1), c.x(2))); }
void b_GetFieldLength(Cpu& c) { ret_int(c, ent(c)->GetFieldLength((s32)c.x(1), (s32)c.x(2))); }
void b_GetStringLength(Cpu& c) { status(c, ent(c)->GetStringLength((s32)c.x(1), xarg<u64>(c, 2), c.x(3))); }
#define SOA_YAYOI_TEXT_BODY(M)                                                                                 \
    void b_##M##Index(Cpu& c) { status(c, ent(c)->M((s32)c.x(1), xarg<char>(c, 2), xarg<u64>(c, 3), c.x(4))); } \
    void b_##M##Name(Cpu& c) { status(c, ent(c)->M(str(c, 1), xarg<char>(c, 2), xarg<u64>(c, 3), c.x(4))); }
SOA_YAYOI_TEXT_BODY(GetTime)
SOA_YAYOI_TEXT_BODY(GetData)
SOA_YAYOI_TEXT_BODY(GetString)
#undef SOA_YAYOI_TEXT_BODY
#define SOA_YAYOI_VALUE_BODY(M, T)                                                                \
    void b_##M##Index(Cpu& c) { status(c, ent(c)->M((s32)c.x(1), xarg<T>(c, 2), c.x(3))); } \
    void b_##M##Name(Cpu& c) { status(c, ent(c)->M(str(c, 1), xarg<T>(c, 2), c.x(3))); }
SOA_YAYOI_VALUE_BODY(GetTinyInt, s8)
SOA_YAYOI_VALUE_BODY(GetShort, s16)
SOA_YAYOI_VALUE_BODY(GetInteger, s32)
SOA_YAYOI_VALUE_BODY(GetLong, s64)
SOA_YAYOI_VALUE_BODY(GetFloat, float)
SOA_YAYOI_VALUE_BODY(GetDouble, double)
#undef SOA_YAYOI_VALUE_BODY
void b_Serialize(Cpu& c) { *reinterpret_cast<SharedBytes*>(c.x(8)) = ent(c)->Serialize(xarg<s64>(c, 1)); }
void b_SerializeCache(Cpu& c) { c.set_x(0, ent(c)->SerializeCache(xarg<u64>(c, 1))); }

// THashMap<char const*, int, StringHasher, StringEqualTo>
void b_MapDtor(Cpu& c) { map(c)->Dtor(); }
void b_MapDtorDelete(Cpu& c) { map(c)->DtorDelete(); }
void b_MapEmplace(Cpu& c) { *reinterpret_cast<ColumnMapInsertResult*>(c.x(8)) = map(c)->Emplace_(xarg<const char* const>(c, 1)); }
void b_MapInsert_(Cpu& c) { *reinterpret_cast<ColumnMapInsertResult*>(c.x(8)) = map(c)->Insert_(xarg<const ColumnPair>(c, 1)); }
void b_MapRehash(Cpu& c) { map(c)->Rehash_(c.x(1)); }
void b_MapInsertRange(Cpu& c) { map(c)->Insert(xarg<ColumnMapIterator>(c, 1), xarg<const ColumnMapIterator>(c, 2)); }

#define SOA_MAP "_ZN4Aska8THashMapIPKciNS_5Yayoi12SQLiteDriver12EntityObject12StringHasherENS5_13StringEqualToENS_10TAllocatorINS_5TPairIKS2_iEEEEE"
#define SOA_DRV "_ZN4Aska5Yayoi12SQLiteDriver"
#define SOA_ENT "_ZN4Aska5Yayoi12SQLiteDriver12EntityObject"
#define F(name, sym, label, obj, ret, ...) \
    {sym, &hook<live::k##name, &b_##name>, "yayoi: " label " (host SQLite)", Obj::obj, Ret::ret, ##__VA_ARGS__}

// In live::Fn order (the README's natives table).
const live::FnInfo kInfo[live::kFnCount] = {
    F(DriverCtor, SOA_DRV "C1Ev", "SQLiteDriver::SQLiteDriver", Driver, Void),
    F(DriverDtor, SOA_DRV "D1Ev", "SQLiteDriver::~SQLiteDriver", Driver, Void),
    F(Open, SOA_DRV "4OpenEPNS0_14IDriverSettingIS1_EE", "SQLiteDriver::Open", Driver, Status),
    F(DoOpen, SOA_DRV "6DoOpenENS0_6Entity4ModeEPKcPKNS0_9DBAddressE", "SQLiteDriver::DoOpen", Driver, Status),
    F(Close, SOA_DRV "5CloseEv", "SQLiteDriver::Close", Driver, Void),
    F(BeginTransaction, SOA_DRV "16BeginTransactionEv", "SQLiteDriver::BeginTransaction", Driver, Status),
    F(_BeginTransaction, SOA_DRV "17_BeginTransactionEv", "SQLiteDriver::_BeginTransaction", Driver, Status),
    F(Commit, SOA_DRV "6CommitEv", "SQLiteDriver::Commit", Driver, Status),
    F(Rollback, SOA_DRV "8RollbackEv", "SQLiteDriver::Rollback", Driver, Status),
    F(Execute, SOA_DRV "7ExecuteEPKcPKNS0_10QueryParamEm", "SQLiteDriver::Execute", Driver, Status),
    F(_Execute, SOA_DRV "8_ExecuteEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE", "SQLiteDriver::_Execute", Driver, Status),
    F(Find, SOA_DRV "4FindEPKcPKNS0_10QueryParamEmPNS1_12EntityObjectE", "SQLiteDriver::Find", Driver, Status),
    F(_Prepare, SOA_DRV "8_PrepareEPKcPi", "SQLiteDriver::_Prepare", Driver, Status, Out::I32At2),
    F(EntityCtor, SOA_ENT "C1Ev", "EntityObject::EntityObject", Entity, Void),
    F(EntityDtor, SOA_ENT "D1Ev", "EntityObject::~EntityObject", Entity, Void),
    F(Release, SOA_ENT "7ReleaseEv", "EntityObject::Release", Entity, Void),
    F(ClearCache, SOA_ENT "10ClearCacheEv", "EntityObject::ClearCache", Entity, Void),
    F(CreateCacheBuffer, SOA_ENT "17CreateCacheBufferEm", "EntityObject::CreateCacheBuffer", Entity, Status),
    F(GetCacheBuffer, SOA_ENT "14GetCacheBufferEPm", "EntityObject::GetCacheBuffer", Entity, Ptr, Out::U64At1),
    F(Store, SOA_ENT "5StoreEP7sqlite3P12sqlite3_stmt", "EntityObject::Store", Entity, Status),
    F(Fetch, SOA_ENT "5FetchEv", "EntityObject::Fetch", Entity, Status),
    F(GetTypeIndex, SOA_ENT "7GetTypeEim", "EntityObject::GetType(int)", Entity, Int),
    F(GetTypeName, SOA_ENT "7GetTypeEPKcm", "EntityObject::GetType(name)", Entity, Int),
    F(GetFieldLength, SOA_ENT "14GetFieldLengthEii", "EntityObject::GetFieldLength", Entity, Int),
    F(GetStringLength, SOA_ENT "15GetStringLengthEiPmm", "EntityObject::GetStringLength", Entity, Status, Out::U64At2),
    F(GetTimeIndex, SOA_ENT "7GetTimeEiPcPmm", "EntityObject::GetTime(int)", Entity, Status, Out::Text),
    F(GetTimeName, SOA_ENT "7GetTimeEPKcPcPmm", "EntityObject::GetTime(name)", Entity, Status, Out::Text),
    F(GetDataIndex, SOA_ENT "7GetDataEiPcPmm", "EntityObject::GetData(int)", Entity, Status, Out::Data),
    F(GetDataName, SOA_ENT "7GetDataEPKcPcPmm", "EntityObject::GetData(name)", Entity, Status, Out::Data),
    F(GetStringIndex, SOA_ENT "9GetStringEiPcPmm", "EntityObject::GetString(int)", Entity, Status, Out::Text),
    F(GetStringName, SOA_ENT "9GetStringEPKcPcPmm", "EntityObject::GetString(name)", Entity, Status, Out::Text),
    F(GetTinyIntIndex, SOA_ENT "10GetTinyIntEiPam", "EntityObject::GetTinyInt(int)", Entity, Status, Out::Value, 1),
    F(GetTinyIntName, SOA_ENT "10GetTinyIntEPKcPam", "EntityObject::GetTinyInt(name)", Entity, Status, Out::Value, 1),
    F(GetShortIndex, SOA_ENT "8GetShortEiPsm", "EntityObject::GetShort(int)", Entity, Status, Out::Value, 2),
    F(GetShortName, SOA_ENT "8GetShortEPKcPsm", "EntityObject::GetShort(name)", Entity, Status, Out::Value, 2),
    F(GetIntegerIndex, SOA_ENT "10GetIntegerEiPim", "EntityObject::GetInteger(int)", Entity, Status, Out::Value, 4),
    F(GetIntegerName, SOA_ENT "10GetIntegerEPKcPim", "EntityObject::GetInteger(name)", Entity, Status, Out::Value, 4),
    F(GetLongIndex, SOA_ENT "7GetLongEiPlm", "EntityObject::GetLong(int)", Entity, Status, Out::Value, 8),
    F(GetLongName, SOA_ENT "7GetLongEPKcPlm", "EntityObject::GetLong(name)", Entity, Status, Out::Value, 8),
    F(GetFloatIndex, SOA_ENT "8GetFloatEiPfm", "EntityObject::GetFloat(int)", Entity, Status, Out::Value, 4),
    F(GetFloatName, SOA_ENT "8GetFloatEPKcPfm", "EntityObject::GetFloat(name)", Entity, Status, Out::Value, 4),
    F(GetDoubleIndex, SOA_ENT "9GetDoubleEiPdm", "EntityObject::GetDouble(int)", Entity, Status, Out::Value, 8),
    F(GetDoubleName, SOA_ENT "9GetDoubleEPKcPdm", "EntityObject::GetDouble(name)", Entity, Status, Out::Value, 8),
    F(Serialize, SOA_ENT "9SerializeEPl", "EntityObject::Serialize", Entity, Shared, Out::SizeAt1),
    F(SerializeCache, SOA_ENT "14SerializeCacheEPm", "EntityObject::SerializeCache", Entity, U64),
    F(MapDtor, SOA_MAP "D2Ev", "THashMap<char const*, int>::~THashMap (D2)", Map, Void),
    F(MapDtorDelete, SOA_MAP "D0Ev", "THashMap<char const*, int>::~THashMap (D0)", Map, Void),
    F(MapEmplace, SOA_MAP "8Emplace_ERSA_", "THashMap<char const*, int>::Emplace_", Map, InsertResult),
    F(MapInsert_, SOA_MAP "7Insert_ERKSB_", "THashMap<char const*, int>::Insert_", Map, InsertResult),
    F(MapRehash, SOA_MAP "7Rehash_Em", "THashMap<char const*, int>::Rehash_", Map, Void),
    F(MapInsertRange, SOA_MAP "6InsertINS_16THashMapIteratorINS_6detail19THashMapBucketArrayINSG_14THashMapBucketISB_EENS8_ISJ_EEEEEEEEvT_SN_",
      "THashMap<char const*, int>::Insert<THashMapIterator>", Map, Void),
};
#undef F

bool register_all() {
    for (int k = 0; k < live::kFnCount; k++)
        register_native_function({kInfo[k].sym, kInfo[k].fn, kInfo[k].label, nullptr, &live::g_orig[k]});
    return true;
}
const bool g_registered = register_all();

}  // namespace

const live::FnInfo& live::info(Fn k) { return kInfo[k]; }

const DriverNative* driver_natives(size_t* n) {
    static DriverNative list[live::kFnCount];
    static std::once_flag once;
    std::call_once(once, [] {
        for (int k = 0; k < live::kFnCount; k++) list[k] = {kInfo[k].sym, kInfo[k].fn, kInfo[k].label};
    });
    *n = live::kFnCount;
    return list;
}

u64 driver_native_thunk(const char* sym) {
    static std::mutex m;
    static std::unordered_map<std::string, u64> thunks;
    std::lock_guard lk(m);
    auto it = thunks.find(sym);
    if (it != thunks.end()) return it->second;
    for (int k = 0; k < live::kFnCount; k++)
        if (std::strcmp(kInfo[k].sym, sym) == 0) return thunks[sym] = make_thunk(kInfo[k].label, kInfo[k].fn);
    return 0;
}

}  // namespace soa::native::yayoi

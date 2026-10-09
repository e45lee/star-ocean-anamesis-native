// info_layout.h: the guest data layouts of the `info` subsystem (the client's info objects and parameter manager (player, roster, missions)).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/info/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types info` turns the structs into port/decomp/info/types.json for Ghidra.
#ifndef SOA_NATIVE_INFO_LAYOUT_H
#define SOA_NATIVE_INFO_LAYOUT_H

#include <cstddef>
#include <cstdint>
#include <span>

#include "../libcxx/libcxx_layout.h"

namespace soa::native::info {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// ---- Framework::CInteroperateParameter: a CSV table looked up by row / column names -------------------

// The table's row and column hashes: std::map<unsigned (CHash32 of the name), unsigned long (the index)>
// (libcxx_layout.h tree; Framework::CSTLAllocator), each allocated alone (operator new, InitializeCommon).
using NameIndexMap = libcxx::tree<libcxx::pair<u32, u64>>;
using NameIndexNode = libcxx::tree_node<libcxx::pair<u32, u64>>;

// The CSV behind the table (ICSVAccessor: TCSVAccessor<CCSV> / <CACSV>), vtable slots the lookups use.
enum CsvSlot : u32 {
    kCsvNumElements = 6,   // (row) -> count (IsExist(key, col): col < count - 1)
    kCsvIsValue = 9,       // (row, col) -> bool
    kCsvIsString = 10,     // (row, col) -> bool
    kCsvValue = 11,        // (row, col) -> float
};

// Framework::CInteroperateParameter: guest size 0x28. Layout from the constructor (vtable; the CSV, the row
// and column hashes 0; +0x24 0), Release / the destructors, Initialize (+0x24 = its count argument),
// InitializeCommon (the hashes), IsExist / ConvertToRow / ConvertToColumn (port/decomp/info/interoperate.c).
// Columns are addressed past the CSV's first (the row's name): the by-key wrappers pass col + 1.
class CInteroperateParameter {
public:
    bool IsExist(const char* row) const;            // _ZNK9Framework22CInteroperateParameter7IsExistEPKc
    bool IsExist(const char* row, u64 col) const;   // ...7IsExistEPKcm: the row has a column `col`
    s32 ConvertToRow(const char* row) const;        // ...12ConvertToRowEPKc: its index, -1 when absent
    s32 ConvertToColumn(const char* column) const;  // ...15ConvertToColumnEPKc
    // IsValue / IsString / Value(row, col): ConvertToRow, then the CSV's slot on (row (sign-extended), col + 1)
    // (natives in info_interoperate.cpp: the result registers are the CSV's).

    const void* vtable;         // 0x00: _ZTVN9Framework22CInteroperateParameterE + 0x10
    void* m_pCSV;               // 0x08: ICSVAccessor*
    NameIndexMap* m_pRowHash;   // 0x10
    NameIndexMap* m_pColumnHash;  // 0x18
    u8 unk_20[4];               // 0x20
    u32 m_count;                // 0x24: Initialize's count argument
};
static_assert(offsetof(CInteroperateParameter, m_pCSV) == 0x08);
static_assert(offsetof(CInteroperateParameter, m_pRowHash) == 0x10);
static_assert(offsetof(CInteroperateParameter, m_pColumnHash) == 0x18);
static_assert(offsetof(CInteroperateParameter, m_count) == 0x24);
static_assert(sizeof(CInteroperateParameter) == 0x28);

// ---- InfoBase: the server responses' objects ----------------------------------------------------------

// InfoBase's maps: CHash32 of the ASON key -> the property / the child object (std::map, the STL allocator).
using PropertyMap = libcxx::tree<libcxx::pair<u32, void*>>;   // -> IParameterProperty*
using PropertyNode = libcxx::tree_node<libcxx::pair<u32, void*>>;
static_assert(offsetof(PropertyNode, value) == 0x20 && sizeof(PropertyNode) == 0x30);

// InfoBase: the base of every info object (CPlayerInfo, CPersonStatusInfo, ...: a response's part),
// guest size 0x38. Layout from the constructors (the two maps' empty heads), Initialize (each property
// named, defaulted and put in m_properties by its NameHash) and DeserializeChild
// (port/decomp/info/person_status.c). The properties (params_layout.h) and children follow at +0x38.
class InfoBase {
public:
    // Virtuals in vtable order (_ZTV8InfoBase):
    bool DeserializeArray(const void* array);  // slot 0: _ZN8InfoBase16DeserializeArrayEPKN4Aska4ASON6AValue6AArrayE (0)
    // slot 1: for each pair of the map: the property its key (CHash32 of the key's C string) names gets
    // Deserialize(the whole map) (slot 3); the child it names gets DeserializeArray / DeserializeChild of
    // the pair's value when that is an array / a map. Returns 1.
    bool DeserializeChild(const void* map);    // _ZN8InfoBase16DeserializeChildEPKN4Aska4ASON6AValue4AMapE
    // slot 2: Initialize (pure), slot 3: pParseName (0 in the base)
    static constexpr int kSlotDeserializeArray = 0, kSlotDeserializeChild = 1, kSlotInitialize = 2, kSlotParseName = 3;

    const void* vtable;         // 0x00
    PropertyMap m_properties;   // 0x08
    PropertyMap m_children;     // 0x20 (-> InfoBase*)
};
static_assert(offsetof(InfoBase, m_properties) == 0x08);
static_assert(offsetof(InfoBase, m_children) == 0x20);
static_assert(sizeof(InfoBase) == 0x38);

// ---- the parameter manager (partial) --------------------------------------------------------------------

// CInfoManager: the info objects of a response (CParameterManager + 0x600), itself an InfoBase (its key, its
// properties and children). Partial: what --fake-server-schema (api/fakeapi.cpp's dump) reads. Layout from
// the constructor (_ZN12CInfoManagerC2Ev @ 0x14fb168, too large for the decompiler: `add x8, x19, #0x978;
// str x8, [x19, #0x970]` makes the map at +0x970 empty) and CParameterManager::Deserialize (slot 0 / 1 on
// it by the value's kind, slot 3 its key). Size not recovered.
class CInfoManager {
public:
    InfoBase base;                   // 0x000
    u8 unk_038[0x970 - 0x38];        // 0x038
    PropertyMap m_infosByHash;       // 0x970: std::map<unsigned (a name's CHash32), InfoBase*>
};
static_assert(offsetof(CInfoManager, m_infosByHash) == 0x970);

// CParameterManager (TSingleton): the client's parameter sets and infos. Partial, as CInfoManager. Layout
// from the constructor (a CFiberUnit(0x600) at 0, the empty list at +0x68, CInfoManager() at +0x600) and
// Deserialize(AMap const*) (each listed parameter set's slot 4 Deserialize(map), then m_infoManager by its
// key, "status" to +0xb728). Size not recovered (beyond 0xb72c).
class CParameterManager {
public:
    u8 unk_000[0x68];                       // 0x000: the CFiberUnit (0x38) and the fields after it
    libcxx::list<InfoBase*> m_parameters;   // 0x068: the registered parameter sets (some InfoBase-derived)
    u8 unk_080[0x600 - 0x80];               // 0x080
    CInfoManager m_infoManager;             // 0x600
};
static_assert(offsetof(CParameterManager, m_parameters) == 0x68);
static_assert(offsetof(CParameterManager, m_infoManager) == 0x600);

// ---- the info classes (gen/info_classes.h, tools/gen_infos.py) ------------------------------------------
//
// Every class derived from InfoBase is an InfoBase, its properties (params_layout.h) and its children,
// embedded: other infos, or containers. The 186 info classes' layouts are generated (read from objects the
// lib builds, under unicorn); their code differs per class only in these lists, so the natives are one
// generic code over a class's InfoClass (info_class.cpp).

// A container child: InfoBaseArray<T> / InfoBaseValueArray<T, P> (an InfoBase and a CSTLVector: begin,
// end, capacity) or IInfoBaseMap<K, T> (an InfoBase and a CSTLMap: begin node, root, size), each a
// derived list class (CPersonInfoList, ...) with its own vtable. Guest size 0x50 (the vmi typeinfos: the
// container base at +0x38; the constructors in CInfoManager's).
class InfoContainer {
public:
    InfoBase base;      // 0x00
    u64 m_body[3];      // 0x38: the vector (begin, end, cap) or the map (begin node, root, size)
};
static_assert(offsetof(InfoContainer, m_body) == 0x38 && sizeof(InfoContainer) == 0x50);

enum class InfoKind : u8 { kInfo, kArray, kMap, kValueArray };
enum class InfoPropKind : u8 { kU32, kS32, kFloat, kBool, kU8, kU64, kString };

// A property of an info: CParameterPropertyValue<T, N, Conv> (0x30) or CParameterPropertyString<N> (0x40).
struct InfoProp {
    u16 offset;
    InfoPropKind kind;
    bool radian;  // CPropertyConverterRadian (a float)
    u32 n;        // the template's N
};
struct InfoClass;
struct InfoChild {
    u32 offset;
    const InfoClass* cls;
};
// One step of a class's Initialize, in its order.
struct InfoStep {
    enum Kind : u8 { kProperty, kChild, kStore };  // kStore: `width` bytes of `def` at `offset` (CInfoManager's members)
    Kind kind;
    u32 offset;
    const char* key;  // a property's ASON key (m_name = CHash32(key))
    u8 width;         // the default's store (0: none, a string's)
    u64 def;          // its bytes
};
struct InfoClass {
    const char* name;
    const char* ztv;  // its vtable symbol
    InfoKind kind;
    u32 size;
    std::span<const InfoProp> props;
    std::span<const InfoChild> children;
    std::span<const InfoStep> init;  // empty: Initialize left to the guest (or a container's)
    // A container's element: InfoBaseArray<T>'s / IInfoBaseMap<K, T>'s T (null when not generated),
    // the map's key size (K: 4 or 8; the node: key at +0x20, T at +0x28), InfoBaseValueArray<T, P>'s P
    // (a CParameterPropertyValue, 0x30: kind and N).
    const InfoClass* elem = nullptr;
    u8 key_size = 0;
    InfoProp elem_prop = {};
    // The guest functions a container's natives call (null: not in the lib): a map's
    // __emplace_hint_unique_key_args<K, pair<K const, T> const&> (one element's copy) and __tree::destroy;
    // the assignment: vector<E>::assign<E*>(first, last) / __tree::__assign_multi(first, last).
    const char* fn_copy = nullptr;
    const char* fn_destroy = nullptr;
    const char* fn_assign = nullptr;
    // Plain data after the last property or child (sizeof as the lib's code uses it, minus where they end):
    // the copies copy it as it is; the constructor, Initialize and the destructor leave it.
    u32 tail = 0;
};

// ---- CTimeUtility: the client's date strings ---------------------------------------------------------------

// CTimeUtility: static helpers (no object). Layout of what str2time_t builds: bionic's struct tm (56
// bytes), from the decompile (port/decomp/info/time.c).
struct GuestTm {
    s32 tm_sec, tm_min, tm_hour, tm_mday, tm_mon, tm_year, tm_wday, tm_yday, tm_isdst;  // 0x00 .. 0x20
    u8 pad_24[4];
    s64 tm_gmtoff;      // 0x28
    const char* tm_zone;  // 0x30
};
static_assert(offsetof(GuestTm, tm_isdst) == 0x20 && offsetof(GuestTm, tm_gmtoff) == 0x28 && sizeof(GuestTm) == 0x38);

class CTimeUtility {
public:
    // str2time_t(text, fallback, date_only, slashes): "Y-M-D h:m:s" (or "Y/M/D ..."; dashes unless the text
    // has a slash, or has no dash and `slashes`) split in place (a 64-byte copy) at the separators; each
    // field through CSTLStringUtility_Base::AToF (a std::string temporary) and FCVTZS; month - 1, year -
    // 1900; time 0 when date_only; tm_yday = tm_isdst = 0; mktime (the runtime's: platform370's local
    // time). The fallback when text is null or the first two separators are missing.
    // _ZN12CTimeUtility10str2time_tEPKclbb
    static s64 str2time_t(const char* text, s64 fallback, bool date_only, bool slashes);
};

}  // namespace soa::native::info

#endif  // SOA_NATIVE_INFO_LAYOUT_H

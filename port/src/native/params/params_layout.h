// params_layout.h: the guest data layouts of the `params` subsystem (the parameter (de)serialization base:
// CParameterElementBase, CParameterParser, CParameterProperty*).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/params/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types params` turns the structs into port/decomp/params/types.json for Ghidra.
//
// The guest's class hierarchy uses data-carrying bases; as in containers_layout.h the base is nested as
// the first member `base` (standard layout), so `p.base.base.m_next` reads
// CParameterPropertyValue -> CParameterPropertyBase -> IParameterProperty's field.
#ifndef SOA_NATIVE_PARAMS_LAYOUT_H
#define SOA_NATIVE_PARAMS_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../data_formats/data_formats_layout.h"
#include "../hash/hash_layout.h"
#include "../libcxx/libcxx_layout.h"

namespace soa::native::params {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

using AMap = data_formats::AMap;      // Aska::ASON::AValue::AMap (the parser's input)
using AArray = data_formats::AArray;  // Aska::ASON::AValue::AArray
using AValue = data_formats::AValue;  // Aska::ASON::AValue
using String = libcxx::String;        // the game's std::string (Framework::CSTLAllocator)
using ASON_Pair = data_formats::ASON_Pair;  // a map entry: key, value

// Framework::CHash32: the `hash` subsystem's class (hash_layout.h: {vtable, u32 m_hash}, 0x10).
using CHash32Ref = hash::CHash32;
static_assert(sizeof(CHash32Ref) == 0x10);

// ---- the properties ------------------------------------------------------------------------------------

// IParameterProperty: the interface of one named field of a parameter element, guest size 0x10. A
// singly linked list (m_next) of them hangs off CParameterElementBase::m_first. Layout from
// CParameterElementBase::AddProperty / Deserialize / PrintC (port/decomp/params/base.c); vtable order from
// _ZTV18IParameterProperty (slots 0-2 pure; the instantiations' vtables fill them, checked by
// params/layout-player).
class IParameterProperty {
public:
    // Virtuals in vtable order, as plain members (no C++ virtual: the guest vtable is the field).
    bool CompareName(const char* name) const;  // slot 0 (pure here): CParameterPropertyBase<N>::CompareName(char const*)
    bool CompareName(u32 hash) const;          // slot 1 (pure here): CompareName(unsigned int)
    u32 NameHash() const;                      // slot 2 (pure here): CParameterPropertyBase<N>::NameHash()
    bool Deserialize(const AMap* map);         // slot 3: _ZN18IParameterProperty11DeserializeEPKN4Aska4ASON6AValue4AMapE (returns 1)
    void PrintC() const;                       // slot 4: _ZNK18IParameterProperty6PrintCEv (empty)
    // No destructor slot: the guest never deletes a property through the interface.

    static constexpr int kSlotCompareNameStr = 0, kSlotCompareNameHash = 1, kSlotNameHash = 2, kSlotDeserialize = 3,
                         kSlotPrintC = 4;

    const void* vtable;          // 0x00: an instantiation's vtable (_ZTV23CParameterPropertyValue... + 0x10)
    IParameterProperty* m_next;  // 0x08: the element's next property (0 at the end); AddProperty appends here
};
static_assert(offsetof(IParameterProperty, m_next) == 0x08);
static_assert(sizeof(IParameterProperty) == 0x10);

// CParameterPropertyBase<N>: a property with a name, guest size 0x28. N is not a name id: it is the XOR
// key of CryptString (N & 0xff; e.g. <42u> ^ 0x2a, <96u> ^ 0x60, <100u> ^ 0x64), so string values are kept
// obfuscated in memory. The constructor is inlined into each element's constructor (e.g.
// CParameterPlayerElement::CParameterPlayerElement: vtable, m_next = 0, m_named = 0, CHash32()); the
// element's Initialize names it (CHash32::operator=(char const*), m_named = 1, the default value) and
// AddProperty links it. Layout from those and CompareName / NameHash (port/decomp/params/property.c).
template <u32 N>
class CParameterPropertyBase {
public:
    // vtable slots 0-2 (the IParameterProperty interface):
    bool CompareName(const char* name) const;  // _ZNK22CParameterPropertyBaseILjNEE11CompareNameEPKc: name && CHash32(name) == m_name
    bool CompareName(u32 hash) const;          // _ZNK22CParameterPropertyBaseILjNEE11CompareNameEj: m_name == hash
    u32 NameHash() const;                      // _ZNK22CParameterPropertyBaseILjNEE8NameHashEv: (u32)m_name
    // Static: dst = each byte of src ^ (N & 0xff), appended one at a time (dst cleared first; src's own
    // bytes are never changed). Used on load (CParameterPropertyString::Deserialize) and on read (e.g.
    // CParameterPlayer::CopyForMultiplay): encrypt and decrypt are the same.
    // _ZN22CParameterPropertyBaseILjNEE11CryptStringINSt6__ndk112basic_string...EEEvRT_RKSB_
    static void CryptString(String& dst, const String& src);
    static constexpr u8 kCryptKey = u8(N & 0xff);

    IParameterProperty base;  // 0x00: vtable, m_next
    bool m_named;             // 0x10: set by the element's Initialize with the name (0 from the constructor)
    u8 unk_11[7];             // 0x11: padding
    CHash32Ref m_name;        // 0x18: the hash of the property's key in the ASON map
};

// The value converters (template tags of CParameterPropertyValue): CPropertyConverter stores the parsed
// value as is; CPropertyConverterRadian (float only) stores v * pi / 180 (constants 3.14159274f and 180.0f
// at vaddr 0x26e3fd0, a float multiply then a divide: CParameterPropertyValue<float, 118u,
// CPropertyConverterRadian>::Deserialize).
struct CPropertyConverter {};
struct CPropertyConverterRadian {};

// CParameterPropertyValue<T, N, Conv>: a scalar property, T in {u32 (290 instantiations), float (227),
// bool (127), u64 (63), s32 (54), u8 (25)}; guest size 0x30 (every T fits the 8 bytes at 0x28). Layout from
// Deserialize (the value at +0x28 when CParameterParser::GetValue<T>(map, NameHash()) found it) and the
// elements' Initialize (the default stored at +0x28).
template <typename T, u32 N, typename Conv = CPropertyConverter>
class CParameterPropertyValue {
public:
    // vtable: slots 0-2 CParameterPropertyBase<N>'s, slot 3 / 4:
    bool Deserialize(const AMap* map);  // _ZN23CParameterPropertyValueI<T>Lj<N>E<Conv>E11DeserializeEPKN4Aska4ASON6AValue4AMapE
    void PrintC() const;                // _ZNK23CParameterPropertyValueI...E6PrintCEv (empty in the shipped build)

    CParameterPropertyBase<N> base;  // 0x00
    T m_value;                       // 0x28: the value (unchanged when the key is missing or the wrong kind);
                                     // the rest up to 0x30 is tail padding (the class is 8-aligned)
};

// CParameterPropertyString<S, N>: a string property (194 instantiations, S = the game's std::string),
// guest size 0x40. The string is stored XORed with N (CryptString), so reading it needs CryptString again.
// Layout from Deserialize (CryptString(this + 0x28, parsed)), the inlined constructor (the three string
// words cleared) and the elements' destructors (Free of a long string's data).
template <u32 N>
class CParameterPropertyString {
public:
    bool Deserialize(const AMap* map);  // slot 3: _ZN24CParameterPropertyStringINSt6__ndk112basic_string...ELj<N>EE11DeserializeEPKN4Aska4ASON6AValue4AMapE
    void PrintC() const;                // slot 4 (empty)

    CParameterPropertyBase<N> base;  // 0x00
    String m_value;                  // 0x28: the value, each byte ^ (N & 0xff)
};

// The instantiations exported to Ghidra (port/decomp/params/types.json) and checked here.
using CParameterPropertyBase36 = CParameterPropertyBase<36>;
using CParameterPropertyValueU32_36 = CParameterPropertyValue<u32, 36>;   // CParameterPlayerElement's "Id"
using CParameterPropertyValueS32_39 = CParameterPropertyValue<s32, 39>;   // "Role"
using CParameterPropertyValueF32_96 = CParameterPropertyValue<float, 96>;
using CParameterPropertyValueBool96 = CParameterPropertyValue<bool, 96>;
using CParameterPropertyValueU64_103 = CParameterPropertyValue<u64, 103>;
using CParameterPropertyValueU8_186 = CParameterPropertyValue<u8, 186>;
using CParameterPropertyValueRad118 = CParameterPropertyValue<float, 118, CPropertyConverterRadian>;
using CParameterPropertyString42 = CParameterPropertyString<42>;          // CParameterPlayerElement's "Name"

static_assert(offsetof(CParameterPropertyBase36, m_named) == 0x10);
static_assert(offsetof(CParameterPropertyBase36, m_name) == 0x18);
static_assert(sizeof(CParameterPropertyBase36) == 0x28);
static_assert(offsetof(CParameterPropertyValueU32_36, m_value) == 0x28);
static_assert(sizeof(CParameterPropertyValueU32_36) == 0x30);
static_assert(sizeof(CParameterPropertyValueS32_39) == 0x30);
static_assert(sizeof(CParameterPropertyValueF32_96) == 0x30);
static_assert(offsetof(CParameterPropertyValueBool96, m_value) == 0x28);
static_assert(sizeof(CParameterPropertyValueBool96) == 0x30);
static_assert(sizeof(CParameterPropertyValueU64_103) == 0x30);
static_assert(sizeof(CParameterPropertyValueU8_186) == 0x30);
static_assert(sizeof(CParameterPropertyValueRad118) == 0x30);
static_assert(offsetof(CParameterPropertyString42, m_value) == 0x28);
static_assert(sizeof(CParameterPropertyString42) == 0x40);

// ---- the parser ----------------------------------------------------------------------------------------

// std::pair<T, bool> as the parser returns it: a composite of at most 16 bytes, so in x0 (and x1 for an
// 8-byte T) as if loaded from the pair in memory: the bool at bit 32 for a 4-byte T (float, int,
// unsigned), at bit 8 for bool / unsigned char, in x1 for long / unsigned long / char*. `found` is the
// pair's bool byte as the guest leaves it: GetValueUTiny's double case returns ((int)v | 0x100) & 0xffff,
// so the byte is (v >> 8) | 1 there (a guest quirk, kept; every caller only tests it for zero).
template <typename T>
struct ParserResult {
    T value;
    u8 found;
};

// CParameterParser: no data, static lookups in an ASON map (port/decomp/params/parser.c;
// ParameterParser.h asserts "apParser is null."). By key: Get*(map, char const* key) is AMap::Get_(key)
// (the keys' C strings); by hash: Get*(map, u32 hash) is GetParserValue, which walks the pairs and
// compares CHash32(key C string) with the hash (string keys only), so the ASON must keep C strings
// (ASON::Init(size, true)). The kinds each getter accepts and how it converts them differ per getter
// (README.md "The parser's kinds"); a key that is missing or of a kind it doesn't take gives {0, false}
// (the by-key getters also build a "not found" message string and drop it: a log compiled out).
class CParameterParser {
public:
    // The pair's value (&pair.value: the AValue at pair + 0x20) whose string key hashes to `hash`, or
    // null (also for hash 0: no scan).
    static const AValue* GetParserValue(const AMap* map, u32 hash);  // _ZN16CParameterParser14GetParserValueEPKN4Aska4ASON6AValue4AMapEj
    // A number value as a double (kinds 2, 3, 4; 0 otherwise). _ZN16CParameterParser8GetValueEPKN4Aska4ASON6AValueE
    static double GetValue(const AValue* v);

    // By hash (_ZN16CParameterParser<n>GetValue<Type>EPKN4Aska4ASON6AValue4AMapEj; the GetValue<T>(map,
    // unsigned) instantiations are the same code: bound to the same members).
    static ParserResult<const char*> GetValueString(const AMap* map, u32 hash);  // the C string, "" when not found
    static ParserResult<float> GetValueFloat(const AMap* map, u32 hash);
    static ParserResult<s32> GetValueInt(const AMap* map, u32 hash);
    static ParserResult<u32> GetValueUInt(const AMap* map, u32 hash);
    static ParserResult<s64> GetValueLong(const AMap* map, u32 hash);
    static ParserResult<u64> GetValueULong(const AMap* map, u32 hash);
    static ParserResult<u8> GetValueBool(const AMap* map, u32 hash);  // (bool: 0 / 1 only, else not found)
    static ParserResult<u8> GetValueUTiny(const AMap* map, u32 hash);
    // GetValue<std::string>(map, unsigned): the pair through x8.
    static void GetValueStdString(libcxx::pair<String, bool>* out, const AMap* map, u32 hash);

    // By key (_ZN16CParameterParser<n>GetValue<Type>EPKN4Aska4ASON6AValue4AMapEPKc; the GetValue<T>(map,
    // char const*) instantiations are 4-byte tail branches to these, or a call and a return).
    static ParserResult<const char*> GetValueString(const AMap* map, const char* key);
    static ParserResult<float> GetValueFloat(const AMap* map, const char* key);
    static ParserResult<s32> GetValueInt(const AMap* map, const char* key);
    static ParserResult<u32> GetValueUInt(const AMap* map, const char* key);
    static ParserResult<s64> GetValueLong(const AMap* map, const char* key);
    static ParserResult<u64> GetValueULong(const AMap* map, const char* key);
    static ParserResult<u8> GetValueBool(const AMap* map, const char* key);
    static ParserResult<u8> GetValueUTiny(const AMap* map, const char* key);
    static void GetValueStdString(libcxx::pair<String, bool>* out, const AMap* map, const char* key);
};
using StdStringResult = libcxx::pair<String, bool>;  // GetValue<std::string>'s pair
static_assert(sizeof(StdStringResult) == 0x20);
static_assert(offsetof(StdStringResult, second) == 0x18);

// ---- the elements and parameters -----------------------------------------------------------------------

// CParameterElementBase: a group of properties deserialized from one ASON map, guest size 0x10. Layout from
// the constructor (vtable, m_first = 0), AddProperty, Deserialize, PrintC (port/decomp/params/base.c).
// Concrete elements (CParameterPlayerElement, ...) embed their properties after it and link them in their
// Initialize (vtable slot 0) with AddProperty.
class CParameterElementBase {
public:
    void Ctor();                    // _ZN21CParameterElementBaseC1Ev (C1 = C2)
    // Virtuals in vtable order (_ZTV21CParameterElementBase):
    void Initialize();              // slot 0: _ZN21CParameterElementBase10InitializeEv (empty)
    bool Deserialize(const AMap* map);  // slot 1: _ZN21CParameterElementBase11DeserializeEPKN4Aska4ASON6AValue4AMapE
                                    // for each pair with a string key (kind 5, C string set): the first
                                    // property whose NameHash() == CHash32(key) gets Deserialize(map); returns 1
    // Derived elements append slots 2 / 3 (their D1 / D0: checked on CParameterPlayerElement).
    void PrintC() const;            // _ZNK21CParameterElementBase6PrintCEv: PrintC of every property
    // Appends p at the end of the list unless found on the way; the last property is not compared (a
    // quirk: adding the last one again links it to itself; see README.md).
    void AddProperty(IParameterProperty* p);  // _ZN21CParameterElementBase11AddPropertyEP18IParameterProperty

    static constexpr int kSlotInitialize = 0, kSlotDeserialize = 1;

    const void* vtable;              // 0x00: _ZTV21CParameterElementBase + 0x10 (or a derived element's)
    IParameterProperty* m_first;     // 0x08: the first property (0 until Initialize links them)
};
static_assert(offsetof(CParameterElementBase, m_first) == 0x08);
static_assert(sizeof(CParameterElementBase) == 0x10);

// CParameterBase: one named parameter document part (the parameter manager's list), guest size 0x08 (the
// constructor stores only the vtable; derived classes start at 0x08). Layout from the constructor, Find,
// pGetRoot (port/decomp/params/base.c) and the derived constructors.
class CParameterBase {
public:
    void CtorBase();                // _ZN14CParameterBaseC2Ev
    // Virtuals in vtable order (_ZTV14CParameterBase):
    void DtorBase();                // slot 0: _ZN14CParameterBaseD2Ev (empty)
    void DtorDelete();              // slot 1: _ZN14CParameterBaseD0Ev (a trap in the base: never deleted as one)
    void Initialize();              // slot 2: _ZN14CParameterBase10InitializeEv (empty)
    const char* pParseName() const; // slot 3 (pure): the key of this part in the parameter document ("Player", ...)
    bool Deserialize(const AMap* map);  // slot 4: _ZN14CParameterBase11DeserializeEPKN4Aska4ASON6AValue4AMapE (returns 1)
    bool ReleaseParameter(const char* name);  // slot 5: _ZN14CParameterBase16ReleaseParameterEPKc (returns 1)
    const AValue* pGetRoot(const AMap* map) const;  // slot 6: _ZNK14CParameterBase8pGetRootEPKN4Aska4ASON6AValue4AMapE:
                                    // AMap::Get_(map, pParseName())
    // Non-virtual:
    bool Find(const AMap* map);     // _ZN14CParameterBase4FindEPKN4Aska4ASON6AValue4AMapE: pGetRoot(map) != 0

    static constexpr int kSlotDtor = 0, kSlotDtorDelete = 1, kSlotInitialize = 2, kSlotParseName = 3, kSlotDeserialize = 4,
                         kSlotReleaseParameter = 5, kSlotGetRoot = 6;

    const void* vtable;  // 0x00: _ZTV14CParameterBase + 0x10 (or a derived class's)
};
static_assert(sizeof(CParameterBase) == 0x08);

// CParameterPlayerElement: the "Player" part's fields, guest size 0x170. Layout from the constructor
// (each property's inlined constructor at its offset), Initialize (names and defaults), the destructor,
// CParameterPlayer::CopyForMultiplay (reads m_id, m_role, m_personId, m_name) (port/decomp/params/concrete.c).
class CParameterPlayerElement {
public:
    void Ctor();                    // _ZN23CParameterPlayerElementC1Ev
    void Dtor();                    // _ZN23CParameterPlayerElementD1Ev
    void DtorDelete();              // _ZN23CParameterPlayerElementD0Ev
    void Initialize();              // slot 0: _ZN23CParameterPlayerElement10InitializeEv: names, defaults, AddProperty x7

    CParameterElementBase base;                     // 0x000
    CParameterPropertyValue<u32, 36> m_id;          // 0x010: "Id" (default 0)
    CParameterPropertyValue<u32, 37> m_token;       // 0x040: "Token" (default 0xffffffff)
    CParameterPropertyValue<u32, 38> m_level;       // 0x070: "Level" (default 0)
    CParameterPropertyValue<s32, 39> m_role;        // 0x0a0: "Role" (default 0)
    CParameterPropertyValue<u32, 40> m_personId;    // 0x0d0: "PersonID" (default 0)
    CParameterPropertyValue<u32, 41> m_weapon;      // 0x100: "Weapon" (default 0)
    CParameterPropertyString<42> m_name;            // 0x130: "Name" (XOR 0x2a; not reset by Initialize)
};
static_assert(offsetof(CParameterPlayerElement, m_id) == 0x010);
static_assert(offsetof(CParameterPlayerElement, m_token) == 0x040);
static_assert(offsetof(CParameterPlayerElement, m_level) == 0x070);
static_assert(offsetof(CParameterPlayerElement, m_role) == 0x0a0);
static_assert(offsetof(CParameterPlayerElement, m_personId) == 0x0d0);
static_assert(offsetof(CParameterPlayerElement, m_weapon) == 0x100);
static_assert(offsetof(CParameterPlayerElement, m_name) == 0x130);
static_assert(sizeof(CParameterPlayerElement) == 0x170);

// CParameterPlayer: the "Player" parameter, guest size 0x180 (CParameterManager::pParameterPlayer, manager
// + 0x40). Layout from the constructor, Deserialize (pGetRoot, Initialize, the element's Deserialize on the
// root's map, m_valid = its result), pParameter (&m_element when m_valid), Initialize (m_valid = 0).
class CParameterPlayer {
public:
    void Ctor();                    // _ZN16CParameterPlayerC1Ev
    // vtable (_ZTV16CParameterPlayer), CParameterBase's slots:
    void Dtor();                    // slot 0: _ZN16CParameterPlayerD2Ev
    void DtorDelete();              // slot 1: _ZN16CParameterPlayerD0Ev
    void Initialize();              // slot 2: _ZN16CParameterPlayer10InitializeEv
    const char* pParseName() const; // slot 3: _ZNK16CParameterPlayer10pParseNameEv ("Player")
    bool Deserialize(const AMap* map);  // slot 4: _ZN16CParameterPlayer11DeserializeEPKN4Aska4ASON6AValue4AMapE
    const CParameterPlayerElement* pParameter() const;  // _ZNK16CParameterPlayer10pParameterEv
    // Aska::Status through x8 (-0x3a5 when not valid): copies Id, Role, PersonID, Name into the
    // multiplay RPC's PlayerDetailInfo (yayoi's struct: +0x6c, +0x2c (u16), +0x14, +0x31 char[0x30]).
    void CopyForMultiplay(void* playerDetailInfo);  // _ZN16CParameterPlayer16CopyForMultiplayEPN4Aska5Yayoi12MultiplayRPC16PlayerDetailInfoE

    CParameterBase base;                // 0x000
    CParameterPlayerElement m_element;  // 0x008
    bool m_valid;                       // 0x178: the last Deserialize found and read the "Player" map
    u8 unk_179[7];                      // 0x179: padding
};
static_assert(offsetof(CParameterPlayer, m_element) == 0x008);
static_assert(offsetof(CParameterPlayer, m_valid) == 0x178);
static_assert(sizeof(CParameterPlayer) == 0x180);

// CParameterCocosCommonResourceElement: one common UI resource, guest size 0xd0 (the unordered_map node's
// value after its 0x18-byte key). Layout from the constructor, Initialize, the destructor and the copy
// constructor (port/decomp/params/concrete.c). The key names are the game's (sic).
class CParameterCocosCommonResourceElement {
public:
    void Ctor();                    // _ZN36CParameterCocosCommonResourceElementC1Ev
    void CtorCopy(const CParameterCocosCommonResourceElement* o);  // ...C1ERKS_ (copies the names, values and list)
    void Dtor();                    // _ZN36CParameterCocosCommonResourceElementD1Ev
    void DtorDelete();              // _ZN36CParameterCocosCommonResourceElementD0Ev
    void Initialize();              // slot 0: _ZN36CParameterCocosCommonResourceElement10InitializeEv

    CParameterElementBase base;                       // 0x00
    CParameterPropertyString<30> m_processingPriority;  // 0x10: "processing_priority" (XOR 0x1e)
    CParameterPropertyString<31> m_destinationName;   // 0x50: "distnation_name" (XOR 0x1f)
    CParameterPropertyString<32> m_sourceName;        // 0x90: "souce_name" (XOR 0x20)
};
static_assert(offsetof(CParameterCocosCommonResourceElement, m_processingPriority) == 0x10);
static_assert(offsetof(CParameterCocosCommonResourceElement, m_destinationName) == 0x50);
static_assert(offsetof(CParameterCocosCommonResourceElement, m_sourceName) == 0x90);
static_assert(sizeof(CParameterCocosCommonResourceElement) == 0xd0);

// CParameterCocosCommonResource: the "CocosCommonResource" parameter, guest size 0x30
// (CParameterManager::pParameterCocosCommonResource, manager + 0x50): a
// Framework::CSTLUnorderedMap<std::string, CParameterCocosCommonResourceElement> (libc++'s unordered_map,
// max_load_factor 1.0f from the constructor). Layout from the constructor, Release / the destructor (walk
// and free the nodes: element at node + 0x28), rParameter (this + 8), Deserialize / DeserializeParameter
// (an ASON array of maps).
class CParameterCocosCommonResource {
public:
    void Ctor();                    // _ZN29CParameterCocosCommonResourceC1Ev
    void Dtor();                    // slot 0: _ZN29CParameterCocosCommonResourceD1Ev
    void DtorDelete();              // slot 1: _ZN29CParameterCocosCommonResourceD0Ev
    const char* pParseName() const; // slot 3: _ZNK29CParameterCocosCommonResource10pParseNameEv ("CocosCommonResource")
    bool Deserialize(const AMap* map);  // slot 4: _ZN29CParameterCocosCommonResource11DeserializeEPKN4Aska4ASON6AValue4AMapE
    void Release();                 // _ZN29CParameterCocosCommonResource7ReleaseEv: clears the map
    const void* rParameter() const; // _ZNK29CParameterCocosCommonResource10rParameterEv: &m_resources
    // static: fills `map` from an array of element maps (_ZN29CParameterCocosCommonResource20DeserializeParameterER...)
    static bool DeserializeParameter(void* map, const AArray* array);

    using Map = libcxx::unordered_map<String, CParameterCocosCommonResourceElement>;

    CParameterBase base;  // 0x00
    Map m_resources;      // 0x08: keyed by each element's processing_priority string (decrypted)
};
static_assert(offsetof(CParameterCocosCommonResource, m_resources) == 0x08);
static_assert(sizeof(CParameterCocosCommonResource) == 0x30);
using CocosCommonResourceNode = libcxx::hash_node<libcxx::pair<String, CParameterCocosCommonResourceElement>>;
static_assert(offsetof(CocosCommonResourceNode, value) == 0x10);
static_assert(sizeof(CocosCommonResourceNode) == 0x10 + 0x18 + 0xd0);

}  // namespace soa::native::params

#endif  // SOA_NATIVE_PARAMS_LAYOUT_H

// data_formats_layout.h: the guest data layouts of the `data_formats` subsystem (ASON, ACSV, msgpack).
//
// Types first (port/PLAN.md task 6): every guest class or struct this subsystem's natives touch is
// recovered here before the code that uses it, as a C++ class with the guest's layout byte for byte
// and the guest's methods attached as members (not a struct + free functions):
//   - fields at the guest's offsets, named after their use (m_hp); unknown bytes as named padding
//     (u8 unk_0c[4]), never offset arithmetic in the natives;
//   - a static_assert per known field offset and one for sizeof, so a wrong guess fails the build;
//   - a comment naming where the layout was read (constructor, decompile in port/decomp/data_formats/).
// Natives are these members (this->m_hp), never *(T*)(p + off). Keep the classes standard-layout (no
// C++ virtual, no non-static members of reference type), so offsetof works. The guest is AArch64 LP64; the
// host (x86-64 / AArch64) has the same sizes and alignments for these plain types.
// `tools/subsystem.py export-types data_formats` turns the structs into port/decomp/data_formats/types.json for Ghidra.
#ifndef SOA_NATIVE_DATA_FORMATS_LAYOUT_H
#define SOA_NATIVE_DATA_FORMATS_LAYOUT_H

#include <cstddef>
#include <cstdint>

#include "../containers/containers_layout.h"
#include "../libcxx/libcxx_layout.h"

namespace soa::native::data_formats {

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;
using s8 = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

// Naming: guest classes nested in another (Aska::ASON::AValue::AMap) are declared flat here (export-types
// sizeof()s every `class X {`); the short guest name is kept where it is unique in the subsystem (AValue,
// AMap, AArray, tElement: tools/subsystem.py attaches symbols.tsv's methods by it), otherwise prefixed
// with the owner (ACSV_AValue = Aska::ACSV::AValue). The Aska / Framework container templates the formats
// embed (TArray, TDynamicArray, TStack, TBitArray) are the `containers` subsystem's types and the std::vector
// libcxx's: included from their layout headers.
// Most methods return Aska::Status (a 64-bit code, < 0 an error: -0x3bd (0xfffffffffffffc43) bad argument,
// -0x3bf no memory, -0x3bc not initialized) through the x8 result pointer, not x0: a native for one of
// those needs a hand-written HostFn (native_method.h: x8 results aren't covered by NATIVE_METHOD).

// Aska::Status: the result of most ASON / ACSV methods, returned through x8.
struct Status {
    s64 code;  // 0 ok; < 0 an error (see above); the deserializers return the byte count read
};
static_assert(sizeof(Status) == 8);

// ---- the container shapes the formats embed: the containers / libcxx subsystems' types ----------------

template <typename T, u32 N>
using TStack = containers::TStack<T, N>;                 // Aska::TStack<T, N>
using TArrayU32 = containers::TArray<u32, false>;        // Aska::TArray<unsigned int, false>
using TBitArrayU32 = containers::TBitArray<u32>;         // Aska::TBitArray<unsigned int, false>
template <typename T>
using StlVector = libcxx::vector<T>;                     // std::__ndk1::vector<T, Framework::CSTLAllocator<...>>

// ---- ASON: Aska's msgpack document --------------------------------------------------------------------

class ASON;
class AValue;
struct ASON_Pair;

// Aska::ASON::AValue::AMap: a map value's body (the 16 bytes at AValue + 8): `this` of AMap::Get_.
// Layout from MakeAValue_Map (n pairs of 0x40 from ASON::Malloc) and AMap::Get_ (linear search).
class AMap {
public:
    // AValue* (the value of the first pair whose key equals the argument), or nullptr.
    AValue* Get_(const AValue* key);  // _ZN4Aska4ASON6AValue4AMap4Get_EPKS1_
    // By a string key: compares the keys' C strings (AValue::m_cstr, only kept when the ASON was
    // Init(..., keepCStrings = true)); keys that aren't strings are skipped.
    AValue* Get_(const char* key);    // _ZN4Aska4ASON6AValue4AMap4Get_EPKc

    ASON_Pair* m_pairs;  // 0x00 (AValue + 0x08)
    u32 m_count;         // 0x08 (AValue + 0x10)
    u16 m_work;          // 0x0c (AValue + 0x14): the work buffer m_pairs is in (ASON::m_workIndex then)
    u8 unk_0e[2];        // 0x0e
};
static_assert(offsetof(AMap, m_count) == 0x08);
static_assert(offsetof(AMap, m_work) == 0x0c);
static_assert(sizeof(AMap) == 0x10);

// Aska::ASON::AValue::AArray: an array value's body (AValue + 8). Layout from MakeAValue_Array
// (n AValues of 0x20) and DeserializeBinary (several roots become one array root).
class AArray {
public:
    AValue* m_elements;  // 0x00 (AValue + 0x08)
    u32 m_count;         // 0x08 (AValue + 0x10)
    u16 m_work;          // 0x0c (AValue + 0x14)
    u8 unk_0e[2];        // 0x0e
};
static_assert(offsetof(AArray, m_count) == 0x08);
static_assert(sizeof(AArray) == 0x10);

// AValue's string body (AValue + 8). Layout from AValue::SetString: the bytes (not terminated) from
// ASON::Malloc, and a terminated copy when the ASON keeps C strings (ASON::m_keepCStrings).
class ASON_StringBody {
public:
    const char* m_data;  // 0x00 (AValue + 0x08): m_length bytes, not terminated
    const char* m_cstr;  // 0x08 (AValue + 0x10): terminated copy, or nullptr
};
static_assert(sizeof(ASON_StringBody) == 0x10);

// AValue's binary / ext body (AValue + 8). Layout from AMap::Get_ (cases 8 and 9: size, then the
// ext type byte) and AValue::Get.
class ASON_BinaryBody {
public:
    const u8* m_data;  // 0x00 (AValue + 0x08)
    u32 m_size;        // 0x08 (AValue + 0x10)
    s8 m_extType;      // 0x0c (AValue + 0x14): msgpack ext type (kind 9 only)
    u8 unk_0d[3];      // 0x0d
};
static_assert(offsetof(ASON_BinaryBody, m_size) == 0x08);
static_assert(offsetof(ASON_BinaryBody, m_extType) == 0x0c);
static_assert(sizeof(ASON_BinaryBody) == 0x10);

// The 16 bytes at AValue + 8, by AValue::m_kind.
union ASON_ValueBody {
    bool b;                     // kind 1
    u64 u;                      // kind 2 (msgpack positive int / uint*)
    s64 s;                      // kind 3 (msgpack negative int / int*)
    double d;                   // kind 4 (msgpack float32 / float64, widened)
    ASON_StringBody str;        // kind 5
    AArray array;               // kind 6
    AMap map;                   // kind 7
    ASON_BinaryBody bin;        // kinds 8 (bin) and 9 (ext)
    u8 raw[16];
};
static_assert(sizeof(ASON_ValueBody) == 0x10);

// Aska::ASON::AValue: one msgpack value, 0x20 bytes. Layout from AValue::SetString, AValue::Get,
// AMap::Get_ (the comparison per kind), MakeAValue_Map / MakeAValue_Array and UnpackMessagePack.
class AValue {
public:
    enum Kind : u32 { kNil = 0, kBool = 1, kUInt = 2, kSInt = 3, kFloat = 4, kString = 5, kArray = 6, kMap = 7,
                      kBinary = 8, kExt = 9 };
    // Aska::Status (x8 result) for both SetString; Get / Set copy the body to / from a buffer (true: ok).
    Status SetString(const char* s, ASON* owner);           // _ZN4Aska4ASON6AValue9SetStringEPKcPS0_
    Status SetString(const char* s, u32 len, ASON* owner);  // _ZN4Aska4ASON6AValue9SetStringEPKcjPS0_
    bool Get(void* out) const;                              // _ZNK4Aska4ASON6AValue3GetEPv
    bool Set(const void* in);                               // _ZN4Aska4ASON6AValue3SetEPKv

    u32 m_kind;            // 0x00: Kind
    u8 unk_04[4];          // 0x04: padding
    ASON_ValueBody m_body; // 0x08
    u32 m_length;          // 0x18: string length (kind 5); 0xffffffff with an empty string's NULL data
    u16 m_dataWork;        // 0x1c: the work buffer of m_body.str.m_data (ASON::m_workIndex then)
    u16 m_cstrWork;        // 0x1e: the work buffer of m_body.str.m_cstr; 0xffff: none
};
static_assert(offsetof(AValue, m_body) == 0x08);
static_assert(offsetof(AValue, m_length) == 0x18);
static_assert(offsetof(AValue, m_dataWork) == 0x1c);
static_assert(offsetof(AValue, m_cstrWork) == 0x1e);
static_assert(sizeof(AValue) == 0x20);

// A map entry: key then value (MakeAValue_Map allocates n * 0x40; AMap::Get_ returns pair + 0x20).
struct ASON_Pair {
    AValue key;    // 0x00
    AValue value;  // 0x20
};
static_assert(offsetof(ASON_Pair, value) == 0x20);
static_assert(sizeof(ASON_Pair) == 0x40);

// Aska::ASON::WorkBufferContext: one block of the ASON's bump allocator. Layout from ASON::InitMemory /
// ASON::Malloc (bump at m_used, rounded to 4) and ASON::Term (delete[] when m_owned).
struct ASON_WorkBufferContext {
    s8* m_buffer;  // 0x00
    u64 m_size;    // 0x08
    u64 m_used;    // 0x10
    bool m_owned;  // 0x18: m_buffer is a new[] (Init / Malloc's growth), not the caller's (InitMemory)
    u8 unk_19[7];  // 0x19
};
static_assert(offsetof(ASON_WorkBufferContext, m_used) == 0x10);
static_assert(offsetof(ASON_WorkBufferContext, m_owned) == 0x18);
static_assert(sizeof(ASON_WorkBufferContext) == 0x20);

// Aska::TDynamicArray<Aska::ASON::WorkBufferContext, Aska::TAllocator<...>>: begin / end / capacity
// (ASON::InitMemory reserves 4 with MemoryManagerAdapter::AlignedMalloc(0x80, 8); Term pops to one).
using TDynamicArrayWorkBuffer = containers::TDynamicArray<ASON_WorkBufferContext>;
static_assert(sizeof(TDynamicArrayWorkBuffer) == 0x20);

// Aska::ASON (an Aska::IAnimatable / IDataFormatter): a msgpack document with its own bump allocator.
// Size 0x90 (port/src/native/api/client_battle_log.cpp: the client's lambdas keep it on the stack).
// Layout from ASON::ASON, Init, InitMemory, Term, ClearRoot, Malloc, TemporaryMalloc / Free, SetRoot,
// DeserializeBinary.
class ASON {
public:
    // Constructors / destructors (bound as Ctor / Dtor: a C++ constructor can't be bound)
    void Ctor();                       // Aska::ASON::ASON()  _ZN4Aska4ASONC1Ev / C2
    void CtorCopy(const ASON* other);  // Aska::ASON::ASON(Aska::ASON const&)  _ZN4Aska4ASONC2ERKS0_
    void CtorMove(u64 move);           // Aska::ASON::ASON(Aska::MoveConstruct<Aska::ASON>)  _ZN4Aska4ASONC1ENS_13MoveConstructIS0_EE
    void Dtor();                       // Aska::ASON::~ASON()  _ZN4Aska4ASOND1Ev
    void DtorDelete();                 // Aska::ASON::~ASON()  _ZN4Aska4ASOND0Ev
    // Virtuals in vtable order (_ZTVN4Aska4ASONE), as plain members: no C++ `virtual` (the guest's vtable is the field)
    // vtable slots 0, 1: the destructors above
    s32 GetClassID(s32) const;                       // vtable slot 2  _ZNK4Aska4ASON10GetClassIDEi
    // vtable slots 3, 4: Aska::IAnimatable::Clone / CreateClone (inherited)
    bool Get(u64 id, void* out) const;               // vtable slot 5  _ZNK4Aska4ASON3GetEmPv
    bool Set(u64 id, const void* in);                // vtable slot 6  _ZN4Aska4ASON3SetEmPKv
    s64 Serialize(void* out, u64 size) const;        // vtable slot 7  _ZNK4Aska4ASON9SerializeEPvm (bytes written, < 0 error)
    s64 Deserialize(const void* in, u64 size);       // vtable slot 8  _ZN4Aska4ASON11DeserializeEPKvm
    s64 CalcSerializedSize() const;                  // vtable slot 9  _ZNK4Aska4ASON18CalcSerializedSizeEv
    // vtable slots 10, 11: Aska::IDataFormatter::Serialize / Deserialize(IStream) (inherited)
    // Methods
    void Copy(const ASON* other, bool deep);         // _ZN4Aska4ASON4CopyERKS0_b
    void Move(ASON* other, bool);                    // _ZN4Aska4ASON4MoveERS0_b
    void Term();                                     // _ZN4Aska4ASON4TermEv
    // operator=(ASON const&) _ZN4Aska4ASONaSERKS0_, operator=(MoveConstruct) _ZN4Aska4ASONaSENS_13MoveConstructIS0_EE
    void CopyMemory_(const ASON* other, bool);       // _ZN4Aska4ASON11CopyMemory_ERKS0_b
    void MoveMemory_(ASON* other, bool);             // _ZN4Aska4ASON11MoveMemory_ERS0_b
    void Swap(ASON* other);                          // _ZN4Aska4ASON4SwapERS0_
    s64 Init(u32 workSize, bool keepCStrings);       // _ZN4Aska4ASON4InitEjb: new[] workSize (>= 0x2000) and InitMemory
    void InitMemory(s8* buffer, u64 size, bool owned);  // _ZN4Aska4ASON10InitMemoryEPamb
    s64 Init(s8* buffer, u32 size, bool keepCStrings);  // _ZN4Aska4ASON4InitEPajb
    void ClearRoot();                                // _ZN4Aska4ASON9ClearRootEv
    void TermMemory();                               // _ZN4Aska4ASON10TermMemoryEv
    s64 DeserializeBinary(const void* in, u64 size); // _ZN4Aska4ASON17DeserializeBinaryEPKvm: msgpack -> m_root (bytes read)
    s64 SerializeBinary(void* out, u64 size, const AValue* v) const;  // _ZNK4Aska4ASON15SerializeBinaryEPvmPKNS0_6AValueE
    // Status PackMessagePack<bool write>(AValue const*, u8* out, u64 size, u64* written) const:
    //   <true> writes v at out (*written: bytes written so far, size: the buffer's), <false> only
    //   counts (Serialize / SerializeBinary write; CalcSerializedSize / ..BinarySize count)
    //   _ZNK4Aska4ASON15PackMessagePackILb1EEENS_6StatusEPKNS0_6AValueEPhmPm / ...ILb0EE...
    template <bool Write>
    Status PackMessagePack(const AValue* v, u8* out, u64 size, u64* written) const;
    s64 CalcRootCount(const s8* in, u64 size);       // _ZN4Aska4ASON13CalcRootCountEPKam
    void AllFree();                                  // _ZN4Aska4ASON7AllFreeEv
    // Status UnpackMessagePack<bool build>(MessagePackContext*, s8 const* in, u64 size, u64* pos)
    //   <false> counts the roots, <true> builds the values (DeserializeBinary runs both)
    //   (msgpack-c's template_execute; both build the containers, only <true> the scalars and strings)
    template <bool Build>
    Status UnpackMessagePack(struct ASON_MessagePackContext* ctx, const s8* in, u64 size, u64* pos);
    s64 SerializeText(void* out, u64 size, const AValue* v) const;   // _ZNK4Aska4ASON13SerializeTextEPvmPKNS0_6AValueE
    void AValue2JValue(const AValue* v, void* jvalue);               // _ZN4Aska4ASON13AValue2JValueEPKNS0_6AValueEPNS_10JsonParser6JValueE
    s64 DeserializeText(const void* in, u64 size);                   // _ZN4Aska4ASON15DeserializeTextEPKvm (JSON)
    void JValue2AValue(const void* jvalue, AValue* v);               // _ZN4Aska4ASON13JValue2AValueEPKNS_10JsonParser6JValueEPNS0_6AValueE
    s64 CalcSerializedBinarySize(const AValue* v) const;             // _ZNK4Aska4ASON24CalcSerializedBinarySizeEPKNS0_6AValueE
    Status GetAValue(const void* keys, s64 n, AValue** out) const;   // _ZNK4Aska4ASON9GetAValueEPKNS0_3KeyElPPNS0_6AValueE
    static Status GetAValue(const AValue* root, const void* keys, s64 n, AValue** out);  // _ZN4Aska4ASON9GetAValueEPKNS0_6AValueEPKNS0_3KeyElPPS1_
    Status GetValue(const void* keys, s64 n, void* out) const;       // _ZNK4Aska4ASON8GetValueEPKNS0_3KeyElPv
    static Status GetValue(const AValue* root, const void* keys, s64 n, void* out);      // _ZN4Aska4ASON8GetValueEPKNS0_6AValueEPKNS0_3KeyElPv
    Status SetValue(const void* keys, s64 n, const void* in);        // _ZN4Aska4ASON8SetValueEPKNS0_3KeyElPKv
    Status SetValue(const AValue* root, const void* keys, s64 n, const void* in);        // _ZN4Aska4ASON8SetValueEPKNS0_6AValueEPKNS0_3KeyElPKv
    Status SetRoot(const AValue* v);                                 // _ZN4Aska4ASON7SetRootEPKNS0_6AValueE: deep copy into m_root
    Status SetAValueRecursive(AValue* dst, const AValue* src);       // _ZN4Aska4ASON18SetAValueRecursiveEPNS0_6AValueEPKS1_
    void CalcFreeWorkSize(s64* free, s64* total);                    // _ZN4Aska4ASON16CalcFreeWorkSizeEPlS1_
    Status MakeAValue_Array(AValue* v, u32 n);                       // _ZN4Aska4ASON16MakeAValue_ArrayEPNS0_6AValueEj
    Status MakeAValue_Map(AValue* v, u32 n);                         // _ZN4Aska4ASON14MakeAValue_MapEPNS0_6AValueEj
    static u64 u64FromAddress(const void* p);                        // _ZN4Aska4ASON14u64FromAddressEPKv
    void PushBackWorkBuffer(s8* buffer, u64 size, bool owned);       // _ZN4Aska4ASON18PushBackWorkBufferEPamb
    void* Malloc(u64 n);                                             // _ZN4Aska4ASON6MallocEm: bump, 4-aligned; grows by m_totalWorkSize
    void RelocateAValueRef(AValue* v, const TDynamicArrayWorkBuffer* old, bool);  // _ZN4Aska4ASON17RelocateAValueRef...
    void ClearWorkBuffer();                                          // _ZN4Aska4ASON15ClearWorkBufferEv
    void* TemporaryMalloc(u64 n);                                    // _ZN4Aska4ASON15TemporaryMallocEm: from m_temp, else new[]
    void TemporaryFree(void* p);                                     // _ZN4Aska4ASON13TemporaryFreeEPv
    void AValue2String(const AValue* v, char** out);                 // _ZN4Aska4ASON13AValue2StringEPKNS0_6AValueEPPc
    // The headers PackMessagePack<true> writes: bytes written (> 0), or -0x3c1 (also m_status) when
    // `room` is too small. _ZNK4Aska4ASON13PackValue_u64ILb1EEElPhmm, ..._s64ILb1EEElPhlm,
    // ..._strILb1EEElPhmm (a string's header), ..._extILb1EEElPhmam (an ext's header, its type byte)
    s64 PackValue_u64(u8* out, u64 v, u64 room) const;
    s64 PackValue_s64(u8* out, s64 v, u64 room) const;
    s64 PackValue_str(u8* out, u64 len, u64 room) const;
    s64 PackValue_ext(u8* out, u64 len, s8 type, u64 room) const;
    // A string UnpackMessagePack<true> read (at p, len bytes of the input at `base`) into v: v points at
    // the input; with m_keepCStrings a terminated copy from Malloc (through a temporary). 0, or < 0
    // (-1, -0x3bf; also m_status). Returns an int (w0), not a Status.
    s32 UnpackValue_str(AValue* v, const s8* base, const s8* p, u32 len, u16 work);  // _ZN4Aska4ASON15UnpackValue_strEPNS0_6AValueEPKaS4_jt

    const void* vtable;                     // 0x00: _ZTVN4Aska4ASONE + 0x10
    s8* m_temp;                             // 0x08: TemporaryMalloc's scratch (0x200 bytes from Malloc)
    u64 m_tempSize;                         // 0x10: 0x200
    u64 m_tempUsed;                         // 0x18
    TDynamicArrayWorkBuffer m_work;       // 0x20: the bump allocator's blocks
    u8 unk_40[8];                           // 0x40: not written by the constructor (TDynamicArray's allocator?)
    ASON_WorkBufferContext* m_currentWork;  // 0x48: the block Malloc bumps
    u64 m_totalWorkSize;                    // 0x50: sum of the blocks' sizes (also the next block's size)
    u16 m_workIndex;                        // 0x58: index of the newest block (stamped into AValue::m_dataWork)
    u8 unk_5a[6];                           // 0x5a
    AValue m_root;                          // 0x60: the document's root (nil after ClearRoot)
    Status m_status;                        // 0x80: the last error
    bool m_keepCStrings;                    // 0x88: Init's flag: strings also get a terminated copy (AMap::Get_(char*) needs it)
    bool m_multiRoot;                       // 0x89: DeserializeBinary found several roots (m_root is then an array of them)
    bool m_initialized;                     // 0x8a: Init done (the deserializers refuse otherwise: -0x3bc)
    u8 unk_8b[5];                           // 0x8b
};
static_assert(offsetof(ASON, m_temp) == 0x08);
static_assert(offsetof(ASON, m_tempSize) == 0x10);
static_assert(offsetof(ASON, m_tempUsed) == 0x18);
static_assert(offsetof(ASON, m_work) == 0x20);
static_assert(offsetof(ASON, m_currentWork) == 0x48);
static_assert(offsetof(ASON, m_totalWorkSize) == 0x50);
static_assert(offsetof(ASON, m_workIndex) == 0x58);
static_assert(offsetof(ASON, m_root) == 0x60);
static_assert(offsetof(ASON, m_status) == 0x80);
static_assert(offsetof(ASON, m_keepCStrings) == 0x88);
static_assert(offsetof(ASON, m_multiRoot) == 0x89);
static_assert(offsetof(ASON, m_initialized) == 0x8a);
static_assert(sizeof(ASON) == 0x90);

// One level of UnpackMessagePack's value stack (msgpack-c's unpack_template.h template_unpack_stack, with
// Aska's values): the container being filled and how far it got. Layout from UnpackMessagePack<true> /
// <false> (frames of 0x50 from context + 0x30: start_container, the push loop) and DeserializeBinary
// (it stamps every frame's m_work with ASON::m_workIndex before a root).
struct ASON_UnpackFrame {
    enum Ct : u32 { kArrayItem = 0, kMapKey = 1, kMapValue = 2 };
    AValue m_value;    // 0x00: the array / map; its body's m_count is the 1-based slot being filled
    u32 m_remaining;   // 0x20: items (pairs) still to read
    u32 m_ct;          // 0x24: Ct, what the next value is
    u16 m_work;        // 0x28: ASON::m_workIndex when the container started (strings / bin / ext read at
                       //       this depth are stamped with it)
    u8 unk_2a[6];      // 0x2a: never written
    AValue m_mapKey;   // 0x30: a map's key until its value is read
};
static_assert(offsetof(ASON_UnpackFrame, m_remaining) == 0x20);
static_assert(offsetof(ASON_UnpackFrame, m_ct) == 0x24);
static_assert(offsetof(ASON_UnpackFrame, m_work) == 0x28);
static_assert(offsetof(ASON_UnpackFrame, m_mapKey) == 0x30);
static_assert(sizeof(ASON_UnpackFrame) == 0x50);

// Aska::ASON::MessagePackContext: UnpackMessagePack's resumable state (msgpack-c's template_context),
// 0xa30 bytes (DeserializeBinary memsets that much on its stack). Layout from UnpackMessagePack<true>
// (it loads the three words at 0x20 on entry and stores them back on exit) and DeserializeBinary (the
// root is frame 0's value).
struct ASON_MessagePackContext {
    AValue m_value;                  // 0x00: the value just read (msgpack-c's obj)
    u32 m_state;                     // 0x20: msgpack-c's cs: 0 at a header byte, else the trail being read
                                     //       (4..0x1f: the header's low 5 bits; 0x20 str, 0x21 bin, 0x22 ext
                                     //       data); after a finished root, the state of its last token
    u32 m_trail;                     // 0x24: the trail's length in bytes
    u32 m_top;                       // 0x28: open containers (m_frames[0..m_top))
    u8 unk_2c[4];                    // 0x2c
    ASON_UnpackFrame m_frames[32];   // 0x30: m_frames[0].m_value is the finished root
};
static_assert(offsetof(ASON_MessagePackContext, m_state) == 0x20);
static_assert(offsetof(ASON_MessagePackContext, m_trail) == 0x24);
static_assert(offsetof(ASON_MessagePackContext, m_top) == 0x28);
static_assert(offsetof(ASON_MessagePackContext, m_frames) == 0x30);
static_assert(sizeof(ASON_MessagePackContext) == 0xa30);

// ---- the client's serializer over ASON ---------------------------------------------------------------

// The containers of _AsonSerializer (instantiations, exported for Ghidra).
using TStackU32 = TStack<u32, 10>;           // Aska::TStack<unsigned int, 10>
using TStackAValue = TStack<AValue*, 10>;    // Aska::TStack<Aska::ASON::AValue*, 10>
using TStackAMap = TStack<AMap*, 10>;        // Aska::TStack<Aska::ASON::AValue::AMap*, 10>
using TStackAArray = TStack<AArray*, 10>;    // Aska::TStack<Aska::ASON::AValue::AArray*, 10>
static_assert(sizeof(TStackU32) == 0x40);
static_assert(offsetof(TStackU32, m_data) == 0x30);
static_assert(offsetof(TStackU32, m_capacity) == 0x38);
static_assert(sizeof(TStackAValue) == 0x68);
static_assert(offsetof(TStackAValue, m_data) == 0x58);
static_assert(offsetof(TStackAValue, m_capacity) == 0x60);

// AsonSerializer_Prepare (a _Serializer<SerializerImpl>): the first pass of AsonSerializer::Serialize<T>,
// counting each object's / array's members. Layout from the inlined constructor in
// AsonSerializer::Serialize<CBattleLogInfo> (the stack object at sp+0x218 there).
class AsonSerializer_Prepare {
public:
    const void* vtable;        // 0x00: _ZTV22AsonSerializer_Prepare + 0x10 (the Serialize_* slots as below)
    s32 m_level;               // 0x08: 0
    s32 m_depth;               // 0x0c: open objects (1 at construction; Increment ++, Serialize_EndObject --)
    TArrayU32 m_counts;      // 0x10: members per object, in visiting order (handed to _AsonSerializer)
    TStackU32 m_levels;      // 0x48
};
static_assert(offsetof(AsonSerializer_Prepare, m_counts) == 0x10);
static_assert(offsetof(AsonSerializer_Prepare, m_levels) == 0x48);
static_assert(sizeof(AsonSerializer_Prepare) == 0x88);

// _AsonSerializer (a _Serializer<SerializerImpl>): AsonSerializer::Serialize<T>'s second pass, building
// the ASON: T::Accept calls the Serialize_* slots. Size 0x218. Layout from the inlined constructor in
// AsonSerializer::Serialize<CBattleLogInfo>, Increment, Serialize_Key / _Value / _StartObject /
// _EndObject / _StartArray.
class _AsonSerializer {
public:
    // Virtuals in vtable order (_ZTV15_AsonSerializer), as plain members: no C++ `virtual`. The value
    // overloads take a reference (here a pointer) to the member being written.
    void Serialize_Key(const char* key);                  // slot 0   _ZN15_AsonSerializer13Serialize_KeyEPKc
    void Serialize_Value(bool* v);                        // slot 1   _ZN15_AsonSerializer15Serialize_ValueERb
    void Serialize_Value(u8* v);                          // slot 2   ...ERh
    void Serialize_Value(s8* v);                          // slot 3   ...ERa
    void Serialize_Value(u16* v);                         // slot 4   ...ERt
    void Serialize_Value(s16* v);                         // slot 5   ...ERs
    void Serialize_Value(u32* v);                         // slot 6   ...ERj
    void Serialize_Value(s32* v);                         // slot 7   ...ERi
    void Serialize_Value(u64* v);                         // slot 8   ...ERm
    void Serialize_Value(s64* v);                         // slot 9   ...ERl
    void Serialize_Value(float* v);                       // slot 10  ...ERf
    void Serialize_ValueString(void* guestString);        // slot 11  ...ERNSt6__ndk112basic_string... (libcxx's String)
    void Serialize_StartObject();                         // slot 12  _ZN15_AsonSerializer21Serialize_StartObjectEv
    void Serialize_EndObject();                           // slot 13  _ZN15_AsonSerializer19Serialize_EndObjectEv
    void Serialize_StartArray(const char* key, u32 n);    // slot 14  _ZN15_AsonSerializer20Serialize_StartArrayEPKcj
    void Serialize_ArrayValue(bool* v);                   // slot 15  _ZN15_AsonSerializer20Serialize_ArrayValueERb
    void Serialize_ArrayValue(u8* v);                     // slot 16
    void Serialize_ArrayValue(s8* v);                     // slot 17
    void Serialize_ArrayValue(u16* v);                    // slot 18
    void Serialize_ArrayValue(s16* v);                    // slot 19
    void Serialize_ArrayValue(u32* v);                    // slot 20
    void Serialize_ArrayValue(s32* v);                    // slot 21
    void Serialize_ArrayValue(u64* v);                    // slot 22
    void Serialize_ArrayValue(s64* v);                    // slot 23
    void Serialize_ArrayValue(float* v);                  // slot 24
    void Serialize_ArrayValueString(void* guestString);   // slot 25
    void Serialize_StartArrayObject(u32 i);               // slot 26  _ZN15_AsonSerializer26Serialize_StartArrayObjectEj
    void Serialize_EndArrayObject(u32 i);                 // slot 27  _ZN15_AsonSerializer24Serialize_EndArrayObjectEj
    void Serialize_EndArray(const char* key, u32 n);      // slot 28  _ZN15_AsonSerializer18Serialize_EndArrayEPKcj
    void Serialize_StartMap(const char* key, u32 n);      // slot 29  _ZN15_AsonSerializer18Serialize_StartMapEPKcj
    void Serialize_StartMapObject(const char* key, u32);  // slot 30  _ZN15_AsonSerializer24Serialize_StartMapObjectEPKcj
    void Serialize_EndMapObject(const char* key, u32);    // slot 31  _ZN15_AsonSerializer22Serialize_EndMapObjectEPKcj
    void Serialize_EndMap(const char* key, u32 n);        // slot 32  _ZN15_AsonSerializer16Serialize_EndMapEPKcj
    // slots 0x60 / 0x68 (12, 13 from the end of _Serializer's table) are the Begin / End the callers run
    // around T::Accept; not in symbols.tsv (inherited).
    void Increment();                                     // _ZN15_AsonSerializer9IncrementEv: push the level, open its index

    const void* vtable;             // 0x000: _ZTV15_AsonSerializer + 0x10
    s32 m_level;                    // 0x008: the current object's index into m_counts / m_indices
    u8 unk_00c[4];                  // 0x00c
    TArrayU32 m_counts;           // 0x010: AsonSerializer_Prepare's member counts (moved in)
    TArrayU32 m_indices;          // 0x048: per open object, the next member's index
    TStackU32 m_levels;           // 0x080: the enclosing m_level values
    ASON* m_ason;                   // 0x0c0: the document being built
    AValue* m_value;                // 0x0c8: the value the next member goes into (first &ason->m_root)
    TStackAValue m_values;        // 0x0d0: the enclosing m_value
    TStackAMap m_maps;            // 0x138: the enclosing m_map
    TStackAArray m_arrays;        // 0x1a0: the enclosing m_array
    AMap* m_map;                    // 0x208: the open object's members (Serialize_Key / _Value write m_map->m_pairs[index])
    AArray* m_array;                // 0x210: the open array
};
static_assert(offsetof(_AsonSerializer, m_level) == 0x008);
static_assert(offsetof(_AsonSerializer, m_counts) == 0x010);
static_assert(offsetof(_AsonSerializer, m_indices) == 0x048);
static_assert(offsetof(_AsonSerializer, m_levels) == 0x080);
static_assert(offsetof(_AsonSerializer, m_ason) == 0x0c0);
static_assert(offsetof(_AsonSerializer, m_value) == 0x0c8);
static_assert(offsetof(_AsonSerializer, m_values) == 0x0d0);
static_assert(offsetof(_AsonSerializer, m_maps) == 0x138);
static_assert(offsetof(_AsonSerializer, m_arrays) == 0x1a0);
static_assert(offsetof(_AsonSerializer, m_map) == 0x208);
static_assert(offsetof(_AsonSerializer, m_array) == 0x210);
static_assert(sizeof(_AsonSerializer) == 0x218);
// SerializerImpl::_Serializer_Impl<KeyValuePair<SerializableArray<T>>> / <SerializableMap<T>>: stateless
// (a static Accept per member type); no layout.

// ---- ACSV: Aska's typed CSV ---------------------------------------------------------------------------

// Aska::ACSV::AValue: one cell, 16 bytes (ACSV::GetValue copies 1 / 2 / 4 / 8 / 16 bytes by type).
struct ACSV_AValue {
    union {
        u8 u8v;        // types 1-3 (bool, s8, u8)
        u16 u16v;      // types 4, 5
        u32 u32v;      // types 6, 7, 10 (float)
        u64 u64v;      // types 8, 9, 11 (double)
        const char* str;  // type 12: the text (not terminated), with m_length
    } m_value;         // 0x00
    u64 m_length;      // 0x08: type 12's length (CACSV::String copies m_length bytes)
};
static_assert(offsetof(ACSV_AValue, m_length) == 0x08);
static_assert(sizeof(ACSV_AValue) == 0x10);

// Aska::ACSV's work memories (WorkMemoryID 0: types, 1: blank bits, 2: values). Layout from
// ACSV::InitMemory / AllocateMemory.
struct ACSV_WorkMemory {
    s8* m_buffer;      // 0x00: in the ACSV's work area, or its own new[] (then m_heapSize != 0)
    u64 m_size;        // 0x08
    u64 m_used;        // 0x10: AllocateMemory's bump
    u64 m_heapSize;    // 0x18
};
static_assert(sizeof(ACSV_WorkMemory) == 0x20);

// Aska::ACSV (an Aska::IAnimatable / IDataFormatter): a typed table, column-major types and row-major cells:
// cell (column c, row r) = m_values[c + m_numColumns * r]. Size 0xe8 (CACSV embeds it at 8 and has a
// field at 0xf0). Layout from ACSV::ACSV (memset 0x78 from 0x70), Init, InitMemory, Term, GetValue and
// CACSV::Value / String / NumRows / NumColumns.
class ACSV {
public:
    enum Type : u32 { kBlank = 0, kBool = 1, kS8 = 2, kU8 = 3, kS16 = 4, kU16 = 5, kS32 = 6, kU32 = 7, kS64 = 8,
                      kU64 = 9, kFloat = 10, kDouble = 11, kString = 12 };
    // Constructors / destructors (bound as Ctor / Dtor: a C++ constructor can't be bound)
    void Ctor();        // Aska::ACSV::ACSV()  _ZN4Aska4ACSVC1Ev
    void DtorBase();    // Aska::ACSV::~ACSV()  _ZN4Aska4ACSVD2Ev
    void DtorDelete();  // Aska::ACSV::~ACSV()  _ZN4Aska4ACSVD0Ev
    // Virtuals in vtable order (_ZTVN4Aska4ACSVE): slots 0, 1 the destructors; 3, 4 IAnimatable::Clone / CreateClone
    s32 GetClassID(s32) const;                   // slot 2   _ZNK4Aska4ACSV10GetClassIDEi
    bool Get(u64 id, void* out) const;           // slot 5   _ZNK4Aska4ACSV3GetEmPv
    bool Set(u64 id, const void* in);            // slot 6   _ZN4Aska4ACSV3SetEmPKv
    s64 Serialize(void* out, u64 size) const;    // slot 7   _ZNK4Aska4ACSV9SerializeEPvm
    s64 Deserialize(const void* in, u64 size);   // slot 8   _ZN4Aska4ACSV11DeserializeEPKvm
    s64 CalcSerializedSize() const;              // slot 9   _ZNK4Aska4ACSV18CalcSerializedSizeEv
    s64 SerializeStream(void* stream) const;     // slot 10  _ZNK4Aska4ACSV9SerializeEPNS_7IStreamE
    s64 DeserializeStream(const void* stream);   // slot 11  _ZN4Aska4ACSV11DeserializeEPKNS_7IStreamE
    // Methods (Status results go through x8)
    void Term();                                                         // _ZN4Aska4ACSV4TermEv
    static u64 CalcWorkSize(u64 columns, u64 rows, u32 extension);       // _ZN4Aska4ACSV12CalcWorkSizeEmmNS0_9ExtensionE
    Status Init(u64 columns, u64 rows, u32 extension);                   // _ZN4Aska4ACSV4InitEmmNS0_9ExtensionE
    Status Init(s8* work, u64 workSize, u64 columns, u64 rows, u32 extension);  // _ZN4Aska4ACSV4InitEPammmNS0_9ExtensionE
    void Clear();                                                        // _ZN4Aska4ACSV5ClearEv
    s64 DeserializeBinary(const void* in, u64 size);                     // _ZN4Aska4ACSV17DeserializeBinaryEPKvm
    Status SetTypes(const u32* types, u64 n);                            // _ZN4Aska4ACSV8SetTypesEPKNS0_4TypeEm
    Status SetBlankBits(const u8* bits, u64 n);                          // _ZN4Aska4ACSV12SetBlankBitsEPKhm
    s64 DeserializeBinaryValues(const void* in, u64 size);               // _ZN4Aska4ACSV23DeserializeBinaryValuesEPKvm
    s64 SerializeBinary(void* stream) const;                             // _ZNK4Aska4ACSV15SerializeBinaryEPNS_7IStreamE
    s64 SerializeBinary(void* out, u64 size, u32 endian) const;          // _ZNK4Aska4ACSV15SerializeBinaryEPvmNS_7Machine6EndianE
    s64 DeserializeText(const void* in, u64 size);                       // _ZN4Aska4ACSV15DeserializeTextEPKvm
    Status AnalyzeTextColumnNum(const void* in, u64 size, u64* columns); // _ZN4Aska4ACSV20AnalyzeTextColumnNumEPKvmPm
    Status AnalyzeTextTypes(const void* in, u64 size, u32* types, u64 n);  // _ZN4Aska4ACSV16AnalyzeTextTypesEPKvmPNS0_4TypeEm
    s64 DeserializeTextValues(const void* in, u64 size);                 // _ZN4Aska4ACSV21DeserializeTextValuesEPKvm
    s64 SerializeText(void* out, u64 size) const;                        // _ZNK4Aska4ACSV13SerializeTextEPvm
    // s64 PackTextValues<1, bool>(char*, u64)  _ZN4Aska4ACSV14PackTextValuesILi1ELb1EEElPcm / ILb0EE
    bool GetValue(u32 type, u64 column, u64 row, void* out) const;       // _ZNK4Aska4ACSV8GetValueENS0_4TypeEmmPv
    bool SetValue(u32 type, u64 column, u64 row, const void* in);        // _ZN4Aska4ACSV8SetValueENS0_4TypeEmmPKv
    void ClearValues();                                                  // _ZN4Aska4ACSV11ClearValuesEv
    void ClearBlankBits();                                               // _ZN4Aska4ACSV14ClearBlankBitsEv
    void ClearTypes();                                                   // _ZN4Aska4ACSV10ClearTypesEv
    void TermMemory(u32 id);                                             // _ZN4Aska4ACSV10TermMemoryENS0_12WorkMemoryIDE
    Status InitMemory(u32 id, u64 size);                                 // _ZN4Aska4ACSV10InitMemoryENS0_12WorkMemoryIDEm
    s64 UnpackBinaryValues(const void* in, u64 size);                    // _ZN4Aska4ACSV18UnpackBinaryValuesEPKvm
    // s64 UnpackTextValues<0|1|2, Unpack{ColumnNum,Type,Value}Args>(Args const*)  _ZN4Aska4ACSV16UnpackTextValuesILi..
    void* AllocateMemory(u32 id, u64 size);                              // _ZN4Aska4ACSV14AllocateMemoryENS0_12WorkMemoryIDEm
    void FreeMemory(u32 id);                                             // _ZN4Aska4ACSV10FreeMemoryENS0_12WorkMemoryIDE
    static s64 EncodeDoubleQuotation(const char* in, u64 n, char* out, u64 size);           // _ZN4Aska4ACSV21EncodeDoubleQuotationEPKcmPcm
    static s64 InsertDoubleQuotation(const char* in, u64 n, char* out, u64 size, s8 quote); // _ZN4Aska4ACSV21InsertDoubleQuotationEPKcmPcma
    static s64 UnpackBinaryValue(const u8* in, u64 size, ACSV_AValue* v, u32 type);         // _ZN4Aska4ACSV17UnpackBinaryValueEPKhmPNS0_6AValueENS0_4TypeE
    static s64 PackBinaryValue(const ACSV_AValue* v, u32 type, void* stream);               // _ZN4Aska4ACSV15PackBinaryValueEPKNS0_6AValueENS0_4TypeEPNS_7IStreamE
    // CalcSizeTextValue<bool> / PackTextValue<bool> / UnpackTextValue<bool>: templates, see symbols.tsv
    static u32 UnpackTextType(const char* in, u64 n, void* priorityContext);                // _ZN4Aska4ACSV14UnpackTextTypeEPKcmPNS0_15PriorityContextE

    const void* vtable;              // 0x00: _ZTVN4Aska4ACSVE + 0x10
    TBitArrayU32 m_blankBits;      // 0x08: bit (c + m_numColumns * r) set: the cell is blank
    ACSV_AValue* m_values;           // 0x30: WorkMemoryID 2
    u32* m_types;                    // 0x38: per column (WorkMemoryID 0)
    u64 m_numColumns;                // 0x40
    u64 m_numRows;                   // 0x48
    u32 m_extension;                 // 0x50: Init's Extension (bit 0: keep blank bits)
    char m_separator;                // 0x54: ','
    u8 unk_55[3];                    // 0x55
    s8* m_workArea;                  // 0x58: Init's work area
    u64 m_workAreaSize;              // 0x60
    bool m_ownsWorkArea;             // 0x68: Init(columns, rows) new[]'d it
    u8 unk_69[7];                    // 0x69
    u64 m_workAreaUsed;              // 0x70: InitMemory's bump in the work area
    u64 m_capColumns;                // 0x78: Init's columns
    u64 m_capRows;                   // 0x80: Init's rows
    ACSV_WorkMemory m_memory[3];     // 0x88: by WorkMemoryID
};
static_assert(offsetof(ACSV, m_blankBits) == 0x08);
static_assert(offsetof(ACSV, m_values) == 0x30);
static_assert(offsetof(ACSV, m_types) == 0x38);
static_assert(offsetof(ACSV, m_numColumns) == 0x40);
static_assert(offsetof(ACSV, m_numRows) == 0x48);
static_assert(offsetof(ACSV, m_extension) == 0x50);
static_assert(offsetof(ACSV, m_separator) == 0x54);
static_assert(offsetof(ACSV, m_workArea) == 0x58);
static_assert(offsetof(ACSV, m_workAreaSize) == 0x60);
static_assert(offsetof(ACSV, m_ownsWorkArea) == 0x68);
static_assert(offsetof(ACSV, m_workAreaUsed) == 0x70);
static_assert(offsetof(ACSV, m_capColumns) == 0x78);
static_assert(offsetof(ACSV, m_capRows) == 0x80);
static_assert(offsetof(ACSV, m_memory) == 0x88);
static_assert(sizeof(ACSV) == 0xe8);

// Framework::CACSV: the Framework's wrapper of an ACSV (text in, values out as float / std::string).
// Layout from CACSV::CACSV (flag, ACSV at 8, a word at 0xf0), Parse, NumRows / NumColumns, Value, String.
class CACSV {
public:
    void Ctor();       // Framework::CACSV::CACSV()  _ZN9Framework5CACSVC1Ev
    void DtorBase();   // Framework::CACSV::~CACSV()  _ZN9Framework5CACSVD2Ev
    void Release();    // _ZN9Framework5CACSV7ReleaseEv
    void Initialize(); // _ZN9Framework5CACSV10InitializeEv
    bool IsParsed() const;                      // _ZNK9Framework5CACSV8IsParsedEv
    void Parse(const char* text);               // _ZN9Framework5CACSV5ParseEPKc: counts the cells, ACSV::Init(columns, rows, 3), DeserializeText
    void AnalyzeCsvTextElement(const char* text, u64* columns, u64* rows);          // _ZN9Framework5CACSV21AnalyzeCsvTextElementEPKcRmS3_
    void ParseBinary(const void* in, u64 size);                                     // _ZN9Framework5CACSV11ParseBinaryEPKvm
    void AnalyzeAcsvBinaryElement(const void* in, u64 size, u64* columns, u64* rows);  // _ZN9Framework5CACSV24AnalyzeAcsvBinaryElementEPKvmRmS3_
    u64 NumRows() const;                        // _ZNK9Framework5CACSV7NumRowsEv: m_acsv.m_numRows
    u64 NumColumns() const;                     // _ZNK9Framework5CACSV10NumColumnsEv: m_acsv.m_numColumns
    void Serialize() const;                     // _ZNK9Framework5CACSV9SerializeEv
    u32 Type(u64 row, u64 column) const;        // _ZNK9Framework5CACSV4TypeEmm
    bool IsBlank(u64 row, u64 column) const;    // _ZNK9Framework5CACSV7IsBlankEmm
    bool IsValue(u64 row, u64 column) const;    // _ZNK9Framework5CACSV7IsValueEmm
    bool IsString(u64 row, u64 column) const;   // _ZNK9Framework5CACSV8IsStringEmm
    // std::string String(row, column) const: x8 result (a guest libc++ string)  _ZNK9Framework5CACSV6StringEmm
    float Value(u64 row, u64 column) const;     // _ZNK9Framework5CACSV5ValueEmm
    void Value(u64 row, u64 column, float v);   // _ZN9Framework5CACSV5ValueEmmf
    void String(u64 row, u64 column, const void* guestString);  // _ZN9Framework5CACSV6StringEmmRKNSt6__ndk112basic_string...
    void PrintC() const;                        // _ZNK9Framework5CACSV6PrintCEv

    bool m_isParsed;   // 0x00
    u8 unk_01[7];      // 0x01
    ACSV m_acsv;       // 0x08
    u64 unk_f0;        // 0xf0: 0 after construction, use unknown
};
static_assert(offsetof(CACSV, m_acsv) == 0x08);
static_assert(offsetof(CACSV, unk_f0) == 0xf0);
static_assert(sizeof(CACSV) == 0xf8);

// ---- CCSV: the Framework's plain CSV --------------------------------------------------------------------

// Framework::CCSV::tElement: one cell, 16 bytes. Layout from its constructors (type 1 + double; type 2 +
// a 0x18-byte guest std::string from the fixed-length STL allocator), Delete, Type / Value / String.
class tElement {
public:
    enum Kind : u32 { kBlank = 0, kValue = 1, kString = 2 };
    void Ctor();                         // tElement()  _ZN9Framework4CCSV8tElementC2Ev
    void Ctor(double v);                 // tElement(double)  _ZN9Framework4CCSV8tElementC1Ed
    void Ctor(const void* guestString);  // tElement(std::string const&)  _ZN9Framework4CCSV8tElementC2ERKNSt6__ndk112basic_string...
    void CtorMove(tElement* other);      // tElement(tElement&&)  _ZN9Framework4CCSV8tElementC2EOS1_
    void CtorCopy(const tElement* other);  // tElement(tElement const&)  _ZN9Framework4CCSV8tElementC1ERKS1_
    void Dtor();                         // ~tElement()  _ZN9Framework4CCSV8tElementD1Ev
    // operator=(tElement const&) _ZN9Framework4CCSV8tElementaSERKS1_, operator=(tElement&&) _ZN9Framework4CCSV8tElementaSEOS1_
    void Delete();                       // _ZN9Framework4CCSV8tElement6DeleteEv: frees the string, kind 0
    bool IsString() const;               // _ZNK9Framework4CCSV8tElement8IsStringEv
    u32 Type() const;                    // _ZNK9Framework4CCSV8tElement4TypeEv: m_kind
    bool IsBlank() const;                // _ZNK9Framework4CCSV8tElement7IsBlankEv
    bool IsValue() const;                // _ZNK9Framework4CCSV8tElement7IsValueEv
    double Value() const;                // _ZNK9Framework4CCSV8tElement5ValueEv
    double ValueSafe(double fallback) const;  // _ZNK9Framework4CCSV8tElement9ValueSafeEd
    const void* String() const;          // _ZNK9Framework4CCSV8tElement6StringEv: the guest std::string*
    const void* StringSafe(const void* fallback) const;  // _ZNK9Framework4CCSV8tElement10StringSafeERK...
    void Value(double v);                // _ZN9Framework4CCSV8tElement5ValueEd
    void String(const void* guestString);  // _ZN9Framework4CCSV8tElement6StringERK...
    void* rString();                     // _ZN9Framework4CCSV8tElement7rStringEv

    u32 m_kind;        // 0x00: Kind
    u8 unk_04[4];      // 0x04
    union {
        double value;  // kind 1
        void* string;  // kind 2: a guest std::__ndk1::basic_string<char, ..., CSTLAllocator> (24 bytes; guest_std.h String)
    } m_data;          // 0x08
};
static_assert(offsetof(tElement, m_data) == 0x08);
static_assert(sizeof(tElement) == 0x10);

// CCSV's rows: std::__ndk1::vector<std::__ndk1::vector<tElement, ...>, ...> (libcxx's vector).
using StlVectorElement = StlVector<tElement>;            // a CCSV row
using StlVectorRow = StlVector<StlVector<tElement>>;     // CCSV's rows
static_assert(sizeof(StlVectorRow) == 0x18);

// Framework::CCSV: rows of cells. Layout from CCSV::CCSV (separator ',', quote '"'), Initialize,
// ~CCSV, NumRows (rows' size / 0x18), NumElements (row's size / 0x10), Element, Separator, Quote.
class CCSV {
public:
    void Ctor();       // Framework::CCSV::CCSV()  _ZN9Framework4CCSVC1Ev
    void DtorBase();   // Framework::CCSV::~CCSV()  _ZN9Framework4CCSVD2Ev
    void Release();    // _ZN9Framework4CCSV7ReleaseEv
    void Initialize(); // _ZN9Framework4CCSV10InitializeEv
    bool IsParsed() const;                     // _ZNK9Framework4CCSV8IsParsedEv
    void Separator(char c);                    // _ZN9Framework4CCSV9SeparatorEc
    void Quote(char c);                        // _ZN9Framework4CCSV5QuoteEc
    void Parse(const char* text, bool);        // _ZN9Framework4CCSV5ParseEPKcb
    void AddParse(const char* text, bool);     // _ZN9Framework4CCSV8AddParseEPKcb
    void AddElementAtLast(const void* guestString, bool);  // _ZN9Framework4CCSV16AddElementAtLastERK...b
    void ParseSingleLine(const char* text, const char** end, bool);  // _ZN9Framework4CCSV15ParseSingleLineEPKcPS2_b
    u64 NumRows() const;                       // _ZNK9Framework4CCSV7NumRowsEv
    u64 MaxElements() const;                   // _ZNK9Framework4CCSV11MaxElementsEv
    u64 NumElements(u64 row) const;            // _ZNK9Framework4CCSV11NumElementsEm
    u64 NumElementsSafe(u64 row) const;        // _ZNK9Framework4CCSV15NumElementsSafeEm
    const tElement* Element(u64 row, u64 i) const;   // _ZNK9Framework4CCSV7ElementEmm
    tElement* rElement(u64 row, u64 i);              // _ZN9Framework4CCSV8rElementEmm
    const tElement* ElementSafe(u64 row, u64 i) const;  // _ZNK9Framework4CCSV11ElementSafeEmm: m_empty when out of range
    bool HasElement(u64 row, u64 i) const;     // _ZNK9Framework4CCSV10HasElementEmm
    void Serialize() const;                    // _ZNK9Framework4CCSV9SerializeEv
    void PrintC() const;                       // _ZNK9Framework4CCSV6PrintCEv
    static void gRegressionTest();             // _ZN9Framework4CCSV15gRegressionTestEv

    bool m_isParsed;     // 0x00
    u8 unk_01;           // 0x01
    char m_separator;    // 0x02: ','
    char m_quote;        // 0x03: '"'
    u8 unk_04[4];        // 0x04
    StlVectorRow m_rows;  // 0x08
    tElement m_empty;    // 0x20: ElementSafe's fallback (blank)
};
static_assert(offsetof(CCSV, m_separator) == 0x02);
static_assert(offsetof(CCSV, m_quote) == 0x03);
static_assert(offsetof(CCSV, m_rows) == 0x08);
static_assert(offsetof(CCSV, m_empty) == 0x20);
static_assert(sizeof(CCSV) == 0x30);

}  // namespace soa::native::data_formats

#endif  // SOA_NATIVE_DATA_FORMATS_LAYOUT_H

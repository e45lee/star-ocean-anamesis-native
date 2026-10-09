// Framework::CHash32: the game's 32-bit name hash (hash_layout.h; port/decomp/hash/chash32.c).
#include <cstdio>
#include <cstring>

#include "soaruntime/core/loader.h"
#include "native/hash/hash_family.h"
#include "native/hash/hash_layout.h"

namespace soa::native::hash {

namespace {

// The guest's table (vaddr 0x2863e48) is zlib's CRC-32 table (test hash/chash32-table).
struct Crc32Table {
    u32 t[256];
    constexpr Crc32Table() : t{} {
        for (u32 i = 0; i < 256; i++) {
            u32 c = i;
            for (int k = 0; k < 8; k++) c = (c & 1) ? (c >> 1) ^ 0xEDB88320u : c >> 1;
            t[i] = c;
        }
    }
};
constexpr Crc32Table kTable;

u64 vtable_addr() {
    static const u64 vt = main_lib()->sym("_ZTVN9Framework7CHash32E") + 0x10;
    return vt;
}

}  // namespace

const u32* chash32_table() { return kTable.t; }

u32 CHash32::Of(const char* s, u64 n) {
    // seeded with the length (its low 32 bits), no final xor; n == 0 leaves it 0
    u32 h = (u32)n;
    for (u64 i = 0; i < n; i++) h = kTable.t[(h ^ (u8)s[i]) & 0xff] ^ (h >> 8);
    return h;
}
u32 CHash32::OfCString(const char* s) { return s ? Of(s, std::strlen(s)) : 0; }

void CHash32::Ctor() {
    vtable = vtable_addr();
    m_hash = 0;
}
void CHash32::Ctor(const char* s) {
    vtable = vtable_addr();
    m_hash = OfCString(s);
}
void CHash32::Ctor(const char* s, u64 n) {
    vtable = vtable_addr();
    m_hash = s ? Of(s, n) : 0;
}
void CHash32::Ctor(const GuestString& s) {
    vtable = vtable_addr();
    m_hash = Of(s.data(), s.size());
}
void CHash32::Ctor(u32 v) {
    vtable = vtable_addr();
    char b[16] = {};
    std::snprintf(b, sizeof b, "%u", v);
    m_hash = OfCString(b);
}
void CHash32::Ctor(s32 v) { Ctor((u32)v); }  // (the guest formats an int with "%u" too)

u32 CHash32::Get() const { return m_hash; }
u32 CHash32::ToU32() const { return m_hash; }
bool CHash32::Eq(const CHash32& o) const { return m_hash == o.m_hash; }
bool CHash32::Eq(const u32& v) const { return m_hash == v; }
bool CHash32::Ne(const CHash32& o) const { return m_hash != o.m_hash; }
bool CHash32::Ne(const u32& v) const { return m_hash != v; }
bool CHash32::Lt(const CHash32& o) const { return m_hash < o.m_hash; }
bool CHash32::Gt(const CHash32& o) const { return o.m_hash < m_hash; }
// (strlen of a null string faults in the guest too)
bool CHash32::Lt(const char* s) const { return m_hash < Of(s, std::strlen(s)); }
bool CHash32::Gt(const char* s) const { return Of(s, std::strlen(s)) < m_hash; }
// The unsigned overloads compare the other way round from their names (a guest quirk, kept).
bool CHash32::Lt(const u32& v) const { return v < m_hash; }
bool CHash32::Gt(const u32& v) const { return m_hash < v; }

CHash32* CHash32::Assign(const char* s) {
    if (!s) {
        static const u64 assert_fn = main_lib()->sym("_ZN9Framework9gDoAssertEPKciS1_z");
        static const char kFile[] = "C:\\BAS_Submission\\Client\\Library\\Framework\\Project\\..\\Source\\Framework\\Hash32.cpp";
        guest_call(assert_fn, {(u64)kFile, 0xda, (u64)"apSrc is null."});
    }
    m_hash = Of(s, std::strlen(s));  // (faults on null after the assert, as the guest does)
    return this;
}
void CHash32::Assign(const GuestString& s) { m_hash = Of(s.data(), s.size()); }

// ---- natives ----

using C = CHash32;
using live::kInt;
using live::kVoid;
constexpr u32 kObj = sizeof(CHash32);  // (the const members snapshot no `this`: it is input only)

LEAF_METHOD(family(), "_ZN9Framework7CHash32C2Ev", static_cast<void (C::*)()>(&C::Ctor), kObj, kVoid, "Framework::CHash32::CHash32()", {});
LEAF_METHOD(family(), "_ZN9Framework7CHash32C2EPKc", static_cast<void (C::*)(const char*)>(&C::Ctor), kObj, kVoid, "Framework::CHash32::CHash32(char const*)", {});
LEAF_METHOD(family(), "_ZN9Framework7CHash32C1EPKcm", static_cast<void (C::*)(const char*, u64)>(&C::Ctor), kObj, kVoid,
            "Framework::CHash32::CHash32(char const*, unsigned long)", {});
LEAF_METHOD(family(), "_ZN9Framework7CHash32C1ERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE",
            static_cast<void (C::*)(const GuestString&)>(&C::Ctor), kObj, kVoid, "Framework::CHash32::CHash32(std::string const&)", {});
LEAF_METHOD(family(), "_ZN9Framework7CHash32C1Ej", static_cast<void (C::*)(u32)>(&C::Ctor), kObj, kVoid, "Framework::CHash32::CHash32(unsigned int)", {});
LEAF_METHOD(family(), "_ZN9Framework7CHash32C2Ei", static_cast<void (C::*)(s32)>(&C::Ctor), kObj, kVoid, "Framework::CHash32::CHash32(int)", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash323GetEv", &C::Get, 0, kInt, "Framework::CHash32::Get", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash32cvjEv", &C::ToU32, 0, kInt, "Framework::CHash32::operator unsigned int", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash32eqERKS0_", static_cast<bool (C::*)(const C&) const>(&C::Eq), 0, kInt, "Framework::CHash32::operator==(CHash32 const&)", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash32eqERKj", static_cast<bool (C::*)(const u32&) const>(&C::Eq), 0, kInt, "Framework::CHash32::operator==(unsigned int const&)", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash32neERKS0_", static_cast<bool (C::*)(const C&) const>(&C::Ne), 0, kInt, "Framework::CHash32::operator!=(CHash32 const&)", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash32neERKj", static_cast<bool (C::*)(const u32&) const>(&C::Ne), 0, kInt, "Framework::CHash32::operator!=(unsigned int const&)", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash32ltERKS0_", static_cast<bool (C::*)(const C&) const>(&C::Lt), 0, kInt, "Framework::CHash32::operator<(CHash32 const&)", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash32gtERKS0_", static_cast<bool (C::*)(const C&) const>(&C::Gt), 0, kInt, "Framework::CHash32::operator>(CHash32 const&)", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash32ltEPKc", static_cast<bool (C::*)(const char*) const>(&C::Lt), 0, kInt, "Framework::CHash32::operator<(char const*)", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash32gtEPKc", static_cast<bool (C::*)(const char*) const>(&C::Gt), 0, kInt, "Framework::CHash32::operator>(char const*)", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash32ltERKj", static_cast<bool (C::*)(const u32&) const>(&C::Lt), 0, kInt, "Framework::CHash32::operator<(unsigned int const&)", {});
LEAF_METHOD(family(), "_ZNK9Framework7CHash32gtERKj", static_cast<bool (C::*)(const u32&) const>(&C::Gt), 0, kInt, "Framework::CHash32::operator>(unsigned int const&)", {});
LEAF_METHOD(family(), "_ZN9Framework7CHash32aSEPKc", static_cast<C* (C::*)(const char*)>(&C::Assign), kObj, kInt, "Framework::CHash32::operator=(char const*)", {});
LEAF_METHOD(family(), "_ZN9Framework7CHash32aSERKNSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEE",
            static_cast<void (C::*)(const GuestString&)>(&C::Assign), kObj, kVoid, "Framework::CHash32::operator=(std::string const&)", {});

}  // namespace soa::native::hash

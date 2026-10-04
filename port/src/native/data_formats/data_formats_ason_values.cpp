// Aska::ASON's value accessors and builders: AMap::Get_, MakeAValue_Array / _Map, AValue::SetString
// (data_formats_layout.h; port/decomp/data_formats/ason.c).
#include <cmath>

#include "native/data_formats/data_formats_ason.h"

namespace soa::native::data_formats {

// The value of the first pair whose key's C string equals `key` (keys that aren't strings, or have no
// C string because the ASON doesn't keep them, never match), else null.
AValue* AMap::Get_(const char* key) {
    if (!key) return nullptr;
    for (u32 i = 0; i < m_count; i++) {
        const AValue& k = m_pairs[i].key;
        if (k.m_kind == AValue::kString && k.m_body.str.m_cstr && std::strcmp(k.m_body.str.m_cstr, key) == 0) return &m_pairs[i].value;
    }
    return nullptr;
}

// The value of the first pair whose key equals *key: same kind, then by kind: nil always, bools by
// truth, integers by bits, doubles by value (NaN never), strings / bin by length and bytes, ext also by
// type, arrays / maps only if they are the same AValue.
AValue* AMap::Get_(const AValue* key) {
    if (!key) return nullptr;
    for (u32 i = 0; i < m_count; i++) {
        AValue& k = m_pairs[i].key;
        if (k.m_kind != key->m_kind) continue;
        bool same = false;
        switch (key->m_kind) {
            case AValue::kNil: same = true; break;
            case AValue::kBool: same = (key->m_body.raw[0] != 0) == (k.m_body.raw[0] != 0); break;
            case AValue::kUInt:
            case AValue::kSInt: same = k.m_body.u == key->m_body.u; break;
            case AValue::kFloat: same = k.m_body.d == key->m_body.d; break;
            case AValue::kString:
                same = k.m_length == key->m_length && std::memcmp(k.m_body.str.m_data, key->m_body.str.m_data, k.m_length) == 0;
                break;
            case AValue::kArray:
            case AValue::kMap: same = key == &k; break;
            case AValue::kExt:
                if ((u8)k.m_body.bin.m_extType != (u8)key->m_body.bin.m_extType) break;
                [[fallthrough]];
            case AValue::kBinary:
                same = k.m_body.bin.m_size == key->m_body.bin.m_size && std::memcmp(k.m_body.bin.m_data, key->m_body.bin.m_data, k.m_body.bin.m_size) == 0;
                break;
            default: break;
        }
        if (same) return &m_pairs[i].value;
    }
    return nullptr;
}

namespace {
// v = an array (map) of n zeroed values (pairs) from the ASON's Malloc. -0x3bd for a null v, -0x3bf
// without memory (both also m_status); n == 0: no storage.
Status make_container(ASON* a, AValue* v, u32 n, u32 kind) {
    s64 code;
    if (!v) {
        code = -0x3bd;
    } else {
        v->m_kind = kind;
        if (n == 0) {
            v->m_body.array.m_count = 0;
            v->m_body.array.m_elements = nullptr;
            return Status{0};
        }
        u64 elem = kind == AValue::kArray ? sizeof(AValue) : sizeof(ASON_Pair);
        if (u8* p = (u8*)a->Malloc((u64)n * elem)) {
            for (u32 k = 0; k < n; k++) {
                auto* x = reinterpret_cast<AValue*>(p + k * elem);
                x->m_kind = 0;
                std::memset(&x->m_body, 0, 0x18);
                if (kind == AValue::kMap) {
                    x = &reinterpret_cast<ASON_Pair*>(x)->value;
                    x->m_kind = 0;
                    std::memset(&x->m_body, 0, 0x18);
                }
            }
            v->m_body.array.m_elements = reinterpret_cast<AValue*>(p);
            v->m_body.array.m_count = n;
            return Status{0};
        }
        code = -0x3bf;
    }
    a->m_status.code = code;
    return Status{code};
}
}  // namespace

Status ASON::MakeAValue_Array(AValue* v, u32 n) { return make_container(this, v, n, AValue::kArray); }
Status ASON::MakeAValue_Map(AValue* v, u32 n) { return make_container(this, v, n, AValue::kMap); }

// This = a string of len bytes of s, copied into the owner's memory (and, when it keeps C strings,
// also a terminated copy made with the guest's _FORTIFY strncpy arithmetic: s's own terminator when it
// is shorter than len). Both stamped with the owner's m_workIndex. -0x3bd for a null s (m_status
// untouched), -0x3bf without memory; an empty string has no storage (data and C string null, length 0).
Status AValue::SetString(const char* s, u32 len, ASON* owner) {
    if (!s) return Status{-0x3bd};
    m_kind = kString;
    if (len == 0) {
        m_body.str.m_cstr = nullptr;
        m_length = 0;
        m_dataWork = 0xffff;
        m_cstrWork = 0xffff;
        m_body.str.m_data = nullptr;
        return Status{0};
    }
    char* data = (char*)owner->Malloc(len);
    m_body.str.m_data = data;
    if (!data) return Status{-0x3bf};
    m_dataWork = owner->m_workIndex;
    std::memcpy(data, s, len);
    m_length = len;
    if (!owner->m_keepCStrings) {
        m_body.str.m_cstr = nullptr;
        m_cstrWork = 0xffff;
        return Status{0};
    }
    char* c = (char*)owner->Malloc((u64)(len + 1));
    m_body.str.m_cstr = c;
    if (!c) return Status{-0x3bf};
    m_cstrWork = owner->m_workIndex;
    u64 l = std::strlen(s), with_nul = l + 1;
    u64 n = with_nul <= len ? (with_nul != len ? l + 1 : l) : len;
    std::strncpy(c, s, n);
    if (with_nul >= len) c[n] = 0;
    return Status{0};
}

Status AValue::SetString(const char* s, ASON* owner) {
    if (!s) return Status{-0x3bd};
    return SetString(s, (u32)std::strlen(s), owner);
}

// ---- natives ----

namespace {
using live::kInt;
using live::kVoid;

void Get_cstr(Cpu& c) { c.set_x(0, (u64)reinterpret_cast<AMap*>(c.x(0))->Get_((const char*)c.x(1))); }
void Get_value(Cpu& c) { c.set_x(0, (u64)reinterpret_cast<AMap*>(c.x(0))->Get_(reinterpret_cast<const AValue*>(c.x(1)))); }
void MakeAValue_Array_(Cpu& c) { ason::set_status(c, reinterpret_cast<ASON*>(c.x(0))->MakeAValue_Array(reinterpret_cast<AValue*>(c.x(1)), (u32)c.x(2))); }
void MakeAValue_Map_(Cpu& c) { ason::set_status(c, reinterpret_cast<ASON*>(c.x(0))->MakeAValue_Map(reinterpret_cast<AValue*>(c.x(1)), (u32)c.x(2))); }
void SetString_(Cpu& c) {
    ason::set_status(c, reinterpret_cast<AValue*>(c.x(0))->SetString((const char*)c.x(1), reinterpret_cast<ASON*>(c.x(2))));
}
void SetString_len(Cpu& c) {
    ason::set_status(c, reinterpret_cast<AValue*>(c.x(0))->SetString((const char*)c.x(1), (u32)c.x(2), reinterpret_cast<ASON*>(c.x(3))));
}

void make_regions(const u64 x[9], live::Regions& r) {
    add_region(r, x[1], sizeof(AValue));
    ason::add_allocator_regions(x[0], r);
}
void set_string_regions(const u64 x[9], live::Regions& r) {
    add_region(r, x[2], sizeof(ASON));
    ason::add_allocator_regions(x[2], r);
}
void set_string_len_regions(const u64 x[9], live::Regions& r) {
    add_region(r, x[3], sizeof(ASON));
    ason::add_allocator_regions(x[3], r);
}
}  // namespace

DF_HOSTFN("_ZN4Aska4ASON6AValue4AMap4Get_EPKc", &Get_cstr, sizeof(AMap), kInt, "Aska::ASON::AValue::AMap::Get_(char const*)", nullptr);
DF_HOSTFN("_ZN4Aska4ASON6AValue4AMap4Get_EPKS1_", &Get_value, sizeof(AMap), kInt, "Aska::ASON::AValue::AMap::Get_(AValue const*)", nullptr);
DF_HOSTFN("_ZN4Aska4ASON16MakeAValue_ArrayEPNS0_6AValueEj", &MakeAValue_Array_, sizeof(ASON), kVoid, "Aska::ASON::MakeAValue_Array", &make_regions);
DF_HOSTFN("_ZN4Aska4ASON14MakeAValue_MapEPNS0_6AValueEj", &MakeAValue_Map_, sizeof(ASON), kVoid, "Aska::ASON::MakeAValue_Map", &make_regions);
DF_HOSTFN("_ZN4Aska4ASON6AValue9SetStringEPKcPS0_", &SetString_, sizeof(AValue), kVoid, "Aska::ASON::AValue::SetString(char const*)",
          &set_string_regions);
DF_HOSTFN("_ZN4Aska4ASON6AValue9SetStringEPKcjPS0_", &SetString_len, sizeof(AValue), kVoid, "Aska::ASON::AValue::SetString(char const*, unsigned)",
          &set_string_len_regions);

}  // namespace soa::native::data_formats

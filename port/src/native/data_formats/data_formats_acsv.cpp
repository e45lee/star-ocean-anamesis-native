// Aska::ACSV::GetValue and Framework::CACSV::Value (data_formats_layout.h;
// port/decomp/data_formats/acsv.c, csv.c): a table cell by type, and as a float.
#include <cstring>

#include "native/data_formats/data_formats_family.h"
#include "native/data_formats/data_formats_layout.h"

namespace soa::native::data_formats {

// Copies cell (column, row) as `type` (1, 2, 4, 8 or 16 bytes; blank: 8 zero bytes) to out. false
// out of range, without out, or for an unknown type.
bool ACSV::GetValue(u32 type, u64 column, u64 row, void* out) const {
    if (column >= m_numColumns || !out || row >= m_numRows) return false;
    const ACSV_AValue& v = m_values[column + m_numColumns * row];
    switch (type) {
        case kBlank: std::memset(out, 0, 8); return true;
        case kBool: case kS8: case kU8: std::memcpy(out, &v, 1); return true;
        case kS16: case kU16: std::memcpy(out, &v, 2); return true;
        case kS32: case kU32: case kFloat: std::memcpy(out, &v, 4); return true;
        case kS64: case kU64: case kDouble: std::memcpy(out, &v, 8); return true;
        case kString: std::memcpy(out, &v, 16); return true;
        default: return false;
    }
}

// Cell (row, column) as a float: 0 when blank, without types, out of range, a string or blank column;
// a bool as 0 / 1; integers converted (signed or unsigned by type), a double rounded.
float CACSV::Value(u64 row, u64 column) const {
    const ACSV& a = m_acsv;
    u64 cell = column + a.m_numColumns * row;
    if (a.m_blankBits.m_bits[(cell >> 5) & 0x7ffffff] & (1u << (cell & 0x1f))) return 0.0f;
    if (!a.m_types || column >= a.m_numColumns) return 0.0f;
    u32 type = a.m_types[column];
    if (type - 1 >= 0xb) return 0.0f;
    union {
        u8 b[8];
        s8 s8v;
        u8 u8v;
        s16 s16v;
        u16 u16v;
        s32 s32v;
        u32 u32v;
        s64 s64v;
        u64 u64v;
        float f;
        double d;
    } v;  // (bytes GetValue doesn't write keep what the stack held: only the typed part is read)
    std::memset(&v, 0, sizeof v);
    a.GetValue(type, column, row, &v);
    switch (type) {
        case ACSV::kS8: return (float)v.s8v;
        case ACSV::kU8: return (float)v.u8v;
        case ACSV::kS16: return (float)v.s16v;
        case ACSV::kU16: return (float)v.u16v;
        case ACSV::kS32: return (float)v.s32v;
        case ACSV::kU32: return (float)v.u32v;
        case ACSV::kS64: return (float)v.s64v;
        case ACSV::kU64: return (float)v.u64v;
        case ACSV::kFloat: return v.f;
        case ACSV::kDouble: return (float)v.d;
        default: return v.u8v ? 1.0f : 0.0f;  // kBool
    }
}

// ---- natives ----

namespace {
void GetValue_(Cpu& c) {
    c.set_x(0, reinterpret_cast<const ACSV*>(c.x(0))->GetValue((u32)c.x(1), c.x(2), c.x(3), (void*)c.x(4)));
}
void Value_(Cpu& c) { c.set_s(0, reinterpret_cast<const CACSV*>(c.x(0))->Value(c.x(1), c.x(2))); }
void get_value_regions(const u64 x[9], live::Regions& r) { add_region(r, x[4], 16); }
}  // namespace

DF_HOSTFN("_ZNK4Aska4ACSV8GetValueENS0_4TypeEmmPv", &GetValue_, 0, live::kInt, "Aska::ACSV::GetValue", &get_value_regions);
DF_HOSTFN("_ZNK9Framework5CACSV5ValueEmm", &Value_, 0, live::kFloat, "Framework::CACSV::Value(row, column)", nullptr);

}  // namespace soa::native::data_formats

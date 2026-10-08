// Framework::CInteroperateParameter's lookups by name (info_layout.h; port/decomp/info/interoperate.c):
// the row / column hashes (std::map<CHash32 of the name, index>, lower_bound as libc++'s) and the
// by-key wrappers of the CSV's IsValue / IsString / Value. Live check (family `info`, run-both): the
// original on the same arguments after the native (they only read), the result registers compared.
#include <cstring>

#include "native/common/live_run_both.h"
#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/hash/hash_layout.h"
#include "native/info/gen/info_addresses.h"
#include "native/info/info_family.h"
#include "native/info/info_guest.h"
#include "native/info/info_layout.h"

namespace soa::native::info {

namespace {

// lower_bound(key) in the map, or its end node.
const libcxx::tree_node_base* find(const NameIndexMap* m, u32 key) {
    auto* end = reinterpret_cast<const libcxx::tree_node_base*>(&m->root);
    const libcxx::tree_node_base* result = end;
    for (auto* nd = reinterpret_cast<const NameIndexNode*>(m->root); nd;) {
        if (!(nd->value.first < key)) {
            result = reinterpret_cast<const libcxx::tree_node_base*>(nd);
            nd = nd->left;
        } else {
            nd = nd->right;
        }
    }
    if (result != end && key < reinterpret_cast<const NameIndexNode*>(result)->value.first) return end;
    return result;
}
u64 index_of(const libcxx::tree_node_base* n) { return reinterpret_cast<const NameIndexNode*>(n)->value.second; }

}  // namespace

bool CInteroperateParameter::IsExist(const char* row) const {
    if (!m_pCSV) g::Assert(g::kInteroperateCpp, 0x14f, g::kCsvIsNull);
    if (!m_pRowHash) g::Assert(g::kInteroperateCpp, 0x150, g::kRowHashIsNull);
    return find(m_pRowHash, hash::CHash32::OfCString(row)) != reinterpret_cast<const libcxx::tree_node_base*>(&m_pRowHash->root);
}

bool CInteroperateParameter::IsExist(const char* row, u64 col) const {
    if (!m_pCSV) g::Assert(g::kInteroperateCpp, 0x158, g::kCsvIsNull);
    if (!m_pRowHash) g::Assert(g::kInteroperateCpp, 0x159, g::kRowHashIsNull);
    const libcxx::tree_node_base* n = find(m_pRowHash, hash::CHash32::OfCString(row));
    if (n == reinterpret_cast<const libcxx::tree_node_base*>(&m_pRowHash->root)) return false;
    if (!m_pCSV) g::Assert(g::kInteroperateCpp, 0x16f, g::kCsvIsNull);
    u64 count = g::vcall(m_pCSV, kCsvNumElements, {index_of(n)});
    u64 cols = count ? count - 1 : 0;
    return col < cols;
}

s32 CInteroperateParameter::ConvertToRow(const char* row) const {
    if (!m_pCSV) g::Assert(g::kInteroperateCpp, 0x214, g::kCsvIsNull);
    if (!m_pRowHash) g::Assert(g::kInteroperateCpp, 0x215, g::kRowHashIsNull);
    const libcxx::tree_node_base* n = find(m_pRowHash, hash::CHash32::OfCString(row));
    return n == reinterpret_cast<const libcxx::tree_node_base*>(&m_pRowHash->root) ? -1 : (s32)index_of(n);
}

s32 CInteroperateParameter::ConvertToColumn(const char* column) const {
    if (!m_pCSV) g::Assert(g::kInteroperateCpp, 0x221, g::kCsvIsNull);
    if (!m_pColumnHash) g::Assert(g::kInteroperateCpp, 0x222, g::kColumnHashIsNull);
    const libcxx::tree_node_base* n = find(m_pColumnHash, hash::CHash32::OfCString(column));
    return n == reinterpret_cast<const libcxx::tree_node_base*>(&m_pColumnHash->root) ? -1 : (s32)index_of(n);
}

namespace {

// ---- the natives and their checks ----

Fn f_is_exist(fam(), "_ZNK9Framework22CInteroperateParameter7IsExistEPKc");
Fn f_is_exist_col(fam(), "_ZNK9Framework22CInteroperateParameter7IsExistEPKcm");
Fn f_row(fam(), "_ZNK9Framework22CInteroperateParameter12ConvertToRowEPKc");
Fn f_column(fam(), "_ZNK9Framework22CInteroperateParameter15ConvertToColumnEPKc");
Fn f_is_value(fam(), "_ZNK9Framework22CInteroperateParameter7IsValueEPKcm");
Fn f_is_string(fam(), "_ZNK9Framework22CInteroperateParameter8IsStringEPKcm");
Fn f_value(fam(), "_ZNK9Framework22CInteroperateParameter5ValueEPKcm");

// A reader's check: the original on the same arguments; the low `bits` of x0 compared (and v0's low 32
// for a float).
void check(Fn& f, Cpu& c, u64 native_x0, u32 bits, bool fp, u32 native_s0) {
    live::RunBothFamily::Scope scope;
    u64 a[3] = {c.x(0), c.x(1), c.x(2)};
    GuestResult g = guest_call_raw(f.orig, a, 3, nullptr, 0, 0);
    u64 mask = bits == 64 ? ~u64(0) : (u64(1) << bits) - 1;
    u32 gs0;
    std::memcpy(&gs0, &g.v0, 4);
    bool ok = fp ? gs0 == native_s0 : (g.x0 & mask) == (native_x0 & mask);
    char m[96];
    snprintf(m, sizeof m, "native %#llx guest %#llx", (unsigned long long)(fp ? native_s0 : native_x0),
             (unsigned long long)(fp ? gs0 : g.x0));
    fam().result(f, ok ? Outcome::Ok : Outcome::Mismatch, ok ? "" : m);
}

const CInteroperateParameter* self(Cpu& c) { return reinterpret_cast<const CInteroperateParameter*>(c.x(0)); }
const char* key(Cpu& c) { return reinterpret_cast<const char*>(c.x(1)); }

void h_is_exist(Cpu& c) {
    bool r = self(c)->IsExist(key(c));
    if (fam().due(f_is_exist)) check(f_is_exist, c, r, 8, false, 0);
    c.set_x(0, r);
}
void h_is_exist_col(Cpu& c) {
    bool r = self(c)->IsExist(key(c), c.x(2));
    if (fam().due(f_is_exist_col)) check(f_is_exist_col, c, r, 8, false, 0);
    c.set_x(0, r);
}
void h_row(Cpu& c) {
    s32 r = self(c)->ConvertToRow(key(c));
    if (fam().due(f_row)) check(f_row, c, (u32)r, 32, false, 0);
    c.set_x(0, (u32)r);
}
void h_column(Cpu& c) {
    s32 r = self(c)->ConvertToColumn(key(c));
    if (fam().due(f_column)) check(f_column, c, (u32)r, 32, false, 0);
    c.set_x(0, (u32)r);
}

// IsValue / IsString / Value(row name, col): the CSV's slot on (ConvertToRow sign-extended, col + 1); its
// result registers handed back as they are.
void by_key(Cpu& c, Fn& f, u32 slot, int line, bool fp) {
    const CInteroperateParameter* t = self(c);
    s32 row = t->ConvertToRow(key(c));
    if (!t->m_pCSV) g::Assert(g::kInteroperateCpp, line, g::kCsvIsNull);
    u64 a[3] = {(u64)t->m_pCSV, (u64)(s64)row, c.x(2) + 1};
    u64 args[3] = {c.x(0), c.x(1), c.x(2)};
    GuestResult r = guest_call_raw(g::slot_of(t->m_pCSV, slot), a, 3, nullptr, 0, 0);
    u32 s0;
    std::memcpy(&s0, &r.v0, 4);
    if (fam().due(f)) {
        live::RunBothFamily::Scope scope;
        GuestResult o = guest_call_raw(f.orig, args, 3, nullptr, 0, 0);
        u32 os0;
        std::memcpy(&os0, &o.v0, 4);
        bool ok = fp ? os0 == s0 : (o.x0 & 0xff) == (r.x0 & 0xff);
        fam().result(f, ok ? Outcome::Ok : Outcome::Mismatch, ok ? "" : "result");
    }
    c.set_x(0, r.x0);
    c.set_v(0, r.v0);
}
void h_is_value(Cpu& c) { by_key(c, f_is_value, kCsvIsValue, 0x1fb, false); }
void h_is_string(Cpu& c) { by_key(c, f_is_string, kCsvIsString, 0x201, false); }
void h_value(Cpu& c) { by_key(c, f_value, kCsvValue, 0x207, true); }

}  // namespace

NATIVE_FUNCTION_ORIG("_ZNK9Framework22CInteroperateParameter7IsExistEPKc", h_is_exist, "info: CInteroperateParameter::IsExist(row)", &f_is_exist.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework22CInteroperateParameter7IsExistEPKcm", h_is_exist_col, "info: CInteroperateParameter::IsExist(row, col)",
                     &f_is_exist_col.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework22CInteroperateParameter12ConvertToRowEPKc", h_row, "info: CInteroperateParameter::ConvertToRow", &f_row.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework22CInteroperateParameter15ConvertToColumnEPKc", h_column, "info: CInteroperateParameter::ConvertToColumn",
                     &f_column.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework22CInteroperateParameter7IsValueEPKcm", h_is_value, "info: CInteroperateParameter::IsValue(row, col)",
                     &f_is_value.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework22CInteroperateParameter8IsStringEPKcm", h_is_string, "info: CInteroperateParameter::IsString(row, col)",
                     &f_is_string.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework22CInteroperateParameter5ValueEPKcm", h_value, "info: CInteroperateParameter::Value(row, col)", &f_value.orig);

}  // namespace soa::native::info

// Differential tests of data_formats_acsv.cpp against the 3.7.0 guest (--selftest data_formats/acsv-):
// random CSV texts parsed by the guest's own CACSV::Parse (column types inferred: bool, every integer
// width, float, double, string, blank cells), then every cell read through the guest and the natives.
#include <cmath>
#include <cstring>
#include <string>

#include "native/common/test.h"
#include "native/data_formats/data_formats_layout.h"

namespace soa::native::data_formats {
namespace {

std::string cell(TestContext& t, int kind) {
    switch (kind) {
        case 0: return t.rand_int(0, 1) ? "true" : "false";
        case 1: return std::to_string(t.rand_int(-100, 100));
        case 2: return std::to_string(t.rand_int(0, 250));
        case 3: return std::to_string(t.rand_int(-30000, 30000));
        case 4: return std::to_string((long long)t.rand_u64() >> t.rand_int(1, 40));
        case 5: return std::to_string(-(long long)(t.rand_u64() >> t.rand_int(1, 40)));
        case 6: return std::to_string(t.rand_u64());
        case 7: return std::to_string(t.rand_int(-100000, 100000) / 7.0);
        case 8: return "s" + std::to_string(t.rand_int(0, 99));
        default: return "";
    }
}

NATIVE_TEST("data_formats/acsv-value") {
    alignas(16) static unsigned char raw[sizeof(CACSV) + 0x40];
    auto* c = reinterpret_cast<CACSV*>(raw);
    for (int k = 0; k < 60; k++) {
        int cols = t.rand_int(1, 8), rows = t.rand_int(1, 12);
        std::vector<int> kinds(cols);
        for (auto& v : kinds) v = t.rand_int(0, 9);
        std::string text;
        for (int r = 0; r < rows; r++) {
            for (int col = 0; col < cols; col++) {
                if (col) text += ",";
                if (t.rand_int(0, 9)) text += cell(t, kinds[col]);
            }
            text += "\n";
        }
        std::memset(raw, 0, sizeof raw);
        t.call("_ZN9Framework5CACSVC1Ev", {(u64)c});
        t.call("_ZN9Framework5CACSV5ParseEPKc", {(u64)c, (u64)text.c_str()});
        const ACSV& a = c->m_acsv;
        for (u64 r = 0; r < a.m_numRows + 1; r++)
            for (u64 col = 0; col < a.m_numColumns + (r < a.m_numRows ? 1 : 0); col++) {
                if (r < a.m_numRows && col < a.m_numColumns) {  // (out of range the guest returns its stack's leftovers)
                    GuestResult g = t.call("_ZNK9Framework5CACSV5ValueEmm", GuestArgs().p(c).i(r).i(col));
                    float gf;
                    std::memcpy(&gf, &g.v0.lo, 4);
                    float nf = c->Value(r, col);
                    if (std::memcmp(&gf, &nf, 4) != 0) {
                        u64 cellno = col + a.m_numColumns * r;
                        t.fail("case %d Value(%llu, %llu): %g vs %g (type %u, blank %u, %llux%llu, value %llx)", k, (unsigned long long)r, (unsigned long long)col, gf,
                               nf, col < a.m_numColumns && a.m_types ? a.m_types[col] : 99u, (a.m_blankBits.m_bits[cellno >> 5] >> (cellno & 31)) & 1,
                               (unsigned long long)a.m_numColumns, (unsigned long long)a.m_numRows, (unsigned long long)a.m_values[cellno].m_value.u64v);
                    }
                }
                for (u32 type = 0; type <= 13; type++) {
                    u8 gb[24], nb[24];
                    std::memset(gb, 0x77, sizeof gb), std::memset(nb, 0x77, sizeof nb);
                    u64 gr = t.call("_ZNK4Aska4ACSV8GetValueENS0_4TypeEmmPv", {(u64)&a, type, col, r, (u64)gb}) & 0xff;
                    u64 nr = a.GetValue(type, col, r, nb);
                    if (gr != nr || std::memcmp(gb, nb, sizeof gb) != 0)
                        t.fail("case %d GetValue(type %u, col %llu, row %llu)", k, type, (unsigned long long)col, (unsigned long long)r);
                }
            }
        if (t.failures()) {
            t.fail("text:\n%s", text.c_str());
            t.call("_ZN9Framework5CACSVD2Ev", {(u64)c});
            return;
        }
        t.call("_ZN9Framework5CACSVD2Ev", {(u64)c});
    }
}

}  // namespace
}  // namespace soa::native::data_formats

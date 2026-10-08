// Differential test of CInteroperateParameter's lookups (info_interoperate.cpp) against the guest's: a
// table the guest builds from CSV text (Initialize with the default CSV accessor), then every lookup by
// the guest's function and by the native on rows and columns that are there and not.
#include <cstring>
#include <string>

#include "native/common/test.h"
#include "native/info/info_layout.h"

namespace soa::native::info {

NATIVE_TEST("info/interoperate") {
    if (!*reinterpret_cast<const u64*>(t.sym("_ZN9Framework22CInteroperateParameter17m_pDefaultKeyWordE"))) {
        t.fail("CInteroperateParameter's default key word isn't set yet");
        return;
    }
    alignas(16) u8 obj[sizeof(CInteroperateParameter)] = {};
    auto* p = reinterpret_cast<CInteroperateParameter*>(obj);
    t.call("_ZN9Framework22CInteroperateParameterC1Ev", {(u64)obj});
    static const char kCsv[] =
        "name,alpha,beta,gamma\n"
        "row_one,1,x,2.5\n"
        "row_two,7,,abc\n"
        "third,0.25,3\n"
        "a_much_longer_row_name_than_twenty_two,9,9,9\n";
    t.call("_ZN9Framework22CInteroperateParameter10InitializeEPKcjPNS0_12ICSVAccessorE", {(u64)obj, (u64)kCsv, 4, 0});
    const char* keys[] = {"name", "row_one", "row_two", "third", "a_much_longer_row_name_than_twenty_two", "missing", "", "alpha",
                          "beta", "gamma", "delta"};
    for (const char* k : keys) {
        if ((t.call("_ZNK9Framework22CInteroperateParameter7IsExistEPKc", {(u64)obj, (u64)k}) & 0xff) != (u64)p->IsExist(k))
            t.fail("IsExist(%s)", k);
        if ((u32)t.call("_ZNK9Framework22CInteroperateParameter12ConvertToRowEPKc", {(u64)obj, (u64)k}) != (u32)p->ConvertToRow(k))
            t.fail("ConvertToRow(%s)", k);
        if (p->m_pColumnHash && (u32)t.call("_ZNK9Framework22CInteroperateParameter15ConvertToColumnEPKc", {(u64)obj, (u64)k}) != (u32)p->ConvertToColumn(k))
            t.fail("ConvertToColumn(%s)", k);
        for (u64 col = 0; col < 5; col++)
            if ((t.call("_ZNK9Framework22CInteroperateParameter7IsExistEPKcm", {(u64)obj, (u64)k, col}) & 0xff) != (u64)p->IsExist(k, col))
                t.fail("IsExist(%s, %llu)", k, (unsigned long long)col);
    }
    if (!p->IsExist("row_one") || p->ConvertToRow("row_two") < 0) t.fail("the test table has no rows (the CSV wasn't read)");
    t.call("_ZN9Framework22CInteroperateParameterD1Ev", {(u64)obj});
}

}  // namespace soa::native::info

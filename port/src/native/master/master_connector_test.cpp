// Differential test of the connectors' natives (master_connector.cpp) against the guest's
// instantiations, on the master the running game has loaded (CStaticTransaction's in-memory database):
// for every connector of gen/master_connectors.inc, QueryToMsgPack with every query number (and one
// past them), the ids of a few rows and one that isn't there, and with a few SQL statements; the
// MessagePack documents must be byte for byte equal. Skipped (with a note) while the game hasn't
// loaded the master yet.
#include <cstring>
#include <string>
#include <vector>

#include "soaruntime/core/log.h"
#include "native/common/guest_std.h"
#include "native/common/test.h"
#include "native/master/master_layout.h"
#include "native/master/master_simple.h"

namespace soa::native::master {

namespace {

struct Syms {
    const char *vtable, *msgpack_id, *msgpack_sql, *result_id, *result_sql, *queries, *keies, *build_query;
    u32 count;
};
#define MASTER_CONNECTOR_ROW(VT, MI, MS, RI, RS, Q, K, BQ, N) {VT, MI, MS, RI, RS, Q, K, BQ, N},
const Syms kRows[] = {
#include "native/master/gen/master_connectors.inc"
    MASTER_CONNECTORS(MASTER_CONNECTOR_ROW)
};
#undef MASTER_CONNECTOR_ROW

std::string compare(const TSharedArray& a, s64 na, const TSharedArray& b, s64 nb) {
    if (na != nb) return "size " + std::to_string(na) + " / " + std::to_string(nb);
    if (na > 0 && std::memcmp(a.m_data, b.m_data, (size_t)na)) return "bytes";
    return {};
}

}  // namespace

NATIVE_TEST("master/connectors") {
    u64 inst = *reinterpret_cast<const u64*>(t.sym("_ZN9Framework10TSingletonI18CStaticTransactionE11m_pInstanceE"));
    if (!inst) {
        LOGW("test", "master/connectors: no CStaticTransaction yet: skipped");
        return;
    }
    int compared = 0;
    for (const Syms& s : kRows) {
        // the connector: its vtable, an empty entity (BuildQuery only compares its address), the id buffer
        auto* c = (CSimpleSqliteConnector*)guest_call(t.sym("_Znwm"), {sizeof(CSimpleSqliteConnector)});
        std::memset(c, 0, sizeof *c);
        c->vtable = (const void*)(t.sym(s.vtable) + 0x10);
        std::vector<u32> ids = {1, 2, 3, 100, 1001, 10001, 0x7fffffff};
        for (u32 q = 0; q <= s.count; q++)
            for (u32 id : ids) {
                if (q == 0 && id != 1) continue;  // (q 0: every row, whatever the id)
                TSharedArray a{}, b{};
                s64 na = 0, nb = 0;
                std::memset(c->m_idText, 0, sizeof c->m_idText);
                guest_call(t.sym(s.msgpack_id), {(u64)c, q, id, (u64)&a, (u64)&na});
                std::memset(c->m_idText, 0, sizeof c->m_idText);
                c->QueryToMsgPack(q, id, &b, &nb);
                std::string why = compare(a, na, b, nb);
                if (!why.empty()) t.fail("%s QueryToMsgPack(%u, %u): %s", s.vtable, q, id, why.c_str());
                SimpleCode::release_array(&a);
                SimpleCode::release_array(&b);
                compared++;
            }
        for (const char* sql : {"SELECT 1 AS a, 'x' AS b", "SELECT name FROM sqlite_master LIMIT 3"}) {  // (no failing SQL: a failing prepare closes the database)
            TSharedArray a{}, b{};
            s64 na = 0, nb = 0;
            guest_call(t.sym(s.msgpack_sql), {(u64)c, (u64)sql, (u64)&a, (u64)&na, 0, 0});
            c->QueryToMsgPackSql(sql, &b, &nb, nullptr, 0);
            std::string why = compare(a, na, b, nb);
            if (!why.empty()) t.fail("%s QueryToMsgPack(%s): %s", s.vtable, sql, why.c_str());
            SimpleCode::release_array(&a);
            SimpleCode::release_array(&b);
            compared++;
        }
        guest_call(t.sym("_ZdlPv"), {(u64)c});
    }
    LOGI("test", "master/connectors: %d queries compared", compared);
}

}  // namespace soa::native::master

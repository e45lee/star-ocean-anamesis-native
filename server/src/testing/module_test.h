#pragma once
// Helpers for a module's tests on a scratch server (ext::with_scratch_server's ext::Ctx). Test
// code: include it only from *_tests.cpp. The older module tests (growth_tests.cpp,
// rules_tests.cpp) still carry their own copies of call / master_id.
#include <string>
#include <utility>
#include <vector>

#include "soaserver/ext.h"

namespace soa::server::module_test {

// Calls the registered handler of `method` with these arguments, as the dispatcher does (no
// transaction, no response hooks); {} when nothing answers it.
inline std::vector<u8> call(ext::Ctx& ctx, const char* method, std::vector<u64> ints, std::vector<std::vector<u64>> vecs = {}) {
    const ext::Handler* handler = ext::find(method);
    if (!handler) return {};
    Request req;
    req.method = method;
    req.ints = std::move(ints);
    req.vecs = std::move(vecs);
    return (*handler)(ctx, req);
}

// The id of the master row of `table` whose id_label is `label` (0 when none).
inline u32 master_id(ext::Ctx& ctx, const char* label, const char* table = "master_item") {
    return (u32)ctx.m.one(std::string("select id from ") + table + " where id_label = ?", {label});
}

// A full-state player response's data, as `method` would answer it: the player state plus every
// OnPlayerLoad hook's keys (login bonus, premium and favor bonuses, achievements, ...).
inline Value player_load_data(ext::Ctx& ctx, const char* method = "GetPlayer") {
    Value data = ctx.base_data();
    Request req;
    req.method = method;
    ext::player_load(ctx, req, data);
    return data;
}

}  // namespace soa::server::module_test

// Unit tests of the social APIs (api/social/social.cpp), on a scratch server seeded from the test
// seed save (--selftest; not differential: the server has no guest counterpart).
#include "soaserver/native_test.h"
#include "soaserver/ext.h"
#include "soaserver/msgpack.h"

namespace soa::server {
namespace {
using namespace ext;

// SearchPlayer: there are no other players, so every search is refused with 10002
// (kPlayerNotFound: the game's "player data not found" dialog; the replay corpora api-sweep and
// profile), the player's own search id too, answering the player state.
NATIVE_TEST("social/search-player") {
    bool ran = with_scratch_server(t.rand_u64(), [&](Ctx& c) {
        c.st.exec("begin");
        const Handler* h = find("SearchPlayer");
        if (!h) return t.fail("SearchPlayer has no handler");
        for (const char* search_id : {"NOBODY0000", "LOCAL00001", ""}) {
            u32 code = 0;
            c.test.on_refuse = [&](u32 e) { code = e; };
            Request r;
            r.method = "SearchPlayer";
            r.strs = {search_id};
            Value d = mp_decode((*h)(c, r));
            t.expect_eq(code, 10002u, "refused with kPlayerNotFound");
            const Value* data = d.find("data");
            t.expect_eq(data && data->find("Player") != nullptr, true, "answers the player state");
        }
    });
    if (!ran) return;  // no 3.7.0 master or save
}

}  // namespace
}  // namespace soa::server

// soa-server's game sessions (server/net/game.h GameServer): a device that bridges again ends its
// earlier unbound sessions (prune_sessions), a session a connection is bound to stays, and the
// session count is capped. Driven through on_data / bridge directly, no sockets.
#include <cstring>
#include <string>
#include <vector>

#include "net/game.h"
#include "net/wire.h"
#include "soaserver/native_test.h"

namespace {

using namespace soa::server;
using namespace soa::server::net;

// A backend without a server: the bridge's device table isn't written (with_state false).
struct NoServer : Backend {
    uint32_t call(const Request&, std::vector<uint8_t>*) override { return kNotHandled; }
    bool with_state(const std::function<void(ext::Sql&)>&) override { return false; }
};

// One clear request on connection `conn`; the reply packet's body.
std::vector<uint8_t> request(GameServer& game, uint64_t conn, const char* api_name, const std::vector<WireArg>& args) {
    const WireApi* api = api_by_name(api_name);
    uint8_t header[16] = {};
    Packet p;
    p.fid = api->fid;
    p.counter = 1;
    p.body = encode_request(*api, header, args);
    std::vector<uint8_t> pkt = encode_packet(p), out;
    game.on_data(conn, pkt.data(), pkt.size(), &out);
    PacketReader reader;
    reader.feed(out.data(), out.size());
    Packet reply;
    return reader.next(&reply) == PacketReader::kPacket ? reply.body : std::vector<uint8_t>();
}

// StartBridge on a new connection, then the bridge POST for `uuid`: the session id ("" on failure).
std::string bridge(GameServer& game, const std::string& uuid, uint64_t* conn_out = nullptr) {
    uint64_t conn = game.open();
    std::vector<uint8_t> start = request(game, conn, "StartBridge", {});
    if (start.size() < 1024) return "";
    std::string token((const char*)start.data(), strnlen((const char*)start.data(), 1024));
    std::string json;
    if (game.bridge(bridge_request_body(uuid, token), &json) != 200) return "";
    std::string sid, key;
    parse_bridge_reply(json, &sid, &key);
    if (conn_out) *conn_out = conn;
    else game.close(conn);
    return sid;
}

NATIVE_TEST("net/session-pruning") {
    NoServer backend;
    GameOptions go;
    go.seed = t.rand_u64();
    GameServer game(backend, go);
    // a device bridging again ends its earlier session (before: every session stayed)
    std::string a1 = bridge(game, "device-a");
    std::string a2 = bridge(game, "device-a");
    t.expect_eq(!a1.empty() && !a2.empty() && a1 != a2, true, "two bridges of device a");
    t.expect_eq(game.session_count(), (size_t)1, "device a's earlier session ended");
    std::string b1 = bridge(game, "device-b");
    t.expect_eq(game.session_count(), (size_t)2, "another device's session stays");
    // a session a connection is bound to (UpdateSession) stays when its device bridges again
    uint64_t conn = game.open();
    WireArg sid;
    sid.s = a2;
    request(game, conn, "UpdateSession", {sid});
    t.expect_eq(game.bound(conn), true, "bound to a2");
    std::string a3 = bridge(game, "device-a");
    t.expect_eq(game.session_count(), (size_t)3, "the bound a2 stays beside a3");
    t.expect_eq(game.key_of(conn).empty(), false, "the bound connection keeps its key");
    game.close(conn);
    bridge(game, "device-a");  // a2 unbound now: it and a3 end
    t.expect_eq(game.session_count(), (size_t)2, "a's unbound sessions ended, b's stays");
    // the cap: many devices, the oldest unbound ones go
    for (size_t k = 0; k < GameServer::kMaxSessions + 10; k++) bridge(game, "many-" + std::to_string(k));
    t.expect_eq(game.session_count(), GameServer::kMaxSessions, "capped at kMaxSessions");
}

}  // namespace

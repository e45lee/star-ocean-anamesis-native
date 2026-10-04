// soa-server end to end over loopback sockets: the poll loop (net/loop.h) on a thread, a scratch
// server behind it, and the wire client (net/client.h) doing what the game does: StartBridge ->
// the HTTP bridge -> UpdateSession -> Login -> GetPlayer -> MissionStart -> MissionEnd with a battle
// log, plus a refusal, a corrupted packet, a request before the bridge and NoLoginStart.
#include "soa/sock.h"
#include <atomic>
#include <thread>

#include "net/client.h"
#include "net/game.h"
#include "net/http.h"
#include "net/loop.h"
#include "net/ninja/ninja_ref.h"
#include "soaserver/msgpack.h"
#include "soaserver/native_test.h"
#include "soaserver/scratch.h"

namespace {

using namespace soa::server;
using namespace soa::server::net;

struct ScratchBackend : Backend {
    testing::Scratch& s;
    explicit ScratchBackend(testing::Scratch& sc) : s(sc) {}
    uint32_t call(const Request& r, std::vector<uint8_t>* out) override { return s.call(r, out); }
    bool with_state(const std::function<void(ext::Sql&)>& fn) override {
        ext::Sql st = s.state();
        fn(st);
        return true;
    }
};

const Value* path(const Value& v, std::initializer_list<const char*> keys) {
    const Value* p = &v;
    for (const char* k : keys) {
        if (!p || p->type != Value::Map) return nullptr;
        p = p->find(k);
    }
    return p;
}

// soa-server over IPv6: --listen / --http [::1]:PORT (parse_host_port), a NoLoginStart on ::1. A
// host without an IPv6 loopback passes with a note.
NATIVE_TEST("net/loopback-ipv6") {
    std::string host;
    uint16_t port = 0;
    t.expect_eq(parse_host_port("[::1]:44300", &host, &port) && host == "::1" && port == 44300, true, "[::1]:44300 parses");
    t.expect_eq(parse_host_port("127.0.0.1:44300", &host, &port) && host == "127.0.0.1", true, "127.0.0.1:44300 parses");
    t.expect_eq(parse_host_port("::1:44300", &host, &port) || parse_host_port("[::1", &host, &port) || parse_host_port(":1", &host, &port), false,
                "a bare IPv6 address with a port, a missing ']' and no host are refused");
    testing::Scratch S(t.rand_u64());
    if (!S.ok()) return;
    ScratchBackend backend(S);
    GameServer game(backend, GameOptions{});
    HttpRouter router;
    router.route("/bridge", game.bridge_handler());
    Loop loop(game, router);
    std::string err;
    if (!loop.listen_game("::1", 0, &err)) {
        printf("      (no IPv6 loopback here: %s)\n", err.c_str());
        return;
    }
    if (!loop.listen_http("::1", 0, &err)) return t.fail("listen_http [::1]: %s", err.c_str());
    std::atomic<bool> stop{false};
    std::thread th([&] {
        while (!stop) loop.run_once(20);
    });
    WireClient c;
    WireReply r;
    bool ok = c.connect("::1", loop.game_port(), &err);
    WireArg id, dev;
    id.s = "abcdefghijklmnop";
    dev.i = 2;
    ok = ok && c.call("NoLoginStart", {id, dev}, &r, &err);
    stop = true;
    th.join();
    if (!ok) return t.fail("NoLoginStart over [::1]: %s", err.c_str());
    t.expect_eq(path(r.msgpack, {"data", "Player"}) != nullptr, true, "NoLoginStartRes over ::1");
}

NATIVE_TEST("net/loopback") {
    testing::Scratch S(t.rand_u64());
    if (!S.ok()) return;  // (the constructor failed the test: no master / seed)
    S.set_live(true);  // the battle log is read as on the live server
    ScratchBackend backend(S);
    GameOptions go;
    go.seed = t.rand_u64();
    GameServer game(backend, go);
    HttpRouter router;
    router.route("/bridge", game.bridge_handler());
    Loop loop(game, router);
    std::string err;
    if (!loop.listen_game("127.0.0.1", 0, &err) || !loop.listen_http("127.0.0.1", 0, &err)) return t.fail("listen: %s", err.c_str());
    const std::string bridge_url = "http://127.0.0.1:" + std::to_string(loop.http_port()) + "/bridge";
    game.set_bridge_url(bridge_url);
    std::atomic<bool> stop{false};
    std::thread th([&] {
        while (!stop) loop.run_once(20);
    });
    auto finish = [&] {
        stop = true;
        th.join();
    };
    const std::string uuid = "11111111-2222-3333-4444-555555555555";
    WireReply r;

    // 1. an encrypted request before the bridge: ProtocolError (the connection has no key)
    {
        WireClient c0;
        if (!c0.connect("127.0.0.1", loop.game_port(), &err)) return finish(), t.fail("%s", err.c_str());
        Packet p;
        p.fid = api_by_name("GetPlayer")->fid;
        p.counter = 9;
        p.flags = kFlagEncrypted;
        p.body = std::vector<uint8_t>(100, 1);
        if (!c0.raw(encode_packet(p), &r, &err)) return finish(), t.fail("pre-bridge: %s", err.c_str());
        t.expect_eq(r.protocol_error, true, "pre-bridge request refused");
        t.expect_eq(r.status, kStatusCommError, "pre-bridge status");
        t.expect_eq(r.failing_fid, p.fid, "pre-bridge failing fid");
        // NoLoginStart needs no bridge (clear request, clear reply); a new connection (the
        // ProtocolError closed this one)
        WireClient c1;
        if (!c1.connect("127.0.0.1", loop.game_port(), &err)) return finish(), t.fail("%s", err.c_str());
        WireArg id, dev;
        id.s = "abcdefghijklmnop";
        dev.i = 2;
        if (!c1.call("NoLoginStart", {id, dev}, &r, &err)) return finish(), t.fail("NoLoginStart: %s", err.c_str());
        t.expect_eq(r.flags, (uint8_t)0, "NoLoginStartRes in the clear");
        t.expect_eq(path(r.msgpack, {"data", "Player"}) != nullptr, true, "NoLoginStartRes data.Player");
    }
    // 2. a bridge POST with an unknown token is refused
    {
        int status = 0;
        std::string reply;
        if (!http_post(bridge_url, "{\"UUID\":\"x\",\"deviceType\":\"2\",\"nativeToken\":\"nope\"}", &status, &reply, &err))
            return finish(), t.fail("%s", err.c_str());
        t.expect_eq(status, 403, "unknown token");
    }
    // 3. the session
    WireClient c;
    if (!c.connect("127.0.0.1", loop.game_port(), &err)) return finish(), t.fail("%s", err.c_str());
    if (!c.bridge(uuid, &err)) return finish(), t.fail("bridge: %s", err.c_str());
    t.expect_eq(c.key().size() >= ninja::kKeySize && c.key()[0] != 0, true, "a printable key of >= 32 characters");
    t.expect_eq(c.session().size(), (size_t)32, "session id fits UpdateSession's char[32]");
    t.expect_eq(game.session_count(), (size_t)1, "one session");
    t.expect_eq(S.state().one("select count(*) from wire_device where uuid = ? and player_id = (select id from player)", {uuid}), (int64_t)1,
                "device -> the server's player");
    // Login, in a non-AES cipher (the client picks one at random per message)
    if (!c.call("Login", {WireArg{0, uuid}, WireArg{0, "token"}, WireArg{0, "00000000-0000-0000-0000-000000000000"}, WireArg{}}, &r, &err,
                ninja::kTwofish))
        return finish(), t.fail("Login: %s", err.c_str());
    t.expect_eq(r.protocol_error, false, "Login accepted");
    t.expect_eq(r.flags, kFlagEncrypted, "LoginResult encrypted");
    t.expect_eq(r.alg, (uint32_t)ninja::kAES128, "reply cipher");
    t.expect_eq(r.login_fid, 0xa01c67efu, "LoginResult's fid word");
    t.expect_eq(path(r.msgpack, {"status"}) != nullptr && path(r.msgpack, {"data", "Player", "id"}) != nullptr, true,
                "LoginResult {data.Player, status}");
    {
        // the root Player the client's CParameterPlayer reads (LoggedIn: its Id != 0)
        const Value* id = path(r.msgpack, {"Player", "Id"});
        const Value* did = path(r.msgpack, {"data", "Player", "id"});
        t.expect_eq(id && did && id->u == (did->u & 0xffffffffu) && id->u != 0, true, "LoginResult root Player.Id = data.Player.id");
    }
    // the GetPlayerRes after it, which ends the client's login request (game.cpp)
    t.expect_eq(fid_name(r.followup_fid) ? std::string(fid_name(r.followup_fid)) : "", std::string("GetPlayerRes"), "Login's follow-up GetPlayerRes");
    t.expect_eq(path(r.followup, {"data", "Player", "id"}) != nullptr, true, "the follow-up carries data.Player");
    if (!c.call("GetPlayer", {}, &r, &err, ninja::kMARS)) return finish(), t.fail("GetPlayer: %s", err.c_str());
    t.expect_eq(fid_name(r.fid) ? std::string(fid_name(r.fid)) : "", std::string("GetPlayerRes"), "GetPlayerRes");
    const Value* ch = path(r.msgpack, {"data", "Character"});
    t.expect_eq(ch && ch->type == Value::Arr && !ch->arr.empty(), true, "GetPlayerRes data.Character");
    // a battle: MissionStart, MissionEnd with the battle log (its mission_time comes back)
    u32 mission = S.id("master_mission", "mf01_001");
    S.state().q("update player set stamina = 200", {});
    if (!c.call("MissionStart", {WireArg{0}, WireArg{mission}, WireArg{}, WireArg{}, WireArg{}, WireArg{}, WireArg{}}, &r, &err, ninja::kSEED))
        return finish(), t.fail("MissionStart: %s", err.c_str());
    t.expect_eq(r.protocol_error, false, "MissionStart accepted");
    t.expect_eq(path(r.msgpack, {"data"}) != nullptr, true, "MissionStartRes data");
    Value log = Value::object();
    log["is_defeat"] = false;
    log["mission_time"] = 83456u;
    log["battle_result"] = 1u;
    log["BattleEvaluationInfo"] = Value::array();
    auto lb = mp_encode(log);
    if (!c.call("MissionEnd", {WireArg{mission}, WireArg{0, std::string(lb.begin(), lb.end())}, WireArg{0}}, &r, &err, ninja::kIDEA))
        return finish(), t.fail("MissionEnd: %s", err.c_str());
    t.expect_eq(r.protocol_error, false, "MissionEnd accepted");
    const Value* mt = path(r.msgpack, {"data", "MissionEndResult", "mission_time"});
    t.expect_eq(mt ? mt->u : 0, (uint64_t)83456, "MissionEndResult.mission_time from the wire's battle log");
    // a refusal: a box gacha without its event coins -> ProtocolError with the server's code
    u32 box = S.id("master_gacha", "box_event_gacha_yumenonagisa_003");
    if (!c.call("BoxGacha", {WireArg{box}, WireArg{3}}, &r, &err)) return finish(), t.fail("BoxGacha: %s", err.c_str());
    t.expect_eq(r.protocol_error, true, "BoxGacha refused");
    t.expect_eq(r.status, (int64_t)10206, "the server's error code as the status");
    t.expect_eq(r.failing_fid, api_by_name("BoxGacha")->fid, "failing fid");
    {
        // the server closes the connection after a ProtocolError (game.cpp on_data)
        uint8_t b;
        int n = (int)soa::sock::recv(c.fd(), &b, 1);
        t.expect_eq(n, 0, "connection closed after the ProtocolError");
    }
    // a reconnect continues the session without StartBridge / UpdateSession (the logged-in
    // client's next request; game.cpp handle_packet)
    WireClient c2;
    if (!c2.connect("127.0.0.1", loop.game_port(), &err)) return finish(), t.fail("%s", err.c_str());
    c2.adopt_session(c);
    if (!c2.call("GetServerTime", {}, &r, &err, ninja::kCAST128)) return finish(), t.fail("GetServerTime after reconnect: %s", err.c_str());
    t.expect_eq(r.protocol_error == false && path(r.msgpack, {"data", "Time"}) != nullptr, true, "reconnect rebound to the session");
    // a corrupted packet (SHA-1): ProtocolError (then the connection closes)
    {
        Packet p;
        p.fid = api_by_name("GetServerTime")->fid;
        p.counter = 77;
        p.body = {1, 2, 3};
        auto b = encode_packet(p);
        b.back() ^= 1;
        if (!c2.raw(b, &r, &err)) return finish(), t.fail("corrupted: %s", err.c_str());
        t.expect_eq(r.protocol_error && r.counter == 77, true, "corrupted packet refused");
    }
    WireClient c3;
    if (!c3.connect("127.0.0.1", loop.game_port(), &err)) return finish(), t.fail("%s", err.c_str());
    c3.adopt_session(c);
    if (!c3.call("GetServerTime", {}, &r, &err)) return finish(), t.fail("GetServerTime: %s", err.c_str());
    t.expect_eq(path(r.msgpack, {"data", "Time"}) != nullptr, true, "GetServerTimeRes data.Time");
    // an API the server doesn't implement: data.Time only (d)
    if (!c3.call("DebugGetCoin", {WireArg{5}}, &r, &err)) return finish(), t.fail("DebugGetCoin: %s", err.c_str());
    t.expect_eq(r.protocol_error == false && path(r.msgpack, {"data", "Time"}) != nullptr, true, "not implemented -> data.Time");
    finish();
}

// GameOptions::close_after_refusal: a ProtocolError ends the connection by default (on_data
// returns false); --keep-open-after-error (false) keeps it open for the next request.
NATIVE_TEST("net/close-after-refusal") {
    struct NoBackend : Backend {
        uint32_t call(const Request&, std::vector<uint8_t>*) override { return 0; }
        bool with_state(const std::function<void(ext::Sql&)>&) override { return false; }
    } backend;
    // An encrypted request on a connection without a session: refused with a ProtocolError.
    Packet p;
    p.fid = api_by_name("GetPlayer")->fid;
    p.counter = 9;
    p.flags = kFlagEncrypted;
    p.body = std::vector<uint8_t>(100, 1);
    const std::vector<uint8_t> pkt = encode_packet(p);
    for (bool close : {true, false}) {
        GameOptions go;
        go.seed = t.rand_u64();
        go.close_after_refusal = close;
        GameServer game(backend, go);
        uint64_t id = game.open();
        std::vector<uint8_t> out;
        bool open = game.on_data(id, pkt.data(), pkt.size(), &out);
        t.expect_eq(out.empty(), false, "a ProtocolError was sent");
        t.expect_eq(open, !close, close ? "the connection closes (default)" : "the connection stays open (keep-open)");
        game.close(id);
    }
}

}  // namespace

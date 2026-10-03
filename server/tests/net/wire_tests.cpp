// soa-server's wire layer (server/net/wire.h): packets, the request decoder, the battle log,
// reply bodies. Ground truth: the client's own serializers (client_requests.txt, written by
// server/tests/ninja/tools/gen_ninja_vectors.py requests under unicorn) and docs/api.md's measured
// example packet.
#include <algorithm>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "net/ninja/ninja_ref.h"
#include "net/wire.h"
#include "soaserver/config.h"
#include "soaserver/msgpack.h"
#include "soaserver/native_test.h"

namespace {

using namespace soa::server;
using namespace soa::server::net;

NATIVE_TEST("net/header-scramble") {
    // docs/api.md "Wire format": the clear NoLoginStartRes packet [run]
    std::vector<uint8_t> h = unhex("003dcc15003ff10d513ff1ccd9d9daa8143fab963d0d0000");
    HeaderFields f = unscramble_header(h.data());
    t.expect_eq(f.t, 0x00000d3dccf13f15ull, "timestamp");
    t.expect_eq(f.size, 68u, "size");
    t.expect_eq(f.fid, 0xa8dad4e4u, "fid");
    t.expect_eq(f.counter, 0x5a5a0001u, "counter");
    t.expect_eq((int)f.flags, 0, "flags");
    uint8_t back[24];
    scramble_header(back, f);
    t.expect_eq(std::vector<uint8_t>(back, back + 24), h, "re-scrambled");
    for (int k = 0; k < 200; k++) {
        HeaderFields g;
        g.size = (uint32_t)t.rand_u64(), g.fid = (uint32_t)t.rand_u64(), g.counter = (uint32_t)t.rand_u64();
        g.flags = (uint8_t)t.rand_u64(), g.t = t.rand_u64();
        uint8_t b[24];
        scramble_header(b, g);
        HeaderFields r = unscramble_header(b);
        if (r.size != g.size || r.fid != g.fid || r.counter != g.counter || r.flags != g.flags || r.t != g.t) t.fail("round trip %d", k);
        if (b[21] != (uint8_t)(g.t >> 40) || b[22] != (uint8_t)(g.t >> 48) || b[23] != (uint8_t)(g.t >> 56)) t.fail("pad bytes %d", k);
    }
}

NATIVE_TEST("net/packet-roundtrip") {
    std::vector<Packet> sent;
    std::vector<uint8_t> stream;
    for (int k = 0; k < 40; k++) {
        Packet p;
        p.fid = (uint32_t)t.rand_u64();
        p.counter = (uint32_t)k;
        p.flags = k & 1 ? kFlagEncrypted : 0;
        p.body = t.rand_bytes((size_t)t.rand_int(0, 3000));
        auto b = encode_packet(p, t.rand_u64());
        if (b.size() != 24 + p.body.size() + 20) t.fail("packet %d size %zu", k, b.size());
        stream.insert(stream.end(), b.begin(), b.end());
        sent.push_back(p);
    }
    // fed in random pieces
    PacketReader rd;
    size_t o = 0, got = 0;
    while (o < stream.size() || rd.buffered()) {
        size_t n = std::min(stream.size() - o, (size_t)t.rand_int(1, 700));
        rd.feed(stream.data() + o, n);
        o += n;
        Packet p;
        PacketReader::Result r;
        while ((r = rd.next(&p)) == PacketReader::kPacket) {
            if (got >= sent.size() || p.fid != sent[got].fid || p.counter != sent[got].counter || p.flags != sent[got].flags ||
                p.body != sent[got].body)
                t.fail("packet %zu differs", got);
            got++;
        }
        if (r != PacketReader::kNeedMore) return t.fail("reader result %d", (int)r);
        if (n == 0 && o >= stream.size()) break;
    }
    t.expect_eq(got, sent.size(), "packets read");
    // a corrupted SHA-1, a corrupted body: refused (consumed), the next packet still reads
    for (size_t pos : {(size_t)30, (size_t)0}) {
        Packet a, b;
        a.fid = 1, a.body = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        b.fid = 2, b.body = {9};
        auto s1 = encode_packet(a), s2 = encode_packet(b);
        if (pos) s1[pos] ^= 1;               // body byte
        else s1[s1.size() - 1] ^= 0x80;      // the trailer
        PacketReader r2;
        r2.feed(s1.data(), s1.size());
        r2.feed(s2.data(), s2.size());
        Packet p;
        t.expect_eq((int)r2.next(&p), (int)PacketReader::kBadSha, "corrupted packet refused");
        t.expect_eq((int)r2.next(&p), (int)PacketReader::kPacket, "next packet");
        t.expect_eq(p.fid, 2u, "next packet fid");
    }
    // an impossible size
    Packet a;
    auto s = encode_packet(a);
    HeaderFields f = unscramble_header(s.data());
    f.size = 3;
    scramble_header(s.data(), f);
    PacketReader r3;
    r3.feed(s.data(), s.size());
    Packet p;
    t.expect_eq((int)r3.next(&p), (int)PacketReader::kBadSize, "size < 24");
}

// What decode_request must produce for random arguments of an API (the shims written out again).
struct Expect {
    std::vector<uint64_t> ints;
    std::vector<std::string> strs;
    std::vector<std::vector<uint64_t>> vecs;
    bool dev = false;
    uint32_t dev_value = 0;
    std::string log;
};

std::string rand_text(testing::Context& t, size_t max) {
    std::string s;
    size_t n = (size_t)t.rand_int(1, (int)max);
    for (size_t i = 0; i < n; i++) s += (char)t.rand_int(0x21, 0x7e);
    return s;
}

NATIVE_TEST("net/decoder-roundtrip") {
    const char* logs[] = {"MissionEnd", "MissionFailed", "Sphere211MissionEnd", "Sphere211MissionFailed"};
    t.expect_eq(apis().size(), (size_t)193, "requests in the table");
    for (const WireApi& api : apis()) {
        for (int rep = 0; rep < 4; rep++) {
            uint8_t hdr[16];
            for (auto& b : hdr) b = (uint8_t)t.rand_u64();
            std::vector<WireArg> args;
            Expect e;
            bool is_log = false;
            for (const char* l : logs) is_log |= api.name == l;
            for (const std::string& tok : api.layout) {
                WireArg a;
                if (tok == "u8" || tok == "s8") a.i = t.rand_u64() & 0xff, e.ints.push_back(a.i);
                else if (tok == "u32" || tok == "s32" || tok == "f32") a.i = t.rand_u64() & 0xffffffff, e.ints.push_back(a.i);
                else if (tok == "u64") a.i = t.rand_u64(), e.ints.push_back(a.i);
                else if (tok == "dev") a.i = (uint64_t)t.rand_int(0, 99), e.dev = true, e.dev_value = (uint32_t)a.i;
                else if (tok.rfind("str[", 0) == 0) {
                    size_t w = (size_t)atoi(tok.c_str() + 4);
                    a.s = rand_text(t, rep == 3 ? w : w - 1);  // rep 3: a field filled to the last byte (no NUL)
                    e.strs.push_back(a.s);
                } else if (tok == "blob") {
                    if (is_log) {
                        Value m = Value::object();
                        m["mission_time"] = (unsigned)t.rand_int(1, 1000000);
                        a.s.assign((const char*)mp_encode(m).data(), mp_encode(m).size());
                        e.log = std::to_string(m.find("mission_time")->u);
                    } else {
                        auto b = t.rand_bytes((size_t)t.rand_int(0, 300));
                        a.s.assign(b.begin(), b.end());
                        e.strs.push_back(a.s);
                    }
                } else if (tok == "vec64" || tok == "vec32") {
                    int n = t.rand_int(0, 12);
                    for (int i = 0; i < n; i++) a.v.push_back(tok == "vec64" ? t.rand_u64() : t.rand_u64() & 0xffffffff);
                    e.vecs.push_back(a.v);
                } else {
                    t.fail("%s: token %s", api.name.c_str(), tok.c_str());
                }
                args.push_back(a);
            }
            if (api.name == "CreatePlayer") std::swap(e.strs[0], e.strs[1]);
            if (api.name == "Login" || api.name == "SimpleLogin") e.ints.clear(), e.strs.clear();
            auto body = encode_request(api, hdr, args);
            Decoded d;
            std::string err;
            if (!decode_request(api, body.data(), body.size(), &d, &err)) {
                t.fail("%s: %s", api.name.c_str(), err.c_str());
                continue;
            }
            if (d.req.method != api.method || d.req.fid != api.fid) t.fail("%s: method/fid", api.name.c_str());
            if (memcmp(d.header, hdr, 16)) t.fail("%s: header", api.name.c_str());
            if (d.req.ints != e.ints) t.fail("%s: ints", api.name.c_str());
            if (d.req.strs != e.strs) t.fail("%s: strs", api.name.c_str());
            if (d.req.vecs != e.vecs) t.fail("%s: vecs", api.name.c_str());
            if (d.has_device_type != e.dev || d.device_type != e.dev_value) t.fail("%s: device type", api.name.c_str());
            if (!e.log.empty() && (!d.req.battle_log || std::to_string(d.req.battle_log->prop_u32("mission_time", 0)) != e.log))
                t.fail("%s: battle log", api.name.c_str());
            if (e.log.empty() && d.req.battle_log) t.fail("%s: unexpected battle log", api.name.c_str());
            // a truncated body and a trailing byte are refused
            if (body.size() > 16 && decode_request(api, body.data(), body.size() - 1, &d, &err)) t.fail("%s: truncated accepted", api.name.c_str());
            body.push_back(0);
            if (decode_request(api, body.data(), body.size(), &d, &err)) t.fail("%s: trailing byte accepted", api.name.c_str());
        }
    }
    // the reply side of the table: 12 clear messages in all (docs/online-server.md §3)
    int clear_req = 0, clear_rep = 0;
    for (const WireApi& a : apis()) clear_req += !a.encrypted, clear_rep += !a.reply_encrypted;
    t.expect_eq(clear_req, 3, "clear requests (StartBridge, NoLoginStart, UpdateSession)");
    t.expect_eq(clear_rep, 5,
                "clear replies of requests (ResultStart, NoLoginStartRes, ResultUpdateSession, EquipAccessoryRes, CoinDepositAndroidUpdateRes)");
    t.expect_eq(std::string(fid_name(kFidProtocolError)), std::string("ProtocolError"), "ProtocolError fid");
    t.expect_eq(api_by_name("UpdateName")->method, std::string("UpdatePlayerName"), "UpdateName -> the server's UpdatePlayerName");
}

std::vector<std::string> split(const std::string& s, char c) {
    std::vector<std::string> o;
    if (s == "-") return o;
    std::string cur;
    std::istringstream ss(s);
    while (std::getline(ss, cur, c)) o.push_back(cur);
    return o;
}

// Request packets the client's own serializers built (unicorn): SHA-1, envelope, decoder.
NATIVE_TEST("net/client-requests") {
    std::string path = find_repo_file("server/tests/net/client_requests.txt");
    std::ifstream in(path);
    if (path.empty() || !in) return t.fail("server/tests/net/client_requests.txt not found");
    std::string line;
    int n = 0;
    std::vector<std::string> names;
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        std::string tag, name, keyh, pkth, method, ints, strs, vecs, dev, log;
        ss >> tag >> name >> keyh >> pkth >> method >> ints >> strs >> vecs >> dev >> log;
        if (tag != "req") continue;
        n++;
        names.push_back(name);
        auto key = unhex(keyh), pkt = unhex(pkth);
        PacketReader rd;
        rd.feed(pkt.data(), pkt.size());
        Packet p;
        if (rd.next(&p) != PacketReader::kPacket) {
            t.fail("%s: packet refused", name.c_str());
            continue;
        }
        const WireApi* api = api_by_fid(p.fid);
        if (!api || api->name != name) {
            t.fail("%s: fid %08x", name.c_str(), p.fid);
            continue;
        }
        if ((p.flags == kFlagEncrypted) != api->encrypted) t.fail("%s: flags %02x", name.c_str(), p.flags);
        std::vector<uint8_t> plain = p.body;
        if (p.flags & kFlagEncrypted) {
            uint32_t alg = 0;
            if (int st = ninja::decrypt(key.data(), p.body.data(), p.body.size(), &plain, &alg)) {
                t.fail("%s: decrypt %d", name.c_str(), st);
                continue;
            }
        }
        Decoded d;
        std::string err;
        if (!decode_request(*api, plain.data(), plain.size(), &d, &err)) {
            t.fail("%s: %s", name.c_str(), err.c_str());
            continue;
        }
        t.expect_eq(d.req.method, method, (name + " method").c_str());
        std::vector<uint64_t> wi;
        for (auto& s : split(ints, ',')) wi.push_back(strtoull(s.c_str(), nullptr, 10));
        if (d.req.ints != wi) t.fail("%s: ints", name.c_str());
        std::vector<std::string> ws;
        for (auto& s : split(strs, ',')) {
            auto b = unhex(s);
            ws.emplace_back(b.begin(), b.end());
        }
        if (d.req.strs != ws) t.fail("%s: strs", name.c_str());
        std::vector<std::vector<uint64_t>> wv;
        for (auto& g : split(vecs, ';')) {
            wv.emplace_back();
            for (auto& s : split(g, ',')) wv.back().push_back(strtoull(s.c_str(), nullptr, 10));
        }
        if (d.req.vecs != wv) t.fail("%s: vecs", name.c_str());
        if (d.has_device_type != (dev != "-") || (dev != "-" && d.device_type != strtoul(dev.c_str(), nullptr, 10)))
            t.fail("%s: device type", name.c_str());
        // the RequestHeader the harness used: player 123456789, request id 0x1a2b3c4d, revision 1471
        if (d.header[0] != 0x15 || d.header[8] != 0x4d || d.header[14] != 0xbf || d.header[15] != 0x05) t.fail("%s: RequestHeader", name.c_str());
        for (auto& kv : split(log, ',')) {
            size_t eq = kv.find('=');
            std::string k = kv.substr(0, eq);
            int64_t want = strtoll(kv.c_str() + eq + 1, nullptr, 10);
            if (!d.req.battle_log) {
                t.fail("%s: no battle log", name.c_str());
                break;
            }
            int64_t got = k.rfind("eval", 0) == 0 ? d.req.battle_log->evaluation(atoi(k.c_str() + 4))
                                                  : (int64_t)d.req.battle_log->prop_u32(k.c_str(), 0xdeadbeef);
            if (got != want) t.fail("%s: battle log %s = %lld, want %lld", name.c_str(), k.c_str(), (long long)got, (long long)want);
        }
    }
    if (n < 8) t.fail("only %d client packets", n);
    for (const char* need : {"SetTitle", "Login", "GetPlayer", "MissionStart", "MissionEnd", "GachaOnce", "StartBridge", "UpdateSession"})
        if (std::find(names.begin(), names.end(), need) == names.end()) t.fail("no client packet for %s", need);
}

NATIVE_TEST("net/battle-log") {
    Value m = Value::object();
    m["is_defeat"] = true;
    m["damage_total"] = 48210u;
    m["mission_time"] = 83000u;
    m["negative"] = -5;
    Value ev = Value::array();
    for (auto [type, score] : {std::pair<int, unsigned>{1, 100}, {6, 83000}, {1, 200}}) {
        Value e = Value::object();
        e["evaluation_type"] = type;
        e["score"] = score;
        ev.push(e);
    }
    m["BattleEvaluationInfo"] = ev;
    m["PlayerCharacter"] = Value::array();
    auto b = mp_encode(m);
    auto log = parse_battle_log(b.data(), b.size());
    if (!log) return t.fail("not parsed");
    t.expect_eq(log->prop_u32("damage_total", 0), 48210u, "damage_total");
    t.expect_eq(log->prop_u32("mission_time", 0), 83000u, "mission_time");
    t.expect_eq(log->prop_u32("is_defeat", 7), 1u, "bool");
    t.expect_eq(log->prop_u32("hit_max", 7), 7u, "missing -> default");
    t.expect_eq(log->prop_u32("PlayerCharacter", 9), 9u, "array -> default");
    t.expect_eq(log->evaluation(1), (int64_t)200, "last evaluation of a type");
    t.expect_eq(log->evaluation(6), (int64_t)83000, "evaluation 6");
    t.expect_eq(log->evaluation(3), (int64_t)-1, "no evaluation");
    auto arr = mp_encode(Value::array());
    t.expect_eq(parse_battle_log(arr.data(), arr.size()) == nullptr, true, "an array is no log");
    t.expect_eq(parse_battle_log(nullptr, 0) == nullptr, true, "empty");
    // through MissionEnd's decoder
    const WireApi* me = api_by_name("MissionEnd");
    uint8_t hdr[16] = {};
    WireArg id, blob, x;
    id.i = 3519778102u;
    blob.s.assign((const char*)b.data(), b.size());
    x.i = 4;
    auto body = encode_request(*me, hdr, {id, blob, x});
    Decoded d;
    std::string err;
    if (!decode_request(*me, body.data(), body.size(), &d, &err)) return t.fail("%s", err.c_str());
    t.expect_eq(d.req.ints, std::vector<uint64_t>{3519778102u, 4}, "MissionEnd ints (mission, u32)");
    t.expect_eq(d.req.strs.empty(), true, "the log isn't a string argument");
    t.expect_eq(d.battle_log.size(), b.size(), "raw log kept");
    t.expect_eq(d.req.battle_log && d.req.battle_log->prop_u32("mission_time", 0) == 83000u, true, "Request::battle_log");
}

NATIVE_TEST("net/reply-bodies") {
    std::vector<uint8_t> mp = {0x81, 0xa6, 's', 't', 'a', 't', 'u', 's', 0x00};
    auto b = reply_body(*api_by_name("GetPlayer"), mp);
    t.expect_eq(b.size(), 4 + mp.size(), "blob size");
    t.expect_eq((int)b[0], (int)mp.size(), "blob length word");
    auto l = reply_body(*api_by_name("Login"), mp);
    t.expect_eq(l.size(), 8 + mp.size(), "LoginResult size");
    t.expect_eq(l[0] | l[1] << 8 | l[2] << 16 | (uint32_t)l[3] << 24, 0xa01c67efu, "LoginResult fid word");
    t.expect_eq(reply_body(*api_by_name("UpdateSession"), mp).empty(), true, "ResultUpdateSession is empty");
    auto s = result_start_body("tok", "http://h:1/bridge", "x");
    t.expect_eq(s.size(), (size_t)1160, "ResultStart = char[1024] + char[128] + char[8]");
    t.expect_eq(std::string((const char*)s.data() + 1024), std::string("http://h:1/bridge"), "url field");
    t.expect_eq(std::string((const char*)s.data() + 1152), std::string("x"), "third field");
    auto long_url = result_start_body("t", std::string(300, 'u'), "");
    t.expect_eq((int)long_url[1024 + 127], 0, "url field NUL-terminated");
    auto e = protocol_error_body(0xa01c67ef, 19001);
    t.expect_eq(hex(e), std::string("394a000000000000ef671ca0"), "ProtocolError body (as SetProtocolError lays it out)");
}

}  // namespace

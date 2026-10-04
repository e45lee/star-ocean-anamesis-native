// soa-server's game-server session logic (game.h). Our code; every behaviour the client can't
// tell us is labelled (d) here and in docs/server-rules.md "soa-server: the wire layer".
#include "game.h"

#include <sys/stat.h>
#include <time.h>

#include <algorithm>
#include <cstring>
#include <optional>

#include "ninja/ninja_ref.h"
#include "soaserver/log.h"
#include "soaserver/msgpack.h"
#include "soaserver/server.h"

namespace soa::server::net {

namespace {

constexpr uint32_t kFidStartBridge = 0xd4053e85;
constexpr uint32_t kFidUpdateSession = 0xea04f3fd;

#define NLOG(level, ...)                                                                  \
    do {                                                                                  \
        if (log_enabled(LogLevel::level)) log_write(LogLevel::level, "net", __VA_ARGS__); \
    } while (0)

struct LiveBackend : Backend {
    // The library's request lifecycle (server::answer: EndMissionTalk, the story campaign, the
    // transaction). (d) no handler: an empty success with data.Time (GameServer logs it), plus the
    // campaign's data, as soa adds it to the canned file it falls back to.
    uint32_t call(const Request& r, std::vector<uint8_t>* out) override {
        Reply reply = answer(r, [] {
            Value data = Value::object();
            data["Time"] = format_time(clock_now());
            return ext::body(data);
        });
        *out = std::move(reply.body);
        return reply.handled ? reply.error_code : kNotHandled;
    }
    bool with_state(const std::function<void(ext::Sql&)>& fn) override {
        return ext::with_live_server([&](ext::Ctx& c) { fn(c.st); });
    }
};

std::string json_escape(const std::string& s) {
    std::string o;
    for (char c : s) {
        if (c == '"' || c == '\\') o += '\\', o += c;
        else if ((unsigned char)c < 0x20) {
            char b[8];
            snprintf(b, sizeof b, "\\u%04x", c);
            o += b;
        } else o += c;
    }
    return o;
}

// The LoginResult body: the server library's Login answer plus a top-level "Player" map, the
// client's legacy CParameterPlayer (docs/server-rules.md "soa-server: the wire
// layer"). (b) CApiNotify::OnLoginResult (3.7.0 @014be668) hands the body's root map to
// CParameterManager::Deserialize, whose CParameterPlayer (pParseName "Player", 3.7.0 @017f84d4)
// reads root["Player"] (CParameterBase::pGetRoot) into its element {Id u32, Token u32, Level u32,
// Role s32, PersonID u32, Weapon u32, Name string} (CParameterPlayerElement::Initialize
// @017f81b8) and only then sets its "deserialized" byte (+0x178). CApiNotify::LoggedIn (@014bb174)
// is that byte && Id != 0, and every API after the login (NetworkApiCaller::GetMissionList
// @015b9c90 and the rest) checks LoggedIn first: without the root Player the client failed them
// locally with 1002 (DisconnectDialog(-0x3b3)) and never sent them. The "data" map (the Info
// path) is never read by OnLoginResult; the GetPlayerRes that follows applies it.
// (d) the values: Id = the player's numeric id, Level and Name the player's; Token / Role /
// PersonID / Weapon are not sent (their defaults stay: -1, 0, 0, 0).
std::vector<uint8_t> login_result_body(const std::vector<uint8_t>& body) {
    Value root = mp_decode(body);
    if (root.type != Value::Map) return body;
    const Value* data = root.find("data");
    const Value* pl = data ? data->find("Player") : nullptr;
    if (!pl) return body;
    Value legacy = Value::object();
    if (const Value* v = pl->find("id")) legacy["Id"] = Value((unsigned long long)(uint32_t)(v->type == Value::UInt ? v->u : (uint64_t)v->i));
    if (const Value* v = pl->find("level")) legacy["Level"] = *v;
    if (const Value* v = pl->find("name")) legacy["Name"] = *v;
    root["Player"] = legacy;
    return mp_encode(root);
}

// The top-level keys of a response's data map (packet log).
std::string data_keys(const std::vector<uint8_t>& msgpack) {
    Value v = mp_decode(msgpack);
    const Value* d = v.type == Value::Map ? v.find("data") : nullptr;
    std::string s;
    if (d && d->type == Value::Map)
        for (auto& e : d->map) s += (s.empty() ? "" : ",") + e.first;
    const Value* st = v.type == Value::Map ? v.find("status") : nullptr;
    return "data{" + s + "} status=" + (st ? std::to_string(st->type == Value::Int ? st->i : (int64_t)st->u) : "-");
}

}  // namespace

std::unique_ptr<Backend> live_backend() { return std::make_unique<LiveBackend>(); }

std::string json_string_field(const std::string& json, const std::string& key) {
    std::string pat = "\"" + key + "\"";
    size_t p = json.find(pat);
    if (p == std::string::npos) return "";
    p = json.find(':', p + pat.size());
    if (p == std::string::npos) return "";
    p = json.find_first_not_of(" \t\r\n", p + 1);
    if (p == std::string::npos) return "";
    if (json[p] != '"') {  // a bare number
        size_t e = json.find_first_of(",} \t\r\n", p);
        return json.substr(p, e == std::string::npos ? std::string::npos : e - p);
    }
    std::string o;
    for (size_t i = p + 1; i < json.size(); i++) {
        if (json[i] == '"') return o;
        if (json[i] == '\\' && i + 1 < json.size()) {
            char c = json[++i];
            o += c == 'n' ? '\n' : c == 't' ? '\t' : c;
        } else o += json[i];
    }
    return "";
}

// (d) The device table. The real server bound a device UUID to its player at CreatePlayer and
// re-bound it through SQEX BRIDGE's data transfer [unknown how]. Ours has one player per state DB
// (the seeded LOCAL00001, or the one CreatePlayer made), so every device gets that player; with no
// player yet (soa-server --new-player on a fresh state) the device has none (player_id NULL; 0
// before PLAN-schema S10; the function returns 0) and its Login is refused with 19001, which
// starts the client's new-player flow. The table (state/schema.cpp,
// on both routes since PLAN-schema S1; only this one writes it) records who connected.
uint32_t map_device(ext::Sql& st, const std::string& uuid, uint32_t device_type, ServerTime now) {
    uint32_t pid = (uint32_t)st.one("select id from player limit 1", {}, 0);
    // the table's player_id: NULL while there is no player (a reference to player.id, PLAN-schema S10)
    const std::optional<PlayerId> player = pid ? std::optional<PlayerId>(PlayerId(pid)) : std::nullopt;
    if (st.one("select count(*) from wire_device where uuid = ?", {uuid}) == 0)
        st.q("insert into wire_device (uuid, player_id, device_type, first_seen, last_seen) values (?, ?, ?, ?, ?)",
             {uuid, player, device_type, now, now});
    else st.q("update wire_device set player_id = ?, device_type = ?, last_seen = ? where uuid = ?", {player, device_type, now, uuid});
    return pid;
}

GameServer::GameServer(Backend& backend, GameOptions opt) : backend_(backend), opt_(std::move(opt)) {
    rng_.seed(opt_.seed ? opt_.seed : ((uint64_t)std::random_device{}() << 32 | std::random_device{}()));
    if (!opt_.log_dir.empty()) {
        mkdir(opt_.log_dir.c_str(), 0755);
        std::string p = opt_.log_dir + "/packets.log";
        log_ = fopen(p.c_str(), "a");
        if (!log_) NLOG(Warn, "--log-packets: can't write %s", p.c_str());
    }
}

GameServer::~GameServer() {
    if (log_) fclose(log_);
}

uint64_t GameServer::open() {
    uint64_t id = next_conn_++;
    conns_[id];
    log("conn " + std::to_string(id) + " open");
    return id;
}

void GameServer::close(uint64_t conn) {
    for (auto it = tokens_.begin(); it != tokens_.end();) it = it->second == conn ? tokens_.erase(it) : std::next(it);
    conns_.erase(conn);
    log("conn " + std::to_string(conn) + " closed");
}

bool GameServer::bound(uint64_t conn) const {
    auto it = conns_.find(conn);
    return it != conns_.end() && !it->second.session.empty();
}
std::string GameServer::key_of(uint64_t conn) const {
    auto it = conns_.find(conn);
    if (it == conns_.end()) return "";
    auto s = sessions_.find(it->second.session);
    return s == sessions_.end() ? "" : s->second.key;
}

std::string GameServer::random_hex(size_t n) {
    static const char d[] = "0123456789abcdef";
    std::string s;
    for (size_t i = 0; i < n; i++) s += d[rng_() & 15];
    return s;
}

void GameServer::log(const std::string& line) {
    NLOG(Debug, "%s", line.c_str());
    if (!log_) return;
    fprintf(log_, "%s %s\n", format_time(time(nullptr)).c_str(), line.c_str());
    fflush(log_);
}

void GameServer::log_file(const std::string& name, const std::vector<uint8_t>& data) {
    if (opt_.log_dir.empty()) return;
    std::string p = opt_.log_dir + "/" + name;
    if (FILE* f = fopen(p.c_str(), "wb")) {
        fwrite(data.data(), 1, data.size(), f);
        fclose(f);
    }
}

void GameServer::record_device(const Session& s, const char* event) {
    uint32_t pid = 0;
    bool ok = backend_.with_state([&](ext::Sql& st) { pid = map_device(st, s.uuid, s.device_type, clock_now()); });
    if (ok)
        NLOG(Info, "%s: device %s (type %u) -> %s", event, s.uuid.c_str(), s.device_type,
             pid ? ("player " + std::to_string(pid)).c_str() : "no player yet (new-player flow)");
}

bool GameServer::on_data(uint64_t id, const uint8_t* p, size_t n, std::vector<uint8_t>* out) {
    auto it = conns_.find(id);
    if (it == conns_.end()) return false;
    Conn& c = it->second;
    c.reader.feed(p, n);
    for (;;) {
        Packet pk;
        PacketReader::Result r = c.reader.next(&pk);
        if (r == PacketReader::kNeedMore) return true;
        if (r == PacketReader::kBadSize) {
            log("conn " + std::to_string(id) + " bad packet size: closing");
            NLOG(Warn, "conn %llu: a packet header with an impossible size; closing", (unsigned long long)id);
            return false;
        }
        if (r == PacketReader::kBadSha) {
            // (b) the client's receiver drops a packet whose SHA-1 doesn't match (-0x3b8); we
            // answer it with a ProtocolError so the client's request fails instead of timing out (d)
            refuse(id, c, pk.fid, pk.counter, kStatusCommError, "SHA-1 mismatch", out);
            c.refused = false;
            return false;  // a ProtocolError ends the connection (below)
        }
        handle_packet(id, c, pk, out);
        // A ProtocolError ends the connection. (b) the client opens a
        // connection per request and closes it after the reply (soa-emu's packet logs), and a
        // logged-in client's next request reconnects with the session key (handle_packet). (d)
        // that the server closes after a ProtocolError: the client tears the socket down on its
        // main thread when it handles the error, while its network thread is in Socket::Poll
        // (3.7.0 @0220dd98), which re-reads the socket's fd after select() returns; with the
        // connection still open the read raced the main thread's Socket::Close (fd = -1) and
        // soa-emu crashed (a top-byte-tagged address, which an ARM64 phone ignores and the JIT
        // didn't; the runtime emulates TBI now: emulator/README.md).
        // Closing first lets the network thread see the end of the connection and close the
        // socket itself. GameOptions::close_after_refusal (--keep-open-after-error) turns it off.
        if (c.refused) {
            c.refused = false;
            if (opt_.close_after_refusal) return false;
        }
    }
}

void GameServer::send(Conn& c, uint32_t fid, uint32_t counter, bool encrypt, const std::vector<uint8_t>& plain, std::vector<uint8_t>* out,
                      const char* what) {
    Packet p;
    p.fid = fid;
    p.counter = counter;  // (d) the request's counter echoed
    std::string alg = "clear";
    if (encrypt) {
        auto s = sessions_.find(c.session);
        const std::string& key = s->second.key;
        uint32_t r2 = (uint32_t)rng_(), salt = (uint32_t)rng_();
        // (d) every reply in AES-128: the client decrypts whichever algorithm the envelope names
        p.body = ninja::encrypt((const uint8_t*)key.data(), ninja::kAES128, r2, salt, plain.data(), plain.size());
        p.flags = kFlagEncrypted;
        alg = ninja::alg_name(ninja::kAES128);
    } else {
        p.body = plain;
    }
    std::vector<uint8_t> pkt = encode_packet(p);
    out->insert(out->end(), pkt.begin(), pkt.end());
    const char* nm = fid_name(fid);
    char fids[16];
    snprintf(fids, sizeof fids, "%08x", fid);
    log(std::string("  < ") + (nm ? nm : "?") + " fid=" + fids + " " + alg + " plain=" + std::to_string(plain.size()) +
        " packet=" + std::to_string(pkt.size()) + (what && *what ? " " : "") + (what ? what : ""));
}

void GameServer::refuse(uint64_t id, Conn& c, uint32_t fid, uint32_t counter, int64_t status, const std::string& why, std::vector<uint8_t>* out) {
    c.refused = true;
    const char* nm = fid_name(fid);
    NLOG(Warn, "conn %llu: %s (fid %08x) refused: %s -> ProtocolError %lld", (unsigned long long)id, nm ? nm : "?", fid, why.c_str(),
         (long long)status);
    send(c, kFidProtocolError, counter, false, protocol_error_body(fid, status), out,
         ("status=" + std::to_string(status) + " (" + why + ")").c_str());
}

void GameServer::handle_packet(uint64_t id, Conn& c, const Packet& p, std::vector<uint8_t>* out) {
    uint64_t seq = ++seq_;
    const WireApi* api = api_by_fid(p.fid);
    char fids[16];
    snprintf(fids, sizeof fids, "%08x", p.fid);
    std::string head = "conn " + std::to_string(id) + " #" + std::to_string(seq) + " > " + (api ? api->name : "?") + " fid=" + fids;
    if (!api) {
        log(head + " unknown FunctionID");
        return refuse(id, c, p.fid, p.counter, kStatusCommError, "unknown FunctionID", out);
    }
    // ---- the plaintext ----
    std::vector<uint8_t> plain;
    std::string alg = "clear";
    if (p.flags & kFlagEncrypted) {
        auto s = sessions_.find(c.session);
        if (s == sessions_.end()) {
            // A reconnect of a logged-in client: the client closes its game
            // connection after the login and reconnects for the next request with no StartBridge
            // or UpdateSession. (b) CApiNotify::OnDisconnect / OnError (3.7.0 @014bb314 /
            // @014bb1fc) keep the bridged flag (+0x4d0) while CApiNotify::LoggedIn holds, and
            // BeginBridge then sends the request at once, encrypted with the session key. (d) how
            // the real server found the session of such a connection is unknown: soa-server tries
            // the keys of its sessions, newest first; the envelope's keyed trailer (ninja kErrMac)
            // rejects every other key, and the connection is bound to the session that decrypts.
            std::vector<std::pair<uint64_t, std::string>> order;
            for (auto& [sid, ss] : sessions_) order.emplace_back(ss.serial, sid);
            std::sort(order.rbegin(), order.rend());
            for (auto& [serial, sid] : order) {
                std::vector<uint8_t> trial;
                if (ninja::decrypt((const uint8_t*)sessions_[sid].key.data(), p.body.data(), p.body.size(), &trial) != ninja::kOk) continue;
                c.session = sid;
                s = sessions_.find(sid);
                log("conn " + std::to_string(id) + " rebound to session " + sid + " (a reconnect without UpdateSession)");
                break;
            }
        }
        if (s == sessions_.end()) {
            log(head + " encrypted, but the connection has no session");
            return refuse(id, c, p.fid, p.counter, kStatusCommError, "encrypted request before UpdateSession", out);
        }
        uint32_t a = 0;
        int st = ninja::decrypt((const uint8_t*)s->second.key.data(), p.body.data(), p.body.size(), &plain, &a);
        if (st != ninja::kOk) {
            log(head + " decrypt failed (" + std::to_string(st) + ")");
            return refuse(id, c, p.fid, p.counter, kStatusCommError, "envelope refused (" + std::to_string(st) + ")", out);
        }
        alg = ninja::alg_name(a) ? ninja::alg_name(a) : "?";
    } else {
        if (api->encrypted) {
            log(head + " sent in the clear but encrypted by the client's serializer");
            return refuse(id, c, p.fid, p.counter, kStatusCommError, "clear body for an encrypted API", out);
        }
        plain = p.body;
    }
    Decoded d;
    std::string err;
    if (!decode_request(*api, plain.data(), plain.size(), &d, &err)) {
        log(head + " " + alg + " decode failed: " + err);
        log_file(std::to_string(seq) + "-" + api->name + ".bin", plain);
        return refuse(id, c, p.fid, p.counter, kStatusCommError, "can't decode: " + err, out);
    }
    log(head + " " + alg + " plain=" + std::to_string(plain.size()) + " method=" + d.req.method + " args: " + d.args);
    log_file(std::to_string(seq) + "-" + api->name + ".bin", plain);
    if (!d.battle_log.empty()) log_file(std::to_string(seq) + "-" + api->name + "-battle_log.msgp", d.battle_log);

    // ---- the session setup (the wire layer's own) ----
    if (p.fid == kFidStartBridge) {
        // (d) a nativeToken of 48 hex characters (ResultStart's field holds up to 1023); the
        // third value is stored by the client in an 8-byte buffer and never read back [unknown]: empty
        std::string token = random_hex(48);
        tokens_[token] = id;
        return send(c, api->reply_fid, p.counter, false, result_start_body(token, opt_.bridge_url, ""), out,
                    ("token=" + token + " url=" + opt_.bridge_url).c_str());
    }
    if (p.fid == kFidUpdateSession) {
        const std::string sid = d.req.strs.empty() ? "" : d.req.strs[0];
        auto s = sessions_.find(sid);
        if (s == sessions_.end()) return refuse(id, c, p.fid, p.counter, kStatusCommError, "unknown nativeSessionId " + sid, out);
        c.session = sid;  // this connection now uses the session's key
        NLOG(Info, "conn %llu: bound to session %s (device %s)", (unsigned long long)id, sid.c_str(), s->second.uuid.c_str());
        return send(c, api->reply_fid, p.counter, false, {}, out, ("session=" + sid).c_str());
    }

    // ---- an API request: the server library answers ----
    std::vector<uint8_t> body;
    uint32_t code = backend_.call(d.req, &body);
    if (code == kNotHandled) {
        // (d) the server has no handler (an API the emulator doesn't serve yet): an empty success
        // with data.Time (and what the backend adds to it, the campaign's data), so the client's
        // screen goes on; logged
        NLOG(Warn, "%s (%s): not implemented by the server; answering data.Time (+ campaign data)", api->name.c_str(), d.req.method.c_str());
        if (body.empty()) {
            Value data = Value::object();
            data["Time"] = format_time(clock_now());
            body = ext::body(data);
        }
        code = 0;
    }
    if (code) return refuse(id, c, p.fid, p.counter, code, "the server's error code", out);
    if (d.req.method == "CreatePlayer") {
        auto s = sessions_.find(c.session);
        if (s != sessions_.end()) record_device(s->second, "CreatePlayer");
    }
    log_file(std::to_string(seq) + "-" + api->reply + ".msgp", body);
    std::string note = data_keys(body);
    if (api->reply_kind == ReplyKind::kEmpty) return send(c, api->reply_fid, p.counter, api->reply_encrypted, {}, out, note.c_str());
    if (api->reply_encrypted && c.session.empty())
        return refuse(id, c, p.fid, p.counter, kStatusCommError, "an encrypted reply without a session", out);
    if (api->reply_kind == ReplyKind::kFidblob) {
        // Login / SimpleLogin: the LoginResult also carries the session's player at the top level.
        std::vector<uint8_t> lr = login_result_body(body);
        log_file(std::to_string(seq) + "-" + api->reply + "-sent.msgp", lr);
        send(c, api->reply_fid, p.counter, api->reply_encrypted, reply_body(*api, lr), out, (note + " +Player{Id,Level,Name}").c_str());
    } else {
        send(c, api->reply_fid, p.counter, api->reply_encrypted, reply_body(*api, body), out, note.c_str());
    }
    if (api->reply_kind == ReplyKind::kFidblob) {
        // Login / SimpleLogin: the LoginResult is followed by a GetPlayerRes with the same body.
        // (b) CApiNotify::OnLoginResult (3.7.0 @014be668) applies the body but never ends the
        // request: no EndRequest, no ErrorHandler::Success, no CAPIWatcher stop (every On<Api>Res
        // does them, for whichever request is in flight; CApiNotify::ResetErrorCode has no
        // caller), so after a LoginResult alone CPhase_Login waits until the 60 s API watchdog
        // fails the login with 1002 (seen with soa-emu). FakeApiCaller::Login, the developers'
        // stand-in for the server, answers Login through OnGetPlayerRes with
        // FakeApi/player_get.msgp. (d) that the real server followed its LoginResult with a
        // GetPlayerRes (an ordinary reply that ends the request) and with this body.
        const WireApi* gp = api_by_name("GetPlayer");
        send(c, gp->reply_fid, p.counter, gp->reply_encrypted, reply_body(*gp, body), out, "(ends the login request)");
    }
}

int GameServer::bridge(const std::string& body, std::string* json) {
    // (b) the client posts {"UUID":"%s","deviceType":"%d","nativeToken":"%s"} plus a NUL
    // (CApiNotify::OnResultStart: SetContent(buf, len + 1))
    std::string uuid = json_string_field(body, "UUID");
    std::string dev = json_string_field(body, "deviceType");
    std::string token = json_string_field(body, "nativeToken");
    auto t = tokens_.find(token);
    if (token.empty() || t == tokens_.end()) {
        log("bridge: unknown nativeToken \"" + token + "\" (UUID " + uuid + ")");
        NLOG(Warn, "bridge: unknown nativeToken \"%s\"", token.c_str());
        *json = "{\"error\":\"unknown nativeToken\"}";
        return 403;
    }
    tokens_.erase(t);
    // (d) nativeSessionId: 32 hex characters (UpdateSession sends it in a char[32] field);
    // sharedSecurityKey: 64 hex characters, printable and never starting with a NUL (the client's
    // KeyStore takes its first 32 bytes as the Ninja key and treats a 0 first byte as no key)
    std::string sid = random_hex(32);
    Session s;
    s.key = random_hex(64);
    s.uuid = uuid;
    s.device_type = (uint32_t)strtoul(dev.c_str(), nullptr, 10);
    s.serial = ++session_serial_;
    sessions_[sid] = s;
    record_device(s, "bridge");
    log("bridge: UUID=" + uuid + " deviceType=" + dev + " token=" + token + " -> session " + sid);
    *json = "{\"nativeSessionId\":\"" + json_escape(sid) + "\",\"sharedSecurityKey\":\"" + json_escape(s.key) + "\"}";
    return 200;
}

HttpHandler GameServer::bridge_handler() {
    return [this](const HttpRequest& req, const std::string& rest, HttpResponse& resp) {
        if (!rest.empty() && rest != "/") return false;
        if (req.method != "POST") {
            resp.status = 405;
            resp.set_header("Content-Type", "text/plain");
            resp.body = "POST only\n";
            return true;
        }
        std::string json;
        resp.status = bridge(req.body, &json);
        // (d) the body is the gzip stream itself, without Content-Encoding (BridgeNotify::OnReceive
        // gunzips the body it is handed; an HTTP layer that honoured Content-Encoding would hand it
        // the inflated JSON instead)
        resp.set_header("Content-Type", "application/json");
        resp.body = gzip(json);
        return true;
    };
}

}  // namespace soa::server::net

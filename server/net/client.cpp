// The wire client (client.h). Our code.
#include "client.h"

#include <cerrno>
#include <cstring>

#include "game.h"
#include "http.h"
#include "ninja/ninja_ref.h"
#include "soa/sock.h"

namespace soa::server::net {

namespace {

int connect_to(const std::string& host, uint16_t port, std::string* err) {
    addrinfo hints = {}, *res = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    sock::startup();  // (Winsock, before the name lookup)
    if (int r = getaddrinfo(host.c_str(), nullptr, &hints, &res); r != 0 || !res) {
        *err = host + ": " + gai_strerror(r);
        return -1;
    }
    sockaddr_in a = *(sockaddr_in*)res->ai_addr;
    freeaddrinfo(res);
    a.sin_port = htons(port);
    int fd = sock::tcp_socket(false);
    if (fd < 0) return *err = "socket: " + sock::last_error(), -1;
    sock::set_timeouts(fd, 10);
    sock::set_nodelay(fd);
    if (::connect(fd, (sockaddr*)&a, sizeof a) != 0) {
        *err = "connect " + host + ":" + std::to_string(port) + ": " + sock::last_error();
        sock::close(fd);
        return -1;
    }
    return fd;
}

bool send_all(int fd, const void* p, size_t n) {
    const char* c = (const char*)p;
    while (n) {
        ssize_t k = sock::send(fd, c, n);
        if (k <= 0) return false;
        c += k, n -= (size_t)k;
    }
    return true;
}

uint32_t le32(const uint8_t* p) { return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }

bool split_url(const std::string& url, std::string* host, uint16_t* port, std::string* path) {
    if (url.rfind("http://", 0) != 0) return false;
    std::string rest = url.substr(7);
    size_t s = rest.find('/');
    std::string hp = rest.substr(0, s);
    *path = s == std::string::npos ? "/" : rest.substr(s);
    size_t c = hp.rfind(':');
    *host = hp.substr(0, c);
    *port = c == std::string::npos ? 80 : (uint16_t)strtoul(hp.c_str() + c + 1, nullptr, 10);
    return true;
}

}  // namespace

WireClient::~WireClient() {
    if (fd_ >= 0) sock::close(fd_);
}

bool WireClient::connect(const std::string& host, uint16_t port, std::string* err) {
    fd_ = connect_to(host, port, err);
    return fd_ >= 0;
}

bool WireClient::read_reply(WireReply* out, std::string* err) {
    PacketReader& rd = rd_;
    Packet p;
    for (;;) {
        PacketReader::Result r = rd.next(&p);
        if (r == PacketReader::kPacket) break;
        if (r != PacketReader::kNeedMore) {
            *err = r == PacketReader::kBadSha ? "reply SHA-1 mismatch" : "reply size impossible";
            return false;
        }
        uint8_t buf[65536];
        ssize_t k = sock::recv(fd_, buf, sizeof buf);
        if (k <= 0) {
            *err = k == 0 ? "connection closed" : std::string("recv: ") + sock::last_error();
            return false;
        }
        rd.feed(buf, (size_t)k);
    }
    *out = WireReply();
    out->fid = p.fid;
    out->counter = p.counter;
    out->flags = p.flags;
    if (p.flags & kFlagEncrypted) {
        if (key_.size() < ninja::kKeySize) return *err = "encrypted reply without a key", false;
        if (int st = ninja::decrypt((const uint8_t*)key_.data(), p.body.data(), p.body.size(), &out->plain, &out->alg); st != ninja::kOk) {
            *err = "reply envelope refused (" + std::to_string(st) + ")";
            return false;
        }
    } else {
        out->plain = p.body;
    }
    if (p.fid == kFidProtocolError) {
        out->protocol_error = true;
        if (out->plain.size() != 12) return *err = "ProtocolError body of " + std::to_string(out->plain.size()) + " bytes", false;
        out->status = (int64_t)((uint64_t)le32(out->plain.data()) | (uint64_t)le32(out->plain.data() + 4) << 32);
        out->failing_fid = le32(out->plain.data() + 8);
    }
    return true;
}

bool WireClient::raw(const std::vector<uint8_t>& bytes, WireReply* out, std::string* err) {
    if (!send_all(fd_, bytes.data(), bytes.size())) return *err = "send failed", false;
    return read_reply(out, err);
}

bool WireClient::call(const std::string& name, const std::vector<WireArg>& args, WireReply* out, std::string* err, uint32_t alg) {
    const WireApi* api = api_by_name(name);
    if (!api) return *err = "unknown API " + name, false;
    uint8_t hdr[16] = {};
    hdr[0] = 0x15, hdr[1] = 0xcd, hdr[2] = 0x5b, hdr[3] = 0x07;  // a player id; the server doesn't read it
    std::vector<uint8_t> plain = encode_request(*api, hdr, args);
    Packet p;
    p.fid = api->fid;
    p.counter = counter_++;
    if (api->encrypted) {
        if (key_.size() < ninja::kKeySize) return *err = name + ": no session key", false;
        r2_ += 0x9e3779b9;
        p.body = ninja::encrypt((const uint8_t*)key_.data(), alg, r2_, r2_ ^ 0x5bd1e995, plain.data(), plain.size());
        p.flags = kFlagEncrypted;
    } else {
        p.body = plain;
    }
    if (!raw(encode_packet(p), out, err)) return false;
    if (out->counter != p.counter) return *err = name + ": the reply's counter isn't the request's", false;
    if (out->protocol_error) return true;
    if (out->fid != api->reply_fid) return *err = name + ": unexpected reply fid", false;
    const std::vector<uint8_t>& b = out->plain;
    size_t o = 0;
    if (api->reply_kind == ReplyKind::kFidblob) {
        if (b.size() < 4) return *err = name + ": short reply", false;
        out->login_fid = le32(b.data());
        o = 4;
    }
    if (api->reply_kind == ReplyKind::kBlob || api->reply_kind == ReplyKind::kFidblob) {
        if (b.size() < o + 4 || le32(b.data() + o) != b.size() - o - 4) return *err = name + ": reply length word doesn't match", false;
        const uint8_t* q = b.data() + o + 4;
        out->msgpack = mp_decode(q, b.data() + b.size());
    }
    if (api->reply_kind == ReplyKind::kFidblob) {
        // the GetPlayerRes that ends the login request (game.cpp)
        WireReply f;
        if (!read_reply(&f, err)) return *err = name + " follow-up: " + *err, false;
        if (f.counter != p.counter) return *err = name + ": the follow-up's counter isn't the request's", false;
        out->followup_fid = f.fid;
        if (f.plain.size() >= 4 && le32(f.plain.data()) == f.plain.size() - 4) {
            const uint8_t* q = f.plain.data() + 4;
            out->followup = mp_decode(q, f.plain.data() + f.plain.size());
        }
    }
    return true;
}

bool http_post(const std::string& url, const std::string& body, int* status, std::string* reply, std::string* err) {
    std::string host, path;
    uint16_t port = 0;
    if (!split_url(url, &host, &port, &path)) return *err = "not an http:// URL: " + url, false;
    int fd = connect_to(host, port, err);
    if (fd < 0) return false;
    std::string req = "POST " + path + " HTTP/1.1\r\nHost: " + host + ":" + std::to_string(port) +
                      "\r\nContent-Type: application/json\r\nConnection: close\r\nContent-Length: " + std::to_string(body.size()) + "\r\n\r\n" + body;
    std::string resp;
    if (send_all(fd, req.data(), req.size())) {
        char buf[16384];
        ssize_t k;
        while ((k = sock::recv(fd, buf, sizeof buf)) > 0) resp.append(buf, (size_t)k);
    }
    sock::close(fd);
    size_t e = resp.find("\r\n\r\n");
    if (resp.rfind("HTTP/1.", 0) != 0 || e == std::string::npos) return *err = "no HTTP response from " + url, false;
    *status = atoi(resp.c_str() + 9);
    *reply = resp.substr(e + 4);
    return true;
}

bool http_get(const std::string& url, int* status, std::string* reply, std::string* err) {
    std::string host, path;
    uint16_t port = 0;
    if (!split_url(url, &host, &port, &path)) return *err = "not an http:// URL: " + url, false;
    int fd = connect_to(host, port, err);
    if (fd < 0) return false;
    std::string req = "GET " + path + " HTTP/1.1\r\nHost: " + host + ":" + std::to_string(port) + "\r\nConnection: close\r\n\r\n";
    std::string resp;
    if (send_all(fd, req.data(), req.size())) {
        char buf[65536];
        ssize_t k;
        while ((k = sock::recv(fd, buf, sizeof buf)) > 0) resp.append(buf, (size_t)k);
    }
    sock::close(fd);
    size_t e = resp.find("\r\n\r\n");
    if (resp.rfind("HTTP/1.", 0) != 0 || e == std::string::npos) return *err = "no HTTP response from " + url, false;
    *status = atoi(resp.c_str() + 9);
    *reply = resp.substr(e + 4);
    return true;
}

bool WireClient::bridge(const std::string& uuid, std::string* err) {
    WireReply r;
    if (!call("StartBridge", {}, &r, err)) return false;
    if (r.protocol_error || r.plain.size() != 1024 + 128 + 8) return *err = "StartBridge: no ResultStart", false;
    std::string token((const char*)r.plain.data(), strnlen((const char*)r.plain.data(), 1024));
    url_.assign((const char*)r.plain.data() + 1024, strnlen((const char*)r.plain.data() + 1024, 128));
    // (b) the client's POST: printf'd JSON plus its NUL (CApiNotify::OnResultStart)
    std::string body = "{\"UUID\":\"" + uuid + "\",\"deviceType\":\"2\",\"nativeToken\":\"" + token + "\"}";
    body.push_back('\0');
    int status = 0;
    std::string reply;
    std::string post_url = url_;
    for (const char* pre : {"https://production-game.so-ana.com/", "http://production-game.so-ana.com/"})
        if (!http_.empty() && url_.rfind(pre, 0) == 0) post_url = "http://" + http_ + "/" + url_.substr(strlen(pre));
    if (!http_post(post_url, body, &status, &reply, err)) return false;
    if (status != 200) return *err = "bridge: HTTP " + std::to_string(status), false;
    std::string json = gunzip(reply);
    if (json.empty()) return *err = "bridge: the reply isn't gzip", false;
    key_ = json_string_field(json, "sharedSecurityKey");
    session_ = json_string_field(json, "nativeSessionId");
    if (key_.size() < ninja::kKeySize || session_.empty()) return *err = "bridge: no session in " + json, false;
    WireArg sid;
    sid.s = session_;
    if (!call("UpdateSession", {sid}, &r, err)) return false;
    if (r.protocol_error) return *err = "UpdateSession refused", false;
    return true;
}

bool run_session(const std::string& host, uint16_t port, const std::string& uuid, std::string* err, const std::string& http) {
    WireClient c;
    c.set_http(http.empty() ? host + ":44380" : http);
    if (!c.connect(host, port, err)) return false;
    if (!c.bridge(uuid, err)) return false;
    printf("bridge: %s -> session %s, key %s...\n", c.bridge_url().c_str(), c.session().c_str(), c.key().substr(0, 8).c_str());
    for (const char* api : {"Login", "GetPlayer", "GetServerTime"}) {
        WireReply r;
        std::vector<WireArg> args;
        if (!strcmp(api, "Login")) {
            args.resize(4);
            args[0].s = uuid;
            args[1].s = "push-token";
            args[2].s = "00000000-0000-0000-0000-000000000000";
        }
        if (!c.call(api, args, &r, err)) return false;
        if (r.protocol_error) {
            printf("%s: ProtocolError status %lld\n", api, (long long)r.status);
            continue;
        }
        const Value* d = r.msgpack.find("data");
        std::string keys;
        if (d)
            for (auto& e : d->map) keys += (keys.empty() ? "" : ",") + e.first;
        printf("%s: %s %zu bytes, data{%s}\n", api, fid_name(r.fid) ? fid_name(r.fid) : "?", r.plain.size(), keys.c_str());
    }
    return true;
}

}  // namespace soa::server::net

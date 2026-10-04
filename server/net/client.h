#pragma once
// A wire client of soa-server (our code): what the game's NetworkApiCaller does on the socket,
// for the loopback selftest (server/tests/net/) and `soa-server --wire-tool session HOST:PORT`
// against a running server. Blocking sockets; one request at a time, as the client.
#include <cstdint>
#include <string>
#include <vector>

#include "soaserver/msgpack.h"
#include "wire.h"

namespace soa::server::net {

struct WireReply {
    uint32_t fid = 0, counter = 0;
    uint8_t flags = 0;
    uint32_t alg = 0;            // the envelope's algorithm (0: clear)
    std::vector<uint8_t> plain;  // the decrypted body
    // Normal replies: the MessagePack after the u32 length (and the u32 fid of LoginResult).
    uint32_t login_fid = 0;
    Value msgpack;
    // ProtocolError
    bool protocol_error = false;
    int64_t status = 0;
    uint32_t failing_fid = 0;
    // Login / SimpleLogin: the reply that follows the LoginResult (GetPlayerRes)
    uint32_t followup_fid = 0;
    Value followup;
};

class WireClient {
public:
    ~WireClient();
    bool connect(const std::string& host, uint16_t port, std::string* err);
    // Sends a request packet of `api` (encrypted with `alg` when the API is) and reads its reply.
    // Login / SimpleLogin: also reads the GetPlayerRes that follows the LoginResult (game.cpp)
    // into `followup`.
    bool call(const std::string& api, const std::vector<WireArg>& args, WireReply* out, std::string* err, uint32_t alg = 0x021d4314 /* AES-128 */);
    // Sends raw bytes and reads one reply packet (tests: corrupted packets).
    bool raw(const std::vector<uint8_t>& bytes, WireReply* out, std::string* err);
    // StartBridge -> POST the bridge URL -> UpdateSession (the session key is then in key()).
    bool bridge(const std::string& uuid, std::string* err);
    const std::string& key() const { return key_; }
    int fd() const { return fd_; }
    const std::string& session() const { return session_; }
    const std::string& bridge_url() const { return url_; }
    // Continues `other`'s session on this (new) connection without StartBridge / UpdateSession,
    // as the client does when it reconnects while logged in.
    void adopt_session(const WireClient& other) { key_ = other.key_, session_ = other.session_, url_ = other.url_; }
    // Where a bridge URL on the client's own host name (production-game.so-ana.com, soa-server's
    // default) is sent, as plain HTTP: soa-server's --http (as soa-emu's host map does).
    void set_http(std::string host_port) { http_ = std::move(host_port); }

private:
    bool read_reply(WireReply* out, std::string* err);
    PacketReader rd_;  // across replies: two can arrive in one recv
    int fd_ = -1;
    uint32_t counter_ = 0x5a5a0001;
    uint32_t r2_ = 0x12345678;
    std::string key_, session_, url_, http_;
};

// One HTTP/1.1 POST of a JSON body (Connection: close; cpp-httplib); the status and the body.
bool http_post(const std::string& url, const std::string& body, int* status, std::string* reply, std::string* err);
// GET url (Connection: close; cpp-httplib): the status and the body (as sent: no content decoding).
bool http_get(const std::string& url, int* status, std::string* reply, std::string* err);

// The scripted session of --wire-tool session: bridge, Login, GetPlayer, GetServerTime; the
// steps are printed to stdout. False on the first failure.
bool run_session(const std::string& host, uint16_t port, const std::string& uuid, std::string* err, const std::string& http = "");

}  // namespace soa::server::net

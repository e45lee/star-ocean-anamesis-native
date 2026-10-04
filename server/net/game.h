#pragma once
// soa-server's wire layer, part 2: the game server's session logic (our code). Per TCP
// connection: StartBridge -> ResultStart (token, bridge URL), the bridge's HTTP POST -> session id
// + shared key, UpdateSession -> the connection is bound to the session and its Ninja key; then
// every request is decrypted, decoded (wire.h), answered by the server library (submit / handle /
// error_code, through a Backend) and sent back encrypted, or refused with a ProtocolError.
// docs/online-server.md §3-4 for the client side; server/README.md "Wire layer" for ours.
#include <cstdint>
#include <functional>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "http.h"
#include "soaserver/ext.h"
#include "wire.h"

namespace soa::server::net {

// The server library as the wire layer uses it. The live one is the library's global server
// (submit / handle / error_code, ext::with_live_server); tests use a scratch server.
constexpr uint32_t kNotHandled = 0xffffffffu;
struct Backend {
    virtual ~Backend() = default;
    // Answers r: the error code (0 accepted; kNotHandled: the server has no handler) and the
    // response MessagePack in *out.
    virtual uint32_t call(const Request& r, std::vector<uint8_t>* out) = 0;
    // Runs fn on the server's state DB (the device table). False without one.
    virtual bool with_state(const std::function<void(ext::Sql&)>& fn) = 0;
};
std::unique_ptr<Backend> live_backend();

struct GameOptions {
    std::string bridge_url;  // ResultStart's URL: http://<--http>/bridge
    std::string log_dir;     // --log-packets DIR ("" = none)
    uint64_t seed = 0;       // tokens, session ids, keys and reply cipher parameters; 0 = random
    // Close the connection after a ProtocolError (game.cpp on_data). Off only for a test: the
    // hidden --keep-open-after-error, which shows that soa-emu no longer needs it (the runtime
    // emulates Top Byte Ignore; emulator/README.md "Error replies and the tagged-address crash").
    bool close_after_refusal = true;
};

// Status codes of our refusals that aren't the library's (d): a ProtocolError with a positive
// status reaches the client as that error code (CNetworkUtility::AskaStatus2ApiErrorCode passes
// positive statuses through); 1002 is the client's generic communication error
// (error_message_text_1002).
constexpr int64_t kStatusCommError = 1002;

class GameServer {
public:
    GameServer(Backend& backend, GameOptions opt);
    ~GameServer();
    GameServer(const GameServer&) = delete;
    GameServer& operator=(const GameServer&) = delete;

    // A TCP connection opened / closed.
    uint64_t open();
    void close(uint64_t conn);
    // Bytes the connection received; the bytes to send are appended to *out. False: close the
    // connection (a broken stream).
    bool on_data(uint64_t conn, const uint8_t* p, size_t n, std::vector<uint8_t>* out);

    // The bridge endpoint (POST {"UUID","deviceType","nativeToken"}): the HTTP status and the
    // JSON reply {"nativeSessionId","sharedSecurityKey"} (before gzip).
    int bridge(const std::string& body, std::string* json);
    // /bridge for the HttpRouter: the JSON gzip-compressed as the body (BridgeNotify::OnReceive
    // gunzips the body itself, AskaUncompressGzipStrict).
    HttpHandler bridge_handler();

    // The URL ResultStart sends (e.g. once the HTTP port is bound).
    void set_bridge_url(std::string url) { opt_.bridge_url = std::move(url); }

    // Tests / logs.
    size_t session_count() const { return sessions_.size(); }
    bool bound(uint64_t conn) const;
    std::string key_of(uint64_t conn) const;

private:
    struct Conn {
        PacketReader reader;
        std::string session;  // nativeSessionId after UpdateSession
        bool refused = false;  // a ProtocolError was just sent: the connection closes after it
    };
    struct Session {
        std::string key;  // sharedSecurityKey (its first 32 bytes are the Ninja key)
        std::string uuid;
        uint32_t device_type = 0;
        uint64_t serial = 0;  // creation order (a reconnect tries the newest first)
    };
    void handle_packet(uint64_t id, Conn& c, const Packet& p, std::vector<uint8_t>* out);
    void send(Conn& c, uint32_t fid, uint32_t counter, bool encrypt, const std::vector<uint8_t>& plain, std::vector<uint8_t>* out, const char* what);
    void refuse(uint64_t id, Conn& c, uint32_t fid, uint32_t counter, int64_t status, const std::string& why, std::vector<uint8_t>* out);
    std::string random_hex(size_t n);
    void record_device(const Session& s, const char* event);
    void log(const std::string& line);
    void log_file(const std::string& name, const std::vector<uint8_t>& data);

    Backend& backend_;
    GameOptions opt_;
    std::mt19937_64 rng_;
    uint64_t next_conn_ = 1;
    uint64_t seq_ = 0;
    uint64_t session_serial_ = 0;
    std::map<uint64_t, Conn> conns_;
    std::map<std::string, uint64_t> tokens_;  // nativeToken -> the connection it was issued on
    std::map<std::string, Session> sessions_;
    FILE* log_ = nullptr;
};

// The server's device table (d): every device UUID the bridge saw, with the player it gets.
// soa-server's state DB, table wire_device. Returns the player id the device maps to (0: none yet,
// the new-player flow).
uint32_t map_device(ext::Sql& st, const std::string& uuid, uint32_t device_type, ServerTime now);

// "key":"value" from a flat JSON object (the bridge request); "" when absent.
std::string json_string_field(const std::string& json, const std::string& key);

}  // namespace soa::server::net

#pragma once
// soa-server's wire layer, part 1: the game RPC's bytes (our code; the format is the client's,
// docs/online-server.md §3 and docs/api.md "Wire format"). Packets (scrambled header, SHA-1
// trailer), the request decoder (layouts measured on the client's own serializers,
// docs/api-wire.txt -> gen/wire_decode.inc by tools/api_wire.py --gen-decoder; the battle log a
// MissionEnd carries is parsed by soaserver/battle_log.h), and the reply bodies. The cipher is ninja_ref.h; the session, the bridge and
// the sockets are game.h / http.h / loop.h.
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "soaserver/battle_log.h"
#include "soaserver/server.h"

namespace soa::server::net {

// ---- packets ------------------------------------------------------------------------------------
// [confirmed, run] header(24, scrambled) | body | SHA-1(header + body). The header's logical
// fields: u32 size (24 + body, without the SHA-1) | u32 fid | u32 counter | u8 flags | 3 zero bytes.
constexpr size_t kHeaderSize = 24;
constexpr size_t kShaSize = 20;
constexpr uint8_t kFlagEncrypted = 0x80;
// Our own limit on a packet (the client's battle log is at most 4096 bytes; the largest request
// is far below this). A bigger size field closes the connection.
constexpr uint32_t kMaxPacket = 1u << 22;

struct Packet {
    uint32_t fid = 0;
    uint32_t counter = 0;
    uint8_t flags = 0;
    std::vector<uint8_t> body;  // as on the wire (the Ninja envelope when flags & 0x80)
};

struct HeaderFields {
    uint32_t size = 0, fid = 0, counter = 0;
    uint8_t flags = 0;
    uint64_t t = 0;  // the sender's CLOCK_MONOTONIC (ns)
};
// The scramble: wire bytes 0..7 are t's bytes 6, 4, 3, 0, 7, 1, 2, 5; bytes 8..23 the 16 logical
// bytes, byte i XOR t's byte (i & 7).
void scramble_header(uint8_t out[kHeaderSize], const HeaderFields& h);
HeaderFields unscramble_header(const uint8_t in[kHeaderSize]);
uint64_t monotonic_ns();

// header + body + SHA-1, with the header timestamp t.
std::vector<uint8_t> encode_packet(const Packet& p, uint64_t t = monotonic_ns());

// Splits a TCP byte stream into packets and checks each SHA-1 (the client's receiver,
// GameProtocoledData::Deserialize, refuses a mismatch with -0x3b8; so do we).
class PacketReader {
public:
    enum Result { kNeedMore, kPacket, kBadSha, kBadSize };
    void feed(const uint8_t* p, size_t n) { buf_.insert(buf_.end(), p, p + n); }
    // kPacket: *out is the next packet. kBadSha: the packet was consumed and dropped (*out has its
    // header fields). kBadSize: the stream is unusable (close it).
    Result next(Packet* out);
    size_t buffered() const { return buf_.size(); }

private:
    std::vector<uint8_t> buf_;
};

// ---- the API table (gen/wire_decode.inc) ----------------------------------------------------------
enum class ReplyKind {
    kBlob,     // u32 length + MessagePack
    kFidblob,  // u32 FunctionID + u32 length + MessagePack (LoginResult, SimpleLoginResult)
    kStart,    // ResultStart: char[1024] token, char[128] url, char[8]
    kEmpty,    // ResultUpdateSession
};
struct WireApi {
    std::string name;    // the serializer's name (SetMissionEnd -> "MissionEnd")
    std::string method;  // the server method it maps to (Request::method)
    uint32_t fid = 0;
    bool encrypted = true;
    std::vector<std::string> layout;  // after the RequestHeader: u8 s8 u32 s32 f32 u64 dev str[N] blob vec64 vec32
    std::string reply;
    uint32_t reply_fid = 0;
    bool reply_encrypted = true;
    ReplyKind reply_kind = ReplyKind::kBlob;
};
const std::vector<WireApi>& apis();
const WireApi* api_by_fid(uint32_t fid);
const WireApi* api_by_name(const std::string& name);
// The API whose server method (WireApi::method, the IApiCaller method NetworkApiCaller sends it
// for) is `method`, nullptr when none: the methods are unique in the table. soa's packet log
// names an in-process request by it (port/src/native/api/packet_log.h).
const WireApi* api_by_method(const std::string& method);
// The name of any request or reply FunctionID (packet log), nullptr when unknown.
const char* fid_name(uint32_t fid);
constexpr uint32_t kFidProtocolError = 0x05aed673;

// ---- requests -------------------------------------------------------------------------------------
// A decoded request: the server's Request (the IApiCaller method's arguments, as soa captures
// them from FakeApiCaller) plus what only the wire has.
struct Decoded {
    Request req;
    uint8_t header[16] = {};        // RequestHeader: u32 player id, u32, u32 request id, u16, u16 asset revision
    bool has_device_type = false;   // NoLoginStart, CreatePlayer, MissionContinue: dropped from req, kept here
    uint32_t device_type = 0;
    std::vector<uint8_t> battle_log;  // MissionEnd & co.: the raw ASON battle log (also parsed into req.battle_log)
    std::string args;                 // the arguments as text (packet log)
};
// Decodes a request body (the plaintext) by its API's layout and applies the per-API shims
// (wire_decode.cpp). False with *err on a short or malformed body.
bool decode_request(const WireApi& api, const uint8_t* p, size_t n, Decoded* out, std::string* err);

// The test encoder: one value per layout token (ints for u8..u64/dev, s for str[N]/blob, v for
// vec64/vec32), laid out as the client's serializer does (str[N] copies N bytes, zero-filled here).
struct WireArg {
    uint64_t i = 0;
    std::string s;
    std::vector<uint64_t> v;
};
std::vector<uint8_t> encode_request(const WireApi& api, const uint8_t header[16], const std::vector<WireArg>& args);

// ---- replies --------------------------------------------------------------------------------------
// The reply plaintext of `api` for a response MessagePack (kBlob: u32 len + msgpack; kFidblob:
// u32 request fid + u32 len + msgpack; kEmpty: nothing).
std::vector<uint8_t> reply_body(const WireApi& api, const std::vector<uint8_t>& msgpack);
// ResultStart: token, url and the third value as fixed char[1024], char[128], char[8] fields
// (measured: SetResultStart copies exactly these widths).
std::vector<uint8_t> result_start_body(const std::string& token, const std::string& url, const std::string& x);
// ProtocolError (clear): s64 Aska::Status + u32 failing FunctionID. A positive status is a server
// error code the client shows as error_message_text_<code> (CNetworkUtility::AskaStatus2ApiErrorCode).
std::vector<uint8_t> protocol_error_body(uint32_t failing_fid, int64_t status);

// Hex helpers (logs, tests, tools).
std::string hex(const uint8_t* p, size_t n);
inline std::string hex(const std::vector<uint8_t>& v) { return hex(v.data(), v.size()); }
std::vector<uint8_t> unhex(const std::string& s);

}  // namespace soa::server::net

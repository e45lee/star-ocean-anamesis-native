// soa-server's wire layer: packets, the request decoder, reply bodies (wire.h); the battle log is soaserver/battle_log.h.
// Our code; the formats are the client's (docs/online-server.md §3, docs/api.md "Wire format").
#include "wire.h"

#include "packet_log.h"  // printable

#include <openssl/sha.h>  // SHA1(): the one-shot digest, not deprecated in OpenSSL 3 (only SHA1_Init / _Update / _Final are)
#include <time.h>

#include <cstring>
#include <map>
#include <mutex>

#include "soaserver/msgpack.h"

namespace soa::server::net {

namespace {

uint32_t le32(const uint8_t* p) { return (uint32_t)p[0] | (uint32_t)p[1] << 8 | (uint32_t)p[2] << 16 | (uint32_t)p[3] << 24; }
uint64_t le64(const uint8_t* p) { return (uint64_t)le32(p) | (uint64_t)le32(p + 4) << 32; }
void put32(std::vector<uint8_t>& o, uint32_t v) {
    for (int k = 0; k < 4; k++) o.push_back((uint8_t)(v >> (8 * k)));
}
void put64(std::vector<uint8_t>& o, uint64_t v) {
    for (int k = 0; k < 8; k++) o.push_back((uint8_t)(v >> (8 * k)));
}

// Wire byte i of the header's first 8 holds timestamp byte kPerm[i].
constexpr int kPerm[8] = {6, 4, 3, 0, 7, 1, 2, 5};

}  // namespace

// ---- packets ------------------------------------------------------------------------------------
void scramble_header(uint8_t out[kHeaderSize], const HeaderFields& h) {
    uint8_t f[16] = {};
    for (int k = 0; k < 4; k++) {
        f[k] = (uint8_t)(h.size >> (8 * k));
        f[4 + k] = (uint8_t)(h.fid >> (8 * k));
        f[8 + k] = (uint8_t)(h.counter >> (8 * k));
    }
    f[12] = h.flags;
    for (int i = 0; i < 8; i++) out[i] = (uint8_t)(h.t >> (8 * kPerm[i]));
    for (int i = 0; i < 16; i++) out[8 + i] = f[i] ^ (uint8_t)(h.t >> (8 * (i & 7)));
}

HeaderFields unscramble_header(const uint8_t in[kHeaderSize]) {
    HeaderFields h;
    for (int i = 0; i < 8; i++) h.t |= (uint64_t)in[i] << (8 * kPerm[i]);
    uint8_t f[16];
    for (int i = 0; i < 16; i++) f[i] = in[8 + i] ^ (uint8_t)(h.t >> (8 * (i & 7)));
    h.size = le32(f);
    h.fid = le32(f + 4);
    h.counter = le32(f + 8);
    h.flags = f[12];
    return h;
}

uint64_t monotonic_ns() {
    timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (uint64_t)ts.tv_sec * 1000000000ull + (uint64_t)ts.tv_nsec;
}

std::vector<uint8_t> encode_packet(const Packet& p, uint64_t t) {
    std::vector<uint8_t> o(kHeaderSize);
    HeaderFields h;
    h.size = (uint32_t)(kHeaderSize + p.body.size());
    h.fid = p.fid;
    h.counter = p.counter;
    h.flags = p.flags;
    h.t = t;
    scramble_header(o.data(), h);
    o.insert(o.end(), p.body.begin(), p.body.end());
    uint8_t sha[SHA_DIGEST_LENGTH];
    SHA1(o.data(), o.size(), sha);
    o.insert(o.end(), sha, sha + kShaSize);
    return o;
}

PacketReader::Result PacketReader::next(Packet* out) {
    if (buf_.size() < kHeaderSize) return kNeedMore;
    HeaderFields h = unscramble_header(buf_.data());
    if (h.size < kHeaderSize || h.size > kMaxPacket) return kBadSize;
    size_t total = (size_t)h.size + kShaSize;
    if (buf_.size() < total) return kNeedMore;
    uint8_t sha[SHA_DIGEST_LENGTH];
    SHA1(buf_.data(), h.size, sha);
    bool ok = memcmp(sha, buf_.data() + h.size, kShaSize) == 0;
    out->fid = h.fid;
    out->counter = h.counter;
    out->flags = h.flags;
    out->body.assign(buf_.begin() + kHeaderSize, buf_.begin() + h.size);
    buf_.erase(buf_.begin(), buf_.begin() + total);
    return ok ? kPacket : kBadSha;
}

// ---- the API table ------------------------------------------------------------------------------
namespace {
struct WireApiRow {
    const char *name, *method;
    uint32_t fid;
    bool encrypted;
    const char* layout;
    const char* reply;
    uint32_t reply_fid;
    bool reply_encrypted;
    ReplyKind reply_kind;
};
struct WireReplyRow {
    const char* name;
    uint32_t fid;
    bool encrypted;
};
#include "gen/wire_decode.inc"
static_assert(kFidProtocolErrorGen == kFidProtocolError);

struct Table {
    std::vector<WireApi> apis;
    std::map<uint32_t, size_t> by_fid;
    std::map<std::string, size_t> by_name;
    std::map<std::string, size_t> by_method;
    std::map<uint32_t, const char*> names;
};
const Table& table() {
    static const Table t = [] {
        Table t;
        for (const WireApiRow& r : kWireApiRows) {
            WireApi a;
            a.name = r.name;
            a.method = r.method;
            a.fid = r.fid;
            a.encrypted = r.encrypted;
            std::string l = r.layout;
            for (size_t i = 0; i < l.size();) {
                size_t j = l.find(' ', i);
                if (j == std::string::npos) j = l.size();
                if (j > i) a.layout.push_back(l.substr(i, j - i));
                i = j + 1;
            }
            a.reply = r.reply;
            a.reply_fid = r.reply_fid;
            a.reply_encrypted = r.reply_encrypted;
            a.reply_kind = r.reply_kind;
            t.by_fid[a.fid] = t.apis.size();
            t.by_name[a.name] = t.apis.size();
            t.by_method[a.method] = t.apis.size();
            t.names[a.fid] = r.name;
            t.apis.push_back(std::move(a));
        }
        for (const WireReplyRow& r : kWireReplyRows) t.names[r.fid] = r.name;
        return t;
    }();
    return t;
}
}  // namespace

const std::vector<WireApi>& apis() { return table().apis; }
const WireApi* api_by_fid(uint32_t fid) {
    auto it = table().by_fid.find(fid);
    return it == table().by_fid.end() ? nullptr : &table().apis[it->second];
}
const WireApi* api_by_name(const std::string& name) {
    auto it = table().by_name.find(name);
    return it == table().by_name.end() ? nullptr : &table().apis[it->second];
}
const WireApi* api_by_method(const std::string& method) {
    auto it = table().by_method.find(method);
    return it == table().by_method.end() ? nullptr : &table().apis[it->second];
}
const char* fid_name(uint32_t fid) {
    auto it = table().names.find(fid);
    return it == table().names.end() ? nullptr : it->second;
}

// ---- requests -----------------------------------------------------------------------------------
namespace {

size_t str_width(const std::string& tok) { return (size_t)strtoul(tok.c_str() + 4, nullptr, 10); }  // "str[N]"

// A request body being read: the bytes, the offset after what was read, the error.
struct BodyReader {
    const uint8_t* p;
    size_t n, o;
    std::string* err;
    // Whether k more bytes are there (else the error names `what`).
    bool need(size_t k, const std::string& what) {
        if (n - o >= k) return true;
        *err = what + " runs past the end of the body (" + std::to_string(n) + " bytes)";
        return false;
    }
};

// One layout token: its value into out->req (ints, vecs, the battle log) or `strs` (strings and
// blobs, in order, before the shims), its text onto out->args. False with *in.err.
bool decode_token(const WireApi& api, const std::string& t, BodyReader& in, Decoded* out, std::vector<std::string>& strs) {
    Request& r = out->req;
    std::string& args = out->args;
    const uint8_t* p = in.p;
    size_t& o = in.o;
    if (t == "u8" || t == "s8") {
        if (!in.need(1, t)) return false;
        r.ints.push_back(p[o]);  // zero-extended, as the w register of a FakeApiCaller argument
        args += std::to_string(p[o]);
        o += 1;
    } else if (t == "u32" || t == "s32" || t == "f32") {
        if (!in.need(4, t)) return false;
        uint32_t v = le32(p + o);
        // f32: the IEEE bits (no server method takes a float; soa's capture can't read them either)
        r.ints.push_back(v);
        if (t == "f32") {
            float f;
            memcpy(&f, &v, 4);
            args += std::to_string(f);
        } else {
            args += t == "s32" ? std::to_string((int32_t)v) : std::to_string(v);
        }
        o += 4;
    } else if (t == "u64") {
        if (!in.need(8, t)) return false;
        uint64_t v = le64(p + o);
        r.ints.push_back(v);
        args += std::to_string(v);
        o += 8;
    } else if (t == "dev") {
        if (!in.need(4, t)) return false;
        out->has_device_type = true;
        out->device_type = le32(p + o);
        args += "dev=" + std::to_string(out->device_type);
        o += 4;
    } else if (t.rfind("str[", 0) == 0) {
        size_t w = str_width(t);
        if (!in.need(w, t)) return false;
        // A fixed-width field: memcpy of N bytes, not zero-padded; the string ends at the
        // first NUL (docs/api.md "Request body").
        size_t len = strnlen((const char*)p + o, w);
        std::string str((const char*)p + o, len);
        args += printable(str);
        strs.push_back(str);
        o += w;
    } else if (t == "blob") {
        if (!in.need(4, t)) return false;
        uint32_t len = le32(p + o);
        o += 4;
        if (!in.need(len, "blob")) return false;
        std::string blob((const char*)p + o, len);
        o += len;
        // the battle log (soaserver/battle_log.h): Request::battle_log, not a string argument
        if (carries_battle_log(api.method)) {
            out->battle_log.assign(blob.begin(), blob.end());
            r.battle_log = parse_battle_log(out->battle_log.data(), out->battle_log.size());
            args += "battle_log[" + std::to_string(len) + "]";
        } else {
            strs.push_back(blob);
            args += len > 64 ? "blob[" + std::to_string(len) + "]" : printable(blob);
        }
    } else if (t == "vec64" || t == "vec32") {
        if (!in.need(4, t)) return false;
        uint32_t k = le32(p + o);
        o += 4;
        size_t es = t == "vec64" ? 8 : 4;
        if (k > (in.n - o) / es) {
            *in.err = t + " count " + std::to_string(k) + " runs past the end of the body";
            return false;
        }
        std::vector<uint64_t> v;
        args += "[";
        for (uint32_t i = 0; i < k; i++, o += es) {
            v.push_back(es == 8 ? le64(p + o) : le32(p + o));
            args += (i ? "," : "") + std::to_string(v.back());
        }
        args += "]";
        r.vecs.push_back(std::move(v));
    } else {
        *in.err = "unknown layout token " + t;
        return false;
    }
    return true;
}

// The per-API shims: the IApiCaller method's arguments where they differ from the wire's.
void apply_shims(const WireApi& api, Request& r, std::vector<std::string>& strs) {
    if (api.name == "CreatePlayer") {
        // wire: char[36] uuid, char[191] name, DeviceType, char[32]; the server's
        // CreatePlayer(name, uuid) (FakeApiCaller::CreatePlayer(s8 const*, s8 const*))
        if (strs.size() >= 2) std::swap(strs[0], strs[1]);
    } else if (api.name == "Login" || api.name == "SimpleLogin") {
        // IApiCaller::Login() takes no arguments: the device UUID, the push token, the advertising
        // id and its flag exist only on the wire (they stay in the packet log)
        strs.clear();
        r.ints.clear();
    }
}

}  // namespace

bool decode_request(const WireApi& api, const uint8_t* p, size_t n, Decoded* out, std::string* err) {
    *out = Decoded();
    Request& r = out->req;
    r.method = api.method;
    r.fid = api.fid;
    if (n < 16) {
        *err = "body shorter than the RequestHeader";
        return false;
    }
    memcpy(out->header, p, 16);
    BodyReader in{p, n, 16, err};
    std::vector<std::string> blobs_and_strs;  // in order, before the shims
    for (const std::string& t : api.layout) {
        if (!out->args.empty()) out->args += " ";
        if (!decode_token(api, t, in, out, blobs_and_strs)) return false;
    }
    if (in.o != n) {
        *err = "body has " + std::to_string(n - in.o) + " bytes after the last argument";
        return false;
    }
    apply_shims(api, r, blobs_and_strs);
    r.strs = std::move(blobs_and_strs);
    return true;
}

std::vector<uint8_t> encode_request(const WireApi& api, const uint8_t header[16], const std::vector<WireArg>& args) {
    std::vector<uint8_t> o(header, header + 16);
    size_t k = 0;
    for (const std::string& t : api.layout) {
        WireArg a = k < args.size() ? args[k] : WireArg();
        k++;
        if (t == "u8" || t == "s8") o.push_back((uint8_t)a.i);
        else if (t == "u32" || t == "s32" || t == "f32" || t == "dev") put32(o, (uint32_t)a.i);
        else if (t == "u64") put64(o, a.i);
        else if (t.rfind("str[", 0) == 0) {
            size_t w = str_width(t);
            for (size_t i = 0; i < w; i++) o.push_back(i < a.s.size() ? (uint8_t)a.s[i] : 0);
        } else if (t == "blob") {
            put32(o, (uint32_t)a.s.size());
            o.insert(o.end(), a.s.begin(), a.s.end());
        } else if (t == "vec64" || t == "vec32") {
            put32(o, (uint32_t)a.v.size());
            for (uint64_t e : a.v) t == "vec64" ? put64(o, e) : put32(o, (uint32_t)e);
        }
    }
    return o;
}

// ---- replies ------------------------------------------------------------------------------------
std::vector<uint8_t> reply_body(const WireApi& api, const std::vector<uint8_t>& msgpack) {
    std::vector<uint8_t> o;
    switch (api.reply_kind) {
        case ReplyKind::kEmpty:
        case ReplyKind::kStart:  // built by result_start_body
            return o;
        case ReplyKind::kFidblob:
        // (b) GetLoginResult reads a FunctionID first; CApiNotify::OnLoginResult only uses it to
        // turn a deserialize failure into an error code, so the request's fid is sent (d).
            put32(o, api.fid);
            [[fallthrough]];
        case ReplyKind::kBlob:
            put32(o, (uint32_t)msgpack.size());
            o.insert(o.end(), msgpack.begin(), msgpack.end());
            return o;
    }
    return o;
}

std::vector<uint8_t> result_start_body(const std::string& token, const std::string& url, const std::string& x) {
    std::vector<uint8_t> o;
    auto field = [&](const std::string& s, size_t w) {
        for (size_t i = 0; i < w; i++) o.push_back(i < s.size() && i + 1 < w ? (uint8_t)s[i] : 0);
    };
    field(token, 1024);
    field(url, 128);
    field(x, 8);
    return o;
}

std::vector<uint8_t> protocol_error_body(uint32_t failing_fid, int64_t status) {
    std::vector<uint8_t> o;
    put64(o, (uint64_t)status);
    put32(o, failing_fid);
    return o;
}

std::string hex(const uint8_t* p, size_t n) {
    static const char d[] = "0123456789abcdef";
    std::string s;
    s.reserve(n * 2);
    for (size_t i = 0; i < n; i++) s += d[p[i] >> 4], s += d[p[i] & 15];
    return s;
}
std::vector<uint8_t> unhex(const std::string& s) {
    std::vector<uint8_t> v;
    auto nib = [](char c) { return c <= '9' ? c - '0' : (c | 0x20) - 'a' + 10; };
    for (size_t i = 0; i + 1 < s.size(); i += 2) v.push_back((uint8_t)(nib(s[i]) << 4 | nib(s[i + 1])));
    return v;
}

}  // namespace soa::server::net

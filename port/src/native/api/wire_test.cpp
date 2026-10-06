// Game-RPC wire format, measured on the client's own serializers (test-only; nothing native).
//
// Every request of the game server API is laid out by `GameProtocoledData::Set<Name>` and then
// encrypted with the session key (Aska::Cryption::Ninja). These tests call each serializer on the
// original ARM64 code without sending anything:
//   - the GameProtocoledData is a zeroed stand-in whose buffer (+0x40, capacity +0x20) is ours;
//   - the Ninja is a zeroed stand-in: its KeyStore is empty, so the encrypt helper returns
//     -0x3b3 before it writes anything and the plaintext body the serializer laid out stays at
//     the tail of the buffer. Two runs over buffers pre-filled with 0xcc and 0x33 give the
//     written bytes (they are the ones both runs agree on).
// The three requests sent in the clear (StartBridge, NoLoginStart, UpdateSession) produce a whole
// packet instead, whose scrambled 24-byte header is decoded and checked.
//
// Tests:
//   wire/request-layouts  all 193 requests (table: wire_table.inc, tools/api_wire.py --gen-inc):
//                         the body must be RequestHeader + the arguments in declaration order,
//                         packed little-endian (see docs/api.md "Wire format"); fixed-width string
//                         fields are measured.
//   wire/reply-roundtrip  a clear reply (NoLoginStartRes) built by the client, sealed with
//                         GameProtocol::Serialize (SHA-1 trailer) and read back by
//                         GameProtocoledData::Deserialize + GetNoLoginStartRes; a corrupted
//                         trailer must be rejected.
//   wire/battle-log       the MissionEnd battle log as the client builds it
//                         (AsonSerializer::Serialize<CBattleLogInfo> + ASON::Serialize, through
//                         client_battle_log.h's serialize_battle_log).
//   wire/inproc-parity    the in-process route's server::Request (server_adapters.h inproc_request)
//                         equals soa-server's decode of the client's own packet for the same call:
//                         the four battle-log APIs through the 3.7.0 request lambdas themselves,
//                         plus requests with vectors and strings through their serializers; and
//                         the route's packet-log text (packet_log.h) equals soa-server's.
//   wire/deco-payload     the SetCharacterDeco payload (AsonSerializer::Serialize<CCharacterDecoSendInfo>).
//   wire/ason-roundtrip   a response body from server/include/soaserver/msgpack.h through the guest
//                         ASON (DeserializeBinary, Serialize) comes back byte-identical.
//   wire/examples         worked examples for docs/api.md.
// SOA_WIRE_DUMP=FILE appends the measured layouts (docs/api-wire.txt) and the examples to FILE.
#include <soa/env.h>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/api/client_battle_log.h"
#include "native/api/packet_log.h"
#include "native/api/server_adapters.h"
#include "native/common/guest_stub.h"
#include "native/common/test.h"
#include "net/wire.h"
#include "soaserver/battle_log.h"
#include "soaserver/msgpack.h"

namespace soa {
namespace {

struct WireApi {
    const char* name;
    const char* sym;
    u32 fid;
    bool enc;
    const char* codes;
};
const WireApi kApis[] = {
#include "native/api/gen/wire_table.inc"
};

constexpr s64 kNoKey = -0x3b3;
constexpr size_t kCap = 0x10000;

FILE* dump_file() {
    static FILE* f = [] {
        const char* p = env::env_str("SOA_WIRE_DUMP");
        return p ? fopen(p, "a") : nullptr;
    }();
    return f;
}
void dump(const char* fmt, ...) __attribute__((format(printf, 1, 2)));
void dump(const char* fmt, ...) {
    FILE* f = dump_file();
    if (!f) return;
    va_list ap;
    va_start(ap, fmt);
    vfprintf(f, fmt, ap);
    va_end(ap);
    fflush(f);
}

std::string hex(const u8* p, size_t n) {
    std::string s;
    char b[4];
    for (size_t i = 0; i < n; i++) snprintf(b, sizeof b, "%02x", p[i]), s += b;
    return s;
}

// The 24-byte packet header: t = CLOCK_MONOTONIC ns, bytes 0..7 = t bytes 6,4,3,0,7,1,2,5,
// bytes 8..23 = {u32 size, u32 fid, u32 counter, u8 flags, 0,0,0} XOR t (byte i ^ t[i & 7]).
struct Header {
    u64 t;
    u32 size, fid, counter;
    u8 flags;
    u8 pad[3];
};
Header descramble(const u8* h) {
    Header r{};
    r.t = (u64)h[4] << 56 | (u64)h[0] << 48 | (u64)h[7] << 40 | (u64)h[1] << 32 | (u64)h[2] << 24 |
          (u64)h[6] << 16 | (u64)h[5] << 8 | (u64)h[3];
    u8 f[16];
    for (int i = 0; i < 16; i++) f[i] = h[8 + i] ^ (u8)(r.t >> (8 * (i & 7)));
    memcpy(&r.size, f, 4), memcpy(&r.fid, f + 4, 4), memcpy(&r.counter, f + 8, 4);
    r.flags = f[12];
    memcpy(r.pad, f + 13, 3);
    return r;
}

// A GameProtocoledData stand-in (the serializers touch +0x20 capacity, +0x24 size, +0x30 fid,
// +0x34 counter, +0x38 flags, +0x40 buffer; the reader also +0x10, +0x19, +0x1c, +0x48..+0x60).
struct FakeData {
    alignas(16) u8 obj[0x100];
    std::vector<u8> buf;
    FakeData() : buf(kCap) { reset(0xcc); }
    void reset(u8 fill) {
        memset(obj, 0, sizeof obj);
        memset(buf.data(), fill, buf.size());
        *(u64*)(obj + 0x40) = (u64)buf.data();
        *(u32*)(obj + 0x20) = (u32)kCap;
        *(u32*)(obj + 0x34) = 0x5a5a0001;  // the counter the header carries
    }
};

struct Arg {
    char code;
    u64 v = 0;
    float f = 0;
    std::vector<u8> mem;
    size_t text_len = 0;  // strings: bytes before the NUL
};

struct Capture {
    s64 status = 0;
    std::vector<u8> body;  // plaintext request body (RequestHeader + arguments)
    bool clear = false;
    Header hdr{};
    std::string error;
};

using Caller = std::function<GuestResult(const GuestArgs&)>;

// Runs a request serializer twice (buffer fills 0xcc / 0x33) and returns the plaintext body.
Capture capture(const WireApi& api, const u8 hdr[16], const std::vector<Arg>& args, const Caller& call) {
    Capture c;
    std::vector<u8> ninja(0x1000, 0);  // empty KeyStore (byte 0 == 0)
    std::vector<u8> runs[2];
    s64 st[2];
    u32 size[2];
    for (int r = 0; r < 2; r++) {
        static FakeData d;
        d.reset(r ? 0x33 : 0xcc);
        GuestArgs ga;
        s64 status = 0x7777;
        ga.sret(&status);
        ga.p(d.obj).p(hdr);
        for (auto& a : args) {
            if (a.code == 'f') ga.f(a.f);
            else ga.i(a.v);
        }
        if (api.enc) ga.p(ninja.data());
        call(ga);
        st[r] = status;
        size[r] = *(u32*)(d.obj + 0x24);
        runs[r] = d.buf;
    }
    c.status = st[0];
    if (st[0] != st[1]) {
        c.error = "status differs between runs";
        return c;
    }
    if (!api.enc) {
        if (st[0] != 0 || size[0] < 24 || size[0] > kCap) {
            c.error = "clear request failed: status " + std::to_string(st[0]);
            return c;
        }
        c.clear = true;
        c.hdr = descramble(runs[0].data());
        c.body.assign(runs[0].begin() + 24, runs[0].begin() + size[0]);
        return c;
    }
    if (st[0] != kNoKey) {
        c.error = "unexpected status " + std::to_string(st[0]);
        return c;
    }
    size_t lo = kCap, hi = 0;
    for (size_t i = 0; i < kCap; i++)
        if (runs[0][i] == runs[1][i]) {
            if (lo == kCap) lo = i;
            hi = i + 1;
        }
    if (lo == kCap) {
        c.error = "nothing written";
        return c;
    }
    for (size_t i = lo; i < hi; i++)
        if (runs[0][i] != runs[1][i]) {
            c.error = "written region not contiguous";
            return c;
        }
    c.body.assign(runs[0].begin() + lo, runs[0].begin() + hi);
    return c;
}

// Matches the body against the argument list; fills `tokens` (layout for the docs).
bool walk(const std::vector<u8>& b, const std::vector<Arg>& args, size_t i, size_t pos,
          std::vector<std::string>& tokens) {
    auto eq = [&](const void* p, size_t n) { return pos + n <= b.size() && memcmp(&b[pos], p, n) == 0; };
    if (i == args.size()) return pos == b.size();
    const Arg& a = args[i];
    size_t mark = tokens.size();
    auto scalar = [&](size_t n, const char* tok) {
        u8 v[8];
        if (a.code == 'f') memcpy(v, &a.f, 4);
        else memcpy(v, &a.v, 8);
        if (!eq(v, n)) return false;
        tokens.push_back(tok);
        if (walk(b, args, i + 1, pos + n, tokens)) return true;
        tokens.resize(mark);
        return false;
    };
    switch (a.code) {
    case 'B': return scalar(1, "u8");
    case 'b': return scalar(1, "s8");
    case 'I': return scalar(4, "u32");
    case 'i': return scalar(4, "s32");
    case 'f': return scalar(4, "f32");
    case 'D': return scalar(4, "dev");
    case 'Q': return scalar(8, "u64");
    case 'P':
    case 'p':
    case 'S': {
        bool counted = i + 1 < args.size() && args[i + 1].code == 'I';
        if (counted) {  // count first, then the elements / bytes
            u32 n = (u32)args[i + 1].v;
            size_t esz = a.code == 'P' ? 8 : a.code == 'p' ? 4 : 1;
            if (eq(&n, 4) && pos + 4 + n * esz <= b.size() && memcmp(&b[pos + 4], a.mem.data(), n * esz) == 0) {
                tokens.push_back(a.code == 'P' ? "vec64" : a.code == 'p' ? "vec32" : "blob");
                if (walk(b, args, i + 2, pos + 4 + n * esz, tokens)) return true;
                tokens.resize(mark);
            }
            if (a.code != 'S') return false;
        }
        // fixed-width field: the longest prefix of the source buffer, then shorter ones
        size_t w = 0;
        while (pos + w < b.size() && w < a.mem.size() && b[pos + w] == a.mem[w]) w++;
        for (; w > 0; w--) {
            tokens.push_back("str[" + std::to_string(w) + "]");
            if (walk(b, args, i + 1, pos + w, tokens)) return true;
            tokens.resize(mark);
        }
        return false;
    }
    }
    return false;
}

// Distinctive arguments for a code string (values depend on the position k).
// small = true: small integers, for the serializers that range-check an argument and refuse
// (-0x3bd) the large distinctive ones (party index < 7, mission type < 4, counts 1..999, ...).
std::vector<Arg> make_args(const char* codes, bool small = false) {
    std::vector<Arg> v;
    size_t n = strlen(codes);
    for (size_t k = 0; k < n; k++) {
        Arg a;
        a.code = codes[k];
        switch (a.code) {
        case 'B': a.v = 0x80 + k; break;
        case 'b': a.v = (u64)(s64)(s8)(-13 - (int)k); break;
        case 'I': a.v = small ? 1 + k % 3 : 0x3c000000u + ((u32)k << 16) + 0x1234; break;
        case 'i': a.v = small ? 1 : (u64)(u32)(-(int)k - 2); break;
        case 'f': a.f = 1.5f + (float)k; break;
        case 'D': a.v = 2; break;  // Android (the serializers refuse > 99)
        case 'Q': a.v = 0x0102030405060700ull + k; break;
        case 'P':
            a.mem.resize(24);
            for (u64 j = 0; j < 3; j++) {
                u64 e = 0x0a0b0c0d00000000ull + (k << 8) + j;
                memcpy(&a.mem[j * 8], &e, 8);
            }
            break;
        case 'p':
            a.mem.resize(12);
            for (u32 j = 0; j < 3; j++) {
                u32 e = 0x0e0f0000u + ((u32)k << 8) + j;
                memcpy(&a.mem[j * 4], &e, 4);
            }
            break;
        case 'S': {
            std::string s = "arg" + std::to_string(k) + "-text";
            a.mem.assign(s.begin(), s.end());
            a.mem.push_back(0);
            a.text_len = s.size();
            for (u32 j = 0; j < 1024; j++) a.mem.push_back((u8)(0x9d + 37 * j + 101 * k + (j >> 8)));
            break;
        }
        }
        v.push_back(std::move(a));
    }
    // counts after arrays / blobs
    for (size_t k = 0; k + 1 < v.size(); k++)
        if ((v[k].code == 'P' || v[k].code == 'p' || v[k].code == 'S') && v[k + 1].code == 'I')
            v[k + 1].v = v[k].code == 'S' ? 5 : 3;
    for (auto& a : v)
        if (!a.mem.empty()) a.v = (u64)a.mem.data();
    return v;
}

const u8 kTestHeader[16] = {0x11, 0x12, 0x13, 0x14, 0x21, 0x22, 0x23, 0x24,
                            0x31, 0x32, 0x33, 0x34, 0x41, 0x42, 0x43, 0x44};

NATIVE_TEST("wire/request-layouts") {
    dump("# Request layouts measured by the `wire/request-layouts` selftest (port/src/native/api/wire_test.cpp)\n"
         "# on the client's GameProtocoledData::Set<Name> serializers. Regenerate: SOA_WIRE_DUMP=FILE soa --selftest wire/request-layouts\n"
         "# name fid plaintext-bytes tokens (hdr = RequestHeader 16 bytes; str[N] = fixed N-byte field;\n"
         "#   blob = u32 len + bytes; vec64/vec32 = u32 n + n elements; dev = u32 DeviceType)\n");
    int ok = 0;
    for (const auto& api : kApis) {
        std::vector<Arg> args = make_args(api.codes);
        u64 fn = t.sym(api.sym);
        if (!fn) continue;
        auto call = [&](const GuestArgs& ga) { return guest_call(fn, ga); };
        Capture c = capture(api, kTestHeader, args, call);
        bool small = false;
        if (c.status == -0x3bd) {  // an argument is range-checked: retry with small values
            small = true;
            args = make_args(api.codes, true);
            c = capture(api, kTestHeader, args, call);
        }
        if (!c.error.empty()) {
            t.fail("%s: %s", api.name, c.error.c_str());
            continue;
        }
        if (c.clear) {
            if (c.hdr.fid != api.fid || c.hdr.size != 24 + c.body.size() || c.hdr.flags != 0 ||
                c.hdr.counter != 0x5a5a0001 || c.hdr.pad[0] | c.hdr.pad[1] | c.hdr.pad[2])
                t.fail("%s: header fid %08x size %u flags %02x counter %08x", api.name, c.hdr.fid, c.hdr.size,
                       c.hdr.flags, c.hdr.counter);
        }
        if (c.body.size() < 16 || memcmp(c.body.data(), kTestHeader, 16) != 0) {
            t.fail("%s: body does not start with the RequestHeader", api.name);
            continue;
        }
        std::vector<std::string> tokens{"hdr"};
        if (!walk(c.body, args, 0, 16, tokens)) {
            t.fail("%s(%s): body does not match the rules: %s", api.name, api.codes,
                   hex(c.body.data(), std::min<size_t>(c.body.size(), 96)).c_str());
            continue;
        }
        ok++;
        std::string line;
        for (auto& s : tokens) line += " " + s;
        dump("%s %08x %zu%s%s\n", api.name, api.fid, c.body.size(), line.c_str(), small ? " range-checked" : "");
    }
    fprintf(stderr, "wire: %d/%zu request layouts match the rules\n", ok, sizeof kApis / sizeof kApis[0]);
}

// ------------------------------------------------------------------------------------------
// Reply framing on the client's own code: SetNoLoginStartRes (a clear reply) -> Serialize
// (SHA-1 trailer) -> Deserialize (header, SHA-1 check) -> GetNoLoginStartRes.

std::vector<u8> sample_reply() {
    server::Value v = server::Value::object();
    v["data"]["Time"] = "2021-06-30 12:00:00";
    v["status"] = 0;
    return server::mp_encode(v);
}

NATIVE_TEST("wire/reply-roundtrip") {
    std::vector<u8> mp = sample_reply();
    FakeData d;
    s64 st = 1;
    GuestArgs ga;
    ga.sret(&st).p(d.obj).p(mp.data()).i(mp.size());
    t.call("_ZN4Aska5Yayoi7GameRPC18GameProtocoledData18SetNoLoginStartResEPKaj", ga);
    u32 size = *(u32*)(d.obj + 0x24);
    if (st != 0 || size != 24 + 4 + mp.size()) return t.fail("SetNoLoginStartRes: status %ld size %u", (long)st, size);
    Header h = descramble(d.buf.data());
    u32 len;
    memcpy(&len, &d.buf[24], 4);
    if (h.fid != 0xa8dad4e4u || h.size != size || h.flags != 0 || len != mp.size() ||
        memcmp(&d.buf[28], mp.data(), mp.size()) != 0)
        t.fail("reply layout: fid %08x size %u flags %02x len %u", h.fid, h.size, h.flags, len);

    std::vector<u8> pkt(size + 0x100);
    u8* out = pkt.data();
    u64 outlen = 0;
    GuestArgs gs;
    gs.sret(&st).i(0).p(d.obj).p(&out).i(pkt.size()).i(0).i(0).p(&outlen);
    t.call("_ZN4Aska5Yayoi7GameRPC12GameProtocol9SerializeEPNS1_18GameProtocoledDataEPPamPKvmPm", gs);
    if (st != 0 || outlen != size + 20) return t.fail("Serialize: status %ld len %lu", (long)st, (unsigned long)outlen);
    pkt.resize(outlen);
    dump("example NoLoginStartRes-packet %s\n", hex(pkt.data(), pkt.size()).c_str());

    auto read_back = [&](const std::vector<u8>& p, s64* status, std::vector<u8>* body) {
        alignas(16) static u8 obj[0x100];
        memset(obj, 0, sizeof obj);
        // Deserialize consumes what it can (header first, then the rest) and sets +0x19 once
        // the whole packet (SHA-1 checked) is in.
        size_t off = 0;
        for (int k = 0; k < 4 && off < p.size() && !obj[0x19]; k++) {
            u64 used = 0;
            GuestArgs gd;
            gd.sret(status).p(obj).p(p.data() + off).p(&used).i(p.size() - off);
            t.call("_ZN4Aska5Yayoi7GameRPC18GameProtocoledData11DeserializeEPKaPmm", gd);
            if (*status < 0 || used == 0) break;
            off += used;
        }
        if (*status == 0 && !obj[0x19]) *status = 0x7fff;  // incomplete
        if (*status == 0) {
            s8* data = nullptr;
            u32 n = 0;
            s64 st2 = 1;
            GuestArgs gg;
            gg.sret(&st2).p(obj).p(&data).p(&n);
            t.call("_ZN4Aska5Yayoi7GameRPC18GameProtocoledData18GetNoLoginStartResERPaRj", gg);
            if (st2 == 0 && data) body->assign((u8*)data, (u8*)data + n);
            if (*(u32*)(obj + 0x30) != 0xa8dad4e4u || *(u32*)(obj + 0x24) != size)
                t.fail("Deserialize: fid %08x size %u", *(u32*)(obj + 0x30), *(u32*)(obj + 0x24));
        }
        if (*(u64*)(obj + 0x40)) guest_call(t.sym("_ZdaPv"), {*(u64*)(obj + 0x40)});
    };
    std::vector<u8> body;
    read_back(pkt, &st, &body);
    if (st != 0 || body != mp) t.fail("read back: status %ld, %zu body bytes", (long)st, body.size());
    std::vector<u8> bad = pkt;
    bad.back() ^= 1;
    body.clear();
    read_back(bad, &st, &body);
    if (st != -0x3b8) t.fail("corrupted SHA-1 trailer: status %ld (want -0x3b8)", (long)st);
}

// ------------------------------------------------------------------------------------------
// MessagePack printing for the docs (JSON-like).
std::string show(const server::Value& v) {
    using V = server::Value;
    switch (v.type) {
    case V::Nil: return "nil";
    case V::Bool: return v.b ? "true" : "false";
    case V::Int: return std::to_string(v.i);
    case V::UInt: return std::to_string(v.u);
    case V::Float: {
        char b[64];
        snprintf(b, sizeof b, "%g", v.f);
        return b;
    }
    case V::Str: return "\"" + v.s + "\"";
    case V::Arr: {
        std::string s = "[";
        for (size_t i = 0; i < v.arr.size(); i++) s += (i ? ", " : "") + show(v.arr[i]);
        return s + "]";
    }
    case V::Map: {
        std::string s = "{";
        for (size_t i = 0; i < v.map.size(); i++) s += (i ? ", " : "") + v.map[i].first + ": " + show(v.map[i].second);
        return s + "}";
    }
    }
    return "?";
}

// The battle log MissionEnd / MissionFailed send, built like the request lambda does
// (x1 = CParameterManager+0x52d8 there; here a fresh CBattleLogInfo with some values).
std::vector<u8> battle_log(TestContext& t) {
    std::vector<u8> info(0x1000, 0);
    u8* p = info.data();
    t.call("_ZN14CBattleLogInfoC2Ev", {(u64)p});
    t.call("_ZN14CBattleLogInfo10InitializeEv", {(u64)p});
    // value slots (property + 0x28) read by CBattleLogInfo::Accept
    auto set = [&](u32 off, u32 v) { memcpy(p + off, &v, 4); };
    p[0x60] = 0;       // is_defeat
    set(0x90, 48210);  // damage_total
    set(0xc0, 48210);  // damage_total_party
    set(0xf0, 12);     // hit_max
    set(0x120, 57);    // hit_total
    set(0x180, 2);     // rush_count
    set(0x1b0, 1);     // battle_result
    set(0x3f0, 83);    // mission_time
    set(0x420, 91);    // mission_total_time
    std::vector<u8> out;
    s64 n = 0;
    if (!server_port::serialize_battle_log((u64)p, &out, &n) || out.size() != (u64)n) t.fail("battle log size %ld (%zu written)", (long)n, out.size());
    t.call("_ZN14CBattleLogInfoD2Ev", {(u64)p});
    return out;
}

NATIVE_TEST("wire/battle-log") {
    std::vector<u8> log = battle_log(t);
    if (log.empty()) return;
    server::Value v = server::mp_decode(log);
    if (v.type != server::Value::Map || !v.find("damage_total") || v.find("damage_total")->u != 48210 ||
        !v.find("mission_time") || v.find("mission_time")->u != 83)
        t.fail("battle log decodes to %s", show(v).c_str());
    std::string keys;
    for (auto& e : v.map) keys += " " + e.first;
    fprintf(stderr, "wire: battle log %zu bytes, %zu keys:%s\n", log.size(), v.map.size(), keys.c_str());
    dump("example battle-log %s\n", hex(log.data(), log.size()).c_str());
    dump("decoded battle-log %s\n", show(v).c_str());
}

// The SetCharacterDeco payload: the live CCharacterDecoSendInfo (CParameterManager+0x8790, the
// object the request lambda serializes) through AsonSerializer::Serialize (read-only).
NATIVE_TEST("wire/deco-payload") {
    u64 pm = *(u64*)t.sym("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE");
    if (!pm) return;
    std::vector<u8> ason(0x200, 0);
    t.call("_ZN4Aska4ASONC1Ev", {(u64)ason.data()});
    t.call("_ZN14AsonSerializer9SerializeI22CCharacterDecoSendInfoEEvRT_jmb", {(u64)ason.data(), pm + 0x8790, 0, 0x4000, 1});
    u64 n = t.call("_ZNK4Aska4ASON18CalcSerializedSizeEv", {(u64)ason.data()});
    std::vector<u8> out(n > 0 && n < 0x10000 ? n : 1);
    u64 w = t.call("_ZNK4Aska4ASON9SerializeEPvm", {(u64)ason.data(), (u64)out.data(), out.size()});
    t.call("_ZN4Aska4ASOND1Ev", {(u64)ason.data()});
    if (w != n) return t.fail("deco payload: size %lu, wrote %ld", (unsigned long)n, (long)w);
    server::Value v = server::mp_decode(out);
    if (v.type != server::Value::Map || !v.find("character_id") || !v.find("hair_id") || !v.find("pose_id"))
        t.fail("deco payload decodes to %s", show(v).c_str());
    dump("example deco-payload %s\n", hex(out.data(), out.size()).c_str());
    dump("decoded deco-payload %s\n", show(v).c_str());
}

// A server-style response through the guest ASON reader and writer.
NATIVE_TEST("wire/ason-roundtrip") {
    using V = server::Value;
    V r = V::object();
    V& d = r["data"];
    d["Time"] = "2021-06-30 12:00:00";
    d["Player"]["id"] = 123456789u;
    d["Player"]["name"] = "Fayt";
    d["Player"]["level"] = 87;
    d["Player"]["fol"] = 1675605u;
    d["Player"]["stamina_update"] = "2021-06-30 11:58:00";
    V ch = V::object();
    ch["id"] = 2130706432u;
    ch["level"] = 60;
    d["MissionResultCharacter"]["2130706432"] = ch;
    d["UpdateStockItem"] = V::array();
    V si = V::object();
    si["master_item_id"] = 3000000001u;
    si["count"] = 12;
    d["UpdateStockItem"].push(si);
    d["rate"] = 1.5;
    d["delta"] = -40;
    d["big"] = 0x1122334455667788ull;
    d["flag"] = true;
    d["none"] = V();
    r["status"] = 0;
    std::vector<u8> mp = server::mp_encode(r);
    std::vector<u8> ason(0x200, 0);
    t.call("_ZN4Aska4ASONC1Ev", {(u64)ason.data()});
    t.call("_ZN4Aska4ASON4InitEjb", {(u64)ason.data(), 0x2000, 1});
    t.call("_ZN4Aska4ASON17DeserializeBinaryEPKvm", {(u64)ason.data(), (u64)mp.data(), mp.size()});
    u64 n = t.call("_ZNK4Aska4ASON18CalcSerializedSizeEv", {(u64)ason.data()});
    std::vector<u8> back(n > 0 && n < 0x10000 ? n : 1);
    u64 w = t.call("_ZNK4Aska4ASON9SerializeEPvm", {(u64)ason.data(), (u64)back.data(), back.size()});
    t.call("_ZN4Aska4ASOND1Ev", {(u64)ason.data()});
    if (w != mp.size() || back != mp)
        t.fail("ASON re-serialized %ld bytes, ours %zu: %s vs %s", (long)w, mp.size(), hex(back.data(), back.size()).c_str(),
               hex(mp.data(), mp.size()).c_str());
    dump("example ason-roundtrip %s\n", hex(mp.data(), mp.size()).c_str());
    dump("decoded ason-roundtrip %s\n", show(r).c_str());
}

// ------------------------------------------------------------------------------------------
// Worked examples for docs/api.md: realistic arguments through the real serializers.
const WireApi* find_api(const char* name) {
    for (const auto& a : kApis)
        if (!strcmp(a.name, name)) return &a;
    return nullptr;
}

NATIVE_TEST("wire/examples") {
    // RequestHeader: player id 123456789, second u32 0, request id 0x1a2b3c4d, u16 0, revision 1471.
    const u8 hdr[16] = {0x15, 0xcd, 0x5b, 0x07, 0, 0, 0, 0, 0x4d, 0x3c, 0x2b, 0x1a, 0, 0, 0xbf, 0x05};
    auto str = [](const char* s, size_t w) {  // a C string in a zeroed buffer (the client's are
        std::vector<u8> m(w + 1024, 0);       // std::strings / stack arrays; see the doc)
        memcpy(m.data(), s, strlen(s));
        return m;
    };
    auto run = [&](const char* label, const char* name, std::vector<Arg> args) {
        const WireApi* api = find_api(name);
        if (!api) return t.fail("%s: no serializer", name);
        for (auto& a : args)
            if (!a.mem.empty()) a.v = (u64)a.mem.data();
        u64 fn = t.sym(api->sym);
        Capture c = capture(*api, hdr, args, [&](const GuestArgs& ga) { return guest_call(fn, ga); });
        if (!c.error.empty()) return t.fail("%s: %s", label, c.error.c_str());
        dump("example %s %s %08x %s\n", label, name, api->fid, hex(c.body.data(), c.body.size()).c_str());
    };
    auto u = [](char code, u64 v) { Arg a; a.code = code; a.v = v; return a; };
    auto m = [](char code, std::vector<u8> mem) { Arg a; a.code = code; a.mem = std::move(mem); return a; };
    auto u64s = [](std::initializer_list<u64> l) {
        std::vector<u8> b(l.size() * 8);
        size_t i = 0;
        for (u64 x : l) memcpy(&b[8 * i++], &x, 8);
        return b;
    };

    run("GetServerTime", "GetServerTime", {});
    const char* uuid = "3f2a9c4e-8b1d-4e7a-9c3f-1b2d3e4f5a6b";
    run("Login", "Login", {m('S', str(uuid, 36)), m('S', str("fcm-token-example", 17)), u('I', 17),
                           m('S', str("00000000-0000-0000-0000-000000000000", 36)), u('I', 36), u('B', 0)});
    run("MissionStart", "MissionStart", {u('i', 0), u('I', 3519778102u /* mf01_001 */), u('I', 0), u('Q', 0),
                                         u('I', 0), u('Q', 0), u('I', 0)});
    std::vector<u8> log = battle_log(t);
    if (!log.empty())
        run("MissionEnd", "MissionEnd", {u('I', 3519778102u), m('S', log), u('I', (u32)log.size()), u('I', 0)});
    run("SaleGacha", "SaleGacha", {u('I', 4218244542u /* gacha_role_0001 */),
                                   m('S', str("0123456789abcdef0123456789abcdef", 32))});
    run("DeepSpaceMissionStart", "DeepSpaceMissionStart",
        {u('I', 2081363u /* ds_area05_He_rare02_A15 */), u('I', 0), m('P', u64s({0x7f000001, 0x7f000002, 0x7f000003})), u('I', 3)});
    run("LockItem", "LockItem", {m('P', u64s({0x7d000001, 0x7d000002})), u('I', 2)});
    run("UpdateName", "UpdateName", {m('S', str("Fayt", 191))});
    run("NoLoginStart", "NoLoginStart", {m('S', str(uuid, 36)), u('D', 2)});
}

// ------------------------------------------------------------------------------------------
// The in-process route's requests equal soa-server's decode of the client's own packets (H,
// port/PLAN.md task 7). For each call: (a) the FakeApiCaller registers -> inproc_request (the
// route's server::Request, battle log included); (b) the 3.7.0 client's packet body for the same
// call -> server::net::decode_request (soa-server's decoder). Method, FunctionID, ints, strings,
// vectors and the battle log's bytes must be equal.
//
// The battle-log APIs run the client's own NetworkApiCaller request lambda (the closure's
// std::function operator(), 3.7.0 @015d68bc, @015d7048, @015f09e8, @015f0c18), with
// NetworkApiCaller::PresendApiCall and GameProtocolProxy::Send<Api> stubbed: Send's arguments
// (the lambda's ints, battle-log buffer and length) then go through GameProtocoledData::Set<Api>,
// the serializer Send uses. The log is the live CBattleLogInfo (CParameterManager+0x52d8) with a
// few values set for the test (restored after).

const char* mismatch(const server::Request& a, const server::Request& b) {
    if (a.method != b.method) return "method";
    if (a.fid != b.fid) return "fid";
    if (a.ints != b.ints) return "ints";
    if (a.strs != b.strs) return "strs";
    if (a.vecs != b.vecs) return "vecs";
    if (!a.battle_log != !b.battle_log) return "battle log presence";
    if (a.battle_log && a.battle_log->ason() != b.battle_log->ason()) return "battle log bytes";
    return nullptr;
}

std::string ints_text(const std::vector<u64>& v) {
    std::string s;
    for (u64 x : v) s += (s.empty() ? "" : ",") + std::to_string(x);
    return s;
}

// The wire request for `name` from serializer arguments, through soa-server's decoder.
bool wire_decode(TestContext& t, const char* name, std::vector<Arg> args, server::net::Decoded* d) {
    const WireApi* api = find_api(name);
    const server::net::WireApi* napi = server::net::api_by_name(name);
    if (!api || !napi) {
        t.fail("%s: not in the wire tables", name);
        return false;
    }
    for (auto& a : args)
        if (!a.mem.empty()) a.v = (u64)a.mem.data();
    u64 fn = t.sym(api->sym);
    Capture c = capture(*api, kTestHeader, args, [&](const GuestArgs& ga) { return guest_call(fn, ga); });
    if (!c.error.empty()) {
        t.fail("%s: serializer: %s", name, c.error.c_str());
        return false;
    }
    std::string err;
    if (!server::net::decode_request(*napi, c.body.data(), c.body.size(), d, &err)) {
        t.fail("%s: soa-server's decoder: %s", name, err.c_str());
        return false;
    }
    return true;
}

void compare(TestContext& t, const char* name, const server::Request& inproc, const server::net::Decoded& d) {
    if (const char* what = mismatch(inproc, d.req))
        t.fail("%s: %s differ: inproc %s(%s) log %zu bytes, wire %s(%s) log %zu bytes", name, what, inproc.method.c_str(),
               ints_text(inproc.ints).c_str(), inproc.battle_log ? inproc.battle_log->ason().size() : 0, d.req.method.c_str(),
               ints_text(d.req.ints).c_str(), d.req.battle_log ? d.req.battle_log->ason().size() : 0);
    // soa --log-packets prints the route's request as soa-server --log-packets prints the wire's
    // (packet_log.h: tests/diff compares the two logs)
    std::string mine = server_port::packet_log::format_args(inproc, inproc.battle_log ? inproc.battle_log->ason().size() : 0);
    if (mine != d.args) t.fail("%s: packet log arguments differ: inproc \"%s\", wire \"%s\"", name, mine.c_str(), d.args.c_str());
}

NATIVE_TEST("wire/inproc-parity") {
    u64 pm_slot = t.sym("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE");
    u64 pm = pm_slot ? *(u64*)pm_slot : 0;
    if (!pm) return t.fail("no CParameterManager");
    u8* log = (u8*)(pm + server_port::kParamBattleLogInfo);
    // value slots of CBattleLogInfo's properties (see battle_log() above): damage_total,
    // mission_time, mission_total_time
    const u32 kSlots[] = {0x90, 0x3f0, 0x420};
    u32 saved[3];
    for (int i = 0; i < 3; i++) memcpy(&saved[i], log + kSlots[i], 4);

    struct BattleApi {
        const char* name;
        const char* fake;  // the FakeApiCaller method (the route's capture symbol)
        u32 fid;
        u64 lambda;  // vaddr of the request lambda's operator() (3.7.0)
        const char* send;
    };
    const BattleApi kBattle[] = {
        {"MissionEnd", "_ZN13FakeApiCaller10MissionEndEjj", 0x8312a64c, 0x14d68bc,
         "_ZN4Aska5Yayoi7GameRPC3Cli17GameProtocolProxy14SendMissionEndERKNS1_13RequestHeaderEjPKajj"},
        {"MissionFailed", "_ZN13FakeApiCaller13MissionFailedEjj", 0x479604f6, 0x14d7048,
         "_ZN4Aska5Yayoi7GameRPC3Cli17GameProtocolProxy17SendMissionFailedERKNS1_13RequestHeaderEijPKaj"},
        {"Sphere211MissionEnd", "_ZN13FakeApiCaller19Sphere211MissionEndEjj", 0x03f169b2, 0x14f09e8,
         "_ZN4Aska5Yayoi7GameRPC3Cli17GameProtocolProxy23SendSphere211MissionEndERKNS1_13RequestHeaderEjjPKaj"},
        {"Sphere211MissionFailed", "_ZN13FakeApiCaller22Sphere211MissionFailedEjj", 0x172f3b5f, 0x14f0c18,
         "_ZN4Aska5Yayoi7GameRPC3Cli17GameProtocolProxy26SendSphere211MissionFailedERKNS1_13RequestHeaderEjjPKaj"},
    };
    const char* kPresend = "_ZN16NetworkApiCaller14PresendApiCallEN4Aska5Yayoi7GameRPC12GameProtocol10FunctionIDEbb";
    if (!native::stub(kPresend, "inproc-parity.presend", 4)) return t.fail("can't stub PresendApiCall");
    std::string presend_name = native::stub_name(t.sym(kPresend));
    int k = 0;
    for (const BattleApi& b : kBattle) {
        k++;
        // this battle's values
        u32 vals[3] = {48210u + (u32)k, 83000u + (u32)k, 91000u + (u32)k};
        for (int i = 0; i < 3; i++) memcpy(log + kSlots[i], &vals[i], 4);
        // the call's two arguments: distinctive (SetMissionFailed range-checks its first, an int:
        // a small one there)
        u32 a1 = k == 2 ? 2u : 0x3c000000u + (u32)k, a2 = 0x0a000000u + (u32)k;

        // (b) the client's lambda -> Send<Api> (stubbed: its arguments) -> Set<Api> -> decoder
        const WireApi* api = find_api(b.name);
        const char* codes = api ? api->codes : "";
        const char* blob_code = strchr(codes, 'S');
        if (!api || strlen(codes) != 4 || !blob_code || blob_code[1] != 'I') {
            t.fail("%s: unexpected serializer codes \"%s\"", b.name, codes);
            continue;
        }
        size_t blob_at = (size_t)(blob_code - codes);
        if (!native::stub(b.send, b.send, 6)) {
            t.fail("%s: can't stub Send", b.name);
            continue;
        }
        std::string send_name = native::stub_name(t.sym(b.send));
        std::vector<Arg> args;
        alignas(16) static u8 nac[0x400];  // the NetworkApiCaller stand-in (only passed along)
        memset(nac, 0, sizeof nac);
        {
            native::StubSession s;
            s.only = {presend_name, send_name};
            s.behave[presend_name] = [&](Cpu& c) { c.set_x(0, (u64)kTestHeader); };
            s.behave[send_name] = [&](Cpu& c) {
                // x8 Status, x0 proxy, x1 header, x2..x5 the arguments in the serializer's order;
                // the log buffer is on the lambda's stack, so it's copied here
                for (size_t i = 0; i < 4; i++) {
                    Arg a;
                    a.code = codes[i];
                    a.v = c.x(2 + (int)i);
                    if (i == blob_at) {
                        const u8* buf = (const u8*)a.v;
                        a.mem.assign(buf, buf + (u32)c.x(3 + (int)i));
                    }
                    args.push_back(std::move(a));
                }
                if (c.x(8)) *(u64*)c.x(8) = 0;
            };
            alignas(16) u8 closure[0x20] = {};
            u64 self = (u64)nac;
            memcpy(closure + 8, &self, 8);
            memcpy(closure + 0x10, &a1, 4);
            memcpy(closure + 0x14, &a2, 4);
            s64 status = 0x7777;
            guest_call(main_lib()->base + b.lambda, {(u64)closure, (u64)&status});
        }
        if (args.size() != 4) {
            t.fail("%s: the request lambda didn't call Send", b.name);
            continue;
        }
        server::net::Decoded d;
        if (!wire_decode(t, b.name, args, &d)) continue;

        // (a) the route: FakeApiCaller::<Api>(this, a1, a2), with garbage in the registers' upper halves
        u64 x[8] = {0x5150, 0xdead000000000000ull | a1, 0xbeef000000000000ull | a2, 0, 0, 0, 0, 0};
        server::Request r = server_port::inproc_request(b.fake, b.fid, x);
        compare(t, b.name, r, d);
        if (!r.battle_log || r.battle_log->prop_u32("mission_time", 0) != vals[1] ||
            r.battle_log->prop_u32("damage_total", 0) != vals[0])
            t.fail("%s: the route's log has mission_time %u damage_total %u (want %u %u)", b.name,
                   r.battle_log ? r.battle_log->prop_u32("mission_time", 0) : 0, r.battle_log ? r.battle_log->prop_u32("damage_total", 0) : 0,
                   vals[1], vals[0]);
        fprintf(stderr, "wire: inproc-parity %s(%s) battle log %zu bytes: equal\n", b.name, ints_text(r.ints).c_str(),
                r.battle_log ? r.battle_log->ason().size() : 0);
    }
    for (int i = 0; i < 3; i++) memcpy(log + kSlots[i], &saved[i], 4);

    // Requests with vectors and strings: the FakeApiCaller registers vs the serializer's packet.
    auto u = [](char code, u64 v) { Arg a; a.code = code; a.v = v; return a; };
    std::vector<u64> items = {0x7d000001, 0x7d000002, 0x7d000003};
    std::vector<u8> item_bytes((const u8*)items.data(), (const u8*)(items.data() + items.size()));
    u64 vec[3] = {(u64)items.data(), (u64)(items.data() + items.size()), (u64)(items.data() + items.size())};
    {
        // DeepSpaceMissionStart(u32 mission, u32, CSTLVector<u64> const& party)
        Arg p;
        p.code = 'P';
        p.mem = item_bytes;
        server::net::Decoded d;
        if (wire_decode(t, "DeepSpaceMissionStart", {u('I', 2081363u), u('I', 2), p, u('I', items.size())}, &d)) {
            u64 x[8] = {0x5150, 2081363u, 2, (u64)vec};
            compare(t, "DeepSpaceMissionStart", server_port::inproc_request("_ZN13FakeApiCaller21DeepSpaceMissionStartEjjRKN9Framework10CSTLVectorImEE", 0x63c9927a, x), d);
        }
    }
    {
        // BulkWithdrawItemFromOneTimeStorage(CSTLVector<u32> const& ids, CSTLVector<u32> const&
        // counts): two u32 vectors, the second mangled as a substitution ("S4_")
        std::vector<u32> ids = {2201000101u, 2201000202u}, counts = {3, 1};
        Arg pi, pc;
        pi.code = pc.code = 'P';
        pi.mem.assign((const u8*)ids.data(), (const u8*)(ids.data() + ids.size()));
        pc.mem.assign((const u8*)counts.data(), (const u8*)(counts.data() + counts.size()));
        u64 vi[3] = {(u64)ids.data(), (u64)(ids.data() + ids.size()), (u64)(ids.data() + ids.size())};
        u64 vc[3] = {(u64)counts.data(), (u64)(counts.data() + counts.size()), (u64)(counts.data() + counts.size())};
        server::net::Decoded d;
        if (wire_decode(t, "BulkWithdrawItemFromOneTimeStorage", {pi, u('I', ids.size()), pc, u('I', counts.size())}, &d)) {
            u64 x[8] = {0x5150, (u64)vi, (u64)vc};
            compare(t, "BulkWithdrawItemFromOneTimeStorage",
                    server_port::inproc_request("_ZN13FakeApiCaller34BulkWithdrawItemFromOneTimeStorageERKN9Framework10CSTLVectorIjEES4_", 0x59f02ddd, x), d);
        }
        // ClearNewOneTimeStorageItem(CSTLVector<u32> const& ids)
        server::net::Decoded d2;
        if (wire_decode(t, "ClearNewOneTimeStorageItem", {pi, u('I', ids.size())}, &d2)) {
            u64 x[8] = {0x5150, (u64)vi};
            compare(t, "ClearNewOneTimeStorageItem",
                    server_port::inproc_request("_ZN13FakeApiCaller26ClearNewOneTimeStorageItemERKN9Framework10CSTLVectorIjEE", 0xd4f178a3, x), d2);
        }
        // DepositItem(CSTLVector<u64> const& uids)
        Arg p;
        p.code = 'P';
        p.mem = item_bytes;
        server::net::Decoded d3;
        if (wire_decode(t, "DepositItem", {p, u('I', items.size())}, &d3)) {
            u64 x[8] = {0x5150, (u64)vec};
            compare(t, "DepositItem", server_port::inproc_request("_ZN13FakeApiCaller11DepositItemERKN9Framework10CSTLVectorImEE", 0xc4cd3b1a, x), d3);
        }
    }
    {
        // The varargs methods (mangled "...z"): a count, then that many u64 uids in the x registers
        // after the fixed arguments and on the stack past x7 (AAPCS64; NetworkApiCaller::LockItem
        // @015c1db8 & co. va_arg them into a CSTLVector<u64>). The wire carries the vector. 9 uids
        // reach the stack for every method; 1 fits in the registers. Garbage in the count
        // register's upper half (a u32 count's own bits only).
        std::vector<u64> many;
        for (u64 i = 0; i < 9; i++) many.push_back(0x7d000010 + i);
        struct Varargs {
            const char* name;
            const char* fake;
            u32 fid;
            bool base;      // a u64 base item uid before the count (ItemCompose, ItemGradeUp)
            bool count64;   // the count is a u64 (GetPresent)
        };
        const Varargs kVarargs[] = {
            {"LockItem", "_ZN13FakeApiCaller8LockItemEjz", 0x88f29383, false, false},
            {"UnlockItem", "_ZN13FakeApiCaller10UnlockItemEjz", 0x2f9569e5, false, false},
            {"SellItem", "_ZN13FakeApiCaller8SellItemEjz", 0x00ee45f7, false, false},
            {"GetPresent", "_ZN13FakeApiCaller10GetPresentEmz", 0x4072d7e1, false, true},
            {"ItemCompose", "_ZN13FakeApiCaller11ItemComposeEmjz", 0x02a5cd1d, true, false},
            {"ItemGradeUp", "_ZN13FakeApiCaller11ItemGradeUpEmjz", 0x8952aa02, true, false},
        };
        const u64 base_uid = 0x7d0000ff;
        for (const Varargs& v : kVarargs) {
            for (size_t n : {(size_t)1, many.size()}) {
                std::vector<u64> uids(many.begin(), many.begin() + n);
                Arg p;
                p.code = 'P';
                p.mem.assign((const u8*)uids.data(), (const u8*)(uids.data() + n));
                std::vector<Arg> args;
                if (v.base) args.push_back(u('Q', base_uid));
                args.push_back(p);
                args.push_back(u('I', n));
                server::net::Decoded d;
                if (!wire_decode(t, v.name, args, &d)) continue;
                u64 x[8] = {0x5150};
                int reg = 1;
                if (v.base) x[reg++] = base_uid;
                x[reg++] = v.count64 ? n : (0xdead000000000000ull | n);
                size_t k = 0;
                for (; k < n && reg < 8; k++) x[reg++] = uids[k];
                std::vector<u64> stack(uids.begin() + k, uids.end());
                stack.push_back(0xbad0bad0bad0bad0ull);  // past the last one: never read
                server::Request r = server_port::inproc_request(v.fake, v.fid, x, stack.data());
                compare(t, v.name, r, d);
                if (r.vecs.size() != 1 || r.vecs[0] != uids) t.fail("%s: %zu uids: the route's vector is wrong", v.name, n);
            }
            fprintf(stderr, "wire: inproc-parity %s (varargs, 1 and %zu uids): equal\n", v.name, many.size());
        }
    }
    {
        // SaleGacha(u32 gacha, s8 const* token): the token is a fixed char[32] on the wire
        const char* token = "0123456789abcdef0123456789abcdef";
        Arg s;
        s.code = 'S';
        s.mem.assign(token, token + 32);
        s.mem.resize(32 + 1024, 0);
        server::net::Decoded d;
        if (wire_decode(t, "SaleGacha", {u('I', 4218244542u), s}, &d)) {
            u64 x[8] = {0x5150, 4218244542u, (u64)token};
            compare(t, "SaleGacha", server_port::inproc_request("_ZN13FakeApiCaller9SaleGachaEjPKa", 0xb164b4c5, x), d);
        }
    }
    // The settings and account requests the route serves (fakeapi.cpp kServedStatusOnly).
    {
        // UpdateConfig(u32 master_config_id, s8 const* value, u32 type): the value a char[191]
        const char* value = "true";
        Arg s;
        s.code = 'S';
        s.mem.assign(value, value + strlen(value));
        s.mem.resize(191 + 1024, 0);
        server::net::Decoded d;
        if (wire_decode(t, "UpdateConfig", {u('I', 4025152546u), s, u('I', 4)}, &d)) {
            u64 x[8] = {0x5150, 4025152546u, (u64)value, 4};
            compare(t, "UpdateConfig", server_port::inproc_request("_ZN13FakeApiCaller12UpdateConfigEjPKaj", 0xf82ca7ca, x), d);
        }
    }
    {
        // ReadExpirationInfo(CSTLVector<u32> const& ids)
        std::vector<u32> ids = {475676447u, 1801260937u};
        Arg p;
        p.code = 'p';
        p.mem.assign((const u8*)ids.data(), (const u8*)(ids.data() + ids.size()));
        u64 v32[3] = {(u64)ids.data(), (u64)(ids.data() + ids.size()), (u64)(ids.data() + ids.size())};
        server::net::Decoded d;
        if (wire_decode(t, "ReadExpirationInfo", {p, u('I', ids.size())}, &d)) {
            u64 x[8] = {0x5150, (u64)v32};
            compare(t, "ReadExpirationInfo",
                    server_port::inproc_request("_ZN13FakeApiCaller18ReadExpirationInfoERKN9Framework10CSTLVectorIjEE", 0xdc269365, x), d);
        }
    }
    {
        // SendGuideInformation(u32), GetScenarioLibraryInfoList(u32): the u32's own bits
        server::net::Decoded d;
        if (wire_decode(t, "SendGuideInformation", {u('I', 732197292u)}, &d)) {
            u64 x[8] = {0x5150, 0xdead00002ba471acull};
            compare(t, "SendGuideInformation", server_port::inproc_request("_ZN13FakeApiCaller20SendGuideInformationEj", 0x5cf6a3e9, x), d);
        }
        server::net::Decoded d2;
        if (wire_decode(t, "GetScenarioLibraryInfoList", {u('I', 3615639045u)}, &d2)) {
            u64 x[8] = {0x5150, 0xbeef0000d7824605ull};
            compare(t, "GetScenarioLibraryInfoList",
                    server_port::inproc_request("_ZN13FakeApiCaller26GetScenarioLibraryInfoListEj", 0xe08c972e, x), d2);
        }
    }
    {
        // UpdateBirthYearMonth(u16 year, u8 month): NetworkApiCaller sends "%u-%02u" in a char[8]
        // (CNetworkUtility::BirthYearMonthNumber2String); the route sends the same string
        const char* text = "1990-05";
        Arg s;
        s.code = 'S';
        s.mem.assign(text, text + strlen(text));
        s.mem.resize(8 + 1024, 0);
        server::net::Decoded d;
        if (wire_decode(t, "UpdateBirthYearMonth", {s}, &d)) {
            u64 x[8] = {0x5150, 0xdead0000000007c6ull, 0xbeef000000000005ull};
            compare(t, "UpdateBirthYearMonth", server_port::inproc_request("_ZN13FakeApiCaller20UpdateBirthYearMonthEth", 0x0088b260, x), d);
        }
    }
    {
        // MissionContinue(bool) (a status-only method the route serves): the wire adds the device
        // UUID (char[36]) and DeviceType, which the server's handlers don't read and the FakeApiCaller
        // method doesn't have (docs/server-rules.md "Wire-only arguments"), so only the method, fid
        // and ints are compared; the bool is the register's low byte only
        const char* uuid = "3f2a9c4e-8b1d-4e7a-9c3f-1b2d3e4f5a6b";
        Arg s;
        s.code = 'S';
        s.mem.assign(uuid, uuid + 36);
        s.mem.resize(36 + 1024, 0);
        server::net::Decoded d;
        if (wire_decode(t, "MissionContinue", {s, u('D', 2), u('B', 1)}, &d)) {
            u64 x[8] = {0x5150, 0xdead000000000001ull};
            server::Request r = server_port::inproc_request("_ZN13FakeApiCaller15MissionContinueEb", 0x755cba3d, x);
            if (r.method != d.req.method || r.fid != d.req.fid || r.ints != d.req.ints)
                t.fail("MissionContinue: inproc %s(%s) fid %x, wire %s(%s) fid %x", r.method.c_str(), ints_text(r.ints).c_str(), r.fid,
                       d.req.method.c_str(), ints_text(d.req.ints).c_str(), d.req.fid);
            if (d.req.strs != std::vector<std::string>{uuid}) t.fail("MissionContinue: the wire's strings aren't the device UUID alone");
        }
    }
    {
        // MissionLose() and InheritAccessory(u64 base, u64 lost) (status-only methods the route serves)
        server::net::Decoded d;
        if (wire_decode(t, "MissionLose", {}, &d)) {
            u64 x[8] = {0x5150};
            compare(t, "MissionLose", server_port::inproc_request("_ZN13FakeApiCaller11MissionLoseEv", 0x863bb1ec, x), d);
        }
        server::net::Decoded d2;
        if (wire_decode(t, "InheritAccessory", {u('Q', 0x7d000005), u('Q', 0x7d000009)}, &d2)) {
            u64 x[8] = {0x5150, 0x7d000005, 0x7d000009};
            compare(t, "InheritAccessory", server_port::inproc_request("_ZN13FakeApiCaller16InheritAccessoryEmm", 0xd9feb3e8, x), d2);
        }
    }
    {
        // TrainMastery(u64 disciple, u64 master, u8 dojo, u32 type, u8 step, u8 option): u8s
        // between wider arguments, their registers' upper bits undefined (AAPCS64)
        server::net::Decoded d;
        if (wire_decode(t, "TrainMastery", {u('Q', 0x7e000005ull), u('Q', 0x7e000009ull), u('B', 2), u('I', 4177083684u), u('B', 3), u('B', 5)},
                        &d)) {
            u64 x[8] = {0x5150, 0x7e000005ull, 0x7e000009ull, 0xdead0002ull, 4177083684u, 0xbeef0003ull, 0x1234505ull};
            compare(t, "TrainMastery", server_port::inproc_request("_ZN13FakeApiCaller12TrainMasteryEmmhjhh", 0xbb0e7ef9, x), d);
        }
    }
    {
        // CoinDepositCreate(u8 platform, s32 product, char const* user): the string is a
        // length-prefixed blob on the wire (CPaymentManager sends "user_id")
        const char* user = "user_id";
        Arg s;
        s.code = 'S';
        s.mem.assign(user, user + strlen(user) + 1);
        s.text_len = strlen(user);
        server::net::Decoded d;
        if (wire_decode(t, "CoinDepositCreate", {u('b', 1), u('i', 3), s, u('I', strlen(user))}, &d)) {
            u64 x[8] = {0x5150, 1, 3, (u64)user};
            compare(t, "CoinDepositCreate", server_port::inproc_request("_ZN13FakeApiCaller17CoinDepositCreateEhiPKc", 0x3850fb96, x), d);
        }
    }
    {
        // CoinDepositAndroidUpdate(u32 trans, char const* receipt, char const* signature): the
        // mangled name's second string is a substitution (S1_)
        const char* receipt = "eyJwcm9kdWN0SWQiOiJzb2EubG9jYWwuY29pbl8wMDEifQ==";
        const char* sig = "local-signature";
        Arg a, b;
        a.code = b.code = 'S';
        a.mem.assign(receipt, receipt + strlen(receipt) + 1);
        a.text_len = strlen(receipt);
        b.mem.assign(sig, sig + strlen(sig) + 1);
        b.text_len = strlen(sig);
        server::net::Decoded d;
        if (wire_decode(t, "CoinDepositAndroidUpdate", {u('I', 7), a, u('I', strlen(receipt)), b, u('I', strlen(sig))}, &d)) {
            u64 x[8] = {0x5150, 7, (u64)receipt, (u64)sig};
            compare(t, "CoinDepositAndroidUpdate",
                    server_port::inproc_request("_ZN13FakeApiCaller24CoinDepositAndroidUpdateEjPKcS1_", 0x089ac659, x), d);
        }
    }
}

}  // namespace
}  // namespace soa

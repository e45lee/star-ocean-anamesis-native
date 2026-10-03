// soa-server --wire-tool (tool.h).
#include "tool.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>

#include "client.h"
#include "loop.h"
#include "ninja/ninja_ref.h"
#include "wire.h"

namespace soa::server::net {

namespace {
int usage() {
    fprintf(stderr,
            "soa-server --wire-tool CMD ...   (packets are printed as hex; KEY is the sharedSecurityKey text,\n"
            "                                 its first 32 characters are the Ninja key)\n"
            "  reply API KEY MSGPACK_HEX|@FILE [COUNTER]  the reply packet of request API (e.g. GetPlayer) for a\n"
            "                                 response MessagePack, encrypted (AES-128) when the reply is\n"
            "  start TOKEN URL [X]             a ResultStart packet\n"
            "  update-session                  a ResultUpdateSession packet\n"
            "  error FID_HEX STATUS            a ProtocolError packet\n"
            "  decode KEY PACKET_HEX           decode a request packet: name, method, its arguments\n"
            "  session HOST:PORT [UUID] [HTTP] a client session against a running soa-server: bridge, Login,\n"
            "                                  GetPlayer, GetServerTime; a bridge URL on production-game.so-ana.com\n"
            "                                  is POSTed to HTTP (soa-server's --http; default HOST:44380)\n");
    return 2;
}
std::vector<uint8_t> key_bytes(const char* k) {
    std::vector<uint8_t> v(ninja::kKeySize, 0);
    for (size_t i = 0; i < ninja::kKeySize && k[i]; i++) v[i] = (uint8_t)k[i];
    return v;
}
void print_packet(const Packet& p) { printf("%s\n", hex(encode_packet(p, 0x0123456789abcdefull)).c_str()); }
}  // namespace

int wire_tool(int argc, char** argv) {
    if (argc < 1) return usage();
    std::string cmd = argv[0];
    if (cmd == "reply" && argc >= 4) {
        const WireApi* api = api_by_name(argv[1]);
        if (!api) return fprintf(stderr, "unknown API %s\n", argv[1]), 1;
        Packet p;
        p.fid = api->reply_fid;
        p.counter = argc >= 5 ? (uint32_t)strtoul(argv[4], nullptr, 0) : 7;
        std::string body_hex = argv[3];
        if (!body_hex.empty() && body_hex[0] == '@') {  // @FILE: the MessagePack's bytes from FILE (bodies too long for an argument)
            FILE* f = fopen(body_hex.c_str() + 1, "rb");
            if (!f) return fprintf(stderr, "cannot read %s\n", body_hex.c_str() + 1), 1;
            std::vector<uint8_t> raw;
            for (int ch; (ch = fgetc(f)) != EOF;) raw.push_back((uint8_t)ch);
            fclose(f);
            body_hex = hex(raw);
        }
        std::vector<uint8_t> plain = reply_body(*api, unhex(body_hex.c_str()));
        if (api->reply_encrypted) {
            auto key = key_bytes(argv[2]);
            p.body = ninja::encrypt(key.data(), ninja::kAES128, 0x2468ace1, 0x13579bdf, plain.data(), plain.size());
            p.flags = kFlagEncrypted;
        } else {
            p.body = plain;
        }
        print_packet(p);
        return 0;
    }
    if (cmd == "start" && argc >= 3) {
        Packet p;
        p.fid = api_by_name("StartBridge")->reply_fid;
        p.counter = 7;
        p.body = result_start_body(argv[1], argv[2], argc >= 4 ? argv[3] : "");
        print_packet(p);
        return 0;
    }
    if (cmd == "update-session") {
        Packet p;
        p.fid = api_by_name("UpdateSession")->reply_fid;
        p.counter = 7;
        print_packet(p);
        return 0;
    }
    if (cmd == "error" && argc >= 3) {
        Packet p;
        p.fid = kFidProtocolError;
        p.counter = 7;
        p.body = protocol_error_body((uint32_t)strtoul(argv[1], nullptr, 16), strtoll(argv[2], nullptr, 0));
        print_packet(p);
        return 0;
    }
    if (cmd == "decode" && argc >= 3) {
        PacketReader rd;
        auto bytes = unhex(argv[2]);
        rd.feed(bytes.data(), bytes.size());
        Packet p;
        auto r = rd.next(&p);
        if (r != PacketReader::kPacket) return fprintf(stderr, "packet refused (%d)\n", (int)r), 1;
        const WireApi* api = api_by_fid(p.fid);
        if (!api) return fprintf(stderr, "unknown fid %08x\n", p.fid), 1;
        std::vector<uint8_t> plain = p.body;
        if (p.flags & kFlagEncrypted) {
            auto key = key_bytes(argv[1]);
            uint32_t alg = 0;
            if (int st = ninja::decrypt(key.data(), p.body.data(), p.body.size(), &plain, &alg)) return fprintf(stderr, "decrypt %d\n", st), 1;
        }
        Decoded d;
        std::string err;
        if (!decode_request(*api, plain.data(), plain.size(), &d, &err)) return fprintf(stderr, "decode: %s\n", err.c_str()), 1;
        printf("%s %s counter=%u args: %s\n", api->name.c_str(), d.req.method.c_str(), p.counter, d.args.c_str());
        return 0;
    }
    if (cmd == "session" && argc >= 2) {
        std::string host, err;
        uint16_t port = 0;
        if (!parse_host_port(argv[1], &host, &port)) return usage();
        if (!run_session(host, port, argc >= 3 ? argv[2] : "3f2a9c4e-8b1d-4e7a-9c3f-1b2d3e4f5a6b", &err, argc >= 4 ? argv[3] : "")) {
            fprintf(stderr, "session failed: %s\n", err.c_str());
            return 1;
        }
        return 0;
    }
    return usage();
}

}  // namespace soa::server::net

// The packet log's line formats (packet_log.h). Our code.
#include "packet_log.h"

#include <cstdio>

#include "soaserver/msgpack.h"
#include "soaserver/server.h"  // format_time
#include "wire.h"              // hex

namespace soa::server::net {

std::string printable(const std::string& s) {
    for (unsigned char c : s)
        if (c < 0x20 || c >= 0x7f) return "0x" + hex((const uint8_t*)s.data(), s.size());
    return "\"" + s + "\"";
}

std::string data_keys(const std::vector<uint8_t>& msgpack) {
    Value v = mp_decode(msgpack);
    const Value* d = v.type == Value::Map ? v.find("data") : nullptr;
    std::string s;
    if (d && d->type == Value::Map)
        for (auto& e : d->map) s += (s.empty() ? "" : ",") + e.first;
    const Value* st = v.type == Value::Map ? v.find("status") : nullptr;
    return "data{" + s + "} status=" + (st ? std::to_string(st->type == Value::Int ? st->i : (int64_t)st->u) : "-");
}

std::string fid_hex(uint32_t fid) {
    char b[16];
    snprintf(b, sizeof b, "%08x", fid);
    return b;
}

std::string log_stamp(time_t t) { return format_time((int64_t)t); }

std::string request_head(uint64_t conn, uint64_t seq, const std::string& api, uint32_t fid) {
    return "conn " + std::to_string(conn) + " #" + std::to_string(seq) + " > " + api + " fid=" + fid_hex(fid);
}

std::string request_line(const std::string& head, const std::string& alg, size_t plain, const std::string& method, const std::string& args) {
    return head + " " + alg + " plain=" + std::to_string(plain) + " method=" + method + " args: " + args;
}

std::string reply_line(const std::string& reply, uint32_t fid, const std::string& alg, size_t plain, std::optional<size_t> packet,
                       const std::string& note) {
    return "  < " + reply + " fid=" + fid_hex(fid) + " " + alg + " plain=" + std::to_string(plain) +
           (packet ? " packet=" + std::to_string(*packet) : "") + (note.empty() ? "" : " " + note);
}

}  // namespace soa::server::net

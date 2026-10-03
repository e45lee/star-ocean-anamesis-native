// The in-process route's packet log (packet_log.h). Port code.
#include "native/api/packet_log.h"

#include <sys/stat.h>
#include <time.h>

#include <cstdio>
#include <cstring>
#include <map>
#include <mutex>

#include "core/log.h"
#include "net/wire.h"
#include "soaserver/msgpack.h"

namespace soa::server_port::packet_log {

namespace {

std::mutex g_mu;
FILE* g_log = nullptr;
std::string g_dir;
uint64_t g_seq = 0;
std::map<uint32_t, uint32_t> g_alias;  // internal request fid -> the fid it answers

// soa-server's packet log stamps (server/net/game.cpp fmt_local): the host's local time.
std::string stamp() {
    time_t t = time(nullptr);
    struct tm tm;
    localtime_r(&t, &tm);
    char b[32];
    strftime(b, sizeof b, "%Y-%m-%d %H:%M:%S", &tm);
    return b;
}

void line(const std::string& s) {
    if (!g_log) return;
    fprintf(g_log, "%s %s\n", stamp().c_str(), s.c_str());
    fflush(g_log);
}

void write_file(const std::string& name, const void* p, size_t n) {
    if (FILE* f = fopen((g_dir + "/" + name).c_str(), "wb")) {
        fwrite(p, 1, n, f);
        fclose(f);
    }
}

std::string fid_hex(uint32_t fid) {
    char b[16];
    snprintf(b, sizeof b, "%08x", fid);
    return b;
}

// server/net/wire.cpp printable(): a string, or its bytes in hex when it isn't plain ASCII.
std::string printable(const std::string& s) {
    for (unsigned char c : s)
        if (c < 0x20 || c >= 0x7f) {
            std::string h = "0x";
            char b[4];
            for (unsigned char d : s) snprintf(b, sizeof b, "%02x", d), h += b;
            return h;
        }
    return "\"" + s + "\"";
}

std::string raw_args(const server::Request& r) {
    std::string a = "ints=[";
    for (size_t i = 0; i < r.ints.size(); i++) a += (i ? "," : "") + std::to_string(r.ints[i]);
    a += "] strs=[";
    for (size_t i = 0; i < r.strs.size(); i++) a += (i ? "," : "") + printable(r.strs[i]);
    a += "] vecs=[";
    for (size_t i = 0; i < r.vecs.size(); i++) {
        a += i ? ",[" : "[";
        for (size_t k = 0; k < r.vecs[i].size(); k++) a += (k ? "," : "") + std::to_string(r.vecs[i][k]);
        a += "]";
    }
    return a + "]";
}

// soa-server's data_keys (server/net/game.cpp): the top-level keys of the data map, the status.
std::string data_keys(const std::vector<char>& body) {
    server::Value v = server::mp_decode(std::vector<uint8_t>(body.begin(), body.end()));
    const server::Value* d = v.type == server::Value::Map ? v.find("data") : nullptr;
    std::string s;
    if (d && d->type == server::Value::Map)
        for (auto& e : d->map) s += (s.empty() ? "" : ",") + e.first;
    const server::Value* st = v.type == server::Value::Map ? v.find("status") : nullptr;
    return "data{" + s + "} status=" + (st ? std::to_string(st->type == server::Value::Int ? st->i : (int64_t)st->u) : "-");
}

}  // namespace

void open(const std::string& dir) {
    std::lock_guard<std::mutex> l(g_mu);
    if (dir.empty() || g_log) return;
    mkdir(dir.c_str(), 0755);
    g_dir = dir;
    g_log = fopen((dir + "/packets.log").c_str(), "a");
    if (!g_log) LOGW("server", "--log-packets: can't write %s/packets.log", dir.c_str());
    else LOGI("server", "--log-packets: the in-process route's requests and replies go to %s/packets.log", dir.c_str());
}

bool enabled() { return g_log != nullptr; }

std::string format_args(const server::Request& r, size_t battle_log_size) {
    const server::net::WireApi* api = server::net::api_by_fid(r.fid);
    if (!api) return raw_args(r);
    // The wire's order of strings: CreatePlayer's wire has (uuid, name), the method (name, uuid)
    // (server/net/wire.cpp's shim, reversed).
    std::vector<std::string> strs = r.strs;
    if (api->name == "CreatePlayer" && strs.size() >= 2) std::swap(strs[0], strs[1]);
    size_t ni = 0, ns = 0, nv = 0;
    std::string args;
    for (const std::string& t : api->layout) {
        if (!args.empty()) args += " ";
        if (t == "u8" || t == "s8" || t == "u32" || t == "s32" || t == "f32" || t == "u64") {
            if (ni >= r.ints.size()) return raw_args(r);
            uint64_t v = r.ints[ni++];
            if (t == "s32") args += std::to_string((int32_t)(uint32_t)v);
            else if (t == "f32") {
                uint32_t bits = (uint32_t)v;
                float f;
                memcpy(&f, &bits, 4);
                args += std::to_string(f);
            } else args += std::to_string(t == "u64" ? v : (uint32_t)v);
        } else if (t == "dev") {
            args += "dev=?";  // the FakeApiCaller methods don't take the DeviceType
        } else if (t.rfind("str[", 0) == 0) {
            if (ns >= strs.size()) return raw_args(r);
            args += printable(strs[ns++]);
        } else if (t == "blob") {
            if (server::carries_battle_log(api->method)) {
                args += "battle_log[" + std::to_string(battle_log_size) + "]";
            } else {
                if (ns >= strs.size()) return raw_args(r);
                const std::string& s = strs[ns++];
                args += s.size() > 64 ? "blob[" + std::to_string(s.size()) + "]" : printable(s);
            }
        } else if (t == "vec64" || t == "vec32") {
            if (nv >= r.vecs.size()) return raw_args(r);
            args += "[";
            const auto& v = r.vecs[nv++];
            for (size_t i = 0; i < v.size(); i++) args += (i ? "," : "") + std::to_string(v[i]);
            args += "]";
        } else {
            return raw_args(r);
        }
    }
    if (ni != r.ints.size() || ns != strs.size() || nv != r.vecs.size()) return raw_args(r);
    return args;
}

void request(const server::Request& r, const std::vector<uint8_t>& battle_log) {
    std::lock_guard<std::mutex> l(g_mu);
    if (!g_log || g_alias.count(r.fid)) return;
    const server::net::WireApi* api = server::net::api_by_fid(r.fid);
    std::string name = api ? api->name : r.method;
    uint64_t seq = ++g_seq;
    line("conn 0 #" + std::to_string(seq) + " > " + name + " fid=" + fid_hex(r.fid) + " inproc plain=0 method=" + r.method +
         " args: " + format_args(r, battle_log.size()));
    if (!battle_log.empty()) write_file(std::to_string(seq) + "-" + name + "-battle_log.msgp", battle_log.data(), battle_log.size());
}

void reply(uint32_t fid, const std::vector<char>& body) {
    std::lock_guard<std::mutex> l(g_mu);
    if (!g_log) return;
    auto a = g_alias.find(fid);
    if (a != g_alias.end()) {
        fid = a->second;
        g_alias.erase(a);
    }
    const server::net::WireApi* api = server::net::api_by_fid(fid);
    std::string name = api ? api->reply : "?";
    uint32_t rfid = api ? api->reply_fid : 0;
    write_file(std::to_string(g_seq) + "-" + name + ".msgp", body.data(), body.size());
    line("  < " + name + " fid=" + fid_hex(rfid) + " inproc plain=" + std::to_string(body.size()) + " " + data_keys(body));
}

void refused(uint32_t fid, uint32_t code) {
    std::lock_guard<std::mutex> l(g_mu);
    if (!g_log) return;
    g_alias.erase(fid);
    line("  < ProtocolError fid=" + fid_hex(server::net::kFidProtocolError) + " inproc plain=0 status=" + std::to_string(code) +
         " (the server's error code)");
}

void answer_as(uint32_t fid, uint32_t as_fid) {
    std::lock_guard<std::mutex> l(g_mu);
    if (g_log) g_alias[fid] = as_fid;
}

}  // namespace soa::server_port::packet_log

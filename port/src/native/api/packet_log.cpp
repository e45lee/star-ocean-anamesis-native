// The in-process route's packet log (packet_log.h). Port code.
#include "native/api/packet_log.h"

#include <sys/stat.h>
#include <time.h>

#include <cstdio>
#include <cstring>
#include <map>
#include <mutex>

#include "soaruntime/core/log.h"
#include "net/packet_log.h"  // the line formats soa-server's log has
#include "net/wire.h"
#include "soaserver/msgpack.h"

namespace soa::server_port::packet_log {

namespace {

std::mutex g_mu;
FILE* g_log = nullptr;
std::string g_dir;
uint64_t g_seq = 0;
// queued fid -> the wire API its request was logged as (the reply's name)
std::map<uint32_t, const server::net::WireApi*> g_api;

// The wire API a captured request is: the one whose method it is, else the one of its fid. Some
// FakeApiCaller methods queue under another API's FunctionID (EquipAccessory under EquipWeapon's,
// Blacklist* under Follow*'s, AchievementReceiveList under AchievementActiveList's, SendErrorLog
// under UpdateKiyakuVersion's, LimitBreakCharacter_Legacy under LimitBreakCharacter's,
// SimpleLogin under Login's: port/src/native/api/gen/fakeapi_tables.inc); by the method, the log
// names them, their fid and their reply as soa-server's wire log does.
const server::net::WireApi* wire_api(const server::Request& r) {
    if (const server::net::WireApi* api = server::net::api_by_method(r.method)) return api;
    return server::net::api_by_fid(r.fid);
}

void line(const std::string& s) {
    if (!g_log) return;
    fprintf(g_log, "%s %s\n", server::net::log_stamp(time(nullptr)).c_str(), s.c_str());
    fflush(g_log);
}

void write_file(const std::string& name, const void* p, size_t n) {
    if (FILE* f = fopen((g_dir + "/" + name).c_str(), "wb")) {
        fwrite(p, 1, n, f);
        fclose(f);
    }
}

std::string raw_args(const server::Request& r) {
    std::string a = "ints=[";
    for (size_t i = 0; i < r.ints.size(); i++) a += (i ? "," : "") + std::to_string(r.ints[i]);
    a += "] strs=[";
    for (size_t i = 0; i < r.strs.size(); i++) a += (i ? "," : "") + server::net::printable(r.strs[i]);
    a += "] vecs=[";
    for (size_t i = 0; i < r.vecs.size(); i++) {
        a += i ? ",[" : "[";
        for (size_t k = 0; k < r.vecs[i].size(); k++) a += (k ? "," : "") + std::to_string(r.vecs[i][k]);
        a += "]";
    }
    return a + "]";
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
    const server::net::WireApi* api = wire_api(r);
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
            args += server::net::printable(strs[ns++]);
        } else if (t == "blob") {
            if (server::carries_battle_log(api->method)) {
                args += "battle_log[" + std::to_string(battle_log_size) + "]";
            } else {
                if (ns >= strs.size()) return raw_args(r);
                const std::string& s = strs[ns++];
                args += s.size() > 64 ? "blob[" + std::to_string(s.size()) + "]" : server::net::printable(s);
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
    if (!g_log) return;
    const server::net::WireApi* api = wire_api(r);
    std::string name = api ? api->name : r.method;
    if (api) g_api[r.fid] = api;
    else g_api.erase(r.fid);
    uint64_t seq = ++g_seq;
    line(server::net::request_line(server::net::request_head(0, seq, name, api ? api->fid : r.fid), "inproc", 0, r.method,
                                   format_args(r, battle_log.size())));
    if (!battle_log.empty()) write_file(std::to_string(seq) + "-" + name + "-battle_log.msgp", battle_log.data(), battle_log.size());
}

void reply(uint32_t fid, const std::vector<char>& body) {
    std::lock_guard<std::mutex> l(g_mu);
    if (!g_log) return;
    auto logged = g_api.find(fid);
    const server::net::WireApi* api = logged != g_api.end() ? logged->second : server::net::api_by_fid(fid);
    if (logged != g_api.end()) g_api.erase(logged);
    std::string name = api ? api->reply : "?";
    uint32_t rfid = api ? api->reply_fid : 0;
    write_file(std::to_string(g_seq) + "-" + name + ".msgp", body.data(), body.size());
    line(server::net::reply_line(name, rfid, "inproc", body.size(), std::nullopt,
                                 server::net::data_keys(std::vector<uint8_t>(body.begin(), body.end()))));
}

void refused(uint32_t fid, uint32_t code) {
    std::lock_guard<std::mutex> l(g_mu);
    if (!g_log) return;
    g_api.erase(fid);
    line(server::net::reply_line("ProtocolError", server::net::kFidProtocolError, "inproc", 0, std::nullopt,
                                 "status=" + std::to_string(code) + " (the server's error code)"));
}


}  // namespace soa::server_port::packet_log

// The client's network redirect (emulator/README.md "Networking"), registered by
// platform370::install (Config::net) through the runtime's extension point (hle_add_registrar +
// Hle::override_fn); the game code is unchanged.
//
// The 3.7.0 client connects to production-game.so-ana.com:443 (raw TCP, its GameRPC protocol;
// docs/online-server.md §2) and, for multiplayer, to <lobby host>:4001. Those hosts no longer
// exist. Like a phone whose DNS (hosts file) points the game's names at another machine, the
// platform answers the name lookups itself and moves the ports to where soa-server listens
// (Config::netcfg; soa-emu's --server, --lobby, --map-host):
//   - getaddrinfo / gethostbyname: production-game.so-ana.com and every mapped NAME resolve
//     to server_host (or the NAME=ADDR address);
//   - connect: to an address a mapped name resolved to (or server_host), port 443 becomes
//     server_port and port 4001 becomes the lobby (when given).
// Every other lookup and connection goes to the runtime's own thunks unchanged.
//
// On the way it fixes two Bionic-vs-glibc gaps of the runtime's getaddrinfo thunk, here in the
// override (the runtime is not edited):
//   - the hints' ai_flags: the bits differ (AI_NUMERICSERV 0x8 / 0x400, AI_ADDRCONFIG 0x400 /
//     0x20, AI_V4MAPPED 0x800 / 0x8, AI_ALL 0x100 / 0x10; PASSIVE, CANONNAME and NUMERICHOST
//     agree). They are translated to glibc's for the call and back to Bionic's in the results;
//   - the EAI_* return codes: Bionic's are positive (netdb.h: EAI_NONAME 8, EAI_AGAIN 2 ...),
//     glibc's negative; they are translated to Bionic's.
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#endif
#include <string.h>

#include <mutex>
#include <set>
#include <string>

#include "soaruntime/core/hle.h"
#include "soaruntime/core/log.h"
#include "soaruntime/core/thread_record.h"
#include "internal.h"
#include "platform370/platform370.h"

namespace soa::platform370 {

// The guest's (Linux / bionic) AF_INET6; Winsock's is 23. Guest sockaddrs carry the guest's.
constexpr int kGuestAfInet6 = 10;

std::string mapped_address(const std::string& name) {
    auto& cfg = net_config();
    if (name.empty()) return "";
    std::string lower;
    for (char ch : name) lower += (char)tolower((unsigned char)ch);
    auto it = cfg.hosts.find(lower);
    if (it != cfg.hosts.end()) return it->second.empty() ? cfg.server_host : it->second;
    if (lower == "production-game.so-ana.com") return cfg.server_host;
    return "";
}

namespace detail {
namespace {

// Bionic's struct addrinfo (64-bit): the same field order as glibc's, but ai_canonname comes
// before ai_addr there too; the runtime's thunk builds this layout.
struct BionicAddrinfo {
    s32 ai_flags, ai_family, ai_socktype, ai_protocol;
    u32 ai_addrlen;
    u32 pad;
    u64 ai_canonname, ai_addr, ai_next;
};

// Bionic <-> glibc ai_flags. Bionic (libc/include/netdb.h): PASSIVE 1, CANONNAME 2, NUMERICHOST 4,
// NUMERICSERV 8, ALL 0x100, V4MAPPED_CFG 0x200, ADDRCONFIG 0x400, V4MAPPED 0x800.
// glibc (netdb.h): PASSIVE 1, CANONNAME 2, NUMERICHOST 4, V4MAPPED 8, ALL 0x10, ADDRCONFIG 0x20,
// NUMERICSERV 0x400. Bionic's AI_V4MAPPED_CFG has no glibc counterpart: dropped.
struct FlagPair {
    int bionic, host;
};
constexpr FlagPair kFlags[] = {
    {0x1, AI_PASSIVE}, {0x2, AI_CANONNAME}, {0x4, AI_NUMERICHOST}, {0x8, AI_NUMERICSERV},
    {0x100, AI_ALL},   {0x400, AI_ADDRCONFIG}, {0x800, AI_V4MAPPED},
};
int flags_to_host(int b) {
    int h = 0;
    for (auto& f : kFlags)
        if (b & f.bionic) h |= f.host;
    return h;
}
int flags_to_bionic(int h) {
    int b = 0;
    for (auto& f : kFlags)
        if (h & f.host) b |= f.bionic;
    return b;
}

// glibc EAI_* (negative) -> Bionic's (positive: ADDRFAMILY 1, AGAIN 2, BADFLAGS 3, FAIL 4,
// FAMILY 5, MEMORY 6, NODATA 7, NONAME 8, SERVICE 9, SOCKTYPE 10, SYSTEM 11, OVERFLOW 14).
int eai_to_bionic(int r) {
    switch (r) {
    case 0: return 0;
    case EAI_BADFLAGS: return 3;
    case EAI_NONAME: return 8;
    case EAI_AGAIN: return 2;
    case EAI_FAIL: return 4;
    case EAI_FAMILY: return 5;
    case EAI_SOCKTYPE: return 10;
    case EAI_SERVICE: return 9;
    case EAI_MEMORY: return 6;
#ifdef EAI_SYSTEM
    case EAI_SYSTEM: return 11;
#endif
#ifdef EAI_OVERFLOW
    case EAI_OVERFLOW: return 14;
#endif
#ifdef EAI_NODATA
    case EAI_NODATA: return 7;
#endif
#ifdef EAI_ADDRFAMILY
    case EAI_ADDRFAMILY: return 1;
#endif
    default: return 4;  // EAI_FAIL
    }
}

HostFn g_getaddrinfo, g_gethostbyname, g_connect;

// The addresses mapped names resolved to (and --server's / the map's literal addresses): the
// connections whose ports are moved. Stored as the sockaddr's address bytes.
std::mutex g_mu;
std::set<std::string> g_mapped_addrs;

std::string addr_key(const sockaddr* sa) {
    if (sa->sa_family == AF_INET) return std::string((const char*)&((const sockaddr_in*)sa)->sin_addr, 4);
    if (sa->sa_family == kGuestAfInet6) {
        auto* a6 = &((const sockaddr_in6*)sa)->sin6_addr;
        if (IN6_IS_ADDR_V4MAPPED(a6)) return std::string((const char*)a6 + 12, 4);
        return std::string((const char*)a6, 16);
    }
    return "";
}
void remember_literal(const std::string& host) {
    in_addr a4;
    in6_addr a6;
    std::lock_guard<std::mutex> lk(g_mu);
    if (inet_pton(AF_INET, host.c_str(), &a4) == 1) g_mapped_addrs.insert(std::string((const char*)&a4, 4));
    else if (inet_pton(AF_INET6, host.c_str(), &a6) == 1) g_mapped_addrs.insert(std::string((const char*)&a6, 16));
}
bool is_mapped(const sockaddr* sa) {
    std::string k = addr_key(sa);
    std::lock_guard<std::mutex> lk(g_mu);
    return !k.empty() && g_mapped_addrs.count(k);
}

void th_getaddrinfo(Cpu& c) {
    const char* node = arg_str(c, 0);
    const char* serv = arg_str(c, 1);
    auto* ghints = (const BionicAddrinfo*)c.x(2);
    std::string target = node ? mapped_address(node) : "";
    if (!target.empty()) {
        LOGI("net", "getaddrinfo(%s, %s) -> %s (mapped)", node, serv ? serv : "", target.c_str());
        struct NodeTag;
        std::string& node_buf = thread_object<std::string, NodeTag>();  // (core/thread_record.h)
        node_buf = target;
        c.set_x(0, (u64)node_buf.c_str());
    }
    // The runtime's thunk copies the hints' fields as they are: hand it glibc's flag bits.
    thread_local BionicAddrinfo t_hints;
    if (ghints) {
        t_hints = *ghints;
        t_hints.ai_flags = flags_to_host(ghints->ai_flags);
        c.set_x(2, (u64)&t_hints);
    }
    u64 out = c.x(3);
    g_getaddrinfo(c);
    int r = (s32)c.x(0);
    if (r == 0 && out) {
        for (auto* a = *(BionicAddrinfo**)out; a; a = (BionicAddrinfo*)a->ai_next) {
            a->ai_flags = flags_to_bionic(a->ai_flags);
            if (!target.empty() && a->ai_addr) {
                std::string k = addr_key((const sockaddr*)a->ai_addr);
                std::lock_guard<std::mutex> lk(g_mu);
                if (!k.empty()) g_mapped_addrs.insert(k);
            }
        }
    }
    if (r != 0) {
        LOGI("net", "getaddrinfo(%s) failed: %s", node ? node : "", gai_strerror(r));
        // The client's URI parser (Aska::Yayoi::URI::Deserialize, given a default port) keeps a
        // URL's ":port" in the host name it resolves, so a URL with a port never resolves, on a
        // phone as here. The service's URLs had none.
        const char* colon = node ? strrchr(node, ':') : nullptr;
        if (colon && colon[1] && strspn(colon + 1, "0123456789") == strlen(colon + 1) && !strchr(colon + 1, ':'))
            LOGW("net", "\"%s\" looks like HOST:PORT from a URL: the client can't use URLs with a port; have the server send "
                        "URLs on a mapped name without one (soa-server --bridge-url https://production-game.so-ana.com/bridge "
                        "--cdn-url http://production-game.so-ana.com)", node);
    }
    c.set_x(0, (u64)(s64)eai_to_bionic(r));
}

void th_gethostbyname(Cpu& c) {
    const char* name = arg_str(c, 0);
    std::string target = name ? mapped_address(name) : "";
    if (!target.empty()) {
        LOGI("net", "gethostbyname(%s) -> %s (mapped)", name, target.c_str());
        struct NameTag;
        std::string& name_buf = thread_object<std::string, NameTag>();  // (core/thread_record.h)
        name_buf = target;
        c.set_x(0, (u64)name_buf.c_str());
    }
    g_gethostbyname(c);
    // struct hostent has the same 64-bit layout in Bionic and glibc.
    auto* he = (hostent*)c.x(0);
    if (he && !target.empty() && he->h_addr_list) {
        std::lock_guard<std::mutex> lk(g_mu);
        for (char** p = he->h_addr_list; *p; p++) g_mapped_addrs.insert(std::string(*p, he->h_length));
    }
}

// connect(fd, addr, len): sockaddr_in / sockaddr_in6 have the same layout in Bionic and glibc.
void th_connect(Cpu& c) {
    auto* sa = (const sockaddr*)c.x(1);
    u32 len = (u32)c.x(2);
    auto& cfg = net_config();
    thread_local sockaddr_storage t_ss;
    if (sa && len <= sizeof(t_ss) && (sa->sa_family == AF_INET || sa->sa_family == kGuestAfInet6) && is_mapped(sa)) {
        u16* port = sa->sa_family == AF_INET ? &((sockaddr_in*)&t_ss)->sin_port : &((sockaddr_in6*)&t_ss)->sin6_port;
        memcpy(&t_ss, sa, len);
        int from = ntohs(*port);
        std::string to_host;
        int to = 0;
        if (from == 443) to = cfg.server_port;
        else if (from == 4001 && cfg.lobby_port) to = cfg.lobby_port, to_host = cfg.lobby_host;
        if (to) {
            if (!to_host.empty() && sa->sa_family == AF_INET) {
                in_addr a;
                if (inet_pton(AF_INET, to_host.c_str(), &a) == 1) ((sockaddr_in*)&t_ss)->sin_addr = a;
                else LOGW("net", "--lobby %s: not an IPv4 address; only the port is moved", to_host.c_str());
            }
            *port = htons((u16)to);
            char buf[INET6_ADDRSTRLEN] = "";
            inet_ntop(sa->sa_family == AF_INET ? AF_INET : AF_INET6, sa->sa_family == AF_INET ? (const void*)&((sockaddr_in*)&t_ss)->sin_addr : (const void*)&((sockaddr_in6*)&t_ss)->sin6_addr, buf, sizeof buf);
            LOGI("net", "connect(fd %d): port %d -> %s:%d (redirected)", (int)c.x(0), from, buf, to);
            c.set_x(1, (u64)&t_ss);
        }
    }
    g_connect(c);
}

}  // namespace

void install_net(Hle& h) {
    g_getaddrinfo = h.override_fn("getaddrinfo", th_getaddrinfo);
    g_gethostbyname = h.override_fn("gethostbyname", th_gethostbyname);
    g_connect = h.override_fn("connect", th_connect);
    if (!g_getaddrinfo || !g_gethostbyname || !g_connect) fatal("platform370: the runtime's socket imports are missing");
    // The configured addresses count as mapped even before a lookup (a numeric host in a URL).
    auto& cfg = net_config();
    remember_literal(cfg.server_host);
    for (auto& [name, addr] : cfg.hosts) remember_literal(addr.empty() ? cfg.server_host : addr);
}

}  // namespace detail
}  // namespace soa::platform370

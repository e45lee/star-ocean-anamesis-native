// The viewer's one platform answer (emulator-viewer/README.md "Network"; docs/client-changes.md
// "Emulator viewer (3.8.0)"), registered through the runtime's extension point
// (hle_add_registrar + Hle::override_fn); the game code is unchanged.
//
// The offline 3.8.0 client still sends one request: the title's NoLoginStart, over raw TCP to
// production-game.so-ana.com:443 (docs/history/libsoa-3.7.0-vs-3.8.0.md 2.1). The service is gone and
// the name no longer resolves, so on a phone today the lookup fails, CPhase_Server's error
// handler sees service_stop_day <= NowTimeTrue() (the clock is frozen there) and ends the phase
// without an error dialog, and the game goes on offline. That is the shipped behaviour, and the
// viewer keeps it -- but deterministically: every name under so-ana.com fails to resolve here
// (EAI_NONAME) without a DNS query, so the client never reaches whoever holds the domain later,
// and never a local soa-server (whose answer mixes a 3.7.0 server player into the offline save:
// README "Network"). Every other lookup goes to the runtime's thunks unchanged.
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <netdb.h>
#endif
#include <strings.h>

#include <cstring>
#include <string>

#include "soaruntime/core/hle.h"
#include "soaruntime/core/log.h"

namespace soa::viewer {
namespace {

constexpr int kBionicEaiNoname = 8;  // Bionic's netdb.h: EAI_NONAME (glibc's is negative)
constexpr const char kDomain[] = "so-ana.com";

HostFn g_getaddrinfo, g_gethostbyname;

// "so-ana.com" or a name under it (case-insensitive, an optional trailing dot).
bool is_service_name(const char* name) {
    if (!name) return false;
    std::string n = name;
    if (!n.empty() && n.back() == '.') n.pop_back();
    size_t d = sizeof kDomain - 1;
    if (n.size() < d || strcasecmp(n.c_str() + n.size() - d, kDomain) != 0) return false;
    return n.size() == d || n[n.size() - d - 1] == '.';
}

void th_getaddrinfo(Cpu& c) {
    const char* node = arg_str(c, 0);
    if (is_service_name(node)) {
        LOGI("net", "getaddrinfo(%s): the service is gone; not found (no DNS query)", node);
        if (c.x(3)) *(u64*)c.x(3) = 0;
        c.set_x(0, kBionicEaiNoname);
        return;
    }
    g_getaddrinfo(c);
}

void th_gethostbyname(Cpu& c) {
    const char* name = arg_str(c, 0);
    if (is_service_name(name)) {
        LOGI("net", "gethostbyname(%s): the service is gone; not found (no DNS query)", name);
        c.set_x(0, 0);
        return;
    }
    g_gethostbyname(c);
}

void install(Hle& h) {
    g_getaddrinfo = h.override_fn("getaddrinfo", th_getaddrinfo);
    g_gethostbyname = h.override_fn("gethostbyname", th_gethostbyname);
    if (!g_getaddrinfo || !g_gethostbyname) fatal("viewer: the runtime's name-lookup imports are missing");
}

const bool registered = hle_add_registrar(install);

}  // namespace
}  // namespace soa::viewer

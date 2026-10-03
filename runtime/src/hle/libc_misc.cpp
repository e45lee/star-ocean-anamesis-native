// Bionic libc: time, sysconf/syscall, dynamic linker, sockets.
#include <arpa/inet.h>
#include <errno.h>
#include <linux/futex.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/socket.h>
#include <sys/syscall.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include <cinttypes>
#include <string>

#include "core/device.h"
#include "core/hle.h"
#include "core/loader.h"
#include "core/log.h"

namespace soa {
namespace {

// ---- time ----
locale_t fixloc(u64 l) {
    static locale_t c = newlocale(LC_ALL_MASK, "C", (locale_t)0);
    return (l == 0 || l == ~0ull) ? c : (locale_t)l;
}
void th_strftime_l(Cpu& c) { ret(c, strftime_l((char*)c.x(0), c.x(1), arg_str(c, 2), (const tm*)c.x(3), fixloc(c.x(4)))); }

// ---- sysconf ----
void th_sysconf(Cpu& c) {
    int n = (int)c.x(0);
    long r;
    switch (n) {
    case 0x0006: r = sysconf(_SC_CLK_TCK); break;
    case 0x000b: r = sysconf(_SC_OPEN_MAX); break;
    case 0x0027:
    case 0x0028: r = 4096; break;
    case 0x004c: r = 16384; break;  // THREAD_STACK_MIN
    // The emulated device's CPU count (device_config().guest_cpus, core/device.h), else the host's.
    case 0x0060: r = device_config().guest_cpus > 0 ? device_config().guest_cpus : sysconf(_SC_NPROCESSORS_CONF); break;
    case 0x0061: r = device_config().guest_cpus > 0 ? device_config().guest_cpus : sysconf(_SC_NPROCESSORS_ONLN); break;
    case 0x0062: r = sysconf(_SC_PHYS_PAGES); break;
    case 0x0063: r = sysconf(_SC_AVPHYS_PAGES); break;
    default:
        LOGW("libc", "sysconf(%#x) unsupported", n);
        r = -1;
        errno = EINVAL;
        break;
    }
    ret(c, (u64)r);
}

// ---- syscall: arm64 numbers -> host ----
void th_syscall(Cpu& c) {
    long nr = (long)c.x(0);
    u64 a1 = c.x(1), a2 = c.x(2), a3 = c.x(3), a4 = c.x(4), a5 = c.x(5), a6 = c.x(6);
    long r;
    switch (nr) {
    case 98: r = syscall(SYS_futex, a1, a2, a3, a4, a5, a6); break;
    case 172: r = getpid(); break;
    case 178: r = gettid(); break;
    case 278: r = syscall(SYS_getrandom, a1, a2, a3); break;
    case 113: r = clock_gettime((clockid_t)a1, (timespec*)a2); break;
    case 123: r = syscall(SYS_sched_getaffinity, a1, a2, a3); break;
    case 122: r = syscall(SYS_sched_setaffinity, a1, a2, a3); break;
    case 168: r = syscall(SYS_getcpu, a1, a2, a3); break;
    case 167: r = 0; break;  // prctl: ignore
    case 131: r = syscall(SYS_tgkill, a1, a2, a3); break;
    default:
        LOGW("libc", "syscall(%ld) unsupported", nr);
        errno = ENOSYS;
        r = -1;
        break;
    }
    ret(c, (u64)r);
}

// ---- dynamic linker ----
constexpr u64 kHandleSelf = 0x1000, kHandleSystem = 0x2000;
thread_local const char* t_dlerror = nullptr;

void th_dlopen(Cpu& c) {
    const char* name = arg_str(c, 0);
    LOGD("dl", "dlopen(%s)", name ? name : "(null)");
    if (!name || strstr(name, "libSOA")) {
        ret(c, kHandleSelf);
        return;
    }
    static const char* known[] = {"libc.so", "libm.so", "libdl.so", "liblog.so", "libandroid.so", "libEGL.so", "libGLESv2.so", "libGLESv3.so", "libOpenSLES.so"};
    for (auto k : known)
        if (strstr(name, k)) {
            ret(c, kHandleSystem);
            return;
        }
    LOGW("dl", "dlopen(%s) -> not available", name);
    t_dlerror = "library not found";
    ret(c, 0);
}
void th_dlsym(Cpu& c) {
    u64 h = c.x(0);
    const char* name = arg_str(c, 1);
    u64 a = 0;
    if (h == kHandleSelf && main_lib()) a = main_lib()->sym(name);
    if (!a) a = Hle::get().lookup(name);
    if (!a && main_lib() && h != kHandleSystem) a = main_lib()->sym(name);
    LOGD("dl", "dlsym(%#" PRIx64 ", %s) = %#" PRIx64, h, name, a);
    if (!a) t_dlerror = "symbol not found";
    ret(c, a);
}
void th_dlclose(Cpu& c) { ret(c, 0); }
void th_dlerror(Cpu& c) {
    ret_ptr(c, t_dlerror);
    t_dlerror = nullptr;
}

struct BionicDlPhdrInfo {
    u64 dlpi_addr;
    u64 dlpi_name;
    u64 dlpi_phdr;
    u16 dlpi_phnum;
    u16 pad[3];
    u64 dlpi_adds, dlpi_subs, dlpi_tls_modid, dlpi_tls_data;
};
void th_dl_iterate_phdr(Cpu& c) {
    // Every loaded image (the game library).
    thread_local BionicDlPhdrInfo info;
    u64 r = 0;
    for (LoadedLib* lib : loaded_libs()) {
        info = {};
        info.dlpi_addr = lib->base;
        info.dlpi_name = (u64)(lib == main_lib() ? "libSOA.so" : "libSOA-other.so");
        info.dlpi_phdr = lib->phdr;
        info.dlpi_phnum = lib->phnum;
        info.dlpi_adds = loaded_libs().size();
        r = guest_call(c.x(0), {(u64)&info, sizeof(info), c.x(1)});
        if ((s32)r != 0) break;
    }
    ret(c, r);
}

// ---- sockets ----
struct BionicAddrinfo {
    s32 ai_flags, ai_family, ai_socktype, ai_protocol;
    u32 ai_addrlen;
    u32 pad;
    u64 ai_canonname, ai_addr, ai_next;
};
void th_getaddrinfo(Cpu& c) {
    const char* node = arg_str(c, 0);
    const char* serv = arg_str(c, 1);
    auto* ghints = (const BionicAddrinfo*)c.x(2);
    addrinfo hints{}, *res = nullptr;
    if (ghints) {
        hints.ai_flags = ghints->ai_flags;
        hints.ai_family = ghints->ai_family;
        hints.ai_socktype = ghints->ai_socktype;
        hints.ai_protocol = ghints->ai_protocol;
    }
    LOGI("net", "getaddrinfo(%s, %s)", node ? node : "", serv ? serv : "");
    int r = getaddrinfo(node, serv, ghints ? &hints : nullptr, &res);
    BionicAddrinfo* head = nullptr;
    BionicAddrinfo** tail = &head;
    for (addrinfo* a = res; a; a = a->ai_next) {
        auto* b = (BionicAddrinfo*)calloc(1, sizeof(BionicAddrinfo) + a->ai_addrlen);
        b->ai_flags = a->ai_flags;
        b->ai_family = a->ai_family;
        b->ai_socktype = a->ai_socktype;
        b->ai_protocol = a->ai_protocol;
        b->ai_addrlen = a->ai_addrlen;
        memcpy(b + 1, a->ai_addr, a->ai_addrlen);
        b->ai_addr = (u64)(b + 1);
        b->ai_canonname = a->ai_canonname ? (u64)strdup(a->ai_canonname) : 0;
        *tail = b;
        tail = (BionicAddrinfo**)&b->ai_next;
    }
    if (res) freeaddrinfo(res);
    *(u64*)c.x(3) = (u64)head;
    ret(c, (u64)(s64)r);
}
void th_freeaddrinfo(Cpu& c) {
    auto* a = (BionicAddrinfo*)c.x(0);
    while (a) {
        auto* n = (BionicAddrinfo*)a->ai_next;
        free((void*)a->ai_canonname);
        free(a);
        a = n;
    }
}

}  // namespace

void register_libc_misc(Hle& h) {
    HLE_WRAP(h, clock_gettime);
    HLE_WRAP(h, gettimeofday);
    HLE_WRAP(h, time);
    HLE_WRAP(h, difftime);
    HLE_WRAP(h, gmtime);
    HLE_WRAP(h, localtime);
    HLE_WRAP(h, localtime_r);
    HLE_WRAP(h, mktime);
    HLE_WRAP(h, strftime);
    h.fn("strftime_l", th_strftime_l);
    h.fn("sysconf", th_sysconf);
    h.fn("syscall", th_syscall);
    h.fn("getrlimit", [](Cpu& c) { ret(c, (u64)(s64)getrlimit((__rlimit_resource_t)c.x(0), (rlimit*)c.x(1))); });

    h.fn("dlopen", th_dlopen);
    h.fn("dlsym", th_dlsym);
    h.fn("dlclose", th_dlclose);
    h.fn("dlerror", th_dlerror);
    h.fn("dl_iterate_phdr", th_dl_iterate_phdr);

    HLE_WRAP(h, socket);
    HLE_WRAP(h, bind);
    HLE_WRAP(h, connect);
    HLE_WRAP(h, listen);
    HLE_WRAP(h, accept);
    HLE_WRAP(h, recv);
    HLE_WRAP(h, recvfrom);
    HLE_WRAP(h, send);
    HLE_WRAP(h, sendto);
    HLE_WRAP(h, setsockopt);
    HLE_WRAP(h, getsockopt);
    HLE_WRAP(h, shutdown);
    HLE_WRAP(h, getpeername);
    HLE_WRAP(h, getsockname);
    HLE_WRAP(h, gethostname);
    HLE_WRAP(h, gethostbyname);
    HLE_WRAP(h, gethostbyaddr);
    HLE_WRAP(h, getnameinfo);
    HLE_WRAP(h, inet_addr);
    h.fn("getaddrinfo", th_getaddrinfo);
    h.fn("freeaddrinfo", th_freeaddrinfo);
}

}  // namespace soa

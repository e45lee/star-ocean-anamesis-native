// Bionic sockets on a Windows host (port/PLAN.md 5b, W): Winsock behind the guest's BSD calls.
// Guest socket descriptors are core/host_fd.h descriptors (read / write / close / poll work on
// them too). What differs from Linux and is translated here:
//   - constants: AF_INET6 (10 / 23), SOL_SOCKET (1 / 0xffff) and its options, the socket type's
//     SOCK_NONBLOCK / SOCK_CLOEXEC bits, MSG_NOSIGNAL / MSG_DONTWAIT, FIONBIO / FIONREAD;
//   - SO_RCVTIMEO / SO_SNDTIMEO take a timeval in the guest, milliseconds in Winsock;
//   - errors come from WSAGetLastError, as errno values (core/linux_errno.h; a non-blocking connect reports
//     EINPROGRESS, Winsock WSAEWOULDBLOCK);
//   - struct hostent has 32-bit h_addrtype / h_length in bionic, 16-bit in Winsock;
//   - fd_set is a 1024-bit mask in bionic (select over WSAPoll).
// Name lookups (getaddrinfo) stay in libc_misc.cpp, with the IPv6 family translated here.
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>

#include <algorithm>
#include <cstring>
#include <mutex>
#include <vector>

#include "core/hle.h"
#include "core/host_fd.h"
#include "core/linux_errno.h"
#include "core/log.h"

namespace soa {

namespace {

constexpr int kGuestAfInet6 = 10;
constexpr int kGuestSockNonblock = 04000, kGuestSockCloexec = 02000000;
constexpr int kGuestMsgDontwait = 0x40, kGuestMsgNosignal = 0x4000;

bool started() {
    static const bool ok = [] {
        WSADATA d;
        return WSAStartup(MAKEWORD(2, 2), &d) == 0;
    }();
    return ok;
}

// errno after a failed Winsock call (as the CRT's constant: core/linux_errno.h); returns -1 for
// the thunk.
s64 fail() {
    errno = host_errno_of_wsa(WSAGetLastError());
    return -1;
}

SOCKET sock(Cpu& c, int i = 0) {
    SOCKET s = (SOCKET)hostfd::socket_of((int)c.x(i));
    if (s == INVALID_SOCKET) WSASetLastError(WSAENOTSOCK);
    return s;
}

// sockaddr: only sa_family differs (AF_INET6). Copies to a host buffer.
int addr_in(const void* guest, int len, sockaddr_storage* out) {
    if (!guest || len <= 0 || len > (int)sizeof *out) return len;
    memcpy(out, guest, len);
    if (out->ss_family == kGuestAfInet6) out->ss_family = AF_INET6;
    return len;
}
void addr_out(void* guest, const sockaddr_storage& host, int len) {
    if (!guest) return;
    memcpy(guest, &host, len);
    if (host.ss_family == AF_INET6) ((sockaddr*)guest)->sa_family = kGuestAfInet6;
}

bool set_nonblocking(SOCKET s, bool on) {
    u_long v = on;
    return ioctlsocket(s, FIONBIO, &v) == 0;
}

void th_socket(Cpu& c) {
    if (!started()) return ret(c, (u64)fail());
    int domain = (int)c.x(0), type = (int)c.x(1), proto = (int)c.x(2);
    bool nonblock = type & kGuestSockNonblock;
    type &= ~(kGuestSockNonblock | kGuestSockCloexec);
    if (domain == kGuestAfInet6) domain = AF_INET6;
    SOCKET s = WSASocketW(domain, type, proto, nullptr, 0, WSA_FLAG_OVERLAPPED | WSA_FLAG_NO_HANDLE_INHERIT);
    if (s == INVALID_SOCKET) return ret(c, (u64)fail());
    if (nonblock) set_nonblocking(s, true);
    ret(c, (u64)(s64)hostfd::adopt_socket(s));
}
void th_bind(Cpu& c) {
    sockaddr_storage a;
    int len = addr_in((const void*)c.x(1), (int)c.x(2), &a);
    SOCKET s = sock(c);
    ret(c, (u64)(s == INVALID_SOCKET || bind(s, (sockaddr*)&a, len) != 0 ? fail() : 0));
}
void th_connect(Cpu& c) {
    sockaddr_storage a;
    int len = addr_in((const void*)c.x(1), (int)c.x(2), &a);
    SOCKET s = sock(c);
    if (s == INVALID_SOCKET) return ret(c, (u64)fail());
    if (connect(s, (sockaddr*)&a, len) == 0) return ret(c, 0);
    s64 r = fail();
    if (errno == EAGAIN) errno = EINPROGRESS;  // a non-blocking connect in progress: EINPROGRESS, as on Linux
    ret(c, (u64)r);
}
void th_listen(Cpu& c) {
    SOCKET s = sock(c);
    ret(c, (u64)(s == INVALID_SOCKET || listen(s, (int)c.x(1)) != 0 ? fail() : 0));
}
void th_accept(Cpu& c) {
    SOCKET s = sock(c);
    if (s == INVALID_SOCKET) return ret(c, (u64)fail());
    sockaddr_storage a;
    int len = sizeof a;
    SOCKET n = accept(s, (sockaddr*)&a, &len);
    if (n == INVALID_SOCKET) return ret(c, (u64)fail());
    if (c.x(1) && c.x(2)) {
        addr_out((void*)c.x(1), a, std::min(len, *(int*)c.x(2)));
        *(u32*)c.x(2) = (u32)len;
    }
    ret(c, (u64)(s64)hostfd::adopt_socket(n));
}
int msg_flags(SOCKET s, int f, bool* restore_blocking) {
    *restore_blocking = false;
    if (f & kGuestMsgDontwait) *restore_blocking = set_nonblocking(s, true);  // (a blocking socket, for this call)
    return f & ~(kGuestMsgDontwait | kGuestMsgNosignal);
}
void th_recvfrom(Cpu& c) {
    SOCKET s = sock(c);
    if (s == INVALID_SOCKET) return ret(c, (u64)fail());
    bool restore;
    int flags = msg_flags(s, (int)c.x(3), &restore);
    sockaddr_storage a;
    int len = sizeof a;
    bool want_addr = c.x(4) && c.x(5);
    int r = recvfrom(s, (char*)c.x(1), (int)std::min<u64>(c.x(2), 0x7fffffff), flags, want_addr ? (sockaddr*)&a : nullptr, want_addr ? &len : nullptr);
    s64 out = r < 0 ? fail() : r;
    if (restore) set_nonblocking(s, false);
    if (r >= 0 && want_addr) {
        addr_out((void*)c.x(4), a, std::min(len, *(int*)c.x(5)));
        *(u32*)c.x(5) = (u32)len;
    }
    ret(c, (u64)out);
}
void th_recv(Cpu& c) {
    c.set_x(4, 0);
    c.set_x(5, 0);
    th_recvfrom(c);
}
void th_sendto(Cpu& c) {
    SOCKET s = sock(c);
    if (s == INVALID_SOCKET) return ret(c, (u64)fail());
    bool restore;
    int flags = msg_flags(s, (int)c.x(3), &restore);
    sockaddr_storage a;
    int len = c.x(4) ? addr_in((const void*)c.x(4), (int)c.x(5), &a) : 0;
    int r = sendto(s, (const char*)c.x(1), (int)std::min<u64>(c.x(2), 0x7fffffff), flags, len ? (sockaddr*)&a : nullptr, len);
    s64 out = r < 0 ? fail() : r;
    if (restore) set_nonblocking(s, false);
    ret(c, (u64)out);
}
void th_send(Cpu& c) {
    c.set_x(4, 0);
    c.set_x(5, 0);
    th_sendto(c);
}

// Socket options: (level, name) Linux -> Winsock. TCP (6) and IP options keep their numbers.
bool sockopt_to_host(int& level, int& name) {
    if (level != 1) return true;  // SOL_SOCKET
    level = SOL_SOCKET;
    switch (name) {
    case 2: name = SO_REUSEADDR; return true;
    case 4: name = SO_ERROR; return true;
    case 6: name = SO_BROADCAST; return true;
    case 7: name = SO_SNDBUF; return true;
    case 8: name = SO_RCVBUF; return true;
    case 9: name = SO_KEEPALIVE; return true;
    case 13: name = SO_LINGER; return true;
    case 20: name = SO_RCVTIMEO; return true;
    case 21: name = SO_SNDTIMEO; return true;
    case 3: name = SO_TYPE; return true;
    default: return false;
    }
}
void th_setsockopt(Cpu& c) {
    SOCKET s = sock(c);
    if (s == INVALID_SOCKET) return ret(c, (u64)fail());
    int level = (int)c.x(1), name = (int)c.x(2), len = (int)c.x(4);
    const void* val = (const void*)c.x(3);
    if (!sockopt_to_host(level, name)) {
        LOGD("net", "setsockopt(level 1, %d): no Winsock counterpart, ignored", (int)c.x(2));
        return ret(c, 0);
    }
    DWORD ms;
    if (level == SOL_SOCKET && (name == SO_RCVTIMEO || name == SO_SNDTIMEO) && len >= 16) {  // timeval -> ms
        const s64* tv = (const s64*)val;
        ms = (DWORD)(tv[0] * 1000 + tv[1] / 1000);
        val = &ms;
        len = sizeof ms;
    }
    ret(c, (u64)(setsockopt(s, level, name, (const char*)val, len) != 0 ? fail() : 0));
}
void th_getsockopt(Cpu& c) {
    SOCKET s = sock(c);
    if (s == INVALID_SOCKET) return ret(c, (u64)fail());
    int level = (int)c.x(1), name = (int)c.x(2);
    if (!sockopt_to_host(level, name)) {
        errno = ENOPROTOOPT;
        return ret(c, (u64)-1);
    }
    char buf[64] = {};
    int len = sizeof buf;
    if (getsockopt(s, level, name, buf, &len) != 0) return ret(c, (u64)fail());
    if (level == SOL_SOCKET && name == SO_ERROR) *(int*)buf = *(int*)buf ? linux_errno(host_errno_of_wsa(*(int*)buf)) : 0;
    int cap = c.x(4) ? *(int*)c.x(4) : 0;
    memcpy((void*)c.x(3), buf, std::min(cap, len));
    if (c.x(4)) *(u32*)c.x(4) = (u32)len;
    ret(c, 0);
}
void th_shutdown(Cpu& c) {
    SOCKET s = sock(c);
    ret(c, (u64)(s == INVALID_SOCKET || shutdown(s, (int)c.x(1)) != 0 ? fail() : 0));
}
template <int (*F)(SOCKET, sockaddr*, int*)>
void name_call(Cpu& c) {
    SOCKET s = sock(c);
    if (s == INVALID_SOCKET) return ret(c, (u64)fail());
    sockaddr_storage a;
    int len = sizeof a;
    if (F(s, (sockaddr*)&a, &len) != 0) return ret(c, (u64)fail());
    addr_out((void*)c.x(1), a, std::min(len, *(int*)c.x(2)));
    *(u32*)c.x(2) = (u32)len;
    ret(c, 0);
}
int WSAAPI wrap_getpeername(SOCKET s, sockaddr* a, int* l) { return getpeername(s, a, l); }
int WSAAPI wrap_getsockname(SOCKET s, sockaddr* a, int* l) { return getsockname(s, a, l); }
int wrap_peer(SOCKET s, sockaddr* a, int* l) { return wrap_getpeername(s, a, l); }
int wrap_name(SOCKET s, sockaddr* a, int* l) { return wrap_getsockname(s, a, l); }

void th_gethostname(Cpu& c) {
    started();
    ret(c, (u64)(gethostname((char*)c.x(0), (int)c.x(1)) != 0 ? fail() : 0));
}
// bionic's struct hostent: h_addrtype and h_length are ints.
struct BionicHostent {
    u64 h_name, h_aliases;
    s32 h_addrtype, h_length;
    u64 h_addr_list;
};
void* to_bionic(const hostent* h) {
    static thread_local BionicHostent b;
    if (!h) return nullptr;
    b.h_name = (u64)h->h_name;
    b.h_aliases = (u64)h->h_aliases;
    b.h_addrtype = h->h_addrtype == AF_INET6 ? kGuestAfInet6 : h->h_addrtype;
    b.h_length = h->h_length;
    b.h_addr_list = (u64)h->h_addr_list;
    return &b;
}
void th_gethostbyname(Cpu& c) {
    started();
    ret_ptr(c, to_bionic(gethostbyname(arg_str(c, 0))));
}
void th_gethostbyaddr(Cpu& c) {
    started();
    int type = (int)c.x(2) == kGuestAfInet6 ? AF_INET6 : (int)c.x(2);
    ret_ptr(c, to_bionic(gethostbyaddr((const char*)c.x(0), (int)c.x(1), type)));
}
void th_getnameinfo(Cpu& c) {
    started();
    sockaddr_storage a;
    int len = addr_in((const void*)c.x(0), (int)c.x(1), &a);
    ret(c, (u64)(s64)getnameinfo((sockaddr*)&a, len, (char*)c.x(2), (DWORD)c.x(3), (char*)c.x(4), (DWORD)c.x(5), (int)c.x(6)));
}
void th_inet_addr(Cpu& c) { ret(c, (u64)inet_addr(arg_str(c, 0))); }

// select over bionic's fd_set (a 1024-bit mask) with hostfd::poll.
void th_select(Cpu& c) {
    int nfds = (int)c.x(0);
    u64* sets[3] = {(u64*)c.x(1), (u64*)c.x(2), (u64*)c.x(3)};
    const s64* tv = (const s64*)c.x(4);
    std::vector<hostfd::PollFd> pf;
    auto isset = [](const u64* s, int fd) { return s && (s[fd / 64] >> (fd % 64) & 1); };
    for (int fd = 0; fd < nfds; fd++) {
        short ev = (isset(sets[0], fd) ? hostfd::kIn : 0) | (isset(sets[1], fd) ? hostfd::kOut : 0) | (isset(sets[2], fd) ? hostfd::kErr : 0);
        if (ev) pf.push_back({fd, ev, 0});
    }
    int timeout = tv ? (int)(tv[0] * 1000 + tv[1] / 1000) : -1;
    int r = hostfd::poll(pf.data(), pf.size(), timeout);
    for (int k = 0; k < 3; k++)
        if (sets[k])
            for (auto& p : pf) sets[k][p.fd / 64] &= ~(1ull << (p.fd % 64));
    int n = 0;
    for (auto& p : pf) {
        if (sets[0] && (p.revents & (hostfd::kIn | hostfd::kHup))) sets[0][p.fd / 64] |= 1ull << (p.fd % 64), n++;
        if (sets[1] && (p.revents & hostfd::kOut)) sets[1][p.fd / 64] |= 1ull << (p.fd % 64), n++;
        if (sets[2] && (p.revents & hostfd::kErr)) sets[2][p.fd / 64] |= 1ull << (p.fd % 64), n++;
    }
    ret(c, (u64)(s64)(r < 0 ? -1 : n));
}

// ioctl: FIONBIO (0x5421) and FIONREAD (0x541b) on sockets.
void th_ioctl(Cpu& c) {
    u32 req = (u32)c.x(1);
    SOCKET s = sock(c);
    if (s == INVALID_SOCKET) {
        errno = ENOTTY;
        return ret(c, (u64)-1);
    }
    if (req == 0x5421) return ret(c, (u64)(set_nonblocking(s, *(int*)c.x(2) != 0) ? 0 : fail()));
    if (req == 0x541b) {
        u_long n = 0;
        if (ioctlsocket(s, FIONREAD, &n) != 0) return ret(c, (u64)fail());
        *(int*)c.x(2) = (int)n;
        return ret(c, 0);
    }
    errno = ENOTTY;
    ret(c, (u64)-1);
}

// fcntl on a socket: F_GETFL (3) / F_SETFL (4) with O_NONBLOCK (04000); F_GETFD / F_SETFD: 0.
HostFn g_fcntl_files;
std::mutex g_nb_mu;
std::vector<int> g_nonblocking;  // sockets set non-blocking through fcntl (Winsock can't be asked)
void th_fcntl(Cpu& c) {
    SOCKET s = (SOCKET)hostfd::socket_of((int)c.x(0));
    if (s == INVALID_SOCKET) return g_fcntl_files(c);
    int cmd = (int)c.x(1), fd = (int)c.x(0);
    std::lock_guard lk(g_nb_mu);
    bool nb = std::find(g_nonblocking.begin(), g_nonblocking.end(), fd) != g_nonblocking.end();
    if (cmd == 3) return ret(c, 2 | (nb ? 04000 : 0));
    if (cmd == 4) {
        bool want = c.x(2) & 04000;
        if (!set_nonblocking(s, want)) return ret(c, (u64)fail());
        if (want && !nb) g_nonblocking.push_back(fd);
        if (!want && nb) g_nonblocking.erase(std::find(g_nonblocking.begin(), g_nonblocking.end(), fd));
        return ret(c, 0);
    }
    ret(c, 0);
}

}  // namespace

void register_net_win32(Hle& h) {
    h.fn("socket", th_socket);
    h.fn("bind", th_bind);
    h.fn("connect", th_connect);
    h.fn("listen", th_listen);
    h.fn("accept", th_accept);
    h.fn("recv", th_recv);
    h.fn("recvfrom", th_recvfrom);
    h.fn("send", th_send);
    h.fn("sendto", th_sendto);
    h.fn("setsockopt", th_setsockopt);
    h.fn("getsockopt", th_getsockopt);
    h.fn("shutdown", th_shutdown);
    h.fn("getpeername", name_call<wrap_peer>);
    h.fn("getsockname", name_call<wrap_name>);
    h.fn("gethostname", th_gethostname);
    h.fn("gethostbyname", th_gethostbyname);
    h.fn("gethostbyaddr", th_gethostbyaddr);
    h.fn("getnameinfo", th_getnameinfo);
    h.fn("inet_addr", th_inet_addr);
    h.fn("select", th_select);
    h.fn("ioctl", th_ioctl);
    g_fcntl_files = h.host_fn("fcntl");
    if (g_fcntl_files) h.fn("fcntl", th_fcntl);
}

void net_win32_startup() { started(); }

}  // namespace soa
#endif

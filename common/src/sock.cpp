// soa/sock.h: BSD sockets on Linux, Winsock on Windows.
#include "soa/sock.h"

#include <cerrno>
#include <cstring>
#include <vector>

#ifndef _WIN32
#include <fcntl.h>
#include <unistd.h>
#endif

namespace soa::sock {

bool split_host_port(const std::string& s, std::string* host, std::string* port) {
    host->clear();
    port->clear();
    if (!s.empty() && s[0] == '[') {
        size_t e = s.find(']');
        if (e == std::string::npos) return false;
        *host = s.substr(1, e - 1);
        if (e + 1 == s.size()) return true;
        if (s[e + 1] != ':') return false;
        *port = s.substr(e + 2);
        return true;
    }
    size_t c = s.find(':');
    if (c == std::string::npos || s.find(':', c + 1) != std::string::npos) {
        *host = s;  // no port, or a bare IPv6 address
        return true;
    }
    *host = s.substr(0, c);
    *port = s.substr(c + 1);
    return true;
}

std::string join_host_port(const std::string& host, int port) {
    return (host.find(':') != std::string::npos ? "[" + host + "]" : host) + ":" + std::to_string(port);
}

#ifdef _WIN32

namespace {
bool started() {
    static const bool ok = [] {
        WSADATA d;
        return WSAStartup(MAKEWORD(2, 2), &d) == 0;
    }();
    return ok;
}
}  // namespace

bool startup() { return started(); }

bool set_nonblocking(int fd, bool on) {
    u_long v = on;
    return ioctlsocket((SOCKET)fd, FIONBIO, &v) == 0;
}

int tcp_socket(bool nonblocking, int family) {
    if (!started()) return -1;
    // WSA_FLAG_NO_HANDLE_INHERIT: close-on-exec
    SOCKET s = WSASocketW(family, SOCK_STREAM, IPPROTO_TCP, nullptr, 0, WSA_FLAG_OVERLAPPED | WSA_FLAG_NO_HANDLE_INHERIT);
    if (s == INVALID_SOCKET) return -1;
    if (nonblocking && !set_nonblocking((int)s, true)) {
        closesocket(s);
        return -1;
    }
    return (int)s;
}

int accept_nonblocking(int listen_fd) {
    SOCKET s = ::accept((SOCKET)listen_fd, nullptr, nullptr);
    if (s == INVALID_SOCKET) return -1;
    set_nonblocking((int)s, true);
    set_nodelay((int)s);
    return (int)s;
}

int accept(int listen_fd) {
    SOCKET s = ::accept((SOCKET)listen_fd, nullptr, nullptr);
    if (s == INVALID_SOCKET) return -1;
    set_nodelay((int)s);
    return (int)s;
}

int close(int fd) { return closesocket((SOCKET)fd); }

void set_timeouts(int fd, int seconds) {
    DWORD ms = (DWORD)seconds * 1000;
    setsockopt((SOCKET)fd, SOL_SOCKET, SO_RCVTIMEO, (const char*)&ms, sizeof ms);
    setsockopt((SOCKET)fd, SOL_SOCKET, SO_SNDTIMEO, (const char*)&ms, sizeof ms);
}

void set_nodelay(int fd) {
    int one = 1;
    setsockopt((SOCKET)fd, IPPROTO_TCP, TCP_NODELAY, (const char*)&one, sizeof one);
}

void set_reuse_addr(int) {}

ssize_t recv(int fd, void* buf, size_t n) { return ::recv((SOCKET)fd, (char*)buf, (int)(n > 0x7fffffff ? 0x7fffffff : n), 0); }
ssize_t send(int fd, const void* buf, size_t n) { return ::send((SOCKET)fd, (const char*)buf, (int)(n > 0x7fffffff ? 0x7fffffff : n), 0); }

bool would_block() { return WSAGetLastError() == WSAEWOULDBLOCK; }
bool connect_in_progress() { return WSAGetLastError() == WSAEWOULDBLOCK; }
bool interrupted() { return WSAGetLastError() == WSAEINTR; }

std::string last_error() {
    int e = WSAGetLastError();
    char buf[256] = {0};
    if (!FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, (DWORD)e, 0, buf, sizeof buf, nullptr))
        return "Winsock error " + std::to_string(e);
    std::string s = buf;
    while (!s.empty() && (s.back() == '\n' || s.back() == '\r' || s.back() == ' ')) s.pop_back();
    return s;
}

int poll(PollFd* fds, size_t n, int timeout_ms) {
    std::vector<WSAPOLLFD> w(n);
    for (size_t i = 0; i < n; i++) w[i] = {(SOCKET)fds[i].fd, fds[i].events, 0};
    int r = WSAPoll(w.data(), (ULONG)n, timeout_ms);
    for (size_t i = 0; i < n; i++) fds[i].revents = r > 0 ? w[i].revents : 0;
    return r;
}

#else

bool startup() { return true; }

int tcp_socket(bool nonblocking, int family) { return ::socket(family, SOCK_STREAM | SOCK_CLOEXEC | (nonblocking ? SOCK_NONBLOCK : 0), 0); }

bool set_nonblocking(int fd, bool on) {
    int f = fcntl(fd, F_GETFL);
    return f >= 0 && fcntl(fd, F_SETFL, on ? f | O_NONBLOCK : f & ~O_NONBLOCK) == 0;
}

int accept_nonblocking(int listen_fd) {
    int fd = accept4(listen_fd, nullptr, nullptr, SOCK_NONBLOCK | SOCK_CLOEXEC);
    if (fd >= 0) set_nodelay(fd);
    return fd;
}

int accept(int listen_fd) {
    int fd = accept4(listen_fd, nullptr, nullptr, SOCK_CLOEXEC);
    if (fd >= 0) set_nodelay(fd);
    return fd;
}

int close(int fd) { return ::close(fd); }

void set_timeouts(int fd, int seconds) {
    timeval tv = {seconds, 0};
    setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
    setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof tv);
}

void set_nodelay(int fd) {
    int one = 1;
    setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &one, sizeof one);
}

void set_reuse_addr(int fd) {
    int one = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof one);
}

ssize_t recv(int fd, void* buf, size_t n) { return ::recv(fd, buf, n, 0); }
ssize_t send(int fd, const void* buf, size_t n) { return ::send(fd, buf, n, MSG_NOSIGNAL); }

bool would_block() { return errno == EAGAIN || errno == EWOULDBLOCK; }
bool connect_in_progress() { return errno == EINPROGRESS; }
bool interrupted() { return errno == EINTR; }
std::string last_error() { return strerror(errno); }

int poll(PollFd* fds, size_t n, int timeout_ms) {
    static_assert(sizeof(PollFd) == sizeof(pollfd) && offsetof(PollFd, revents) == offsetof(pollfd, revents));
    return ::poll((pollfd*)fds, (nfds_t)n, timeout_ms);
}

#endif

}  // namespace soa::sock

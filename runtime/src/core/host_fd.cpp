// host_fd.h: kernel descriptors on Linux, in-process emulation on Windows.
#include "core/host_fd.h"

#include <algorithm>
#include <cerrno>
#include <cstdint>
#include <cstring>

#ifdef _WIN32
#include <io.h>
#include <winsock2.h>

#include <chrono>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <unordered_map>
#include <vector>
#else
#include <fcntl.h>
#include <poll.h>
#include <sys/eventfd.h>
#include <unistd.h>
#endif

namespace soa::hostfd {

#ifndef _WIN32

int make_event() { return eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC); }
void event_signal(int fd) {
    uint64_t one = 1;
    (void)!::write(fd, &one, 8);
}
void event_drain(int fd) {
    uint64_t v;
    (void)!::read(fd, &v, 8);
}
int make_pipe(int fds[2]) { return pipe2(fds, O_CLOEXEC); }
bool emulated(int) { return false; }
ssize_t read(int fd, void* buf, size_t n) { return ::read(fd, buf, n); }
ssize_t write(int fd, const void* buf, size_t n) { return ::write(fd, buf, n); }
int close(int fd) { return ::close(fd); }
int poll(PollFd* fds, size_t n, int timeout_ms) {
    static_assert(sizeof(PollFd) == sizeof(pollfd) && kIn == POLLIN && kOut == POLLOUT && kErr == POLLERR && kHup == POLLHUP);
    return ::poll((pollfd*)fds, (nfds_t)n, timeout_ms);
}

#else

namespace {

// The guest's descriptor table: guest numbers are small (lowest free first, as POSIX: bionic's
// fd_set is a 1024-bit mask) and map to a CRT descriptor (a file), a Winsock socket, or an
// in-process channel (a pipe end or an event counter). Every channel state change notifies g_cv,
// which poll() and blocking reads wait on (one condition variable: the descriptors are few).
struct Channel {
    bool event = false;
    uint64_t count = 0;     // event
    std::deque<char> data;  // pipe
    bool reader_open = true, writer_open = true;
};
struct Fd {
    enum Kind { kCrt, kSocket, kChannel } kind = kCrt;
    int crt = -1;
    SOCKET sock = INVALID_SOCKET;
    std::shared_ptr<Channel> ch;
    bool write_end = false;
};

std::mutex g_mu;
std::condition_variable g_cv;
std::unordered_map<int, Fd> g_fds;

void init_std() {  // 0, 1, 2: the CRT's
    if (g_fds.empty())
        for (int i = 0; i < 3; i++) g_fds[i] = Fd{Fd::kCrt, i};
}
Fd* find(int fd) {
    init_std();
    auto it = g_fds.find(fd);
    return it == g_fds.end() ? nullptr : &it->second;
}
int add(Fd f) {
    init_std();
    int fd = 3;
    while (g_fds.count(fd)) fd++;
    g_fds[fd] = std::move(f);
    return fd;
}
short ready(const Fd& f, short events) {
    if (f.kind == Fd::kCrt) return events & (kIn | kOut);  // a file: always ready
    if (f.kind == Fd::kSocket) return 0;                   // WSAPoll (poll below)
    const Channel& c = *f.ch;
    short r = 0;
    if (c.event) {
        if ((events & kIn) && c.count) r |= kIn;
        if (events & kOut) r |= kOut;
        return r;
    }
    if (!f.write_end) {
        if ((events & kIn) && !c.data.empty()) r |= kIn;
        if (!c.writer_open) r |= kHup;
    } else {
        if (!c.reader_open) r |= kErr;
        else if (events & kOut) r |= kOut;
    }
    return r;
}
int wsa_errno() {
    switch (WSAGetLastError()) {
    case WSAEWOULDBLOCK: return EAGAIN;
    case WSAEINTR: return EINTR;
    case WSAECONNRESET: return ECONNRESET;
    case WSAENOTCONN: return ENOTCONN;
    case WSAETIMEDOUT: return ETIMEDOUT;
    case WSAECONNABORTED: return ECONNABORTED;
    default: return EIO;
    }
}

}  // namespace

int make_event() {
    std::lock_guard lk(g_mu);
    auto ch = std::make_shared<Channel>();
    ch->event = true;
    Fd f;
    f.kind = Fd::kChannel;
    f.ch = ch;
    return add(f);
}
void event_signal(int fd) {
    std::lock_guard lk(g_mu);
    if (Fd* f = find(fd); f && f->ch) f->ch->count++;
    g_cv.notify_all();
}
void event_drain(int fd) {
    std::lock_guard lk(g_mu);
    if (Fd* f = find(fd); f && f->ch) f->ch->count = 0;
}
int make_pipe(int fds[2]) {
    std::lock_guard lk(g_mu);
    auto ch = std::make_shared<Channel>();
    Fd r, w;
    r.kind = w.kind = Fd::kChannel;
    r.ch = w.ch = ch;
    w.write_end = true;
    fds[0] = add(r);
    fds[1] = add(w);
    return 0;
}
bool emulated(int fd) {
    std::lock_guard lk(g_mu);
    Fd* f = find(fd);
    return f && f->kind == Fd::kChannel;
}
int adopt_file(int crt) {
    if (crt < 0) return -1;
    std::lock_guard lk(g_mu);
    Fd f;
    f.crt = crt;
    return add(f);
}
int crt_of(int fd) {
    std::lock_guard lk(g_mu);
    Fd* f = find(fd);
    return f && f->kind == Fd::kCrt ? f->crt : -1;
}
int adopt_socket(uintptr_t sock) {
    std::lock_guard lk(g_mu);
    Fd f;
    f.kind = Fd::kSocket;
    f.sock = (SOCKET)sock;
    return add(f);
}
uintptr_t socket_of(int fd) {
    std::lock_guard lk(g_mu);
    Fd* f = find(fd);
    return f && f->kind == Fd::kSocket ? f->sock : INVALID_SOCKET;
}

ssize_t read(int fd, void* buf, size_t n) {
    std::unique_lock lk(g_mu);
    Fd* f = find(fd);
    if (!f) return errno = EBADF, -1;
    if (f->kind == Fd::kCrt) {
        int crt = f->crt;
        lk.unlock();
        return ::_read(crt, buf, (unsigned)std::min<size_t>(n, 0x7fffffff));
    }
    if (f->kind == Fd::kSocket) {
        SOCKET s = f->sock;
        lk.unlock();
        int r = ::recv(s, (char*)buf, (int)std::min<size_t>(n, 0x7fffffff), 0);
        return r < 0 ? (errno = wsa_errno(), -1) : r;
    }
    if (f->write_end) return errno = EBADF, -1;
    std::shared_ptr<Channel> c = f->ch;
    if (c->event) {  // eventfd: 8 bytes, the count, then 0; EAGAIN when 0 (non-blocking)
        if (n < 8) return errno = EINVAL, -1;
        if (!c->count) return errno = EAGAIN, -1;
        memcpy(buf, &c->count, 8);
        c->count = 0;
        return 8;
    }
    g_cv.wait(lk, [&] { return !c->data.empty() || !c->writer_open; });  // a pipe read blocks
    size_t k = 0;
    while (k < n && !c->data.empty()) {
        ((char*)buf)[k++] = c->data.front();
        c->data.pop_front();
    }
    return (ssize_t)k;
}

ssize_t write(int fd, const void* buf, size_t n) {
    std::unique_lock lk(g_mu);
    Fd* f = find(fd);
    if (!f) return errno = EBADF, -1;
    if (f->kind == Fd::kCrt) {
        int crt = f->crt;
        lk.unlock();
        return ::_write(crt, buf, (unsigned)std::min<size_t>(n, 0x7fffffff));
    }
    if (f->kind == Fd::kSocket) {
        SOCKET s = f->sock;
        lk.unlock();
        int r = ::send(s, (const char*)buf, (int)std::min<size_t>(n, 0x7fffffff), 0);
        return r < 0 ? (errno = wsa_errno(), -1) : r;
    }
    Channel& c = *f->ch;
    if (c.event) {
        if (n < 8) return errno = EINVAL, -1;
        uint64_t v;
        memcpy(&v, buf, 8);
        c.count += v;
    } else {
        if (!f->write_end) return errno = EBADF, -1;
        if (!c.reader_open) return errno = EPIPE, -1;
        c.data.insert(c.data.end(), (const char*)buf, (const char*)buf + n);
    }
    g_cv.notify_all();
    return (ssize_t)n;
}

int close(int fd) {
    std::lock_guard lk(g_mu);
    Fd* f = find(fd);
    if (!f) return errno = EBADF, -1;
    int r = 0;
    if (f->kind == Fd::kCrt) r = fd > 2 ? ::_close(f->crt) : 0;  // (the host keeps its own stdio)
    else if (f->kind == Fd::kSocket) closesocket(f->sock);
    else if (!f->ch->event) (f->write_end ? f->ch->writer_open : f->ch->reader_open) = false;
    if (fd > 2) g_fds.erase(fd);
    g_cv.notify_all();
    return r;
}

int poll(PollFd* fds, size_t n, int timeout_ms) {
    std::unique_lock lk(g_mu);
    std::vector<WSAPOLLFD> socks;  // the sockets in the set, and where they are in fds
    std::vector<size_t> sock_at;
    for (size_t i = 0; i < n; i++)
        if (Fd* f = fds[i].fd >= 0 ? find(fds[i].fd) : nullptr; f && f->kind == Fd::kSocket) {
            short ev = (short)(((fds[i].events & kIn) ? POLLRDNORM : 0) | ((fds[i].events & kOut) ? POLLWRNORM : 0));
            socks.push_back({f->sock, ev, 0});
            sock_at.push_back(i);
        }
    auto scan = [&](int sock_wait_ms) {
        int k = 0;
        if (!socks.empty()) {
            for (auto& w : socks) w.revents = 0;
            lk.unlock();
            WSAPoll(socks.data(), (ULONG)socks.size(), sock_wait_ms);
            lk.lock();
        }
        for (size_t i = 0, si = 0; i < n; i++) {
            fds[i].revents = 0;
            if (fds[i].fd < 0) continue;
            if (si < sock_at.size() && sock_at[si] == i) {
                short r = socks[si++].revents;
                fds[i].revents = (short)(((r & POLLRDNORM) ? kIn : 0) | ((r & POLLWRNORM) ? kOut : 0) | ((r & POLLERR) ? kErr : 0) |
                                         ((r & POLLHUP) ? kHup | (fds[i].events & kIn) : 0));
            } else if (Fd* f = find(fds[i].fd)) {
                fds[i].revents = ready(*f, fds[i].events);
            } else {
                fds[i].revents = 0x020;  // POLLNVAL
            }
            k += fds[i].revents != 0;
        }
        return k;
    };
    int k = scan(0);
    if (k || timeout_ms == 0) return k;
    auto until = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms);
    for (;;) {
        // Sockets can't wake the condition variable: with any in the set, poll both in slices.
        if (!socks.empty()) {
            if ((k = scan(10))) return k;
            if (timeout_ms >= 0 && std::chrono::steady_clock::now() >= until) return 0;
            continue;
        }
        if (timeout_ms < 0) g_cv.wait(lk);
        else if (g_cv.wait_until(lk, until) == std::cv_status::timeout) return scan(0);
        if ((k = scan(0))) return k;
    }
}

#endif

}  // namespace soa::hostfd

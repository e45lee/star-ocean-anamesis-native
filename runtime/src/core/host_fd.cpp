// host_fd.h: kernel descriptors on Linux, in-process emulation on Windows.
#include "core/host_fd.h"

#include <cerrno>
#include <cstdint>
#include <cstring>

#ifdef _WIN32
#include <io.h>

#include <chrono>
#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <unordered_map>
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

// A pipe's shared buffer, or an event counter. Every state change notifies g_cv, which poll() and
// blocking reads wait on (one condition variable: the descriptors are few and quiet).
struct Channel {
    bool event = false;
    uint64_t count = 0;        // event
    std::deque<char> data;     // pipe
    bool reader_open = true, writer_open = true;
};
struct Fd {
    std::shared_ptr<Channel> ch;
    bool write_end = false;
};

std::mutex g_mu;
std::condition_variable g_cv;
std::unordered_map<int, Fd> g_fds;
int g_next = kFirstEmulated;

Fd* find(int fd) {
    auto it = g_fds.find(fd);
    return it == g_fds.end() ? nullptr : &it->second;
}
int add(Fd f) {
    int fd = g_next++;
    g_fds[fd] = std::move(f);
    return fd;
}
short ready(const Fd& f, short events) {
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

}  // namespace

int make_event() {
    std::lock_guard lk(g_mu);
    auto ch = std::make_shared<Channel>();
    ch->event = true;
    return add({ch, false});
}
void event_signal(int fd) {
    std::lock_guard lk(g_mu);
    if (Fd* f = find(fd)) f->ch->count++;
    g_cv.notify_all();
}
void event_drain(int fd) {
    std::lock_guard lk(g_mu);
    if (Fd* f = find(fd)) f->ch->count = 0;
}
int make_pipe(int fds[2]) {
    std::lock_guard lk(g_mu);
    auto ch = std::make_shared<Channel>();
    fds[0] = add({ch, false});
    fds[1] = add({ch, true});
    return 0;
}
bool emulated(int fd) {
    if (fd < kFirstEmulated) return false;
    std::lock_guard lk(g_mu);
    return find(fd) != nullptr;
}

ssize_t read(int fd, void* buf, size_t n) {
    if (fd < kFirstEmulated) return ::_read(fd, buf, (unsigned)n);
    std::unique_lock lk(g_mu);
    Fd* f = find(fd);
    if (!f || f->write_end) return errno = EBADF, -1;
    Channel& c = *f->ch;
    if (c.event) {  // eventfd: 8 bytes, the count, then 0; EAGAIN when 0 (non-blocking)
        if (n < 8) return errno = EINVAL, -1;
        if (!c.count) return errno = EAGAIN, -1;
        memcpy(buf, &c.count, 8);
        c.count = 0;
        return 8;
    }
    std::shared_ptr<Channel> keep = f->ch;  // a pipe read blocks until data or the writer closes
    g_cv.wait(lk, [&] { return !keep->data.empty() || !keep->writer_open; });
    size_t k = 0;
    while (k < n && !keep->data.empty()) {
        ((char*)buf)[k++] = keep->data.front();
        keep->data.pop_front();
    }
    return (ssize_t)k;
}

ssize_t write(int fd, const void* buf, size_t n) {
    if (fd < kFirstEmulated) return ::_write(fd, buf, (unsigned)n);
    std::lock_guard lk(g_mu);
    Fd* f = find(fd);
    if (!f) return errno = EBADF, -1;
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
    if (fd < kFirstEmulated) return ::_close(fd);
    std::lock_guard lk(g_mu);
    Fd* f = find(fd);
    if (!f) return errno = EBADF, -1;
    if (!f->ch->event) (f->write_end ? f->ch->writer_open : f->ch->reader_open) = false;
    g_fds.erase(fd);
    g_cv.notify_all();
    return 0;
}

int poll(PollFd* fds, size_t n, int timeout_ms) {
    std::unique_lock lk(g_mu);
    auto scan = [&] {
        int k = 0;
        for (size_t i = 0; i < n; i++) {
            fds[i].revents = 0;
            if (fds[i].fd < 0) continue;
            if (fds[i].fd < kFirstEmulated) {
                fds[i].revents = fds[i].events & (kIn | kOut);  // a file: always ready
            } else if (Fd* f = find(fds[i].fd)) {
                fds[i].revents = ready(*f, fds[i].events);
            } else {
                fds[i].revents = 0x020;  // POLLNVAL
            }
            k += fds[i].revents != 0;
        }
        return k;
    };
    int k = scan();
    if (k || timeout_ms == 0) return k;
    auto until = std::chrono::steady_clock::now() + std::chrono::milliseconds(timeout_ms);
    for (;;) {
        if (timeout_ms < 0) g_cv.wait(lk);
        else if (g_cv.wait_until(lk, until) == std::cv_status::timeout) return scan();
        if ((k = scan())) return k;
    }
}

#endif

}  // namespace soa::hostfd

#pragma once
// The pollable host descriptors the runtime makes for the guest (port/PLAN.md 5b, W): pipes (the
// guest's pipe(), android_native_app_glue's message pipe), event counters (the input queue's
// eventfd) and poll() over them (ALooper). Linux: the real pipe2 / eventfd / poll / read / write /
// close. Windows has no pollable pipes: these descriptors are emulated in process there, numbered
// from kFirstEmulated up, apart from the CRT's file descriptors; read / write / close / poll take
// either kind (a CRT descriptor counts as always ready).
#include <cstddef>
#include <sys/types.h>

namespace soa::hostfd {

#ifdef _WIN32
constexpr int kFirstEmulated = 0x10000;
#endif

// A non-blocking event counter (eventfd(0, EFD_NONBLOCK)); -1 on failure.
int make_event();
void event_signal(int fd);  // adds 1
void event_drain(int fd);   // resets to 0
// pipe2(fds, O_CLOEXEC): fds[0] reads, fds[1] writes. 0 or -1.
int make_pipe(int fds[2]);
// Whether `fd` is one of ours (Windows); always false on Linux, where they are kernel descriptors.
bool emulated(int fd);
ssize_t read(int fd, void* buf, size_t n);
ssize_t write(int fd, const void* buf, size_t n);
int close(int fd);

struct PollFd {
    int fd;
    short events, revents;  // POLLIN / POLLOUT / POLLERR / POLLHUP as <poll.h>
};
constexpr short kIn = 0x001, kOut = 0x004, kErr = 0x008, kHup = 0x010;
// poll(): >0 ready, 0 timeout (timeout_ms < 0: forever), -1 error.
int poll(PollFd* fds, size_t n, int timeout_ms);

}  // namespace soa::hostfd

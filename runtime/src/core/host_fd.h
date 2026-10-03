#pragma once
// The pollable host descriptors the runtime makes for the guest (port/PLAN.md 5b, W): pipes (the
// guest's pipe(), android_native_app_glue's message pipe), event counters (the input queue's
// eventfd) and poll() over them (ALooper). Linux: the real pipe2 / eventfd / poll / read / write /
// close, and guest descriptors are kernel descriptors. Windows has no pollable pipes, and CRT
// descriptors, sockets and pipes are separate namespaces: there the guest's descriptors are a table
// (small numbers, lowest free first, as POSIX) over CRT descriptors (files), Winsock sockets and
// in-process channels (pipes, event counters); read / write / close / poll take any of them (a file
// counts as always ready).
#include <cstddef>
#include <cstdint>
#include <sys/types.h>

namespace soa::hostfd {

// A non-blocking event counter (eventfd(0, EFD_NONBLOCK)); -1 on failure.
int make_event();
void event_signal(int fd);  // adds 1
void event_drain(int fd);   // resets to 0
// pipe2(fds, O_CLOEXEC): fds[0] reads, fds[1] writes. 0 or -1.
int make_pipe(int fds[2]);
// Whether `fd` is an in-process pipe or event (Windows); always false on Linux.
bool emulated(int fd);
ssize_t read(int fd, void* buf, size_t n);
ssize_t write(int fd, const void* buf, size_t n);
int close(int fd);

#ifdef _WIN32
// A CRT descriptor (an opened file) / a Winsock socket as a guest descriptor; -1 on failure.
int adopt_file(int crt);
int adopt_socket(uintptr_t sock);
// The CRT descriptor / socket behind a guest descriptor: -1 / ~0 (INVALID_SOCKET) when it isn't one.
int crt_of(int fd);
uintptr_t socket_of(int fd);
#endif

struct PollFd {
    int fd;
    short events, revents;  // POLLIN / POLLOUT / POLLERR / POLLHUP as <poll.h>
};
constexpr short kIn = 0x001, kOut = 0x004, kErr = 0x008, kHup = 0x010;
// poll(): >0 ready, 0 timeout (timeout_ms < 0: forever), -1 error.
int poll(PollFd* fds, size_t n, int timeout_ms);

}  // namespace soa::hostfd

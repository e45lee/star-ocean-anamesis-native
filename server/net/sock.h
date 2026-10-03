// The socket calls of the wire layer (loop.cpp, client.cpp), portable: BSD sockets on Linux,
// Winsock on Windows (port/PLAN.md 5b, W). Sockets are ints on both (a Winsock SOCKET handle fits).
#pragma once

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <poll.h>
#include <sys/socket.h>
#endif

#include <cstddef>
#include <cstdint>
#include <string>
#include <sys/types.h>

namespace soa::server::net::sock {

// A TCP/IPv4 socket, close-on-exec, non-blocking if asked; -1 on failure. Starts Winsock first.
int tcp_socket(bool nonblocking);
// accept() on a listening socket; the new socket non-blocking, close-on-exec, TCP_NODELAY. -1: none.
int accept_nonblocking(int listen_fd);
int close(int fd);
// SO_RCVTIMEO and SO_SNDTIMEO.
void set_timeouts(int fd, int seconds);
void set_nodelay(int fd);
// SO_REUSEADDR for a listener (Linux: rebind while old connections linger). Nothing on Windows,
// where SO_REUSEADDR would let a second server bind the same port.
void set_reuse_addr(int fd);
ssize_t recv(int fd, void* buf, size_t n);
ssize_t send(int fd, const void* buf, size_t n);  // never raises SIGPIPE
// The last call failed only because it would block / was interrupted.
bool would_block();
bool interrupted();
std::string last_error();

struct PollFd {
    int fd;
    short events, revents;
};
// poll(): POLLIN / POLLOUT / POLLERR / POLLHUP / POLLNVAL as <poll.h> (WSAPoll on Windows).
int poll(PollFd* fds, size_t n, int timeout_ms);

}  // namespace soa::server::net::sock

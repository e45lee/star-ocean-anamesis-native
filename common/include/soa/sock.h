// Host TCP sockets, portable: BSD sockets on Linux, Winsock on Windows (port/PLAN.md 5b, W).
// Used by soa-server's wire layer (server/net: loop.cpp, client.cpp) and the 3.7.0 platform's HTTP
// client (platform370/src/http_370.cpp): both connect with connect_tcp and write with send_all. Sockets are ints on both (a Winsock SOCKET handle fits).
// Not the guest's sockets: those are the runtime's HLE (runtime/src/hle/net_win32.cpp on Windows).
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

namespace soa::sock {

// Starts Winsock (once; nothing on Linux): before getaddrinfo and the like. tcp_socket does it too.
bool startup();
// A TCP socket (IPv4 unless `family` says otherwise), close-on-exec, non-blocking if asked; -1 on
// failure. Starts Winsock first.
int tcp_socket(bool nonblocking, int family = AF_INET);
// accept() on a listening socket; the new socket non-blocking, close-on-exec, TCP_NODELAY. -1: none.
int accept_nonblocking(int listen_fd);
// accept() on a listening socket; the new socket blocking, close-on-exec, TCP_NODELAY. -1: failed.
int accept(int listen_fd);
int close(int fd);
// SO_RCVTIMEO and SO_SNDTIMEO.
void set_timeouts(int fd, int seconds);
void set_nodelay(int fd);
// SO_REUSEADDR for a listener (Linux: rebind while old connections linger). Nothing on Windows,
// where SO_REUSEADDR would let a second server bind the same port.
void set_reuse_addr(int fd);
ssize_t recv(int fd, void* buf, size_t n);
ssize_t send(int fd, const void* buf, size_t n);  // never raises SIGPIPE
// fcntl(O_NONBLOCK) / FIONBIO.
bool set_nonblocking(int fd, bool on);
// The last call failed only because it would block / was interrupted / a non-blocking connect is
// under way (EINPROGRESS; WSAEWOULDBLOCK on Windows).
bool would_block();
bool connect_in_progress();
bool interrupted();
std::string last_error();

struct PollFd {
    int fd;
    short events, revents;
};
// Splits "HOST:PORT", "[IPV6]:PORT", ":PORT", "HOST", "[IPV6]" or a bare IPv6 address ("::1": more
// than one colon, no brackets) into the host (brackets removed; "" for ":PORT") and the port's text
// ("" when there is none). False for a "[" without its "]" or anything but ":PORT" after the "]".
// Callers check the port (digits, range) themselves.
bool split_host_port(const std::string& s, std::string* host, std::string* port);
// "HOST:PORT", or "[HOST]:PORT" when HOST is an IPv6 address (has a colon).
std::string join_host_port(const std::string& host, int port);

// poll(): POLLIN / POLLOUT / POLLERR / POLLHUP / POLLNVAL as <poll.h> (WSAPoll on Windows).
int poll(PollFd* fds, size_t n, int timeout_ms);

// A blocking TCP connection to `host`:`port` (a name, an IPv4 or an IPv6 address): every address the
// name resolves to, in order, each tried with a non-blocking connect of at most `connect_timeout_ms`;
// the first that connects, close-on-exec and blocking again. -1 when none does, with *err (if given)
// the last reason: "resolve: ...", "connect timeout", "connect: error N" or last_error().
int connect_tcp(const std::string& host, int port, int connect_timeout_ms, std::string* err = nullptr);
// send() until all `n` bytes are out (a short send continues); false on an error or a closed
// connection.
bool send_all(int fd, const void* data, size_t n);
inline bool send_all(int fd, const std::string& s) { return send_all(fd, s.data(), s.size()); }

}  // namespace soa::sock

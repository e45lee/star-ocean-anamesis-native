// soa-server's poll() loop (loop.h). Our code.
#include "loop.h"

#include <chrono>
#include <cstring>
#include <thread>

#include "soa/sock.h"
#include "soaserver/log.h"

namespace soa::server::net {

bool parse_host_port(const std::string& s, std::string* host, uint16_t* port) {
    std::string h, ps;
    if (!sock::split_host_port(s, &h, &ps) || h.empty() || ps.empty()) return false;
    char* e = nullptr;
    unsigned long p = strtoul(ps.c_str(), &e, 10);
    if (!e || *e || p > 65535) return false;
    *host = h;
    *port = (uint16_t)p;
    return true;
}

Loop::~Loop() {
    http_server_.reset();  // (stops it: no handler runs after this)
    for (auto& [fd, c] : conns_) {
        game_.close(c.game_id);
        sock::close(fd);
    }
    if (game_fd_ >= 0) sock::close(game_fd_);
}

bool Loop::listen_on(const std::string& host, uint16_t port, int* fd, uint16_t* bound, std::string* err) {
    addrinfo hints = {}, *res = nullptr;
    hints.ai_family = AF_UNSPEC;  // (an IPv6 host too: --listen [::1]:PORT)
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    sock::startup();  // (Winsock, before the name lookup)
    const std::string port_s = std::to_string(port);
    if (int r = getaddrinfo(host.c_str(), port_s.c_str(), &hints, &res); r != 0 || !res) {
        *err = host + ": " + gai_strerror(r);
        return false;
    }
    sockaddr_storage a = {};
    socklen_t alen = (socklen_t)res->ai_addrlen;
    memcpy(&a, res->ai_addr, res->ai_addrlen);
    freeaddrinfo(res);
    int s = sock::tcp_socket(true, a.ss_family);
    if (s >= 0) sock::set_reuse_addr(s);
    if (s < 0 || bind(s, (sockaddr*)&a, alen) != 0 || listen(s, 16) != 0) {
        *err = sock::join_host_port(host, port) + ": " + sock::last_error();
        if (s >= 0) sock::close(s);
        return false;
    }
    socklen_t len = sizeof a;
    getsockname(s, (sockaddr*)&a, &len);
    *fd = s;
    *bound = ntohs(a.ss_family == AF_INET6 ? ((sockaddr_in6*)&a)->sin6_port : ((sockaddr_in*)&a)->sin_port);
    return true;
}

bool Loop::listen_game(const std::string& host, uint16_t port, std::string* err) { return listen_on(host, port, &game_fd_, &game_port_, err); }
bool Loop::listen_http(const std::string& host, uint16_t port, std::string* err) {
    auto server = std::make_unique<HttpServer>(http_, &lock_);
    if (!server->listen(host, port, err)) return false;
    http_port_ = server->port();
    http_server_ = std::move(server);
    return true;
}

void Loop::accept_on(int lfd) {
    for (;;) {
        int fd = sock::accept_nonblocking(lfd);
        if (fd < 0) return;
        Conn& c = conns_[fd];
        c = Conn();
        c.game_id = game_.open();
    }
}

void Loop::drop(int fd) {
    auto it = conns_.find(fd);
    if (it == conns_.end()) return;
    game_.close(it->second.game_id);
    sock::close(fd);
    conns_.erase(it);
}

void Loop::on_readable(int fd, Conn& c) {
    uint8_t buf[65536];
    for (;;) {
        ssize_t n = sock::recv(fd, buf, sizeof buf);
        if (n == 0) {
            c.close_after = true;
            if (c.out.empty()) return drop(fd);
            return;
        }
        if (n < 0) {
            if (sock::would_block()) return;
            if (sock::interrupted()) continue;
            return drop(fd);
        }
        // A refused connection (a ProtocolError) ends once its reply is sent: later bytes (packets
        // buffered behind the refused one) are read and dropped, never handled.
        if (c.close_after) continue;
        if (!game_.on_data(c.game_id, buf, (size_t)n, &c.out)) c.close_after = true;
    }
}

void Loop::run_once(int timeout_ms) {
    std::vector<sock::PollFd> fds;
    if (game_fd_ >= 0) fds.push_back({game_fd_, POLLIN, 0});
    for (auto& [fd, c] : conns_) fds.push_back({fd, (short)(POLLIN | (c.out.empty() ? 0 : POLLOUT)), 0});
    if (fds.empty()) {  // HTTP only (WSAPoll refuses an empty set at once)
        std::this_thread::sleep_for(std::chrono::milliseconds(timeout_ms));
        return;
    }
    int r = sock::poll(fds.data(), fds.size(), timeout_ms);
    if (r <= 0) return;
    std::lock_guard<std::mutex> held(lock_);
    for (const sock::PollFd& p : fds) {
        if (!p.revents) continue;
        if (p.fd == game_fd_) {
            accept_on(p.fd);
            continue;
        }
        auto it = conns_.find(p.fd);
        if (it == conns_.end()) continue;
        if (p.revents & POLLIN) on_readable(p.fd, it->second);
        it = conns_.find(p.fd);
        if (it == conns_.end()) continue;
        Conn& c = it->second;
        if (p.revents & (POLLERR | POLLNVAL)) {
            drop(p.fd);
            continue;
        }
        while (!c.out.empty()) {
            ssize_t n = sock::send(p.fd, c.out.data(), c.out.size());
            if (n <= 0) {
                if (n < 0 && (sock::would_block() || sock::interrupted())) break;
                c.out.clear();
                c.close_after = true;
                break;
            }
            c.out.erase(c.out.begin(), c.out.begin() + n);
        }
        if (c.out.empty() && (c.close_after || (p.revents & POLLHUP))) drop(p.fd);
    }
}

void Loop::run(const std::atomic<bool>& stop) {
    while (!stop.load()) run_once(100);
}

}  // namespace soa::server::net

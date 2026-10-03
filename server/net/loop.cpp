// soa-server's poll() loop (loop.h). Our code.
#include "loop.h"

#include <strings.h>

#include <cstring>

#include "soa/sock.h"
#include "soaserver/log.h"

namespace soa::server::net {

#define NLOG(level, ...)                                                                  \
    do {                                                                                  \
        if (log_enabled(LogLevel::level)) log_write(LogLevel::level, "net", __VA_ARGS__); \
    } while (0)

bool parse_host_port(const std::string& s, std::string* host, uint16_t* port) {
    size_t c = s.rfind(':');
    if (c == std::string::npos || c == 0) return false;
    char* e = nullptr;
    unsigned long p = strtoul(s.c_str() + c + 1, &e, 10);
    if (!e || *e || p > 65535) return false;
    *host = s.substr(0, c);
    *port = (uint16_t)p;
    return true;
}

Loop::~Loop() {
    for (auto& [fd, c] : conns_) {
        if (!c.http) game_.close(c.game_id);
        sock::close(fd);
    }
    if (game_fd_ >= 0) sock::close(game_fd_);
    if (http_fd_ >= 0) sock::close(http_fd_);
}

bool Loop::listen_on(const std::string& host, uint16_t port, int* fd, uint16_t* bound, std::string* err) {
    addrinfo hints = {}, *res = nullptr;
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    sock::startup();  // (Winsock, before the name lookup)
    if (int r = getaddrinfo(host.c_str(), nullptr, &hints, &res); r != 0 || !res) {
        *err = host + ": " + gai_strerror(r);
        return false;
    }
    sockaddr_in a = *(sockaddr_in*)res->ai_addr;
    freeaddrinfo(res);
    a.sin_port = htons(port);
    int s = sock::tcp_socket(true);
    if (s >= 0) sock::set_reuse_addr(s);
    if (s < 0 || bind(s, (sockaddr*)&a, sizeof a) != 0 || listen(s, 16) != 0) {
        *err = host + ":" + std::to_string(port) + ": " + sock::last_error();
        if (s >= 0) sock::close(s);
        return false;
    }
    socklen_t len = sizeof a;
    getsockname(s, (sockaddr*)&a, &len);
    *fd = s;
    *bound = ntohs(a.sin_port);
    return true;
}

bool Loop::listen_game(const std::string& host, uint16_t port, std::string* err) { return listen_on(host, port, &game_fd_, &game_port_, err); }
bool Loop::listen_http(const std::string& host, uint16_t port, std::string* err) { return listen_on(host, port, &http_fd_, &http_port_, err); }

void Loop::accept_on(int lfd, bool http) {
    for (;;) {
        int fd = sock::accept_nonblocking(lfd);
        if (fd < 0) return;
        Conn& c = conns_[fd];
        c = Conn();
        c.http = http;
        if (!http) c.game_id = game_.open();
    }
}

void Loop::drop(int fd) {
    auto it = conns_.find(fd);
    if (it == conns_.end()) return;
    if (!it->second.http) game_.close(it->second.game_id);
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
        if (!c.http) {
            if (!game_.on_data(c.game_id, buf, (size_t)n, &c.out)) c.close_after = true;
            continue;
        }
        c.parser.feed((const char*)buf, (size_t)n);
        for (;;) {
            HttpRequest req;
            HttpParser::Result r = c.parser.next(&req);
            if (r == HttpParser::kNeedMore) break;
            HttpResponse resp;
            bool keep = false;
            if (r == HttpParser::kBad) {
                resp.status = 400;
                resp.body = "bad request\n";
            } else {
                http_.handle(req, resp);
                // A streamed body (the CDN's files and bundles) is sent from memory like any other.
                if (!resp.materialize()) {
                    resp = HttpResponse();
                    resp.status = 500;
                    resp.body = "read error\n";
                }
                const std::string* conn = req.header("Connection");
                keep =
                    req.version == "HTTP/1.1" ? !(conn && !strcasecmp(conn->c_str(), "close")) : (conn && !strcasecmp(conn->c_str(), "keep-alive"));
                NLOG(Info, "http %s %s -> %d (%zu bytes)", req.method.c_str(), req.target.c_str(), resp.status, resp.body.size());
            }
            std::string s = serialize_response(resp, keep, req.method == "HEAD");
            c.out.insert(c.out.end(), s.begin(), s.end());
            if (!keep) {
                c.close_after = true;
                break;
            }
        }
    }
}

void Loop::run_once(int timeout_ms) {
    std::vector<sock::PollFd> fds;
    if (game_fd_ >= 0) fds.push_back({game_fd_, POLLIN, 0});
    if (http_fd_ >= 0) fds.push_back({http_fd_, POLLIN, 0});
    for (auto& [fd, c] : conns_) fds.push_back({fd, (short)(POLLIN | (c.out.empty() ? 0 : POLLOUT)), 0});
    int r = sock::poll(fds.data(), fds.size(), timeout_ms);
    if (r <= 0) return;
    for (const sock::PollFd& p : fds) {
        if (!p.revents) continue;
        if (p.fd == game_fd_ || p.fd == http_fd_) {
            accept_on(p.fd, p.fd == http_fd_);
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

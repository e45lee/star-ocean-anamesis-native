// soa_sock_tests: soa/sock.h's connect_tcp and send_all over loopback (IPv4, and IPv6 where the
// host has it), an address nothing answers, a name that doesn't resolve. Prints "ok" / "FAIL" lines; the exit
// status is the number of failures.
#include <cstdio>
#include <cstring>
#include <string>
#include <thread>
#include <vector>

#include <soa/sock.h>

namespace {

int g_failures = 0;
void check(bool ok, const std::string& what) {
    fprintf(stderr, "%s  %s\n", ok ? "ok  " : "FAIL", what.c_str());
    if (!ok) g_failures++;
}

// A listener on an ephemeral loopback port of `family`; -1 when the host has no such loopback.
int listen_loopback(int family, int* port) {
    int fd = soa::sock::tcp_socket(false, family);
    if (fd < 0) return -1;
    sockaddr_storage ss{};
    socklen_t len;
    if (family == AF_INET6) {
        auto* a = (sockaddr_in6*)&ss;
        a->sin6_family = AF_INET6;
        a->sin6_addr = in6addr_loopback;
        len = sizeof *a;
    } else {
        auto* a = (sockaddr_in*)&ss;
        a->sin_family = AF_INET;
        a->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        len = sizeof *a;
    }
    if (bind(fd, (sockaddr*)&ss, len) != 0 || listen(fd, 4) != 0 || getsockname(fd, (sockaddr*)&ss, &len) != 0) {
        soa::sock::close(fd);
        return -1;
    }
    *port = ntohs(family == AF_INET6 ? ((sockaddr_in6*)&ss)->sin6_port : ((sockaddr_in*)&ss)->sin_port);
    return fd;
}

// Connects to `host` on a fresh listener, sends `n` bytes with send_all, and checks they arrive.
void round_trip(int family, const std::string& host, size_t n) {
    int port = 0;
    int lfd = listen_loopback(family, &port);
    std::string tag = host + " (" + std::to_string(n) + " bytes)";
    if (lfd < 0) {
        fprintf(stderr, "skip  %s: no loopback of that family\n", tag.c_str());
        return;
    }
    std::vector<uint8_t> sent(n), got;
    for (size_t i = 0; i < n; i++) sent[i] = (uint8_t)(i * 131 + 7);
    std::thread reader([&] {
        int c = soa::sock::accept(lfd);
        if (c < 0) return;
        uint8_t buf[65536];
        for (ssize_t k; (k = soa::sock::recv(c, buf, sizeof buf)) > 0;) got.insert(got.end(), buf, buf + k);
        soa::sock::close(c);
    });
    std::string err;
    int fd = soa::sock::connect_tcp(host, port, 5000, &err);
    check(fd >= 0, "connect_tcp " + tag + (fd < 0 ? ": " + err : ""));
    if (fd >= 0) {
        check(soa::sock::send_all(fd, sent.data(), sent.size()), "send_all " + tag);
        soa::sock::close(fd);
    } else {
        soa::sock::close(lfd);  // (unblocks the reader's accept)
        lfd = -1;
    }
    reader.join();
    if (fd >= 0) check(got == sent, "the bytes arrive " + tag);
    if (lfd >= 0) soa::sock::close(lfd);
}

}  // namespace

int main() {
    round_trip(AF_INET, "127.0.0.1", 3);
    round_trip(AF_INET, "127.0.0.1", 5u << 20);  // (more than one send's worth)
    round_trip(AF_INET6, "::1", 1000);
    // a name: every address it resolves to is tried in turn (localhost may be ::1 first)
    round_trip(AF_INET, "localhost", 100);
    // an address nothing answers (TEST-NET-1): unreachable or the connect timeout, with a reason. (Not
    // a closed loopback port: WSL's mirrored networking accepts those.)
    std::string err;
    int fd = soa::sock::connect_tcp("192.0.2.1", 9, 300, &err);
    check(fd < 0 && !err.empty(), "an address nothing answers: -1 (" + err + ")");
    if (fd >= 0) soa::sock::close(fd);
    err.clear();
    fd = soa::sock::connect_tcp("no-such-host.invalid", 80, 2000, &err);
    check(fd < 0 && err.rfind("resolve: ", 0) == 0, "an unknown name: -1 (" + err + ")");
    fprintf(stderr, "%s (%d failures)\n", g_failures ? "FAIL" : "all passed", g_failures);
    return g_failures;
}

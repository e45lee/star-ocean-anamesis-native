// soa-server's HTTP server (http_server.h): cpp-httplib's server with one catch-all route per
// method that hands the request to the HttpRouter.
// cpp-httplib first (net/use_httplib.h: winsock2.h before windows.h).
#include "net/use_httplib.h"

#include "http_server.h"

#include <strings.h>

#include <algorithm>
#include <thread>

#include "soa/sock.h"
#include "soaserver/log.h"

namespace soa::server::net {

#define NLOG(level, ...)                                                                  \
    do {                                                                                  \
        if (log_enabled(LogLevel::level)) log_write(LogLevel::level, "net", __VA_ARGS__); \
    } while (0)

namespace {

constexpr size_t kMaxBody = 16 * 1024 * 1024;  // a request body (the bridge's JSON is ~100 bytes)

// An HttpBodyStream as cpp-httplib's content provider: the stream is sequential, so a request for
// a later offset (a Range) reads and drops the bytes before it; an earlier offset can't be served.
struct StreamProvider {
    std::shared_ptr<HttpBodyStream> stream;
    uint64_t pos = 0;
    bool operator()(size_t offset, size_t length, httplib::DataSink& sink) {
        char buf[1 << 16];
        if (offset < pos) return false;
        while (pos < offset) {
            int64_t k = stream->read(buf, (size_t)std::min<uint64_t>(sizeof buf, offset - pos));
            if (k <= 0) return false;
            pos += (uint64_t)k;
        }
        int64_t k = stream->read(buf, std::min(sizeof buf, length));
        if (k <= 0) return false;
        pos += (uint64_t)k;
        return sink.write(buf, (size_t)k);
    }
};

}  // namespace

struct HttpServer::Impl {
    httplib::Server svr;
    std::thread th;
};

HttpServer::HttpServer(const HttpRouter& router, std::mutex* lock) : impl_(std::make_unique<Impl>()) {
    httplib::Server& svr = impl_->svr;
    auto serve = [&router, lock](const httplib::Request& in, httplib::Response& out) {
        std::vector<std::pair<std::string, std::string>> headers(in.headers.begin(), in.headers.end());
        // the raw target: make_request splits the query and URL-decodes the path as it always did
        HttpRequest req = make_request(in.method, in.target, std::move(headers), in.body, in.version);
        HttpResponse resp;
        {
            std::unique_lock<std::mutex> held;
            if (lock) held = std::unique_lock<std::mutex>(*lock);
            router.handle(req, resp);
        }
        // read by emulator/scripts/standin_fetch_test.sh ("I/net: http GET <target> -> ...")
        NLOG(Info, "http %s %s -> %d (%llu bytes)", req.method.c_str(), req.target.c_str(), resp.status, (unsigned long long)resp.content_length());
        // a 200 is left to cpp-httplib: 206 when the request has a Range
        if (resp.status != 200) out.status = resp.status;
        std::string type = "application/octet-stream";
        for (auto& [k, v] : resp.headers) {
            if (!strcasecmp(k.c_str(), "Content-Length") || !strcasecmp(k.c_str(), "Connection")) continue;
            if (!strcasecmp(k.c_str(), "Content-Type")) type = v;
            else out.set_header(k, v);
        }
        if (resp.stream) {
            uint64_t n = resp.stream->size();
            out.set_content_provider((size_t)n, type, StreamProvider{std::move(resp.stream)});
        } else {
            out.set_content(std::move(resp.body), type);
        }
    };
    svr.Get(".*", serve);  // (and HEAD)
    svr.Post(".*", serve);
    svr.Put(".*", serve);
    svr.Delete(".*", serve);
    svr.Options(".*", serve);
    svr.Patch(".*", serve);
    svr.set_payload_max_length(kMaxBody);
    svr.set_keep_alive_max_count(1000);
    svr.set_address_family(AF_INET);  // (listen: AF_INET6 for an IPv6 address)
    svr.set_tcp_nodelay(true);
    // SO_REUSEADDR as the game port's listener (sock::set_reuse_addr: nothing on Windows)
    svr.set_socket_options([](socket_t s) { sock::set_reuse_addr((int)s); });
}

HttpServer::~HttpServer() { stop(); }

bool HttpServer::listen(const std::string& host, uint16_t port, std::string* err) {
    httplib::Server& svr = impl_->svr;
    sock::startup();
    if (host.find(':') != std::string::npos) svr.set_address_family(AF_INET6);  // --http [::1]:PORT
    int bound = port ? (svr.bind_to_port(host, port) ? port : -1) : svr.bind_to_any_port(host);
    if (bound <= 0) {
        *err = sock::join_host_port(host, port) + ": " + sock::last_error();
        return false;
    }
    port_ = (uint16_t)bound;
    impl_->th = std::thread([&svr] { svr.listen_after_bind(); });
    svr.wait_until_ready();
    return true;
}

void HttpServer::stop() {
    if (!impl_->th.joinable()) return;
    impl_->svr.stop();
    impl_->th.join();
}

}  // namespace soa::server::net

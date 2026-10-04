#pragma once
// soa-server's HTTP server (our code over cpp-httplib): serves an HttpRouter (http.h) on a TCP
// port. cpp-httplib owns the connections on its own threads: keep-alive, HEAD (a GET without the
// body), Range requests (206, also of a streamed body: the stream is read from the range's
// offset), request bodies up to 16 MiB. Every request is logged as
// "http <METHOD> <target> -> <status> (<n> bytes)" (read by emulator/scripts/standin_fetch_test.sh).
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>

#include "http.h"

namespace soa::server::net {

class HttpServer {
public:
    // `router` answers every request; `lock`, when given, is held while it does (the router's
    // handlers then run one at a time with whatever else takes the lock: the game loop, loop.h).
    // A streamed body is read after the lock is released.
    HttpServer(const HttpRouter& router, std::mutex* lock = nullptr);
    ~HttpServer();  // stop()s
    // Binds host:port (port 0: any; the bound port is port()) and starts serving on a thread.
    bool listen(const std::string& host, uint16_t port, std::string* err);
    uint16_t port() const { return port_; }
    // Stops serving and joins the thread (open connections are closed).
    void stop();

private:
    struct Impl;
    std::unique_ptr<Impl> impl_;
    uint16_t port_ = 0;
};

}  // namespace soa::server::net

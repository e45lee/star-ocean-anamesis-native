#pragma once
// soa-server's HTTP side (our code): the requests, responses and the router of the bridge
// (/bridge) and the CDN (Android/<file>). Handlers are mounted by URL prefix (HttpRouter::route),
// so the CDN content (server/src/cdn*) is mounted next to the bridge. The connections are
// cpp-httplib's (http_server.h: keep-alive, HEAD, ranges); soa's in-process CDN calls the router
// in memory (HttpRouter::handle).
#include <cstdint>
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace soa::server::net {

struct HttpRequest {
    std::string method, target, path, query, version;
    std::vector<std::pair<std::string, std::string>> headers;  // names as sent
    std::string body;
    // A header's value by case-insensitive name, nullptr when absent.
    const std::string* header(const std::string& name) const;
};

// A request from its parts, as the HTTP server (http_server.cpp) makes it from the wire: `target` is split at '?' into
// the URL-decoded `path` (an absolute-form target keeps only its path) and `query`. The router's
// in-memory callers (the port's in-process server) build their requests with it.
HttpRequest make_request(std::string method, std::string target, std::vector<std::pair<std::string, std::string>> headers = {}, std::string body = {},
                         std::string version = "HTTP/1.1");

// A response body read in pieces (HttpResponse::stream), for bodies too big to hold (the CDN's
// bundles). One reader per response; not thread-safe.
class HttpBodyStream {
public:
    virtual ~HttpBodyStream() = default;
    virtual uint64_t size() const = 0;               // the whole body's length (Content-Length)
    virtual int64_t read(char* buf, size_t n) = 0;   // > 0 bytes read, 0 at the end, < 0 on an error
};

struct HttpResponse {
    int status = 200;
    std::vector<std::pair<std::string, std::string>> headers;  // Content-Length is added
    std::string body;
    // When set, the body is this stream's bytes instead of `body` (a handler sets one or the other).
    // An in-memory caller of HttpRouter::handle reads it as it goes; the HTTP server sends it as it
    // reads it (a Range request skips forward to its offset).
    std::shared_ptr<HttpBodyStream> stream;
    void set_header(const std::string& name, const std::string& value);
    // The body's length (the stream's size when there is one).
    uint64_t content_length() const { return stream ? stream->size() : body.size(); }
};

// A handler answers the request (true) or passes (false: the next route, then 404). `path` is
// the request path with the route's prefix removed.
using HttpHandler = std::function<bool(const HttpRequest& req, const std::string& rest, HttpResponse& resp)>;

class HttpRouter {
public:
    // Requests whose path starts with `prefix` (e.g. "/bridge", "/Android/") go to `handler`;
    // routes are tried longest prefix first.
    void route(const std::string& prefix, HttpHandler handler);
    // The answer to one request: the first route that takes it, else 404. No connection is
    // involved, so this is also the in-memory entry point (a request from make_request; the
    // response's body may be a stream). Thread-safe once the routes are mounted when the handlers
    // are (the CDN's: cdn::Tree::lookup only reads).
    void handle(const HttpRequest& req, HttpResponse& resp) const;

private:
    std::vector<std::pair<std::string, HttpHandler>> routes_;
};

// Static files: GET <prefix><rel> -> <dir>/<rel> (no "..", no absolute paths). The placeholder
// CDN: soa-server mounts it as /Android/ over --download-dir.
HttpHandler static_files(std::string dir);

// gzip (RFC 1952) with zlib; gunzip for tests. Empty on error.
std::string gzip(const std::string& data);
std::string gunzip(const std::string& data);

// Percent-decodes a URL path (%XX). A '+' stays a '+': only a query's form encoding makes it a
// space (RFC 3986), and the path is decoded here once (make_request), not again by its handlers.
std::string url_decode(const std::string& s);

}  // namespace soa::server::net

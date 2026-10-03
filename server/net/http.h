#pragma once
// soa-server's HTTP side (our code): a minimal HTTP/1.1 server for the bridge (/bridge) and the
// CDN (Android/<file>). GET / POST / HEAD with Content-Length bodies, keep-alive, no chunked
// requests. Handlers are mounted by URL prefix (HttpRouter::route), so the CDN content
// (server/src/cdn*, a separate step) can be mounted next to the bridge; the sockets are loop.h's.
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

// A request from its parts, as HttpParser makes it from the wire: `target` is split at '?' into
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
    // An in-memory caller of HttpRouter::handle reads it as it goes; the socket loop reads it whole
    // first (materialize), as it did with every body.
    std::shared_ptr<HttpBodyStream> stream;
    void set_header(const std::string& name, const std::string& value);
    // The body's length (the stream's size when there is one).
    uint64_t content_length() const { return stream ? stream->size() : body.size(); }
    // Reads the stream into `body` and drops it; false (body cleared) when it fails or comes up short.
    bool materialize();
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

// Parses requests from one connection's byte stream.
class HttpParser {
public:
    enum Result { kNeedMore, kRequest, kBad };
    void feed(const char* p, size_t n) { buf_.append(p, n); }
    Result next(HttpRequest* out);

private:
    std::string buf_;
};

// The response bytes (status line, headers incl. Content-Length and Connection, body; a HEAD
// response keeps the headers and drops the body). A stream is not read: materialize() first.
std::string serialize_response(const HttpResponse& r, bool keep_alive, bool head = false);
const char* status_text(int status);

// Static files: GET <prefix><rel> -> <dir>/<rel> (no "..", no absolute paths). The placeholder
// CDN: soa-server mounts it as /Android/ over --download-dir.
HttpHandler static_files(std::string dir);

// gzip (RFC 1952) with zlib; gunzip for tests. Empty on error.
std::string gzip(const std::string& data);
std::string gunzip(const std::string& data);

// URL-decodes %XX and '+'.
std::string url_decode(const std::string& s);

}  // namespace soa::server::net

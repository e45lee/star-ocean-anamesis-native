// The CDN's HTTP handler (net/cdn_http.h).
#include "cdn_http.h"

namespace soa::server::net {

namespace {
// A cdn::Reader as the response's body stream.
class CdnStream : public HttpBodyStream {
public:
    explicit CdnStream(std::unique_ptr<cdn::Reader> r) : r_(std::move(r)) {}
    uint64_t size() const override { return r_->size(); }
    int64_t read(char* buf, size_t n) override { return r_->read((uint8_t*)buf, n); }

private:
    std::unique_ptr<cdn::Reader> r_;
};
}  // namespace

HttpHandler cdn_handler(std::shared_ptr<const cdn::Tree> tree) {
    return [tree = std::move(tree)](const HttpRequest& req, const std::string&, HttpResponse& resp) {
        if (req.method != "GET" && req.method != "HEAD") return false;
        cdn::Response r;
        if (!tree->lookup(req.path, r, /*stream=*/true) || r.status != 200) return false;
        resp.status = 200;
        resp.set_header("Content-Type", r.content_type.empty() ? "application/octet-stream" : r.content_type);
        if (r.bundle || !r.file.empty()) {
            // Files and bundles (up to hundreds of MB) as a stream: read as the caller asks for it
            // in memory (the port's in-process server), whole by the socket loop.
            std::unique_ptr<cdn::Reader> rd = r.open();
            if (!rd) return false;
            resp.stream = std::make_shared<CdnStream>(std::move(rd));
        } else {
            resp.body.assign(r.body.begin(), r.body.end());
        }
        return true;
    };
}

void mount_cdn(HttpRouter& router, std::shared_ptr<const cdn::Tree> tree) {
    for (const char* p : {"/download/", "/master/", "/Android/"}) router.route(p, cdn_handler(tree));
}

}  // namespace soa::server::net

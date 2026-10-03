// --server inproc: the local server's CDN, in the soa process, with no sockets (port plumbing, not
// a native).
//
// The 3.7.0 client finds its downloadable game data (the home's 3D map and characters, sounds,
// episodes, ...) through the Login reply's CDN keys: AssetPath, MasterPath and r_ver
// (server/src/api/entry/entry.cpp add_cdn_paths; CApiNotify::OnGetPlayerRes deserializes them like every
// other key). Without them the client never checks or mounts its download storage, and the home
// shows the missing-texture checkerboard (P1 finding, docs/history/REBASE-370.md). soa-server sends them
// and serves the CDN on its HTTP port. The in-process server does the same here, without the
// port: the library's CDN tree (soaserver/cdn.h, built from --download-dir and the stand-ins, with
// the served master) mounted on soa-server's own HTTP router (net/cdn_http.h mount_cdn, the same
// handlers), and the router installed as platform370's HTTP backend (platform370.h
// set_http_backend). platform370's HTTP client then hands each request to a mapped host
// (production-game.so-ana.com: config().cdn_url is the client's own host name, without a port,
// which the 3.7.0 URI parser can't resolve anyway) to HttpRouter::handle as a call, and reads the
// body from the handler's stream (files and bundles are read as the client asks for them, not
// held whole). No socket is opened, no port listened on, no thread started. So the in-process
// client downloads (or checks) its data exactly as soa-emu's does from soa-server: a
// server-side answer, no client change.
//
// /bridge isn't mounted: the FakeApiCaller route sends no GameRPC, so the bridge has nothing to
// carry.
#include <memory>
#include <string>

#include "net/cdn_http.h"
#include "net/http.h"
#include "platform370/platform370.h"
#include "soaserver/cdn.h"
#include "soaserver/config.h"

namespace soa::server_port {

// soa-server's default --cdn-url (server/app/main.cpp kClientCdnUrl): the client's own host.
constexpr const char* kClientCdnUrl = "http://production-game.so-ana.com";

namespace {

namespace net = server::net;

// The router's streamed body as platform370's body reader.
class StreamReader : public platform370::HttpBodyReader {
public:
    explicit StreamReader(std::shared_ptr<net::HttpBodyStream> s) : s_(std::move(s)) {}
    int64_t read(void* buf, size_t n) override { return s_->read((char*)buf, n); }

private:
    std::shared_ptr<net::HttpBodyStream> s_;
};

// platform370's HTTP backend over soa-server's router: request -> HttpRouter::handle -> response.
// Thread-safe: the router doesn't change once mounted, and the CDN's handler only reads its tree.
class RouterBackend : public platform370::HttpBackend {
public:
    explicit RouterBackend(std::shared_ptr<const server::cdn::Tree> tree) : tree_(std::move(tree)) { net::mount_cdn(router_, tree_); }

    bool handle(const platform370::HttpBackendRequest& req, platform370::HttpBackendResponse& out) override {
        net::HttpRequest rq = net::make_request(req.method, req.target, req.headers, req.body);
        net::HttpResponse rs;
        router_.handle(rq, rs);
        out.status = rs.status;
        out.headers = std::move(rs.headers);
        out.length = rs.content_length();
        if (rs.stream) out.reader = std::make_unique<StreamReader>(std::move(rs.stream));
        else out.body = std::move(rs.body);
        return true;
    }

    const std::shared_ptr<const server::cdn::Tree>& tree() const { return tree_; }

private:
    std::shared_ptr<const server::cdn::Tree> tree_;
    net::HttpRouter router_;
};

// The process's backend (never destroyed: platform370 may call it until exit).
RouterBackend* g_backend = nullptr;

}  // namespace

// Builds the CDN from server::config() (download_dir, the stand-ins, the scratch dir), sets
// config().cdn_url / cdn_revision, and installs its router as platform370's HTTP backend. true,
// with what is served in *err; false (why in *err) when there is no content.
bool start_inproc_cdn(std::string* err) {
    server::ServerConfig& c = server::config();
    auto tree = server::cdn::build_from_config();
    if (!tree) {
        *err = "no CDN content (download dir " + c.download_dir + ")";
        return false;
    }
    g_backend = new RouterBackend(tree);
    platform370::set_http_backend(g_backend);
    if (c.cdn_url.empty()) c.cdn_url = kClientCdnUrl;
    *err = c.cdn_url + "/download/" + tree->revision() + "/Android/<name> (" + tree->summary() + ")";
    return true;
}

// The in-process CDN's tree (nullptr before start_inproc_cdn), for the tests (server_cdn_test.cpp).
std::shared_ptr<const server::cdn::Tree> inproc_cdn_tree() { return g_backend ? g_backend->tree() : nullptr; }

}  // namespace soa::server_port

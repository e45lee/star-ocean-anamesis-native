// The in-process CDN without sockets (server_cdn.cpp; test-only, nothing native).
//
// server/inproc-http-backend: --server inproc (the selftest's default) installs the CDN's router as
// platform370's HTTP backend. Through the jb.Aska.AskaActivity HTTP methods the client calls
// (platform370's HttpRequest / GetStatusCode / GetHttpHeader / ReadHttpResponse), GET
// version.bin, a bundle of the Individual manifest (read in the client's way: ReadHttpResponse
// until -1) and a missing file; the bytes must be cdn::Tree::lookup's, the head the native parser's
// shape (header fields only, the real Content-Length), the bundle's SHA-1 the manifest's md5.
// Then no TCP socket may be open in the process (/proc/self/fd against /proc/self/net/tcp{,6}).
#include <dirent.h>
#include <unistd.h>

#include <cstring>
#include <fstream>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "jni/jvm.h"
#include "native/api/server_adapters.h"
#include "native/common/test.h"
#include "platform370/platform370.h"
#include "soaserver/cdn.h"
#include "soaserver/config.h"
#include "soaserver/msgpack.h"

namespace soa::server_port {
namespace {

struct Got {
    bool ok = false;
    int status = 0;
    std::string head, body;
};

// One request through the AskaActivity methods, as NativeHttpClient::_doRequest makes it.
Got client_get(TestContext& t, const std::string& url) {
    Got g;
    auto& vm = jni::Vm::get();
    jni::Class* c = vm.find_class("jb/Aska/AskaActivity", false);
    auto m = [&](const char* name, const char* sig) -> jni::Method* {
        jni::Method* mm = c ? vm.find_method(c, name, sig, false) : nullptr;
        if (!mm || !mm->impl) t.fail("AskaActivity.%s%s missing", name, sig);
        return mm && mm->impl ? mm : nullptr;
    };
    jni::Method *req = m("HttpRequest", "(Ljava/lang/String;ILjava/lang/String;Z)I"), *st = m("GetStatusCode", "()I"),
                *hd = m("GetHttpHeader", "()Ljava/lang/String;"), *rd = m("ReadHttpResponse", "([B)I"), *cl = m("CloseHttpRequest", "()V");
    if (!req || !st || !hd || !rd || !cl) return g;
    jni::Object* self = vm.activity;
    if ((s32)req->impl(self, {(u64)vm.str(url), 0, (u64)vm.str(""), 0}) < 1) {
        t.fail("HttpRequest(%s) failed", url.c_str());
        return g;
    }
    g.status = (s32)st->impl(self, {});
    g.head = jni::jstr(hd->impl(self, {}));
    jni::Array* buf = vm.new_array('B', 32768);  // the client's GetTcpReceiveSize-sized buffer
    for (;;) {
        s32 n = (s32)rd->impl(self, {(u64)buf});
        if (n < 0) break;
        g.body.append((const char*)buf->data.data(), (size_t)n);
    }
    cl->impl(self, {});
    g.ok = true;
    return g;
}

std::string lookup(TestContext& t, const server::cdn::Tree& tree, const std::string& path) {
    server::cdn::Response r;
    std::vector<uint8_t> b;
    if (!tree.lookup(path, r) || !r.read(b)) t.fail("Tree::lookup(%s)", path.c_str());
    return std::string(b.begin(), b.end());
}

// The inodes of the sockets this process has open, and those of them that are TCP sockets.
std::set<std::string> tcp_sockets_open() {
    std::set<std::string> mine, tcp;
    if (DIR* d = opendir("/proc/self/fd")) {
        while (dirent* e = readdir(d)) {
            char link[256];
            ssize_t n = readlink(("/proc/self/fd/" + std::string(e->d_name)).c_str(), link, sizeof link - 1);
            if (n <= 0) continue;
            link[n] = 0;
            if (!strncmp(link, "socket:[", 8)) mine.insert(std::string(link + 8, strcspn(link + 8, "]")));
        }
        closedir(d);
    }
    for (const char* f : {"/proc/self/net/tcp", "/proc/self/net/tcp6"}) {
        std::ifstream in(f);
        std::string line;
        std::getline(in, line);  // header
        while (std::getline(in, line)) {
            std::istringstream ss(line);
            std::string col[10];
            for (auto& s : col) ss >> s;  // sl local rem st tx:rx tr:when retrnsmt uid timeout inode
            if (mine.count(col[9])) tcp.insert(col[9]);
        }
    }
    return tcp;
}

NATIVE_TEST("server/inproc-http-backend") {
    auto tree = inproc_cdn_tree();
    if (!tree) return t.fail("no in-process CDN (the selftest runs --server inproc)");
    if (!platform370::http_backend()) t.fail("platform370 has no HTTP backend installed");
    const std::string& cdn = server::config().cdn_url;
    if (platform370::mapped_address(cdn.substr(cdn.find("://") + 3)).empty()) t.fail("%s isn't a mapped host", cdn.c_str());
    const std::string path = "/download/" + tree->revision() + "/Android/", base = cdn + path;

    // version.bin (in memory in the tree)
    Got v = client_get(t, base + "version.bin");
    t.expect_eq(v.status, 200, "version.bin status");
    std::string want = lookup(t, *tree, path + "version.bin");
    if (v.body != want) t.fail("version.bin: %zu bytes, Tree::lookup %zu", v.body.size(), want.size());
    if (v.head.rfind("HTTP/", 0) == 0) t.fail("the head has a status line: %s", v.head.c_str());
    if (v.head.find("Content-Length: " + std::to_string(want.size()) + "\r\n") == std::string::npos)
        t.fail("the head lacks Content-Length %zu: %s", want.size(), v.head.c_str());

    // A bundle of the Individual manifest (streamed by the backend): the largest up to 64 MB.
    std::string man = lookup(t, *tree, path + "manifest/etc2/hi/version_latest_Individual.bin");
    server::Value mv = server::mp_decode(std::vector<uint8_t>(man.begin(), man.end()));
    const server::Value* assets = mv.find("assets");
    std::string bundle, md5;
    uint64_t best = 0;
    for (auto& [name, e] : assets ? assets->map : std::vector<std::pair<std::string, server::Value>>{}) {
        const server::Value* sz = e.find("size");
        const server::Value* h = e.find("md5");
        if (sz && h && sz->u > best && sz->u <= (64u << 20)) best = sz->u, bundle = name, md5 = h->s;
    }
    if (bundle.empty()) return t.fail("no bundle in version_latest_Individual.bin");
    Got b = client_get(t, base + bundle);
    t.expect_eq(b.status, 200, "bundle status");
    want = lookup(t, *tree, path + bundle);
    if (b.body != want) t.fail("%s: %zu bytes, Tree::lookup %zu", bundle.c_str(), b.body.size(), want.size());
    if (b.body.size() != best) t.fail("%s: %zu bytes, the manifest says %llu", bundle.c_str(), b.body.size(), (unsigned long long)best);
    if (server::cdn::sha1_hex((const uint8_t*)b.body.data(), b.body.size()) != md5) t.fail("%s: SHA-1 != the manifest's md5", bundle.c_str());

    // A missing file.
    Got n = client_get(t, base + "no/such.file");
    t.expect_eq(n.status, 404, "404");

    // No TCP socket in the process: the backend took every request.
    auto tcp = tcp_sockets_open();
    if (!tcp.empty()) t.fail("%zu TCP socket(s) open in the process (first inode %s)", tcp.size(), tcp.begin()->c_str());
}

}  // namespace
}  // namespace soa::server_port

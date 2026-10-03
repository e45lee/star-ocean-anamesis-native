// The CDN over soa-server's HTTP server (net/cdn_http.h): a synthetic download (version.bin, an
// Individual manifest, one asset) and a tiny master, the tree mounted on the router, fetched over
// loopback the way the 3.7.0 client builds its URLs: <AssetPath>/<r_ver>/Android/<name>
// (net/cdn-loopback), and in memory through HttpRouter::handle (net/cdn-in-memory).
#include <ftw.h>
#include <sqlite3.h>
#include <sys/stat.h>
#include <unistd.h>

#include <atomic>
#include <cstdio>
#include <cstring>
#include <thread>

#include "net/cdn_http.h"
#include "net/client.h"
#include "net/game.h"
#include "net/http.h"
#include "net/loop.h"
#include "soaserver/adld.h"
#include "soaserver/cdn.h"
#include "soaserver/msgpack.h"
#include "soaserver/native_test.h"

namespace {

using namespace soa::server;
using namespace soa::server::net;

struct NoBackend : Backend {
    uint32_t call(const Request&, std::vector<uint8_t>*) override { return 0xffffffffu; }
    bool with_state(const std::function<void(ext::Sql&)>&) override { return false; }
};

void put(const std::string& p, const std::vector<uint8_t>& d) {
    for (size_t i = 1; i < p.size(); i++)
        if (p[i] == '/') mkdir(p.substr(0, i).c_str(), 0755);
    FILE* f = fopen(p.c_str(), "wb");
    if (!f) return;
    fwrite(d.data(), 1, d.size(), f);
    fclose(f);
}

// The synthetic download and master under `root`, and the tree built from them (nullptr: failed).
std::shared_ptr<cdn::Tree> make_tree(soa::server::testing::Context& t, const std::string& root) {
    std::string mir = root + "/mirror";
    auto plain = t.rand_bytes(700);
    auto file = adld::encrypt("BG/x.aaf", plain, adld::kXor);
    put(mir + "/BG/x.aaf", file);
    std::string master = root + "/master.sqlite3";
    mkdir(root.c_str(), 0755);
    sqlite3* db = nullptr;
    sqlite3_open(master.c_str(), &db);
    sqlite3_exec(db, "create table master_global (key text, value text); insert into master_global (key, value) values ('service_stop_day', 'x');",
                 nullptr, nullptr, nullptr);
    sqlite3_close(db);
    auto entry = [](uint64_t size, uint32_t enc) {
        Value e = Value::object();
        e["md5"] = Value("old");
        e["size"] = Value((unsigned long long)size);
        e["time"] = Value(0u);
        e["parentHash"] = Value(0u);
        e["flags"] = Value(0u);
        e["encType"] = Value(enc);
        e["ep_data"] = Value("");
        e["meta"] = Value::array();
        return e;
    };
    Value vb = Value::object();
    vb["appliversion"] = Value(1u);
    vb["version"] = Value("00000000000000000000000000000000");
    vb["revision"] = Value("41");
    vb["assets"] = Value::object();
    vb["assets"]["BG/x.aaf"] = entry(file.size(), 1);
    vb["assets"]["sqlite/basmaster.sqlite3"] = entry(1, 2);
    put(mir + "/version.bin", mp_encode(vb));
    Value man = Value::object();
    man["version"] = Value("00000000000000000000000000000000");
    man["toolversion"] = Value("1.2.0");
    man["assets"] = Value::object();
    for (auto [bundle, name, enc] : {std::tuple{"I/1/1.bin", "BG/x.aaf", 1u}, std::tuple{"I/2/2.bin", "sqlite/basmaster.sqlite3", 2u}}) {
        Value m = Value::object();
        m["size"] = Value(1u);
        m["md5"] = Value("old");
        m["meta"] = Value::array();
        m["p"] = Value(std::string(bundle).substr(0, strlen(bundle) - 4));
        m["e"] = Value(enc);
        m["ep_data"] = Value("");
        Value b = Value::object();
        b[name] = m;
        b["md5"] = Value("old");
        b["size"] = Value(0u);
        b["meta"] = Value::array();
        man["assets"][bundle] = b;
    }
    put(mir + "/manifest/etc2/hi/version_latest_Individual.bin", mp_encode(man));

    cdn::Options o;
    o.mirror = mir;
    o.master = master;
    o.scratch = root + "/scratch";
    o.overrides = false;
    o.hash_cache = false;
    std::string err;
    std::shared_ptr<cdn::Tree> tree = cdn::Tree::build(o, &err);
    if (!tree) t.fail("build: %s", err.c_str());
    return tree;
}

void remove_tree(const std::string& root) {
    nftw(root.c_str(), [](const char* q, const struct stat*, int, struct FTW*) { return ::remove(q); }, 16, FTW_DEPTH | FTW_PHYS);
}

NATIVE_TEST("net/cdn-loopback") {
    std::string root = "/tmp/soa-cdn-test-" + std::to_string(getpid()) + "-http";
    std::shared_ptr<cdn::Tree> tree = make_tree(t, root);
    if (!tree) return;
    std::string err;
    NoBackend backend;
    GameServer game(backend, GameOptions{});
    HttpRouter router;
    mount_cdn(router, tree);
    Loop loop(game, router);
    if (!loop.listen_http("127.0.0.1", 0, &err)) return t.fail("listen: %s", err.c_str());
    std::atomic<bool> stop{false};
    std::thread th([&] {
        while (!stop) loop.run_once(20);
    });
    // AssetPath = http://127.0.0.1:<port>/download, r_ver = the tree's revision (42)
    const std::string base = "http://127.0.0.1:" + std::to_string(loop.http_port()) + "/download/" + tree->revision() + "/Android/";
    t.expect_eq(tree->revision(), std::string("42"), "revision");
    int status = 0;
    std::string body;
    if (!http_get(base + "version.bin", &status, &body, &err)) t.fail("GET version.bin: %s", err.c_str());
    t.expect_eq(status, 200, "version.bin status");
    Value v = mp_decode(std::vector<uint8_t>(body.begin(), body.end()));
    const Value* me = v.find("assets") ? v.find("assets")->find("sqlite/basmaster.sqlite3") : nullptr;
    t.expect_eq(v.find("revision") ? v.find("revision")->s : "", std::string("42"), "served revision");
    if (!http_get(base + "sqlite/basmaster.sqlite3", &status, &body, &err) || status != 200) t.fail("GET master: %d %s", status, err.c_str());
    std::vector<uint8_t> enc(body.begin(), body.end());
    auto p = adld::decrypt("sqlite/basmaster.sqlite3", enc);
    if (!me || me->find("md5")->s != cdn::sha1_hex(p.data(), p.size()) || me->find("size")->u != enc.size())
        t.fail("the master doesn't match version.bin");
    if (p.size() < 16 || memcmp(p.data(), "SQLite format 3", 15) != 0) t.fail("the served master isn't SQLite");
    // its bundle, as the manifest lists it
    if (!http_get(base + "manifest/etc2/hi/version_latest_Individual.bin", &status, &body, &err) || status != 200) t.fail("GET manifest");
    Value mv = mp_decode(std::vector<uint8_t>(body.begin(), body.end()));
    const Value* b2 = mv.find("assets") ? mv.find("assets")->find("I/2/2.bin") : nullptr;
    if (!http_get(base + "I/2/2.bin", &status, &body, &err) || status != 200) t.fail("GET bundle");
    if (!b2 || b2->find("md5")->s != cdn::sha1_hex((const uint8_t*)body.data(), body.size())) t.fail("bundle SHA-1 != manifest md5");
    // the master/ spelling, and a 404
    if (!http_get("http://127.0.0.1:" + std::to_string(loop.http_port()) + "/master/42/version.bin", &status, &body, &err) || status != 200)
        t.fail("master/ path");
    if (!http_get(base + "no/such.file", &status, &body, &err) || status != 404) t.fail("404 expected, got %d", status);
    stop = true;
    th.join();
    remove_tree(root);
}

// The same router called in memory (HttpRouter::handle on make_request, the port's in-process
// server: port/src/native/api/server_cdn.cpp): files and bundles come back as a stream, read in
// small pieces here, with the bytes Tree::lookup gives; the socket loop's materialize() gives the
// same bytes.
NATIVE_TEST("net/cdn-in-memory") {
    std::string root = "/tmp/soa-cdn-test-" + std::to_string(getpid()) + "-mem";
    std::shared_ptr<cdn::Tree> tree = make_tree(t, root);
    if (!tree) return;
    HttpRouter router;
    mount_cdn(router, tree);
    const std::string base = "/download/" + tree->revision() + "/Android/";
    auto get = [&](const std::string& target, HttpResponse& r) {
        r = HttpResponse();
        router.handle(make_request("GET", target, {{"Host", "production-game.so-ana.com"}}), r);
    };
    // Reads the body (a stream in 7-byte pieces, or `body`).
    auto body_of = [&](HttpResponse& r, const char* what) {
        if (!r.stream) return r.body;
        std::string out;
        char buf[7];
        int64_t k;
        while ((k = r.stream->read(buf, sizeof buf)) > 0) out.append(buf, (size_t)k);
        if (k < 0) t.fail("%s: stream read error", what);
        if (out.size() != r.content_length())
            t.fail("%s: %zu bytes streamed, Content-Length %llu", what, out.size(), (unsigned long long)r.content_length());
        return out;
    };
    auto lookup = [&](const std::string& name) {
        cdn::Response lr;
        std::vector<uint8_t> b;
        if (!tree->lookup(base + name, lr) || !lr.read(b)) t.fail("lookup %s", name.c_str());
        return std::string(b.begin(), b.end());
    };
    HttpResponse r;
    for (const char* name : {"version.bin", "manifest/etc2/hi/version_latest_Individual.bin", "I/1/1.bin", "I/2/2.bin", "BG/x.aaf"}) {
        get(base + name, r);
        t.expect_eq(r.status, 200, name);
        bool streamed = r.stream != nullptr;
        // the bundles and the plain file stream; version.bin and the manifests are in memory
        t.expect_eq(streamed, std::string(name).find(".bin") == std::string::npos || std::string(name).rfind("I/", 0) == 0, name);
        std::string b = body_of(r, name);
        if (b != lookup(name)) t.fail("%s: the in-memory body != Tree::lookup's (%zu bytes)", name, b.size());
        // the socket loop's path: materialize gives the same bytes
        get(base + name, r);
        if (!r.materialize() || r.stream || r.body != b) t.fail("%s: materialize", name);
    }
    // the bundle's SHA-1 is the manifest's md5
    get(base + "manifest/etc2/hi/version_latest_Individual.bin", r);
    Value mv = mp_decode(std::vector<uint8_t>(r.body.begin(), r.body.end()));
    const Value* b2 = mv.find("assets") ? mv.find("assets")->find("I/2/2.bin") : nullptr;
    get(base + "I/2/2.bin", r);
    std::string bundle = body_of(r, "I/2/2.bin");
    if (!b2 || b2->find("md5")->s != cdn::sha1_hex((const uint8_t*)bundle.data(), bundle.size())) t.fail("bundle SHA-1 != manifest md5");
    // a query and a %-escape are handled as on the wire; a 404
    get(base + "version%2Ebin?x=1", r);
    t.expect_eq(r.status, 200, "escaped target");
    get(base + "no/such.file", r);
    t.expect_eq(r.status, 404, "404");
    remove_tree(root);
}

}  // namespace

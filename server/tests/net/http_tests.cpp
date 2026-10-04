// soa-server's HTTP pieces (server/net/http.h, http_server.h) and the bridge's JSON.
// cpp-httplib first (net/use_httplib.h: winsock2.h before windows.h): the server test talks to the server with its client.
#include "net/use_httplib.h"
#include <sys/stat.h>
#include <unistd.h>

#include <algorithm>
#include <memory>
#include <mutex>
#include <string>

#include "net/game.h"
#include "net/client.h"
#include "net/http.h"
#include "net/http_server.h"
#include "soaserver/native_test.h"

namespace {

using namespace soa::server::net;

// make_request: the target split at '?', the path URL-decoded, an absolute-form target's path.
NATIVE_TEST("net/http-request") {
    HttpRequest a = make_request("GET", "/Android/a%20b+c.bin?x=1", {{"connection", "close"}});
    t.expect_eq(a.path, std::string("/Android/a b c.bin"), "decoded path ('+' is a space)");
    t.expect_eq(a.query, std::string("x=1"), "query");
    t.expect_eq(*a.header("Connection"), std::string("close"), "header lookup ignores case");
    t.expect_eq(a.version, std::string("HTTP/1.1"), "version");
    HttpRequest b = make_request("GET", "http://example/Android/c", {}, {}, "HTTP/1.0");
    t.expect_eq(b.path, std::string("/Android/c"), "absolute-form target");
    t.expect_eq(b.version, std::string("HTTP/1.0"), "version");
    t.expect_eq(make_request("GET", "https://example").path, std::string("/"), "absolute-form without a path");
}

// The HTTP server (http_server.h) on a loopback port: GET, HEAD, POST bodies, 404, keep-alive (two
// requests on one connection), a streamed body whole and by Range (206), the log line's counts.
NATIVE_TEST("net/http-server") {
    // a 300,000-byte streamed body: byte k is k * 7 mod 251
    struct Counting : HttpBodyStream {
        uint64_t pos = 0;
        uint64_t size() const override { return 300000; }
        int64_t read(char* buf, size_t n) override {
            size_t k = (size_t)std::min<uint64_t>(n, size() - pos);
            for (size_t i = 0; i < k; i++) buf[i] = (char)((pos + i) * 7 % 251);
            pos += k;
            return (int64_t)k;
        }
    };
    std::string whole;
    for (uint64_t k = 0; k < 300000; k++) whole += (char)(k * 7 % 251);
    HttpRouter router;
    router.route("/s/", [](const HttpRequest& req, const std::string&, HttpResponse& r) {
        r.set_header("Content-Type", "application/octet-stream");
        r.stream = std::make_shared<Counting>();
        return true;
    });
    router.route("/echo", [](const HttpRequest& req, const std::string& rest, HttpResponse& r) {
        r.set_header("Content-Type", "text/plain");
        r.set_header("X-Method", req.method);
        r.body = req.method + " " + rest + " " + req.query + " " + req.body;
        return true;
    });
    std::mutex lock;
    HttpServer server(router, &lock);
    std::string err;
    if (!server.listen("127.0.0.1", 0, &err)) return t.fail("listen: %s", err.c_str());
    const std::string base = "http://127.0.0.1:" + std::to_string(server.port());
    int status = 0;
    std::string body;
    t.expect_eq(http_get(base + "/echo/a%20b?q=1", &status, &body, &err) && status == 200, true, "GET");
    t.expect_eq(body, std::string("GET /a b q=1 "), "GET reaches the router decoded");
    std::string post = std::string("{\"x\":1}") + '\0';  // a NUL-terminated body, as the bridge's
    t.expect_eq(http_post(base + "/echo", post, &status, &body, &err) && status == 200, true, "POST");
    t.expect_eq(body, "POST   " + post, "POST body intact");
    t.expect_eq(http_get(base + "/nothing", &status, &body, &err) && status == 404, true, "404");
    t.expect_eq(http_get(base + "/s/x", &status, &body, &err) && status == 200, true, "stream");
    t.expect_eq(body == whole, true, "streamed body whole");
    // keep-alive, HEAD and Range with one client
    httplib::Client cli("127.0.0.1", server.port());
    cli.set_keep_alive(true);
    auto h = cli.Head("/s/x");
    t.expect_eq(h && h->status == 200 && h->body.empty() && h->get_header_value("Content-Length") == "300000", true, "HEAD: length, no body");
    auto e = cli.Head("/echo");
    t.expect_eq(e && e->get_header_value("X-Method") == "HEAD", true, "HEAD reaches the router as HEAD");
    auto r = cli.Get("/s/x", httplib::Headers{{"Range", "bytes=100000-100099"}});
    t.expect_eq(r && r->status == 206 && r->body == whole.substr(100000, 100), true, "Range: 206 and the slice");
    auto tail = cli.Get("/s/x", httplib::Headers{{"Range", "bytes=-10"}});
    t.expect_eq(tail && tail->status == 206 && tail->body == whole.substr(299990), true, "suffix Range");
    auto again = cli.Get("/echo/k");
    t.expect_eq(again && again->status == 200 && again->get_header_value("Connection") != "close", true, "connection kept alive");
    server.stop();
    t.expect_eq(http_get(base + "/echo", &status, &body, &err), false, "stopped");
}

NATIVE_TEST("net/http-router-static") {
    std::string dir = "/tmp/soa-server-net-test-" + std::to_string(getpid());
    mkdir(dir.c_str(), 0755);
    mkdir((dir + "/sub").c_str(), 0755);
    FILE* f = fopen((dir + "/sub/file.bin").c_str(), "wb");
    fwrite("content", 1, 7, f);
    fclose(f);
    HttpRouter router;
    router.route("/Android/", static_files(dir));
    router.route("/", [](const HttpRequest&, const std::string& rest, HttpResponse& r) {
        if (rest != "hello") return false;
        r.body = "root";
        return true;
    });
    auto get = [&](const std::string& path) {
        HttpRequest q;
        q.method = "GET";
        q.path = path;
        HttpResponse r;
        router.handle(q, r);
        return r;
    };
    t.expect_eq(get("/Android/sub/file.bin").body, std::string("content"), "static file");
    t.expect_eq(get("/Android/sub/../sub/file.bin").status, 404, "'..' refused");
    t.expect_eq(get("/Android//etc/passwd").status, 404, "absolute refused");
    t.expect_eq(get("/Android/missing").status, 404, "missing");
    t.expect_eq(get("/hello").body, std::string("root"), "shorter prefix");
    unlink((dir + "/sub/file.bin").c_str());
    rmdir((dir + "/sub").c_str());
    rmdir(dir.c_str());
}

NATIVE_TEST("net/gzip-json") {
    std::string s;
    for (int i = 0; i < 2000; i++) s += (char)t.rand_int(0, 255);
    std::string z = gzip(s);
    t.expect_eq(z.size() > 10 && (uint8_t)z[0] == 0x1f && (uint8_t)z[1] == 0x8b, true, "gzip magic");
    t.expect_eq(gunzip(z), s, "round trip");
    t.expect_eq(gunzip("not gzip"), std::string(), "garbage");
    // the client's bridge POST: printf'd JSON plus a NUL (CApiNotify::OnResultStart)
    std::string body = std::string("{\"UUID\":\"3f2a-x\",\"deviceType\":\"2\",\"nativeToken\":\"abc\\\"d\"}") + '\0';
    t.expect_eq(json_string_field(body, "UUID"), std::string("3f2a-x"), "UUID");
    t.expect_eq(json_string_field(body, "deviceType"), std::string("2"), "deviceType");
    t.expect_eq(json_string_field(body, "nativeToken"), std::string("abc\"d"), "escaped quote");
    t.expect_eq(json_string_field("{\"n\": 12}", "n"), std::string("12"), "bare number");
    t.expect_eq(json_string_field(body, "missing"), std::string(), "missing");
}

}  // namespace

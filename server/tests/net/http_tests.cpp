// soa-server's HTTP pieces (server/net/http.h) and the bridge's JSON.
#include <sys/stat.h>
#include <unistd.h>

#include <string>

#include "net/game.h"
#include "net/http.h"
#include "soaserver/native_test.h"

namespace {

using namespace soa::server::net;

NATIVE_TEST("net/http-parser") {
    std::string reqs =
        "POST /bridge HTTP/1.1\r\nHost: x\r\nContent-Length: 5\r\n\r\nhello"
        "GET /Android/a%20b.bin?x=1 HTTP/1.1\r\nconnection: close\r\n\r\n"
        "GET http://example/Android/c HTTP/1.0\r\n\r\n";
    // byte by byte, then all at once: the same three requests
    for (int mode = 0; mode < 2; mode++) {
        HttpParser p;
        std::vector<HttpRequest> got;
        auto drain = [&] {
            HttpRequest r;
            HttpParser::Result res;
            while ((res = p.next(&r)) == HttpParser::kRequest) got.push_back(r);
            if (res == HttpParser::kBad) t.fail("bad");
        };
        if (mode == 0)
            for (char c : reqs) p.feed(&c, 1), drain();
        else p.feed(reqs.data(), reqs.size()), drain();
        if (got.size() != 3) {
            t.fail("mode %d: %zu requests", mode, got.size());
            continue;
        }
        t.expect_eq(got[0].method, std::string("POST"), "method");
        t.expect_eq(got[0].body, std::string("hello"), "body");
        t.expect_eq(got[1].path, std::string("/Android/a b.bin"), "decoded path");
        t.expect_eq(got[1].query, std::string("x=1"), "query");
        t.expect_eq(*got[1].header("Connection"), std::string("close"), "header lookup ignores case");
        t.expect_eq(got[2].path, std::string("/Android/c"), "absolute-form target");
        t.expect_eq(got[2].version, std::string("HTTP/1.0"), "version");
    }
    HttpParser bad;
    std::string b = "NONSENSE\r\n\r\n";
    bad.feed(b.data(), b.size());
    HttpRequest r;
    t.expect_eq((int)bad.next(&r), (int)HttpParser::kBad, "malformed request line");
    std::string resp = serialize_response(HttpResponse{200, {{"Content-Type", "text/plain"}}, "abc"}, true);
    t.expect_eq(resp, std::string("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\nContent-Length: 3\r\nConnection: keep-alive\r\n\r\nabc"),
                "response bytes");
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

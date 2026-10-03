// The Java HTTP client of the 3.7.0 client (emulator/README.md "Networking"): a host HTTP/1.1
// client behind the jb.Aska.AskaActivity HTTP methods, registered by platform370::install
// (Config::http) through the runtime's extension point (jni::add_class_installer +
// Vm::override_method). The runtime refuses them (offline).
//
// The native side (Aska::Yayoi::NativeHttpClient::_doRequest @026a4f40 in 3.7.0, decompiled with
// tools/decomp.sh --v370) runs one request on its network thread, blocking, calling the activity:
//   1. SetHttpUserAgent(String) -> Boolean, when a user agent is set;
//   2. HttpRequest(String url, int port, String body, boolean post) -> int: url is the full URL
//      (for a GET with parameters: url + '?' + params), port the URI's port, body the POST
//      content (the native MakeParamString: SetContent's bytes, or the url-encoded params), post
//      true for POST. A result < 1 is "unexpected error";
//   3. GetHttpHeader() -> String: the response's header fields, parsed by
//      HttpProtocol::ParseHeader: it starts the native HTTP parser (HttpProtocol::Deserialize) in
//      its header-field state (2), so the string is the "Name: value" lines only, each ending in
//      "\r\n", without the status line (a line without ':' ends the header there, so a status
//      line first would hide every field). null = "response header is nothing";
//   4. GetStatusCode() -> int (stored in the response; the head's status line also carries it);
//   5. ReadHttpResponse(byte[] buf) -> int, in a loop: n >= 0 bytes of the body were put in buf
//      (fed to HttpProtocol::ParseMessageBody), < 0 = the end of the body (the request then
//      completes). The buffer is AppNetworkCommonSettingProxy::GetTcpReceiveSize() bytes;
//   6. AbortHttpRequest() -> Boolean when the request was cancelled meanwhile.
// So HttpRequest performs the exchange up to the response head; ReadHttpResponse then streams
// a Content-Length body from the connection (a chunked or connection-delimited body is read whole
// in HttpRequest).
//
// The body is handed over as it came, except a chunked transfer encoding, which is decoded (and
// the head then says Content-Length instead): the native parser then sees one plain body, as
// Java's HttpURLConnection delivered it. Content-Encoding is left alone (the native side knows
// gzip: HttpProtocoledData::ParseContentEncoding); no Accept-Encoding is sent.
//
// Where requests go: a URL whose host is mapped (net_370.cpp: production-game.so-ana.com and
// --map-host names) goes to the host's HttpBackend when one is installed (set_http_backend: the
// port's in-process server; a call, no socket, the body read from the backend's reader as the
// client asks), else to soa-server's HTTP port (--http, default <server host>:44380) as plain
// HTTP, also for https:// (soa-server has no TLS). https:// to the server's own address is
// plain HTTP too. Other http:// URLs are fetched as they are; other https:// URLs fail (no TLS
// here; the original services are gone).
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <poll.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <memory>
#include <string>

#include "core/log.h"
#include "internal.h"
#include "jni/jvm.h"
#include "platform370/platform370.h"

namespace soa::platform370::detail {
namespace {

using jni::Args;
using jni::Impl;
using jni::Object;
using jni::Vm;

const char* const AA = "jb/Aska/AskaActivity";
constexpr int kConnectTimeoutMs = 15000, kReadTimeoutMs = 60000;  // assumption (d)

// One request at a time per calling thread (the native client runs its requests on its own
// network thread; the Java object it calls held one connection).
struct Exchange {
    bool done = false;  // a response is ready
    int status = 0;
    std::string head;   // the header fields (GetHttpHeader)
    std::string body;   // the body read so far and not yet handed out (from `pos`)
    size_t pos = 0;
    int fd = -1;            // streaming: the connection the rest of the body comes from
    std::unique_ptr<HttpBodyReader> reader;  // streaming (the backend): where the rest comes from
    u64 remaining = 0;      // streaming: body bytes still to receive on fd / from reader
    std::string url;        // for the log
};
thread_local Exchange t_x;
// Ends the calling thread's exchange (closes a streaming connection).
void reset_exchange() {
    if (t_x.fd >= 0) close(t_x.fd);
    t_x = Exchange{};
}
std::string g_user_agent = "Dalvik/2.1.0 (Linux; U; Android 9)";  // until SetHttpUserAgent; assumption (d)

struct Url {
    std::string scheme, host, path;
    int port = 0;
};
bool parse_url(const std::string& u, Url& out) {
    size_t s = u.find("://");
    if (s == std::string::npos) return false;
    out.scheme = u.substr(0, s);
    for (auto& ch : out.scheme) ch = (char)tolower((unsigned char)ch);
    size_t h = s + 3, p = u.find_first_of("/?#", h);
    std::string auth = u.substr(h, p == std::string::npos ? std::string::npos : p - h);
    out.path = p == std::string::npos ? "/" : u.substr(p);
    if (out.path[0] != '/') out.path = "/" + out.path;
    size_t at = auth.rfind('@');
    if (at != std::string::npos) auth = auth.substr(at + 1);
    if (!auth.empty() && auth[0] == '[') {  // [v6]:port
        size_t e = auth.find(']');
        out.host = auth.substr(1, e - 1);
        if (e + 1 < auth.size() && auth[e + 1] == ':') out.port = atoi(auth.c_str() + e + 2);
    } else {
        size_t c = auth.rfind(':');
        out.host = auth.substr(0, c);
        if (c != std::string::npos) out.port = atoi(auth.c_str() + c + 1);
    }
    return !out.host.empty();
}

int connect_to(const std::string& host, int port, std::string& err) {
    addrinfo hints{}, *res = nullptr;
    hints.ai_socktype = SOCK_STREAM;
    int r = getaddrinfo(host.c_str(), std::to_string(port).c_str(), &hints, &res);
    if (r) {
        err = std::string("resolve: ") + gai_strerror(r);
        return -1;
    }
    int fd = -1;
    for (addrinfo* a = res; a; a = a->ai_next) {
        fd = socket(a->ai_family, a->ai_socktype | SOCK_CLOEXEC | SOCK_NONBLOCK, a->ai_protocol);
        if (fd < 0) continue;
        if (connect(fd, a->ai_addr, a->ai_addrlen) == 0) break;
        if (errno == EINPROGRESS) {
            pollfd p{fd, POLLOUT, 0};
            int e = 0;
            socklen_t el = sizeof e;
            if (poll(&p, 1, kConnectTimeoutMs) == 1 && getsockopt(fd, SOL_SOCKET, SO_ERROR, &e, &el) == 0 && e == 0) break;
            err = e ? strerror(e) : "connect timeout";
        } else {
            err = strerror(errno);
        }
        close(fd);
        fd = -1;
    }
    freeaddrinfo(res);
    if (fd >= 0) fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) & ~O_NONBLOCK);
    if (fd >= 0) {
        timeval tv{kReadTimeoutMs / 1000, 0};
        setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
        setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof tv);
    }
    return fd;
}

bool send_all(int fd, const std::string& s) {
    size_t off = 0;
    while (off < s.size()) {
        ssize_t n = send(fd, s.data() + off, s.size() - off, MSG_NOSIGNAL);
        if (n <= 0) return false;
        off += (size_t)n;
    }
    return true;
}

std::string header_value(const std::string& head, const char* name) {
    size_t i = head.find("\r\n");
    size_t nl = strlen(name);
    while (i != std::string::npos && i + 2 < head.size()) {
        size_t s = i + 2, e = head.find("\r\n", s);
        if (e == std::string::npos) break;
        std::string line = head.substr(s, e - s);
        if (line.size() > nl && line[nl] == ':' && !strncasecmp(line.c_str(), name, nl)) {
            size_t v = nl + 1;
            while (v < line.size() && line[v] == ' ') v++;
            return line.substr(v);
        }
        i = e;
    }
    return "";
}

// Decodes a chunked body; false when malformed.
bool dechunk(const std::string& in, std::string& out) {
    size_t p = 0;
    out.clear();
    for (;;) {
        size_t e = in.find("\r\n", p);
        if (e == std::string::npos) return false;
        unsigned long n = strtoul(in.substr(p, e - p).c_str(), nullptr, 16);
        p = e + 2;
        if (n == 0) return true;
        if (p + n > in.size()) return false;
        out.append(in, p, n);
        p += n + 2;
    }
}

std::atomic<HttpBackend*> g_backend{nullptr};

// The header fields handed to the native parser (GetHttpHeader): `fields` without
// Transfer-Encoding / Content-Length / Connection, then the body's real length.
std::string client_head(const std::vector<std::pair<std::string, std::string>>& fields, u64 length) {
    std::string out;
    for (auto& [k, v] : fields) {
        if (!strcasecmp(k.c_str(), "Transfer-Encoding") || !strcasecmp(k.c_str(), "Content-Length") || !strcasecmp(k.c_str(), "Connection"))
            continue;
        out += k + ": " + v + "\r\n";
    }
    return out + "Content-Length: " + std::to_string(length) + "\r\n";
}

// The exchange with the host's in-process server (set_http_backend): the request the socket path
// would send, as a call; fills t_x like exchange().
bool exchange_backend(HttpBackend& be, const std::string& url, const Url& u, const std::string& body, bool post) {
    auto t0 = std::chrono::steady_clock::now();
    HttpBackendRequest rq;
    rq.method = post ? "POST" : "GET";
    rq.url = url;
    rq.host = u.host;
    rq.target = u.path;
    rq.headers = {{"Host", u.host + (u.port ? ":" + std::to_string(u.port) : "")}, {"User-Agent", g_user_agent}, {"Connection", "close"}};
    if (post) {
        rq.headers.emplace_back("Content-Type", "application/x-www-form-urlencoded");  // as the socket path: assumption (d)
        rq.headers.emplace_back("Content-Length", std::to_string(body.size()));
        rq.body = body;
    }
    HttpBackendResponse rs;
    if (!be.handle(rq, rs)) {
        LOGW("http", "%s %s (in-process): no response", rq.method.c_str(), url.c_str());
        return false;
    }
    if (rs.body.size() > rs.length) rs.body.resize(rs.length);
    t_x.status = rs.status;
    t_x.head = client_head(rs.headers, rs.length);
    t_x.remaining = rs.length - rs.body.size();
    if (t_x.remaining) {
        if (!rs.reader) {
            LOGW("http", "%s %s (in-process): %llu bytes promised, no reader", rq.method.c_str(), url.c_str(), (unsigned long long)t_x.remaining);
            t_x = Exchange{};
            return false;
        }
        t_x.reader = std::move(rs.reader);
    }
    t_x.body = std::move(rs.body);
    t_x.done = true;
    t_x.url = url;
    LOGI("http", "%s %s -> in-process: %d, %llu bytes (head in %.0f ms)", rq.method.c_str(), url.c_str(), t_x.status, (unsigned long long)rs.length,
         std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count());
    return true;
}

// The whole exchange; fills t_x. false (and a log line) on any failure.
bool exchange(const std::string& url, int port_arg, const std::string& body, bool post) {
    reset_exchange();
    Url u;
    if (!parse_url(url, u)) {
        LOGW("http", "HttpRequest(%s): not a URL", url.c_str());
        return false;
    }
    auto& cfg = net_config();
    std::string host = u.host;
    int port = u.port ? u.port : port_arg ? port_arg : (u.scheme == "https" ? 443 : 80);
    std::string mapped = mapped_address(u.host);
    if (!mapped.empty()) {
        // A mapped host: the host's in-process server when it installed one (no socket), else
        // soa-server's HTTP server, plain HTTP whatever the scheme says.
        if (HttpBackend* be = g_backend.load()) return exchange_backend(*be, url, u, body, post);
        host = cfg.http_host.empty() ? mapped : cfg.http_host;
        port = cfg.http_port;
    } else if (u.scheme == "https") {
        if (u.host != cfg.server_host && u.host != cfg.http_host) {
            LOGW("http", "HttpRequest(%s): https to an unmapped host isn't supported (no TLS; --map-host it)", url.c_str());
            return false;
        }
        if (!u.port) port = cfg.http_port;
    } else if (u.scheme != "http") {
        LOGW("http", "HttpRequest(%s): unsupported scheme", url.c_str());
        return false;
    }
    std::string err;
    auto t0 = std::chrono::steady_clock::now();
    int fd = connect_to(host, port, err);
    if (fd < 0) {
        LOGW("http", "%s %s: connect %s:%d failed: %s", post ? "POST" : "GET", url.c_str(), host.c_str(), port, err.c_str());
        return false;
    }
    std::string req = std::string(post ? "POST " : "GET ") + u.path + " HTTP/1.1\r\n";
    req += "Host: " + u.host + (u.port ? ":" + std::to_string(u.port) : "") + "\r\n";
    req += "User-Agent: " + g_user_agent + "\r\n";
    req += "Connection: close\r\n";
    if (post) {
        // HttpURLConnection's default for a POST with output: assumption (d).
        req += "Content-Type: application/x-www-form-urlencoded\r\n";
        req += "Content-Length: " + std::to_string(body.size()) + "\r\n";
    }
    req += "\r\n";
    if (post) req += body;
    std::string resp;
    bool ok = send_all(fd, req);
    size_t he = std::string::npos;
    if (ok) {
        // The head first.
        char buf[65536];
        while ((he = resp.find("\r\n\r\n")) == std::string::npos) {
            ssize_t n = recv(fd, buf, sizeof buf, 0);
            if (n < 0 && errno == EINTR) continue;
            if (n <= 0) {
                err = n < 0 ? strerror(errno) : "connection closed";
                break;
            }
            resp.append(buf, (size_t)n);
        }
    } else {
        err = strerror(errno);
    }
    if (!ok || he == std::string::npos || resp.compare(0, 5, "HTTP/") != 0) {
        close(fd);
        LOGW("http", "%s %s (%s:%d): no response (%s)", post ? "POST" : "GET", url.c_str(), host.c_str(), port, err.empty() ? "malformed" : err.c_str());
        return false;
    }
    std::string head = resp.substr(0, he + 2), rbody = resp.substr(he + 4);
    size_t sp = head.find(' ');
    t_x.status = sp == std::string::npos ? 0 : atoi(head.c_str() + sp + 1);
    std::string cl = header_value(head, "Content-Length");
    bool chunked = !strcasecmp(header_value(head, "Transfer-Encoding").c_str(), "chunked");
    u64 length = 0;
    if (!chunked && !cl.empty()) {
        // Streamed: ReadHttpResponse receives the rest of the body as the client asks for it
        // (bundles run to hundreds of MB).
        length = strtoull(cl.c_str(), nullptr, 10);
        if (rbody.size() > length) rbody.resize(length);
        t_x.remaining = length - rbody.size();
        if (t_x.remaining) t_x.fd = fd;
        else close(fd);
    } else {
        // Chunked, or delimited by the end of the connection: read it whole.
        char buf[65536];
        for (;;) {
            ssize_t n = recv(fd, buf, sizeof buf, 0);
            if (n < 0 && errno == EINTR) continue;
            if (n <= 0) break;
            rbody.append(buf, (size_t)n);
        }
        close(fd);
        if (chunked) {
            std::string dec;
            if (!dechunk(rbody, dec)) {
                LOGW("http", "%s: malformed chunked body", url.c_str());
                t_x = Exchange{};
                return false;
            }
            rbody.swap(dec);
        }
        length = rbody.size();
    }
    // The header fields handed to the native parser (GetHttpHeader): the response's, without
    // the status line and Transfer-Encoding / Content-Length / Connection, then the body's real
    // length.
    std::string out;
    size_t i = head.find("\r\n") + 2;
    while (i < head.size()) {
        size_t e = head.find("\r\n", i);
        std::string line = head.substr(i, e - i);
        i = e + 2;
        if (line.find(':') == std::string::npos || !strncasecmp(line.c_str(), "Transfer-Encoding:", 18) ||
            !strncasecmp(line.c_str(), "Content-Length:", 15) || !strncasecmp(line.c_str(), "Connection:", 11))
            continue;
        out += line + "\r\n";
    }
    out += "Content-Length: " + std::to_string(length) + "\r\n";
    t_x.head = out;
    t_x.body = std::move(rbody);
    t_x.done = true;
    t_x.url = url;
    LOGI("http", "%s %s -> %s:%d: %d, %llu bytes (head in %.0f ms)", post ? "POST" : "GET", url.c_str(), host.c_str(), port, t_x.status,
         (unsigned long long)length, std::chrono::duration<double, std::milli>(std::chrono::steady_clock::now() - t0).count());
    return true;
}

}  // namespace

void install_http(Vm& vm) {
    // SetHttpUserAgent(String) -> Boolean: the User-Agent of the following requests.
    vm.override_method(AA, "SetHttpUserAgent", "(Ljava/lang/String;)Ljava/lang/Boolean;", [&vm](Object*, const Args& a, const Impl&) -> u64 {
        g_user_agent = jni::jstr(a[0]);
        LOGD("http", "SetHttpUserAgent(%s)", g_user_agent.c_str());
        return (u64)vm.boolean(true);
    });
    vm.override_method(AA, "HttpRequest", "(Ljava/lang/String;ILjava/lang/String;Z)I", [](Object*, const Args& a, const Impl&) -> u64 {
        std::string url = jni::jstr(a[0]), body = jni::jstr(a[2]);
        bool post = a[3] & 1;
        return exchange(url, (int)(s32)a[1], body, post) ? 1 : 0;
    });
    vm.override_method(AA, "GetStatusCode", "()I", [](Object*, const Args&, const Impl&) -> u64 { return (u64)(s64)(t_x.done ? t_x.status : -1); });
    vm.override_method(AA, "GetHttpHeader", "()Ljava/lang/String;", [&vm](Object*, const Args&, const Impl&) -> u64 {
        return t_x.done ? (u64)vm.str(t_x.head) : 0;
    });
    // ReadHttpResponse(byte[]) -> int: the next part of the body (> 0 bytes), -1 at its end.
    vm.override_method(AA, "ReadHttpResponse", "([B)I", [](Object*, const Args& a, const Impl&) -> u64 {
        auto* arr = (jni::Array*)a[0];
        if (!t_x.done || !arr || !arr->length) return (u64)(s64)-1;
        if (arr->data.size() < arr->length) arr->data.resize(arr->length);
        if (t_x.pos < t_x.body.size()) {
            size_t n = std::min(arr->length, t_x.body.size() - t_x.pos);
            memcpy(arr->data.data(), t_x.body.data() + t_x.pos, n);
            t_x.pos += n;
            return (u64)n;
        }
        if (t_x.reader && t_x.remaining) {
            // The in-process server's stream.
            s64 n = t_x.reader->read(arr->data.data(), (size_t)std::min<u64>(arr->length, t_x.remaining));
            if (n <= 0) {
                // A short body: the client's size / SHA-1 checks catch it.
                LOGW("http", "%s: the body ended %llu bytes early (%s)", t_x.url.c_str(), (unsigned long long)t_x.remaining,
                     n < 0 ? "read error" : "end of stream");
                t_x.reader.reset();
                return (u64)(s64)-1;
            }
            t_x.remaining -= (u64)n;
            if (!t_x.remaining) t_x.reader.reset();
            return (u64)n;
        }
        if (t_x.fd < 0 || !t_x.remaining) return (u64)(s64)-1;
        for (;;) {
            ssize_t n = recv(t_x.fd, arr->data.data(), (size_t)std::min<u64>(arr->length, t_x.remaining), 0);
            if (n < 0 && errno == EINTR) continue;
            if (n <= 0) {
                // A short body: the client's size / SHA-1 checks catch it.
                LOGW("http", "%s: the body ended %llu bytes early (%s)", t_x.url.c_str(), (unsigned long long)t_x.remaining,
                     n < 0 ? strerror(errno) : "connection closed");
                close(t_x.fd);
                t_x.fd = -1;
                return (u64)(s64)-1;
            }
            t_x.remaining -= (u64)n;
            if (!t_x.remaining) {
                close(t_x.fd);
                t_x.fd = -1;
            }
            return (u64)n;
        }
    });
    vm.override_method(AA, "AbortHttpRequest", "()Ljava/lang/Boolean;", [&vm](Object*, const Args&, const Impl&) -> u64 {
        LOGI("http", "AbortHttpRequest()");
        reset_exchange();
        return (u64)vm.boolean(true);
    });
    vm.override_method(AA, "CloseHttpRequest", "()V", [](Object*, const Args&, const Impl&) -> u64 {
        reset_exchange();
        return 0;
    });
    vm.override_method(AA, "SetHttpProxy", "(ILjava/lang/String;)V", [](Object*, const Args& a, const Impl&) -> u64 {
        LOGI("http", "SetHttpProxy(%d, %s) ignored (direct connections)", (int)(s32)a[0], jni::jstr(a[1]).c_str());
        return 0;
    });
}

}  // namespace soa::platform370::detail

namespace soa::platform370 {
void set_http_backend(HttpBackend* backend) {
    detail::g_backend.store(backend);
    LOGI("http", "HTTP backend: %s", backend ? "in-process (no sockets for mapped hosts)" : "sockets");
}
HttpBackend* http_backend() { return detail::g_backend.load(); }
}  // namespace soa::platform370

// soa-server's HTTP requests, responses and router (http.h). Our code.
#include "http.h"

#include <fcntl.h>
#include <strings.h>
#include <sys/stat.h>
#include <unistd.h>
#include <zlib.h>

#include <algorithm>
#include <cstring>

namespace soa::server::net {

const std::string* HttpRequest::header(const std::string& name) const {
    for (auto& h : headers)
        if (!strcasecmp(h.first.c_str(), name.c_str())) return &h.second;
    return nullptr;
}

void HttpResponse::set_header(const std::string& name, const std::string& value) {
    for (auto& h : headers)
        if (!strcasecmp(h.first.c_str(), name.c_str())) {
            h.second = value;
            return;
        }
    headers.emplace_back(name, value);
}

void HttpRouter::route(const std::string& prefix, HttpHandler handler) {
    routes_.emplace_back(prefix, std::move(handler));
    std::stable_sort(routes_.begin(), routes_.end(), [](auto& a, auto& b) { return a.first.size() > b.first.size(); });
}

void HttpRouter::handle(const HttpRequest& req, HttpResponse& resp) const {
    for (auto& [prefix, h] : routes_) {
        if (req.path.compare(0, prefix.size(), prefix) != 0) continue;
        if (h(req, req.path.substr(prefix.size()), resp)) return;
    }
    resp = HttpResponse();
    resp.status = 404;
    resp.set_header("Content-Type", "text/plain");
    resp.body = "not found\n";
}

HttpRequest make_request(std::string method, std::string target, std::vector<std::pair<std::string, std::string>> headers, std::string body,
                         std::string version) {
    HttpRequest r;
    r.method = std::move(method);
    r.target = std::move(target);
    r.version = std::move(version);
    r.headers = std::move(headers);
    r.body = std::move(body);
    size_t q = r.target.find('?');
    std::string path = r.target.substr(0, q);
    // an absolute-form target (a proxy-style request): keep only the path
    if (path.rfind("http://", 0) == 0 || path.rfind("https://", 0) == 0) {
        size_t s = path.find('/', path.find("//") + 2);
        path = s == std::string::npos ? "/" : path.substr(s);
    }
    r.path = url_decode(path);
    r.query = q == std::string::npos ? "" : r.target.substr(q + 1);
    return r;
}

std::string url_decode(const std::string& s) {
    std::string o;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == '%' && i + 2 < s.size() && isxdigit((unsigned char)s[i + 1]) && isxdigit((unsigned char)s[i + 2])) {
            o += (char)strtoul(s.substr(i + 1, 2).c_str(), nullptr, 16);
            i += 2;
        } else {
            o += s[i];
        }
    }
    return o;
}

HttpHandler static_files(std::string dir) {
    return [dir = std::move(dir)](const HttpRequest& req, const std::string& rest, HttpResponse& resp) {
        if (req.method != "GET" && req.method != "HEAD") return false;
        if (rest.empty() || rest[0] == '/' || rest.find("..") != std::string::npos || rest.find('\0') != std::string::npos) return false;
        std::string p = dir + "/" + rest;
        struct stat st;
        if (stat(p.c_str(), &st) != 0 || !S_ISREG(st.st_mode)) return false;
        int fd = open(p.c_str(), O_RDONLY | O_CLOEXEC);
        if (fd < 0) return false;
        std::string body;
        body.resize((size_t)st.st_size);
        size_t got = 0;
        while (got < body.size()) {
            ssize_t k = read(fd, &body[got], body.size() - got);
            if (k <= 0) break;
            got += (size_t)k;
        }
        close(fd);
        if (got != body.size()) return false;
        resp.status = 200;
        resp.set_header("Content-Type", "application/octet-stream");
        resp.body = std::move(body);
        return true;
    };
}

std::string gzip(const std::string& data) {
    z_stream z = {};
    if (deflateInit2(&z, Z_DEFAULT_COMPRESSION, Z_DEFLATED, 15 + 16, 8, Z_DEFAULT_STRATEGY) != Z_OK) return "";
    std::string out;
    out.resize(deflateBound(&z, data.size()) + 32);
    z.next_in = (Bytef*)data.data();
    z.avail_in = (uInt)data.size();
    z.next_out = (Bytef*)&out[0];
    z.avail_out = (uInt)out.size();
    int r = deflate(&z, Z_FINISH);
    out.resize(z.total_out);
    deflateEnd(&z);
    return r == Z_STREAM_END ? out : "";
}

std::string gunzip(const std::string& data) {
    z_stream z = {};
    if (inflateInit2(&z, 15 + 16) != Z_OK) return "";
    std::string out;
    char buf[16384];
    z.next_in = (Bytef*)data.data();
    z.avail_in = (uInt)data.size();
    int r;
    do {
        z.next_out = (Bytef*)buf;
        z.avail_out = sizeof buf;
        r = inflate(&z, Z_NO_FLUSH);
        if (r != Z_OK && r != Z_STREAM_END) break;
        out.append(buf, sizeof buf - z.avail_out);
    } while (r != Z_STREAM_END);
    inflateEnd(&z);
    return r == Z_STREAM_END ? out : "";
}

}  // namespace soa::server::net

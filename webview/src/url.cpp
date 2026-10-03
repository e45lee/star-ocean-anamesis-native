// URL resolution (soawebview/page.h resolve_url), from the Dragalia Lost project's renderer.
#include <litehtml.h>
#include <litehtml/url.h>

#include <string>
#include <vector>

#include "soawebview/page.h"

namespace soa::webview {

namespace lh = litehtml;

std::string resolve_url(const std::string& base, const std::string& ref) {
    if (ref.empty()) return base;
    if (base.empty()) return ref;
    // file:///path: litehtml's url drops the empty authority ("file:/path"), so resolve it as a
    // path on a stand-in host and put the scheme back.
    if (base.rfind("file://", 0) == 0 && ref.find("://") == std::string::npos) {
        std::string r = resolve_url("http://file.invalid" + base.substr(7), ref);
        const std::string host = "http://file.invalid";
        return r.rfind(host, 0) == 0 ? "file://" + r.substr(host.size()) : r;
    }
    std::string u = lh::resolve(lh::url(base), lh::url(ref)).str();
    // RFC 3986 remove_dot_segments on the path (litehtml leaves "a/../b" as is)
    size_t ps = u.find("://");
    ps = ps == std::string::npos ? 0 : u.find('/', ps + 3);
    if (ps == std::string::npos) return u;
    size_t pe = u.find_first_of("?#", ps);
    std::string path = u.substr(ps, pe == std::string::npos ? std::string::npos : pe - ps), tail = pe == std::string::npos ? "" : u.substr(pe);
    std::vector<std::string> segs;
    size_t i = 1;
    bool dir = false;
    while (i <= path.size()) {
        size_t j = path.find('/', i);
        if (j == std::string::npos) j = path.size();
        std::string seg = path.substr(i, j - i);
        dir = j < path.size();
        if (seg == "..") {
            if (!segs.empty()) segs.pop_back();
            dir = true;
        } else if (seg == ".") {
            dir = true;
        } else {
            segs.push_back(seg);
        }
        i = j + 1;
    }
    std::string np;
    for (auto& sg : segs) np += "/" + sg;
    if (dir && (np.empty() || np.back() != '/') && (segs.empty() || !segs.back().empty())) np += "/";
    if (np.empty()) np = "/";
    return u.substr(0, ps) + np + tail;
}

}  // namespace soa::webview

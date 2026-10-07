// The stubs' one shape (ext::add_stub, soaserver/ext.h; port code, not guest behaviour): a method
// the local server answers without implementing it (docs/unimplemented-apis.md part 3, Decisions:
// the social calls of a server without other players, the debug APIs).
#include <string>

#include "core/log.h"
#include "soaserver/ext.h"
#include "soaserver/server.h"

namespace soa::server::ext {

namespace {

// The request's arguments in short form: integers, strings (quoted, cut at 32 bytes) and vectors
// (their length and first values), as one line.
std::string short_args(const Request& r) {
    std::string out;
    for (u64 v : r.ints) out += " " + std::to_string(v);
    for (const std::string& s : r.strs) out += " \"" + (s.size() > 32 ? s.substr(0, 32) + "..." : s) + "\"";
    for (const std::vector<u64>& v : r.vecs) {
        out += " [";
        for (size_t i = 0; i < v.size() && i < 4; i++) out += (i ? "," : "") + std::to_string(v[i]);
        if (v.size() > 4) out += ",... (" + std::to_string(v.size()) + ")";
        out += "]";
    }
    return out;
}

}  // namespace

void add_stub(std::initializer_list<const char*> methods, StubData data, const char* file, int line) {
    add_api(
        methods,
        [data](Ctx& ctx, const Request& r) {
            const std::string args = short_args(r);
            LOGW("server", "stub: %s (fid %08x) called; answered success, nothing stored (docs/unimplemented-apis.md)%s%s", r.method.c_str(), r.fid,
                 args.empty() ? "" : ";", args.c_str());
            Value d = Value::object();
            d["Time"] = format_time(ctx.now());
            if (data) data(d);
            return body(d);
        },
        file, line);
}

}  // namespace soa::server::ext

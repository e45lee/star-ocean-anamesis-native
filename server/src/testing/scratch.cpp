// The library's scratch servers for tests (testing/scratch.h). Library code.
#include "testing/scratch.h"

#include <sqlite3.h>
#include <unistd.h>

#include <ctime>
#include <functional>

#include "core/log.h"
#include "core/time.h"  // parse_time
#include "soaserver/config.h"
#include "soaserver/master_source.h"
#include "soaserver/scratch.h"
#include "soaserver/testing.h"

namespace soa::server {

ext::Sql* test_master() {
    static ext::Sql m;
    static bool tried = false;
    if (!tried) {
        tried = true;
        std::string p = master_source::resolve();  // the repo's, else derived (soaserver/master_source.h)
        if (!p.empty()) m.open(p, true);
    }
    return m.h ? &m : nullptr;
}

bool scratch_inputs(std::string& master, std::string& save) {
    master = master_source::resolve();
    save = find_repo_file("server/tests/fixtures/test-seed.xml");
    if (!master.empty() && !save.empty()) return true;
    std::string why;
    if (master.empty()) why += "no 3.7.0 master DB (data/basmaster-3.7.0.sqlite3, decrypted from the 3.7.0 download)";
    if (save.empty()) why += std::string(why.empty() ? "" : "; ") + "no test seed save (server/tests/fixtures/test-seed.xml; tools/make_test_seed.py)";
    LOGE("server", "scratch-server test data missing: %s", why.c_str());
    if (testing::Context* t = testing::current()) t->fail("scratch-server test data missing: %s", why.c_str());
    return false;
}

ScratchServer::ScratchServer(u64 seed, Options opt) : own_test_options_(opt.own_test_options) {
    std::string save, master;
    if (!scratch_inputs(master, save)) return;  // (fails the running library test)
    inputs = true;
    if (own_test_options_) {
        ServerConfig& c = config();
        saved_fail_ = c.fail;
        saved_surprise_ = c.surprise;
        c.fail.clear();
        c.surprise = false;
    }
    static int n = 0;
    sv.live = false;
    db = "/tmp/soa-server-scratch-" + std::to_string(getpid()) + "-" + std::to_string(n++) + ".sqlite3";
    for (const char* suffix : {"", "-wal", "-shm"}) unlink((db + suffix).c_str());
    ok = sv.m.open(master, true) && sv.open_state(db, seed, save);
    if (opt.pools) sv.pools.open();
}
ScratchServer::~ScratchServer() {
    sv.st.close();
    sv.m.close();
    if (!db.empty())
        for (const char* suffix : {"", "-wal", "-shm"}) unlink((db + suffix).c_str());
    if (own_test_options_) {
        config().fail = saved_fail_;
        config().surprise = saved_surprise_;
    }
    set_server_clock(0);
}
u32 ScratchServer::id(const char* table, const char* label) {
    return (u32)sv.m.one(std::string("select id from ") + table + " where id_label = ?", {label});
}
u32 ScratchServer::call(Request r, std::vector<u8>* out) {
    std::vector<u8> b;
    sv.pending[r.fid] = r;
    if (!sv.handle(r.fid, b)) return 0xffffffffu;
    if (out) *out = b;
    return sv.errors[r.fid];
}
void ScratchServer::set_clock(const char* t) { set_server_clock(parse_time(t)); }

// For the extension modules' tests (ext.h): a scratch server without the gacha pools and with its
// own test options, its state DB deleted afterwards. False (and the running test failed) when the
// 3.7.0 master or save is missing.
bool ext::with_scratch_server(u64 seed, const std::function<void(ext::Ctx&)>& fn) {
    ScratchServer::Options opt;
    opt.pools = false;
    opt.own_test_options = true;
    ScratchServer s(seed, opt);
    if (!s.ok) return false;
    RequestContext rc = s.sv.new_request();
    ext::Ctx c = s.sv.make_ctx(rc);
    fn(c);
    return true;
}

// The scratch server for tests outside the library (soaserver/scratch.h).
struct testing::Scratch::Impl {
    ScratchServer s;
    explicit Impl(u64 seed) : s(seed) {}
};
testing::Scratch::Scratch(uint64_t seed) : p_(std::make_unique<Impl>(seed)) {}
testing::Scratch::~Scratch() = default;
bool testing::Scratch::ok() const { return p_->s.ok; }
bool testing::Scratch::inputs_missing() const { return !p_->s.inputs; }
uint32_t testing::Scratch::id(const char* table, const char* label) { return p_->s.id(table, label); }
uint32_t testing::Scratch::call(const Request& r, std::vector<uint8_t>* out) { return p_->s.call(r, out); }
void testing::Scratch::set_live(bool live) { p_->s.sv.live = live; }
ext::Sql testing::Scratch::state() { return ext::Sql{p_->s.sv.st.h}; }
ext::Sql testing::Scratch::master() { return ext::Sql{p_->s.sv.m.h}; }

}  // namespace soa::server

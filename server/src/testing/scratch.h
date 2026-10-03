#pragma once
// The library's scratch servers for tests (library code): a Server on a fresh state DB under /tmp,
// seeded from the committed synthetic port/server-data/test-seed.xml, with the 3.7.0 master
// (data/basmaster-3.7.0.sqlite3). One implementation behind the three ways tests get one:
// ScratchServer (the library's own tests), ext::with_scratch_server (a module's tests, through
// an ext::Ctx) and testing::Scratch (tests outside the library, soaserver/scratch.h).
#include <string>
#include <vector>

#include "core/server.h"

namespace soa::server {

// The scratch-server tests' inputs: the 3.7.0 master DB and a seed save (the game's Game.xml,
// Aska::LocalKVS). The seed is the committed synthetic port/server-data/test-seed.xml
// (tools/make_test_seed.py: no real account data), so the tests don't depend on a local real
// save; the master DB is local data (decrypted from the 3.7.0 download). When one is missing the
// running test fails with a message saying what to put where (instead of skipping silently and
// passing). Returns false when one is missing.
bool scratch_inputs(std::string& master, std::string& save);
// The 3.7.0 master, read-only, for the tests that only read master data; nullptr without it.
ext::Sql* test_master();

// A scratch server (a unit-test one: live = false). `ok` is false (and the running test failed)
// when the 3.7.0 master or the seed save is missing.
struct ScratchServer {
    struct Options {
        bool pools = true;  // open the reconstructed gacha pools (else draws go by rarity)
        // Its own run options: the run's server test hooks (SOA_SERVER_FAIL / _SURPRISE) don't apply.
        bool own_test_options = false;
    };
    Server sv;
    std::string db;
    bool ok = false;
    bool inputs = false;  // the master and the seed save were found

    explicit ScratchServer(u64 seed) : ScratchServer(seed, Options()) {}
    ScratchServer(u64 seed, Options opt);
    ~ScratchServer();
    ScratchServer(const ScratchServer&) = delete;
    ScratchServer& operator=(const ScratchServer&) = delete;

    // The id of the master row with id_label `label` in `table`.
    u32 id(const char* table, const char* label);
    // A request through handle() (transaction, refusal and error code), as the fake server sends it.
    u32 call(Request r, std::vector<u8>* out = nullptr);
    // The server clock at "YYYY-MM-DD HH:MM:SS" and running on (as --clock); the destructor
    // returns it to the real time.
    void set_clock(const char* t);

private:
    std::string saved_fail_;
    bool saved_surprise_ = false, own_test_options_ = false;
};

}  // namespace soa::server

#pragma once
// A scratch server for tests (library code): a fresh state DB under /tmp seeded from the committed
// synthetic port/server-data/test-seed.xml, with the 3.7.0 master (data/basmaster-3.7.0.sqlite3),
// as the library's own unit tests use it. For tests outside the library that need the server's
// request path, e.g. the port's tests that compare with the live client (set_live).
#include <memory>
#include <vector>

#include "soaserver/ext.h"

namespace soa::server::testing {

class Scratch {
public:
    // Fails the running test (and ok() is false) when the master or the seed save is missing.
    explicit Scratch(uint64_t seed);
    ~Scratch();
    Scratch(const Scratch&) = delete;
    Scratch& operator=(const Scratch&) = delete;

    // The scratch server is usable (its master and seed save were found).
    bool ok() const;
    // The master or the seed save is missing (logged; a library test is failed by the constructor,
    // others should fail themselves).
    bool inputs_missing() const;
    // The id of the master row with id_label `label` in `table`.
    uint32_t id(const char* table, const char* label);
    // A request through the server's handle() (transaction, refusal and error code), as a client
    // sends it: the error code (0 accepted; 0xffffffff not handled) and the body in *out.
    uint32_t call(const Request& r, std::vector<uint8_t>* out = nullptr);
    // A live server (true: the request's battle log and the client interfaces of hooks.h are used)
    // or a unit-test one (false, the default).
    void set_live(bool live);
    ext::Sql state();
    ext::Sql master();

private:
    struct Impl;
    std::unique_ptr<Impl> p_;
};

}  // namespace soa::server::testing

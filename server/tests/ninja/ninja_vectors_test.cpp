// The Ninja reference (server/net/ninja/ninja_ref.h) against the envelopes the client's own code produced
// (ninja_vectors.txt, written by tools/gen_ninja_vectors.py gen under unicorn): every vector must
// encrypt to the client's bytes and decrypt back, and tampered envelopes / a wrong key must be
// refused. The same check as the command-line ninja_check.cpp, in soa-server --selftest.
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "net/ninja/ninja_ref.h"
#include "net/wire.h"
#include "soaserver/config.h"
#include "soaserver/native_test.h"

namespace {

using soa::server::net::unhex;

NATIVE_TEST("net/ninja-vectors") {
    std::string path = soa::server::find_repo_file("server/tests/ninja/ninja_vectors.txt");
    std::ifstream in(path);
    if (path.empty() || !in) return t.fail("server/tests/ninja/ninja_vectors.txt not found");
    std::string line;
    int n = 0, per[10] = {};
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        std::string tag, name, r2s, salts, keys, plains, envs;
        ss >> tag >> name >> r2s >> salts >> keys >> plains >> envs;
        if (tag != "env") continue;
        int ai = -1;
        for (int i = 0; i < 10; i++)
            if (name == ninja::alg_name(ninja::kAllAlgs[i])) ai = i;
        if (ai < 0) {
            t.fail("unknown algorithm %s", name.c_str());
            continue;
        }
        uint32_t alg = ninja::kAllAlgs[ai];
        uint32_t r2 = (uint32_t)strtoul(r2s.c_str(), nullptr, 16), salt = (uint32_t)strtoul(salts.c_str(), nullptr, 16);
        auto key = unhex(keys), plain = unhex(plains), env = unhex(envs);
        n++, per[ai]++;
        auto mine = ninja::encrypt(key.data(), alg, r2, salt, plain.data(), plain.size());
        std::vector<uint8_t> back;
        uint32_t got = 0;
        int st = ninja::decrypt(key.data(), env.data(), env.size(), &back, &got);
        if (mine != env || st != ninja::kOk || back != plain || got != alg)
            t.fail("%s r2=%08x len=%zu: encrypt %s, decrypt %d %s", name.c_str(), r2, plain.size(), mine == env ? "ok" : "differs", st,
                   back == plain ? "ok" : "differs");
        // every 7th vector: a flipped byte and a wrong key are refused
        if (n % 7 == 0) {
            for (size_t pos : {(size_t)0, (size_t)5, env.size() / 2, env.size() - 1}) {
                auto e2 = env;
                e2[pos] ^= 0x10;
                if (ninja::decrypt(key.data(), e2.data(), e2.size(), &back) == ninja::kOk)
                    t.fail("%s: byte %zu flipped, accepted", name.c_str(), pos);
            }
            auto k2 = key;
            k2[3] ^= 1;
            if (ninja::decrypt(k2.data(), env.data(), env.size(), &back) == ninja::kOk) t.fail("%s: wrong key accepted", name.c_str());
        }
    }
    t.expect_eq(n, 700, "vector count");
    for (int i = 0; i < 10; i++)
        if (!per[i]) t.fail("no vectors for %s", ninja::alg_name(ninja::kAllAlgs[i]));
}

}  // namespace

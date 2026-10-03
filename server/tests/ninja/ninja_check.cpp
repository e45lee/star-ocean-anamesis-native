// Checks server/net/ninja/ninja_ref against vectors captured from the client's own code
// (ninja_vectors.txt, written by ninja_client.py), and encrypts for the reverse check.
//   ninja_check [vectors.txt]               verify every vector (default: next to this file)
//   ninja_check encrypt ALG R2 SALT KEY PLAIN   print the envelope (hex arguments)
//   ninja_check decrypt KEY ENVELOPE             print "<algorithm> <plaintext hex>"
// Build and run: server/tests/ninja/ninja_check.sh
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "../../net/ninja/ninja_ref.h"

static std::vector<uint8_t> unhex(const std::string& s) {
    std::vector<uint8_t> v;
    for (size_t i = 0; i + 1 < s.size(); i += 2) v.push_back((uint8_t)strtoul(s.substr(i, 2).c_str(), nullptr, 16));
    return v;
}
static std::string hex(const std::vector<uint8_t>& v) {
    std::string s;
    char b[3];
    for (uint8_t c : v) snprintf(b, sizeof b, "%02x", c), s += b;
    return s;
}

int main(int argc, char** argv) {
    if (argc >= 2 && !strcmp(argv[1], "encrypt")) {
        if (argc != 7) return fprintf(stderr, "usage: encrypt ALG R2 SALT KEY PLAIN\n"), 2;
        uint32_t alg = strtoul(argv[2], nullptr, 16), r2 = strtoul(argv[3], nullptr, 16), salt = strtoul(argv[4], nullptr, 16);
        auto key = unhex(argv[5]), plain = unhex(argv[6]);
        if (key.size() != ninja::kKeySize) return fprintf(stderr, "key must be 32 bytes\n"), 2;
        auto env = ninja::encrypt(key.data(), alg, r2, salt, plain.data(), plain.size());
        printf("%s\n", hex(env).c_str());
        return env.empty();
    }
    if (argc >= 2 && !strcmp(argv[1], "decrypt")) {
        if (argc != 4) return fprintf(stderr, "usage: decrypt KEY ENVELOPE\n"), 2;
        auto key = unhex(argv[2]), env = unhex(argv[3]);
        if (key.size() != ninja::kKeySize) return fprintf(stderr, "key must be 32 bytes\n"), 2;
        std::vector<uint8_t> plain;
        uint32_t alg = 0;
        int st = ninja::decrypt(key.data(), env.data(), env.size(), &plain, &alg);
        if (st) return printf("error %d\n", st), 1;
        printf("%s %s\n", ninja::alg_name(alg), hex(plain).c_str());
        return 0;
    }
    std::string path = argc >= 2 ? argv[1] : std::string(__FILE__).substr(0, std::string(__FILE__).rfind('/') + 1) + "ninja_vectors.txt";
    std::ifstream in(path);
    if (!in) return fprintf(stderr, "cannot open %s\n", path.c_str()), 2;
    std::string line;
    int n = 0, bad = 0, per[10] = {}, perbad[10] = {};
    while (std::getline(in, line)) {
        if (line.empty() || line[0] == '#') continue;
        std::istringstream ss(line);
        std::string tag, name, r2s, salts, keys, plains, envs;
        ss >> tag >> name >> r2s >> salts >> keys >> plains >> envs;
        if (tag != "env") continue;
        uint32_t alg = 0;
        int ai = -1;
        for (int i = 0; i < 10; i++)
            if (!strcmp(ninja::alg_name(ninja::kAllAlgs[i]), name.c_str())) alg = ninja::kAllAlgs[i], ai = i;
        if (ai < 0) {
            printf("FAIL unknown algorithm %s\n", name.c_str());
            bad++;
            continue;
        }
        uint32_t r2 = strtoul(r2s.c_str(), nullptr, 16), salt = strtoul(salts.c_str(), nullptr, 16);
        auto key = unhex(keys), plain = unhex(plains), env = unhex(envs);
        n++, per[ai]++;
        auto mine = ninja::encrypt(key.data(), alg, r2, salt, plain.data(), plain.size());
        std::vector<uint8_t> back;
        uint32_t got_alg = 0;
        int st = ninja::decrypt(key.data(), env.data(), env.size(), &back, &got_alg);
        bool ok = mine == env && st == 0 && back == plain && got_alg == alg;
        if (!ok) {
            bad++, perbad[ai]++;
            if (perbad[ai] <= 3) {
                size_t d = 0;
                while (d < mine.size() && d < env.size() && mine[d] == env[d]) d++;
                printf("FAIL %s r2=%08x len=%zu: encrypt %s (first diff at byte %zu of %zu/%zu), decrypt status %d %s\n", name.c_str(), r2,
                       plain.size(), mine == env ? "ok" : "differs", d, mine.size(), env.size(), st, back == plain ? "ok" : "differs");
            }
        }
    }
    for (int i = 0; i < 10; i++)
        if (per[i]) printf("  %-12s %3d vectors, %d failing\n", ninja::alg_name(ninja::kAllAlgs[i]), per[i], perbad[i]);
    printf("%s: %d/%d vectors match the client\n", bad ? "FAIL" : "PASS", n - bad, n);
    return bad != 0 || n == 0;
}

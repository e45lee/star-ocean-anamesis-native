// Test data from the 3.7.0 download (test_assets.h).
#include "native/common/test_assets.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <filesystem>

#include "core/paths.h"
#include "soaserver/adld.h"

namespace soa::test_assets {

std::vector<uint8_t> read_file(const std::string& path) {
    std::vector<uint8_t> d;
    if (path.empty()) return d;
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return d;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (n > 0) {
        d.resize((size_t)n);
        if (fread(d.data(), 1, d.size(), f) != d.size()) d.clear();
    }
    fclose(f);
    return d;
}

const std::string& download_dir() {
    static const std::string d = find_repo_file("work/download-3.7.0");
    return d;
}

std::vector<std::string> download_files(const std::string& dir, const std::string& suffix, size_t n) {
    std::vector<std::string> out;
    if (download_dir().empty()) return out;
    std::error_code ec;
    for (auto& e : std::filesystem::directory_iterator(download_dir() + "/" + dir, ec)) {
        std::string name = e.path().filename().string();
        if (e.is_regular_file() && name.size() >= suffix.size() && name.compare(name.size() - suffix.size(), suffix.size(), suffix) == 0)
            out.push_back(dir + "/" + name);
    }
    std::sort(out.begin(), out.end());
    if (out.size() > n) out.resize(n);
    return out;
}

std::vector<uint8_t> download_payload(const std::string& rel) {
    std::vector<uint8_t> f = read_file(download_dir() + "/" + rel);
    if (f.empty()) return f;
    if (!server::adld::is_adld(f.data(), f.size())) return f;
    return server::adld::decrypt(rel, f);
}

std::vector<SlzChunk> slz_chunks(const std::vector<uint8_t>& p, int codec, size_t n) {
    std::vector<SlzChunk> out;
    if (p.size() < 0x20 || memcmp(p.data(), "SLZ", 3) || p[3] != codec) return out;
    auto u32 = [&](size_t o) { return (uint32_t)p[o] | (uint32_t)p[o + 1] << 8 | (uint32_t)p[o + 2] << 16 | (uint32_t)p[o + 3] << 24; };
    size_t raw = u32(0xc), at = u32(0x14), chunk = p[0x19] ? (size_t)p[0x19] * 1024 : raw;
    for (size_t done = 0; done < raw && out.size() < n && at + 2 <= p.size();) {
        size_t len = (size_t)p[at] | (size_t)p[at + 1] << 8;
        size_t o = std::min(chunk, raw - done);
        at += 2;
        if (len == 0) len = o;  // stored raw
        else {
            SlzChunk c;
            c.data.assign(p.begin() + (long)at, p.end());
            c.stored = len;
            c.out = o;
            out.push_back(std::move(c));
        }
        at += len;
        done += o;
    }
    return out;
}

}  // namespace soa::test_assets

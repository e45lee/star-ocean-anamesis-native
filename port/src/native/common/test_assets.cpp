// Test data from the 3.7.0 download (test_assets.h).
#include "native/common/test_assets.h"

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <memory>

#include "core/paths.h"
#include "soa/file_tree.h"
#include "soa/install.h"
#include "soa/adld.h"
#include "soa/aska_image.h"

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

const FileTree* download_tree() {
    static const std::shared_ptr<const FileTree> tree = [] {
        std::string p = find_repo_file(install::kRepoDownloadZip);
        return p.empty() ? nullptr : FileTree::open(p);
    }();
    return tree.get();
}

std::vector<uint8_t> download_file(const std::string& rel) {
    std::vector<uint8_t> d;
    if (const FileTree* t = download_tree(); !t || !t->read(rel, d)) d.clear();
    return d;
}

std::vector<std::string> download_files(const std::string& dir, const std::string& suffix, size_t n) {
    std::vector<std::string> out;
    const FileTree* t = download_tree();
    if (!t) return out;
    for (auto& name : t->list(dir))  // (sorted)
        if (name.size() >= suffix.size() && name.compare(name.size() - suffix.size(), suffix.size(), suffix) == 0) out.push_back(dir + "/" + name);
    if (out.size() > n) out.resize(n);
    return out;
}

std::vector<uint8_t> download_payload(const std::string& rel) {
    std::vector<uint8_t> f = download_file(rel);
    if (f.empty()) return f;
    if (!adld::is_adld(f.data(), f.size())) return f;
    return adld::decrypt(rel, f);
}

std::vector<SlzChunk> slz_chunks(const std::vector<uint8_t>& p, int codec, size_t n) {
    std::vector<SlzChunk> out;
    if (!aska::is_slz(p) || p[3] != codec) return out;
    std::vector<aska::SlzChunk> chunks;
    aska::slz_chunks(p, chunks);  // (a truncated file: the chunks before the end)
    for (const aska::SlzChunk& c : chunks) {
        if (out.size() >= n) break;
        if (c.raw) continue;
        SlzChunk t;
        t.data.assign(p.begin() + (long)c.offset, p.end());
        t.stored = c.stored;
        t.out = c.size;
        out.push_back(std::move(t));
    }
    return out;
}

}  // namespace soa::test_assets

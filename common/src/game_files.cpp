// The install-dir lookup's zip-aware half (soa/game_files.h).
#include "soa/game_files.h"

#include <cstdio>

#include "soa/file_tree.h"
#include "soa/zip.h"

namespace soa::install {

namespace {
int64_t lib_size(const std::string& apk) {
    ZipArchive z;
    if (!z.open(apk)) return -1;
    const ZipArchive::Entry* e = z.find(kLibEntry);
    return e ? (int64_t)e->size : -1;
}
}  // namespace

bool is_apk_370(const std::string& path) { return lib_size(path) == (int64_t)kLib370Size; }

std::string find_apk(const std::vector<std::string>& dirs, std::vector<std::string>* notes) {
    return find_apk_370(dirs, lib_size, notes);
}

bool is_download(const std::string& path) {
    auto t = FileTree::open(path);
    return t && is_download_tree(*t);
}

std::string find_download(const std::vector<std::string>& dirs, std::vector<std::string>* notes) {
    if (std::string d = find_download_dir(dirs); !d.empty()) return d;
    for (auto& d : dirs) {
        std::vector<std::string> zips;
        if (is_file(d + "/" + kDataZipName)) zips.push_back(d + "/" + kDataZipName);
        for (auto& n : list_dir(d))
            if (n != kDataZipName && ends_with_ci(n, ".zip") && is_file(d + "/" + n)) zips.push_back(d + "/" + n);
        for (auto& z : zips) {
            if (is_download(z)) return z;
            if (notes) notes->push_back(z + ": not the 3.7.0 download (no version.bin, manifest/ and sqlite/basmaster.sqlite3 in it)");
        }
    }
    return "";
}

bool extract_entry(const std::string& zip, const std::string& name, const std::string& out) {
    ZipArchive z;
    std::vector<uint8_t> data;
    const ZipArchive::Entry* e = z.open(zip) ? z.find(name) : nullptr;
    if (!e || !z.extract(*e, data)) return false;
    std::string tmp = out + ".tmp";
    FILE* f = fopen(tmp.c_str(), "wb");
    if (!f) return false;
    bool ok = fwrite(data.data(), 1, data.size(), f) == data.size();
    ok = fclose(f) == 0 && ok;
    if (ok) {
        remove(out.c_str());  // (Windows: rename doesn't replace)
        ok = rename(tmp.c_str(), out.c_str()) == 0;
    }
    if (!ok) remove(tmp.c_str());
    return ok;
}

}  // namespace soa::install

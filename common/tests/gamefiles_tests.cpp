// Unit tests of soa/file_tree.h and soa/game_files.h (build/common/soa_gamefiles_tests): the same
// download-like tree as a folder, a flat zip (stored and deflated entries), a zip with one top
// folder; locate() in place, read(), files() / list(), is_download_tree; the zip-aware lookups
// (the APK by its libSOA.so's size, the download as a folder or a zip, extract_entry).
#include <sys/stat.h>
#include <unistd.h>

#include <cstdio>
#include <filesystem>
#include <string>
#include <vector>

#include <soa/file_tree.h>
#include <soa/game_files.h>

#include "zip_writer.h"

namespace {
using namespace soa::ziptest;
namespace fs = std::filesystem;
int g_failures = 0;
void check(bool ok, const std::string& what) {
    fprintf(stderr, "%s  %s\n", ok ? "ok  " : "FAIL", what.c_str());
    if (!ok) g_failures++;
}
bool write_file(const fs::path& p, const Bytes& b) {
    fs::create_directories(p.parent_path());
    FILE* f = fopen(p.string().c_str(), "wb");
    if (!f) return false;
    bool ok = fwrite(b.data(), 1, b.size(), f) == b.size();
    return fclose(f) == 0 && ok;
}
Bytes text(const std::string& s) { return Bytes(s.begin(), s.end()); }
Bytes pread_file(const std::string& path, uint64_t off, size_t n) {
    Bytes b(n);
    FILE* f = fopen(path.c_str(), "rb");
    if (!f) return {};
    bool ok = fseeko(f, (off_t)off, SEEK_SET) == 0 && fread(b.data(), 1, n, f) == n;
    fclose(f);
    return ok ? b : Bytes{};
}

const std::vector<Member> kTree = {
    {"version.bin", text("v1"), false},
    {"manifest/etc2/hi/version_latest_Bulk.bin", text("bulk manifest"), true},
    {"sqlite/basmaster.sqlite3", text("ADLD....master"), false},
    {"Sound/a.aac", Bytes(5000, 7), false},
    {"Sound/b.aac", Bytes(3000, 9), true},
    {"Sound/sub/c.aac", text("c"), false},
};

void check_tree(const soa::FileTree& t, const std::string& what) {
    check(soa::is_download_tree(t), what + ": a download tree");
    std::vector<uint8_t> b;
    check(t.read("Sound/b.aac", b) && b == Bytes(3000, 9), what + ": read (deflated in a zip)");
    soa::FileTree::Loc loc;
    check(t.locate("Sound/a.aac", &loc) && loc.in_place && loc.size == 5000 && pread_file(loc.file, loc.offset, 5000) == Bytes(5000, 7),
          what + ": locate in place (pread of the host file)");
    check(!t.locate("Sound", nullptr) && !t.locate("nope", nullptr) && !t.locate("../x", nullptr), what + ": no folders, missing or escaping paths");
    check(t.is_dir("Sound") && t.is_dir("manifest") && !t.is_dir("Sound/a.aac") && !t.is_dir("Movie"), what + ": is_dir");
    auto all = t.files();
    check(all.size() == kTree.size() && all.front() == "Sound/a.aac", what + ": files(), sorted");
    auto snd = t.files("Sound");
    check(snd == std::vector<std::string>({"Sound/a.aac", "Sound/b.aac", "Sound/sub/c.aac"}), what + ": files(dir), recursive");
    check(t.list("Sound") == std::vector<std::string>({"a.aac", "b.aac"}), what + ": list(dir), this level only");
}
}  // namespace

int main() {
    fs::path root = fs::temp_directory_path() / ("soa_gamefiles_tests." + std::to_string(getpid()));
    fs::create_directories(root);
    // the folder
    for (auto& m : kTree) write_file(root / "dir" / m.name, m.data);
    auto dir = soa::FileTree::open((root / "dir").generic_string());
    check(dir && !dir->is_zip(), "a folder opens as a folder");
    if (dir) check_tree(*dir, "folder");
    // a flat zip, and one with a top folder
    write_file(root / "flat.zip", make_zip(kTree));
    std::vector<Member> nested;
    for (auto& m : kTree) nested.push_back({"download-3.7.0/" + m.name, m.data, m.deflate});
    write_file(root / "nested.zip", make_zip(nested));
    auto flat = soa::FileTree::open((root / "flat.zip").generic_string());
    check(flat && flat->is_zip() && flat->prefix().empty(), "a flat zip");
    if (flat) check_tree(*flat, "flat zip");
    auto top = soa::FileTree::open((root / "nested.zip").generic_string());
    check(top && top->prefix() == "download-3.7.0/", "a zip with one top folder: read from inside it");
    if (top) check_tree(*top, "nested zip");
    write_file(root / "junk.bin", text("not a zip"));
    check(!soa::FileTree::open((root / "junk.bin").generic_string()) && !soa::FileTree::open((root / "none").generic_string()),
          "neither a folder nor a zip: nullptr");

    // the lookups: game/ holds the APK (by content) and the download as a zip
    using namespace soa::install;
    std::string g = (root / "game").generic_string();
    fs::create_directories(g);
    check(find_download({g}).empty(), "find_download: nothing yet");
    fs::copy_file(root / "flat.zip", fs::path(g) / kDataZipName);
    write_file(fs::path(g) / "a-other.zip", make_zip({{"x.txt", text("x"), false}}));
    std::vector<std::string> notes;
    check(find_download({g}, &notes) == g + "/" + kDataZipName, "find_download: the canonical zip");
    fs::remove(fs::path(g) / kDataZipName);
    fs::copy_file(root / "nested.zip", fs::path(g) / "my-download.zip");
    notes.clear();
    check(find_download({g}, &notes) == g + "/my-download.zip" && notes.size() == 1, "find_download: any zip holding the tree; others noted");
#ifdef _WIN32  // a copy: MinGW's libstdc++ makes no symlinks, and Windows' need a privilege anyway
    fs::copy(root / "dir", fs::path(g) / "extracted", fs::copy_options::recursive);
#else  // a linked folder, as a user's link to their download
    fs::create_directory_symlink(root / "dir", fs::path(g) / "extracted");
#endif
    check(find_download({g}) == g + "/extracted", "find_download: a folder tree before a zip");
    Bytes lib(kLib370Size, 0);  // a 3.7.0-sized libSOA.so (stored)
    write_file(fs::path(g) / "renamed.apk", make_zip({{"AndroidManifest.xml", text("m"), true}, {kLibEntry, lib, false}}));
    write_file(fs::path(g) / "old.apk", make_zip({{kLibEntry, Bytes(100, 1), false}}));
    notes.clear();
    check(find_apk({g}, &notes) == g + "/renamed.apk" && notes.size() == 1, "find_apk: the 3.7.0 one by content, another version noted");
    check(is_apk_370(g + "/renamed.apk") && !is_apk_370(g + "/old.apk"), "is_apk_370");
    std::string out = (root / "libSOA-3.7.0.so").generic_string();
    struct stat st;
    check(extract_entry(g + "/renamed.apk", kLibEntry, out) && stat(out.c_str(), &st) == 0 && (uint64_t)st.st_size == kLib370Size,
          "extract_entry: the library extracted");
    check(!extract_entry(g + "/renamed.apk", "nope", out + "2"), "extract_entry: a missing entry fails");
    dir.reset(), flat.reset(), top.reset();  // close the archives first: Windows deletes no open file
    fs::remove_all(root);
    fprintf(stderr, g_failures ? "%d FAILED\n" : "all passed\n", g_failures);
    return g_failures ? 1 : 0;
}

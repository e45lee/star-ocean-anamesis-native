#pragma once
// A read-only tree of files that is either a folder or a ZIP archive (target soa_gamefiles,
// common/CMakeLists.txt): how the programs read the 3.7.0 download, extracted
// (work/download-3.7.0, game/<folder>) or as the user's SOA-3.7.0-canonical-data.zip without
// extracting it. Readers: the server's CDN and its asset index (server/src/cdn), the master's
// derivation (soaserver/master_source.h), the runtime's download fallback for assets and movies
// (runtime/src/android/ndk.h AssetManager::set_download_dir).
//
// Paths are relative, '/'-separated ("sqlite/basmaster.sqlite3"). A zip whose only top-level entry
// is one folder holding the tree (e.g. download-3.7.0/...) is read from inside that folder.
// locate() gives where a file's bytes are: a range of a host file (the folder's file itself, or a
// stored zip entry in place: no copy, pread / mmap / the movie player's reader), or not in place (a deflated
// entry: read() inflates it). Const methods are thread-safe (soa::ZipArchive's rule).
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace soa {

class ZipArchive;

class FileTree {
public:
    // The folder or the .zip at `path` (decided by what it is, not its name). nullptr (and *err)
    // when it is neither.
    static std::shared_ptr<const FileTree> open(const std::string& path, std::string* err = nullptr);
    ~FileTree();

    const std::string& path() const { return path_; }
    bool is_zip() const { return zip_ != nullptr; }
    // The zip's folder prefix (see above; "" for a folder or a flat zip).
    const std::string& prefix() const { return prefix_; }

    struct Loc {
        std::string file;      // the host file holding the bytes (the zip for an entry)
        uint64_t offset = 0;   // where they start in it
        uint64_t size = 0;     // the file's (uncompressed) size
        bool in_place = true;  // false: a compressed entry (read() it)
        int64_t mtime = 0;     // the host file's modification time (s), for caches
    };
    // A regular file's location; false when there is no such file.
    bool locate(const std::string& rel, Loc* out) const;
    bool exists(const std::string& rel) const { return locate(rel, nullptr); }
    // A folder (a prefix of some file)?
    bool is_dir(const std::string& rel) const;
    // The whole file (inflated when compressed).
    bool read(const std::string& rel, std::vector<uint8_t>& out) const;
    // Every regular file under the folder `dir` ("" = all), recursive, relative to the tree, sorted.
    std::vector<std::string> files(const std::string& dir = "") const;
    // The names of the regular files directly in the folder `dir` (not recursive), sorted.
    std::vector<std::string> list(const std::string& dir) const;
    // The zip (nullptr for a folder).
    const ZipArchive* zip() const { return zip_.get(); }

private:
    FileTree() = default;
    std::string path_, prefix_;
    std::unique_ptr<ZipArchive> zip_;
    std::vector<std::string> names_;  // a zip's files, relative to prefix_, sorted
    int64_t mtime_ = 0;
};

// Is `t` a 3.7.0 download tree (version.bin, manifest/, sqlite/basmaster.sqlite3)?
bool is_download_tree(const FileTree& t);

}  // namespace soa

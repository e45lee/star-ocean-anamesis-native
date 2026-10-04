#pragma once
// Read-only ZIP archives (APKs, app bundles and the APKs inside them, the data zips), on minizip-ng
// (vcpkg.json; target soa_zip, common/CMakeLists.txt). Shared by the runtime (runtime/src/android/zip.h:
// the AAssetManager, the movie player, the programs' library extraction) and anything else that
// reads a zip (the server's data zips) without depending on the runtime.
//
// The file is memory-mapped and minizip-ng reads it through a 64-bit stream over the mapping (its
// own memory stream is limited to 2 GB), so:
//   - ZIP64 archives work (more than 65,535 entries, offsets and sizes past 4 GB);
//   - a stored (uncompressed) entry is served in place: stored_data() points into the mapping and
//     data_offset_of() is its offset in path(), for pread / mmap (the movie player reads stored_data());
//   - an archive stored inside another one (an app bundle's APKs) opens in place, without extracting
//     it: open_member(), or open(path, offset, length) for any byte range of a file.
// Deflated entries are inflated by minizip-ng's zlib stream (extract(), read()).
//
// Concurrency: after open() returns, every const method may be called from any number of threads
// at once. Inflating uses per-call streams; the one shared minizip handle (resolving an entry's data
// offset from its local header, once per entry, then cached) is used under a mutex.
#include <atomic>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

namespace soa {

class ZipArchive {
public:
    struct Entry {
        uint64_t local_header = 0;  // offset of the local header, relative to the archive's start
        uint64_t comp_size = 0, size = 0;
        uint32_t crc = 0;           // the central directory's CRC-32
        uint16_t method = 0;        // 0 stored, 8 deflated
        uint32_t index = 0;         // position in the central directory
        int64_t cd_pos = 0;         // (minizip-ng's handle for the entry)
    };

    ZipArchive();
    ~ZipArchive();
    ZipArchive(const ZipArchive&) = delete;
    ZipArchive& operator=(const ZipArchive&) = delete;

    // The zip file at `path`.
    bool open(const std::string& path);
    // The zip occupying bytes [offset, offset + length) of the file at `path` (length 0: to the end).
    bool open(const std::string& path, uint64_t offset, uint64_t length);
    // The zip that is the stored member `name` of `outer` (an APK inside an app bundle), read in place.
    // False when there is no such member, or it is compressed (extract it instead).
    bool open_member(const ZipArchive& outer, const std::string& name);

    // The entries by name (directories too, with a trailing '/'). The first of duplicate names wins.
    const std::unordered_map<std::string, Entry>& entries() const { return entries_; }
    const Entry* find(const std::string& name) const;
    // A stored entry's bytes inside the mapping; nullptr when it is compressed (or unreadable).
    const uint8_t* stored_data(const Entry& e) const;
    // The whole entry, inflated when compressed (CRC-checked then).
    bool extract(const Entry& e, std::vector<uint8_t>& out) const;
    // Up to `len` bytes of the entry's content from `off` (stored: copied from the mapping;
    // deflated: inflated from the start, the first `off` bytes dropped). The bytes read; -1 on error.
    int64_t read(const Entry& e, uint64_t off, void* buf, size_t len) const;
    // The file this archive's bytes are in (the outer file for a nested archive), and an entry's
    // data offset in it.
    const std::string& path() const { return path_; }
    uint64_t data_offset_of(const Entry& e) const { return base_ + data_offset(e); }
    // Where the archive starts in path() and how long it is.
    uint64_t base_offset() const { return base_; }
    uint64_t size() const { return size_; }

private:
    struct Mapping;
    uint64_t data_offset(const Entry& e) const;  // relative to the archive's start; 0 if unreadable
    void close();

    std::string path_;
    std::shared_ptr<Mapping> map_file_;  // this archive's mapping (a nested archive maps the file again; the page cache is shared)
    const uint8_t* map_ = nullptr;       // the archive's first byte
    uint64_t base_ = 0, size_ = 0;
    void* stream_ = nullptr;  // minizip-ng: the stream over [map_, map_ + size_) and the zip handle
    void* handle_ = nullptr;
    mutable std::mutex mu_;   // guards handle_ / stream_ after open
    std::unique_ptr<std::atomic<uint64_t>[]> offsets_;  // resolved data offsets by index (0: not yet)
    uint32_t count_ = 0;                                 // central directory entries (offsets_' size)
    std::unordered_map<std::string, Entry> entries_;
};

}  // namespace soa

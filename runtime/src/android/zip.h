#pragma once
// Minimal read-only ZIP (APK) reader over an mmap'd file.
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "core/host_mem.h"

namespace soa {

class ZipArchive {
public:
    struct Entry {
        uint64_t data_offset = 0;  // resolved lazily from the local header
        uint64_t local_header = 0;
        uint64_t comp_size = 0, size = 0;
        uint16_t method = 0;
    };

    bool open(const std::string& path);
    ~ZipArchive();

    const std::unordered_map<std::string, Entry>& entries() const { return entries_; }
    const Entry* find(const std::string& name) const;
    // For stored entries: pointer to the bytes inside the mapping. nullptr if compressed.
    const uint8_t* stored_data(const Entry& e) const;
    bool extract(const Entry& e, std::vector<uint8_t>& out) const;
    const std::string& path() const { return path_; }
    // File offset of an entry's (possibly compressed) data.
    uint64_t data_offset_of(const Entry& e) const { return data_offset(e); }

private:
    uint64_t data_offset(const Entry& e) const;
    std::string path_;
    hostmem::MappedFile file_;
    const uint8_t* map_ = nullptr;
    size_t size_ = 0;
    std::unordered_map<std::string, Entry> entries_;
};

// Extracts the entry `name` of the zip `zip_path` to the file `out` (written through "<out>.tmp" and
// a rename, so a reader never sees half a file). False when the zip, the entry or the write fails.
// soa and soa-emu extract the APK's lib/arm64-v8a/libSOA.so with it.
bool extract_zip_entry(const std::string& zip_path, const std::string& name, const std::string& out);
// The entry `name` of the zip `zip_path` into `out` (the server's master derivation reads the APK's
// built-in master with it: soaserver/master_source.h set_zip_reader).
bool read_zip_entry(const std::string& zip_path, const std::string& name, std::vector<uint8_t>& out);
// The uncompressed size of the entry `name`, -1 when the file isn't a zip or has no such entry (the
// install-dir APK lookup's probe, soa/install.h find_apk_370).
int64_t zip_entry_size(const std::string& zip_path, const std::string& name);

}  // namespace soa

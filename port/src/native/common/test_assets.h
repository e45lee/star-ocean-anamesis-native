#pragma once
// Test data from the 3.7.0 download (work/download-3.7.0, found from the repo; absent on a machine
// without it: tests skip) for the differential tests of the host-library families: whole files,
// their ADLD payloads, and the compressed chunks of SLZ files (docs/notes.md "SLZ compressed files").
#include <cstdint>
#include <string>
#include <vector>

namespace soa::test_assets {

// The file's bytes ("" path or unreadable: empty).
std::vector<uint8_t> read_file(const std::string& path);
// The download's root ("" when absent).
const std::string& download_dir();
// Up to `n` files under download_dir()/dir (sorted by name) whose names end with `suffix`, as
// download-relative paths ("Image/etc2/x.aif"), the ADLD key names.
std::vector<std::string> download_files(const std::string& dir, const std::string& suffix, size_t n);
// The decrypted payload of a download file (its ADLD layer removed; empty when unreadable).
std::vector<uint8_t> download_payload(const std::string& rel);

// One compressed chunk of an SLZ file: the bytes from its start to the end of the file (a decoder
// may be handed more than the chunk, as the game does), the chunk's own stored size, the size it
// decompresses to.
struct SlzChunk {
    std::vector<uint8_t> data;
    size_t stored = 0;
    size_t out = 0;
};
// The codec-`codec` chunks of an SLZ ("SLZ" tag; "SLE" ones are skipped) payload, at most `n`;
// empty when it isn't one or the codec differs.
std::vector<SlzChunk> slz_chunks(const std::vector<uint8_t>& payload, int codec, size_t n);

}  // namespace soa::test_assets

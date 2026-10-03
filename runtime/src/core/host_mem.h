#pragma once
// Host memory for the guest (port/PLAN.md 5b, W): anonymous mappings, guard pages and read-only
// file mappings, over mmap on Linux and VirtualAlloc / file mappings on Windows. Guest memory is
// identity-mapped (guest pointers are host pointers), so these are where guest code, stacks and
// images live.
#include <cstddef>
#include <string>

namespace soa::hostmem {

// `bytes` of zeroed read-write memory, page-aligned (64 KiB-aligned on Windows); nullptr on failure.
// `reserve_only_touched`: commit pages lazily where the OS allows it (Linux MAP_NORESERVE).
void* map_rw(size_t bytes, bool reserve_only_touched = false);
// Releases a whole mapping made by map_rw.
void unmap(void* p, size_t bytes);
// Makes [p, p+bytes) inaccessible (a guard page); page-aligned.
bool protect_none(void* p, size_t bytes);
// Gives the pages back to the OS; they read as zero afterwards.
void discard(void* p, size_t bytes);

// A read-only mapping of a whole file.
struct MappedFile {
    const unsigned char* data = nullptr;
    size_t size = 0;
    void* handle = nullptr;  // Windows: the file-mapping handle
};
bool map_file(const std::string& path, MappedFile* out);
void unmap_file(MappedFile& f);

}  // namespace soa::hostmem

// host_mem.h: mmap on Linux, VirtualAlloc and file mappings on Windows.
#include "core/host_mem.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

namespace soa::hostmem {

#ifdef _WIN32

void* map_rw(size_t bytes, bool) { return VirtualAlloc(nullptr, bytes, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE); }
void unmap(void* p, size_t) {
    if (p) VirtualFree(p, 0, MEM_RELEASE);
}
bool protect_none(void* p, size_t bytes) {
    DWORD old;
    return VirtualProtect(p, bytes, PAGE_NOACCESS, &old) != 0;
}
void discard(void* p, size_t bytes) {
    // decommit + recommit: the pages come back zeroed, like MADV_DONTNEED on anonymous memory
    if (VirtualFree(p, bytes, MEM_DECOMMIT)) VirtualAlloc(p, bytes, MEM_COMMIT, PAGE_READWRITE);
}

bool map_file(const std::string& path, MappedFile* out) {
    HANDLE f = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (f == INVALID_HANDLE_VALUE) return false;
    LARGE_INTEGER sz;
    if (!GetFileSizeEx(f, &sz) || sz.QuadPart == 0) {
        CloseHandle(f);
        return false;
    }
    HANDLE m = CreateFileMappingA(f, nullptr, PAGE_READONLY, 0, 0, nullptr);
    CloseHandle(f);
    if (!m) return false;
    void* p = MapViewOfFile(m, FILE_MAP_READ, 0, 0, 0);
    if (!p) {
        CloseHandle(m);
        return false;
    }
    out->data = (const unsigned char*)p;
    out->size = (size_t)sz.QuadPart;
    out->handle = m;
    return true;
}
void unmap_file(MappedFile& f) {
    if (f.data) UnmapViewOfFile(f.data);
    if (f.handle) CloseHandle((HANDLE)f.handle);
    f = MappedFile();
}

#else

void* map_rw(size_t bytes, bool reserve_only_touched) {
    void* p = mmap(nullptr, bytes, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | (reserve_only_touched ? MAP_NORESERVE : 0), -1, 0);
    return p == MAP_FAILED ? nullptr : p;
}
void unmap(void* p, size_t bytes) {
    if (p) munmap(p, bytes);
}
bool protect_none(void* p, size_t bytes) { return mprotect(p, bytes, PROT_NONE) == 0; }
void discard(void* p, size_t bytes) { madvise(p, bytes, MADV_DONTNEED); }

bool map_file(const std::string& path, MappedFile* out) {
    int fd = open(path.c_str(), O_RDONLY | O_CLOEXEC);
    if (fd < 0) return false;
    struct stat st;
    if (fstat(fd, &st) != 0 || st.st_size == 0) {
        close(fd);
        return false;
    }
    void* p = mmap(nullptr, (size_t)st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
    close(fd);
    if (p == MAP_FAILED) return false;
    out->data = (const unsigned char*)p;
    out->size = (size_t)st.st_size;
    return true;
}
void unmap_file(MappedFile& f) {
    if (f.data) munmap((void*)f.data, f.size);
    f = MappedFile();
}

#endif

}  // namespace soa::hostmem

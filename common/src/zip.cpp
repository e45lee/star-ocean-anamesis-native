// soa/zip.h: read-only ZIP archives on minizip-ng, over a memory-mapped file.
#include <soa/zip.h>

#include <cstring>

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

extern "C" {
#include <mz.h>
#include <mz_crypt.h>
#include <mz_strm.h>
#include <mz_strm_zlib.h>
#include <mz_zip.h>
}

namespace soa {

// ---- the file mapping -------------------------------------------------------------------------
struct ZipArchive::Mapping {
    const uint8_t* data = nullptr;
    uint64_t size = 0;
#ifdef _WIN32
    HANDLE handle = nullptr;
#endif
    bool map(const std::string& path) {
#ifdef _WIN32
        HANDLE f = CreateFileA(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING,
                               FILE_ATTRIBUTE_NORMAL, nullptr);
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
        data = (const uint8_t*)p;
        size = (uint64_t)sz.QuadPart;
        handle = m;
        return true;
#else
        int fd = ::open(path.c_str(), O_RDONLY | O_CLOEXEC);
        if (fd < 0) return false;
        struct stat st;
        if (fstat(fd, &st) != 0 || st.st_size == 0) {
            ::close(fd);
            return false;
        }
        void* p = mmap(nullptr, (size_t)st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
        ::close(fd);
        if (p == MAP_FAILED) return false;
        data = (const uint8_t*)p;
        size = (uint64_t)st.st_size;
        return true;
#endif
    }
    ~Mapping() {
#ifdef _WIN32
        if (data) UnmapViewOfFile(data);
        if (handle) CloseHandle(handle);
#else
        if (data) munmap((void*)data, (size_t)size);
#endif
    }
};

namespace {

// ---- a read-only minizip-ng stream over a byte range in memory (64-bit: minizip-ng's own memory
// stream takes int32_t sizes, and the data zips are larger than 2 GB) -------------------------------
struct ViewStream {
    mz_stream s;  // first: minizip-ng passes this struct as its mz_stream
    const uint8_t* data;
    int64_t size, pos;
};

int32_t view_open(void*, const char*, int32_t mode) { return (mode & MZ_OPEN_MODE_WRITE) ? MZ_SUPPORT_ERROR : MZ_OK; }
int32_t view_is_open(void*) { return MZ_OK; }
int32_t view_read(void* stream, void* buf, int32_t size) {
    auto* v = (ViewStream*)stream;
    if (size < 0) return MZ_PARAM_ERROR;
    int64_t n = v->size - v->pos;
    if (n > size) n = size;
    if (n <= 0) return 0;
    memcpy(buf, v->data + v->pos, (size_t)n);
    v->pos += n;
    return (int32_t)n;
}
int32_t view_write(void*, const void*, int32_t) { return MZ_SUPPORT_ERROR; }
int64_t view_tell(void* stream) { return ((ViewStream*)stream)->pos; }
int32_t view_seek(void* stream, int64_t offset, int32_t origin) {
    auto* v = (ViewStream*)stream;
    int64_t p = origin == MZ_SEEK_SET ? offset : origin == MZ_SEEK_CUR ? v->pos + offset : v->size + offset;
    if (p < 0 || p > v->size) return MZ_SEEK_ERROR;
    v->pos = p;
    return MZ_OK;
}
int32_t view_close(void*) { return MZ_OK; }
int32_t view_error(void*) { return MZ_OK; }
void* view_create();
void view_destroy(void** stream) {
    if (stream && *stream) {
        delete (ViewStream*)*stream;
        *stream = nullptr;
    }
}
int32_t view_get_prop(void*, int32_t, int64_t*) { return MZ_EXIST_ERROR; }
int32_t view_set_prop(void*, int32_t, int64_t) { return MZ_EXIST_ERROR; }

mz_stream_vtbl g_view_vtbl = {view_open, view_is_open, view_read,  view_write,    view_tell,    view_seek,
                              view_close, view_error,  view_create, view_destroy, view_get_prop, view_set_prop};
void* view_create() {
    auto* v = new ViewStream();
    v->s.vtbl = &g_view_vtbl;
    v->s.base = nullptr;
    v->data = nullptr;
    v->size = v->pos = 0;
    return v;
}
void* make_view(const uint8_t* data, uint64_t size) {
    auto* v = (ViewStream*)mz_stream_create(&g_view_vtbl);
    v->data = data;
    v->size = (int64_t)size;
    return v;
}

// Streams one deflated entry's content (its compressed bytes in [src, src + comp_size)) to `sink`
// (called with each piece in order) until `want` bytes have come out. Per call: no shared state.
template <typename Sink>
bool inflate_entry(const uint8_t* src, uint64_t comp_size, uint64_t want, Sink&& sink) {
    void* view = make_view(src, comp_size);
    void* z = mz_stream_zlib_create();
    bool ok = z != nullptr;
    if (ok) {
        mz_stream_set_base(z, view);
        mz_stream_set_prop_int64(z, MZ_STREAM_PROP_TOTAL_IN_MAX, (int64_t)comp_size);
        ok = mz_stream_open(z, nullptr, MZ_OPEN_MODE_READ) == MZ_OK;
    }
    uint8_t buf[64 * 1024];
    uint64_t done = 0;
    while (ok && done < want) {
        uint64_t n = want - done < sizeof buf ? want - done : sizeof buf;
        int32_t r = mz_stream_read(z, buf, (int32_t)n);
        if (r <= 0) {
            ok = false;
            break;
        }
        sink(buf, (size_t)r);
        done += (uint64_t)r;
    }
    if (z) {
        mz_stream_close(z);
        mz_stream_zlib_delete(&z);
    }
    mz_stream_delete(&view);
    return ok;
}

}  // namespace

// ---- ZipArchive -------------------------------------------------------------------------------
ZipArchive::ZipArchive() = default;
ZipArchive::~ZipArchive() { close(); }

void ZipArchive::close() {
    if (handle_) {
        mz_zip_close(handle_);
        mz_zip_delete(&handle_);
    }
    if (stream_) mz_stream_delete(&stream_);
    entries_.clear();
    offsets_.reset();
    count_ = 0;
    map_file_.reset();
    map_ = nullptr;
    base_ = size_ = 0;
}

bool ZipArchive::open(const std::string& path) { return open(path, 0, 0); }

bool ZipArchive::open(const std::string& path, uint64_t offset, uint64_t length) {
    close();
    auto m = std::make_shared<Mapping>();
    if (!m->map(path)) return false;
    if (offset > m->size || length > m->size - offset) return false;
    if (length == 0) length = m->size - offset;
    path_ = path;
    map_file_ = std::move(m);
    map_ = map_file_->data + offset;
    base_ = offset;
    size_ = length;

    stream_ = make_view(map_, size_);
    handle_ = mz_zip_create();
    if (!handle_ || mz_zip_open(handle_, stream_, MZ_OPEN_MODE_READ) != MZ_OK) {
        close();
        return false;
    }
    uint64_t count = 0;
    mz_zip_get_number_entry(handle_, &count);
    entries_.reserve((size_t)count);
    uint32_t index = 0;
    for (int32_t err = mz_zip_goto_first_entry(handle_); err == MZ_OK; err = mz_zip_goto_next_entry(handle_)) {
        mz_zip_file* fi = nullptr;
        if (mz_zip_entry_get_info(handle_, &fi) != MZ_OK || !fi || !fi->filename) continue;
        Entry e;
        e.local_header = (uint64_t)fi->disk_offset;
        e.comp_size = (uint64_t)fi->compressed_size;
        e.size = (uint64_t)fi->uncompressed_size;
        e.crc = fi->crc;
        e.method = fi->compression_method;
        e.index = index++;
        e.cd_pos = mz_zip_get_entry(handle_);
        entries_.emplace(std::string(fi->filename, fi->filename_size), e);
    }
    offsets_.reset(new std::atomic<uint64_t>[index ? index : 1]());
    count_ = index;
    return true;
}

bool ZipArchive::open_member(const ZipArchive& outer, const std::string& name) {
    const Entry* e = outer.find(name);
    if (!e || e->method != 0 || e->comp_size != e->size) return false;
    uint64_t off = outer.data_offset(*e);
    if (!off) return false;
    return open(outer.path_, outer.base_ + off, e->size);
}

const ZipArchive::Entry* ZipArchive::find(const std::string& name) const {
    auto it = entries_.find(name);
    return it == entries_.end() ? nullptr : &it->second;
}

uint64_t ZipArchive::data_offset(const Entry& e) const {
    if (!offsets_ || e.index >= count_) return 0;
    uint64_t off = offsets_[e.index].load(std::memory_order_acquire);
    if (off) return off;
    // minizip-ng reads the local header (its name and extra field lengths); the stream then
    // stands at the entry's data.
    std::lock_guard<std::mutex> lock(mu_);
    if (mz_zip_goto_entry(handle_, e.cd_pos) == MZ_OK && mz_zip_entry_read_open(handle_, 1, nullptr) == MZ_OK) {
        int64_t t = mz_stream_tell(stream_);
        mz_zip_entry_close(handle_);
        if (t > 0 && (uint64_t)t <= size_ && e.comp_size <= size_ - (uint64_t)t) off = (uint64_t)t;
    }
    if (off) offsets_[e.index].store(off, std::memory_order_release);
    return off;
}

const uint8_t* ZipArchive::stored_data(const Entry& e) const {
    if (e.method != 0) return nullptr;
    uint64_t off = data_offset(e);
    return off ? map_ + off : nullptr;
}

bool ZipArchive::extract(const Entry& e, std::vector<uint8_t>& out) const {
    uint64_t off = data_offset(e);
    if (!off) return false;
    out.resize((size_t)e.size);
    if (e.method == 0) {
        if (e.comp_size != e.size) return false;
        memcpy(out.data(), map_ + off, (size_t)e.size);
        return true;
    }
    if (e.method != MZ_COMPRESS_METHOD_DEFLATE) return false;
    size_t at = 0;
    uint32_t crc = 0;
    bool ok = inflate_entry(map_ + off, e.comp_size, e.size, [&](const uint8_t* p, size_t n) {
        memcpy(out.data() + at, p, n);
        crc = mz_crypt_crc32_update(crc, p, (int32_t)n);
        at += n;
    });
    return ok && at == e.size && crc == e.crc;
}

int64_t ZipArchive::read(const Entry& e, uint64_t off, void* buf, size_t len) const {
    if (off >= e.size) return 0;
    if (len > e.size - off) len = (size_t)(e.size - off);
    uint64_t doff = data_offset(e);
    if (!doff) return -1;
    if (e.method == 0) {
        if (e.comp_size != e.size) return -1;
        memcpy(buf, map_ + doff + off, len);
        return (int64_t)len;
    }
    if (e.method != MZ_COMPRESS_METHOD_DEFLATE) return -1;
    uint64_t pos = 0;
    size_t got = 0;
    bool ok = inflate_entry(map_ + doff, e.comp_size, off + len, [&](const uint8_t* p, size_t n) {
        uint64_t end = pos + n;
        if (end > off) {
            uint64_t from = pos < off ? off - pos : 0;
            memcpy((uint8_t*)buf + got, p + from, (size_t)(n - from));
            got += (size_t)(n - from);
        }
        pos = end;
    });
    return ok ? (int64_t)got : -1;
}

}  // namespace soa

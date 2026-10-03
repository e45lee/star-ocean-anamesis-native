#include "android/zip.h"

#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <zlib.h>

#include <cstring>

#include "core/log.h"

namespace soa {

namespace {
template <typename T>
T rd(const uint8_t* p) {
    T v;
    memcpy(&v, p, sizeof v);
    return v;
}
}  // namespace

bool ZipArchive::open(const std::string& path) {
    path_ = path;
    if (!hostmem::map_file(path, &file_)) return false;
    map_ = file_.data;
    size_ = file_.size;

    // End of central directory (with possible comment), and ZIP64 locator.
    if (size_ < 22) return false;
    size_t eocd = 0;
    for (size_t i = size_ - 22; i + 1 > 0 && size_ - i < 70000; i--) {
        if (rd<uint32_t>(map_ + i) == 0x06054b50) {
            eocd = i;
            break;
        }
        if (i == 0) break;
    }
    if (!eocd) return false;
    uint64_t cd_off = rd<uint32_t>(map_ + eocd + 16);
    uint64_t cd_count = rd<uint16_t>(map_ + eocd + 10);
    if ((cd_off == 0xffffffff || cd_count == 0xffff) && eocd >= 20 && rd<uint32_t>(map_ + eocd - 20) == 0x07064b50) {
        uint64_t z64 = rd<uint64_t>(map_ + eocd - 20 + 8);
        cd_count = rd<uint64_t>(map_ + z64 + 32);
        cd_off = rd<uint64_t>(map_ + z64 + 48);
    }
    const uint8_t* p = map_ + cd_off;
    for (uint64_t i = 0; i < cd_count; i++) {
        if (rd<uint32_t>(p) != 0x02014b50) {
            LOGE("zip", "%s: bad central directory entry", path.c_str());
            return false;
        }
        Entry e;
        e.method = rd<uint16_t>(p + 10);
        e.comp_size = rd<uint32_t>(p + 20);
        e.size = rd<uint32_t>(p + 24);
        uint16_t nlen = rd<uint16_t>(p + 28), xlen = rd<uint16_t>(p + 30), clen = rd<uint16_t>(p + 32);
        e.local_header = rd<uint32_t>(p + 42);
        // ZIP64 extra field
        const uint8_t* x = p + 46 + nlen;
        for (const uint8_t* xe = x + xlen; x + 4 <= xe;) {
            uint16_t id = rd<uint16_t>(x), len = rd<uint16_t>(x + 2);
            if (id == 1) {
                const uint8_t* q = x + 4;
                if (e.size == 0xffffffff) e.size = rd<uint64_t>(q), q += 8;
                if (e.comp_size == 0xffffffff) e.comp_size = rd<uint64_t>(q), q += 8;
                if (e.local_header == 0xffffffff) e.local_header = rd<uint64_t>(q);
            }
            x += 4 + len;
        }
        entries_.emplace(std::string((const char*)p + 46, nlen), e);
        p += 46 + nlen + xlen + clen;
    }
    return true;
}

ZipArchive::~ZipArchive() {
    hostmem::unmap_file(file_);
}

const ZipArchive::Entry* ZipArchive::find(const std::string& name) const {
    auto it = entries_.find(name);
    return it == entries_.end() ? nullptr : &it->second;
}

uint64_t ZipArchive::data_offset(const Entry& e) const {
    const uint8_t* lh = map_ + e.local_header;
    return e.local_header + 30 + rd<uint16_t>(lh + 26) + rd<uint16_t>(lh + 28);
}

const uint8_t* ZipArchive::stored_data(const Entry& e) const {
    if (e.method != 0) return nullptr;
    return map_ + data_offset(e);
}

bool ZipArchive::extract(const Entry& e, std::vector<uint8_t>& out) const {
    const uint8_t* src = map_ + data_offset(e);
    out.resize(e.size);
    if (e.method == 0) {
        memcpy(out.data(), src, e.size);
        return true;
    }
    if (e.method != 8) return false;
    z_stream zs{};
    if (inflateInit2(&zs, -MAX_WBITS) != Z_OK) return false;
    zs.next_in = (Bytef*)src;
    zs.avail_in = (uInt)e.comp_size;
    zs.next_out = out.data();
    zs.avail_out = (uInt)e.size;
    int r = inflate(&zs, Z_FINISH);
    inflateEnd(&zs);
    return r == Z_STREAM_END;
}

}  // namespace soa

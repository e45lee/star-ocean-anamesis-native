// AFF containers: the AMF data buffers and the index-list codecs (soa/aff.h).
#include <soa/aff.h>

#include <soa/adld.h>
#include <soa/aska_image.h>

#include <cstdio>

namespace soa::aff {

std::string Auid::hex() const {
    char s[33];
    for (int i = 0; i < 16; i++) snprintf(s + i * 2, 3, "%02x", b[i]);
    return s;
}

// The AMF chunk ends the file. Its entries are chunks too; the data buffers follow it back to back
// to the end of the AMF chunk, each padded to 16 bytes, in 'buff' order (the decoded SLZ output has
// no other record of where they start: the 'buff' +0x18 offsets are the authoring tool's layout).
bool Amf::parse(const Bytes& d, std::string* err) {
    d_ = &d;
    amf_ = SIZE_MAX;
    buffers_.clear();
    blocks_.clear();
    // The AMF chunk follows the file's top-level chunk (the AskaFile: its +4 is its size).
    size_t pos = 0;
    if (d.size() >= 16) pos = rd32(&d[4]);
    if (pos + 16 > d.size() || !tag_is(&d[pos], " FMA")) {
        // Not at the expected place: look for it (some files carry an extra chunk first).
        pos = SIZE_MAX;
        for (size_t p = 0; p + 16 <= d.size(); p += 16)
            if (tag_is(&d[p], " FMA")) { pos = p; break; }
        if (pos == SIZE_MAX) { if (err) *err = "no AMF chunk"; return false; }
    }
    size_t end = pos + rd32(&d[pos + 4]);
    if (end > d.size()) { if (err) *err = "AMF chunk runs past the end"; return false; }
    amf_ = pos;
    for (size_t p = pos + 0x10; p + 16 <= end;) {
        uint32_t next = rd32(&d[p + 0xc]);
        if (tag_is(&d[p], "ffub") && p + 0x38 <= end) {
            Buffer b;
            b.size = rd64(&d[p + 0x10]);
            b.offset = rd64(&d[p + 0x18]);
            b.type = (int16_t)rd16(&d[p + 0x2c]);
            b.decoded_size = rd64(&d[p + 0x30]);
            buffers_.push_back(b);
        } else if (tag_is(&d[p], "rdda") && p + 0x50 <= end) {
            Block b;
            b.size = rd64(&d[p + 0x20]);
            b.offset = rd64(&d[p + 0x28]);
            b.align = rd32(&d[p + 0x30]);
            b.buffer_type = (int16_t)rd16(&d[p + 0x3c]);
            b.kind = d[p + 0x3e];
            b.flags = d[p + 0x3f];
            b.decoded_size = rd64(&d[p + 0x48]);
            blocks_[auid_at(&d[p + 0x10])] = b;
        }
        if (next == 0) break;
        p += next;
    }
    size_t e = end;
    for (size_t i = buffers_.size(); i-- > 0;) {
        uint64_t n = (buffers_[i].size + 15) & ~uint64_t(15);
        if (n > e - (pos + 0x10)) { if (err) *err = "AMF buffers larger than the chunk"; return false; }
        e -= n;
        buffers_[i].start = e;
    }
    return true;
}

const Block* Amf::find(const Auid& a) const {
    auto it = blocks_.find(a);
    return it == blocks_.end() ? nullptr : &it->second;
}

const Buffer* Amf::buffer_of(const Block& b) const {
    for (const Buffer& f : buffers_)
        if (f.type == b.buffer_type) return &f;
    return nullptr;
}

const uint8_t* Amf::raw_block(const Auid& a, size_t* n) const {
    const Block* b = find(a);
    if (!b) return nullptr;
    const Buffer* f = buffer_of(*b);
    if (!f || f->type != 0 || b->offset + b->size > f->size || f->start + b->offset + b->size > d_->size()) return nullptr;
    if (n) *n = (size_t)b->size;
    return d_->data() + f->start + b->offset;
}

bool Amf::block(const Auid& a, Bytes& out, std::string* err) const {
    const Block* b = find(a);
    if (!b) { if (err) *err = "unknown block " + a.hex(); return false; }
    const Buffer* f = buffer_of(*b);
    if (!f || b->offset + b->size > f->size || f->start + b->offset + b->size > d_->size()) {
        if (err) *err = "block " + a.hex() + " outside its buffer";
        return false;
    }
    const uint8_t* src = d_->data() + f->start + b->offset;
    int t = f->type < 0 ? -f->type : f->type;
    if (t >= 7 && t <= 18) {
        out.assign((size_t)b->decoded_size, 0);
        bool ok = t <= 12 ? decompress_triangle_list(src, (size_t)b->size, out.data(), out.size())
                          : decompress_index_buffer(src, (size_t)b->size, out.data(), out.size());
        if (!ok) { if (err) *err = "block " + a.hex() + " does not decompress"; return false; }
        return true;
    }
    out.assign(src, src + b->size);
    return true;
}

bool decompress_triangle_list(const uint8_t* src, size_t src_size, uint8_t* dst, size_t dst_size) {
    size_t n = src_size / 2;
    if (n == 0) return true;
    n -= 1;  // codes after the constant
    uint16_t K = rd16(src);
    const uint8_t* c = src + 2;
    auto code = [&](size_t i) -> uint32_t { return i < n ? rd16(c + i * 2) : 0; };
    size_t out = 0, cap = dst_size / 2;
    auto put = [&](std::initializer_list<uint32_t> v) {
        if (out + v.size() > cap) return false;
        for (uint32_t x : v) {
            uint16_t s = (uint16_t)x;
            memcpy(dst + out * 2, &s, 2);
            out++;
        }
        return true;
    };
    size_t i = 0;
    if (K == 0xffff) {
        while (i < n) {
            uint32_t a = code(i), b = code(i + 1), cc = code(i + 2);
            if (a < b) {
                if (!put({a, b, cc, a, code(i + 3), b})) return false;
                i += 4;
            } else {
                if (!put({a, b, cc})) return false;
                i += 3;
            }
        }
        return true;
    }
    uint32_t hw = (uint32_t)K + 0xffff;
    while (i < n) {
        hw &= 0xffff;
        uint32_t a = (hw - code(i)) & 0xffff;
        if (hw <= a + K) hw = a + K;
        hw &= 0xffff;
        uint32_t b = (hw - code(i + 1)) & 0xffff;
        if (hw <= b + K) hw = b + K;
        hw &= 0xffff;
        uint32_t cc = (hw - code(i + 2)) & 0xffff;
        if (hw <= cc + K) hw = cc + K;
        if (a < b) {
            hw &= 0xffff;
            uint32_t d = (hw - code(i + 3)) & 0xffff;
            if (!put({a, b, cc, a, d, b})) return false;
            if (hw <= d + K) hw = d + K;
            i += 4;
        } else {
            if (!put({a, b, cc})) return false;
            i += 3;
        }
    }
    return true;
}

namespace {
// Aska::BitStreamReader: bits LSB first; a read past the end returns 0 and doesn't advance.
struct Bits {
    const uint8_t* p;
    uint64_t pos = 0, total;
    Bits(const uint8_t* d, size_t n) : p(d), total((uint64_t)n * 8) {}
    uint32_t u(unsigned n) {
        if (pos + n > total) return 0;
        uint32_t v = 0;
        for (unsigned i = 0; i < n; i++, pos++) v |= (uint32_t)((p[pos >> 3] >> (pos & 7)) & 1) << i;
        return v;
    }
    int32_t s(unsigned n) {
        uint32_t v = u(n);
        unsigned sh = (32 - n) & 31;
        return (int32_t)(v << sh) >> sh;
    }
};
}  // namespace

bool decompress_index_buffer(const uint8_t* src, size_t src_size, uint8_t* dst, size_t dst_size) {
    Bits r(src, src_size);
    size_t cap = dst_size / 2;
    uint32_t count = r.u(32);
    uint16_t first = (uint16_t)r.u(16);
    if (cap == 0) return false;
    std::vector<uint16_t> out(cap, 0);
    // (the output is written in place in the game; collected here, then copied)
    out[0] = first;
    if (count >= 2) {
        unsigned bits = 3;
        size_t i = 1;
        do {
            uint32_t run = r.u(16) & 0xffff;
            for (uint32_t k = 0; k < run; k++) {
                if (i >= cap) return false;
                out[i] = (uint16_t)(out[i - 1] + (int16_t)r.s(bits));
                i++;
            }
            if (bits > 4 && i < count) {
                if (i >= cap) return false;
                out[i++] = (uint16_t)r.u(16);
                bits = 2;
            }
            bits++;
        } while (bits < 32 && i < count);
    }
    memcpy(dst, out.data(), cap * 2);
    return true;
}

bool decode_game_file(const std::string& name, const Bytes& src, Bytes& out, std::string* err) {
    Bytes plain = adld::is_adld(src.data(), src.size()) ? adld::decrypt(name, src) : src;
    if (aska::is_slz(plain)) {
        if (!aska::slz_decode(plain, out, err)) return false;
        return true;
    }
    out.swap(plain);
    return true;
}

std::string game_name_of(const std::string& path) {
    static const char* const kTop[] = {"Character/", "Motion/", "Weapon/", "BG/", "MapHome/", "Deco/", "Effect/",
                                       "Camera/", "Image/", "TalkScene/", "UI/", "Parameter/", "Script/", "Sound/",
                                       "EP1/", "EP2/", "EP3/", "Scenario/", "Font/", "Shader/", "Movie/"};
    std::string p = path;
    for (char& c : p)
        if (c == '\\') c = '/';
    size_t best = std::string::npos;
    for (const char* t : kTop) {
        for (size_t at = p.find(t); at != std::string::npos; at = p.find(t, at + 1))
            if ((at == 0 || p[at - 1] == '/') && (best == std::string::npos || at < best)) { best = at; break; }
    }
    return best == std::string::npos ? "" : p.substr(best);
}

}  // namespace soa::aff

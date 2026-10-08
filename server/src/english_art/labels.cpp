// The layout labels of a scene's node tree (docs/english.md 7.14): the str values of its
// LabelText / ButtonText keys, read and replaced in the raw msgpack stream. Every other byte of the
// stream is copied as it is (int keys, bin, ext, float32 and the encoder's choice of headers stay
// the game's), so a tree without a replaced label comes back byte for byte.
// (b) the keys: the scenes' TextObjectData nodes carry their text as LabelText, the two
// ButtonObjectData texts as ButtonText (a dump of the 853 3.7.0 scenes); (d) the rewrite
// (docs/server-rules.md#english-labels).
#include <cstring>

#include "english_art/art.h"

namespace soa::server::english_art {
namespace {

uint64_t be(const uint8_t* p, int n) {
    uint64_t v = 0;
    for (int i = 0; i < n; i++) v = v << 8 | p[i];
    return v;
}

bool is_label_key(const uint8_t* s, size_t n) { return (n == 9 && !memcmp(s, "LabelText", 9)) || (n == 10 && !memcmp(s, "ButtonText", 10)); }

struct Walker {
    const Bytes& in;
    const LabelFn& fn;
    Bytes* out;  // nullptr: only read
    size_t replaced = 0;
    std::string err;

    void emit(size_t from, size_t to) {
        if (out) out->insert(out->end(), in.begin() + from, in.begin() + to);
    }
    // A str at p: its payload [*s, *s + *n); false when p isn't a str.
    bool str_at(size_t p, size_t* s, size_t* n, size_t* end) {
        uint8_t b = in[p];
        int hl;
        if (b >= 0xa0 && b <= 0xbf) hl = 0, *n = b & 0x1f;
        else if (b == 0xd9) hl = 1;
        else if (b == 0xda) hl = 2;
        else if (b == 0xdb) hl = 4;
        else return false;
        if (p + 1 + hl > in.size()) return false;
        if (hl) *n = (size_t)be(&in[p + 1], hl);
        *s = p + 1 + hl;
        *end = *s + *n;
        return *end <= in.size();
    }
    // Writes a str with the smallest header (msgpack's own rule).
    void put_str(const std::string& v) {
        size_t n = v.size();
        if (n < 32) out->push_back((uint8_t)(0xa0 | n));
        else if (n < 0x100) out->insert(out->end(), {0xd9, (uint8_t)n});
        else if (n < 0x10000) out->insert(out->end(), {0xda, (uint8_t)(n >> 8), (uint8_t)n});
        else out->insert(out->end(), {0xdb, (uint8_t)(n >> 24), (uint8_t)(n >> 16), (uint8_t)(n >> 8), (uint8_t)n});
        out->insert(out->end(), v.begin(), v.end());
    }
    // One object at p; its end in *end. `label`: the value of a LabelText / ButtonText key.
    bool object(size_t p, size_t* end, bool label, int depth) {
        if (depth > 512) return err = "nested too deep", false;
        if (p >= in.size()) return err = "truncated", false;
        uint8_t b = in[p];
        size_t s, n;
        if (str_at(p, &s, &n, end)) {
            const std::string* rep = nullptr;
            if (label) rep = fn(std::string((const char*)&in[s], n));
            if (rep && out) {
                put_str(*rep);
                replaced++;
            } else {
                if (rep) replaced++;
                emit(p, *end);
            }
            return true;
        }
        size_t count = 0, hl = 0;
        bool map = false;
        if (b <= 0x7f || b >= 0xe0 || b == 0xc0 || b == 0xc2 || b == 0xc3) return emit(p, *end = p + 1), true;
        if (b >= 0x80 && b <= 0x8f) map = true, count = b & 0x0f;
        else if (b >= 0x90 && b <= 0x9f) count = b & 0x0f;
        else if (b == 0xdc || b == 0xdd || b == 0xde || b == 0xdf) {
            hl = (b == 0xdc || b == 0xde) ? 2 : 4;
            map = b >= 0xde;
            if (p + 1 + hl > in.size()) return err = "truncated", false;
            count = (size_t)be(&in[p + 1], (int)hl);
        } else {
            // scalars of a fixed or prefixed size: copied whole
            size_t len;
            switch (b) {
                case 0xcc:
                case 0xd0:
                    len = 2;
                    break;
                case 0xcd:
                case 0xd1:
                    len = 3;
                    break;
                case 0xca:
                case 0xce:
                case 0xd2:
                    len = 5;
                    break;
                case 0xcb:
                case 0xcf:
                case 0xd3:
                    len = 9;
                    break;
                case 0xd4:
                    len = 3;
                    break;
                case 0xd5:
                    len = 4;
                    break;
                case 0xd6:
                    len = 6;
                    break;
                case 0xd7:
                    len = 10;
                    break;
                case 0xd8:
                    len = 18;
                    break;
                case 0xc4:
                case 0xc5:
                case 0xc6:
                case 0xc7:
                case 0xc8:
                case 0xc9: {
                    int w = (b == 0xc4 || b == 0xc7) ? 1 : (b == 0xc5 || b == 0xc8) ? 2 : 4;
                    if (p + 1 + w > in.size()) return err = "truncated", false;
                    len = 1 + w + (size_t)be(&in[p + 1], w) + (b >= 0xc7 ? 1 : 0);  // ext: + its type byte
                    break;
                }
                default:
                    return err = "bad msgpack byte " + std::to_string(b) + " at " + std::to_string(p), false;
            }
            if (p + len > in.size()) return err = "truncated", false;
            return emit(p, *end = p + len), true;
        }
        size_t q = p + 1 + hl;
        emit(p, q);
        for (size_t i = 0; i < count; i++) {
            bool is_label = false;
            if (map) {
                size_t ks, kn, kend;
                if (q < in.size() && str_at(q, &ks, &kn, &kend)) is_label = is_label_key(&in[ks], kn);
                if (!object(q, &q, false, depth + 1)) return false;
            }
            if (!object(q, &q, is_label, depth + 1)) return false;
        }
        *end = q;
        return true;
    }
};

}  // namespace

bool rewrite_labels(const Bytes& msgp, const LabelFn& fn, Bytes* out, size_t* replaced, std::string* err) {
    Walker w{msgp, fn, out};
    if (out) out->clear(), out->reserve(msgp.size() + 256);
    size_t p = 0;
    while (p < msgp.size())  // one object in the files; a stream of several is walked the same way
        if (!w.object(p, &p, false, 0)) {
            if (err) *err = w.err;
            return false;
        }
    if (replaced) *replaced = w.replaced;
    return true;
}

}  // namespace soa::server::english_art

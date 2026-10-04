// The shader cache's LZ word compressor: Aska::ShaderComprssionTree (sic: the guest's spelling) and
// Aska::ShaderCompression::CompressLZwordDic, from port/decomp/render/shader_compression.c.
//
// At boot the AHSL cache thread decompresses every compressed shader-cache entry, creates its GL shader and
// compresses the entry again in place (AHSLCacheManagerV2::BuildLinkedDiskCacheL2 ->
// AHSLBase::CreateCompressedShaderCache -> CompressLZwordDic; port/decomp/render/shader_cache.c): the
// guest's hottest render code (InsertNode 3,125 self samples, CompressLZwordDic 3,803 inclusive, ~1.1% of
// all busy samples). The output is stored back into the cache, so the native is bit-exact: the same tree
// (Okumura's LZSS binary tree over 16-bit words), the same match choices, the same bytes.
//
// Live check (soa --live-check render): CompressLZwordDic runs native into the caller's buffer, then the
// guest original (its trampoline) into a scratch buffer, and the sizes and bytes are compared. The
// original's InsertNode / DeleteNode calls land in these natives (they're hooked too), so the live check
// proves the composite; the tree members alone are proved by render/shader-compression-tree (guest vs
// native tree, every word of it, after each call).
#include <cstring>
#include <memory>
#include <new>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "native/common/live_run_both.h"
#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/render/render_check.h"
#include "native/render/render_layout.h"

namespace soa::native::render {

// ---- Aska::ShaderComprssionTree ----

void ShaderComprssionTree::Ctor() {
    for (s32 w = 0; w < 0x10000; w++) m_right[0x1001 + w] = kNil;  // every root
    for (s32 i = 0; i < kNil; i++) m_parent[i] = kNil;           // every node out of the tree
}

// Inserts window position r: walks the tree of r's first word comparing the words after it
// (`maxLen` words at most, the window indices wrapping at 0x1000), records the longest match in
// m_matchPos / m_matchLen, and links r where the walk ends; a match of the full `maxLen` replaces the
// old node by r (the newer position is the nearer one).
void ShaderComprssionTree::InsertNode(s32 r, s32 maxLen) {
    m_left[r] = kNil;
    m_right[r] = kNil;
    s32 p = m_text[r] + 0x1001;  // the root slot of r's first word (an index into m_right)
    m_matchLen = 0;
    if (maxLen < 2) {
        s32 q = m_right[p];
        if (q == kNil) {
            m_right[p] = r;
            m_parent[r] = p;
            return;
        }
        m_matchPos = q;
        m_matchLen = 1;
        p = q;
    } else {
        s32 cmp = 1, best = 0;
        bool differ;
        do {
            s32 i;
            do {
                s32* link = cmp < 0 ? &m_left[p] : &m_right[p];
                if (*link == kNil) {
                    *link = r;
                    m_parent[r] = p;
                    return;
                }
                p = *link;
                differ = false;
                cmp = 0;
                for (i = 1; i < maxLen; i++) {
                    cmp = m_text[(r + i) & 0xfff] - m_text[(p + i) & 0xfff];
                    if (cmp != 0) {
                        differ = true;
                        break;
                    }
                }
                if (!differ) cmp = 0;
            } while (i <= best);  // not longer than the best so far: keep descending
            m_matchPos = p;
            m_matchLen = i;
            best = i;
        } while (differ);
    }
    // r takes p's place (p's children, p's parent's link), p leaves the tree
    m_parent[r] = m_parent[p];
    m_left[r] = m_left[p];
    m_right[r] = m_right[p];
    m_parent[m_left[p]] = r;   // (NIL children: m_parent[0x1000], a scratch slot)
    m_parent[m_right[p]] = r;
    s32 pp = m_parent[p];
    if (m_right[pp] == p) m_right[pp] = r;
    else m_left[pp] = r;
    m_parent[p] = kNil;
}

// Removes window position p (a no-op when it isn't in the tree): a node with one child is replaced
// by it, one with two by its in-order predecessor (the rightmost node of the left subtree).
void ShaderComprssionTree::DeleteNode(s32 p) {
    if (m_parent[p] == kNil) return;
    s32 q;
    if (m_right[p] == kNil) {
        q = m_left[p];
    } else if (m_left[p] == kNil) {
        q = m_right[p];
    } else {
        q = m_left[p];
        if (m_right[q] != kNil) {
            do q = m_right[q];
            while (m_right[q] != kNil);
            m_right[m_parent[q]] = m_left[q];
            m_parent[m_left[q]] = m_parent[q];
            m_left[q] = m_left[p];
            m_parent[m_left[p]] = q;
        }
        m_right[q] = m_right[p];
        m_parent[m_right[p]] = q;
    }
    m_parent[q] = m_parent[p];
    s32 pp = m_parent[p];
    if (m_right[pp] == p) m_right[pp] = q;
    else m_left[pp] = q;
    m_parent[p] = kNil;
}

// ---- Aska::ShaderCompression::CompressLZwordDic ----

namespace {

inline s32 be16(const u8* p) { return (s32)((u32)p[0] << 8 | p[1]); }

// Writes `n` code words big-endian (the guest swaps each u16 of its code buffer into the output).
inline void put_words(u8*& out, const u16* words, s32 n) {
    for (s32 i = 0; i < n; i++) {
        *out++ = (u8)(words[i] >> 8);
        *out++ = (u8)words[i];
    }
}

}  // namespace

// Compresses `size` bytes at src (as size / 2 big-endian words) into dst with the 0x2000-byte dictionary
// `dic` priming the window; returns the compressed size in bytes (0 when the tree can't be allocated).
// The format: groups of a big-endian flag word (bit k, LSB first: item k is a literal word) and up to 16
// items, a literal word or a match `(len - 2) << 12 | distance` (big-endian, distance in words), ended by a
// match of distance 0. Quirks kept from the guest: the lookahead fill reads one word past the input
// (two bytes past `size` when it's short), the input stops at size / 2 words with the last odd byte
// dropped, and a match never runs past the input's end (the clamp at the top of the loop).
s32 ShaderCompression::CompressLZwordDic(void* src_, s32 size, void* dst_, u8* dic) {
    const u8* src = static_cast<const u8*>(src_);
    u8* out = static_cast<u8*>(dst_);
    // The guest allocates the tree with operator new(nothrow) and frees it at the end; the heap never
    // sees it otherwise, so here it's host memory.
    std::unique_ptr<ShaderComprssionTree> mem(new (std::nothrow) ShaderComprssionTree);
    if (!mem) return 0;
    ShaderComprssionTree& t = *mem;
    t.Ctor();
    for (s32 i = 0; i < 0x1000; i++) t.m_text[i] = be16(dic + 2 * i);
    u16 code[17];  // the group being built: [0] the flags, then up to 16 items
    code[0] = 0;
    for (s32 r = 0x11; r < 0x1000; r++) t.InsertNode(r, ShaderComprssionTree::kMaxMatch);

    const s32 words = (size < 0 ? size + 1 : size) >> 1;
    // The lookahead: up to 17 words at window positions 0..; `len` of them count, `next` is the next
    // input word to read.
    s32 len, next;
    t.m_text[0] = be16(src);
    for (s32 k = 1;; k++) {
        if (size < 2 * k) {
            len = k - 1;
            next = k;
            break;
        }
        if (k == 16) {
            len = size > 0x21 ? 0x11 : 0x10;
            t.m_text[16] = be16(src + 0x20);
            next = 0x11;
            break;
        }
        t.m_text[k] = be16(src + 2 * k);
    }

    s32 s = 0x11;  // the window position the next input word goes to (the oldest one, deleted first)
    t.InsertNode(0, ShaderComprssionTree::kMaxMatch);
    s32 r = 0;      // the current position
    u32 mask = 1;   // this item's flag bit
    s32 cp = 1;     // the next item slot in code[]
    s32 total = 0;  // words written
    s32 seen = len; // input words consumed into the lookahead (with the initial ones)
    do {
        s32 n = t.m_matchLen < len ? t.m_matchLen : len;  // (matchLen <= len ? matchLen : len)
        const s32 over = seen + n - 0x10;
        if (words <= over) n = words - seen;
        bool literal;
        if (len < t.m_matchLen || words <= over) {
            t.m_matchLen = n;
            literal = n <= 1;
        } else {
            literal = n < 2;
        }
        u16 item;
        if (literal) {
            n = 1;
            t.m_matchLen = 1;
            item = (u16)t.m_text[r];
            code[0] |= (u16)mask;
        } else {
            item = (u16)((n * 0x1000 + 0xe000) | ((r - t.m_matchPos) & 0xfff));
        }
        code[cp] = item;
        s32 got;  // words read into the window for this item
        if (((mask << 1) & 0xfffe) == 0) {
            // the group is full: write it
            put_words(out, code, cp + 1);
            total += cp + 1;
            code[0] = 0;
            cp = 1;
            mask = 1;
            if (n <= 0) {
                got = 0;
                goto advance;
            }
        } else {
            mask = (mask << 1) & 0x1fffe;
            cp++;
        }
        {
            // read up to n more input words, sliding the window one position per word
            s32 i = 0, last = 0;
            for (;;) {
                last = i;
                if (words <= next + i) break;  // no more input (`next` then advances one extra)
                const u8* w = src + 2 * (next + i);
                t.DeleteNode(s);
                r = (r + 1) & 0xfff;
                t.m_text[s] = be16(w);
                s = (s + 1) & 0xfff;
                t.InsertNode(r, ShaderComprssionTree::kMaxMatch);
                i++;
                if (i >= n) {
                    last = i - 1;
                    break;
                }
            }
            got = i;
            next += last + 1;
        }
    advance:
        seen += got;
        // past the input's end: the window still slides n positions, the lookahead shrinks
        for (s32 k = got; k < n; k++) {
            t.DeleteNode(s);
            len--;
            s = (s + 1) & 0xfff;
            r = (r + 1) & 0xfff;
            if (len != 0) t.InsertNode(r, ShaderComprssionTree::kMaxMatch);
        }
    } while (len > 0);
    code[cp] = 0;  // the end: a match of distance 0
    put_words(out, code, cp + 1);
    total += cp + 1;
    return total << 1;
}

// ---- the natives ----

namespace {

live::RunBothFamily::Fn fCompress(fam(), "_ZN4Aska17ShaderCompression17CompressLZwordDicEPviS1_Ph");

void HostCompressLZwordDic(Cpu& c) {
    void* src = (void*)c.x(0);
    s32 size = (s32)c.x(1);
    void* dst = (void*)c.x(2);
    u8* dic = (u8*)c.x(3);
    if (__builtin_expect(!fam().due(fCompress), 1)) {
        c.set_x(0, (u32)ShaderCompression::CompressLZwordDic(src, size, dst, dic));
        return;
    }
    live::RunBothFamily::Scope scope;
    s32 n = ShaderCompression::CompressLZwordDic(src, size, dst, dic);
    std::vector<u8> scratch((size_t)(size > 0 ? size : 0) * 2 + 0x100, 0);
    s32 g = (s32)guest_call(fCompress.orig, {(u64)src, (u64)(u32)size, (u64)scratch.data(), (u64)dic});
    std::string why;
    if (g != n) why = "size: native " + std::to_string(n) + ", guest " + std::to_string(g) + " (input " + std::to_string(size) + " bytes)";
    else why = live::RunBothFamily::diff_bytes(dst, scratch.data(), (size_t)n);
    fam().result(fCompress, why.empty() ? live::RunBothFamily::Outcome::Ok : live::RunBothFamily::Outcome::Mismatch, why);
    c.set_x(0, (u32)n);
}

}  // namespace

NATIVE_METHOD("_ZN4Aska20ShaderComprssionTreeC2Ev", &ShaderComprssionTree::Ctor, "render: ShaderComprssionTree::ShaderComprssionTree");
NATIVE_METHOD("_ZN4Aska20ShaderComprssionTree10InsertNodeEii", &ShaderComprssionTree::InsertNode, "render: ShaderComprssionTree::InsertNode");
NATIVE_METHOD("_ZN4Aska20ShaderComprssionTree10DeleteNodeEi", &ShaderComprssionTree::DeleteNode, "render: ShaderComprssionTree::DeleteNode");
NATIVE_FUNCTION_ORIG("_ZN4Aska17ShaderCompression17CompressLZwordDicEPviS1_Ph", HostCompressLZwordDic,
                     "render: ShaderCompression::CompressLZwordDic", &fCompress.orig);

}  // namespace soa::native::render

// TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Descend / Ascend: the object manager's sort of
// the renderable objects by a float key (port/decomp/containers/arrays.c). An iterative quicksort
// (middle-element pivot, Hoare partition, an explicit stack of 64 ranges, ranges of 10 or fewer left
// unsorted) finished by one insertion sort over the whole range. Not stable: equal keys keep the order
// this exact partition gives them, which is the draw order, so the algorithm is the guest's step for
// step (never std::sort).
#include "native/common/live_leaf.h"
#include "native/containers/containers_family.h"
#include "native/containers/containers_layout.h"

namespace soa::native::containers {

namespace {

// The two fields the sort reads (the scene subsystem's classes; only these offsets are used here):
// Aska::RenderableObject's index into the context's per-object entries, and the entry's sort key.
struct RenderableObject {
    u8 unk_000[0x1b8];
    u16 m_contextIndex;  // 0x1b8
};
struct RenderableObjectContextEntry {
    u32 unk_0;
    float m_sortKey;  // 0x04
};
static_assert(offsetof(RenderableObject, m_contextIndex) == 0x1b8 && sizeof(RenderableObjectContextEntry) == 8);

}  // namespace

// TOMQuickSort<T, K, N, M>: static members only (N: the range stack, M: the insertion-sort cutoff).
struct TOMQuickSortRenderable {
    static void Descend(RenderableObject** a, s32 lo, s32 hi, const RenderableObjectContextEntry* ctx);
    static void Ascend(RenderableObject** a, s32 lo, s32 hi, const RenderableObjectContextEntry* ctx);
};

namespace {

// `Before(x, y)`: key x goes before key y (Descend: x > y, Ascend: x < y).
template <bool (*Before)(float, float), bool (*NotAfter)(float, float)>
void quick_sort(RenderableObject** a, s32 lo, s32 hi, const RenderableObjectContextEntry* ctx) {
    auto key = [&](const RenderableObject* o) { return ctx[o->m_contextIndex].m_sortKey; };
    if (lo == hi) return;
    s32 stack_l[64], stack_r[64];
    int sp = 0;
    s32 l = lo, r = hi - 1;
    for (;;) {
        if (r - l < 10) {
            if (sp == 0) break;
            --sp;
            l = stack_l[sp], r = stack_r[sp];
        }
        float pivot = key(a[(l + r) / 2]);
        s32 i = l, j = r;
        RenderableObject *x, *y;
        for (;;) {
            while (Before(key(x = a[i]), pivot)) i++;
            while (Before(pivot, key(y = a[j]))) j--;
            if (j <= i) break;
            a[i++] = y;
            a[j--] = x;
        }
        // left part [l, i - 1], right part [j + 1, r]: the larger one (if over 10) waits on the stack
        s32 left = i - l, right = r - j;
        if (right < left) {
            if (left > 10) stack_l[sp] = l, stack_r[sp] = i - 1, sp++;
            l = j + 1;
        } else {
            if (right > 10) stack_l[sp] = j + 1, stack_r[sp] = r, sp++;
            r = i - 1;
        }
    }
    for (s32 k = lo + 1; k < hi; k++) {  // insertion sort over everything
        RenderableObject* cur = a[k];
        float c = key(cur);
        s32 m = k - 1;
        // (the guest stops at the first key it may follow: !Before(key, c) as "<=" / ">=" on the
        // operands, so a NaN key keeps shifting)
        for (; m >= lo && !NotAfter(c, key(a[m])); m--) a[m + 1] = a[m];
        a[m + 1] = cur;
    }
}

bool greater(float x, float y) { return x > y; }
bool less(float x, float y) { return x < y; }
bool less_equal(float x, float y) { return x <= y; }     // Descend: c may follow k when c <= k
bool greater_equal(float x, float y) { return x >= y; }  // Ascend: when c >= k

}  // namespace

void TOMQuickSortRenderable::Descend(RenderableObject** a, s32 lo, s32 hi, const RenderableObjectContextEntry* ctx) { quick_sort<&greater, &less_equal>(a, lo, hi, ctx); }
void TOMQuickSortRenderable::Ascend(RenderableObject** a, s32 lo, s32 hi, const RenderableObjectContextEntry* ctx) { quick_sort<&less, &greater_equal>(a, lo, hi, ctx); }

// ---- natives ----

LEAF_FUNCTION(family(), "_ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE7DescendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE",
              &TOMQuickSortRenderable::Descend, live::kVoid, "TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Descend", {live::out_len(0, 2, 8)});
LEAF_FUNCTION(family(), "_ZN12TOMQuickSortIN4Aska16RenderableObjectEfLi64ELi10EE6AscendEPPS1_iiPNS0_13ObjectManager23RenderableObjectContextE",
              &TOMQuickSortRenderable::Ascend, live::kVoid, "TOMQuickSort<Aska::RenderableObject, float, 64, 10>::Ascend", {live::out_len(0, 2, 8)});

// (for the test)
void tom_quick_sort(bool descend, void** a, s32 lo, s32 hi, const void* ctx) {
    if (descend) TOMQuickSortRenderable::Descend((RenderableObject**)a, lo, hi, (const RenderableObjectContextEntry*)ctx);
    else TOMQuickSortRenderable::Ascend((RenderableObject**)a, lo, hi, (const RenderableObjectContextEntry*)ctx);
}

}  // namespace soa::native::containers

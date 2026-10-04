// Aska::TPoolFast<unsigned char[90], true>::Scoop(int) / Sink(T*, int): the object manager's pool of
// 90-byte shader-key links (containers_layout.h TPoolFastLocked; port/decomp/containers/pool.c). A
// used-bit per slot (64-bit words); Scoop looks for n free slots in a row from the cursor (or from 0
// when that window would pass the end), skipping past each used slot it meets, under the pool's
// FastCriticalSection (sync's Enter / Leave: the guest inlines the same code).
#include "native/containers/containers_family.h"
#include "native/containers/containers_layout.h"

namespace soa::native::containers {

namespace {

// Bits [first, first + n) of the bit words: true when all clear.
bool range_free(const u64* words, s32 first, s32 n) {
    s32 word = first >> 6, bit = first & 63;  // (first >= 0)
    for (s32 rem = n; rem > 0; word++, bit = 0) {
        u64 mask = rem >= 64 ? ~0ull : ~0ull >> (64 - rem);
        if ((mask << bit) & words[word]) return false;
        s32 take = rem < 64 ? rem : 64;
        if (take > 64 - bit) take = 64 - bit;
        rem -= take;
    }
    return true;
}

// Sets (or clears) bits [first, first + n): the first word from `bit` on, then whole words, the last
// one's low bits (the guest's two loops).
void set_range(u64* words, s32 first, s32 n, bool on) {
    s32 word = first >> 6, bit = first & 63;
    u64 mask = (n >= 64 ? ~0ull : ~0ull >> (64 - n)) << bit;
    words[word] = on ? words[word] | mask : words[word] & ~mask;
    s32 take = n < 64 ? n : 64;
    if (take > 64 - bit) take = 64 - bit;
    for (s32 rem = n - take; rem != 0; rem -= take) {
        word++;
        take = rem < 64 ? rem : 64;
        u64 m = rem >= 64 ? ~0ull : ~0ull >> (64 - rem);
        words[word] = on ? words[word] | m : words[word] & ~m;
    }
}

}  // namespace

template <typename T>
T* TPoolFastLocked<T>::Scoop(s32 n) {
    m_lock.Enter();
    T* result = nullptr;
    u32 cap = m_used.m_numBits;
    if (m_count + (u32)n <= cap) {
        // the window: from the cursor when it fits before the end, else from 0; `last` tracks how far
        // the search has gone (it fails once that passes the capacity)
        bool from_cursor = (s32)(m_cursor + n) <= (s32)cap;
        s32 start = from_cursor ? (s32)m_cursor : 0;
        s32 last = from_cursor ? n - 1 : (s32)(cap + n - 1 - m_cursor);
        while (last < (s32)cap) {
            if (n == 0 || range_free(m_used.m_bits, start, n)) {
                if (n) set_range(m_used.m_bits, start, n, true);
                u32 next = (u32)start + (u32)n;
                m_cursor = cap ? next % cap : next;
                m_count += n;
                result = m_pool + start;
                break;
            }
            // the last used slot in the window: start again after it, or from 0 when that window
            // would pass the end; `last` grows by the slots passed over (and the wrap's rest)
            s32 used = start + n - 1;
            while (!((m_used.m_bits[(u32)used >> 6] >> (used & 63)) & 1)) used--;
            s32 wrapped = 0;
            s32 old_start = start;
            if (used + 1 + n <= (s32)cap) {
                start = used + 1;
            } else {
                wrapped = (s32)cap - 1 - used;
                start = 0;
            }
            last += wrapped + (used - old_start + 1);
        }
    }
    m_lock.Leave();
    return result;
}

template <typename T>
bool TPoolFastLocked<T>::Sink(T* p, s32 n) {
    m_lock.Enter();
    // the slot index: (p - pool) / 90, computed as the guest does (a 32-bit multiply by the inverse of 45)
    s32 index = (s32)((u32)((u64)((u8*)p - (u8*)m_pool) >> 1) * 0xa4fa4fa5u);
    if (n != 0) set_range(m_used.m_bits, index, n, false);
    m_count -= n;
    m_lock.Leave();
    return true;
}

template class TPoolFastLocked<Opaque<90>>;

// ---- natives ----

namespace {
using Pool90 = TPoolFastLocked<Opaque<90>>;
void Scoop90(Cpu& c) { c.set_x(0, (u64)reinterpret_cast<Pool90*>(c.x(0))->Scoop((s32)c.x(1))); }
void Sink90(Cpu& c) { c.set_x(0, reinterpret_cast<Pool90*>(c.x(0))->Sink(reinterpret_cast<Opaque<90>*>(c.x(1)), (s32)c.x(2))); }
void pool_regions(const u64 x[9], live::Regions& r) {  // the used-bit words
    if (const Pool90* p = reinterpret_cast<const Pool90*>(x[0]); p && p->m_used.m_bits && p->m_used.m_numWords)
        r.add((u64)p->m_used.m_bits, p->m_used.m_numWords * 8);
}
}  // namespace

CONTAINERS_HOSTFN("_ZN4Aska9TPoolFastIA90_hLb1EE5ScoopEi", &Scoop90, sizeof(Pool90), live::kInt, "Aska::TPoolFast<unsigned char[90], true>::Scoop(int)",
                  &pool_regions);
CONTAINERS_HOSTFN("_ZN4Aska9TPoolFastIA90_hLb1EE4SinkEPS1_i", &Sink90, sizeof(Pool90), live::kInt, "Aska::TPoolFast<unsigned char[90], true>::Sink",
                  &pool_regions);

}  // namespace soa::native::containers

// Aska::ASON's bump allocator and string reader: Malloc, UnpackValue_str (data_formats_layout.h;
// port/decomp/data_formats/ason.c).
#include "native/containers/containers_dynamic_array.h"
#include "native/containers/containers_layout.h"
#include "native/data_formats/data_formats_ason.h"

namespace soa::native::data_formats {

// Bumps the current block (4-aligned); when it doesn't fit, a new block of m_totalWorkSize bytes
// (the sum so far: the blocks double) becomes the current one and m_workIndex counts it. 0 for 0
// bytes, and when no block can be had (the guest then asks the memory manager for its free size, a
// leftover of a report).
void* ASON::Malloc(u64 n) {
    if (n == 0) return nullptr;
    ASON_WorkBufferContext* w = m_currentWork;
    for (;;) {
        u64 used = w->m_used, end = used + ((n + 3) & ~u64(3));
        if (end <= w->m_size) {
            w->m_used = end;
            if (s8* p = w->m_buffer + used) return p;
        }
        u64 size = m_totalWorkSize;
        auto* block = (s8*)ason::new_array_nothrow(size);
        if (!block) break;
        ASON_WorkBufferContext added{block, size, 0, true, {}};
        m_work.InsertFill(m_work.m_end, 1, 1, &added);
        w = m_currentWork = m_work.m_end - 1;
        m_totalWorkSize += size;
        m_workIndex++;
    }
    static const u64 get_mm = main_lib()->sym("_ZN4Aska6Global25GetAvailableMemoryManagerEv");
    static const u64 calc_free = main_lib()->sym("_ZN4Aska13MemoryManager12CalcFreeSizeEb");
    u64 mm = live::out_call(family(), get_mm, {});
    live::out_call(family(), calc_free, {mm, 0});
    return nullptr;
}

// v = the string at p (len bytes of the input, not copied), stamped with `work`. With m_keepCStrings
// (and a non-empty string) also a terminated copy from Malloc, made through a temporary (from the
// m_temp scratch when it fits, else new[]) and Utf8ToMultiByte, which stops at an embedded NUL.
s32 ASON::UnpackValue_str(AValue* v, const s8* base, const s8* p, u32 len, u16 work) {
    v->m_body.str.m_data = (const char*)p;
    v->m_length = len;
    v->m_kind = AValue::kString;
    v->m_dataWork = work;
    if (!p || !len || !m_keepCStrings) {
        v->m_body.str.m_cstr = nullptr;
        v->m_cstrWork = 0xffff;
        return 0;
    }
    // TemporaryMalloc(len + 1), inlined
    char* tmp = nullptr;
    u64 used = m_tempUsed, end = used + (((u64)len + 4) & 0x1fffffffcull);
    if (end <= m_tempSize) {
        m_tempUsed = end;
        tmp = (char*)(m_temp + used);
    }
    if (!tmp) tmp = (char*)ason::new_array_nothrow((u64)len + 1);
    auto temporary_free = [&] {  // TemporaryFree, inlined
        if ((u64)tmp < (u64)m_temp || (u64)m_temp + m_tempSize <= (u64)tmp) ason::delete_array(tmp);
        else m_tempUsed = 0;
    };
    if (tmp) {
        std::memcpy(tmp, p, len);
        tmp[len] = 0;
        s32 need = (s32)containers::StringUtility::Utf8ToMultiByte(tmp, nullptr, 0);
        if (need == 0) {  // (never: the size counts the terminator)
            temporary_free();
            m_status.code = -1;
            return -1;
        }
        if (char* c = (char*)Malloc((u64)(s64)need)) {
            containers::StringUtility::Utf8ToMultiByte(tmp, c, (u32)need);
            temporary_free();
            v->m_body.str.m_cstr = c;
            v->m_cstrWork = m_workIndex;
            return 0;
        }
        temporary_free();
    }
    m_status.code = -0x3bf;
    return -0x3bf;
}

// ---- natives ----

namespace {
using live::kInt;
using live::kVoid;

void malloc_regions(const u64 x[9], live::Regions& r) {
    if (x[0]) add_region(r, (u64)reinterpret_cast<const ASON*>(x[0])->m_currentWork, sizeof(ASON_WorkBufferContext));
}
void unpack_str_regions(const u64 x[9], live::Regions& r) {
    add_region(r, x[1], sizeof(AValue));
    ason::add_allocator_regions(x[0], r);
}

void Malloc_(Cpu& c) { c.set_x(0, (u64)reinterpret_cast<ASON*>(c.x(0))->Malloc(c.x(1))); }
void UnpackValue_str_(Cpu& c) {
    auto* a = reinterpret_cast<ASON*>(c.x(0));
    s32 r = a->UnpackValue_str(reinterpret_cast<AValue*>(c.x(1)), (const s8*)c.x(2), (const s8*)c.x(3), (u32)c.x(4), (u16)c.x(5));
    c.set_x(0, (u64)(u32)r);
}
}  // namespace

DF_HOSTFN("_ZN4Aska4ASON6MallocEm", &Malloc_, sizeof(ASON), kInt, "Aska::ASON::Malloc", &malloc_regions);
DF_HOSTFN("_ZN4Aska4ASON15UnpackValue_strEPNS0_6AValueEPKaS4_jt", &UnpackValue_str_, sizeof(ASON), kInt, "Aska::ASON::UnpackValue_str",
          &unpack_str_regions);

}  // namespace soa::native::data_formats

// Aska::ASON::UnpackMessagePack<bool Build>: Aska's msgpack reader (data_formats_layout.h;
// port/decomp/data_formats/ason.c), msgpack-c's resumable template_execute (unpack_template.h) with
// ASON's values: ctx->m_value is msgpack-c's obj, m_state / m_trail / m_top its cs / trail / top, the
// frames its stack. DeserializeBinary runs <false> to count the roots and <true> to build them; both
// allocate the containers (from the ASON's Malloc), only <true> stores scalars and strings.
//
// Aska's differences from msgpack-c, kept here:
//   - a value only writes the AValue fields its kind uses (nil only the kind; bool one byte), so the
//     others keep what the previous value left in ctx->m_value, and that is what gets copied;
//   - a container's body count is the 1-based slot being filled while it is open;
//   - running out of input right after a value (at a header) ends like a finished root: frame 0 gets
//     the last value and *pos goes one past the end; both return Status 0 (a parse error -1); a
//     finished root leaves m_state at the last token's state, not 0;
//   - strings, bin and ext at depth top are stamped with frames[top].m_work (the frame about to be
//     used: DeserializeBinary stamps them all with m_workIndex before a root);
//   - an empty fixstr points at whatever trail the previous token read (msgpack-c's n);
//   - more than 32 open containers is an error (-1).
#include "native/data_formats/data_formats_ason.h"

namespace soa::native::data_formats {

using ason::load_be16;
using ason::load_be32;
using ason::load_be64;

namespace {

enum State : u32 {
    kHeader = 0x00,
    kBin8 = 0x04, kBin16, kBin32,
    kExt8 = 0x07, kExt16, kExt32,
    kFloat = 0x0a, kDouble,
    kUInt8 = 0x0c, kUInt16, kUInt32, kUInt64,
    kInt8 = 0x10, kInt16, kInt32, kInt64,
    kFixExt1 = 0x14, kFixExt2, kFixExt4, kFixExt8, kFixExt16,
    kStr8 = 0x19, kStr16, kStr32,
    kArray16 = 0x1c, kArray32, kMap16, kMap32,
    kStrValue = 0x20, kBinValue = 0x21, kExtValue = 0x22,
};

constexpr u32 kMaxDepth = 32;

// Zeroes what MakeAValue_Array / _Map and start_container zero: an AValue's kind and bytes 8..0x20
// (the kind's padding is left).
void clear_value(AValue& v) {
    v.m_kind = 0;
    std::memset(&v.m_body, 0, 0x18);
}

}  // namespace

template <bool Build>
Status ASON::UnpackMessagePack(ASON_MessagePackContext* ctx, const s8* data, u64 len, u64* off) {
    AValue& obj = ctx->m_value;
    ASON_UnpackFrame* const stack = ctx->m_frames;
    u32 cs = ctx->m_state, trail = ctx->m_trail, top = ctx->m_top;
    const u8* p = (const u8*)data + *off;
    const u8* const pe = (const u8*)data + len;
    const u8* n = nullptr;  // the trail being read (kept across tokens: an empty fixstr points at it)
    s64 ret = 0;

    // A container of `count` values (pairs) at stack[top]: its storage zeroed, then filled by the
    // values that follow (0: done at once). false: an error (ret, m_status set).
    auto start_container = [&](u32 kind, u32 count) -> int {  // -1 error, 0 empty (obj = it), 1 opened
        if (top >= kMaxDepth) return ret = -1, -1;
        ASON_UnpackFrame& f = stack[top];
        f.m_value.m_kind = kind;
        f.m_value.m_body.array.m_count = 0;
        u64 elem = kind == AValue::kArray ? sizeof(AValue) : sizeof(ASON_Pair);
        u8* elems = (u8*)Malloc((u64)count * elem);
        if (elems) {
            for (u32 k = 0; k < count; k++) {
                clear_value(*reinterpret_cast<AValue*>(elems + k * elem));
                if (kind == AValue::kMap) clear_value(reinterpret_cast<ASON_Pair*>(elems + k * elem)->value);
            }
        }
        f.m_value.m_body.array.m_elements = reinterpret_cast<AValue*>(elems);
        if (!elems && count) {
            m_status.code = -0x3bf;
            return ret = -1, -1;
        }
        f.m_value.m_body.array.m_work = m_workIndex;
        f.m_work = m_workIndex;
        if (count == 0) {
            obj = f.m_value;
            return 0;
        }
        f.m_remaining = count;
        f.m_ct = kind == AValue::kArray ? ASON_UnpackFrame::kArrayItem : ASON_UnpackFrame::kMapKey;
        f.m_value.m_body.array.m_count++;
        ++top;
        return 1;
    };
    auto stamp = [&] { return stack[top].m_work; };
    auto set_bin = [&](const u8* at, u32 size) {
        if (!Build) return;
        obj.m_kind = AValue::kBinary;
        obj.m_body.bin.m_data = at;
        obj.m_body.bin.m_size = size;
        u16 w = stamp();
        std::memcpy(&obj.m_body.raw[0x0c], &w, 2);  // (bin keeps its stamp at body + 0x0c)
    };
    auto set_ext = [&](const u8* at, u32 trail_len) {  // at: the type byte, then trail_len - 1 bytes
        if (!Build) return;
        obj.m_kind = AValue::kExt;
        obj.m_body.bin.m_data = at + 1;
        obj.m_body.bin.m_size = trail_len - 1;
        obj.m_body.bin.m_extType = (s8)*at;
        u16 w = stamp();
        std::memcpy(&obj.m_body.raw[0x0e], &w, 2);  // (ext: at body + 0x0e)
    };
    auto set_uint = [&](u64 v) {
        if (!Build) return;
        obj.m_kind = AValue::kUInt;
        obj.m_body.u = v;
    };
    auto set_int = [&](s64 v) {  // a signed msgpack int: kind 3 only when negative
        if (!Build) return;
        obj.m_kind = v < 0 ? AValue::kSInt : AValue::kUInt;
        obj.m_body.s = v;
    };
    // A string of trail bytes at n (Build); false: UnpackValue_str failed (ret = -1).
    auto read_str = [&]() -> bool {
        if (!Build) return true;
        if (UnpackValue_str(&obj, data, (const s8*)n, trail, stamp()) < 0) return ret = -1, false;
        return true;
    };

    if (*off == len) goto end;  // nothing to read: the state stays as it is
    if (cs != kHeader) {
        n = p;
        goto trail_check;
    }
    for (;;) {
        {
            // ---- a header byte at p ----
            u8 b = *p;
            if (b < 0x80) {  // positive fixint
                set_uint(b);
                goto push;
            }
            if (b >= 0xe0) {  // negative fixint
                if (Build) obj.m_kind = AValue::kSInt, obj.m_body.s = (s8)b;
                goto push;
            }
            if (b >= 0xc0) {
                switch (b) {
                    case 0xc0:
                        if (Build) obj.m_kind = AValue::kNil;
                        goto push;
                    case 0xc2:
                    case 0xc3:
                        if (Build) obj.m_kind = AValue::kBool, obj.m_body.raw[0] = b & 1;
                        goto push;
                    case 0xc4: case 0xc5: case 0xc6:                        // bin 8/16/32: the length
                    case 0xca: case 0xcb:                                   // float, double
                    case 0xcc: case 0xcd: case 0xce: case 0xcf:             // uint 8..64
                    case 0xd0: case 0xd1: case 0xd2: case 0xd3:             // int 8..64
                        trail = 1u << (b & 3);
                        break;
                    case 0xc7: case 0xc8: case 0xc9:  // ext 8/16/32: the length
                        trail = 1u << ((b + 1) & 3);
                        break;
                    case 0xd4: case 0xd5: case 0xd6: case 0xd7:  // fixext 1..8: type + data
                        trail = (1u << (b & 3)) + 1;
                        cs = kExtValue;
                        goto trail_again;
                    case 0xd8:  // fixext 16
                        trail = 17;
                        cs = kExtValue;
                        goto trail_again;
                    case 0xd9: case 0xda: case 0xdb:  // str 8/16/32: the length
                        trail = 1u << ((b & 3) - 1);
                        break;
                    case 0xdc: case 0xdd: case 0xde: case 0xdf:  // array / map 16/32: the count
                        trail = 2u << (b & 1);
                        break;
                    default:  // 0xc1: never used
                        ret = -1;
                        goto end;
                }
                cs = b & 0x1f;
                goto trail_again;
            }
            if (b >= 0xa0) {  // fixstr
                trail = b & 0x1f;
                if (trail) {
                    cs = kStrValue;
                    goto trail_again;
                }
                if (!read_str()) goto end;  // (empty: n is the previous token's trail)
                goto push;
            }
            int r = start_container(b >= 0x90 ? AValue::kArray : AValue::kMap, b & 0x0f);  // fixarray / fixmap
            if (r < 0) goto end;
            if (r == 0) goto push;
            goto header_again;
        }

    trail_again:
        n = ++p;
    trail_check:
        if ((u64)(pe - n) < trail) {  // the rest of this token isn't there yet
            p = n;
            ret = 0;
            goto end;
        }
        p = n + (u32)(trail - 1);  // (32-bit: a 0 trail, only from a corrupt context, wraps as in the guest)
        switch (cs) {
            case kBin8: case kBin16: case kBin32:
                trail = cs == kBin8 ? *n : cs == kBin16 ? load_be16(n) : load_be32(n);
                if (!trail) {
                    set_bin(n, 0);
                    goto push;
                }
                cs = kBinValue;
                goto trail_again;
            case kExt8: case kExt16: case kExt32:
                trail = (cs == kExt8 ? *n : cs == kExt16 ? load_be16(n) : load_be32(n)) + 1;
                if (!trail) {  // (a 32-bit length of 0xffffffff)
                    set_ext(n, 0);
                    goto push;
                }
                cs = kExtValue;
                goto trail_again;
            case kFloat: {
                u32 bits = load_be32(n);
                float f;
                std::memcpy(&f, &bits, 4);
                if (Build) obj.m_kind = AValue::kFloat, obj.m_body.d = (double)f;
                goto push;
            }
            case kDouble:
                if (Build) obj.m_kind = AValue::kFloat, obj.m_body.u = load_be64(n);
                goto push;
            case kUInt8: set_uint(*n); goto push;
            case kUInt16: set_uint(load_be16(n)); goto push;
            case kUInt32: set_uint(load_be32(n)); goto push;
            case kUInt64: set_uint(load_be64(n)); goto push;
            case kInt8: set_int((s8)*n); goto push;
            case kInt16: set_int((s16)load_be16(n)); goto push;
            case kInt32: set_int((s32)load_be32(n)); goto push;
            case kInt64: set_int((s64)load_be64(n)); goto push;
            case kFixExt1: case kFixExt2: case kFixExt4: case kFixExt8: case kFixExt16:  // (unused: fixext goes to kExtValue)
                trail = (1u << (cs - kFixExt1)) + 1;
                cs = kExtValue;
                goto trail_again;
            case kStr8: case kStr16: case kStr32:
                trail = cs == kStr8 ? *n : cs == kStr16 ? load_be16(n) : load_be32(n);
                if (trail) {
                    cs = kStrValue;
                    goto trail_again;
                }
                if (!read_str()) goto end;
                goto push;
            case kArray16: case kArray32: case kMap16: case kMap32: {
                u32 count = (cs & 1) ? load_be32(n) : load_be16(n);
                int r = start_container(cs < kMap16 ? AValue::kArray : AValue::kMap, count);
                if (r < 0) goto end;
                if (r == 0) goto push;
                goto header_again;
            }
            case kStrValue:
                if (!read_str()) goto end;
                goto push;
            case kBinValue:
                set_bin(n, trail);
                goto push;
            case kExtValue:
                set_ext(n, trail);
                goto push;
            default:  // (a state no header sets)
                ret = -1;
                goto end;
        }

    push:  // obj is complete: into the open container, closing those it completes
        while (top != 0) {
            ASON_UnpackFrame& c = stack[top - 1];
            AArray& body = c.m_value.m_body.array;
            if (c.m_ct == ASON_UnpackFrame::kArrayItem) {
                body.m_elements[body.m_count - 1] = obj;
                if (--c.m_remaining != 0) {
                    body.m_count++;
                    goto header_again;
                }
            } else if (c.m_ct == ASON_UnpackFrame::kMapKey) {
                c.m_mapKey = obj;
                c.m_ct = ASON_UnpackFrame::kMapValue;
                goto header_again;
            } else if (c.m_ct == ASON_UnpackFrame::kMapValue) {
                ASON_Pair& pair = c.m_value.m_body.map.m_pairs[body.m_count - 1];
                pair.key = c.m_mapKey;
                pair.value = obj;
                if (--c.m_remaining != 0) {
                    body.m_count++;
                    c.m_ct = ASON_UnpackFrame::kMapKey;
                    goto header_again;
                }
            } else {
                ret = -1;
                goto end;
            }
            obj = c.m_value;
            --top;
        }
        goto finish;

    header_again:
        cs = kHeader;
        if (++p == pe) goto finish;  // (Aska: ends like a finished root)
    }

finish:
    stack[0].m_value = obj;
    ++p;
    ret = 0;
end:
    ctx->m_state = cs;
    ctx->m_trail = trail;
    ctx->m_top = top;
    *off = (u64)(p - (const u8*)data);
    return Status{ret};
}

template Status ASON::UnpackMessagePack<true>(ASON_MessagePackContext*, const s8*, u64, u64*);
template Status ASON::UnpackMessagePack<false>(ASON_MessagePackContext*, const s8*, u64, u64*);

// ---- natives ----

namespace {

template <bool Build>
void Unpack_(Cpu& c) {
    auto* a = reinterpret_cast<ASON*>(c.x(0));
    ason::set_status(c, a->UnpackMessagePack<Build>(reinterpret_cast<ASON_MessagePackContext*>(c.x(1)), (const s8*)c.x(2), c.x(3),
                                                     reinterpret_cast<u64*>(c.x(4))));
}
void unpack_regions(const u64 x[9], live::Regions& r) {
    add_region(r, x[1], sizeof(ASON_MessagePackContext));
    add_region(r, x[4], 8);
    ason::add_allocator_regions(x[0], r);
}

}  // namespace

DF_HOSTFN("_ZN4Aska4ASON17UnpackMessagePackILb1EEENS_6StatusEPNS0_18MessagePackContextEPKamPm", &Unpack_<true>, sizeof(ASON), live::kVoid,
          "Aska::ASON::UnpackMessagePack<true>", &unpack_regions);
DF_HOSTFN("_ZN4Aska4ASON17UnpackMessagePackILb0EEENS_6StatusEPNS0_18MessagePackContextEPKamPm", &Unpack_<false>, sizeof(ASON), live::kVoid,
          "Aska::ASON::UnpackMessagePack<false>", &unpack_regions);

}  // namespace soa::native::data_formats

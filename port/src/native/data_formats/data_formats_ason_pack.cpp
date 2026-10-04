// Aska::ASON::PackMessagePack<bool Write> and the PackValue_* header writers: an AValue tree as msgpack
// (data_formats_layout.h; port/decomp/data_formats/ason.c). <true> writes at `out` (the buffer's
// `size` bytes, *written of them used), <false> only adds the bytes it would write to *written.
//
// Guest details kept: a value needs strictly more room than its header for the fixed forms the guest
// tests with `>` (e.g. a double needs 9 of 9 bytes: room > 8), a string's / bin's / ext's data is
// checked against the room before its header; running out of room is -0x3c1 (also m_status) with
// the header bytes already counted; a kind above 9 writes nothing and succeeds.
#include "native/data_formats/data_formats_ason.h"

namespace soa::native::data_formats {

namespace {
constexpr s64 kNoRoom = -0x3c1;
}

// The writers return the bytes written, or -0x3c1 (and set m_status) when `room` is too small.
s64 ASON::PackValue_u64(u8* out, u64 v, u64 room) const {
    if (v < 0x100) {
        if (v < 0x80) {
            if (room) return out[0] = (u8)v, 1;
        } else if (room > 1) {
            return out[0] = 0xcc, out[1] = (u8)v, 2;
        }
    } else if (v >> 16 == 0) {
        if (room > 2) return out[0] = 0xcd, ason::store_be16(out + 1, (u16)v), 3;
    } else if (v >> 32 == 0) {
        if (room > 4) return out[0] = 0xce, ason::store_be32(out + 1, (u32)v), 5;
    } else if (room > 8) {
        return out[0] = 0xcf, ason::store_be64(out + 1, v), 9;
    }
    const_cast<ASON*>(this)->m_status.code = kNoRoom;
    return kNoRoom;
}

s64 ASON::PackValue_s64(u8* out, s64 v, u64 room) const {
    if (v < -0x20) {
        if (v < -0x8000) {
            if (v < -0x80000000ll) {
                if (room > 8) return out[0] = 0xd3, ason::store_be64(out + 1, (u64)v), 9;
            } else if (room > 4) {
                return out[0] = 0xd2, ason::store_be32(out + 1, (u32)v), 5;
            }
        } else if (v < -0x80) {
            if (room > 2) return out[0] = 0xd1, ason::store_be16(out + 1, (u16)v), 3;
        } else if (room > 1) {
            return out[0] = 0xd0, out[1] = (u8)v, 2;
        }
    } else if (v < 0x80) {
        if (room) return out[0] = (u8)v, 1;
    } else if (v < 0x10000) {
        if (v < 0x100) {
            if (room > 1) return out[0] = 0xcc, out[1] = (u8)v, 2;
        } else if (room > 2) {
            return out[0] = 0xcd, ason::store_be16(out + 1, (u16)v), 3;
        }
    } else if (v < 0x100000000ll) {
        if (room > 4) return out[0] = 0xce, ason::store_be32(out + 1, (u32)v), 5;
    } else if (room > 8) {
        return out[0] = 0xcf, ason::store_be64(out + 1, (u64)v), 9;
    }
    const_cast<ASON*>(this)->m_status.code = kNoRoom;
    return kNoRoom;
}

s64 ASON::PackValue_str(u8* out, u64 len, u64 room) const {
    if (len < 0x20) {
        if (room) return out[0] = (u8)(0xa0 | len), 1;
    } else if (len < 0x100) {
        if (room > 1) return out[0] = 0xd9, out[1] = (u8)len, 2;
    } else if (len >> 16 == 0) {
        if (room > 2) return out[0] = 0xda, ason::store_be16(out + 1, (u16)len), 3;
    } else if (room > 4) {
        return out[0] = 0xdb, ason::store_be32(out + 1, (u32)len), 5;
    }
    const_cast<ASON*>(this)->m_status.code = kNoRoom;
    return kNoRoom;
}

s64 ASON::PackValue_ext(u8* out, u64 len, s8 type, u64 room) const {
    u8 fix = len == 1 ? 0xd4 : len == 2 ? 0xd5 : len == 4 ? 0xd6 : len == 8 ? 0xd7 : len == 16 ? 0xd8 : 0;
    if (fix) {
        if (room > 1) return out[0] = fix, out[1] = (u8)type, 2;
    } else if (len < 0x100) {
        if (room > 2) return out[0] = 0xc7, out[1] = (u8)len, out[2] = (u8)type, 3;
    } else if (len >> 16 == 0) {
        if (room > 3) return out[0] = 0xc8, ason::store_be16(out + 1, (u16)len), out[3] = (u8)type, 4;
    } else if (room > 5) {
        return out[0] = 0xc9, ason::store_be32(out + 1, (u32)len), out[5] = (u8)type, 6;
    }
    const_cast<ASON*>(this)->m_status.code = kNoRoom;
    return kNoRoom;
}

namespace {

Status pack_write(const ASON* self, const AValue* v, u8* out, u64 size, u64* written) {
    auto no_room = [&] {
        const_cast<ASON*>(self)->m_status.code = kNoRoom;
        return Status{kNoRoom};
    };
    if (size <= *written) return no_room();
    if (v->m_kind > AValue::kExt) return Status{0};
    u64 room = size - *written;
    s64 head = 0;      // a string's / bin's / ext's header bytes
    u64 data_len = 0;  // and its data
    switch (v->m_kind) {
        case AValue::kNil:
            if (!room) return no_room();
            out[0] = 0xc0;
            *written += 1;
            return Status{0};
        case AValue::kBool:
            if (!room) return no_room();
            out[0] = v->m_body.raw[0] ? 0xc3 : 0xc2;
            *written += 1;
            return Status{0};
        case AValue::kUInt:
        case AValue::kSInt: {
            s64 r = v->m_kind == AValue::kUInt ? self->PackValue_u64(out, v->m_body.u, room) : self->PackValue_s64(out, v->m_body.s, room);
            if (r > 0) {
                *written += r;
                r = 0;
            }
            return Status{r};
        }
        case AValue::kFloat:
            if (room <= 8) return no_room();
            out[0] = 0xcb;
            ason::store_be64(out + 1, v->m_body.u);
            *written += 9;
            return Status{0};
        case AValue::kString:
            head = self->PackValue_str(out, v->m_length, room);
            if (head < 1) return Status{head};
            *written += head;
            data_len = v->m_length;
            break;
        case AValue::kExt:
            head = self->PackValue_ext(out, v->m_body.bin.m_size, v->m_body.bin.m_extType, room);
            if (head < 1) return Status{head};
            *written += head;
            data_len = v->m_body.bin.m_size;
            break;
        case AValue::kBinary: {
            u32 n = v->m_body.bin.m_size;
            if (n < 0x100) {
                if (room <= 1) return no_room();
                out[0] = 0xc4, out[1] = (u8)n, head = 2;
            } else if (n >> 16) {
                if (room <= 4) return no_room();
                out[0] = 0xc6, ason::store_be32(out + 1, n), head = 5;
            } else {
                if (room < 3) return no_room();
                out[0] = 0xc5, ason::store_be16(out + 1, (u16)n), head = 3;
            }
            *written += head;
            data_len = n;
            break;
        }
        case AValue::kArray:
        case AValue::kMap: {
            bool map = v->m_kind == AValue::kMap;
            u32 count = v->m_body.array.m_count;
            if (count < 0x10) {
                if (!room) return no_room();
                out[0] = (u8)((map ? 0x80 : 0x90) | count);
                head = 1;
            } else if (count >> 16 == 0) {
                if (room <= 2) return no_room();
                out[0] = map ? 0xde : 0xdc;
                ason::store_be16(out + 1, (u16)count);
                head = 3;
            } else {
                if (room <= 4) return no_room();
                out[0] = map ? 0xdf : 0xdd;
                ason::store_be32(out + 1, count);
                head = 5;
            }
            *written += head;
            u8* q = out + head;
            u64 w0 = *written;
            for (u32 i = 0; i < count; i++) {
                if (!map) {
                    Status s = self->PackMessagePack<true>(&v->m_body.array.m_elements[i], q, size, written);
                    if (s.code < 0) return s;
                } else {
                    const ASON_Pair& pair = v->m_body.map.m_pairs[i];
                    Status s = self->PackMessagePack<true>(&pair.key, q, size, written);
                    if (s.code < 0) return s;
                    u64 w1 = *written;
                    q += w1 - w0;
                    w0 = w1;
                    s = self->PackMessagePack<true>(&pair.value, q, size, written);
                    if (s.code < 0) return s;
                }
                q += *written - w0;
                w0 = *written;
            }
            return Status{0};
        }
    }
    // the data of a string / bin / ext, after its header (checked against the room before the header)
    if (room < data_len) return no_room();
    std::memcpy(out + head, v->m_body.bin.m_data, data_len);
    *written += data_len;
    return Status{0};
}

Status pack_count(const ASON* self, const AValue* v, u8* out, u64 size, u64* written) {
    u64 head = 0, data_len = 0;
    switch (v->m_kind) {
        case AValue::kNil:
        case AValue::kBool:
            *written += 1;
            return Status{0};
        case AValue::kUInt: {
            u64 x = v->m_body.u;
            head = x < 0x100 ? (x > 0x7f ? 2 : 1) : x < 0x10000 ? 3 : x >> 32 ? 9 : 5;
            *written += head;
            return Status{0};
        }
        case AValue::kSInt: {
            s64 x = v->m_body.s;
            if (x < -0x20) head = x < -0x8000 ? (x < -0x80000000ll ? 9 : 5) : (x < -0x80 ? 3 : 2);
            else if (x < 0x80) head = 1;
            else if (x <= 0xffff) head = x > 0xff ? 3 : 2;
            else head = x < 0x100000000ll ? 5 : 9;
            *written += head;
            return Status{0};
        }
        case AValue::kFloat:
            *written += 9;
            return Status{0};
        case AValue::kString: {
            u32 n = v->m_length;
            head = n < 0x20 ? 1 : n < 0x100 ? 2 : n > 0xffff ? 5 : 3;
            data_len = n;
            break;
        }
        case AValue::kBinary: {
            u32 n = v->m_body.bin.m_size;
            head = n > 0xff ? (n > 0xffff ? 5 : 3) : 2;
            data_len = n;
            break;
        }
        case AValue::kExt: {
            u32 n = v->m_body.bin.m_size;
            if (n < 0x11 && ((1u << n) & 0x10116u)) head = 2;
            else head = n < 0x100 ? 3 : n < 0x10000 ? 4 : 6;
            data_len = n;
            break;
        }
        case AValue::kArray:
        case AValue::kMap: {
            bool map = v->m_kind == AValue::kMap;
            u32 count = v->m_body.array.m_count;
            head = count < 0x10 ? 1 : count > 0xffff ? 5 : 3;
            *written += head;
            for (u32 i = 0; i < count; i++) {  // (the guest passes a meaningless `out` down: unused here)
                if (!map) {
                    Status s = self->PackMessagePack<false>(&v->m_body.array.m_elements[i], out, size, written);
                    if (s.code < 0) return s;
                } else {
                    Status s = self->PackMessagePack<false>(&v->m_body.map.m_pairs[i].key, out, size, written);
                    if (s.code < 0) return s;
                    s = self->PackMessagePack<false>(&v->m_body.map.m_pairs[i].value, out, size, written);
                    if (s.code < 0) return s;
                }
            }
            return Status{0};
        }
        default:
            return Status{0};
    }
    *written += head + data_len;
    return Status{0};
}

}  // namespace

template <bool Write>
Status ASON::PackMessagePack(const AValue* v, u8* out, u64 size, u64* written) const {
    if constexpr (Write) return pack_write(this, v, out, size, written);
    else return pack_count(this, v, out, size, written);
}
template Status ASON::PackMessagePack<true>(const AValue*, u8*, u64, u64*) const;
template Status ASON::PackMessagePack<false>(const AValue*, u8*, u64, u64*) const;

// ---- natives ----

namespace {

template <bool Write>
void Pack_(Cpu& c) {
    auto* a = reinterpret_cast<const ASON*>(c.x(0));
    ason::set_status(c, a->PackMessagePack<Write>(reinterpret_cast<const AValue*>(c.x(1)), (u8*)c.x(2), c.x(3), reinterpret_cast<u64*>(c.x(4))));
}
void pack_regions(const u64 x[9], live::Regions& r) {
    add_region(r, x[4], 8);
    if (x[2] && x[4]) {
        u64 used = *reinterpret_cast<const u64*>(x[4]);
        if (used < x[3]) add_region(r, x[2], x[3] - used);
    }
}
void count_regions(const u64 x[9], live::Regions& r) { add_region(r, x[4], 8); }

void PackValue_u64_(Cpu& c) { c.set_x(0, (u64)reinterpret_cast<const ASON*>(c.x(0))->PackValue_u64((u8*)c.x(1), c.x(2), c.x(3))); }
void PackValue_s64_(Cpu& c) { c.set_x(0, (u64)reinterpret_cast<const ASON*>(c.x(0))->PackValue_s64((u8*)c.x(1), (s64)c.x(2), c.x(3))); }
void PackValue_str_(Cpu& c) { c.set_x(0, (u64)reinterpret_cast<const ASON*>(c.x(0))->PackValue_str((u8*)c.x(1), c.x(2), c.x(3))); }
void PackValue_ext_(Cpu& c) {
    c.set_x(0, (u64)reinterpret_cast<const ASON*>(c.x(0))->PackValue_ext((u8*)c.x(1), c.x(2), (s8)c.x(3), c.x(4)));
}
void header_regions(const u64 x[9], live::Regions& r) { add_region(r, x[1], 9); }

}  // namespace

using live::kInt;
using live::kVoid;
DF_HOSTFN("_ZNK4Aska4ASON15PackMessagePackILb1EEENS_6StatusEPKNS0_6AValueEPhmPm", &Pack_<true>, sizeof(ASON), kVoid,
          "Aska::ASON::PackMessagePack<true>", &pack_regions);
DF_HOSTFN("_ZNK4Aska4ASON15PackMessagePackILb0EEENS_6StatusEPKNS0_6AValueEPhmPm", &Pack_<false>, sizeof(ASON), kVoid,
          "Aska::ASON::PackMessagePack<false>", &count_regions);
DF_HOSTFN("_ZNK4Aska4ASON13PackValue_u64ILb1EEElPhmm", &PackValue_u64_, sizeof(ASON), kInt, "Aska::ASON::PackValue_u64<true>", &header_regions);
DF_HOSTFN("_ZNK4Aska4ASON13PackValue_s64ILb1EEElPhlm", &PackValue_s64_, sizeof(ASON), kInt, "Aska::ASON::PackValue_s64<true>", &header_regions);
DF_HOSTFN("_ZNK4Aska4ASON13PackValue_strILb1EEElPhmm", &PackValue_str_, sizeof(ASON), kInt, "Aska::ASON::PackValue_str<true>", &header_regions);
DF_HOSTFN("_ZNK4Aska4ASON13PackValue_extILb1EEElPhmam", &PackValue_ext_, sizeof(ASON), kInt, "Aska::ASON::PackValue_ext<true>", &header_regions);

}  // namespace soa::native::data_formats

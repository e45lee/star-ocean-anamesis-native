// The property templates (params_layout.h; port/decomp/params/property.c): CParameterPropertyValue<T, N,
// Conv>::Deserialize (786 instantiations), CParameterPropertyString<std::string, N>::Deserialize and
// CParameterPropertyBase<N>::CryptString (194 each), bound from gen/params_instantiations.inc
// (tools/gen_params_instantiations.py: every instantiation in the lib, its shape checked). N is the XOR
// key of CryptString and nothing else, so one template body serves every N.
#include <atomic>
#include <cstring>
#include <mutex>
#include <vector>

#include "core/loader.h"
#include "native/common/arm_float.h"
#include "native/common/native.h"
#include "native/params/params_check.h"
#include "native/params/params_guest.h"
#include "native/params/params_parser.h"
#include "native/params/params_property.h"

namespace soa::native::params {

// ---- the registry of bound vtables ----

namespace {

struct Pending {
    const char* ztv;
    PropertyDeserialize fn;
};
std::vector<Pending>& pending() {
    static std::vector<Pending> v;
    return v;
}

// An open-addressing table vtable -> entry, built once (the lookups need no lock after it).
class VtableTable {
public:
    static constexpr u32 kSize = 4096;  // > 2 x the 980 instantiations
    PropertyDeserialize find(u64 vt) const {
        for (u32 i = slot(vt);; i = (i + 1) & (kSize - 1)) {
            if (keys_[i] == vt) return fns_[i];
            if (!keys_[i]) return nullptr;
        }
    }
    void add(u64 vt, PropertyDeserialize fn) {
        u32 i = slot(vt);
        while (keys_[i] && keys_[i] != vt) i = (i + 1) & (kSize - 1);
        keys_[i] = vt;
        fns_[i] = fn;
    }

private:
    static u32 slot(u64 vt) { return (u32)((vt >> 3) * 0x9E3779B97F4A7C15ull >> 52) & (kSize - 1); }
    u64 keys_[kSize] = {};
    PropertyDeserialize fns_[kSize] = {};
};

const VtableTable& table() {
    static VtableTable* t = [] {
        auto* tt = new VtableTable;
        for (const Pending& p : pending()) {
            u64 a = main_lib()->sym(p.ztv);
            if (a) tt->add(a + 0x10, p.fn);
        }
        return tt;
    }();
    return *t;
}

}  // namespace

bool AddKnownProperty(const char* ztv, PropertyDeserialize fn) {
    pending().push_back({ztv, fn});
    return true;
}

PropertyDeserialize KnownProperty(const void* vtable) { return table().find((u64)vtable); }

namespace {
std::vector<std::pair<const char*, CryptStringFn>>& crypts() {
    static std::vector<std::pair<const char*, CryptStringFn>> v;
    return v;
}
}  // namespace
bool AddKnownCryptString(const char* sym, CryptStringFn fn) {
    crypts().push_back({sym, fn});
    return true;
}
CryptStringFn KnownCryptString(const char* sym) {
    for (auto& [s, f] : crypts())
        if (!std::strcmp(s, sym)) return f;
    return nullptr;
}

u32 CallNameHash(const IParameterProperty* p) {
    if (KnownProperty(p->vtable)) return NameOf(p);
    return (u32)guest_call(((const u64*)p->vtable)[IParameterProperty::kSlotNameHash], {(u64)p});
}

bool CallDeserialize(IParameterProperty* p, const AMap* map) {
    if (PropertyDeserialize fn = KnownProperty(p->vtable)) return fn(p, map);
    return guest_call(((const u64*)p->vtable)[IParameterProperty::kSlotDeserialize], {(u64)p, (u64)map}) & 0xff;
}

// ---- the members ----

namespace {
// CPropertyConverterRadian: v * pi / 180 in float (a multiply, then a divide; 3.14159274f and 180.0f
// at vaddr 0x26e3fd0).
template <typename Conv, typename T>
T Convert(T v) {
    if constexpr (std::is_same_v<Conv, CPropertyConverterRadian>) return (armf::F(v) * armf::F(3.14159274f) / armf::F(180.0f)).v;
    else return v;
}
}  // namespace

template <typename T, u32 N, typename Conv>
bool CParameterPropertyValue<T, N, Conv>::Deserialize(const AMap* map) {
    ParserResult<T> r = GetValueByHash<T>(map, CallNameHash(&base.base));
    if (r.found) m_value = Convert<Conv>(r.value);
    return r.found != 0;
}

template <u32 N>
void CParameterPropertyBase<N>::CryptString(String& dst, const String& src) {
    // dst cleared (its capacity kept), then src's bytes ^ key appended. The guest appends one at a
    // time, growing through __grow_by(cap, 1, size, size, 0, 0) whenever size == capacity; here a run
    // of bytes goes in at once between the same growth calls, so the allocations and the final string
    // are the guest's. (src aliasing dst: cleared first, so nothing is appended, as in the guest.)
    if (!dst.is_long()) {
        dst.r.s.head.size = 0;
        dst.r.s.data[0] = 0;
    } else {
        dst.r.l.data[0] = 0;
        dst.r.l.size = 0;
    }
    u64 n = src.size();
    const char* p = src.data();
    while (n) {
        bool lng = dst.is_long();
        u64 size = lng ? dst.r.l.size : dst.r.s.head.size >> 1;
        u64 cap = lng ? (dst.r.l.cap & ~u64(1)) - 1 : 22;
        if (size == cap) {
            g::GrowBy(&dst, cap, 1, cap, cap, 0, 0);
            cap = (dst.r.l.cap & ~u64(1)) - 1;  // (long from now on)
        }
        u64 k = cap - size < n ? cap - size : n;
        char* d = dst.is_long() ? dst.r.l.data : dst.r.s.data;
        for (u64 i = 0; i < k; i++) d[size + i] = char(p[i] ^ kCryptKey);
        d[size + k] = 0;
        if (dst.is_long()) dst.r.l.size = size + k;
        else dst.r.s.head.size = u8((size + k) << 1);
        p += k;
        n -= k;
    }
}

// (CryptString through its checked entry: defined with the binding below)
template <u32 N>
void CryptStringEntry(String& dst, const String& src);

template <u32 N>
bool CParameterPropertyString<N>::Deserialize(const AMap* map) {
    alignas(16) libcxx::pair<String, bool> v;
    GetValueStdStringByHash(&v, map, CallNameHash(&base.base));
    u8 found = *(const u8*)&v.second;
    if (found) CryptStringEntry<N>(m_value, v.first);
    if (v.first.is_long()) g::StlFree(v.first.r.l.data);
    return found != 0;
}

// ---- binding: the checked entries, one per instantiation ----

namespace {

// A value property: the native on the object, then the original on the object as it was, the 0x30
// bytes and the result compared (the native's bytes stay).
template <typename T, u32 N, typename Conv>
struct ValueBinding {
    using P = CParameterPropertyValue<T, N, Conv>;
    static inline Fn* fn = nullptr;

    static bool Entry(IParameterProperty* p, const AMap* map) {
        if (t_record) {
            t_record->push_back({p, map});
            return true;
        }
        P* self = reinterpret_cast<P*>(p);
        if (__builtin_expect(!fam().due(*fn), 1)) return self->Deserialize(map);
        live::RunBothFamily::Scope scope;
        alignas(16) u8 before[sizeof(P)], native[sizeof(P)];
        std::memcpy(before, self, sizeof(P));
        bool rn = self->Deserialize(map);
        std::memcpy(native, self, sizeof(P));
        std::memcpy((void*)self, before, sizeof(P));
        bool rg = guest_call(fn->orig, {(u64)self, (u64)map}) & 0xff;
        std::string d = live::RunBothFamily::diff_bytes(native, self, sizeof(P));
        if (d.empty() && rn != rg) d = "the result";
        std::memcpy((void*)self, native, sizeof(P));
        fam().result(*fn, d.empty() ? Outcome::Ok : Outcome::Mismatch, d);
        return rn;
    }
    static void Host(Cpu& c) { c.set_x(0, Entry((IParameterProperty*)c.x(0), (const AMap*)c.x(1))); }
    static bool Bind(const char* sym, const char* ztv) {
        fn = new Fn(fam(), sym);
        register_native_function({sym, &Host, "params: CParameterPropertyValue<T, N, Conv>::Deserialize", nullptr, &fn->orig});
        return AddKnownProperty(ztv, &Entry);
    }
};

// A string property and its CryptString: the original runs on a private copy (the destination string
// cloned with its capacity), compared by the strings' representation.
template <u32 N>
struct StringBinding {
    using P = CParameterPropertyString<N>;
    static inline Fn* fn = nullptr;
    static inline Fn* crypt = nullptr;

    static bool Entry(IParameterProperty* p, const AMap* map) {
        if (t_record) {
            t_record->push_back({p, map});
            return true;
        }
        P* self = reinterpret_cast<P*>(p);
        if (__builtin_expect(!fam().due(*fn), 1)) return self->Deserialize(map);
        live::RunBothFamily::Scope scope;
        alignas(16) P shadow;
        std::memcpy((void*)&shadow, self, offsetof(P, m_value));
        copy_string(shadow.m_value, self->m_value);
        bool rn = self->Deserialize(map);
        bool rg = guest_call(fn->orig, {(u64)&shadow, (u64)map}) & 0xff;
        std::string d = live::RunBothFamily::diff_bytes(self, &shadow, offsetof(P, m_value));
        if (d.empty()) d = diff_strings(self->m_value, shadow.m_value);
        if (d.empty() && rn != rg) d = "the result";
        free_copy(shadow.m_value);
        fam().result(*fn, d.empty() ? Outcome::Ok : Outcome::Mismatch, d);
        return rn;
    }
    static void Host(Cpu& c) { c.set_x(0, Entry((IParameterProperty*)c.x(0), (const AMap*)c.x(1))); }

    static void Crypt(String& dst, const String& src) {
        if (__builtin_expect(!fam().due(*crypt), 1)) return CParameterPropertyBase<N>::CryptString(dst, src);
        live::RunBothFamily::Scope scope;
        alignas(16) String copy;
        copy_string(copy, dst);
        const String* gsrc = &src == &dst ? &copy : &src;
        CParameterPropertyBase<N>::CryptString(dst, src);
        guest_call(crypt->orig, {(u64)&copy, (u64)gsrc});
        std::string d = diff_strings(dst, copy);
        free_copy(copy);
        fam().result(*crypt, d.empty() ? Outcome::Ok : Outcome::Mismatch, d);
    }
    static void HostCrypt(Cpu& c) { Crypt(*(String*)c.x(0), *(const String*)c.x(1)); }

    static bool Bind(const char* sym, const char* crypt_sym, const char* ztv) {
        fn = new Fn(fam(), sym);
        crypt = new Fn(fam(), crypt_sym);
        register_native_function({sym, &Host, "params: CParameterPropertyString<std::string, N>::Deserialize", nullptr, &fn->orig});
        register_native_function({crypt_sym, &HostCrypt, "params: CParameterPropertyBase<N>::CryptString", nullptr, &crypt->orig});
        AddKnownCryptString(crypt_sym, &Crypt);
        return AddKnownProperty(ztv, &Entry);
    }
};

#define PARAMS_BIND_VALUE(T, N, CONV, SYM, ZTV) \
    [[maybe_unused]] const bool NATIVE_CONCAT(params_value_, __COUNTER__) = ValueBinding<T, N, CONV>::Bind(SYM, ZTV);
#define PARAMS_BIND_STRING(N, SYM, CRYPT, ZTV) \
    [[maybe_unused]] const bool NATIVE_CONCAT(params_string_, __COUNTER__) = StringBinding<N>::Bind(SYM, CRYPT, ZTV);

#include "native/params/gen/params_instantiations.inc"
PARAMS_VALUES(PARAMS_BIND_VALUE)
PARAMS_STRINGS(PARAMS_BIND_STRING)

}  // namespace

template <u32 N>
void CryptStringEntry(String& dst, const String& src) {
    StringBinding<N>::Crypt(dst, src);
}

}  // namespace soa::native::params

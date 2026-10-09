// The element natives' live check (master_family.h; master_element.h ElementCheck): each checked call
// runs the native for real and the guest original (its hook's trampoline) on the state the native
// started from, then compares.
//   - Ctor, Initialize: in place: the element's bytes before, the native's result kept aside, the
//     bytes put back, the original run on the element itself; the two results must be equal byte for
//     byte (Initialize's long keys are allocated and freed by both runs).
//   - CtorCopy: in place as well; the strings are compared by representation (a long one has its own
//     storage in each run: the original's is freed afterwards) and the native's result put back.
//   - Assign, Dtor: the original runs on a private copy of the element as it was (its long strings in
//     storage of their own, same capacity), compared by representation (Dtor: a long string's storage
//     pointer aside, freed in both runs).
#include <cstring>
#include <string>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "native/master/master_element.h"
#include "native/master/master_guest.h"
#include "native/params/params_check.h"

namespace soa::native::master {

namespace {

using live::RunBothFamily;

// An element's bytes in host memory the guest can address (8-aligned).
struct Buf {
    std::vector<u64> w;
    explicit Buf(u32 size) : w((size + 7) / 8) {}
    Buf(const u8* from, u32 size) : w((size + 7) / 8) { std::memcpy(w.data(), from, size); }
    u8* p() { return reinterpret_cast<u8*>(w.data()); }
};

bool is_string_value(const ElementInfo& I, u32 at, const ElementProp** prop) {
    for (const ElementProp& d : I.props) {
        if (d.kind != PropKind::kString) continue;
        u32 lo = d.offset + (u32)offsetof(AnyStringProperty, m_value);
        if (at >= lo && at < lo + sizeof(String)) {
            *prop = &d;
            return true;
        }
    }
    return false;
}

// "" when the native's element and the guest's are the same: every byte outside the string values,
// and each string by representation (strings = false: their bytes too; dead = true: a destroyed
// element's long strings by their capacity and size words only).
std::string compare(const ElementInfo& I, const u8* native, const u8* guest, bool strings, bool dead) {
    for (u32 i = 0; i < I.size; i++) {
        const ElementProp* d = nullptr;
        if (strings && is_string_value(I, i, &d)) {
            const auto& n = string_property(native, *d)->m_value;
            const auto& g = string_property(guest, *d)->m_value;
            std::string why;
            if (dead && n.is_long() && g.is_long()) {
                if (n.r.l.cap != g.r.l.cap || n.r.l.size != g.r.l.size) why = RunBothFamily::diff_bytes(&n, &g, 16);
            } else {
                why = params::diff_strings(n, g);
            }
            if (!why.empty()) return std::string(I.cls) + " string at +" + std::to_string(d->offset) + ": " + why;
            i = d->offset + (u32)offsetof(AnyStringProperty, m_value) + sizeof(String) - 1;
            continue;
        }
        if (native[i] != guest[i]) return std::string(I.cls) + " " + RunBothFamily::diff_bytes(native + i, guest + i, 1) + " at +" + std::to_string(i);
    }
    return {};
}

void free_long_strings(const ElementInfo& I, u8* obj) {
    for (const ElementProp& d : I.props)
        if (d.kind == PropKind::kString) {
            String& s = string_property(obj, d)->m_value;
            if (s.is_long()) g::StlFree(s.r.l.data);
        }
}

// A private copy of an element: its bytes, each long string in storage of its own (same capacity).
void deep_copy(const ElementInfo& I, u8* to, const u8* from) {
    std::memcpy(to, from, I.size);
    for (const ElementProp& d : I.props)
        if (d.kind == PropKind::kString) params::copy_string(string_property(to, d)->m_value, string_property(from, d)->m_value);
}

void result(Fn& f, const std::string& why) { fam().result(f, why.empty() ? Outcome::Ok : Outcome::Mismatch, why); }

}  // namespace

void ElementCheck::Ctor(const ElementInfo& I, Fn& f, u8* obj) {
    RunBothFamily::Scope scope;
    Buf pre(obj, I.size);
    ElementCode::Ctor(I, obj);
    Buf nat(obj, I.size);
    std::memcpy(obj, pre.p(), I.size);
    guest_call(f.orig, {(u64)obj});
    std::string why = compare(I, nat.p(), obj, false, false);
    std::memcpy(obj, nat.p(), I.size);
    result(f, why);
}

void ElementCheck::Initialize(const ElementInfo& I, Fn& f, u8* obj) {
    RunBothFamily::Scope scope;
    Buf pre(obj, I.size);
    ElementCode::Initialize(I, obj);
    Buf nat(obj, I.size);
    std::memcpy(obj, pre.p(), I.size);
    guest_call(f.orig, {(u64)obj});
    std::string why = compare(I, nat.p(), obj, false, false);
    std::memcpy(obj, nat.p(), I.size);
    result(f, why);
}

void ElementCheck::CtorCopy(const ElementInfo& I, Fn& f, u8* obj, const u8* src) {
    RunBothFamily::Scope scope;
    Buf pre(obj, I.size);
    ElementCode::CtorCopy(I, obj, src);
    Buf nat(obj, I.size);
    std::memcpy(obj, pre.p(), I.size);
    guest_call(f.orig, {(u64)obj, (u64)src});
    std::string why = compare(I, nat.p(), obj, true, false);
    free_long_strings(I, obj);
    std::memcpy(obj, nat.p(), I.size);
    result(f, why);
}

void ElementCheck::Assign(const ElementInfo& I, Fn& f, u8* obj, const u8* src) {
    RunBothFamily::Scope scope;
    Buf copy(I.size);
    deep_copy(I, copy.p(), obj);
    ElementCode::Assign(I, obj, src);
    guest_call(f.orig, {(u64)copy.p(), (u64)src});
    std::string why = compare(I, obj, copy.p(), true, false);
    free_long_strings(I, copy.p());
    result(f, why);
}

void ElementCheck::Dtor(const ElementInfo& I, Fn& f, u8* obj) {
    RunBothFamily::Scope scope;
    Buf copy(I.size);
    deep_copy(I, copy.p(), obj);
    ElementCode::Dtor(I, obj);
    guest_call(f.orig, {(u64)copy.p()});
    result(f, compare(I, obj, copy.p(), true, true));
}

}  // namespace soa::native::master

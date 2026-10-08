// Differential tests of the info class natives (info_class.cpp) against the guest's code, for every
// generated class: the exported default constructors (the same buffer, built by each), Initialize (two
// objects built the same way, one initialized by the guest, one by the native: the state must agree).
#include <cstring>
#include <vector>

#include "native/common/test.h"
#include "native/info/info_class.h"

namespace soa::native::info {

namespace {

struct Case {
    const InfoClass* cls;
    const char* sym;
};

#define INFO_CASE(C, SYM) {&kInfo_##C, SYM},
constexpr Case kInits[] = {INFO_INITIALIZERS(INFO_CASE)};
constexpr Case kCtors[] = {INFO_CONSTRUCTORS(INFO_CASE)};
#undef INFO_CASE

}  // namespace

// Every exported default constructor: the guest's on a 0xcc-filled buffer, then the native's on the
// same buffer filled again: the bytes must agree (the values the constructor leaves alone included).
NATIVE_TEST("info/constructors") {
    int bad = 0;
    for (const Case& c : kCtors) {
        const InfoClass& K = *c.cls;
        std::vector<u8> buf(K.size + 64), guest;
        std::memset(buf.data(), 0xcc, buf.size());
        t.call(c.sym, {reinterpret_cast<u64>(buf.data())});
        guest = buf;
        std::memset(buf.data(), 0xcc, buf.size());
        InfoCode::Ctor(K, buf.data());
        if (buf != guest && bad++ < 8) t.fail("%s: %s", K.name, live::RunBothFamily::diff_bytes(buf.data(), guest.data(), buf.size()).c_str());
    }
}

// Every Initialize: two objects built by the native constructor (values 0xcc), the guest's Initialize on
// one, the native's on the other; the state (each property's bytes, a string's text, both maps by key
// and the value's offset, the children's: their Initialize runs (the guest's) from both) must agree.
NATIVE_TEST("info/initialize") {
    int bad = 0;
    for (const Case& c : kInits) {
        const InfoClass& K = *c.cls;
        std::vector<u8> a(K.size, 0xcc), b(K.size, 0xcc);
        InfoCode::Ctor(K, a.data());
        InfoCode::Ctor(K, b.data());
        std::vector<u8> before = info_state(K, a.data());
        t.call(c.sym, {reinterpret_cast<u64>(a.data())});
        if (info_state(K, a.data()) == before && bad++ < 8) t.fail("%s: the guest's Initialize changed nothing", K.name);
        InfoCode::Initialize(K, b.data());
        if (info_state(K, a.data()) != info_state(K, b.data()) && bad++ < 8) t.fail("%s: the state differs", K.name);
        info_free_maps(K, a.data());
        info_free_maps(K, b.data());
    }
}

}  // namespace soa::native::info

// StringDB::GetNativeString / Get (master_layout.h StringDB; port/decomp/master/stringdb.c and the
// disassembly: the key formatted by the guest's CSTLStringUtility_Base::Format, the element from the
// table's native pParameterFromHash). platform370's English text hooks read the master's texts through
// StringDB::Get (platform370/src/text_370.cpp): with this native their guest_call lands here.
// Live check (family `master`): the original runs after the native on the same arguments (its lookup
// then hits the cache the native's filled) and the strings and flags are compared.
#include <cstring>

#include "native/common/native.h"
#include "native/hash/hash_layout.h"
#include "native/libcxx/libcxx_string.h"
#include "native/master/gen/master_addresses.h"
#include "native/master/master_guest.h"
#include "native/master/master_simple.h"
#include "native/params/params_check.h"

namespace soa::native::master {

namespace {

using params::String;
constexpr const char* kFormat =
    "_ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE6FormatEPKcz";
constexpr const char* kReplace =
    "_ZN9Framework22CSTLStringUtility_BaseINSt6__ndk112basic_stringIcNS1_11char_traitsIcEENS_13CSTLAllocatorIcNS_22CSTLStringAllocatorInfEEEEEE7ReplaceERKS8_SB_SB_Pb";
constexpr const char* kCrypt32 =
    "_ZN22CParameterPropertyBaseILj32EE11CryptStringINSt6__ndk112basic_stringIcNS2_11char_traitsIcEEN9Framework13CSTLAllocatorIcNS6_"
    "22CSTLStringAllocatorInfEEEEEEEvRT_RKSB_";

// A short guest string (the literal temporaries Get builds on its stack).
String short_string(const char* s) {
    String r{};
    u64 n = std::strlen(s);
    r.r.s.head.size = (u8)(n << 1);
    std::memcpy(&r.r.s.data[0], s, n);
    return r;
}

Fn* g_native_fn = nullptr;  // GetNativeString's live-check slot
Fn* g_get_fn = nullptr;     // Get's

}  // namespace

void StringDB::GetNativeString(String* out, const char* id, bool* found) {
    static const u64 format = g::sym(kFormat), crypt = g::sym(kCrypt32);
    String key{};
    u64 args[3] = {g::at(g::kFmtLangId), g::at(g::kLangJa), (u64)id};
    guest_call_raw(format, args, 3, nullptr, 0, (u64)&key);
    u32 h = hash::CHash32::Of(key.data(), key.size());
    SharedPtr p{};
    SimpleCode::pParameterFromHash(table_info<StringDBEelement>(), &table, &p, h);
    libcxx::string_destroy(&key);
    if (p.ptr) {
        if (found) *found = true;
        std::memset(out, 0, sizeof *out);
        guest_call(crypt, {(u64)out, (u64)(p.ptr + 0xa8)});  // text_value (CParameterPropertyString<32> at +0x80)
        if (p.ctrl) p.ctrl->__release_shared();
        return;
    }
    if (p.ctrl) p.ctrl->__release_shared();
    if (found) *found = false;
    // basic_string(char const*): its storage from the STL allocator when it is 23 bytes or longer
    std::memset(out, 0, sizeof *out);
    u64 n = std::strlen(id);
    char* to;
    if (n < 0x17) {
        out->r.s.head.size = (u8)(n << 1);
        to = (char*)&out->r.s.data[0];
    } else {
        u64 alloc = (n + 0x10) & ~u64(0xf);
        to = (char*)g::StringAllocate(alloc);
        out->r.l.cap = alloc | 1;
        out->r.l.size = n;
        out->r.l.data = to;
    }
    if (n) std::memcpy(to, id, n);
    to[n] = 0;
}

void StringDB::Get(String* out, const char* id, bool* found) {
    static const u64 replace = g::sym(kReplace);
    GetNativeString(out, id, found);
    String from = short_string("\\n"), to = short_string("\n"), res{};
    u64 args[4] = {(u64)out, (u64)&from, (u64)&to, 0};
    guest_call_raw(replace, args, 4, nullptr, 0, (u64)&res);
    // *out = std::move(res): cleared, its storage released (reserve(0)), then the words taken
    if (out->is_long()) {
        out->r.l.data[0] = 0;
        out->r.l.size = 0;
    } else {
        out->r.s.head.size = 0;
        out->r.s.data[0] = 0;
    }
    out->reserve(0);
    *out = res;
}

namespace {

void check_string(Fn& f, const String& n, bool nf, String& g, bool gf) {
    std::string why = nf != gf ? "found" : params::diff_strings(n, g);
    if (why.empty() && n.is_long() && std::memcmp(n.data(), g.data(), n.size())) why = "bytes";
    libcxx::string_destroy(&g);
    fam().result(f, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
}

void h_get_native(Cpu& c) {
    auto* self = reinterpret_cast<StringDB*>(c.x(0));
    auto* out = reinterpret_cast<String*>(c.x(8));
    const char* id = reinterpret_cast<const char*>(c.x(1));
    bool* found = reinterpret_cast<bool*>(c.x(2));
    if (!g_native_fn || !fam().due(*g_native_fn)) return self->GetNativeString(out, id, found);
    live::RunBothFamily::Scope scope;
    bool nf = false, gf = false;
    self->GetNativeString(out, id, &nf);
    String g{};
    u64 args[3] = {(u64)self, (u64)id, (u64)&gf};
    guest_call_raw(g_native_fn->orig, args, 3, nullptr, 0, (u64)&g);
    if (found) *found = nf;
    check_string(*g_native_fn, *out, nf, g, gf);
}

void h_get(Cpu& c) {
    auto* self = reinterpret_cast<StringDB*>(c.x(0));
    auto* out = reinterpret_cast<String*>(c.x(8));
    const char* id = reinterpret_cast<const char*>(c.x(1));
    bool* found = reinterpret_cast<bool*>(c.x(2));
    if (!g_get_fn || !fam().due(*g_get_fn)) return self->Get(out, id, found);
    live::RunBothFamily::Scope scope;
    bool nf = false, gf = false;
    self->Get(out, id, &nf);
    String g{};
    u64 args[3] = {(u64)self, (u64)id, (u64)&gf};
    guest_call_raw(g_get_fn->orig, args, 3, nullptr, 0, (u64)&g);
    if (found) *found = nf;
    check_string(*g_get_fn, *out, nf, g, gf);
}

bool bind() {
    g_native_fn = new Fn(fam(), "_ZN8StringDB15GetNativeStringEPKcPb");
    g_get_fn = new Fn(fam(), "_ZN8StringDB3GetEPKcPb");
    register_native_function({g_native_fn->sym, &h_get_native, "master: StringDB::GetNativeString", nullptr, &g_native_fn->orig, nullptr,
                              "StringDB::GetNativeString"});
    register_native_function({g_get_fn->sym, &h_get, "master: StringDB::Get", nullptr, &g_get_fn->orig, nullptr, "StringDB::Get"});
    return true;
}
[[maybe_unused]] const bool g_bound = bind();

}  // namespace

}  // namespace soa::native::master

// The one native patch of the 3.7.0 client (platform370::install_patches, Config::patch):
// master_global.service_stop_day is hidden from the game, so the client runs on the real date
// (emulator/README.md "The date and service_stop_day"; docs/client-changes.md "Emulator mode").
//
// What the client does with the row (work/libSOA-3.7.0.so; every reader of the key: the string
// "service_stop_day" @0x27652ac has two references, both through
// CParameterUtility::FindGlobalStringWithKey; no code uses the key's id 0x25cf21e2):
//   1. CTitle::Setup @0x1d83d9c-0x1d83ec8: str2time_t(value) <= CTimeUtility::NowTimeTrue() sets
//      CTitle+0x91d (the service has ended), and then pay_back_stop >= now sets +0x91e (the
//      refund period runs). With +0x91d the title shows the service-end notice and "TAP TO START"
//      opens the "update the app" dialog instead of logging in.
//   2. CPhase_Server::CPhase_Server @0x17c3774-0x17c37f0 stores str2time_t(value) at +0x30. The
//      error handler of its first request (the lambda @0x17c459c, at 0x17c47b8-0x17c47cc) skips
//      the error dialog (with its retry) and ends the phase (state 10) when that time is set and
//      <= NowTimeTrue().
// Both read the value as a string and skip their check when it is empty (cbz on the size at
// 0x1d83df4 and 0x17c37c8) -- what the client does with a master that has no such row.
//
// The patch: FindGlobalStringWithKey (0x58 bytes, @0x1716640) is hooked with a host function
// that answers "service_stop_day" with the empty string (what the original returns for a missing
// key) and runs the original guest code, through a trampoline, for every other key. So the check
// never happens, at both sites, whatever the date; everything else reads the master as before.
// soa-server does the same on the data side: the master it serves drops the row
// (apply_client_master), but the first boot reads the APK's built-in master, which has it.
//
// Installed after load_library and before any guest code runs (run_initializers), so no JIT has
// translated the function yet. The runtime's guest-function hook (core/cpu.h:
// hook_guest_function, make_original_trampoline) does the patching, as for the port's natives.
// A host that replaces FindGlobalStringWithKey itself (the port's native) applies the same rule
// through platform370::hides_global_key instead (platform370/README.md "Hosts with natives").
#include <cstring>

#include "core/cpu.h"
#include "core/loader.h"
#include "core/log.h"
#include "internal.h"
#include "platform370/platform370.h"

namespace soa::platform370 {
namespace {

constexpr const char* kFindGlobalStringWithKey =
    "_ZN17CParameterUtility23FindGlobalStringWithKeyERKNSt6__ndk112basic_stringIcNS0_11char_traitsIcEEN9Framework13"
    "CSTLAllocatorIcNS4_22CSTLStringAllocatorInfEEEEE";
// Its first two instructions in 3.7.0 (sub sp, sp, #0x20; stp x19, x30, [sp, #0x10]): the
// trampoline relocates them, and a different library isn't patched.
constexpr u32 kEntry0 = 0xd10083ff, kEntry1 = 0xa9017bf3;
constexpr const char* kKey = detail::kHiddenGlobalKey;
constexpr size_t kKeyLen = sizeof detail::kHiddenGlobalKey - 1;

u64 g_orig = 0, g_base = 0;

// A guest libc++ string (24 bytes; CSTLAllocator doesn't change the layout): short form when bit
// 0 of byte 0 is clear (size = byte0 >> 1, chars from byte 1), else {cap|1, size, data}.
bool guest_string_is(u64 s, const char* want, size_t n) {
    const u8* p = (const u8*)s;
    size_t size;
    const char* data;
    if (!(p[0] & 1)) size = p[0] >> 1, data = (const char*)p + 1;
    else size = *(const u64*)(p + 8), data = *(const char* const*)(p + 16);
    return size == n && std::memcmp(data, want, n) == 0;
}

// std::string CParameterUtility::FindGlobalStringWithKey(std::string const& key): x0 = key,
// x8 = the result.
void h_find_global_string_with_key(Cpu& c) {
    u64 key = c.x(0), out = c.x(8);
    if (guest_string_is(key, kKey, kKeyLen)) {
        std::memset((void*)out, 0, 24);  // "": as the original's not-found path (0x1716658-0x171665c)
        LOGI("p370", "patch: master_global.service_stop_day read (from %#llx); answered \"\" (the service-end check is skipped)",
             (unsigned long long)(c.lr() - g_base));
        return;
    }
    u64 ints[1] = {key};
    guest_call_raw(g_orig, ints, 1, nullptr, 0, out);
}

}  // namespace

PatchStatus install_patches(LoadedLib& lib) {
    if (!detail::patch_enabled()) return PatchStatus::Disabled;
    u64 a = lib.sym(kFindGlobalStringWithKey);
    if (!a || ((const u32*)a)[0] != kEntry0 || ((const u32*)a)[1] != kEntry1) {
        LOGW("p370", "patch: CParameterUtility::FindGlobalStringWithKey isn't 3.7.0's; service_stop_day not hidden");
        return PatchStatus::NotFound;
    }
    g_base = lib.base;
    g_orig = make_original_trampoline(a);
    if (!g_orig) fatal("platform370: FindGlobalStringWithKey's prologue can't be relocated");
    hook_guest_function(a, "CParameterUtility::FindGlobalStringWithKey [platform370: hides service_stop_day]", h_find_global_string_with_key);
    LOGI("p370", "patch: CParameterUtility::FindGlobalStringWithKey hooked at %#llx: master_global.service_stop_day is hidden",
         (unsigned long long)(a - lib.base));
    return PatchStatus::Hooked;
}

}  // namespace soa::platform370

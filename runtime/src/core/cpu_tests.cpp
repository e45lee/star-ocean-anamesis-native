// Runtime tests of the guest CPU (core/selftest.h). Run by `soa --selftest` and soaruntime_tests.
//
// cpu/tbi-tagged-data-addresses: AArch64 Top Byte Ignore. Linux enables TBI0 for user space, so
// bits 56-63 of a data address are ignored by loads, stores and exclusives. A guest access
// through a tagged address must reach the same memory as the untagged address (CpuCallbacks in
// cpu.cpp; dynarmic's fastmem faults on the non-canonical x86-64 address and falls back to the
// callbacks). 3.7.0 Aska::Yayoi::Socket::Poll reads `[fdset + 0x1ffffffffffffff8]` when the main
// thread closed the socket (fd = -1) meanwhile: on a phone that reads fdset - 8; before this the
// JIT crashed there (emulator/README.md "Error replies and the tagged-address crash").
#include <cinttypes>
#include <cstring>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/selftest.h"

namespace soa {
namespace {

// AArch64 encodings used below.
constexpr u32 ldr_x(int t, int n, int imm) { return 0xf9400000u | (u32)(imm / 8) << 10 | (u32)n << 5 | (u32)t; }
constexpr u32 str_x(int t, int n, int imm) { return 0xf9000000u | (u32)(imm / 8) << 10 | (u32)n << 5 | (u32)t; }
constexpr u32 ldrb_w(int t, int n, int imm) { return 0x39400000u | (u32)imm << 10 | (u32)n << 5 | (u32)t; }
constexpr u32 strb_w(int t, int n, int imm) { return 0x39000000u | (u32)imm << 10 | (u32)n << 5 | (u32)t; }
constexpr u32 ldr_q(int t, int n, int imm) { return 0x3dc00000u | (u32)(imm / 16) << 10 | (u32)n << 5 | (u32)t; }
constexpr u32 str_q(int t, int n, int imm) { return 0x3d800000u | (u32)(imm / 16) << 10 | (u32)n << 5 | (u32)t; }
constexpr u32 add_x(int d, int n, int imm) { return 0x91000000u | (u32)imm << 10 | (u32)n << 5 | (u32)d; }
constexpr u32 add_w(int d, int n, int imm) { return 0x11000000u | (u32)imm << 10 | (u32)n << 5 | (u32)d; }
constexpr u32 ldaxr_x(int t, int n) { return 0xc85ffc00u | (u32)n << 5 | (u32)t; }
constexpr u32 stlxr_x(int s, int t, int n) { return 0xc800fc00u | (u32)s << 16 | (u32)n << 5 | (u32)t; }
constexpr u32 cbnz_w(int t, int words) { return 0x35000000u | ((u32)words & 0x7ffff) << 5 | (u32)t; }
constexpr u32 mov_x(int d, int m) { return 0xaa0003e0u | (u32)m << 16 | (u32)d; }
constexpr u32 kRetInsn = 0xd65f03c0u;

// probe(x0 = block, x1 = v) -> block[0]
//   block[1] = v; block[2] += 1 (an LDAXR/STLXR loop); byte block[3] += 1;
//   16 bytes at +32 copied to +48 (128-bit load / store)
const u32 kProbe[] = {
    ldr_x(2, 0, 0),     // ldr   x2, [x0]
    str_x(1, 0, 8),     // str   x1, [x0, #8]
    add_x(4, 0, 16),    // add   x4, x0, #16
    ldaxr_x(3, 4),      // 1: ldaxr x3, [x4]
    add_x(3, 3, 1),     //    add   x3, x3, #1
    stlxr_x(5, 3, 4),   //    stlxr w5, x3, [x4]
    cbnz_w(5, -3),      //    cbnz  w5, 1b
    ldrb_w(6, 0, 24),   // ldrb  w6, [x0, #24]
    add_w(6, 6, 1),     // add   w6, w6, #1
    strb_w(6, 0, 24),   // strb  w6, [x0, #24]
    ldr_q(0, 0, 32),    // ldr   q0, [x0, #32]
    str_q(0, 0, 48),    // str   q0, [x0, #48]
    mov_x(0, 2),        // mov   x0, x2
    kRetInsn,
};

RUNTIME_TEST("cpu/tbi-tagged-data-addresses") {
    auto* code = (u32*)map_guest_code(4096);
    std::memcpy(code, kProbe, sizeof kProbe);
    alignas(16) static u64 block[8];
    // Untagged first (compiled with fastmem), then tagged as Android's heap tags (0xb4) and with
    // every top bit set: the first tagged call faults in fastmem and falls back to the callbacks,
    // later ones run the recompiled code (callbacks only), so both paths are covered.
    const u64 tags[] = {0, 0xb4, 0xff, 0x01, 0x20, 0xb4};  // 0x20: Socket::Poll's fd = -1 address
    u64 expect_counter = 0;
    u8 expect_byte = 0x10;
    block[2] = 0;
    block[3] = 0x10;
    for (size_t k = 0; k < sizeof tags / sizeof *tags; k++) {
        u64 tag = tags[k];
        block[0] = 0x1111000000000000ull + k;
        block[1] = 0;
        block[4] = 0xa5a5a5a5a5a5a5a5ull ^ k;
        block[5] = 0x5a5a5a5a5a5a5a5aull ^ k;
        block[6] = block[7] = 0;
        u64 addr = (u64)block | tag << 56;
        u64 v = 0x2222000000000000ull + k;
        u64 r = guest_call((u64)code, {addr, v});
        expect_counter++;
        expect_byte++;
        if (r != block[0]) t.fail("tag %#" PRIx64 ": load read %#" PRIx64 ", memory has %#" PRIx64, tag, r, block[0]);
        if (block[1] != v) t.fail("tag %#" PRIx64 ": store wrote %#" PRIx64 ", expected %#" PRIx64, tag, block[1], v);
        if (block[2] != expect_counter) t.fail("tag %#" PRIx64 ": exclusive increment: %" PRIu64 ", expected %" PRIu64, tag, block[2], expect_counter);
        if ((u8)block[3] != expect_byte) t.fail("tag %#" PRIx64 ": byte increment: %#x, expected %#x", tag, (u8)block[3], expect_byte);
        if (block[6] != block[4] || block[7] != block[5]) t.fail("tag %#" PRIx64 ": 128-bit copy differs", tag);
    }
    unmap_guest_code(code, 4096);
}

}  // namespace
}  // namespace soa

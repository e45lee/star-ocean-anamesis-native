// The GDB remote protocol's encodings (core/gdb_protocol.h): pure, no socket. Also run by
// build/runtime/soaruntime_tests; the stub end to end is runtime/tests/gdbstub_test.cpp.
#include <string>
#include <vector>

#include "core/gdb_protocol.h"
#include "soaruntime/core/selftest.h"

namespace soa {
namespace {

using namespace gdbrsp;

RUNTIME_TEST("gdb/protocol-framing") {
    t.expect_eq(frame("OK"), std::string("$OK#9a"), "frame OK");
    t.expect_eq(frame("a$b"), std::string("$a}\x04" "b#44"), "frame escapes $");
    Reader r;
    r.buf = "+$qC#b4$m10,4#";
    bool bad = true;
    auto p = r.next(&bad);
    t.expect_eq(p.has_value() && *p == "qC" && !bad, true, "reads a packet after an ack");
    t.expect_eq(r.next().has_value(), false, "an incomplete packet waits for more bytes");
    r.buf += "2e\x03";
    p = r.next();
    t.expect_eq(p.has_value() && *p == "m10,4", true, "completes it");
    p = r.next();
    t.expect_eq(p.has_value() && *p == "\x03", true, "an interrupt byte");
    r.buf = "$qC#00";
    p = r.next(&bad);
    t.expect_eq(bad, true, "a bad checksum is reported");
    t.expect_eq(unescape("a}\x03" "b0* "), std::string("a#b0000"), "unescape and run-length decode");
}

RUNTIME_TEST("gdb/protocol-encodings") {
    t.expect_eq(le_hex(0x1122334455667788ull, 8), std::string("8877665544332211"), "le_hex 8");
    t.expect_eq(le_hex(0xdeadbeef, 4), std::string("efbeadde"), "le_hex 4");
    t.expect_eq(le_from_hex("efbeadde"), (uint64_t)0xdeadbeef, "le_from_hex");
    std::string b;
    t.expect_eq(from_hex("00ff41", b) && b == std::string("\0\xff" "A", 3), true, "from_hex");
    t.expect_eq(from_hex("0", b), false, "from_hex odd length");
    t.expect_eq(to_hex(std::string("\x01\xab", 2)), std::string("01ab"), "to_hex");
    size_t i = 1;
    uint64_t v;
    t.expect_eq(parse_hex("m7fff0000,10", i, v) && v == 0x7fff0000 && i == 9, true, "parse_hex");
    std::vector<VContAction> a;
    t.expect_eq(parse_vcont("vCont;s:1f;c", a) && a.size() == 2 && a[0].op == 's' && a[0].tid == 0x1f && a[1].op == 'c' && a[1].tid == -1, true,
                "vCont;s:1f;c");
    t.expect_eq(parse_vcont("vCont;C05:-1", a) && a.size() == 1 && a[0].op == 'c' && a[0].tid == -1, true, "vCont;C05:-1");
    t.expect_eq(parse_vcont("vCont;x", a), false, "vCont with an unknown action");
}

}  // namespace
}  // namespace soa

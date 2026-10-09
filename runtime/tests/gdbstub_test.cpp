// The GDB stub (core/gdbstub.h) end to end, without the game: a guest loop runs on its own thread
// under the JIT while a raw protocol client attaches, stops it, reads registers and memory, sets a
// breakpoint, hits it, single-steps, writes memory, continues and detaches; the guest then finishes
// normally. Run from soaruntime_tests' main (not a RUNTIME_TEST: it turns the debugger hooks on for
// the whole process, which a game's --selftest must not).
//
// Then the same with the loop's leaf replaced by a native (hook_guest_function): a breakpoint there
// stops before the native runs, with the guest's argument in x0; a step runs the native; and the
// stub over IPv6 ([::1], skipped when the host has no IPv6 loopback).
//
// `soaruntime_tests --gdb-demo HOST:PORT [--fault] [--native] [--at-leaf] [--slow-park]` runs the same
// guest loop with the stub listening until a debugger sets the loop's stop flag
// (control/tests/test_gdbclient.py drives it with control/gdbclient.py; gdb-multiarch can attach too).
// With --fault the guest then loads from address 0x10: the fault (SIGSEGV) is reported to the
// attached debugger before the process dies. With --native the leaf is a native (`monitor natives`
// lists it as gdb_demo_leaf). With --at-leaf the guest is already stopped at the leaf's first
// instruction when the debugger attaches (where a breakpoint will go). With --slow-park a thread
// whose JIT stopped sleeps 200 ms before it parks (a loaded host's scheduling, made certain).
#include "gdbstub_test.h"

#include <soa/sock.h>  // (Winsock first on Windows)

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/prctl.h>
#include <sys/resource.h>
#endif

#include <atomic>
#include <chrono>
#include <cinttypes>
#include <cstdio>
#include <cstring>
#include <functional>
#include <string>
#include <thread>

#include "soaruntime/core/cpu.h"
#include "core/gdb_protocol.h"
#include "soaruntime/core/gdbstub.h"
#include "soaruntime/core/log.h"

using namespace soa;

namespace {

// entry(x0 = data): x19 = data; loop { data[0]++; x0 = leaf(data[0]); data[2] = x0; } until data[1]
const u32 kLoop[] = {
    0xaa1e03f4,  // 0x00 mov x20, x30
    0xaa0003f3,  // 0x04 mov x19, x0
    0xf9400260,  // 0x08 loop: ldr x0, [x19]
    0x91000400,  // 0x0c add x0, x0, #1
    0xf9000260,  // 0x10 str x0, [x19]
    0x94000006,  // 0x14 bl leaf
    0xf9000a60,  // 0x18 str x0, [x19, #16]
    0xf9400662,  // 0x1c ldr x2, [x19, #8]
    0xb4ffff42,  // 0x20 cbz x2, loop
    0xaa1403fe,  // 0x24 mov x30, x20
    0xd65f03c0,  // 0x28 ret
    0x91004000,  // 0x2c leaf: add x0, x0, #0x10
    0x9e670000,  // 0x30 fmov d0, x0
    0xd65f03c0,  // 0x34 ret
    0xf9400000,  // 0x38 fault: ldr x0, [x0]
    0xd65f03c0,  // 0x3c ret
};
constexpr u64 kLeaf = 0x2c, kFault = 0x38;

// The native that replaces the leaf with --native / in the natives check: what the leaf computes
// (x0 + 0x10, also in d0), counted.
std::atomic<u64> g_native_calls{0};
void host_leaf(Cpu& c) {
    c.set_x(0, c.x(0) + 0x10);
    c.set_v(0, {c.x(0), 0});
    g_native_calls++;
}

struct Guest {
    u32* code = nullptr;
    alignas(16) u64 data[8] = {};
    std::thread th;
    std::atomic<bool> done{false};
    void start(bool fault, bool native = false) {
        code = (u32*)map_guest_code(4096);
        memcpy(code, kLoop, sizeof kLoop);
        if (native) hook_guest_function((u64)code + kLeaf, "gdb_demo_leaf", host_leaf, "host_leaf");
        th = std::thread([this, fault] {
            guest_call((u64)code, {(u64)data});
            done = true;
            if (fault) guest_call((u64)code + kFault, {0x10});
        });
    }
};

struct Client {
    int fd = -1;
    gdbrsp::Reader rd;
    bool connect_to(int port, bool v6 = false) {
        sock::startup();
        fd = sock::tcp_socket(false, v6 ? AF_INET6 : AF_INET);
        if (fd < 0) return false;
        sockaddr_storage ss{};
        int len;
        if (v6) {
            auto* a = (sockaddr_in6*)&ss;
            a->sin6_family = AF_INET6;
            a->sin6_port = htons((u16)port);
            a->sin6_addr = in6addr_loopback;
            len = sizeof *a;
        } else {
            auto* a = (sockaddr_in*)&ss;
            a->sin_family = AF_INET;
            a->sin_port = htons((u16)port);
            a->sin_addr.s_addr = htonl(INADDR_LOOPBACK);
            len = sizeof *a;
        }
        if (::connect(fd, (sockaddr*)&ss, len) != 0) return false;
        sock::set_timeouts(fd, 10);
        return true;
    }
    std::string cmd(const std::string& p) {
        std::string f = gdbrsp::frame(p);
        if (sock::send(fd, f.data(), f.size()) != (ssize_t)f.size()) return "<send failed>";
        for (;;) {
            if (auto r = rd.next()) return *r;
            char b[4096];
            ssize_t n = sock::recv(fd, b, sizeof b);
            if (n <= 0) return "<closed>";
            rd.buf.append(b, (size_t)n);
        }
    }
    // A monitor command's console output (the O packets) up to its OK.
    std::string monitor(const std::string& command) {
        std::string out, r = cmd("qRcmd," + gdbrsp::to_hex(command));
        while (r.size() > 1 && r[0] == 'O' && r != "OK") {
            std::string t;
            gdbrsp::from_hex(r.substr(1), t);
            out += t;
            r = next();
        }
        return out;
    }
    std::string next() {
        for (;;) {
            if (auto r = rd.next()) return *r;
            char b[4096];
            ssize_t n = sock::recv(fd, b, sizeof b);
            if (n <= 0) return "<closed>";
            rd.buf.append(b, (size_t)n);
        }
    }
    ~Client() {
        if (fd >= 0) sock::close(fd);
    }
};

std::string hexu(u64 v) {
    char b[24];
    snprintf(b, sizeof b, "%" PRIx64, v);
    return b;
}

u64 reg(Client& c, int n) {
    char b[16];
    snprintf(b, sizeof b, "p%x", n);
    return gdbrsp::le_from_hex(c.cmd(b));
}

int tid_of(const std::string& stop) {
    size_t i = stop.find("thread:");
    if (i == std::string::npos) return 0;
    return (int)strtol(stop.c_str() + i + 7, nullptr, 16);
}

bool wait_for(const std::function<bool()>& f, int ms = 5000) {
    for (int i = 0; i < ms; i++) {
        if (f()) return true;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    return f();
}

// A breakpoint on a native: the loop's leaf replaced by host_leaf.
void check_native_breakpoint(void (*check)(bool, const char*)) {
    Guest g;
    g.start(false, true);
    const u64 leaf = (u64)g.code + kLeaf;
    check(wait_for([&] { return g.data[0] > 1000; }) && g_native_calls > 1000, "gdb natives: the loop runs with its leaf a native");
    Client c;
    check(c.connect_to(gdb_port()), "gdb natives: a client connects");
    c.cmd("QStartNoAckMode");
    c.cmd("?");  // (reports any thread: the loop's spends its time in the native, host code)
    std::string mon = c.monitor("natives gdb_demo");
    check(mon.find("0x" + hexu(leaf) + "\tgdb_demo_leaf\tgdb_demo_leaf\thost_leaf\t0x" + hexu((u64)(uintptr_t)&host_leaf)) != std::string::npos &&
              mon.find("# 1 natives") == 0,
          "gdb natives: monitor natives lists the leaf (guest address, symbol, the C++, host address)");
    check(c.cmd("Z0," + hexu(leaf) + ",4") == "OK" && (g.code[kLeaf / 4] & 0xffe0001fu) == 0xd4000001u,
          "gdb natives: Z0 on a native's entry is accepted (the hook's SVC stays)");
    std::string stop = c.cmd("vCont;c");
    u64 calls = g_native_calls;
    const int tid = tid_of(stop);
    check(c.cmd("Hg" + hexu((u64)tid)) == "OK" && stop.rfind("T05", 0) == 0 && stop.find("swbreak") != std::string::npos && reg(c, 32) == leaf,
          "gdb natives: continue stops at the native's guest entry (T05 swbreak, pc at it)");
    check(reg(c, 0) == g.data[0] && calls == g.data[0] - 1, "gdb natives: before the native runs, x0 holds the guest's argument");
    check(c.cmd("P0=" + gdbrsp::le_hex(g.data[0] + 0x1000, 8)) == "OK", "gdb natives: a register write at the entry (x0 += 0x1000)");
    check(c.cmd("z0," + hexu(leaf) + ",4") == "OK", "gdb natives: z0 removes it");
    stop = c.cmd("vCont;s:" + hexu((u64)tid));
    check(stop.rfind("T05", 0) == 0 && tid_of(stop) == tid && reg(c, 32) == leaf + 4 && g_native_calls == calls + 1,
          "gdb natives: a step runs the whole native and stops at the hook's RET");
    check(reg(c, 0) == g.data[0] + 0x1000 + 0x10, "gdb natives: the native saw the written argument (x0 = arg + 0x10)");
    check(c.cmd("Z0," + hexu(leaf) + ",4") == "OK" && c.cmd("c").find("swbreak") != std::string::npos && reg(c, 32) == leaf &&
              g_native_calls == calls + 1,
          "gdb natives: continue runs on to the next call (the native ran once in between)");
    c.cmd("M" + hexu((u64)(g.data + 1)) + ",8:0100000000000000");
    check(c.cmd("D") == "OK", "gdb natives: detach");
    check(wait_for([&] { return g.done.load(); }), "gdb natives: after detach the loop runs to its end");
    if (g.th.joinable()) g.th.join();
    check(g_native_calls == g.data[0] && hooked_host_fn(leaf) == &host_leaf, "gdb natives: every call ran the native; the hook stays");
    unmap_guest_code(g.code, 4096);
}

// The stub on [::1] (an IPv6 client): attach, stop, read, detach.
void check_ipv6(void (*check)(bool, const char*)) {
    std::string err;
    if (!gdb_listen("[::1]:0", &err)) {
        fprintf(stderr, "skip  gdb: no IPv6 loopback here (%s)\n", err.c_str());
        return;
    }
    Guest g;
    g.start(false);
    wait_for([&] { return g.data[0] > 1000; });
    {
        Client c;
        check(c.connect_to(gdb_port(), true), "gdb ipv6: a client connects to [::1]");
        std::string stop = c.cmd("?");
        check(stop.rfind("T05thread:", 0) == 0, "gdb ipv6: '?' stops the guest");
        check(gdbrsp::le_from_hex(c.cmd("m" + hexu((u64)g.data) + ",8")) == g.data[0], "gdb ipv6: memory reads back");
        c.cmd("M" + hexu((u64)(g.data + 1)) + ",8:0100000000000000");
        check(c.cmd("D") == "OK", "gdb ipv6: detach");
    }
    check(wait_for([&] { return g.done.load(); }), "gdb ipv6: the guest runs to its end");
    if (g.th.joinable()) g.th.join();
    gdb_shutdown();
    unmap_guest_code(g.code, 4096);
}

}  // namespace

void run_gdbstub_tests(void (*check)(bool, const char*)) {
    std::string err;
    check(gdb_listen("127.0.0.1:0", &err) && gdb_port() > 0, "gdb: the stub listens on an ephemeral port");
    Guest g;
    g.start(false);
    check(wait_for([&] { return g.data[0] > 1000; }), "gdb: the guest loop runs under the JIT");

    Client c;
    check(c.connect_to(gdb_port()), "gdb: a client connects");
    std::string sup = c.cmd("qSupported:multiprocess+;swbreak+;xmlRegisters=i386");
    check(sup.find("qXfer:features:read+") != std::string::npos && sup.find("swbreak+") != std::string::npos, "gdb: qSupported");
    check(c.cmd("QStartNoAckMode") == "OK", "gdb: no-ack mode");
    std::string stop = c.cmd("?");
    int tid = tid_of(stop);
    check(stop.rfind("T05thread:", 0) == 0 && tid > 0, "gdb: '?' stops the guest and reports a thread");
    check(c.cmd("qfThreadInfo").find(hexu((u64)tid)) != std::string::npos,
          "gdb: qfThreadInfo lists the guest thread");
    std::string xml = c.cmd("qXfer:features:read:target.xml:0,3fff");
    check(xml.size() > 1 && xml[0] == 'l' && xml.find("org.gnu.gdb.aarch64.core") != std::string::npos && xml.find("org.gnu.gdb.aarch64.fpu") != std::string::npos,
          "gdb: the target description (core + fpu)");

    char h[64];
    snprintf(h, sizeof h, "Hg%x", tid);
    check(c.cmd(h) == "OK", "gdb: Hg selects the thread");
    std::string regs = c.cmd("g");
    check(regs.size() == 2 * (33 * 8 + 4 + 32 * 16 + 8), "gdb: 'g' returns x0-x30, sp, pc, cpsr, v0-v31, fpsr, fpcr");
    check(gdbrsp::le_from_hex(regs.substr(19 * 16, 16)) == (u64)g.data, "gdb: x19 holds the loop's data pointer");
    u64 n0 = g.data[0];
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    snprintf(h, sizeof h, "m%" PRIx64 ",8", (u64)g.data);
    check(gdbrsp::le_from_hex(c.cmd(h)) == n0 && g.data[0] == n0, "gdb: stopped: memory reads back and the counter doesn't move");
    check(c.cmd("m10,8") == "E14", "gdb: reading unmapped memory is an error reply");

    const u64 leaf = (u64)g.code + kLeaf;
    snprintf(h, sizeof h, "Z0,%" PRIx64 ",4", leaf);
    check(c.cmd(h) == "OK", "gdb: Z0 inserts a breakpoint");
    snprintf(h, sizeof h, "m%" PRIx64 ",4", leaf);
    check(c.cmd(h) == "00400091", "gdb: memory reads show the original instruction under a breakpoint");
    stop = c.cmd("vCont;c");
    check(stop.rfind("T05", 0) == 0 && stop.find("swbreak") != std::string::npos && tid_of(stop) == tid, "gdb: continue runs to the breakpoint (T05 swbreak)");
    check(reg(c, 32) == leaf, "gdb: pc is at the breakpoint");
    u64 x0 = reg(c, 0);
    check(x0 == g.data[0], "gdb: x0 is the counter passed to the leaf");

    // Step over the breakpoint as gdb does: remove, step this thread, re-insert.
    snprintf(h, sizeof h, "z0,%" PRIx64 ",4", leaf);
    check(c.cmd(h) == "OK", "gdb: z0 removes the breakpoint");
    snprintf(h, sizeof h, "vCont;s:%x", tid);
    stop = c.cmd(h);
    check(stop.rfind("T05", 0) == 0 && tid_of(stop) == tid, "gdb: vCont;s steps the thread");
    check(reg(c, 32) == leaf + 4 && reg(c, 0) == x0 + 0x10, "gdb: one instruction executed (pc + 4, x0 + 0x10)");
    check(c.cmd("s").rfind("T05", 0) == 0 && reg(c, 32) == leaf + 8, "gdb: 's' steps again (fmov)");
    check(reg(c, 34) == x0 + 0x10, "gdb: v0 (fmov d0, x0) reads back");
    check(c.cmd("P15=efbeadde00000000") == "OK" && reg(c, 21) == 0xdeadbeef, "gdb: P writes a register (x21)");
    snprintf(h, sizeof h, "Z0,%" PRIx64 ",4", leaf);
    c.cmd(h);
    stop = c.cmd("c");
    check(stop.find("swbreak") != std::string::npos && g.data[0] == x0 + 1, "gdb: 'c' runs one more iteration to the breakpoint");

    // Let the loop end: data[1] = 1 (M), then detach.
    snprintf(h, sizeof h, "M%" PRIx64 ",8:0100000000000000", (u64)(g.data + 1));
    check(c.cmd(h) == "OK" && g.data[1] == 1, "gdb: M writes guest memory");
    std::string x = "X" + hexu((u64)(g.data + 3)) + ",8:" + std::string("\x24\x23\x7d\x2a\x01\x02\x03\x04", 8);  // frame() escapes $ # } *
    check(c.cmd(x) == "OK" && g.data[3] == 0x040302012a7d2324ull, "gdb: X writes binary (escaped) data");
    check(c.monitor("threads").find("parked") != std::string::npos, "gdb: monitor threads");
    check(c.cmd("D") == "OK", "gdb: detach");
    check(wait_for([&] { return g.done.load(); }), "gdb: after detach the breakpoint is gone and the guest runs to its end");
    if (g.th.joinable()) g.th.join();
    check(g.data[2] == g.data[0] + 0x10 && g.code[kLeaf / 4] == 0x91004000, "gdb: the guest's results are consistent; the code is restored");
    unmap_guest_code(g.code, 4096);

    check_native_breakpoint(check);
    gdb_shutdown();
    check_ipv6(check);
}

int run_gdb_demo(const char* addr, const GdbDemoOptions& o) {
    const bool fault = o.fault, native = o.native;
    std::string err;
    if (!gdb_listen(addr, &err)) {
        fprintf(stderr, "%s\n", err.c_str());
        return 2;
    }
    if (fault) {  // the crash is the point: no core dump / crash dialog
#ifdef _WIN32
        SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
#else
        // (a piped core_pattern, e.g. WSL's crash capture, ignores RLIMIT_CORE 0, and dumping the
        // JIT's mappings took 20 s under load)
        rlimit rl{0, 0};
        setrlimit(RLIMIT_CORE, &rl);
        prctl(PR_SET_DUMPABLE, 0);
#endif
    }
    Guest g;
    g.start(fault, native);
    while (g.data[0] < 1000) std::this_thread::sleep_for(std::chrono::milliseconds(1));  // the loop is running
    if (o.slow_park) g_gdb_before_park = [] { std::this_thread::sleep_for(std::chrono::milliseconds(200)); };
    if (o.at_leaf && !gdb_stop_at((u64)g.code + kLeaf, 10000)) {
        fprintf(stderr, "gdb-demo: the loop didn't reach the leaf\n");
        return 2;
    }
    // For the client: where the loop's code and data are (control/tests/test_gdbclient.py); with
    // --native the native's call counter (host memory, readable through the stub too).
    printf("gdb-demo port %d code 0x%" PRIx64 " data 0x%" PRIx64 " leaf 0x%" PRIx64 " calls 0x%" PRIx64 "\n", gdb_port(), (u64)g.code,
           (u64)g.data, (u64)g.code + kLeaf, (u64)(uintptr_t)&g_native_calls);
    fflush(stdout);
    g.th.join();
    printf("gdb-demo done: counter %" PRIu64 "\n", g.data[0]);
    fflush(stdout);
    gdb_shutdown();
    return 0;
}

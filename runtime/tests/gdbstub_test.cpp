// The GDB stub (core/gdbstub.h) end to end, without the game: a guest loop runs on its own thread
// under the JIT while a raw protocol client attaches, stops it, reads registers and memory, sets a
// breakpoint, hits it, single-steps, writes memory, continues and detaches; the guest then finishes
// normally. Run from soaruntime_tests' main (not a RUNTIME_TEST: it turns the debugger hooks on for
// the whole process, which a game's --selftest must not).
//
// `soaruntime_tests --gdb-demo HOST:PORT [--fault]` runs the same guest loop with the stub listening
// until a debugger sets the loop's stop flag (control/tests/test_gdbclient.py drives it with
// control/gdbclient.py; gdb-multiarch can attach too). With --fault the guest then loads from
// address 0x10: the SIGSEGV is reported to the attached debugger before the process dies.
#include "gdbstub_test.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <cstdio>
#include <cstring>
#include <functional>
#include <string>
#include <thread>

#include "core/cpu.h"
#include "core/gdb_protocol.h"
#include "core/gdbstub.h"
#include "core/log.h"

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

struct Guest {
    u32* code = nullptr;
    alignas(16) u64 data[8] = {};
    std::thread th;
    std::atomic<bool> done{false};
    void start(bool fault) {
        code = (u32*)map_guest_code(4096);
        memcpy(code, kLoop, sizeof kLoop);
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
    bool connect_to(int port) {
        fd = socket(AF_INET, SOCK_STREAM, 0);
        sockaddr_in a{};
        a.sin_family = AF_INET;
        a.sin_port = htons((u16)port);
        a.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        if (::connect(fd, (sockaddr*)&a, sizeof a) != 0) return false;
        timeval tv{10, 0};
        setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
        return true;
    }
    std::string cmd(const std::string& p) {
        std::string f = gdbrsp::frame(p);
        if (::send(fd, f.data(), f.size(), MSG_NOSIGNAL) != (ssize_t)f.size()) return "<send failed>";
        for (;;) {
            if (auto r = rd.next()) return *r;
            char b[4096];
            ssize_t n = recv(fd, b, sizeof b, 0);
            if (n <= 0) return "<closed>";
            rd.buf.append(b, (size_t)n);
        }
    }
    ~Client() {
        if (fd >= 0) close(fd);
    }
};

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
    check(c.cmd("qfThreadInfo").find([&] { char b[16]; snprintf(b, sizeof b, "%x", tid); return std::string(b); }()) != std::string::npos,
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
    snprintf(h, sizeof h, "m%lx,8", (unsigned long)g.data);
    check(gdbrsp::le_from_hex(c.cmd(h)) == n0 && g.data[0] == n0, "gdb: stopped: memory reads back and the counter doesn't move");
    check(c.cmd("m10,8") == "E14", "gdb: reading unmapped memory is an error reply");

    const u64 leaf = (u64)g.code + kLeaf;
    snprintf(h, sizeof h, "Z0,%lx,4", (unsigned long)leaf);
    check(c.cmd(h) == "OK", "gdb: Z0 inserts a breakpoint");
    snprintf(h, sizeof h, "m%lx,4", (unsigned long)leaf);
    check(c.cmd(h) == "00400091", "gdb: memory reads show the original instruction under a breakpoint");
    stop = c.cmd("vCont;c");
    check(stop.rfind("T05", 0) == 0 && stop.find("swbreak") != std::string::npos && tid_of(stop) == tid, "gdb: continue runs to the breakpoint (T05 swbreak)");
    check(reg(c, 32) == leaf, "gdb: pc is at the breakpoint");
    u64 x0 = reg(c, 0);
    check(x0 == g.data[0], "gdb: x0 is the counter passed to the leaf");

    // Step over the breakpoint as gdb does: remove, step this thread, re-insert.
    snprintf(h, sizeof h, "z0,%lx,4", (unsigned long)leaf);
    check(c.cmd(h) == "OK", "gdb: z0 removes the breakpoint");
    snprintf(h, sizeof h, "vCont;s:%x", tid);
    stop = c.cmd(h);
    check(stop.rfind("T05", 0) == 0 && tid_of(stop) == tid, "gdb: vCont;s steps the thread");
    check(reg(c, 32) == leaf + 4 && reg(c, 0) == x0 + 0x10, "gdb: one instruction executed (pc + 4, x0 + 0x10)");
    check(c.cmd("s").rfind("T05", 0) == 0 && reg(c, 32) == leaf + 8, "gdb: 's' steps again (fmov)");
    check(reg(c, 34) == x0 + 0x10, "gdb: v0 (fmov d0, x0) reads back");
    check(c.cmd("P15=efbeadde00000000") == "OK" && reg(c, 21) == 0xdeadbeef, "gdb: P writes a register (x21)");
    snprintf(h, sizeof h, "Z0,%lx,4", (unsigned long)leaf);
    c.cmd(h);
    stop = c.cmd("c");
    check(stop.find("swbreak") != std::string::npos && g.data[0] == x0 + 1, "gdb: 'c' runs one more iteration to the breakpoint");

    // Let the loop end: data[1] = 1 (M), then detach.
    snprintf(h, sizeof h, "M%lx,8:0100000000000000", (unsigned long)(g.data + 1));
    check(c.cmd(h) == "OK" && g.data[1] == 1, "gdb: M writes guest memory");
    std::string x = "X" + [&] { char b[40]; snprintf(b, sizeof b, "%lx,8:", (unsigned long)(g.data + 3)); return std::string(b); }() + std::string("\x24\x23\x7d\x2a\x01\x02\x03\x04", 8);  // frame() escapes $ # } *
    check(c.cmd(x) == "OK" && g.data[3] == 0x040302012a7d2324ull, "gdb: X writes binary (escaped) data");
    std::string mon;
    gdbrsp::from_hex(c.cmd("qRcmd," + gdbrsp::to_hex(std::string("threads"))).substr(1), mon);
    check(mon.find("parked") != std::string::npos, "gdb: monitor threads");
    check(c.cmd("D") == "OK", "gdb: detach");
    check(wait_for([&] { return g.done.load(); }), "gdb: after detach the breakpoint is gone and the guest runs to its end");
    if (g.th.joinable()) g.th.join();
    check(g.data[2] == g.data[0] + 0x10 && g.code[kLeaf / 4] == 0x91004000, "gdb: the guest's results are consistent; the code is restored");
    gdb_shutdown();
    unmap_guest_code(g.code, 4096);
}

int run_gdb_demo(const char* addr, bool fault) {
    std::string err;
    if (!gdb_listen(addr, &err)) {
        fprintf(stderr, "%s\n", err.c_str());
        return 2;
    }
    Guest g;
    g.start(fault);
    while (g.data[0] < 1000) std::this_thread::sleep_for(std::chrono::milliseconds(1));  // the loop is running
    // For the client: where the loop's code and data are (control/tests/test_gdbclient.py).
    printf("gdb-demo port %d code 0x%lx data 0x%lx leaf 0x%lx\n", gdb_port(), (unsigned long)g.code, (unsigned long)g.data,
           (unsigned long)((u64)g.code + kLeaf));
    fflush(stdout);
    g.th.join();
    printf("gdb-demo done: counter %lu\n", (unsigned long)g.data[0]);
    fflush(stdout);
    gdb_shutdown();
    return 0;
}

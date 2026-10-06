// The GDB remote stub for the guest (core/gdbstub.h; runtime/README.md "Debugging the guest with gdb").
//
// Threads: one server thread accepts one debugger connection at a time and runs the protocol. Guest
// threads never block on the socket: they park in gdb_park() (called by core/cpu.cpp's run_jit when
// their JIT returns with kGdbHalt, or when they enter the JIT while the guest is stopped) and wait for
// the server's resume / step order. Only the owning thread runs its JIT (Run, Step); the server
// reads and writes a parked thread's registers directly (they are plain memory while the JIT is
// stopped) and guest memory through process_vm_readv / writev (Linux) or Read/WriteProcessMemory
// (Windows) on its own process: an unmapped address is an error reply, not a crash.
#include "core/gdbstub.h"

#include <soa/sock.h>  // (Winsock on Windows: first, before <windows.h>)

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/uio.h>
#include <unistd.h>
#endif

#include <cxxabi.h>

#include <atomic>
#include <chrono>
#include <cinttypes>
#include <condition_variable>
#include <cstdlib>
#include <cstring>
#include <map>
#include <mutex>
#include <optional>
#include <set>
#include <thread>

#include "core/gdb_protocol.h"
#include "core/crash.h"
#include "core/thread_record.h"
#include "core/loader.h"
#include "core/log.h"
#include "dynarmic/interface/A64/a64.h"

namespace soa {

bool g_gdb_enabled = false;

namespace {

using namespace gdbrsp;
using HR = Dynarmic::HaltReason;

constexpr u32 kBrk = 0xd4200000u | (0x7d0u << 5);  // BRK #0x7d0: the stub's breakpoint instruction
constexpr u64 kTbiMask = 0x00ffffffffffffffull;    // data addresses ignore the top byte (cpu.cpp)

enum class Act { None, Cont, Step };
struct ThreadCtl {
    Cpu* cpu = nullptr;  // the level that parked
    bool parked = false;  // waiting in gdb_park or gdb_call_native: registers readable and writable
    bool faulted = false;  // waiting in gdb_fault (a signal handler): registers readable, can't run
    Act act = Act::None;
};
struct Stop {
    int tid = 0;
    int sig = kGdbSigTrap;
    bool swbreak = false;
};

std::mutex g_m;
std::condition_variable g_cv_thr;  // guest threads wait here (parked)
std::condition_variable g_cv_srv;  // the server waits here (stops, parks)
std::atomic<bool> g_stopped{false};
bool g_attached = false;
std::map<int, ThreadCtl> g_ctl;  // by tid
std::optional<Stop> g_pending;   // a stop not yet reported
std::map<u64, u32> g_bps;        // inserted breakpoints: address -> original instruction
std::set<u64> g_native_bps;      // breakpoints on natives' hooked entries (no BRK: see gdb_call_native)
std::atomic<int> g_native_bp_count{0};
int g_listen_fd = -1;
std::atomic<int> g_port{0};
std::atomic<bool> g_shutdown{false};
std::thread g_server;

thread_local int t_tid = 0;
int my_tid() {  // the id guest_threads() reports (ThreadState::tid): gettid(), GetCurrentThreadId on Windows
    if (!t_tid) t_tid = (int)gettid();
    return t_tid;
}

// With g_m held: stop the world (every guest CPU halts at its next block boundary) and record
// why, unless an earlier stop is still unreported.
void stop_world_locked(const Stop& s) {
    if (!g_pending) g_pending = s;
    g_stopped = true;
    halt_all_guest_cpus(kGdbHalt);
    g_cv_srv.notify_all();
}

// ---- guest memory ----

// One copy within this process, failing (not faulting) on unmapped memory: the number of bytes
// copied, -1 when none could be.
ssize_t copy_mem(void* dst, const void* src, size_t n, bool to_guest) {
#ifdef _WIN32
    SIZE_T done = 0;
    BOOL ok = to_guest ? WriteProcessMemory(GetCurrentProcess(), dst, src, n, &done) : ReadProcessMemory(GetCurrentProcess(), src, dst, n, &done);
    return ok ? (ssize_t)done : -1;
#else
    iovec l{to_guest ? (void*)src : dst, n}, r{to_guest ? dst : (void*)src, n};
    return to_guest ? process_vm_writev(getpid(), &l, 1, &r, 1, 0) : process_vm_readv(getpid(), &l, 1, &r, 1, 0);
#endif
}

size_t read_mem(u64 addr, void* out, size_t n) {
    addr &= kTbiMask;
    ssize_t got = copy_mem(out, (const void*)addr, n, false);
    if (got < 0) {  // a range crossing into an unmapped page: byte by byte up to it
        size_t k = 0;
        for (; k < n; k++)
            if (copy_mem((char*)out + k, (const void*)(addr + k), 1, false) != 1) break;
        return k;
    }
    return (size_t)got;
}

bool write_mem(u64 addr, const void* in, size_t n) {
    addr &= kTbiMask;
    return copy_mem((void*)addr, in, n, true) == (ssize_t)n;
}

// Memory as the program has it: the breakpoints' original instructions shown instead of the BRKs.
std::string read_program_mem(u64 addr, size_t n) {
    std::string out(n, '\0');
    out.resize(read_mem(addr, out.data(), n));
    std::lock_guard lk(g_m);
    for (auto& [a, orig] : g_bps)
        for (int k = 0; k < 4; k++)
            if (a + k >= (addr & kTbiMask) && a + k < (addr & kTbiMask) + out.size()) out[a + k - (addr & kTbiMask)] = (char)(orig >> (8 * k));
    return out;
}

// ---- breakpoints (g_m held) ----

bool insert_bp_locked(u64 addr) {
    if (g_bps.count(addr) || g_native_bps.count(addr)) return true;
    if (addr & 3) return false;
    if (hooked_host_fn(addr)) {  // a native: its first word is the hook's SVC; gdb_call_native stops there
        g_native_bps.insert(addr);
        g_native_bp_count.store((int)g_native_bps.size(), std::memory_order_release);
        return true;
    }
    u32 orig;
    if (read_mem(addr, &orig, 4) != 4) return false;
    if (!write_mem(addr, &kBrk, 4)) return false;
    g_bps[addr] = orig;
    invalidate_guest_code(addr, 4);
    return true;
}

bool remove_bp_locked(u64 addr) {
    if (g_native_bps.erase(addr)) {
        g_native_bp_count.store((int)g_native_bps.size(), std::memory_order_release);
        return true;
    }
    auto it = g_bps.find(addr);
    if (it == g_bps.end()) return true;
    write_mem(addr, &it->second, 4);
    g_bps.erase(it);
    invalidate_guest_code(addr, 4);
    return true;
}

void remove_all_bps_locked() {
    while (!g_bps.empty()) remove_bp_locked(g_bps.begin()->first);
    g_native_bps.clear();
    g_native_bp_count.store(0, std::memory_order_release);
}

// ---- registers ----

constexpr int kRegCount = 68;  // x0-x30, sp, pc, cpsr, v0-v31, fpsr, fpcr
int reg_size(int n) { return n < 33 ? 8 : n == 33 ? 4 : n < 66 ? 16 : 4; }

std::string read_reg(Cpu& c, int n) {
    if (n < 31) return le_hex(c.x(n), 8);
    if (n == 31) return le_hex(c.sp(), 8);
    if (n == 32) return le_hex(c.pc(), 8);
    if (n == 33) return le_hex(c.jit()->GetPstate(), 4);
    if (n < 66) {
        V128 v = c.v(n - 34);
        return le_hex(v.lo, 8) + le_hex(v.hi, 8);
    }
    if (n == 66) return le_hex(c.jit()->GetFpsr(), 4);
    if (n == 67) return le_hex(c.jit()->GetFpcr(), 4);
    return "";
}

bool write_reg(Cpu& c, int n, const std::string& hex) {
    if (n < 0 || n >= kRegCount || (int)hex.size() != 2 * reg_size(n)) return false;
    if (n < 33) {
        c.xregs()[n] = le_from_hex(hex);  // x0-x30, sp (31), pc (32)
    } else if (n == 33) {
        c.jit()->SetPstate((u32)le_from_hex(hex));
    } else if (n < 66) {
        c.set_v(n - 34, {le_from_hex(hex.substr(0, 16)), le_from_hex(hex.substr(16))});
    } else if (n == 66) {
        c.jit()->SetFpsr((u32)le_from_hex(hex));
    } else {
        c.jit()->SetFpcr((u32)le_from_hex(hex));
    }
    return true;
}

// ---- target description ----

std::string target_xml() {
    std::string x =
        "<?xml version=\"1.0\"?>\n<!DOCTYPE target SYSTEM \"gdb-target.dtd\">\n<target>\n"
        "<architecture>aarch64</architecture>\n<osabi>none</osabi>\n"
        "<feature name=\"org.gnu.gdb.aarch64.core\">\n";
    for (int i = 0; i < 31; i++) x += "<reg name=\"x" + std::to_string(i) + "\" bitsize=\"64\"" + (i == 0 ? " regnum=\"0\"" : "") + "/>\n";
    x += "<reg name=\"sp\" bitsize=\"64\" type=\"data_ptr\"/>\n<reg name=\"pc\" bitsize=\"64\" type=\"code_ptr\"/>\n"
         "<reg name=\"cpsr\" bitsize=\"32\" type=\"int\"/>\n</feature>\n"
         "<feature name=\"org.gnu.gdb.aarch64.fpu\">\n"
         "<vector id=\"v2d\" type=\"ieee_double\" count=\"2\"/><vector id=\"v2u\" type=\"uint64\" count=\"2\"/>"
         "<vector id=\"v2i\" type=\"int64\" count=\"2\"/><vector id=\"v4f\" type=\"ieee_single\" count=\"4\"/>"
         "<vector id=\"v4u\" type=\"uint32\" count=\"4\"/><vector id=\"v4i\" type=\"int32\" count=\"4\"/>"
         "<vector id=\"v8f\" type=\"ieee_half\" count=\"8\"/><vector id=\"v8u\" type=\"uint16\" count=\"8\"/>"
         "<vector id=\"v8i\" type=\"int16\" count=\"8\"/><vector id=\"v16u\" type=\"uint8\" count=\"16\"/>"
         "<vector id=\"v16i\" type=\"int8\" count=\"16\"/><vector id=\"v1u\" type=\"uint128\" count=\"1\"/>"
         "<vector id=\"v1i\" type=\"int128\" count=\"1\"/>\n"
         "<union id=\"vnd\"><field name=\"f\" type=\"v2d\"/><field name=\"u\" type=\"v2u\"/><field name=\"s\" type=\"v2i\"/></union>\n"
         "<union id=\"vns\"><field name=\"f\" type=\"v4f\"/><field name=\"u\" type=\"v4u\"/><field name=\"s\" type=\"v4i\"/></union>\n"
         "<union id=\"vnh\"><field name=\"f\" type=\"v8f\"/><field name=\"u\" type=\"v8u\"/><field name=\"s\" type=\"v8i\"/></union>\n"
         "<union id=\"vnb\"><field name=\"u\" type=\"v16u\"/><field name=\"s\" type=\"v16i\"/></union>\n"
         "<union id=\"vnq\"><field name=\"u\" type=\"v1u\"/><field name=\"s\" type=\"v1i\"/></union>\n"
         "<union id=\"aarch64v\"><field name=\"d\" type=\"vnd\"/><field name=\"s\" type=\"vns\"/><field name=\"h\" type=\"vnh\"/>"
         "<field name=\"b\" type=\"vnb\"/><field name=\"q\" type=\"vnq\"/></union>\n";
    for (int i = 0; i < 32; i++) x += "<reg name=\"v" + std::to_string(i) + "\" bitsize=\"128\" type=\"aarch64v\"" + (i == 0 ? " regnum=\"34\"" : "") + "/>\n";
    x += "<reg name=\"fpsr\" bitsize=\"32\"/>\n<reg name=\"fpcr\" bitsize=\"32\"/>\n</feature>\n</target>\n";
    return x;
}

// The loaded images for gdb's solib-target (qXfer:libraries:read): each image at its load base
// (its first PT_LOAD has vaddr 0).
std::string libraries_xml() {
    std::string x = "<library-list>\n";
    for (LoadedLib* l : loaded_libs()) {
        if (!l || l->path.empty()) continue;
        char b[32];
        snprintf(b, sizeof b, "0x%" PRIx64, (u64)l->base);
        x += "<library name=\"" + l->path + "\"><segment address=\"" + b + "\"/></library>\n";
    }
    return x + "</library-list>\n";
}

std::string xfer_slice(const std::string& doc, const std::string& args) {
    size_t i = 0;
    uint64_t off = 0, len = 0;
    if (!parse_hex(args, i, off) || i >= args.size() || args[i++] != ',' || !parse_hex(args, i, len)) return "E01";
    if (off >= doc.size()) return "l";
    std::string part = doc.substr(off, len);
    return (off + part.size() >= doc.size() ? "l" : "m") + part;
}

// ---- the session ----

class Session {
public:
    explicit Session(int fd) : fd_(fd) {}

    void run() {
        {
            std::lock_guard lk(g_m);
            g_attached = true;
        }
        LOGI("gdb", "debugger attached");
        char b[4096];
        for (;;) {
            std::optional<std::string> p;
            bool bad = false;
            while (!(p = rd_.next(&bad))) {
                ssize_t n = sock::recv(fd_, b, sizeof b);
                if (n <= 0 || g_shutdown) return finish();
                rd_.buf.append(b, (size_t)n);
            }
            if (bad) {
                raw("-");
                continue;
            }
            if (!noack_) raw("+");
            if (*p == "\x03") {  // interrupt while stopped: report the stop again
                ensure_stopped(kGdbSigInt);
                send(stop_reply());
                continue;
            }
            if (!handle(*p)) return finish();
        }
    }

private:
    int fd_;
    Reader rd_;
    bool noack_ = false;
    int cur_g_ = 0;     // Hg thread (registers), 0 = the stop's thread
    int cur_c_ = 0;     // Hc thread (s / c)
    Stop last_{};       // the last reported stop

    void raw(const std::string& s) {
        size_t off = 0;
        while (off < s.size()) {
            ssize_t n = sock::send(fd_, s.data() + off, s.size() - off);
            if (n <= 0) return;
            off += (size_t)n;
        }
    }
    void send(const std::string& data) { raw(frame(data)); }

    void finish() {
        detach();
        LOGI("gdb", "debugger detached");
    }

    // Removes every breakpoint and lets every thread run.
    void detach() {
        std::lock_guard lk(g_m);
        remove_all_bps_locked();
        g_attached = false;
        g_pending.reset();
        g_stopped = false;
        for (auto& [tid, t] : g_ctl) t.act = Act::None;
        g_cv_thr.notify_all();
    }

    // Waits until no thread is running JIT code without having parked (threads in host code count as
    // stopped), at most 3 s.
    void wait_quiescent() {
        auto until = std::chrono::steady_clock::now() + std::chrono::seconds(3);
        for (;;) {
            bool busy = false;
            {
                std::unique_lock lk(g_m);
                for (auto& v : guest_threads()) {
                    auto it = g_ctl.find(v.tid);
                    bool parked = it != g_ctl.end() && (it->second.parked || it->second.faulted);
                    if (v.in_jit && !parked) busy = true;
                }
                if (!busy) return;
                g_cv_srv.wait_for(lk, std::chrono::milliseconds(5));
            }
            if (std::chrono::steady_clock::now() > until) {
                LOGW("gdb", "some guest threads didn't stop within 3 s; their registers may be stale");
                return;
            }
        }
    }

    void ensure_stopped(int sig) {
        {
            std::lock_guard lk(g_m);
            if (!g_stopped) {
                int tid = 0;  // report a thread that is running guest code, else the first
                for (auto& v : guest_threads())
                    if (!tid || v.in_jit) {
                        tid = v.tid;
                        if (v.in_jit) break;
                    }
                stop_world_locked({tid, sig, false});
            }
        }
        wait_quiescent();
        std::lock_guard lk(g_m);
        if (g_pending) {
            last_ = *g_pending;
            g_pending.reset();
        }
        if (!last_.tid) {
            auto ts = guest_threads();
            if (!ts.empty()) last_.tid = ts[0].tid;
        }
    }

    std::string stop_reply() {
        char b[64];
        snprintf(b, sizeof b, "T%02xthread:%x;%s", last_.sig & 0xff, last_.tid, last_.swbreak ? "swbreak:;" : "");
        return b;
    }

    // The CPU whose registers thread `tid` shows: the level that parked (or faulted), else its
    // innermost level in use.
    Cpu* cpu_of(int tid, bool* runnable = nullptr) {
        if (tid <= 0) tid = last_.tid;
        std::lock_guard lk(g_m);
        auto it = g_ctl.find(tid);
        if (it != g_ctl.end() && (it->second.parked || it->second.faulted) && it->second.cpu) {
            if (runnable) *runnable = it->second.parked;
            return it->second.cpu;
        }
        if (runnable) *runnable = false;
        for (auto& v : guest_threads())
            if (v.tid == tid) return v.cpu;
        return nullptr;
    }

    // Resumes per the actions and waits for the next stop (a breakpoint, a step's end, a fault, or
    // ^C from the debugger), which it reports.
    bool resume(const std::vector<VContAction>& acts) {
        bool step_unparked = false;
        int unparked_tid = 0;
        {
            std::lock_guard lk(g_m);
            const VContAction* def = nullptr;
            for (auto& a : acts)
                if (a.tid == -1) def = &a;
            for (auto& [tid, t] : g_ctl) t.act = Act::None;
            for (auto& a : acts) {
                if (a.tid == -1 || a.op == 't') continue;
                auto it = g_ctl.find(a.tid);
                if (it == g_ctl.end() || !it->second.parked) {
                    if (a.op == 's') step_unparked = true, unparked_tid = a.tid;
                    continue;
                }
                it->second.act = a.op == 's' ? Act::Step : Act::Cont;
            }
            if (def && def->op == 's') {  // "step every thread": step the current one, continue the rest
                int tid = cur_c_ > 0 ? cur_c_ : last_.tid;
                auto it = g_ctl.find(tid);
                if (it != g_ctl.end() && it->second.parked) it->second.act = Act::Step;
                else step_unparked = true, unparked_tid = tid;
            }
            g_pending.reset();
            if (step_unparked) {
                // A thread in host code can't execute one instruction: report it stopped where it is.
                g_pending = Stop{unparked_tid, kGdbSigTrap, false};
            } else {
                if (def) g_stopped = false;  // the default action resumes every other thread
                g_cv_thr.notify_all();
            }
        }
        // Wait for the next stop; ^C on the socket interrupts.
        char b[512];
        for (;;) {
            {
                std::unique_lock lk(g_m);
                if (g_pending) break;
                g_cv_srv.wait_for(lk, std::chrono::milliseconds(20));
                if (g_pending) break;
            }
            sock::PollFd pf{fd_, POLLIN, 0};
            if (sock::poll(&pf, 1, 0) > 0) {
                ssize_t n = sock::recv(fd_, b, sizeof b);
                if (n <= 0) return false;
                rd_.buf.append(b, (size_t)n);
                if (rd_.buf.find('\x03') != std::string::npos) {
                    rd_.buf.erase(rd_.buf.find('\x03'), 1);
                    std::lock_guard lk(g_m);
                    int tid = 0;  // report a thread that was running guest code, else the first
                    for (auto& v : guest_threads())
                        if (!tid || (v.in_jit && !g_ctl[v.tid].parked)) tid = v.tid;
                    stop_world_locked({tid, kGdbSigInt, false});
                }
            }
            if (g_shutdown) return false;
        }
        ensure_stopped(kGdbSigTrap);
        send(stop_reply());
        return true;
    }

    std::string monitor(const std::string& cmd) {
        std::string out;
        if (cmd == "base" || cmd == "libs") {
            for (LoadedLib* l : loaded_libs()) {
                char b[64];
                snprintf(b, sizeof b, "0x%" PRIx64, (u64)l->base);
                out += std::string(b) + " " + l->path + "\n";
            }
            if (LoadedLib* m = main_lib()) {
                char b[64];
                snprintf(b, sizeof b, "0x%" PRIx64, (u64)m->base);
                out += "symbols: add-symbol-file work/libSOA-3.7.0.so -o " + std::string(b) + "\n";
            }
        } else if (cmd == "threads") {
            std::lock_guard lk(g_m);
            for (auto& v : guest_threads()) {
                auto it = g_ctl.find(v.tid);
                const char* st = it != g_ctl.end() && it->second.parked ? "parked" : it != g_ctl.end() && it->second.faulted ? "faulted" : v.in_jit ? "running" : "in host code";
                char b[64];
                snprintf(b, sizeof b, "%d (0x%x) %s, entry ", v.tid, v.tid, st);
                out += b + describe_guest_addr(v.entry) + ", pc " + describe_guest_addr(v.cpu ? v.cpu->pc() : 0) + "\n";
            }
        } else if (cmd == "natives" || cmd.rfind("natives ", 0) == 0) {
            out = natives(cmd.size() > 8 ? cmd.substr(8) : "");
        } else {
            out = "monitor commands: base (the loaded images and their load addresses), threads, natives [TEXT] (the guest\n"
                  "functions replaced by native code: guest address, symbol, demangled, the C++ native, its host address;\n"
                  "TEXT filters), help\n";
        }
        return out;
    }

    // `monitor natives [TEXT]`: one line per guest function that is now a native (hooked), tab-separated:
    // guest address, guest symbol, demangled, the C++ that replaces it, the host function's address.
    static std::string natives(const std::string& filter) {
        std::string out;
        size_t n = 0;
        for (const HookedFunction& h : hooked_functions()) {
            std::string sym = h.name ? h.name : "", dem = sym;
            int st = 0;
            if (char* d = sym.rfind("_Z", 0) == 0 ? abi::__cxa_demangle(sym.c_str(), nullptr, nullptr, &st) : nullptr) {
                dem = d;
                free(d);
            }
            std::string host = h.host_name ? h.host_name : "?";
            if (!filter.empty() && sym.find(filter) == std::string::npos && dem.find(filter) == std::string::npos &&
                host.find(filter) == std::string::npos)
                continue;
            char a[40], f[40];
            snprintf(a, sizeof a, "0x%" PRIx64, h.guest_addr);
            snprintf(f, sizeof f, "0x%" PRIx64, (u64)(uintptr_t)h.fn);
            out += std::string(a) + "\t" + sym + "\t" + dem + "\t" + host + "\t" + f + "\n";
            n++;
        }
        return "# " + std::to_string(n) + " natives: guest address, guest symbol, demangled, native (C++), host function\n" + out;
    }

    // One packet. False: close the connection.
    bool handle(const std::string& p) {
        char c = p.empty() ? 0 : p[0];
        if (p.rfind("qSupported", 0) == 0) {
            send("PacketSize=4000;qXfer:features:read+;qXfer:libraries:read+;QStartNoAckMode+;vContSupported+;swbreak+");
        } else if (p == "QStartNoAckMode") {
            send("OK");
            noack_ = true;
        } else if (p.rfind("qXfer:features:read:target.xml:", 0) == 0) {
            send(xfer_slice(target_xml(), p.substr(31)));
        } else if (p.rfind("qXfer:libraries:read::", 0) == 0) {
            send(xfer_slice(libraries_xml(), p.substr(22)));
        } else if (p == "?") {
            ensure_stopped(kGdbSigTrap);
            send(stop_reply());
        } else if (p == "qAttached") {
            send("1");
        } else if (p == "qC") {
            char b[32];
            snprintf(b, sizeof b, "QC%x", cur_g_ > 0 ? cur_g_ : last_.tid);
            send(b);
        } else if (p == "qfThreadInfo") {
            std::string r = "m";
            for (auto& v : guest_threads()) {
                char b[16];
                snprintf(b, sizeof b, "%s%x", r.size() > 1 ? "," : "", v.tid);
                r += b;
            }
            send(r.size() > 1 ? r : "l");
        } else if (p == "qsThreadInfo") {
            send("l");
        } else if (p.rfind("qThreadExtraInfo,", 0) == 0) {
            size_t i = 17;
            uint64_t tid = 0;
            parse_hex(p, i, tid);
            std::string s;
            for (auto& v : guest_threads())
                if (v.tid == (int)tid) s = "entry " + describe_guest_addr(v.entry);
            send(to_hex(s));
        } else if (p.rfind("qRcmd,", 0) == 0) {
            std::string cmd;
            from_hex(p.substr(6), cmd);
            std::string text = monitor(cmd);
            for (size_t off = 0; off < text.size(); off += 1024) send("O" + to_hex(text.substr(off, 1024)));  // console output, in pieces
            send("OK");
        } else if (c == 'H' && p.size() >= 2) {
            size_t i = 2;
            uint64_t t = 0;
            int tid = p.compare(2, 2, "-1") == 0 ? -1 : (parse_hex(p, i, t) ? (int)t : 0);
            (p[1] == 'g' ? cur_g_ : cur_c_) = tid;
            send("OK");
        } else if (c == 'T') {
            size_t i = 1;
            uint64_t t = 0;
            parse_hex(p, i, t);
            bool alive = false;
            for (auto& v : guest_threads()) alive |= v.tid == (int)t;
            send(alive ? "OK" : "E01");
        } else if (c == 'g') {
            Cpu* cpu = cpu_of(cur_g_);
            if (!cpu) return send("E01"), true;
            std::string r;
            for (int n = 0; n < kRegCount; n++) r += read_reg(*cpu, n);
            send(r);
        } else if (c == 'G') {
            bool runnable = false;
            Cpu* cpu = cpu_of(cur_g_, &runnable);
            std::string h = p.substr(1);
            if (!cpu || !runnable) return send("E01"), true;
            size_t off = 0;
            for (int n = 0; n < kRegCount && off + 2 * reg_size(n) <= h.size(); n++) {
                write_reg(*cpu, n, h.substr(off, 2 * reg_size(n)));
                off += 2 * reg_size(n);
            }
            send("OK");
        } else if (c == 'p') {
            size_t i = 1;
            uint64_t n = 0;
            Cpu* cpu = cpu_of(cur_g_);
            if (!parse_hex(p, i, n) || n >= kRegCount || !cpu) return send("E01"), true;
            send(read_reg(*cpu, (int)n));
        } else if (c == 'P') {
            size_t i = 1;
            uint64_t n = 0;
            bool runnable = false;
            Cpu* cpu = cpu_of(cur_g_, &runnable);
            if (!parse_hex(p, i, n) || i >= p.size() || p[i] != '=' || !cpu || !runnable) return send("E01"), true;
            send(write_reg(*cpu, (int)n, p.substr(i + 1)) ? "OK" : "E01");
        } else if (c == 'm') {
            size_t i = 1;
            uint64_t a = 0, n = 0;
            if (!parse_hex(p, i, a) || i >= p.size() || p[i++] != ',' || !parse_hex(p, i, n)) return send("E01"), true;
            std::string m = read_program_mem(a, std::min<uint64_t>(n, 0x4000));
            send(m.empty() && n ? "E14" : to_hex(m));
        } else if (c == 'M' || c == 'X') {
            size_t i = 1;
            uint64_t a = 0, n = 0;
            if (!parse_hex(p, i, a) || i >= p.size() || p[i++] != ',' || !parse_hex(p, i, n) || i >= p.size() || p[i++] != ':')
                return send("E01"), true;
            std::string data;
            if (c == 'M') {
                if (!from_hex(p.substr(i), data)) return send("E01"), true;
            } else {
                data = p.substr(i);  // already unescaped by the reader
            }
            if (data.size() != n) return send("E01"), true;
            bool ok = n == 0 || write_mem(a, data.data(), n);
            if (ok && n) invalidate_guest_code(a & kTbiMask, n);
            send(ok ? "OK" : "E14");
        } else if ((c == 'Z' || c == 'z') && p.size() > 3 && (p[1] == '0' || p[1] == '1')) {
            size_t i = 3;
            uint64_t a = 0;
            if (!parse_hex(p, i, a)) return send("E01"), true;
            std::lock_guard lk(g_m);
            send((c == 'Z' ? insert_bp_locked(a) : remove_bp_locked(a)) ? "OK" : "E01");
        } else if (c == 'Z' || c == 'z') {
            send("");  // watchpoints: not supported
        } else if (p == "vCont?") {
            send("vCont;c;C;s;S;t");
        } else if (p.rfind("vCont;", 0) == 0) {
            std::vector<VContAction> acts;
            if (!parse_vcont(p, acts)) return send("E01"), true;
            return resume(acts);
        } else if (c == 'c' || c == 'C') {
            return resume({{'c', -1}});
        } else if (c == 's' || c == 'S') {
            int tid = cur_c_ > 0 ? cur_c_ : last_.tid;
            return resume({{'s', tid}});
        } else if (c == 'D') {
            send("OK");
            return false;
        } else if (c == 'k') {
            return false;  // "kill": detach; the client keeps running
        } else {
            send("");
        }
        return true;
    }
};

void server_main() {
    ThreadScope thread_scope("gdb-server");  // crash reports; per-thread state ends with it (core/thread_record.h)
    while (!g_shutdown) {
        int fd = sock::accept(g_listen_fd);  // (gdb_shutdown closes the listener: accept fails)
        if (fd < 0) {
            if (g_shutdown) break;
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            continue;
        }
        Session(fd).run();
        sock::close(fd);
    }
}

// With g_m held: wait as a parked thread (registers readable and writable) until the debugger
// resumes this thread (Act::Cont, or every thread) or steps it (returns true).
bool wait_parked_locked(std::unique_lock<std::mutex>& lk, ThreadCtl& t) {
    bool step = false;
    for (;;) {
        if (t.act == Act::Step) {
            step = true;
            break;
        }
        if (t.act == Act::Cont || !g_stopped) break;
        t.parked = true;
        g_cv_srv.notify_all();
        g_cv_thr.wait(lk);
    }
    t.parked = false;
    t.act = Act::None;
    return step;
}

}  // namespace

bool gdb_stopped() { return g_stopped.load(std::memory_order_acquire); }

void gdb_park(Cpu& c) {
    std::unique_lock lk(g_m);
    const int tid = my_tid();
    ThreadCtl& t = g_ctl[tid];
    t.cpu = &c;
    for (;;) {
        if (t.act == Act::Step) {
            t.act = Act::None;
            c.jit()->ClearHalt((HR)kGdbHalt);
            lk.unlock();
            c.jit()->Step();
            lk.lock();
            stop_world_locked({tid, kGdbSigTrap, false});
            continue;
        }
        if (t.act == Act::Cont || !g_stopped) break;
        t.parked = true;
        g_cv_srv.notify_all();
        g_cv_thr.wait(lk);
    }
    t.parked = false;
    t.act = Act::None;
    c.jit()->ClearHalt((HR)kGdbHalt);
}

bool gdb_breakpoint_hit(Cpu& c, u64 pc) {
    std::lock_guard lk(g_m);
    if (!g_bps.count(pc)) return false;
    stop_world_locked({my_tid(), kGdbSigTrap, true});
    return true;
}

bool gdb_native_breakpoints() { return g_native_bp_count.load(std::memory_order_acquire) != 0; }

void gdb_call_native(Cpu& c, u64 hook, HostFn fn, bool in_jit) {
    bool step = false;
    {
        std::unique_lock lk(g_m);
        if (g_attached && g_native_bps.count(hook)) {
            const int tid = my_tid();
            ThreadCtl& t = g_ctl[tid];
            t.cpu = &c;
            const u64 ret_pc = c.pc();  // hook + 4: the hook's RET
            c.xregs()[32] = hook;       // (the pc) reported where the breakpoint is, the guest's arguments as they are
            stop_world_locked({tid, kGdbSigTrap, true});
            step = wait_parked_locked(lk, t);
            if (c.pc() != hook) return;  // the debugger moved the PC: the native doesn't run; the JIT goes on there
            c.xregs()[32] = ret_pc;
        }
    }
    fn(c);
    if (!step) return;
    // A step from the native's entry: all of it ran; stop at the hook's RET.
    std::unique_lock lk(g_m);
    if (!g_attached) return;
    const int tid = my_tid();
    stop_world_locked({tid, kGdbSigTrap, false});  // (halts this JIT too: it parks in gdb_park on return)
    if (in_jit) return;
    // A direct host call has no JIT to return to: wait here (a further step can't run guest code:
    // reported stopped where it is).
    ThreadCtl& t = g_ctl[tid];
    t.cpu = &c;
    while (wait_parked_locked(lk, t)) stop_world_locked({tid, kGdbSigTrap, false});
}

void gdb_fault(Cpu* c, int gdb_sig) {
    std::unique_lock lk(g_m);
    if (!g_attached) return;
    const int tid = my_tid();
    ThreadCtl& t = g_ctl[tid];
    t.cpu = c;
    t.faulted = true;
    g_pending.reset();
    stop_world_locked({tid, gdb_sig, false});
    LOGE("gdb", "guest fault (signal %d) on thread %d: reported to the debugger; waiting for it to continue or detach", gdb_sig, tid);
    while (g_attached && g_stopped) g_cv_thr.wait(lk);
    t.faulted = false;
}

bool gdb_listen(const std::string& host_port, std::string* err) {
    std::string host, port;
    if (host_port.find_first_not_of("0123456789") == std::string::npos) port = host_port;  // "PORT"
    else if (!sock::split_host_port(host_port, &host, &port)) port.clear();
    if (host.empty()) host = "127.0.0.1";
    if (port.empty() || port.find_first_not_of("0123456789") != std::string::npos || port.size() > 5 || atoi(port.c_str()) > 65535) {
        if (err) *err = "--gdb: expected HOST:PORT, [IPV6]:PORT, :PORT or PORT, got \"" + host_port + "\"";
        return false;
    }
    addrinfo hints{}, *res = nullptr;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    sock::startup();
    if (getaddrinfo(host.c_str(), port.c_str(), &hints, &res) != 0 || !res) {
        if (err) *err = "--gdb: can't resolve " + host;
        return false;
    }
    int fd = sock::tcp_socket(false, res->ai_family);
    if (fd >= 0) sock::set_reuse_addr(fd);
    if (fd < 0 || bind(fd, res->ai_addr, (int)res->ai_addrlen) != 0 || listen(fd, 1) != 0) {
        if (err) *err = "--gdb: can't listen on " + host_port + ": " + sock::last_error();
        if (fd >= 0) sock::close(fd);
        freeaddrinfo(res);
        return false;
    }
    freeaddrinfo(res);
    sockaddr_storage ss{};
    socklen_t sl = sizeof ss;
    getsockname(fd, (sockaddr*)&ss, &sl);
    g_port = ntohs(ss.ss_family == AF_INET6 ? ((sockaddr_in6*)&ss)->sin6_port : ((sockaddr_in*)&ss)->sin_port);
    g_listen_fd = fd;
    g_gdb_enabled = true;
    g_shutdown = false;
    g_server = std::thread(server_main);
    // (soadrive reads the port from this line: control/soadrive/gdb.py listen_port)
    LOGI("gdb", "GDB stub listening on %s (gdb-multiarch -x control/gdbinit-soa, or control/gdbclient.py)",
         sock::join_host_port(host, g_port.load()).c_str());
    return true;
}

int gdb_port() { return g_port; }

void gdb_shutdown() {
    if (g_listen_fd < 0) return;
    g_shutdown = true;
#ifndef _WIN32
    shutdown(g_listen_fd, SHUT_RDWR);  // wakes accept() (closing the socket does on Windows)
#endif
    sock::close(g_listen_fd);
    g_listen_fd = -1;
    if (g_server.joinable()) g_server.join();
    std::lock_guard lk(g_m);
    remove_all_bps_locked();
    g_attached = false;
    g_stopped = false;
    g_pending.reset();
    g_cv_thr.notify_all();
}

}  // namespace soa

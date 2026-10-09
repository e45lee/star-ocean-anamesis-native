// Crash reports (core/crash.h; runtime/README.md "Crash reports"), end to end: soaruntime_tests
// runs itself as a child with `--crash-demo KIND`, which starts a guest thread through the HLE'd
// pthread_create (the game's path: thread_body, its 256 KiB host stack) and crashes it, and checks
// what the child logged:
//   overflow  the thread names itself (prctl(PR_SET_NAME) through the HLE'd syscall, as a guest
//             would) and then recurses on its host stack until it runs out: the report must say
//             "stack overflow on thread overflower" (on Linux it runs on the thread's alternate
//             signal stack, reached through dynarmic's SIGSEGV handler; on Windows on the stack
//             SetThreadStackGuarantee kept).
//   null      guest code loads from address 0x10: the usual report (host signal / exception, the
//             guest pc) and no overflow line.
// Both must end the child with a failure status.
#include "crash_test.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <fcntl.h>
#include <sys/prctl.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <unistd.h>
#endif

#include <cstdio>
#include <cstring>
#include <string>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/hle.h"

using namespace soa;

namespace {

// Recurses with a 4 KiB frame until the host stack runs out (the bound only keeps the compiler
// from calling it infinite).
__attribute__((noinline)) u64 recurse(u64 n) {
    volatile char frame[4096];
    frame[n & 4095] = (char)n;
    if (n > (1ull << 40)) return n;
    return recurse(n + 1) + frame[(n * 7) & 4095];
}

// The overflowing thread's guest entry: an HLE import's thunk.
void overflow_entry(Cpu& c) {
    guest_call(Hle::get().lookup("syscall"), {167, 15 /* PR_SET_NAME */, (u64) "overflower"});
    c.set_x(0, recurse(1));
}

bool g_registered = hle_add_registrar([](Hle& h) { h.fn("soa_crash_test_overflow", overflow_entry); });

const u32 kNullLoad[] = {
    0xf9400000,  // ldr x0, [x0]
    0xd65f03c0,  // ret
};

std::string read_file(const std::string& path) {
    std::string s;
    if (FILE* f = fopen(path.c_str(), "rb")) {
        char buf[4096];
        size_t n;
        while ((n = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, n);
        fclose(f);
    }
    return s;
}

// Runs `soaruntime_tests --crash-demo KIND` with stdout and stderr into a file; returns its output
// and whether it ended with a failure (non-zero exit or a signal).
std::string run_child(const char* kind, bool* failed) {
    *failed = false;
#ifdef _WIN32
    char self[MAX_PATH], tmp[MAX_PATH], path[MAX_PATH];
    GetModuleFileNameA(nullptr, self, sizeof self);
    GetTempPathA(sizeof tmp, tmp);
    GetTempFileNameA(tmp, "soa", 0, path);
    SECURITY_ATTRIBUTES sa{sizeof sa, nullptr, TRUE};
    HANDLE out = CreateFileA(path, GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (out == INVALID_HANDLE_VALUE) return "(no output file)";
    STARTUPINFOA si{};
    si.cb = sizeof si;
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    si.hStdOutput = out;
    si.hStdError = out;
    PROCESS_INFORMATION pi{};
    std::string cmd = std::string("\"") + self + "\" --crash-demo " + kind;
    if (!CreateProcessA(nullptr, cmd.data(), nullptr, nullptr, TRUE, 0, nullptr, nullptr, &si, &pi)) {
        CloseHandle(out);
        return "(CreateProcess failed)";
    }
    CloseHandle(out);
    WaitForSingleObject(pi.hProcess, 60000);
    DWORD code = 0;
    GetExitCodeProcess(pi.hProcess, &code);
    if (code == STILL_ACTIVE) TerminateProcess(pi.hProcess, 1);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    *failed = code != 0;
    std::string s = read_file(path);
    DeleteFileA(path);
    return s;
#else
    char path[] = "/tmp/soaruntime_crash.XXXXXX";
    int fd = mkstemp(path);
    if (fd < 0) return "(mkstemp failed)";
    pid_t pid = fork();
    if (pid == 0) {
        dup2(fd, 1);
        dup2(fd, 2);
        execl("/proc/self/exe", "soaruntime_tests", "--crash-demo", kind, (char*)nullptr);
        _exit(127);
    }
    close(fd);
    int status = 0;
    if (pid > 0) waitpid(pid, &status, 0);
    *failed = pid > 0 && (WIFSIGNALED(status) || (WIFEXITED(status) && WEXITSTATUS(status) != 0));
    std::string s = read_file(path);
    unlink(path);
    return s;
#endif
}

bool has(const std::string& s, const char* what) { return s.find(what) != std::string::npos; }

}  // namespace

int run_crash_demo(const char* kind) {
    // The crash is the point: no core dump or crash dialog.
#ifdef _WIN32
    SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOGPFAULTERRORBOX);
#else
    rlimit rl{0, 0};
    setrlimit(RLIMIT_CORE, &rl);
    prctl(PR_SET_DUMPABLE, 0);
#endif
    setvbuf(stdout, nullptr, _IONBF, 0);
    cpu_global_init();
    hle_init();
    auto& h = Hle::get();
    u64 fn = 0, arg = 0;
    if (!strcmp(kind, "overflow")) {
        fn = h.lookup("soa_crash_test_overflow");
    } else if (!strcmp(kind, "null")) {
        void* code = map_guest_code(4096);
        memcpy(code, kNullLoad, sizeof kNullLoad);
        fn = (u64)code, arg = 0x10;
    } else {
        fprintf(stderr, "--crash-demo overflow|null\n");
        return 2;
    }
    u64 thread = 0;
    printf("crash-demo %s: starting the guest thread\n", kind);
    if (guest_call(h.lookup("pthread_create"), {(u64)&thread, 0, fn, arg}) != 0) return 3;
    guest_call(h.lookup("pthread_join"), {thread, 0});
    printf("crash-demo %s: the thread returned\n", kind);
    return 0;
}

void run_crash_tests(void (*check)(bool ok, const char* what)) {
    check(g_registered, "crash: test import registered");
    bool failed = false;
    std::string log = run_child("overflow", &failed);
    bool ok = failed && has(log, "*** stack overflow on thread overflower (") && has(log, "soa_crash_test_overflow") && has(log, "host backtrace")
#ifndef _WIN32
              && has(log, "Unhandled SIGSEGV")  // dynarmic's handler ran and chained to the runtime's
#endif
              && !has(log, "the thread returned");
    check(ok, "crash: a host stack overflow on a guest thread reports itself (thread name, stack use)");
    if (!ok) fprintf(stderr, "---- child log ----\n%s\n-------------------\n", log.c_str());

    log = run_child("null", &failed);
    ok = failed && has(log, "guest pc (last sync)") && !has(log, "stack overflow") && !has(log, "the thread returned")
#ifdef _WIN32
         && has(log, "*** host exception 0xc0000005")
#else
         && has(log, "*** host signal 11")
#endif
        ;
    check(ok, "crash: a null load on a guest thread gets the usual crash report");
    if (!ok) fprintf(stderr, "---- child log ----\n%s\n-------------------\n", log.c_str());
}

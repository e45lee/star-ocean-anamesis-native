// The guest's errno (core/linux_errno.h): the values the guest reads through __errno are Linux's
// (bionic's) numbers on either host. Also run by build/runtime/soaruntime_tests (and so on Windows
// by win:runtime-tests, where MinGW numbers everything above ERANGE (34) differently).
//
// hle/libc-errno-linux-numbers: imports that fail with an errno above 34 (popen ENOSYS, mbrtowc
// EILSEQ, rmdir of a non-empty directory ENOTEMPTY, an unknown syscall ENOSYS), called the way the
// guest calls them (guest_call on the import's thunk), leave Linux's number where __errno points;
// before code review CR3 (R2) Windows left the CRT's (40, 42, 41). An import that succeeds leaves
// the guest's own value alone.
#include <cstdio>
#include <cstring>
#include <string>

#include "core/cpu.h"
#include "core/hle.h"
#include "core/selftest.h"
#include "core/vfs.h"

namespace soa {
namespace {

RUNTIME_TEST("hle/libc-errno-linux-numbers") {
    Hle& h = Hle::get();
    auto imp = [&](const char* name) {
        u64 a = h.lookup(name);
        if (!a) t.fail("no import %s", name);
        return a;
    };
    const u64 errno_fn = imp("__errno");
    if (!errno_fn) return;
    auto* e = (volatile int*)guest_call(errno_fn, {});
    if (!e) {
        t.fail("__errno returned null");
        return;
    }
    if ((int*)guest_call(errno_fn, {}) != e) t.fail("__errno: a second call on the thread points elsewhere");

    // A successful import keeps the guest's value (the guest sets errno = 0 before strtol, say).
    *e = 1234;
    guest_call(imp("strlen"), {(u64) "abc"});
    t.expect_eq((int)*e, 1234, "errno after a successful strlen");

    *e = 0;
    t.expect_eq(guest_call(imp("popen"), {(u64) "true", (u64) "r"}), (u64)0, "popen result");
    t.expect_eq((int)*e, 38, "errno after popen (ENOSYS)");

    *e = 0;
    u32 wc = 0;
    u8 st[8] = {};
    t.expect_eq(guest_call(imp("mbrtowc"), {(u64)&wc, (u64) "\xff\xfe", 2, (u64)st}), (u64)-1, "mbrtowc result on an invalid byte");
    t.expect_eq((int)*e, 84, "errno after mbrtowc (EILSEQ)");

    *e = 0;
    t.expect_eq((s64)guest_call(imp("syscall"), {99999}), (s64)-1, "syscall(99999) result");
    t.expect_eq((int)*e, 38, "errno after an unknown syscall (ENOSYS)");

    // rmdir of a directory that isn't empty: ENOTEMPTY (39; MinGW 41).
    const std::string dir = "/tmp/soa_errno_test", file = dir + "/f";
    make_dirs(host_path(dir.c_str()));
    if (FILE* f = fopen(host_path(file.c_str()).c_str(), "wb")) fclose(f);
    *e = 0;
    t.expect_eq((s64)guest_call(imp("rmdir"), {(u64)dir.c_str()}), (s64)-1, "rmdir result on a non-empty directory");
    t.expect_eq((int)*e, 39, "errno after rmdir of a non-empty directory (ENOTEMPTY)");
    remove(host_path(file.c_str()).c_str());
    guest_call(imp("rmdir"), {(u64)dir.c_str()});
    *e = 0;
}

}  // namespace
}  // namespace soa

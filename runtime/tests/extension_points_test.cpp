// soaruntime_tests: the runtime's extension points (runtime/README.md), exercised the way a host
// program uses them and checked through the same dispatch the game goes through: HLE imports are
// called as guest code calls them (guest_call on the import's thunk), Java methods through the
// JNIEnv function table (FindClass / Get*MethodID / Call*MethodA). No game library is loaded.
//
// Linked against libsoaruntime alone (whole archive), so building it also proves that the runtime
// needs nothing from port/, server/ or emulator/. Run: build/runtime/soaruntime_tests
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <string>

#include "core/cpu.h"
#include "core/device.h"
#include "core/hle.h"
#include "core/log.h"
#include "core/selftest.h"
#include "core/vfs.h"
#include "crash_test.h"
#include "gdbstub_test.h"
#include "jni/jni_names.h"
#include "jni/jvm.h"

using namespace soa;

namespace {

int g_failures = 0;
void check(bool ok, const char* what) {
    fprintf(stderr, "%s  %s\n", ok ? "ok  " : "FAIL", what);
    if (!ok) g_failures++;
}

// The runtime's own RUNTIME_TESTs that need no game (core/selftest.h), run here too.
struct Ctx : RuntimeTestContext {
    void report_failure(const char* msg) override { fprintf(stderr, "        %s\n", msg); }
};
void run_runtime_tests(const char* prefix) {
    for (auto& r : runtime_tests()) {
        if (strncmp(r.name, prefix, strlen(prefix))) continue;
        Ctx c;
        r.fn(c);
        check(c.failures() == 0, r.name);
    }
}


// ---- HLE ------------------------------------------------------------------------------------
HostFn g_orig_strlen = nullptr;
// Overrides a built-in import and delegates to it: strlen(s) + 1000.
void my_strlen(Cpu& c) {
    g_orig_strlen(c);
    c.set_x(0, c.x(0) + 1000);
}
// Replaces a built-in import outright (as a host would replace getaddrinfo).
void my_getaddrinfo(Cpu& c) { c.set_x(0, 0x5eed); }
// A new import, added from a registrar (before hle_init).
void my_new_import(Cpu& c) { c.set_x(0, c.x(0) * 3); }

bool g_registrar_ran = hle_add_registrar([](Hle& h) {
    h.fn("soa_runtime_test_import", my_new_import);
    g_orig_strlen = h.override_fn("strlen", my_strlen);
});

// ---- JVM ------------------------------------------------------------------------------------
const char* kSoa = "com/square_enix/android_googleplay/StarOceanj/SOAActivity";

bool g_installer_ran = jni::add_class_installer([](jni::Vm& vm) {
    // A new class with a static method.
    vm.define_class("soa/test/Extra");
    vm.def("soa/test/Extra", "answer", "(I)I", [](jni::Object*, const jni::Args& a) -> u64 { return (u64)(s32)a[0] + 41; }, true);
    // An override of a built-in method that delegates to the original.
    vm.override_method(kSoa, "GetApplicationVersion", "()Ljava/lang/String;",
                       [&vm](jni::Object* self, const jni::Args& a, const jni::Impl& original) -> u64 {
                           std::string v = original ? jni::jstr(original(self, a)) : "?";
                           return (u64)vm.str(v + "+override");
                       });
});

u64 env_fn(jni::Vm& vm, const char* name) {
    u64* table = *(u64**)vm.env_ptr();
    for (size_t i = 0; i < sizeof kJniFunctionNames / sizeof *kJniFunctionNames; i++)
        if (!strcmp(kJniFunctionNames[i], name)) return table[i];
    fatal("no JNI function %s", name);
}

}  // namespace

int main(int argc, char** argv) {
    if (argc >= 3 && !strcmp(argv[1], "--crash-demo")) return run_crash_demo(argv[2]);  // crash_test.cpp: the crashing child
    if (argc >= 3 && !strcmp(argv[1], "--gdb-demo")) {  // gdbstub_test.cpp: the guest loop for a debugger
        cpu_global_init();
        bool fault = false, native = false;
        for (int i = 3; i < argc; i++) fault |= !strcmp(argv[i], "--fault"), native |= !strcmp(argv[i], "--native");
        return run_gdb_demo(argv[2], fault, native);
    }
    // A scratch data dir: jni/references-low-byte writes (and deletes) a SharedPreferences file.
    char dir[] = "/tmp/soaruntime_tests.XXXXXX";
    if (!mkdtemp(dir)) fatal("mkdtemp failed");
    vfs_init({dir});
    cpu_global_init();
    hle_init();
    auto& h = Hle::get();
    check(g_registrar_ran, "hle: registrar registered");

    // A registrar's new import.
    u64 t = h.lookup("soa_runtime_test_import");
    check(t && guest_call(t, {14}) == 42, "hle: new import from a registrar dispatches");
    // A registrar's override that delegates to the built-in thunk.
    check(g_orig_strlen != nullptr, "hle: override_fn returns the built-in host function");
    check(guest_call(h.lookup("strlen"), {(u64) "hello"}) == 1005, "hle: overridden strlen delegates to the original");
    check(h.host_fn("strlen") == my_strlen, "hle: host_fn reports the override");
    // An override after hle_init (before a library is loaded).
    HostFn prev = h.override_fn("getaddrinfo", my_getaddrinfo);
    check(prev != nullptr && prev != my_getaddrinfo, "hle: getaddrinfo had a built-in host function");
    check(guest_call(h.lookup("getaddrinfo"), {0, 0, 0, 0}) == 0x5eed, "hle: overridden getaddrinfo dispatches");
    check(h.override_fn("soa_runtime_test_unknown", my_getaddrinfo) == nullptr, "hle: override of an unknown import returns nullptr");

    // JVM: the host's version string, an override delegating to the built-in getter, a new class.
    device_config().app_version = "1.2.3";
    auto& vm = jni::Vm::get();
    vm.init();
    check(g_installer_ran, "jvm: class installer registered");
    u64 env = vm.env_ptr();
    u64 soa = guest_call(env_fn(vm, "FindClass"), {env, (u64)kSoa});
    u64 mid = guest_call(env_fn(vm, "GetMethodID"), {env, soa, (u64) "GetApplicationVersion", (u64) "()Ljava/lang/String;"});
    u64 jargs[1] = {0};
    u64 s = guest_call(env_fn(vm, "CallObjectMethodA"), {env, (u64)vm.activity, mid, (u64)jargs});
    check(jni::jstr(s) == "1.2.3+override", "jvm: overridden GetApplicationVersion delegates to the built-in one (device_config)");

    u64 extra = guest_call(env_fn(vm, "FindClass"), {env, (u64) "soa/test/Extra"});
    u64 smid = guest_call(env_fn(vm, "GetStaticMethodID"), {env, extra, (u64) "answer", (u64) "(I)I"});
    jargs[0] = 1;
    check((s32)guest_call(env_fn(vm, "CallStaticIntMethodA"), {env, extra, smid, (u64)jargs}) == 42, "jvm: installer's new static method dispatches");

    // An override after init keeps the method ID the game already holds.
    vm.override_method(kSoa, "GetApplicationVersion", "()Ljava/lang/String;",
                       [&vm](jni::Object*, const jni::Args&, const jni::Impl&) -> u64 { return (u64)vm.str("late"); });
    s = guest_call(env_fn(vm, "CallObjectMethodA"), {env, (u64)vm.activity, mid, (u64)jargs});
    check(jni::jstr(s) == "late", "jvm: override after init applies to an existing method ID");

    // The runtime tests of the guest CPU and the JNI layer (core/cpu_tests.cpp, jni/jvm_tests.cpp).
    run_runtime_tests("cpu/");
    run_runtime_tests("jni/");
    run_runtime_tests("frontend/text-");  // the text-entry editor (frontend/text_entry_tests.cpp)
    run_runtime_tests("frontend/touch-");  // scripted taps paced by frames (frontend/touch_script_tests.cpp)
    run_runtime_tests("frontend/movie-");  // the movie player on FFmpeg's libraries, with a built-in clip (frontend/movie_tests.cpp)
    run_runtime_tests("gdb/");             // the GDB protocol's encodings (core/gdb_protocol_tests.cpp)
    run_runtime_tests("hle/libc-");        // the guest libc helpers that differ by host (hle/format_tests.cpp)
    run_runtime_tests("hle/host-file-");   // Linux file semantics on either host (hle/host_file_tests.cpp)
    run_crash_tests(check);                // crash reports of a guest thread, in a child process (crash_test.cpp)
    run_gdbstub_tests(check);              // the GDB stub end to end (gdbstub_test.cpp; last: it turns the debugger hooks on)
    std::error_code ec;
    std::filesystem::remove_all(dir, ec);
    if (ec) fprintf(stderr, "couldn't remove %s\n", dir);

    fprintf(stderr, "%s: %d failure(s)\n", g_failures ? "FAIL" : "PASS", g_failures);
    return g_failures ? 1 : 0;
}

// Runtime tests of the JNI layer (core/selftest.h). Run by `soa --selftest` and soaruntime_tests.
//
// jni/references-low-byte: every handle the JNIEnv functions give the guest (references, class
// references, method and field IDs) has a non-zero low byte, as ART's do (jvm.h TaggedAlloc).
// 3.7.0 LocalKVS::SetBinaryAndroid (ELF 0x1f28474) tests the low byte of the java.lang.Boolean
// reference SetSharedPreferences returns (`ldrb w8, [sp, #8]; cbnz w8, ok`); with raw 16-aligned
// heap addresses that failed 1 time in 16 (emulator/README.md "The lost first request"). Each kind
// is made 256 times through the guest's dispatch (guest_call on the JNIEnv table's thunks): a
// 16-aligned allocator would give a zero low byte with probability 1 - (15/16)^256 > 0.99999.
//
// jni/method-tables-threads: the game resolves and calls Java methods from several threads while
// others define methods (RegisterNatives, Vm::override_method after start). Callers go through
// CallIntMethodA's virtual dispatch (an object of a subclass, the superclass's method ID) while one
// thread keeps replacing the method's implementation and another keeps adding methods to the
// subclass (the map the dispatch searches). Before code review CR3 (R1) the dispatch searched the
// map unlocked and an implementation was replaced while other threads ran it (a std::function
// assigned while called): wrong results or a crash.
#include <unistd.h>

#include <atomic>
#include <chrono>
#include <cinttypes>
#include <cstring>
#include <string>
#include <thread>
#include <vector>

#include "core/cpu.h"
#include "core/selftest.h"
#include "core/thread_record.h"
#include "core/vfs.h"
#include "jni/jni_names.h"
#include "jni/jvm.h"

namespace soa::jni {
namespace {

u64 env_fn(Vm& vm, const char* name) {
    u64* table = *(u64**)vm.env_ptr();
    for (size_t i = 0; i < sizeof kJniFunctionNames / sizeof *kJniFunctionNames; i++)
        if (!strcmp(kJniFunctionNames[i], name)) return table[i];
    return 0;
}

RUNTIME_TEST("jni/references-low-byte") {
    Vm& vm = Vm::get();
    const u64 env = vm.env_ptr();
    const char* names[] = {"NewStringUTF", "NewString", "FindClass", "GetMethodID", "GetStaticMethodID", "GetFieldID",
                           "NewObjectA", "AllocObject", "NewByteArray", "NewIntArray", "NewObjectArray", "GetObjectArrayElement",
                           "NewGlobalRef", "NewLocalRef", "NewWeakGlobalRef", "GetObjectClass", "CallObjectMethodA",
                           "CallStaticObjectMethodA"};
    for (const char* n : names)
        if (!env_fn(vm, n)) {
            t.fail("no JNIEnv function %s", n);
            return;
        }
    auto call = [&](const char* n, std::initializer_list<u64> a) { return guest_call(env_fn(vm, n), a); };

    // A test class with a constructor, a field and methods returning boxes, as the game's are.
    const char* kCls = "soa/test/RefTag";
    vm.def(kCls, "<init>", "()V", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(kCls, "flag", "(Z)Ljava/lang/Boolean;", [&vm](Object*, const Args& a) -> u64 { return (u64)vm.boolean(a[0] & 1); }, true);
    vm.def(kCls, "num", "(I)Ljava/lang/Integer;", [&vm](Object*, const Args& a) -> u64 { return (u64)vm.integer((int)a[0]); }, true);
    vm.def(kCls, "self", "()Ljava/lang/Object;", [](Object* s, const Args&) -> u64 { return (u64)s; });

    // The exact guest call: AskaActivity.SetSharedPreferences(String, String, byte[]) -> Boolean,
    // on the activity, into a scratch prefs file that is deleted afterwards.
    const char* kPrefs = "soa_selftest_jni_refs";
    u64 aa = call("FindClass", {env, (u64) "jb/Aska/AskaActivity"});
    u64 set_mid = call("GetMethodID", {env, aa, (u64) "SetSharedPreferences", (u64) "(Ljava/lang/String;Ljava/lang/String;[B)Ljava/lang/Boolean;"});
    const bool have_activity = vm.activity != nullptr;

    int zero = 0, total = 0;
    std::string first_zero;
    auto check = [&](const char* what, u64 ref) {
        total++;
        if (!ref) {
            t.fail("%s returned null", what);
            return;
        }
        if (!(ref & 0xff)) {
            if (!zero++) first_zero = what;
        }
    };
    const char16_t u16[] = {u'x', u'y'};
    for (int i = 0; i < 256; i++) {
        u64 s = call("NewStringUTF", {env, (u64) "ref"});
        check("NewStringUTF", s);
        check("NewString", call("NewString", {env, (u64)u16, 2}));
        // FindClass of a class that doesn't exist yet creates it (a new Class object each time).
        std::string cn = "soa/test/RefTag" + std::to_string(i);
        u64 cls = call("FindClass", {env, (u64)cn.c_str()});
        check("FindClass (new class)", cls);
        u64 tc = call("FindClass", {env, (u64)kCls});
        check("FindClass", tc);
        // New method / field IDs: a new Method / Field object each (defined first, so that the
        // lookups don't log "unknown method").
        std::string mn = "m" + std::to_string(i);
        vm.def(cn, mn, "()V", [](Object*, const Args&) -> u64 { return 0; });
        vm.def(cn, mn, "()I", [](Object*, const Args&) -> u64 { return 0; }, true);
        ((Class*)cls)->fields[mn] = new Field{{}, (Class*)cls, mn, "I", false};
        check("GetMethodID", call("GetMethodID", {env, cls, (u64)mn.c_str(), (u64) "()V"}));
        check("GetStaticMethodID", call("GetStaticMethodID", {env, cls, (u64)mn.c_str(), (u64) "()I"}));
        check("GetFieldID", call("GetFieldID", {env, cls, (u64)mn.c_str(), (u64) "I"}));
        u64 init = call("GetMethodID", {env, tc, (u64) "<init>", (u64) "()V"});
        u64 none[2] = {0, 0};
        u64 o = call("NewObjectA", {env, tc, init, (u64)none});
        check("NewObjectA", o);
        check("AllocObject", call("AllocObject", {env, tc}));
        u64 flag = call("GetStaticMethodID", {env, tc, (u64) "flag", (u64) "(Z)Ljava/lang/Boolean;"});
        u64 num = call("GetStaticMethodID", {env, tc, (u64) "num", (u64) "(I)Ljava/lang/Integer;"});
        u64 self = call("GetMethodID", {env, tc, (u64) "self", (u64) "()Ljava/lang/Object;"});
        u64 arg[1] = {(u64)(i & 1)};
        check("CallStaticObjectMethodA (Boolean)", call("CallStaticObjectMethodA", {env, tc, flag, (u64)arg}));
        arg[0] = (u64)i;
        check("CallStaticObjectMethodA (Integer)", call("CallStaticObjectMethodA", {env, tc, num, (u64)arg}));
        check("CallObjectMethodA (this)", call("CallObjectMethodA", {env, o, self, (u64)none}));
        check("NewByteArray", call("NewByteArray", {env, 4}));
        check("NewIntArray", call("NewIntArray", {env, 4}));
        u64 oa = call("NewObjectArray", {env, 2, tc, s});
        check("NewObjectArray", oa);
        check("GetObjectArrayElement", call("GetObjectArrayElement", {env, oa, 1}));
        check("NewGlobalRef", call("NewGlobalRef", {env, s}));
        check("NewLocalRef", call("NewLocalRef", {env, s}));
        check("NewWeakGlobalRef", call("NewWeakGlobalRef", {env, s}));
        check("GetObjectClass", call("GetObjectClass", {env, o}));
        // Host-side constructors the Java methods use.
        check("Vm::boolean", (u64)vm.boolean(true));
        check("Vm::integer", (u64)vm.integer(i));
        check("Vm::str", (u64)vm.str("s"));
        check("Vm::byte_array", (u64)vm.byte_array("ab", 2));
        check("Vm::instance", (u64)vm.instance("java/lang/Object"));
        if (have_activity && set_mid) {
            u8 bytes[4] = {1, 2, 3, (u8)i};
            u64 ba = call("NewByteArray", {env, 4});
            guest_call(env_fn(vm, "SetByteArrayRegion"), {env, ba, 0, 4, (u64)bytes});
            u64 a3[3] = {call("NewStringUTF", {env, (u64)kPrefs}), call("NewStringUTF", {env, (u64) "key"}), ba};
            u64 r = call("CallObjectMethodA", {env, (u64)vm.activity, set_mid, (u64)a3});
            check("SetSharedPreferences (Boolean)", r);
            // The guest's test (ELF 0x1f28474): the low byte of the reference is the result.
            if (!(u8)r) t.fail("SetSharedPreferences: the guest's low-byte test reads the save as failed (%#" PRIx64 ")", r);
        }
    }
    if (have_activity && set_mid) unlink((host_shared_prefs_dir() + "/" + kPrefs + ".xml").c_str());
    if (zero) t.fail("%d of %d handles had a zero low byte (first: %s)", zero, total, first_zero.c_str());
    // Every one ends in 8 (mod 16): TaggedAlloc's offset.
    if ((u64)vm.boolean(false) % TaggedAlloc::kAlign != TaggedAlloc::kTag) t.fail("a Boolean isn't at kTag (mod kAlign)");
    // The activity (activity->clazz) and the classes made at init are tagged too.
    if (have_activity && !((u64)vm.activity & 0xff)) t.fail("the activity object has a zero low byte");
    if (!((u64)vm.find_class("java/lang/String") & 0xff)) t.fail("java/lang/String has a zero low byte");
}

RUNTIME_TEST("jni/method-tables-threads") {
    Vm& vm = Vm::get();
    const u64 env = vm.env_ptr();
    const u64 find_class = env_fn(vm, "FindClass"), get_mid = env_fn(vm, "GetMethodID"), call_int = env_fn(vm, "CallIntMethodA");
    if (!find_class || !get_mid || !call_int) {
        t.fail("no JNIEnv FindClass / GetMethodID / CallIntMethodA");
        return;
    }
    const char* kBase = "soa/test/RaceBase";
    const char* kSub = "soa/test/RaceSub";
    // An implementation's state, cleared by its destructor. A call reads it twice, 20 us apart
    // (a busy wait, the same on every host): when the implementation is replaced and destroyed
    // while it runs, the second read sees 0 and the call returns 0.
    constexpr u64 kPayload = 64;
    struct State {
        u64 v;
        char pad[48];  // (past std::function's local storage: the functor is on the heap)
        explicit State(u64 v) : v(v) {}
        State(const State&) = default;
        ~State() { *(volatile u64*)&v = 0; }
    };
    auto impl = [](u64 gen) {
        return [st = State(kPayload + gen)](Object*, const Args&) -> u64 {
            u64 a = *(volatile const u64*)&st.v;
            auto until = std::chrono::steady_clock::now() + std::chrono::microseconds(20);
            while (std::chrono::steady_clock::now() < until) {}
            return a == *(volatile const u64*)&st.v ? a : 0;
        };
    };
    vm.def(kBase, "val", "()I", impl(0));
    vm.define_class(kSub, kBase);
    Object* obj = vm.instance(kSub);
    const u64 base = guest_call(find_class, {env, (u64)kBase});
    const u64 mid = guest_call(get_mid, {env, base, (u64) "val", (u64) "()I"});
    if (!mid) {
        t.fail("GetMethodID(RaceBase.val) is null");
        return;
    }

    constexpr int kCallers = 4, kCalls = 5000;
    std::atomic<bool> stop{false};
    std::atomic<int> bad{0};
    std::atomic<u64> first_bad{0};
    std::vector<std::thread> threads;
    for (int i = 0; i < kCallers; i++)
        threads.emplace_back([&] {
            ThreadScope scope("jni-race");
            guest_thread_init(256 << 10);
            u64 none[1] = {0};
            for (int n = 0; n < kCalls; n++) {
                u64 r = (u32)guest_call(call_int, {env, (u64)obj, mid, (u64)none});
                if (r < kPayload) {
                    if (!bad++) first_bad = r;
                }
            }
        });
    std::thread redefine([&] {
        for (u64 n = 1; !stop; n++) vm.def(kBase, "val", "()I", impl(n));
    });
    std::thread add([&] {
        for (int n = 0; n < 50000 && !stop; n++)  // new keys: inserts into the map the dispatch searches
            vm.def(kSub, "m" + std::to_string(n), "()V", [](Object*, const Args&) -> u64 { return 0; });
    });
    for (auto& th : threads) th.join();
    stop = true;
    redefine.join();
    add.join();
    if (bad)
        t.fail("%d of %d calls returned %#" PRIx64 " (first): an implementation was destroyed while it ran", bad.load(), kCallers * kCalls,
               first_bad.load());
}

}  // namespace
}  // namespace soa::jni

// Aska::Thread: the handle's bookkeeping, joining and sleeping (port/decomp/sync/thread.c).
// Creating a thread (Create, with the priority mapping), Main (every Aska thread's entry) and Exit
// stay guest code: they go through the HLE's pthread_create / pthread_exit (README.md "Scope").
#include <pthread.h>
#include <time.h>

#include "soaruntime/core/cpu.h"
#include "native/common/guest_std.h"
#include "native/common/native_method.h"
#include "native/sync/sync_layout.h"

namespace soa::native::sync {

namespace {
const void* thread_vtable() {
    static const u64 vt = guest::sym("_ZTVN4Aska6ThreadE") + 0x10;
    return (const void*)vt;
}
// pthread_join on the guest's handle: the HLE's pthread_t is the host's (hle/libc_thread.cpp th_join).
s32 join(u64 thread) {
    ProfNativeWait wait;
    return pthread_join((pthread_t)thread, nullptr);
}
// The guest's nanosleep(&ts, &ts): the HLE passes the guest timespec to the host's nanosleep.
s32 sleep_for(u64 sec, u64 nsec) {
    struct timespec ts;
    ts.tv_sec = (time_t)sec;
    ts.tv_nsec = (long)nsec;
    ProfNativeWait wait;
    return nanosleep(&ts, &ts);
}
}  // namespace

void Thread::Ctor() {
    vtable = thread_vtable();
    m_thread = 0;
}

void Thread::DtorBase() {
    vtable = thread_vtable();
    if (m_thread) join(m_thread);
    m_thread = 0;
}

void Thread::DtorDelete() {
    vtable = thread_vtable();
    if (m_thread) join(m_thread);
    static const u64 op_delete = guest::sym("_ZdlPv");
    guest_call(op_delete, {(u64)this});
}

s32 Thread::WaitEnd() { return m_thread ? join(m_thread) : 0; }

void Thread::Delete() { m_thread = 0; }

u64 Thread::GetCurrentID() { return (u64)pthread_self(); }  // (the HLE's pthread_self)

s32 Thread::Sleep(u32 ms) {
    u32 us = ms * 1000u;  // (32-bit in the guest: wraps from 4294968 ms on)
    return sleep_for(us / 1000000u, (u64)(us % 1000000u) * 1000u);
}

s32 Thread::SleepU(u32 usec) { return sleep_for(usec / 1000000u, (u64)(usec % 1000000u) * 1000u); }

NATIVE_METHOD("_ZN4Aska6ThreadC2Ev", &Thread::Ctor, "sync: Aska::Thread::Thread");
NATIVE_METHOD("_ZN4Aska6ThreadD2Ev", &Thread::DtorBase, "sync: Aska::Thread::~Thread (joins)");
NATIVE_METHOD("_ZN4Aska6ThreadD0Ev", &Thread::DtorDelete, "sync: Aska::Thread::~Thread (deleting)");
NATIVE_METHOD("_ZN4Aska6Thread7WaitEndEv", &Thread::WaitEnd, "sync: Aska::Thread::WaitEnd (pthread_join)");
NATIVE_METHOD("_ZN4Aska6Thread6DeleteEv", &Thread::Delete, "sync: Aska::Thread::Delete");
NATIVE_FUNCTION("_ZN4Aska6Thread5SleepEj", wrap<&Thread::Sleep>(), "sync: Aska::Thread::Sleep (nanosleep)");
NATIVE_FUNCTION("_ZN4Aska6Thread6SleepUEj", wrap<&Thread::SleepU>(), "sync: Aska::Thread::SleepU (nanosleep)");

}  // namespace soa::native::sync

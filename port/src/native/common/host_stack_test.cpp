// runtime/guest-thread-host-stack: a guest thread's host stack keeps its kGuestThreadHostStack for
// the JIT whatever the program's static TLS (runtime/include/soaruntime/hle/thread.h). glibc places the static
// TLS block at the top of each thread's stack, inside the requested size: when the port's TLS grew
// to 160 KB (input's live-check buffers, n-io), the game thread kept ~90 KB of its 256 KiB, and
// the tower menu's ~55 nested guest_calls overflowed it (session:tower died with SIGSEGV).
// The test makes a host thread as the HLE'd pthread_create does and measures what is left below
// its first frame, in this binary, with its TLS.
#ifndef _WIN32
#include <pthread.h>

#include "soaruntime/hle/thread.h"
#include "native/common/test.h"

using namespace soa;

namespace {

struct Probe {
    size_t usable = 0, total = 0;
};

void* probe(void* p) {
    auto* r = (Probe*)p;
    pthread_attr_t at;
    void* lo = nullptr;
    size_t size = 0;
    if (pthread_getattr_np(pthread_self(), &at) == 0) {
        pthread_attr_getstack(&at, &lo, &size);
        pthread_attr_destroy(&at);
    }
    volatile char here = 0;
    r->usable = (size_t)((const char*)&here - (const char*)lo);
    r->total = size;
    return nullptr;
}

}  // namespace

NATIVE_TEST("runtime/guest-thread-host-stack") {
    const size_t tls = hle_static_tls_size(), stack = hle_guest_thread_host_stack();
    t.expect_eq(stack, kGuestThreadHostStack + tls, "the guest thread's host stack (256 KiB + the static TLS)");
    pthread_attr_t ha;
    pthread_attr_init(&ha);
    pthread_attr_setstacksize(&ha, stack);
    Probe r;
    pthread_t th;
    if (pthread_create(&th, &ha, probe, &r) != 0) {
        pthread_attr_destroy(&ha);
        return t.fail("pthread_create failed");
    }
    pthread_join(th, nullptr);
    pthread_attr_destroy(&ha);
    // The first frame of the thread function: everything above it is the TLS, the TCB and libc's
    // start frames (a few KB); 8 KB of slack for those.
    if (r.usable + (8 << 10) < kGuestThreadHostStack)
        t.fail("a guest thread has %zu bytes of host stack below its first frame (of %zu; static TLS %zu): fewer than %zu", r.usable, r.total,
               tls, (size_t)kGuestThreadHostStack);
}
#endif

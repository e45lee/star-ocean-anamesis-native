#pragma once
// Host objects behind the HLE'd bionic threading imports, for native replacements that must
// interoperate with guest code using the same guest objects.
#include <semaphore.h>

#include <cstddef>

#include "core/cpu.h"

namespace soa {

// The host semaphore standing in for the guest (bionic) sem_t at `guest_sem`: the same object
// the HLE sem_* imports use (created on first use for a zero-initialised guest semaphore).
sem_t* hle_host_sem(u64 guest_sem);
// sem_init / sem_destroy on a guest sem_t, as the HLE imports do them.
int hle_host_sem_init(u64 guest_sem, unsigned value);
void hle_host_sem_destroy(u64 guest_sem);

// The HLE'd pthread mutex / condition variable / semaphore imports as host calls on guest objects
// (guest addresses), for natives working on objects guest code shares (port/src/native/sync): the
// same host objects and rules as the imports (glibc / winpthreads objects in place, bionic's static
// initializers converted on first use, the window thread's sliced condition wait for idle
// presenting), and the imports' results (Linux errno values; the sem_* ones 0 / -1 with the
// host's errno set, which the thunk dispatch makes the guest's: core/linux_errno.h).
// They block like the imports; a native wraps a blocking call in ProfNativeWait (core/cpu.h).
int hle_mutex_init(u64 guest_mutex, u64 guest_attr /* 0: default */);
int hle_mutex_destroy(u64 guest_mutex);
int hle_mutex_lock(u64 guest_mutex);
int hle_mutex_trylock(u64 guest_mutex);
int hle_mutex_unlock(u64 guest_mutex);
int hle_cond_init(u64 guest_cond);
int hle_cond_destroy(u64 guest_cond);
int hle_cond_signal(u64 guest_cond);
int hle_cond_broadcast(u64 guest_cond);
int hle_cond_wait(u64 guest_cond, u64 guest_mutex);
int hle_cond_timedwait(u64 guest_cond, u64 guest_mutex, u64 guest_abstime /* a guest timespec */);
int hle_sem_wait(u64 guest_sem);  // (EINTR retried)
int hle_sem_trywait(u64 guest_sem);
int hle_sem_post(u64 guest_sem);
int hle_sem_getvalue(u64 guest_sem, int* value);

// The host stack a guest thread (the HLE'd pthread_create) gets: kGuestThreadHostStack for the JIT
// levels and thunks (~1.7 KB per nested guest_call), plus the static TLS that glibc carves out of
// it (hle_static_tls_size: the PT_TLS segments of the modules loaded at start-up; 0 on Windows,
// where TLS isn't on the stack). Selftest runtime/guest-thread-host-stack.
inline constexpr size_t kGuestThreadHostStack = 256 << 10;
size_t hle_static_tls_size();
size_t hle_guest_thread_host_stack();

}  // namespace soa

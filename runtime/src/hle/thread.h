#pragma once
// Host objects behind the HLE'd bionic threading imports, for native replacements that must
// interoperate with guest code using the same guest objects.
#include <semaphore.h>

#include "core/cpu.h"

namespace soa {

// The host semaphore standing in for the guest (bionic) sem_t at `guest_sem`: the same object
// the HLE sem_* imports use (created on first use for a zero-initialised guest semaphore).
sem_t* hle_host_sem(u64 guest_sem);
// sem_init / sem_destroy on a guest sem_t, as the HLE imports do them.
int hle_host_sem_init(u64 guest_sem, unsigned value);
void hle_host_sem_destroy(u64 guest_sem);

}  // namespace soa

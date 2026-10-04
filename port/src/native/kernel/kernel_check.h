#pragma once
// The live check of the kernel natives (soa --live-check kernel[:every=N][:budget=N][:only=..][:out=FILE]).
//
// The dispatcher's natives are stateful under its FastCriticalSection, so they are checked like
// sync's primitives (common/shadow_check.h): the native records the dispatcher as it found it
// once it held the lock (its bytes, the worker array, the block storage, the counters its queued
// sync-end messages wait on) and as it left it before releasing the lock, plus what its wake pass
// read and did; the check then builds a private shadow of that state (pointers relocated, its own
// lock, semaphore and events) and runs the guest original on it (kernel_dispatcher_check.cpp).
#include <utility>
#include <vector>

#include "native/common/shadow_check.h"
#include "native/kernel/kernel_layout.h"

namespace soa::native::kernel {

// The family (--live-check kernel).
live::ShadowFamily& family();
struct CheckedFn : live::CheckedFn {
    explicit CheckedFn(const char* s) : live::CheckedFn(::soa::native::kernel::family(), s) {}
};

constexpr int kMaxWorkers = 256;

// What a dispatcher native saw (filled when t_dobs is set: only inside a check on this thread).
struct DispatchObservation {
    // The state under the lock: the dispatcher (0x1d0), the worker array (with its new[] cookie)
    // and the block storage, concatenated (Snapshot::capture in kernel_dispatcher_check.cpp).
    std::vector<u8> pre, post;
    bool have_pre = false, have_post = false;
    std::vector<std::pair<u64, s32>> counters;  // pre: the queued kFlagWaitCounter blocks' *m_counter
    // The wake passes (outside or inside the lock): per worker, kRead | the flags read; kSet when
    // the native Set its event.
    static constexpr u8 kRead = 0x80, kWaiting = 1, kBusy = 2, kSignaled = 4, kSet = 0x40;
    u8 wake[kMaxWorkers] = {};
    void note_worker(s32 i, u8 flags) {
        if (i >= 0 && i < kMaxWorkers) wake[i] |= (u8)(kRead | flags);
    }
    void note_set(s32 i) {
        if (i >= 0 && i < kMaxWorkers) wake[i] |= kSet;
    }
    void capture_pre(const SimpleMessageDispatcher* d);
    void capture_post(const SimpleMessageDispatcher* d);
};
extern thread_local DispatchObservation* t_dobs;

// What a TaskManager barrier native saw under m_barrierCs (kernel_task_check.cpp).
struct TaskObservation {
    u8 pre[sizeof(TaskManager)], post[sizeof(TaskManager)];
    bool have_pre = false, have_post = false;
    s32 refs_read = -1;  // IncrementThreadBarrierCount: the reference count read before the lock
    void capture_pre(const TaskManager* m);
    void capture_post(const TaskManager* m);
};
extern thread_local TaskObservation* t_tobs;

}  // namespace soa::native::kernel

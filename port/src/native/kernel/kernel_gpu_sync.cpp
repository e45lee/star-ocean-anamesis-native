// Aska::GPUSync (port/decomp/kernel/gpu_sync.c): the render thread's "GPU frame done" notifier.
// WaitGPUSync blocks the caller (ObjectManager::WaitGPUSync) until the pending frame is notified;
// Notify (the render thread) clears the flag, stamps performance counter 2 and runs the notifier's
// handlers. The NotifierThread's own methods (AddNotify / RemoveNotify / Notify) stay guest code.
//
// Live check: none. Notify runs the registered handlers (other subsystems' code, real wake-ups) and
// WaitGPUSync blocks until another thread's Notify: neither can be replayed on a copy. Covered by the
// differential tests (kernel/gpu-sync-*), which compare the call sequences with the guest's.
#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/guest_std.h"
#include "native/common/native_method.h"
#include "native/kernel/kernel_layout.h"

namespace soa::native::kernel {

namespace {
u64 fn(const char* sym) { return guest::sym(sym); }
}  // namespace

void GPUSync::WaitGPUSync() {
    static const u64 add_notify = fn("_ZN4Aska14NotifierThread9AddNotifyEPNS_7INotifyEj");
    static const u64 remove_notify = fn("_ZN4Aska14NotifierThread12RemoveNotifyEPNS_7INotifyE");
    static const u64 event_notify_vt = fn("_ZTVN4Aska11EventNotifyE") + 0x10;
    m_lock.Wait();
    if (!__atomic_load_n(&m_pending, __ATOMIC_SEQ_CST)) {
        m_lock.Signal();
        return;
    }
    alignas(16) Event ev;
    ev.Ctor();
    if (ev.Create(true, false)) {
        alignas(16) EventNotify n{(const void*)event_notify_vt, &ev};
        guest_call(add_notify, {(u64)this, (u64)&n, 0});
        m_lock.Signal();
        ev.Wait(0);
        guest_call(remove_notify, {(u64)this, (u64)&n});
        ev.Exit();
    } else {
        // (no event: poll the flag)
        m_lock.Signal();
        while (__atomic_load_n(&m_pending, __ATOMIC_SEQ_CST)) Thread::Sleep(1);
    }
    ev.Exit();  // (a second Exit after the first: a no-op, as in the guest)
}

void GPUSync::Notify() {
    static const u64 notifier_notify = fn("_ZN4Aska14NotifierThread6NotifyEv");
    m_lock.Wait();
    m_pending = 0;
    auto* pc = *reinterpret_cast<PerformanceCounter**>(main_lib()->base + kVaddrGlobalPerformanceCounter);
    pc->Set(2);
    guest_call(notifier_notify, {(u64)this});
    m_lock.Signal();
}

NATIVE_METHOD("_ZN4Aska7GPUSync11WaitGPUSyncEv", &GPUSync::WaitGPUSync, "kernel: GPUSync::WaitGPUSync");
NATIVE_METHOD("_ZN4Aska7GPUSync6NotifyEv", &GPUSync::Notify, "kernel: GPUSync::Notify");

}  // namespace soa::native::kernel

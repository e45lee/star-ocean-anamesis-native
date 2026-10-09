// Differential tests of GPUSync (kernel_gpu_sync.cpp): two private GPUSyncs (the NotifierThread
// constructor, GPUSync's vtable, the lock created as the render thread's does: Create(1, 1)), one
// driven by the guest functions, one by the native members; the notifier's list, the flag, the lock's
// count and the handlers' events compared. WaitGPUSync with a pending frame waits on its event: the
// guest's Event::Wait is stubbed for its run (the stub records the wait), the native's returns at once
// (sync::t_replay_no_wait), so both register, wait and remove their EventNotify.
#include <cstring>
#include <string>

#include "soaruntime/core/cpu.h"
#include "soaruntime/hle/thread.h"
#include "native/common/guest_stub.h"
#include "native/common/test.h"
#include "native/kernel/kernel_layout.h"
#include "native/sync/sync_check.h"

using namespace soa;
using namespace soa::native;
using namespace soa::native::kernel;

namespace {

struct PrivateGPUSync {
    alignas(16) u8 storage[sizeof(GPUSync)];
    alignas(16) Event ev;  // a handler's event
    alignas(16) EventNotify notify;
    GPUSync* g() { return reinterpret_cast<GPUSync*>(storage); }
    void build(TestContext& t) {
        std::memset(storage, 0, sizeof storage);
        t.call("_ZN4Aska14NotifierThreadC2Ei", {(u64)g(), 8});
        g()->base.base.vtable = (const void*)(t.sym("_ZTVN4Aska7GPUSyncE") + 0x10);
        t.call("_ZN4Aska9SemaphoreC1Ev", {(u64)&g()->m_lock});
        t.call("_ZN4Aska9Semaphore6CreateEii", {(u64)&g()->m_lock, 1, 1});
        t.call("_ZN4Aska5EventC1Ev", {(u64)&ev});
        t.call("_ZN4Aska5Event6CreateEbb", {(u64)&ev, 1, 0});
        notify.vtable = (const void*)(t.sym("_ZTVN4Aska11EventNotifyE") + 0x10);
        notify.m_event = &ev;
    }
    std::string state() {
        int v = -1;
        hle_sem_getvalue(g()->m_lock.m_pSem, &v);
        return "pending " + std::to_string(g()->m_pending) + " list " + std::to_string(g()->base.m_list.m_count) + " lock " + std::to_string(v) +
               " handler event " + std::to_string(ev.m_signaled);
    }
    void destroy(TestContext& t) {
        t.call("_ZN4Aska5Event4ExitEv", {(u64)&ev});
        t.call("_ZN4Aska7GPUSyncD2Ev", {(u64)g()});
    }
};

}  // namespace

NATIVE_TEST("kernel/gpu-sync") {
    static PrivateGPUSync a, b;
    a.build(t);
    b.build(t);
    const u64 wait_fn = t.sym("_ZNK4Aska5Event4WaitEj");
    stub_isolated_at(wait_fn, "kernel_gpusync_wait", 2);
    const std::string wait_name = stub_name(wait_fn);
    // No frame pending: returns at once.
    t.call("_ZN4Aska7GPUSync11WaitGPUSyncEv", {(u64)a.g()});
    b.g()->WaitGPUSync();
    t.expect_eq(a.state(), b.state(), "WaitGPUSync, nothing pending");
    // A frame pending: registers an EventNotify, waits, removes it.
    a.g()->m_pending = b.g()->m_pending = 1;
    int waits = 0;
    {
        StubSession ss;
        ss.only = {wait_name};
        ss.behave[wait_name] = [&](Cpu& c) {
            waits++;
            t.expect_eq((s32)a.g()->base.m_list.m_count, 1, "guest: its EventNotify registered while waiting");
            c.set_x(0, 0);
        };
        t.call("_ZN4Aska7GPUSync11WaitGPUSyncEv", {(u64)a.g()});
    }
    sync::t_replay_no_wait = true;
    b.g()->WaitGPUSync();
    sync::t_replay_no_wait = false;
    t.expect_eq(waits, 1, "guest waited once");
    t.expect_eq(a.state(), b.state(), "WaitGPUSync, a frame pending");
    // Notify: the flag cleared, the registered handlers run (a one-shot EventNotify sets its event and goes).
    for (PrivateGPUSync* s : {&a, &b}) t.call("_ZN4Aska14NotifierThread9AddNotifyEPNS_7INotifyEj", {(u64)s->g(), (u64)&s->notify, 1});
    t.call("_ZN4Aska7GPUSync6NotifyEv", {(u64)a.g()});
    b.g()->Notify();
    t.expect_eq(a.state(), b.state(), "Notify");
    t.expect_eq(b.ev.m_signaled, (u8)1, "Notify ran the handler");
    a.destroy(t);
    b.destroy(t);
}

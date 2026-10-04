// render_test_util.cpp: see render_test_util.h. The frame hook is a NATIVE_TEST_HOOK, so it exists only in
// --selftest runs (natives and normal runs never see it).
#include "native/render/render_test_util.h"

#include <chrono>
#include <condition_variable>
#include <mutex>
#include <vector>

namespace soa::native::render::testutil {

u64 vcall(const void* obj, int slot, std::initializer_list<u64> rest) {
    GuestArgs ga;
    ga.i((u64)obj);
    for (u64 a : rest) ga.i(a);
    return guest_call(vslot(obj, slot), ga).x0;
}

namespace {

std::mutex g_mu;
std::condition_variable g_cv;
const std::function<void()>* g_pending = nullptr;  // the body to run at the next frame
bool g_done = false;
u64 g_orig_prepaint = 0;

// Aska::ObjectManager::OnPrePaint(): runs a pending test body first, then the original.
void hook_prepaint(Cpu& c) {
    u64 self = c.x(0);
    {
        std::unique_lock<std::mutex> lk(g_mu);
        if (g_pending) {
            const std::function<void()>* body = g_pending;
            g_pending = nullptr;
            lk.unlock();
            (*body)();
            lk.lock();
            g_done = true;
            g_cv.notify_all();
        }
    }
    c.set_x(0, guest_call(g_orig_prepaint, {self}));
}

NATIVE_TEST_HOOK("_ZN4Aska13ObjectManager10OnPrePaintEv", hook_prepaint, &g_orig_prepaint);

}  // namespace

bool on_frame(TestContext& t, const std::function<void()>& body, int timeout_ms) {
    std::unique_lock<std::mutex> lk(g_mu);
    g_done = false;
    g_pending = &body;
    if (g_cv.wait_for(lk, std::chrono::milliseconds(timeout_ms), [] { return g_done; })) return true;
    if (g_pending == &body) {  // never taken: withdraw it (the hook takes it under the lock)
        g_pending = nullptr;
        t.fail("no frame (Aska::ObjectManager::OnPrePaint) within %d ms", timeout_ms);
        return false;
    }
    g_cv.wait(lk, [] { return g_done; });  // taken and running: `body` must outlive it
    return true;
}

}  // namespace soa::native::render::testutil

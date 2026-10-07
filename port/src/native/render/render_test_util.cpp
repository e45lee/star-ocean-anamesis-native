// render_test_util.cpp: see render_test_util.h. The frame hook is a NATIVE_TEST_HOOK, so it exists only in
// --selftest runs (natives and normal runs never see it).
#include "native/render/render_test_util.h"

#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <condition_variable>
#include <mutex>
#include <vector>

#include <soa/env.h>

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

void probe_hook(Probe& p, Cpu& c) {
    {
        std::unique_lock<std::mutex> lk(p.mu);
        if (p.body) {
            const std::function<bool(Cpu&)>* body = p.body;
            p.body = nullptr;  // taken: other threads' calls pass while it runs
            lk.unlock();
            bool took = (*body)(c);
            lk.lock();
            if (took) {
                p.done = true;
                p.cv.notify_all();
            } else {
                p.body = body;  // not this one: stay armed
            }
        }
    }
    GuestArgs ga;
    for (int i = 0; i < 8; i++) ga.i(c.x(i));
    for (int i = 0; i < 8; i++) ga.vecs.push_back(c.v(i));
    ga.x8 = c.x(8);
    GuestResult r = guest_call(p.orig, ga);
    c.set_x(0, r.x0);
    c.set_x(1, r.x1);
    c.set_v(0, r.v0);
    c.set_v(1, r.v1);
    c.set_v(2, r.v2);
    c.set_v(3, r.v3);
}

// (main.cpp reads it the same way: set and non-empty)
bool live_screen() { return env::env_str("SOA_SELFTEST_START_FILE") != nullptr; }

bool probe_call(TestContext& t, Probe& p, const std::function<bool(Cpu&)>& body, int timeout_ms, const char* what,
                bool required) {
    std::unique_lock<std::mutex> lk(p.mu);
    p.done = false;
    p.body = &body;
    if (p.cv.wait_for(lk, std::chrono::milliseconds(timeout_ms), [&] { return p.done; })) return true;
    if (p.body == &body) {  // armed, not running: withdraw it
        p.body = nullptr;
        if (required)
            t.fail("no call of %s within %d ms", what, timeout_ms);
        else
            fprintf(stderr, "    note: no call of %s within %d ms (not on this screen; skipped)\n", what, timeout_ms);
        return false;
    }
    p.cv.wait(lk, [&] { return p.done || p.body == &body; });  // running now: `body` must outlive it
    if (p.body == &body) p.body = nullptr;
    return p.done;
}

}  // namespace soa::native::render::testutil

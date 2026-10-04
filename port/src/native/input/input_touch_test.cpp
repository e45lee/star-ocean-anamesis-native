// Differential tests of input_touch.cpp: TouchPanel::CopyMessages and ResetStatus on private panels
// (zeroed, TouchPanel's vtable, the critical section built by the guest's constructor), the guest
// original on one and the native on a twin with the same messages. Both take the real
// TouchPanel::m_criGlobal (the running game's peripheral thread takes it too). In --selftest natives
// aren't installed: t.call reaches the guest code.
#include <cstring>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/common/test.h"
#include "native/input/input_check.h"
#include "native/input/input_layout.h"

using namespace soa;
using namespace soa::native::input;

namespace {

struct TestPanel {
    alignas(16) u8 storage[sizeof(TouchPanel)];
    TouchPanel* panel() { return reinterpret_cast<TouchPanel*>(storage); }
    void build(TestContext& t) {
        std::memset(storage, 0, sizeof storage);
        panel()->base.vtable = (const void*)(t.sym("_ZTVN4Aska10TouchPanelE") + 0x10);
        t.call("_ZN4Aska19FastCriticalSectionC2Ev", {(u64)&panel()->base.m_cs});
    }
    void destroy(TestContext& t) { t.call("_ZN4Aska19FastCriticalSectionD2Ev", {(u64)&panel()->base.m_cs}); }
};

bool same_panel(TestContext& t, TouchPanel* a, TouchPanel* b, const char* what) {
    std::string why = live::diff_bytes((const u8*)a, (const u8*)b, 0, sizeof(TouchPanel), {{kSemPtrOff, kSemPtrOff + 8}});
    if (why.empty()) return true;
    t.fail("%s: %s", what, why.c_str());
    return false;
}

}  // namespace

NATIVE_TEST("input/touch-copy-messages") {
    static TestPanel gp, np;
    gp.build(t);
    np.build(t);
    TouchPanel* g = gp.panel();
    TouchPanel* n = np.panel();
    alignas(16) static TouchData gout[64], nout[64];
    const s32 counts[] = {0, 1, 2, 7, 8, 63, 64};
    for (int round = 0; round < 24; round++) {
        s32 count = round < 7 ? counts[round] : t.rand_int(0, 64);
        auto data = t.rand_bytes(sizeof g->m_data);
        std::memcpy(g->m_data, data.data(), data.size());
        std::memcpy(n->m_data, data.data(), data.size());
        g->m_numData = n->m_numData = count;
        std::memset(gout, 0x3c, sizeof gout);
        std::memset(nout, 0x3c, sizeof nout);
        s32 rg = (s32)t.call("_ZN4Aska10TouchPanel12CopyMessagesEPNS_9TouchDataE", {(u64)g, (u64)gout});
        s32 rn = n->CopyMessages(nout);
        t.expect_eq(rn, rg, "CopyMessages count");
        if (std::memcmp(gout, nout, sizeof gout) != 0) t.fail("CopyMessages output differs (count %d)", count);
        same_panel(t, g, n, "after CopyMessages");
        // CTouchPanel::Reset's ResetStatus, then a copy of nothing
        t.call("_ZN4Aska10TouchPanel11ResetStatusEv", {(u64)g});
        n->ResetStatus();
        same_panel(t, g, n, "after ResetStatus");
        t.expect_eq(n->m_numData, 0, "ResetStatus clears the count");
        rg = (s32)t.call("_ZN4Aska10TouchPanel12CopyMessagesEPNS_9TouchDataE", {(u64)g, (u64)gout});
        rn = n->CopyMessages(nout);
        t.expect_eq(rn, rg, "CopyMessages after ResetStatus");
    }
    t.expect_eq(n->base.m_cs.m_lock, FastCriticalSection::kFree, "panel lock released");
    t.expect_eq(TouchPanel::CriGlobal()->m_lock == FastCriticalSection::kFree || TouchPanel::CriGlobal()->m_lock == FastCriticalSection::kHeld, true,
                "m_criGlobal's lock word valid");
    gp.destroy(t);
    np.destroy(t);
}

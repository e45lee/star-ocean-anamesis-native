// Differential tests of the AudioSignalNotify natives (audio_signal.cpp): two private notifies built as
// SoundManager::Initialize builds them (vtable, the guest's FastCriticalSection constructor, empty
// slots), one driven through the guest functions (natives aren't installed in --selftest), the other
// through the native members, by the same random sequence of Add / Delete / GetSignalCount over a few
// fake voices; results and slots compared after every step, and the lock word / waiter count left free.
// Handler: the fake voices' vtable slot 10 is a fake function answered by a stub session, so both
// runs' voice calls (voice, slot) are logged and compared.
#include <cstring>
#include <string>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "native/audio/audio_layout.h"
#include "native/common/guest_stub.h"
#include "native/common/test.h"

using namespace soa;
using namespace soa::native;
using namespace soa::native::audio;

namespace {

constexpr int kVoices = 24;  // more than the slots: Add fails when full

struct Rig {
    TestContext& t;
    alignas(16) AudioSignalNotify guest_n, native_n;
    alignas(16) u64 vtable[16] = {};
    alignas(16) u64 voices[kVoices][4] = {};  // fake SLVoices: only the vtable pointer is read

    explicit Rig(TestContext& tc) : t(tc) {
        static const u64 fSignal = fake_function("audio.t.voice-signal", 2);
        vtable[AudioSignalNotify::kSlotVoiceAudioSignal] = fSignal;
        for (auto& v : voices) v[0] = (u64)vtable;
        for (AudioSignalNotify* n : {&guest_n, &native_n}) {
            std::memset(n, 0, sizeof *n);
            n->vtable = (const void*)(t.sym("_ZTVN4Aska17AudioSignalNotifyE") + 0x10);
            t.call("_ZN4Aska19FastCriticalSectionC1Ev", {(u64)&n->m_cs});
        }
    }
    ~Rig() {
        for (AudioSignalNotify* n : {&guest_n, &native_n}) t.call("_ZN4Aska19FastCriticalSectionD1Ev", {(u64)&n->m_cs});
    }
    SLVoice* voice(int i) { return reinterpret_cast<SLVoice*>(voices[i]); }
    int index_of(u64 p) const {
        for (int i = 0; i < kVoices; i++)
            if ((u64)voices[i] == p) return i;
        return -1;
    }
    bool same(const char* what) {
        bool ok = true;
        for (int i = 0; i < AudioSignalNotify::kSlots; i++)
            if (guest_n.m_voices[i] != native_n.m_voices[i]) {
                t.fail("%s: slot %d: guest voice %d native voice %d", what, i, index_of((u64)guest_n.m_voices[i]),
                       index_of((u64)native_n.m_voices[i]));
                ok = false;
            }
        for (AudioSignalNotify* n : {&guest_n, &native_n})
            if (n->m_cs.m_lock != FastCriticalSection::kFree || n->m_cs.m_waiters != FastCriticalSection::kWaiterBias) {
                t.fail("%s: %s lock left %d / %d", what, n == &guest_n ? "guest" : "native", n->m_cs.m_lock, n->m_cs.m_waiters);
                ok = false;
            }
        return ok;
    }
    // Handler on one side, its voice calls logged as "voice N slot S".
    std::vector<std::string> handler(bool native) {
        StubSession s;
        s.only.insert("audio.t.voice-signal");
        std::vector<std::string> log;
        s.behave["audio.t.voice-signal"] = [&](Cpu& c) {
            log.push_back("voice " + std::to_string(index_of(c.x(0))) + " slot " + std::to_string(c.x(1)));
            c.set_x(0, 0);
        };
        if (native) native_n.Handler(0x1234);
        else t.call("_ZN4Aska17AudioSignalNotify7HandlerEm", {(u64)&guest_n, 0x1234});
        return log;
    }
};

}  // namespace

NATIVE_TEST("audio/signal-notify") {
    Rig r(t);
    for (int step = 0; step < 600 && !t.failures(); step++) {
        int op = t.rand_int(0, 9);
        int vi = t.rand_int(0, kVoices - 1);
        SLVoice* v = t.rand_int(0, 15) == 0 ? nullptr : r.voice(vi);
        std::string what = "step " + std::to_string(step);
        if (op <= 4) {
            u64 g = t.call("_ZN4Aska17AudioSignalNotify18AddSignalVoiceListEPNS_7SLVoiceE", {(u64)&r.guest_n, (u64)v}) & 0xff;
            u64 n = r.native_n.AddSignalVoiceList(v);
            if (g != n) t.fail("%s Add: guest %llu native %llu", what.c_str(), (unsigned long long)g, (unsigned long long)n);
        } else if (op <= 7) {
            u64 g = t.call("_ZN4Aska17AudioSignalNotify21DeleteSignalVoiceListEPNS_7SLVoiceE", {(u64)&r.guest_n, (u64)v}) & 0xff;
            u64 n = r.native_n.DeleteSignalVoiceList(v);
            if (g != n) t.fail("%s Delete: guest %llu native %llu", what.c_str(), (unsigned long long)g, (unsigned long long)n);
        } else if (op == 8) {
            u32 g = (u32)t.call("_ZNK4Aska17AudioSignalNotify14GetSignalCountEv", {(u64)&r.guest_n});
            u32 n = r.native_n.GetSignalCount();
            if (g != n) t.fail("%s GetSignalCount: guest %u native %u", what.c_str(), g, n);
        } else {
            auto g = r.handler(false), n = r.handler(true);
            if (g != n) t.fail("%s Handler: guest %zu calls native %zu", what.c_str(), g.size(), n.size());
            for (size_t i = 0; i < g.size() && i < n.size(); i++)
                if (g[i] != n[i]) t.fail("%s Handler call %zu: guest %s native %s", what.c_str(), i, g[i].c_str(), n[i].c_str());
        }
        r.same(what.c_str());
    }
}

// A full notify: Add fails and leaves the slots alone; the count is 20; Handler calls all 20 in order.
NATIVE_TEST("audio/signal-notify-full") {
    Rig r(t);
    for (int i = 0; i < AudioSignalNotify::kSlots; i++) {
        t.call("_ZN4Aska17AudioSignalNotify18AddSignalVoiceListEPNS_7SLVoiceE", {(u64)&r.guest_n, (u64)r.voice(i)});
        r.native_n.AddSignalVoiceList(r.voice(i));
    }
    t.expect_eq(t.call("_ZN4Aska17AudioSignalNotify18AddSignalVoiceListEPNS_7SLVoiceE", {(u64)&r.guest_n, (u64)r.voice(21)}) & 0xff,
                (u64)r.native_n.AddSignalVoiceList(r.voice(21)), "Add to a full list");
    t.expect_eq((u32)t.call("_ZNK4Aska17AudioSignalNotify14GetSignalCountEv", {(u64)&r.guest_n}), r.native_n.GetSignalCount(), "count");
    t.expect_eq(r.native_n.GetSignalCount(), 20u, "count = 20");
    auto g = r.handler(false), n = r.handler(true);
    t.expect_eq(g, n, "Handler's calls");
    t.expect_eq(n.size(), (size_t)20, "20 calls");
    r.same("full");
}

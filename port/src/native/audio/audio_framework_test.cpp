// Differential tests of Framework::CSoundManager::PreProgress / PostProgress and CSound::CElement::
// PostProgress (audio_framework.cpp): two private managers (no parent time element: the Framework's
// dt; a real CMutex or none) over private element arrays (the Framework's TObjectContainer<CElement>
// vtable) whose elements are random mixes of free / active, watchdog on / off, watched or not, over
// fake sound objects (random type bits and finished flags; a fake vtable whose DeleteThis is logged).
// Aska::SoundManager::StopSound and FunctorAllPlayingElements are stubbed and logged. One manager runs
// the guest functions, the other the natives; the logs (objects by index), the elements and
// m_numPlaying must match.
#include <cstring>
#include <memory>
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

constexpr int kElements = 24, kObjects = 24;

struct Side {
    alignas(16) CSoundManager m;
    alignas(16) CElementContainer cont;
    alignas(16) CElement elems[kElements];
    alignas(16) SoundObject objs[kObjects];
    alignas(16) u8 mutex[sizeof(CMutex)];
};

struct Rig {
    TestContext& t;
    Side g, n;
    alignas(16) u64 obj_vtable[16] = {};
    bool with_mutex;

    Rig(TestContext& tc, bool mutex) : t(tc), with_mutex(mutex) {
        static const u64 fDelete = fake_function("audio.t.delete-this", 1);
        obj_vtable[SoundObject::kSlotDeleteThis] = fDelete;
        stub("_ZN4Aska12SoundManager9StopSoundEPNS_11SoundObjectEj", "audio.t.stop-sound", 3);
        stub("_ZN9Framework13CSoundManager25FunctorAllPlayingElementsERNS_9ICallbackE", "audio.t.functor", 2);
        const u64 invalid = *reinterpret_cast<const u64*>(t.sym("_ZN9Framework6CSound14iInvalidHandleE"));
        Side& a = g;
        std::memset(&a, 0, sizeof a);
        a.m.base.base.vtable = (const void*)(t.sym("_ZTVN9Framework13CSoundManagerE") + 0x10);
        a.m.base.m_rate = 1.0f;
        a.m.m_callPlayingElements = (u8)t.rand_int(0, 1);
        a.m.m_numPlaying = 77;
        a.cont.vtable = (const void*)(t.sym("_ZTVN9Framework16TObjectContainerINS_6CSound8CElementEEE") + 0x10);
        a.cont.m_count = kElements;
        for (int i = 0; i < kObjects; i++) {
            u8 raw[sizeof(SoundObject)];
            for (auto& b : raw) b = (u8)t.rand_int(0, 255);
            std::memcpy(&a.objs[i], raw, sizeof raw);
            a.objs[i].vtable = obj_vtable;
            a.objs[i].m_type = (u32)t.rand_int(0, 7);
            a.objs[i].m_flags1f2 = (u8)t.rand_int(0, 3);
        }
        for (int i = 0; i < kElements; i++) {
            u8 raw[sizeof(CElement)];
            for (auto& b : raw) b = (u8)t.rand_int(0, 255);
            std::memcpy(&a.elems[i], raw, sizeof raw);
            a.elems[i].vtable = (const void*)(t.sym("_ZTVN9Framework6CSound8CElementE") + 0x10);
            bool active = t.rand_int(0, 3) != 0;
            a.elems[i].m_handle = active ? (u64)t.rand_int(1, 1000) : invalid;
            a.elems[i].m_pAskaSoundObject = &a.objs[i];
            a.elems[i].m_keepPlayByWatchdog = (u8)t.rand_int(0, 1);
            a.elems[i].m_watched = (u8)t.rand_int(0, 1);
        }
        std::memcpy(&n, &g, sizeof g);
        // the pointers into each side's own arrays
        for (Side* s : {&g, &n}) {
            s->m.m_pElements = &s->cont;
            s->cont.m_elements = s->elems;
            for (int i = 0; i < kElements; i++) s->elems[i].m_pAskaSoundObject = &s->objs[i];
            if (with_mutex) {
                t.call("_ZN9Framework6CMutexC1Ev", {(u64)s->mutex});
                t.call("_ZN9Framework6CMutex10InitializeEv", {(u64)s->mutex});
                s->m.m_pMutex = reinterpret_cast<CMutex*>(s->mutex);
            } else {
                s->m.m_pMutex = nullptr;
            }
        }
    }
    ~Rig() {
        if (with_mutex)
            for (Side* s : {&g, &n}) t.call("_ZN9Framework6CMutex7ReleaseEv", {(u64)s->mutex});
    }
    std::string name(const Side& s, u64 p) const {
        for (int i = 0; i < kObjects; i++)
            if (p == (u64)&s.objs[i]) return "obj" + std::to_string(i);
        if (p == (u64)&s.m) return "manager";
        return "?";
    }
    std::vector<std::string> run(bool native, bool post) {
        Side& s = native ? n : g;
        StubSession ss;
        ss.only = {"audio.t.delete-this", "audio.t.stop-sound", "audio.t.functor"};
        std::vector<std::string> log;
        ss.behave["audio.t.delete-this"] = [&](Cpu& c) { log.push_back("DeleteThis " + name(s, c.x(0))); };
        ss.behave["audio.t.stop-sound"] = [&](Cpu& c) { log.push_back("StopSound " + name(s, c.x(1)) + " " + std::to_string(c.x(2) & 0xffffffff)); };
        ss.behave["audio.t.functor"] = [&](Cpu& c) { log.push_back("Functor " + name(s, c.x(0))); };
        if (native) {
            if (post) s.m.PostProgress();
            else s.m.PreProgress();
        } else {
            t.call(post ? "_ZN9Framework13CSoundManager12PostProgressEv" : "_ZN9Framework13CSoundManager11PreProgressEv", {(u64)&s.m});
        }
        return log;
    }
    void compare(const char* what) {
        for (int i = 0; i < kElements; i++) {
            CElement a = g.elems[i], b = n.elems[i];
            // (the object pointers by index)
            int ia = (int)(a.m_pAskaSoundObject ? a.m_pAskaSoundObject - g.objs : -1), ib = (int)(b.m_pAskaSoundObject ? b.m_pAskaSoundObject - n.objs : -1);
            a.m_pAskaSoundObject = b.m_pAskaSoundObject = nullptr;
            if (ia != ib || std::memcmp(&a, &b, sizeof a) != 0) t.fail("%s: element %d differs", what, i);
        }
        if (g.m.m_numPlaying != n.m.m_numPlaying) t.fail("%s: m_numPlaying guest %u native %u", what, g.m.m_numPlaying, n.m.m_numPlaying);
    }
};

}  // namespace

NATIVE_TEST("audio/framework-progress") {
    int stops = 0, deletes = 0, functors = 0;
    for (int round = 0; round < 40 && !t.failures(); round++) {
        auto rig = std::make_unique<Rig>(t, round % 2 == 0);
        Rig& r = *rig;
        for (int step = 0; step < 3; step++) {
            bool post = (step + round) % 2 == 1;
            auto lg = r.run(false, post), ln = r.run(true, post);
            for (auto& l : lg) stops += l.rfind("StopSound", 0) == 0, deletes += l.rfind("DeleteThis", 0) == 0, functors += l.rfind("Functor", 0) == 0;
            if (lg != ln) {
                t.fail("round %d %s: guest %zu calls native %zu", round, post ? "PostProgress" : "PreProgress", lg.size(), ln.size());
                for (size_t i = 0; i < lg.size() || i < ln.size(); i++)
                    t.fail("  %s | %s", i < lg.size() ? lg[i].c_str() : "-", i < ln.size() ? ln[i].c_str() : "-");
            }
            r.compare(post ? "PostProgress" : "PreProgress");
        }
    }
    if (!stops || !deletes || !functors) t.fail("the paths weren't all reached: %d stops, %d deletes, %d functor calls", stops, deletes, functors);
}

// CElement::PostProgress alone, on single elements.
NATIVE_TEST("audio/element-post-progress") {
    auto rig = std::make_unique<Rig>(t, false);
    Rig& r = *rig;
    for (int i = 0; i < kElements && !t.failures(); i++) {
        StubSession ss;
        ss.only = {"audio.t.delete-this", "audio.t.stop-sound"};
        std::vector<std::string> lg, ln;
        std::vector<std::string>* log = &lg;
        ss.behave["audio.t.delete-this"] = [&](Cpu& c) { log->push_back("DeleteThis " + std::to_string((c.x(0) == (u64)&r.g.objs[i]) || (c.x(0) == (u64)&r.n.objs[i]))); };
        ss.behave["audio.t.stop-sound"] = [&](Cpu& c) { log->push_back("StopSound " + std::to_string(c.x(2) & 0xffffffff)); };
        t.call("_ZN9Framework6CSound8CElement12PostProgressEf", GuestArgs().p(&r.g.elems[i]).f(0.016f));
        log = &ln;
        r.n.elems[i].PostProgress(0.016f);
        t.expect_eq(lg, ln, "CElement::PostProgress calls");
    }
    r.compare("CElement::PostProgress");
}

// Framework::CSoundManager::PreProgress / PostProgress and CSound::CElement::PostProgress
// (port/decomp/audio/framework.c; the layouts in audio_layout.h). The game thread's sound layer runs
// these each frame on its two CManageFiber fibers: PreProgress clears every active element's watchdog
// mark (CElement::PreProgress, inlined), PostProgress counts the active elements and lets each one
// release its Aska::SoundObject once that is finished, stopping the sounds whose owner stopped calling
// Watchdog(). Both walk the element array through its vtable (NumElements / rElement per element in
// the guest); here the array is read directly when it is the TObjectContainer<CElement> the
// Framework makes (else the vtable calls run as in the guest).
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#include "core/cpu.h"
#include "core/loader.h"
#include "native/audio/audio_check.h"
#include "native/audio/audio_layout.h"
#include "native/common/gen/common_addresses.h"
#include "native/common/guest_assert.h"
#include "native/common/guest_std.h"
#include "native/common/live_check.h"
#include "native/common/native_method.h"

namespace soa::native::audio {

namespace {

u64 at(u64 vaddr) { return main_lib()->base + vaddr; }
u64 invalid_handle() { return *reinterpret_cast<const u64*>(at(kInvalidHandle)); }

struct GuestFns {
    u64 container_vtable = guest::sym("_ZTVN9Framework16TObjectContainerINS_6CSound8CElementEEE") + 0x10;
    u64 time_dt = guest::sym("_ZNK9Framework12CTimeElement2DTEv");
    u64 framework_dt = guest::sym("_ZN9Framework21CTimeElementContainer11FrameworkDTEv");
    u64 stop_sound = guest::sym("_ZN4Aska12SoundManager9StopSoundEPNS_11SoundObjectEj");
    u64 sound_object_delete_this = guest::sym("_ZN4Aska11SoundObject10DeleteThisEv");
    u64 functor_all_playing = guest::sym("_ZN9Framework13CSoundManager25FunctorAllPlayingElementsERNS_9ICallbackE");
};
const GuestFns& fns() {
    static const GuestFns f;
    return f;
}

// The calls a checked run made (live check only; null otherwise), as "what object" pairs.
struct FrameworkObs {
    std::vector<std::pair<std::string, u64>> calls;
};
thread_local FrameworkObs* t_fobs = nullptr;

const u64* vtable_of(const void* obj) { return *reinterpret_cast<const u64* const*>(obj); }

// TObjectContainer<CElement>::NumElements / rElement as the guest calls them (vtable slots 4 / 5).
u64 num_elements(CElementContainer* c) {
    if ((u64)c->vtable == fns().container_vtable) {
        if (!c->m_elements) guest_assert(kStrObjectContainerH, 0x3e, kStrElementsNull);
        return c->m_count;
    }
    return guest_call(vtable_of(c)[CSoundManager::kSlotNumElements], {(u64)c});
}
CElement* element(CElementContainer* c, u64 i) {
    if ((u64)c->vtable == fns().container_vtable && c->m_elements && i < c->m_count) return &c->m_elements[i];
    return reinterpret_cast<CElement*>(guest_call(vtable_of(c)[CSoundManager::kSlotElement], {(u64)c, i}));
}

// The manager's dt: its own CTimeElement's when it has a parent, else the Framework's.
float manager_dt(const CSoundManager* m) {
    if (m->base.base.m_parent == nullptr) return guest_invoke<float>(fns().framework_dt);
    return guest_invoke<float>(fns().time_dt, (u64)m);
}

void lock(CMutex* m) {
    if (!m) return;
    if (!m->IsInitialized()) m->Initialize();
    m->Lock();
}

}  // namespace

bool CElement::IsActive() const { return m_handle != invalid_handle(); }

void CElement::PreProgress(float /*dt*/) { m_watched = 0; }

void CElement::PostProgress(float /*dt*/) {
    const u64 invalid = invalid_handle();
    if (m_handle == invalid) return;
    if (!m_pAskaSoundObject) guest_assert(kSoundCpp, 0x1eb, kStrAskaSoundObjectNull);
    // The watchdog: a sound kept only while its owner calls Watchdog() each frame.
    if (m_keepPlayByWatchdog && !m_watched && m_handle != invalid) {
        SoundObject* o = m_pAskaSoundObject;
        if (!(o->m_flags1f2 & SoundObject::kFlagFinished)) {
            if (!(o->m_type & SoundObject::kTypeSE) && !(o->m_type & SoundObject::kTypeBGM)) {
                guest_assert(kSoundCpp, 0x1b1, kStrIllegalSoundType);  // (and no StopSound)
            } else {
                u64 manager = *reinterpret_cast<const u64*>(guest::sym("_ZN4Aska6Global15m_pSoundManagerE"));
                if (t_fobs) t_fobs->calls.emplace_back("StopSound", (u64)o);
                guest_call(fns().stop_sound, {manager, (u64)o, 10});
            }
        }
        m_keepPlayByWatchdog = 0;
    }
    // A finished sound object goes back (its DeleteThis, vtable slot 7) and the element is free again.
    SoundObject* o = m_pAskaSoundObject;
    if (o->m_flags1f2 & SoundObject::kFlagFinished) {
        if (t_fobs) t_fobs->calls.emplace_back("DeleteThis", (u64)o);
        guest_call(vtable_of(o)[SoundObject::kSlotDeleteThis], {(u64)o});
        m_pAskaSoundObject = nullptr;
        m_handle = invalid_handle();
    }
}

void CSoundManager::PreProgress() {
    CMutex* mutex = m_pMutex;
    lock(mutex);
    if (!m_pElements) guest_assert(kSoundCpp, 0x2f6, kStrElementsNull);
    float dt = manager_dt(this);
    for (u64 i = 0; i < num_elements(m_pElements); i++) {
        CElement* e = element(m_pElements, i);
        if (e->IsActive()) e->PreProgress(dt);
    }
    if (mutex) mutex->Unlock();
}

void CSoundManager::PostProgress() {
    CMutex* mutex = m_pMutex;
    lock(mutex);
    if (!m_pElements) guest_assert(kSoundCpp, 0x305, kStrElementsNull);
    m_numPlaying = 0;
    float dt = manager_dt(this);
    for (u64 i = 0; i < num_elements(m_pElements); i++) {
        CElement* e = element(m_pElements, i);
        if (e->IsActive()) {
            e->PostProgress(dt);
            m_numPlaying++;
        }
    }
    if (mutex) mutex->Unlock();
    if (m_callPlayingElements) {
        // A stack ICallback (the guest's own local class: only its vtable).
        u64 callback = at(kPlayingElementsCallbackVtbl) + 0x10;
        if (t_fobs) t_fobs->calls.emplace_back("FunctorAllPlayingElements", (u64)this);
        guest_call(fns().functor_all_playing, {(u64)this, (u64)&callback});
    }
}

// ---- The live check (audio_check.h) ----
//
// The native for real (its StopSound / DeleteThis / FunctorAllPlayingElements calls logged), then the
// guest original on a shadow manager: the manager's bytes without its mutex (the guest then skips the
// lock), a shadow element array copied before the native ran, and shadow copies of the elements' sound
// objects (their flags as the native saw them); the three callees answered by the check's stubs on this
// thread. The calls (shadow objects mapped back), the elements and m_numPlaying must match. A sound
// object whose flags the sound thread changed during the native run makes it a race.

namespace {

CheckedFn g_pre("_ZN9Framework13CSoundManager11PreProgressEv"), g_post("_ZN9Framework13CSoundManager12PostProgressEv");

template <void (CSoundManager::*M)()>
void progress_checked(Cpu& c, CheckedFn& f) {
    if (!live::check_due(f)) return wrap_method<M>()(c);
    auto* self = reinterpret_cast<CSoundManager*>(c.x(0));
    CElementContainer* cont = self->m_pElements;
    if (!cont || (u64)cont->vtable != fns().container_vtable || !cont->m_elements || cont->m_count > 4096) {
        wrap_method<M>()(c);
        return live::check_result(f, live::Outcome::Skipped, "not the Framework's element array");
    }
    const GuestFns& g = fns();
    const char* stub_stop = live::ensure_stub(g.stop_sound);
    const char* stub_delete = live::ensure_stub(g.sound_object_delete_this);
    const char* stub_functor = live::ensure_stub(g.functor_all_playing);
    if (!stub_stop || !stub_delete || !stub_functor) {
        wrap_method<M>()(c);
        return live::check_result(f, live::Outcome::Skipped, "callees can't be stubbed");
    }
    live::CheckScope scope;
    const u64 n = cont->m_count;
    // Before: the elements and their sound objects.
    std::vector<CElement> pre(cont->m_elements, cont->m_elements + n);
    std::vector<SoundObject> objs;
    std::vector<u64> obj_real;
    for (const CElement& e : pre)
        if (e.IsActive() && e.m_pAskaSoundObject) {
            if ((u64)vtable_of(e.m_pAskaSoundObject)[SoundObject::kSlotDeleteThis] != g.sound_object_delete_this) {
                wrap_method<M>()(c);
                return live::check_result(f, live::Outcome::Skipped, "a sound object of another class");
            }
            obj_real.push_back((u64)e.m_pAskaSoundObject);
            objs.push_back(*e.m_pAskaSoundObject);
        }
    auto flags_of = [](const SoundObject& o) { return (u64)o.m_type << 8 | o.m_flags1f2; };
    // The native, for real.
    FrameworkObs native;
    t_fobs = &native;
    (self->*M)();
    t_fobs = nullptr;
    for (size_t k = 0; k < objs.size(); k++)
        if (flags_of(*reinterpret_cast<const SoundObject*>(obj_real[k])) != flags_of(objs[k]) &&
            std::find_if(native.calls.begin(), native.calls.end(), [&](auto& p) { return p.second == obj_real[k]; }) == native.calls.end())
            return live::check_result(f, live::Outcome::Race, "a sound object changed during the native run");
    // The shadow: manager, container, elements, sound objects.
    alignas(16) CSoundManager sh;
    std::memcpy(&sh, self, sizeof sh);
    alignas(16) CElementContainer sh_cont = *cont;
    std::vector<CElement> sh_elems = pre;
    for (CElement& e : sh_elems)
        for (size_t k = 0; k < objs.size(); k++)
            if ((u64)e.m_pAskaSoundObject == obj_real[k] && e.IsActive()) e.m_pAskaSoundObject = &objs[k];
    sh_cont.m_elements = sh_elems.data();
    sh.m_pElements = &sh_cont;
    sh.m_pMutex = nullptr;
    auto real_of = [&](u64 p) -> u64 {
        for (size_t k = 0; k < objs.size(); k++)
            if (p == (u64)&objs[k]) return obj_real[k];
        return p == (u64)&sh ? (u64)self : p;
    };
    std::vector<std::pair<std::string, u64>> guest_calls;
    {
        live::ReplaySession s;
        s.answer(stub_stop, [&](Cpu& cc) {
            guest_calls.emplace_back("StopSound", real_of(cc.x(1)));
            cc.set_x(0, 0);
        });
        s.answer(stub_delete, [&](Cpu& cc) {
            guest_calls.emplace_back("DeleteThis", real_of(cc.x(0)));
            cc.set_x(0, 0);
        });
        s.answer(stub_functor, [&](Cpu& cc) {
            guest_calls.emplace_back("FunctorAllPlayingElements", real_of(cc.x(0)));
            cc.set_x(0, 0);
        });
        live::drop_stale_code(g.stop_sound);
        live::drop_stale_code(g.sound_object_delete_this);
        live::drop_stale_code(g.functor_all_playing);
        guest_call(f.orig, {(u64)&sh});
    }
    std::string why;
    if (guest_calls != native.calls)
        why = "calls: native " + std::to_string(native.calls.size()) + " guest " + std::to_string(guest_calls.size());
    for (u64 i = 0; why.empty() && i < n; i++) {
        CElement a = cont->m_elements[i], b = sh_elems[i];
        b.m_pAskaSoundObject = reinterpret_cast<SoundObject*>(real_of((u64)b.m_pAskaSoundObject));
        if (std::memcmp(&a, &b, sizeof a) != 0) why = "element " + std::to_string(i) + ": " + live::diff_bytes((const u8*)&a, (const u8*)&b, 0, sizeof a);
    }
    if (why.empty() && sh.m_numPlaying != self->m_numPlaying)
        why = "m_numPlaying: native " + std::to_string(self->m_numPlaying) + " guest " + std::to_string(sh.m_numPlaying);
    live::check_result(f, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}
void pre_checked(Cpu& c) { progress_checked<&CSoundManager::PreProgress>(c, g_pre); }
void post_checked(Cpu& c) { progress_checked<&CSoundManager::PostProgress>(c, g_post); }

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN9Framework13CSoundManager11PreProgressEv", pre_checked, "audio: Framework::CSoundManager::PreProgress", &g_pre.orig);
NATIVE_FUNCTION_ORIG("_ZN9Framework13CSoundManager12PostProgressEv", post_checked, "audio: Framework::CSoundManager::PostProgress", &g_post.orig);
NATIVE_METHOD("_ZN9Framework6CSound8CElement12PostProgressEf", &CElement::PostProgress, "audio: Framework::CSound::CElement::PostProgress");

}  // namespace soa::native::audio

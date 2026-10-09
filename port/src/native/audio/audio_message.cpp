// The sound thread's mailboxes (port/decomp/audio/mixer.c, sound_manager.c; the layouts in
// audio_layout.h): Aska::TSoundDynamicQueue<T>, a growable ring, behind AudioPlayer::SendMessage /
// GetMessage (the sequencer's messages for the player) and SoundObject::RequestSet / RequestGet (requests
// for the object's AudioRun). Each takes its owner's FastCriticalSection (inlined in the guest: sync's
// Enter / Leave on the same words) around one push or pop. The guest's SendMessage calls
// TSoundDynamicQueue<AudioMessage>::AddEx (left to the guest: SendMessage was its only caller, and the
// live check's guest run needs it); RequestSet has its own inlined copy (the same code at a 0x10 stride).
//
// The live check (`--live-check audio`): the native for real, the queue captured under the lock before and
// after its change; then the guest original on a shadow owner holding a copy of the queue as it was (the
// lock free); result, out-parameter, the queue's fields and its slots compared. A push that grows the ring
// allocates through the game's sound memory: those are skipped here (the differential test covers them).
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "native/audio/audio_check.h"
#include "native/audio/audio_layout.h"
#include "native/common/guest_std.h"
#include "native/common/live_check.h"
#include "native/common/native_method.h"

namespace soa::native::audio {

namespace {

struct QueueFns {
    u64 malloc = guest::sym("_ZN4Aska11SoundMemory6MallocEm");
    u64 op_delete = guest::sym("_ZdlPv");
};
const QueueFns& fns() {
    static const QueueFns f;
    return f;
}

// A checked call's view of the queue, taken under the owner's lock (live check only; null otherwise).
struct QueueObs {
    static constexpr u32 kMaxItems = 4096;
    bool captured = false;
    u8 pre[0x20], post[0x20];       // the TSoundDynamicQueue before / after
    std::vector<u8> pre_items, post_items;
    bool grew = false;
};
thread_local QueueObs* t_qobs = nullptr;

template <typename T>
void snap(const TSoundDynamicQueue<T>& q, u8* head, std::vector<u8>& items) {
    std::memcpy(head, &q, sizeof q);
    if (q.m_items && q.m_capacity <= QueueObs::kMaxItems) items.assign((const u8*)q.m_items, (const u8*)(q.m_items + q.m_capacity));
}

}  // namespace

// ---- Aska::TSoundDynamicQueue<T> ----

template <typename T>
T* TSoundDynamicQueue<T>::AddEx() {
    u32 w = m_write;
    T* slot;
    if (m_read == w) {  // full: one slot more, the ring unrolled from m_write
        auto* grown = reinterpret_cast<T*>(guest_call(fns().malloc, {(u64)(u32)(m_capacity + 1) * sizeof(T)}));
        if (!grown) return nullptr;
        if (t_qobs) t_qobs->grew = true;
        std::memcpy(grown, m_items + m_write, (u64)(m_capacity - m_write) * sizeof(T));
        if (m_read) std::memcpy(grown + (u32)(m_capacity - m_write), m_items, (u64)m_read * sizeof(T));
        if (m_items) guest_call(fns().op_delete, {(u64)m_items});
        u32 cap = m_capacity;
        m_items = grown;
        m_read = 0;
        m_capacity = cap + 1;
        slot = grown + cap;
        w = 0;
    } else {
        slot = m_items + w;
        w = w + 1 < m_capacity ? w + 1 : 0;
    }
    m_write = w;
    return slot;
}

template <typename T>
bool TSoundDynamicQueue<T>::Get(T* out) {
    u32 next = m_read + 1 < m_capacity ? m_read + 1 : 0;
    if (next == m_write) return false;
    m_read = next;
    std::memcpy((void*)out, &m_items[next], sizeof(T));
    return true;
}

namespace {

// One push or pop under the owner's lock, captured for a check.
template <typename T, typename Op>
auto locked(FastCriticalSection& cs, TSoundDynamicQueue<T>& q, Op op) {
    cs.Enter();
    if (t_qobs) snap(q, t_qobs->pre, t_qobs->pre_items);
    auto r = op();
    if (t_qobs) {
        snap(q, t_qobs->post, t_qobs->post_items);
        t_qobs->captured = true;
    }
    cs.Leave();
    return r;
}

}  // namespace

// ---- Aska::AudioPlayer ----

bool AudioPlayer::SendMessage(u32 message, const void* a0, const void* a1) {
    return locked(m_messageCs, m_messages, [&] {
        AudioMessage* m = m_messages.AddEx();
        if (m) {
            m->m_arg0 = a0;
            m->m_arg1 = a1;
            m->m_message = message;
        }
        return m != nullptr;
    });
}

bool AudioPlayer::GetMessage(AudioMessage* out) {
    return locked(m_messageCs, m_messages, [&] { return m_messages.Get(out); });
}

// ---- Aska::SoundObject ----

bool SoundObject::RequestSet(u32 type, const void* data) {
    return locked(m_requestCs, m_requests, [&] {
        SoundRequest* r = m_requests.AddEx();
        if (r) {
            r->m_data = data;
            r->m_type = type;
        }
        return r != nullptr;
    });
}

bool SoundObject::RequestGet(SoundRequest* out) {
    return locked(m_requestCs, m_requests, [&] { return m_requests.Get(out); });
}

// ---- The live check (audio_check.h) ----

namespace {

CheckedFn g_send("_ZN4Aska11AudioPlayer11SendMessageEjPvS1_"), g_get("_ZN4Aska11AudioPlayer10GetMessageEPNS_12AudioMessageE"),
    g_rset("_ZN4Aska11SoundObject10RequestSetEjPKv"), g_rget("_ZN4Aska11SoundObject10RequestGetEPNS0_16RequestContainerE");

// The owner's shadow: zeroed but for the queue as the native found it (its slots a private copy) and a
// free lock. Owner is AudioPlayer or SoundObject; Q / CS the queue and lock members.
template <typename Owner, typename T>
struct ShadowOwner {
    alignas(16) Owner o;
    std::vector<u8> items;
    ShadowOwner(const QueueObs& obs, TSoundDynamicQueue<T> Owner::*q, FastCriticalSection Owner::*cs) : items(obs.pre_items) {
        std::memset((void*)&o, 0, sizeof o);
        std::memcpy((void*)&(o.*q), obs.pre, sizeof(TSoundDynamicQueue<T>));
        if (!items.empty()) (o.*q).m_items = reinterpret_cast<T*>(items.data());
        (o.*cs).m_lock = FastCriticalSection::kFree;
        (o.*cs).m_waiters = FastCriticalSection::kWaiterBias;
    }
};

// Runs `native` for real, then `guest` on the shadow; compares the results, `out` bytes and the queues.
template <typename Owner, typename T, typename Native, typename Guest>
void queue_check(CheckedFn& f, TSoundDynamicQueue<T> Owner::*q, FastCriticalSection Owner::*cs, Native native, Guest guest, const void* out_native,
                 const void* out_guest, size_t out_size) {
    live::CheckScope scope;
    QueueObs obs;
    t_qobs = &obs;
    bool rn = native();
    t_qobs = nullptr;
    if (!obs.captured) return live::check_result(f, live::Outcome::Skipped, "nothing captured");
    if (obs.grew) return live::check_result(f, live::Outcome::Skipped, "the ring grew (sound memory; the selftest covers it)");
    const auto* pre = reinterpret_cast<const TSoundDynamicQueue<T>*>(obs.pre);
    if (pre->m_items && (pre->m_capacity > QueueObs::kMaxItems || obs.pre_items.size() != pre->m_capacity * sizeof(T)))
        return live::check_result(f, live::Outcome::Skipped, "queue too large");
    if (!pre->m_items && pre->m_write != pre->m_read) return live::check_result(f, live::Outcome::Skipped, "no buffer");
    ShadowOwner<Owner, T> sh(obs, q, cs);
    bool rg = guest(&sh.o);
    std::string why;
    if (rn != rg) why = std::string("result: native ") + (rn ? "1" : "0") + " guest " + (rg ? "1" : "0");
    if (why.empty() && rn && out_size && std::memcmp(out_native, out_guest, out_size) != 0)
        why = "out: " + live::diff_bytes((const u8*)out_native, (const u8*)out_guest, 0, out_size);
    const TSoundDynamicQueue<T>& gq = sh.o.*q;
    const auto* post = reinterpret_cast<const TSoundDynamicQueue<T>*>(obs.post);
    if (why.empty() && (gq.m_write != post->m_write || gq.m_read != post->m_read || gq.m_capacity != post->m_capacity || gq.vtable != post->vtable))
        why = "queue: native w" + std::to_string(post->m_write) + " r" + std::to_string(post->m_read) + " c" + std::to_string(post->m_capacity) + " guest w" +
              std::to_string(gq.m_write) + " r" + std::to_string(gq.m_read) + " c" + std::to_string(gq.m_capacity);
    if (why.empty() && sh.items != obs.post_items) why = "slots: " + live::diff_bytes(obs.post_items.data(), sh.items.data(), 0, std::min(sh.items.size(), obs.post_items.size()));
    if (why.empty() && ((sh.o.*cs).m_lock != FastCriticalSection::kFree || (sh.o.*cs).m_waiters != FastCriticalSection::kWaiterBias))
        why = "the guest left the lock changed";
    live::check_result(f, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}

void send_checked(Cpu& c) {
    if (!live::check_due(g_send)) return wrap_method<&AudioPlayer::SendMessage>()(c);
    auto* self = reinterpret_cast<AudioPlayer*>(c.x(0));
    u32 message = (u32)c.x(1);
    u64 a0 = c.x(2), a1 = c.x(3);
    bool r = false;
    queue_check(
        g_send, &AudioPlayer::m_messages, &AudioPlayer::m_messageCs,
        [&] { return r = self->SendMessage(message, (const void*)a0, (const void*)a1); },
        [&](AudioPlayer* p) { return (guest_call(g_send.orig, {(u64)p, message, a0, a1}) & 0xff) != 0; }, nullptr, nullptr, 0);
    c.set_x(0, r);
}

void get_checked(Cpu& c) {
    if (!live::check_due(g_get)) return wrap_method<&AudioPlayer::GetMessage>()(c);
    auto* self = reinterpret_cast<AudioPlayer*>(c.x(0));
    auto* out = reinterpret_cast<AudioMessage*>(c.x(1));
    alignas(16) AudioMessage gout{};
    bool r = false;
    queue_check(
        g_get, &AudioPlayer::m_messages, &AudioPlayer::m_messageCs, [&] { return r = self->GetMessage(out); },
        [&](AudioPlayer* p) { return (guest_call(g_get.orig, {(u64)p, (u64)&gout}) & 0xff) != 0; }, out, &gout, sizeof gout);
    c.set_x(0, r);
}

void rset_checked(Cpu& c) {
    if (!live::check_due(g_rset)) return wrap_method<&SoundObject::RequestSet>()(c);
    auto* self = reinterpret_cast<SoundObject*>(c.x(0));
    u32 type = (u32)c.x(1);
    u64 data = c.x(2);
    bool r = false;
    queue_check(
        g_rset, &SoundObject::m_requests, &SoundObject::m_requestCs, [&] { return r = self->RequestSet(type, (const void*)data); },
        [&](SoundObject* o) { return (guest_call(g_rset.orig, {(u64)o, type, data}) & 0xffffffff) != 0; }, nullptr, nullptr, 0);
    c.set_x(0, r);
}

void rget_checked(Cpu& c) {
    if (!live::check_due(g_rget)) return wrap_method<&SoundObject::RequestGet>()(c);
    auto* self = reinterpret_cast<SoundObject*>(c.x(0));
    auto* out = reinterpret_cast<SoundRequest*>(c.x(1));
    alignas(16) SoundRequest gout{};
    bool r = false;
    queue_check(
        g_rget, &SoundObject::m_requests, &SoundObject::m_requestCs, [&] { return r = self->RequestGet(out); },
        [&](SoundObject* o) { return (guest_call(g_rget.orig, {(u64)o, (u64)&gout}) & 0xff) != 0; }, out, &gout, sizeof gout);
    c.set_x(0, r);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN4Aska11AudioPlayer11SendMessageEjPvS1_", send_checked, "audio: Aska::AudioPlayer::SendMessage", &g_send.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska11AudioPlayer10GetMessageEPNS_12AudioMessageE", get_checked, "audio: Aska::AudioPlayer::GetMessage", &g_get.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska11SoundObject10RequestSetEjPKv", rset_checked, "audio: Aska::SoundObject::RequestSet", &g_rset.orig);
NATIVE_FUNCTION_ORIG("_ZN4Aska11SoundObject10RequestGetEPNS0_16RequestContainerE", rget_checked, "audio: Aska::SoundObject::RequestGet", &g_rget.orig);

}  // namespace soa::native::audio

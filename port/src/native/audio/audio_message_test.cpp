// Differential tests of the mailbox natives (audio_message.cpp): two private AudioPlayers and two private
// SoundObjects (zeroed, the lock built by the guest's FastCriticalSection constructor, a ring of 2-6 slots
// from the game's sound memory as SEControlObject's constructor makes it: write 1, read 0), one driven
// through the guest functions (no natives in --selftest), the other through the native members, by the
// same random pushes and pops: SendMessage / GetMessage, RequestSet / RequestGet. The pushes outrun the
// pops now and then, so the rings fill and grow (SoundMemory::Malloc, operator delete: the game's, for
// real). After every step: the results, the popped bytes, the queues' fields and their slots must match.
#include <cstring>
#include <string>

#include "core/cpu.h"
#include "native/audio/audio_layout.h"
#include "native/common/test.h"

using namespace soa;
using namespace soa::native;
using namespace soa::native::audio;

namespace {

struct Side {
    alignas(16) AudioPlayer player;
    alignas(16) SoundObject object;
};

template <typename T>
void init_queue(TestContext& t, TSoundDynamicQueue<T>& q, const char* vtable, u32 cap) {
    q.vtable = (const void*)(t.sym(vtable) + 0x10);
    q.m_write = 1;
    q.m_read = 0;
    q.m_capacity = cap;
    q.m_items = reinterpret_cast<T*>(t.call("_ZN4Aska11SoundMemory6MallocEm", {(u64)cap * sizeof(T)}));
    std::memset((void*)q.m_items, 0xcd, (size_t)cap * sizeof(T));
}

// A slot's fields (not its padding: a grown ring's new slot has the allocator's leftovers there).
bool same(const AudioMessage& a, const AudioMessage& b) { return a.m_message == b.m_message && a.m_arg0 == b.m_arg0 && a.m_arg1 == b.m_arg1; }
bool same(const SoundRequest& a, const SoundRequest& b) { return a.m_type == b.m_type && a.m_data == b.m_data; }

template <typename T>
void compare_queues(TestContext& t, const std::string& what, const TSoundDynamicQueue<T>& g, const TSoundDynamicQueue<T>& n) {
    if (g.m_write != n.m_write || g.m_read != n.m_read || g.m_capacity != n.m_capacity || g.vtable != n.vtable) {
        t.fail("%s: queue guest w%u r%u c%u native w%u r%u c%u", what.c_str(), g.m_write, g.m_read, g.m_capacity, n.m_write, n.m_read, n.m_capacity);
        return;
    }
    for (u32 i = 0; i < g.m_capacity; i++)
        if (!same(g.m_items[i], n.m_items[i])) t.fail("%s: slot %u differs", what.c_str(), i);
}

}  // namespace

NATIVE_TEST("audio/mailboxes") {
    int grows = 0, empty_pops = 0, pops = 0;
    for (int round = 0; round < 40 && !t.failures(); round++) {
        Side g, n;
        u32 cap_m = (u32)t.rand_int(2, 6), cap_r = (u32)t.rand_int(2, 6);  // (write starts at 1: 2 slots at least)
        for (Side* s : {&g, &n}) {
            std::memset((void*)&s->player, 0, sizeof s->player);
            std::memset((void*)&s->object, 0, sizeof s->object);
            t.call("_ZN4Aska19FastCriticalSectionC1Ev", {(u64)&s->player.m_messageCs});
            t.call("_ZN4Aska19FastCriticalSectionC1Ev", {(u64)&s->object.m_requestCs});
            init_queue(t, s->player.m_messages, "_ZTVN4Aska18TSoundDynamicQueueINS_12AudioMessageEEE", cap_m);
            init_queue(t, s->object.m_requests, "_ZTVN4Aska18TSoundDynamicQueueINS_11SoundObject16RequestContainerEEE", cap_r);
        }
        int bias = t.rand_int(0, 2);  // 0: pops win, 1: even, 2: pushes win
        for (int step = 0; step < 120 && !t.failures(); step++) {
            std::string what = "round " + std::to_string(round) + " step " + std::to_string(step);
            int op = t.rand_int(0, 5 + bias);
            bool push = op >= 3;
            bool messages = t.rand_int(0, 1) == 0;
            u32 cap_before = messages ? g.player.m_messages.m_capacity : g.object.m_requests.m_capacity;
            if (messages && push) {
                u32 message = (u32)t.rand_int(0, 12);
                u64 a0 = t.rand_u64(), a1 = t.rand_u64();
                what += " SendMessage";
                u64 gr = t.call("_ZN4Aska11AudioPlayer11SendMessageEjPvS1_", {(u64)&g.player, message, a0, a1}) & 0xff;
                u64 nr = n.player.SendMessage(message, (const void*)a0, (const void*)a1);
                if (gr != nr) t.fail("%s: result guest %llu native %llu", what.c_str(), (unsigned long long)gr, (unsigned long long)nr);
            } else if (messages) {
                alignas(16) AudioMessage go, no;
                std::memset((void*)&go, 0xee, sizeof go);
                std::memset((void*)&no, 0xee, sizeof no);
                what += " GetMessage";
                u64 gr = t.call("_ZN4Aska11AudioPlayer10GetMessageEPNS_12AudioMessageE", {(u64)&g.player, (u64)&go}) & 0xff;
                u64 nr = n.player.GetMessage(&no);
                if (gr != nr) t.fail("%s: result guest %llu native %llu", what.c_str(), (unsigned long long)gr, (unsigned long long)nr);
                if (!same(go, no)) t.fail("%s: the message differs", what.c_str());
                (gr ? pops : empty_pops)++;
            } else if (push) {
                u32 type = (u32)t.rand_int(0, 20);
                u64 data = t.rand_u64();
                what += " RequestSet";
                u64 gr = t.call("_ZN4Aska11SoundObject10RequestSetEjPKv", {(u64)&g.object, type, data}) & 0xffffffff;
                u64 nr = n.object.RequestSet(type, (const void*)data);
                if (gr != nr) t.fail("%s: result guest %llu native %llu", what.c_str(), (unsigned long long)gr, (unsigned long long)nr);
            } else {
                alignas(16) SoundRequest go, no;
                std::memset((void*)&go, 0xee, sizeof go);
                std::memset((void*)&no, 0xee, sizeof no);
                what += " RequestGet";
                u64 gr = t.call("_ZN4Aska11SoundObject10RequestGetEPNS0_16RequestContainerE", {(u64)&g.object, (u64)&go}) & 0xff;
                u64 nr = n.object.RequestGet(&no);
                if (gr != nr) t.fail("%s: result guest %llu native %llu", what.c_str(), (unsigned long long)gr, (unsigned long long)nr);
                if (!same(go, no)) t.fail("%s: the request differs", what.c_str());
                (gr ? pops : empty_pops)++;
            }
            if ((messages ? g.player.m_messages.m_capacity : g.object.m_requests.m_capacity) != cap_before) grows++;
            compare_queues(t, what, g.player.m_messages, n.player.m_messages);
            compare_queues(t, what, g.object.m_requests, n.object.m_requests);
            for (Side* s : {&g, &n})
                if (s->player.m_messageCs.m_lock != FastCriticalSection::kFree || s->object.m_requestCs.m_lock != FastCriticalSection::kFree)
                    t.fail("%s: a lock left held", what.c_str());
        }
        for (Side* s : {&g, &n}) {
            t.call("_ZdlPv", {(u64)s->player.m_messages.m_items});
            t.call("_ZdlPv", {(u64)s->object.m_requests.m_items});
            t.call("_ZN4Aska19FastCriticalSectionD1Ev", {(u64)&s->player.m_messageCs});
            t.call("_ZN4Aska19FastCriticalSectionD1Ev", {(u64)&s->object.m_requestCs});
        }
    }
    if (grows < 20 || empty_pops < 20 || pops < 100) t.fail("too few paths reached: %d grows, %d empty pops, %d pops", grows, empty_pops, pops);
}

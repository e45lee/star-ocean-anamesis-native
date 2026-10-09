// Differential tests of resource_manager.cpp: private CResourceManagers (m_isInitialized set, a
// CMutex built and initialized by the guest, a std::list of tElements in nodes from the game's STL
// allocator) over fake elements (zeroed CResourceElements with a phase, a file number, a direct-file
// name). The read-only members run the guest original and the native on the same manager; Run runs on
// twin managers with CDelayDelete::AddTask stubbed (the fake elements must not reach the real delay
// queue) and compares the calls and the lists left. In --selftest natives aren't installed: t.call
// reaches the guest code.
#include <cstring>
#include <string>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/loader.h"
#include "native/common/guest_std.h"
#include "native/common/guest_stub.h"
#include "native/common/test.h"
#include "native/resource/resource_layout.h"

using namespace soa;
using namespace soa::native::resource;

namespace {

// Fake elements: only the fields the list walks read.
struct alignas(16) ElementStorage {
    u8 bytes[sizeof(CResourceElement)];
};
struct FakeElements {
    std::vector<CResourceElement*> e;
    std::vector<ElementStorage*> storage;
    void make(TestContext& t, int n, bool direct) {
        for (int i = 0; i < n; i++) {
            storage.push_back(new ElementStorage{});
            auto* p = reinterpret_cast<CResourceElement*>(storage.back()->bytes);
            p->m_phase = t.rand_int(0, 2) ? 9 : t.rand_int(0, 9);
            if (direct) {
                p->base.m_fileNumber = -2;
                p->base.m_isDirectOpened = 1;
                std::string name = "res/file" + std::to_string(i) + ".bin";  // short form (< 23 chars)
                auto* b = reinterpret_cast<u8*>(&p->base.m_directRelativeName);
                b[0] = (u8)(name.size() << 1);
                std::memcpy(b + 1, name.c_str(), name.size() + 1);
            } else {
                p->base.m_fileNumber = 1000 + i * 3;
            }
            e.push_back(p);
        }
    }
    ~FakeElements() {
        for (auto* p : storage) delete p;
    }
};

struct TestManager {
    alignas(16) u8 storage[sizeof(CResourceManager)];
    CResourceManager* m() { return reinterpret_cast<CResourceManager*>(storage); }
    void build(TestContext& t) {
        std::memset(storage, 0, sizeof storage);
        m()->m_isInitialized = 1;
        auto* s = m()->m_elements.sentinel();
        m()->m_elements.prev = m()->m_elements.next = s;
        t.call("_ZN9Framework6CMutexC1Ev", {(u64)&m()->m_mutex});
        t.call("_ZN9Framework6CMutex10InitializeEv", {(u64)&m()->m_mutex});
    }
    void push(CResourceElement* e, s32 refs, u32 flags) {
        auto* n = static_cast<ListNodeTElement*>(guest::stl_alloc(sizeof(ListNodeTElement)));
        n->value.m_referenceCounter = refs;
        n->value.m_uniqueBitFlag = flags;
        n->value.m_pResourceElement = e;
        auto* s = m()->m_elements.sentinel();
        n->prev = s->prev;
        n->next = s;
        s->prev->next = n;
        s->prev = n;
        m()->m_elements.size++;
    }
    void destroy(TestContext& t) {
        auto* s = m()->m_elements.sentinel();
        for (auto* n = s->next; n != s;) {
            auto* next = n->next;
            guest::stl_free(n);
            n = next;
        }
        t.call("_ZN9Framework6CMutex7ReleaseEv", {(u64)&m()->m_mutex});
    }
};

}  // namespace

NATIVE_TEST("resource/manager-searches") {
    for (int round = 0; round < 6; round++) {
        bool direct = round % 2 == 1;
        FakeElements fe;
        fe.make(t, round < 2 ? round * 3 : t.rand_int(1, 40), direct);
        static TestManager tm;
        tm.build(t);
        for (auto* e : fe.e) tm.push(e, t.rand_int(0, 2), (u32)t.rand_u64());
        CResourceManager* m = tm.m();
        u64 self = (u64)m;
        // counts
        t.expect_eq((s32)t.call("_ZNK9Framework16CResourceManager3NumEv", {self}), m->Num(), "Num");
        t.expect_eq((s32)t.call("_ZNK9Framework16CResourceManager10NumLoadingEv", {self}), m->NumLoading(), "NumLoading");
        t.expect_eq((u8)t.call("_ZNK9Framework16CResourceManager9IsLoadingEv", {self}), (u8)m->IsLoading(), "IsLoading");
        for (u32 flag : {1u, 0x80u, 0xffffffffu, (u32)t.rand_u64()})
            t.expect_eq((s32)t.call("_ZNK9Framework16CResourceManager18NumByUniqueBitFlagEj", {self, flag}), m->NumByUniqueBitFlag(flag), "NumByUniqueBitFlag");
        // NumLoading / IsLoading while the mutex is locked (they don't lock then)
        m->m_mutex.Lock();
        t.expect_eq((s32)t.call("_ZNK9Framework16CResourceManager10NumLoadingEv", {self}), m->NumLoading(), "NumLoading (locked)");
        t.expect_eq((u8)t.call("_ZNK9Framework16CResourceManager9IsLoadingEv", {self}), (u8)m->IsLoading(), "IsLoading (locked)");
        // searches (the caller holds the lock), hits and misses
        for (int k = 0; k < (int)fe.e.size() + 3; k++) {
            if (direct) {
                std::string path = "res/file" + std::to_string(k) + ".bin";
                const char* p = path.c_str();
                t.expect_eq(t.call("_ZN9Framework16CResourceManager19pSearchByDirectPathEPKc", {self, (u64)p}), (u64)m->pSearchByDirectPath(p), "pSearchByDirectPath");
                const CResourceManager* cm = m;
                t.expect_eq(t.call("_ZNK9Framework16CResourceManager19pSearchByDirectPathEPKc", {self, (u64)p}), (u64)cm->pSearchByDirectPath(p),
                            "pSearchByDirectPath const");
            } else {
                u32 num = 1000 + (u32)k * 3;
                t.expect_eq(t.call("_ZN9Framework16CResourceManager7pSearchEj", {self, num}), (u64)m->pSearch(num), "pSearch");
                const CResourceManager* cm = m;
                t.expect_eq(t.call("_ZNK9Framework16CResourceManager7pSearchEj", {self, num}), (u64)cm->pSearch(num), "pSearch const");
            }
        }
        m->m_mutex.Unlock();
        // IsReady / IsReadyDirectFile (they lock), with and without the out-parameter
        for (int k = 0; k < (int)fe.e.size() + 3; k++) {
            bool fg = true, fn = false;
            if (direct) {
                std::string path = "res/file" + std::to_string(k) + ".bin";
                u8 rg = (u8)t.call("_ZNK9Framework16CResourceManager17IsReadyDirectFileEPKcPb", {self, (u64)path.c_str(), (u64)&fg});
                bool rn = m->IsReadyDirectFile(path.c_str(), &fn);
                t.expect_eq(rg, (u8)rn, "IsReadyDirectFile");
                t.expect_eq(fg, fn, "IsReadyDirectFile found");
                t.expect_eq((u8)t.call("_ZNK9Framework16CResourceManager17IsReadyDirectFileEPKcPb", {self, (u64)path.c_str(), 0}),
                            (u8)m->IsReadyDirectFile(path.c_str(), nullptr), "IsReadyDirectFile (no out)");
            } else {
                u32 num = 1000 + (u32)k * 3;
                u8 rg = (u8)t.call("_ZNK9Framework16CResourceManager7IsReadyEjPb", {self, num, (u64)&fg});
                bool rn = m->IsReady(num, &fn);
                t.expect_eq(rg, (u8)rn, "IsReady");
                t.expect_eq(fg, fn, "IsReady found");
            }
        }
        t.expect_eq(m->m_mutex.m_lockCount, 0, "lock count back to 0");
        tm.destroy(t);
    }
}

NATIVE_TEST("resource/manager-run") {
    const u64 add_task = t.sym("_ZN9Framework12CDelayDelete7AddTaskERN4Aska4TaskE");
    if (!native::stub_isolated_at(add_task, "rm:AddTask", 1)) {
        t.fail("CDelayDelete::AddTask can't be stubbed");
        return;
    }
    std::string name = native::stub_name(add_task);
    for (int round = 0; round < 12; round++) {
        FakeElements fe;
        fe.make(t, round == 0 ? 0 : t.rand_int(1, 30), round % 2 == 1);
        static TestManager ga, na;
        ga.build(t);
        na.build(t);
        for (auto* e : fe.e) {
            s32 refs = t.rand_int(0, 3) ? 0 : t.rand_int(1, 2);
            u32 flags = (u32)t.rand_u64();
            ga.push(e, refs, flags);
            na.push(e, refs, flags);
        }
        std::vector<std::string> glog, nlog;
        {
            native::StubSession s;
            s.only = {name};
            t.call("_ZN9Framework16CResourceManager3RunEi", {(u64)ga.m(), 0});
            glog = s.log;
        }
        {
            native::StubSession s;
            s.only = {name};
            na.m()->Run(0);
            nlog = s.log;
        }
        if (!t.expect_eq(glog == nlog, true, "Run: the AddTask calls")) t.fail("guest %zu calls, native %zu", glog.size(), nlog.size());
        t.expect_eq(na.m()->m_elements.size, ga.m()->m_elements.size, "Run: list size");
        auto* gs = ga.m()->m_elements.sentinel();
        auto* ns = na.m()->m_elements.sentinel();
        auto* g = gs->next;
        auto* n = ns->next;
        for (; g != gs && n != ns; g = g->next, n = n->next)
            if (std::memcmp(&g->value, &n->value, sizeof(tElement)) != 0) {
                t.fail("Run: the elements left differ");
                break;
            }
        t.expect_eq(g == gs && n == ns, true, "Run: the same number of nodes left");
        t.expect_eq(na.m()->m_mutex.m_lockCount, 0, "Run: unlocked");
        ga.destroy(t);
        na.destroy(t);
    }
}

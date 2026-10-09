// Framework::CResourceManager's list walks and Run (port/decomp/resource/resource_manager.c,
// file_loader.c), on the classes of resource_layout.h and sync's CMutex.
//
// The manager is an Aska::Task holding a std::list of tElement handles (refcount, flags, the
// CResourceElement) under its Framework::CMutex. Run (every frame) hands the elements that are loaded
// and no longer referenced to CDelayDelete and frees their list nodes; IsReady / IsReadyDirectFile
// (polled by loaders every frame), the counts and the searches walk the list. The guest inlines
// tElement::crResourceElement / rResourceElement (their null asserts, at different lines),
// CResourceElement::IsDone (m_phase == 9) and CFileLoader::FileNumber into these, and calls the
// CMutex members and CFileLoader::pFileName.
#include <cstring>
#include <string>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "soaruntime/core/loader.h"
#include "native/common/guest_assert.h"
#include "native/common/guest_std.h"
#include "native/common/live_check.h"
#include "native/common/native_method.h"
#include "native/resource/resource_check.h"
#include "native/resource/resource_layout.h"
#include "native/common/gen/common_addresses.h"
#include "native/resource/gen/resource_addresses.h"

namespace soa::native::resource {

namespace {

// ResourceManager.cpp's / FileLoader.cpp's assert strings: resource/addresses.txt, common's
// kStrUninitializedObject.

void rm_assert(int line, u64 message) { guest_assert(kResourceManagerCpp, line, message); }

constexpr s32 kPhaseDone = 9;

}  // namespace

// ---- the leaves the guest inlines ----

CResourceElement* tElement::rResourceElement() {
    if (!m_pResourceElement) rm_assert(0x7e, kElementNull);
    return m_pResourceElement;
}

const CResourceElement* tElement::crResourceElement() const {
    if (!m_pResourceElement) rm_assert(0x84, kElementNull);
    return m_pResourceElement;
}

bool CResourceElement::IsDone() const { return m_phase == kPhaseDone; }
s32 CFileLoader::FileNumber() const { return m_fileNumber; }

const char* CFileLoader::pFileName() const {
    if (m_fileNumber == -1) guest_assert(kFileLoaderCpp, 0x22e, kStrUninitializedObject);
    if (m_isDirectOpened) return m_directRelativeName.data();
    static const u64 gp_file_name = guest::sym("_ZN9Framework6FileID10gpFileNameEj");
    return reinterpret_cast<const char*>(guest_call(gp_file_name, {(u64)(u32)m_fileNumber}));
}

// ---- searches (the caller holds m_mutex) ----

tElement* CResourceManager::pSearch(u32 fileNumber) {
    if (!m_isInitialized) rm_assert(0x10a, kNotInitialized);
    for (auto* n = m_elements.next; n != m_elements.sentinel(); n = n->next)
        if ((u32)n->value.rResourceElement()->base.FileNumber() == fileNumber) return &n->value;
    return nullptr;
}

const tElement* CResourceManager::pSearch(u32 fileNumber) const {
    if (!m_isInitialized) rm_assert(0xfc, kNotInitialized);
    auto* end = const_cast<libcxx::list<tElement>&>(m_elements).sentinel();
    for (auto* n = m_elements.next; n != end; n = n->next)
        if ((u32)n->value.crResourceElement()->base.FileNumber() == fileNumber) return &n->value;
    return nullptr;
}

tElement* CResourceManager::pSearchByDirectPath(const char* path) {
    if (!m_isInitialized) rm_assert(300, kNotInitialized);
    for (auto* n = m_elements.next; n != m_elements.sentinel(); n = n->next)
        if (std::strcmp(n->value.rResourceElement()->base.pFileName(), path) == 0) return &n->value;
    return nullptr;
}

const tElement* CResourceManager::pSearchByDirectPath(const char* path) const {
    if (!m_isInitialized) rm_assert(0x11c, kNotInitialized);
    auto* end = const_cast<libcxx::list<tElement>&>(m_elements).sentinel();
    for (auto* n = m_elements.next; n != end; n = n->next)
        if (std::strcmp(n->value.crResourceElement()->base.pFileName(), path) == 0) return &n->value;
    return nullptr;
}

// ---- under the manager's own lock ----

namespace {
// The guest's lock / unlock of a const member: Initialize on first use, then Lock.
CMutex& lock_of(const CResourceManager* m) {
    auto& mx = const_cast<CMutex&>(m->m_mutex);
    if (!mx.IsInitialized()) mx.Initialize();
    mx.Lock();
    return mx;
}
}  // namespace

bool CResourceManager::IsReady(u32 fileNumber, bool* found) const {
    if (!m_isInitialized) rm_assert(0x251, kNotInitialized);
    CMutex& mx = lock_of(this);
    const tElement* e = pSearch(fileNumber);
    if (found) *found = e != nullptr;
    bool ready = e ? e->crResourceElement()->IsDone() : false;
    mx.Unlock();
    return ready;
}

bool CResourceManager::IsReadyDirectFile(const char* path, bool* found) const {
    if (!m_isInitialized) rm_assert(0x263, kNotInitialized);
    CMutex& mx = lock_of(this);
    const tElement* e = pSearchByDirectPath(path);
    if (found) *found = e != nullptr;
    bool ready = e ? e->crResourceElement()->IsDone() : false;
    mx.Unlock();
    return ready;
}

s32 CResourceManager::Num() const {
    if (!m_isInitialized) rm_assert(0x306, kNotInitialized);
    CMutex& mx = lock_of(this);
    s32 n = (s32)m_elements.size;
    mx.Unlock();
    return n;
}

s32 CResourceManager::NumByUniqueBitFlag(u32 flag) const {
    if (!m_isInitialized) rm_assert(0x312, kNotInitialized);
    CMutex& mx = lock_of(this);
    s32 n = 0;
    auto* end = const_cast<libcxx::list<tElement>&>(m_elements).sentinel();
    for (auto* e = m_elements.next; e != end; e = e->next)
        if (e->value.m_uniqueBitFlag & flag) n++;
    mx.Unlock();
    return n;
}

// NumLoading / IsLoading lock only when the mutex isn't locked (by anyone: CMutex::IsLocked is the
// m_locked flag, not "locked by this thread"), as the guest does.
s32 CResourceManager::NumLoading() const {
    if (!m_isInitialized) rm_assert(0x2cd, kNotInitialized);
    auto& mx = const_cast<CMutex&>(m_mutex);
    bool was_locked = mx.IsLocked();
    if (!was_locked) mx.Lock();
    s32 n = 0;
    auto* end = const_cast<libcxx::list<tElement>&>(m_elements).sentinel();
    for (auto* e = m_elements.next; e != end; e = e->next)
        if (!e->value.crResourceElement()->IsDone()) n++;
    if (!was_locked) mx.Unlock();
    return n;
}

bool CResourceManager::IsLoading() const {
    if (!m_isInitialized) rm_assert(0x2e6, kNotInitialized);
    auto& mx = const_cast<CMutex&>(m_mutex);
    bool was_locked = mx.IsLocked();
    if (!was_locked) mx.Lock();
    bool loading = false;
    auto* end = const_cast<libcxx::list<tElement>&>(m_elements).sentinel();
    for (auto* e = m_elements.next; e != end; e = e->next) {
        if (!e->value.crResourceElement()->IsDone()) {
            loading = true;
            break;
        }
    }
    if (!was_locked) mx.Unlock();
    return loading;
}

// ---- Run: the done, unreferenced elements to CDelayDelete ----

namespace {
// Set by Run's check: the calls the native run made (what the guest's stubs record on the shadow).
struct RunLog {
    std::vector<u64> add_task;  // CDelayDelete::AddTask's Task&
    std::vector<u64> freed;     // the list nodes given back to the STL allocator
};
thread_local RunLog* t_run_log = nullptr;

void delay_delete(kernel::Task* task) {
    static const u64 add_task = guest::sym("_ZN9Framework12CDelayDelete7AddTaskERN4Aska4TaskE");
    if (t_run_log) t_run_log->add_task.push_back((u64)task);
    guest_call(add_task, {(u64)task});
}
void free_node(void* node) {
    if (t_run_log) t_run_log->freed.push_back((u64)node);
    guest::stl_free(node);
}
}  // namespace

void CResourceManager::Run(s32) {
    if (!m_isInitialized) rm_assert(0xd5, kNotInitialized);
    if (!m_mutex.IsInitialized()) m_mutex.Initialize();
    m_mutex.Lock();
    auto* end = m_elements.sentinel();
    for (auto* n = m_elements.next; n != end;) {
        tElement& e = n->value;
        if (!(e.rResourceElement()->IsDone() && e.m_referenceCounter == 0)) {
            n = n->next;
            continue;
        }
        delay_delete(&e.m_pResourceElement->m_task);
        auto* next = n->next;
        e.m_pResourceElement = nullptr;
        e.m_referenceCounter = 0;
        n->prev->next = next;
        next->prev = n->prev;
        m_elements.size--;
        free_node(n);
        n = next;
    }
    m_mutex.Unlock();
}

// ---- bindings and live checks (resource_check.h) ----

namespace {

CheckedFn g_run("_ZN9Framework16CResourceManager3RunEi"), g_is_ready("_ZNK9Framework16CResourceManager7IsReadyEjPb"),
    g_is_ready_direct("_ZNK9Framework16CResourceManager17IsReadyDirectFileEPKcPb"), g_num("_ZNK9Framework16CResourceManager3NumEv"),
    g_num_flag("_ZNK9Framework16CResourceManager18NumByUniqueBitFlagEj"), g_num_loading("_ZNK9Framework16CResourceManager10NumLoadingEv"),
    g_is_loading("_ZNK9Framework16CResourceManager9IsLoadingEv"), g_search("_ZN9Framework16CResourceManager7pSearchEj"),
    g_search_c("_ZNK9Framework16CResourceManager7pSearchEj"), g_search_path("_ZN9Framework16CResourceManager19pSearchByDirectPathEPKc"),
    g_search_path_c("_ZNK9Framework16CResourceManager19pSearchByDirectPathEPKc");

using SearchFn = tElement* (CResourceManager::*)(u32);
using SearchFnC = const tElement* (CResourceManager::*)(u32) const;
using SearchPathFn = tElement* (CResourceManager::*)(const char*);
using SearchPathFnC = const tElement* (CResourceManager::*)(const char*) const;
constexpr SearchFn kSearch = &CResourceManager::pSearch;
constexpr SearchFnC kSearchC = &CResourceManager::pSearch;
constexpr SearchPathFn kSearchPath = &CResourceManager::pSearchByDirectPath;
constexpr SearchPathFnC kSearchPathC = &CResourceManager::pSearchByDirectPath;

template <auto M>
void getter(Cpu& c, CheckedFn& f, u64 mask, int out_reg = -1, size_t out_bytes = 0) {
    if (!live::check_due(f)) return wrap_method<M>()(c);
    live::check_getter(c, f, wrap_method<M>(), mask, out_reg, out_bytes);
}
void is_ready_checked(Cpu& c) { getter<&CResourceManager::IsReady>(c, g_is_ready, 0xff, 2, 1); }
void is_ready_direct_checked(Cpu& c) { getter<&CResourceManager::IsReadyDirectFile>(c, g_is_ready_direct, 0xff, 2, 1); }
void num_checked(Cpu& c) { getter<&CResourceManager::Num>(c, g_num, 0xffffffffu); }
void num_flag_checked(Cpu& c) { getter<&CResourceManager::NumByUniqueBitFlag>(c, g_num_flag, 0xffffffffu); }
void num_loading_checked(Cpu& c) { getter<&CResourceManager::NumLoading>(c, g_num_loading, 0xffffffffu); }
void is_loading_checked(Cpu& c) { getter<&CResourceManager::IsLoading>(c, g_is_loading, 0xff); }
void search_checked(Cpu& c) { getter<kSearch>(c, g_search, ~0ull); }
void search_c_checked(Cpu& c) { getter<kSearchC>(c, g_search_c, ~0ull); }
void search_path_checked(Cpu& c) { getter<kSearchPath>(c, g_search_path, ~0ull); }
void search_path_c_checked(Cpu& c) { getter<kSearchPathC>(c, g_search_path_c, ~0ull); }

// Run, under the manager's own (recursive) lock for the whole check, so no other thread sees or
// changes the list in between: the native for real (its CDelayDelete::AddTask and node frees
// logged), then the guest original on a shadow manager whose list is a copy of the list as it was
// (the same tElements, so the same elements), with AddTask and the allocator's Free answered by the
// check's stubs on this thread (live_check.h's stub registry). The calls, in order, and the list
// left behind must match.
void run_checked(Cpu& c) {
    if (!live::check_due(g_run)) return wrap_method<&CResourceManager::Run>()(c);
    auto* self = reinterpret_cast<CResourceManager*>(c.x(0));
    if (!self->m_isInitialized || !self->m_mutex.IsInitialized()) {
        wrap_method<&CResourceManager::Run>()(c);
        return live::check_result(g_run, live::Outcome::Skipped, "not initialized yet");
    }
    live::CheckScope scope;
    static const u64 add_task = guest::sym("_ZN9Framework12CDelayDelete7AddTaskERN4Aska4TaskE");
    static const u64 stl_free = guest::sym("_ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv");
    const char* add_task_stub = live::ensure_stub(add_task);
    const char* free_stub = live::ensure_stub(stl_free);
    if (!add_task_stub || !free_stub) {
        wrap_method<&CResourceManager::Run>()(c);
        return live::check_result(g_run, live::Outcome::Skipped, "callees can't be stubbed");
    }
    self->m_mutex.Lock();
    // The state before: the manager's bytes and the list.
    alignas(16) u8 pre[sizeof(CResourceManager)];
    std::memcpy(pre, self, sizeof pre);
    std::vector<ListNodeTElement*> before;
    for (auto* n = self->m_elements.next; n != self->m_elements.sentinel(); n = n->next) before.push_back(n);
    std::vector<ListNodeTElement> nodes(before.size());  // the shadow's nodes (host memory: identity-mapped)
    for (size_t i = 0; i < before.size(); i++) nodes[i] = *before[i];
    // The native, for real.
    RunLog native;
    t_run_log = &native;
    wrap_method<&CResourceManager::Run>()(c);
    t_run_log = nullptr;
    std::vector<ListNodeTElement*> after;
    for (auto* n = self->m_elements.next; n != self->m_elements.sentinel(); n = n->next) after.push_back(n);
    // The shadow: the manager as it was, its list relinked over the copied nodes; its mutex a copy of
    // the real one, held by this thread (the guest's Lock / Unlock on it only count).
    alignas(16) u8 shadow_bytes[sizeof(CResourceManager)];
    std::memcpy(shadow_bytes, pre, sizeof shadow_bytes);
    auto* sh = reinterpret_cast<CResourceManager*>(shadow_bytes);
    auto* sent = sh->m_elements.sentinel();
    ListNodeTElement* prev = sent;
    for (auto& n : nodes) {
        n.prev = prev;
        prev->next = &n;
        prev = &n;
    }
    prev->next = sent;
    sent->prev = prev;
    RunLog guest;
    {
        live::ReplaySession s;
        s.answer(add_task_stub, [&](Cpu& cc) {
            guest.add_task.push_back(cc.x(0));
            cc.set_x(0, 0);
        });
        s.answer(free_stub, [&](Cpu& cc) {
            guest.freed.push_back(cc.x(0));
            cc.set_x(0, 0);
        });
        live::drop_stale_code(add_task);
        live::drop_stale_code(stl_free);
        guest_call(g_run.orig, {(u64)sh, c.x(1)});
    }
    self->m_mutex.Unlock();
    // Compare: the calls, the nodes freed (by index), the list left (by index, its values), the size.
    auto index_of_real = [&](u64 a) -> long {
        for (size_t i = 0; i < before.size(); i++)
            if ((u64)before[i] == a) return (long)i;
        return -1;
    };
    auto index_of_shadow = [&](u64 a) -> long {
        for (size_t i = 0; i < nodes.size(); i++)
            if ((u64)&nodes[i] == a) return (long)i;
        return -1;
    };
    std::string why;
    if (native.add_task != guest.add_task)
        why = "AddTask calls: native " + std::to_string(native.add_task.size()) + " guest " + std::to_string(guest.add_task.size());
    if (why.empty()) {
        if (native.freed.size() != guest.freed.size()) why = "frees: native " + std::to_string(native.freed.size()) + " guest " + std::to_string(guest.freed.size());
        for (size_t i = 0; why.empty() && i < native.freed.size(); i++)
            if (index_of_real(native.freed[i]) != index_of_shadow(guest.freed[i]) || index_of_real(native.freed[i]) < 0) why = "freed node " + std::to_string(i) + " differs";
    }
    if (why.empty() && sh->m_elements.size != self->m_elements.size) why = "list size differs";
    if (why.empty()) {
        size_t k = 0;
        for (auto* n = sh->m_elements.next; why.empty() && n != sent; n = n->next, k++) {
            long i = index_of_shadow((u64)n);
            if (k >= after.size() || i < 0 || before[i] != after[k]) why = "the list left differs at " + std::to_string(k);
            else if (std::memcmp(&n->value, &after[k]->value, sizeof(tElement)) != 0) why = "tElement " + std::to_string(k) + " differs";
        }
        if (why.empty() && k != after.size()) why = "the list left is longer in the native run";
    }
    if (why.empty()) why = live::diff_bytes((const u8*)self, shadow_bytes, 0, offsetof(CResourceManager, m_elements));
    live::check_result(g_run, why.empty() ? live::Outcome::Ok : live::Outcome::Mismatch, why);
}

}  // namespace

NATIVE_FUNCTION_ORIG("_ZN9Framework16CResourceManager3RunEi", run_checked, "resource: Framework::CResourceManager::Run (sync's CMutex)", &g_run.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework16CResourceManager7IsReadyEjPb", is_ready_checked, "resource: Framework::CResourceManager::IsReady", &g_is_ready.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework16CResourceManager17IsReadyDirectFileEPKcPb", is_ready_direct_checked,
                     "resource: Framework::CResourceManager::IsReadyDirectFile", &g_is_ready_direct.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework16CResourceManager3NumEv", num_checked, "resource: Framework::CResourceManager::Num", &g_num.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework16CResourceManager18NumByUniqueBitFlagEj", num_flag_checked, "resource: Framework::CResourceManager::NumByUniqueBitFlag",
                     &g_num_flag.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework16CResourceManager10NumLoadingEv", num_loading_checked, "resource: Framework::CResourceManager::NumLoading",
                     &g_num_loading.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework16CResourceManager9IsLoadingEv", is_loading_checked, "resource: Framework::CResourceManager::IsLoading", &g_is_loading.orig);
NATIVE_FUNCTION_ORIG("_ZN9Framework16CResourceManager7pSearchEj", search_checked, "resource: Framework::CResourceManager::pSearch", &g_search.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework16CResourceManager7pSearchEj", search_c_checked, "resource: Framework::CResourceManager::pSearch const", &g_search_c.orig);
NATIVE_FUNCTION_ORIG("_ZN9Framework16CResourceManager19pSearchByDirectPathEPKc", search_path_checked, "resource: Framework::CResourceManager::pSearchByDirectPath",
                     &g_search_path.orig);
NATIVE_FUNCTION_ORIG("_ZNK9Framework16CResourceManager19pSearchByDirectPathEPKc", search_path_c_checked,
                     "resource: Framework::CResourceManager::pSearchByDirectPath const", &g_search_path_c.orig);

}  // namespace soa::native::resource

// The table natives' live check (master_simple.h SimpleCheck; family `master`, master_family.h): a copy
// of the table as it was (its three maps copied node for node, the elements shared through their
// control blocks; the connector shared: its Open / Close are RETs, its queries read the database) is
// made first; the native runs on the table, the original (the hook's trampoline) on the copy; then
// results and caches are compared (master_compare.h: the padding and the pointers into each run's own
// elements aside). Out-parameters (a map, an element) get the same treatment. The copy is freed after.
// Initialize: the copy's new connector is deleted afterwards; the destructor runs on a copy without
// the connector (the table's own is deleted once, by the native).
#include <cstring>
#include <string>
#include <vector>

#include "native/master/master_compare.h"
#include "native/master/master_simple.h"

namespace soa::native::master {

namespace {

using live::RunBothFamily;
using This = CMasterParameterSimple;

// A copy of a table (in host memory the guest can address).
struct TableCopy {
    const ElementInfo& I;
    alignas(16) u8 bytes[sizeof(This) + 0x60] = {};
    This* t() { return reinterpret_cast<This*>(bytes); }
    TableCopy(const ElementInfo& el, const This* from) : I(el) {
        std::memcpy(bytes, from, sizeof(This));
        clone_map(I, t()->m_all, from->m_all, true);
        clone_map(I, t()->m_cache, from->m_cache, true);
        clone_map(I, t()->m_queryCache, from->m_queryCache, true);
    }
    ~TableCopy() {
        free_map(I, t()->m_all, true);
        free_map(I, t()->m_cache, true);
        free_map(I, t()->m_queryCache, true);
    }
};

std::string cmp_tables(const ElementInfo& I, This* n, This* g) {
    if ((n->base.m_pConnector != nullptr) != (g->base.m_pConnector != nullptr)) return "connector";
    if (n->base.vtable != g->base.vtable || n->parameter.vtable != g->parameter.vtable) return "vtables";
    if (n->m_cacheLimit != g->m_cacheLimit || n->m_queryLimit != g->m_queryLimit) return "limits";
    std::string why;
    if (!(why = cmp_map(I, n->m_all, g->m_all, true)).empty()) return "m_all: " + why;
    if (!(why = cmp_map(I, n->m_cache, g->m_cache, true)).empty()) return "m_cache: " + why;
    if (!(why = cmp_map(I, n->m_queryCache, g->m_queryCache, true)).empty()) return "m_queryCache: " + why;
    return {};
}

std::string cmp_result(const ElementInfo& I, const SharedPtr& n, const SharedPtr& g) {
    if ((n.ctrl == nullptr) != (g.ctrl == nullptr)) return "result's control block";
    std::string why = cmp_element(I, n.ptr, g.ptr);
    return why.empty() ? why : "result: " + why;
}

void release(SharedPtr& p) {
    if (p.ctrl) p.ctrl->__release_shared();
    p = {};
}

void done(Fn& f, const std::string& why) { fam().result(f, why.empty() ? Outcome::Ok : Outcome::Mismatch, why); }

}  // namespace

SimpleRole simple_role(const char* s) {
    static const char* const kNames[] = {"pParameterFromHash", "ParameterByQuery", "ParameterByQueryMap", "MakeCacheKey",
                                         "InsertCustomizeCache", "ClearCache", "SetStoreAllCacheSize", "Initialize", "Dtor",
                                         "Deserialize", "ReleaseParameter", "DeserializeParameter", "DeserializeMsgPack"};
    for (int i = 0; i < (int)SimpleRole::kCount; i++)
        if (!std::strcmp(s, kNames[i])) return (SimpleRole)i;
    return SimpleRole::kCount;
}

void SimpleCheck::pParameterFromHash(const TableInfo& T, Fn& f, This* self, SharedPtr* out, u32 hash) {
    RunBothFamily::Scope scope;
    TableCopy copy(*T.el, self);
    SimpleCode::pParameterFromHash(T, self, out, hash);
    SharedPtr g{};
    u64 regs[2] = {(u64)copy.t(), hash};
    guest_call_raw(f.orig, regs, 2, nullptr, 0, (u64)&g);
    std::string why = cmp_result(*T.el, *out, g);
    if (why.empty()) why = cmp_tables(*T.el, self, copy.t());
    release(g);
    done(f, why);
}

void SimpleCheck::ParameterByQuery(const TableInfo& T, Fn& f, This* self, SharedPtr* out, const char* sql, void* params, u32 n) {
    RunBothFamily::Scope scope;
    TableCopy copy(*T.el, self);
    SimpleCode::ParameterByQuery(T, self, out, sql, params, n);
    SharedPtr g{};
    u64 regs[4] = {(u64)copy.t(), (u64)sql, (u64)params, n};
    guest_call_raw(f.orig, regs, 4, nullptr, 0, (u64)&g);
    std::string why = cmp_result(*T.el, *out, g);
    if (why.empty()) why = cmp_tables(*T.el, self, copy.t());
    release(g);
    done(f, why);
}

void SimpleCheck::ParameterByQueryMap(const TableInfo& T, Fn& f, This* self, const char* sql, U32Map* out, void* params, u32 n) {
    RunBothFamily::Scope scope;
    TableCopy copy(*T.el, self);
    U32Map gout;
    clone_map(*T.el, gout, *out, false);
    SimpleCode::ParameterByQueryMap(T, self, sql, out, params, n);
    guest_call(f.orig, {(u64)copy.t(), (u64)sql, (u64)&gout, (u64)params, n});
    std::string why = cmp_map(*T.el, *out, gout, false);
    if (!why.empty()) why = "out: " + why;
    else why = cmp_tables(*T.el, self, copy.t());
    free_map(*T.el, gout, false);
    done(f, why);
}

u32 SimpleCheck::MakeCacheKey(Fn& f, This* self, const char* sql, void* params, u32 n) {
    RunBothFamily::Scope scope;
    u32 a = SimpleCode::MakeCacheKey(sql, params, n);
    u32 b = (u32)guest_call(f.orig, {(u64)self, (u64)sql, (u64)params, n});
    char m[64];
    snprintf(m, sizeof m, "native %#x guest %#x", a, b);
    done(f, a == b ? "" : m);
    return a;
}

void SimpleCheck::InsertCustomizeCache(const TableInfo& T, Fn& f, This* self, u32 key, const SharedPtr* p) {
    RunBothFamily::Scope scope;
    TableCopy copy(*T.el, self);
    SimpleCode::InsertCustomizeCache(self, key, p);
    guest_call(f.orig, {(u64)copy.t(), key, (u64)p});
    done(f, cmp_tables(*T.el, self, copy.t()));
}

void SimpleCheck::Plain(const TableInfo& T, Fn& f, This* self, SimpleRole r) {
    RunBothFamily::Scope scope;
    TableCopy copy(*T.el, self);
    if (r == SimpleRole::Initialize || r == SimpleRole::Dtor) copy.t()->base.m_pConnector = nullptr;
    switch (r) {
        case SimpleRole::ClearCache: SimpleCode::ClearCache(self); break;
        case SimpleRole::SetStoreAllCacheSize: SimpleCode::SetStoreAllCacheSize(T, self); break;
        case SimpleRole::Initialize: SimpleCode::Initialize(self); break;
        case SimpleRole::Dtor: SimpleCode::Dtor(T, self); break;
        default: break;
    }
    guest_call(f.orig, {(u64)copy.t()});
    std::string why;
    if (r == SimpleRole::Dtor) {
        // (both deleted their maps: the copy's are gone, nothing left for ~TableCopy but empty heads)
        if (self->base.vtable != copy.t()->base.vtable || self->parameter.vtable != copy.t()->parameter.vtable) why = "vtables";
        for (U32Map* m : {&self->m_all, &self->m_cache, &self->m_queryCache})
            if (m->buckets) why = "a map's buckets left";
        for (U32Map* m : {&copy.t()->m_all, &copy.t()->m_cache, &copy.t()->m_queryCache}) *m = {};
        if (self->base.m_pConnector) why = "connector left";
    } else {
        why = cmp_tables(*T.el, self, copy.t());
        if (r == SimpleRole::Initialize && copy.t()->base.m_pConnector) {
            void* c = copy.t()->base.m_pConnector;
            guest_call(reinterpret_cast<const u64*>(*reinterpret_cast<u64*>(c))[kConnDtorDelete], {(u64)c});
            copy.t()->base.m_pConnector = nullptr;
        }
    }
    done(f, why);
}

bool SimpleCheck::Deserialize(const TableInfo& T, Fn& f, This* self, const data_formats::AMap* map) {
    RunBothFamily::Scope scope;
    TableCopy copy(*T.el, self);
    bool a = SimpleCode::Deserialize(self, map);
    bool b = guest_call(f.orig, {(u64)copy.t(), (u64)map}) & 1;
    std::string why = a != b ? "result" : cmp_tables(*T.el, self, copy.t());
    done(f, why);
    return a;
}

bool SimpleCheck::ReleaseParameter(const TableInfo& T, Fn& f, This* self, const char* name) {
    RunBothFamily::Scope scope;
    TableCopy copy(*T.el, self);
    bool a = SimpleCode::ReleaseParameter(self, name);
    bool b = guest_call(f.orig, {(u64)copy.t(), (u64)name}) & 1;
    std::string why = a != b ? "result" : cmp_tables(*T.el, self, copy.t());
    done(f, why);
    return a;
}

bool SimpleCheck::DeserializeParameter(const TableInfo& T, Fn& f, This* self, U32Map* map, const data_formats::AArray* array) {
    RunBothFamily::Scope scope;
    // (the map is usually the table's own m_all: then the copy's)
    TableCopy copy(*T.el, self);
    U32Map gmap;
    U32Map* gm = map == &self->m_all ? &copy.t()->m_all : &gmap;
    if (gm == &gmap) clone_map(*T.el, gmap, *map, true);
    bool a = SimpleCode::DeserializeParameter(T, self, map, array);
    bool b = guest_call(f.orig, {(u64)copy.t(), (u64)gm, (u64)array}) & 1;
    std::string why = a != b ? "result" : cmp_map(*T.el, *map, *gm, true);
    if (why.empty()) why = cmp_tables(*T.el, self, copy.t());
    if (gm == &gmap) free_map(*T.el, gmap, true);
    done(f, why);
    return a;
}

void SimpleCheck::DeserializeMsgPack(const TableInfo& T, Fn& f, This* self, const TSharedArray* data, const s64* size, u8* single,
                                     U32Map* map) {
    RunBothFamily::Scope scope;
    const ElementInfo& I = *T.el;
    std::vector<u64> gsingle;
    U32Map gmap;
    if (single) {
        gsingle.resize((I.size + 7) / 8);
        ElementCode::CtorCopy(I, reinterpret_cast<u8*>(gsingle.data()), single);
    }
    if (map) clone_map(I, gmap, *map, false);
    SimpleCode::DeserializeMsgPack(T, &self->base, data, size, single, map);
    guest_call(f.orig, {(u64)self, (u64)data, (u64)size, single ? (u64)gsingle.data() : 0, map ? (u64)&gmap : 0});
    std::string why;
    if (single) why = cmp_element(I, single, reinterpret_cast<u8*>(gsingle.data()));
    if (why.empty() && map) why = cmp_map(I, *map, gmap, false);
    if (single) ElementCode::Dtor(I, reinterpret_cast<u8*>(gsingle.data()));
    if (map) free_map(I, gmap, false);
    done(f, why);
}

}  // namespace soa::native::master

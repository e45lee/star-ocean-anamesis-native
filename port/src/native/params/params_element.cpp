// CParameterElementBase and CParameterBase (params_layout.h; port/decomp/params/base.c): an element's
// properties deserialized from one ASON map, the property list, a parameter part's root map.
#include <algorithm>
#include <cstring>
#include <vector>

#include "soaruntime/core/thread_record.h"
#include "native/common/native.h"
#include "native/common/native_method.h"
#include "native/hash/hash_layout.h"
#include "native/params/params_check.h"
#include "native/params/params_corpus.h"
#include "native/params/params_guest.h"
#include "native/params/params_parser.h"
#include "native/params/params_property.h"

namespace soa::native::params {

namespace {

// One property of the list as the fast walk sees it.
struct Prop {
    IParameterProperty* p;
    u32 name;
    PropertyDeserialize deserialize;
};

// The list, when every property is a bound instantiation and the list ends (no self link: see
// AddProperty); false otherwise (then the literal walk, as the guest's).
bool Collect(IParameterProperty* first, std::vector<Prop>& out) {
    for (IParameterProperty* p = first; p; p = p->m_next) {
        PropertyDeserialize fn = KnownProperty(p->vtable);
        if (!fn || p->m_next == p || out.size() > 0x10000) return false;
        out.push_back({p, NameOf(p), fn});
    }
    return true;
}

void Call(IParameterProperty* p, const AMap* map, PropertyDeserialize fn) {
    if (t_trace) t_trace->push_back({p, map});
    if (fn) fn(p, map);
    else CallDeserialize(p, map);
}

}  // namespace

// For each pair whose key is a string with its C string (kind 5), the first property whose NameHash()
// equals CHash32(key) gets Deserialize(map) (the whole map: the property looks its own key up again).
// The guest hashes the key once per pair and calls NameHash on every property before the match; here
// the keys are hashed once (KeyHashes, also lent to the properties' GetParserValue lookups) and the
// names read once per call: the same calls in the same order, since a bound property's Deserialize
// changes neither the list nor the names. Any other list (a property that isn't a bound instantiation,
// or the self link) gets the guest's walk literally: NameHash and Deserialize through the vtable, per
// pair (a self-linked list then spins on a key no property has, as the guest does).
bool CParameterElementBase::Deserialize(const AMap* map) {
    if (!map) g::Assert(g::kParameterBaseCpp, 0x1e, g::kApParserIsNull);
    KeyHashes keys(map);
    struct PropsTag;
    std::vector<Prop>& props_buf = thread_object<std::vector<Prop>, PropsTag>();  // (core/thread_record.h)
    std::vector<Prop> props;
    props.swap(props_buf);  // (a nested element's Deserialize gets an empty one)
    props.clear();
    if (Collect(m_first, props)) {
        if (props.size() <= 16) {
            for (u32 i = 0; i < map->m_count; i++) {
                if (!keys.named(i)) continue;
                u32 h = keys.hash(i);
                for (const Prop& q : props)
                    if (q.name == h) {
                        Call(q.p, map, q.deserialize);
                        break;
                    }
            }
        } else {
            // (a long list: the first property of each name by a sorted index)
            struct IndexTag;
            auto& index_buf = thread_object<std::vector<std::pair<u32, u32>>, IndexTag>();
            std::vector<std::pair<u32, u32>> index;
            index.swap(index_buf);
            index.clear();
            for (u32 j = 0; j < props.size(); j++) index.push_back({props[j].name, j});
            std::sort(index.begin(), index.end());
            for (u32 i = 0; i < map->m_count; i++) {
                if (!keys.named(i)) continue;
                auto it = std::lower_bound(index.begin(), index.end(), std::pair<u32, u32>{keys.hash(i), 0});
                if (it != index.end() && it->first == keys.hash(i)) Call(props[it->second].p, map, props[it->second].deserialize);
            }
            index.swap(index_buf);
        }
    } else {
        for (u32 i = 0; i < map->m_count; i++) {
            if (!keys.named(i)) continue;
            u32 h = keys.hash(i);
            for (IParameterProperty* p = m_first; p; p = p->m_next)
                if (CallNameHash(p) == h) {
                    Call(p, map, KnownProperty(p->vtable));
                    break;
                }
        }
    }
    props.swap(props_buf);
    return true;
}

// Appends p at the end of the list, unless it is found on the way. The walk compares every property
// but the last, so adding the last one again links it to itself (README.md "AddProperty quirk"), and
// adding any other one to a self-linked list spins: both kept.
void CParameterElementBase::AddProperty(IParameterProperty* p) {
    IParameterProperty** slot = &m_first;
    IParameterProperty* cur = m_first;
    if (cur) {
        for (;;) {
            slot = &cur->m_next;
            if (!*slot) break;
            bool found = cur == p;
            cur = *slot;
            if (found) return;
        }
    }
    *slot = p;
}

const AValue* CParameterBase::pGetRoot(const AMap* map) const {
    if (!map) g::Assert(g::kParameterBaseCpp, 0x70, g::kApParserIsNull);
    const char* name = (const char*)guest_call(((const u64*)vtable)[kSlotParseName], {(u64)this});
    return g::AMapGet(map, name);
}

bool CParameterBase::Find(const AMap* map) {
    if (!map) g::Assert(g::kParameterBaseCpp, 100, g::kApParserIsNull);
    const char* name = (const char*)guest_call(((const u64*)vtable)[kSlotParseName], {(u64)this});
    return g::AMapGet(map, name) != nullptr;
}

// ---- binding, with the live checks ----

namespace {

#define ELEMENT_DESERIALIZE "_ZN21CParameterElementBase11DeserializeEPKN4Aska4ASON6AValue4AMapE"
#define ELEMENT_ADDPROPERTY "_ZN21CParameterElementBase11AddPropertyEP18IParameterProperty"
#define BASE_GETROOT "_ZNK14CParameterBase8pGetRootEPKN4Aska4ASON6AValue4AMapE"
#define BASE_FIND "_ZN14CParameterBase4FindEPKN4Aska4ASON6AValue4AMapE"

Fn fDeserialize(fam(), ELEMENT_DESERIALIZE);
Fn fAddProperty(fam(), ELEMENT_ADDPROPERTY);
Fn fGetRoot(fam(), BASE_GETROOT);
Fn fFind(fam(), BASE_FIND);

// Deserialize: the native's property calls (t_trace) against the original's (t_record: the bound
// properties' natives note the call instead of deserializing). Only for a list of bound properties
// without the self link (else the original would run unbound code twice, or spin).
bool CheckedDeserialize(CParameterElementBase* e, const AMap* map) {
    if (corpus_on()) corpus_record(e, map);
    if (__builtin_expect(!fam().due(fDeserialize), 1)) return e->Deserialize(map);
    live::RunBothFamily::Scope scope;
    std::vector<Prop> props;
    if (!map || !Collect(e->m_first, props)) {
        fam().result(fDeserialize, Outcome::Skipped, "a property that isn't bound, or a self-linked list");
        return e->Deserialize(map);
    }
    std::vector<PropertyCall> native, guest;
    t_trace = &native;
    e->Deserialize(map);
    t_trace = nullptr;
    t_record = &guest;
    u64 rg = guest_call(fDeserialize.orig, {(u64)e, (u64)map}) & 0xff;
    t_record = nullptr;
    std::string why;
    if (native != guest || rg != 1) {
        char m[160];
        size_t k = 0;
        while (k < native.size() && k < guest.size() && native[k] == guest[k]) k++;
        snprintf(m, sizeof m, "%zu calls native, %zu guest, first difference at %zu (native %p, guest %p), guest result %llu", native.size(),
                 guest.size(), k, k < native.size() ? native[k].property : nullptr, k < guest.size() ? guest[k].property : nullptr,
                 (unsigned long long)rg);
        why = m;
    }
    fam().result(fDeserialize, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
    return true;
}
void HostDeserialize(Cpu& c) { c.set_x(0, CheckedDeserialize((CParameterElementBase*)c.x(0), (const AMap*)c.x(1))); }
NATIVE_FUNCTION_ORIG(ELEMENT_DESERIALIZE, HostDeserialize, "params: CParameterElementBase::Deserialize", &fDeserialize.orig);

// AddProperty: the original on a private copy of the chain ({vtable, m_next} per node, p's own copy
// when it isn't in the list), the slot each run wrote compared.
void CheckedAddProperty(CParameterElementBase* e, IParameterProperty* p) {
    if (__builtin_expect(!fam().due(fAddProperty), 1)) return e->AddProperty(p);
    live::RunBothFamily::Scope scope;
    std::vector<IParameterProperty*> chain;
    for (IParameterProperty* q = e->m_first; q; q = q->m_next) {
        if (q->m_next == q || chain.size() > 0x10000) {
            fam().result(fAddProperty, Outcome::Skipped, "a self-linked list");
            return e->AddProperty(p);
        }
        chain.push_back(q);
    }
    size_t n = chain.size();
    size_t pi = std::find(chain.begin(), chain.end(), p) - chain.begin();  // n: not in the list
    std::vector<IParameterProperty> shadow(n + 1);
    for (size_t k = 0; k < n; k++) shadow[k] = {chain[k]->vtable, k + 1 < n ? &shadow[k + 1] : nullptr};
    shadow[n] = {p ? p->vtable : nullptr, nullptr};
    alignas(16) CParameterElementBase se{e->vtable, n ? &shadow[0] : nullptr};
    IParameterProperty* sp = !p ? nullptr : pi < n ? &shadow[pi] : &shadow[n];
    guest_call(fAddProperty.orig, {(u64)&se, (u64)sp});
    // which slot the original wrote (m_first, a node's m_next) and what (as a chain index)
    auto index_of = [&](IParameterProperty* q) -> long { return q ? (long)(q - &shadow[0]) : -1; };
    long g_first = index_of(se.m_first);
    std::vector<long> g_next(n);
    for (size_t k = 0; k < n; k++) g_next[k] = index_of(shadow[k].m_next);
    e->AddProperty(p);
    auto real_index = [&](IParameterProperty* q) -> long {
        if (!q) return -1;
        if (q == p) return pi < n ? (long)pi : (long)n;
        return (long)(std::find(chain.begin(), chain.end(), q) - chain.begin());
    };
    std::string why;
    if (real_index(e->m_first) != g_first) why = "m_first";
    for (size_t k = 0; k < n && why.empty(); k++)
        if (real_index(chain[k]->m_next) != g_next[k]) why = "m_next of property " + std::to_string(k);
    fam().result(fAddProperty, why.empty() ? Outcome::Ok : Outcome::Mismatch, why);
}
void HostAddProperty(Cpu& c) { CheckedAddProperty((CParameterElementBase*)c.x(0), (IParameterProperty*)c.x(1)); }
NATIVE_FUNCTION_ORIG(ELEMENT_ADDPROPERTY, HostAddProperty, "params: CParameterElementBase::AddProperty", &fAddProperty.orig);

void HostGetRoot(Cpu& c) {
    const CParameterBase* b = (const CParameterBase*)c.x(0);
    const AMap* map = (const AMap*)c.x(1);
    if (fam().due(fGetRoot)) {
        c.set_x(0, check_pure(fGetRoot, [&] { return Regs{(u64)b->pGetRoot(map), 0}; }, {(u64)b, (u64)map}, false).x0);
        return;
    }
    c.set_x(0, (u64)b->pGetRoot(map));
}
NATIVE_FUNCTION_ORIG(BASE_GETROOT, HostGetRoot, "params: CParameterBase::pGetRoot", &fGetRoot.orig);
void HostFind(Cpu& c) {
    CParameterBase* b = (CParameterBase*)c.x(0);
    const AMap* map = (const AMap*)c.x(1);
    if (fam().due(fFind)) {
        Regs r = check_pure(fFind, [&] { return Regs{(u64)b->Find(map), 0}; }, {(u64)b, (u64)map}, false);
        c.set_x(0, r.x0 & 0xff);
        return;
    }
    c.set_x(0, b->Find(map));
}
NATIVE_FUNCTION_ORIG(BASE_FIND, HostFind, "params: CParameterBase::Find", &fFind.orig);

}  // namespace

// For the tests: the checked entries as the guest calls them.
bool ElementDeserializeEntry(CParameterElementBase* e, const AMap* map) { return CheckedDeserialize(e, map); }

}  // namespace soa::native::params

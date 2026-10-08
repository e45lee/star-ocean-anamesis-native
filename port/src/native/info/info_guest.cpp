// The guest functions the info natives call (info_guest.h).
#include "native/info/info_guest.h"

#include <string>

#include "native/common/gen/common_addresses.h"
#include "native/common/guest_std.h"
#include "native/info/gen/info_addresses.h"

namespace soa::native::info::g {

u64 sym(const char* mangled) { return guest::sym(mangled); }

void Assert(u64 file_vaddr, int line, u64 msg_vaddr) {
    static const u64 f = sym("_ZN9Framework9gDoAssertEPKciS1_z");
    guest_call(f, {at(file_vaddr), (u64)(u32)line, at(msg_vaddr)});
}

u64 vcall(const void* obj, u32 slot, std::initializer_list<u64> rest) {
    u64 a[8] = {(u64)obj};
    size_t n = 1;
    for (u64 v : rest) a[n++] = v;
    return guest_call_raw(slot_of(obj, slot), a, n, nullptr, 0, 0).x0;
}

void* StringAllocate(u64 n) {
    static const u64 f = sym("_ZN9Framework37CAssignedMemoryManagerForSTLAllocator8AllocateEmPKcj");
    return reinterpret_cast<void*>(guest_call(f, {n, at(native::kStrStlStringH), 0x1c}));
}

void* VectorAllocate(u64 bytes) {
    static const u64 f = sym("_ZN9Framework37CAssignedMemoryManagerForSTLAllocator8AllocateEmPKcj");
    return reinterpret_cast<void*>(guest_call(f, {bytes, at(kStlVectorH), 0x20}));
}

u64 call(u64 fn, std::initializer_list<u64> args) { return guest_call(fn, args); }

void StlFree(void* p) {
    static const u64 f = sym("_ZN9Framework37CAssignedMemoryManagerForSTLAllocator4FreeEPv");
    guest_call(f, {reinterpret_cast<u64>(p)});
}

namespace {
constexpr const char* kPropTree =
    "_ZNSt6__ndk16__treeINS_12__value_typeIjP18IParameterPropertyEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13"
    "CSTLAllocatorIS4_NS9_19CSTLMapAllocatorInfEEEE";
constexpr const char* kChildTree =
    "_ZNSt6__ndk16__treeINS_12__value_typeIjP8InfoBaseEENS_19__map_value_compareIjS4_NS_4lessIjEELb1EEEN9Framework13CSTLAllocatorIS4_"
    "NS9_19CSTLMapAllocatorInfEEEE";
u64 tree_sym(const char* tree, const char* tail) { return sym((std::string(tree) + tail).c_str()); }
}  // namespace

void EmplaceProperty(PropertyMap* m, u32 key, void* property) {
    static const u64 f = tree_sym(kPropTree,
                                  "25__emplace_unique_key_argsIjJjRS3_EEENS_4pairINS_15__tree_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEbEERKT_"
                                  "DpOT0_");
    u32 k = key;
    void* v = property;
    guest_call(f, {reinterpret_cast<u64>(m), reinterpret_cast<u64>(&k), reinterpret_cast<u64>(&k), reinterpret_cast<u64>(&v)});
}

void EmplaceChild(PropertyMap* m, const void* hash, void* child) {
    static const u64 f = tree_sym(kChildTree,
                                  "21__emplace_unique_implIJNS9_7CHash32ERS3_EEENS_4pairINS_15__tree_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEbE"
                                  "EDpOT_");
    void* v = child;
    guest_call(f, {reinterpret_cast<u64>(m), reinterpret_cast<u64>(hash), reinterpret_cast<u64>(&v)});
}

void DestroyPropertyTree(PropertyMap* m) {
    static const u64 f = tree_sym(kPropTree, "7destroyEPNS_11__tree_nodeIS4_PvEE");
    guest_call(f, {reinterpret_cast<u64>(m), reinterpret_cast<u64>(m->root)});
}

void DestroyChildTree(PropertyMap* m) {
    static const u64 f = tree_sym(kChildTree, "7destroyEPNS_11__tree_nodeIS4_PvEE");
    guest_call(f, {reinterpret_cast<u64>(m), reinterpret_cast<u64>(m->root)});
}

void CopyPropertyMap(PropertyMap* m, const PropertyMap* src) {
    static const u64 f = sym("_ZN9Framework7CSTLMapIjP18IParameterPropertyEC2ERKS3_");
    guest_call(f, {reinterpret_cast<u64>(m), reinterpret_cast<u64>(src)});
}

void CopyChildMap(PropertyMap* m, const PropertyMap* src) {
    static const u64 f = sym("_ZN9Framework7CSTLMapIjP8InfoBaseEC2ERKS3_");
    guest_call(f, {reinterpret_cast<u64>(m), reinterpret_cast<u64>(src)});
}

namespace {
constexpr const char* kAssignMulti = "14__assign_multiINS_21__tree_const_iteratorIS4_PNS_11__tree_nodeIS4_PvEElEEEEvT_SL_";
void assign_multi(u64 f, PropertyMap* m, const PropertyMap* src) {
    guest_call(f, {reinterpret_cast<u64>(m), reinterpret_cast<u64>(src->begin_node), reinterpret_cast<u64>(&src->root)});
}
}  // namespace

void AssignPropertyMap(PropertyMap* m, const PropertyMap* src) {
    static const u64 f = tree_sym(kPropTree, kAssignMulti);
    assign_multi(f, m, src);
}

void AssignChildMap(PropertyMap* m, const PropertyMap* src) {
    static const u64 f = tree_sym(kChildTree, kAssignMulti);
    assign_multi(f, m, src);
}

}  // namespace soa::native::info::g

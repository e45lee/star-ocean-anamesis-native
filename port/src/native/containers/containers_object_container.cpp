// Framework::TObjectContainer<T>'s accessors: NumElements / rElement / crElement of the executed
// instantiations (port/decomp/containers/object_container.c, port/decomp/memory/stl_allocator.c).
//
// The class is memory_layout.h's (memory's scope.txt claims Framework::TObjectContainer: the base of
// CFixedLengthAllocatorContainer); its accessors are bound here, by the containers code agent, as
// the hottest container code (the profile's 4 instantiations below). Initialize and the destructors
// (which run constructors / destructors of T and allocate) stay guest.
//
// rElement / crElement ask the object's NumElements through its vtable (slot 4) for the range check:
// when the slot is this instantiation's own NumElements the native reads m_count directly (a pure
// callee: the live check's replay runs the guest one unrecorded), else it calls the slot.
#include "core/loader.h"
#include "native/common/live_call.h"
#include "native/containers/containers_family.h"
#include "native/containers/containers_object_container.h"
#include "native/common/gen/common_addresses.h"
#include "native/containers/gen/containers_addresses.h"

namespace soa::native::memory {

namespace {

// What differs between the instantiations: the symbols, and the source path in the asserts (the
// framework's own instantiations were compiled from the Library project, the client's from the
// Client project).
struct Names {
    const char* num_elements;  // NumElements' mangled name
    u64 assert_file;           // vaddr of the assert's source path
};

template <typename T>
struct Inst;
template <>
struct Inst<SoundElement> {
    static constexpr Names n{"_ZNK9Framework16TObjectContainerINS_6CSound8CElementEE11NumElementsEv", kStrObjectContainerH};
};
template <>
struct Inst<CollisionShapeGroup> {
    static constexpr Names n{"_ZNK9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE11NumElementsEv", containers::kStrObjectContainerClientH};
};
template <>
struct Inst<IFixedLengthAllocatorRef*> {
    static constexpr Names n{"_ZNK9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE11NumElementsEv", kStrObjectContainerH};
};
template <>
struct Inst<BehaviorQueueRef*> {
    static constexpr Names n{"_ZNK9Framework16TObjectContainerIP13BehaviorQueueE11NumElementsEv", containers::kStrObjectContainerClientH};
};

u64 guest(u64 vaddr) { return main_lib()->base + vaddr; }

void do_assert(u64 file, u32 line, u64 msg) {
    static const u64 fn = main_lib()->sym("_ZN9Framework9gDoAssertEPKciS1_z");
    live::out_call(containers::family(), fn, {guest(file), line, guest(msg)});
}
void do_assert(u64 file, u32 line, u64 msg, u64 a, u64 b) {
    static const u64 fn = main_lib()->sym("_ZN9Framework9gDoAssertEPKciS1_z");
    live::out_call(containers::family(), fn, {guest(file), line, guest(msg), a, b});
}

// The count through vtable slot 4, as the guest's range check asks it.
template <typename T>
u64 virtual_count(const TObjectContainer<T>* self) {
    static const u64 own = main_lib()->sym(Inst<T>::n.num_elements);
    u64 slot = reinterpret_cast<const u64*>(self->vtable)[4];
    if (slot == own) return self->NumElements();
    return live::out_call(containers::family(), slot, {(u64)self});
}

}  // namespace

template <typename T>
u64 TObjectContainer<T>::NumElements() const {
    if (!m_elements) do_assert(Inst<T>::n.assert_file, 0x3e, kStrElementsNull);
    return m_count;
}

template <typename T>
T* TObjectContainer<T>::rElement(u64 i) {
    if (!m_elements) do_assert(Inst<T>::n.assert_file, 0x44, kStrElementsNull);
    if (virtual_count(this) <= i) do_assert(Inst<T>::n.assert_file, 0x45, kStrOutOfRange, i, virtual_count(this));
    return m_elements + i;
}

template <typename T>
const T* TObjectContainer<T>::crElement(u64 i) const {
    if (!m_elements) do_assert(Inst<T>::n.assert_file, 0x4b, kStrElementsNull);
    if (virtual_count(this) <= i) do_assert(Inst<T>::n.assert_file, 0x4c, kStrOutOfRange, i, virtual_count(this));
    return m_elements + i;
}

#define SOA_OBJC_INSTANTIATE(T)                         \
    template u64 TObjectContainer<T>::NumElements() const; \
    template T* TObjectContainer<T>::rElement(u64);        \
    template const T* TObjectContainer<T>::crElement(u64) const;
SOA_OBJC_INSTANTIATE(SoundElement)
SOA_OBJC_INSTANTIATE(CollisionShapeGroup)
SOA_OBJC_INSTANTIATE(IFixedLengthAllocatorPtr)
SOA_OBJC_INSTANTIATE(BehaviorQueuePtr)
#undef SOA_OBJC_INSTANTIATE

// ---- natives ----

namespace {
using live::kInt;
using SoundC = TObjectContainer<SoundElement>;
using CollC = TObjectContainer<CollisionShapeGroup>;
using AllocC = TObjectContainer<IFixedLengthAllocatorRef*>;
using BehC = TObjectContainer<BehaviorQueueRef*>;
constexpr u32 kObj = sizeof(SoundC);
static_assert(sizeof(SoundC) == 0x18 && sizeof(CollC) == 0x18);

LEAF_METHOD(containers::family(), "_ZNK9Framework16TObjectContainerINS_6CSound8CElementEE11NumElementsEv", &SoundC::NumElements, kObj, kInt,
            "Framework::TObjectContainer<Framework::CSound::CElement>::NumElements", {});
LEAF_METHOD(containers::family(), "_ZN9Framework16TObjectContainerINS_6CSound8CElementEE8rElementEm", &SoundC::rElement, kObj, kInt,
            "Framework::TObjectContainer<Framework::CSound::CElement>::rElement", {});
LEAF_METHOD(containers::family(), "_ZNK9Framework16TObjectContainerINS_6CSound8CElementEE9crElementEm", &SoundC::crElement, kObj, kInt,
            "Framework::TObjectContainer<Framework::CSound::CElement>::crElement", {});
LEAF_METHOD(containers::family(), "_ZNK9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE11NumElementsEv", &CollC::NumElements, kObj, kInt,
            "Framework::TObjectContainer<Collision::CollisionShapeGroup>::NumElements", {});
LEAF_METHOD(containers::family(), "_ZN9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE8rElementEm", &CollC::rElement, kObj, kInt,
            "Framework::TObjectContainer<Collision::CollisionShapeGroup>::rElement", {});
LEAF_METHOD(containers::family(), "_ZNK9Framework16TObjectContainerIN9Collision19CollisionShapeGroupEE9crElementEm", &CollC::crElement, kObj, kInt,
            "Framework::TObjectContainer<Collision::CollisionShapeGroup>::crElement", {});
LEAF_METHOD(containers::family(), "_ZNK9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE11NumElementsEv", &AllocC::NumElements, kObj, kInt,
            "Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::NumElements", {});
LEAF_METHOD(containers::family(), "_ZN9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE8rElementEm", &AllocC::rElement, kObj, kInt,
            "Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::rElement", {});
LEAF_METHOD(containers::family(), "_ZNK9Framework16TObjectContainerIPNS_21IFixedLengthAllocatorEE9crElementEm", &AllocC::crElement, kObj, kInt,
            "Framework::TObjectContainer<Framework::IFixedLengthAllocator*>::crElement", {});
LEAF_METHOD(containers::family(), "_ZNK9Framework16TObjectContainerIP13BehaviorQueueE11NumElementsEv", &BehC::NumElements, kObj, kInt,
            "Framework::TObjectContainer<BehaviorQueue*>::NumElements", {});
LEAF_METHOD(containers::family(), "_ZN9Framework16TObjectContainerIP13BehaviorQueueE8rElementEm", &BehC::rElement, kObj, kInt,
            "Framework::TObjectContainer<BehaviorQueue*>::rElement", {});
LEAF_METHOD(containers::family(), "_ZNK9Framework16TObjectContainerIP13BehaviorQueueE9crElementEm", &BehC::crElement, kObj, kInt,
            "Framework::TObjectContainer<BehaviorQueue*>::crElement", {});
}  // namespace

}  // namespace soa::native::memory

#pragma once
// The TObjectContainer instantiations whose accessors are native (containers_object_container.cpp):
// their element types, by size only (their own subsystems recover them), and the accessors'
// explicit instantiations (defined in that file), so tests can call them.
#include "native/memory/memory_layout.h"

namespace soa::native::memory {

struct SoundElement { u8 bytes[0x70]; };         // Framework::CSound::CElement
struct CollisionShapeGroup { u8 bytes[0x90]; };  // Collision::CollisionShapeGroup
struct IFixedLengthAllocatorRef;                 // (opaque: the pointer instantiations)
struct BehaviorQueueRef;
using IFixedLengthAllocatorPtr = IFixedLengthAllocatorRef*;
using BehaviorQueuePtr = BehaviorQueueRef*;

#define SOA_OBJC_EXTERN(T)                                 \
    extern template u64 TObjectContainer<T>::NumElements() const; \
    extern template T* TObjectContainer<T>::rElement(u64);        \
    extern template const T* TObjectContainer<T>::crElement(u64) const;
SOA_OBJC_EXTERN(SoundElement)
SOA_OBJC_EXTERN(CollisionShapeGroup)
SOA_OBJC_EXTERN(IFixedLengthAllocatorPtr)
SOA_OBJC_EXTERN(BehaviorQueuePtr)
#undef SOA_OBJC_EXTERN

}  // namespace soa::native::memory

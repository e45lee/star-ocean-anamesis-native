#pragma once
// The property natives' registry (internal): which vtables belong to the bound instantiations, and the
// virtual calls CParameterElementBase makes on a property through them.
#include "native/params/params_layout.h"

namespace soa::native::params {

// A bound instantiation's Deserialize, as its checked entry (the native, recording or checking).
using PropertyDeserialize = bool (*)(IParameterProperty* p, const AMap* map);

// The entry of the instantiation whose vtable `vtable` is (the address point), or null for any other
// class (a derived property, a class the generator didn't see). Every bound vtable's slot 2 is its
// CParameterPropertyBase<N>::NameHash (the only 333 implementations of the slot in the lib), which
// returns m_name: a known vtable's NameHash is read directly.
PropertyDeserialize KnownProperty(const void* vtable);
// Registers an instantiation (static initialisation; resolved by symbol at the first lookup).
bool AddKnownProperty(const char* ztv, PropertyDeserialize fn);

// CParameterPropertyBase<N>::CryptString by its symbol (the tests; null when not bound).
using CryptStringFn = void (*)(String& dst, const String& src);
CryptStringFn KnownCryptString(const char* sym);
bool AddKnownCryptString(const char* sym, CryptStringFn fn);

// slot 2 / slot 3 of a property's vtable: the native for a known one, else the guest call.
u32 CallNameHash(const IParameterProperty* p);
bool CallDeserialize(IParameterProperty* p, const AMap* map);

// Any property's name: CParameterPropertyBase<N>'s layout doesn't depend on N.
inline u32 NameOf(const IParameterProperty* p) { return reinterpret_cast<const CParameterPropertyBase<0>*>(p)->m_name.m_hash; }

}  // namespace soa::native::params

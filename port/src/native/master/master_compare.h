#pragma once
// Comparing two runs' elements and maps (the tests and the live check): field by field, the padding
// (whatever the allocator left) and the pointers into each run's own elements (only whether they are
// set) aside; and copies of a table's state for the guest's run (master_simple_check.cpp).
#include <string>

#include "native/master/master_simple.h"

namespace soa::native::master {

// "" when equal: the element's vtable and list head, each property's vtable, m_next, m_named, hash and
// value (sizeof(T); not an unnamed one's: never written) or string (by representation).
std::string cmp_element(const ElementInfo& I, const u8* a, const u8* b);
// "" when equal: sizes, bucket counts, which buckets are set, the keys in list order, each value
// (`shared`: a shared_ptr<E>: the elements and the control blocks' vtables and counts; else an E).
std::string cmp_map(const ElementInfo& I, U32Map& a, U32Map& b, bool shared);

// A copy of a map with the same structure (bucket count, list order, the buckets pointing at the same
// predecessors): shared_ptr values share the element (add_shared), E values are copy-constructed.
void clone_map(const ElementInfo& I, U32Map& to, const U32Map& from, bool shared);
// Destroys such a copy (releases / destroys the values, frees the nodes and the buckets).
void free_map(const ElementInfo& I, U32Map& m, bool shared);

}  // namespace soa::native::master

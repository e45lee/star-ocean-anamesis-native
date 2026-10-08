#pragma once
// The master caches' maps (U32Map, master_layout.h): Framework::CSTLUnorderedMap<unsigned int, V> (libc++'s unordered_map with
// std::hash<unsigned> and the STL allocator; libcxx_layout.h hash_table), whatever V is: the node is
// {next, hash, unsigned key, V at +0x18} (V = shared_ptr<E> or E itself, both 8-aligned). libc++ 6.0's
// algorithms as the game's instantiations compile them (port/decomp/libcxx/hash.c, port/decomp/master/
// stringdb.c: rehash, __rehash, the inlined find / __node_insert_unique / erase / clear), storage
// from Framework::CAssignedMemoryManagerForSTLAllocator ("STL_UnorderedMap.h", 0x1c).
#include "native/master/master_layout.h"

namespace soa::native::master {

// FCVTPU (float -> u64 toward +infinity): NaN and <= -1 give 0, too large saturates.
u64 fcvtpu(float f);

}  // namespace soa::native::master

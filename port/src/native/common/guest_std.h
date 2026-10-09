#pragma once
// Access to the game's C++ runtime objects from native code.
//
// The game is built against the NDK's libc++ (std::__ndk1) with Framework::CSTLAllocator,
// whose storage comes from Framework::CAssignedMemoryManagerForSTLAllocator. Native
// replacements that read or build those objects must keep that exact layout and allocator,
// because guest code elsewhere still uses them. These helpers do that.
#include <cstring>
#include <string>
#include <string_view>

#include "soaruntime/core/cpu.h"

namespace soa::guest {

// Framework::CAssignedMemoryManagerForSTLAllocator::Allocate / Free
void* stl_alloc(size_t n);
void stl_free(void* p);
// operator new[](size_t, std::nothrow_t const&) / operator delete[](void*)
void* new_array_nothrow(size_t n);
void delete_array(void* p);
// Guest address of an exported symbol (fatal if missing).
u64 sym(const char* mangled);

// std::__ndk1::basic_string<char, ..., Framework::CSTLAllocator<char, ...>> (24 bytes).
// Short form: byte 0 = size << 1, chars from byte 1 (22 max). Long form: word 0 = capacity | 1,
// word 1 = size, word 2 = data.
struct String {
    unsigned char raw[24];

    bool is_long() const { return raw[0] & 1; }
    size_t size() const {
        if (is_long()) {
            u64 n;
            std::memcpy(&n, raw + 8, 8);
            return n;
        }
        return raw[0] >> 1;
    }
    const char* data() const {
        if (is_long()) {
            u64 p;
            std::memcpy(&p, raw + 16, 8);
            return (const char*)p;
        }
        return (const char*)raw + 1;
    }
    std::string_view view() const { return {data(), size()}; }
    std::string str() const { return std::string(view()); }

    // Constructs an empty string (does not free anything).
    void init() { std::memset(raw, 0, sizeof raw); }
    // Constructs from s (does not free anything).
    void init(std::string_view s);
    // Replaces the contents, freeing a previous long buffer.
    void assign(std::string_view s);
    void destroy();
};
static_assert(sizeof(String) == 24);

// std::__ndk1::list<String, Framework::CSTLAllocator<...>>: the list object holds the sentinel
// node {prev, next} followed by the size. Nodes are {prev, next, String value} (0x28 bytes).
struct StringList {
    u64 prev, next, count;

    struct Node {
        u64 prev, next;
        String value;
    };
    void init() { prev = next = (u64)this, count = 0; }
    void push_back(std::string_view s);
    template <typename F>
    void for_each(F&& f) const {
        for (u64 n = next; n != (u64)this; n = ((const Node*)n)->next) f(((const Node*)n)->value);
    }
};
static_assert(sizeof(StringList) == 24);

}  // namespace soa::guest

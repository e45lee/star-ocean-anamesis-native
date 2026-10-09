#pragma once
// Helpers of the sync subsystem's differential tests: guest objects in host memory (guest memory is
// identity-mapped) and host threads that may call guest code.
#include <cstring>
#include <functional>
#include <thread>
#include <vector>

#include "soaruntime/core/cpu.h"
#include "native/sync/sync_layout.h"

namespace soa::native::sync::test {

// A zeroed, 16-aligned object of T's guest size.
template <typename T>
struct GuestObj {
    alignas(16) u8 raw[sizeof(T)] = {};
    T* get() { return reinterpret_cast<T*>(raw); }
    u64 addr() const { return (u64)raw; }
    T* operator->() { return get(); }
};

// The object's bytes with every guest pointer into itself (at `self_ptr_offsets`) made relative,
// so a guest-run object and a native-run one compare equal.
template <typename T>
std::vector<u8> normalized(const T* o, std::initializer_list<size_t> self_ptr_offsets) {
    std::vector<u8> b((const u8*)o, (const u8*)o + sizeof(T));
    for (size_t off : self_ptr_offsets) {
        u64 v;
        std::memcpy(&v, b.data() + off, 8);
        if (v >= (u64)o && v < (u64)o + sizeof(T)) v -= (u64)o;
        std::memcpy(b.data() + off, &v, 8);
    }
    return b;
}

// Runs fn(i) on n host threads that may call guest code (each with its own guest stack), and joins.
inline void run_guest_threads(int n, const std::function<void(int)>& fn) {
    std::vector<std::thread> ts;
    for (int i = 0; i < n; i++)
        ts.emplace_back([&fn, i] {
            guest_thread_init(256 << 10);
            fn(i);
            thread_end();  // core/thread_record.h
        });
    for (auto& t : ts) t.join();
}

}  // namespace soa::native::sync::test

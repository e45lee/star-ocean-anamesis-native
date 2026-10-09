#pragma once
// Per-thread objects with an explicit lifetime: what the runtime, the port and its natives use
// instead of a `thread_local` whose type has a destructor (runtime/README.md "Per-thread state").
//
// Only trivially destructible `thread_local`s are allowed (pointers, integers, flags, enums, POD
// buffers; tools/check_thread_local.py in T0 fails on any other). A thread_local with a destructor
// is destroyed by the C++ runtime at thread exit in an order nobody controls, and the MinGW GCC
// build got that order wrong twice (its TLS is emulated, libgcc's emutls): the destructors ran on
// storage emutls had already freed, then the main thread's ran after the static objects they used.
// The workaround (a __cxa_thread_atexit replacement in common/) is gone with them.
//
// Instead each thread has a ThreadRecord on the heap, reached through one trivial thread_local
// pointer and made on the thread's first use. It owns the thread's objects, which are destroyed in
// a fixed order: the thread's objects (thread_object<T, Tag>(): the live checks' scratch, caches,
// buffers) in reverse order of creation, then the guest CPU state (core/cpu.cpp's ThreadState: its
// JIT instances and guest stack), then the crash-report setup (core/crash.cpp: the alternate signal
// stack). thread_end() runs them:
//   - guest threads: the HLE'd pthread_create's thread body (hle/libc_thread.cpp), after the guest's
//     key destructors;
//   - the runtime's own threads (watchdog, control, profiler, GDB stub, movie decoders):
//     ThreadScope at the top of the thread function;
//   - the main thread: the program's main() before it returns (soaruntime_tests), before the static
//     objects are destroyed. A program that leaves through exit() or _exit() elsewhere (the port's
//     host loop, --selftest) leaves the main thread's record to the operating system: nothing
//     per-thread runs after the statics;
//   - any other thread (a library's, such as SDL's audio thread): a pthread key destructor at its
//     exit, given the record itself (on MinGW the emulated TLS may be gone by then: the record
//     doesn't need it).
// A destructor that makes another per-thread object is fine (it is destroyed in its phase, or in
// a later one if its phase is done); a thread that goes on after thread_end() gets a new record.
#include <cstddef>
#include <cstdint>
#include <vector>

namespace soa {

// The destruction phases, in order.
enum class ThreadPhase : uint8_t {
    kObjects,  // thread_object<T, Tag>() (reverse order of creation)
    kCpu,      // the guest CPU state (core/cpu.cpp)
    kCrash,    // the crash-report setup (core/crash.cpp)
};

struct ThreadRecord {
    struct Entry {
        void* obj;
        void (*destroy)(void*);
        ThreadPhase phase;
    };
    std::vector<void*> slots;    // thread_object's objects by slot (null: not made on this thread)
    std::vector<Entry> entries;  // every object, in order of creation
};

namespace thread_record_detail {
extern thread_local ThreadRecord* t_record;
size_t new_slot();  // a slot for one thread_object<T, Tag> (process-wide)
void* add(size_t slot, ThreadPhase phase, void* obj, void (*destroy)(void*));
inline constexpr size_t kNoSlot = ~size_t{0};
}  // namespace thread_record_detail

// The calling thread's record (made if it has none).
ThreadRecord& this_thread_record();

// Gives `obj` to the calling thread's record: `destroy(obj)` runs at the thread's end in `phase`.
inline void thread_record_add(ThreadPhase phase, void* obj, void (*destroy)(void*)) {
    thread_record_detail::add(thread_record_detail::kNoSlot, phase, obj, destroy);
}

// The calling thread's T (value-initialized on its first use there): one per (T, Tag) and thread,
// on the heap (no static TLS: glibc carves static TLS out of every thread's stack, and guest
// threads run on 256 KiB host stacks). The fast path is one thread_local load and an index.
template <typename T, typename Tag = T>
T& thread_object() {
    static const size_t slot = thread_record_detail::new_slot();
    ThreadRecord* r = thread_record_detail::t_record;
    if (r && slot < r->slots.size() && r->slots[slot]) [[likely]]
        return *static_cast<T*>(r->slots[slot]);
    return *static_cast<T*>(thread_record_detail::add(slot, ThreadPhase::kObjects, new T(), [](void* p) { delete static_cast<T*>(p); }));
}

// Destroys the calling thread's record (the phases above, in order). Idempotent.
void thread_end();

// A runtime thread's function body: sets the thread up for crash reports (core/crash.h) and ends
// its record when the function returns.
class ThreadScope {
public:
    explicit ThreadScope(const char* name, uint64_t guest_entry = 0);
    ~ThreadScope() { thread_end(); }
    ThreadScope(const ThreadScope&) = delete;
    ThreadScope& operator=(const ThreadScope&) = delete;
};

}  // namespace soa

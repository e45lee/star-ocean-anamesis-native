// Per-thread objects with an explicit lifetime (core/thread_record.h).
#include "core/thread_record.h"

#include <pthread.h>

#include <atomic>
#include <cstdio>
#include <cstdlib>

#include "core/crash.h"

namespace soa {

namespace thread_record_detail {

thread_local ThreadRecord* t_record = nullptr;

namespace {

std::atomic<size_t> g_next_slot{0};

// Runs the record's objects, phase by phase; in a phase the newest first. A destructor may add
// objects (to this record: t_record is cleared only after): the loop picks them up.
void destroy(ThreadRecord* r) {
    for (int ph = (int)ThreadPhase::kObjects; ph <= (int)ThreadPhase::kCrash; ph++) {
        for (;;) {
            size_t i = r->entries.size();
            while (i > 0 && (int)r->entries[i - 1].phase != ph) i--;
            if (i == 0) break;
            ThreadRecord::Entry e = r->entries[i - 1];
            r->entries.erase(r->entries.begin() + (ptrdiff_t)(i - 1));
            for (void*& s : r->slots)
                if (s == e.obj) s = nullptr;
            e.destroy(e.obj);
        }
    }
    // (an object a kCrash destructor made: not expected; run it anyway)
    while (!r->entries.empty()) {
        ThreadRecord::Entry e = r->entries.back();
        r->entries.pop_back();
        e.destroy(e.obj);
    }
    delete r;
}

// Ends record r on its own thread. The thread_local pointers to it and its objects (t_record here,
// cpu.cpp's and crash.cpp's, cleared by those objects' destructors) are cleared only while they
// still point at them: on the key-destructor path under MinGW, emutls may have freed the thread's
// TLS already (its key can come first), and a read then sees a fresh zeroed block.
void end(ThreadRecord* r) {
    const bool live = t_record == r;
    destroy(r);
    if (live) t_record = nullptr;
}

// A thread that never called thread_end() (a library's thread): its record at the thread's exit.
void key_destructor(void* p) { end((ThreadRecord*)p); }

pthread_key_t make_key() {
    pthread_key_t k;
    if (pthread_key_create(&k, key_destructor) != 0) {
        fprintf(stderr, "thread_record: pthread_key_create failed\n");
        abort();
    }
    return k;
}
pthread_key_t key() {
    static const pthread_key_t k = make_key();
    return k;
}

}  // namespace

size_t new_slot() { return g_next_slot.fetch_add(1, std::memory_order_relaxed); }

void* add(size_t slot, ThreadPhase phase, void* obj, void (*destroy_fn)(void*)) {
    ThreadRecord& r = this_thread_record();
    if (slot != kNoSlot) {
        if (r.slots.size() <= slot) r.slots.resize(slot + 1, nullptr);
        r.slots[slot] = obj;
    }
    r.entries.push_back({obj, destroy_fn, phase});
    return obj;
}

}  // namespace thread_record_detail

using namespace thread_record_detail;

ThreadRecord& this_thread_record() {
    if (ThreadRecord* r = t_record) return *r;
    auto* r = new ThreadRecord;
    t_record = r;
    pthread_setspecific(key(), r);
    return *r;
}

void thread_end() {
    ThreadRecord* r = t_record;
    if (!r) return;
    pthread_setspecific(key(), nullptr);
    end(r);
}

ThreadScope::ThreadScope(const char* name, uint64_t guest_entry) { crash_thread_begin(name, guest_entry); }

}  // namespace soa

// Runtime tests of the per-thread records (core/thread_record.h). Run by `soa --selftest` and
// soaruntime_tests.
//
// cpu/thread-record-order: a thread's objects are its own, made once, and thread_end() destroys
// them in the fixed order: the thread objects newest first (one a destructor makes included), while
// the guest CPU state and the crash setup are still there; then those two. A use after
// thread_end() gets a new record.
// cpu/thread-record-library-thread: a thread that never calls thread_end() (a library's) has its
// objects destroyed at its exit (the pthread key destructor), before join() returns.
#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "core/cpu.h"
#include "core/crash.h"
#include "core/selftest.h"
#include "core/thread_record.h"

namespace soa {
namespace {

std::mutex g_log_m;
std::vector<std::string> g_log;
void log_event(std::string s) {
    std::lock_guard lk(g_log_m);
    g_log.push_back(std::move(s));
}
std::string state_now() {  // whether the later phases are still there
    return std::string(crash_thread() ? "crash" : "-") + "," + (guest_thread().stack_lo ? "cpu" : "-");
}

struct First {
    int v = 0;
    ~First() { log_event("First:" + state_now()); }
};
struct Second {
    ~Second() { log_event("Second"); }
};
struct Late {
    ~Late() { log_event("Late"); }
};
struct MakesLate {
    ~MakesLate() {
        thread_object<Late>();  // made while the record is being destroyed
        log_event("MakesLate");
    }
};
struct TagA;
struct TagB;

RUNTIME_TEST("cpu/thread-record-order") {
    {
        std::lock_guard lk(g_log_m);
        g_log.clear();
    }
    int* main_obj = &thread_object<int, TagA>();
    std::string err;
    std::thread th([&] {
        crash_thread_begin("thread-record-test");
        guest_thread_init(256 << 10);  // the CPU state
        First& f = thread_object<First>();
        f.v = 7;
        thread_object<Second>();
        thread_object<MakesLate>();
        if (&thread_object<First>() != &f || thread_object<First>().v != 7) err += "a second use made a new object; ";
        if (&thread_object<int, TagA>() == main_obj) err += "the main thread's object on another thread; ";
        if (&thread_object<int, TagA>() == &thread_object<int, TagB>()) err += "two tags share an object; ";
        thread_end();
        if (crash_thread()) err += "the crash setup outlived thread_end; ";
        {
            std::lock_guard lk(g_log_m);
            g_log.push_back("end");
        }
        if (thread_object<First>().v != 0) err += "the object after thread_end isn't a new one; ";
        thread_end();
    });
    th.join();
    if (!err.empty()) t.fail("%s", err.c_str());
    const std::vector<std::string> want = {"MakesLate", "Late", "Second", "First:crash,cpu", "end", "First:-,-"};
    std::lock_guard lk(g_log_m);
    if (g_log != want) {
        std::string got;
        for (auto& s : g_log) got += s + " ";
        t.fail("destruction order: %s(want MakesLate Late Second First:crash,cpu end First:-,-)", got.c_str());
    }
}

std::atomic<int> g_gone{0};
struct Counted {
    ~Counted() { g_gone.fetch_add(1); }
};

RUNTIME_TEST("cpu/thread-record-library-thread") {
    g_gone = 0;
    std::thread th([] { thread_object<Counted>(); });
    th.join();
    if (g_gone != 1) t.fail("a library thread's object destroyed %d times at its exit (want 1)", g_gone.load());
}

}  // namespace
}  // namespace soa

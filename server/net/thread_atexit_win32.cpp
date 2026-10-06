// thread_local destructors for cpp-httplib on Windows (MinGW GCC only). Only third-party code
// needs this: our own code has no thread_local with a destructor or a dynamic initializer
// (runtime/src/core/thread_record.h; tools/check_thread_local.py in T0), but cpp-httplib's header
// (0.58) has about ten (std::regex, std::set, std::mt19937, ...), compiled into this library's
// http_server.cpp and client.cpp, so soa-server is the one program that links this file (soa,
// soa-emu, soa-viewer and soaruntime_tests reference no __cxa_thread_atexit; the check verifies).
//
// Why: GCC's TLS on MinGW is emulated (libgcc's emutls). libstdc++'s __cxa_thread_atexit runs the
// destructors from a winpthreads key destructor whose key is created after emutls' own, and
// winpthreads runs key destructors in key order: emutls frees a thread's TLS blocks first, then the
// destructors run on freed memory (seen as soaruntime_tests crashing in ~ThreadState under Wine,
// before the runtime's thread_locals became trivial). This replacement (it takes the place of
// libstdc++'s: the linker finds it in this library first) keeps each thread's destructors in a key
// created at start-up, before any emulated TLS is touched, so they run while the blocks are alive;
// the main thread's at exit(), through an atexit handler registered at each of its registrations
// (C++ destroys thread storage before the statics; static destructors are atexit handlers too, run
// in reverse order of registration, so an object constructed before the thread_local outlives it).
// (clang, llvm-mingw, has native TLS: none of this.)
#if defined(_WIN32) && defined(__GNUC__) && !defined(__clang__)
#include <pthread.h>
#include <stdlib.h>
#include <windows.h>

#include <vector>

namespace {
struct ThreadDtor {
    void (*fn)(void*);
    void* obj;
};
using ThreadDtors = std::vector<ThreadDtor>;
pthread_key_t g_dtor_key;
bool g_dtor_key_ok = false;
DWORD g_main_tid = 0;  // the thread the constructors run on

void run_thread_dtors(void* p) {
    auto* v = (ThreadDtors*)p;
    while (!v->empty()) {  // in reverse order of construction; a destructor may register more
        ThreadDtor d = v->back();
        v->pop_back();
        d.fn(d.obj);
    }
    delete v;
}

void run_main_thread_dtors() {  // (no key destructor runs for the main thread)
    if (auto* v = (ThreadDtors*)pthread_getspecific(g_dtor_key)) {
        pthread_setspecific(g_dtor_key, nullptr);
        run_thread_dtors(v);
    }
}

__attribute__((constructor(101))) void init_thread_dtors() {
    g_dtor_key_ok = pthread_key_create(&g_dtor_key, run_thread_dtors) == 0;
    g_main_tid = GetCurrentThreadId();
}
}  // namespace

extern "C" int __cxa_thread_atexit(void (*fn)(void*), void* obj, void* /*dso*/) {
    if (!g_dtor_key_ok) return -1;
    auto* v = (ThreadDtors*)pthread_getspecific(g_dtor_key);
    if (!v) {
        v = new ThreadDtors;
        pthread_setspecific(g_dtor_key, v);
    }
    v->push_back({fn, obj});
    if (GetCurrentThreadId() == g_main_tid) atexit(run_main_thread_dtors);  // (before the statics constructed so far)
    return 0;
}
#endif

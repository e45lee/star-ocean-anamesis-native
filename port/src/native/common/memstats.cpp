// Memory diagnostics (port-only, inert by default): one "I/memstats" block per snapshot with the
// process RSS, host threads by name, the guest CPU contexts (each a dynarmic JIT with its own code
// cache) per host thread, the JIT code-cache mappings' RSS, host malloc (mallinfo2), the guest
// engine heap (Aska default MemoryManager) and the largest mappings from /proc/self/smaps.
//
//   --memstats        a snapshot at every CPhase change (battle start/end, home, ...)
//   --memstats S      (S > 1) also every S seconds
//   control "memstats[:TAG]"  one snapshot now (e.g. from a session script)
//
// Written for PLAN-next D7 (per-battle growth); see port/README.md "Memory diagnostics".
#include "native/common/memstats.h"

#include <dirent.h>
#include <malloc.h>
#include <unistd.h>

#include <algorithm>
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <string>
#include <vector>

#include "core/log.h"
#include "core/options.h"
#include "native/common/guest_std.h"
#include "native/memory/memory_callees.h"

namespace soa::native::memstats {
namespace {
using memory::kCalcFreeSizeCallee;

std::string read_file(const char* path) {
    std::string s;
    if (FILE* f = fopen(path, "r")) {
        char buf[4096];
        size_t n;
        while ((n = fread(buf, 1, sizeof buf, f)) > 0) s.append(buf, n);
        fclose(f);
    }
    return s;
}

long status_kb(const std::string& st, const char* key) {
    size_t p = st.find(key);
    if (p == std::string::npos) return -1;
    return strtol(st.c_str() + p + strlen(key), nullptr, 10);
}

std::string thread_comm(int tid) {
    char path[64];
    snprintf(path, sizeof path, "/proc/self/task/%d/comm", tid);
    std::string s = read_file(path);
    while (!s.empty() && (s.back() == '\n' || s.back() == ' ')) s.pop_back();
    return s.empty() ? "?" : s;
}

struct Mapping {
    unsigned long lo = 0, hi = 0;
    std::string perms, name;
    long rss_kb = 0;
};

std::vector<Mapping> read_smaps() {
    std::vector<Mapping> out;
    FILE* f = fopen("/proc/self/smaps", "r");
    if (!f) return out;
    char line[1024];
    while (fgets(line, sizeof line, f)) {
        unsigned long lo, hi;
        char perms[8];
        int name_at = 0;
        if (sscanf(line, "%lx-%lx %7s %*s %*s %*s %n", &lo, &hi, perms, &name_at) >= 3 && strchr(line, '-') < strchr(line, ' ')) {
            Mapping m;
            m.lo = lo;
            m.hi = hi;
            m.perms = perms;
            if (name_at > 0) {
                m.name = line + name_at;
                while (!m.name.empty() && (m.name.back() == '\n' || m.name.back() == ' ')) m.name.pop_back();
            }
            out.push_back(std::move(m));
        } else if (!out.empty() && strncmp(line, "Rss:", 4) == 0) {
            out.back().rss_kb = strtol(line + 4, nullptr, 10);
        }
    }
    fclose(f);
    return out;
}

// dynarmic's code cache: one anonymous mapping of code_cache_size (256 MB) + one page per JIT
// (third_party/dynarmic block_of_code.cpp CustomXbyakAllocator), plus xbyak's rounding.
bool is_jit_cache(const Mapping& m) {
    unsigned long sz = m.hi - m.lo;
    return m.name.empty() && sz >= (256ul << 20) && sz <= (256ul << 20) + (64ul << 10);
}

}  // namespace

int mode() { return options().client.memstats; }

void log(const char* why) {
    const std::string st = read_file("/proc/self/status");
    LOGI("memstats", "---- %s: rss %ld MB (hwm %ld MB, anon %ld MB, file %ld MB), %ld threads", why, status_kb(st, "VmRSS:") / 1024,
         status_kb(st, "VmHWM:") / 1024, status_kb(st, "RssAnon:") / 1024, status_kb(st, "RssFile:") / 1024, status_kb(st, "Threads:"));

    // Host threads by name.
    std::map<std::string, int> names;
    if (DIR* d = opendir("/proc/self/task")) {
        while (dirent* e = readdir(d))
            if (e->d_name[0] != '.') names[thread_comm(atoi(e->d_name))]++;
        closedir(d);
    }
    std::string ns;
    for (auto& [n, k] : names) ns += " " + n + "x" + std::to_string(k);
    LOGI("memstats", "threads:%s", ns.c_str());

    // Guest CPU contexts, grouped by the threads' guest entry function.
    CpuMemStats cs = cpu_memstats();
    LOGI("memstats", "guest cpu contexts %zu (ids used up to %zu of %zu) in %zu threads", cs.contexts, cs.peak_ids, cs.limit, cs.threads.size());
    struct Group {
        size_t threads = 0, levels = 0, max = 0;
        std::string tids;
    };
    std::map<u64, Group> groups;
    for (auto& t : cs.threads) {
        Group& g = groups[t.entry];
        g.threads++;
        g.levels += t.levels;
        g.max = std::max(g.max, t.levels);
        if (g.threads <= 4) g.tids += " " + std::to_string(t.tid) + ":" + std::to_string(t.levels);
    }
    for (auto& [entry, g] : groups)
        LOGI("memstats", "  %zu contexts in %zu threads (max %zu levels) from %s;%s%s", g.levels, g.threads, g.max,
             entry ? describe_guest_addr(entry).c_str() : "?", g.tids.c_str(), g.threads > 4 ? " ..." : "");

    // Mappings: JIT code caches, the rest by kind, the largest ones.
    std::vector<Mapping> maps = read_smaps();
    long jit_n = 0, jit_kb = 0, anon_kb = 0, file_kb = 0, heap_kb = 0, stack_kb = 0;
    for (auto& m : maps) {
        if (is_jit_cache(m)) {
            jit_n++;
            jit_kb += m.rss_kb;
        } else if (m.name == "[heap]") heap_kb += m.rss_kb;
        else if (m.name.rfind("[stack", 0) == 0) stack_kb += m.rss_kb;
        else if (m.name.empty() || m.name[0] == '[') anon_kb += m.rss_kb;
        else file_kb += m.rss_kb;
    }
    LOGI("memstats", "smaps: %zu mappings; jit code caches %ld (%ld MB rss, %ld KB avg), [heap] %ld MB, other anon %ld MB, files %ld MB",
         maps.size(), jit_n, jit_kb / 1024, jit_n ? jit_kb / jit_n : 0, heap_kb / 1024, anon_kb / 1024, file_kb / 1024);
    std::vector<const Mapping*> big;
    for (auto& m : maps)
        if (!is_jit_cache(m)) big.push_back(&m);
    std::sort(big.begin(), big.end(), [](const Mapping* a, const Mapping* b) { return a->rss_kb > b->rss_kb; });
    for (size_t i = 0; i < big.size() && i < 8 && big[i]->rss_kb >= 16 * 1024; i++)
        LOGI("memstats", "  map %lx-%lx %s %lu MB, rss %ld MB %s", big[i]->lo, big[i]->hi, big[i]->perms.c_str(), (big[i]->hi - big[i]->lo) >> 20,
             big[i]->rss_kb / 1024, big[i]->name.c_str());

    // Host malloc (glibc's; the /proc parts above find nothing on Windows).
#ifndef _WIN32
    struct mallinfo2 mi = mallinfo2();
    LOGI("memstats", "host malloc: in use %zu MB (arena %zu MB, mmapped %zu MB in %zu), free in arenas %zu MB, top pad %zu MB",
         (mi.uordblks + mi.hblkhd) >> 20, mi.arena >> 20, mi.hblkhd >> 20, mi.hblks, mi.fordblks >> 20, mi.keepcost >> 20);
#endif

    // Guest engine heap (docs/notes.md "Engine heap"): the available manager, +0x28 heap size.
    static const u64 get_mm = guest::sym("_ZN4Aska6Global25GetAvailableMemoryManagerEv");
    if (get_mm) {
        u64 mm = guest_call(get_mm, {});
        if (mm) {
            u64 size = *(u64*)(mm + 0x28);
            u64 free_b = kCalcFreeSizeCallee.direct() ? (u64)reinterpret_cast<native::memory::MemoryManager*>(mm)->CalcFreeSize(false)
                                                : guest_call(kCalcFreeSizeCallee.addr(), {mm, 0});
            LOGI("memstats", "guest heap: %llu MB used of %llu MB (%llu MB free)", (unsigned long long)((size - free_b) >> 20),
                 (unsigned long long)(size >> 20), (unsigned long long)(free_b >> 20));
        }
    }
}

void on_phase(u32 phase) {
    const int m = mode();
    if (!m) return;
    static u32 last = ~0u;
    static auto last_t = std::chrono::steady_clock::now();
    auto now = std::chrono::steady_clock::now();
    if (phase != last) {
        char why[32];
        snprintf(why, sizeof why, "phase %u", phase);
        log(why);
        last = phase;
        last_t = now;
    } else if (m > 1 && now - last_t >= std::chrono::seconds(m)) {
        log("periodic");
        last_t = now;
    }
}

}  // namespace soa::native::memstats

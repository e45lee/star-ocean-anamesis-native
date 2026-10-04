#pragma once
// The live check of a family bound to a host library at the library's API (port/PLAN.md task 6,
// "Per library": zlib, zstd, libVorbis + libogg, libjpeg, the OpenSSL pieces): run both, in lockstep.
//
// The natives own the real state (host z_stream, host vorbis_dsp_state, a host ZSTD_DStream...), so
// a record / replay of one call can't work: the guest library's state would be missing. Instead, while
// the family is switched on (soa --live-check <tag>), every guest object the natives see gets a
// *shadow*: a block in the guest library's own layout that the guest originals (the hooks'
// trampolines) run on, call for call, with the same inputs. Each native then compares what the host
// library produced with what the guest library produced on its shadow (results, written bytes,
// decoded samples bit for bit) and counts a check per call (ok / mismatch). Nothing of the shadow
// run reaches the game: outputs go to scratch buffers.
//
// The guest library calls its own exported functions too (vorbis_synthesis_headerin -> vorbis_info_clear,
// AES_set_decrypt_key -> AES_set_encrypt_key, ...), and those are natives now: while a thread runs the
// guest library for a shadow (shadow_call), a native entered on it forwards to its guest original, so
// the guest library keeps running on its own state (lib_sqlite's t_guest, shared by these families).
//
// Switches: --live-check <tag>[:out=FILE][:only=SUB|..] (live_check.h; every= and budget= don't apply:
// a shadow must see every call to stay in step). only= limits the comparisons, not the shadow run.
// The totals are logged as I/<tag>_check every 1000 checks and written to out=FILE every 10 s.
#include <atomic>
#include <cstdarg>
#include <map>
#include <mutex>
#include <string>
#include <unordered_map>

#include "native/common/live_check.h"

namespace soa::live {

class Lockstep : public Family {
public:
    explicit Lockstep(const char* tag) : Family(tag, 1, false) {}

    bool active() const { return on.load(std::memory_order_relaxed); }

    // Shadow objects, keyed by the guest object they mirror (its address): zeroed blocks of the
    // guest layout's size, in guest-visible memory (host malloc is the guest's malloc).
    u64 shadow(u64 key, size_t bytes);  // the key's shadow, made on first use
    u64 find(u64 key);                  // 0 if the key has none
    void drop(u64 key);                 // frees the key's shadow
    // A shadow the guest library made itself (e.g. its ZSTD_createDStream's): registered, not owned.
    void adopt(u64 key, u64 block);
    u64 release(u64 key);  // unregisters the key's shadow (not freed); returns it (0: none)

    // Results of one comparison of `fn` (a check). bad() logs the first mismatches (E/<tag>_check).
    void ok(const char* fn);
    void bad(const char* fn, const char* fmt, ...) __attribute__((format(printf, 3, 4)));
    bool chosen(const char* fn) const { return only.match(fn); }

    u64 checks() const { return stats.checks.load(); }
    u64 mismatches() const { return stats.bad.load(); }
    void write_summary();  // out=FILE (also every 10 s from ok() / bad())

private:
    struct Counts {
        u64 checks = 0, bad = 0;
    };
    void count(const char* fn, bool good);
    std::mutex m_;
    std::unordered_map<u64, std::pair<u64, size_t>> shadows_;  // key -> (block, bytes; 0: adopted)
    std::map<std::string, Counts> per_fn_;
    std::atomic<s64> last_write_{0};
    std::atomic<int> logged_{0};
};

// A shadow run: the guest library's function `fn` (a hook's original) called for the check. While it
// runs, in_shadow_run() is true on this thread, and the natives forward to their originals.
u64 shadow_call(u64 fn, std::initializer_list<u64> args);
bool in_shadow_run();

}  // namespace soa::live

#pragma once
// The environment of the runnable programs (soa, soa-server, soa-emu, soa-viewer, soa-webview-render;
// docs/environment.md). Header-only, so every library can use it without depending on another
// (target soa_env, common/CMakeLists.txt).
//
// The rule: a setting is a command-line flag. The environment carries only diagnostics and
// test-harness switches (SOA_TRACE, SOA_PROFILE, SOA_SELFTEST_*, ...; listed in runtime/README.md
// for the runtime's and port/README.md for soa's), and they are read through the helpers below:
//   - one on/off rule (env_bool): unset or "" = the default; 0, false, no, off (any case) = off;
//     anything else = on;
//   - numbers range-checked (env_int): a bad value is warned about and the default used.
// The variables that were settings are in kRemoved: a program that finds one set prints one line,
// "<program>: SOA_CLOCK is gone: use --clock", at startup (warn_removed_env) and otherwise ignores it.
#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <optional>
#include <strings.h>
#include <unistd.h>  // environ
#include <string>
#include <string_view>
#include <vector>

namespace soa::env {

// The programs (a mask: which ones a removed variable's flag belongs to).
enum Program : unsigned { kSoa = 1, kServer = 2, kEmu = 4, kViewer = 8, kRender = 16 };
constexpr unsigned kRuntimePrograms = kSoa | kEmu | kViewer;

struct Removed {
    const char* name;
    const char* use;    // what to give instead: the flag
    unsigned programs;  // the programs that have that flag (and warn)
};

// Every variable that became a flag (2026-10-03, branch port/env-flags), with its flag, in the
// programs that have the flag. Keep docs/environment.md "Removed" in step (tests/env_removed.sh
// checks the binaries print each line).
inline constexpr Removed kRemoved[] = {
    // the source checkout, the asset sources and the device
    {"SOA_REPO", "--repo", kSoa | kServer | kEmu | kViewer},
    {"SOA_DOWNLOAD_DIR", "--download-dir", kSoa | kServer | kEmu | kViewer},
    {"SOA_DOWNLOAD_PREFER", "--download-prefer", kSoa | kEmu | kViewer},
    {"SOA_STANDIN_ASSETS", "--standin-assets", kSoa | kServer},
    {"SOA_GUEST_CPUS", "--guest-cpus", kRuntimePrograms},
    {"SOA_HEADLESS", "--headless / --windowed", kRuntimePrograms},
    // soa's own
    {"SOA_NATIVES", "--natives", kSoa},
    {"SOA_FAKE_SERVER", "--fake-server", kSoa},
    {"SOA_FAKE_SERVER_SCHEMA", "--fake-server-schema", kSoa},
    {"SOA_MEMSTATS", "--memstats", kSoa},
    {"SOA_RESTORE", "--server inproc (the default)", kSoa},
    // the local server's (soa --server inproc and soa-server take the same flags)
    {"SOA_SERVER_DB", "--db", kSoa | kServer},
    {"SOA_SERVER_MASTER", "--master", kSoa | kServer},
    {"SOA_GACHA_POOLS", "--gacha-pools", kSoa | kServer},
    {"SOA_SERVER_SEED", "--seed", kSoa | kServer},
    {"SOA_SERVER_GAME_XML", "--seed", kSoa | kServer},
    {"SOA_SERVER_SEED_RNG", "--seed-rng", kSoa | kServer},
    {"SOA_RESTORE_NEW_PLAYER", "--new-player", kSoa | kServer},
    {"SOA_CLOCK", "--clock", kSoa | kServer},
    {"SOA_START_COINS", "--start-coins", kSoa | kServer},
    {"SOA_GALAXY_PASS", "--galaxy-pass", kSoa | kServer},
    {"SOA_ENABLE_EVENTS", "--enable-events", kSoa | kServer},
    {"SOA_EVENT_KEYWORDS", "--event-keywords", kSoa | kServer},
    {"SOA_RESTORE_TOWER", "--restore-tower", kSoa | kServer},
    {"SOA_MASTER_DB", "--campaign-master-db", kSoa | kServer},
    {"SOA_CAMPAIGN_SEED", "--campaign-seed", kSoa | kServer},
    {"SOA_SERVER_FAIL", "--fail", kSoa | kServer},
    {"SOA_SERVER_SURPRISE", "--surprise", kSoa | kServer},
    {"SOA_LOG_PACKETS", "--log-packets", kSoa | kServer},
};

// The live check's per-family switches SOA_<FAMILY>_CHECK, _CHECK_EVERY, _CHECK_OUT, _CHECK_ONLY,
// _CHECK_TRACE, _CHECK_DUMP (now soa --live-check; port/src/native/common/live_check.h).
inline bool is_live_check_var(std::string_view n) {
    if (n.size() < 11 || n.substr(0, 4) != "SOA_") return false;
    for (const char* s : {"_CHECK", "_CHECK_EVERY", "_CHECK_OUT", "_CHECK_ONLY", "_CHECK_TRACE", "_CHECK_DUMP"}) {
        size_t k = strlen(s);
        if (n.size() > 4 + k && n.substr(n.size() - k) == s) return true;
    }
    return false;
}

// The warning lines (without the program prefix) for the removed variables set in `envp`, in
// kRemoved's order, each once. A variable set to "" counts as set.
inline std::vector<std::string> removed_env_warnings(unsigned program, char* const* envp) {
    std::vector<std::string> out;
    auto set = [&](std::string_view name) {
        for (char* const* e = envp; e && *e; e++) {
            std::string_view v = *e;
            if (v.size() > name.size() && v.substr(0, name.size()) == name && v[name.size()] == '=') return true;
        }
        return false;
    };
    for (const Removed& r : kRemoved)
        if ((r.programs & program) && set(r.name)) out.push_back(std::string(r.name) + " is gone: use " + r.use);
    if (program & kSoa)
        for (char* const* e = envp; e && *e; e++) {
            std::string_view v = *e;
            std::string_view n = v.substr(0, v.find('='));
            if (is_live_check_var(n)) out.push_back(std::string(n) + " is gone: use --live-check");
        }
    return out;
}

// The program's name in the helpers' warnings (warn_removed_env sets it).
inline const char*& program_name() {
    static const char* name = "soa";
    return name;
}

// At the top of main: one line per removed variable that is set, "<prog>: NAME is gone: use FLAG",
// on stderr. Returns the count.
inline int warn_removed_env(const char* prog, unsigned program) {
    program_name() = prog;
    auto lines = removed_env_warnings(program, environ);
    for (auto& l : lines) fprintf(stderr, "%s: %s\n", prog, l.c_str());
    return (int)lines.size();
}

// ---- reading the diagnostics and test switches ----

// The value of `name` when set and non-empty, else nullptr.
inline const char* env_str(const char* name) {
    const char* e = getenv(name);
    return e && *e ? e : nullptr;
}

// The one on/off rule: unset or "" = `dflt`; 0, false, no, off (any case) = off; anything else on.
inline bool parse_bool(const char* v, bool dflt) {
    if (!v || !*v) return dflt;
    for (const char* off : {"0", "false", "no", "off"})
        if (!strcasecmp(v, off)) return false;
    return true;
}
inline bool env_bool(const char* name, bool dflt) { return parse_bool(getenv(name), dflt); }
// A switch that is off by default.
inline bool env_on(const char* name) { return env_bool(name, false); }
// A switch whose default depends on the run: nullopt when unset or "".
inline std::optional<bool> env_tristate(const char* name) {
    const char* e = env_str(name);
    if (!e) return std::nullopt;
    return parse_bool(e, false);
}

// A whole number in lo..hi (base 10); unset or "" = `dflt`. A value that isn't one (or is out of
// range) is warned about, once per call, and `dflt` is used: as a flag would refuse it.
inline long env_int(const char* name, long lo, long hi, long dflt) {
    const char* e = env_str(name);
    if (!e) return dflt;
    char* end = nullptr;
    errno = 0;
    long v = strtol(e, &end, 10);
    if (errno || end == e || *end || v < lo || v > hi) {
        fprintf(stderr, "%s: %s=%s: expected a number in %ld..%ld; using %ld\n", program_name(), name, e, lo, hi, dflt);
        return dflt;
    }
    return v;
}

// A comma-separated list; empty items are dropped.
inline std::vector<std::string> env_list(const char* name) {
    std::vector<std::string> out;
    const char* e = env_str(name);
    if (!e) return out;
    std::string s = e;
    for (size_t p = 0; p <= s.size();) {
        size_t q = s.find(',', p);
        if (q == std::string::npos) q = s.size();
        if (q > p) out.push_back(s.substr(p, q - p));
        p = q + 1;
    }
    return out;
}

}  // namespace soa::env

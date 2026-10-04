#pragma once
// The programs' command lines on CLI11 (vcpkg `cli11`, linked through soa_env): what every program
// shares. The option groups shared by more than one program are defined once, next to the type
// they fill:
//   - runtime/src/app/cli.h               the window, scripted driving, the device (soa, soa-emu, soa-viewer)
//   - platform370/include/platform370/cli.h  the 3.7.0 phone's clock, patch and network (soa, soa-emu)
//   - server/include/soaserver/cli.h      the local server's rules and state (soa, soa-server)
//   - here                                --repo, --download / --download-dir, --download-prefer,
//                                         --standin-assets, -v (soa, soa-server, soa-emu, soa-viewer)
// Each program's own options and its parse function are in its cli.cpp (port/src/core/cli.cpp,
// server/app/cli.cpp, emulator/src/cli.cpp, emulator-viewer/src/cli.cpp); tests/cli checks every
// option of every program against the hand-written parsers they replaced.
//
// The rules the old parsers had, kept for every program (make_app, parse):
//   - a value-taking option given twice: the last one wins (repeatable ones collect every value);
//   - every error (an unknown option, a missing or malformed value) prints one line and exits 2;
//     -h / --help prints the help and exits 0;
//   - no Windows-style /option parsing (a value such as soa-server --cdn-check /download/... stays
//     a value), no environment fallbacks: settings are flags only (docs/environment.md). The help
//     notes, for each flag that replaced a removed SOA_* variable, which one (env::kRemoved).
#include <CLI/CLI.hpp>

#include <cctype>
#include <cerrno>
#include <functional>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>

#include <soa/env.h>

namespace soa::cli {

// A new program's App with the shared rules (see above).
inline void setup_app(CLI::App& app) {
    app.allow_windows_style_options(false);
    app.option_defaults()->multi_option_policy(CLI::MultiOptionPolicy::TakeLast);
    app.set_help_flag("-h,--help", "this text");
    auto fmt = app.get_formatter();
    fmt->column_width(34);
    fmt->right_column_width(70);
    fmt->long_option_alignment_ratio(6.0f / 34);
    fmt->footer_paragraph_width(100);
    fmt->enable_default_flag_values(false);
    fmt->description_paragraph_width(100);
}

// A repeatable option: every occurrence adds its value, in command-line order; one value each
// (a word after it that isn't an option is an error, as before).
inline CLI::Option* add_list(CLI::App& app, const std::string& name, std::vector<std::string>& to, const std::string& desc) {
    return app.add_option(name, to, desc)->allow_extra_args(false)->multi_option_policy(CLI::MultiOptionPolicy::TakeAll);
}

// A flag whose callback runs where it stands on the command line (for flags that undo each other:
// --headless / --windowed, --natives / --no-native).
inline CLI::Option* add_ordered_flag(CLI::App& app, const std::string& name, std::function<void()> f, const std::string& desc) {
    return app.add_flag_callback(name, std::move(f), desc)->trigger_on_parse();
}

// Throws the parse error the helpers report as "OPTION: MESSAGE" (exit 2).
[[noreturn]] inline void bad_value(const std::string& option, const std::string& msg) { throw CLI::ValidationError(option, msg); }

// ---- value formats shared by several options ------------------------------------------------

// A whole number in lo..hi (decimal), as the old parsers checked them (strtol / strtoull); false
// when it isn't one.
inline bool parse_long_in(const std::string& s, long lo, long hi, long* out) {
    char* end = nullptr;
    errno = 0;
    long v = strtol(s.c_str(), &end, 10);
    if (s.empty() || *end || errno == ERANGE || v < lo || v > hi) return false;
    *out = v;
    return true;
}
// An unsigned 64-bit number: strtoull with `base` (0: 0x... hex and 0... octal too); false when
// the whole string isn't one.
inline bool parse_u64(const std::string& s, int base, uint64_t* out) {
    char* end = nullptr;
    unsigned long long v = strtoull(s.c_str(), &end, base);
    if (s.empty() || *end) return false;
    *out = (uint64_t)v;
    return true;
}

// --guest-cpus N|host: 1..256, or "host" (0: the host's count).
inline int parse_guest_cpus(const std::string& c) {
    long v = 0;
    if (c == "host") return 0;
    if (!parse_long_in(c, 1, 256, &v)) bad_value("--guest-cpus", "expected 1..256 or \"host\", got \"" + c + "\"");
    return (int)v;
}

// "YYYY-MM-DD[ HH:MM:SS]" (local time), or a plain integer (Unix seconds). 0 when unparsable.
// (--clock: soa and soa-server; the server library's parse_clock.)
inline int64_t parse_clock(const std::string& s) {
    struct tm tm = {};
    if (sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec) >= 3) {
        tm.tm_year -= 1900;
        tm.tm_mon -= 1;
        tm.tm_isdst = -1;
        return (int64_t)mktime(&tm);
    }
    char* end = nullptr;
    long long v = strtoll(s.c_str(), &end, 10);
    return end && end != s.c_str() && *end == 0 && v > 0 ? (int64_t)v : 0;
}

// ---- options more than one program has (the asset sources, the checkout, logging) -----------

// --repo DIR (soa, soa-server, soa-emu, soa-viewer).
inline CLI::Option* add_repo(CLI::App& app, std::string& to) {
    return app.add_option("--repo", to,
                          "the source checkout repo files are read from (master DBs, seed saves, gacha pools, "
                          "work/...); default: found upwards from the executable, then the working directory")
        ->type_name("DIR");
}
// --download PATH (= --download-dir PATH): the 3.7.0 download, a folder or a zip (soa, soa-server,
// soa-emu, soa-viewer); `desc` says what the program does with it.
inline CLI::Option* add_download(CLI::App& app, std::string& to, const std::string& desc) {
    return app.add_option("--download,--download-dir", to, desc)->type_name("PATH");
}
// --download-prefer (soa, soa-emu, soa-viewer).
inline CLI::Option* add_download_prefer(CLI::App& app, bool& to) {
    return app.add_flag("--download-prefer", to, "with --download: its files win over the APK's");
}
// --standin-assets DIR|off (soa, soa-server): the stand-in overlay; "off" / "0" = none.
inline CLI::Option* add_standin_assets(CLI::App& app, std::string& dir, bool& off, const std::string& desc) {
    return app
        .add_option_function<std::string>(
            "--standin-assets",
            [&dir, &off](const std::string& v) {
                if (v == "off" || v == "0") off = true;
                else dir = v;
            },
            desc)
        ->type_name("DIR|off");
}
// -v (debug log) / -vv or -v -v (trace): the count.
inline CLI::Option* add_verbose(CLI::App& app, int& count, const std::string& desc = "verbose logging; -vv (or -v -v): trace") {
    return app.add_flag("-v", count, desc)->default_str("");
}

// ---- help --------------------------------------------------------------------------------------

// Appends "(was SOA_X)" to every option that replaced a removed variable in this program
// (env::kRemoved; the live check's per-family variables to --live-check). After all options exist.
inline void note_removed_env(CLI::App& app, unsigned program) {
    for (CLI::Option* o : app.get_options()) {
        std::vector<std::string> was;
        for (const env::Removed& r : env::kRemoved) {
            if (!(r.programs & program)) continue;
            std::string use = r.use;
            for (const std::string& n : o->get_lnames()) {
                std::string flag = "--" + n;
                size_t p = use.find(flag);
                size_t e = p + flag.size();
                if (p != std::string::npos && (e == use.size() || (!isalnum((unsigned char)use[e]) && use[e] != '-'))) {
                    was.push_back(r.name);
                    break;
                }
            }
        }
        if ((program & env::kSoa) && o->check_lname("live-check")) was.push_back("SOA_<FAMILY>_CHECK*");
        if (was.empty()) continue;
        std::string note = " (was ";
        for (size_t i = 0; i < was.size(); i++) note += (i ? ", " : "") + was[i];
        o->description(o->get_description() + note + ")");
    }
}

// Every name the App's options answer to ("--long", "-s"; the hidden ones too): tests/cli checks
// them against the options the old parsers had.
inline std::vector<std::string> option_names(const CLI::App& app) {
    std::vector<std::string> out;
    for (const CLI::Option* o : app.get_options()) {
        for (const std::string& n : o->get_lnames()) out.push_back("--" + n);
        for (const std::string& n : o->get_snames()) out.push_back("-" + n);
    }
    return out;
}

// Parses the command line. -1: go on; else the exit status: 0 after --help (printed on stdout), 2
// after an error (one line on stderr, "PROGRAM: OPTION: MESSAGE", and where to find the help).
inline int parse(CLI::App& app, int argc, const char* const* argv) {
    try {
        app.parse(argc, argv);
        return -1;
    } catch (const CLI::CallForHelp&) {
        fputs(app.help().c_str(), stdout);
        return 0;
    } catch (const CLI::ParseError& e) {
        // (CLI11's own messages for stray arguments start with the program's name already)
        std::string msg = e.what(), name = app.get_name();
        if (msg.compare(0, name.size() + 1, name + ":") != 0) msg = name + ": " + msg;
        fprintf(stderr, "%s\n(%s --help lists the options)\n", msg.c_str(), name.c_str());
        return 2;
    }
}

}  // namespace soa::cli

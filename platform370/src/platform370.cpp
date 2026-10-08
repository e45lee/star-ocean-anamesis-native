// platform370::install: registers the enabled pieces of the 3.7.0 platform layer with the
// runtime's extension points (platform370/README.md "API").
//
// The registration order is the one soa-emu had when each file registered itself from a static
// initializer (link order = file-name order): imports (hle_370.cpp), the clock (hle_370.cpp), the
// network redirect (net_370.cpp) at the end of hle_init(); the HTTP client (http_370.cpp), then
// the Java answers (java_370.cpp) at the end of Vm::init().
#include <stdio.h>
#include <time.h>

#include "core/device.h"
#include "core/hle.h"
#include "core/log.h"
#include "internal.h"
#include "jni/jvm.h"
#include "platform370/platform370.h"

#include <soa/local_time.h>

namespace soa::platform370 {
namespace {

bool g_installed = false;
bool g_patch = false;
NetConfig g_net;

// "YYYY-MM-DD HH:MM:SS" (local time) -> time_t; -1 when malformed.
time_t parse_clock(const std::string& s) {
    struct tm tm = {};
    if (sscanf(s.c_str(), "%d-%d-%d %d:%d:%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday, &tm.tm_hour, &tm.tm_min, &tm.tm_sec) != 6) return -1;
    tm.tm_year -= 1900, tm.tm_mon -= 1;
    return (time_t)soa::mktime_local(&tm);
}

}  // namespace

const NetConfig& net_config() { return g_net; }

bool detail::patch_enabled() { return g_patch; }

bool hides_global_key(std::string_view key) { return g_patch && key == detail::kHiddenGlobalKey; }

void install(const Config& cfg) {
    if (g_installed) fatal("platform370::install called twice");
    g_installed = true;
    g_patch = cfg.patch;
    g_net = cfg.netcfg;
    set_local_time(cfg.local_time);
    if (cfg.lang != "ja" && cfg.lang != "en") fatal("platform370: lang \"%s\": expected ja or en", cfg.lang.c_str());
    if (cfg.voice_lang != "ja" && cfg.voice_lang != "keep") fatal("platform370: voice_lang \"%s\": expected ja or keep", cfg.voice_lang.c_str());
    detail::set_language(cfg.lang, cfg.voice_lang);

    if (!cfg.app_version.empty()) device_config().app_version = cfg.app_version;

    if (cfg.clock) {
        if (cfg.device_clock == "host") LOGI("p370", "device clock: the host's real time");
        else {
            time_t want = parse_clock(cfg.device_clock);
            if (want == -1) fatal("--device-clock: expected \"YYYY-MM-DD HH:MM:SS\" or host, got \"%s\"", cfg.device_clock.c_str());
            detail::set_device_clock((s64)want - (s64)time(nullptr));
            LOGI("p370", "device clock starts at %s (local time) and runs on", cfg.device_clock.c_str());
        }
    } else if (cfg.device_clock != "host") {
        fatal("platform370: device_clock \"%s\" needs Config::clock", cfg.device_clock.c_str());
    }

    bool imports = cfg.imports, clock = cfg.clock, net = cfg.net, http = cfg.http, java = cfg.java;
    if (imports || clock || net)
        hle_add_registrar([=](Hle& h) {
            if (imports) detail::install_imports(h);
            if (clock) detail::install_clock(h);
            if (net) detail::install_net(h);
        });
    if (http || java)
        jni::add_class_installer([=](jni::Vm& vm) {
            if (http) detail::install_http(vm);
            if (java) detail::install_java(vm);
        });
    LOGI("p370", "3.7.0 platform: app_version %s; java %s, imports %s, clock %s, net %s, http %s, patch %s, local time %s, lang %s, voice-lang %s",
         cfg.app_version.empty() ? "(unchanged)" : cfg.app_version.c_str(), java ? "on" : "off", imports ? "on" : "off",
         clock ? "on" : "off", net ? "on" : "off", http ? "on" : "off", cfg.patch ? "on" : "off",
         !clock ? "off" : cfg.local_time ? "with daylight saving" : "standard (--no-dst-fix)", cfg.lang.c_str(),
         cfg.voice_lang.c_str());
}

}  // namespace soa::platform370

#pragma once
// platform370's pieces, as platform370.cpp (install) registers them. Not part of the public API
// (include/platform370/platform370.h).
#include <cstdint>
#include <string>

namespace soa {
class Hle;
}
namespace soa::jni {
class Vm;
}

namespace soa::platform370::detail {

// hle_370.cpp: the fmod import; the device clock's time overrides and its offset (device clock -
// host clock, seconds; 0 = the host's real time).
void install_imports(Hle& h);
void install_clock(Hle& h);
void set_device_clock(std::int64_t offset_seconds);

// net_370.cpp: getaddrinfo / gethostbyname / connect.
void install_net(Hle& h);

// http_370.cpp: the AskaActivity HTTP methods. java_370.cpp: the 3.7.0-only AskaActivity methods.
void install_http(jni::Vm& vm);
void install_java(jni::Vm& vm);

// patch_370.cpp: the master_global key the patch hides, and whether Config::patch is on.
constexpr const char kHiddenGlobalKey[] = "service_stop_day";
bool patch_enabled();

// lang_370.cpp: the language settings install() was given.
void set_language(const std::string& lang, const std::string& voice_lang);

}  // namespace soa::platform370::detail

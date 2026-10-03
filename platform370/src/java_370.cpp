// The Java side of the 3.7.0 client: what it calls through JNI that the offline build (and so the
// runtime's jni/java_android.cpp) doesn't have. Registered by platform370::install (Config::java)
// through the runtime's extension point (jni::add_class_installer), so the runtime itself is
// unchanged. docs/client-changes.md "Emulator mode" lists these answers.
//
// Names and signatures: the strings in work/libSOA-3.7.0.so that the offline build lacks, paired with the
// signature string loaded next to each name at its GetMethodID call site (Platform::Android::*
// around 0x1e38c04-0x1e39fb4; emulator/README.md "How the Java list was found").
//
// The answers are those of a phone without the services: no Google Play Games account (sign-in
// fails when asked for, no achievements), location unavailable, notifications accepted and
// dropped. Assumption (d): the exact values a real phone without Play Games returned aren't
// recorded anywhere we have; these are the natural "not available" values of each signature.
#include <atomic>
#include <cstring>

#include "core/device.h"
#include "core/log.h"
#include "internal.h"
#include "jni/jvm.h"

namespace soa::platform370::detail {
namespace {

using jni::Args;
using jni::Object;
using jni::Vm;

const char* const AA = "jb/Aska/AskaActivity";

// Set by ConnectPlayServices: the sign-in was attempted (and, with no Play Games, failed).
std::atomic<bool> g_play_connect_tried{false};
// Set by StartLocationCapture: the capture ran (and, with no location service, failed).
std::atomic<bool> g_location_tried{false};

u64 R(Object* o) { return (u64)o; }

}  // namespace

void install_java(Vm& vm) {
    // ---- Google Play Games (GamerServiceManager) ----
    vm.def(AA, "ConnectPlayServices", "()V", [](Object*, const Args&) -> u64 {
        LOGI("java", "ConnectPlayServices(): no Google Play Games on this device; sign-in fails");
        g_play_connect_tried = true;
        return 0;
    });
    vm.def(AA, "IsConnectedGooglePlayServices", "()Z", [](Object*, const Args&) -> u64 { return 0; });
    // false until a sign-in was attempted, then true: the attempt failed.
    vm.def(AA, "IsLoginFailedGooglePlayServices", "()Z", [](Object*, const Args&) -> u64 { return g_play_connect_tried ? 1 : 0; });

    // ---- achievements (the 11 Play Games achievement calls): none loaded, none shown ----
    vm.def(AA, "SetReportAchievementTarget", "(Ljava/lang/String;)V", [](Object*, const Args& a) -> u64 {
        LOGD("java", "SetReportAchievementTarget(%s) ignored (no Play Games)", jni::jstr(a[0]).c_str());
        return 0;
    });
    vm.def(AA, "ReportAchievement", "(I)V", [](Object*, const Args& a) -> u64 {
        LOGD("java", "ReportAchievement(%d) ignored (no Play Games)", (int)(s32)a[0]);
        return 0;
    });
    vm.def(AA, "ResetAchievements", "()V", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "ShowAchievements", "()V", [](Object*, const Args&) -> u64 {
        LOGI("java", "ShowAchievements(): no Play Games; nothing shown");
        return 0;
    });
    vm.def(AA, "IsShowingAchievements", "()Z", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "IsLoadedAchievements", "()Z", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "GetAchievementCurrentStep", "(Ljava/lang/String;)I", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "IsAchievementUnlocked", "(Ljava/lang/String;)Z", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "IsExistAchievement", "(Ljava/lang/String;)Z", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "NumAchievements", "()I", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "GetAchievementId", "(I)Ljava/lang/String;", [&vm](Object*, const Args&) -> u64 { return R(vm.str("")); });

    // ---- location: the service is unavailable; a capture finishes at once, unsuccessfully ----
    vm.def(AA, "StartLocationCapture", "()V", [](Object*, const Args&) -> u64 {
        LOGI("java", "StartLocationCapture(): no location service; the capture fails");
        g_location_tried = true;
        return 0;
    });
    vm.def(AA, "StopLocationCapture", "()V", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "IsUpdateLocation", "()Z", [](Object*, const Args&) -> u64 { return g_location_tried ? 1 : 0; });
    vm.def(AA, "IsSucceedLocation", "()Z", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "IsRequestLocationPermission", "()Z", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "GetLocationErrorCode", "()I", [](Object*, const Args&) -> u64 { return g_location_tried ? 1 : 0; });
    vm.def(AA, "GetLocationX", "()D", [](Object*, const Args&) -> u64 { return 0; });  // 0.0
    vm.def(AA, "GetLocationY", "()D", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "OpenLocationSetting", "()V", [](Object*, const Args&) -> u64 {
        LOGI("java", "OpenLocationSetting() ignored");
        return 0;
    });
    vm.def(AA, "OpenApplicationSettings", "()V", [](Object*, const Args&) -> u64 {
        LOGI("java", "OpenApplicationSettings() ignored");
        return 0;
    });

    // ---- local notifications ----
    vm.def(AA, "UnScheduleLocalNotification", "()V", [](Object*, const Args&) -> u64 { return 0; });

    // The HTTP methods (HttpRequest, GetStatusCode, GetHttpHeader, ReadHttpResponse,
    // AbortHttpRequest, SetHttpUserAgent) aren't here: http_370.cpp (Config::http) overrides them
    // with a host HTTP client; without it they stay as the runtime has them (refused, offline).
}

}  // namespace soa::platform370::detail

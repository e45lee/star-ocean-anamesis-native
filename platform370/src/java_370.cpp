// The Java side of the 3.7.0 client: what it calls through JNI that the offline build (and so the
// runtime's jni/java_android.cpp) doesn't have. Registered by platform370::install (Config::java)
// through the runtime's extension point (jni::add_class_installer), so the runtime itself is
// unchanged. docs/client-changes.md "Emulator mode" lists these answers.
//
// Names and signatures: the strings in work/libSOA-3.7.0.so that the offline build lacks, paired with the
// signature string loaded next to each name at its GetMethodID call site (Platform::Android::*
// around 0x1e38c04-0x1e39fb4; emulator/README.md "How the Java list was found").
//
// The in-app billing methods (install_billing) are a local store instead: the coin shop's
// purchases complete for nothing (the user's decision; docs/client-changes.md "In-app billing").
//
// The other answers are those of a phone without the services: no Google Play Games account (sign-in
// fails when asked for, no achievements), location unavailable, notifications accepted and
// dropped. Assumption (d): the exact values a real phone without Play Games returned aren't
// recorded anywhere we have; these are the natural "not available" values of each signature.
#include <atomic>
#include <cstring>
#include <mutex>
#include <string>

#include "soaruntime/core/device.h"
#include "soaruntime/core/log.h"
#include "soaruntime/core/vfs.h"
#include "internal.h"
#include "soaruntime/jni/jvm.h"

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

// ---- in-app billing (jb.Aska.InAppBilling behind AskaActivity; the coin shop's store) ----------
// Port-specific platform answer (docs/client-changes.md "In-app billing"): the store completes
// every purchase at once and charges nothing (the user's decision, docs/unimplemented-apis.md
// "Decisions"); the local server credits the stones (server/src/api/shop/coins.cpp). The Java
// contract is the APK's (classes.dex, jadx): RequestProduct answers 5 strings per product
// (productId, title, type, description, price); PurchaseProduct starts the purchase (0 = started)
// and GetPurchaseProductResult then answers {Integer resultCode (0 = RESULT_OK as the activity
// maps it), Integer RESPONSE_CODE, String signature, String purchase data} once; ConsumeProduct and
// CanPurchaseDevice answer 0 (OK); ReverifyProduct lists the purchases not yet consumed (null: none).
std::mutex g_billing_m;
Object* g_purchase_result = nullptr;  // the finished purchase GetPurchaseProductResult hands over once
u64 g_purchase_count = 0;

std::string json_escape(const std::string& s) {
    std::string o;
    for (char ch : s) {
        if (ch == '"' || ch == '\\') o += '\\';
        if ((unsigned char)ch >= 0x20) o += ch;
    }
    return o;
}

void install_billing(Vm& vm) {
    vm.def(AA, "CanPurchaseDevice", "()I", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "RequestProduct", "([Ljava/lang/String;)[Ljava/lang/String;", [&vm](Object*, const Args& a) -> u64 {
        auto* skus = (jni::Array*)a[0];
        size_t n = skus ? skus->objs.size() : 0;
        jni::Array* out = vm.new_array('L', n * 5, vm.find_class("java/lang/String"));
        for (size_t i = 0; i < n; i++) {
            std::string sku = skus->objs[i] ? ((jni::String*)skus->objs[i])->utf8 : std::string();
            // the title and description are the client's own (CPaymentManager::
            // SetProductDetailFromCoinInfo_ sets them from the CoinList); nothing is charged
            const char* fields[5] = {sku.c_str(), sku.c_str(), "inapp", "", "\xEF\xBF\xA5" "0"};
            for (int k = 0; k < 5; k++) out->objs[i * 5 + k] = vm.str(fields[k]);
        }
        LOGI("java", "RequestProduct(%zu products): the local store knows every product", n);
        return R(out);
    });
    vm.def(AA, "PurchaseProduct", "(Ljava/lang/String;Ljava/lang/String;)I", [&vm](Object*, const Args& a) -> u64 {
        std::string sku = jni::jstr(a[0]), payload = jni::jstr(a[1]);
        std::lock_guard lk(g_billing_m);
        u64 n = ++g_purchase_count;
        std::string token = "local-purchase-" + std::to_string(n);
        std::string data = "{\"orderId\":\"LOCAL." + std::to_string(n) + "\",\"packageName\":\"" + std::string(kPackageName) +
                           "\",\"productId\":\"" + json_escape(sku) + "\",\"purchaseTime\":0,\"purchaseState\":0,\"developerPayload\":\"" +
                           json_escape(payload) + "\",\"purchaseToken\":\"" + token + "\"}";
        jni::Array* r = vm.new_array('L', 4);
        r->objs[0] = vm.integer(0);  // the activity's result: RESULT_OK
        r->objs[1] = vm.integer(0);  // RESPONSE_CODE: BILLING_RESPONSE_RESULT_OK
        // INAPP_DATA_SIGNATURE: never empty: GooglePlayUtil::JNI_WaitPurchaseProductResult (@0269fa24)
        // substitutes a static "" for an empty one and then frees it (a crash); the local server
        // checks nothing
        r->objs[2] = vm.str("local-store");
        r->objs[3] = vm.str(data);   // INAPP_PURCHASE_DATA
        g_purchase_result = r;
        LOGI("java", "PurchaseProduct(%s, payload %s): completed by the local store, nothing charged", sku.c_str(), payload.c_str());
        return 0;
    });
    vm.def(AA, "GetPurchaseProductResult", "()[Ljava/lang/Object;", [](Object*, const Args&) -> u64 {
        std::lock_guard lk(g_billing_m);
        Object* r = g_purchase_result;
        g_purchase_result = nullptr;
        return R(r);
    });
    vm.def(AA, "ConsumeProduct", "(Ljava/lang/String;)I", [](Object*, const Args& a) -> u64 {
        LOGI("java", "ConsumeProduct(%s)", jni::jstr(a[0]).c_str());
        return 0;
    });
    vm.def(AA, "ReverifyProduct", "()[Ljava/lang/String;", [](Object*, const Args&) -> u64 { return 0; });
}

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

    install_billing(vm);

    // The HTTP methods (HttpRequest, GetStatusCode, GetHttpHeader, ReadHttpResponse,
    // AbortHttpRequest, SetHttpUserAgent) aren't here: http_370.cpp (Config::http) overrides them
    // with a host HTTP client; without it they stay as the runtime has them (refused, offline).
}

}  // namespace soa::platform370::detail

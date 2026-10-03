// Java-side classes the game calls through JNI: jb.Aska.AskaActivity, SOAActivity, and the
// bits of the Android framework / Play Core they touch.
#include <sys/stat.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <sys/statvfs.h>
#endif
#include <unistd.h>

#include <cstring>
#include <ctime>

#include "android/platform.h"
#include "android/prefs.h"
#include "core/device.h"
#include "core/log.h"
#include "core/vfs.h"
#include "jni/jvm.h"

namespace soa::jni {

namespace {

u64 R(Object* o) { return (u64)o; }
u64 f32bits(float f) {
    u32 b;
    memcpy(&b, &f, 4);
    return b;
}
Array* ba(u64 r) { return (Array*)r; }

}  // namespace

void install_android_classes(Vm& vm) {
    // ---- java.lang ----
    vm.define_class("java/lang/Boolean");
    vm.def("java/lang/Boolean", "booleanValue", "()Z", [](Object* s, const Args&) -> u64 { return ((Instance*)s)->value & 1; });
    vm.define_class("java/lang/Integer");
    vm.def("java/lang/Integer", "intValue", "()I", [](Object* s, const Args&) -> u64 { return ((Instance*)s)->value; });
    vm.def("java/lang/Object", "toString", "()Ljava/lang/String;", [&vm](Object* s, const Args&) -> u64 {
        if (s && s->cls && s->cls->name == "java/lang/String") return R(s);
        return R(vm.str(s && s->cls ? s->cls->name : "null"));
    });
    vm.def("java/lang/Object", "getClass", "()Ljava/lang/Class;", [](Object* s, const Args&) -> u64 { return R(s ? s->cls : nullptr); });
    vm.def("java/lang/Class", "getName", "()Ljava/lang/String;", [&vm](Object* s, const Args&) -> u64 {
        std::string n = ((Class*)s)->name;
        for (auto& c : n)
            if (c == '/') c = '.';
        return R(vm.str(n));
    });
    vm.define_class("java/lang/ClassLoader");
    vm.def("java/lang/ClassLoader", "loadClass", "(Ljava/lang/String;)Ljava/lang/Class;",
           [&vm](Object*, const Args& a) -> u64 { return R(vm.find_class(jstr(a[0]))); });

    // ---- java.io.File ----
    vm.define_class("java/io/File");
    auto file_path = [&vm](Object* s, const Args&) -> u64 { return R(vm.str(((String*)((Instance*)s)->fields["path"])->utf8)); };
    vm.def("java/io/File", "getAbsolutePath", "()Ljava/lang/String;", file_path);
    vm.def("java/io/File", "getPath", "()Ljava/lang/String;", file_path);
    auto make_file = [&vm](const std::string& p) {
        Instance* f = vm.instance("java/io/File");
        f->fields["path"] = R(vm.str(p));
        return f;
    };

    // ---- android.view ----
    vm.define_class("android/view/WindowManager");
    vm.define_class("android/view/Display");
    vm.def("android/view/WindowManager", "getDefaultDisplay", "()Landroid/view/Display;",
           [&vm](Object*, const Args&) -> u64 { return R(vm.instance("android/view/Display")); });
    vm.def("android/view/Display", "getRefreshRate", "()F", [](Object*, const Args&) -> u64 { return f32bits(60.0f); });
    vm.def("android/view/Display", "getRotation", "()I", [](Object*, const Args&) -> u64 { return 0; });

    // ---- activity hierarchy ----
    vm.define_class("android/content/Context");
    vm.define_class("android/app/Activity", "android/content/Context");
    vm.define_class("android/app/NativeActivity", "android/app/Activity");
    vm.define_class("jb/Aska/AskaActivity", "android/app/NativeActivity");
    const std::string SOA = "com/square_enix/android_googleplay/StarOceanj/SOAActivity";
    vm.define_class(SOA, "jb/Aska/AskaActivity");

    const std::string ACT = "android/app/Activity";
    vm.def(ACT, "getWindowManager", "()Landroid/view/WindowManager;", [&vm](Object*, const Args&) -> u64 { return R(vm.instance("android/view/WindowManager")); });
    vm.def(ACT, "getClassLoader", "()Ljava/lang/ClassLoader;", [&vm](Object*, const Args&) -> u64 { return R(vm.instance("java/lang/ClassLoader")); });
    vm.def(ACT, "getFilesDir", "()Ljava/io/File;", [make_file](Object*, const Args&) -> u64 { return R(make_file(guest_internal_dir())); });
    vm.def(ACT, "getCacheDir", "()Ljava/io/File;", [make_file](Object*, const Args&) -> u64 { return R(make_file(guest_cache_dir())); });
    vm.def(ACT, "getExternalFilesDir", "(Ljava/lang/String;)Ljava/io/File;",
           [make_file](Object*, const Args&) -> u64 { return R(make_file(guest_external_dir())); });
    vm.def(ACT, "getPackageName", "()Ljava/lang/String;", [&vm](Object*, const Args&) -> u64 { return R(vm.str(kPackageName)); });

    // ---- jb.Aska.AskaActivity ----
    const std::string AA = "jb/Aska/AskaActivity";
    vm.def(AA, "GetSharedPreferences", "(Ljava/lang/String;Ljava/lang/String;)[B", [&vm](Object*, const Args& a) -> u64 {
        auto v = SharedPrefs::get().get_bytes(jstr(a[0]), jstr(a[1]));
        return R(vm.byte_array(v.data(), v.size()));
    });
    vm.def(AA, "SetSharedPreferences", "(Ljava/lang/String;Ljava/lang/String;[B)Ljava/lang/Boolean;", [&vm](Object*, const Args& a) -> u64 {
        Array* arr = ba(a[2]);
        std::vector<unsigned char> v;
        if (arr) v.assign(arr->data.begin(), arr->data.end());
        SharedPrefs::get().set_bytes(jstr(a[0]), jstr(a[1]), v);
        return R(vm.boolean(true));
    });
    vm.def(AA, "RemoveSharedPreferences", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Boolean;", [&vm](Object*, const Args& a) -> u64 {
        SharedPrefs::get().remove(jstr(a[0]), jstr(a[1]));
        return R(vm.boolean(true));
    });
    vm.def(AA, "ClearSharedPreferences", "(Ljava/lang/String;)Ljava/lang/Boolean;", [&vm](Object*, const Args& a) -> u64 {
        SharedPrefs::get().clear(jstr(a[0]));
        return R(vm.boolean(true));
    });
    auto real_w = [](Object*, const Args&) -> u64 { return (u64)platform().width.load(); };
    auto real_h = [](Object*, const Args&) -> u64 { return (u64)platform().height.load(); };
    vm.def(AA, "GetRealWidth", "()I", real_w);
    vm.def(AA, "GetRealHeight", "()I", real_h);
    vm.def(AA, "IsMaterialDesign", "()I", [](Object*, const Args&) -> u64 { return 1; });
    vm.def(AA, "IsDebugMode", "()Ljava/lang/Boolean;", [&vm](Object*, const Args&) -> u64 { return R(vm.boolean(false)); });
    vm.def(AA, "GetAndroidID", "()Ljava/lang/String;", [&vm](Object*, const Args&) -> u64 { return R(vm.str("0123456789abcdef")); });
    vm.def(AA, "GetMacAddress", "()Ljava/lang/String;", [&vm](Object*, const Args&) -> u64 { return R(vm.str("02:00:00:00:00:00")); });
    vm.def(AA, "GetAudioLatency", "()F", [](Object*, const Args&) -> u64 { return f32bits(45.0f); });
    vm.def(AA, "GetBatteryChargeCounter", "()I", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "GetBatteryCurrentAverage", "()I", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "GetBatteryCurrentNow", "()I", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "GetBatteryEnergyCounter", "()J", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "CallbackKeyEvent", "(II)V", [](Object*, const Args&) -> u64 { return 0; });
    // Networking bridge: the offline build has no server.
    vm.def(AA, "HttpRequest", "(Ljava/lang/String;ILjava/lang/String;Z)I", [](Object*, const Args& a) -> u64 {
        LOGW("java", "HttpRequest(%s) refused (offline)", jstr(a[0]).c_str());
        return (u64)-1;
    });
    vm.def(AA, "GetStatusCode", "()I", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "GetHttpHeader", "()Ljava/lang/String;", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "ReadHttpResponse", "([B)I", [](Object*, const Args&) -> u64 { return (u64)-1; });
    vm.def(AA, "CloseHttpRequest", "()V", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "SetHttpProxy", "(ILjava/lang/String;)V", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(AA, "InitX509", "(I)Ljava/lang/Boolean;", [&vm](Object*, const Args&) -> u64 { return R(vm.boolean(false)); });
    vm.def(AA, "AddDERX509", "([BI)Ljava/lang/Boolean;", [&vm](Object*, const Args&) -> u64 { return R(vm.boolean(false)); });
    vm.def(AA, "EvaluateX509", "()Ljava/lang/Boolean;", [&vm](Object*, const Args&) -> u64 { return R(vm.boolean(false)); });

    // ---- SOAActivity ----
    vm.def(SOA, "GetDisplayWidth", "()I", real_w);
    vm.def(SOA, "GetDisplayHeight", "()I", real_h);
    vm.def(SOA, "GetRealWidth", "()I", real_w);
    vm.def(SOA, "GetRealHeight", "()I", real_h);
    for (const char* n : {"GetSafeAreaTop", "GetSafeAreaBottom", "GetSafeAreaLeft", "GetSafeAreaRight", "GetStatusBarHeight"})
        vm.def(SOA, n, "()I", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(SOA, "GetOSVersion", "()I", [](Object*, const Args&) -> u64 { return 30; });
    vm.def(SOA, "GetNetworkStatus", "()I", [](Object*, const Args&) -> u64 { return 1; });
    vm.def(SOA, "GetApplicationID", "()Ljava/lang/String;", [&vm](Object*, const Args&) -> u64 { return R(vm.str(kPackageName)); });
    vm.def(SOA, "GetApplicationVersion", "()Ljava/lang/String;", [&vm](Object*, const Args&) -> u64 { return R(vm.str(device_config().app_version)); });
    vm.def(SOA, "GetDeviceName", "()Ljava/lang/String;", [&vm](Object*, const Args&) -> u64 { return R(vm.str("Linux Desktop")); });
    vm.def(SOA, "GetDeviceAdvertisementID", "()Ljava/lang/String;", [&vm](Object*, const Args&) -> u64 { return R(vm.str("")); });
    vm.def(SOA, "GetDeviceToken", "()Ljava/lang/String;", [&vm](Object*, const Args&) -> u64 { return R(vm.str("")); });
    vm.def(SOA, "GetUniqueUserID", "()Ljava/lang/String;", [&vm](Object*, const Args&) -> u64 {
        auto v = SharedPrefs::get().get_bytes("SOAActivity", "UniqueUserID");
        std::string id(v.begin(), v.end());
        if (id.empty()) {
            char buf[40];
            srand((unsigned)time(nullptr) ^ getpid());
            snprintf(buf, sizeof buf, "%08x-%04x-4%03x-a%03x-%08x%04x", rand(), rand() & 0xffff, rand() & 0xfff, rand() & 0xfff, rand(), rand() & 0xffff);
            id = buf;
            SharedPrefs::get().set_bytes("SOAActivity", "UniqueUserID", {id.begin(), id.end()});
        }
        return R(vm.str(id));
    });
    vm.def(SOA, "GetBattery", "()F", [](Object*, const Args&) -> u64 { return f32bits(100.0f); });
    vm.def(SOA, "GetBattery_State", "()I", [](Object*, const Args&) -> u64 { return 1; });
    auto mem = [](Object*, const Args&) -> u64 { return (u64)512 << 20; };
    for (const char* n : {"GetAvailableHeapSize", "GetHeapMaxSize", "GetJavaHeapFreeSize", "GetJavaHeapTotalSize", "GetNativeHeapAllocatedSize", "GetNativeHeapFreeSize",
                          "GetNativeHeapSize"})
        vm.def(SOA, n, "()J", mem);
    auto free_space = [](Object*, const Args&) -> u64 {
#ifdef _WIN32
        ULARGE_INTEGER avail;
        if (!GetDiskFreeSpaceExA(vfs_config().root.c_str(), &avail, nullptr, nullptr)) return (u64)8 << 30;
        return (u64)avail.QuadPart;
#else
        struct statvfs s;
        if (statvfs(vfs_config().root.c_str(), &s) != 0) return (u64)8 << 30;
        return (u64)s.f_bavail * s.f_frsize;
#endif
    };
    vm.def(SOA, "GetDeviceFreeSize", "()J", free_space);
    vm.def(SOA, "GetSDCardFreeSize", "()J", free_space);
    vm.def(SOA, "IsMaterialDesign", "()I", [](Object*, const Args&) -> u64 { return 1; });
    for (const char* n : {"IsShowingWebView", "IsInstalledLine", "IsLoginFacebook", "IsLoginTwitter"})
        vm.def(SOA, n, "()Z", [](Object*, const Args&) -> u64 { return 0; });
    for (const char* n : {"InitMovie", "PopSplashImage", "PushSplashImage", "PrintMemorySize", "StopMovie", "ExitApplication"})
        vm.def(SOA, n, "()V", [n](Object*, const Args&) -> u64 {
            LOGD("java", "SOAActivity.%s()", n);
            if (!strcmp(n, "ExitApplication")) platform().quit_requested = true;
            return 0;
        });
    for (const char* n : {"ClipBoard", "OpenBrowser", "SetRootURI", "RequestMediaScannerConnection", "InviteByFacebook", "InviteByLine", "InviteByTwitter"})
        vm.def(SOA, n, "(Ljava/lang/String;)V", [n](Object*, const Args& a) -> u64 {
            LOGI("java", "SOAActivity.%s(\"%s\")", n, jstr(a[0]).c_str());
            return 0;
        });
    vm.def(SOA, "LockSleep", "(I)V", [](Object*, const Args&) -> u64 { return 0; });
    vm.def(SOA, "GetFileModificationDate", "(Ljava/lang/String;)Ljava/lang/String;", [&vm](Object*, const Args& a) -> u64 {
        struct stat st;
        time_t t = 0;
        if (stat(host_path(jstr(a[0]).c_str()).c_str(), &st) == 0) t = st.st_mtime;
        char buf[32];
        strftime(buf, sizeof buf, "%Y/%m/%d %H:%M:%S", localtime(&t));
        return R(vm.str(buf));
    });
    vm.def(SOA, "ClearCache", "(Ljava/lang/String;)Z", [](Object*, const Args& a) -> u64 {
        LOGW("java", "ClearCache(%s) ignored", jstr(a[0]).c_str());
        return 1;
    });
    // (The port overrides it to show its local server's pages: port/src/native/ui/webview_local.cpp.)
    vm.def(SOA, "ShowWebView", "(Ljava/lang/String;IIIIZLjava/lang/String;ZIII)V", [](Object*, const Args& a) -> u64 {
        LOGI("java", "ShowWebView(%s) not supported", jstr(a[0]).c_str());
        return 0;
    });
    vm.def(SOA, "RequestPermissions", "(Ljava/lang/String;[Ljava/lang/String;Ljava/lang/String;)V", [](Object*, const Args&) -> u64 { return 0; });

    // Movies (MoviePlayerActivity)
    vm.def(SOA, "PlayMovie", "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Z)V", [](Object*, const Args& a) -> u64 {
        auto& p = platform();
        p.movie_path = jstr(a[0]);
        p.movie_volume = (s32)a[1] / 100.0f;
        p.movie_is_file = a[5] & 1;
        LOGI("java", "PlayMovie(%s, vol=%d, file=%d)", p.movie_path.c_str(), (int)(s32)a[1], (int)(a[5] & 1));
        frontend_play_movie();  // sets movie_playing once the movie runs
        return 0;
    });
    vm.def(SOA, "MovieFinished", "()Z", [](Object*, const Args&) -> u64 { return !platform().movie_playing; });

    // Text entry (KeyboardActivity)
    vm.def(SOA, "StartKeyboardActivity", "(IIILjava/lang/String;)V", [](Object*, const Args& a) -> u64 {
        auto& p = platform();
        {
            std::lock_guard lk(p.text_mutex);
            p.text_numeric = (s32)a[0] == 1;
            p.text_max_len = (s32)a[2];
            p.text_editing = jstr(a[3]);
            p.text_value.clear();
            p.text_cursor = p.text_editing.size();
            p.text_composition.clear();
            p.text_comp_cursor = 0;
            p.text_serial++;
        }
        LOGI("java", "StartKeyboardActivity(type=%d, lines=%d, max=%d, \"%s\")", (int)(s32)a[0], (int)(s32)a[1], (int)(s32)a[2], jstr(a[3]).c_str());
        p.text_active = true;
        frontend_start_text_input();
        return 0;
    });
    vm.def(SOA, "IsEndKeyboardActivity", "()Z", [](Object*, const Args&) -> u64 { return !platform().text_active; });
    vm.def(SOA, "GetEditText", "()Ljava/lang/String;", [&vm](Object*, const Args&) -> u64 {
        std::lock_guard lk(platform().text_mutex);
        return R(vm.str(platform().text_value));
    });

    // Activity instance
    vm.activity = vm.instance(SOA);
}

}  // namespace soa::jni

#pragma once
// The emulated Android device and the installed app, as the host program configures them before
// the game starts (the port fills it from its run options: port/src/main.cpp). The runtime knows
// nothing about which build of the game it runs; whatever differs between builds is set here or
// through the extension points (runtime/README.md).
#include <string>

namespace soa {

struct DeviceConfig {
    // CPUs the guest sees (sysconf(_SC_NPROCESSORS_*) in hle/libc_misc.cpp,
    // /sys/devices/system/cpu/{present,possible} in core/vfs.cpp); 0 = the host's count.
    int guest_cpus = 8;
    // The app's versionName, returned by SOAActivity.GetApplicationVersion (jni/java_android.cpp).
    std::string app_version;
};

DeviceConfig& device_config();

}  // namespace soa

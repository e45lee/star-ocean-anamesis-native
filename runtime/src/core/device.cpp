// The emulated device's configuration (see device.h).
#include "soaruntime/core/device.h"

namespace soa {

DeviceConfig& device_config() {
    static DeviceConfig c;
    return c;
}

}  // namespace soa

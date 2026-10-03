// The battle log on the FakeApiCaller route (client_battle_log.h): the 3.7.0 request lambdas'
// serialization, made with the client's own functions (guest calls), so the bytes are the ones
// NetworkApiCaller would send.
#include "native/api/client_battle_log.h"

#include "native/common/guest_std.h"
#include "soaserver/battle_log.h"

namespace soa::server_port {

namespace {
// Aska::ASON is 0x90 bytes (the lambdas' stack object); a little room to spare.
constexpr size_t kAsonSize = 0x200;
}  // namespace

bool serialize_battle_log(u64 info, std::vector<u8>* out, s64* size) {
    out->clear();
    *size = 0;
    u64 ctor = guest::sym("_ZN4Aska4ASONC1Ev");
    u64 ser = guest::sym("_ZN14AsonSerializer9SerializeI14CBattleLogInfoEEvRT_jmb");
    u64 calc = guest::sym("_ZNK4Aska4ASON18CalcSerializedSizeEv");
    u64 write = guest::sym("_ZNK4Aska4ASON9SerializeEPvm");
    u64 dtor = guest::sym("_ZN4Aska4ASOND1Ev");
    if (!ctor || !ser || !calc || !write || !dtor || !info) return false;
    std::vector<u8> ason(kAsonSize, 0);
    u64 a = (u64)ason.data();
    guest_call(ctor, {a});
    guest_call(ser, {a, info, 0, 0x4000, 1});
    *size = (s64)guest_call(calc, {a});
    bool ok = false;
    // (b) `if (size < 0x1001 && (n = ason.Serialize(buf, size)) >= 0)`: the lambdas' check (an
    // unsigned compare, so a negative size fails it too)
    if ((u64)*size <= server::kMaxBattleLog) {
        std::vector<u8> buf(server::kMaxBattleLog);
        s64 n = (s64)guest_call(write, {a, (u64)buf.data(), (u64)*size});
        if (n >= 0 && (u64)n <= server::kMaxBattleLog) {  // the lambdas send n bytes (Serialize's result)
            out->assign(buf.begin(), buf.begin() + (size_t)n);
            ok = true;
        } else {
            *size = n;
        }
    }
    guest_call(dtor, {a});
    return ok;
}

bool client_battle_log(std::vector<u8>* out, s64* size) {
    u64 slot = guest::sym("_ZN9Framework10TSingletonI17CParameterManagerE11m_pInstanceE");
    u64 pm = slot ? *(u64*)slot : 0;
    if (!pm) {
        out->clear();
        *size = 0;
        return false;
    }
    return serialize_battle_log(pm + kParamBattleLogInfo, out, size);
}

}  // namespace soa::server_port

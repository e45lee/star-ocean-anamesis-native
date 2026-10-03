#pragma once
// The battle log a MissionEnd carries (library code; the format is the client's).
//
// (b) NetworkApiCaller::MissionEnd, MissionFailed, Sphere211MissionEnd and Sphere211MissionFailed
// each pass BeginBridge a lambda (3.7.0 @015d68bc, @015d7048, @015f09e8, @015f0c18) that
// serializes the client's CBattleLogInfo (CParameterManager+0x52d8) as ASON:
// AsonSerializer::Serialize<CBattleLogInfo>(ason, log, 0, 0x4000, 1), then
// ASON::CalcSerializedSize / ASON::Serialize; a log over 0x1000 bytes is not sent (nor is the
// request). The bytes go on the wire as the request's blob argument. They are MessagePack
// (docs/ason.md "Battle log"): a map of u32/bool properties ("mission_time", "damage_total", ...)
// and arrays, among them "BattleEvaluationInfo" [{evaluation_type, score}].
//
// soa-server's wire decoder (server/net/wire.cpp) and soa's FakeApiCaller route
// (port/src/native/api/server_adapters.cpp, which runs the same client serializer) both attach the
// bytes to the request as Request::battle_log through parse_battle_log.
#include <cstddef>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include "soaserver/msgpack.h"

namespace soa::server {

// The largest log the client sends (the lambdas' buffer).
constexpr size_t kMaxBattleLog = 0x1000;

class BattleLog {
public:
    BattleLog() = default;
    BattleLog(std::vector<uint8_t> ason, Value root) : ason_(std::move(ason)), root_(std::move(root)) {}
    // The bytes as the client serialized them.
    const std::vector<uint8_t>& ason() const { return ason_; }
    const Value& root() const { return root_; }
    // A u32 property by name (bool -> 0/1); dflt when missing or not a number.
    uint32_t prop_u32(const char* name, uint32_t dflt) const;
    // (b) The battle's evaluation value of `type` (1..6) from "BattleEvaluationInfo": the last entry
    // of the type (CBattleLogModel::EndMission appends one per type); -1 when none.
    int64_t evaluation(int type) const;

private:
    std::vector<uint8_t> ason_;
    Value root_;
};

// The APIs whose blob argument is the battle log (Request::method / the wire API's name).
bool carries_battle_log(const std::string& method);

// The log in `p`; nullptr when the bytes aren't a MessagePack map (or n == 0).
std::shared_ptr<const BattleLog> parse_battle_log(const uint8_t* p, size_t n);

}  // namespace soa::server

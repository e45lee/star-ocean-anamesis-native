#pragma once
// The battle log on the FakeApiCaller route (port code over guest calls): the bytes the 3.7.0
// NetworkApiCaller sends with MissionEnd, MissionFailed, Sphere211MissionEnd and
// Sphere211MissionFailed, made by the client's own serializer (soaserver/battle_log.h).
#include <cstdint>
#include <vector>

#include "core/cpu.h"

namespace soa::server_port {

// (b) CParameterManager+0x52d8: the CBattleLogInfo the request lambdas serialize (3.7.0 @015d68bc
// and its three siblings: `AsonSerializer::Serialize<CBattleLogInfo>(ason, pm + 0x52d8, 0,
// 0x4000, 1)`).
constexpr u64 kParamBattleLogInfo = 0x52d8;

// Serializes the CBattleLogInfo at `info` as the lambdas do: ASON(), AsonSerializer::Serialize
// <CBattleLogInfo>(ason, info, 0, 0x4000, 1), ASON::CalcSerializedSize(), and, when that is at most
// 0x1000, ASON::Serialize(buf, size). *size = the serialized size (or the negative status). False
// when the client would send nothing: over 0x1000 bytes (the request isn't sent then) or a failed
// Serialize.
bool serialize_battle_log(u64 info, std::vector<u8>* out, s64* size);

// The same on the live client's log (CParameterManager+0x52d8); false without a CParameterManager.
bool client_battle_log(std::vector<u8>* out, s64* size);

// (b) CParameterManager+0x8790: the CCharacterDecoSendInfo SetCharacterDeco's request lambda
// (3.7.0 @015ef218) serializes: AsonSerializer::Serialize<CCharacterDecoSendInfo>(ason, pm + 0x8790,
// 0, 0x4000, 1), CalcSerializedSize, Serialize into a buffer of that size (no size limit).
constexpr u64 kParamCharacterDecoSend = 0x8790;

// The SetCharacterDeco payload of the live client, made as that lambda makes it (the bytes
// NetworkApiCaller sends as the request's blob); false without a CParameterManager or when the
// serializer fails (the lambda sends nothing then).
bool client_character_deco(std::vector<u8>* out);

}  // namespace soa::server_port

#pragma once
// Building responses (port code, not guest behaviour): the one envelope and the one refusal path
// the modules share. ext.h declares body() and refuse() (the public module API); they are defined
// in core/response.cpp. ARCHITECTURE.md "Transactions, refusals and errors" is the contract.
#include <vector>

#include "core/errors.h"
#include "soaserver/ext.h"

namespace soa::server::ext {

// The answer that is the player state only, {Time, Player, Wallet}: body(c.base_data()).
std::vector<u8> with_player_state(Ctx& c);

// refuse() with the reason formatted printf-style: logs "<method> refused: <why> (error N)",
// records the code, answers the player state.
std::vector<u8> refusef(Ctx& c, const char* method, ErrorCode code, const char* why_fmt, ...) __attribute__((format(printf, 4, 5)));

}  // namespace soa::server::ext

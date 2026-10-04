#pragma once
// The gacha (port code, not guest behaviour): the draws and GetGachaInData (gacha.cpp), step-up
// chains (stepup.cpp), box gacha (box.cpp) and the rate dialog (rates.cpp). The pools are
// master/gacha_pools.h's (ctx.pools). docs/server-rules.md "4. Gacha", "Gacha: step-up and box".
#include <vector>

#include "soaserver/ext.h"

namespace soa::server {

// (a) master_gacha.opened_at / closed_at, or --enable-events (gacha.cpp).
bool gacha_open(ext::Ctx& ctx, const ext::Row& gacha_row, ServerTime t);
// The step-up chain of gacha `id`, step 1 first (stepup.cpp).
std::vector<u32> stepup_chain(ext::Ctx& ctx, u32 id);
// Whether the step `current` is closed after `restarts` laps.
bool stepup_closed(ext::Ctx& ctx, u32 current, u32 restarts);
// StepUpGacha (CStepUpGachaInfoList, a map keyed by step): every open chain, or only the chain of
// `only_head` (UpdateStepUpGacha).
Value stepup_gacha_info(ext::Ctx& ctx, u32 only_head = 0);
// BoxGacha (CBoxGachaInfo map, keyed by slot): the slots of box `gacha` (into `*into` when given)
// (box.cpp).
Value box_gacha_info(ext::Ctx& ctx, u32 gacha, Value* into = nullptr);
// BoxGachaList (CBoxGachaListInfo map, keyed by box): every open series, or only the series of
// box `only`; the current box's slots into `*slots` when given.
Value box_gacha_list_info(ext::Ctx& ctx, u32 only = 0, Value* slots = nullptr);

// The handlers (registered by register_gacha / register_box_gacha / register_gacha_rate).
std::vector<u8> get_gacha_in_data(ext::Ctx& ctx, const Request& req);
std::vector<u8> gacha(ext::Ctx& ctx, const Request& req);
std::vector<u8> box_gacha(ext::Ctx& ctx, const Request& req);
std::vector<u8> reset_box_gacha(ext::Ctx& ctx, const Request& req);
std::vector<u8> get_box_gacha(ext::Ctx& ctx, const Request& req);
// GetGachaRate from the pools (rates.cpp; get_gacha_rate answers the player state without them).
std::vector<u8> gacha_rate_from_pools(ext::Ctx& ctx, const Request& req);

}  // namespace soa::server

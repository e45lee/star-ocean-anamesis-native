// GetGachaRate: the rate dialog (api/gacha/gacha.h). Port code, not guest behaviour.
// Every rule carries its source label, (a) master data, (b) client-side evidence, (c) outside
// knowledge, (d) assumption (docs/server-rules.md#gacha-rules).
#include "api/gacha/gacha.h"

#include "api/player/player_info.h"  // base_data
#include "core/log.h"
#include "core/request_args.h"
#include "master/gacha_pools.h"

namespace soa::server {

using ext::body;
using ext::Row;

namespace {

// One CGachaRateInfo page {id, title, introduction_msg, bonus_msg, stepup_number,
// GachaRateContentInfoList: [CGachaRateContentInfo]} (docs/server-rules.md#gacha-pools).
Value gacha_rate_info(const gacha_pools::RateInfo& page) {
    Value info = Value::object();
    info["id"] = page.id;
    info["title"] = page.title;
    info["introduction_msg"] = page.introduction_msg;
    info["bonus_msg"] = page.bonus_msg;
    info["stepup_number"] = page.stepup_number;
    Value lines = Value::array();
    for (const auto& line : page.lines) {
        Value content = Value::object();
        content["type"] = line.type;
        content["message_id"] = line.message_id;
        content["content_id"] = line.content_id;
        content["percentage"] = line.percentage;
        content["direct_message"] = line.direct_message;
        content["order_id"] = line.order_id;
        lines.push(content);
    }
    info["GachaRateContentInfoList"] = lines;
    return info;
}

}  // namespace

// GetGachaRate from the pools: the rate dialog, from the same pools the draws use
// (gacha_pools::Pools::rate_info).
std::vector<u8> gacha_rate_from_pools(ext::Ctx& ctx, const Request& req) {
    u32 id = args::GachaIdArgs::from(req).gacha_id;
    Value list = Value::array();
    for (auto& page : ctx.pools->rate_info(id, format_time(clock_now()))) {
        // (a) a pools file without the titles (the release packages'): the master's
        if (page.title.empty()) page.title = gacha_pools::name_from_master(ctx.m.h, page.id);
        list.push(gacha_rate_info(page));
    }
    Value data = base_data(ctx);
    data["GachaRateInfoList"] = list;
    LOGI("server", "GetGachaRate %u: %zu rate pages", id, list.arr.size());
    return body(data);
}

namespace {

// GetGachaRate(u32 gacha, s8 const* hash) -> GetGachaRateRes             fid d6bcb49d
// API: docs/api.md#getgacharate   Rules: docs/server-rules.md#gacha-pools
//
// The rate dialog of a banner (b: CGacha::CallRateWebView sends it; docs/api.md Callers).
//   (b) GachaRateInfoList: CGachaRateInfo pages with their CGachaRateContentInfo lines.
//   (d) the lines are the reconstructed pools' (master/gacha_pools.h), the same the draws use.
//   (d) without the pools there is no rate data: the player state only (a fake-server file would
//       add characters the server doesn't know).
// Answers: the player state with GachaRateInfoList (with the pools), else the player state only.
std::vector<u8> get_gacha_rate(ext::Ctx& ctx, const Request& req) {
    if (ctx.pools->is_open()) return gacha_rate_from_pools(ctx, req);
    LOGW("server", "%s: not implemented; answering the player state only", req.method.c_str());
    return body(base_data(ctx));
}

}  // namespace

// GetGachaRate (src/core/modules.cpp: the core's APIs first).
void register_gacha_rate() { ext::add_core_api({"GetGachaRate"}, get_gacha_rate); }

}  // namespace soa::server

// The assist pairs: SetAssist (README.md). Port code, not guest behaviour; every rule carries its
// source label, (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption
// (docs/server-rules.md "Assist").
#include "api/player/player_info.h"  // base_data
#include "core/log.h"
#include "core/modules.h"
#include "core/request_args.h"

namespace soa::server {

using ext::body;

namespace {

// SetAssist(u64 character_uid, u64 assist_uid) -> SetAssistRes   fid 741e0072
// API: docs/api.md#setassist   Rules: docs/server-rules.md "Assist"
//
// Gives an owned character an assist character, or takes it off with assist 0 (the equipment
// screen's assist icon, CAssistCharacterList::Progress).
//   (b) CApiNotify::OnSetAssistRes applies SetAssistResult {character_id, assist_id,
//       old_assist_id} to the client's characters: a character has one assist, and an assist
//       character assists one character (it's taken off whoever had it). The server keeps the
//       same pairs (table assist; Character's assist keys, api/player/roster.cpp).
//   (d) both must be owned and differ; else nothing changes and the request isn't handled (no
//       body: the host's fallback answer, no error code). The level-70 requirement is the
//       client's (b: its assist list refuses lower levels).
// Answers: the player state and SetAssistResult.
std::vector<u8> set_assist(ext::Ctx& ctx, const Request& req) {
    const auto args = args::SetAssistArgs::from(req);
    const u64 character_uid = args.character_uid, assist_uid = args.assist_uid;
    auto owned = [&](u64 uid) { return uid && ctx.st.one("select count(*) from roster where uid = ?", {uid}) > 0; };
    if (!owned(character_uid) || (assist_uid && (!owned(assist_uid) || assist_uid == character_uid))) {
        LOGW("server", "SetAssist %llu <- %llu refused", (unsigned long long)character_uid, (unsigned long long)assist_uid);
        return {};
    }
    u64 old_assist_uid = (u64)ctx.st.one("select assist_uid from assist where uid = ?", {character_uid}, 0);
    if (assist_uid) ctx.st.q("delete from assist where assist_uid = ?", {assist_uid});  // it leaves whoever it assisted
    if (assist_uid) ctx.st.q("insert or replace into assist values (?,?)", {character_uid, assist_uid});
    else ctx.st.q("delete from assist where uid = ?", {character_uid});
    Value result = Value::object();
    result["character_id"] = character_uid;
    result["assist_id"] = assist_uid;
    result["old_assist_id"] = old_assist_uid;
    Value data = base_data(ctx);
    data["SetAssistResult"] = result;
    LOGI("server", "SetAssist: %llu <- %llu (was %llu)", (unsigned long long)character_uid, (unsigned long long)assist_uid,
         (unsigned long long)old_assist_uid);
    return body(data);
}

}  // namespace

// The assist's API (src/core/modules.cpp: the core's APIs first, after the parties').
void register_assist() { ext::add_core_api({"SetAssist"}, set_assist); }

}  // namespace soa::server

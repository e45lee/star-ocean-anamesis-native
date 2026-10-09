// The account's small APIs (api/settings/README.md): the birth month asked before a purchase, the
// term-info screen's read marks and the guide popups' taps. Port code, not guest behaviour; every
// rule carries its source label, (a) master data, (b) client-side evidence, (c) outside knowledge,
// (d) assumption. Rules in docs/server-rules.md#account.
//
// What the client reads (b):
//  - `Birth`: CBirthInfo {year, month} (CBirthInfo::Initialize: two u32).
//  - GetBirthYearMonth's result lambda (BirthDialogUtility::RequestGetAge's, @019587d8): a success
//    calls back "known"; a failure with error 10009 (誕生年月が確認できません。) opens the birth
//    dialog (CDialogManager::OpenBirthDialog), whose CBirthDialog sends UpdateBirthYearMonth.
//  - UpdateBirthYearMonth(u16 year, u8 month): NetworkApiCaller sends it as the string "%u-%02u"
//    (CNetworkUtility::BirthYearMonthNumber2String @015f7c60, char[8]), and only for a year in
//    1900..2100 and a month in 1..12; BirthYearMonthString2Number (@015f7cc0) reads it back the
//    same way.
//  - `GuideInformationInfoList`: an InfoBaseValueArray<u32> (its vtable's DeserializeArray), the
//    master_guide_information ids the guide popup shows, in CParameterManager+0x89c8;
//    CGuideInformationUtility::GetGuideInformationData (@01c64328) lists exactly those ids, and an
//    empty list shows no popup.
//  - CTermInfoUI::Progress (@01c8a19c) sends ReadExpirationInfo with the ids its list shows when it
//    opens (none: no request); the list's state (limit, read) comes from ExpirationInfoList
//    (CParameterManager+0x9918, CTermInfoUI::tTermInfoData::MargeExpirationInfo), which no
//    response of the local server carries.
//
// State: player.birth_year / birth_month (schema version 14; NULL: never entered).
#include <cstdio>
#include <string>
#include <vector>

#include "api/gen/reply_types.h"  // the replies' C*Info types
#include "api/settings/settings.h"
#include "core/errors.h"
#include "core/log.h"
#include "core/modules.h"
#include "soaserver/ext.h"

namespace soa::server {

namespace args {
// UpdateBirthYearMonth(u16 year, u8 month), as sent: the string "YYYY-MM" (b: above). The in-process
// route sends the same string (port/src/native/api/server_adapters.cpp formats it as
// NetworkApiCaller does). `ok` is false for a string the client's own reader
// (BirthYearMonthString2Number) wouldn't accept: not "%u-%u", a year outside 1900..2100 or a
// month outside 1..12.
struct UpdateBirthYearMonthArgs {
    u32 year = 0, month = 0;
    bool ok = false;
    static UpdateBirthYearMonthArgs from(const Request& r) {
        UpdateBirthYearMonthArgs a;
        if (r.strs.empty()) return a;
        unsigned year = 0, month = 0;
        if (sscanf(r.strs[0].c_str(), "%u-%u", &year, &month) != 2) return a;
        a.year = year;
        a.month = month;
        a.ok = year >= 1900 && year <= 2100 && month >= 1 && month <= 12;
        return a;
    }
};

// SendGuideInformation(u32 master_guide_information_id) (b: CGuideInformation::Progress sends the
// shown guide's id when the player follows its link).
struct SendGuideInformationArgs {
    u32 guide_id = 0;
    static SendGuideInformationArgs from(const Request& r) { return {r.ints.empty() ? 0u : (u32)r.ints[0]}; }
};

// ReadExpirationInfo(CSTLVector<u32> const& ids) (b: CTermInfoUI::Progress, the ids it shows).
struct ReadExpirationInfoArgs {
    std::vector<u64> ids;
    static ReadExpirationInfoArgs from(const Request& r) { return {r.vecs.empty() ? std::vector<u64>() : r.vecs[0]}; }
};
}  // namespace args

namespace settings {

namespace {

using ext::Row;

Value birth_info(u32 year, u32 month) { return infos::to_value(infos::CBirthInfo{year, month}); }

// GetBirthYearMonth() -> GetBirthYearMonthRes                                   fid 59a48d41
// API: docs/api.md#getbirthyearmonth
// Rules: docs/server-rules.md#account
//
// The birth month the client checks before a coin purchase (BirthDialogUtility::RequestGetAge:
// CCoinShop::ToShop, CGuideInformation).
//   (b) Never entered: refused with kBirthUnknown (10009), the one code on which the result lambda
//       (@019587d8) opens the birth dialog.
//   (d) The age isn't checked against anything: a local game has no monthly spending limit for
//       minors (docs/unimplemented-apis.md, Decisions).
// Answers: the player state and Birth {year, month}.
std::vector<u8> get_birth_year_month(ext::Ctx& ctx, const Request& req) {
    bool known = false;
    u32 year = 0, month = 0;
    ctx.st.q("select birth_year, birth_month from player where birth_year is not null and birth_month is not null", {}, [&](const Row& r) {
        known = true;
        year = (u32)r.i("birth_year");
        month = (u32)r.i("birth_month");
    });
    if (!known) return ext::refuse(ctx, req.method.c_str(), "no birth month entered", ErrorCode::kBirthUnknown);
    Value data = ctx.base_data();
    data["Birth"] = birth_info(year, month);
    return ext::body(data);
}

// UpdateBirthYearMonth(u16 year, u8 month) -> UpdateBirthYearMonthRes          fid 0088b260
// API: docs/api.md#updatebirthyearmonth
// Rules: docs/server-rules.md#account
//
// The birth month the player enters in the birth dialog (CBirthDialog).
//   (b) The request is the string "YYYY-MM"; the client's own ranges (year 1900..2100, month
//       1..12; CNetworkUtility::BirthYearMonthString2Number @015f7cc0).
//   (d) A string outside them is refused with kInvalidOperation (10403); the client never sends one.
//   (d) Stored as entered, and entering it again replaces it (the client asks only while
//       GetBirthYearMonth is refused).
// Answers: the player state and Birth (the stored month).
std::vector<u8> update_birth_year_month(ext::Ctx& ctx, const Request& req) {
    const auto a = args::UpdateBirthYearMonthArgs::from(req);
    if (!a.ok) return ext::refuse(ctx, req.method.c_str(), "not a birth month the client sends", ErrorCode::kInvalidOperation);
    ctx.st.q("update player set birth_year = ?, birth_month = ?", {a.year, a.month});
    LOGI("server", "UpdateBirthYearMonth: %u-%02u", a.year, a.month);
    Value data = ctx.base_data();
    data["Birth"] = birth_info(a.year, a.month);
    return ext::body(data);
}

// ReadExpirationInfo(CSTLVector<u32> ids) -> ReadExpirationInfoRes             fid dc269365
// API: docs/api.md#readexpirationinfo
// Rules: docs/server-rules.md#account
//
// 期限情報 (CTermInfoUI) marks the entries it shows as read.
//   (a) The ids are master_expiration_information ids; one it doesn't have is logged.
//   (d) Nothing is stored and ExpirationInfoList isn't answered: the local server keeps no
//       expiration state (no response carries ExpirationInfoList), so a read mark would have
//       nothing to change on the client.
// Answers: the player state.
std::vector<u8> read_expiration_info(ext::Ctx& ctx, const Request& req) {
    const auto a = args::ReadExpirationInfoArgs::from(req);
    for (u64 id : a.ids)
        if (!ctx.m.one("select count(*) from master_expiration_information where id = ?", {(u32)id}))
            LOGW("server", "ReadExpirationInfo: %llu isn't a master_expiration_information id", (unsigned long long)id);
    LOGI("server", "ReadExpirationInfo: %zu entries read (nothing stored)", a.ids.size());
    return ext::body(ctx.base_data());
}

// SendGuideInformation(u32 master_guide_information_id) -> SendGuideInformationRes  fid 5cf6a3e9
// API: docs/api.md#sendguideinformation
// Rules: docs/server-rules.md#account
//
// The guide popup's link was followed (CGuideInformation::Progress).
//   (b) GuideInformationInfoList is the list of guides the popup shows (above).
//   (d) The local server shows no guide popups (they announced the service's dated campaigns and
//       shop items; no player load sends a guide), so the list answered is empty and nothing is
//       stored; an id master_guide_information doesn't have is logged.
// Answers: the player state and GuideInformationInfoList (empty).
std::vector<u8> send_guide_information(ext::Ctx& ctx, const Request& req) {
    const auto a = args::SendGuideInformationArgs::from(req);
    if (!ctx.m.one("select count(*) from master_guide_information where id = ?", {a.guide_id}))
        LOGW("server", "SendGuideInformation: %u isn't a master_guide_information id", a.guide_id);
    LOGI("server", "SendGuideInformation %u (no guides are shown; nothing stored)", a.guide_id);
    Value data = ctx.base_data();
    data["GuideInformationInfoList"] = infos::to_array(std::vector<u32>{});  // (CGuideInformationInfoList: guide ids)
    return ext::body(data);
}

}  // namespace

void register_account() {
    ext::add_api({"GetBirthYearMonth"}, get_birth_year_month);
    ext::add_api({"UpdateBirthYearMonth"}, update_birth_year_month);
    ext::add_api({"ReadExpirationInfo"}, read_expiration_info);
    ext::add_api({"SendGuideInformation"}, send_guide_information);
}

}  // namespace settings

// The settings module (core/modules.h): its three parts, in this order.
void register_settings() {
    settings::register_config();
    settings::register_account();
    settings::register_scenario_library();
}

}  // namespace soa::server

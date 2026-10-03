// The present box lines (free_text_message_id). Port code, not guest behaviour. Rules:
// docs/server-rules.md "Present box lines"; labels: (a) master data, (b) client-side evidence,
// (c) outside knowledge, (d) assumption.
// (b) CPresentbox::CreateAllPresentList (and the list cell's lambda) shows a present's
// free_text_message_id (CPresentBoxInfo +0x1f0, a string property) verbatim; it never reads
// reason_type / reason_param and the client has no Present_box* key of its own. The live server
// therefore sent the finished line. The server builds it from the master_text templates
// Present_box_1..10 / 99, Present_favor_1 (a), picked per reason as in ext.h (d).
#include "soaserver/ext.h"
#include "master/master.h"

namespace soa::server::ext {

std::string text(Sql& master_db, const std::string& message_id) { return master::text(master_db.h, message_id); }

std::string format_present(const std::string& tmpl, const std::string& s, int64_t d) {
    std::string out;
    for (size_t i = 0; i < tmpl.size(); i++) {
        if (tmpl[i] == '%' && i + 1 < tmpl.size() && tmpl[i + 1] == 's') {
            out += s;
            i++;
        } else if (tmpl[i] == '%' && i + 1 < tmpl.size() && tmpl[i + 1] == 'd') {
            if (d >= 0) out += std::to_string(d);
            i++;
        } else {
            out += tmpl[i];
        }
    }
    return out;
}

namespace {
// The name text of master row `id` of `table` (its name_message_id), "" without one.
std::string name_of(Sql& master_db, const char* table, u32 id) {
    std::string name_message_id;
    master_db.q(std::string("select name_message_id from ") + table + " where id = ?", {id},
                [&](const Row& row) { name_message_id = row.s("name_message_id"); });
    return name_message_id.empty() ? "" : text(master_db, name_message_id);
}
// (a) a character's name: its master_person's name_message_id (the role's own name is its class,
// e.g. アタッカー)
std::string person_name(Sql& master_db, u32 role_id) {
    std::string name_message_id;
    master_db.q("select p.name_message_id from master_role r join master_person p on p.id = r.master_person_id where r.id = ?", {role_id},
                [&](const Row& person_row) { name_message_id = person_row.s("name_message_id"); });
    return name_message_id.empty() ? "" : text(master_db, name_message_id);
}
// A mission's name: the first of the mission tables that has the id.
std::string mission_name(Sql& master_db, u32 mission_id) {
    for (const char* table :
         {"master_mission", "master_event_mission", "master_world_map_mission", "master_tower_mission", "master_training_mission"}) {
        std::string name = name_of(master_db, table, mission_id);
        if (!name.empty()) return name;
    }
    return "";
}
}  // namespace

std::string present_text(Sql& state, Sql& master_db, int64_t id, u32 reason_type, u32 reason_param) {
    std::string stored;
    state.q("select text from present_texts where id = ?", {id}, [&](const Row& row) { stored = row.s("text"); });
    if (!stored.empty()) return stored;
    switch (reason_type) {
        case kPresentLoginBonus:  // (d) without the stored day: the bonus name alone
            return name_of(master_db, "master_login_bonus", reason_param);
        case kPresentMissionClear:  // (a) Present_box_2 "%sより" with the mission's name (d: the template)
            return format_present(text(master_db, "Present_box_2"), mission_name(master_db, reason_param));
        case kPresentAchievement:  // (a) Present_box_3 "%s" with the achievement's name
            return format_present(text(master_db, "Present_box_3"), name_of(master_db, "master_achievement", reason_param));
        case kPresentPremiumLogin:
            return name_of(master_db, "master_premium_login_bonus", reason_param);
        case kPresentFavorBonus:
            return format_present(text(master_db, "Present_favor_1"), person_name(master_db, reason_param));
        default:  // (a) Present_box_99 運営からのプレゼント (d: for anything else)
            return text(master_db, "Present_box_99");
    }
}

}  // namespace soa::server::ext

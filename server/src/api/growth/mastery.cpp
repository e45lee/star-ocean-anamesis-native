// Mastery (キャラクター > マスタリー: 道場 1-3, 師匠 / 弟子, 皆伝師弟): GetMasteryInfo,
// TrainMastery, ResetMastery (README.md). Port code, not guest behaviour. Rules in
// docs/server-rules.md#mastery; every rule carries its source label:
//   (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
// Client structures (b, 3.7.0 decompiles work/decomp/server-u-mastery-*.resolved.c):
//   - CPlayerCharacterMasteryInfo (Initialize @014f772c): character_id (u64, the 弟子 = the map's
//     key), player_id (u32), parent_character_id (u64, the 師匠), dojo_no (u32; fields.txt misses
//     the inline name), master_mastery_step_type_id (u32), master_mastery_step_1..5_option_no
//     (u32), created_at, updated_at (strings). GetMasteryInfo's PlayerCharacterMasteryInfoMap is
//     an InfoBaseNumberMap of them keyed by the character id.
//   - CMasteryTop::UpdateList (@01b95450) shows the rows of the player's player_id
//     (CParameterManager+0x698): one with fewer than five cleared trainings in 道場 dojo_no (1-3),
//     the others in the 皆伝 list with their updated_at.
//   - CUpdateCharacterMasteryInfo = CPlayerCharacterMasteryInfo + mastery_talent_id,
//     parent_master_role_id. CApiNotify::OnTrainMasteryRes (@014e8ba0) merges each element of
//     UpdateCharacterMasteryInfoArray into the map and copies the two into the CPersonInfo of
//     character_id; OnResetMasteryRes (@014e9958) erases each element's character_id from the map
//     and zeroes the two.
//   - tCharaData::InitializeMastery (@01822340): a role with a mastery type (CMasterParameterRole
//     +0x11b8) is a 師匠 (trainer), the others can be 弟子; a 弟子 counts its cleared trainings
//     (non-zero option_no), and a non-zero parent role in its CPersonInfo counts as all five;
//     MasteryTalentID / MasteryRoleID / IsClearAllMasteryTraining report only past four.
#include "api/growth/mastery.h"

#include <string>
#include <vector>

#include "api/growth/growth_args.h"
#include "api/player/player_info.h"
#include "core/errors.h"
#include "core/log.h"
#include "core/modules.h"
#include "master/master.h"
#include "soaserver/ext.h"

namespace soa::server {

namespace {
using namespace ext;

constexpr u32 kSteps = 5;    // (a) master_mastery_step.step 1..5; (b) "達成済みの訓練(%lu／%lu)" of 5
constexpr u32 kOptions = 3;  // (a) master_mastery_step.option_no 1..3; (b) the three Button_%lu cards
constexpr u32 kDojos = 3;    // (b) CMasteryTop::UpdateList: three 道場 (dojo_no - 1 < 3)
// (b) uimsg_mastery_Warning_01 "師匠、弟子になるためにはLV70になっている必要があります。
// また、師匠と弟子は同じロールである必要があります。" (the selection screen's warning); no master
// row holds the level.
constexpr u32 kMasteryLevel = 70;

// One stored pair (state table `mastery`).
struct Pair {
    bool found = false;
    CharacterUid disciple, master;
    u32 dojo_no = 0, type_id = 0;
    u32 option[kSteps] = {0, 0, 0, 0, 0};
    int64_t created_at = 0, updated_at = 0;
    u32 cleared() const {
        u32 n = 0;
        for (u32 k = 0; k < kSteps; k++) n += option[k] ? 1 : 0;
        return n;
    }
};

Pair read_pair(const Row& row) {
    Pair p;
    p.found = true;
    p.disciple = row.id<CharacterUid>("uid");
    p.master = row.id<CharacterUid>("master_uid");
    p.dojo_no = (u32)row.i("dojo_no");
    p.type_id = (u32)row.i("type_id");
    for (u32 k = 0; k < kSteps; k++) p.option[k] = (u32)row.i(("step" + std::to_string(k + 1)).c_str());
    p.created_at = row.i("created_at");
    p.updated_at = row.i("updated_at");
    return p;
}

Pair pair_of_disciple(Ctx& ctx, CharacterUid disciple) {
    Pair p;
    ctx.st.q("select * from mastery where uid = ?", {disciple}, [&](const Row& row) { p = read_pair(row); });
    return p;
}

// An owned character's role and level, and its role's mastery fields.
struct Member {
    bool found = false;
    RoleId role;
    u32 level = 0, awaken = 0, category_type = 0, step_type_id = 0;
};

Member member(Ctx& ctx, CharacterUid uid) {
    Member c;
    ctx.st.q("select role_id, level, awaken from roster where uid = ?", {uid}, [&](const Row& row) {
        c.found = true;
        c.role = row.id<RoleId>("role_id");
        c.level = (u32)row.i("level");
        c.awaken = (u32)row.i("awaken");
    });
    if (!c.found) return c;
    ctx.m.q("select category_type, ifnull(master_mastery_step_type_id, 0) as type_id from master_role where id = ?", {c.role}, [&](const Row& row) {
        c.category_type = (u32)row.i("category_type");
        c.step_type_id = (u32)row.i("type_id");
    });
    return c;
}

// CPlayerCharacterMasteryInfo of a pair (b: its Initialize's keys, above).
Value mastery_info(Ctx& ctx, const Pair& p) {
    Value info = Value::object();
    info["character_id"] = p.disciple.v;
    info["player_id"] = player_id(ctx).v;
    info["parent_character_id"] = p.master.v;
    info["dojo_no"] = p.dojo_no;
    info["master_mastery_step_type_id"] = p.type_id;
    for (u32 k = 0; k < kSteps; k++) info["master_mastery_step_" + std::to_string(k + 1) + "_option_no"] = p.option[k];
    info["created_at"] = ctx.fmt_time(p.created_at);
    info["updated_at"] = ctx.fmt_time(p.updated_at);
    return info;
}

// CUpdateCharacterMasteryInfo: the pair plus what the disciple's CPersonInfo gets (b:
// OnTrainMasteryRes copies them; 0 until all five trainings are cleared, since a non-zero parent
// role counts as a finished training to InitializeMastery).
Value update_info(Ctx& ctx, const Pair& p) {
    Value info = mastery_info(ctx, p);
    MasteryInheritance inh = mastery_inheritance(ctx, p.disciple);
    info["mastery_talent_id"] = inh.mastery_talent_id;
    info["parent_master_role_id"] = inh.parent_master_role_id;
    return info;
}

// UpdateStockItem's entry for a stack item (the count now), as RemoveGear sends it.
Value stock_entry(Ctx& ctx, u32 item) {
    Value e = Value::object();
    e["id"] = item;
    e["master_item_id"] = item;
    e["num"] = stock_count(ctx, item);
    return e;
}

// (b) 師弟解消 (uimsg_mastary_dialog2 / dialog4): parting loses the trainings and the inherited
// talent: the row goes.
void part(Ctx& ctx, const Pair& p) { ctx.st.q("delete from mastery where uid = ?", {p.disciple}); }

// The pair (either way round) of two characters (found = false: none).
Pair pair_between(Ctx& ctx, CharacterUid a, CharacterUid b) {
    Pair p;
    ctx.st.q("select * from mastery where (uid = ? and master_uid = ?) or (uid = ? and master_uid = ?)", {a, b, b, a},
             [&](const Row& row) { p = read_pair(row); });
    return p;
}

// TrainMastery with step 0: forming the pair (師弟関係を結ぶ).
std::vector<u8> form_pair(Ctx& ctx, const args::TrainMasteryArgs& a) {
    const char* m = "TrainMastery";
    if (a.disciple_uid == a.master_uid) return refuse(ctx, m, "the same character twice", ErrorCode::kItemUnusable);
    Member disciple = member(ctx, a.disciple_uid), master = member(ctx, a.master_uid);
    if (!disciple.found || !master.found) return refuse(ctx, m, "unknown character", ErrorCode::kItemUnusable);
    // (b) a 師匠 has a mastery type (InitializeMastery's trainer flag), a 弟子 hasn't
    // (IsMasteryTrainee needs it clear); (a) the pair's type is the master role's
    // master_mastery_step_type_id
    if (!master.step_type_id || master.step_type_id != a.step_type_id)
        return refuse(ctx, m, "the master's role has another (or no) mastery type", ErrorCode::kItemUnusable);
    if (disciple.step_type_id) return refuse(ctx, m, "a master role can't be a disciple", ErrorCode::kItemUnusable);
    // (b) uimsg_mastery_Warning_01: the same ロール, (a) master_role.category_type (1..5: the
    // five mastery types attacker, defender, shooter, caster, healer match it one to one)
    if (disciple.category_type != master.category_type) return refuse(ctx, m, "not the same role type", ErrorCode::kItemUnusable);
    // (b) uimsg_mastery_Warning_01: both at LV70
    if (disciple.level < kMasteryLevel || master.level < kMasteryLevel) return refuse(ctx, m, "below LV70", ErrorCode::kLevelCap);
    if (a.dojo_no < 1 || a.dojo_no > kDojos) return refuse(ctx, m, "no such dojo", ErrorCode::kItemUnusable);
    // (b) uimsg_mastary_dialog4 "すでに師弟関係を結んでいるキャラクターが含まれています。現在の師弟関係を
    // 解消して、新たな師弟関係を結びますか？": a character in another pair (as either side,
    // graduated or not) leaves it
    std::vector<Pair> old;
    ctx.st.q("select * from mastery where uid in (?, ?) or master_uid in (?, ?)", {a.disciple_uid, a.master_uid, a.disciple_uid, a.master_uid},
             [&](const Row& row) { old.push_back(read_pair(row)); });
    // (d) a dojo holds one pair in training (CMasteryTop::UpdateList places one per dojo_no); the
    // selection screen pairs only in an empty one, so another pair still training there (one that
    // isn't parted here) is refused
    bool busy = false;
    ctx.st.q("select * from mastery where dojo_no = ?", {a.dojo_no}, [&](const Row& row) {
        Pair p = read_pair(row);
        if (p.cleared() >= kSteps) return;
        for (const Pair& o : old)
            if (o.disciple == p.disciple) return;
        busy = true;
    });
    if (busy) return refuse(ctx, m, "the dojo is in use", ErrorCode::kItemUnusable);
    for (const Pair& p : old) {
        part(ctx, p);
        LOGI("server", "TrainMastery: pair %llx / %llx parted for the new one", (unsigned long long)p.master.v, (unsigned long long)p.disciple.v);
    }
    const int64_t now = ctx.now().v;
    ctx.st.q("insert into mastery (uid, master_uid, dojo_no, type_id, created_at, updated_at) values (?, ?, ?, ?, ?, ?)",
             {a.disciple_uid, a.master_uid, a.dojo_no, a.step_type_id, now, now});
    Pair p = pair_of_disciple(ctx, a.disciple_uid);
    Value data = ctx.base_data(), list = Value::array();
    list.push(update_info(ctx, p));
    data["UpdateCharacterMasteryInfoArray"] = list;
    // read by mastery_session.sh
    LOGI("server", "TrainMastery: paired master %llx and disciple %llx in dojo %u (type %u)", (unsigned long long)a.master_uid.v,
         (unsigned long long)a.disciple_uid.v, a.dojo_no, a.step_type_id);
    return body(data);
}

}  // namespace

MasteryInheritance mastery_inheritance(Ctx& ctx, CharacterUid uid) {
    MasteryInheritance inh;
    Pair p = pair_of_disciple(ctx, uid);
    if (!p.found || p.cleared() < kSteps) return inh;
    Member master = member(ctx, p.master);
    if (!master.found) return inh;
    inh.graduated = true;
    inh.parent_master_role_id = master.role.v;
    inh.mastery_talent_id = mastery_talent_of(ctx, master.role, master.awaken);
    return inh;
}

u32 mastery_talent_of(Ctx& ctx, RoleId master_role, u32 awaken_level) {
    // (a) master_role.mastery_talent_slot (1, 3 or 5 in 3.7.0) names the talent passed on;
    // (b) InitializeMastery picks that slot of the master's talents when the CPersonInfo sends none
    u32 talent = 0;
    ctx.m.q("select * from master_role where id = ?", {master_role}, [&](const Row& role_row) {
        if (role_row.null("mastery_talent_slot")) return;
        const std::string column = "master_talent" + std::to_string(role_row.i("mastery_talent_slot")) + "_id";
        talent = role_row.null(column.c_str()) ? 0 : (u32)role_row.i(column.c_str());
        // (a) the awakening's talents: the master_awaken row of the role's category at the
        // master's awaken_level (the row CParameterUtility::FindAwakenWithRoleCateforyIdAndLevel
        // finds for tTalentDataSet::Create); (d) its slot, when set, replaces the role's
        if (awaken_level > 0)
            ctx.m.q("select * from master_awaken where role_category_id = ? and awaken_level = ?", {role_row.i("role_category_id"), awaken_level},
                    [&](const Row& awaken_row) {
                        if (!awaken_row.null(column.c_str()) && awaken_row.i(column.c_str())) talent = (u32)awaken_row.i(column.c_str());
                    });
    });
    return talent;
}

std::optional<CharacterUid> graduated_disciple_of(Ctx& ctx, CharacterUid master_uid) {
    std::optional<CharacterUid> disciple;
    ctx.st.q("select * from mastery where master_uid = ?", {master_uid}, [&](const Row& row) {
        Pair p = read_pair(row);
        if (p.cleared() >= kSteps) disciple = p.disciple;
    });
    return disciple;
}

// GetMasteryInfo() -> GetMasteryInfoRes                                           fid 45bea005
// API: docs/api.md#getmasteryinfo   Rules: docs/server-rules.md#mastery
//
// The player's 師弟 pairs, which CMasteryTop::Initialize asks for when the マスタリー screen opens.
//   (b) every stored pair, in training (shown in its 道場) or graduated (皆伝), as
//   CPlayerCharacterMasteryInfo keyed by the disciple's uid.
// Answers: the player state, PlayerCharacterMasteryInfoMap.
std::vector<u8> get_mastery_info(Ctx& ctx, const Request&) {
    Value data = ctx.base_data(), map = Value::object();
    int n = 0;
    ctx.st.q("select * from mastery order by uid", {}, [&](const Row& row) {
        Pair p = read_pair(row);
        map[std::to_string(p.disciple.v)] = mastery_info(ctx, p);
        n++;
    });
    data["PlayerCharacterMasteryInfoMap"] = map;
    LOGI("server", "GetMasteryInfo: %d pair(s)", n);  // read by mastery_session.sh
    return body(data);
}

// TrainMastery(u64 disciple, u64 master, u8 dojo_no, u32 step_type_id, u8 step, u8 option)
//   -> TrainMasteryRes                                                             fid bb0e7ef9
// API: docs/api.md#trainmastery   Rules: docs/server-rules.md#mastery
//
// Forms a 師弟 pair (step 0) or clears one training of a pair (step 1-5); the fifth is 皆伝.
//   Pairing (b: the selection screen's lambda sends step 0, option 0): form_pair above (both
//   owned and distinct, the master's role has the request's mastery type and the disciple's none,
//   (a)+(b) the same category_type, (b) both LV70, (b) dojo 1-3; (b) either character's other pair
//   is parted first; (d) a dojo with a pair still training refuses).
//   A training:
//   - (b) only the pair's next one: step = its cleared trainings + 1 (the client sends that).
//   - (a) option 1-3: the cost is master_mastery_step (type_id, step, option_no):
//     required_master_item_id × required_num and required_fol.
//   - (a)+(b) option 4-6 (the dialog's マスタリーパスメダルを使う adds 3): instead
//     master_global mastery_training_pass_item_id × mastery_training_pass_required_num and no FOL
//     (b: CMasteryTrainingConfirmationDialog::Setup enables that button on the medal count alone).
//     (d) The training stored is the chosen card's (option - 3).
//   - (a) The fifth: master_global mastery_reward_master_item_id × mastery_reward_num to the
//     stock (b: CMasteryTrainingAllClearDialog shows that gift, uimsg_mastary_dialog11), and the
//     disciple inherits the master's role and talent (mastery_inheritance).
//   Refused: unknown pair or characters, not the next training, no master row (10208), items short
//   (10206), FOL short (10710), below LV70 (11002).
// Answers: the player state, UpdateCharacterMasteryInfoArray (the pair, with mastery_talent_id
// and parent_master_role_id), after a training UpdateStockItem (the items it changed) and
// StockItem, after the fifth MasteryRewardInfo {master_item_id, num}.
std::vector<u8> train_mastery(Ctx& ctx, const Request& req) {
    const auto a = args::TrainMasteryArgs::from(req);
    const char* m = "TrainMastery";
    if (a.step == 0) return form_pair(ctx, a);
    Pair p = pair_of_disciple(ctx, a.disciple_uid);
    if (!p.found || p.master != a.master_uid) return refuse(ctx, m, "no such pair", ErrorCode::kItemUnusable);
    if (a.step > kSteps || a.step != p.cleared() + 1) return refuse(ctx, m, "not the pair's next training", ErrorCode::kItemUnusable);
    const bool pass = a.option > kOptions && a.option <= 2 * kOptions;
    const u32 option = pass ? a.option - kOptions : a.option;
    if (option < 1 || option > kOptions) return refuse(ctx, m, "no such training", ErrorCode::kItemUnusable);
    u32 item = 0, num = 0, need_fol = 0;
    if (pass) {
        // (a) the pass medal (master_global), no FOL (b)
        item = (u32)ctx.m.one("select id from master_item where id_label = ?", {master::global_str(ctx.m.h, "mastery_training_pass_item_id")});
        num = ctx.global_u32("mastery_training_pass_required_num", 1);
    } else {
        bool found = false;
        ctx.m.q("select * from master_mastery_step where type_id = ? and step = ? and option_no = ?", {p.type_id, a.step, option},
                [&](const Row& step_row) {
                    found = true;
                    item = (u32)step_row.i("required_master_item_id");
                    num = (u32)step_row.i("required_num");
                    need_fol = (u32)step_row.i("required_fol");
                });
        if (!found) return refuse(ctx, m, "no master_mastery_step row", ErrorCode::kItemUnusable);
    }
    if (!item && num) return refuse(ctx, m, "no pass item in the master", ErrorCode::kItemUnusable);
    if (num && stock_count(ctx, item) < num) return refuse(ctx, m, "not enough items", ErrorCode::kItemCountError);
    if (fol(ctx) < need_fol) return refuse(ctx, m, "not enough FOL", ErrorCode::kFolShort);
    if (num) add_stock(ctx, item, -(int64_t)num);
    add_fol(ctx, -(int64_t)need_fol);
    ctx.st.q("update mastery set step" + std::to_string(a.step) + " = ?, updated_at = ? where uid = ?", {option, ctx.now(), p.disciple});
    Value changed = Value::array();
    if (num) changed.push(stock_entry(ctx, item));
    Value reward;  // Nil: no 皆伝 yet
    if (a.step == kSteps) {
        // (a) the 皆伝 gift
        u32 reward_item =
            (u32)ctx.m.one("select id from master_item where id_label = ?", {master::global_str(ctx.m.h, "mastery_reward_master_item_id")});
        u32 reward_num = ctx.global_u32("mastery_reward_num", 1);
        if (reward_item && reward_num) {
            add_stock(ctx, reward_item, reward_num);
            if (num && reward_item == item) changed.arr.back() = stock_entry(ctx, reward_item);  // the medal paid, then given
            else changed.push(stock_entry(ctx, reward_item));
            reward = Value::object();
            reward["master_item_id"] = reward_item;
            reward["num"] = reward_num;
        }
    }
    p = pair_of_disciple(ctx, a.disciple_uid);
    Value data = ctx.base_data(), list = Value::array();
    list.push(update_info(ctx, p));
    data["UpdateCharacterMasteryInfoArray"] = list;
    if (reward.type != Value::Nil) data["MasteryRewardInfo"] = reward;
    data["UpdateStockItem"] = changed;
    data["StockItem"] = ctx.stock();
    // read by mastery_session.sh
    LOGI("server", "TrainMastery: disciple %llx training %u/%u option %u%s, FOL -%u%s", (unsigned long long)p.disciple.v, a.step, kSteps, option,
         pass ? " (pass medal)" : "", need_fol, a.step == kSteps ? "; 皆伝" : "");
    return body(data);
}

// ResetMastery(u64, u64) -> ResetMasteryRes                                        fid 614fa7ea
// API: docs/api.md#resetmastery   Rules: docs/server-rules.md#mastery
//
// Parts a 師弟 pair (師弟解消), in training or graduated.
//   (b) the two characters come master first or disciple first (ResetMasteryArgs); either order
//   finds the pair.
//   (b) uimsg_mastary_dialog2: the trainings and the inherited talent are lost (the row goes; the
//   client zeroes the disciple's parent role and talent itself, OnResetMasteryRes).
//   (d) Nothing paid is returned (the dialog doesn't offer it).
//   Refused: no such pair (10208).
// Answers: the player state, UpdateCharacterMasteryInfoArray (the parted pair: its character_id
// is the key the client erases).
std::vector<u8> reset_mastery(Ctx& ctx, const Request& req) {
    const auto a = args::ResetMasteryArgs::from(req);
    Pair p = pair_between(ctx, a.a, a.b);
    if (!p.found) return refuse(ctx, "ResetMastery", "no such pair", ErrorCode::kItemUnusable);
    Value info = mastery_info(ctx, p);
    info["mastery_talent_id"] = 0u;
    info["parent_master_role_id"] = 0u;
    part(ctx, p);
    Value data = ctx.base_data(), list = Value::array();
    list.push(info);
    data["UpdateCharacterMasteryInfoArray"] = list;
    // read by mastery_session.sh
    LOGI("server", "ResetMastery: parted master %llx and disciple %llx (%u training(s) cleared)", (unsigned long long)p.master.v,
         (unsigned long long)p.disciple.v, p.cleared());
    return body(data);
}

// The mastery APIs (src/core/modules.cpp's order).
void register_mastery() {
    add_api({"GetMasteryInfo"}, get_mastery_info);
    add_api({"TrainMastery"}, train_mastery);
    add_api({"ResetMastery"}, reset_mastery);
}

}  // namespace soa::server

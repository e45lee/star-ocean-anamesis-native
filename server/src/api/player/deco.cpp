// Character decorations (会話モード > キャラデコ, CHomeDecoMenu): GetDecoInfo, SetCharacterDeco,
// FavoriteDecoObject, UnFavoriteDecoObject, the decoration grants (content types 17, 18) and the
// NumDecoObject key (README.md). Port code, not guest behaviour; rules in docs/server-rules.md#deco,
// each with its label: (a) master data, (b) client-side evidence, (c) outside knowledge, (d) assumption.
// Client structures (b, 3.7.0 decompiles work/decomp/server-u-mastery-{n,r}.resolved.c):
//   - CDecoObjectInfo (Initialize): id (u64), player_id (u32), master_deco_id (u32), is_favorite;
//     the owned list `DecoObject` (CParameterManager+0x8728). tItemData::GetDecoItemList makes an
//     item of each (content types 17..19: objects, hair colours) for the menu.
//   - CParameterUtility::tItemData::HasDecoItem (@01851b88) reads one u32 of the player state
//     (CParameterManager+0xaf30); キャラデコ opens the menu (asking GetDecoInfo first) only when it
//     isn't 0, else "デコを所持していません". The state key it fills is `NumDecoObject` (the only
//     deco count among the response keys, port/fakeapi/schema.txt #531).
//   - CPersonInfo carries the character's setting: hair_id (+0x7d0), pose_id (+0x800) and the list
//     `CharacterDecoObject` (CCharacterDecoObjectInfo: player_character_id, index,
//     master_deco_object_id, attach_bone, attach_type, pos_x..z, rotate_x..z, slider_pos_x..z,
//     slider_rotate_x..z, scale; Initialize, names read from .rodata).
//   - SetCharacterDeco's request is CCharacterDecoSendInfo (CParameterManager+0x8790) serialized
//     by AsonSerializer (NetworkApiCaller's lambda @015ef218): MessagePack {character_id, hair_id,
//     pose_id, CharacterDecoObject: [CCharacterDecoObjectInfo]} (wire/deco-payload). Its answer's
//     `CharacterDeco` (the same shape) is copied into that character's CPersonInfo
//     (CApiNotify::OnSetCharacterDecoRes @014eabd0).
//   - FavoriteDecoObjectResult is a map of CDecoObjectInfo by master_deco_id, merged into the
//     owned list (OnFavoriteDecoObjectRes @014ea318).
#include "api/player/deco.h"

#include <string>
#include <vector>

#include "api/player/player_info.h"  // player_id
#include "api/player/roster.h"       // owns_character
#include "core/errors.h"
#include "core/log.h"
#include "core/modules.h"
#include "soaserver/ext.h"

namespace soa::server {

namespace {
using namespace ext;

constexpr u32 kContentDecoObject = 17;  // (a) docs/api.md "Content types": de01head_049a
constexpr u32 kContentDecoHair = 18;    // (a) deco_hair_010101

// The owned decorations as CDecoObjectInfo, in the order acquired.
Value deco_list(Ctx& ctx) {
    Value list = Value::array();
    const PlayerId owner = player_id(ctx);
    ctx.st.q("select * from deco_owned order by id", {}, [&](const Row& row) {
        Value e = Value::object();
        e["id"] = kDecoUid0 + (u64)row.i("id");
        e["player_id"] = owner.v;
        e["master_deco_id"] = (u32)row.i("master_deco_id");
        e["is_favorite"] = row.i("is_favorite") != 0;
        list.push(e);
    });
    return list;
}

// The objects' MessagePack as hex text (character_deco.objects) and back.
std::string to_hex(const std::vector<u8>& b) {
    static const char* d = "0123456789abcdef";
    std::string s;
    for (u8 c : b) s += d[c >> 4], s += d[c & 15];
    return s;
}
std::vector<u8> from_hex(const std::string& s) {
    std::vector<u8> b;
    auto v = [](char c) { return c <= '9' ? c - '0' : c - 'a' + 10; };
    for (size_t i = 0; i + 1 < s.size(); i += 2) b.push_back((u8)(v(s[i]) << 4 | v(s[i + 1])));
    return b;
}

u32 owned_count(Ctx& ctx) { return (u32)ctx.st.one("select count(*) from deco_owned", {}); }

bool owns_deco(Ctx& ctx, u32 master_deco_id) { return ctx.st.one("select count(*) from deco_owned where master_deco_id = ?", {master_deco_id}) > 0; }

// Hook (ext::add_grant 17 and 18): a decoration object (master_deco_object) or a hair colour
// (master_deco_hair) joins the owned list.
//   (a) the id is a row of the type's table; (d) one of each: a second grant of an owned one adds
//   nothing (FavoriteDecoObject names decorations by master id, so the client keeps one each).
//   The client asks for the list (GetDecoInfo) when the menu opens, and NumDecoObject comes with
//   every response (deco_count_key), so a grant only changes the state.
void grant_deco_content(Ctx& ctx, u32 id, u32, Value&, Value&, Value&) { grant_deco(ctx, id); }

// OnResponse hook (every response).
// Rules: docs/server-rules.md#deco
//   (b) NumDecoObject: the owned count, which キャラデコ checks before it opens the menu
//   (HasDecoItem); (d) sent with every response once the player owns one (left out at 0: the
//   client's default, and what the server always sent).
// Adds: NumDecoObject. True when it changed the response.
bool deco_count_key(Ctx& ctx, const Request&, Value& data) {
    const u32 n = owned_count(ctx);
    if (!n || data.type != Value::Map) return false;
    data["NumDecoObject"] = n;
    return true;
}

}  // namespace

bool grant_deco(Ctx& ctx, u32 master_deco_id) {
    const bool known = ctx.m.one("select count(*) from master_deco_object where id = ?", {master_deco_id}) > 0 ||
                       ctx.m.one("select count(*) from master_deco_hair where id = ?", {master_deco_id}) > 0;
    if (!known) {
        LOGW("server", "deco %u: no master_deco_object / master_deco_hair row; not granted", master_deco_id);
        return false;
    }
    if (owns_deco(ctx, master_deco_id)) {
        LOGI("server", "deco %u: owned already", master_deco_id);
        return false;
    }
    ctx.st.q("insert into deco_owned (master_deco_id, created_at) values (?, ?)", {master_deco_id, ctx.now()});
    LOGI("server", "deco %u granted", master_deco_id);  // read by mastery_session.sh
    return true;
}

void add_character_deco(Ctx& ctx, CharacterUid uid, Value& info) {
    ctx.st.q("select * from character_deco where uid = ?", {uid}, [&](const Row& row) {
        info["hair_id"] = (u32)row.i("hair_id");
        info["pose_id"] = (u32)row.i("pose_id");
        Value objects = mp_decode(from_hex(row.s("objects")));
        info["CharacterDecoObject"] = objects.type == Value::Arr ? objects : Value::array();
    });
}

// GetDecoInfo() -> GetDecoInfoRes                                                  fid 33015ed5
// API: docs/api.md#getdecoinfo   Rules: docs/server-rules.md#deco
//
// The owned decorations, which キャラデコ asks for before it opens the menu (when NumDecoObject
// isn't 0: the lambda @01afe53c).
//   (b) DecoObject: every owned decoration as CDecoObjectInfo {id, player_id, master_deco_id,
//   is_favorite}; NumDecoObject: their count.
// Answers: the player state, DecoObject, NumDecoObject.
std::vector<u8> get_deco_info(Ctx& ctx, const Request&) {
    Value data = ctx.base_data();
    data["DecoObject"] = deco_list(ctx);
    data["NumDecoObject"] = owned_count(ctx);
    LOGI("server", "GetDecoInfo: %u decoration(s)", owned_count(ctx));  // read by mastery_session.sh
    return body(data);
}

// SetCharacterDeco(CCharacterDecoSendInfo) -> SetCharacterDecoRes                  fid 0747f39c
// API: docs/api.md#setcharacterdeco   Rules: docs/server-rules.md#deco
//
// A character's decorations as the menu decided them (CHomeDecoMenu::DecideDecoStatus).
//   (b) The request's string argument is the MessagePack of CCharacterDecoSendInfo (the wire's
//   blob; in-process the port serializes the same object, docs/client-changes.md "SetCharacterDeco").
//   (b) The character is owned; hair_id is 0 or an owned hair colour, every object's
//   master_deco_object_id an owned decoration (the menu lists the owned ones); 10208 otherwise.
//   (d) pose_id is stored as sent (its table isn't known); the objects are stored as sent (their
//   positions and the client's own keys), with player_character_id set to the character.
//   (d) The setting replaces the character's previous one; no cost limit is checked (the menu
//   shows the cost gauge, CHomeDecoMenu::GetTotalCost).
// Answers: the player state, CharacterDeco (the setting, which OnSetCharacterDecoRes copies into
// the character), DecoObject.
std::vector<u8> set_character_deco(Ctx& ctx, const Request& req) {
    const char* m = "SetCharacterDeco";
    if (req.strs.empty()) return refuse(ctx, m, "no CharacterDeco payload", ErrorCode::kItemUnusable);
    Value sent = mp_decode(std::vector<u8>(req.strs[0].begin(), req.strs[0].end()));
    if (sent.type != Value::Map) return refuse(ctx, m, "the payload isn't a map", ErrorCode::kItemUnusable);
    auto num = [&](const char* key) -> u64 {
        const Value* v = sent.find(key);
        return !v ? 0 : v->type == Value::Int ? (u64)v->i : v->u;
    };
    const CharacterUid uid(num("character_id"));
    const u32 hair = (u32)num("hair_id"), pose = (u32)num("pose_id");
    if (!owns_character(ctx, uid)) return refuse(ctx, m, "unknown character", ErrorCode::kItemUnusable);
    if (hair && !owns_deco(ctx, hair)) return refuse(ctx, m, "a hair colour not owned", ErrorCode::kItemUnusable);
    Value objects = Value::array();
    if (const Value* list = sent.find("CharacterDecoObject"); list && list->type == Value::Arr)
        for (const Value& e : list->arr) {
            const Value* id = e.find("master_deco_object_id");
            const u32 deco = id ? (u32)(id->type == Value::Int ? (u64)id->i : id->u) : 0;
            if (!deco || !owns_deco(ctx, deco)) return refuse(ctx, m, "a decoration not owned", ErrorCode::kItemUnusable);
            Value o = e;
            o["player_character_id"] = uid.v;
            objects.push(o);
        }
    ctx.st.q(
        "insert into character_deco (uid, hair_id, pose_id, objects) values (?, ?, ?, ?) "
        "on conflict(uid) do update set hair_id = excluded.hair_id, pose_id = excluded.pose_id, objects = excluded.objects",
        {uid, hair, pose, to_hex(mp_encode(objects))});
    Value data = ctx.base_data(), deco = Value::object();
    deco["character_id"] = uid.v;
    deco["hair_id"] = hair;
    deco["pose_id"] = pose;
    deco["CharacterDecoObject"] = objects;
    data["CharacterDeco"] = deco;
    data["DecoObject"] = deco_list(ctx);
    // read by mastery_session.sh
    LOGI("server", "SetCharacterDeco %llx: hair %u, pose %u, %zu object(s)", (unsigned long long)uid.v, hair, pose, objects.arr.size());
    return body(data);
}

// FavoriteDecoObject(vector<u32> master_deco_ids) -> FavoriteDecoObjectRes         fid 2b486f97
// UnFavoriteDecoObject(vector<u32> master_deco_ids) -> UnFavoriteDecoObjectRes     fid 6c67993d
// API: docs/api.md#favoritedecoobject, docs/api.md#unfavoritedecoobject   Rules: docs/server-rules.md#deco
//
// Marks (or unmarks) owned decorations as favourites (the menu's list, sorted by them).
//   (b) The request names master_deco_ids; the answer FavoriteDecoObjectResult is a map of the
//   changed CDecoObjectInfo by master_deco_id, which the client merges into its list.
//   (d) Ids not owned are skipped (logged), not refused.
// Answers: the player state, FavoriteDecoObjectResult.
std::vector<u8> favorite_deco_object(Ctx& ctx, const Request& req) {
    const bool on = req.method == "FavoriteDecoObject";
    Value result = Value::object();
    const PlayerId owner = player_id(ctx);
    if (!req.vecs.empty())
        for (u64 v : req.vecs[0]) {
            const u32 id = (u32)v;
            if (!owns_deco(ctx, id)) {
                LOGW("server", "%s: decoration %u not owned; skipped", req.method.c_str(), id);
                continue;
            }
            ctx.st.q("update deco_owned set is_favorite = ? where master_deco_id = ?", {on ? 1 : 0, id});
            ctx.st.q("select * from deco_owned where master_deco_id = ?", {id}, [&](const Row& row) {
                Value e = Value::object();
                e["id"] = kDecoUid0 + (u64)row.i("id");
                e["player_id"] = owner.v;
                e["master_deco_id"] = id;
                e["is_favorite"] = on;
                result[std::to_string(id)] = e;
            });
        }
    Value data = ctx.base_data();
    data["FavoriteDecoObjectResult"] = result;
    LOGI("server", "%s: %zu decoration(s)", req.method.c_str(), result.map.size());  // read by mastery_session.sh
    return body(data);
}

// The decoration APIs and hooks (src/core/modules.cpp's order).
void register_deco() {
    add_api({"GetDecoInfo"}, get_deco_info);
    add_api({"SetCharacterDeco"}, set_character_deco);
    add_api({"FavoriteDecoObject", "UnFavoriteDecoObject"}, favorite_deco_object);
    add_grant(kContentDecoObject, grant_deco_content);
    add_grant(kContentDecoHair, grant_deco_content);
    add_response_hook(deco_count_key);
}

}  // namespace soa::server

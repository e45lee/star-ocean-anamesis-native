"""Part 2: content beyond events and gacha. Each master row becomes a ContentItem whose `gate` lists
the files its use needs; its other refs are reported but don't block it.

Kinds: missions and story chapters (master_mission by area, the world map's chapters, the tower,
training), Sphere 211 (floors, mission boxes), characters (master_role -> master_person), items,
and the one-row-one-item kinds in ROW_KINDS (world bosses, deep space, login bonuses, titles,
deco, stamps, exchange shops, skills, studio backgrounds).
"""
from __future__ import annotations

import collections
import re
from dataclasses import dataclass
from typing import Callable, Optional

from . import rules
from .master import MasterIndex, group_rows
from .model import ContentGroup, ContentItem, ContentKind
from .references import add_mission_refs

#: World map chapters are labelled `mXX_YY_...`: XX names the episode (d, from the chapters' dates
#: and the EP2 / EP3 packs), YY the chapter.
WORLD_MAP_CHAPTER_RE = re.compile(r"m(\d\d)_(\d\d)")
WORLD_MAP_CHAPTER_LEN = 6
WORLD_MAP_EPISODES = {"02": 2, "06": 3}
#: Weapon kind whose master_weapon.asf names an image, not a model (skipped).
WEAPON_KIND_NOT_A_MODEL = "W99St"
#: master_exchange_shop_contents.content_type values that are master_item ids (a).
SHOP_ITEM_CONTENT_TYPES = (1, 8, 9)


def new_item(master: MasterIndex, typ: str, key, label: str, mid: Optional[str], ja: Optional[str] = None,
             start: str = "", end: str = "", extra: str = "") -> ContentItem:
    """A part-2 row: its Japanese name and English from the TSV / Global master only (no glossary
    for row names; `how` is "gl" for either source)."""
    names = master.names
    ja = ja if ja is not None else names.text(mid)
    en = (names.official(mid) if mid else names.tsv.get(names.key(ja))) or ""
    return ContentItem(typ, key, label, ja, en, "gl" if en else "none", start, end, extra)


def mission_items(master: MasterIndex, rows, table: str, replace: Optional[dict] = None) -> list[ContentItem]:
    """One item per mission row, gated by its playability files."""
    items = []
    for m in rows:
        item = new_item(master, "mission", m["id"], m["id_label"], m["name_message_id"])
        item.gate = add_mission_refs(master, item, m, replace or {}, table).gate
        items.append(item)
    return items


def collect_beyond(master: MasterIndex) -> list[ContentKind]:
    """Every part-2 kind, in document order."""
    kinds = [missions_kind(master), sphere211_kind(master), characters_kind(master), items_kind(master)]
    kinds += [row_kind(master, k) for k in ROW_KINDS]
    return kinds


# ---------------------------------------------------------------- missions
MISSIONS_DESCRIPTION = (
    "Each mission is playable when the local server's check "
    "passes: every stage's battle map (`BG/<map>.asf/.aaf/.acf`) and every enemy's model "
    "(`Character/<asf>.asf`) are present; a story mission (no stages) needs its `Script/` and "
    "`Scenario/` file (server/src/api/events/event_missions.cpp `battle_files` / `story_playable`, "
    "the rule Sphere 211 and the tower use too; docs/server-rules.md). Stage BGM, enemy "
    "animation / motion files and story scripts of battle missions are listed but don't block. "
    "The episode packs (`EP1`-`EP3`: the main story's scripts, scenario text, talk scenes, voices, "
    "SE and movies) are complete: every member of the ep1-3 manifests is in the download. Event "
    "story voices and SE (`Sound/TS_*`, `Voice_TS_*`) are named inside the scripts, not by the "
    "master, and are gone with the missing event scripts (part 1).")


def missions_kind(master: MasterIndex) -> ContentKind:
    """Missions: EP1 planets (master_mission by area), the world map (EP2 / EP3), tower, training."""
    return ContentKind("Missions and story chapters", MISSIONS_DESCRIPTION,
                       area_mission_groups(master) + world_map_groups(master) + tower_groups(master)
                       + [training_group(master)])


def area_mission_groups(master: MasterIndex) -> list[ContentGroup]:
    names = master.names
    area = {r["id"]: r for r in master.query("select * from master_area")}
    by_area = group_rows(master.query("select * from master_mission order by order_id, id"), "master_area_id")
    groups = []
    for aid, rows in sorted(by_area.items(), key=lambda x: (area[x[0]]["order_id"] if x[0] in area else 0, x[0])):
        ar = area.get(aid)
        if ar:
            ja = names.text(ar["name_message_id"])
            en, how = names.english(ar["name_message_id"])
        else:
            ja, en, how = f"master_area_id {aid}", "no master_area row (test missions, by their names)", "tsv"
        groups.append(ContentGroup(ja or f"area {aid}", en, how,
                                   f"master_mission, area `{ar['id_label'] if ar else aid}`",
                                   mission_items(master, rows, "master_mission")))
    return groups


def world_map_groups(master: MasterIndex) -> list[ContentGroup]:
    chapters = collections.defaultdict(list)
    for m in master.query("select * from master_world_map_mission order by order_id, id"):
        chapters[m["id_label"][:WORLD_MAP_CHAPTER_LEN]].append(m)
    groups = []
    for chapter, rows in sorted(chapters.items()):
        mm = WORLD_MAP_CHAPTER_RE.match(chapter)
        ep = WORLD_MAP_EPISODES.get(mm.group(1)) if mm else None
        ja = f"EP{ep} 第{int(mm.group(2))}章" if ep else chapter
        en = f"Episode {ep}, Chapter {int(mm.group(2))}" if ep else chapter
        groups.append(ContentGroup(ja, en, "tsv", f"master_world_map_mission `{chapter}_*` (EP from the label: "
                                   "m02 = EP2, m06 = EP3, (d) from the chapters' dates and the EP2 / EP3 packs)",
                                   mission_items(master, rows, "master_world_map_mission")))
    return groups


def tower_groups(master: MasterIndex) -> list[ContentGroup]:
    names = master.names
    by_area = group_rows(master.query("select * from master_tower_mission order by order_id, id"),
                         "master_tower_area_id")
    groups = []
    for ar in master.query("select * from master_tower_area order by serial_number, id"):
        en, how = names.english(ar["name_message_id"])
        groups.append(ContentGroup(names.text(ar["name_message_id"]), en, how,
                                   f"master_tower_mission, tower area `{ar['id_label']}` "
                                   f"({ar['opened_at']} → {ar['closed_at']})",
                                   mission_items(master, by_area.get(ar["id"], []), "master_tower_mission")))
    return groups


def training_group(master: MasterIndex) -> ContentGroup:
    rows = master.query("select * from master_training_mission order by id")
    return ContentGroup("シミュレーター", "Simulator (training)", "tsv", "master_training_mission",
                        mission_items(master, rows, "master_training_mission"))


# ---------------------------------------------------------------- Sphere 211
SPHERE211_DESCRIPTION = (
    "Floors need their battle map; a cell battle is lotted from the floor's mission "
    "box, and the server lots only playable missions (docs/server-rules.md \"Sphere 211\", "
    "\"Missing maps\"; the same check as above). Floor backgrounds and BGM are listed but don't block.")


def sphere211_kind(master: MasterIndex) -> ContentKind:
    """Sphere 211: floors (their map, background, BGM) and the mission boxes' missions."""
    return ContentKind("Sphere 211", SPHERE211_DESCRIPTION, floor_groups(master) + mission_box_groups(master))


def floor_item(master: MasterIndex, f) -> ContentItem:
    item = new_item(master, "floor", f["id"], f["id_label"], f["name_message_id"])
    if f["bg_resource"]:
        item.add(rules.IMAGE.path(f["bg_resource"]), "floor background", "master_sphere211_floor.bg_resource",
                 f["id_label"], item.ja)
    if f["master_map_id_label"]:
        for ext, path in rules.map_files(f["master_map_id_label"]):
            item.add(path, f"battle map (.{ext})", "master_sphere211_floor.master_map_id", f["id_label"], item.ja, 3)
            item.gate.add(path)
    if f["stage_bgm"]:
        item.add(rules.BGM.path(f["stage_bgm"]), "stage BGM", "master_sphere211_floor.stage_bgm", f["id_label"],
                 item.ja, 4)
    return item


def floor_groups(master: MasterIndex) -> list[ContentGroup]:
    floors = group_rows(master.query("select * from master_sphere211_floor order by floor_group_id, level, id"),
                        "floor_group_id_label")
    return [ContentGroup(f"フロアグループ {fg}", f"Floor group {fg}", "tsv", "master_sphere211_floor",
                         [floor_item(master, f) for f in rows])
            for fg, rows in sorted(floors.items())]


def mission_box_groups(master: MasterIndex) -> list[ContentGroup]:
    boxes = group_rows(master.query(
        "select b.mission_box_group_id_label g, m.* from master_sphere211_mission_box b "
        "join master_event_mission m on m.id = b.master_mission_id order by b.mission_box_group_id_label, b.id"), "g")
    event_area = {r["id"]: r for r in master.query("select * from master_event_area")}
    groups = []
    for g, rows in sorted(boxes.items()):
        items = []
        for m in rows:
            area = event_area.get(m["master_event_area_id"])
            replace = master.replacements(area["resource_replace_group_id"]) if area else {}
            items += mission_items(master, [m], "master_event_mission", replace)
        groups.append(ContentGroup(f"ミッションボックス {g}", f"Mission box {g}", "tsv",
                                   "master_sphere211_mission_box -> master_event_mission", items))
    return groups


# ---------------------------------------------------------------- characters
CHARACTERS_DESCRIPTION = (
    "Each playable role (`master_role`): its person's model files gate it (the "
    "four person resource fields, docs/notes.md \"Characters\"), and its portraits "
    "`Image/<code>_{fl,ic,fv,cs,ca}<variant>.aif` (code and variant from the person label "
    "`<code>_b<variant>`; the rule is (d), from the names: 302 of 307 playable persons have all five) "
    "gate it too, since the roster and party screens show them. Voices, the universe-chip "
    "portrait and the home model are listed but don't block.")


def character_item(master: MasterIndex, role) -> ContentItem:
    """A playable role: model files and portraits gate it; voices, chip and home model don't."""
    person = master.person[role["master_person_id"]]
    item = new_item(master, "character", role["id"], role["id_label"], person["name_message_id"],
                    start=role["opened_at"] or "")
    ja, en = master.names.person(person["name_message_id"])
    item.ja, item.en, item.how = ja, en or item.en, "names" if en else item.how
    item.ja = f"★{role['rarity']} {item.ja}"
    label = person["id_label"]
    for col, rule, _, kind in rules.PERSON_RESOURCES:
        if person[col]:
            item.add(rule.path(person[col]), kind, f"master_person.{col}", label, item.ja, 1)
            item.gate.add(rule.path(person[col]))
    mm = re.match(rules.PERSON_LABEL_RE, label)
    if mm:
        for k, kind in rules.PORTRAIT_KINDS:
            path = rules.IMAGE.path(f"{mm.group(1)}_{k}{mm.group(2)}")
            item.add(path, kind, "master_person.id_label (naming rule (d))", label, item.ja, 2)
            item.gate.add(path)
        if mm.end() == len(label):  # suffixed persons (`_2`, ...) have no chip of their own
            item.add(rules.UNIVERSE_CHIP.path(label), "universe-chip portrait",
                     "master_person.id_label (naming rule (d))", label, item.ja, 2)
    for col, kind in rules.PERSON_VOICE_PACKS:
        if person[col]:
            item.add(rules.SOUND_PACK.path(person[col]), kind, f"master_person.{col}", label, item.ja, 3)
    if person["home3d_file"]:
        item.add(rules.CHARACTER_MODEL.path(person["home3d_file"]), "home 3D model", "master_person.home3d_file",
                 label, item.ja, 4)
    return item


def characters_kind(master: MasterIndex) -> ContentKind:
    roles = master.query("select r.*, p.id_label person from master_role r join master_person p "
                         "on p.id = r.master_person_id order by r.order_id, r.id")
    return ContentKind("Characters", CHARACTERS_DESCRIPTION,
                       [ContentGroup("キャラクター", "Characters", "tsv", "master_role -> master_person",
                                     [character_item(master, r) for r in roles])])


# ---------------------------------------------------------------- items
ITEMS_DESCRIPTION = (
    "Every `master_item` row: its icon "
    "(`thumbnail_id` -> `Image/<label>.aif`, (b) libSOA has `Image/itm_th_%s.aif`) and, for "
    "weapons, the model `Weapon/<master_weapon.asf>.asf` (docs/notes.md \"Resource names\"; "
    "the `W99St` kind names an image there and is skipped). Weapon `.apk` files exist for "
    "animated weapons only and aren't checked.")


def item_item(master: MasterIndex, it) -> ContentItem:
    """A master_item row: its icon and, for weapons, the model gate it."""
    item = new_item(master, "item", it["id"], it["id_label"], it["name_message_id"])
    if it["thumbnail_id_label"]:
        path = rules.IMAGE.path(it["thumbnail_id_label"])
        item.add(path, "item icon", "master_item.thumbnail_id", it["id_label"], item.ja, 1)
        item.gate.add(path)
    if it["wasf"] and it["wkind"] != WEAPON_KIND_NOT_A_MODEL:
        path = rules.WEAPON_MODEL.path(it["wasf"])
        item.add(path, "weapon model", "master_weapon.asf", it["id_label"], item.ja, 2)
        item.gate.add(path)
    return item


def items_kind(master: MasterIndex) -> ContentKind:
    rows = master.query("select i.*, w.asf wasf, w.master_weapon_kind_id_label wkind from master_item i "
                        "left join master_weapon w on w.id = i.master_weapon_id order by i.type, i.serial_number, i.id")
    return ContentKind("Weapons, accessories and items", ITEMS_DESCRIPTION,
                       [ContentGroup("アイテム", "Items", "tsv", "master_item", [item_item(master, it) for it in rows])])


# ---------------------------------------------------------------- one row, one item
def _gate_image(item: ContentItem, name: str, kind: str, col: str, row: str, subject: str) -> None:
    path = rules.IMAGE.path(name)
    item.add(path, kind, col, row, subject)
    item.gate.add(path)


def world_boss_item(master: MasterIndex, r) -> ContentItem:
    item = new_item(master, "world boss", r["id"], r["id_label"], r["message_id_label"], start=r["opened_at"] or "")
    _gate_image(item, r["enemy_icon"], "world boss icon", "master_world_boss.enemy_icon", r["id_label"], item.ja)
    return item


def deep_space_item(master: MasterIndex, r) -> ContentItem:
    item = new_item(master, "deep space area", r["id"], r["id_label"], r["name_message_id_label"])
    for col, kind in (("resource", "area picture"), ("item_icon", "area item icon")):
        if r[col]:
            _gate_image(item, r[col], kind, f"master_deep_space_area.{col}", r["id_label"], item.ja)
    return item


def login_bonus_item(master: MasterIndex, r) -> ContentItem:
    item = new_item(master, "login bonus", r["id"], r["id_label"], r["name_message_id"], start=r["opened_at"] or "",
                    end=r["closed_at"] or "")
    if r["banner_image"]:
        _gate_image(item, r["banner_image"], "login bonus banner", "master_login_bonus.banner_image", r["id_label"],
                    item.ja)
    return item


def title_item(master: MasterIndex, r) -> ContentItem:
    item = new_item(master, "title", r["id"], r["id_label"], r["name_message_id"])
    if r["tips_resource"]:
        _gate_image(item, r["tips_resource"], "title plate", "master_title.tips_resource", r["id_label"], item.ja)
    return item


def deco_item(master: MasterIndex, r) -> ContentItem:
    item = new_item(master, "deco", r["id"], r["id_label"], None, ja=r["id_label"])
    item.en, item.how = "", "none"
    if r["model_resource_name"]:
        path = rules.DECO_MODEL.path(r["model_resource_name"])
        item.add(path, "deco model", "master_deco_object.model_resource_name", r["id_label"], "")
        item.gate.add(path)
    if r["animation_resource_name"]:
        item.add(rules.DECO_ANIMATION.path(r["animation_resource_name"]), "deco animation",
                 "master_deco_object.animation_resource_name", r["id_label"], "")
    return item


def stamp_item(master: MasterIndex, r) -> ContentItem:
    item = new_item(master, "stamp", r["id"], r["id_label"], r["name_message_id"])
    if r["resource_name"]:
        path = rules.IMAGE_WITH_EXT.path(r["resource_name"])
        item.add(path, "stamp image", "master_stamp.resource_name", r["id_label"], item.ja)
        item.gate.add(path)
    if r["sound_resource"]:
        item.add(rules.SOUND_PACK.path(r["sound_resource"]), "stamp voice", "master_stamp.sound_resource",
                 r["id_label"], item.ja)
    return item


def exchange_shop_item(master: MasterIndex, r) -> ContentItem:
    """A shop needs the icons of its prices and goods."""
    item = new_item(master, "exchange shop", r["id"], r["id_label"], r["name_message_id"],
                    start=r["opened_at"] or "", end=r["closed_at"] or "")
    for c in master.shop_contents.get(r["id"], []):
        goods = c["content_id"] if c["content_type"] in SHOP_ITEM_CONTENT_TYPES else None
        for iid in (c["ex_item_id"], goods):
            it = master.items.get(iid) if iid else None
            thumb = master.item_thumb.get(iid) if iid else None
            if it and thumb:
                _gate_image(item, thumb, "item icon", "master_exchange_shop_contents -> master_item.thumbnail_id",
                            it["id_label"], master.names.text(it["name_message_id"]))
    return item


def skill_item(master: MasterIndex, r) -> ContentItem:
    item = new_item(master, "skill", r["id"], r["id_label"], r["name_message_id"])
    if r["skill_icon"]:
        _gate_image(item, r["skill_icon"], "skill icon", "master_skill.skill_icon", r["id_label"], item.ja)
    return item


def studio_bg_item(master: MasterIndex, r) -> ContentItem:
    item = new_item(master, "studio background", r["id"], r["id_label"], r["name_id_label"])
    if r["thumbnail"]:
        _gate_image(item, r["thumbnail"], "studio background thumbnail", "master_studio_bg.thumbnail", r["id_label"],
                    item.ja)
    return item


@dataclass(frozen=True)
class RowKind:
    """A kind whose rows are items one to one: the query, its table and the row -> item maker."""
    title: str
    description: str
    sql: str
    table: str
    make: Callable[[MasterIndex, object], ContentItem]


ROW_KINDS = (
    RowKind("World bosses", "`master_world_boss.enemy_icon`; the fights are event missions (above).",
            "select * from master_world_boss order by opened_at, id", "master_world_boss", world_boss_item),
    RowKind("Deep space areas", "`master_deep_space_area.resource` / `item_icon` (images). Deep-space "
            "missions are timed expeditions with no battle files.",
            "select * from master_deep_space_area order by id", "master_deep_space_area", deep_space_item),
    RowKind("Login bonuses", "`master_login_bonus.banner_image` (the bonus screen's banner); "
            "`master_premium_login_bonus` has no images.",
            "select * from master_login_bonus order by opened_at, id", "master_login_bonus", login_bonus_item),
    RowKind("Titles", "`master_title.tips_resource` (the plate image; most titles have none).",
            "select * from master_title order by order_id, id", "master_title", title_item),
    RowKind("Deco (accessories worn on the model)", "`master_deco_object.model_resource_name` -> `Deco/<x>.asf` "
            "(docs/notes.md \"Resource names\").",
            "select * from master_deco_object order by order_id, id", "master_deco_object", deco_item),
    RowKind("Stamps", "`master_stamp.resource_name` (an image name with its extension), `sound_resource`.",
            "select * from master_stamp order by order_id, id", "master_stamp", stamp_item),
    RowKind("Exchange shops", "`master_exchange_shop` names no file; a shop needs the icons of its prices "
            "and goods (`master_exchange_shop_contents` -> `master_item.thumbnail_id`).",
            "select * from master_exchange_shop order by opened_at, id", "master_exchange_shop", exchange_shop_item),
    RowKind("Skills", "`master_skill.skill_icon` (images). Skill effects (`Effect/<id>.asf/.apk/.aaf`, "
            "loaded per battle) are not checked here.",
            "select * from master_skill order by id", "master_skill", skill_item),
    RowKind("Photo studio backgrounds", "`master_studio_bg.thumbnail`.",
            "select * from master_studio_bg order by order_id, id", "master_studio_bg", studio_bg_item),
)


def row_kind(master: MasterIndex, kind: RowKind) -> ContentKind:
    items = [kind.make(master, r) for r in master.query(kind.sql)]
    return ContentKind(kind.title, kind.description, [ContentGroup(kind.title, kind.title, "tsv", kind.table, items)])

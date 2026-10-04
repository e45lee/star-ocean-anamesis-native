"""Reference collectors shared by events, gacha banners and part 2: a banner's images and a
mission's files (script, scenario text, stage maps, BGM, boss icons, enemy models)."""
from __future__ import annotations

from typing import Optional

from . import rules
from .master import MasterIndex
from .model import ContentItem, MissionFiles

# display order of a mission's files within an item (rendering sorts by it)
ORDER_SCRIPT, ORDER_SCENARIO, ORDER_MAP, ORDER_BGM, ORDER_ICON, ORDER_ENEMY = 1, 2, 3, 4, 5, 6


def add_banner_refs(master: MasterIndex, item: ContentItem, banner, col: str, why: str, subject: str) -> None:
    """A master_banner row's image (a) and the dated replacements of its replace type
    (master_banner_replace.image, a); `Image/<x>.aif` (b)."""
    if not banner or not banner["image"]:
        return
    item.add(rules.IMAGE.path(banner["image"]), why, col, banner["id_label"], subject, 0)
    for r in master.banner_replace.get(banner["master_banner_replace_type_id"], []):
        if r["image"]:
            item.add(rules.IMAGE.path(r["image"]), why + " (dated replacement)", "master_banner_replace.image",
                     r["id_label"], subject, 0)


def add_mission_refs(master: MasterIndex, item: ContentItem, mission, replace: dict[str, str],
                     table: str) -> MissionFiles:
    """Add a mission's files to `item`; return its label, name and gating paths. Gating = what the
    local server's playability check needs (server/src/api/events/event_missions.cpp `battle_files`,
    `story_playable`): each stage's map (.asf/.aaf/.acf) and its enemies' models (.asf); a mission
    without stages needs its Script (and Scenario when named)."""
    name = master.mission_display_name(mission["name_message_id"])
    gate: set[str] = set()
    stages = master.stages.get(mission["id"], [])
    _add_story_refs(item, mission, table, name, gate, story_only=not stages)
    for stage in stages:
        _add_stage_refs(master, item, stage, replace, name, gate)
    return MissionFiles(mission["id_label"], name, gate)


def _column(row, col: str) -> Optional[str]:
    """A column that not every mission table has (None when absent or empty)."""
    return row[col] if col in row.keys() else None


def _add_story_refs(item: ContentItem, mission, table: str, name: str, gate: set[str], story_only: bool) -> None:
    script, scenario = _column(mission, "talk_event_id_label"), _column(mission, "talk_message_file")
    if script:
        path = rules.SCRIPT.path(script)
        item.add(path, "story scene script", f"{table}.talk_event_id_label", mission["id_label"], name, ORDER_SCRIPT)
        if story_only:
            gate.add(path)
    if scenario:
        path = rules.SCENARIO.path(scenario)
        item.add(path, "story dialogue text pack", f"{table}.talk_message_file", mission["id_label"], name,
                 ORDER_SCENARIO)
        if story_only:
            gate.add(path)


def _add_stage_refs(master: MasterIndex, item: ContentItem, stage, replace: dict[str, str], name: str,
                    gate: set[str]) -> None:
    map_label = stage["master_map_id_label"]
    if map_label:
        map_name = replace.get(map_label, map_label)
        col = "master_mission_stage.master_map_id" + (" -> master_replace_resource" if map_name != map_label else "")
        for ext, path in rules.map_files(map_name):
            item.add(path, f"battle map (.{ext})", col, stage["id_label"], name, ORDER_MAP)
            gate.add(path)
    if stage["stage_bgm"]:
        item.add(rules.BGM.path(stage["stage_bgm"]), "boss-stage BGM" if stage["is_boss"] else "stage BGM",
                 "master_mission_stage.stage_bgm", stage["id_label"], name, ORDER_BGM)
    if stage["boss_icon"]:
        item.add(rules.IMAGE.path(stage["boss_icon"]), "boss icon", "master_mission_stage.boss_icon",
                 stage["id_label"], name, ORDER_ICON)
    for pid, person, boss in master.enemy_members(stage["master_enemy_party_id"]):
        who = master.person_name(pid) + (" (boss)" if boss else "")
        for col, rule, enemy_kind, _ in rules.PERSON_RESOURCES:
            if person[col]:
                item.add(rule.path(person[col]), enemy_kind, f"master_person.{col} (enemy party)",
                         stage["master_enemy_party_id_label"], who, ORDER_ENEMY)
        if person["asf"]:
            gate.add(rules.CHARACTER_MODEL.path(person["asf"]))

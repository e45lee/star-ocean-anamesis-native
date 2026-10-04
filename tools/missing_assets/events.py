"""Part 1, events: what each master_event_area references.

  master_event_area.bg_resource                                  Image/<x>.aif
  master_banner.image (area.master_banner_id(_label); banners whose target_content_type = 3 point
    at the area; master_banner_replace.image of their replace type)  Image/<x>.aif
  master_event_area.voice_menu_pack_name                         Sound/<x>.spk
  master_event_mission (by area): the mission's files (references.add_mission_refs), its maps
    mapped through master_replace_resource of the area's resource_replace_group_id
  master_world_boss.enemy_icon (area.event_id_label = world boss id_label)  Image/<x>.aif
"""
from __future__ import annotations

from . import rules
from .master import BANNER_TARGET_EVENT_AREA, MasterIndex, group_rows
from .model import ContentItem
from .names import TSV_LABEL_PREFIX
from .references import ORDER_ICON, add_banner_refs, add_mission_refs

WEEKDAYS = "Sun Mon Tue Wed Thu Fri Sat".split()
#: Japanese names that mean "no name" (the area is then named by its label in the TSV).
NO_NAME = ("", "--")


def event_window(area, terms: list, weekly: list) -> tuple[str, str, str]:
    """(start, end, note) of an area: its master_event_term span, else the area's own window, else
    its weekly days."""
    if terms:
        start = f"{min(t['opened_day'] for t in terms)} {terms[0]['opened_time'] or ''}".strip()
        end = max(f"{t['closed_day']} {t['closed_time'] or ''}".strip() for t in terms)
        return start, end, f"{len(terms)} term(s)"
    if area["opened_at"]:
        return area["opened_at"], area["closed_at"] or "", "area window"
    if weekly:
        days = sorted({WEEKDAYS[w["week_id"] % 7] for w in weekly}, key=WEEKDAYS.index)
        return "", "", "weekly: " + ", ".join(days)
    return "", "", "no term"


def collect_events(master: MasterIndex) -> list[ContentItem]:
    """One ContentItem per master_event_area row, by id."""
    q, names = master.query, master.names
    terms = group_rows(q("select * from master_event_term order by opened_day, opened_time, id"), "master_event_area_id")
    weekly = group_rows(q("select * from master_event_weekly order by week_id, id"), "master_event_area_id")
    missions = group_rows(q("select * from master_event_mission order by order_id, id"), "master_event_area_id")
    world_boss = {r["id_label"]: r for r in q("select * from master_world_boss")}
    out = []
    for area in q("select * from master_event_area order by id"):
        start, end, extra = event_window(area, terms.get(area["id"], []), weekly.get(area["id"], []))
        ja = names.text(area["name_message_id"])
        en, how = names.english(area["name_message_id"])
        if ja in NO_NAME and TSV_LABEL_PREFIX + area["id_label"] in names.tsv:  # unnamed areas: named by label
            en, how = names.tsv[TSV_LABEL_PREFIX + area["id_label"]], "tsv"
        item = ContentItem("event", area["id"], area["id_label"], ja, en, how, start, end, extra)
        subject = en or area["id_label"]
        _add_area_refs(master, item, area, subject)
        replace = master.replacements(area["resource_replace_group_id"])
        item.missions = [add_mission_refs(master, item, m, replace, "master_event_mission")
                         for m in missions.get(area["id"], [])]
        boss = world_boss.get(area["event_id_label"] or "")
        if boss and boss["enemy_icon"]:
            item.add(rules.IMAGE.path(boss["enemy_icon"]), "world boss icon", "master_world_boss.enemy_icon",
                     boss["id_label"], names.text(boss["message_id_label"]), ORDER_ICON)
        out.append(item)
    return out


def _add_area_refs(master: MasterIndex, item: ContentItem, area, subject: str) -> None:
    """The area's background, its banners and its menu voice pack."""
    if area["bg_resource"]:
        kind = "mission-board map background" if area["is_mission_board"] == 1 else "event list banner"
        item.add(rules.IMAGE.path(area["bg_resource"]), kind, "master_event_area.bg_resource", area["id_label"], subject)
    banner = (master.banner_by_label.get(area["master_banner_id_label"] or "")
              or master.banner_by_id.get(area["master_banner_id"]))
    add_banner_refs(master, item, banner, "master_banner.image (master_event_area.master_banner_id)", "event banner",
                    subject)
    for banner in master.banner_targets.get((BANNER_TARGET_EVENT_AREA, area["id"]), []):
        add_banner_refs(master, item, banner, "master_banner.image (target_content_type 3)", "home / notice banner",
                        subject)
    if area["voice_menu_pack_name"]:
        item.add(rules.SOUND_PACK.path(area["voice_menu_pack_name"]), "event menu voice pack",
                 "master_event_area.voice_menu_pack_name", area["id_label"],
                 f"cues {area['voice_menu_cue_min']}-{area['voice_menu_cue_max']}")

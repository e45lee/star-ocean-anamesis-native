"""Part 1, gacha banners: master_gacha rows grouped by banner_id (one list banner; step-up chains
share it), and what each group references.

  master_banner.image (id_label = banner_id; banners whose target_content_type = 1 point at a
    gacha of the group; master_banner_replace.image)                 Image/<x>.aif
  master_gacha.image1..image4, master_gacha_image.image_resource      Image/<x>.aif
  master_gacha.resource_replace_group_id -> master_replace_resource.replace_res (res_type 4)
                                                                      BG/<x>.asf/.aaf/.acf
"""
from __future__ import annotations

import collections
import re

from . import rules
from .master import BANNER_TARGET_GACHA, MasterIndex, group_rows
from .model import ContentItem, GachaRow
from .references import add_banner_refs

GACHA_TYPES = {0: "character", 1: "weapon", 2: "box"}
#: master_gacha.image1..image4: the HTML-era gacha screen's pick-up panels.
PANEL_COLUMNS = 4
#: How many pick-up names the subject line shows.
SUBJECT_PICKS = 4
# display order: panels k = 1..4, gacha_image panels 10 + view index, the scene map last
ORDER_IMAGE_PANEL_BASE = 10
ORDER_SCENE_MAP = 30
#: Group key for gacha rows without a banner_id.
NO_BANNER_KEY = "(none:{})"
#: A step's number at the end of the title (or before a parenthesis) is dropped for a step-up chain.
STEP_SUFFIX_RE = re.compile(r"\s*ステップ\s*\d+\s*$")
STEP_BEFORE_PAREN_RE = re.compile(r"\s*ステップ\s*\d+(?=\()")


def group_by_banner(rows) -> dict[str, list]:
    """Gacha rows (in opening order) grouped by banner_id, in order of each group's first row."""
    groups: dict[str, list] = collections.OrderedDict()
    for g in rows:
        groups.setdefault(g["banner_id"] or NO_BANNER_KEY.format(g["id_label"]), []).append(g)
    return groups


def banner_title(first_name: str, steps: int) -> str:
    """The group's title: the first row's name, without the step number when the group has steps."""
    if steps <= 1:
        return first_name
    return STEP_BEFORE_PAREN_RE.sub("", STEP_SUFFIX_RE.sub("", first_name))


def group_note(rows) -> str:
    """`<n> gacha row(s), <types>[, step-up]`."""
    kinds = sorted({GACHA_TYPES.get(g["gacha_type"], str(g["gacha_type"])) for g in rows})
    return f"{len(rows)} gacha row(s), {'/'.join(kinds)}" + (", step-up" if any(g["is_stepup"] for g in rows) else "")


def collect_gachas(master: MasterIndex) -> tuple[list[ContentItem], list[ContentItem]]:
    """(one ContentItem per banner group, the groups whose banner_id has no master_banner row)."""
    names = master.names
    images = group_rows(master.query("select * from master_gacha_image order by master_gacha_id, view_index, id"),
                        "master_gacha_id")
    groups = group_by_banner(master.query("select * from master_gacha order by opened_at, serial_number, id"))
    out, dangling = [], []
    for banner_id, rows in groups.items():
        title = banner_title(names.text(rows[0]["name_message_id"]), len(rows))
        en, how = names.english(None, title)
        start = min((g["opened_at"] or "") for g in rows)
        end = max((g["closed_at"] or "") for g in rows)
        item = ContentItem("gacha", banner_id, banner_id, title, en, how, start, end, group_note(rows))
        item.gachas = [GachaRow(g["id_label"], names.text(g["name_message_id"]), g["opened_at"], g["closed_at"])
                       for g in rows]
        item.picks = _pick_ups(master, rows, images)
        subject = (en or title) + (" — pick-ups: " + "; ".join(item.picks[:SUBJECT_PICKS]) if item.picks else "")
        banner = master.banner_by_label.get(banner_id)
        if banner is None:
            dangling.append(item)
        add_banner_refs_for_group(master, item, banner, rows, subject)
        for g in rows:
            _add_gacha_row_refs(master, item, g, images.get(g["id"], []), subject)
        out.append(item)
    return out, dangling


def _pick_ups(master: MasterIndex, rows, images) -> list[str]:
    """The distinct names of what the group's gacha images show, in order."""
    picks: list[str] = []
    for g in rows:
        for im in images.get(g["id"], []):
            name = master.gacha_content_name(im)
            if name and name not in picks:
                picks.append(name)
    return picks


def add_banner_refs_for_group(master: MasterIndex, item: ContentItem, banner, rows, subject: str) -> None:
    """The list banner (banner_id) and the home / notice banners that target a gacha of the group."""
    add_banner_refs(master, item, banner, "master_banner.image (master_gacha.banner_id)", "gacha list banner", subject)
    for g in rows:
        for target in master.banner_targets.get((BANNER_TARGET_GACHA, g["id"]), []):
            if target is not banner:
                add_banner_refs(master, item, target, "master_banner.image (target_content_type 1)",
                                "home / notice banner", subject)


def _add_gacha_row_refs(master: MasterIndex, item: ContentItem, g, images, subject: str) -> None:
    """A gacha row's panels (image1..4, master_gacha_image) and its scene map replacements."""
    for k in range(1, PANEL_COLUMNS + 1):
        if g[f"image{k}"]:
            item.add(rules.IMAGE.path(g[f"image{k}"]), f"pick-up panel {k} (HTML-era gacha screen)",
                     f"master_gacha.image{k}", g["id_label"], subject, k)
    for im in images:
        if im["image_resource"]:
            name = master.gacha_content_name(im)
            kind = f"pick-up panel (view {im['view_index']})" if name else f"main panel (view {im['view_index']})"
            item.add(rules.IMAGE.path(im["image_resource"]), kind, "master_gacha_image.image_resource", g["id_label"],
                     name or subject, ORDER_IMAGE_PANEL_BASE + (im["view_index"] or 0))
    for original, replacement in sorted(master.replacements(g["resource_replace_group_id"]).items()):
        for ext, path in rules.map_files(replacement):
            item.add(path, f"gacha scene map {rules.MAP_PART[ext]} (replaces {original})",
                     "master_gacha.resource_replace_group_id -> master_replace_resource.replace_res",
                     g["id_label"], subject, ORDER_SCENE_MAP)

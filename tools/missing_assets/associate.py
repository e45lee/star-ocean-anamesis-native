"""Which event a gacha banner belongs to. The master has no gacha -> event column, so two rules join
what it does record; the first that gives exactly one event wins:

1. **Bonus characters** ((a) the join, (d) the time check): the event's bonus characters
   (`master_mission_character_bonus.master_role_category_id`, whose `master_area_id` is the
   `master_event_area.id`) include a pick-up of the banner (`master_gacha_image` rows with
   content_type 2, `master_gacha_pickup` of the gacha's `gacha_pickup_group_id`; both mapped to
   `master_role.role_category_id`), and the banner opens inside one of the event's windows
   (`master_event_term`, else the area's own opened_at..closed_at). Several such events: those
   that also pass rule 2; still several: unassociated.
2. **Released together** ((d)): the banner opens within an hour of the first window start of
   exactly one story event (an event with a mission that has a talk script). Banners that are
   not event draws are excluded from this rule (they stay unassociated unless rule 1 places
   them; (a) the columns, (d) what they mean): every gacha row of the banner is a step-up row
   (`is_stepup`), a ticket draw (not a box, `coin` 0, paid with `ticket_item_id`) or a free
   limited draw (not a box, `coin` 0, no ticket, `limit_count` > 0: the download-milestone and
   campaign "once per person" draws such as banner212). Box draws paid with event coins stay in.

A banner opens at the earliest opened_at of its gacha rows. A banner_id reused for a later
release (e.g. `banner_20180426_3001` opening on 2018-10-11) is one group and is placed by its
earliest opening. Anything else stays unassociated.
"""
from __future__ import annotations

import collections
import datetime as dt
from dataclasses import dataclass, field
from typing import Optional

from .master import CONTENT_TYPE_ROLE, MasterIndex, group_rows
from .model import ContentItem

RELEASE_TOLERANCE = dt.timedelta(hours=1)
RULE_BONUS = "bonus characters"
RULE_RELEASE = "released together"
RULE_AMBIGUOUS = "several events"

Window = tuple[dt.datetime, dt.datetime]


def not_an_event_draw(row) -> bool:
    """A step-up row, a ticket draw or a free limited (milestone / campaign) draw (see rule 2)."""
    if row["is_stepup"]:
        return True
    if row["is_box"] or (row["coin"] or 0) > 0:
        return False
    return bool(row["ticket_item_id"]) or (row["limit_count"] or 0) > 0


def excluded_from_release_rule(rows) -> bool:
    """Every gacha row of the banner is not an event draw."""
    return bool(rows) and all(not_an_event_draw(r) for r in rows)


def parse_time(s: Optional[str]) -> Optional[dt.datetime]:
    """A master date-time (`YYYY-MM-DD hh:mm:ss`), or None."""
    try:
        return dt.datetime.fromisoformat(s.strip()) if s else None
    except ValueError:
        return None


@dataclass
class Association:
    """banner key -> event label, and how many banners each rule placed."""
    event_of: dict[str, str] = field(default_factory=dict)
    by_rule: collections.Counter = field(default_factory=collections.Counter)
    excluded: int = 0  # banners rule 2 skipped (not event draws) that rule 1 did not place

    def banners_of(self, event_label: str, banners: list[ContentItem]) -> list[ContentItem]:
        return [b for b in banners if self.event_of.get(b.key) == event_label]


def event_windows(master: MasterIndex) -> dict[str, list[Window]]:
    """Each event's windows: its master_event_term rows, else the area's own window."""
    out: dict[str, list[Window]] = collections.defaultdict(list)
    for t in master.query("select * from master_event_term order by opened_day, opened_time, id"):
        start = parse_time(f"{t['opened_day']} {t['opened_time'] or '00:00:00'}")
        end = parse_time(f"{t['closed_day']} {t['closed_time'] or '23:59:59'}")
        if start and end:
            out[t["master_event_area_id_label"]].append((start, end))
    for area in master.query("select * from master_event_area order by id"):
        start, end = parse_time(area["opened_at"]), parse_time(area["closed_at"])
        if area["id_label"] not in out and start and end:
            out[area["id_label"]].append((start, end))
    return out


def story_events(master: MasterIndex) -> set[str]:
    """Events with at least one mission that has a talk script."""
    return {r[0] for r in master.query("select distinct master_event_area_id_label from master_event_mission "
                                       "where talk_event_id_label is not null and talk_event_id_label != ''")}


def bonus_events_by_category(master: MasterIndex) -> dict[object, set[str]]:
    """Role category -> the events whose bonus characters include it."""
    areas = {r["id"]: r["id_label"] for r in master.query("select id, id_label from master_event_area")}
    out: dict[object, set[str]] = collections.defaultdict(set)
    for r in master.query("select master_area_id, master_role_category_id from master_mission_character_bonus"):
        if r["master_area_id"] in areas:
            out[r["master_role_category_id"]].add(areas[r["master_area_id"]])
    return out


class Associator:
    """Applies the rules above; the lookup tables are built once."""

    def __init__(self, master: MasterIndex):
        self.master = master
        self.windows = event_windows(master)
        self.story = story_events(master)
        self.bonus = bonus_events_by_category(master)
        self.role_category = {r["id"]: r["role_category_id"]
                              for r in master.query("select id, role_category_id from master_role")}
        self.images = group_rows(master.query("select master_gacha_id, content_id from master_gacha_image "
                                              "where content_type=?", CONTENT_TYPE_ROLE), "master_gacha_id")
        self.pickups = group_rows(master.query("select pickup_group_id, master_role_id from master_gacha_pickup"),
                                  "pickup_group_id")

    def categories(self, rows) -> set:
        """The role categories of a banner group's pick-ups."""
        roles = set()
        for g in rows:
            roles |= {im["content_id"] for im in self.images.get(g["id"], [])}
            roles |= {p["master_role_id"] for p in self.pickups.get(g["gacha_pickup_group_id"], [])}
        return {self.role_category[r] for r in roles if r in self.role_category}

    def released_with(self, opening: dt.datetime) -> set[str]:
        """Story events whose first window starts within the tolerance of `opening`."""
        return {e for e, ws in self.windows.items()
                if e in self.story and abs(min(ws)[0] - opening) <= RELEASE_TOLERANCE}

    def event_for(self, rows) -> tuple[Optional[str], Optional[str]]:
        """(event label, rule) for a banner group's gacha rows, or (None, None / RULE_AMBIGUOUS)."""
        openings = [t for t in (parse_time(g["opened_at"]) for g in rows) if t]
        if not openings:
            return None, None
        opening = min(openings)
        bonus = set()
        for cat in self.categories(rows):
            bonus |= self.bonus.get(cat, set())
        bonus = {e for e in bonus if any(a <= opening <= b for a, b in self.windows.get(e, []))}
        if len(bonus) == 1:
            return next(iter(bonus)), RULE_BONUS
        released = set() if excluded_from_release_rule(rows) else self.released_with(opening)
        if bonus:
            both = bonus & released
            return (next(iter(both)), RULE_BONUS) if len(both) == 1 else (None, RULE_AMBIGUOUS)
        if len(released) == 1:
            return next(iter(released)), RULE_RELEASE
        return None, (RULE_AMBIGUOUS if released else None)


def associate(master: MasterIndex, gachas: list[ContentItem]) -> Association:
    """The event of each banner group (`ContentItem.key` = banner key) that the rules place."""
    rows_by_label = {r["id_label"]: r for r in master.query("select * from master_gacha")}
    associator = Associator(master)
    result = Association()
    for banner in gachas:
        rows = [rows_by_label[g.label] for g in banner.gachas]
        event, rule = associator.event_for(rows)
        if event:
            result.event_of[banner.key] = event
        elif excluded_from_release_rule(rows):
            result.excluded += 1
        result.by_rule[rule or "none"] += 1
    return result

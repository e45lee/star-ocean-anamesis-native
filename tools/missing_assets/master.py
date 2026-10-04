"""The 3.7.0 master DB: the connection, the lookup tables the collectors share, and the subject names
(roles, items, persons) shown next to files."""
from __future__ import annotations

import collections
import functools
import sqlite3
from typing import Optional

from .names import Names

#: master_replace_resource.res_type of map replacements (CResourceReplaceManager::GetResourceName(id, 4)).
RES_TYPE_MAP = 4
#: master_banner.target_content_type values (a): what a home / notice banner points at.
BANNER_TARGET_GACHA = 1
BANNER_TARGET_EVENT_AREA = 3
#: master_gacha_image.content_type values (a): 1 item (weapon), 2 role.
CONTENT_TYPE_ITEM, CONTENT_TYPE_ROLE = 1, 2
#: master_enemy_party has member1..member8 (and member<i>_boss).
ENEMY_PARTY_SIZE = 8


def open_master(path: str) -> sqlite3.Connection:
    """The master, read-only, rows addressable by column name."""
    conn = sqlite3.connect(f"file:{path}?mode=ro", uri=True)
    conn.row_factory = sqlite3.Row
    return conn


def group_rows(rows, key: str) -> dict:
    """Rows grouped by a column, each group in row order."""
    out = collections.defaultdict(list)
    for r in rows:
        out[r[key]].append(r)
    return out


class MasterIndex:
    """The lookup tables over the master that several collectors use."""

    def __init__(self, conn: sqlite3.Connection, names: Names):
        self.conn, self.names = conn, names
        q = self.query
        banners = q("select * from master_banner")
        self.banner_by_label = {r["id_label"]: r for r in banners}
        self.banner_by_id = {r["id"]: r for r in banners}
        self.banner_targets = collections.defaultdict(list)  # (target_content_type, target id) -> banners
        for r in q("select * from master_banner where target_content_type is not null order by id"):
            self.banner_targets[(r["target_content_type"], r["target_content_id"])].append(r)
        self.banner_replace = group_rows(q("select * from master_banner_replace order by id"), "type_id")
        self.map_replace = collections.defaultdict(dict)  # replace group -> {original map: replacement}
        for r in q("select * from master_replace_resource where res_type=? order by id", RES_TYPE_MAP):
            self.map_replace[r["replace_group_id"]][r["original_res"]] = r["replace_res"]
        self.stages = group_rows(q("select * from master_mission_stage order by master_mission_id, order_id, id"),
                                 "master_mission_id")
        self.parties = {r["id"]: r for r in q("select * from master_enemy_party")}
        self.enemy_person = {r["id"]: r["master_person_id"]
                             for r in q("select id, master_person_id from master_enemy_base_parameter")}
        self.person = {r["id"]: r for r in q("select * from master_person")}
        self.roles = {r["id"]: r for r in q("select id, id_label, master_person_id, rarity from master_role")}
        self.items = {r["id"]: r for r in q("select id, id_label, name_message_id from master_item")}
        self.item_thumb = {r["id"]: r["thumbnail_id_label"] for r in q("select id, thumbnail_id_label from master_item")}

    def query(self, sql: str, *params) -> list[sqlite3.Row]:
        return list(self.conn.execute(sql, params))

    @functools.cached_property
    def shop_contents(self) -> dict:
        """master_exchange_shop_contents by shop, in display order."""
        return group_rows(self.query("select * from master_exchange_shop_contents order by order_id, id"),
                          "master_exchange_shop_id")

    def replacements(self, group_id) -> dict[str, str]:
        """The map replacements of a resource replace group ({} when none)."""
        return self.map_replace.get(group_id, {})

    def enemy_members(self, party_id):
        """(person row, is boss) of each member of an enemy party that resolves to a person."""
        party = self.parties.get(party_id)
        for i in range(1, ENEMY_PARTY_SIZE + 1):
            pid = self.enemy_person.get(party[f"member{i}_id"]) if party else None
            person = self.person.get(pid)
            if person:
                yield pid, person, bool(party[f"member{i}_boss"])

    # -------------------------------------------------------- subject names
    def role_name(self, role_id) -> str:
        """`★<rarity> <Japanese> (<English>)` of a role."""
        r = self.roles.get(role_id)
        if not r:
            return ""
        p = self.person.get(r["master_person_id"])
        ja, en = self.names.person(p["name_message_id"]) if p else ("", None)
        star = f"★{r['rarity']} " if r["rarity"] else ""
        return f"{star}{ja}" + (f" ({en})" if en else "")

    def item_name(self, item_id) -> str:
        """`<Japanese> (<Global English>)` of an item."""
        it = self.items.get(item_id)
        if not it:
            return ""
        ja = self.names.text(it["name_message_id"])
        en = self.names.gl.get(it["name_message_id"]) or self.names.gl_text.get(ja)
        return ja + (f" ({en})" if en else "")

    def person_name(self, pid) -> str:
        """`<Japanese or label> (<English>)` of a person."""
        p = self.person.get(pid)
        if not p:
            return ""
        ja, en = self.names.person(p["name_message_id"])
        return (ja or p["id_label"]) + (f" ({en})" if en else "")

    def gacha_content_name(self, image_row) -> str:
        """The name of what a master_gacha_image row shows (a role or an item), or ""."""
        lab = image_row["content_id_label"] or ""
        if lab.startswith("role_") or image_row["content_type"] == CONTENT_TYPE_ROLE:
            return self.role_name(image_row["content_id"])
        if lab.startswith("item_") or image_row["content_type"] == CONTENT_TYPE_ITEM:
            return self.item_name(image_row["content_id"])
        return ""

    def mission_display_name(self, name_message_id: Optional[str]) -> str:
        """`<Japanese> (<official English>)` of a mission."""
        ja = self.names.text(name_message_id)
        en = self.names.official(name_message_id)
        return ja + (f" ({en})" if en else "")

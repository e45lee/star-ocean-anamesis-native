"""Roster helpers for Game.xml (person_size / person_master_role_id_N)."""
import zipfile
import io

from .master import BASE_APK, NAMES_EN, Master
from .paths import xapk


def roster(kvs):
    return [kvs.get_u32(f"person_master_role_id_{i}") for i in range(kvs.get_u32("person_size"))]


def set_roster(kvs, ids):
    """Rewrite the roster keys, keeping the file's existing entry order where possible."""
    old = kvs.get_u32("person_size")
    for i in range(len(ids), old):
        del kvs.entries[f"person_master_role_id_{i}"]
    for i, rid in enumerate(ids):
        kvs.set_u32(f"person_master_role_id_{i}", rid)
    kvs.set_u32("person_size", len(ids))


def _shipped_files():
    names = set()
    with zipfile.ZipFile(xapk()) as x:
        for apk in (BASE_APK, "assetinstalltime.apk"):
            with zipfile.ZipFile(io.BytesIO(x.read(apk))) as z:
                names.update(n.rsplit("/", 1)[-1] for n in z.namelist())
    return names


def all_playable_roles(master=None):
    """Highest-rarity role id for every playable variant whose model ships in the APK.

    A "variant" is (master_person, role_category); its rarity tiers are separate role ids
    (e.g. role_cp0303_b04a_5131 / _6131). Dummy/test entries (names containing ※) and
    characters not in names_en.json are skipped.
    """
    m = master or Master()
    files = _shipped_files()
    best = {}
    q = """SELECT r.id, r.rarity, r.role_category_id, p.id, p.id_label, p.asf, t.text_value
           FROM master_role r JOIN master_person p ON p.id = r.master_person_id
           LEFT JOIN master_text t ON t.message_id = p.name_message_id AND t.lang = 'ja'"""
    for rid, rarity, cat, pid, plabel, asf, name in m.db.execute(q):
        if not name or "※" in name or plabel.split("_")[0] not in NAMES_EN["characters"]:
            continue
        if not asf or f"{asf}.asf" not in files:
            continue
        key = (pid, cat)
        if key not in best or rarity > best[key][0]:
            best[key] = (rarity, rid)
    return sorted(rid for _, rid in best.values())


def unlock_all(kvs, master=None):
    """Append the top-rarity role of every variant not already owned. Returns ids added."""
    m = master or Master()
    have = roster(kvs)
    owned = set()
    for rid in have:
        r = m.db.execute("SELECT master_person_id, role_category_id FROM master_role WHERE id=?", (rid,)).fetchone()
        if r:
            owned.add(tuple(r))
    added = []
    for rid in all_playable_roles(m):
        key = tuple(m.db.execute("SELECT master_person_id, role_category_id FROM master_role WHERE id=?", (rid,)).fetchone())
        if key not in owned:
            added.append(rid)
            owned.add(key)
    set_roster(kvs, have + added)
    return added

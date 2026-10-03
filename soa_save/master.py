"""Access the decrypted master DB (basmaster.sqlite3) for readable names.

Role/item ids in saves are Framework::CHash32 of the row's id_label (see adld.chash32).
"""
import io
import json
import pathlib
import sqlite3
import zipfile

from .adld import decode
from .paths import GAME_VERSION, REPO, xapk

BASE_APK = "com.square_enix.android_googleplay.StarOceanj.apk"
ASSET = "assets/builtin_data/sqlite/basmaster.sqlite3"
CACHE = REPO / f"data/basmaster-{GAME_VERSION}.sqlite3"


def ensure_db(path=CACHE, xapk_path=None) -> pathlib.Path:
    """Return the decrypted master DB, decrypting it out of the XAPK (version-checked) if missing."""
    path = pathlib.Path(path)
    if not path.exists():
        with zipfile.ZipFile(xapk_path or xapk()) as x:
            version = json.loads(x.read("manifest.json"))["version_name"]
            if version != GAME_VERSION:
                raise ValueError(f"XAPK is game version {version}, expected {GAME_VERSION} (see soa_save/paths.py)")
            with zipfile.ZipFile(io.BytesIO(x.read(BASE_APK))) as apk:
                raw = apk.read(ASSET)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(decode(raw, "sqlite/basmaster.sqlite3"))
    return path


NAMES_EN = json.loads((pathlib.Path(__file__).with_name("names_en.json")).read_text(encoding="utf-8"))


def english_name(person_label, ja_name):
    """Translate a master DB character name using names_en.json. Returns None if unknown."""
    if not ja_name:
        return None
    ch = NAMES_EN["characters"].get((person_label or "").split("_")[0])
    if not ch:
        return None
    base_ja, base_en = ch[0], ch[1]
    rest, suffix = ja_name, ""
    for sj, se in NAMES_EN["suffixes"].items():
        if rest.endswith(sj):
            rest, suffix = rest[: -len(sj)], se
    if base_ja not in rest:
        return None
    prefix = rest[: rest.rindex(base_ja)]
    if not prefix:
        return base_en + suffix
    title = NAMES_EN["titles"].get(prefix)
    if title is None:
        return None
    return (title + base_en if title.endswith("-") else f"{title} {base_en}") + suffix


class Master:
    def __init__(self, path=None):
        self.db = sqlite3.connect(f"file:{ensure_db(path or CACHE)}?mode=ro", uri=True)

    def text(self, message_id, lang="ja"):
        r = self.db.execute("SELECT text_value FROM master_text WHERE message_id=? AND lang=?", (message_id, lang)).fetchone()
        return r[0] if r else None

    def role(self, role_id):
        """Return {id, label, person_label, name, rarity} for a role id, or None."""
        r = self.db.execute(
            "SELECT r.id_label, r.master_person_id_label, p.name_message_id, r.rarity "
            "FROM master_role r LEFT JOIN master_person p ON p.id = r.master_person_id WHERE r.id = ?",
            (role_id,)).fetchone()
        if not r:
            return None
        name = self.text(r[2])
        return {"id": role_id, "label": r[0], "person_label": r[1], "name": name,
                "name_en": english_name(r[1], name), "rarity": r[3]}

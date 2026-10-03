"""CLI: python -m soa_save {dump,set,load} ...

  dump FILE [--json]                 print decrypted entries
  set  FILE KEY VALUE [--type T] [-o OUT]
                                     T is u32/u8/str/hex; defaults to the existing entry's type.
                                     Without -o, FILE is edited in place and FILE.bak is kept.
  load JSON OUT                      rebuild an XML from `dump --json` output
  roster FILE                        list the Game.xml party roster with names from the master DB
  unlock-all FILE -o OUT [--player-id ID]
                                     add every playable character variant (top rarity) to the roster;
                                     --player-id replaces BAS:PlayerID (default: keep the original)
"""
import argparse
import json
import shutil
import sys

from .kvs import KVSFile, describe


def encode(t, v):
    if t == "u32":
        return int(v, 0).to_bytes(4, "little") if isinstance(v, str) else int(v).to_bytes(4, "little")
    if t == "u8":
        return bytes([int(v, 0) if isinstance(v, str) else int(v)])
    if t == "str":
        return v.encode("utf-8") + b"\0"
    if t == "hex":
        return bytes.fromhex(v)
    raise ValueError(t)


def main(argv=None):
    p = argparse.ArgumentParser(prog="soa_save")
    sub = p.add_subparsers(dest="cmd", required=True)
    d = sub.add_parser("dump"); d.add_argument("file"); d.add_argument("--json", action="store_true")
    s = sub.add_parser("set"); s.add_argument("file"); s.add_argument("key"); s.add_argument("value")
    s.add_argument("--type", choices=["u32", "u8", "str", "hex"]); s.add_argument("-o", "--out")
    ld = sub.add_parser("load"); ld.add_argument("json"); ld.add_argument("out")
    r = sub.add_parser("roster"); r.add_argument("file")
    u = sub.add_parser("unlock-all"); u.add_argument("file"); u.add_argument("-o", "--out", required=True)
    u.add_argument("--player-id", help="replacement BAS:PlayerID, e.g. AAAAAAAAAA")
    a = p.parse_args(argv)

    if a.cmd == "dump":
        k = KVSFile.load(a.file)
        rows = [(n, *describe(v)) for n, v in k.entries.items()]
        if a.json:
            json.dump([{"key": n, "type": t, "value": v} for n, t, v in rows], sys.stdout, indent=1, ensure_ascii=False)
            print()
        else:
            for n, t, v in rows:
                print(f"{n:48s} {t:4s} {v}")
    elif a.cmd == "set":
        k = KVSFile.load(a.file)
        t = a.type or (describe(k.entries[a.key])[0] if a.key in k.entries else None)
        if t is None:
            p.error(f"new key {a.key!r}: pass --type")
        k.entries[a.key] = encode(t, a.value)
        out = a.out or a.file
        if not a.out:
            shutil.copy2(a.file, a.file + ".bak")
        k.save(out)
        print(f"{a.key} = {describe(k.entries[a.key])[1]} -> {out}")
    elif a.cmd == "load":
        k = KVSFile({r["key"]: encode(r["type"], r["value"]) for r in json.load(open(a.json, encoding="utf-8"))})
        k.save(a.out)
    elif a.cmd == "unlock-all":
        from .roster import unlock_all
        k = KVSFile.load(a.file)
        before = k.get_u32("person_size")
        added = unlock_all(k)
        if a.player_id:
            k.set_str("BAS:PlayerID", a.player_id)
        k.save(a.out)
        print(f"roster {before} -> {k.get_u32('person_size')} (+{len(added)}) -> {a.out}")
    elif a.cmd == "roster":
        from .master import Master
        m, k = Master(), KVSFile.load(a.file)
        home = k.get_u32("player_home_pc_roleid") if "player_home_pc_roleid" in k.entries else None
        for i in range(k.get_u32("person_size")):
            rid = k.get_u32(f"person_master_role_id_{i}")
            info = m.role(rid) or {"label": "?", "name": "?", "name_en": None, "rarity": "?"}
            mark = " (home)" if rid == home else ""
            en = info["name_en"] or "?"
            print(f"{i:3d}  {rid:10d}  {info['label']:28s} ★{info['rarity']}  {en:22s} {info['name']}{mark}")


if __name__ == "__main__":
    main()

#!/usr/bin/env -S sh -c 'exec "${0%/*}/../py" "$0" "$@"'
"""A character's animation set, from the 3.7.0 master data and parameter files, as the JSON
tools/asf2gltf (--set) reads: which .aaf files belong to the model, in which role (battle idle,
attacks, skills, home stand / talk motions, facial expressions, the character viewer's motions),
and the effects each battle motion triggers (docs/notes.md "Animation sets and effect triggers").

    .venv/bin/python tools/asf2gltf/anim_set.py ROLE [--data ZIP] [--master DB] [-o SET.json]

ROLE is a master_role id or id_label (role_cp0303_b04a_6131: Seaside Maria). The sources:
  - master_role -> master_person (asf, unique_apk, sex), master_weapon_kind (weapon_apk, the normal
    attacks short1/2, long1/2), master_role's skills 1-4 and rush skill 1 (master_skill.motion_name,
    .no), viewer_motion;
  - the battle motions: Motion/<Female|Male><weapon_apk>.apk (one package: idle, run, attacks, guard,
    damage, down, magic, win), a skill's Motion/<weapon_apk>_<motion_name><f|m>.apk;
  - the home: Parameter/Home3D/home3d_<person>.msgp (motion_filename -> Motion/home_<name>.apk, its
    facial_filename an expression in Motion/home_<cpNNNN>.apk, its facial_effect_filename an effect);
  - the effect triggers: Parameter/Battle/signal_<weapon>.msgp rows signal_<weapon><motion>_ATTACK_<n>
    (frameN / signalN: at frame N the signal takes value N) joined with
    Parameter/Battle/attack_<weapon>_action.msgp rows (attack_id = master_skill.no, signal_id = the
    value): effect_body_id_label / effect_bullet_id_label (Effect/<id>), link_node_name (the node it
    is attached to), launch offsets. The other signal kinds (AIM, SEDIV*, FOOT*, MOVE, ...) are
    listed as they are.
Reads the download in place (soa_save.adld / slz for the ADLD and SLZ layers, msgpack).
"""
import argparse
import json
import os
import re
import sqlite3
import struct
import sys
import zipfile

import msgpack

REPO = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
sys.path.insert(0, REPO)
from soa_save import adld, slz  # noqa: E402


class Data:
    def __init__(self, path):
        self.z = zipfile.ZipFile(path)
        self.names = set(self.z.namelist())

    def has(self, name):
        return name in self.names

    def read(self, name):
        d = adld.decode(self.z.read(name), name)
        return slz.decode(d) if slz.is_slz(d) else d

    def msgp(self, name):
        return msgpack.unpackb(self.read(name), raw=False, strict_map_key=False)

    def members(self, name):
        """The member names of a motion package ("\\0ISF")."""
        d = self.read(name)
        if d[:4] != b"\0ISF":
            return []
        n = struct.unpack_from("<I", d, 8)[0]
        out = []
        for i in range(n):
            no = struct.unpack_from("<I", d, 0x10 + i * 16)[0]
            out.append(d[no:d.index(b"\0", no)].decode())
        return out


def row(db, sql, *args):
    db.row_factory = sqlite3.Row
    r = db.execute(sql, args).fetchone()
    return dict(r) if r else None


def effect_triggers(data, weapon, motion, attack_id):
    """The effects motion `motion` fires for the skill whose master_skill.no is attack_id, and its
    other signals."""
    sig_file = f"Parameter/Battle/signal_{weapon}.msgp"
    act_file = f"Parameter/Battle/attack_{weapon}_action.msgp"
    signals, effects = [], []
    if not data.has(sig_file):
        return signals, effects
    rows = data.msgp(sig_file).get("master_signal", {}).get(f"signal_{weapon}", [])
    prefix = f"signal_{weapon}{motion}_"
    attack_frames = {}  # signal value -> frames it is set at
    for r in rows:
        if not r["id_label"].startswith(prefix):
            continue
        kind = r["id_label"][len(prefix):]
        kind = re.sub(r"_\d+$", "", kind)
        keys = []
        k = 1
        while f"frame{k}" in r:
            keys.append({"frame": r[f"frame{k}"], "value": r.get(f"signal{k}", 0)})
            k += 1
        signals.append({"kind": kind, "start_frame": r.get("start_frame", 0), "keys": keys})
        if kind == "ATTACK":
            for kv in keys:
                attack_frames.setdefault(kv["value"], []).append(kv["frame"])
    if attack_id is None or not data.has(act_file):
        return signals, effects
    acts = data.msgp(act_file).get("master_attack_action", None)
    if acts is None:  # (one table, whatever its key)
        tables = list(data.msgp(act_file).values())[0]
        acts = list(tables.values())[0] if isinstance(tables, dict) else tables
    elif isinstance(acts, dict):
        acts = list(acts.values())[0]
    for a in acts:
        if a.get("attack_id") != attack_id:
            continue
        sid = a.get("signal_id")
        for kind in ("effect_body_id_label", "effect_bullet_id_label", "effect_hit_id_label"):
            if a.get(kind):
                e = {"effect": a[kind], "kind": kind.split("_")[1], "signal": sid, "frames": attack_frames.get(sid, []),
                     "node": (a.get("link_node_name") or "").replace("R:", ""), "action": a["id_label"]}
                off = {k: a[k] for k in ("launch_offset_x", "launch_offset_y", "launch_offset_z") if k in a}
                if off:
                    e["offset"] = off
                effects.append(e)
    return signals, effects


def build(data, db, ref):
    role = row(db, "select * from master_role where id = ? or id_label = ?", int(ref) if ref.isdigit() else -1, ref)
    if not role:
        raise SystemExit(f"anim_set: no master_role {ref}")
    person = row(db, "select * from master_person where id = ?", role["master_person_id"])
    weapon = row(db, "select * from master_weapon_kind where id = ?", role["master_weapon_kind_id"])
    female = person.get("sex") == 2
    cp = person["id_label"].split("_")[0]
    out = {"role": role["id_label"], "person": person["id_label"],
           "model": f"Character/etc2/hi/{person['asf']}.asf", "animations": []}

    def add(source, name, role_name, extras=None):
        pkg = source.split(":")[0]
        if not data.has(pkg):
            out.setdefault("missing", []).append(source)
            return
        if ":" in source and source.split(":", 1)[1] not in data.members(pkg):
            out.setdefault("missing", []).append(source)
            return
        e = {"source": source, "name": name, "role": role_name}
        if extras:
            e["extras"] = extras
        out["animations"].append(e)

    # battle: the weapon package, its normal attacks, the skills
    wk = weapon["id_label"]
    base = f"Motion/{'Female' if female else 'Male'}{weapon['weapon_apk']}.apk"
    normal = {}
    for slot in ("short1", "short2", "long1", "long2"):
        sk = row(db, "select * from master_skill where id = ?", weapon.get(f"{slot}_skill_id"))
        if sk:
            normal[sk["motion_name"]] = sk
    if data.has(base):
        for m in data.members(base):
            if not m.endswith(".aaf"):
                continue
            motion = m[:-4]
            sk = normal.get(motion)
            sig, eff = effect_triggers(data, wk, motion, sk["no"] if sk else None)
            ex = {"set": "battle", "motion": motion}
            if sk:
                ex["skill"] = sk["id_label"]
            if sig:
                ex["signals"] = sig
            if eff:
                ex["effects"] = eff
            add(f"{base}:{m}", f"battle {motion}", f"battle/{motion}", ex)
    for col in ("master_skill1_id", "master_skill2_id", "master_skill3_id", "master_skill4_id", "rush_skill1_id"):
        sk = row(db, "select * from master_skill where id = ?", role.get(col))
        if not sk or not sk.get("motion_name"):
            continue
        motion = sk["motion_name"]
        pkg = f"Motion/{weapon['weapon_apk']}_{motion}{'f' if female else 'm'}.apk"
        sig, eff = effect_triggers(data, wk, motion, sk["no"])
        ex = {"set": "battle", "motion": motion, "skill": sk["id_label"], "rush": col.startswith("rush")}
        if sig:
            ex["signals"] = sig
        if eff:
            ex["effects"] = eff
        add(f"{pkg}:{motion}.aaf", f"skill {sk['id_label']} ({motion})", f"battle/skill/{sk['id_label']}", ex)
    # the character viewer's motions
    if role.get("viewer_motion"):
        pkg = f"Motion/{role['viewer_motion']}.apk"
        if data.has(pkg):
            for m in data.members(pkg):
                if m.endswith(".aaf"):
                    add(f"{pkg}:{m}", f"viewer {m[:-4]}", f"viewer/{m[:-4]}", {"set": "viewer"})
    # the home: stand, long stand, talk motions, facial expressions
    h3 = f"Parameter/Home3D/home3d_{person['id_label']}.msgp"
    faces = f"Motion/home_{cp}.apk"
    if data.has(h3):
        rows = data.msgp(h3).get("master_home3d", {}).get(f"home3d_{person['id_label']}", [])
        seen = set()
        for r in rows:
            mf = re.sub(r"_eye\d+$", "", r.get("motion_filename", ""))
            if not mf or mf in seen:
                continue
            seen.add(mf)
            pkg = f"Motion/home_{mf}.apk"
            if not data.has(pkg):
                out.setdefault("missing", []).append(pkg)
                continue
            kind = re.sub(r"^home3d_" + re.escape(person["id_label"]), "", r["id_label"])
            ex = {"set": "home", "home3d": r["id_label"]}
            for k in ("facial_filename", "facial_effect_filename", "voice_id", "text_id"):
                if r.get(k):
                    ex[k] = r[k]
            if r.get("facial_effect_filename"):
                ex["effects"] = [{"effect": r["facial_effect_filename"], "kind": "facial", "frames": [0], "node": ""}]
            for m in data.members(pkg):
                if m.endswith(".aaf"):
                    add(f"{pkg}:{m}", f"home {kind} ({m[:-4]})", f"home/{kind}", ex)
    if data.has(faces):
        for m in data.members(faces):
            if m.endswith(".aaf"):
                add(f"{faces}:{m}", f"face {m[:-4]}", f"home/face/{m[:-4]}", {"set": "home-face"})
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("role", help="a master_role id or id_label")
    ap.add_argument("--data", default=os.path.join(REPO, "work", "SOA-3.7.0-canonical-data.zip"))
    ap.add_argument("--master", default=os.path.join(REPO, "data", "basmaster-3.7.0.sqlite3"))
    ap.add_argument("-o", "--out", help="the JSON (default: stdout)")
    a = ap.parse_args()
    s = build(Data(a.data), sqlite3.connect(a.master), a.role)
    text = json.dumps(s, ensure_ascii=False, indent=1)
    if a.out:
        with open(a.out, "w") as f:
            f.write(text + "\n")
        print(f"{a.out}: {len(s['animations'])} animations ({s['person']})")
    else:
        print(text)


if __name__ == "__main__":
    main()

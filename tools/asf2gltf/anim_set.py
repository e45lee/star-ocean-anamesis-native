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
        # the row id is "<weapon><motion>_<KIND>_<attack id>" (CSignalChecker::CheckSignal @01428940 builds it with
        # "%s_%s_%d": the motion, the kind, the attack id: master_skill.no, 0 for a motion without an attack); a
        # motion shared by several skills has one set of rows per skill
        m = re.match(r"(.*)_(\d+)$", r["id_label"][len(prefix):])
        if not m or int(m.group(2)) != (attack_id or 0):
            continue
        kind = m.group(1)
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


# The sound a battle motion's SEDIV signals play (CCharacterObject::CheckSignal @01352500, one CSignalChecker per
# signal kind, 0x88 bytes apart, in the order of the kind table @02ab7f28: ATTACK, AIM, JUMP, STAY, FALL, MOVE,
# SIDEMOVE, CIRCLEMOVE, ARMOR, DIVIDE, MOVECOLOFF, ROTATEY, NOPUSHMOVE, FOOT0-5, SEDIV1-5, SEDIV7, SEDIV8, VISIBLE0-4,
# RCSPACE, FADE). A key's value is an SE queue number (CBattleUtility::CheckSeQue @013e80ac): +80000 a 2D sound
# (CArena::PlaySE), +50000 stop the loop, +20000 start a loop (StartSignalLoopSE), +10000 the sound follows the
# character; the rest r: r >= 9000 cue r - 9000 of BattleCommonSE; else, with the motion's attack, cue r % 1000 of
# the attack's SE package number r / 1000 (master_skill.se_sound_package, _1, _2, _3), and without one (or when that
# package has no such cue) the character's own SE package.
SE_KINDS = {
    "SEDIV2": "character",  # CheckSeQue(null, null, v): the character's SE package
    "SEDIV3": "foot",       # the foot SE package, cue = a ground-surface offset + v (or a running-smoke effect)
    "SEDIV4": "voice",      # CArena::PlayCharacterVoice: cue v of the character's voice package
    "SEDIV5": "attack",     # CheckSeQue(this, attack, v): the attack's SE packages
    "SEDIV7": "attack_voice",  # v == 1: CVoicePlayer::PlayVoice(attack id - 1) (attack ids < 7) or PlayExAttackVoice
    "SEDIV8": "move_loop",  # v != 0: PlayMoveLoopSE, 0: stop it
}


def sound_cues(signals, skill, person, weapon):
    out = []
    packs = [skill.get(k) for k in ("se_sound_package", "se_sound_package1", "se_sound_package2", "se_sound_package3")] if skill else []
    for sg in signals:
        what = SE_KINDS.get(sg["kind"])
        if not what:
            continue
        for kv in sg["keys"]:
            v = kv["value"]
            cue = {"frame": kv["frame"], "signal": sg["kind"], "value": v, "kind": what}
            if what in ("character", "attack"):
                mode, r = "play", v
                if r >= 80000:
                    mode, r = "play_2d", r - 80000
                if r >= 50000:
                    mode, r = "loop_stop", r - 50000
                if r >= 20000:
                    mode, r = "loop_start", r - 20000
                if r >= 10000:
                    cue["follow"] = True
                    r -= 10000
                cue["mode"] = mode
                if r >= 9000:
                    cue.update(package="BattleCommonSE", cue=r - 9000)
                elif what == "attack" and packs:
                    b = min(r // 1000, 3)
                    cue.update(package=packs[b], cue=r - 1000 * b)
                else:
                    # (d) the character's SE package (CCharacterObject+0x50e8): read as master_person.se_sound_package,
                    # else master_weapon_kind.se_sound_package; not traced to its setter
                    cue.update(package=person.get("se_sound_package") or weapon.get("se_sound_package"), cue=r)
            elif what == "voice":
                cue.update(package=person.get("voice_sound_package"), cue=v)
            elif what == "foot":
                cue.update(package=person.get("foot_sound_package"), cue=v)
            elif what == "attack_voice":
                if v != 1:
                    continue
                if skill and skill.get("no", 0) < 7:
                    cue.update(package=person.get("voice_sound_package"), voice="attack", index=skill["no"] - 1)
                elif skill:
                    cue.update(package=person.get("voice_sound_package"), voice="ex_attack", attack=skill["id_label"])
            out.append(cue)
    return out


HOME3D_RULES = {
    "pick": "GetRandomMotion @014830a0: weighted among the category's rows that are available, weight > 0 and level_low <= favor level <= level_upper (HighPrecisionRandom() % sum, cumulative)",
    "stay": "PlayStayMotionRandom @0147fb8c mode 0: a stay row looped, StartAnimation(motion, blend: the row's blend_frame, loop)",
    "stay_long": "Progress_HomeTalk @0147ccec: when the stay motion has terminated, a counter (HomeCharacter+0x1028) counts frames to 121, then MouthMotionStop and Random(2) == 1 plays a stay_long row (mode 1: blend 45, not looped, its facial anim as an overwrite layer, its facial effect after effect_delay_frame), else the count restarts; after a stay_long ends PlayStayMotionRandom(99): Random(2) picks stay or stay_long again",
    "tap": "TapReactionMotionRandom @01484a18: weighted among the talk and reaction rows (motion not empty, available, weight > 0, favor level in range), never the row played last unless it is the only one; text_id to the speech box (CHome::PlayTalk @01aef4e8), voice_id to PlayVoice @01487ae8",
    "blink": "Progress_HomeTalk: a timer (HomeCharacter+0x102c, frames) runs while the eyes are enabled (a row with no_blink 0 sets it to 0, no_blink 1 stops it: EyeMotionStop); when it exceeds the current blink clip's length, Random(2) == 0 plays the eye row's clip (EyeMotion @0148151c, an additive layer) and resets the timer, else the eye2 row's clip (the timer is not reset there); without eye rows the clips are Motion/home_eye_blink_01 / _02",
    "mouth": "Progress_HomeTalk: while a voice plays and the row allows lip sync (no_lipsync 0, not_lipsync_voice 0) a timer (HomeCharacter+0x1034) restarts the mouth clip (MouthMotion @014816f4, an additive layer) each time it exceeds the clip's length; when the voice stops, MouthMotionStop",
    "facial": "the row's facial_filename plays as an overwrite layer over the body motion (StartOverwriteAnimation); facial_effect_filename is the blush / mood effect (BlushEffectStart @0148362c) after effect_delay_frame",
    "levels": "a row's favor gate: level_low (default 0) .. level_upper (default 9999); dated rows: opened_at <= now and not closed_at < now (CHomeUtility::GetHomeParameter @014af0ec)",
}


def as_number(v):
    """A master value stored as text ("8.5") as a number; None stays None."""
    try:
        return None if v is None or v == "" else float(v)
    except (TypeError, ValueError):
        return v


def home_text(db, db_gl, en_tsv, message_id):
    """The JP line and an English one: Global's official text, else the repository's machine translation."""
    if not message_id:
        return {}
    out = {}
    r = db.execute("select text_value from master_text where message_id = ? and lang = 'ja'", (message_id,)).fetchone()
    if r:
        out["text_ja"] = r[0].replace("\\n", "\n")
    if db_gl is not None:
        r = db_gl.execute("select text_value from master_text where message_id = ? and lang = 'en'", (message_id,)).fetchone()
        if r:
            out["text_en"] = r[0].replace("\\n", "\n")
            out["text_en_source"] = "Global (official)"
            return out
    if message_id in en_tsv:
        out["text_en"] = en_tsv[message_id].replace("\\n", "\n")
        out["text_en_source"] = "machine translation (data/english/master-en.tsv)"
    return out


def home3d_table(data, db, db_gl, en_tsv, person, rows, anim_name, h3_file):
    """The character's Home3D rows (docs/home3d.md, docs/notes.md "glTF export": extras.soa_home3d)."""
    out_rows = []
    for r in rows:
        label = r["id_label"]
        suffix = label[len("home3d_" + person["home3d_file"]):] if label.startswith("home3d_" + (person.get("home3d_file") or "")) else label
        m = re.match(r"([a-z_]+?)(\d*)$", suffix)
        cat, num = (m.group(1), m.group(2)) if m else (suffix, "")
        setting = row(db, "select * from master_home3d_motion_setting where id_label = ?", r.get("motion_filename", "")) if r.get("motion_filename") else None
        motion_file = setting["motion_filename"] if setting else None
        e = {"id": r.get("id"), "id_label": label, "category": cat, "number": num,
             "motion_filename": r.get("motion_filename"),
             "motion": anim_name.get(f"Motion/home_{motion_file}.apk") if motion_file else None,
             "motion_setting": {k: setting[k] for k in ("id_label", "motion_filename", "no_skip", "no_blink", "no_lipsync", "blend_frame", "skip_enable_frame")} if setting else None,
             "facial_filename": r.get("facial_filename"),
             "facial": anim_name.get(f"face:{r['facial_filename']}") if r.get("facial_filename") else None,
             "facial_effect_filename": r.get("facial_effect_filename"),
             "effect_delay_frame": r.get("effect_delay_frame", 0),
             "weight": r.get("weight", 0),
             "level_low": r.get("level_low", 0), "level_upper": r.get("level_upper", 9999),
             "scenario_id_low": r.get("scenario_id_low"), "scenario_id_upper": r.get("scenario_id_upper"),
             "opened_at": r.get("opened_at"), "closed_at": r.get("closed_at"),
             # master_home3d_motion_setting overrides no_skip / no_blink / no_lipsync / blend_frame (docs/home3d.md);
             # blend_frame 45 when unset (CMasterHome3DElement::Initialize @01288a84)
             "no_skip": (setting or {}).get("no_skip", r.get("no_skip", 0)) or 0,
             "no_blink": (setting or {}).get("no_blink", r.get("no_blink", 0)) or 0,
             "no_lipsync": (setting or {}).get("no_lipsync", r.get("no_lipsync", 0)) or 0,
             "blend_frame": (setting or {}).get("blend_frame") or r.get("blend_frame") or 45,
             "text_id": r.get("text_id"), "voice_id": r.get("voice_id"),
             "not_lipsync_voice": r.get("not_lipsync_voice", 0), "voice_delay_frame": r.get("voice_delay_frame", 0)}
        if not motion_file and r.get("motion_filename"):
            e["note"] = "no master_home3d_motion_setting row: the game skips this motion (CHomeModelViewManager)"
        e.update(home_text(db, db_gl, en_tsv, r.get("text_id")))
        out_rows.append({k: v for k, v in e.items() if v is not None})
    cats = {x["category"] for x in out_rows}
    cp = person["id_label"].split("_")[0]
    clips = {
        # no available eye / eye2 row: the shared blink clips; no mouth row: the per-character package's mouth
        # (docs/home3d.md "What the 3D home loads")
        "eye": anim_name.get("Motion/home_eye_blink_01.apk") if "eye" not in cats else "the eye row's motion",
        "eye2": anim_name.get("Motion/home_eye_blink_02.apk") if "eye2" not in cats else "the eye2 row's motion",
        "mouth": anim_name.get("face:mouth") if "mouth" not in cats else "the mouth row's motion",
        "correction": anim_name.get("face:correction"),
        "t_stance": anim_name.get("Motion/home_t_stance.apk"),
    }
    return {"schema": "soa_home3d/1", "source": h3_file, "person": person["id_label"],
            "home_voice_package": person.get("home_voice_sound_package"),
            "faces_package": f"Motion/home_{cp}.apk",
            "camera": {"height_offset": as_number(person.get("home3d_camera_height_offset")),
                       "depth_offset": as_number(person.get("home3d_camera_depth_offset"))},
            "clips": clips, "rules": HOME3D_RULES, "rows": out_rows}


def build(data, db, ref, db_gl=None, en_tsv=None):
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
                snd = sound_cues(sig, sk, person, weapon)
                if snd:
                    ex["sounds"] = snd
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
            snd = sound_cues(sig, sk, person, weapon)
            if snd:
                ex["sounds"] = snd
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
    # the home (docs/home3d.md): the Home3D rows' motions, the facial expressions and the mouth / correction clips
    # of the per-character package, the shared blink clips and the T-pose
    h3 = f"Parameter/Home3D/home3d_{person.get('home3d_file') or person['id_label']}.msgp"
    if not data.has(h3):  # FindHomeParameterName @014ae474: the common file by sex (1 = male)
        h3 = f"Parameter/Home3D/home3d_{'male' if person.get('sex') == 1 else 'female'}_common.msgp"
    faces = f"Motion/home_{cp}.apk"
    anim_name = {}
    rows = []
    if data.has(h3):
        tables = data.msgp(h3).get("master_home3d", {})
        rows = next(iter(tables.values()), []) if tables else []
        for r in rows:
            if not r.get("motion_filename"):
                continue
            setting = row(db, "select * from master_home3d_motion_setting where id_label = ?", r["motion_filename"])
            if not setting:  # the game skips a motion without a setting row
                continue
            mf = setting["motion_filename"]
            pkg = f"Motion/home_{mf}.apk"
            if pkg in anim_name:
                continue
            if not data.has(pkg):
                out.setdefault("missing", []).append(pkg)
                continue
            kind = r["id_label"][len("home3d_" + (person.get("home3d_file") or "")):]
            ex = {"set": "home", "home3d": r["id_label"]}
            for k in ("facial_filename", "facial_effect_filename", "voice_id", "text_id"):
                if r.get(k):
                    ex[k] = r[k]
            if r.get("facial_effect_filename"):
                ex["effects"] = [{"effect": r["facial_effect_filename"], "kind": "facial",
                                  "frames": [r.get("effect_delay_frame", 0)], "node": ""}]
            for m in data.members(pkg):
                if m.endswith(".aaf"):
                    name = f"home {kind} ({m[:-4]})"
                    anim_name[pkg] = name
                    add(f"{pkg}:{m}", name, f"home/{kind}", ex)
    if data.has(faces):
        for m in data.members(faces):
            if m.endswith(".aaf"):
                anim_name[f"face:{m[:-4]}"] = f"face {m[:-4]}"
                add(f"{faces}:{m}", f"face {m[:-4]}", f"home/face/{m[:-4]}", {"set": "home-face"})
    for pkg, role_name in (("Motion/home_eye_blink_01.apk", "home/eye/blink_01"), ("Motion/home_eye_blink_02.apk", "home/eye/blink_02"),
                           ("Motion/home_t_stance.apk", "home/t_stance")):
        if data.has(pkg):
            for m in data.members(pkg):
                if m.endswith(".aaf"):
                    name = f"{'face' if 'eye' in pkg else 'home'} {m[:-4]}"
                    anim_name[pkg] = name
                    add(f"{pkg}:{m}", name, role_name, {"set": "home-face" if "eye" in pkg else "home"})
    if rows:
        out["home3d"] = home3d_table(data, db, db_gl, en_tsv or {}, person, rows, anim_name, h3)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("role", help="a master_role id or id_label")
    ap.add_argument("--data", default=os.path.join(REPO, "work", "SOA-3.7.0-canonical-data.zip"))
    ap.add_argument("--master", default=os.path.join(REPO, "data", "basmaster-3.7.0.sqlite3"))
    ap.add_argument("-o", "--out", help="the JSON (default: stdout)")
    a = ap.parse_args()
    gl = os.path.join(REPO, "data", "basmaster-gl.sqlite3")
    en = {}
    tsv = os.path.join(REPO, "data", "english", "master-en.tsv")
    if os.path.exists(tsv):
        with open(tsv, encoding="utf-8") as f:
            for line in f:
                c = line.rstrip("\n").split("\t")
                if len(c) >= 3 and "hmmsg" in c[0]:
                    en[c[0]] = c[2]
    s = build(Data(a.data), sqlite3.connect(a.master), a.role,
              sqlite3.connect(gl) if os.path.exists(gl) else None, en)
    text = json.dumps(s, ensure_ascii=False, indent=1)
    if a.out:
        with open(a.out, "w") as f:
            f.write(text + "\n")
        print(f"{a.out}: {len(s['animations'])} animations ({s['person']})")
    else:
        print(text)


if __name__ == "__main__":
    main()

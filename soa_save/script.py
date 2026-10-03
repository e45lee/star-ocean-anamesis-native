"""Decode the event scripts (Script/*.msgp) and their dialogue text (Scenario/TS_*.msgp).

Both ship in the install-time asset pack (assetinstalltime.apk: assets/assetpack/...) as ADLD
containers with flags=1: the payload is XORed with the ASCII hex of CHash32(name), where
`name` is the path relative to assetpack/, e.g. "Script/1000_010.msgp" (the format strings
"Script/%s.msgp" and "Scenario/%s.msgp" are in EventScenario::CEventScenario::SetEventId).
The plaintext is MessagePack:

  Script/<id>.msgp:      {"Script": {<id>: [{"id", "command_type", "command_param0".."8"}, ...]}}
  Scenario/TS_<n>.msgp:  {"master_text": [{"message_id", "text_value", "lang", ...}, ...]}

command_type indexes EventScenario::CEventScenario::CalcCommand_Table (see COMMANDS).
Dialogue commands reference text by message_id ("1000_010_01"); speakers and characters are
referenced by model code ("cp0003_ta01a" -> cp0003 = Coro); listings name them from the master DB's
master_text (one row per full model code, as the game's nameplate) and names_en.json.

CLI: python -m soa_save.script {extract,decrypt,encrypt,json,list} ...

  extract [-o DIR] [--xapk X] [--format raw,json,txt]
                        decode every Script/ and Scenario/ file straight from the XAPK
  decrypt FILE... [-o OUT] [--name N]
                        strip the ADLD layer from any asset (writes raw .msgp; one file with -o
                        FILE, several with -o DIR, default FILE.dec)
  encrypt FILE --name N -o OUT
                        wrap plaintext back into an ADLD flags=1 container (for modding)
  json FILE             print a script/scenario file as JSON
  list FILE... [--text SRC]
                        readable listing with command names and inline dialogue; SRC is a
                        Scenario directory or the XAPK (default: a sibling Scenario/ directory,
                        else the XAPK)

--name is only needed when a file isn't under an assetpack/ or builtin_data/ directory and
isn't named like Script/x.msgp or Scenario/x.msgp.
"""
import argparse
import io
import json
import pathlib
import struct
import sys
import zipfile

import msgpack

from .adld import chash32, decode
from .master import CACHE, NAMES_EN, Master
from .paths import REPO
from .paths import xapk

PACK_APK = "assetinstalltime.apk"
PACK_PREFIX = "assets/assetpack/"
DIRS = ("Script", "Scenario")

# EventScenario::CEventScenario::CalcCommand_Table (vaddr 0x2bc7690), CalcCommand_<name>.
COMMANDS = [
    "None", "EventExit", "MessageShow", "MessageHide", "CharacterShow", "CharacterHide",
    "MessageSpeedChange", "BgShow", "BgHide", "WaitTime", "WaitInput", "TelopShow", "TelopHide",
    "SpriteShow", "SpriteHide", "FilterShow", "FilterHide", "ShakeStart", "ShakeEnd", "BgmPlay",
    "BgmStop", "SePlay", "SeStop", "MessageChange", "Label", "Jump", "CharacterShakeStart",
    "CharacterShakeEnd", "MessageColorChange", "TelopChange", "SelectMenu", "CharacterManpuShow",
    "CharacterManpuHide", "CharacterAnimationStart", "CharacterAnimationStop", "BgAnimationStart",
    "BgAnimationStop", "SpriteAnimationStart", "SpriteAnimationStop", "AnimationStart",
    "AnimationStop", "Flag", "IfJump", "CharacterHidePosition", "None", "MessageClear",
    "CharacterLayoutChangeSingle", "CharacterLayoutChangeAdd", "ParticlePlay", "ParticleStop",
    "MessageAppend", "VoicePlay", "VoiceStop", "SelectMenu_ErrorSE", "SeChangeVolume",
    "OffscreenFilterShow", "OffscreenFilterHide", "SkinChange", "MessageNameColorChange",
    "BacklogChange", "BacklogAppend", "InsertBlank", "StageDirectionsInvisible",
    "StageDirectionsAppear", "MessageDelete", "PlayMovie", "StageDirectionsCharacterShow",
    "StageDirectionsCharacterHide", "SpriteShowNew", "SpriteHideNew", "SpriteAnimationStartNew",
    "SpriteAnimationStopNew", "StageDirectionsMessageFlush", "MovieFilterHide",
    "SetEnableSkipButton", "SetEnableBackLogButton", "SetEnableAutoButton",
    "SetEnableFastForwardButton",
]
# Commands whose param0 is a message_id spoken by the character in param1.
SPEECH = {"MessageChange", "MessageAppend", "BacklogChange", "BacklogAppend"}
# Commands whose params are (message_id, jump label) pairs.
MENUS = {"SelectMenu", "SelectMenu_ErrorSE"}


def command_name(t):
    return COMMANDS[t] if 0 <= t < len(COMMANDS) else f"Unknown{t}"


def asset_name(path):
    """The CHash32 key name for an asset path: the part after assetpack/ or builtin_data/."""
    parts = pathlib.PurePath(path).parts
    for root in ("assetpack", "builtin_data"):
        if root in parts:
            i = len(parts) - 1 - parts[::-1].index(root)
            return "/".join(parts[i + 1:])
    if len(parts) >= 2 and parts[-2] in DIRS:
        return "/".join(parts[-2:])
    raise ValueError(f"can't derive the asset name of {path}; pass --name (e.g. Script/1000_010.msgp)")


def encrypt(plain: bytes, name: str) -> bytes:
    """Inverse of adld.decode for flags=1 (the flavour every Script/Scenario file uses)."""
    k = b"%x" % chash32(name.encode())
    return b"ADLD" + struct.pack("<I", 1) + bytes(8) + bytes(b ^ k[i % len(k)] for i, b in enumerate(plain))


def load(data: bytes, name: str):
    """Decode an ADLD (or already-decrypted) MessagePack asset."""
    return msgpack.unpackb(decode(data, name), raw=False, strict_map_key=False)


def pack_files(xapk_path=None):
    """Yield (name, encrypted bytes) for every Script/ and Scenario/ file in the install-time pack."""
    with zipfile.ZipFile(xapk_path or xapk()) as x:
        with zipfile.ZipFile(io.BytesIO(x.read(PACK_APK))) as pack:
            for n in sorted(pack.namelist()):
                name = n[len(PACK_PREFIX):]
                if n.startswith(PACK_PREFIX) and name.split("/")[0] in DIRS and not n.endswith("/"):
                    yield name, pack.read(n)


def texts_from(items):
    """message_id -> text from (name, bytes) Scenario files."""
    out = {}
    for name, data in items:
        for row in load(data, name).get("master_text", []):
            out[row["message_id"]] = row["text_value"]
    return out


def load_texts(src=None, near=None):
    """Dialogue text from a Scenario directory or an XAPK. With neither, use a Scenario/ directory
    next to `near` if there is one, else the repository's XAPK."""
    if src is None and near is not None:
        sib = pathlib.Path(near).resolve().parent.parent / "Scenario"
        if sib.is_dir():
            src = sib
    if src is not None and pathlib.Path(src).is_dir():
        return texts_from((f"Scenario/{p.name}", p.read_bytes()) for p in sorted(pathlib.Path(src).glob("*.msgp")))
    return texts_from((n, d) for n, d in pack_files(src) if n.startswith("Scenario/"))


# Master DBs that name speakers, in order: this build's, then 3.7.0's (it keeps event NPCs that
# 3.8.0 dropped). master_text has one row per full model code (message_id "cp0006_ta01a").
SPEAKER_DBS = (CACHE, REPO / "data/basmaster-3.7.0.sqlite3")
_speaker_dbs = None


def _db_name(code):
    global _speaker_dbs
    if _speaker_dbs is None:
        _speaker_dbs = []
        for path in SPEAKER_DBS:
            try:
                if path.exists():
                    _speaker_dbs.append(Master(path))
            except Exception:  # a missing or unreadable DB just means fewer names
                pass
    # The exact code, then its base variant: "cp0006_ta01b" (an outfit/expression variant without
    # its own row) is named like "cp0006_ta01a".
    for c in (code, code[:-1] + "a") if code[-1:].isalpha() else (code,):
        for m in _speaker_dbs:
            name = m.text(c)
            if name:
                return name
    return None


def speaker(code):
    """'cp0013_ta01a' -> 'cp0013_ta01a ユーイン/Yrian'; 'cp0024_ta01a' -> 'cp0024_ta01a ケビン'.

    The Japanese name is the game's own nameplate (master_text by the full model code), else
    names_en.json by the code's prefix. The English name comes from names_en.json and is added
    when its Japanese name is the same character.
    """
    if not isinstance(code, str) or not code:
        return None
    ch = NAMES_EN["characters"].get(code.split("_")[0])
    ja = _db_name(code) or (ch[0] if ch else None)
    if not ja:
        return code
    return f"{code} {ja}/{ch[1]}" if ch and ch[0] == ja else f"{code} {ja}"


def _params(cmd):
    return {int(k[len("command_param"):]): v for k, v in cmd.items() if k.startswith("command_param")}


def _text(texts, mid):
    t = texts.get(mid) if isinstance(mid, str) else None
    return t if t is not None else f"<{mid}: text not in this build>"


def listing(obj, texts=None):
    """Render a decoded Script file as readable text."""
    texts = texts or {}
    out = []
    for sid, cmds in obj["Script"].items():
        out.append(f"# Script {sid} ({len(cmds)} commands)")
        for c in cmds:
            name = command_name(c["command_type"])
            p = _params(c)
            head = f"{c['id']:5d}  "
            if name == "Label":
                out.append(f"{head}{p.get(0)}:")
            elif name in SPEECH:
                who = speaker(p.pop(1, None))
                mid = p.pop(0, None)
                rest = " ".join(f"p{k}={v!r}" for k, v in sorted(p.items()))
                out.append(f"{head}{name:<28s}{mid}" + (f"  [{who}]" if who else "") + (f"  {rest}" if rest else ""))
                out.extend("       | " + line for line in _text(texts, mid).split("\n"))
            elif name in MENUS:
                out.append(f"{head}{name}" + (f"  p8={p[8]!r}" if 8 in p else ""))
                for k in range(0, 8, 2):
                    if k in p:
                        text = _text(texts, p[k]).replace("\n", " ")
                        out.append(f"       > {text}  -> {p.get(k + 1)}  ({p[k]})")
            else:
                args = " ".join(f"p{k}={v!r}" for k, v in sorted(p.items()))
                out.append(f"{head}{name:<28s}{args}".rstrip())
    return "\n".join(out) + "\n"


def _dump_json(obj):
    return json.dumps(obj, ensure_ascii=False, indent=1) + "\n"


def extract(out_dir, xapk_path=None, formats=("json", "txt")):
    out_dir = pathlib.Path(out_dir)
    files = list(pack_files(xapk_path))
    texts = texts_from((n, d) for n, d in files if n.startswith("Scenario/"))
    for name, data in files:
        stem = out_dir / pathlib.PurePosixPath(name).with_suffix("")
        stem.parent.mkdir(parents=True, exist_ok=True)
        if "raw" in formats:
            stem.with_suffix(".msgp").write_bytes(decode(data, name))
        obj = load(data, name)
        if "json" in formats:
            stem.with_suffix(".json").write_text(_dump_json(obj), encoding="utf-8")
        if "txt" in formats and "Script" in obj:
            stem.with_suffix(".txt").write_text(listing(obj, texts), encoding="utf-8")
    return len(files)


def main(argv=None):
    p = argparse.ArgumentParser(prog="python -m soa_save.script", description=__doc__.split("\n")[0])
    sub = p.add_subparsers(dest="cmd", required=True)
    e = sub.add_parser("extract", help="decode every script/scenario file from the XAPK")
    e.add_argument("-o", "--out", default="work/scripts")
    e.add_argument("--xapk")
    e.add_argument("--format", default="json,txt", help="comma list of raw,json,txt")
    d = sub.add_parser("decrypt", help="strip the ADLD layer")
    d.add_argument("files", nargs="+"); d.add_argument("-o", "--out"); d.add_argument("--name")
    n = sub.add_parser("encrypt", help="re-wrap plaintext as ADLD")
    n.add_argument("file"); n.add_argument("--name", required=True); n.add_argument("-o", "--out", required=True)
    j = sub.add_parser("json", help="print a file as JSON")
    j.add_argument("file"); j.add_argument("--name")
    li = sub.add_parser("list", help="readable script listing")
    li.add_argument("files", nargs="+"); li.add_argument("--text", help="Scenario directory or XAPK")
    li.add_argument("--name")
    a = p.parse_args(argv)

    if a.cmd == "extract":
        formats = set(a.format.split(","))
        if formats - {"raw", "json", "txt"}:
            p.error(f"unknown --format {a.format}")
        count = extract(a.out, a.xapk, formats)
        print(f"{count} files -> {a.out}", file=sys.stderr)
    elif a.cmd == "decrypt":
        if len(a.files) > 1 and a.name:
            p.error("--name applies to a single file")
        out = pathlib.Path(a.out) if a.out else None
        to_dir = out is not None and (len(a.files) > 1 or out.is_dir() or a.out.endswith("/"))
        for f in a.files:
            raw = decode(pathlib.Path(f).read_bytes(), a.name or asset_name(f))
            if out is None:
                dst = pathlib.Path(f + ".dec")
            else:
                dst = out / pathlib.Path(f).name if to_dir else out
            dst.parent.mkdir(parents=True, exist_ok=True)
            dst.write_bytes(raw)
    elif a.cmd == "encrypt":
        pathlib.Path(a.out).write_bytes(encrypt(pathlib.Path(a.file).read_bytes(), a.name))
    elif a.cmd == "json":
        sys.stdout.write(_dump_json(load(pathlib.Path(a.file).read_bytes(), a.name or asset_name(a.file))))
    elif a.cmd == "list":
        if len(a.files) > 1 and a.name:
            p.error("--name applies to a single file")
        texts = load_texts(a.text, near=a.files[0])
        for f in a.files:
            obj = load(pathlib.Path(f).read_bytes(), a.name or asset_name(f))
            if "Script" not in obj:
                p.error(f"{f} is not a Script file")
            sys.stdout.write(listing(obj, texts))


if __name__ == "__main__":
    main()

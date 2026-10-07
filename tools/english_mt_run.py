#!/usr/bin/env python3
"""Machine-translation batches for the English mode (docs/PLAN-english.md M2/M3/M4; the engine
decision of 2026-10-07: Gemma 4 31B-it QAT UD-Q4_K_XL, prompt v2, llama.cpp CUDA).

The engine runs locally: this script starts llama.cpp's `llama-server` from work/tools/ with the
model from work/tools/mt-models/ (both local only, never in git), sends one request per item and
appends each answer to a checkpoint (JSON lines in work/english/mt/). A batch is resumable: items
already in the checkpoint are skipped, so a stopped run continues where it ended. Inputs are
deterministic (the committed master DBs, the download's Scenario files, the glossary, this file's
prompt with its version), and every row records the model, quantization, prompt version,
llama.cpp build, temperature and slot count. With several parallel slots llama.cpp's batched
arithmetic is not bit-reproducible (docs/english.md 7.8): the checkpoint, not a re-run, is the
record. Nothing here is called by the server or the gates; `tools/english_text.py import-mt`
turns a checkpoint into `machine` rows of data/english/.

The GPU is shared with game clients, which starve beside the model (gates time out): the batch
starts only when at least --min-free MiB are free AND no game client holds a slot of the pool
(control/soaslot.py status); while running, a client in the pool (or free VRAM under --low-free
MiB on two checks in a row) stops the server, and the batch waits for both conditions again, then
restarts it (other programs win; --share-gpu ignores the pool).

Usage:
  tools/english_mt_run.py names [--model 31b|26b]   # M2: katakana terms of the gap -> name list
  tools/english_mt_run.py ui    [--model 31b|26b]   # M3: the master's gap texts
  tools/english_mt_run.py story [--model 31b|26b]   # M4: the story's untranslated lines, by scene
  tools/english_mt_run.py story-fix                  # the story lines still without English, one
                                                     # per request with context (story-fix.jsonl)
  tools/english_mt_run.py shorten                    # E7: machine story lines over four window lines,
                                                     # rewritten shorter (story-short.jsonl)
  tools/english_mt_run.py status                     # rows done per checkpoint
Options: --slots N (4), --port P (18431), --limit N (stop after N new items), --out DIR,
         --redo KEYS (translate these checkpoint keys again, e.g. rows import-mt rejected after a
         glossary correction), --redo-model NAME (translate again every row NAME wrote: the
         user's 2026-10-07 decision to redo the 26B-A4B fallback's rows with the 31B).
The glossary is the committed data/english/glossary.tsv as tools/english_text.py reads it.
Python standard library only (plus tools/english_mt.py).
"""
import argparse
import collections
import datetime
import json
import os
import pathlib
import re
import signal
import subprocess
import sys
import threading
import time
import urllib.request
import concurrent.futures as cf

REPO = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(REPO / "tools"))
import english_mt as E  # noqa: E402

LLAMA_BUILD = "b11443"
LLAMA_DIR = REPO / "work/tools/llama.cpp-cuda" / f"llama-{LLAMA_BUILD}"
MODELS = {
    "31b": ("gemma-4-31B-it", "qat-UD-Q4_K_XL",
            REPO / "work/tools/mt-models/gemma-4-31b-gguf/gemma-4-31B-it-qat-UD-Q4_K_XL.gguf"),
    "26b": ("gemma-4-26B-A4B-it", "UD-Q4_K_M",
            REPO / "work/tools/mt-models/gemma-4-26b-a4b-gguf/gemma-4-26B-A4B-it-UD-Q4_K_M.gguf"),
}
TEMPERATURE = 0
CTX_PER_SLOT = 3072

# ---------------------------------------------------------------- prompts (versioned)

PROMPT_VERSION = "v2"
# v1: the trial's rules (docs/english.md 7.4); v2 adds Global's conventions, the %% rule and "no
# Japanese may remain" (docs/english.md 7.8). Changing the text means a new PROMPT_VERSION.
SYSTEM = """You translate Japanese game text from the mobile RPG STAR OCEAN: anamnesis into English.
Rules:
- Use the glossary's English for every glossary term (official names from the game's English release).
- Keep every printf specifier (%d, %s, %u, %02d, %.5f ...) and every tag (<player>, <font color=...>, </font>) exactly, in the same order.
- Write numbers with ASCII digits; full-width symbols become ASCII (ＨＰ＋１０％ -> HP +10%).
- UI labels and buttons: short and terse, title case for labels. Descriptions: one plain sentence. Dialogue: natural, in the speaker's voice.
- Do not add explanations, quotes or notes. Output only the English text.
- Follow the game's English conventions: （全体） = (party), （自分） = (self), a name ending in ・改 = "Revised" before the name (〇〇・改 = Revised 〇〇), 紋章石 = Gems, ＋/－ values as "+10%".
- A literal percent sign after a printf specifier is written %% (%d％ -> %d%%) in rows that contain printf specifiers.
- Translate everything: no Japanese characters may remain. Names not in the glossary: romanize them consistently."""

NAMES_VERSION = "names-v1"
NAMES_SYSTEM = """You help localize the Japanese mobile RPG STAR OCEAN: anamnesis into English.
You get one katakana term and up to three lines of game text it appears in (with the official English names of other terms for reference).
Answer with one JSON object and nothing else: {"en": "<English>", "proper_noun": true|false}
- "en": the English the term should have everywhere in the game: for a name of a person, creature, place, organization, ship, weapon, skill or item, the most plausible intended romanization or English name (as an official English localization of a Japanese RPG would write it; STAR OCEAN series names where you know them); for an ordinary loanword, the plain English word.
- "proper_noun": true for a name (person, creature, place, organization, ship, unique object, skill or move name), false for an ordinary word (damage, clear, mission, coin, gear...)."""


def user_prompt(kind, mid, ja, glossary, terms):
    hits = E.glossary_hits(ja, glossary, terms)
    k = "story dialogue line" if kind == "story" else f"UI/system text (message_id {mid})"
    gl = "".join(f"\n{t} = {glossary[t]['en']}" for t in hits)
    return f"Kind: {k}\nGlossary:{gl or ' (none)'}\nJapanese:\n{ja}"


# ---------------------------------------------------------------- inputs

def sources():
    a = argparse.Namespace(master=str(REPO / "data/basmaster-3.7.0.sqlite3"),
                           gl=str(REPO / "data/basmaster-gl.sqlite3"),
                           scenario=str(REPO / "work/SOA-3.7.0-canonical-data.zip"))
    return E.Sources(a)


def master_gap(src, mem):
    """{ja text_value: [message_ids]} of the master rows with no official/memory/template English."""
    gap = collections.defaultdict(list)
    for mid in sorted(src.jp_rows):
        ja = src.jp_rows[mid] or ""
        if src.official(mid, ja) or not E.has_kana(ja) or mem.lookup(ja)[0] is not None:
            continue
        gap[ja].append(mid)
    return gap


KATA_RUN = re.compile("[ァ-ヺー・]+")


def kata_terms(text, glossary):
    for m in KATA_RUN.finditer(text):
        r = m.group().strip("・")
        if r.startswith("ー"):
            r = r.lstrip("ー")
        if len(r) < 2 or r in glossary:
            continue
        yield r


def load_glossary(names_tsv=None):
    """The committed glossary (data/english/glossary.tsv through tools/english_text.py: Global's
    terms, the human corrections and removals, the M2 machine names), as english_text's checks
    read it, so the engine is told exactly the terms the import checks. `names_tsv` is unused
    since the M2 names were committed (kept for the call sites)."""
    import english_text as T
    ctx = T.Ctx()
    g = T.glossary_dict(T.glossary_rows(ctx))
    return sources(), g


# ---------------------------------------------------------------- engine

def gpu_free_mib():
    try:
        out = subprocess.run(["nvidia-smi", "--query-gpu=memory.free", "--format=csv,noheader,nounits"],
                             capture_output=True, text=True, timeout=30).stdout
        return int(out.split()[0])
    except Exception:
        return -1


def game_clients():
    """Game clients on the GPU holding a slot of the pool (control/soaslot.py status: "slot N: held
    ... by pid P"): every gate, session and hand-started client takes one. A holder whose
    environment selects llvmpipe (SOA_SLOT_SOFTWARE_GL=1 or GALLIUM_DRIVER=llvmpipe:
    docs/testing-software-gl.md) doesn't count. 0 when the pool can't be read."""
    try:
        out = subprocess.run([sys.executable, str(REPO / "control/soaslot.py"), "status"],
                             capture_output=True, text=True, timeout=60).stdout
    except Exception:
        return 0
    n = 0
    for pid in re.findall(r"^\s*slot \d+: held .*?by pid (\d+)", out, re.M):
        try:
            env = open(f"/proc/{pid}/environ", "rb").read().split(b"\0")
        except OSError:
            env = []
        if b"SOA_SLOT_SOFTWARE_GL=1" in env or b"GALLIUM_DRIVER=llvmpipe" in env:
            continue
        n += 1
    return n


YIELD_TO_CLIENTS = True  # --share-gpu turns it off


class Engine:
    def __init__(self, model, port, slots, logdir):
        self.name, self.quant, self.gguf = MODELS[model]
        self.port, self.slots, self.logdir = port, slots, logdir
        self.proc = None
        self.lock = threading.Lock()

    def start(self, min_free):
        while True:
            free = gpu_free_mib()
            clients = game_clients() if YIELD_TO_CLIENTS else 0
            if free >= min_free and not clients:
                break
            print(f"[gpu] {free} MiB free (need {min_free}), {clients} game clients in the slot pool: waiting", flush=True)
            time.sleep(60)
        env = dict(os.environ, LD_LIBRARY_PATH=f"{LLAMA_DIR}:/usr/lib/wsl/lib")
        log = open(self.logdir / f"llama-server-{self.port}.log", "ab")
        cmd = [str(LLAMA_DIR / "llama-server"), "-m", str(self.gguf), "--port", str(self.port),
               "-ngl", "99", "-np", str(self.slots), "-c", str(self.slots * CTX_PER_SLOT), "-fa", "on",
               "--jinja", "-rea", "off", "-t", "16", "--no-webui"]
        self.proc = subprocess.Popen(cmd, env=env, stdout=log, stderr=subprocess.STDOUT)
        print(f"[engine] llama-server pid {self.proc.pid} ({self.name} {self.quant}, {self.slots} slots)", flush=True)
        for _ in range(600):
            if self.proc.poll() is not None:
                sys.exit(f"llama-server exited ({self.proc.returncode}); see {log.name}")
            try:
                urllib.request.urlopen(f"http://127.0.0.1:{self.port}/health", timeout=5)
                return
            except Exception:
                time.sleep(2)
        sys.exit("llama-server did not become ready")

    def stop(self):
        if self.proc and self.proc.poll() is None:
            self.proc.send_signal(signal.SIGTERM)
            try:
                self.proc.wait(60)
            except subprocess.TimeoutExpired:
                self.proc.kill()
        self.proc = None

    def chat(self, system, user, max_tokens):
        req = {"messages": [{"role": "system", "content": system}, {"role": "user", "content": user}],
               "temperature": TEMPERATURE, "max_tokens": max_tokens, "seed": 0,
               "chat_template_kwargs": {"enable_thinking": False}}
        for attempt in range(1000):  # the guard may be restarting the server (GPU contention)
            try:
                r = urllib.request.urlopen(urllib.request.Request(
                    f"http://127.0.0.1:{self.port}/v1/chat/completions", data=json.dumps(req).encode(),
                    headers={"Content-Type": "application/json"}), timeout=900)
                d = json.load(r)
                txt = re.sub(r"<think>.*?</think>", "", d["choices"][0]["message"]["content"] or "", flags=re.S).strip()
                return txt, d["choices"][0].get("finish_reason")
            except Exception as e:  # server restarting under GPU contention
                print(f"[engine] request failed ({e}); retry", flush=True)
                time.sleep(30)
        raise RuntimeError("engine unreachable")

    def provenance(self):
        return {"model": self.name, "quant": self.quant, "llama_build": LLAMA_BUILD,
                "temperature": TEMPERATURE, "slots": self.slots}


def run_batch(a, items, ckpt, make_request, make_row):
    """items: [(key, payload)], key unique; skips keys already in ckpt. make_request(payload) ->
    (system, user, max_tokens); make_row(key, payload, text, finish) -> dict appended to ckpt."""
    if a.redo or a.redo_model:  # re-translate: drop those rows from the checkpoint (backup kept)
        redo = set(pathlib.Path(a.redo).read_text().split()) if a.redo else set()
        if a.redo_model and ckpt.exists():  # every row an engine model wrote (e.g. the fallback's)
            redo |= {r["key"] for r in map(json.loads, open(ckpt, encoding="utf-8")) if r.get("model") == a.redo_model}
        if ckpt.exists() and redo:
            lines = open(ckpt, encoding="utf-8").read().splitlines(True)
            keep = [ln for ln in lines if json.loads(ln)["key"] not in redo]
            bak = ckpt.with_suffix(f".jsonl.bak-{datetime.datetime.now():%Y%m%d%H%M%S}")
            bak.write_text("".join(lines), encoding="utf-8")
            ckpt.write_text("".join(keep), encoding="utf-8")
            print(f"[batch] --redo: {len(lines) - len(keep)} rows dropped (backup {bak.name})", flush=True)
    done = set()
    if ckpt.exists():
        for line in open(ckpt, encoding="utf-8"):
            done.add(json.loads(line)["key"])
    todo = [(k, p) for k, p in items if k not in done]
    if a.limit:
        todo = todo[:a.limit]
    print(f"[batch] {ckpt.name}: {len(items)} items, {len(done)} done, {len(todo)} to do", flush=True)
    if not todo:
        return
    eng = Engine(a.model, a.port, a.slots, ckpt.parent)
    eng.start(a.min_free)
    stop = threading.Event()
    low = [0]

    def guard():  # other programs win the GPU
        while not stop.wait(30):
            free = gpu_free_mib()
            clients = game_clients() if YIELD_TO_CLIENTS else 0
            low[0] = low[0] + 1 if 0 <= free < a.low_free else 0
            if low[0] >= 2 or clients:  # game clients starve beside the model: yield at once
                with eng.lock:
                    print(f"[gpu] {free} MiB free, {clients} game clients: stopping the engine until they are gone "
                          f"and {a.min_free} MiB are free", flush=True)
                    eng.stop()
                    time.sleep(120)
                    eng.start(a.min_free)
                low[0] = 0
    threading.Thread(target=guard, daemon=True).start()
    out = open(ckpt, "a", encoding="utf-8")
    wlock = threading.Lock()
    t0, n = time.time(), [0]

    def one(kp):
        k, p = kp
        system, user, mt = make_request(p)
        txt, finish = eng.chat(system, user, mt)
        row = make_row(k, p, txt, finish)
        row.update(eng.provenance())
        row["date"] = datetime.date.today().isoformat()
        with wlock:
            out.write(json.dumps(row, ensure_ascii=False) + "\n")
            out.flush()
            n[0] += 1
            if n[0] % 200 == 0:
                dt = time.time() - t0
                print(f"[batch] {n[0]}/{len(todo)} in {dt / 60:.1f} min ({n[0] / dt * 60:.0f}/min)", flush=True)
    try:
        with cf.ThreadPoolExecutor(a.slots) as ex:
            list(ex.map(one, todo))
    finally:
        stop.set()
        eng.stop()
        out.close()
    print(f"[batch] done: {n[0]} items in {(time.time() - t0) / 60:.1f} min", flush=True)


# ---------------------------------------------------------------- commands

def cmd_names(a):
    """M2: every katakana run of the master's gap and of the story's untranslated lines that is not
    a glossary term, sent once with up to three context lines; the answers become the name list
    (names.tsv: ja, en, proper_noun, count), and the proper nouns join the glossary (M-Q7: the
    engine's first spelling is accepted)."""
    src, g = load_glossary()
    mem = E.Memory(src)
    terms_sorted = sorted(g, key=len, reverse=True)
    ctx = collections.defaultdict(list)
    count = collections.Counter()
    texts = [ja for ja in master_gap(src, mem)]
    texts += [ja for _, mid, ja in src.story() if E.has_kana(ja) and not src.story_official(mid, ja)]
    for t in texts:
        for r in set(kata_terms(t, g)):
            count[r] += 1
            if len(ctx[r]) < 3 and len(t) <= 160:
                ctx[r].append(t.replace("\\n", " ").replace("\n", " "))
    items = sorted(count)
    print(f"[names] {len(items)} katakana terms", flush=True)

    def req(term):
        lines = "\n".join(f"- {c}" for c in ctx[term]) or "- (no short context)"
        refs = set()
        for c in ctx[term]:
            refs.update(E.glossary_hits(c, g, terms_sorted))
        ref = "".join(f"\n{t} = {g[t]['en']}" for t in sorted(refs)) or " (none)"
        return NAMES_SYSTEM, f"Term: {term}\nContext:\n{lines}\nKnown names:{ref}", 80

    def row(term, _p, txt, finish):
        m = re.search(r"\{.*\}", txt, re.S)
        try:
            d = json.loads(m.group()) if m else {}
        except ValueError:
            d = {}
        return {"key": term, "ja": term, "count": count[term], "raw": txt, "finish": finish,
                "en": d.get("en"), "proper_noun": bool(d.get("proper_noun")), "prompt": NAMES_VERSION}
    ckpt = a.out / "names.jsonl"
    run_batch(a, [(t, t) for t in items], ckpt, req, row)
    write_names_tsv(ckpt, a.out / "names.tsv")


def write_names_tsv(ckpt, tsv):
    rows = {}
    for line in open(ckpt, encoding="utf-8"):
        r = json.loads(line)
        rows.setdefault(r["key"], r)  # the first answer is kept (M-Q7)
    with open(tsv, "w", encoding="utf-8") as f:
        f.write("ja\ten\tproper_noun\tcount\n")
        for k in sorted(rows):
            r = rows[k]
            en = (r.get("en") or "").replace("\t", " ").strip()
            if not en or E.has_kana(en):
                continue
            f.write(f"{k}\t{en}\t{1 if r['proper_noun'] else 0}\t{r['count']}\n")
    print(f"[names] -> {tsv}")


def cmd_ui(a):
    """M3: each distinct Japanese text of the master's gap once (fanned out to its message_ids at
    import), with the glossary (Global's terms + the name pass's proper nouns)."""
    src, g = load_glossary(a.out / "names.tsv")
    if not (a.out / "names.tsv").exists():
        sys.exit("run `names` first (M2): the glossary needs the name pass")
    terms = sorted(g, key=len, reverse=True)
    mem = E.Memory(src)
    gap = master_gap(src, mem)
    items = sorted((E.sha1(ja), (ja, ids)) for ja, ids in gap.items())

    def req(p):
        ja, ids = p
        text = ja.replace("\\n", "\n")
        return SYSTEM, user_prompt("master", ids[0], text, g, terms), max(300, 3 * len(text) + 100)

    def row(k, p, txt, finish):
        ja, ids = p
        if len(txt) > 1 and txt[0] == txt[-1] and txt[0] in '"「':
            txt = txt[1:-1]
        return {"key": k, "ja_sha1": k, "ja": ja, "mt": txt, "finish": finish, "kind": "master",
                "ids": ids, "prompt": PROMPT_VERSION}
    run_batch(a, items, a.out / "ui.jsonl", req, row)


STORY_VERSION = "story-v1"
STORY_EXTRA = """
You now translate story dialogue: a numbered block of consecutive lines of one scene, each with its speaker.
- Translate each numbered line into natural English dialogue in the speaker's voice, keeping the scene's tone; keep the speaker names and every name in the glossary exactly as given.
- Keep <player> (the player's name) and every <fontcolor=...>, <fontsize=...>, </font> tag exactly.
- Lines marked (context) are earlier lines for reference only: do not translate them.
- Output exactly one line per numbered line to translate, as "[N] English", in order, nothing else. Write each line's English on one line (no line breaks inside it)."""
STORY_CHUNK = 12
STORY_CONTEXT = 4


def scenes(src):
    """[(scene id, [(message_id, speaker code or None)])] in script order, from the download's
    Script/*.msgp (src.scenario: the download, its zip read in place or a folder)."""
    from soa_save import script
    from soa_save.download_tree import DownloadTree
    out = []
    tree = DownloadTree.open_or_none(src.scenario)
    for n in tree.list("Script") if tree else []:
        if not n.endswith(".msgp"):
            continue
        o = script.load(tree.read("Script/" + n), "Script/" + n)
        lines = []
        for _sid, cmds in o.get("Script", {}).items():
            for c in cmds:
                name = script.command_name(c["command_type"])
                if name in script.SPEECH:
                    mid = c.get("command_param0")
                    who = c.get("command_param6") or c.get("command_param1")
                    if isinstance(mid, str):
                        lines.append((mid, who if isinstance(who, str) else None))
                elif name in script.MENUS:
                    for k in range(0, 8, 2):
                        mid = c.get(f"command_param{k}")
                        if isinstance(mid, str) and mid:
                            lines.append((mid, "(choice)"))
        if lines:
            out.append((n[: -len(".msgp")], lines))
    return out


def cmd_story(a):
    """M4: the story's untranslated lines, a chunk of a scene per request with the speakers named
    and the lines before it as context; each line is checkpointed by message_id."""
    src, g = load_glossary(a.out / "names.tsv")
    if not (a.out / "names.tsv").exists():
        sys.exit("run `names` first (M2)")
    terms = sorted(g, key=len, reverse=True)
    text = {mid: (stem, ja) for stem, mid, ja in src.story()}
    jp_names = src.jp_rows

    def speaker(code):
        if not code:
            return "Narration"
        if code == "<player>":
            return "<player>"
        if code == "(choice)":
            return "(menu choice)"
        for c in (code, code[:-1] + "a"):
            en = src.gl_english(c)
            if en:
                return en
            ja = jp_names.get(c)
            if ja:
                return g[ja]["en"] if ja in g else ja
        return code

    items, seen = [], set()
    for scene, lines in scenes(src):
        lines = [(m, w) for m, w in lines if m in text]
        todo = [i for i, (m, _) in enumerate(lines)
                if m not in seen and E.has_kana(text[m][1]) and not src.story_official(m, text[m][1])]
        for m, _ in lines:
            seen.add(m)
        for k in range(0, len(todo), STORY_CHUNK):
            idx = todo[k:k + STORY_CHUNK]
            first = idx[0]
            ctx = list(range(max(0, first - STORY_CONTEXT), first))
            items.append((f"{scene}:{lines[first][0]}", (scene, [lines[i] for i in ctx], [lines[i] for i in idx])))
    # lines no script references (unused or menu text): in message_id order per file, no speaker
    rest = collections.defaultdict(list)
    for m, (stem, ja) in sorted(text.items()):
        if m not in seen and E.has_kana(ja) and not src.story_official(m, ja):
            rest[stem].append((m, None))
    for stem, lines in sorted(rest.items()):
        for k in range(0, len(lines), STORY_CHUNK):
            items.append((f"{stem}:{lines[k][0]}", (stem, [], lines[k:k + STORY_CHUNK])))
    # the user's order (2026-10-07): the event story files first, then EP2, then EP3, then the
    # rest (EP1's and TS_3xxx / TS_5xxx's few gaps); stable within a group (script order)
    rank = {"events/other": 0, "EP2": 1, "EP3": 2}
    items.sort(key=lambda kp: rank.get(E.story_group(text[kp[1][2][0][0]][0]), 3))
    print(f"[story] {len(items)} requests, {sum(len(p[2]) for _, p in items)} lines", flush=True)

    def req(p):
        scene, ctx, todo = p
        block, hits = [], []
        for m, w in ctx:
            block.append(f"(context) {speaker(w)}: {text[m][1].replace(chr(10), '')}")
        for n, (m, w) in enumerate(todo, 1):
            ja = text[m][1].replace("\n", "")  # Japanese breaks carry no space
            hits += E.glossary_hits(ja, g, terms)
            block.append(f"[{n}] {speaker(w)}: {ja}")
        gl = "".join(f"\n{t} = {g[t]['en']}" for t in dict.fromkeys(hits))
        user = f"Scene {scene}\nGlossary:{gl or ' (none)'}\nLines:\n" + "\n".join(block)
        return SYSTEM + STORY_EXTRA, user, 120 * len(todo) + 200

    def row(k, p, txt, finish):
        scene, _ctx, todo = p
        got = {int(m.group(1)): m.group(2).strip() for m in re.finditer(r"^\[(\d+)\]\s*(.*)$", txt, re.M)}
        lines = []
        for n, (m, w) in enumerate(todo, 1):
            en = got.get(n)
            if en and ":" in en and en.split(":", 1)[0].strip() == speaker(w):
                en = en.split(":", 1)[1].strip()  # the model repeated the speaker
            lines.append({"message_id": m, "file": text[m][0], "ja_sha1": E.sha1(text[m][1]),
                          "ja": text[m][1], "speaker": speaker(w), "mt": en})
        return {"key": k, "scene": scene, "kind": "story", "lines": lines, "raw": txt, "finish": finish,
                "prompt": f"{PROMPT_VERSION}+{STORY_VERSION}"}
    run_batch(a, items, a.out / "story.jsonl", req, row)


SHORT_VERSION = "short-v1"
SHORT_SYSTEM = """You edit the English localization of the Japanese mobile RPG STAR OCEAN: anamnesis.
A line of story dialogue is too long for the game's small message window. Rewrite it shorter, in at most {limit} characters (tags not counted), keeping its meaning, the speaker's voice and tone, every name exactly, and every tag (<player>, <fontcolor=...>, <fontsize=...>, </font>) exactly.
Output only the shortened line, on one line, nothing else."""
STORY_LINES_MAX = 4      # the message window shows four lines (english.md 7.5)
SHORT_LIMIT = 150        # characters asked for: about four lines of the window


def cmd_shorten(a):
    """E7/M4: machine story lines that need more than four lines of the message window (re-broken
    at the window's width with the font's advances, as tools/english_text.py does) are sent once
    more, with the Japanese for reference, to be rewritten shorter. Writes story-short.jsonl in
    story.jsonl's form (one line per item); tools/english_text.py import-mt --replace takes it."""
    import english_text as T
    ctx = T.Ctx()
    font = ctx.fnt
    items = []
    for line in open(a.out / "story.jsonl", encoding="utf-8"):
        r = json.loads(line)
        for x in r["lines"]:
            if not x["mt"]:
                continue
            e = font.rebreak(font.fold(x["mt"]).strip(), T.STORY_BUDGET, T.PLAYER_PX)
            if e.count("\n") + 1 > STORY_LINES_MAX:
                items.append((x["message_id"] + ":" + E.sha1(x["mt"]), (r["scene"], x)))
    items.sort()
    print(f"[shorten] {len(items)} story lines over {STORY_LINES_MAX} lines", flush=True)

    def req(p):
        _scene, x = p
        user = (f"Speaker: {x['speaker']}\nJapanese (reference): {x['ja'].replace(chr(10), '')}\n"
                f"English ({len(x['mt'])} characters): {x['mt']}")
        return SHORT_SYSTEM.format(limit=SHORT_LIMIT), user, 200

    def row(k, p, txt, finish):
        scene, x = p
        txt = txt.strip().strip('"')
        return {"key": k, "scene": scene, "kind": "story", "raw": txt, "finish": finish,
                "lines": [dict(x, mt=txt or None, long=x["mt"])],
                "prompt": f"{PROMPT_VERSION}+story-v1+{SHORT_VERSION}"}
    run_batch(a, items, a.out / "story-short.jsonl", req, row)


def cmd_story_fix(a):
    """Q12 needs every line of a file: the story lines still without English after `story` and its
    redo (rejected by the checks or skipped by the model) are sent one at a time, with the scene's
    four lines before as context (their English when the table has it) and the speaker; the answers
    go to story-fix.jsonl in story.jsonl's form (import-mt takes it)."""
    src, g = load_glossary()
    terms = sorted(g, key=len, reverse=True)
    text = {mid: (stem, ja) for stem, mid, ja in src.story()}
    have = {}
    for p in sorted((REPO / "data/english/story-en").glob("TS_*.tsv")):
        for line in p.read_text(encoding="utf-8").splitlines()[1:]:
            c = line.split("\t")
            have[c[0]] = c[2].replace("\\n", " ")
    items = []
    for scene, lines in scenes(src):
        lines = [(m, w) for m, w in lines if m in text]
        for i, (m, w) in enumerate(lines):
            stem, ja = text[m]
            if m in have or not E.has_kana(ja) or src.story_official(m, ja):
                continue
            items.append((f"fix:{m}", (scene, lines[max(0, i - STORY_CONTEXT):i], (m, w))))
    seen = {k for k, _ in items}
    for m, (stem, ja) in sorted(text.items()):  # lines no script references
        if f"fix:{m}" not in seen and m not in have and E.has_kana(ja) and not src.story_official(m, ja):
            items.append((f"fix:{m}", (stem, [], (m, None))))
    print(f"[story-fix] {len(items)} lines", flush=True)

    def speaker(code):
        if not code:
            return "Narration"
        if code in ("<player>", "(choice)"):
            return code
        for c in (code, code[:-1] + "a"):
            en = src.gl_english(c)
            if en:
                return en
            ja = src.jp_rows.get(c)
            if ja:
                return g[ja]["en"] if ja in g else ja
        return code

    def req(p):
        scene, ctx, (m, w) = p
        block = []
        for cm, cw in ctx:
            en = have.get(cm)
            block.append(f"(context) {speaker(cw)}: {text[cm][1].replace(chr(10), '')}" + (f"  [English: {en}]" if en else ""))
        ja = text[m][1].replace("\n", "")
        hits = E.glossary_hits(ja, g, terms)
        block.append(f"[1] {speaker(w)}: {ja}")
        gl = "".join(f"\n{t} = {g[t]['en']}" for t in hits)
        user = f"Scene {scene}\nGlossary:{gl or ' (none)'}\nLines:\n" + "\n".join(block)
        return SYSTEM + STORY_EXTRA, user, 400

    def row(k, p, txt, finish):
        scene, _ctx, (m, w) = p
        got = re.search(r"^\[1\]\s*(.*)$", txt, re.M)
        en = (got.group(1) if got else txt).strip()
        if en and ":" in en and en.split(":", 1)[0].strip() == speaker(w):
            en = en.split(":", 1)[1].strip()
        return {"key": k, "scene": scene, "kind": "story", "raw": txt, "finish": finish,
                "lines": [{"message_id": m, "file": text[m][0], "ja_sha1": E.sha1(text[m][1]), "ja": text[m][1],
                           "speaker": speaker(w), "mt": en or None}],
                "prompt": f"{PROMPT_VERSION}+{STORY_VERSION}+fix"}
    run_batch(a, items, a.out / "story-fix.jsonl", req, row)


def cmd_status(a):
    for p in sorted(a.out.glob("*.jsonl")):
        n = sum(1 for _ in open(p, encoding="utf-8"))
        print(f"{p.name}: {n}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["names", "ui", "story", "story-fix", "shorten", "status"])
    ap.add_argument("--model", choices=sorted(MODELS), default="31b")
    ap.add_argument("--slots", type=int, default=4)
    ap.add_argument("--port", type=int, default=18431)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--redo", help="a file of checkpoint keys (ja_sha1 / story chunk keys) to translate again")
    ap.add_argument("--share-gpu", action="store_true",
                    help="keep running beside game clients (default: the batch waits while any client holds a slot of the pool)")
    ap.add_argument("--redo-model", help="translate again every checkpoint row this model wrote (e.g. gemma-4-26B-A4B-it)")
    ap.add_argument("--min-free", type=int, default=23000, help="MiB free before loading the model")
    ap.add_argument("--low-free", type=int, default=300, help="MiB free under which the engine yields")
    ap.add_argument("--out", type=pathlib.Path, default=REPO / "work/english/mt")
    a = ap.parse_args()
    a.out.mkdir(parents=True, exist_ok=True)
    global YIELD_TO_CLIENTS
    YIELD_TO_CLIENTS = not a.share_gpu
    {"names": cmd_names, "ui": cmd_ui, "story": cmd_story, "shorten": cmd_shorten, "story-fix": cmd_story_fix, "status": cmd_status}[a.cmd](a)


if __name__ == "__main__":
    main()

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

The GPU is shared with game clients: before loading, at least --min-free MiB must be free; while
running, if free VRAM drops under --low-free MiB on two checks in a row the server is stopped and
the batch waits until --min-free MiB are free again, then restarts it (other programs win).

Usage:
  tools/english_mt_run.py names [--model 31b|26b]   # M2: katakana terms of the gap -> name list
  tools/english_mt_run.py ui    [--model 31b|26b]   # M3: the master's gap texts
  tools/english_mt_run.py status                     # rows done per checkpoint
Options: --slots N (4), --port P (18431), --limit N (stop after N new items), --out DIR.
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
                           scenario=str(REPO / "work/download-3.7.0/Scenario"))
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
    """Global's glossary (english_mt.build_glossary over the whole master) plus the name pass's
    proper nouns (kind 'name', source machine) when names_tsv exists."""
    src = sources()
    g = E.build_glossary(src)
    if names_tsv and os.path.exists(names_tsv):
        for line in open(names_tsv, encoding="utf-8").read().splitlines()[1:]:
            ja, en, proper, count = line.split("\t")[:4]
            # a name seen in one text only gains nothing from the glossary (and an interjection
            # misread as a name would only constrain that row)
            if proper == "1" and int(count) >= 2 and ja not in g:
                g[ja] = {"en": en, "kind": "name", "variants": [], "ids": []}
    return src, g


# ---------------------------------------------------------------- engine

def gpu_free_mib():
    try:
        out = subprocess.run(["nvidia-smi", "--query-gpu=memory.free", "--format=csv,noheader,nounits"],
                             capture_output=True, text=True, timeout=30).stdout
        return int(out.split()[0])
    except Exception:
        return -1


class Engine:
    def __init__(self, model, port, slots, logdir):
        self.name, self.quant, self.gguf = MODELS[model]
        self.port, self.slots, self.logdir = port, slots, logdir
        self.proc = None
        self.lock = threading.Lock()

    def start(self, min_free):
        while True:
            free = gpu_free_mib()
            if free >= min_free:
                break
            print(f"[gpu] {free} MiB free < {min_free}: waiting", flush=True)
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
            low[0] = low[0] + 1 if 0 <= free < a.low_free else 0
            if low[0] >= 2:
                with eng.lock:
                    print(f"[gpu] {free} MiB free: stopping the engine until {a.min_free} MiB are free", flush=True)
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


def cmd_status(a):
    for p in sorted(a.out.glob("*.jsonl")):
        n = sum(1 for _ in open(p, encoding="utf-8"))
        print(f"{p.name}: {n}")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cmd", choices=["names", "ui", "status"])
    ap.add_argument("--model", choices=sorted(MODELS), default="31b")
    ap.add_argument("--slots", type=int, default=4)
    ap.add_argument("--port", type=int, default=18431)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--min-free", type=int, default=23000, help="MiB free before loading the model")
    ap.add_argument("--low-free", type=int, default=300, help="MiB free under which the engine yields")
    ap.add_argument("--out", type=pathlib.Path, default=REPO / "work/english/mt")
    a = ap.parse_args()
    a.out.mkdir(parents=True, exist_ok=True)
    {"names": cmd_names, "ui": cmd_ui, "status": cmd_status}[a.cmd](a)


if __name__ == "__main__":
    main()

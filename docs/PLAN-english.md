# Plan: English text in the 3.7.0 client

A plan built on the findings in [english.md](english.md). Nothing here is implemented yet. Each step lists its effort (S = a day or less, M = a few days, L = a week or more), what it depends on, how it is proved and where it sits on the server-first rule ([AGENTS.md "Hard rules"](../AGENTS.md#hard-rules)).

History:
- 2026-10-06 (agents `english`, `english2`): three options, A (server only), B (client switch + `en_` rows) and C (client switch + per-language files), with C recommended. Their comparison is in [english.md 6.6](english.md#66-consequence-the-smallest-client-change-is-one-site).
- 2026-10-07: the user's decisions below; the plan is now **option C only**, restructured around them. The machine-translation option for the gaps (Q2, Q12, still open) was investigated the same day (agent `english-mt`, [english.md section 7](english.md#7-machine-translation-for-the-gaps)) and is the last part of this plan.
- 2026-10-07, later: the user's answers to the MT questions (M-Q1 and M-Q3 to M-Q7, below), and a second trial with 12–31B local LLMs on the GPU (agent `english-llm`, [english.md 7.8](english.md#78-local-llms-on-the-gpu-1231b)); the engine (M-Q2) is still open.

## Decisions (the user, 2026-10-07)

**M-Q2 decided (the user, 2026-10-07: "select the best local model and execute the plan"):** the engine is **Gemma 4 31B-it, QAT UD-Q4_K_XL, with the v2 prompt** (llama.cpp CUDA, work/tools/), chrF 44.9 in the blind trial (Claude Opus 44.4), for the UI/system text and the story. It needs the whole GPU (~22.5 GB): run the MT batches when no game sessions use the GPU; Gemma 4 26B-A4B (v2 prompt, 44.3, ~3x faster) is the fallback when VRAM is contended.

| Q | Decision |
|---|---|
| Q9 | **Option C only**: the client's `CLanguage` switch (`--lang en`) plus a server that serves `-en` files, including a full English master. No B (no StringDB patch); A is not kept as a mode. |
| Q1 | **UI first** (the `-en` master), the story after. |
| Q2 = M-Q1 | **(c)**: machine-translate the UI and system text now; the story after its names are set. |
| Q12 = M-Q6 | A story file's `-en` version is served **only when every line has English**, machine lines included. |
| M-Q2 | The engine: **open**, to be decided after the local 12–31B test ([english.md 7.8](english.md#78-local-llms-on-the-gpu-1231b)); the options are under [Machine translation for the gaps](#machine-translation-for-the-gaps-m-steps). |
| M-Q3 | **Test larger local models first** (done: english.md 7.8). |
| M-Q4 | `machine` rows **may ship unreviewed**, marked `machine` in the provenance and the coverage report. |
| M-Q5 | The glossary and the translation tables are **committed** under `data/english/`. **Release packages ship the already-built `-en` files.** An `-en` master is a full master DB built from the game's master, so this needs an explicit packaging exception (step P2): `tools/package.py`'s game-file scan rejects SQLite files with `master_*` tables and its allow-list has no `-en` entries. Not changed yet. |
| M-Q7 | **The engine's choice for new names is accepted**: the first spelling is fixed into the glossary automatically and reused everywhere after. |
| Q3 | **No fan translations**: Global's official English plus whatever Q2 decides. |
| Q4 | **Our own English UI art**, as a second, English-only stand-in overlay (e.g. `standin-assets-en/`) served as `-en` members; the Japanese image is the client's fallback. The images are edits of the game's art, so git holds only a **per-image recipe** (source file, text box, English text, font and style) and the generator; the server or package builds the `-en` images locally at first run from the user's own download, like the master derivation. No game art in git or packages. Global's own assets, if the user obtains them later, could replace generated images. |
| Q5 | Client `--lang` defaults to **`ja`**. Release packages default to Japanese and add **English launchers** (`run-port-en`, `run-emulator-en`: server `--english`, client `--lang en`). |
| Q6 | **Client changes now**: word wrap, and natives replacing the 14 hard-coded strings, are part of the first English steps (logged in [client-changes.md](client-changes.md)). |
| Q7 | The 803 rows whose Global English translates an older Japanese text **follow the gap rule**; the coverage report lists them with Global's old English as an editor's reference. |
| Q8 | **Global's terminology**: one glossary seeded from Global; all new and machine text follows it. |
| Q10 | **Japanese voices** in English mode (`--voice-lang ja`); revisit if an English dub source appears. |
| Q11 | The CDN carries the `-en` files **only when the server runs with `--english`**. |
| Q13 | **Skip the pre-download screens** for now. |

## How option C works

- The client is told its language: **one site**, `CLanguage::Current` = `en` (B1).
- The client's own loader already tries `name-en.ext` before `name.ext` for every file: master, story, layouts, images, font and voices ([english.md 6.3](english.md#63-files-name-enext-with-the-plain-name-as-the-fallback-already-built-in)).
- The server, with `--english`, serves English as **new `-en` members** beside the Japanese files:
  - `sqlite/basmaster-en.sqlite3`: the served master with English in its `ja_` rows;
  - `Scenario/TS_*-en.msgp`;
  - `-en` images (our art, Q4) and layouts.
- StringDB is untouched: it keeps reading `ja_` rows, of the English files.
- A Japanese file is the fallback **per file**, made by the client. A Japanese row is the fallback **per row**, made by the server when it builds the `-en` master.
- Cost: every client of an `--english` server fetches every `-en` member at its data check, about **36 MB** for the second master plus story and art ([english.md 6.3](english.md#63-files-name-enext-with-the-plain-name-as-the-fallback-already-built-in)). A server without `--english` costs nothing (Q11).
- Not reached: a real phone or Waydroid (unpatched client: Japanese); the pre-download screens (Q13); voices (no English data, Q10).

## Steps

### Phase 1: the UI in English

| Step | What | Effort | Depends on | Proof |
|---|---|---|---|---|
| **E1** (done 2026-10-06, agent `en-data`: [english.md 7.6 "As built"](english.md#76-storage-provenance-and-editing)) | **English text table and coverage report** ([english.md 7.6](english.md#76-storage-provenance-and-editing)):<br>1. Global by id with the five filters;<br>2. exact and template memory (english.md 7.2);<br>3. the glossary (`data/english/glossary.tsv`, Q8);<br>4. the committed table for everything else (`data/english/master.tsv`: `human`, `reviewed` and, if Q2 says so, `machine` rows).<br>Glyph folding and the checks of english.md 7.5 (specifiers, tags, glyphs, glossary, widths). The report lists rows per source and prefix, the failing rows, and the 803 rows with older Global English (Q7). | M | — | counts as english.md 7.1 (19,145 by id, 6,265 exact, 2,412 template); 0 failing rows served; pytest of the checks |
| **B1** | **Client: the language code.** A platform370 patch (`platform370/src/patch_370.cpp`, `Config::lang`), active in `soa` and `soa-emu`, with `--lang ja\|en` (default `ja`, Q5). After `CLanguage::CLanguage` (ELF 0x13b4b18; `CGame::OnInitialize` builds it with 0x100 at 0x114256c) it sets `Current` (+4) to 1. `Default` (+0) stays 0x100; `Voice` (+8) stays the save's `BAS:VoiceLanguage`. Logged in `docs/client-changes.md`. | S | — | `CLanguage::Current()` is 1 with `--lang en` and 0x100 without; a `FileExistLanguage` probe in a selftest |
| **C2** (done 2026-10-07, agent `en-server`: `cdn::Options::member_roots` and the generated root `<scratch>/lang-en` under `--english`; test `cdn/lang-members`; byte-identical CDN without `--english`; soa-emu `--lang en` (a build of `port/en-client`) fetched the `-en` master from soa-server's CDN only and showed the English home header with the right event badge, `emulator/scripts/lang_fetch_test.sh`) | **Server: `-en` members on the CDN, only with `--english`** (Q11). Generalise the stand-in step (`TreeBuilder::add_standins`, `server/src/cdn/tree.cpp`) to more roots: the generated root holds the `-en` master, story files and art, names the download doesn't have. They become members as stand-ins do: version.bin entries, one Individual bundle each, a Bulk bundle, a new revision. | M | — | a `cdn/lang-members` selftest; **`soa-emu` with a `-en` master from soa-server's CDN only** (the pattern of `emulator/scripts/standin_fetch_test.sh`), showing the English header |
| **C1** (done 2026-10-07, agent `en-server`: `cdn::make_english_master`, `--english`, `--english-text`; with the real table 27,859 rows English, 0 stale; tests `cdn/served-master-en`, `server/english-text`; docs/server-rules.md#english) | **Server: the English master as a `-en` member.** `make_served_master` (`server/src/cdn/served_master.cpp`) writes a second output: a copy of the served master **after** every `ClientMaster` hook, with E1's English in its `ja_` rows' `text_value`, AES-ADLD (encType 2) under `sqlite/basmaster-en.sqlite3`. The server's own rules keep reading its Japanese master. Labels (a) Global, (d) filters, memory, glossary and our rows; `docs/server-rules.md` `#english`; `docs/client-changes.md` "Data overrides". | M | E1, C2 | `cdn/served-master-en` selftest: the `-en` master's rows equal the served master's except `text_value` of filled rows; ids unchanged; two builds byte-identical |
| **E3** (tokens done 2026-10-06, agent `en-data`: 37 master rows and 117 EP1 + 27 `TS_3/5xxx` story lines official; 22 composed fragments stay gaps; the `uimsg_remain_*` review is open) | Global tokens and composed fragments: `<NUM n>`/`<STR n>` → the JP row's specifiers (no positional `%2$d`: reword), `<INSERT>` fixed, `<EMDASH>` → `―` (turns 117 EP1 story lines official), the `uimsg_remain_*` family reviewed. | S | E1 | E1's report: 0 token rows |
| **E6** (done 2026-10-07, agent `en-server`: `ext::display_text` for the present lines, the notice page in English, the rate headings when the printf conversions match; replay corpus `english`, test `player/notice-english`; the port's `--lang en` → `config().english` is the client agent's wiring) | **Server texts** (notice page, gacha rate headings, present lines) follow `--english`. In-process the port passes its own `--lang` to the server. | S | E1 | replay corpus lines |
| **E10** | **Client changes, now (Q6):** (a) natives for the 10 functions that show the 14 hard-coded strings, reading new `master_text` ids the `-en` master carries; (b) **word wrap** in `CCocosLabel::DrawSelf` / `ComposeString_` when a line exceeds the label's box. Both only with `--lang en`; logged in `docs/client-changes.md`. | M + M | B1 | NATIVE_TEST of each; with `--lang ja` identical to the guest; EN shots of the dialogs and of `uimsg_chara_top_info` |
| **E9** | **English UI art (Q4). Done 2026-10-07 (agent `en-art`) for the first scenes**: recipes (`standin-assets-en/recipes/*.json`: source scene, sprites, text box, area to clear, English, style) and a C++ generator in the server library (`server/src/english_art`, `english_art::build`; not the Python banner tool: packages have no Python) that builds the `-en` scenes from the user's own download in the game's own font into the server's generated root (C2), cached, byte-identical across runs and platforms. Done: the footer and badges (`common`), the home buttons, badges and talk-mode words (`home`), the gacha top (`gacha_top`). Open: other scenes, `Image/` files (JPEG ones need an encoder). No game art in git or packages ([english.md section 8](english.md#8-english-ui-art)). | L | C2 | home and gacha shots with `--lang en`; a package scan with no game images |
| **P1** | **English launchers (Q5):** `run-port-en.sh/.cmd`, `run-emulator-en.sh/.cmd` (server `--english`, client `--lang en`), in `scripts/package.sh`'s ZIPs. | S | B1, C1 | the package lists them; a smoke run of each |
| **P2** | **Packaging exception for the built `-en` files (M-Q5).** Release packages ship the `-en` master and story files the server builds (C1, C3), but an `-en` master is a full master DB derived from the game's master. Design an explicit, narrow exception in `tools/package.py`: allow-list entries for exactly the `-en` outputs, and a scan rule that accepts a `master_*` SQLite file only under those names (and, e.g., only when it matches a build manifest); every other game-file rule stays. Record it in README.md "Game files" and "Packaging". | S | C1, C3 | the package scan passes with the `-en` files and still rejects a plain master or a renamed one |
| **B7** | **Voices (Q10):** `--voice-lang ja` (default) writes `BAS:VoiceLanguage` = 0 to `Game.xml`, as the sessions write `BAS:DownloadEpisodeFlag`: always the Japanese packs, no `-en` probe. | S | B1 | a `Voice_*` probe |
| **E11** | **Tests.** Gates keep running Japanese. Add `home --lang en` as a T2 entry with its own references; E1's report in T1. | S | C1 | `tools/gate.sh T2` |

Order: E1 → B1 → C2 → C1 → E3 → E6 → E10 → P1 → P2 → B7 → E11, with E9 in parallel once C2 exists.

### Phase 2: the story

| Step | What | Effort | Depends on | Proof |
|---|---|---|---|---|
| **C3** | **English story files.** For each `Scenario/TS_*.msgp` with English for the lines Q12 requires, generate `Scenario/TS_*-en.msgp`: the same rows, English in `text_value` (real newlines), ADLD XOR keyed by the `-en` name, served through C2. Official today: EP1 (all but 10 lines after E3), `TS_3xxx`, `TS_5xxx`. EP2, EP3 and the events need MT or a human (M4). | M | E1, E3, C2 | the campaign and tutorial sessions with `--lang en` show English story; every served row parses (`<player>`, `<font…>` only) |
| **C4** | **Proof: the story release path.** `StringDB::ReleaseParameter` frees the rows by `strcmp` with the name `CEventScenario::Run` gave `SetAddLoadFileName`. Play several chapters in a row; watch memory and the next scene's text. | S | B1, C3 | a session over two or more scenes |
| **E7** | **Layout pass.** Re-break story lines to the message window with the font's advances (Global's breaks are for a wider window, english.md 6.5); the about one line in ten that needs five or more lines gets a shorter wording or a `<fontsize=…>` tag (english.md 7.5, untested). Re-break the 459 master rows that lost their line breaks; short overrides for overflowing labels and buttons not covered by E10's wrap. | M | C1, C3 | EN contact sheets with no clipped text on the listed screens |

### Not in this plan any more

- **B's StringDB patch** (`en_` rows, three client sites) and **A's server-only mode** (Q9).
- **B9, the pre-download screens** in English (Q13). The port's asset overlay could still carry them later.
- **B8, a font with accents**: not needed while every text is folded to the font's glyphs (english.md 7.5); kept as an option if a translation ever needs é or —.
- **Fan translations** (Q3).

## Machine translation for the gaps (M steps)

The findings are in [english.md section 7](english.md#7-machine-translation-for-the-gaps). In short:

- After Global's English (19,145 rows by id), exact memory (6,265) and template memory (2,412), **37,593 master rows** (27,847 distinct texts, 705k JA characters) and **17,182 story lines** (530k characters: EP2 7,906, EP3 5,037, events 3,932) have no English. **EP2 has no official English at all.**
- A blind trial on 310 rows (250 scored against Global's English) gave chrF **44** for Claude (Opus 5.5 44.4, Sonnet 5.5 43.8) against **32** (FuguMT) and **28** (Opus-MT) for the offline NMT models. The LLMs kept every printf specifier and tag (36 of 36 rows) and used the glossary in 83–84 of 85 rows; the NMT models lost tokens in 8–9 of 36 rows, can't take a glossary, and translate the game's terms literally ("heraldic stones" for Gems). A 1.1 GB local LLM (Qwen2.5-1.5B) scored 35 and lost tokens in 16 of 36 rows.
- A second trial (english.md 7.8) ran 12–31B local LLMs, quantized to about 4 bits, through llama.cpp on this machine's GPU with the same prompt: **Gemma 4 31B-it** (Apache-2.0, 17 GB) scored chrF **44.3** (44.9 with a prompt carrying Global's conventions), kept every token (36 of 36) and followed the glossary in 81 of 85 rows: within noise of Claude Opus. Gemma 4 26B-A4B 43.8–44.3, Qwen3.8-27B 44.0, Gemma 4 12B 43.4; the Japanese-tuned shisa-v2-mistral-small-24b only 37.6. Claude still looked better on new names and story tone (20 EP3 lines, no reference).
- **Engine (M-Q2, open):** a local model is now a real option. Gemma 4 31B needs about **9–11 hours** of the whole GPU for the gap (26 hours if other programs keep 7 GB of it); Gemma 4 26B-A4B about **3–6 hours**. Claude through the Batch API costs about **$10–20** (Sonnet) or **$20–40** (Opus) and finishes within a day. **Offline fallback without a GPU:** FuguMT through CTranslate2, as a marked rough fill only.
- **The source of truth** is a committed translation table (`data/english/`), keyed by `message_id` with the source text's hash and per-row provenance (`machine` with engine, model and prompt version; `human` with the editor; `reviewed`). Human rows always win and an MT re-run never touches them. The server builds the `-en` files from the table deterministically and never calls an engine.

**Q2 (the gaps) is decided: (c)**, machine translation for the UI and system text now, the story after its names are set (M-Q1). The options it was chosen from were (a) leave the gaps Japanese, (b) MT for all, (c) and (d) human translation only. **Q12:** a story file's `-en` version is served only when every line has English, machine lines included (M-Q6); a file whose MT lines failed the checks waits until they are fixed.

Options for **M-Q2, the engine** (the measurements are english.md 7.4 and 7.8):

| | Quality on the trial | Time and cost for the whole gap | Notes |
|---|---|---|---|
| (a) **Gemma 4 31B-it, local** (GGUF QAT Q4_K_XL, llama.cpp CUDA) | chrF 44.3 (v2 prompt 44.9); tokens 36/36; glossary 81/85 | 9–11 h with the GPU to itself (26 h beside 7 GB of other use); electricity | nothing leaves the machine; Apache-2.0; downloaded (17 GB in `work/tools/mt-models/`) |
| (b) Gemma 4 26B-A4B, local | chrF 43.8 (v2 44.3); tokens 36/36; glossary 80–81/85 | 3–4 h (6 h beside other use) | fastest good model; one wrong name and one invented `%d` in the sample |
| (c) Claude Sonnet 5.5 / Opus 5.5, Batch API | chrF 43.8 / 44.4; tokens 36/36; glossary 83–84/85 | within a day; about $10–20 / $20–40 | best on new names and story tone; the game text goes to Anthropic; needs an API key |
| (d) Mixed: (a) or (b) for the UI and system text (M3), the story engine (M4) chosen after comparing one full scene from (a) and (c) | as above | the UI part locally; the story about half the API cost | proposed |
| (e) DeepL / Google | not measured | $15–35 | no glossary in context, weaker on the game's formulas |
| (f) Offline NMT (FuguMT) | chrF 32; loses tokens in 1 of 4 token rows | 13–16 h on the CPU | rough fill only |

Proposed: **(d)**, with the v2 prompt (Global's conventions, the `%%` rule) and a richer glossary whichever engine runs. New names (M-Q7) take the engine's first spelling, so the name pass (M2) should use the strongest engine available.

| Step | What | Effort | Depends on | Proof |
|---|---|---|---|---|
| **M1** (done 2026-10-06, agent `en-data`; the glossary seed of M2 too: `data/english/glossary.tsv`) | **The table and its tools.** `data/english/` (`glossary.tsv`, `master.tsv`, `story/TS_*.tsv` without the Japanese), the build precedence (human/reviewed > official > memory/template > machine > Japanese), stale-hash detection, and `tools/english_text.py`: `show`, `set --by`, `review`, `stale`, `report`, `export-po`/`import-po` (Poedit, Lokalize, Weblate) and CSV. `tools/english_mt.py`'s checks become a module both use. The font advances come from `Font/etc2/font.fpk` directly (record layout in english.md 3.1), not from the scratch dump in `work/english/font/glyphs.pkl` the prototype reads. | M | E1 | pytest: a human row survives an MT re-run; a changed hash is reported; two builds byte-identical |
| **M2** | **Names first.** The glossary from Global (3,246 terms), its 302 conflicts resolved once, and a list of new proper nouns (katakana runs and names in the gap, e.g. EP3's characters), each sent once with its context to the engine (M-Q7: its first spelling is accepted) and fixed into `glossary.tsv` as `machine`, reused by every later row; a human may change one later. | S | M1 | every name of the story's speakers has a glossary row; no name has two spellings in the table |
| **M3** | **UI and system MT** (Q2 (c)): the 27,847 distinct gap texts through the engine (M-Q2), the checks, rows that fail stay Japanese; written as `machine` rows. | S (+ engine time: 3–11 h locally, english.md 7.8) | M1, M2 | the report: rows per source; 0 failing rows served; an EN `home` session and contact sheets |
| **M4** | **Story MT**, a scene (one `Script`/`TS` group) per request with the speakers named, EP2, EP3, then the events; written as `machine` rows; C3 then serves the complete files (Q12). | M | M2, M3, C3 | a campaign session over an EP2 chapter in English |
| **M5** | **Review pass**, optional (M-Q4: `machine` rows ship unreviewed): a second LLM pass that flags rows breaking Global's conventions or the glossary, then a human pass over the flagged rows, names and story (PO or CSV round trip). | ongoing | M3/M4 | the report's `reviewed` share |
| **M6** | **Hooks into the build**: C1 and C3 read only the table; E11's report adds the per-source counts. | S | M1, C1, C3 | `cdn/served-master-en` still byte-identical across runs |

Questions the MT option raised, and the user's answers (2026-10-07):

- **M-Q1 (Q2).** Fill the gaps by MT? **Decided: (c)**, the UI and system text now, the story after its names are set.
- **M-Q2. Engine.** **Open**: the options (a)–(f) above, now with the local measurements. Proposed (d).
- **M-Q3. A larger local model.** **Decided: test first; done** (english.md 7.8; 71 GB of models in `work/tools/mt-models/`, kept for the choice).
- **M-Q4. Review.** **Decided:** `machine` rows may ship unreviewed, marked in the provenance and the coverage report.
- **M-Q5. What is committed.** **Decided:** the glossary and the translation tables go into `data/english/`; release packages ship the already-built `-en` files, which needs the packaging exception P2.
- **M-Q6 (Q12).** **Decided:** a story file's `-en` version is served only when every line has English, machine lines included.
- **M-Q7. New names.** **Decided:** accept the engine's choice; the first spelling is fixed into the glossary automatically and reused everywhere after.

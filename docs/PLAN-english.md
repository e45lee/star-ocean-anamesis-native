# Plan: English text in the 3.7.0 client (draft for review)

A plan built on the findings in [english.md](english.md), for the user to review. Nothing here is implemented yet. Each step lists its effort (S = a day or less, M = a few days, L = a week or more), what it depends on, how it is proved and where it sits on the server-first rule ([AGENTS.md "Hard rules"](../AGENTS.md#hard-rules)).

Revision of 2026-10-06 (agent `english2`), at the user's request: **an option with a client change for English, plus a server that serves English assets with Japanese as the fallback for missing assets and voices.** The findings behind it are [english.md section 6](english.md#6-the-clients-own-language-switch), with experiment 3 (english.md 6.5; shots in `work/english/exp2/`). The plan now has three options and recommends C.

## The options

**A. Server only (the first draft).**
- The served master's `ja_` rows get English text in place.
- Edited story files replace the download's through a new CDN overlay.
- The client is unchanged, so every client of that server sees English.

**B. Client switch + `en_` rows.**
- The client is told its language and reads `en_` rows, falling back to `ja_` per message id.
- That takes three client sites: `CLanguage`, `StringDB::GetNativeString` and `StringDB::GetList`.
- The server adds `en_` rows to the one served master, and `-en` files for story and art.

**C. Client switch + per-language files (recommended).**
- The client is told its language: **one site**, `CLanguage::Current` = `en`.
- The client's own loader already tries `name-en.ext` before `name.ext` for every file: the master, story, layouts, images, font and voices (english.md 6.3).
- The server serves English as **new `-en` members** beside the Japanese files:
  - `sqlite/basmaster-en.sqlite3`: the served master with English in its `ja_` rows;
  - `Scenario/TS_*-en.msgp`;
  - `-en` images and layouts.
- StringDB is untouched: it keeps reading `ja_` rows, of the English files.
- A Japanese file is the fallback **per file**, made by the client. A Japanese row is the fallback **per row**, made by the server when it builds the `-en` master.

What experiment 3 showed with the one-site switch (english.md 6.5):
- **`-en` images** replaced the gacha banners.
- **A `-en` story file** played in English, through a session that passed.
- **A whole `-en` master** turned the home header English. Those labels come through `GetList`, and the same labels stayed Japanese with B's `en_` rows and only `GetNativeString` patched.
- **The pre-download data dialog** read English, through the port's asset overlay.

Coverage:

| | A: server only | B: switch + `en_` rows | C: switch + per-language files |
|---|---|---|---|
| UI and system text | yes | yes | yes |
| List screens through `tMessage` (`StringDB::GetList`, 122 call sites) | yes | only with the `GetList` patch | yes (run 3) |
| Story | overlay replaces `TS_*.msgp` (new CDN step) | `TS_*-en.msgp` as a superset (`ja_` + `en_` rows) | `TS_*-en.msgp` with English in the `ja_` rows |
| Images, baked `UI/*.csf` labels | overlay replaces the download's file | `-en` members | `-en` members |
| Font with accents | overlay `font.fpk` | `Font/etc2/font-en.fpk` | `Font/etc2/font-en.fpk` (the font load goes through the lookup) |
| Voices | n/a | `Voice_*-en.spk`, Japanese fallback; **no English voice data exists** | the same |
| Pre-download screens | no | with a port overlay of a built-in `-en` master that holds `en_` rows | with a port overlay of the built-in `-en` master (run 3's dialog) |
| The 14 hard-coded strings, word wrap | client change (E10) | the same | the same |
| Server texts (notice, gacha headings, present lines) | `--lang` | `--lang` | `--lang` |
| `soa-emu` | yes, as data | with a platform370 patch | with a platform370 patch |
| A real phone or Waydroid | yes | no: Japanese | no: Japanese |

Comparison:

| | A | B | C |
|---|---|---|---|
| **Client change** | none | 3 sites | **1 site** |
| **Risk** | the overlay re-fetch of replaced members is unproven | `GetList`'s per-message-id merge needs care (english.md 6.2) | the `-en` master path is proven only in the port so far (english.md 6.5, run 3) |
| **Extra download per client** (every client fetches every new member, english.md 6.3) | none extra | about 2.4 MB of master, plus the story and art files | **about 36 MB** for the second master, plus the story and art files; Japanese clients pay it too |
| **Server work** | a `ClientMaster` hook that replaces text, plus a new overlay CDN step | a hook that inserts rows, plus `-en` members (the stand-in step generalised) | the served-master pipeline gets a second output (its `ClientMaster` edits, then the English), plus `-en` members |
| **Reversible by the player** | no: a server restart and a master re-download | yes: restart without `--lang en`; nothing is downloaded again | yes, the same |
| **One server, mixed languages** | no | yes | yes |
| **Sessions and gates** | keep a Japanese server | unchanged (the Japanese client never opens `-en` files or `en_` rows) | unchanged |
| **Effort to first English UI** | S + S | S + M + S | **S + M** |

**Shared by all three:**
- E1, the English text table: Global by id, text memory, overrides, glyph folding and checks.
- E3, the token rewrites.
- E6, the server texts.
- E7, the layout pass.
- E8, the gap text.
- E9, the images.
- E10, the client extras.
- E11, the tests.

C and A produce the same English master data: A serves it as the master, C as `basmaster-en.sqlite3`. C and B share the `-en` member step (B4) and the client's `CLanguage` switch (B1).

## Recommendation

**C, with B's two StringDB sites as a follow-on only if the second master's 36 MB per client is unacceptable (Q9).**
- **C is the smallest client change.** One field is set; everything else is the client's own lookup.
- **C is non-destructive.** The Japanese files stay complete and untouched. A player switches back with a flag, one server serves both languages, and the sessions and gates keep running Japanese against the same CDN.
- **C has the fewest unknowns in StringDB.** `GetList`'s screens became English without touching it.
- **A stays as a mode** for clients that can't be patched (a real phone). Its master data is C's `-en` master served under the plain name.

## Steps (option C)

| Step | What | Effort | Depends on | Proof |
|---|---|---|---|---|
| **E1** | **English text table and coverage report**:<br>1. Global by id with the five filters;<br>2. text memory;<br>3. `data/english/overrides.tsv`.<br>Glyph folding and the checks (unknown tags, missing glyphs, printf specifiers). Output: per JP `message_id` the English and its source. | S | — | counts as english.md (19,145 by id, about 6,800 by memory); 0 bad rows; pytest |
| **B1** | **Client: the language code.** A third platform370 patch (`platform370/src/patch_370.cpp`, `Config::lang`), active in `soa` and `soa-emu`, with `--lang ja\|en` (default `ja`).<br>After `CLanguage::CLanguage` (ELF 0x13b4b18; `CGame::OnInitialize` builds it with 0x100 at 0x114256c) it sets `Current` (+4) to 1. `Default` (+0) stays 0x100; `Voice` (+8) stays the save's `BAS:VoiceLanguage`.<br>Logged in `docs/client-changes.md` ("Emulator mode" and a new entry). | S | — | a check that `CLanguage::Current()` is 1 with `--lang en` and 0x100 without; a `FileExistLanguage` probe in a selftest |
| **C1** | **Server: the English master as a `-en` member.** `make_served_master` (`server/src/cdn/served_master.cpp`) writes a second output.<br>1. Copy the served master **after** every `ClientMaster` hook (the event dates, Sphere 211, the tower rows, `--enable-events`), so both masters carry the same edits.<br>2. Write E1's English into its `ja_` rows' `text_value`.<br>3. Encrypt it AES-ADLD (encType 2) under `sqlite/basmaster-en.sqlite3`.<br>The server's own rules keep reading its Japanese master. Labels (a) Global, (d) filters and memory; `docs/server-rules.md` `#english`; `docs/client-changes.md` "Data overrides". | M | E1, C2 | `cdn/served-master-en` selftest: the `-en` master's rows equal the served master's except `text_value` of the filled rows; ids unchanged |
| **C2** | **Server: `-en` members on the CDN.** Generalise the stand-in step (`TreeBuilder::add_standins`, `server/src/cdn/tree.cpp`) to more roots. The generated root (the scratch dir) holds the `-en` master, story files and art: names the download doesn't have. They become new members as stand-ins do: version.bin entries, one Individual bundle each, a Bulk bundle, a new revision. Served only with the server's `--english` switch (Q11), so a Japanese-only server costs its clients nothing. | M | — | a `cdn/lang-members` selftest; **`soa-emu` with a `-en` master from soa-server's CDN only** (the pattern of `emulator/scripts/standin_fetch_test.sh`), showing the English header. Run 3 proved this only through the port's overlay |
| **E3** | Global tokens and composed fragments: `<NUM n>`/`<STR n>` → the JP row's specifiers, `<INSERT>` fixed, the `uimsg_remain_*` family reviewed. | S | E1 | E1's report: 0 token rows |
| **E6** | **Server texts** (notice page, gacha rate headings, present lines) follow `--lang`. In-process the port passes its own `--lang` to the server. | S | E1 | replay corpus lines |
| **C3** | **English story files.** For each `Scenario/TS_*.msgp` with enough English (Q12), generate `Scenario/TS_*-en.msgp`: the same rows, with English in `text_value` (real newlines; `<EMDASH>` → ―). ADLD XOR is keyed by the `-en` name. Served through C2. Covers EP1 (3,379 of 3,389 lines), `TS_3xxx` (782 of 882), `TS_5xxx` (891 of 941). | M | E1, E3, C2 | the campaign and tutorial sessions with `--lang en` show English story; every served row parses (`<player>`, `<font…>` only) |
| **C4** | **Proof: the story release path.** `StringDB::ReleaseParameter` frees the story rows by `strcmp` with the name `CEventScenario::Run` gave `SetAddLoadFileName`. Run 2 played one scene with a `-en` file and passed. Play several chapters in a row and watch memory and the next scene's text: a stale or leaked row set is the risk. | S | B1, C3 | a session over two or more story scenes |
| **E7** | **Layout pass.**<br>- Re-break the 459 master rows that lost their Japanese line breaks.<br>- **Story lines:** Global's breaks don't fit the 3.7.0 message window (run 2's `82-story.png`), so re-break every story line to the window's width with the font's advances.<br>- Pre-wrap new text.<br>- Short overrides for overflowing labels and buttons (`uimsg_chara_top_info`; "Return to Title Screen" in the data dialog, run 3). | M | C1, C3 | EN contact sheets with no clipped text on the listed screens |
| **B7** | **Voices.** No code: `BAS:VoiceLanguage` in `Game.xml` decides. 0 = always the Japanese (bare) pack, 1 = `-en` first, 256 (what the committed save holds) = follow `Current`. A port option `--voice-lang ja\|auto` would write it, as the sessions write `BAS:DownloadEpisodeFlag`. **No English voice data exists anywhere we have** (english.md 6.4), so the default is `ja`. | S | B1 | a `Voice_*` probe with each setting |
| **B8** | **Font.** `Font/etc2/font.fpk` goes through the lookup (english.md 6.3), so a `font-en.fpk` with accented letters and dashes would load under `--lang en`. It needs an fpk writer (ADLD, SLZ, ISF, an ETC2 page, the glyph table). Otherwise keep folding (E1). | M | C2 | a render of é — in a label |
| **B9** | **Pre-download screens.** Port-only: the asset overlay (`AssetManager`, `runtime/src/android/ndk.cpp`) carries a built-in `sqlite/basmaster-en.sqlite3`, and `builtin_data/UI/*-en.csf` for the baked labels. Run 3 showed the master part working. `soa-emu` wouldn't get this. | S | C1 | a fresh phone (`SOA_PHONE=none`) with `--lang en`: title and data dialog in English |
| **E8** | **Gap text** (Q2, Q3): import path for a translation table. | S + L | E1 | coverage report |
| **E9** | **Images and baked layouts** (Q4): our own English art and edited `UI/*.csf`, as `-en` members. | L | C2 | home and gacha shots |
| **E10** | **Client extras, only if wanted** (Q6): (a) the 14 hard-coded strings as new `master_text` ids, so they get English rows too; (b) automatic word wrap. Both behind `--lang`. | M each | B1 | NATIVE_TEST, EN shots |
| **E11** | **Tests.** Gates keep running Japanese. Add `home --lang en`, then `campaign` / `tutorial --lang en`, as a T2 entry with their own references; E1's report in T1. | S | C1 | `tools/gate.sh T2` |

Order:
1. E1 → B1 → C2 → C1 → E3 → E6: the UI in English, switchable per client.
2. C3 → C4: the story.
3. E7, then B7–B9 and E8–E10 after the user's answers.

**B's follow-on, if wanted (Q9):** patch `StringDB::GetNativeString` (ELF 0x16faaec) and `StringDB::GetList` (ELF 0x16fac78) to read `<code>_` rows with a per-message-id fallback to `ja_` (english.md 6.2). The server then adds `en_` rows to the one master instead of serving a second one, saving about 34 MB per client. Effort M. The scratch hook of `GetNativeString` in `work/english/exp2/lang_scratch.cpp` is a start; `GetList` must return one row per message id.

**A as a mode, if wanted (Q9):** `--lang-mode replace` serves C1's English master under the plain name, plus A's overlay for the story files. Effort S (master) + M (overlay).

## Questions for the user

Kept from the first draft:
- **Q1. Which content first?** The UI (E1, B1, C1, C2, E6), or the story (C3, C4)? Proposed: UI first.
- **Q2. The gaps:** leave them Japanese (mixed text), or fill them? If filled, by machine translation, marked as such in the coverage report and overridable?
- **Q3. Fan translations:** any to import (`soa_save/names_en.json`, fan story translations)?
- **Q4. Images:** our own English art for the text in images (home buttons, footer, banners, tutorial pages), or keep them Japanese?
- **Q6. Client extras:** the hard-coded strings (E10a) and word wrap (E10b), or pre-wrap only (E7)?
- **Q7. Global's older English for edited JP texts** (821 rows): take them, or leave them Japanese (proposed)?
- **Q8. Wording:** keep Global's terms ("Gems", "FOL", "Augment", "Transmute")?

New or changed:
- **Q5 (changed). The defaults:** client `--lang` defaults to `ja` (sessions, gates, current players unchanged). Should release packages default to `en`, or offer a launcher choice?
- **Q9. Which option?** C (one client site; a second 36 MB master that every client of an English-enabled server downloads), B (three client sites; 2.4 MB), or C now and B later? And should A's server-only mode be kept for unpatched clients (a real phone)?
- **Q10. Voice language default:** no English voice files exist. Default `--voice-lang ja` (always the Japanese voices; proposed), or `auto` (English voices if any ever appear)? If an English dub source exists (a Global 1.5.0 download), should we look for it?
- **Q11. Always serve English?** Should the CDN always carry the `-en` members, or only when the server runs with `--english`? Proposed: only with `--english`, so a Japanese-only server costs its clients nothing.
- **Q12. Mixed story lines:** EP2 has English for 453 of 8,428 lines. Serve a story file's `-en` version only when it is nearly complete (for example at least 90% of its lines, as the experiment did), and keep the rest Japanese?
- **Q13. Pre-download screens in English (B9)?** They are seen once per phone, and need a port-only built-in data overlay (no effect in `soa-emu`). Worth it?

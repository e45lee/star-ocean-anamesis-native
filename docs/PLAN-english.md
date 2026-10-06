# Plan: English text in the 3.7.0 client (draft for review)

A plan built on the findings in [english.md](english.md), for the user to review. Nothing here is implemented yet. Each step lists its effort (S = a day or less, M = a few days, L = a week or more), what it depends on, how it is proved and where it sits on the server-first rule ([AGENTS.md "Hard rules"](../AGENTS.md#hard-rules)).

Revision of 2026-10-06 (agent `english2`), at the user's request: **an option with a client change for English, plus a server that serves English assets with Japanese as the fallback for missing assets and voices.** The findings behind it are [english.md section 6](english.md#6-the-clients-own-language-switch). The plan now has two options and recommends a combination.

## The two options

**Option A, server only (the first draft).** The served master's `ja_` rows get English text in place, and edited copies of story files replace the download's through a CDN overlay. The client is unchanged.

**Option B, a client language switch with a bilingual server.** The client is told its language (`--lang en`). It reads `en_` rows and `name-en.ext` files first and falls back to `ja_` rows and `name.ext` files, per message id and per file. The server adds English beside the Japanese and never replaces it.

The client already has most of B (english.md 6.1–6.3):
- **Files.** `CLanguage` and `CGameResourceManager::FileExistLanguage` already look up `name-<code>.ext` before `name.ext`, for every direct file and for `Voice_*.spk`. The 3.7.0 client never uses this, because `CGame::OnInitialize` builds `CLanguage(0x100)`, the "no postfix" code.
- **Master rows.** Every `master_text` row's id is `CHash32("<lang>_<message_id>")`, as in Global's bilingual master. So `en_` rows can sit beside the `ja_` rows.
- **What is missing.** StringDB hard-codes `"ja"` at two sites, `GetNativeString` and `GetList`, and nothing sets the language.

What each option covers:

| | A: server only | B: client switch + bilingual server |
|---|---|---|
| UI and system text (`master_text`) | yes: `ja_` replaced in the served master | yes: `en_` rows added; per-id fallback to `ja_` |
| List screens built through `tMessage` (`StringDB::GetList`, 123 call sites) | yes | yes, once `GetList` is patched (otherwise those lists stay Japanese) |
| Story (`Scenario/TS_*.msgp`) | yes: overlay replaces the download's file (new CDN step, E4) | yes: new `TS_*-en.msgp` members through the existing stand-in path. The load path and its release by name are still to be proven (B6) |
| Images, `UI/*.csf` baked labels | overlay replaces the download's file (every client sees them) | new `-en` members; `ja` clients never open them |
| Voices | n/a: no English voice files exist | the switch exists (`Voice_*-en.spk` with the Japanese voice as the fallback), but **no English voice data exists** (english.md 6.4) |
| Font with accents | overlay `font.fpk` | `Font/etc2/font-en.fpk`, if the font load goes through `FileExistLanguage` (B8) |
| The 14 hard-coded strings | client change either way (E10a) | the same |
| Word wrap | pre-wrap (E7) or client change | the same |
| Pre-download screens (the APK's built-in master and UI) | not reachable | not by the server either. A port-only asset overlay could carry an English built-in master (B9) |
| Server texts (notice, gacha headings, present lines) | `--lang` | `--lang` (the server can't see the client's switch, except in-process) |
| `soa-emu` / a real phone | works, as data | `soa-emu`: with the same platform370 patch. A real phone or Waydroid without the patch sees Japanese |

Comparison:

| | A | B |
|---|---|---|
| **Client change** | none (until E10) | a platform370 patch at 3 sites. It is in `docs/client-changes.md` behind `--lang`, and is active in `soa` and `soa-emu` |
| **Effort to first English UI** | S+S (E1, E2) | S+S+M (E1, B1–B3) |
| **Effort to English story** | +M (E4 overlay, E5) | +S (B5, B6: stand-in path exists) |
| **Risk** | low for text. Medium for the overlay (re-fetch of a replaced member unproven) | patching StringDB at 2 sites. `GetList`'s per-message-id merge needs care (6.2); a bad merge shows the wrong language, never a key |
| **Mixed text** | per row | per row, the same |
| **Reversible by the player** | no: a server restart, a new master (the 35 MB download dialog) and story re-fetches | yes: restart the client without `--lang en`. The data is unchanged; nothing is downloaded again |
| **Several players, different languages, one server** | no: one master per server | yes for master text, story and assets. Server texts follow the server's `--lang` |
| **Sessions and gates** | keep `--lang ja`; English is a separate server mode | unchanged: the JP client ignores `en_` rows and `-en` members. A `--lang en` session is its own T2 entry |
| **Server rules that read Japanese text** | must read the unedited master (served copy only) | same; `ja_` rows are never touched |

**Shared by both:**
- E1, the English text table: Global by id, text memory, overrides, glyph folding and checks.
- E3, the token rewrites.
- E6, the server texts.
- E7, the layout pass and pre-wrap.
- E8, the gap text.
- E9, the images, made by us.
- E10, the client extras.
- E11, the tests.

Only the delivery differs: A writes `text_value` of `ja_` rows and replaces files, B adds `en_` rows and `-en` files.

## Recommendation

**Option B, with A kept as a fallback mode.**
- **B is non-destructive.** The Japanese data stays complete and untouched. A player switches back with a flag, and one server serves both languages. The sessions and gates keep running Japanese against the same CDN.
- **The fallback is the game's own design.** Per row and per file, the client keeps Japanese wherever English is missing.
- **The client change is small and well-bounded.** It covers the language code, the two StringDB sites, and nothing in the file loaders.
- **Story delivery is simpler than A's.** It reuses the stand-in route, which is already proven with the unmodified client (`emulator/scripts/standin_fetch_test.sh`). A needs a new overlay that replaces download members.

A stays possible for a client that can't be patched (a real phone or Waydroid). Its served-master hook is the same code as B2 with "replace" instead of "add", so it costs an S on top.

## Steps (Option B)

| Step | What | Effort | Depends on | Proof |
|---|---|---|---|---|
| **E1** | **English text table and coverage report**, unchanged from the first draft:<br>1. Global by id with the five filters;<br>2. text memory;<br>3. `data/english/overrides.tsv`.<br>Glyph folding and the checks (unknown tags, missing glyphs, printf specifiers). New check: the two `CHash32("en_" + id)` collisions (`item_coin_281_text_message` / `factor_message_10008`, `item_chip_cp0112_b03a_item_message` / `uimsg_gear_ax_30_25`, english.md 6.2) get no `en_` row, so both stay Japanese. | S | — | counts as english.md (19,145 by id, about 6,800 by memory); 0 bad rows; pytest |
| **B1** | **Client: the language code.** A third platform370 patch (`platform370/src/patch_370.cpp`, `Config::lang`), in `soa` and `soa-emu`, with `--lang ja\|en` (default `ja`). After `CLanguage::CLanguage` (ELF 0x13b4b18, built by `CGame::OnInitialize` at 0x114256c with 0x100) it sets `Current` (+4) to 1. `Default` (+0) stays 0x100, so the third lookup step is the bare name. `Voice` (+8) stays the save's `BAS:VoiceLanguage`. Logged in `docs/client-changes.md` ("Emulator mode" and a new entry). | S | — | the scratch experiment's hook (english.md 6.5); a NATIVE_TEST-style check that `CLanguage::Current()` is 1; the `FileExistLanguage` trace shows `-en` probes |
| **B2** | **Client: StringDB reads the current language with a per-id fallback.** Two sites, both patched in platform370:<br>1. `StringDB::GetNativeString` (ELF 0x16faaec): look up `CHash32("<code>_" + id)` through `pParameterFromHash`; on a miss, run the original (`ja_`).<br>2. `StringDB::GetList` (ELF 0x16fac78): query the `<code>_` ids first. Pass only the message ids that got no row to the original, so the output map holds one row per message id. `tMessage::SetMessageList` keys its map by message id and would otherwise keep whichever row came last.<br>No other reader of `master_text` exists (english.md 6.2). | M | B1 | experiment: an `en_` row shown, a missing one falls back to Japanese, not to its key; the `GetList` screens (item lists, gacha list, mission lists, the Other menu) in English; a differential test of `GetList` with `ja` (byte-identical map to the original) |
| **B3** | **Server: `en_` rows in the served master.** A `ClientMaster` hook, run **last** in the module order (after the tower and `--enable-events` rows), inserts E1's English as new rows: `id` = `CHash32("en_" + message_id)`, `lang` = `en`, the other columns copied from the `ja_` row. It never edits a `ja_` row. Always on, or under `--english`: the cost is about 2.4 MB of master (19,145 rows; english.md 6.5) and one master re-download. A JP client never reads the rows. Labels (a) Global, (d) filters and memory; `docs/server-rules.md` `#english`; `docs/client-changes.md` "Data overrides". | S | E1 | `cdn/served-master-en` selftest: `ja_` rows byte-identical to the unedited served master, `en_` ids unique and not colliding; `control/run.py home` passes with and without `--lang en` |
| **E3** | Global tokens and composed fragments: as the first draft (`<NUM n>`/`<STR n>` → the JP row's specifiers, `<INSERT>` fixed, the `uimsg_remain_*` family reviewed). | S | E1 | E1's report: 0 token rows |
| **B4** | **Server: `-en` members on the CDN.** Generalise the stand-in step (`TreeBuilder::add_standins`, `server/src/cdn/tree.cpp`) to a list of overlay roots. The new root (generated at start into the scratch dir) holds only names that don't exist in the download: `X-en.ext` beside the download's `X.ext`. They become new members exactly as stand-ins do: version.bin entries, one Individual bundle each, a Bulk bundle, and a new revision. **Open:** whether the `-en` members go into the Bulk bundle, which every client fetches at its data check (JP clients download unused bytes), or only into Individual bundles. `FileExistLanguage`'s status 1 ("in the download DB, not on disk") triggers an on-demand `RequestDownload` (english.md 6.3); to be proven. | M | — | a `cdn/lang-members` selftest (entries and bundles); `emulator/scripts/standin_fetch_test.sh` pattern with a `-en` member; experiment run 2 (english.md 6.5) |
| **B5** | **English story files.** For each `Scenario/TS_*.msgp` with English, generate `Scenario/TS_*-en.msgp` (ADLD XOR keyed by the `-en` name). It is a **superset**: all `ja_` rows plus `en_` rows (id `CHash32("en_" + message_id)`), because the `-en` file is loaded *instead of* the plain one. B2's per-id fallback keeps untranslated lines Japanese. Covers EP1 (3,379 of 3,389 lines), `TS_3xxx` (782 of 882), `TS_5xxx` (891 of 941). | M | E1, E3, B2, B4 | B6's proof, then the tutorial and campaign sessions with `--lang en` show English story |
| **B6** | **Proof: the story load path.** `CEventScenario::Run` hands the file's parameter name to `StringDB::SetAddLoadFileName`, and `StringDB::ReleaseParameter` releases by `strcmp` with that name. Prove these on a client with `--lang en`:<br>- that the TS file is loaded through `AddDirectFile` (so `-en` is found);<br>- that the `-en` name doesn't break the release by name (a leak or a stale cache is the risk).<br>If it fails, fall back to `en_` rows inside the plain `TS_*.msgp`, which needs A's overlay (E4). | S | B1, B4 | a campaign session with one `TS_1000-en.msgp`; the `FileExistLanguage` trace; memory stable over two chapters |
| **E6** | **Server texts** (notice page, gacha rate headings, present lines) follow the server's `--lang`. In-process the port passes its own `--lang` to the server. | S | E1 | replay corpus lines |
| **E7** | **Layout pass**: re-break the 459 rows, pre-wrap with font metrics, short overrides for overflowing labels; unchanged. | M | B3, B5 | EN contact sheets |
| **B7** | **Voices.** No code: the client's rule exists. `BAS:VoiceLanguage` in `Game.xml` decides: 0 = always the Japanese (bare) pack, 1 = `-en` first, 256 (what the committed save holds) = follow the text language. A port option `--voice-lang ja\|auto` would write it, as the sessions write `BAS:DownloadEpisodeFlag`. **No English voice data exists anywhere we have** (english.md 6.4), so the default is `ja`, and B7 is only the switch until a source turns up. | S | B1 | a `Voice_*` probe in the trace with each setting |
| **B8** | **Font.** If the trace shows `Font/etc2/font.fpk` going through `FileExistLanguage`, an English `font-en.fpk` with accented letters and dashes could ship as a `-en` member. It needs an fpk writer (ADLD, SLZ, ISF, an ETC2 page, the glyph table). Otherwise keep folding (E1). | M | B4 | a render of é — in a label |
| **B9** | **Pre-download screens** (title, terms, download dialog; the APK's built-in master and `builtin_data/UI`). Port-only: the asset layer (`AssetManager`, `runtime/src/android/ndk.cpp`) could serve an English built-in master (the APK's plus `en_` rows) or `builtin_data/UI/*-en.csf`. The stand-in overlay already merges into `builtin_data/`. Whether `-en` built-in files are found depends on `CGameResourceDownloader::IsBuildInData` (english.md 6.3). Seen once per phone, so it comes last. | M | B1, B2 | a fresh phone (`SOA_PHONE=none`) with `--lang en`: title and download dialog in English |
| **E8** | **Gap text** (Q2, Q3): import path for a translation table; unchanged. | S + L | E1 | coverage report |
| **E9** | **Images and baked layouts** (Q4): our own English art and edited `UI/*.csf`, now as `-en` members (B4) instead of replacements. | L | B4 | home and gacha shots |
| **E10** | **Client extras, only if wanted** (Q6): (a) the 14 hard-coded strings as new `master_text` ids, so they get `en_` rows too; (b) automatic word wrap. Both behind `--lang`. | M each | B1 | NATIVE_TEST, EN shots |
| **E11** | **Tests.** Gates keep running Japanese. Add `home --lang en`, then `tutorial` / `campaign --lang en`, as a T2 entry with their own references; E1's report in T1; a selftest that the B2 patch with `ja` is identical to the original (`GetNativeString`, `GetList`). | S | B2, B3 | `tools/gate.sh T2` |

Order:
1. E1 → B1 → B2 → B3 → E3 → E6: the UI in English, about 26,000 rows, switchable per client.
2. B4 → B6 → B5: the story.
3. E7, B7–B9, E8–E10 follow the user's answers.

**Option A as a mode** (if wanted, Q9): `--lang-mode replace` writes E1's English into the `ja_` rows of the served master (B3's hook in replace mode) and serves `TS_*.msgp` through an overlay (E4 of the first draft: `add_overlay()` in `tree.cpp`, md5/size in every manifest and version.bin, a new revision). It works for an unpatched client and a real phone. Effort S (master) + M (overlay).

## Questions for the user

Kept from the first draft:
- **Q1. Which content first?** The UI (E1, B1–B3, E6), or the story (B4–B6)? Proposed: UI first.
- **Q2. The gaps:** leave them Japanese (mixed text), or fill them? If filled, by machine translation, marked as such in the coverage report and overridable?
- **Q3. Fan translations:** any to import (`soa_save/names_en.json`, fan story translations)?
- **Q4. Images:** our own English art for the text in images (home buttons, footer, banners, tutorial pages), or keep them Japanese?
- **Q6. Client extras:** the hard-coded strings (E10a) and word wrap (E10b), or pre-wrap only (E7)?
- **Q7. Global's older English for edited JP texts** (821 rows): take them, or leave them Japanese (proposed)?
- **Q8. Wording:** keep Global's terms ("Gems", "FOL", "Augment", "Transmute")?

New or changed:
- **Q5 (changed). The defaults:** client `--lang` defaults to `ja` (sessions, gates, current players unchanged). Should release packages default to `en`, or ship a launcher choice?
- **Q9. Option B, A, or both?** Is the client change (a platform370 patch at 3 sites, active in `soa` and `soa-emu` only with `--lang en`) acceptable? Should the server-only replace mode also be kept, for unpatched clients and a real phone?
- **Q10. Voice language default:** no English voice files exist. Default `--voice-lang ja` (always the Japanese voices, proposed), or `auto` (English voices if any ever appear)? If an English dub source exists (a Global 1.5.0 download), should we look for it?
- **Q11. Always serve English?** Should the served master always carry the `en_` rows and the CDN the `-en` members (one server for both languages; JP clients download unused bytes, about 2.4 MB of master plus the story files)? Or only when the server runs with `--english`?
- **Q12. Mixed story lines:** EP2 has English for 453 of 8,428 lines. With per-id fallback a chapter would switch between English and Japanese line by line. Serve English for a story file only when it is (nearly) complete, e.g. at least 95% of its lines, and keep the other files Japanese?
- **Q13. Pre-download screens in English (B9)?** They are seen once per phone, and need a port-only built-in data overlay. Worth it?

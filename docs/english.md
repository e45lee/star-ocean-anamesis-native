# English text in the 3.7.0 client: where the text comes from, what English exists, how to deliver it

The experiment files (screenshots, the English-merged masters, font and string dumps) are in `work/english/` of the main checkout: local only, not committed (derived game data).

Investigation of 2026-10-06 (agent `english`), at the user's request: **how can translated English text get into the 3.7.0 client?** Nothing was changed in code or data; the plan built on these findings is [PLAN-english.md](PLAN-english.md). The official English is the Global master, described in [basmaster-gl.md](basmaster-gl.md); the Global voice files are in [global-voice-files.md](global-voice-files.md).

Ghidra addresses are ELF vaddr + 0x100000, as `tools/decomp_at.sh` takes them. Counts come from read-only queries over `data/basmaster-3.7.0.sqlite3`, `data/basmaster-gl.sqlite3`, the 3.7.0 download (`work/SOA-3.7.0-canonical-data.zip`), the 3.7.0 APK and `work/libSOA-3.7.0.so`. Each section ends with "How measured". Scratch files (scripts, renders, screenshots) are outside the repo in `/home/fish/.claude/jobs/ac4802d9/tmp/english-*` and are not committed.

## Summary

- **The client renders English.** Its one font, `Font/etc2/font.fpk`, is a bitmap atlas of 7,133 glyphs. It has all of ASCII with **proportional** advances, but **no accented letters and no em/en dash**: a missing glyph draws as `?`. None of Global's 34,317 English rows uses a missing glyph.
- **The client never wraps lines.** It breaks only at `\n`. A long English line runs off both sides of a dialog (experiment 2). 436 of the 2,632 label nodes shrink overflowing text to fit; the rest grow or overflow.
- **Almost all non-story text is in the master's `master_text`.** That is 66,945 `ja_` rows. Outside it, the master has no display text: only 6 Shift-JIS developer comments.
- **The served master is the delivery route, and it works without a client change.**
  - The server already edits the master the client downloads (`apply_client_master`).
  - A throwaway master with **19,145** English rows from Global, served through `--master`, ran the unchanged `home` session to PASS.
  - Its screenshots show English mixed with Japanese, cleanly rendered (experiment 1).
- **Story text is in 64 `Scenario/TS_*.msgp` files** (23,169 rows). Global English exists for 5,505 of them, nearly all of EP1. Serving edited copies needs one new CDN step, an overlay that wins over the download. That is server code, not a client change.
- **Official English covers 30% of the master text.** The id match gives 19,145 safe rows. Reusing English by identical Japanese text adds about 6,800 more. The 3.x features Global never had (Sphere 211, universe board, gear, favor, guide) have none.
- **Text that stays Japanese without more work:**
  - Images: about 1,000 `Image/` files and the `UI/` atlases, including the home buttons and footer.
  - About 400 labels baked into `UI/*.csf` layouts.
  - 14 hard-coded strings in `libSOA.so`, and the screens shown before the first download, which read the APK's built-in master (section 1.5).
  - The server's own texts (section 1.6).
  - Voices.
- **The client has its own language switch, unused in 3.7.0 (section 6, investigation 2).**
  - `CLanguage` makes every file load try `name-en.ext` before `name.ext`: master, story, layouts, images, font and voices. `CGame::OnInitialize` sets it to "no language" (0x100).
  - Setting it to `en` is a **one-site client change**. With per-language files served as new CDN members, it gave an English master (including the pre-download dialog), English story and replaced images, with Japanese as the per-file fallback (experiment 3).
  - StringDB hard-codes `ja` at two sites. Adding `en_` rows beside `ja_` needs both patched.
  - **No English voice data exists anywhere we have.**
- **Machine translation for the gaps (section 7).**
  - After Global's English, exact memory and a new **template memory** (Global's stat lines with new numbers, 92% exact on held-out pairs), 37,593 master rows (705k distinct JA characters) and 17,182 story lines (530k) remain. **EP2 has no official English at all.**
  - In a blind 310-row trial, an LLM with the glossary in the prompt (Claude Sonnet 5.5 / Opus 5.5) scored chrF 44 against Global's English, kept every specifier and tag and followed the glossary; the offline models (two NMT models, a 1.5B local LLM) scored 28–35 and broke terms and tokens.
  - A second trial (7.8) ran 12–31B local LLMs on this machine's GPU with the same prompt: **Gemma 4 31B (Apache-2.0, 17 GB at 4 bits) scored chrF 44.3, kept every token and followed the glossary in 81 of 85 rows: within noise of Claude Opus (44.4).** It needs about 9–11 hours for the whole gap with the GPU to itself (26 hours when other programs hold 7 GB of it); the faster Gemma 4 26B-A4B does it in 3–6 hours at chrF 43.8–44.3.
  - The proposed source of truth is a committed table keyed by `message_id` with a hash of the Japanese and per-row provenance (`machine`, `human`, `reviewed`); human edits always win, and the server builds the `-en` files from it without calling an engine.

## 1. Where the client's text comes from

| Source | Size | Japanese | Notes |
|---|---:|---:|---|
| Master `master_text` (`ja_` rows) | 66,945 rows | almost all | system, UI, names, skills, items, missions, profiles, help ([1.1](#11-the-master-master_text)) |
| Other master columns | — | 6 values | developer comments only (`master_partial_maintenance.comment`, `master_debug_param.comment`, Shift-JIS) |
| `Scenario/TS_*.msgp` | 64 files, 23,169 rows | 21,663 rows | story dialogue, StringDB rows like `master_text` ([1.2](#12-story-and-script-files)) |
| `Script/*.msgp` | 598 files | 45 files, 1,143 strings | StringDB keys; literal Japanese only in debug/sample scripts, plus 3 reachable name-plate values |
| `TalkScene/*.csf` | 577 files | 1 file, 10 strings | `EventBase.csf` placeholders (選択肢1-4, スキップしますか？, はい/いいえ) |
| `Parameter/*.msgp` | 1,935 files | 2 files | developer comments, not displayed |
| `UI/*.csf` layouts (download) | 276 files | 181 files, 1,043 labels | 495 unique; about 411 are not placeholders; 216 equal a `master_text` value ([1.3](#13-text-in-ui-layouts-and-images)) |
| APK `builtin_data/UI` | 21 files | 16 files, 94 labels | the pre-download screens (title, terms) |
| `Image/*.aif` | 7,029 files | about 1,000 | banners, gacha art, tutorial pages, tips thumbnails |
| `UI/` atlases | 276 atlases, 5,548 sprites | many | home buttons, footer, gacha top; the battle menu is mostly Latin already |
| `Movie/*.mp4` | 12 | logos only | no subtitles |
| `libSOA.so` .rodata | see [1.5](#15-hard-coded-strings) | | dialogs shown before or without the master |
| Server-sent text | see [1.6](#16-text-the-server-sends) | | login-bonus and present lines, notice page, error texts |
| Font | `Font/etc2/font.fpk` | — | glyph coverage, [3.1](#31-the-font) |

### 1.1 The master: `master_text`

- **One table holds the client's text.** It has 66,945 rows: `data_type` is `package` in 66,894 and NULL in 51. All rows have `category_id_label` `system` (66,878) or NULL. Every other master column with kana or kanji is a developer comment (6 values in total).
- **The client reads only the `ja_` rows.** `StringDB::GetNativeString` (Ghidra 0x17faaec) looks a row up by `CHash32(Format("%s_%s", "ja", message_id))`, with `"ja"` hard-coded. On a miss it returns the key itself, so a missing row shows its message_id on screen.
  - `StringDB::Get` (0x17faa2c) turns the two characters `\n` into a newline. `CMessagePrint::Initialize` (0x1458534) does the same for the message window.
  - The `lang` column is never read ([basmaster-gl.md 5(b)](basmaster-gl.md#b-an-english-mode-for-the-370-client)). English therefore has to replace `text_value` of the `ja_` rows and keep their ids.
- **Lazy loading.** The client reads rows on demand. `StringDBEelement::Initialize` (0x17fd0f0) loads `message_id`, `text_value`, `text_kana` and `data_type`. `text_kana` (5,101 non-empty rows) was not found displayed or used for sorting.
- **printf specifiers.** 205 JP rows contain one: `%d` (130), `%s` (85), `%u` (25), `%02d`, `%2d`, `%5.2f`, `%.5f`. A replacement must keep the same specifiers in the same order, or the client's printf reads the wrong arguments.
- **No length limits.** The column is SQLite `TEXT`. The only limits are on screen (section 3).

How measured: a scan of every TEXT column of every table for `[぀-ヿ一-鿿]`; `select data_type, count(*) from master_text group by 1`. The decompiles are listed in section 3.

### 1.2 Story and script files

- **Scenario.** Each file is `{"master_text": [{message_id, lang: "ja", text_value, category_id_label: "TS_x", data_type: "package", id}]}`, using real newlines and ADLD XOR (encType 1). There are 64 files and 23,169 rows, 21,663 of them Japanese (about 659k characters).
  - There is no SLZ layer: the file is ADLD XOR over plain msgpack (`soa_save.script.load` = `adld.decode` then `msgpack.unpackb`; `soa_save.script.encrypt` writes it back). The `UI/*.csf` layouts and the font do have an SLZ (zstd) layer.
  - `CEventScenario::ParseMessage` (0x142fcc8) reads them through StringDB by message_id.
  - Where the files live: 40 in the Bulk/Individual manifests; `TS_1040`–`TS_1100` in episode pack EP1, `TS_2010`–`TS_2110` in EP2 and `TS_6010`–`TS_6060` in EP3.
- **Script.** `Script/*.msgp` holds StringDB keys only: 22,560 speech commands and 94 menus. Speakers are model codes, named from `master_text`. Literal Japanese is limited to the 9991/9997/9998/9999 debug and sample scripts, `6035_220` ("これは削除イベント") and three `p6='ギディオン'` name plates in `9996_015`. The scripts therefore need no translation, except those three name plates.
- **Inline tags.** `ParseMessage` expands `<player>` and splits at `fontcolor`, `fontsize` and `/font`, ignoring spaces inside the tag. The tag lookup at ELF 0x1330c6c reads through the map's result with no null check, so an unknown tag (Global's `<EMDASH>`, `<NUM n>`…) most likely crashes. This was read from the disassembly, not run.

How measured: decoding ADLD, then SLZ, then ISF, then msgpack for each file (`soa_save.adld`, `soa_save.script.load_texts`); the manifests' `ep_data`.

### 1.3 Text in UI layouts and images

- **`UI/*.csf` layouts.** These are Cocos node trees: 2,632 `TextObjectData` labels, 0 `TextBMFontObjectData` and 1 `TextFieldObjectData` across 853 UI and TalkScene files.
  - 1,043 label values are Japanese, 495 of them unique and about 411 not placeholders.
  - 216 of those 411 equal a JP `master_text` value. The code probably overwrites those labels from StringDB.
  - The rest are fixed in the layout, for example 今日は表示しない and the help paragraphs of `config1`. The files with the most are `config1` (56), `common_resource` (46), `character_status` (36), `sort2` (30) and `pausemenu` (20).
  - Changing them means serving edited `.csf` members (the overlay of [4.2](#42-story-files-a-cdn-overlay)).
- **APK `builtin_data/UI`.** These 21 files are the screens shown before the first download (`title_logo`, `title_dialog1/3/4`: terms of service, the minors notice). All 20 that also exist in the download differ from the download's copy. Which copy the client loads after the download was not established.
- **Images.** About 1,000 `Image/` files carry Japanese text:

  | Kind | Files |
  |---|---:|
  | Dated gacha, event and campaign art (`YYYYMMDD_*`) | 499 |
  | `banner_*` | 163 |
  | `tips_th_*` | 118 |
  | `tuto_pic*` (dense tutorial paragraphs) | 75 |
  | `pickup_img_*` | 62 |
  | `ticketgacha*` and rarity labels | 43 |
  | `btn_planet` | 19 |
  | other | about 20 |

  The `UI/` atlases hold 5,548 sprites. `home.csf` and `gacha_top.csf` are full of Japanese buttons (イベント, ミッション, スフィア211, the footer's ホーム…その他, キャラガチャ). `battlemenu.csf` is almost all Latin already. `Movie/` and `title_logo` hold logos only. `Effect/` couldn't be decoded with `aif2png`; its names suggest no text.
- **Global's images are not in hand.** Global swapped art under the **same file names** on its own CDN: 89 of its 901 `master_banner.image` names exist in the JP download. It didn't use `CLanguage::PostfixLanguageCodeFilepath`, the `name-<code>.ext` mechanism, which is inactive in 3.7.0. No Global image, script or APK is in the repo or `work/`. The only Global file is the master DB.

How measured: the decoded node trees (`TextObjectData` `LabelText` / `ButtonText`); file-name categories, with samples rendered by `build/tools/aif2png` (sheets in `work/english/assets/sheet_*.png`).

### 1.4 What English exists

See [basmaster-gl.md section 4](basmaster-gl.md#4-text) for the full analysis. The numbers that matter here:

| | Rows |
|---|---:|
| JP 3.7.0 `master_text` | 66,945 |
| … message_id not in Global's master (3.x content, `Asset*`, `Guide*`, Sphere 211, universe, gear, favor…) | 30,560 |
| … in Global but untranslated (`en` has kana or equals `ja`) | 15,980 |
| … language-neutral (`en` = `ja`, no kana) | 319 |
| … English, but Global's `ja` is an older JP text (`gl_ja_differs`) | 821 |
| … English with a Global-only token (`<NUM>`, `<STR>`, `<INSERT>`, `<EMDASH>`) | 119 |
| … English whose printf specifiers differ from JP's | 1 |
| **… English, safe to merge by id** | **19,145** (28.6%) |
| Not merged by id, but the identical JP text has a safe English elsewhere (text memory) | 6,845 (1,761 of them with more than one English variant) |
| Scenario rows with English ([basmaster-gl.md](basmaster-gl.md#coverage-of-jp-370-by-official-english)) | 5,505 of 23,169 (EP1 3,379 of 3,389; `TS_3xxx` 782 of 882; `TS_5xxx` 891 of 941; EP2 453 of 8,428; EP3 and later events 0) |

- **Why 19,145 and not 19,265.** basmaster-gl.md counts 19,265 rows where Global `ja` = JP `ja`. This filter also drops the 119 rows with Global tokens and the one specifier mismatch.
  - The specifier test is `%[-+#0]*\d*(?:\.\d+)?(?:ll|l|h)?[dusfxXc]`, compared as ordered lists.
  - A looser regex that allows a space flag counted 1,604 "mismatches", because it read `50% f…` as a specifier. That count is wrong.
- **Text memory matters for the UI.** The 3.7.0 menus often use newer message_ids that Global never translated, for the same Japanese that Global did translate under another id. Examples:
  - The character menu's パーティ編成 is `uimsg_party_edit`, which is untranslated in Global, while `uimsg_chara_party_name` = "Edit Party".
  - 武器カスタム and 素材合成 are untranslated in Global under all their ids.
  - エクシードコネクト and ユニバースボード are 3.x features with no Global row.
- **Prefixes of the 19,145 merged rows:** `seed` 3,904, `message` 2,783, `factor` 2,612, `name` 1,626, `cp` 1,461, `item` 1,457, `talentName` 1,016, `AttackName` 1,015, `uimsg` 723, `AttackExplainName` 460.
- **Prefixes of the 30,560 rows Global lacks:** `seed` 6,327, `message` 2,789, `factor` 2,723, `Asset` 2,542, `item` 2,507, `cp` 1,980, `name` 1,907, `uimsg` 1,796, `talentName` 1,417, `Guide` 1,318.
- **Global English is already broken into lines.** Global's translators broke lines with `\n` at about 41 characters (p90), so most rows fit a Japanese-sized box. Their line breaks differ from the Japanese ones: 3,962 merged rows have a `\n`, against 2,402 of their Japanese originals. But 459 merged rows lost the line breaks their Japanese had, and those overflow; see section 3.2.
- **Fan translations** are out of scope here. They are an option if the user supplies them (PLAN-english.md, question Q3).

How measured: `work/english/exp/merge.py`, which builds the experiment's master (filters below), plus the bucket query in the same directory's notes. The text memory maps each Global `ja` to its safe English and looks up every JP row the id merge didn't fill.

### 1.5 Hard-coded strings

- **`libSOA.so` has almost no hard-coded Japanese.** Its `.rodata` has 14 real Japanese strings (about 514 bytes); `.data`, `.data.rel.ro` and `.text` have none. The text the client shows by id instead:
  - 1,687 distinct ASCII strings in the lib are `master_text` message_ids (`cp0003_tutor_*`, `uimsg_*`, `sys_*`, `error_message_text_*`);
  - 12 more message_ids are built with format strings (`uimsg_%s_name`, `uimsg_item_confirmation_%d`).

  The visible literals:

  | ELF vaddr | String | Function | Use |
  |---|---|---|---|
  | 0x271424b | 空き容量が不足しています。\n容量を確保して再起動してください。 | `CErrorHandlerWrap::StrageShort` | storage-full dialog |
  | 0x282fb50 | 空き容量が不足しています。\n%dMBの空きが必要です。 | `CGameDataDownloadError::Progress` | download error dialog |
  | 0x282fb46 | 閉じる | `CGameDataDownloadError::Initialize` | its button |
  | 0x272d97e | プレイヤー用ダミーネーム | `CPlayerInfo::Initialize` | default player name |
  | 0x276ab5a | 変更するホームマスコットを選択してください。 | `CMascotSelectDialog::Open` | dialog |
  | 0x2791891 | 3Dモデル表示 | `CDetailDialog_Other::Start` | button |
  | 0x27927cb | LV%d習得 | `CDetailDialog_Character::SetBattleSkillParam2` and 2 more | format |
  | 0x2816fb1 | 装備の入れ替えを行います\nよろしいですか？ | `CPartyCompositionWeaponList::ReturnEquipHome` | confirmation |
  | 0x283adb6 / 0x283adc6 | フィルター / 並び替え | `CSortDialogWrapper::StartDialogFromProperty` | sort dialog titles |
  | 0x27bc5b7 | ？？？ | `CItemAlchemyPotal::InitializePotal` | unknown item |

  The rest are placeholders: ああああ…, ０１２３４５６７８９ (scene preload), and an unreferenced ￥. None is compared with anything.
- **The literals can't be patched in place.** clang copies the tail bytes of short literals into instructions: 閉じる's last byte, a `movk` for 並び替え at 0x1d4f2d8, and the dummy name in `CPlayerInfo::Initialize`. Rewriting `.rodata` alone would leave mixed bytes, so these need function-level changes.
- **The pre-download screens read the APK's built-in master.** Until the first download the client reads `assets/builtin_data/sqlite/basmaster.sqlite3`, whose `master_text` has 66,654 of the 66,945 ids. So the title, network-error, maintenance, service-end and 販売停止 dialogs (`uimsg_service_end_dialog`, `uimsg_osusume_not_buy_end_dialog`) come from that master on a fresh phone, and from the served master afterwards.
  - The built-in UI layouts are client files too: the terms dialog `title_dialog1`, the download dialog `title_dialog3` (ゲームデータをダウンロードします。…, 標準版/高画質版), name entry `title_dialog4`, 未成年の方へ and 初期化中….
  - The server can't reach any of these; only an APK change or a client hook could. They show once, before the first download.
- **Java.** `classes.dex` has no Japanese. `resources.arsc` has 25 strings (Play Services / AdMob boilerplate, the notification channel 通知). None of them shows in the port.
- **The port's own UI** (`runtime/`, `port/`, `platform370/`, `emulator/`, `webview/`) shows no Japanese literals. The only ones are tests, comments and the webview's kinsoku table, `webview/src/text_ja.cpp`.

How measured: valid UTF-8 runs with kana or kanji over every section of the lib (lief), with xrefs from the decompiles (`work/decomp/eng_vis*.resolved.c`); `aapt`-style dumps of the APK; `git grep` over the port's sources.

### 1.6 Text the server sends

Responses carry master ids, not text, with these exceptions:

- **The notice board page** (お知らせ, `server/src/api/player/notice.cpp`, about 12 lines) is the server's own HTML (`<html lang="ja">`). It has the headings 【お知らせ】, このゲームはローカルサーバーで動作しています。, 日時, イベントカレンダー, ■ 開催中のイベント, ほか N 件, ・なし, ■ ログインボーナス, N日目 and ■ プレゼントBOX: N 件. Event and bonus names come from `master_text` (`ext::text`). The page is rendered by litehtml ([webview.md](webview.md)), with a label fallback in `port/src/native/ui/webview_local.cpp`. It is ours, so it can be English with any font.
- **Gacha rate dialog headings** (`server/src/master/gacha_pools.cpp`, 4 lines): ★提供割合 %.5f%%, レアリティー別提供割合, 一般提供割合 and 10連ガチャ特典枠.
- **Present box lines** are composed by `format_present()` from the master templates `Present_box_1/2/6` and `Present_favor_1`, plus names: login bonus, premium and favor bonuses, world boss, rental. Two things follow:
  - They are **stored in the player's state** when granted, so a switch to English leaves the existing lines Japanese.
  - The server reads its own Japanese master, so they come out Japanese (1日目ログインボーナス in experiment 1). An English mode would compose them from the English texts.
- **Text used as a key, server side:** `kDefaultEventKeywords` (水着,夏,サマー,!福袋; `server/include/soaserver/config.h`) matches `master_text` values to pick the events `--enable-events` opens. This is why English must go only into the **served** master, never the server's.

How measured: `git grep -nP '[\x{3040}-\x{30ff}\x{4e00}-\x{9fff}]' server/src` (64 lines in 41 files, mostly tests and comments), then reading each hit; `port/fakeapi/responses/*.msgp` has no Japanese.

## 2. Experiments

Both experiments used the unchanged 3.7.0 client (the main checkout's `build/port/soa`) and the standard `home` session (`control/run.py home`), run through a wrapper that adds `--master FILE`. Both ran in the slot pool on the shared phone. The client downloaded the changed master (the 35 MB dialog, `00-download-dialog.png`) and the session passed: "PASS: every home destination reached".

**Experiment 1: 19,145 Global English rows.** The master was `data/basmaster-3.7.0.sqlite3` with `text_value` of each `ja_` row replaced by Global's `en` under these filters:
1. The message_id is in Global's master.
2. The `en` value has no kana or kanji and differs from Global's `ja`.
3. Global's `ja` equals JP 3.7.0's `ja`.
4. No Global-only token.
5. The same printf specifiers in the same order.

Shots are in `work/english/exp/home-out/shots/`:

| Shot | What it shows |
|---|---|
| `04-home.png` | The header reads "Stamina", "Next", "Gems", "FOL", "Rank" and the title "Anamnesis Debut", all English. The home buttons, the footer and 会話モード stay Japanese: they are images. |
| `26-achievements.png` | "Achievements", "Reward: 500 gems", "Progress" and "Close" in English, beside untranslated 3.x achievements (スフィア週間チャレンジ). **Composition problem:** "Time Left  Left:2d". JP composes 残り時間 (`uimsg_time_limit`) with あと (`uimsg_remain_base`) + 2日; Global translated each fragment for its own layout, so the English pair repeats "Left". |
| `24-titles.png` | Titles and their conditions all English ("Fledgling Hunter", "Defeat 1,000 Monsters"); tabs Japanese (バトル/シナリオ/育成). |
| `30-character.png` | **Overflow:** the header line "Enhance characters and organize a…" (`uimsg_chara_top_info`) runs off the right edge: no shrink and no wrap. Most menu buttons stay Japanese (`uimsg_party_edit` and others untranslated in Global, or 3.x features); "Limit Break" is English. |
| `31-item.png`, `34-other.png` | Item and Other menus mostly English ("View Items Held", "Enhance", "Transmute", "Sell Items"; "Settings", "Help", "Official Forums", "Change Player Name"). 武器カスタム and 素材合成 stay Japanese. "Official Forums" is Global's wording for a link that 3.7.0 points elsewhere. |
| `03-login-bonus.png` | "Gems ×500" from the master; the line 1日目ログインボーナス is the **server's** text; the LOGIN BONUS logo is an image (English with a Japanese subtitle). |
| `29-stamina.png` | A JP-only dialog (no Global row) between English buttons. |

The English rows draw cleanly. The proportional Latin glyphs sit on the same baseline as the Japanese, with no `?` and no crash, through every home destination.

**Experiment 2: a long line.** Experiment 1's master, plus `uimsg_full_stamina` set to a 170-character English sentence without `\n`. In `work/english/exp/wrap-out/shots/29-stamina.png` the sentence is **one line, centred, cut off at both window edges**. That confirms the decompile: no automatic wrap, and no shrink in this dialog.

The scripts and masters are in `work/english/exp/`: `merge.py`, `basmaster-en.sqlite3`, `basmaster-wrap.sqlite3`, and the `soa-en` / `soa-wrap` wrappers.

## 3. Rendering English: font, line breaks, markup

### 3.1 The font

- **Format.** `Font/etc2/font.fpk` is the only font. The APK copy is identical to the download's. It is packed as ADLD XOR (key `CHash32("Font/etc2/font.fpk")`), then SLZ codec 7 (zstd), then an ISF container that holds `fontData.bin` and `font_0.aif`.
- **Atlas.** One 2048×2048 ETC2 page. Glyphs are white on alpha; colour comes from the vertex colour.
- **Glyph table.** `fontData.bin` has a header (u32 24, u32 24, u32 7133), then 7,133 BMFont-style records of 40 bytes: id, x, y, w, h, xoff, yoff, xadvance, page, chnl.
- **Loader.** `CBitmapFontManager::RegistryFont` (around 0x1f649xx) reads only the low 16 bits of the id, so the font covers the BMP only. It registers `?` (0x3f) as the fallback glyph.
- **Text layout.** `TTextCompositor<Utf8>::ComposeString_<DirectAofText::CharPrinter>` (0x1f796dc) uses the fallback for every missing code point.
- **Coverage.** The set is roughly JIS X 0208:

  | Range | Glyphs |
  |---|---|
  | ASCII 0x20–0x7E | all 95 |
  | Latin-1 | 15 symbols (¡ ¢ £ ¤ ¥ ¦ § ¨ © ° ± ´ ¶ × ÷); **no accented letters** |
  | Greek / Cyrillic | 48 / 66 |
  | General Punctuation | ‐ ― ‘ ’ “ ” † ‡ ‥ … ‰ ′ ″ ※ |
  | Kana | 177 |
  | CJK ideographs | 6,360 |
  | Full-width and half-width forms | 163 |

  **Missing:** é ï ü ñ (every accented letter), the em dash U+2014, the en dash U+2013, •, ·, ™, ®, €. Global's English avoids all of them; `<EMDASH>` is a token, see 3.3. Translations written fresh, by hand or by machine, must be folded to the covered set: é → e, — → ― (U+2015), and so on.
- **Advances are proportional.** Glyphs are 24 px, scaled by the label's FontSize / 24, plus the label's letter spacing.
  - Sample advances: i and l 7, a 18, digits 21, m 26, W 27, space 12.
  - Every Japanese glyph advances 24.
  - The curly quotes ’ “ ” are half-width cells with the glyph at the left, so "you’re" shows a small gap. ASCII `'` and `"` look better.
- **No other text source.** No system font is used: the only JNI text is the soft-keyboard EditText, and `runtime/src/app/text_overlay.cpp` draws only the port's own keyboard box.
- **Proof:** `work/english/font/sample_gl_story.png` renders a Global English story line in the game font, with é ï – — drawn as `?`. The atlas and ASCII renders are in the same directory.

### 3.2 Line breaks, box widths, shrink

- **No wrap.** `ComposeString_` acts only on `\n`, `\t` (tab stops) and control characters. It never tests the width, never breaks at spaces or between characters, and has no kinsoku table. Experiment 2 shows the result.
- **Labels.** `CCocosLabel::DrawSelf` (0x1faca74) measures the text (`CDirectAofTextRenderer::CalcStringRect`) and aligns each `\n` line when the label's HorizontalAlignment is set.
  - **Auto-shrink:** when the label has `IsCustomSize` (+0x280, read by `Read_TextObjectData` 0x1fd5e8c) and +0x282 (default 1), overflowing text is scaled uniformly by min(boxW/textW, boxH/textH). That is 436 of 2,632 label nodes.
  - Every other label takes the text's size, so a long text overflows its neighbours. There is no clipping and no ellipsis.
- **Message window.** `Behavior_TalkText::UpdateFont` (0x1954818) and `Behavior_TalkText2::UpdateFont` (0x1954dc4) reveal the text character by character with `SubStrUTF8`. `CEventScenarioMessageWindow::Append` (0x145df78) measures only to place segments. Neither wraps.
- **How much wider English is.** For each row, compare the widest line in pixels, measured with the font's advances.
  - Over the 19,145 merged rows the English line is wider than the Japanese in 15,938 rows: more than 1.25× in 11,725, more than 1.5× in 6,754, more than 2× in 2,135.
  - The prefixes with the most rows above 1.25×: `seed` 2,523, `message` 2,218, `name` 1,359, `factor` 1,224, `talentName` 886, `item` 874, `cp` 682, `uimsg` 460.
  - Over all of Global's English, the widest line is 1.45× the Japanese at p50 and 2.18× at p90.
  - Widest-line pixels: Global English story p50 425, p90 624, p99 876; JP 3.7.0 master p50 325, p90 548, p99 836.
  - Global's 1.5.0 client may have had wider boxes or more shrinking labels; its layouts are not in hand.
  - A wider line overflows only where the box has no shrink and no spare room, so these counts are an upper bound on visible problems. The per-screen box widths have not been measured.

### 3.3 Markup and formatting codes

| Where | Codes the 3.7.0 client understands | Code |
|---|---|---|
| UI labels in tag mode | `<font color=red\|blue\|green\|black\|yellow\|light-blue>…</font>` | `CUIUtility::SetLabelTextTag` (0x1ef620c, 20 call sites) sets +0x281; `DrawSelf` matches `<.*?>.*?</font>`, `<(.+)>(.+)(</font>)`, `(.+)(=)(.+)`; `TagedText::SetColor` (0x1fb3054); `Framework::Cocos::TextTagParse` (around 0x1fab9xx–0x1fac4xx) strips `<…>` unless the `<` is backslash-escaped |
| UI labels not in tag mode | none: tags print as text | |
| Story (`ParseMessage` 0x142fcc8) | `<player>`, `<fontcolor=…>`, `<fontsize=…>`, `</font>` | an unknown tag likely null-dereferences (ELF 0x1330c6c); a tag with no `>` asserts "Unsolved tag" |
| Everywhere | printf specifiers, filled by the calling code | |
| Ruby / furigana | none | `text_kana` is not displayed |

- **Global-only tokens, which 3.7.0 has no code for:**
  - `<EMDASH>` occurs 223 times. Replace it with ― U+2015, which the font has.
  - `<NUM n>` (55 times) and `<STR n>` (31 times) need rewriting as the JP row's printf specifiers in JP's argument order. For example, Global's `Present_box_1` "Day <NUM 2> <STR 1>" becomes "Day %2$d…". **A reordered row needs rewording:** the port's printf (`runtime/src/hle/format.cpp`) logs "positional printf argument not supported" for `%2$d`, and a real phone's bionic printf was not checked either.
  - `<INSERT n>singular/plural</INSERT>` (13 times) needs one fixed form.
- **Plain text, not markup:** Global's `[G]`, `[R]`, `[Blue]`, `[Crimson]`, `[Hard]` (chip and coral colour names, difficulty).

### 3.4 Text used as keys

- **StringDB keys rows by message_id, not by text.** No comparison or sort by `text_value` or `text_kana` was found (`StringDB::GetList` has 2 callers, `tMessage` / `tMessageCache::SetMessageList`; a quick look only).
- **Sorting.** Lists sort by numeric columns such as `sort_name_idx`, which are precomputed in Japanese order. With English names the name sort stays in Japanese order. That is cosmetic.
- **Missing rows show their key.** A missing `ja_` row shows the message_id, so an English mode must never delete rows.

## 4. Delivery, server-first

### 4.1 Master texts: a `ClientMaster` hook

The mechanism exists. `ext::add_client_master(fn)` hooks run in `server::apply_client_master` (`server/src/core/server.cpp`) on the copy of the master the CDN serves, through `make_served_master` (`server/src/cdn/served_master.cpp`). Both server modes serve it: the in-process CDN for `soa`, and soa-server's HTTP CDN for `soa-emu` and `soa --server`.

An English module would add one hook:
- It attaches a text source: Global's master, or an English text table we keep.
- It runs `update master_text set text_value = ? where id = ?` on the served copy only, so the server's own rules keep reading the Japanese master.

Experiment 1 used `--master`, which replaced the server's master too. That is fine for an experiment; the real feature must not do it.

Consequences:
- **A new master to download.** Any change to the served master makes every client download it again: the 35 MB dialog, which the sessions already answer. A pre-downloaded shared phone in English would be a separate phone (`scripts/make-phone-370.sh --out`), or sessions accept the download.
- **Labels.** Each rule gets a label: (a) for Global's official text, (d) for our choices (the filters, the text memory, the token rewrites, the glyph folding). Each is documented in `docs/server-rules.md` and listed under "Data overrides" in `docs/client-changes.md`, as the other master edits are.
- **A switch.** For example `--lang en|ja`, a `ServerConfig` flag defined once for `soa` and `soa-server` (`server/include/soaserver/cli.h`; settings are flags, not environment variables).
  - Per server, not per player: one CDN serves one master to every client.
  - A per-player language would need per-player master URLs (Login's `MasterPath` / `r_ver`), and no 3.7.0 reader of `MasterPath` was found.
- **Mixing is the default outcome.** Rows without English keep their Japanese, so English and Japanese sit side by side (experiment 1).

### 4.2 Story files: a CDN overlay

- **Why stand-ins can't do it.** Stand-ins (`standin-assets/`) are only for names the download lacks. `TreeBuilder::add_standins` skips a name already in `version.bin`. Replacing `Scenario/TS_1000.msgp` therefore needs a new build step in `server/src/cdn/tree.cpp`, sketched below. It is server code; the client is unchanged.
  1. `add_overlay()` after `add_standins`: for each file of the overlay directory whose name is in `version.bin`, set `t->overlay_[rel]` so the overlay wins in `member_of`. Record its plaintext SHA-1, plaintext size, ADLD size and `e`.
  2. `collect_bundles`: set that member's `md5` and `size` in every manifest that lists it (Bulk, Individual, ep1–3), as it does for `kMasterName`.
  3. `write_version_bin`: the member's `md5`, `size` and `time`, as for the master.
  4. `renew_ids`: a different revision while an overlay is active.
  5. `cdn::Options` (`server/include/soaserver/cdn.h`) and `options_from_config`: the overlay directory. Both server modes mount the same Tree.
- **Would the client fetch the replacement?** `CVerifyTask::ProgressManifestCheck` (ELF 0x17e4418) compares the manifest member's `md5` and `e` with the stored `CAssetInfo` and fetches on a mismatch. `ProgressServerManifestCheck` (ELF 0x17e2b68) reads the server manifests when `SetServerAssetRevision` (ELF 0x17ddfe4) sees a new `r_ver`. So a phone that already has the data would likely re-fetch the changed bundle. **This is not yet proven.** A session on a copy of the shared phone with one changed `TS_1000` should see `I/9d6f29c1/5637558c.bin` requested.
- **Episode packs.** EP1–EP3 files are fetched only for the packs flagged in `BAS:DownloadEpisodeFlag`. The sessions use 0 unless `SOA_EPISODE_PACKS=1`, and re-checking an already-downloaded pack is untested.
- **Can the server write the files? Yes.**
  - Every Scenario, Script, UI, Image and TalkScene member is ADLD XOR, encType 1. `adld::encrypt(name, plain, adld::kXor)` (`common/include/soa/adld.h`, tests `cdn/adld-roundtrip` and `soa_codec_tests`) and `soa_save.adld.encode` (`soa_save.script.encrypt`) produce it.
  - The overlay can hold ADLD files, or plaintext that the server encrypts at build time, as `serve_master` does.
  - The English Scenario rows replace `text_value` only: same `id`, same `message_id`, `lang` left `ja`, `\n` turned into real newlines.
  - **Generation, not files in git.** The edited files are the game's own files with our text in them, so the server should generate them at startup from the download plus an English text table, as it does for the served master, rather than shipping them.
- **The same overlay serves the rest.** It also serves edited `UI/*.csf` layouts (baked labels) and English images that replace existing ones (banners, the home and footer atlases). The images would be ours: made-up replacements like the stand-ins, since Global's art is lost.

### 4.3 Hard-coded strings, pre-download screens, font, word wrap

- **Hard-coded strings.** These are the 14 literals of section 1.5, and no server data reaches them. Because clang copied parts of them into instructions, the route is a native per function: each of the 10 functions calls `SetMessage` / `SetText` with an English string, or with a new StringDB id that the served master carries. That is a client change, logged in `docs/client-changes.md` behind the same `--lang` switch. It is low value: storage errors, a download error, the sort dialog title, a confirmation, a button.
- **The pre-download screens** (the APK's built-in master and UI layouts, section 1.5) are client files. Showing them in English needs a client hook that serves an edited built-in master and layouts from the port's asset layer, like `--download-dir`. They are seen once per phone, so they come last.
- **The client's own language switch.** `CGame::OnInitialize` builds `CLanguage(0x100)` (ELF 0x114256c, `orr w1, wzr, #0x100`). With 1 (`en`) instead, `CGameResourceManager::FileExistLanguage` would look for `name-en.ext` first and fall back to `name.ext`, for direct files and for `Voice_*` packs.
  - English images and layouts could then ship as *new* `-en` members, which the stand-in path already serves. No overlay that replaces the download's files would be needed.
  - StringDB ignores `CLanguage`, so text still goes through the served master. (Section 6.6: the master is itself a file, so a `-en` master works with no StringDB change.)
  - This is a one-argument client change, but which loaders use `FileExistLanguage` must be checked first. (Checked in section 6.3: all of them, including the master, the story files and the font.)
- **The font: a server route exists.** An overlay `Font/etc2/font.fpk` with added glyphs (é, —, •, ™) would be data. It needs an fpk writer: ADLD, SLZ/zstd, ISF, an ETC2 page, the glyph table. Folding text to the existing glyphs (3.1) avoids all of that.
- **Word wrap: client change, or pre-wrapping on the server.**
  - **Server-side pre-wrapping.** Insert `\n` using the font's advances and a width budget per text kind; data only. This needs the budgets: the box widths per screen and message kind, measured from the `.csf` layouts or by screenshots.
  - **Client change.** A wrap in `ComposeString_` or `CCocosLabel::DrawSelf` when a line exceeds the label's box: one native, logged as a client change. It fixes every screen at once, including server text.
  - Global's English is already pre-broken, so wrapping matters mainly for new translations and for the 459 rows that lost their line breaks.

## 5. Risks and unknowns

| Risk | Status | Mitigation |
|---|---|---|
| Missing glyphs (accented letters, dashes, •, ™) | **known**: drawn as `?` | fold to the covered set before serving; a coverage check in tests |
| Lines too long: no wrap | **known** (experiment 2) | keep Global's `\n`; re-break the 459 rows that lost theirs; pre-wrap new text with font metrics; or a client wrap native |
| Single-line labels overflowing (`uimsg_chara_top_info`) | **known** (experiment 1) | per-id shorter text, or a width budget per label kind |
| Composed fragments that read wrong ("Time Left  Left:2d") | **known** | review the `uimsg_remain_*` / `*_limit` families; take JP's composition, not Global's |
| printf specifiers mismatched or reordered | filtered (1 row by id; 55 Global token rows) | specifier check in the build; reword reordered rows |
| Unknown tag in story text crashes `ParseMessage` | likely (disassembly) | strip or convert Global tokens; a test that every served Scenario row parses |
| Text used as keys | none found | — |
| Japanese sort order of English names | cosmetic | — |
| Global `ja` older than JP (821 rows) | the English may describe old values (hit counts, shop names) | leave Japanese, or take it after review (question Q7) |
| Global wording for things 3.7.0 does differently ("Gems" for 紋章石, "Official Forums") | cosmetic | a small override table |
| Client re-fetch of an overlay member | likely, unproven | the session proof in E4 |
| Which builtin UI copy the client uses after the download | unknown | only matters for title-screen labels |
| Server rules keyed by Japanese text (`kDefaultEventKeywords`) | **known** | English goes only into the served master |
| Present lines already stored in a save stay Japanese | **known** | cosmetic; new grants follow the language |
| Session drivers match Japanese screens by pixel signatures (`control/soadrive/popups.py`, `tests/smoke-base/*.png`) | **known** | sessions and gates keep `--lang ja`; English sessions get their own references |

**How to test.** Use a screenshot pair per session: the same session with `--lang ja` and `--lang en`, contact sheets side by side (`tools/contact_sheet.py`). Add a coverage report generated by the build of the English table. Checks:
- the rows filled, per source (id, text memory, manual);
- the rows left Japanese, per prefix;
- rows with a missing glyph or an unknown tag (both must be 0);
- rows wider than the JP row by more than N px.

The game sessions that exercise text are `home`, `tutorial`, `campaign` (story), `gacha`, `events` and `settings`.

## 6. The client's own language switch

Investigation of 2026-10-06 (agent `english2`), at the user's request: **a client change for English, plus a server that serves English assets with Japanese as the fallback for missing assets and voices.** The plan's options B and C ([PLAN-english.md](PLAN-english.md)) are built on this section. Decompiles: `work/decomp/eng2_*.resolved.c` (scratch, local). Addresses are ELF vaddr unless marked "Ghidra" (vaddr + 0x100000). Callers come from a scan of every `BL` in `.text` and of every ADRP+LDR/ADD pair, so a call through a vtable or `std::function` would not show.

### 6.1 What `CLanguage` controls

- **The object.** `CLanguage` is 12 bytes: `Default` (+0), `Current` (+4), `Voice` (+8), plus a singleton (`TSingleton<CLanguage>`).
  - The codes are `tLanguage` 0 = `ja`, 1 = `en`, 0x100 = `""` (no postfix), 0x101 = `none` (strip a postfix). `CLanguage::LanguageCode` (0x13b4b90) asserts on any other value.
  - The only constructor call is in `CGame::OnInitialize`: `CLanguage(0x100)` (`orr w1, wzr, #0x100` at 0x114256c). It sets all three fields to 0x100.
  - Nothing sets `Current` afterwards: `CLanguage::Current(tLanguage)` has 0 callers.
- **Its users: 6 functions, 10 references to the singleton** (an exact ADRP+LDR scan of its GOT slot; `tools/xref_got.py` also lists `LocalSetControllerU24_Default_TrRtSc<false>`, but none of that function's LDRs reads the slot, so it is a false hit):

  | Function (ELF) | Reads | Does |
  |---|---|---|
  | `CLanguage::CLanguage` (0x13b4b18) | — | installs the singleton, sets the three fields |
  | `CGameResourceManager::FileExistLanguage` (0x17f8634) | Voice, Current, Default | file lookup with postfix (6.3); called by `AddDirectFile` (45 calls in 23 functions), `IsFileExist` (51 calls in 33 functions) and `DownloadDirectFile` (2) |
  | `CGameResourceManager::RegisteredFileLanguage` (0x17f8c5c) | Voice, Current, Default | the same order for files already registered; called by `RemoveDirectFile`, `IsReadyDirectFile`, `rResourceElementDirectFile`, `crResourceElementDirectFile`, `CheckResourceStatusByFileName` |
  | `CGameResourceManager::IsFileExistDownloadFolder` (0x17f9590) | Voice, Current, Default | the same order in the download folder (`CFileLoader::gIsFileExist`) |
  | `CUIUtility::GetVoiceLanguage` (0x1dec438) | Default | `BAS:VoiceLanguage` from the local KVS (`Game.xml`); a value > 1 or a missing key gives `Default()` |
  | `CUIUtility::SetVoiceLanguage` (0x1dec558) | Default | a value > 1 becomes `Default()`; writes `BAS:VoiceLanguage`; `CLanguage::Voice(v)` |

- **Nothing else uses the language:**
  - **StringDB** hard-codes `"ja"` (6.2).
  - **The device locale.** `AConfiguration_getLanguage` / `getCountry` are called only by `android_native_app_glue` (`android_app_pre_exec_cmd`, `ANativeActivity_onCreate`), which the game never reads back.
  - **`master_language`.** `MasterDB::CLanguage` / `CMasterParameterLanguage` is a compiled-in master table class with 0 callers of `CParameterManager::pMasterParameterLanguage`. No `master_language` table exists in the 3.7.0 master or in Global's.
  - **Date and number formatting.** The formats are fixed and numeric (`%04d/%02d/%02d %02d:%02d`, `%Y-%m-%d %H:%M:%S`). The words come from `master_text` (`uimsg_thursday` (木), `uimsg_month` 月, `uimsg_day_on_day` 日), and Global has English rows for them ("(Thurs)", "m", "d").
  - **The web view.** The client's strings have no language parameter or language path in any URL. The notice page is the server's own HTML (1.6).
- **Voices.** `CUIUtility::EffectiveSetting` (0x1df2048, the last call of `CGame::OnInitialize`) runs `SetVoiceLanguage(GetVoiceLanguage())`.
  - The committed client save holds `BAS:VoiceLanguage` = 256 (0x100, from that round trip). So `Voice` is 0x100 unless the save says 0 or 1.
  - The 3.7.0 UI has no voice-language setting: `SetVoiceLanguage` has no caller but `EffectiveSetting`, and the JP master has no `uimsg_menu_voice_language*` rows, which Global's has ("Voice", "Japanese", "English").
  - The value can still be set in `Game.xml` (`python -m soa_save set --type u32 Game.xml BAS:VoiceLanguage 0`), as the sessions set `BAS:DownloadEpisodeFlag`. That needs no code change.

How measured: `tools/decomp.sh` of `CLanguage::*`, `FileExistLanguage`, `RegisteredFileLanguage`, `IsFileExistDownloadFolder`, `CheckResourceStatusByFileName`, `AddDirectFile`, `DownloadDirectFile`, `IsFileExist`, `Get/SetVoiceLanguage`, `EffectiveSetting`, `CGame::OnInitialize`. The `BL` and GOT scans (numpy over `.text`, as `tools/callers.py` / `tools/xref_got.py`). `python -m soa_save dump data/saves/client/Game.xml`.

### 6.2 StringDB: two hard-coded `"ja"` sites, and the row ids

- **Row ids.** Every row's `id` is `CHash32("<lang>_<message_id>")`. This holds for all 66,945 rows of the JP 3.7.0 master and all 129,808 rows of Global's master (64,904 `ja` + 64,904 `en`).
  - So Global's master is bilingual in exactly the format the JP client reads, and `en_` rows can be **added** to the JP master with computable ids.
  - No `CHash32("en_" + id)` of a JP message id collides with a `ja_` id.
  - Two pairs of JP message ids collide with each other in the `en_` space: `item_coin_281_text_message` / `factor_message_10008` and `item_chip_cp0112_b03a_item_message` / `uimsg_gear_ax_30_25`. An `en_` row for one of a pair would also answer the other, so both must stay Japanese.
- **Site 1: `StringDB::GetNativeString`** (0x16faaec, Ghidra 0x17faaec).
  - It formats `"%s_%s"` with the literal `"ja"` (0x270bbba, the same string `CLanguage::LanguageCode` returns for 0), hashes it and calls `pParameterFromHash`.
  - On a miss it returns the key. Its only caller is `StringDB::Get` (0x16faa2c), which has 63 calls in 50 functions.
- **Site 2: `StringDB::GetList`** (0x16fac78, Ghidra 0x17fac78).
  - It builds `SELECT * FROM master_text WHERE id IN (` from `CHash32("ja_%s")` of each message id (literal 0x275ebfa) and runs it through `ParameterByQuery`.
  - Its callers are `tMessage::SetMessageList` and `tMessageCache::SetMessageList`. Together they preload the text of 122 call sites: 73 of the vector overload, 46 of the `initializer_list` overload (which forwards to it), and 3 of `tMessageCache`.
  - These are most screens' fixed labels: the home header, the episode select, the item, gacha, mission, deep-space, shop and Other menus.
  - Experiment 3's run 1 (6.5) shows the weight of this site. With `GetNativeString` patched and `en_` rows served, the home header and the episode select stayed Japanese. `GetNativeString` ran fewer than 1,025 times in either direction over the whole home session.
  - `tMessage::GetMessage` returns an empty string for an id the preload didn't fetch. It doesn't fall back to `StringDB::Get`.
  - `tMessage` keys its `std::map` by the row's **message_id** string, so a query that returned both an `en_` and a `ja_` row for an id would keep whichever came last from an unordered map. A per-id fallback has to return **one row per message id**: query the `en_` ids, then the `ja_` ids of the message ids that got no row.
- **`GetList` reads the master only.** `ParameterByQuery` (Ghidra 0x17fb164) opens `sqlite/basmaster.sqlite3` and appends the rows it returns to the caller's map, so story rows never reach a `tMessage`.
- **No other reader of `master_text`.** `pParameterFromHash` is called only by `GetNativeString`, and `ParameterByQuery` only by `GetList`. The client has no other `master_text` query string, and the `lang` column is never read.
- **Story files load into the same StringDB.** `CEventScenario::Run` calls `StringDB::SetAddLoadFileName(GetParameterName(file))`. The Scenario rows (ids `CHash32("ja_" + id)` like the master's) are then found by `pParameterFromHash` through the same `"ja"` key. `StringDB::ReleaseParameter` frees them when its argument `strcmp`s equal to that name.
- **So `en_` rows need two functions changed** (option B of the plan). `GetNativeString` and `GetList` take the code from `CLanguage::Current()` and fall back to `ja` per message id. A `-en` master with English in its `ja_` rows needs neither (6.6).
  - Both run on the APK's built-in master before the first download, where no `en_` rows exist, so the fallback gives Japanese there.
  - With `Current` = 0x100 or 0, both must behave exactly as the original; a selftest can compare them.

### 6.3 Files: `name-en.ext` with the plain name as the fallback, already built in

- **The lookup.** `CGameResourceManager::FileExistLanguage(name, mode, out)` returns a status:

  | Status | Meaning |
  |---|---|
  | 0 | not found |
  | 1 | in the download DB, not on disk |
  | 2 | in the download list |
  | 3 | in the download folder |
  | 4 | built in, or a plain file |
  | 5 | registered and ready |

  The order it tries, stopping at the first non-zero status:
  1. **Voice packs.** When the tail contains `Voice_` and the extension is `.spk`: `PostfixLanguageCodeFilepath(name, Voice())`. With `Voice` = 0 the postfix is stripped, so the result is the bare (Japanese) name. With 1 it is `Voice_x-en.spk`. With 0x100 the name is unchanged.
  2. If `Current()` is 0x100, or the name already contains `-` (`IsPostfixLanguageCode(name, 0x100)` searches the tail for `"-"` + `""`): the plain name only.
  3. Otherwise `name-<Current>.ext`, then `name.ext`, then `name-<Default>.ext` (with `Default` = 0x100 the plain name again).
- **Where the resolved name goes.** `AddDirectFile` registers the resolved name (`name-en.ext`), and `RegisteredFileLanguage` finds it again later in the same order.
  - With status 1–2 `AddDirectFile` calls `CGameResourceDownloader::RequestDownload` for the resolved name: an on-demand fetch of a member the manifests list but the phone doesn't have.
  - So with `Current` = 1, every direct file, image, layout, parameter, sound and script loaded through `AddDirectFile` / `IsFileExist` gets an English variant **with the Japanese file as the fallback**, and nothing in the loaders needs changing.
- **A naming constraint.** A name that already contains `-` is never postfixed. None of the 26,046 files of the 3.7.0 download has a `-` in its name, so every file takes part.
- **Built-in (APK) files.** `CheckResourceStatusByFileName` asks `CGameResourceDownloader::IsBuildInData(name)` and then `CFileLoader::gIsFileExist(name)`. Whether a `-en` file added only to the port's asset overlay is found before the first download depends on these two (6.5).
- **Which loads take part (experiment 3).** A trace of every `FileExistLanguage` call, one line per distinct name, logged 229 names over the home session:

  | Directory | Names |
  |---|---:|
  | `UI` | 80 |
  | `Image` | 49 |
  | `Sound` | 38 |
  | `Parameter` | 21 |
  | `Motion` | 19 |
  | `Effect` | 10 |
  | other (`MapHome`, `Character`, `Shader`, a few `dummy*.png`) | 12 |
  | `Font` | 1: `Font/etc2/font.fpk` |
  | `sqlite` | 1: `sqlite/basmaster.sqlite3` |

  The campaign session adds `Scenario/TS_1010.msgp`, `Script/1010_030.msgp`, `TalkScene/*.csf` and the `Voice_TS_*` packs. So the font, the master and the story files all have `-en` variants for free.
- **The data check fetches every new member.** On the pre-downloaded shared phone, the client fetched the Individual bundle of each of the 106 `-en` members it lacked (`I/5374616e/<hash>.bin`, 106 GETs) and not the Bulk bundle, before the home screen. It does this whatever its language. So a `-en` member costs every client its size, Japanese clients included.
- **The CDN side exists.** A `-en` file is a new name, which is what stand-ins are:
  - `TreeBuilder::add_standins` (`server/src/cdn/tree.cpp`) turns each overlay file the download lacks into a version.bin entry, an Individual bundle `I/5374616e/<chash32>.bin` and a member of the Bulk bundle `B/5374616e/standins.bin`, under a new revision.
  - The unmodified 3.7.0 client fetches them at its data check (`emulator/scripts/standin_fetch_test.sh`).
  - ADLD XOR is keyed by `CHash32` of the member's path (`Image/etc2/x-en.aif`), so a `-en` file is encrypted under its own name.

### 6.4 Voices: the switch exists, the English voices don't

- **The voice files.** [global-voice-files.md](global-voice-files.md) lists 187 `-en` voice packs Global must have shipped (`Sound/Voice_<x>-en.spk`), derived from the rule in 6.3.
  - **None is in hand.** `find` over the 3.7.0 download (26,046 files), the APK, `work/SOA_2021-06-10`, `work/extracted` and `work/backup-lfs` finds no file whose name contains `-en.`, and no file with `-` in its name at all.
  - The Global master (`data/basmaster-gl.sqlite3`) is the only Global file we have. It names voice packs but contains no audio.
- **With the switch, the Japanese voice is the fallback automatically.** With `Current` = 1 and `Voice` = 0x100, `Voice_x-en.spk` is probed (status 0) and `Voice_x.spk` plays. With `BAS:VoiceLanguage` = 0 the probe is skipped: always Japanese.
- **What English voices would need.** Global's 1.5.0 data (its CDN is gone) or newly recorded audio. Neither is in scope: PLAN-english.md Q10.

### 6.5 Experiment 3: the switch, `en_` rows beside `ja_`, `-en` images

All runs used the worktree's `build/port/soa` with a scratch native file, `work/english/exp2/lang_scratch.cpp`. It was compiled in for these runs only and is not committed. Under `SOA_LANG_EXP=1` it does three things:
- It sets `CLanguage::Current` to 1 after the constructor. `Default` and `Voice` stay 0x100.
- It makes `StringDB::GetNativeString` read `CHash32("en_" + id)` through `pParameterFromHash`, and fall back to the original (`ja_`) on a miss.
- It logs every `FileExistLanguage` call once per name, with the status and the resolved name.

The sessions ran in the slot pool on the shared phone, with the standard drivers (`control/run.py`). Everything is in `work/english/exp2/`: the wrappers `soa-exp` and `soa-exp3`, the scripts, the masters, the stand-in dirs, and each run's `*-out/` (shots, `log.txt`).

**Run 1: `home`, `en_` rows and `-en` images.**
- **Setup.**
  - `--master basmaster-en-added.sqlite3`: the JP master plus 19,145 `en_` rows (id `CHash32("en_" + id)`, `lang` `en`, from `merge_add.py`); 40.0 MB against 37.6 MB.
  - `--standin-assets standin-en`: the repo's stand-ins, plus 80 `Image/etc2/banner_gacha*-en.aif` / `banner_ticketgacha*-en.aif`, plus 26 `Scenario/TS_*-en.msgp`. Each image is the stand-in `banner_gacha_pickup_role_0054`, re-encrypted under its `-en` name. Each story file holds all its `ja_` rows plus `en_` rows, for the files where Global's English covers at least 90% of the lines.
- **PASS** ("every home destination reached").
  - The data dialog asked for 40 MB: the master and the 106 new members.
  - `home-out/shots/32-gacha.png`: **every banner of the recommended tab is the `-en` copy** (trace: `Image/etc2/banner_gacha_weapon_0002_002.aif -> 3 …_002-en.aif`). "Draws" is English (`GetNativeString`); the tabs are Japanese.
  - `04-home.png`: the title "Anamnesis Debut" is English, but the header (スタミナ, 紋章石, 調査ランク) stays Japanese. It comes through `GetList`, which the scratch file didn't patch (6.2).
- **Voices.** Every `Sound/Voice_*.spk` resolved to its bare name, status 3.

**Run 2: `campaign`, the story.** Same wrapper.
- **PASS** ("episode 1 -> mf01_001 cleared -> mc01_030 played"; the next mission unlocked, so the story scene ended normally).
- **The trace.** It has `Scenario/TS_1010.msgp -> 3 Scenario/TS_1010-en.msgp`.
- **The shots.** `campaign-out/shots/82-story.png` and `83-story.png` show the story in English: speaker "Coro" (an `en_` master row), "Thanks to your efforts, I was able t…".
  - **The English lines run past the right edge of the message window.** Global's line breaks were made for a wider window than 3.7.0's.
  - The window's buttons (早送り, ログ表示, スキップ, オート) stay Japanese.
- **Not shown.** Whether `StringDB::ReleaseParameter` released the `-en` file's rows: the session played one scene. **Shown 2026-10-07 (agent `en-server`, C4):** with the server-built `Scenario/TS_1010-en.msgp` (English in its `ja_` rows, no StringDB change) `soa --lang en` played two scenes of that file in a row (mc01_030, then mc01_020), both in English, and the client's RSS stayed at about 1.59 GB; the data check had fetched all 24 `-en` story files, also those of the EP1 pack (docs/server-rules.md#english-story). The English lines run past the message window (no re-break yet, E7).

**Run 3: `home`, a whole English master as a `-en` file, no StringDB change in effect.**
- **Setup.**
  - The server's own master, unchanged, as the served master.
  - `--standin-assets standin-en3`: the repo's stand-ins, plus `sqlite/basmaster-en.sqlite3`. That is experiment 1's master, with English in 19,145 `ja_` rows, AES-ADLD (encType 2) under its `-en` name.
  - The `GetNativeString` hook was still on, but this master has no `en_` rows, so it always fell back to the original.
- **The master resolved to the `-en` file.** The trace has `sqlite/basmaster.sqlite3 -> 4 sqlite/basmaster-en.sqlite3` in the title phase, before the download. The client then fetched the `-en` member (`I/5374616e/1bc76693.bin`, 37.6 MB) as well as the served master (36.2 MB).
- **PASS.**
  - `home3-out/shots/04-home.png`: **the header is English** ("Stamina", "Gems", "Rank", "Next"), through `GetList`, with no StringDB patch doing anything.
  - `00-download-dialog.png`: the **pre-download** data dialog shows "Space Required: 71 MB", "Download" and "Return to Title Screen", which overflows its button. The labels baked into the layout stay Japanese.
  - The home's event badge reads 4, not 5. This `-en` master didn't get the server's `ClientMaster` edits (event dates), which the served master gets.
- **What run 3 did not prove:**
  - **The port's overlay helped.** Status 4 means a built-in file: the port's `AssetManager::find_download` merges the stand-in dir into `builtin_data/`, so the `-en` master was visible before any download. `soa-emu` gets stand-ins only through the CDN.
  - **Which copy was used after login.** The trace logs each name once, so whether the client read the downloaded copy or the overlay's is not shown.
  - **The proof still to make.** `soa-emu` with a `-en` master from soa-server's CDN only, as `emulator/scripts/standin_fetch_test.sh` does for the stand-ins. **Made 2026-10-07 (agent `en-server`):** soa-emu `--lang en` against `soa-server --english` fetched `I/5374616e/1bc76693.bin` (the `-en` master, built by the server from `data/english/master-en.tsv` after every `ClientMaster` hook) from the CDN only, stored it byte for byte, and its home header was English with the event badge at 5 (`emulator/scripts/lang_fetch_test.sh`; docs/server-rules.md#english).
- **Story files in this shape.** A story `-en` file with English in the `ja_` rows, which is what this design needs, was not run. Run 2 used the superset form with the `GetNativeString` hook.

### 6.6 Consequence: the smallest client change is one site

Run 3 shows a second way to deliver text: not `en_` rows that StringDB must learn to read, but **per-language files**. The client already picks `name-en.ext` over `name.ext`. That holds for the master (`sqlite/basmaster-en.sqlite3`), the story (`Scenario/TS_*-en.msgp`), the layouts, the images, the font and the voices. So the only code change is **setting `CLanguage::Current` to 1**, and StringDB keeps reading `ja_` rows, of the English files. The two designs, in [PLAN-english.md](PLAN-english.md):

| | Per-language files (one site) | `en_` rows (three sites) |
|---|---|---|
| Client code | `CLanguage::Current` = 1 | the same, plus `StringDB::GetNativeString` and `StringDB::GetList` |
| Master text | `sqlite/basmaster-en.sqlite3`: a second master, the served one with English in its `ja_` rows. The per-row fallback is made by the server when it builds the file | `en_` rows added to the one served master; the per-row fallback is made by the client |
| Story | `TS_*-en.msgp` with English in the `ja_` rows | `TS_*-en.msgp` as a superset (`ja_` + `en_`) |
| `GetList` screens | English with no extra code (run 3) | need the `GetList` patch (run 1) |
| Cost per client | every client fetches every `-en` member (6.3): **+36 MB for the second master**, plus the story and art files | +2.4 MB of master, plus the same story and art files |
| Server work | the served-master pipeline gets a second output: its `ClientMaster` edits, then the English | one `ClientMaster` hook that inserts rows |
| Pre-download screens | the port can carry an English built-in master through its asset overlay (run 3's dialog) | the same, with a built-in `-en` master that holds `en_` rows; without one, Japanese until the first download |

### 6.7 Implemented: `--lang` and `--voice-lang` (B1, B7, E10)

Agent `en-client`, 2026-10-07 ([PLAN-english.md](PLAN-english.md) B1, B7, E10; [client-changes.md "English mode"](client-changes.md)).

- **`--lang ja|en`** (`soa` and `soa-emu`; `platform370::Config::lang`, `platform370/src/lang_370.cpp`). With `en`, `CLanguage::CLanguage` is hooked and sets Current to 1 after the original; with `ja` nothing is hooked. The selftest `platform370/lang` checks the singleton (Default 0x100, Current 1 or 0x100, Voice 0) and that `PostfixLanguageCodeFilepath("Font/etc2/font.fpk", Current)` is `font-en.fpk`.
- **`--voice-lang ja|keep`** (default `ja`): `BAS:VoiceLanguage` = 0 written into the phone's `Game.xml` before the client starts, through the runtime's SharedPreferences and the game's KVS encoding (moved from the server to `common/include/soa/kvs.h`).
- **The `home` session with `--lang en`** (the unchanged Japanese server; `SOA_TRACE` on `CLanguage::PostfixLanguageCodeFilepath` with `:0=s`, a string dump added to `core/trace.cpp`) passed ("every home destination reached"). Its log (`work/english/exec/client/b1-home/log.txt`, local):
  - 16,196 postfix calls, 12,867 of them giving an `-en` name: `Font/etc2/font-en.fpk`, `sqlite/basmaster-en.sqlite3`, `UI/etc2/home-en.csf`, `Character/…-en.acf`, `Sound/…-en.aac` and so on. None exists, so every load fell back to the Japanese file.
  - The voice packs: `FileExistLanguage` and `IsFileExistDownloadFolder` (the disk and download lookups) resolved every `Sound/Voice_*.spk` to its bare name through Voice 0, with no `-en` name. `RegisteredFileLanguage` (the in-memory table of files already registered) still tries Voice, then Current (`Voice_UI_001-en.spk`), then the plain name while a pack isn't registered yet: a lookup in memory, not a file probe or a download.
  - The client read `BAS:VoiceLanguage` 256 from the session's save; the log shows `256 -> 0`.
- **E10 (a), the hard-coded strings** (`platform370/src/text_370.cpp`): the 14 literals all reach the screen through `CCocosLabel::SetText(std::string const&)` (`CUIUtility::SetText` / `SetButtonText` / `SetLabelText` → it; `CSortDialogWrapper` and the LV%d習得 sites call it directly; `CDialogCommon::SetMessage` only stores the text for the dialog's label). One hook there replaces them with `port_en_*` master text (10 ids, `data/english/client-strings.tsv`), Japanese when the master has no row. The フィルター / 並び替え titles are only the fallback for a sort-dialog group without a title (`StartDialogFromProperty` @0x1d4ef70); the character list's dialog didn't show them. プレイヤー用ダミーネーム (`CPlayerInfo::Initialize`) is a default property value, never a label's text.
- **E10 (b), word wrap**: the box is known only for `IsCustomSize` labels (+0x280, width +0x94). Every other label (both experiment cases: the dialog message `dialog1.csf` `Text`, 533 wide from its placeholder, and `partymenu_common.csf` `Text_2`, 183 wide) takes its text's size, and its layout size is its placeholder's, so the room is taken from the screen: world position, scale and anchor (`GetWorldMatrix` + `CMatrix::PutPRS`) against the 720-wide design area. The header line is first drawn at its layout x (657) and then slides to its place after the title (326), so a label is wrapped again whenever its room changes.
- **Shots** (`work/english/exec/client/`, local; a throwaway master with experiment 2's long `uimsg_full_stamina` and the `port_en_*` rows, through `--master`): `e10-home/shots/29-stamina.png` (the 170-character line in four centred lines), `30-character.png` (`uimsg_chara_top_info` in two lines beside "Characters"), `21-follow.png`, `31-item.png`, `34-other.png`; `e10-tour/` (the character list's sort dialog), `e10-live/` (the selftests at home on soa against soa-server with the rows). The `home` session passed.
- **The story window** (`Behavior_TalkText(2)::UpdateFont` reveals the text with `SubStrUTF8` into a label; `CEventScenarioMessageWindow::Append` places colour segments by the measured width of the text before them): its labels are wrapped only when a line would leave the screen, not at the window's frame, so story lines are to be broken by the data (E7).

## 7. Machine translation for the gaps

Investigation of 2026-10-07 (agent `english-mt`), at the user's request: **how would a machine-translation (MT) option for the text Global never translated work, and how would it be documented and edited later?** Nothing in the server or client changed. The data-side prototype is `tools/english_mt.py` (coverage, glossary, translation memory, protected tokens, glyph folding, line widths, checks); it only reads data and writes to `work/`. The trial's engine adapters, raw outputs and scores are in `work/english/mt-trial/` (local, not committed: derived game text). The plan's steps are in [PLAN-english.md "Machine translation"](PLAN-english.md#machine-translation-for-the-gaps-m-steps).

### 7.1 What is left after the official English

`tools/english_mt.py coverage` sorts every JP row by where its English can come from, in this order:

| Source | Master rows | JA characters | |
|---|---:|---:|---|
| Official, by id (the five filters of 1.4) | 19,145 | 327,086 | Global |
| Language-neutral (no kana or kanji) | 1,530 | 7,342 | nothing to do |
| **Exact memory**: another official pair has the identical Japanese | 6,265 | 92,257 | Global's words, reused |
| **Template memory**: an official pair differing only in its numbers | 2,412 | 43,179 | Global's words, new numbers (7.2) |
| **Gap** | **37,593** | **884,701** | MT, a human, or Japanese |
| … as distinct texts | 27,847 | 704,830 | what an engine actually translates |

- The gap's biggest prefixes: `message` 5,071, `uimsg` 3,739, `item` 3,660, `seed` 3,495, `cp` (profiles) 3,385, `factor` 2,831, `name` 2,576, `Asset` 2,542, `talentName` 2,014, `AttackName` 1,575, `gachaPickup` 1,451, `Guide` 1,308.
- 803 gap rows have Global English for an **older** Japanese text (the user's Q7: they follow the gap rule). The coverage report should show Global's old English beside them as an editor's reference.
- The exact memory is 6,265 rows here against 6,845 in 1.4: this count also drops Global pairs with Global-only tokens or a specifier mismatch.

Story (`Scenario/TS_*.msgp`, lines with kana or kanji):

| Group | Official | Gap lines | Gap JA characters |
|---|---:|---:|---:|
| EP1 | 2,979 | 127 | 4,395 |
| EP2 | 0 | 7,906 | 238,231 |
| EP3 | 0 | 5,037 | 157,793 |
| `TS_3xxx` / `TS_5xxx` | 708 / 794 | 116 / 64 | 2,985 / 1,786 |
| `TS_9996`, `TS_C*`, `TS_D*`, `TS_E*` (events) | 0 | 3,932 | 125,008 |
| **Total** | 4,481 | **17,182** | **530,198** |

- **EP2 has no official English at all.** The "453 of 8,428" of 1.4 and basmaster-gl.md are lines whose Global `en` equals the `ja` (`……`, `！？`): language-neutral, not translated. Of EP2's other lines, 7,570 have Japanese in Global's `en` and 405 aren't in Global's master.
- 117 of EP1's 127 gap lines are official English with `<EMDASH>`: E3's rewrite (`<EMDASH>` → `―`) turns them official. EP1 is then complete but for 10 lines. (2,979 official + 117 + 283 language-neutral = the 3,379 of 1.4.)
- **Volume for an engine:** about **705k JA characters of master text plus 530k of story, 1.24M in all.** English came out at 2.06 characters per JA character in the trial, so about 2.5M characters of English.

### 7.2 Before any MT: memory and glossary

These are deterministic, free, and use Global's own words, so they run first and MT only gets what is left.

- **Template memory.** Each official pair is normalised with NFKC (full-width digits and symbols to ASCII: `ＨＰ＋１０％` → `HP+10%`) and its numbers replaced by slots. A JP row whose normalised text equals a template, with different numbers, gets the template's English with its own numbers.
  - Only templates whose English contains each Japanese number exactly once are kept; templates with month names or ordinals are dropped (`９月` = "September", `21th`), and `1 times` becomes `1 time`.
  - **Accuracy, held out:** templates built from half of Global's official pairs, applied to the other half where only a template matched: 1,459 of 1,661 identical to Global's own English, 72 more equal up to spaces and line breaks (92%). The rest are Global's own inconsistencies (`1000` vs `1,000`, "Spirit Shock" vs "Spirit Strike" for the same 衝霊破) and a few wrong matches (`あと2回で新武器確定`).
  - It fills 2,412 gap rows, mostly `seed` (1,599) and `factor` (442).
- **Glossary.** `tools/english_mt.py glossary` mines Global's official English of every name field: 3,246 terms (character 348, speaker 150, skill 910, talent 487, item 767, mission 337, short UI terms 247). 302 terms have more than one official English: the most used one wins, then the shortest; the others are accepted variants. Examples: 紋章石 = Gems, スタミナ = Stamina, フェイト = Fayt, コロ = Coro.
  - A katakana term inside a longer katakana word doesn't count (レイ = "Laser Beams" in マルチプレイ, フレイ = "Freya" in フレイムロンド: found by the trial's Opus translator).
  - Generic 2-character UI words (入手 = "Obtained", 必要, はい) made bad terms and were dropped: only katakana terms and terms of 3 or more characters without hiragana are kept from `uimsg_*` labels.
  - **New names are the open gap.** EP3's characters never reached Global. In the trial, リーシュ came out as "Leesh", "Lishe", "Reese" and "Reish" from four engines. The new proper nouns (katakana runs in story and names that aren't in the glossary) need one decision each, made once, before the story is translated: a human, or an LLM proposal a human approves, added to the glossary as `human`.

### 7.3 Engines

Measured on this machine where marked; prices as published in October 2026 (check before buying).

| Engine | Kind | Size / where | License of the model / terms | Trial (7.4) | Notes |
|---|---|---|---|---|---|
| Opus-MT `Helsinki-NLP/opus-mt-ja-en` | Marian NMT, offline | 293 MB (CTranslate2 int8 ~75 MB) | Apache-2.0 | measured | hallucinates on short UI strings ("Oh, my God." for オーブ; "== sync, corrected by elderman ==" for a line with a tag): subtitle training data |
| FuguMT `staka/fugumt-ja-en` | Marian NMT, offline | 119 MB | CC-BY-SA-4.0 | measured | **broken under transformers 5** (garbage output); correct through CTranslate2 |
| Sugoi v4 (JParaCrawl) | fairseq NMT, offline | 1.1 GB | NTT terms: research only, no commercial use, also for derived data | not run | popular for visual novels; its terms don't fit shipping its output |
| NLLB-200 distilled 600M / 1.3B | multilingual NMT | 2.5 / 5.5 GB | CC-BY-NC-4.0 | not run | non-commercial; general multilingual models trail dedicated JA→EN pairs |
| M2M100 418M | multilingual NMT | 1.9 GB | MIT | not run | the same; weakest of the multilingual set |
| Qwen2.5-1.5B-Instruct (GGUF Q4_K_M) | small local LLM | 1.1 GB | Apache-2.0 | measured | the largest Apache-licensed Qwen2.5 under the ~2 GB limit; Qwen2.5-3B is under a research license |
| Gemma 4 31B-it, 26B-A4B, 12B; Qwen3.8-27B; shisa-v2-mistral-small-24b (GGUF ~Q4) | local LLM, GPU | 7–17 GB each, llama.cpp CUDA | Apache-2.0 (all five) | measured (7.8) | the user lifted the size limit for this test (M-Q3); Gemma 4 31B ties Claude on the trial |
| DeepL API Pro | online NMT | — | output is yours; Pro deletes texts after translation and doesn't train on them | not run | about $25 (€20) per million characters plus a monthly base fee; glossaries supported; 500k characters/month free tier |
| Google Cloud Translation | online NMT | — | — | not run | $20 per million characters (NMT), first 500k/month free; LLM mode about $10 + $10 per million characters in and out |
| Claude API (Sonnet 5.5, Opus 5.5) | online LLM | — | output is yours; API inputs aren't used for training by default (commercial terms) | measured (in-session, see 7.4) | follows a glossary and rules in the prompt; context of a whole scene; Batch API halves the price |

**Cost for the whole gap** (1.24M JA characters, 7.1):

| Engine | Estimate | Basis |
|---|---:|---|
| Local NMT / local LLM | electricity | CPU or GPU hours (below) |
| Google NMT | about $15–25 | $20 per million source characters |
| DeepL API Pro | about $30–35 | $25 per million plus the base fee |
| Claude Sonnet 5.5, Batch API | about $10–20 | input about 3–4M tokens (the Japanese at roughly 1–1.3 tokens per character, plus per-row kind and glossary lines and scene context) at $1 per million; output about 1–1.5M tokens (2.5M English characters, JSON wrapping, thinking) at $5 per million |
| Claude Opus 5.5, Batch API | about $20–40 | the same tokens at $2 / $10 per million |
| A second LLM pass (review against the checks, 7.5) | about the same again | |

The token counts are estimates from character counts: no API key was used, so `count_tokens` was not run. They are within a small factor either way; the order of magnitude (tens of dollars) is the point.

**Speed.** The trial ran while other agents' gates and clients loaded the machine (load average about 50 on 32 threads), so these are lower bounds: Opus-MT and FuguMT through CTranslate2 int8 on 16 CPU threads did 21–27 JA characters per second (about 13–16 hours for 1.24M characters at that rate; CTranslate2 on the GPU needs the CUDA 12 cuBLAS libraries, not installed). Qwen2.5-1.5B through llama-cpp-python on 16 CPU threads (no CUDA toolkit for a GPU build) took 1,619 s for the 310 rows, about 4.6 JA characters per second: days for the whole gap on this loaded CPU. An online engine finishes the whole gap in about an hour (Batch API: within 24 hours). The 12–31B local LLMs on the GPU (7.8) do 13–108 JA characters per second: **3–26 hours** for the whole gap, depending on the model and on how much of the GPU other programs hold.

**Privacy.** The text sent out is the publisher's game text: no personal data, no player ids. Sending it to an API is a copyright question, not a privacy one, and the same one as committing translations of it (7.6).

### 7.4 The trial

- **Sample** (`tools/english_mt.py sample`, seed 20261007): 310 rows.
  - 200 master rows with official English, stratified: UI/system 30, `message` 25, `seed`/`factor` 25, items 20, `name` 20, skills/talents 20, profiles 20, rows with printf specifiers 20, rows with `\n` 20.
  - 40 master gap rows from 3.x features (`Guide`, Sphere 211, universe, `Asset`, `gachaPickup`, `uimsg`): no reference; shown for behaviour.
  - 50 EP1 story lines with official English (10 of them with `<player>` or `<font…>`), and 20 EP3 gap lines (no reference).
- **Leak control.** The glossary and memory given to the engines were built **without** the sampled ids, so no row is scored against its own official English. The Claude translations were made by two fresh subagents (Opus 5.5 and Sonnet 5.5) that read only the prompt file (`claude-input.txt`: the rules, each row's kind, its glossary hits and the Japanese; no reference). This is the same model as the API but not an API run. Their prompt file was built with an earlier glossary that still had generic UI words (入手 = "Obtained", 必要 = "Needed", dropped since: 7.2); both followed it ("Obtain 82 FOL" where Global has "Get"), which costs them a little chrF and makes their glossary count slightly flattering. A model may have seen Global's English on the web (wikis quote it); that would inflate its scores and can't be ruled out.
- **Pipeline**, the same for every engine: NFKC on the Japanese; `\n` joined (story) or turned into a space (master); for the NMT engines, specifiers and tags masked as `X0X` placeholders and restored; then `post`: NFC, glyph folding (7.5), story and multi-line rows re-broken at the font's advances, checks.
- **Scores** against Global's English (sacrebleu chrF, chrF++, BLEU over the 250 rows with a reference; `\n` and spaces collapsed):

| Engine | chrF all | chrF master (200) | chrF story (50) | chrF++ | BLEU | tokens kept (36 rows) | glossary used (85 rows) |
|---|---:|---:|---:|---:|---:|---:|---:|
| Opus-MT (CT2 int8) | 27.6 | 27.7 | 27.3 | 25.5 | 9.3 | 27 | 21 |
| FuguMT (CT2 int8) | 32.3 | 33.1 | 30.1 | 29.6 | 12.2 | 28 | 31 |
| Qwen2.5-1.5B (Q4, local, glossary in the prompt) | 35.3 | 38.5 | 26.6 | 32.5 | 10.6 | 20 | 74 |
| Claude Sonnet 5.5 | 43.8 | 47.3 | 34.5 | 41.3 | 21.3 | **36** | 83 |
| Claude Opus 5.5 | **44.4** | **47.4** | **36.5** | **41.8** | 21.1 | **36** | **84** |

  Per stratum (chrF, Opus-MT / FuguMT / Qwen / Sonnet / Opus): `seed`/`factor` 34 / 45 / 43 / 67 / 60; skills/talents 20 / 22 / 45 / 46 / 44; `name` 14 / 25 / 38 / 49 / 52; UI 35 / 32 / 41 / 43 / 45; EP1 story 27 / 30 / 27 / 35 / 37.
- **How to read the numbers.** chrF against one reference punishes valid wording ("Obtain 82 FOL" vs Global's "Get 82 FOL"; "Arctic Impact Revised" vs "Revised Arctic Impact"), and short UI strings make it noisy. The gap between the families is large and consistent across every stratum; the gap between Sonnet and Opus isn't significant on 250 rows.
- **What the rows look like** (Japanese, Global, then Opus-MT / FuguMT / Sonnet / Opus):

  | Japanese | Global | Opus-MT | FuguMT | Claude Sonnet | Claude Opus |
  |---|---|---|---|---|---|
  | 紋章石が不足しています。 | Not enough gems. | There's a shortage of coatstones. | There is a shortage of heraldic stones. | Not enough Gems. | Not enough Gems. |
  | ＨＰ１００％時に与ダメージ＋５５％ | Damage dealt +55% at 100% HP | Damage at 100% HP + 55% | 55% damage at 100% HP | Damage dealt +55% at 100% HP | Damage Dealt +55% at 100% HP |
  | ＨＰ１５％以下の被ダメで怯まず（全体）\n狙われやすくなる効果＋３（自分） | No flinching when taking damage of 15% HP or less (party), and Taunt +3 (self) | (HP 15% less than or equal to whole) | 15% or less of HP's power is going to make it easier to be targeted | No flinching from damage taken at 15% HP or less (All); Target-attracting effect +3 (Self) | No flinching from damage taken at 15% HP or less (All); Aggro +3 (Self) |
  | フリージングインパクト・改 | Revised Arctic Impact | "Frequency Influence" | Fringing Impact Change | Arctic Impact Revised | Arctic Impact+ |
  | `<player>`、お願いじゃ、協力してくれ！ (EP1) | `<player>`, please will you come with me? | `<player>`, please help me! | `<player>`, please, help me! | `<player>`, I beg you, help us! | `<player>`, I beg you, please help us! |
  | 任官して間もないわたしにとって、今際の際の約束というものはとても衝撃でした。 (EP3, no Global) | — | For me, as soon as I was in charge, the promise I made at this time was a great shock. | For me, who had just been appointed to this post, the promise I made at this time was very shocking. | For me, newly commissioned, a promise made at someone's last breath was a great shock. | For me, freshly commissioned, a promise made on someone's deathbed came as a real shock. |

- **Failure modes seen:**
  - NMT: game terms translated literally (紋章石 "coatstones"/"heraldic stones" instead of Gems), formulaic stat lines garbled, dropped clauses and dropped placeholders (`%d`, `%s`, `<player>` lost in 8–9 of 36 rows), and Opus-MT's subtitle hallucinations. Neither NMT model can be told a glossary.
  - Small local LLM (Qwen2.5-1.5B): follows the glossary (74 of 85) but loses tokens in 16 of 36 rows (`<player>` dropped: "You, please, help me!"), leaves kana in 11 rows, misspells ("Normaly") and paraphrases stat lines ("When HP is 100%, it deals 55% more damage.").
  - Claude: kept every specifier and tag, used the glossary in 83–84 of 85 rows (the misses: a variant form, "Great Sword" for a "Great Swords" term), but **invents a form where Global has a convention** ("Arctic Impact+" for `・改`; "(All)" where Global writes "(party)"), and labels UI rows in the glossary's form even when a sentence reads better ("Purchase Gems completed successfully"). Both are fixable with more glossary entries and a few style examples in the prompt (Global's conventions: `（全体）` = "(party)", `（自分）` = "(self)", `・改` = "Revised").
  - Opus wrote `%d%%` for `%d％`: right, since the row goes through printf. The NFKC step itself turns `％` into a bare `%` for the other engines, which printf would read as a conversion (`% o`); `post` now rewrites a bare `%` in a printf row to `%%`, and the check flags any left.
  - **Width.** 74–81 of the 310 rows per engine were single-line rows more than 1.5× as wide as the Japanese; on the 250 rows with a reference that is 65–70 per engine, against 60 for Global's own English. That is the English, not the engine: labels need the shrink of 3.2, a shorter override, or the client's word wrap (Q6).
- **Verdict.** The two offline NMT models are not usable as-is for this game: they fail the game's terminology, its formulaic stat lines and its tokens, which is most of the gap. An LLM with the glossary in the prompt is clearly better on every stratum and keeps every token; its output needs the same checks and a light human pass, mainly for names, Global's conventions and the story's tone. A 1.5B local LLM sits between the two: better than NMT on terms, worse on tokens and story, and slow on this CPU.

How measured: `tools/english_mt.py coverage|glossary|sample|post`; the engine adapters `work/english/mt-trial/engines/run_ct2.py`, `run_llama.py`, `prompt.py` and the scorer `score.py` (sacrebleu 2.6.0) in `work/tools/mt-venv` (Python 3.12: torch 2.14.1+cpu, transformers 5.18.0, ctranslate2 4.8.2, sentencepiece, llama-cpp-python, sacrebleu); models under `work/tools/mt-models/`. Outputs: `raw-<engine>.jsonl` (engine output), `post-<engine>.jsonl` (after `post`, with each row's problems), `scores.json`, `side-by-side.tsv`.

### 7.5 Rules every translated row must pass

These are checks in the build (and in `tools/english_mt.py`'s `check()`), for MT and human rows alike. A row that fails is served in Japanese and listed in the report, never served broken.

| Rule | Check | Why |
|---|---|---|
| printf specifiers | the same specifiers in the same order (`%d`, `%s`, `%u`, `%02d`, `%.5f`; no space flag, so `50% c…` is prose); a literal percent after a specifier must be `%%` | the client fills them with printf: a missing or extra one reads the wrong argument (1.1) |
| Positional specifiers | none (`%1$s`, `%2$d`); a bare `%` in a printf row becomes `%%` | the port's printf doesn't support them (3.3); reword instead of reordering arguments |
| Markup | the same tags: `<font color=…>…</font>` in labels, `<player>`, `<fontcolor=…>`, `<fontsize=…>`, `</font>` in story; no Global token (`<NUM>`, `<STR>`, `<INSERT>`, `<EMDASH>`) | an unknown story tag likely crashes `ParseMessage` (3.3) |
| Glyphs | every character in the font (3.1); folding first: accents stripped, `—` → `―`, `–` → `-`, curly quotes → ASCII, `•` and `·` → `・`, `™` `®` dropped | a missing glyph draws as `?` |
| Glossary | every glossary term in the Japanese appears as its English (or an accepted variant; case, line breaks and a plural `s` ignored) | Q8: Global's terminology everywhere |
| No Japanese left | no kana or kanji | a half-translated row is worse than a Japanese one |
| Width | story and multi-line rows re-broken at spaces to the budget with the font's advances; single-line rows reported when wider than 1.5× the Japanese | the client never wraps (3.2) |

- **Line budgets.** The trial used the Japanese row's own widest line for multi-line master rows, and for the story the p99 widest JP story line, 407 px (max 483). The build now uses 480 px, measured on screen (7.6 "The story tables"). JP story lines have 1–4 lines (5+ in 266 of 21,663). Global's official story English (EP1, `TS_3xxx`, `TS_5xxx`) re-broken at 407 px needs 5 or more lines in 675 of 4,893 lines (at 483 px: 281). So about one story line in ten needs a shorter wording or a smaller font. The user chose the smaller font (2026-10-07): the client scales the message window's font to fit (E13, 7.13); `<fontsize=…>` turned out not to be a size the 3.7.0 client applies (7.13).
- **Style per kind** (the prompt's rules, from Global's practice): UI labels and buttons terse, title case; descriptions one plain sentence; stat lines in Global's formula ("Damage dealt +55% at 100% HP", "(party)", "(self)", "(N seconds)"); dialogue natural, in the speaker's voice; names transliterated as the glossary has them.

### 7.6 Storage, provenance and editing

**The source of truth is a translation table in the repo, not engine output and not a database.**

- **Layout** (`data/english/`; built 2026-10-06, see "As built" below):
  - `glossary.tsv`: `ja, en, kind, variants, source (official|human), note`. Generated from Global, then edited by hand; a `human` row wins over a generated one and survives regeneration.
  - `master.tsv`: one row per JP `message_id` that isn't official by id: `message_id, ja_sha1, en, source, engine, date, editor, note`.
  - `story/TS_xxxx.tsv`: the same per story file, **without the Japanese text** (it is not in git; 7.6 below).
  - Sorted by `message_id`, UTF-8, `\n` as the two characters, so diffs are one line per row and a build is byte-reproducible.
- **Provenance** (`source`):
  - `official`: Global, by id. Not stored: derived at build time from `data/basmaster-gl.sqlite3` (already in git).
  - `memory` / `template`: derived at build time (7.2); not stored.
  - `machine`: an engine wrote it. `engine` names the engine and model version and its prompt version (e.g. `claude-sonnet-5-5/prompt-v1`), `date` the run.
  - `human`: a person wrote or edited it (`editor` = who).
  - `reviewed`: a person checked a `machine` row and kept it unchanged.
- **Changed source text.** `ja_sha1` is the SHA-1 of the Japanese the row translates. A different hash at build time marks the row **stale**: reported, and served only if the user says so. 3.7.0 is the last version, so this mainly catches a wrong master or a mis-keyed row.
- **Precedence at build:** `human` and `reviewed` > `official` > `memory`/`template` > `machine` > Japanese. A human row may override Global (the "Time Left  Left" composition of section 2); the report lists every such override.
- **Re-running MT never touches** `human` or `reviewed` rows. It writes only rows that are missing, or `machine` rows whose hash, engine or prompt version changed, when asked to. So a human edit is permanent until a human changes it.
- **Editing.**
  - A small CLI (`tools/english_text.py`, built: see "As built" below): `show ID` (JA, Global's reference, current EN, width, problems), `set ID TEXT --by NAME`, `review ID…`, `stale`, `report` (coverage per source and prefix, failing rows, width outliers, the 803 rows with stale Global English and their old English).
  - **PO round trip** for Poedit, Lokalize or Weblate: `export-po` writes one `.po` per category to `work/english/po/` with `msgctxt` = message_id, `msgid` = the Japanese (from the master or the download at export time), `msgstr` = the English, `#,fuzzy` for `machine` rows, and the provenance and Global's reference as comments; `import-po` turns a changed `msgstr` into a `human` row and a cleared `fuzzy` flag into `reviewed`. The `.po` files are a working copy in `work/`, never the source of truth: their `msgid` is the game's Japanese.
  - **Spreadsheet round trip**: the same as CSV (JA, Global, EN, width in px, problems), imported by `message_id`.
- **How the server consumes it.** The `-en` master builder (C1) and story builder (C3) read only the committed tables, the two master DBs and the download, apply the precedence and the checks, fold glyphs and break lines with the font's advances, and write the files. **No engine is called at server start** (an API isn't reproducible, and a server must not need the network). Same inputs, same bytes, so the CDN's version ids stay stable.
- **What is safe to commit** (the user's game-file policy, README.md "Game files"):
  - The master's Japanese is already in git (`data/basmaster-3.7.0.sqlite3`), and so is Global's English. A table of our English keyed by `message_id` adds no game data beyond what's there: committable, like the master DBs.
  - The story's Japanese is **not** in git (only in the 3.7.0 download, `work/SOA-3.7.0-canonical-data.zip`). The story tables therefore hold `message_id`, a hash and our English, and no Japanese; tools read the Japanese from the download when they need it.
  - Our English is still a translation of the publisher's text: whether it goes into git, and whether release packages carry it (they never carry game files), is the user's call (PLAN-english.md M-Q5; decided: both, and the packages carry the tables `master-en.tsv` and `story-en/`, from which the packaged server builds the `-en` files at every start: P2; changed 2026-10-07: the tables hold only our rows, and the packages ship `data/basmaster-gl.sqlite3`, from which the official English is derived). The glossary of names is small and needed in any case.
  - Engine outputs before review (`raw-*.jsonl`), PO exports and the trial stay in `work/`.

**As built** (2026-10-06, agent `en-data`; PLAN-english.md E1, M1, E3). The tool is `tools/english_text.py`. Its shared library, also used by `tools/english_mt.py`, is `tools/english_core.py`. The test is `tests/test_english_text.py` (T0).

- **Files** in `data/english/`:
  - `master.tsv`: only `machine`, `human` and `reviewed` rows (columns as above).
  - `glossary.tsv`: only `human` and `machine` rows (M2's names: kind `name`). Global's terms (`official`) are derived at load time (`english_core.build_glossary`) and not committed (the user's decision of 2026-10-07). Per term a `human` row wins over `official`, which wins over `machine`; an empty `en` removes the term.
  - `client-strings.tsv`: `message_id, en, note`; the client's `port_en_*` strings, merged as `human` rows with an empty `ja_sha1`.
  - `master-en.tsv`: **generated** by `build`: `message_id, ja_sha1, en, source`, sorted. **Since 2026-10-07 (the user's decision) it holds only our rows**: every `machine`, `human` or `reviewed` row of `master.tsv`, and every client string, that passes its checks, already post-processed. Official, memory and template English is derived at build time from `data/basmaster-gl.sqlite3`, by `tools/english_text.py` and by the server's `-en` builder ([7.9](#79-the-derivation-spec)), and is not committed; the packages ship `data/basmaster-gl.sqlite3`. `build --check` (and the T0 pytest) fails when this file or `glossary.tsv` is stale. `tools/english_text.py derive --out DIR` writes the full resolved tables (`master-en-full.tsv`, `story-en-full/TS_*.tsv` and `index.tsv`, the old committed format): the reference for the C++ port.
- **The font** is read from the committed APK (`assets/builtin_data/Font/etc2/font.fpk`, the same file as the download's): ADLD, then SLZ (all chunks), then the ISF member `fontData.bin`, whose 7,133 records give the advances. `work/english/font/glyphs.pkl` is no longer needed.
- **Candidates per JP row**, in order: `human`/`reviewed` > `official` (Global by id; or a Global token row rewritten by E3) > `memory`/`template` > `machine`. The first candidate that passes the checks is served. A failing candidate is listed and the next one is tried. A table row with a different `ja_sha1` is stale and is not served.
- **What every candidate gets:** NFC (human rows), glyph folding, and the `%%` rule in printf rows (this makes `uimsg_deep_space_new_area_term`'s Global "%d% or above" safe).
- **Global's own line breaks are kept.** Re-breaking official multi-line rows to the JP row's widest line would make 1,873 of 2,299 rows taller than the Japanese. Only rows whose Japanese has `\n` and whose English has none are re-broken (official 460, memory 131, template 5). `machine` rows are re-broken at import.
- **Check strength per source.** These choices keep Global's 19,145 rows whole:
  - **Glossary:** a hard check for `machine`, `human` and `reviewed` rows. For official, memory and template rows it is only a warning (627 rows): the glossary is mined from Global, so Global's rows define it.
  - **Tags:** strict (the same tags) for `machine` rows. For official, memory, template and human label rows the English may use a subset of the Japanese row's tag kinds, with balanced `<font>`/`</font>`. This covers 16 Global tutorial rows that colour fewer or more words. Story lines will use the strict check (unknown story tags crash).
- **E3** (`english_core.rewrite_tokens`, shared by the master and the story):
  - `<EMDASH>` becomes `―`.
  - `<INSERT n>one/many</INSERT>` becomes the plural form.
  - `<NUM n>`/`<STR n>` becomes the JP row's n-th printf specifier, spelled as JP spells it (`%02d`, `%u`). This needs each JP argument used exactly once, in JP's order.
  - Result: 37 master rows become official. The other 22 rows have no specifier in JP: the client composes the name around the fragment (`uimsg_block_*`, `follow_*`, `loginbonus`…). They stay gaps and are listed in `token-gaps.tsv`.
  - In the story: EP1 2,979 official + 117 by E3, 10 gap lines left; `TS_3xxx` +16; `TS_5xxx` +11.
  - No served row has a Global token.
- **Counts of the first build:**
  - Candidates: official by id 19,145, E3 37, exact memory 6,265, template 2,412, language-neutral 1,527, gap 37,559.
  - Served: 27,859 rows (official 19,182, memory 6,265, template 2,412), 0 failing.
  - Reported: 7,916 single-line rows over 1.5× the Japanese width, 803 Q7 rows, 302 glossary conflicts.
- **Commands:**
  - `build [--check]`.
  - `report [--out DIR]`: the summary to stdout; `prefixes`, `failing`, `width`, `q7`, `token-gaps`, `e3`, `glossary-conflicts`, `glossary-warnings`, `overrides`, `stale` `.tsv` files and `summary.json` in `work/english/report/`.
  - `show ID…`, `set ID TEXT --by NAME` (refused when it fails a check, unless `--force`), `review ID… --by NAME`, `stale [--fail]`.
  - `export-po`/`import-po` (polib; `work/english/po/<prefix>.po`).
  - `export-csv`/`import-csv`.
  - `import-mt CHECKPOINT.jsonl [--replace]`: rows of the MT runner, writing `machine` rows with `engine` = `model/quant/prompt/llama.cpp-build/tTemperature`.
    - It writes only rows in the gap. It never touches `human`/`reviewed` rows, and replaces a `machine` row only with `--replace` when the hash, engine or prompt changed.
    - Rows failing the checks go to `work/english/mt-rejected.tsv` and are counted by `report`.
  - Edits rebuild `master-en.tsv` unless `--no-build` is given.

**The story tables** (2026-10-06, agent `en-data`; PLAN C3 data side, E7 data side, M4 import).

- **Files:**
  - `data/english/story/TS_xxxx.tsv`: the `machine`/`human`/`reviewed` rows of one Scenario file, with the columns of `master.tsv` and no Japanese.
  - `data/english/story-en/TS_xxxx.tsv`: **generated**, `message_id, ja_sha1, en, source`: since 2026-10-07 only our rows (as `master-en.tsv`), for every file with any. Official story lines are derived ([7.9](#79-the-derivation-spec)).
  - `index.tsv` (`file, lines, need, english, complete`) is no longer committed: it counts derived lines too, so the server computes completeness itself; `derive` writes it into `story-en-full/` as the reference.
    - `need` counts the lines with kana or kanji; language-neutral lines (`……`) need no row.
    - The server serves `TS_x-en.msgp` only when `complete` is `yes` (Q12).
- **The hash.** A story line's `ja_sha1` is the SHA-1 of the Scenario row's `text_value` exactly as the file holds it: UTF-8, with **real newlines**. This is unlike the master's two-character `\n`. `en` uses the two-character `\n`.
- **Where the Japanese comes from.** It is read from the download's `Scenario/` at build time (`work/SOA-3.7.0-canonical-data.zip`, read in place; `--scenario PATH` names another zip or folder, or a folder of `TS_*.msgp`). Without it, `build` and `build --check` skip the story part and say so, and the story pytests skip.
- **Candidates:** `human`/`reviewed` > official (Global by id, plus E3) > `machine`.
- **Checks:**
  - No Global token, every glyph in the font (after folding), no kana left.
  - Every tag must be one `ParseMessage` reads (`<player>`, `<font color=…>`, `<fontcolor=…>`, `<fontsize=…>`, `</font>`).
  - Tags must equal the Japanese line's exactly for `machine` rows.
  - Official and human lines may colour other words, or name `<player>` where the Japanese says 艦長, as long as `<font>` stays balanced. Without this, 16 EP1/`TS_5xxx` lines that no MT run translates would block their files.
- **Line breaking (E7, data side).** Every served line is re-broken at spaces to a message window of **480 font px** (2026-10-07; first 407 px, the p99 widest JP story line). The width was measured on a `--lang en` campaign shot (`work/english/exec/art/final-campaign/shots/85-story.png`, 729 px wide): 388 font px show as 486 px (scale 1.25), the text starts at x≈57 and the window is symmetric, so there is room for ≈615 display px ≈ 492 font px; the widest JP story line is 483. `<player>` is counted as 120 px (an assumption: about 8 Latin letters).
  - At 480 px, 290 served official lines need 5 or more lines (690 at 407 px); `report` lists them in `story-long.tsv`. The change re-broke 3,498 of the 5,037 served story lines; their ids, sources and the completeness are unchanged, and the master is byte-identical.
  - Lines over the window's four lines: the client shrinks the font (E13, 7.13); no shortening.
- **First build:**
  - 4,625 of the 21,663 story lines that need English have it (official 5,037 rows including 412 language-neutral lines Global spelled out), 0 failing.
  - 24 of 64 files are complete: EP1 10 of 11 (10 lines missing), `TS_3xxx` 9 of 10, `TS_5xxx` 5 of 7.
- **`import-mt`** reads the story checkpoint (`"kind": "story"`, a `lines` list) with the master's rules. Failing lines go to `work/english/mt-rejected-story.tsv`.
- **`report`** adds the story per group: lines official, machine, human, reviewed, missing and failing, and the complete files. Its lists are `story-files.tsv`, `story-long.tsv`, `story-failing.tsv` and `story-stale.tsv`.
- **The editing tools take story ids too:** `show`, `set`, `review`, `stale`, `export-po` (`TS_xxxx.po`, msgid = the download's Japanese at export time), CSV and the imports.

**Composed fragments** (2026-10-07, agent `en-data`; E3's second half). Some texts are fragments the client joins, so their English has to read right **in place**. These are now `human` rows with editor `english-exec`, listed in `report`'s `human.tsv` (and `overrides.tsv` where they replace Global's text).

- **Name fragments: a suffix after the name.**
  - The block, follow, unfollow and unblock texts, the shortage texts and the disconnect texts are appended to a name: `GetSystemMessage(id)`, then the name is inserted at position 0 (`CFollowSelect::Progress`, `CFriendMenu`, `CGachaShortage::UpdateData`).
  - Their English is a suffix with its leading space: `uimsg_block_decide` = " has been blocked.", `uimsg_gacha_item_shortage` = ":\nnot enough.".
  - `uimsg_rentalbonus_num` "%u players" + `_main` " borrowed your character." are composed the same way (`CRentalBonus::Setup`).
  - `uimsg_loginbonus` is " Day Login Bonus", after the day number.
  - `uimsg_boxgacha_*_num` are "Resets Left", a label beside the number.
- **Remaining time and end dates: `CUIUtility::GetBannerEndTime`** (Ghidra 0x1ecb8b4). The only caller of `CTimeUtility::RemainTypedText` composes:
  - `uimsg_remain_base` + `%d` + a unit (`uimsg_year`, `uimsg_month`, `uimsg_day_on_day`, `uimsg_hour`, `uimsg_min`, `uimsg_sec`, from a table at Ghidra 0x2b9fde8).
  - Under a day, `uimsg_time_to_the_end` comes first. A day or more gives `uimsg_time_limit_head` + the weekday + `uimsg_time_limit_tail`.
  - `uimsg_time_limit` ("Time Left") labels the value on the achievement and event screens.
  - **Every remaining-time text goes through `RemainTypedText`** (Ghidra 0x1ecbe88): `RemainTypedTextAuto`, `RemainTimeText` and `RemainTimeDateFromNowText` pick the unit (days up to 99, hours, minutes, seconds) and call it. The achievements list's label comes from `CParameterUtility::tAchievement::Time` → `RemainTimeDateFromNowText` (or `uimsg_achievement_non`), so the empty `uimsg_remain_base` fixes it too. The proof is a `--lang en` home session on 2026-10-07 with the derived full table (`--english-text`, `work/english/exec/en-data/home-en/shots/`): `26-achievements.png` "Time Left  1d", `10-event.png` "Ends in 6h", `25-present.png` "Expires In: 29d" (Global's label, no doubled "Left:"). The shot with "Time Left  Left:1d" was taken with a master from before the fix.
  - Global's "Left:" therefore read "Time Left  Left:2d" (section 2), and "Until: " ran into the weekday. The new rows are:
    - `uimsg_remain_base` = "" (empty), giving "Time Left 2d" and "Ends in 5h";
    - `uimsg_time_to_the_end` = "Ends in ";
    - `uimsg_time_limit_tail` = " until %d:%02d", giving "2021/7/25(Thurs) until 14:00".
- **Not done:** `uimsg_chiket_error` (チケットが) and `uimsg_gacha_need_head` (紋章石が) are heads whose continuation wasn't found; they stay Japanese until it is.

**Glossary rules** (2026-10-07):

- **Matching:**
  - accents are ignored (the output is folded);
  - a label's trailing colon or full stop is ignored ("Role:" matches "Roles");
  - -y/-ies plurals count, besides -s.
- **Weak Global terms** (`tools/english_text.py glossary-weak [--apply]`):
  - **Rule:** an official term of kind `ui`, `skill`, `talent` or `speaker` is demoted when Global's own official English misses it in at least half of at least 3 rows (master by id and story).
  - Applied, this removed 35 terms with `human` rows whose `en` is empty, for example:

    | Term | Global's glossary English | Missed in |
    |---|---|---:|
    | モンスター | Enemies | 43 of 44 |
    | 願い | Wish | 41 of 47 |
    | 全員 | Everyone | 33 of 35 |
    | 上限解放 | Cap Inc. | 39 of 52 |
    | 紋章石購入 | Purchase Gems | 22 of 23 |
    | 片手剣 | OHS | 11 of 12 |
    | 強化素材 | Mats. | 10 of 15 |
    | 乱射 | Rapid Fire | 6 of 7 |

  - These are labels' abbreviations and ordinary words, not names.
  - Nine more ordinary words with too few Global rows for the rule (期間：, 分裂, 殴り, 突進, 融合, 産卵, 咆哮, 嘲笑, 怒り) were removed by hand.
  - Names of people, items, missions and areas are kept (Q8).
- **M2's machine names that Global's text contradicts:** `glossary-weak` also lists them. Many of these names occur in Global's running text, not in its name fields, so the name pass didn't know Global's spelling. They now have `human` rows with Global's spelling, for example:

  | Term | M2's machine spelling | Global's spelling | Global rows |
  |---|---|---|---:|
  | リーシュ | Leash | Eve | 130 of 131 |
  | ランビュランス | Lamburance | Levarance / Purge | 113 |
  | ローク | Roque | Roak | |
  | クロノス | Chronos | Kronos | |
  | シーハーツ | Sea Hearts | Aquaria | |
  | アーリグリフ | Ariglyph | Airyglyph | |
  | エリクール | Elikoor | Elicoor | |
  | フェイクリード | Fakelead | Faykreed | |
  | バーニィ | Bernie | Bunny | |

  36 names in all. リム and オバ (parts of words) and ステップアップキャラガチャ (a label) are removed.
- **Effect on the UI batch.** A dry run of `import-mt` on the UI batch (about 8,150 rows so far, into a scratch dir) went from 87 glossary rejections, mostly the weak terms, to 93 that are almost all the corrected names. Those MT rows used M2's spellings, so they should be re-translated with the corrected glossary.
- **Width (informational, E10 wraps labels):** `report` lists the single-line rows wider than the 720 px design width at the font's size (`wider-than-screen.tsv`: 1,267 rows).

### 7.7 Recommendation

Revised after the local-LLM trial (7.8) and the user's decisions of 2026-10-07 (PLAN-english.md).

- **First the free, deterministic steps:** E3's token rewrites (117 EP1 lines become official), template memory (2,412 rows), and the glossary.
- **Engine: a local LLM on this machine's GPU is now a real option, not just a fallback.** Gemma 4 31B-it (Apache-2.0, GGUF QAT Q4_K_XL, 17 GB) through llama.cpp scored the same as Claude Opus 5.5 on the blind trial (chrF 44.3 against 44.4; with the conventions prompt 44.9) and kept every token. It costs nothing but GPU time, sends no text out, and every run can be repeated from the committed glossary and prompt. For speed, Gemma 4 26B-A4B (16 GB, a mixture of experts) is about three times faster at chrF 43.8–44.3, with one dropped name in 20 EP3 lines.
- **Claude through the Batch API stays the stronger choice for names and story tone** (it is the only engine that wrote マスティマ as "Mastema"; 7.8), at tens of dollars and with the text sent to Anthropic. A good split: the UI and system text (M3) locally, and a decision on the story engine (M4) after a look at a full scene from each.
- **Whichever engine:** the conventions prompt (7.8's "v2": Global's `（全体）` = "(party)", `・改` = "Revised", the `%%` rule) and a richer glossary, every row through the checks of 7.5, the story a scene at a time with the speakers named.
- **New names** (M-Q7): the engine's first spelling becomes the glossary entry and is reused everywhere after. The local models spelled EP3's names inconsistently between models (リーシュ: "Leesh", "Leash", "Rish", "Lishe"), so the name pass should run once, before the story, as a list of the new proper nouns with their context, through the strongest engine available.
- **Fallback without a GPU:** FuguMT through CTranslate2 (CC-BY-SA model, no glossary, chrF 32), as a clearly-marked rough fill only.
- **Review** (M-Q4): `machine` rows may ship unreviewed; the provenance and the coverage report mark them, and every row stays editable.

### 7.8 Local LLMs on the GPU (12–31B)

Investigation of 2026-10-07 (agent `english-llm`), at the user's request (M-Q3): **does a larger local LLM on this machine's GPU come near the API's quality?** The user lifted the download limit for this test; models only under `work/tools/mt-models/`.

**Setup.**

- **Machine:** NVIDIA RTX PRO 4000 Blackwell (24 GB; 145 W), 32 threads, 45 GB RAM, WSL2. During the runs the load average was about 1 (the earlier trial ran at about 50); the GPU was mostly free, with 0.4–6 GB held by another program at times. `nvidia-smi` was checked before each model load.
- **Runtime:** llama.cpp b11443, the official prebuilt Ubuntu CUDA 12.8 build with its cudart/cuBLAS libraries (`work/tools/llama.cpp-cuda/`, 1.1 GB; no CUDA toolkit needed; the WSL driver's `libcuda` from `/usr/lib/wsl/lib`). `llama-server` with every layer on the GPU (`-ngl 99`), flash attention, 3,072 tokens of context per slot, thinking off (`-rea off`, `enable_thinking: false`), prompt cache off, 4 or 8 parallel slots. One row per request, temperature 0.
- **Prompt:** exactly the Claude runs' prompt (the system rules and each row's kind, glossary hits and Japanese from `claude-input.txt`): no reference, no sampled id in the glossary (7.4). A second prompt, **v2**, adds Global's conventions (`（全体）` = "(party)", `（自分）` = "(self)", a name ending in `・改` = "Revised" before the name, `紋章石` = Gems), the `%%` rule and "no Japanese may remain"; it ran on the two best Gemma models only, and **Claude was not re-run with it**. v2's conventions were seen in the trial's references, and three scored `factor` rows use "(party)", so v2's gain is partly that.
- **Scoring:** the same `score.py` and `tools/english_mt.py post` as 7.4 (re-scoring the earlier engines reproduced their numbers exactly).
- **Candidates** (all Apache-2.0 by their model cards; GGUF conversions by unsloth and mradermacher under the same licence):

| Model | Kind | Quantization | File |
|---|---|---|---:|
| Gemma 4 31B-it (Google, 2026-03) | dense, 31.3B (the edge of "up to 31B") | unsloth QAT UD-Q4_K_XL | 17.3 GB |
| Gemma 4 26B-A4B-it | mixture of experts, 25.8B, about 4B active | unsloth UD-Q4_K_M | 17.0 GB |
| Gemma 4 12B-it | dense, 12.0B | unsloth Q4_K_M | 7.1 GB |
| Qwen3.8-27B (Alibaba, 2026-08) | dense, 27.8B | unsloth UD-Q4_K_M | 16.5 GB |
| shisa-v2-mistral-small-24b (Shisa.AI) | Mistral Small 3.1 24B tuned for Japanese and English | mradermacher i1-Q4_K_M | 14.3 GB |

  Not run: Qwen3.5-35B-A3B (35B, over the limit), PLaMo 2 Translate (10B, a dedicated JA↔EN model, but under the PLaMo community licence with revenue limits and registration), Mistral Small 3.2 (the shisa model covers its base), the Qwen3 30B-A3B of 2025 (superseded by Qwen3.8).

**Scores** (the 250 rows with Global's English; tokens kept of 36 rows with specifiers or tags; glossary followed of 85 rows with hits; rows with kana left of 310; throughput for the 310 rows, 7,233 JA characters, the GPU to itself):

| Engine | chrF all | master | story | chrF++ | BLEU | tokens | glossary | kana | JA chars/s | hours for 1.24M |
|---|---:|---:|---:|---:|---:|---:|---:|---:|---:|---:|
| Claude Opus 5.5 (7.4) | 44.4 | 47.4 | 36.5 | 41.8 | 21.1 | **36** | **84** | 0 | API | about 1 |
| Claude Sonnet 5.5 (7.4) | 43.8 | 47.3 | 34.5 | 41.3 | **21.3** | **36** | 83 | 0 | API | about 1 |
| **Gemma 4 31B, v2 prompt** | **44.9** | **47.9** | **36.8** | **42.3** | 20.0 | **36** | 81 | 0 | 31.0 (4 slots) | 11.1 |
| **Gemma 4 31B** | 44.3 | 47.1 | 36.6 | 41.6 | 19.4 | **36** | 81 | 0 | 38.7 (4 slots) | 8.9 |
| Gemma 4 26B-A4B, v2 prompt | 44.3 | 47.2 | 36.5 | 41.7 | 20.3 | **36** | 80 | 1 | 92.3 (8 slots) | 3.7 |
| Gemma 4 26B-A4B | 43.8 | 46.6 | 36.4 | 41.3 | 19.5 | **36** | 81 | 2 | **108.5** (8 slots) | **3.2** |
| Qwen3.8-27B | 44.0 | 47.8 | 33.6 | 41.5 | 20.3 | 34 | 79 | 1 | 45.4 (8 slots) | 7.6 |
| Gemma 4 12B | 43.4 | 46.0 | 36.3 | 40.8 | 19.4 | 35 | 82 | 0 | 80.8 (8 slots) | 4.2 |
| shisa-v2-mistral-small-24b | 37.6 | 39.0 | 33.2 | 35.0 | 11.0 | 32 | 81 | 16 | 105.4 (8 slots) | 3.3 |
| Qwen2.5-1.5B, CPU (7.4) | 35.3 | 38.5 | 26.6 | 32.5 | 10.6 | 20 | 74 | 11 | 4.6 | 75 |
| FuguMT, CPU (7.4) | 32.3 | 33.1 | 30.1 | 29.6 | 12.2 | 28 | 31 | 1 | 21–27 | 13–16 |

  Per stratum (chrF; `seed`/`factor`, skills/talents, `name`, UI, EP1 story): Opus 60 / 44 / 52 / 45 / 37; Sonnet 67 / 46 / 49 / 43 / 35; Gemma 4 31B 51 / 46 / 51 / 44 / 37 (v2: 55 / 48 / 52 / 44 / 37); 26B-A4B 48 / 46 / 46 / 46 / 36; Qwen3.8-27B 66 / 46 / 49 / 45 / 34; Gemma 4 12B 52 / 49 / 47 / 45 / 36.

- **Significance.** A paired bootstrap of chrF (1,000 resamples of the 250 rows) puts every 12–31B model but shisa within noise of Claude Opus: Gemma 4 31B −0.2 (95% interval −1.4 to +1.0), v2 +0.5 (−0.8 to +1.6), 26B-A4B −0.6 (−2.0 to +0.6), Qwen3.8-27B −0.5 (−2.2 to +1.1), Gemma 4 12B −1.0 (−2.6 to +0.3), Sonnet −0.6 (−1.7 to +0.4). shisa is −6.8 (−9.7 to −4.3), FuguMT −12.2. chrF against one reference can't rank these models; the checks and the rows below do.
- **Run-to-run variation.** With parallel slots the output isn't fully deterministic (batched arithmetic): two identical 8-slot Qwen3.8 runs differed in 33 of 310 rows (a 4-slot run in 37), and the scores moved by up to 0.4 chrF. A run for the table should use one slot, or accept this and rely on the table's provenance, not on re-running.

**What the rows look like** (Japanese and Global; then Claude Opus / Gemma 4 31B / 31B v2 / 26B-A4B / Qwen3.8-27B):

| Japanese | Global | Claude Opus | Gemma 4 31B | Gemma 4 31B v2 | Gemma 4 26B-A4B | Qwen3.8-27B |
|---|---|---|---|---|---|---|
| ＨＰ１００％時に与ダメージ＋５５％ | Damage dealt +55% at 100% HP | Damage Dealt +55% at 100% HP | Damage +55% when HP is 100% | Damage +55% when HP is 100% | Damage +55% when HP is at 100% | Damage dealt +55% at 100% HP |
| ＤＥＦ＋１０％（全体） | DEF +10% (party) | DEF +10% (All) | DEF +10% (All) | DEF +10% (party) | DEF +10% (All) | DEF +10% (All) |
| フリージングインパクト・改 | Revised Arctic Impact | Arctic Impact+ | Arctic Impact+ | Revised Arctic Impact | Arctic Impact 改 | Arctic Impact II |
| 消費ＡＰ－５０％（２０秒間） | AP cost -50% (20 seconds) | AP Cost -50% (20 sec) | AP Cost -50% (for 20 sec) | AP Cost -50% (for 20 sec) | AP Consumption -50% (20 sec) | AP Consumption -50% (20 seconds) |
| `<player>`、お願いじゃ、協力してくれ！ (EP1) | `<player>`, please will you come with me? | `<player>`, I beg you, please help us! | `<player>`, I'm begging you, please help me! | the same | `<player>`, I'm asking you, please help me! | `<player>`, I'm asking a favor. Please help me! |
| ……のうマスティマ。先ほどウルザ・システムの稼働にはエネルギーが必要と言っておったが、 (EP3) | — | ...Say, Mastema. Earlier you said the Ursa System needs energy to run, | ...Now then, Mastima. You mentioned earlier that the Urza System requires energy to operate, | the same | ...Now, Mastima. You were saying just a moment ago that energy is needed to activate the Urza System, | ...No Mastima. You said earlier that the Ulza System requires energy to operate, |
| 任官して間もないわたしにとって、今際の際の約束というものはとても衝撃でした。 (EP3) | — | For me, freshly commissioned, a promise made on someone's deathbed came as a real shock. | For someone like me, who was only recently commissioned, a promise made at the moment of death was quite a shock. | the same | For someone like me, who has only just been commissioned, the idea of making a promise on one's deathbed... it was quite a shock. | For someone who had just taken office, the promise made on the brink of death was a tremendous shock. |
| リーシュっ！ (EP3) | — | Lishe! | Leesh! | Leash! | Leash! | Rish! |

**Failure modes seen:**

- **Gemma 4 31B:** the cleanest of the local models: no token lost, no Japanese left, and its four glossary misses are the glossary's own weak entries (全員 = "Everyone", 願い = "Wish", 強化素材 = "Mats.", 期間： = "Expires In:"), of which Claude Opus missed only 願い. Without v2 it writes stat lines in its own order ("Damage +55% when HP is 100%", lower `seed`/`factor` chrF than Claude and Qwen) and "(All)" for `（全体）`, as Claude did; with v2 it follows the conventions it was told. Names in EP3 are plausible but not always the intended ones (マスティマ "Mastima" for Mastema).
- **Gemma 4 26B-A4B:** one invented specifier (`FOLを入手しました。` → "Obtained %d FOL."), `・改` left in Japanese once, and one wrong name: ヴァルとトオル ("Val and Toru") became "you and Terry" in an EP3 line. Otherwise close to the 31B.
- **Qwen3.8-27B:** the best on Global's stat-line formula without being told, but dropped `<font color=…>…</font>` from two EP1 lines (2 of 36 token rows), left kana once, and its story lines are flatter (EP1 chrF 34).
- **Gemma 4 12B:** close behind the large models on UI, but invented a third `%d` in `%d年%d月生まれ` ("Born on %d/%d/%d"), the kind of error the checks catch.
- **shisa-v2-mistral-small-24b:** the Japanese-tuned model is the weakest of the set here: it appends translator's notes to 19 of 310 rows ("(Note: The original Japanese text is very concise…)") despite the rule, leaves Japanese in 16 rows and loses tokens in 4. Not a candidate.
- **All local models** share Claude's weaknesses of 7.4 (inventing a form where Global has a convention unless told) and widen labels the same way (65–78 of the 250 scored rows over 1.5× the Japanese width, Global 60).

**Throughput and the GPU.**

- One row per request, as measured above. The MoE Gemma 4 26B-A4B is the fastest large model (108 JA characters per second: **3.2 hours** for the 1.24M characters of the gap). The dense 27–31B models do 39–45 characters per second (**8–10 hours**): they are bound by the memory bandwidth of a 145 W card. More slots don't help once the GPU memory is full: Qwen3.8 with 16 slots and Gemma 4 31B with 8 ran 2–3 times slower than with 8 and 4 (apparently WSL spills to shared system memory instead of failing).
- **The 31B needs the whole card.** With 4 slots it uses about 22.5 GB. Leaving 7 GB for other programs (`--fit-target 7000`: llama.cpp keeps some layers on the CPU) cut it to 13.2 characters per second (**26 hours**); the 26B-A4B under the same limit did 60 per second (**5.7 hours**: its experts move to the CPU cheaply). So the 31B is a job for a night with the GPU free; the 26B-A4B also runs beside other work.
- A real run would send a story scene or a batch of related UI rows per request, which saves repeating the system prompt and gives context; the times above are an upper bound for one-row requests.

**Disk used** (`work/tools/`, local only): Gemma 4 31B 17 GB, Gemma 4 26B-A4B 16 GB, Qwen3.8-27B 16 GB, shisa-v2 14 GB, Gemma 4 12B 6.7 GB, llama.cpp 1.1 GB: **about 71 GB**, on top of the first trial's 1.7 GB. The models are kept for the user's choice; any but the chosen one can be deleted.

**Verdict.** On this sample a quantized 31B model on the local GPU is as good as the Claude API by every automatic measure: chrF within noise, every token kept, the glossary followed nearly as often. **Gemma 4 31B-it with the v2 prompt is the best local engine**; Gemma 4 26B-A4B is the fast alternative. Where Claude still looks better is what the sample measures least: new proper nouns and story tone, on 20 EP3 lines without a reference. The engine for M3 (UI) can be local; for M4 (story) the user should compare a full scene from each before choosing.

How measured: `work/english/mt-trial/engines/serve.sh` (llama-server), `run_server.py` (the prompts, timing), `score.py`, `bootstrap.py`; outputs `raw-<engine>.jsonl`, `post-<engine>.jsonl`, `timing-<engine>-c<slots>.json`, `scores.json`, server logs `server-*.log`. Models in `work/tools/mt-models/<name>-gguf/`.

### 7.10 The MT run as executed (2026-10-06, agent `english-exec`)

`tools/english_mt_run.py` (llama.cpp b11443 `llama-server` from `work/tools/`, one request per item,
temperature 0, row-level checkpoints in `work/english/mt/*.jsonl`, resumable) ran the plan's M2–M4;
`tools/english_text.py import-mt` turned the checkpoints into `machine` rows. Every row's `engine`
field names model, quantization, prompt version, llama.cpp build and temperature.

| Pass | Items | Engine | Result |
|---|---:|---|---|
| M2 names (`names`, names-v1) | 4,489 katakana terms of the gap and the story | Gemma 4 31B, 4 slots, ~62/min | 1,259 proper nouns (seen in 2+ texts) into `glossary.tsv` as `machine`; `glossary-weak` later replaced 36 with Global's in-text spelling |
| M3 UI (`ui`, v2) | 27,847 distinct texts (37,593 rows) | 31B for 10,858 (~50/min); the 26B-A4B fallback for 16,989 (~125/min, 6 slots) after other programs held 2–4 GB of the GPU for 25 min | 37,456 rows imported; 82 rejected (they stay Japanese); 1,711 texts were translated again after the glossary corrections |
| M4 story (`story`, v2+story-v1) | 1,696 requests (up to 12 lines, speakers named, 4 lines of context; events, EP2, EP3, then the rest) | 26B-A4B, ~30/min | 16,872 lines; 110 chunks with a rejected or skipped line translated again |
| E7 shortening (`shorten`, short-v1) | 2,067 machine lines over four window lines (480 px) | 26B-A4B | 1,951 shorter lines imported (`--replace`); lines of 5+ window lines 2,313 → 1,166 |

- **Checks that mattered.** The glossary (corrected names, Global's Misery 2 / 3 for 滅級 / 絶級),
  tags (an invented `</p>`), specifiers, Japanese left (difficulty marks such as 【滅】), and a
  **runaway** check added for machine rows: the 26B-A4B sometimes repeats a sound thousands of times
  ("CAPTAIIII…", "Ka-ka-ka-…"); a machine row more than 80 characters and 8 times the Japanese, or
  with a 2–8 character unit repeated 12+ times, is refused. A list dot between stat names becomes
  Global's slash at import ("ATK/INT/DEF/HIT/GRD").
- **Coverage after the run** (`tools/english_text.py report`): the master 65,346 of 66,945 rows
  English (official 19,177, memory 6,265, template 2,412, human 36, machine 37,456; the rest is
  language-neutral or rejected); the story 21,497 of 21,663 lines, 37 of 64 files complete and served
  (Q12; the other 27 miss 1–21 lines each, `story-fix` translates them one at a time).
- **GPU sharing.** A 31B batch holds about 22.5 GB; game clients beside it render slowly and gates
  time out. The runner therefore starts only with ≥ 23 GB free and **no game client in the slot
  pool** (`control/soaslot.py status`), and stops the server whenever a client appears or free
  VRAM drops, then waits (the user, 2026-10-07: pause on contention, no model switch for the redo).
- **The 26B-A4B rows are redone on the 31B** (the user, 2026-10-07; PLAN-english.md "M-Q2 redo"):
  `ui` / `story` / `shorten --redo-model gemma-4-26B-A4B-it`, then `import-mt --replace`.

### 7.11 The home speech box (home talk lines)

Investigation of 2026-10-07 (agent `en-homeline`), after the user's report that the English lines on the home screen are too big and overflow; the fix the user chose is at the end of this section. The investigation changed nothing in the client or in `data/english/`. The one tool change is a box check in `tools/english_text.py report` (`BOXES`, `boxes.tsv`).

**Summary.** The home's speech box holds **two lines of 480 font px**: exactly two lines of 20 full-width characters, which is how every Japanese line is written. Of the 2,738 English home lines served, **159 fit** and 2,398 need 3 to 7 lines. The extra lines don't widen or shrink anything: they run down out of the frame, over the main buttons on the home and over the footer in Talk Mode. A re-break at 480 px would rescue only 519 rows. The rest are about 1.3× (median) to 1.7× (p90) too long for two lines. **Recommendation:** a shortening pass to two lines (data, like E7), with a shrink-to-fit layout edit in the served `home-en.csf` as the safety net (server data, no client change).

**Where the text comes from.**

- `CHome::PlayTalk` @01aef4e8 (`Home.cpp`) writes the line into one of two labels of `UI/etc2/home.csf`: `talk_menu_gp/talk_frame/talk_text` on the home, and `talk_menu_talkmode/talk_frame/talk_text` in Talk Mode (会話モード). It writes the speaker into `talk_name` beside it.
- The line is a `master_text` row, read through `CUIUtility::GetSystemMessage`. Its message id comes from one of two places:
  - a `master_home_message` row: types 0 and 1, 610 rows, gated by `opened_at` / `closed_at` and the scenario range, collected by `CUIUtility::CollectMasterHomeMessage`; this covers the partner's greeting and Coro's lines;
  - a Home3D row's `text_id`, through `CHomeModelViewManager::GetTextId`: the tap reactions, Talk Mode and gift reactions (`SendPresentReaction`; [home3d.md](home3d.md) "How motions and lines are picked").
- Every one of those ids is a `*_hmmsg_*` message id: **2,743 `master_text` rows**, 604 id prefixes (characters and their event variants).
- **The Japanese:** 2,655 rows have 2 lines and 88 have 1. The widest line is 490 px (p99 473); 10 rows are over 480, by at most 10 px.
- **The English served now** (`derive`, 2,738 rows; 5 have no English):

  | Source | Rows | Fit as served | Fit after a re-break at 480 px | 3 lines after the re-break | 4+ lines after the re-break |
  |---|---|---|---|---|---|
  | machine (1,348 written by 26B-A4B, 849 by 31B) | 2,197 | 98 | 400 | 1,011 | 786 |
  | official (Global) | 535 | 55 | 113 | 238 | 184 |
  | memory | 6 | 6 | 6 | 0 | 0 |

- **Lines as served:** 85 rows have 1 line, 255 have 2, 911 have 3, 1,149 have 4, 309 have 5, and 29 have 6 or 7.
- **Line widths:** the widest line is p50 411 px and p90 548 px. Flattened to a single line, the text is p50 1,251 px, p90 1,655 px and at most 2,567 px; two lines hold 960 px.
- **Why the English is tall.**
  - Global broke its home lines into 3–4 lines of about 28 characters. Its 1.x client's box is not in hand. `finish` keeps Global's own breaks (3.2).
  - A machine row is re-broken at the Japanese row's widest line (`post_one`, about 470 px). That is the right width, but nothing limits the number of lines.
  - English needs about 1.3× the room of the Japanese line. At 15.0 px per character, two lines hold about 64 characters. The longest text that still re-breaks into two lines is 70 characters; the served median is 83 and p90 110.

**How the client draws it** (`home.csf`, the node tree read from the download; the same in both menus):

- `talk_text` is a `TextObjectData` label with FontSize 24, anchor (0, 1) (top left) and a placeholder of `１２３４５６７８９０…` in 2 lines, so its size is 480×48. It has **no `IsCustomSize`**, so `CCocosLabel::DrawSelf` gives it its text's size: no shrink, no clip, no ellipsis (3.2). It sits at x 34, y 69 (51 px from the top) in `talk_frame`, a 540×120 `ImageViewObjectData` whose image does not grow.
- On screen (729 px wide, scale 1.01) the lines are about 31 px apart. Two lines fill the frame. The third starts at its bottom edge, and the fourth and fifth cover the home's main buttons (Events, Missions…). In Talk Mode the third line lands on the footer (Home, Change Favorite…).
- The client never wraps (3.2). The E10 word wrap (`text_370.cpp`, `--lang en`) sees a label without a custom size and breaks only a line wider than the room left on the screen: 500 px at this label's world x of 202. Here that makes things worse. Global's `cp0002_b01a_hmmsg_15` ("Aaah! Why did you touch me!? You know \nthat startles me!", first line 629 px) became 3 lines, with "You know" on a line of its own. Only 1 of the run's lines was affected; most served lines are already narrower than 500 px.
- `talk_name` (FontSize 18, 164×18) showed "Evelysse" fine; long English names were not checked.
- Story markup (`<fontsize=…>`) is read only by the story's `ParseMessage`. This label isn't in tag mode, so no data route to a smaller font exists inside the text.

**Shots** (`work/english/homeline/`, local; `control/run.py home-character` with Evelysse `role_cp0002_b01a_6025`, the in-process server; `--soa-arg=--lang --soa-arg=en --soa-arg=--english --movie 72 --movie-fps 1` for taps every 9 s, and once in Japanese):

- `ja-hmmsg_01-2-lines.png` and `en-hmmsg_01-4-lines.png`: the same line, Japanese in 2 lines, Global's English in 4;
- `en-hmmsg_13-5-lines.png` (machine, 5 lines over the buttons), `en-hmmsg_11-4-lines.png`, `en-hmmsg_15-wrapped-3-lines.png` (the E10 wrap above), `en-hmmsg_02-2-lines-fits.png`;
- `en-talkmode.png` / `ja-talkmode.png`: Talk Mode;
- `en-movie-sheet.png`: every second frame of the movie, cropped to the box;
- `en/` and `ja/` hold the runs; `boxes.tsv` is the per-row list.

**Measuring.** `tools/english_text.py report` now writes `boxes.tsv` and a `boxes` summary per entry of `BOXES` (`home-talk`: ids containing `_hmmsg`, 2 lines × 480 px). Each row gets its lines and widest px as served and after a re-break at the box width, and a status of fits, wide or tall. The build does not apply the budget yet.

**Options.**

| | What | Cost | Trade-off |
|---|---|---|---|
| **(a) data: shorten to the box** | Re-break home lines at 480 px instead of keeping Global's breaks or the Japanese width (an `hmmsg` budget in `finish` / `post_one`), then a `shorten`-style MT pass for master rows: one request per line over 2 lines, asking for at most about 60 characters, checked by a re-break at 480 px to 2 lines, retried or reported. About 2,200 short requests on the 31B (E7's pass did 2,067). | S for the tools; one GPU batch, run **after the 31B redo**, which rewrites 1,348 of these rows anyway | The meaning is cut by about a quarter (median) to two fifths (p90): chatty lines lose clauses. **The 422 official rows that don't fit** need a precedence change: a shortened row for a context with a hard box must win over `official`. Today only `human` / `reviewed` do (7.6), so that is a new rule in both `tools/english_text.py` and the server's C++ derivation (7.9). Otherwise they stay at 3–4 lines, or get reviewed by hand. |
| **(b) client: fit in the bubble** | In the existing `CCocosLabel::DrawSelf` hook, for this label, scale the text so its lines fit the frame's room (480×69), or wrap at 480 instead of the screen's 500. | S, a client change logged in client-changes.md "English mode" | Every line shows, but 4–5 lines shrink to about 50–60%: small text. Server-first prefers a data route, and (c) is one. |
| **(c) server data: edit the served layout** | The server already writes `UI/etc2/home-en.csf` for the English art (section 8: the same node tree, a new atlas). Its `home.msgp` could change too: `talk_text` with `IsCustomSize` and a box of 480×66, so `DrawSelf`'s own shrink (+0x282, `min(boxW/w, boxH/h)`) fits anything taller; or a smaller FontSize (20: 576 px per line) with the label moved up. A recipe key per node in `standin-assets-en/recipes/home.json`; the server re-encodes the msgpack with msgpack-cxx. | S–M in `server/src/english_art/`; **not tried** (that the client honours an edited `IsCustomSize` on this label is (b) client evidence from `Read_TextObjectData`, untested here) | No client change. Without (a) it has the same small-text trade-off as (b). With (a) it only catches the few rows left over. |

**Recommendation: (a), with (c) as the safety net.**

- Two lines is the box the Japanese was written for, and only shorter text reads well in it.
- The shortening pass belongs after the running 31B redo, since that redo rewrites 1,348 of these rows.
- The 422 official rows need the user's decision. Either a box-context rule lets shortened rows win over Global's text, or they are reviewed by hand (the export / import tools exist, 7.6).
- (c) then shrinks whatever is still over budget, instead of letting it spill over the buttons. It also covers server text and future edits.
- (b) is not needed once (c) exists, since (c) is server data. Either way, the E10 wrap must not break a line of this label at 500 px when the frame's text width is 480 px: with (c) the label gets a custom size and the hook wraps at its box.

How measured: `tools/english_text.py derive` and `report` (the box check above) over the committed tables and `data/basmaster-3.7.0.sqlite3` / `data/basmaster-gl.sqlite3`. The layout comes from the download's `UI/etc2/home.csf` (ADLD + SLZ + ISF, `home.msgp` decoded with msgpack). The code is Ghidra (MCP) on `CHome::PlayTalk`, `CHome::SendPresentReaction` and the callers of `CUIUtility::CollectMasterHomeMessage`. The screen comes from the two runs above. Each run held one slot for about 5 minutes; no client was left running.

**Why only 535 home lines are official** (2026-10-07, agent `en-textclean-gl`). Global never translated the rest; no other id, table or text holds their English:

- Of the 2,743 `*_hmmsg_*` rows, 721 ids are not in Global's master (later content), and for 1,487 of the 2,022 Global has, its `en` row **is the Japanese** (untranslated). Global's English exists essentially only for the greetings `hmmsg_01` / `_02` (244 each) and a few `_15`; the Home3D tap and gift reactions (`_11`, `_21`, `_25`, `_31`, `_35`, `_41`, `_45`, `_91`, `_95`) have none. The bios (`*_prmsg_06`) are alike: 142 official, 137 untranslated, 103 not in Global, 9 with an older Japanese (8 of them a `０` placeholder, no English either).
- Rules tried and measured on the machine rows: the same Japanese elsewhere in Global after white space removal (+0 home, +0 bio; the master's 140 gains are UI rows: id-ws and memory-ws in 7.9), after NFKC and punctuation removal (rejected: `＋２０％` matched `－２０％`, `リーシュ` matched "Eve!!!"), the same character and line slot in another costume (rejected: 172 matches, all other lines), Global's `master_home_message` (its 308 own ids are other cards' lines). Story memory (the same Japanese line elsewhere) was also rejected: of 131 official story lines whose text recurs, only 59 have the same English (interjections such as `えっ……。` have 2–5 different translations).

**Decision and fix (2026-10-07, agent `en-homefit`).** The user chose **(b), the client change**, and to keep Global's official English as it is (no shortening or override of official rows, no MT pass for this box). With `--lang en` the E10 hook on `CCocosLabel::DrawSelf` fits every English line into the box ([client-changes.md "The home's speech box"](client-changes.md)):

- **Which labels:** the two `talk_text` labels, told by their node path (`talk_text` in `talk_frame` in `talk_menu_gp` or `talk_menu_talkmode`). `CHome::PlayTalk` is the only code that names them (the two path strings are referenced only there; `talk_menu_talkmode` is also shown and hidden by `SetTalkMode`). Talk Mode uses the same box.
- **The box:** 480 units wide (the placeholder in `home.csf`) and two lines high, as `CalcStringRect` measures two lines of the label's font: **55 units on the home** (24 for the first line, 31 per further line) and **48 in Talk Mode** (that label's lines are 24 apart). The home's frame has about 69 units below the text's top. Two lines is what every Japanese line fills, with the same bottom margin.
- **Re-break:** the line breaks are collapsed (with the white space around them) and the text is re-broken at spaces for this box. That drops Global's own breaks, which were made for a wider window. This rule is for these two labels only.
- **Fit:** the fewest lines n whose re-break at 480 / k fits, with k = min(1, box height / height of n lines); then the label is made a fixed-size, shrinking label (`IsCustomSize`, +0x282, the box) so `DrawSelf`'s own fit scales the font by min(1, 480 / w, box height / h). The text's top left stays where it was. Because the greedy re-break never gains lines at a wider width, this is the largest font at which the line fits.
- **Minimum:** none. A line that would need less than 16 px still gets the size that keeps it inside (the user's rule: the text always stays inside the frame).
- **What it gives on the home** (all 2,738 English home lines, by the font's advances; the live shots agree to 0.1 px; Talk Mode's lower box gives a little less): 519 lines keep 24 px; 895 get 16–23 px; 1,316 get 14–16 px (mostly 3 lines at 15.3 px); 8 get 11–14 px. The median is 16 px. The longest line (`cp0003_to_cp0108b01a_hmmsg_01_Ap`, 2,567 px flat) gets 3 lines at 12.1 px. Line counts: 68 rows take 1 line, 1,979 take 2 and 691 take 3.
- **The E10 wrap** no longer touches these labels (the 500 px break of `cp0002_b01a_hmmsg_15` is gone: 2 lines at 24 px).
- **Japanese:** a row without English keeps the label's own fields (drawn as shipped). `--lang ja` installs no hook.
- **Shots** (`work/english/homefit/`, local; `control/run.py home-character` with Evelysse, `--movie 72`, `SOA_TEST_TALK_IDS` picking the lines): `en-hmmsg_01.png` (Global's 4 lines → 3 at 15.3 px), `en-hmmsg_13.png` (5 → 3), `en-hmmsg_11.png` (4 → 3), `en-hmmsg_15.png` (the 500 px wrap case: 2 lines at 24 px), `en-longest.png` (`cp0003_to_cp0108b01a_hmmsg_01_Ap`: 3 lines at 12.1 px), `en-talkmode-smallest.png` (Talk Mode, `cm405_b02g_hmmsg_21`: 3 lines at 12.7 px), and `ja-home.png` / `ja-talkmode.png` (`--lang ja`: as before). `en/` and `ja/` hold the runs.
- **Open:** shorter wordings (option (a)) would give larger text, but only for machine rows: the user keeps the official ones. A 3-line box (the frame's 64 units) would raise the median to about 18 px. It is one constant, if the user prefers it.

- **After the 31B redo (2026-10-07).** The chain (`work/english/mt/run-31b.sh`, 2 slots, waiting for an
  idle GPU) re-translated every UI text and the whole story with Gemma 4 31B (~9 story requests/min).
  Imported (`--replace`; story-fix without): master **65,389 of 66,945 rows English** (official 19,177,
  memory 6,265, template 2,412, human 36, machine 37,499: 37,452 on the 31B, 47 left on the 26B where
  the 31B's answer failed a check); story **21,638 of 21,663 lines English, 51 of 64 files complete and
  served** (official 5,037, machine 17,013: 16,889 on the 31B, 124 on the 26B). The E7 shortening is
  retired (the user: shrink the font in the client instead), so no `short-v1` row remains; story lines
  needing 5+ window lines: 2,103, for the client font shrink.

### 7.12 The `--lang en` screen sweep

Agent `en-textclean-sweep`, 2026-10-07: every screen the named sessions reach, plus a hand-driven run, taken with `--lang en --english` and again with `--lang ja`, compared shot by shot. The English shots are from the build of `port/en-textclean` at 1cb83d7 (the 31B import, E13's story shrink, E10 on the shared breaker) plus this branch's two fixes; the first pass (before the import) is in `runs-old/`.

**How it was run.** 26 sessions (`control/run.py --list`: home, home-character, events, missions, sphere211, sphere211-continue, deepspace, gacha, battle-gacha, items, add-item, equipment, party, growth, mastery, favor, stamps, badges, storage, coins, rental, settings, campaign, battle, tower, simulator-continue) through the slot pool, each with a wrapper as its `soa` binary that appends `--lang en --english` (or `--lang ja`): most sessions take no pass-through flags, and the wrapper changes nothing else. Mastery derives `soa-server` from the binary's folder, so its wrapper sits in a `port/` folder beside a `server/soa-server` link. A hand-driven client (log in, then `soactl.py` taps with a shot after each step) covered the character guide (details, stats, talents, battle skills, the ability list), the gacha's notice and odds dialogs, the item exchange and the party edit, in both languages. Every run passed its own verdict except `stamps --lang ja` (its palette check; the shots are complete).

**Shots** (`work/english/textclean/`, local): `<session>/en-NN-name.png` and `<session>/ja-NN-name.png` (the sessions' own shot names), `manual/` for the hand-driven run; `runs/<session>-<lang>/` keeps each run's log (`lang: wrapped` / `lang: fitted` lines), packets and verdict; `runs-old/` the English runs before the import.

**How a Japanese leftover was classified.** The layout labels of the 853 UI and TalkScene scenes were dumped (the `.msgp` node trees: scene, node path, `IsCustomSize`, `FontSize`, `LabelText`); a Japanese text found there is a layout label. Otherwise `master_text` gives its row (and `master-en.tsv` / Global whether it has English), and the rest are pictures (the scene's `.csv` sprite table).

**What was found** (376 problem rows over 26 sessions and the hand-driven run; a row can have several causes: data 213, client wrap or fit 202, picture 165, layout label 117, server 50). The full lists are local in `work/english/textclean/`: `data-rows.tsv` (181: 169 message ids and 12 row families, with suggested English), `labels.tsv` (59 client cases in 14 classes, with node paths), `jp-left.tsv` (112 Japanese leftovers), `screens.tsv` (the table below), `story-missing.tsv` (25 story lines).

- **Japanese in the layouts (the biggest gap).** 920 labels with Japanese text (440 distinct, placeholders left out) are fixed in 173 scenes' node trees, and nothing translates them: the result screens (`result.csf` 調査ランク / 獲得調査ポイント / 獲得FOL / 報酬アイテム / 獲得EXP on every mission result), the mission card and detail (消費スタミナ, 初回クリア報酬…), the party select (パーティ戦闘力, 戻る / キャラクター設定), enhancement, evolution and limit-break dialogs, the stamina heal, the birth-date dialogs, the story's skip popup (`EventBase.csf` スキップしますか？ / いいえ / はい). 533 of the 920 have the same Japanese as a master row, and 519 of those have English. A server route exists: the `-en` scene that `english_art` already writes for the art could carry the node tree with these `LabelText`s replaced (msgpack-cxx is a dependency), from the master's English where the Japanese matches and from new rows otherwise (option (c) of [7.11](#711-the-home-speech-box-home-talk-lines) for one label). Done after the sweep: [7.14](#714-layout-labels-the-japanese-in-the-scenes-node-trees).
- **Pictures without a recipe:** 46 sprites (the item list's lock buttons and tabs `tab.csf`, Deep Space's 探査率 / 進行中 / 今すぐ帰還 badges, the character detail's round buttons, イベントメニュー, 全件取得, 強化開始, the Sphere 211 result titles…) and the title screen's buttons.
- **Data rows (machine):** narrow breaks at the Japanese width (`uimsg_full_stamina` 5 lines of 13 characters; 528 `uimsg` dialogs are broken narrower than the Japanese), lists merged into prose (`uimsg_item_confirmation_sell_1` and siblings: 10 lines over the buttons), a table's cells re-broken as prose (`uimsg_able_use_money`), one reversed meaning (`uimsg_drop_bonus_on_this_condition` "+10 drops every 1 hits"), long labels (691 weapon and item descriptions of 5+ lines), terms rendered several ways (転移 as Warp / Transfer / Teleport, OHS / One-Handed). Official rows with problems: the typo "Blue EXP Misisons" (`name_event_exp_blue`), "Not enough SP." (`error_message_text_10004`), "Delete" for 修正する (`uimsg_button_back`).
- **Client wrap and fit** (for the E10 / E13 owner): the header description (FS18, no custom size) is wrapped at the room it has when first drawn (63 px at x 645) and hangs a second line below the header on almost every menu; long header titles are drawn over the description; menu buttons' text runs over their left icon; fixed-size labels shrink a two-line wrap to about 40 % ("Change Equipment, Skills, and Assists"); labels wider than their icon or card ("Limit Break", "To Exceed Connect"); labels running into their value ("Continuous Clear Count", "Max Transfer Floor"); list rows wrapped at the screen edge instead of the row frame (the item exchange); a tag-mode ticker (character guide) running off both edges; and the story window: `1010_030_02` (5 lines) is drawn at full size over Skip / Auto although E13's hooks are installed, and no shrink was logged.
- **Story:** 25 lines of 13 Scenario files have no English, so those files are served Japanese as a whole (`TS_2010`, `TS_2040`, `TS_2050`, `TS_2060`, `TS_2070`, `TS_2090`, `TS_2100`, `TS_6020`, `TS_6040`, `TS_6050`, `TS_D076`, `TS_D093`, `TS_E036`). **Fixed after the sweep ([7.16](#716-the-follow-ups-story-gaps-the-profile-and-back-log-data-rows)): all 64 files are served.**
- **Before the English master:** the first download dialog and the title screen are Japanese (they show before the `-en` master is fetched); not a gap in the table.

**Fixed in this branch:**

- The gacha rate dialog's title was Japanese (キャラガチャ): `GetGachaRate` sent the pools' Japanese name. Under `--english` it is now the English of `master_gacha.name_message_id` ("Character Draw"; `gacha_pools::display_title`, selftest `server/gacha-title-english`, [server-rules](server-rules.md#english)).
- English art: the おまけつき cover on the 10-chain button reached only the top half of the Japanese (`gacha_select.json`); the standard gacha panel's footnote ※進化や覚醒なども含む… stayed Japanese (`pickup_img_chara_1610_002`, `tools/english_art/specs/pickup_misc.py`).

**Fixed after the sweep (agent `en-textclean`, same day):**

- **The story window** (`1010_030_02` and every message over four lines): the E13 fit needs the label's renderer, which the label gets only at its first draw; the sweep's build measured at `Change`, found none and left the font alone. It now fits at the label's first draw when `Change` came too early (7.13); `1010_030_02` shows four lines at 84% (`story-e13/en-1010_030_02-84pct.png`).
- **E10, the label wrap** (client-changes.md "Word wrap at spaces"), re-checked on battle-gacha, deepspace, growth and home (`work/english/textclean/after/`):
  - labels that slide in were wrapped at the room they had on their first frame (x 645: 63 units): a screen label is now wrapped only once it is drawn twice at the same x; the header descriptions get their real room (374 at x 330);
  - a menu's header description (`*_common.csf` `Node_1` / `Node_maintitle` `/Text_2`, `gacha_main.csf` `subtitle/text2`) stays on one line, shrunk into the bar (to at least 50%; the Japanese is one line); short labels (up to three words: enemy names, captions, "Hide Today's Updates") are shrunk on one line rather than broken into a column (to at least 60%, else wrapped);
  - wrapped lines are balanced (the narrowest width that keeps the line count: no "Skills:" or "loan." alone);
  - a dialog's message taller than the room above its buttons (`pop1/window/Text`; the room measured from the window's `line_1` rule to its `Button_*` siblings) keeps its lines and is shrunk into that room (`uimsg_mastary_dialog0`: 73%, `after/mastery/shots/06-pair-confirm.png`);
  - a fixed box that shrinks its text is re-broken for the largest scale (`fit_box`, as the home's talk box): "Change Equipment, Skills, and Assists" is two readable lines on the character menu instead of one line at 40%.
- **Data:** three machine rows whose text was wrong or garbled are replaced by `agent` rows (an AI agent's hand-written rows, ranked like machine, marked for review; 7.9 step 7): `uimsg_drop_bonus_on_this_condition` (wrong meaning: "+%u drops every %u hits" gave the combo count to the drops), `uimsg_item_confirmation_sell_1` (the five list lines run into each other) and `uimsg_able_use_money` (the table's nine cells re-broken as prose, so they shifted); the last two keep the machine wording, one item or cell per line. No row is shortened for space (the user: shrink the font, don't shorten): the sweep's shorter wordings were not applied, and its list's official rows keep Global's text until the user decides (`uimsg_birth_verify`, `uimsg_full_stamina` and `uimsg_item_WarningConfirmation` are official now, 7.9 white-space matching).
- **Still open** (client): dialogs laid out otherwise (`gacha_result.csf`: Global's two rows in 7 lines over Next; no `line_1` / button siblings around its text), the birth-date table's middle and right cells overlapping (`uimsg_able_use_money`, separate cells of one layout), header titles over the description, menu-button text over its left icon, list rows wrapped at the screen edge instead of their frame, labels wider than their icon or button, labels running into their value, the tag-mode ticker. These need a box the label doesn't carry (the parent's or a sibling's); `labels.tsv` has the node paths. (Layout labels and pictures: the server route in the first bullet above.)

**The `items` session with `--lang en`** passed both times (once before the import, once after). The failure english-exec saw (`work/english/exec/art/before-items/`) was a lost tap: after two login-bonus popups, the session's Home and Items footer taps reached a home that did not react (no phase line), and its next tap at 615:1120 opened Deep Space, so `LockItem` never came. That run had software GL at about 12 fps and a two-bonus day; nothing in it is English-specific, and it did not happen again.

**Not reached:** the character profile (CV, birthday: `uimsg_ch_profile_*`; the guide's detail has no way to it, the list's long press can't be sent by `soactl`); the normal battle's pause menu, the lose / continue / retire dialogs, Sphere 211's failed and result pages, the gacha's "Chip Obtained" page (the sessions pass these screens without a shot); the gacha's Notice tab is empty in both languages. Two shots are black frames from a transition (`party/14-battle`, `sphere211/50-boss-battle`).

How measured: the sessions and the hand-driven run above, one slot each (up to 6 at once), all through the pool; the shots compared in pairs (en | ja) by eye; the layout labels from the decoded `.msgp` node trees of the download's scenes; the rows from `master-en.tsv` at 1cb83d7, `data/basmaster-gl.sqlite3` and `tools/english_text.py derive`.

**The table** (`work/english/textclean/<session>/`; the download dialog, title, notice and login-bonus shots repeat in every session and are listed once, under home):

| Screen | en shot | ja shot | Status | Problem | Cause | Fix or proposed fix |
|---|---|---|---|---|---|---|
| add-item/03-weapon-gachas | `en-03-weapon-gachas.png` | `ja-03-weapon-gachas.png` | problem | banner caption "Great Swords / OHS / Arms / Axes" condensed, "OHS" opaque; header desc 2 lines | sprite+data+client-wrap | -en banner wording; gacha_Weapon_title_message_0005; header-desc fix |
| add-item/04-confirm | `en-04-confirm.png` | `ja-04-confirm.png` | problem | "Do you want to perform 1 Draws?" plural | data | uimsg_gacha_confirm "Draw ×%d?" |
| add-item/06-item-list | `en-06-item-list.png` | `ja-06-item-list.png` | problem | header desc 2 lines, "you." on header edge; ロックモード button Japanese | client-wrap+data+sprite | header-desc fix / "View your items."; -en lock art |
| add-item/07-sell | `en-07-sell.png` | `ja-07-sell.png` | problem | header desc 2 lines; "Sell For:" coin icon on the colon (minor) | client-wrap+data | "Sell unneeded items for FOL." |
| add-item/09-sell-warning | `en-09-sell-warning.png` | `ja-09-sell-warning.png` | problem | WORST: 5-item list merged into prose, 10 lines over "Proceed?"/buttons; title 2 lines; 選択中 overlay JP | data+client-wrap+sprite | uimsg_item_confirmation_sell_1 one item per line; shorter title; -en overlay |
| add-item/10-sold | `en-10-sold.png` | `ja-10-sold.png` | problem | "4000 FOL has / been / obtained." 3 lines | data+client-wrap | uimsg_Sellitem_Result_2 " FOL obtained." |
| add-item (other shots) | | | ok | 02-home, 05-result, 08-sell-confirm | | |
| badges/30-title | `en-30-title.png` | `ja-30-title.png` | problem | ムービー再生 label + round title buttons Japanese | server+sprite | English master before the title; -en title button art |
| badges/12-gacha | `en-12-gacha.png` | `ja-12-gacha.png` | problem | header desc "Use gems to summon..." 2 lines | client-wrap+data | header-desc class fix; "Summon characters and weapons." |
| badges/13-gacha-detail | `en-13-gacha-detail.png` | `ja-13-gacha-detail.png` | problem | "×2500" touches "10-chain Draw" art; stale -en.aif left JP footnote (fixed in newer art); desc 2 lines | sprite+client-wrap | narrower -en art; re-run with the 5-label art; header-desc fix |
| badges/14-gacha-confirm | `en-14-gacha-confirm.png` | `ja-14-gacha-confirm.png` | problem | header desc 2 lines (dialog ok) | client-wrap | header-desc fix |
| badges/16-gacha-result | `en-16-gacha-result.png` | `ja-16-gacha-result.png` | problem | "Limit Break" wider than the 96 px face icon | layout-label+client-wrap | shrink FaceThumbIcon Text_1 to icon width / "Lim. Break" |
| badges/17-gacha-closed | `en-17-gacha-closed.png` | `ja-17-gacha-closed.png` | problem | as 13 | sprite+client-wrap | as 13 |
| badges/20-list-new | `en-20-list-new.png` | `ja-20-list-new.png` | problem | title "Select Characters" into desc, desc 2 lines; レンタル / EP2専用 badges JP; "Des." | client-wrap+data+sprite | header class fix / "Pick your party."; -en badges; "Desc." |
| badges/21-list-cleared | `en-21-list-cleared.png` | `ja-21-list-cleared.png` | problem | as 20 | client-wrap+data+sprite | as 20 |
| badges/32-list-relogin | `en-32-list-relogin.png` | `ja-32-list-relogin.png` | problem | as 21 (byte-identical) | client-wrap+data+sprite | as 20 |
| badges (other shots) | | | ok | 02-home, 15-summon, 18-home-end, 31-home | | |
| battle/03-episodes | `en-03-episodes.png` | `ja-03-episodes.png` | problem | episode caption wider than banner, clipped both ends; bottom note 3 lines in a 2-line plate, 3rd cut | data+client-wrap | uimsg_episode_data_not_downloaded / _one_ shorter; shrink to banner |
| battle/05-battle-loading | `en-05-battle-loading.png` | `ja-05-battle-loading.png` | problem | tip art Japanese; tip 3 lines with "attack." alone | sprite+data | -en tip art; nowloading_battle_tips_023 2 lines |
| battle/92-result | `en-92-result.png` | `ja-92-result.png` | problem | 獲得EXP Japanese on Mission Result | layout-label | translate result.csf reward_exp label: "EXP Gained" |
| battle (other shots) | | | ok | 02-home, 04-home, 10-13 battle, 90, 91, 93 result, 99-home | | |
| battle-gacha/03-battle-loading | `en-03-battle-loading.png` | `ja-03-battle-loading.png` | problem | tip art caption アタッカー Japanese | sprite | -en tip art |
| battle-gacha/82-result | `en-82-result.png` | `ja-82-result.png` | problem | result labels 調査ランク / 獲得調査ポイント / 獲得FOL / 報酬アイテム Japanese | layout-label | translate result.csf labels: Rank / Exploration Points / FOL Gained / Rewards |
| battle-gacha/83-result | `en-83-result.png` | `ja-83-result.png` | problem | 獲得EXP Japanese on Mission Result | layout-label | translate result.csf reward_exp label: "EXP Gained" |
| battle-gacha/12-gacha | `en-12-gacha.png` | `ja-12-gacha.png` | problem | header desc "Use gems to summon..." 2 lines | client-wrap+data | header-desc class fix; "Summon characters and weapons." |
| battle-gacha/13-gacha-detail | `en-13-gacha-detail.png` | `ja-13-gacha-detail.png` | problem | "×2500" touches "10-chain Draw" art (pickup footnote now English: FIXED) | sprite | narrower -en art |
| battle-gacha/16-gacha-result | `en-16-gacha-result.png` | `ja-16-gacha-result.png` | problem | WORST: result text re-wrapped to 7 lines over the face icon and Next; "Limit Break" wider than icon | data+client-wrap+layout-label | shorter uimsg_gacha_chara/_limitover; no re-wrap of \n text; shrink icon label |
| battle-gacha/17-gacha-closed | `en-17-gacha-closed.png` | `ja-17-gacha-closed.png` | problem | as 13 (×2500 tight; header desc 2 lines) | sprite+client-wrap | as 13 |
| battle-gacha (other shots) | | | ok | 02-home, 10-13 battle, 80, 81, 84-result, 14-gacha-confirm, 15-summon, 18-home-end, 99-home | | |
| campaign/03-episodes | `en-03-episodes.png` | `ja-03-episodes.png` | problem | Ep1 caption 3 lines touching the logo; Ep2 caption clipped at both banner edges | data+client-wrap | uimsg_episode_one_not_downloaded 2 lines; shorter _data_not_downloaded |
| campaign/04-planets | `en-04-planets.png` | `ja-04-planets.png` | problem | header desc "Please select the planet..." 2 lines on header edge | client-wrap+data | header-desc fix; "Select a planet to explore." |
| campaign/05-planet-mere | `en-05-planet-mere.png` | `ja-05-planet-mere.png` | problem | header desc "Please select the planet..." 2 lines on header edge | client-wrap+data | header-desc fix; "Select a planet to explore." |
| campaign/06-mission-map | `en-06-mission-map.png` | `ja-06-mission-map.png` | problem | header desc 2nd line half below the header bar | client-wrap+data | header-desc fix; "Select a mission." |
| campaign/07-mission-detail | `en-07-mission-detail.png` | `ja-07-mission-detail.png` | problem | mission card + 初回クリア報酬 / 主な報酬 Japanese; header desc 2 lines | layout-label+client-wrap | translate mission_confirmation labels; header-desc fix |
| campaign/08-rental | `en-08-rental.png` | `ja-08-rental.png` | problem | title "Character on Loan" into desc; desc wraps ("loan." alone); 最終ログイン Japanese | client-wrap+layout-label+data | header-desc class fix; "Pick a loan character."; "Last Login" |
| campaign/09-party | `en-09-party.png` | `ja-09-party.png` | problem | パーティ戦闘力, 戻る / キャラクター設定, card labels Japanese | layout-label | "Party Power" / "Back" / "Characters"; card labels |
| campaign/10-confirm | `en-10-confirm.png` | `ja-10-confirm.png` | problem | same JP labels as 09 behind the dialog | layout-label | as 09 |
| campaign/61-result | `en-61-result.png` | `ja-61-result.png` | problem | result labels 調査ランク / 獲得調査ポイント / 獲得FOL / 報酬アイテム Japanese | layout-label | translate result.csf labels: Rank / Exploration Points / FOL Gained / Rewards |
| campaign/62-result | `en-62-result.png` | `ja-62-result.png` | problem | 獲得EXP Japanese on Mission Result | layout-label | translate result.csf reward_exp label: "EXP Gained" |
| campaign/63-result | `en-63-result.png` | `ja-63-result.png` | problem | header desc 2 lines (as 06) | client-wrap+data | as 06 |
| campaign/80-map-after-clear | `en-80-map-after-clear.png` | `ja-80-map-after-clear.png` | problem | header desc 2 lines (as 06) | client-wrap+data | as 06 |
| campaign/81-story-detail | `en-81-story-detail.png` | `ja-81-story-detail.png` | problem | header desc 2 lines (as 06) | client-wrap+data | as 06 |
| campaign/96-after-story | `en-96-after-story.png` | `ja-96-after-story.png` | problem | header desc 2 lines (as 06) | client-wrap+data | as 06 |
| campaign/97-map | `en-97-map.png` | `ja-97-map.png` | problem | header desc 2 lines (as 06) | client-wrap+data | as 06 |
| campaign/84-story | `en-84-story.png` | `ja-84-story.png` | problem | story 1010_030_02 5 lines at full size, 5th on Skip/Auto; E13 never logged a shrink | client-wrap+data | debug E13 (per-entry log); optional shorter story line |
| campaign/86-skip | `en-86-skip.png` | `ja-86-skip.png` | problem | skip popup スキップしますか？ / いいえ / はい Japanese | layout-label | translate EventBase SkipPopup: "Skip?" / "No" / "Yes" |
| campaign (other shots) | | | ok | 02-home, 11-battle, 12-battle (enemy name fixed), 13-battle, 60-result, 82-story, 83-story, 85-story | | |
| coins/30-title | `en-30-title.png` | `ja-30-title.png` | problem | ムービー再生 label + round title buttons Japanese | server+sprite | English master before the title; -en title button art |
| coins/10-gacha-banner | `en-10-gacha-banner.png` | `ja-10-gacha-banner.png` | problem | "×2500" touches "10-chain Draw"; header desc 2 lines (footnote English: FIXED) | sprite+client-wrap | narrower -en art; header-desc fix |
| coins/11-birth-confirm | `en-11-birth-confirm.png` | `ja-11-birth-confirm.png` | problem | WORST: question 4 lines overlapping "Born"; table cells shifted; "Delete" for 修正する; ※ note JP | data+layout-label | uimsg_birth_verify 1 line; uimsg_able_use_money 9 cells; "Edit"; shop_dialog1 Text_red |
| coins/11-birth-dialog | `en-11-birth-dialog.png` | `ja-11-birth-dialog.png` | problem | 8 dense lines; table cells shifted; 年 / 月 / 登録する / ※ note Japanese | data+layout-label | uimsg_please_birth_add_need3; uimsg_able_use_money; translate shop_dialog2 labels |
| coins/12-coin-shop | `en-12-coin-shop.png` | `ja-12-coin-shop.png` | problem | 閉じる button Japanese | layout-label | shop_menulist Button_close2/Text "Close" |
| coins/14-result-closed | `en-14-result-closed.png` | `ja-14-result-closed.png` | problem | as 12 (閉じる) | layout-label | as 12 |
| coins/33-coin-shop-relogin | `en-33-coin-shop-relogin.png` | `ja-33-coin-shop-relogin.png` | problem | as 12 (閉じる) | layout-label | as 12 |
| coins (other shots) | | | ok | 02-home, 13-purchased, 15-shop-closed, 16-home-stones, 31-home, 32-home-stones-relogin | | |
| deepspace/04-deepspace | `en-04-deepspace.png` | `ja-04-deepspace.png` | problem | header desc 2 lines, "explore." over 探査率/進行中; badges Japanese | client-wrap+data+sprite | header-desc fix; "Select a sector to explore."; -en badges |
| deepspace/05-missions | `en-05-missions.png` | `ja-05-missions.png` | problem | header desc 2nd line on edge; 探査率 badge JP; "Des." | client-wrap+data+sprite | as 04; "Desc." |
| deepspace/06-party | `en-06-party.png` | `ja-06-party.png` | problem | desc 2 lines; bonus help orphan; bonus names 2 lines/clipped under × tab; tiny "Enhancement Condition" | client-wrap+data | shorter name_ds_bonus_* / help; room to the tab; "Requires" |
| deepspace/07-auto | `en-07-auto.png` | `ja-07-auto.png` | problem | 優先編成選択中 badge JP; bonus list as 06 | sprite+client-wrap+data | -en "Priority" art; as 06 |
| deepspace/08-confirm | `en-08-confirm.png` | `ja-08-confirm.png` | problem | "Start Exploration" past the right button edge; bonus names 2 lines | data+client-wrap | "Explore" / shrink to button; shorter names |
| deepspace/09-started | `en-09-started.png` | `ja-09-started.png` | problem | 進行中▶▶ badge, 今すぐ帰還 button JP; header 2nd line | sprite+client-wrap | -en art; header-desc fix |
| deepspace/10-returned | `en-10-returned.png` | `ja-10-returned.png` | problem | header "explore." over 探査率/進行中; badges JP | client-wrap+sprite | as 04 |
| deepspace/11-area | `en-11-area.png` | `ja-11-area.png` | problem | 帰還済 badge JP | sprite | -en "Returned" art |
| deepspace/12-result-items | `en-12-result-items.png` | `ja-12-result-items.png` | problem | "Raise Exploration Rate" reads as an action | data | "Exploration Rate Up:" |
| deepspace/14-after | `en-14-after.png` | `ja-14-after.png` | problem | as 05 | client-wrap+data+sprite | as 05 |
| deepspace/18-returned-2 | `en-18-returned-2.png` | `ja-18-returned-2.png` | problem | as 05/11 | client-wrap+data+sprite | as 05/11 |
| deepspace/20-after-2 | `en-20-after-2.png` | `ja-20-after-2.png` | problem | as 05 | client-wrap+data+sprite | as 05 |
| deepspace/15-started-2 | `en-15-started-2.png` | `ja-15-started-2.png` | problem | as 09 (進行中 / 今すぐ帰還 JP) | sprite+client-wrap | as 09 |
| deepspace/22-two-ships | `en-22-two-ships.png` | `ja-22-two-ships.png` | problem | as 09 (進行中 / 今すぐ帰還 JP) | sprite+client-wrap | as 09 |
| deepspace/16-quick-return | `en-16-quick-return.png` | `ja-16-quick-return.png` | problem | "Hyper-Distance Warp Device" runs through "×0"; prompt 3 lines with orphan | data+client-wrap | "Warp Device" / shrink Text_itemname1; 2-line prompt |
| deepspace/19-result-2 | `en-19-result-2.png` | `ja-19-result-2.png` | problem | レアボーナス badge JP; "Raise Exploration Rate" | sprite+data | -en art; as 12 |
| deepspace/21-party-2 | `en-21-party-2.png` | `ja-21-party-2.png` | problem | "Exploration Skill" clipped "Explorati"; bonus names clipped; as 06 | client-wrap+data | no wrap txt_2 / "Skill"; shorter names |
| deepspace/23-achievements | `en-23-achievements.png` | `ja-23-achievements.png` | problem | "Time LefNon-expiring" overlap; 達成！ badge JP; "200 gems" lowercase; reward shrunk | data+sprite+client-wrap | "No limit"; -en art; "Gems" |
| deepspace/24-achievements-other | `en-24-achievements-other.png` | `ja-24-achievements-other.png` | problem | as 23 | data+sprite+client-wrap | as 23 |
| deepspace/25-achievements-received | `en-25-achievements-received.png` | `ja-25-achievements-received.png` | problem | dialog 5 forced lines, "counted." over the first achievement | data | uimsg_achievement_all_get_dialog 2 lines |
| deepspace (other shots) | | | ok | 03-home, 13-result-characters, 17-quick-returned, 19b-result-2-characters | | |
| equipment/20-title | `en-20-title.png` | `ja-20-title.png` | problem | ムービー再生 label + round title buttons Japanese | server+sprite | English master before the title; -en title button art |
| equipment/03-item-menu | `en-03-item-menu.png` | `ja-03-item-menu.png` | problem | "Weapon Customization" shrunk in fixed-size label (minor) | client-wrap+data | "Weapon Custom" |
| equipment/04-accessories | `en-04-accessories.png` | `ja-04-accessories.png` | problem | tabs 武器 / アクセ, 装備所持 JP; header desc 2 lines | sprite+client-wrap | -en art; header-desc fix |
| equipment/05-base | `en-05-base.png` | `ja-05-base.png` | problem | panel labels JP; 素材選択 / 強化開始 art JP; "Enhance Weapon" on an accessory; desc 2 lines | layout-label+sprite+data+client-wrap | translate synthesis_powerup labels; -en art; "Enhance" |
| equipment/06-materials | `en-06-materials.png` | `ja-06-materials.png` | problem | 到達LV / 到達上限解放 / 強化ポイント JP; ベース選択中 overlay JP | layout-label+sprite | translate; -en art |
| equipment/07-preview | `en-07-preview.png` | `ja-07-preview.png` | problem | same JP panel labels as 05 | layout-label+sprite | as 05 |
| equipment/08-confirm-inherit | `en-08-confirm-inherit.png` | `ja-08-confirm-inherit.png` | problem | 8 dense lines, no break before the question (JP 5) | data | uimsg_item_WarningInherit_Normal with paragraph break |
| equipment/09-confirm-lost | `en-09-confirm-lost.png` | `ja-09-confirm-lost.png` | problem | broken at JP width, 4 lines ~20 chars | data | uimsg_item_WarningConfirmation re-break |
| equipment/10-confirm-rare | `en-10-confirm-rare.png` | `ja-10-confirm-rare.png` | problem | WORST: 5-item list merged into prose, 10 lines over buttons; title 2 lines | data+client-wrap | uimsg_item_confirmation_sell_1 one item per line |
| equipment/11-inherited | `en-11-inherited.png` | `ja-11-inherited.png` | problem | 強化成功 banner JP | sprite | -en art |
| equipment/11-result | `en-11-result.png` | `ja-11-result.png` | problem | ロック button JP | sprite | -en art |
| equipment/11-closed | `en-11-closed.png` | `ja-11-closed.png` | problem | as 05 | layout-label+sprite | as 05 |
| equipment/12-characters | `en-12-characters.png` | `ja-12-characters.png` | problem | title into desc, desc 2 lines; レンタル / EP2専用 badges JP | client-wrap+sprite | header class fix; -en badges |
| equipment/13-equipment | `en-13-equipment.png` | `ja-13-equipment.png` | problem | WORST: title "Change Equipment, Skills, and Assists" over the desc; 装備なし / 限界突破 / 設定なし / 自動設定 JP | data+client-wrap+layout-label+sprite | title "Equip / Skills / Assists"; translate labels; -en art |
| equipment/14-auto-confirm | `en-14-auto-confirm.png` | `ja-14-auto-confirm.png` | problem | "Assistance" vs "Assists" (term) | data | uimsg_party_equip_have_best_equip_v2_2 |
| equipment/15-auto-equipped | `en-15-auto-equipped.png` | `ja-15-auto-equipped.png` | problem | as 13 | data+client-wrap+layout-label+sprite | as 13 |
| equipment/22-equipment-after-relogin | `en-22-equipment-after-relogin.png` | `ja-22-equipment-after-relogin.png` | problem | as 13 | data+client-wrap+layout-label+sprite | as 13 |
| equipment (other shots) | | | ok | 02-home, 21-home | | |
| events/10-events | `en-10-events.png` | `ja-10-events.png` | problem | イベントメニュー button and event banners Japanese | sprite | -en btn_eventmenu (copy mission_list2); banners known |
| events/13-daily | `en-13-daily.png` | `ja-13-daily.png` | problem | mission card labels 消費スタミナ / モンスターレベル / ステージ数 Japanese | layout-label | "Stamina Cost" / "Monster Lv" / "Stages" |
| events/14-daily-detail | `en-14-daily-detail.png` | `ja-14-daily-detail.png` | problem | 初回クリア報酬 / 主な報酬 / 主な出現モンスター + card labels JP | layout-label | translate mission_confirmation subtitles |
| events/20-daily-party | `en-20-daily-party.png` | `ja-20-daily-party.png` | problem | パーティ戦闘力, 戻る / キャラクター設定 JP; "No Loans" vs "No Loan" | layout-label+data | translate; "No Loan" |
| events/20-daily-helper | `en-20-daily-helper.png` | `ja-20-daily-helper.png` | problem | title "Character on Loan" into desc; desc wraps ("loan." alone); 最終ログイン Japanese | client-wrap+layout-label+data | header-desc class fix; "Pick a loan character."; "Last Login" |
| events/20-daily-after | `en-20-daily-after.png` | `ja-20-daily-after.png` | problem | mission card labels 消費スタミナ / モンスターレベル / ステージ数 Japanese | layout-label | "Stamina Cost" / "Monster Lv" / "Stages" |
| events/30-event-tab | `en-30-event-tab.png` | `ja-30-event-tab.png` | problem | as 10 (イベントメニュー art, banners) | sprite | as 10 |
| events/31-first-event | `en-31-first-event.png` | `ja-31-first-event.png` | problem | card stat labels JP (as 13) | layout-label | as 13 |
| events (other shots) | | | ok | 04-home, 11-materials, 12-materials-end, 20-daily-result | | |
| favor/10-battle | `en-10-battle.png` | `ja-10-battle.png` | problem | tip art Japanese (Talent-detail card) | sprite | -en tip art |
| favor/82-result | `en-82-result.png` | `ja-82-result.png` | problem | 獲得EXP Japanese on Mission Result | layout-label | translate result.csf reward_exp label: "EXP Gained" |
| favor (other shots) | | | ok | 01-title (known), 02-home-level1, 03, 04-levelup, 05-level2, 11-13 battle, 80, 81, 83, 99-home | | |
| gacha/03-gacha | `en-03-gacha.png` | `ja-03-gacha.png` | problem | header desc "Use gems to summon..." 2 lines | client-wrap+data | header-desc class fix; "Summon characters and weapons." |
| gacha/04-tab-chara | `en-04-tab-chara.png` | `ja-04-tab-chara.png` | problem | header desc 2 lines (as 03) | client-wrap+data | as 03 |
| gacha/05-tab-weapon | `en-05-tab-weapon.png` | `ja-05-tab-weapon.png` | problem | header desc 2 lines (as 03) | client-wrap+data | as 03 |
| gacha/06-tab-event | `en-06-tab-event.png` | `ja-06-tab-event.png` | problem | "Box Draws" tag at/past its plate end (minor) | client-wrap+data | shrink to plate / "Box" |
| gacha/13-gacha-detail | `en-13-gacha-detail.png` | `ja-13-gacha-detail.png` | problem | "×2500" touches "10-chain Draw" art; JP footnote (stale art, fixed later); desc 2 lines | sprite+client-wrap | narrower -en art; 5-label -en.aif |
| gacha/14-gacha-confirm | `en-14-gacha-confirm.png` | `ja-14-gacha-confirm.png` | problem | header desc 2 lines (dialog ok) | client-wrap | as 03 |
| gacha/16-gacha-result | `en-16-gacha-result.png` | `ja-16-gacha-result.png` | problem | "Limit Break" wider than 96 px face icon; desc 2 lines | layout-label+client-wrap | shrink to icon / "Lim. Break" |
| gacha/17-gacha-closed | `en-17-gacha-closed.png` | `ja-17-gacha-closed.png` | problem | as 13 | sprite+client-wrap | as 13 |
| gacha (other shots) | | | ok | 02-home, 15-summon, 18-home-end | | |
| growth/03-character-menu | `en-03-character-menu.png` | `ja-03-character-menu.png` | problem | desc 2 lines; "Change Equipment, Skills, and Assists" ~10px; 大成功率UP! JP | client-wrap+data+sprite | header-desc fix; "Equip / Skills / Assists"; -en badge |
| growth/04-strengthen-select | `en-04-strengthen-select.png` | `ja-04-strengthen-select.png` | problem | title into desc, desc 2 lines; レンタル / EP2専用 JP | client-wrap+sprite | header class fix; -en badges |
| growth/05-strengthen | `en-05-strengthen.png` | `ja-05-strengthen.png` | problem | desc 2 lines; 所持 row label JP | client-wrap+layout-label | header-desc fix; "Owned" |
| growth/06-strengthen-count | `en-06-strengthen-count.png` | `ja-06-strengthen-count.png` | problem | dialog texts + 戻る JP; 獲得EXP / 所持FOL / 必要FOL plates JP | layout-label+sprite | translate pm_powerup_dialog1 labels; -en art |
| growth/07-strengthen-confirm | `en-07-strengthen-confirm.png` | `ja-07-strengthen-confirm.png` | problem | confirm text + 戻る JP; plates JP | layout-label+sprite | translate; -en art |
| growth/08-strengthen-anim | `en-08-strengthen-anim.png` | `ja-08-strengthen-anim.png` | problem | 強化成功 banner JP | sprite | -en art |
| growth/09-strengthen-result | `en-09-strengthen-result.png` | `ja-09-strengthen-result.png` | problem | 限界突破 row label, 閉じる JP | layout-label | "Limit Break" / "Close" |
| growth/10-evolve-offer | `en-10-evolve-offer.png` | `ja-10-evolve-offer.png` | problem | 6 narrow lines, near the buttons (JP 4) | data | uimsg_next_evolution re-break |
| growth/11-evolve | `en-11-evolve.png` | `ja-11-evolve.png` | problem | panel labels JP; 詳細 / 進化する art JP; "Augment" vs "Evolve"; talent name with period | layout-label+sprite+data | translate party_evolution labels; -en art; one term |
| growth/12-evolve-confirm | `en-12-evolve-confirm.png` | `ja-12-evolve-confirm.png` | problem | confirm text, captions, 戻る / 実行 JP; FOL plates JP | layout-label+sprite | translate pm_evolution labels; -en art |
| growth/13-evolve-result | `en-13-evolve-result.png` | `ja-13-evolve-result.png` | problem | as 09 | layout-label | as 09 |
| growth/14-evolve-skill | `en-14-evolve-skill.png` | `ja-14-evolve-skill.png` | problem | "Skills:" alone on line 2 (wrap 680); 閉じる JP | client-wrap+data+layout-label | "New Battle Skills learned:"; "Close" |
| growth/15-evolve-level1 | `en-15-evolve-level1.png` | `ja-15-evolve-level1.png` | problem | "Strengthen" vs "Enhance Status" (term) | data | "Enhance" |
| growth/16-character-menu | `en-16-character-menu.png` | `ja-16-character-menu.png` | problem | as 03 | client-wrap+data+sprite | as 03 |
| growth/17-limitbreak-select | `en-17-limitbreak-select.png` | `ja-17-limitbreak-select.png` | problem | as 04 | client-wrap+sprite | as 04 |
| growth/18-limitbreak | `en-18-limitbreak.png` | `ja-18-limitbreak.png` | problem | desc 3 lines below the bar; select text + 必要素材/必要数/所持 JP; panel art JP | client-wrap+data+layout-label+sprite | shorter uimsg_chara_unlimit_info; translate party_overlimit labels; -en art |
| growth/19-limitbreak-confirm | `en-19-limitbreak-confirm.png` | `ja-19-limitbreak-confirm.png` | problem | confirm text, 戻る / 実行 JP; plates JP | layout-label+sprite | translate pm_overlimit labels; -en art |
| growth/20-limitbreak-result | `en-20-limitbreak-result.png` | `ja-20-limitbreak-result.png` | problem | 限界突破 / 閉じる JP; desc 3 lines (as 18) | layout-label+client-wrap | as 09, 18 |
| growth/21-limitbreak-result2 | `en-21-limitbreak-result2.png` | `ja-21-limitbreak-result2.png` | problem | 限界突破 / 閉じる JP; desc 3 lines (as 18) | layout-label+client-wrap | as 09, 18 |
| growth/23-custom | `en-23-custom.png` | `ja-23-custom.png` | problem | WORST: title "Weapon Customization" over the desc; tab / mode art JP | data+client-wrap+sprite | title "Weapon Custom"; desc shorter; -en art |
| growth/24-custom-gears | `en-24-custom-gears.png` | `ja-24-custom-gears.png` | problem | title over desc; "Set Condition" into ★5/"ATK"; coin icon over "Required"; OHS/One-Handed mix; ギア解除 JP | data+client-wrap+sprite | uimsg_setting_condition "Req."; "FOL Cost"; one gear naming; -en art |
| growth/25-custom-selected | `en-25-custom-selected.png` | `ja-25-custom-selected.png` | problem | 選択中 overlay, セット開始 JP; title/desc as 24 | sprite+data+client-wrap | -en art; as 24 |
| growth/26-custom-detail | `en-26-custom-detail.png` | `ja-26-custom-detail.png` | problem | WORST: weapon desc 6 lines of 1-3 words over ファクター; factor ~9px; 説明/ファクター/ロック JP | data+client-wrap+layout-label+sprite | item_W01Sw_58 2 lines (family); factor shorter; translate captions |
| growth/27-custom-confirm | `en-27-custom-confirm.png` | `ja-27-custom-confirm.png` | problem | 6 lines fill the dialog, no blank line | data | uimsg_gear_set_dialog1 with paragraph break |
| growth/28-custom-done | `en-28-custom-done.png` | `ja-28-custom-done.png` | problem | セット 完了 banner JP | sprite | -en art |
| growth/30-remove-confirm | `en-30-remove-confirm.png` | `ja-30-remove-confirm.png` | problem | 4 narrow lines (minor) | data | uimsg_gear_slot_remove 2 lines |
| growth/31-remove-detail | `en-31-remove-detail.png` | `ja-31-remove-detail.png` | problem | as 26 (+ "Confirm Removal" shrunk, readable) | data+client-wrap+layout-label+sprite | as 26 |
| growth/33-remove-closed | `en-33-remove-closed.png` | `ja-33-remove-closed.png` | problem | as 24 | data+client-wrap+sprite | as 24 |
| growth/34-custom-top | `en-34-custom-top.png` | `ja-34-custom-top.png` | problem | as 23 | data+client-wrap+sprite | as 23 |
| growth/35-purify | `en-35-purify.png` | `ja-35-purify.png` | problem | "Expected Gear Value" under "Factor Extraction Rate"; "Materials" into icon; hint 2 lines; art JP | data+client-wrap+sprite | shorter labels; "Optional: pick 1 extra Item type."; -en art |
| growth/36-purify-material | `en-36-purify-material.png` | `ja-36-purify-material.png` | problem | as 35 | data+client-wrap+sprite | as 35 |
| growth/37-purify-result | `en-37-purify-result.png` | `ja-37-purify-result.png` | problem | gear help 4 lines touching ファクター, "OHS"; "Set Condition--"; 説明/ファクター/閉じる JP | data+layout-label | uimsg_gear_sword_10_help 2 lines; "Req."; translate captions |
| growth (other shots) | | | ok | 01-title (known), 02-home, 22-item-menu (minor shrink), 29-custom-customised, 32-remove-done | | |
| home/00-download-dialog | `en-00-download-dialog.png` | `ja-00-download-dialog.png` | problem | download dialog all Japanese (pre-master) | server | serve the English master before the first download, or accept |
| home/01-title | `en-01-title.png` | `ja-01-title.png` | problem | ムービー再生 label + round title buttons Japanese | server+sprite | English master before the title; -en title button art |
| home/02-notice | `en-02-notice.png` | `ja-02-notice.png` | problem | "Hide Today's Updates" 2 lines over footer; "Blue EXP Misisons" typo | layout-label+client-wrap+data | no wrap/shrink NoticeBoard box/Text; override "Blue EXP Missions" |
| home/03-login-bonus | `en-03-login-bonus.png` | `ja-03-login-bonus.png` | problem | -ログインボーナス- subtitle Japanese | sprite | -en login bonus art |
| home/10-event | `en-10-event.png` | `ja-10-event.png` | problem | イベントメニュー button and banners JP | sprite | -en btn_eventmenu; banners known |
| home/11-mission | `en-11-mission.png` | `ja-11-mission.png` | problem | bottom panel 3 lines in 2-line panel; episode header clipped both ends | data+client-wrap | uimsg_episode_one_/_data_not_downloaded shorter |
| home/12-sphere211 | `en-12-sphere211.png` | `ja-12-sphere211.png` | problem | WRONG: "+10 drops every 1 hits"; Clear Count under "0"; Deployed Count tiny; S-Stamina over 9/9 | data+client-wrap | "%u-hit combo: drops +%u"; "Clear Streak"; "Deployed"; "S.Stam." |
| home/13-deepspace | `en-13-deepspace.png` | `ja-13-deepspace.png` | problem | header desc "explore." over the 探査率/進行中 tags; tags JP | client-wrap+data+sprite | header-desc fix; "Select a sector to explore."; -en art |
| home/21-follow | `en-21-follow.png` | `ja-21-follow.png` | problem | button labels start over the left icons; コピー art JP; header desc 2 lines | client-wrap+sprite | left-align after icon; -en art |
| home/23-recent | `en-23-recent.png` | `ja-23-recent.png` | problem | title and 2-line desc overlap; 変更を確定 art JP | data+client-wrap+sprite | "Recent Players" / "Players you recently played with."; -en art |
| home/24a-titles-other | `en-24a-titles-other.png` | `ja-24a-titles-other.png` | problem | title desc 2 lines touching "Attained" (minor) | data+client-wrap | "You prefer manual over auto battles" |
| home/24d-notice | `en-24d-notice.png` | `ja-24d-notice.png` | problem | as 02-notice | layout-label+client-wrap+data | as 02 |
| home/25-present | `en-25-present.png` | `ja-25-present.png` | problem | プレゼント所持 / 全件取得 JP (art) | sprite | -en presentbox art ("Gifts Held" / "Claim All") |
| home/28-datasave | `en-28-datasave.png` | `ja-28-datasave.png` | problem | 7 dense lines, no paragraph break | data | uimsg_user_data_saving_end_dialog 2 paragraphs |
| home/29-stamina | `en-29-stamina.png` | `ja-29-stamina.png` | problem | 5 lines of ~13 chars (JP width) | data | uimsg_full_stamina 2 lines |
| home/30-character | `en-30-character.png` | `ja-30-character.png` | problem | "Change Equipment, Skills, and Assists" shrunk to ~40%; 大成功率UP! JP; desc 2 lines | data+client-wrap+sprite | "Equip / Skills / Assists"; -en badge |
| home/31-item | `en-31-item.png` | `ja-31-item.png` | problem | "Weapon Customization" shrunk (readable, minor) | data+client-wrap | "Weapon Custom" |
| home/33-shop | `en-33-shop.png` | `ja-33-shop.png` | problem | "Expand Follow Slots", "Increase Inventory Slots", "Expand Gear Slots" over their icons | client-wrap+data | left-align after icon; shorter "... Slots+" |
| home (other shots) | | | ok | 04, 20-menu, 22-follow-search, 24-titles, 24b, 24c, 26-achievements, 27-recommended, 32-gacha, 34-36-other, 40 | | |
| home-character/*/00-03 (download, title, notice, login bonus) | — | — | problem | as home/00-03 (Hide Today's Updates wrap logged in every role) | server+sprite+layout-label+client-wrap | as home/00-03 |
| home-character (other shots) | | | ok | */04-home, 10-idle, 11-14 talk lines (64-100% fit, readable), 20-22 Talk Mode, 23-24 2D/3D (4 roles) | | |
| items/03-locked | `en-03-locked.png` | `ja-03-locked.png` | problem | header desc 2 lines; lock/tab art and 装備所持 JP | client-wrap+sprite | header-desc fix; -en art |
| items/04-sell-warning | `en-04-sell-warning.png` | `ja-04-sell-warning.png` | problem | WORST: red list 10 lines merged prose over "Proceed?"/buttons; title 2 lines | data+client-wrap | uimsg_item_confirmation_sell_1 one item per line; shorter title |
| items/05-sold | `en-05-sold.png` | `ja-05-sold.png` | problem | "1200 FOL has / been / obtained." 3 lines | data+client-wrap | " FOL obtained." |
| items/06-compose | `en-06-compose.png` | `ja-06-compose.png` | problem | synthesis_powerup labels and art JP; desc 2 lines | layout-label+sprite+client-wrap | translate labels; -en art |
| items/07-composed | `en-07-composed.png` | `ja-07-composed.png` | problem | ロック解除 badge art JP (details text 4 lines ok) | sprite | -en art |
| items/r04-unlocked | `en-r04-unlocked.png` | `ja-r04-unlocked.png` | problem | as 03 (lock art, 装備所持) | sprite | as 03 |
| items (other shots) | | | ok | 01-title (known), 02-home, r03-list | | |
| manual/m04-guide-detail | `en-m04-guide-detail.png` | `ja-m04-guide-detail.png` | problem | ticker runs off both screen edges; detail round buttons JP | client-wrap+data+sprite | shrink tag-mode label to width; shorter ticker row; -en art |
| manual/m05-status | `en-m05-status.png` | — | problem | "Limit Break" / "Awakenings" run into their icons | client-wrap | shrink to the room before the icon |
| manual/m07-skill | `en-m07-skill.png` | — | problem | 威力 / 最大ヒット数 / アシストスキル JP; long skill descs 2 small lines | layout-label | "Power" / "Max Hit" / "Assist Skill" |
| manual/m11-banner | `en-m11-banner.png` | — | problem | "×2500" into "10-chain Draw" (minor) | sprite | narrower -en art |
| manual/m13-guide | `en-m13-guide.png` | — | problem | ticker runs off both edges (as m04) | client-wrap | as m04 |
| manual/m14-exchange | `en-m14-exchange.png` | `ja-m14-exchange.png` | problem | row texts wrap at screen edge, clip at row frame; names shrunk; Scenery/Scenic | client-wrap+data | wrap at row frame; one "Scenic Photo" name |
| manual/m15-exchange-item | `en-m15-exchange-item.png` | `ja-m15-exchange-item.png` | problem | 在庫 JP; "Items Required" over icon; item name under it; "Held:" from x=0 | layout-label+client-wrap | "Stock"; shrink to room; anchor fix |
| manual/m16-equiplist | `en-m16-equiplist.png` | — | problem | "To Exceed Connect" wider than card; ▼シンボル選択/ロック/メンバー変更, パーティ戦闘力 JP | data+client-wrap+sprite+layout-label | "Exceed Connect"; -en art; "Party Power" |
| manual/m17-card | `en-m17-card.png` | — | problem | title "Select Characters" into the desc | client-wrap | header class fix |
| manual (other shots) | | | ok | m06-talent, m12 (rate title FIXED: "Character Draw"; Notice body empty in JA too), m13-odds | | |
| mastery/03-mastery | `en-03-mastery.png` | `ja-03-mastery.png` | problem | tabs 道場 / 皆伝師弟 JP; desc 2 lines (tight) | sprite+client-wrap+data | -en art; "Pick a dojo or view mastered pairs." |
| mastery/03a-equipment | `en-03a-equipment.png` | `ja-03a-equipment.png` | problem | title over desc (as equipment/13); 装備なし / 限界突破 / 設定なし / 自動設定 JP | data+client-wrap+layout-label+sprite | as equipment/13 |
| mastery/03c-role-changed | `en-03c-role-changed.png` | `ja-03c-role-changed.png` | problem | orphan "reset." (JP 2 lines) | data | uimsg_evolution_role_change_done* 2 lines |
| mastery/03d-attacker | `en-03d-attacker.png` | `ja-03d-attacker.png` | problem | as 03a | data+client-wrap+layout-label+sprite | as 03a |
| mastery/04-select-master | `en-04-select-master.png` | `ja-04-select-master.png` | problem | desc 3 lines, 3rd over the plates | client-wrap+data | "Choose a master and a disciple." |
| mastery/05-select-disciple | `en-05-select-disciple.png` | `ja-05-select-disciple.png` | problem | "Midsummer Tika" under portrait; talent desc 4 tiny lines; レンタル tag JP | client-wrap+data+sprite | shrink name; shorter factor; -en art |
| mastery/06-pair-confirm | `en-06-pair-confirm.png` | `ja-06-pair-confirm.png` | problem | WORST: 7 short lines, last over Close/Confirm | data | uimsg_mastary_dialog0 4 lines |
| mastery/08-training | `en-08-training.png` | `ja-08-training.png` | problem | 師弟解消 art JP; desc "perform." alone; talent desc tiny | sprite+client-wrap+data | -en art; "Select a training." |
| mastery/10-medal-confirm | `en-10-medal-confirm.png` | `ja-10-medal-confirm.png` | problem | "Use 1 Mastery Pass Medals?" plural | data | "Use Mastery Pass Medal x%lu?" |
| mastery/11-full-mastership | `en-11-full-mastership.png` | `ja-11-full-mastership.png` | problem | WORST: gift line 6 lines over the Close button; talent desc tiny | data | uimsg_mastary_dialog11 2 lines |
| mastery/12-graduated | `en-12-graduated.png` | `ja-12-graduated.png` | problem | tabs 道場 / 皆伝師弟 JP | sprite | -en art |
| mastery/13-deco | `en-13-deco.png` | `ja-13-deco.png` | problem | deco buttons JP | sprite | -en home_decomode art |
| mastery/16-deco-adjust | `en-16-deco-adjust.png` | `ja-16-deco-adjust.png` | problem | deco adjust buttons JP | sprite | -en home_decomode art |
| mastery (other shots) | | | ok | 02-home, 03b-role-select, 07-paired, 09-training-1..4, 14-deco-list (minor), 15-deco-set | | |
| missions/03-battle-loading | `en-03-battle-loading.png` | `ja-03-battle-loading.png` | problem | tip art JP; English tip 4 lines, 4th on the panel border | sprite+data | -en tip art; nowloading_battle_tips_057 2 lines |
| missions/a02-result | `en-a02-result.png` | `ja-a02-result.png` | problem | result labels 調査ランク / 獲得調査ポイント / 獲得FOL / 報酬アイテム Japanese | layout-label | translate result.csf labels: Rank / Exploration Points / FOL Gained / Rewards |
| missions/a03-result | `en-a03-result.png` | `ja-a03-result.png` | problem | 獲得EXP Japanese on Mission Result | layout-label | translate result.csf reward_exp label: "EXP Gained" |
| missions/c0-stepup-banner | `en-c0-stepup-banner.png` | `ja-c0-stepup-banner.png` | problem | header desc 2 lines; ribbon unreadable; "Bonus!" over おまけつき; ×2500 touches art; banner JP | client-wrap+data+sprite | header-desc fix; "PU guaranteed in N pulls!"; -en art |
| missions/c1-result | `en-c1-result.png` | `ja-c1-result.png` | problem | 7-line result text over Next; "Limit Break" spills; ガチャ tag JP | data+client-wrap+layout-label+sprite | as battle-gacha/16; shrink icon label |
| missions/c1-banner-after | `en-c1-banner-after.png` | `ja-c1-banner-after.png` | problem | as c0 (9 more pulls) | client-wrap+data+sprite | as c0 |
| missions/c2-result | `en-c2-result.png` | `ja-c2-result.png` | problem | as c1-result | data+client-wrap+layout-label | as c1-result |
| missions/c2-banner-after | `en-c2-banner-after.png` | `ja-c2-banner-after.png` | problem | as c0 (8 more pulls) | client-wrap+data+sprite | as c0 |
| missions/d0-error-dialog | `en-d0-error-dialog.png` | `ja-d0-error-dialog.png` | problem | "Not enough SP." (stat is Stamina); tip art JP | data+sprite | error_message_text_10004 "Not enough Stamina." |
| missions (other shots) | | | ok | 02-home, 10-20 battle (enemy names 1 line), a0, a04, a1, b0-home, c1-summon, c2-summon, c9-home-after-stepup | | |
| party/03-character-menu | `en-03-character-menu.png` | `ja-03-character-menu.png` | problem | "Change Equipment, Skills, and Assists" ~40%; 大成功率UP! JP; desc 2 lines | data+client-wrap+sprite | "Equip / Skills / Assists"; -en badge |
| party/04-party-top | `en-04-party-top.png` | `ja-04-party-top.png` | problem | "To Exceed Connect" over cards; names over element icon; buttons + パーティ戦闘力 JP; desc 2 lines | data+client-wrap+sprite+layout-label | "Exceed Connect"; name room; -en art; "Party Power" |
| party/05-member-select | `en-05-member-select.png` | `ja-05-member-select.png` | problem | title into desc, desc 2 lines; パーティ戦闘力 + badges JP | client-wrap+layout-label+sprite | header class fix; "Party Power"; -en badges |
| party/06-member-changed | `en-06-member-changed.png` | `ja-06-member-changed.png` | problem | as 05 | client-wrap+layout-label+sprite | as 05 |
| party/09-party-2-changed | `en-09-party-2-changed.png` | `ja-09-party-2-changed.png` | problem | as 05 | client-wrap+layout-label+sprite | as 05 |
| party/07-party-saved | `en-07-party-saved.png` | `ja-07-party-saved.png` | problem | as 04 | data+client-wrap+sprite+layout-label | as 04 |
| party/08-party-2 | `en-08-party-2.png` | `ja-08-party-2.png` | problem | as 04 | data+client-wrap+sprite+layout-label | as 04 |
| party/10-party-2-saved | `en-10-party-2-saved.png` | `ja-10-party-2-saved.png` | problem | as 04 | data+client-wrap+sprite+layout-label | as 04 |
| party/11-character-menu | `en-11-character-menu.png` | `ja-11-character-menu.png` | problem | as 03 | data+client-wrap+sprite | as 03 |
| party/12a-favorite-select | `en-12a-favorite-select.png` | `ja-12a-favorite-select.png` | problem | 選択中 overlay + レンタル / EP2専用 badges JP | layout-label+sprite | "Selected"; -en badges |
| party/14-battle | `en-14-battle.png` | `ja-14-battle.png` | problem | en shot black (transition): not reviewable | - | re-take the shot |
| party (other shots) | | | ok | 02-home, 12-home, 12b-favorite-changed, 12c-home-new-favorite, 13-battle | | |
| rental/70-title | `en-70-title.png` | `ja-70-title.png` | problem | ムービー再生 label + round title buttons Japanese | server+sprite | English master before the title; -en title button art |
| rental/03-detail | `en-03-detail.png` | `ja-03-detail.png` | problem | header desc 2nd line below the bar; card + reward labels JP | client-wrap+data+layout-label | header-desc fix; translate mission_confirmation labels |
| rental/04-rental | `en-04-rental.png` | `ja-04-rental.png` | problem | title "Character on Loan" into desc; desc wraps ("loan." alone); 最終ログイン Japanese | client-wrap+layout-label+data | header-desc class fix; "Pick a loan character."; "Last Login" |
| rental/05-party | `en-05-party.png` | `ja-05-party.png` | problem | パーティ戦闘力, 戻る / キャラクター設定, card labels Japanese | layout-label | "Party Power" / "Back" / "Characters"; card labels |
| rental/61-result | `en-61-result.png` | `ja-61-result.png` | problem | result labels 調査ランク / 獲得調査ポイント / 獲得FOL / 報酬アイテム Japanese | layout-label | translate result.csf labels: Rank / Exploration Points / FOL Gained / Rewards |
| rental/62-result-exp | `en-62-result-exp.png` | `ja-62-result-exp.png` | problem | 獲得EXP Japanese on Mission Result | layout-label | translate result.csf reward_exp label: "EXP Gained" |
| rental/71-rental-bonus | `en-71-rental-bonus.png` | `ja-71-rental-bonus.png` | problem | "1 players borrowed your character." runs into the portrait; plural | data | "Borrowed by %u" + " player(s)." |
| rental (other shots) | | | ok | 02-home, 06-confirm (JP labels behind as 05), 07-08 battle, 60-result, 72-home | | |
| settings/10-other-settings | `en-10-other-settings.png` | `ja-10-other-settings.png` | problem | storage setting labels/descs forced to 3-4 lines, touch the next row frames | data | shorter 2-line uimsg_*equipstorage* rows |
| settings/11-reopened | `en-11-reopened.png` | `ja-11-reopened.png` | problem | as 10 | data | as 10 |
| settings/21-after-restart | `en-21-after-restart.png` | `ja-21-after-restart.png` | problem | as 10 | data | as 10 |
| settings/23-after-reset | `en-23-after-reset.png` | `ja-23-after-reset.png` | problem | as 10 | data | as 10 |
| settings/22-reset-dialog | `en-22-reset-dialog.png` | `ja-22-reset-dialog.png` | problem | prompt 3 short lines (machine replaced GL); 初期設定に戻す art JP | data+sprite | GL wording; -en config_top art |
| settings/29-planets | `en-29-planets.png` | `ja-29-planets.png` | problem | header desc 2 lines on the header edge | client-wrap+data | "Select a planet to explore." |
| settings/30-library | `en-30-library.png` | `ja-30-library.png` | problem | メインストーリー / サブストーリー tab art JP | sprite | -en scenario_library art |
| settings (other shots) | | | ok | 02-home | | |
| simulator-continue/20-title | `en-20-title.png` | `ja-20-title.png` | problem | ムービー再生 label + round title buttons Japanese | server+sprite | English master before the title; -en title button art |
| simulator-continue/04-simulator-rental | `en-04-simulator-rental.png` | `ja-04-simulator-rental.png` | problem | title "Character on Loan" into desc; desc wraps ("loan." alone); 最終ログイン Japanese | client-wrap+layout-label+data | header-desc class fix; "Pick a loan character."; "Last Login" |
| simulator-continue/05-simulator-party | `en-05-simulator-party.png` | `ja-05-simulator-party.png` | problem | モンスターレベル / ステージ数, パーティ戦闘力, 戻る / キャラクター設定 JP; "No Loans" | layout-label+data | translate labels; "No Loan" |
| simulator-continue/09-simulator-end | `en-09-simulator-end.png` | `ja-09-simulator-end.png` | problem | 3 short ragged lines (minor) | data | uimsg_training_retire2 2 lines |
| simulator-continue/10-character-menu-again | `en-10-character-menu-again.png` | `ja-10-character-menu-again.png` | problem | "Change Equipment, Skills, and Assists" ~10px; 大成功率UP! JP | data+client-wrap+sprite | "Equip / Skills / Assists"; -en badge |
| simulator-continue (other shots) | | | ok | 02-home, 03-character-menu-end, 06, 07, 08-pause, 11-continued, 12-retired, 21-home | | |
| sphere211/04-home | `en-04-home.png` | `ja-04-home.png` | problem | GAP: rental bonus popup Japanese except the item name | data | add uimsg_sphere211_getting_rental_bonus English |
| sphere211/04b-rental-bonus | `en-04b-rental-bonus.png` | `ja-04b-rental-bonus.png` | problem | GAP: rental bonus popup Japanese except the item name | data | add uimsg_sphere211_getting_rental_bonus English |
| sphere211/05-board | `en-05-board.png` | `ja-05-board.png` | problem | WRONG drop bonus; Clear Count / Deployed Count / S Stamina label-value overlaps | data+client-wrap | as sphere211-continue/05-board |
| sphere211/35-board | `en-35-board.png` | `ja-35-board.png` | problem | WRONG drop bonus; Clear Count / Deployed Count / S Stamina label-value overlaps | data+client-wrap | as sphere211-continue/05-board |
| sphere211/45-board-after | `en-45-board-after.png` | `ja-45-board-after.png` | problem | WRONG drop bonus; Clear Count / Deployed Count / S Stamina label-value overlaps | data+client-wrap | as sphere211-continue/05-board |
| sphere211/49-board | `en-49-board.png` | `ja-49-board.png` | problem | WRONG drop bonus; Clear Count / Deployed Count / S Stamina label-value overlaps | data+client-wrap | as sphere211-continue/05-board |
| sphere211/60-goal | `en-60-goal.png` | `ja-60-goal.png` | problem | WRONG drop bonus; Clear Count / Deployed Count / S Stamina label-value overlaps | data+client-wrap | as sphere211-continue/05-board |
| sphere211/66-floor2 | `en-66-floor2.png` | `ja-66-floor2.png` | problem | WRONG drop bonus; Clear Count / Deployed Count / S Stamina label-value overlaps | data+client-wrap | as sphere211-continue/05-board |
| sphere211/70-board-after | `en-70-board-after.png` | `ja-70-board-after.png` | problem | WRONG drop bonus; Clear Count / Deployed Count / S Stamina label-value overlaps | data+client-wrap | as sphere211-continue/05-board |
| sphere211/10-cell1-detail | `en-10-cell1-detail.png` | `ja-10-cell1-detail.png` | problem | mission detail labels + シングルプレイ開始 / 戻る JP; "Stamina Consumed" tiny | layout-label+data+client-wrap | translate mission_confirmation labels |
| sphere211/10-cell1-rental | `en-10-cell1-rental.png` | `ja-10-cell1-rental.png` | problem | title "Character on Loan" into desc; desc wraps ("loan." alone); 最終ログイン Japanese | client-wrap+layout-label+data | header-desc class fix; "Pick a loan character."; "Last Login" |
| sphere211/10-cell1-party | `en-10-cell1-party.png` | `ja-10-cell1-party.png` | problem | "Number of Depl70/73 Characters戦闘力"; 3 buttons overflow; パーティ戦闘力 JP | data+client-wrap+layout-label | as sphere211-continue/06-rental-party |
| sphere211/20-cell2-detail | `en-20-cell2-detail.png` | `ja-20-cell2-detail.png` | problem | mission detail labels + シングルプレイ開始 / 戻る JP; "Stamina Consumed" tiny | layout-label+data+client-wrap | translate mission_confirmation labels |
| sphere211/20-cell2-rental | `en-20-cell2-rental.png` | `ja-20-cell2-rental.png` | problem | title "Character on Loan" into desc; desc wraps ("loan." alone); 最終ログイン Japanese | client-wrap+layout-label+data | header-desc class fix; "Pick a loan character."; "Last Login" |
| sphere211/20-cell2-party | `en-20-cell2-party.png` | `ja-20-cell2-party.png` | problem | "Number of Depl70/73 Characters戦闘力"; 3 buttons overflow; パーティ戦闘力 JP | data+client-wrap+layout-label | as sphere211-continue/06-rental-party |
| sphere211/30-cell3-detail | `en-30-cell3-detail.png` | `ja-30-cell3-detail.png` | problem | mission detail labels + シングルプレイ開始 / 戻る JP; "Stamina Consumed" tiny | layout-label+data+client-wrap | translate mission_confirmation labels |
| sphere211/30-cell3-rental | `en-30-cell3-rental.png` | `ja-30-cell3-rental.png` | problem | title "Character on Loan" into desc; desc wraps ("loan." alone); 最終ログイン Japanese | client-wrap+layout-label+data | header-desc class fix; "Pick a loan character."; "Last Login" |
| sphere211/30-cell3-party | `en-30-cell3-party.png` | `ja-30-cell3-party.png` | problem | "Number of Depl70/73 Characters戦闘力"; 3 buttons overflow; パーティ戦闘力 JP | data+client-wrap+layout-label | as sphere211-continue/06-rental-party |
| sphere211/40-cell6-detail | `en-40-cell6-detail.png` | `ja-40-cell6-detail.png` | problem | mission detail labels + シングルプレイ開始 / 戻る JP; "Stamina Consumed" tiny | layout-label+data+client-wrap | translate mission_confirmation labels |
| sphere211/40-cell6-rental | `en-40-cell6-rental.png` | `ja-40-cell6-rental.png` | problem | title "Character on Loan" into desc; desc wraps ("loan." alone); 最終ログイン Japanese | client-wrap+layout-label+data | header-desc class fix; "Pick a loan character."; "Last Login" |
| sphere211/40-cell6-party | `en-40-cell6-party.png` | `ja-40-cell6-party.png` | problem | "Number of Depl70/73 Characters戦闘力"; 3 buttons overflow; パーティ戦闘力 JP | data+client-wrap+layout-label | as sphere211-continue/06-rental-party |
| sphere211/50-boss-detail | `en-50-boss-detail.png` | `ja-50-boss-detail.png` | problem | mission detail labels + シングルプレイ開始 / 戻る JP; "Stamina Consumed" tiny | layout-label+data+client-wrap | translate mission_confirmation labels |
| sphere211/50-boss-rental | `en-50-boss-rental.png` | `ja-50-boss-rental.png` | problem | title "Character on Loan" into desc; desc wraps ("loan." alone); 最終ログイン Japanese | client-wrap+layout-label+data | header-desc class fix; "Pick a loan character."; "Last Login" |
| sphere211/50-boss-party | `en-50-boss-party.png` | `ja-50-boss-party.png` | problem | "Number of Depl70/73 Characters戦闘力"; 3 buttons overflow; パーティ戦闘力 JP | data+client-wrap+layout-label | as sphere211-continue/06-rental-party |
| sphere211/15-heal-items | `en-15-heal-items.png` | `ja-15-heal-items.png` | problem | title + 所持 JP; "Sphere Stamina" vs "S Stamina" (minor) | layout-label+data | "Select an item to use." / "Owned" |
| sphere211/15-heal | `en-15-heal.png` | `ja-15-heal.png` | problem | "recover" alone; 現在のスタミナ / 回復後のスタミナ / 決定 JP | data+client-wrap+layout-label | as sphere211-continue/09-heal |
| sphere211/15-healed | `en-15-healed.png` | `ja-15-healed.png` | problem | done dialog all JP | layout-label | translate shop_stamina2 labels |
| sphere211/40-cell6-result | `en-40-cell6-result.png` | `ja-40-cell6-result.png` | problem | 調査ランク / 獲得調査ポイント / 獲得FOL JP; 初回クリア badge JP | layout-label+sprite | translate result_sphere211 labels; -en first_badge |
| sphere211/45-return-dialog | `en-45-return-dialog.png` | `ja-45-return-dialog.png` | problem | rate list merged into prose, panel full; "Reset" | data | uimsg_sphere211_return_dialog one rate per line |
| sphere211/70-return-dialog | `en-70-return-dialog.png` | `ja-70-return-dialog.png` | problem | rate list merged into prose, panel full; "Reset" | data | uimsg_sphere211_return_dialog one rate per line |
| sphere211/45-returned | `en-45-returned.png` | `ja-45-returned.png` | problem | sentence split after "All", stray capitals (minor) | data | uimsg_sphere211_return_finished |
| sphere211/70-returned | `en-70-returned.png` | `ja-70-returned.png` | problem | sentence split after "All", stray capitals (minor) | data | uimsg_sphere211_return_finished |
| sphere211/45-treasure-data | `en-45-treasure-data.png` | `ja-45-treasure-data.png` | problem | section header art スフィア211 / 解析するトレジャーデータ / 解析結果 JP | sprite | -en result_tbox title_logo art |
| sphere211/70-treasure-data | `en-70-treasure-data.png` | `ja-70-treasure-data.png` | problem | section header art スフィア211 / 解析するトレジャーデータ / 解析結果 JP | sprite | -en result_tbox title_logo art |
| sphere211/45-treasure-items | `en-45-treasure-items.png` | `ja-45-treasure-items.png` | problem | section header art トレジャーデータ / 獲得アイテム JP | sprite | -en result_tbox title_logo art |
| sphere211/70-treasure-items | `en-70-treasure-items.png` | `ja-70-treasure-items.png` | problem | section header art トレジャーデータ / 獲得アイテム JP | sprite | -en result_tbox title_logo art |
| sphere211/50-boss-battle | `en-50-boss-battle.png` | `ja-50-boss-battle.png` | problem | en shot black (transition): not reviewable | - | re-take the shot |
| sphere211/62-next-floor | `en-62-next-floor.png` | `ja-62-next-floor.png` | problem | question + warning as 5-line prose | data | uimsg_sphere211_next_floor_confirm with blank line |
| sphere211/63-floor-result | `en-63-floor-result.png` | `ja-63-floor-result.png` | problem | section header art フロアリザルト / 獲得トレジャーデータ / クリア報酬 JP | sprite | -en sphere211_result_floor art |
| sphere211/64-floor-select | `en-64-floor-select.png` | `ja-64-floor-select.png` | problem | "Max Transfer+Floor"; "To Selected Floor" over button; 4-line annotation, 3 words for 転移; header art JP | data+client-wrap+sprite | "Max Floor"; "Go to Floor"; one term "Warp LV"; -en art |
| sphere211/64b-reroll-confirm | `en-64b-reroll-confirm.png` | `ja-64b-reroll-confirm.png` | problem | ragged 3 lines (minor) | data | "Use %s\nto reroll the floors?" |
| sphere211/64c-rerolled | `en-64c-rerolled.png` | `ja-64c-rerolled.png` | problem | as 64-floor-select | data+client-wrap+sprite | as 64 |
| sphere211/65-confirm | `en-65-confirm.png` | `ja-65-confirm.png` | problem | "sure?" alone (minor) | data | uimsg_sphere211_select_next_floor_confirm 3 lines |
| sphere211 (other shots) | | | ok | 04c-home, 10/20/30/40-cell battle, 10/20/30-cell result, 50-boss-result | | |
| sphere211-continue/04-home | `en-04-home.png` | `ja-04-home.png` | problem | GAP: rental bonus popup Japanese except the item name | data | add uimsg_sphere211_getting_rental_bonus English |
| sphere211-continue/04b-rental-bonus | `en-04b-rental-bonus.png` | `ja-04b-rental-bonus.png` | problem | GAP: rental bonus popup Japanese except the item name | data | add uimsg_sphere211_getting_rental_bonus English |
| sphere211-continue/05-board | `en-05-board.png` | `ja-05-board.png` | problem | WRONG: "+10 drops every 1 hits"; label/value overlaps; "Records" art vs "Achievements" | data+client-wrap+sprite | "%u-hit combo: drops +%u"; short labels; -en art |
| sphere211-continue/06-rental-list | `en-06-rental-list.png` | `ja-06-rental-list.png` | problem | title "Character on Loan" into desc; desc wraps ("loan." alone); 最終ログイン Japanese | client-wrap+layout-label+data | header-desc class fix; "Pick a loan character."; "Last Login" |
| sphere211-continue/06-rental-party | `en-06-rental-party.png` | `ja-06-rental-party.png` | problem | "Number of Depl73/73 Characters戦闘力"; 3 buttons overflow; tiny "Stamina Consumed"; JP labels | data+client-wrap+layout-label | "Deployable"; shorter/shrink buttons; translate labels |
| sphere211-continue/06-party | `en-06-party.png` | `ja-06-party.png` | problem | as 06-rental-party | data+client-wrap+layout-label | as 06-rental-party |
| sphere211-continue/06-lose-detail | `en-06-lose-detail.png` | `ja-06-lose-detail.png` | problem | 主な報酬 / 主な出現モンスター / シングルプレイ開始 / 戻る JP | layout-label | translate mission_confirmation labels |
| sphere211-continue/08-board | `en-08-board.png` | `ja-08-board.png` | problem | as 05-board | data+client-wrap+sprite | as 05 |
| sphere211-continue/09-heal-items | `en-09-heal-items.png` | `ja-09-heal-items.png` | problem | title 使用するアイテムを... and 所持 JP | layout-label | "Select an item to use." / "Owned" |
| sphere211-continue/09-heal | `en-09-heal.png` | `ja-09-heal.png` | problem | "recover" alone on line 2; 現在のスタミナ / 回復後のスタミナ / 決定 JP | data+client-wrap+layout-label | "Use %s\nto recover %d Stamina."; translate shop_stamina |
| sphere211-continue/09-healed | `en-09-healed.png` | `ja-09-healed.png` | problem | done dialog all JP | layout-label | translate shop_stamina2 labels |
| sphere211-continue/10-achievements-other | `en-10-achievements-other.png` | `ja-10-achievements-other.png` | problem | "Time LefNon-expiring"; summon row 3 lines in 2-line slot | data+client-wrap | "No limit"; message_ac_ind_05 shorter |
| sphere211-continue/11-decline-detail | `en-11-decline-detail.png` | `ja-11-decline-detail.png` | problem | as 06-lose-detail | layout-label | as 06-lose-detail |
| sphere211-continue/11-decline-party | `en-11-decline-party.png` | `ja-11-decline-party.png` | problem | as 06-rental-party | data+client-wrap+layout-label | as 06-rental-party |
| sphere211-continue/12-declined | `en-12-declined.png` | `ja-12-declined.png` | problem | as 05-board | data+client-wrap+sprite | as 05-board |
| sphere211-continue/12-board | `en-12-board.png` | `ja-12-board.png` | problem | as 05-board | data+client-wrap+sprite | as 05-board |
| sphere211-continue (other shots) | | | ok | 04c-home, 07-continued, 10-achievements-daily/-weekly/-event | | |
| stamps/03-stamps-menu | `en-03-stamps-menu.png` | `ja-03-stamps-menu.png` | problem | header desc 2 lines on the header edge | client-wrap+data | header-desc fix |
| stamps/07-back | `en-07-back.png` | `ja-07-back.png` | problem | header desc 2 lines on the header edge | client-wrap+data | header-desc fix |
| stamps/r03-stamps-menu | `en-r03-stamps-menu.png` | `ja-r03-stamps-menu.png` | problem | header desc 2 lines on the header edge | client-wrap+data | header-desc fix |
| stamps/r06-back | `en-r06-back.png` | — | problem | header desc 2 lines on the header edge | client-wrap+data | header-desc fix |
| stamps/03-stamps | `en-03-stamps.png` | `ja-03-stamps.png` | problem | stamp pictures carry Japanese lettering (low priority) | sprite | accept or -en stamp art |
| stamps (other shots) | | | ok | 02-home, 04-help-on-page1, 05-page4, 06-rush-on-page4, r03-stamps, r04-page4-kept, r05-rush-on-page3 | | |
| storage/03-item-menu | `en-03-item-menu.png` | `ja-03-item-menu.png` | problem | storage buttons shrunk to ~10 px in fixed-size labels | data+client-wrap | shorter uimsg_itemmenu_*equipstorage* |
| storage/04-deposit | `en-04-deposit.png` | `ja-04-deposit.png` | problem | "Inventory Storage" runs into its count; desc 2 lines; tab/button art JP | data+client-wrap+sprite | "Stored"; "Select items to store."; -en art |
| storage/05-deposit-confirm | `en-05-deposit-confirm.png` | `ja-05-deposit-confirm.png` | problem | 3 lines (fits); footer overlap as 04 | data+client-wrap | as 04 |
| storage/06-deposited | `en-06-deposited.png` | `ja-06-deposited.png` | problem | "storage." alone on line 2 (wrap 680) | data+client-wrap | "Equipment moved to storage." |
| storage/07-withdraw | `en-07-withdraw.png` | `ja-07-withdraw.png` | problem | WORST: title "Remove from Storage" over desc; footer overlap; art JP | data+client-wrap+sprite | "Withdraw"; "Select items to take out." |
| storage/08-withdrawn | `en-08-withdrawn.png` | `ja-08-withdrawn.png` | problem | "storage." alone; title/desc overlap | data+client-wrap | "Equipment taken out of storage."; as 07 |
| storage/09-sell-confirm | `en-09-sell-confirm.png` | `ja-09-sell-confirm.png` | problem | desc 2 lines; title touches desc; "Sell For:" icon (minor) | data+client-wrap | "Sell unneeded items for FOL." |
| storage/10-sell-warning | `en-10-sell-warning.png` | `ja-10-sell-warning.png` | problem | WORST: red list 10 lines merged prose over buttons; title 2 lines; 選択中 JP | data+client-wrap+sprite | one item per line; shorter title; -en overlay |
| storage/11-sold | `en-11-sold.png` | `ja-11-sold.png` | problem | "1200 FOL has / been / obtained." 3 lines | data+client-wrap | " FOL obtained." |
| storage/12-presents | `en-12-presents.png` | `ja-12-presents.png` | problem | プレゼント所持 / 全件取得 JP | sprite | -en presentbox art |
| storage/13-received | `en-13-received.png` | `ja-13-received.png` | problem | 以下のプレゼントを取得しました / 閉じる JP | layout-label | translate presentbox_dialog3 labels |
| storage/14-item-menu | `en-14-item-menu.png` | `ja-14-item-menu.png` | problem | as 03 | data+client-wrap | as 03 |
| storage/16-back | `en-16-back.png` | `ja-16-back.png` | problem | as 03 | data+client-wrap | as 03 |
| storage/r03-item-menu | `en-r03-item-menu.png` | `ja-r03-item-menu.png` | problem | as 03 | data+client-wrap | as 03 |
| storage/15-one-time | `en-15-one-time.png` | `ja-15-one-time.png` | problem | title "Retrieve from Storage" over desc; does not say Temporary | data+client-wrap | "Temp. Storage"; "Select items to take out." |
| storage/r04-storage | `en-r04-storage.png` | `ja-r04-storage.png` | problem | as 07 + footer overlap + art | data+client-wrap+sprite | as 07, 04 |
| storage/r05-one-time | `en-r05-one-time.png` | `ja-r05-one-time.png` | problem | as 15 | data+client-wrap | as 15 |
| storage/r06-count | `en-r06-count.png` | `ja-r06-count.png` | problem | 選択中 overlay JP; title/desc as 15 | sprite+data+client-wrap | -en art; as 15 |
| storage/r07-confirm | `en-r07-confirm.png` | `ja-r07-confirm.png` | problem | uneven 3 lines (minor); title/desc as 15 | data+client-wrap | uimsg_item_dialog_gacha_equipstorage_out |
| storage/r08-taken | `en-r08-taken.png` | `ja-r08-taken.png` | problem | title/desc overlap as 15 (text fits) | data+client-wrap | as 15 |
| storage/r09-empty | `en-r09-empty.png` | `ja-r09-empty.png` | problem | title/desc overlap as 15 (text fits) | data+client-wrap | as 15 |
| storage (other shots) | | | ok | 01-title (known), 02-home | | |
| tower/05-extra-dungeon | `en-05-extra-dungeon.png` | `ja-05-extra-dungeon.png` | problem | desc "Please select an episode. (Temp)" 2 lines; banner art JP | data+client-wrap+sprite | "Select an episode."; -en banners |
| tower/06-floors | `en-06-floors.png` | `ja-06-floors.png` | problem | title into desc; desc 2 lines; floor banners + イベントメニュー JP | data+client-wrap+sprite | "Pick a floor (solo only)."; header class fix; -en art |
| tower/07-area | `en-07-area.png` | `ja-07-area.png` | problem | title over desc; コンティニュー不可 / モンスターレベル / ステージ数 JP | client-wrap+layout-label | header class fix; translate card labels |
| tower/08-detail | `en-08-detail.png` | `ja-08-detail.png` | problem | 初回クリア報酬 / 主な報酬 / 主な出現モンスター + card labels JP | layout-label | translate mission_confirmation labels |
| tower/09-helper | `en-09-helper.png` | `ja-09-helper.png` | problem | title "Character on Loan" into desc; desc wraps ("loan." alone); 最終ログイン Japanese | client-wrap+layout-label+data | header-desc class fix; "Pick a loan character."; "Last Login" |
| tower/10-party | `en-10-party.png` | `ja-10-party.png` | problem | パーティ戦闘力, 戻る / キャラクター設定, card labels JP | layout-label | "Party Power" / "Back" / "Characters" |
| tower/14-area-after | `en-14-area-after.png` | `ja-14-area-after.png` | problem | as 07 | client-wrap+layout-label | as 07 |
| tower/15-floors-again | `en-15-floors-again.png` | `ja-15-floors-again.png` | problem | as 06 | data+client-wrap+sprite | as 06 |
| tower/16-back | `en-16-back.png` | `ja-16-back.png` | problem | as 05 | data+client-wrap+sprite | as 05 |
| tower (other shots) | | | ok | 04-home, 11-confirm, 12-battle, 13-result | | |

### 7.13 Line breaking: who breaks what; the story window's font (E13)

Agent `en-textclean`, 2026-10-07. One breaker, `soa::text::break_lines` (`common/include/soa/line_break.h`), with explicit options; its rules are the shared vectors `common/tests/line_break_vectors.tsv`, which `build/common/soa_text_tests` (T0 `line-break`) and `tests/test_line_break.py` (against `tools/english_core.py` `Font.rebreak`) both pass. The server's derivation calls it (`rebreak_u`; byte-identical, `tests/test_english_derive.py`), and so do the client's label wrap (E10) and box fit (`fit_box`, E12, E13).

| Text | Broken by | Rule |
|---|---|---|
| master rows whose Japanese has line breaks, when Global's English has none | the data (`finish`) | at the Japanese row's widest line (≥ 200 px) |
| every other label (buttons, dialogs, lists) | the client at draw time (E10) | the label's existing breaks kept, each line broken at its room (a fixed box's width, else the room on the screen); Japanese lines left alone |
| the home's two talk labels | the client (E12) | breaks collapsed, re-broken for 480 × 2 lines at the largest scale that fits, shrunk by the label's own fit |
| story lines | the data only (`story_finish` → `story_break`) | 480 px when the line fits the window's 4 lines; else 128 n − 32 px for the fewest n lines that hold it |
| the story window's font | the client (E13) | k = min(1, 600 / width, 4 lines' height / height) at Show's FontSize 30, from the data's breaks |

- **No double wrapping.** The E10 wrap leaves the story window's labels (the message label, `Append`'s `AppendMessage` clones) alone; before E13 it could re-break a story line revealed a character at a time differently from the whole line. The offline break and the client's scale agree: n lines at the client's scale k_n = 150 / (40 n − 10) are as wide as 480 / k_n = 128 n − 32 font px, which is the width the data breaks them at.
- **The story window** (client-changes.md "The story message window"): one label at FontSize 30, line spacing 10 (lines 40 apart; four lines 150 units high, measured), 600 units (480 font px) wide; `ParseMessage` splits a message at its tags into `MessageChange` (the text up to the first tag) and `MessageAppend` (colour segments, clones of the label placed after the text before them). No font-size tag is applied by the 3.7.0 client: `ParseMessage`'s segment switch has no size case (3.3's `<fontsize=…>` was read from the disassembly and never run). So E13 hooks `ParseMessage` (to know each message's whole text) and `Change` (to set the label's FontSize and spacing before the message is laid out).
- **Sizes** (every English story line served on 2026-10-07, after the 31B import, by the font's advances; the live client's scale agreed exactly on the lines shot): 22,050 lines; 21,650 of them take 1–4 lines (5,565 / 5,583 / 5,390 / 5,112), 399 take 5 and 1 takes 6. 19,946 keep FontSize 30 (100%); 16 get 27–30, 1,200 get 24–27, 861 get 21–24, 27 get 19.6–21. The smallest is 65% (FontSize 19.6, `D026_030_18`, six lines); p1 79%, p5 80%, median 100%. Before (one break at 480 px for every line) 2,103 lines needed 5 or more window lines and ran over Skip / Auto; at the same scale rule but without the wider break the smallest would have been 43% (nine lines).
- **Shots** (`work/english/textclean/story-e13/`, local; `control/run.py campaign ... --lang en --english`): `en-D026_030_18-65pct.png` and `en-D056_030_06-68pct.png` (with `SOA_TEST_STORY_TEXTS`), `en-1010_030_02-84pct.png` (the scene mc01_030 with the served data: four lines at 84%).
- **Open:** the back log (`CEventScenarioBackLog`) shows past messages in its own layout and was not checked for 5-line messages. A message whose wider break comes out with fewer lines than n (the greedy break) is scaled by its width, a little smaller than its height would allow (`1010_030_02`: 84% for four lines). Checked in 7.15: its narrowest four-line break is 572 px (83.9% against 83.6% now; five lines would be 78.9%), so choosing the narrowest break for the line count would gain a third of a point there; `story_break` is left as it is.

### 7.14 Layout labels: the Japanese in the scenes' node trees

Agent `enf-labels`, 2026-10-07 (rules: [server-rules](server-rules.md#english-labels)). The server's `--english` CDN step now writes a `-en` copy of every scene whose node tree has a fixed Japanese label it can translate, in the same pass as the English art (one file per scene, with the atlas edit when the scene also has a recipe).

**What is in the trees.** A dump of every `.msgp` member of the 853 `UI/` and `TalkScene/` scenes (1,001 node trees; `msgpack` in Python, `work/english/followup/labels/all.tsv`, local) found Japanese only in the str values of two keys: `LabelText` (1,051 values, `TextObjectData` nodes) and `ButtonText` (2: `stamp.csf`'s 閉じる). That is 1,053 labels, 503 distinct texts, in 182 scenes (the sweep's 920 / 440 / 173 left out the placeholders it recognised).

**Which are translated: `data/english/labels.tsv`.** Only the Japanese listed there is replaced. Left out (they stay as they are): placeholder texts the client overwrites, such as ああああ runs, 説明文…, 名前ああ…, ０００ / 999 / 99枠, sample dates (2018/12/31(水)メンテナンスまで), sample names (惑星エリクール, フィオーレ), and fragments whose word order English can't keep (さんとの after a player name). The list was made from the dump by pattern and then by hand, unclear texts judged by their node paths (名前 is a name plate's, 説明文 a header description's placeholder); when unsure a label was kept (a placeholder the code overwrites shows the code's text anyway, e.g. クリアタイム shows as "Clear Time"). 364 distinct texts are listed. Of the 1,053 labels, 788 in 170 scenes are translated; 265 (139 distinct) stay.

**Where the English comes from** (at server start, `english::resolve_labels`; the precedence of [7.9](#79-the-derivation-spec) step 7):

| Source | Distinct texts | Labels | How |
|---|---:|---:|---|
| official | 202 | 515 | the served English of a JP master row with the same Japanese (exact, or but for white space), whose English is Global's |
| memory / template | 52 / 1 | 87 / 2 | Global's English for the same Japanese text (the derivation's memory over `data/basmaster-gl.sqlite3`; e.g. 獲得EXP "EXP Gained:", 消費スタミナ "Stamina Cost", スキップしますか？ "Skip this?") |
| machine | 103 | 178 | 13 served master machine rows; 90 new rows of the MT run below |
| agent | 6 | 6 | rows where the machine text ran the Japanese paragraphs together or added a heading (marked for a person's review) |

Official and memory English is not committed: a `derived` row of `labels.tsv` has no `en`, and the server takes the English from the merged master table or Global's memory at build time, as for the master. Our rows (machine, agent, human, reviewed) are checked as master rows (`english_text.py labels --check`, in the T0 pytest).

**The MT batch.** `tools/english_mt_run.py labels --dump DIR` (DIR from `soa-server --english-dump`, whose `labels-en.tsv` lists what the server resolves) sends each listed label without English once (Gemma 4 31B, prompt v2 with the kind "UI layout label", `--share-gpu`, 2 slots: 100 labels in 2.1 min); `english_text.py import-mt` takes the `"kind": "label"` rows into `labels.tsv` as `machine` rows. 99 passed, 1 failed the glossary (ホストがコンティニュー選択中です, a multiplayer popup the local server never shows: dropped from the list). No row was shortened for space. The record is the checkpoint `work/english/followup/labels/mt/labels.jsonl` (local; model, quantization, prompt, llama.cpp build per row), not a re-run (7.10).

**The file.** A scene is the ISF image `<name>.msgp` (+ `.aif`, `.csv`, more trees in 59 scenes). The label walk (`english_art::rewrite_labels`) goes through the raw msgpack stream and replaces only the str payloads of `LabelText` / `ButtonText` values that are listed (the smallest str header for the new text; the files use fixstr and str8); every other byte is copied, so int keys, `bin` and `ext` values, float32 and the encoder's header choices stay the game's. The ISF repacker (`aska::isf_repack`) lays the members out again: header, entry table and names as they were, then each payload in entry order at the next 32-byte boundary, the gaps and the end padded with 0xee, each entry's offset, size and sum (`aska::isf_payload_sum`) rewritten. All 853 scenes follow that layout, so a scene repacks to its own bytes; `english-art --check-roundtrip` checks the repack and the walk on every scene of the download (853 scenes, 1,001 trees: the same bytes). The build reads every scene at start (a partial SLZ decode up to the last tree), about 0.5 s with the stamps current; a cold build of art and labels together about 50 s.

**Shots** (`work/english/followup/labels/`, local; `before-*` are the sweep's `--lang en` shots of the same steps, `after-*` this branch's, every session with the sweep's wrapper adding `--lang en --english`): the mission result (`missions-a02-result`: Rank, Exploration Points:, FOL:, Rewards; `a03`: EXP Gained:), the mission detail (`campaign-07`: Stamina Cost, Enemy Level, Number of Stages, Initial Clear Reward, Primary Rewards:), the party select (`campaign-09`: Party Combat Strength, Back, Character Settings), the story's skip popup (`campaign-86`: Skip this? / No / Yes), the birth-date dialog (`coins-11`: Register, the red note), the coin shop's Close, the enhancement / augment / limit-break dialogs (`growth-*`). Sessions missions, party, campaign, growth and coins passed.

**Left for the client (E10) or pictures:**

- パーティ戦闘力 "Party Combat Strength" runs into the number on its right (`party_organization.csf` `Node_2/power_base/Text`, `party_select_single2.csf` `list/plate/power_base/Text`, `partymenu_top2.csf` `list/power_base/Text`, FS18, no custom size): it needs to shrink into the room left of the value.
- The augment dialog's 必要素材 / 必要数 column ("Materials" / "Needed", `pm_evolution.csf` `pop1/window/all/Text_1` and its siblings; `party_evolution.csf`, `party_overlimit.csf`, `pm_awake.csf` alike) is wider than the Japanese column and overlaps the item icons.
- The birth-date table's cells (`uimsg_able_use_money`: master rows, not labels) still overlap (7.12 "Still open").
- Pictures, not labels: the growth dialogs' 獲得EXP / 所持FOL / 必要FOL / 所持 plates, 限界突破後, 詳細, 進化する, the party edit's シンボル選択 / ロック / メンバー変更 (no recipe yet).

### 7.15 Client layout fixes after the sweep

Agent `enf-client`, 2026-10-07: the "Still open (client)" list of 7.12 (`labels.tsv`'s classes). One rule does most of it: E10 now gives a label the room its **layout** leaves it, not only the room on the screen (client-changes.md "Word wrap at spaces", the bullet "The room from the layout"; `text::layout_room`, selftest `platform370/lang-layout-room`). The room ends where a shown sibling on the label's row begins (two labels that face each other share the gap at one scale) and at the box of a parent that holds the label (a button, a list row, an icon); a label so bounded is **shrunk** into it, never reworded and not moved. Texts of any length are considered now (the old wrap needed 12 bytes and a space), tag-mode labels too.

| Case (7.12) | What changed | Shots (`work/english/followup/client/`, local) |
|---|---|---|
| a. header titles over the description | the title (`Node_1` / `Node_maintitle` `/Text_1`) ends 6 units before its description `Text_2` once the description has slid in (both settled): "Weapon Customization" 80%, "Select Characters" 99% (a gap now), "Character on Loan" | `before-a-*`, `after-a-growth-04-select-characters.png`, `after-a-growth-23-weapon-customization.png` |
| b. menu-button text over its left icon | the centred text's room ends at the icon (`follow_top`, `shop_top`): "Increase Follow Slots", "Expand Follow Slots", "Increase Inventory Slots" … shrunk to the room right of the icon | `after-b-home-21-follow.png`, `after-b-home-33-shop.png` |
| c. list rows wrapped at the screen edge | the row frame (the parent `Button`, 622 wide) ends the room; a description that would wrap out of its free band (under the row's name) is one line shrunk to the frame | `after-c-m14-exchange.png` |
| d. labels running into their values / wider than their icon | sibling and parent rooms: "Continuous Clear Count", "S Stamina", "Max Transfer Floor", "Number of Deployable Characters", "EXP Needed for Next LV", "Factor Extraction Rate", "FOL Required:", "Awakenings"; "Limit Break" on the gacha's face icons and "To Exceed Connect" fit their icon / plate; button texts wider than their button ("To Selected Floor", "Auto-Formation") fit it; from en-followup's layout labels: "Party Combat Strength" ends at its arrow icon (about 55%: it is centred, the icon is close), "Materials" / "Needed" end at the item list beside them (a sibling as tall as the rows it spans counts on each row) | `after-d-home-12-sphere211.png`, `after-d-sphere211-64-floor-select.png`, `after-d-m05-status.png`, `after-d-party-04-party-top.png`, `after-d-growth-11-evolve-materials.png` |
| e. the gacha result dialog | a dialog's message with the data's own breaks keeps them and is shrunk into the room (Global's two rows: 4 lines, as the Japanese, shrunk to the room's 658 units); the room above its button counts `menu_pop_line` rules too | `after-e-battle-gacha-16-result.png` |
| f. the birth-date table | its cells are siblings: "1 month" and "Up to 5,000 yen" face each other and share the gap at one scale | `after-f-coins-11-birth-dialog.png` |
| g. the tag-mode line of the character guide | not a marquee (the Japanese is one static line): shrunk into the screen's room on one line | `after-g-m04-guide-detail.png` |
| h. `1010_030_02` at 84% | not changed: the narrowest four-line break gains a third of a point (7.13 Open) | — |

**How it was run:** the sessions home, growth, coins, battle-gacha, sphere211, party and deepspace with a wrapper that appends `--lang en --english` (as in 7.12), all PASS; a hand-driven client (`soaslot.py run` + `soactl.py`) for the item exchange, the character guide and its stat details. The before shots are 7.12's (`work/english/textclean/after/` and `manual/`, the same E10 code before this change), copied as `before-*`. The after shots of home, coins, growth, party and battle-gacha are from the final build; those of sphere211 and the hand-driven run (the exchange, the guide, the stat details) from earlier builds of this change (the exchange's with the free-band rule). One growth run crashed in the guest's `Aska::TextureManager::SubRemoveTextureEx` (a guest read fault, opening the item menu); two reruns of the same build passed, so it is noted as a flake, not this change's.

**Not fixed (and why):**
- Labels bounded by a **cousin** (a node under another parent): the party card's names grow left over the element icon (`name_plate/name`, the icon is under `chara_plate`); "Limit Break" on the stat details runs into its icon (another node); the gear menus' "Set Condition" / ★ cases where the icon isn't a sibling. The room comes only from siblings and the parent, a rule that holds for the whole UI; reaching into other branches needs per-screen knowledge.
- The character profile (en-followup's item 4, `character_profile.csf`): "Japanese VA:", "Birthplace:" and "Birthday:" are siblings of their values (`cv/title` / `cv/name`, `title_bar/Text_2_1` / `Text_2_2`, `Text_6_1` / `Text_6_2`), so this rule should shrink them before their value (down to about 50%: the values sit where the short Japanese captions end; not shot). The profile's description `title_bar/Text_4` (15 lines, the data's breaks) runs past its box onto Close: Close is not its sibling and the label is not a dialog message, so it is left; a rule for it would need the window's button as the bound.
- Two labels that overlap by more than the 40% floor allows are left (they are laid out on top of each other on purpose, or one of them is a placeholder); labels whose layout needs less than 50% on one line are wrapped (or left) as before.

### 7.16 The follow-ups: story gaps, the profile and back log, data rows

Agent `en-followup`, 2026-10-07, after the sweep (7.12).

**The 25 story lines without English (all 64 story files complete and served now).** The 25 lines of 13 files (`story-missing.tsv` of the sweep) were translated by the 31B (`story-fix`) on 2026-10-07 but refused by the checks (`work/english/mt-rejected-story.tsv`). Why, and what was done:

| Lines | Why refused | Done |
|---|---|---|
| `2018_290_41`, `2018_300_09`, `2043_130_31`, `2061_010_22` (+ `2051_020_24`) | the machine glossary contradicted itself: ユーイン = Euwin (the name 310 story rows use) but ユーイン・ラクスター = Ewin Laxter, サー・ユーイン = Sir Ewin, ラクスター = Rakstar | the three glossary rows made consistent (Euwin Laxter, Sir Euwin, Laxter; the old spellings kept as variants, so no served row changes); the 31B's answers then pass and were imported |
| `2072_110_17`, `2091_050_58`, `2101_020_62`, `6024_190_04`, `6041_030_20/34/54`, `D076_030_05`, `D076_050_20`, `D093_020_09`, `E036_060_26`, `2067_270_04`, `6053_220_13` | the engine left out a name (Eve, Tika, Lavarnia, Nel, Clair, Crowe, Chisato: "you" for ラヴァーニアさん), stretched a sound without end, or changed a tag | sent again with what was wrong (`english_mt_run.py story-retry`: the story-fix request plus the refused English and, per problem, the rule it broke; prompt `v2+story-v1+fix+retry1`, `work/english/followup/mt/story-retry.jsonl`, 18 lines in 0.7 min); these 13 passed and are machine rows |
| `2012_040_12`, `2042_070_48`, `D093_020_06`, `2067_270_01` | the retry still repeated the colour tag, wrote "a Copy" mid-sentence, merged the ship and its captain ("the Accura Crow, F. Almedio"), or ran away (CAPTAIII…) | `agent` rows (7.9): the engine's wording where it was right, the error mended |
| `2101_020_40`, `2101_030_104`, `6043_250_19` | the glossary check's false hits: ハナから is "from the start" (not the name Hana), 臨機応変 the idiom "adapt as we go" (not the skill Expedient Adaptation), カー……リン Karlyn stammered (not Lin) | `agent` rows whose note waives that term for that row only (`glossary-waive: ハナ (why)`; `english_text.py row_glossary`, `tests/test_english_text.py::test_glossary_waiver`); `2101_020_40` also had its subject dropped |

Result (`tools/english_text.py build`): story **21,663 of 21,663 lines English** (official 5,037, machine 17,031, agent 7), **64 of 64 files complete**; `soa-server --english` logs `english story: 64 tables, 64 files served, 0 incomplete` (was 51).

**Not yet checked in the sweep: the character profile and the story back log** (hand-driven, `--lang en --english`, shots `work/english/followup/manual/`):

- **The profile** is reached by a long press on a character's face (`soactl.py drag:X:Y:X:Y+1:1800` is a long press), then the portrait, then the round プロフィール button (`p04-longpress`, `p05-portrait`, `p06-profile`). Found: the labels "Japanese VA:", "Birthplace:" and "Birthday:" (official) are overdrawn by their values (the value labels sit where they did for the short CV： / 出身： / 生年月日：); the description (`cp0010_b01a_prmsg_06`, a machine row broken at the Japanese row's width, 15 lines) runs past its box onto the Close button; the round buttons ボイス再生 / プロフィール and the detail's round buttons are Japanese art. Fixed after: the description is fitted to the box of the layout's placeholder (552 units x 12 lines, paragraphs kept, shrunk; client-changes "The character profile's description"; `manual2/q06-profile.png`: Tika's 15 lines now 12 above the caption); "Birthplace:" and "Birthday:" are shrunk into the room before their values by 7.15's rule ("Birthplace:" to about 50%). Still open: "Japanese VA:" is overdrawn by its value (`pop_0/pop/cv/title` and `cv/name`: the room before the value is under 40% of the label, so 7.15's rule leaves it; a fix would move the value, which the rules don't do). The birthplace "Myiddok, Faykreed IV" for 惑星ダフティーネ is Global's error spread by memory (7.17).
- **The back log** (`p21-log`, `p22-log-up`, the Prologue's first scene): each entry is as tall as its lines (1, 2 and 3 line entries shot, the speakers above them), at the data's breaks; nothing runs into the next entry, so a 5-line message takes five lines there (no 5-line message was shot). No change needed. The Scenario Library's tabs メインストーリー / サブストーリー are Japanese.

**The sweep's data rows (`data-rows.tsv`, 181 rows).** The rule (the user): fix machine rows whose text is wrong or garbled, as `agent` rows (7.9: ranked like machine, marked for review); never shorten for space (that is the client's shrink, 7.15); official rows are not overridden (7.17). By the served source today: 57 official, 99 machine, 3 agent (en-textclean's), 3 human, 2 memory, 2 without a row, 15 row families (`CLASS:`).

- **Fixed: 16 master rows as `agent` rows** (`english_text.py set --source agent --by en-followup`, each with a note saying what was wrong; the engine's wording kept wherever it was right):
  - lists and tables run into prose (the cells shifted): `uimsg_item_confirmation_1`, `_3`, `uimsg_Sellitem_Warning_2` (one item per line, as en-textclean did `_sell_1`), `uimsg_sphere211_return_dialog` (one rate per line, the ※ note apart);
  - a ※ note or a question run into the paragraph the Japanese sets apart with a blank line: `uimsg_please_birth_add_need3`, `uimsg_sphere211_next_floor_confirm`, `uimsg_gear_set_dialog1`, `uimsg_user_data_saving_end_dialog` (prose re-broken at the Japanese row's widest line, as `import-mt` does);
  - garbled: `uimsg_material_compose_confirm` / `_result` ("%s Compose %d? Items…": now "%s / ×%d will be composed."), `uimsg_pshop_pass_count` ("%dnd time": 1nd, 3nd; now "Time %d");
  - wrong name or term: `item_favor_up_21_text_message`, `cp0002_b01b_message` (リーシュ is Eve, not Leash), `uimsg_consumption_sphere_stamina` (消費Sスタミナ: "S Stamina Consumed", not Stamina);
  - "1 Draws", "1 Mastery Pass Medals" for the commonest count: `uimsg_gacha_confirm`, `uimsg_mastary_dialog9` ("Draw(s)", "Medal(s)").
- **Names in the story:** 33 machine story lines said "Lady Leash" and "Lady Carlin" (the M2 name pass) where the glossary has Eve (Global) and Karlyn: they are `agent` rows with the engine's text and the names mended, and the glossary rows レディ・リーシュ / レディ・カーリン now say Lady Eve / Lady Karlyn (the old names as variants).
- **No master row is Japanese any more.** The 37 master texts the 31B's answers had failed (`mt-rejected.tsv`; specifiers reordered, tags, kana left in, names left out, a runaway) were sent again with what was wrong (`english_mt_run.py ui-retry`, `work/english/followup/mt/ui-retry.jsonl`, 35 texts in 1.5 min): 36 pass as machine rows after four machine glossary rows were mended (エサ = Feed, was "Barnie Feed"; バーニィクッキー = Bunny Cookie, was "Barny Cookie" against Global's Bunny; the plurals Half-Elves and Scoutmen as variants), and `uimsg_buy_premium_explan2` is an `agent` row (the engine kept the Japanese list dots and ran the list together). Every master row with Japanese text now has English: 65,429 rows (agent 20, human 36, machine 37,376, memory 6,348, official 19,239, template 2,410).
- **Left as they are, and why:**
  - space only (a header description or label longer than its room, Japanese-width breaks, 691 item descriptions of 5+ lines, 1,505 factor rows of 3+ lines, the `name_ds_bonus_*` and `stepup_botton_message_*` families): the user's rule is to shrink, not shorten; the client fits them (E10, 7.15);
  - term splits that need a decision, not a fix: 進化 Augment (Global) vs Evolve (machine), 強化 Strengthen vs Enhance, アシスト Assistance vs Assists, 片手剣 OHS vs One-Handed (and two trait names), 転移 Teleport / Transfer / Warp, Scenery vs Scenic Photo; a glossary row each would settle them for a later MT pass;
  - faithful to the Japanese: `uimsg_extra_top_info` "(Temp)" (the Japanese has (仮)), the talent name ending in a period (`talentName_021_005_006_201/202`);
  - `uimsg_rentalbonus_num*` are human rows (the user's); the achievement reward line "200 gems" is not master text.

### 7.17 Global's official wording: problems for the user to decide

Official rows (Global's English, 7.9) are never overridden by us. These read wrong in the 3.7.0 client; each would need a `human` row (`english_text.py set ID TEXT --by NAME`) if the user decides to change it. Found in the sweep (7.12) and this pass; fit-only problems (too long for a box) are not listed: the client shrinks them.

| message_id | Japanese | Global's English | Problem | Suggested fix |
|---|---|---|---|---|
| `name_event_exp_blue` | 青の経験値素材ミッション | Blue EXP Misisons | typo | Blue EXP Missions |
| `error_message_text_10004` | スタミナが不足しています。 | Not enough SP. | the stat is "Stamina" on every other screen (SP is not a 3.7.0 term) | Not enough Stamina. |
| `uimsg_button_back` | 修正する | Delete | wrong meaning: the birth-date dialog's button goes back to correct the date, nothing is deleted | Edit (or Correct) |
| `uimsg_item_WarningConfirmation` | ベースアイテムを強化します。／素材にしたアイテムは失われます。／よろしいですか？ | Base item will be enhanced. All other items will be used as materials. Proceed? | the warning is missing: the Japanese says the material items will be lost | Base item will be enhanced.\n\nItems used as materials will be lost.\nProceed? |
| `uimsg_item_stren_name` | 強化合成 | Enhance Weapon | the title of every enhancement, accessories too (the Japanese is generic) | Enhance |
| `uimsg_deep_space_exploration_rate_up` | 上昇探査率 | Raise Exploration Rate | reads as an action; it labels the exploration rate a return gained | Exploration Rate Up |
| `uimsg_sort_order_desc` | 降順 | Des. | unclear abbreviation (the ascending one is "Asc.") | Desc. |
| `uimsg_miss_no_rental` | レンタルなし | No Loans | the loan list's button says "No Loan" (our English art, `mission_rental`) for the same choice | No Loan |
| `uimsg_chara_evolution_name` | 進化 | Augment | a term split: Global says Augment (101 rows), our machine rows say Evolve / Evolution for 進化 | keep Augment and align the machine rows (a glossary row and a re-check), or Evolve everywhere |
| `cp0014_b01a_prmsg_05` (and by text memory 24 more `cp00xx_*_prmsg_05` rows and `message_2nd_planet_01`) | 惑星ダフティーネ | Myiddok, Faykreed IV | wrong: Global's row gives Welch's birthplace for "Planet Daftine"; our text memory (7.9, exact Japanese) copies it to every profile of the Daftine characters (Tika's profile shows "Birthplace: Myiddok, Faykreed IV") and to the EP2 planet name | Planet Daftine (a `human` row for the 26 ids, or a rule that keeps this Global row out of the memory) |
| `uimsg_full_stamina`, `uimsg_deep_space_quick_return_confirm` | — | "…restored. \nIt cannot…", "…shuttle now. \nIs this OK?" | a space before the line break (invisible; harmless) | drop the space |

Not a problem: `message_ac_ind_05` "Campaign Draws" for ピックアップガチャ is Global's own term (39 of the 59 Global rows with ピックアップガチャ say Campaign).

### 7.18 The character bio pages; Global's credits and near matches

Agent `en-bio`, 2026-10-08 (the user: "check the rendering on the character bio pages, and that the text is from GL when necessary: especially Seaside Maria").

**How it was run.** A seed save with ten ★6 characters (`tools/make_test_seed.py --extra-roles` Seaside Maria `role_cp0303_b04a_6131` as the home character, Lenneth `cc0001`, Reimi of the Phoenix Bow `cp0402_b06a` (the longest machine profile), Jeanne `cp0023`, Welch `cp0014`, Maria `cp0303_b01a`, and the seed's own Rufus, Fina, Bride Rena, Evelysse), hand-driven clients (`soaslot.py run`, `soactl.py`) with `--lang en --english` and `--lang ja`: per character a long press on its face in Enhance Status (the detail), the illustration (the portrait: CV, illustrator, the round buttons), プロフィール (the profile: name, birthplace, birthday, age and its note, the description, the source game). Shots in `work/english/bio/` (local): `en-before-c1..10-{a-portrait,b-profile}` (before), `en4-after-c*` (after), `ja-before-c*` (Japanese), `en4-d-*` (Seaside Maria's detail, portrait and profile after).

**Seaside Maria (cp0303_b04a), fully checked.** Every text on her pages is Global's: the name 渚のマリア "Seaside Maria" (`_message`), the real name "Maria Traydor" (`prmsg_03`), the VA "Michiko Neya" (`prmsg_01`), birthplace "Earth" (`prmsg_05`), birthday "November 19th, 753 S.D." (`prmsg_08`), the description (`prmsg_06`, Global's three paragraphs), the source "Star Ocean: Till the End of Time" (`prmsg_07`), her two home lines (`hmmsg_01/02`); the illustrator (`prmsg_02`) is now Global's `太子\n\nTaishi` (was the machine's "Crown Prince"); the age 19 (`prmsg_04`) and `prmsg_09` (a U+3000) are language-neutral. Her assist-skill and chip rows (`assist_skill_role_cp0303_b04a_*`, `item_chip_cp0303_b04a_*`) are machine rows: Global has none.

**Rendering: found and fixed** (client-changes "The character profile's rows"; `en-before-*` vs `en4-after-*`):

| Before | After |
|---|---|
| "Japanese VA:" overdrawn by the VA's name (all ten) | the value moved after its caption: "Japanese VA: Michiko Neya" |
| "Birthplace:" at about 50%, "Birthday:" squeezed | full size, the values moved after them |
| Jeanne's birthday "Cosmic Calendar 513, December 1" wrapped onto the age row | one line, shrunk into the row |
| the illustrator credit (Global's three lines) over the VA row | one line: "太子  Taishi", "吉成鋼  Kou Yoshinari" |
| the round buttons ボイス再生 / プロフィール / ボイス変更 (portrait) and ステータス詳細 / タレント詳細 / バトルスキル詳細 / ユニバースタレント詳細 (detail) in Japanese | English art (section 8): Play Voice, Profile, Change Voice (no Global English: our wording), Stat Details, Talent Details, Battle Skill Details (Global's `uimsg_ch_dialog_status_title`, `uimsg_talent_detail`, `uimsg_ch_dialog_battleskill_title`), Universe Talent Details (the glossary) |

Fine as they were: the description fit (7.16; Global's paragraphs kept), the age note (Rena's "(Born approx. 700 million years ago)", `Text_6_3`), the source game (two right-aligned lines, as the Japanese). Not changed: a machine profile that ran the Japanese paragraphs together (Reimi's `cp0402_b06a_prmsg_06`, 645 characters in one paragraph) is fitted small (it fits the 12-line box at 75%); the source game sits over the dimmed illustrator row behind the profile window, as in Japanese.

**Global preferred: illustrator credits (official-credit, 7.9).** Global writes an illustrator as `<the Japanese name>\n\n<romanization>`; the old filter dropped every Global text with kana or kanji, so the 120 credit rows of 3.7.0's ids got machine English that translated names as words ("Crown Prince" for 太子, "Hagane Yoshinari" for 吉成鋼 Kou Yoshinari, "Enami Katsumi" for Global's "Katsumi Enami"). Now a Global text with Japanese is English when it is exactly that form: before its first line break Global's own Japanese (but for white space), after it text without kana. Rejected as before: 【未翻訳】 (14 login-bonus titles), 【N版】 / 【N翻訳待ち】 work markers, `Nルーム選択`, Global's 【メモ】 English-VA field (`prmsg_10`, not in 3.7.0). Served exactly as Global wrote it (the user's default; the font has the kanji), and through the memory to 59 more rows with the same Japanese name (`あきまん\n\nakiman`, `箕星太朗\n\nTaro Minoboshi`). Served `prmsg_02`: official 40 + credit 120, memory 65, machine 56 and agent 9 (names Global never had: Omutatsu, Nishikawa Eight …; the machine had translated four pen names as words, now `agent` rows marked for review: 蟻束 "Arizuka" (was "Ant Bundle"), 壱子みるく亭 "Ichiko Milktei" ("Ichiko Milk Tea Shop", 4 rows), DSマイル "DSmile" ("DS Miles", 2 rows), and two names put in Global's given-name-first order, はっとりみつる "Mitsuru Hattori", つくし　あきひと "Akihito Tsukushi"), 32 language-neutral (full-width Latin, e.g. ｍｏｔ, shown as written; Global's memory has "mot" for it, see below).

**Global preferred: rows whose Japanese 3.7.0 changed (Q7).** 747 JP rows have Global English for another (older) Japanese text of the same id. Classified (`work/english/bio/q7-classes.tsv`, local: class, id, served source, both Japanese texts, Global's English):

| Class | Rows | Served | Examples |
|---|---:|---|---|
| near: punctuation, width, white space or an abbreviation of the same term (official-near, 7.9) | 40 | Global's English (was machine) | クリダメ → クリティカルダメージ, クリティカル率 → クリティカル発生率, 使用で → 使用時に, 秒 → 秒間, を付与 → を付与する, 時 → の時に (`factor_message_*`, `seed_message_*`, assist skills) |
| numbers changed | 23 | machine | event missions' counts (`message_Event_ac_April_02_04`: 20 → 80 clears), `factor_message_fiore_403` (80% → 90%), daily challenge days; Global's English has Global's numbers and extra digits ("[Misery 1]", "M2"), so no template can rewrite it safely |
| a word or phrase changed (near but not near enough, similarity ≥ 0.8) | 155 | machine | 詠唱中は → 使用中に (24 factor / seed rows: "no flinching during symbol invocation" vs while using), 標的 / 敵 (skill descriptions), 新X交換所 (36 `item_coin_*`: Global's English describes another acquisition), 使用時 → 使用後 (when vs after), シーハーツ… 施術 → 施文 (`cn0008_b01a_prmsg_06`, the only profile: a one-character fix in 3.7.0) |
| different content (ids reused or rewritten) | 274 | machine | `message_me*` (57: event names of other events), box-gacha titles with the event's name, `seed_message_*` with other effects, tutorial pages, `Present_box_99` (Global's placeholder WWW…) |
| already Global's words by the memory / template, or a person's row | 255 | memory / template / human | |

Conservative on purpose: a row is "near" only by the listed equivalences and with the same numbers; when in doubt it stays machine and is listed. The 155 "word changed" rows are where a person could take Global's English (`english_text.py set ID TEXT --by NAME` makes a human row; e.g. the 24 詠唱中は / 使用中に rows and `cn0008_b01a_prmsg_06` read the same).

**Not done (found):** about 600 language-neutral rows (no kana or kanji, so 7.9 gives them nothing) have Global English for the identical text through the memory: 521 `seed_message_*` (`ＡＴＫ＋２０％` → "ATK +20%"), 27 credits (`ｍｏｔ` → "mot"), factor rows (`ＡＴＫ＋２０％　ＨＰ＋３０％` → "ATK +20% and HP +30%"). They are shown in full-width as in Japanese. Serving them would be a change of rule 4 (memory for neutral rows); left for the user.

**Bio and interaction lines by source after this change** (JP rows `*_prmsg_*` / `*_hmmsg_*`):

| | official | official-credit | memory | machine | neutral |
|---|---:|---:|---:|---:|---:|
| `prmsg` (profiles: VA, illustrator, real name, age, birthplace, description, source, birthday, note) | 953 | 120 | 577 | 598 (+ 9 agent) | 641 |
| `hmmsg` (home and talk lines) | 519 | 0 | 6 | 1,885 | 0 |

Per field: `prmsg_06` (descriptions) official 138, machine 180; `prmsg_02` (illustrators) above; `hmmsg_01/02` official 244 each, machine 356 each; the talk-mode lines (`hmmsg_09` and up) are almost all machine (Global had few). No machine `prmsg` / `hmmsg` row has Global English left but `cn0008_b01a_prmsg_06` (above): the rest are characters and lines Global never had.

**Checked:** `check_english_official.py` (T0, now with official-credit and official-near): master 28,216 ok, story 5,037 ok, 0 violations, for the Python build and `soa-server --english-dump`'s tables; `tests/test_english_derive.py` byte-identical.

## 8. English UI art

Implemented 2026-10-07 (agent `en-art`, PLAN-english.md step E9, decision Q4). The images whose Japanese text is part of the picture (section 1.3) get English copies served as `-en` members; the client with `--lang en` picks them up through `FileExistLanguage` (6.3) and keeps the Japanese image for every file without one.

**What is probed: the scene, not the atlas.** A UI atlas is not a file of its own: it is the `.aif` member of a Cocos scene `UI/etc2/<name>.csf` (an ISF image of `<name>.msgp`, the node tree; `<name>.aif`, one 2048×2048 ETC2 RGBA8 page; `<name>.csv`, the sprite table `name,x,y,w,h`). The client asks `FileExistLanguage` for the scene (`UI/etc2/home.csf -> UI/etc2/home-en.csf`, experiment 3's trace and this step's runs), so an English atlas is a whole `-en` scene: the same node tree and sprite table, the same member names inside (`home.msgp`, not `home-en.msgp`: a repack with the original names loads), only the atlas's pixels changed.

- **The ISF entry's fourth word** is the byte sum of the member's payload padded to 32 bytes with 0xee (every member of the 3.7.0 scenes and the font follows it; `aska::isf_payload_sum`). The generator recomputes it for the changed atlas.
- The `-en` scene is written with SLZ codec 5 (raw deflate, 64 KiB chunks, as 643 shipped files are) and ADLD XOR keyed by the `-en` name, like the stand-ins.

**Recipes in git, images built at run time.** The images are edits of the game's art, so git and the release packages hold only:

- `standin-assets-en/recipes/*.json`: one file per source; per label the sprites (names from the scene's `.csv`, or none for a plain `Image/` file), the text box and the area to clear (relative to the sprite), the Japanese it replaces, the English, and a style;
- the generator, C++ in the server library (`server/src/english_art/`, `soaserver/english_art.h`; the codecs in `common/` `soa/aska_image.h`, shared with `tools/aif2png`).

The server's `--english` CDN step calls `english_art::build({download, recipes, out, cache})`: for each recipe it reads the source from the user's download (a folder or the zip), decodes the atlas, clears each label's area, draws the English, re-encodes **only the 4×4 blocks whose pixels changed** (every other byte of the game's file stays as it was), and writes `<out>/<dir>/<stem>-en<ext>`. A stamp per output (the SHA-1 of the generator version, the recipe, the font file and the source file) skips unchanged ones; an output whose recipe is gone is deleted. Same inputs, same bytes: all arithmetic is integer (the ETC1/EAC encoder, the resampling, the fill), zlib's deflate at level 9.

**Drawing.**

- **The game's own font** (`Font/etc2/font.fpk` of the same download, 3.1): the glyph table and the 2048×2048 page's alpha. Text is laid out at the font's 24 px (proportional advances, `?` for a missing glyph, `\n` for a second line), made bolder by widening strokes, scaled to the style's size by area averaging, squeezed horizontally (down to 70% by default) and then shrunk to fit the box. No font file ships and no font dependency is added.
- **Effects:** an outline (a disc dilation), a glow (the outline spread and blurred), an optional shadow, then the fill; colours `#rrggbb[aa]` per style.
- **Clearing the Japanese:** `inpaint` (the default) solves the discrete Laplace equation over the area from the pixels around it inside the sprite (premultiplied colour, so transparent surroundings stay transparent); `fill` paints a colour; `none` keeps the picture.
- **Encoding:** the ETC1 individual and differential modes with both flips, a base colour search of ±1 step around each half's average and every table; EAC alpha by a search over every table and multiplier near the base that centres the table on the block's range. A constant alpha is exact.

**The recipes so far** (English from Global where Global had the screen, `data/basmaster-gl.sqlite3` `uimsg_*`):

| Source | Labels | English |
|---|---|---|
| `UI/etc2/common.csf` | the footer, each in its on / off / dimmed state; the gold and red badges | Home, Characters, Draws, Items, Missions, Shop, Other (`uimsg_*_top_name`; Missions as Global's mission texts); Campaign, 1 Free a Day!, 1 a Day, Great Success UP!, Ship Returned!, Raid! |
| `UI/etc2/home.csf` | the four main buttons, the starter-mission button, the side buttons, the partner menu's round buttons, the talk-mode logo and level words, "back to favorite", the badges | Events, Missions, Sphere 211, Deep Space, Starter Missions; Achievements, Save Data, Follow, Featured, Notice, Gifts, Titles; 2D/3D, Deco, Home, Gift, Change Favorite, Studio Mode; Talk Mode; Normal, Curious, Friend, Like, Love; Back to Favorite; Ship Returned!, Affection Rate UP, Half Stamina Cost!, New Chapter, Raid Boss!, Ranking On! |
| `UI/etc2/gacha_top.csf` | the four tabs, Back, the two legal-notice buttons | Recommended / Character / Weapon / Event Draws (`uimsg_gacha_title_*`), Back (`sys_return`), Commercial Transactions Act, Payment Services Act (no Global English) |
| `TalkScene/etc2/EventBase.csf` | the story and talk window's buttons, each state | Auto, Skip (glossary), Fast Fwd, Log, Close Log |
| `UI/etc2/mission_menu_common.csf` | the mission menus' buttons and badges | Planet Selection (Global's 艦に戻る), Back, Select Planet, Scenario Library, Episodes, Event Menu, Ranking, Fusion, Records; Join All-Event / This Event's Multiplayer; badges |
| `UI/etc2/mission_top.csf` | the planet select | Sortie (the subtitle -Start- is the game's), -Download-, Join All-Planet Multiplayer |
| `UI/etc2/mission_select.csf` | the mission list | Multiplayer (Global's マルチプレイ開始), Select Part, Join This Planet's Multiplayer, badges |
| `UI/etc2/mission_confirmation.csf`, `result.csf` | the mission detail's and the result's badges | Initial Clear (Global's 初回クリア報酬), Bonus!, Owned Char., Defeated, Extra Bonus, Time Bonus, EX Bonus, Affection Bonus, Host Bonus, Beginner, Char. Pass, Surprise |
| `UI/etc2/mission_rental.csf`, `party_select_single2.csf` | the loan list's and the party's buttons | No Loan, Confirm (Global's 決定) |
| `UI/etc2/gacha_select.csf`, `gacha_main.csf` | the draw buttons' captions, Box Details, Pass History, the frames' notes; Back and the legal notices | Single Draw, 2- to 10-chain Draw (Global's 10連ガチャ: 10-chain), … |
| `UI/etc2/common_resource.csf` | shared badges and small buttons | To Shop, Update, Block, Mutual, Follow, Follower, Story Only, Done!, Cap Inc., Rank, Rewards |
| `UI/etc2/eventmission_top.csf`, `honor_change.csf`, `achievement_list.csf` | the event list's tabs, the titles' and achievements' tabs, the equipped badge, the round Gifts button | Events, Materials; Battles, Story (glossary), Training, Other; Event, Daily, Weekly; Equipped; Gifts |
| `UI/etc2/ds_common.csf`, `sphere211_missionboard.csf` | Deep Space's and Sphere 211's buttons and tags | Remove (Global's 外す), Confirm, Check Ships, Switch View, Ships; Return, Floor Info, Ranking, Bonus Floor, Challenge Floor, Goal |
| `Image/etc2/banner_roleevoAtk_001`, `banner_roleexAtk_001`, `banner_seed_001`, `banner_ticket_event_002` | the permanent events' banners (event list) | Attacker / Augment Mission, EXP Material Mission, Status Material Mission / Seed Mission (glossary), with Mission Tickets / Unlock Event Missions |
| `Image/etc2/banner_gacha_*` and 4 more (`banner_gacha_tag.json`, `"sources"`) | the 「ガチャ」 tag of the 8 gacha banners that share it | Draws |
| **Live banners** (2026-10-07, the user: the banners open at the server's clock first): every `master_banner` row open in the served master at the session's date (46 images; 5 more are dated banners the download lacks) | the 12 role material events, the weapon and character gachas, the ticket gachas, Sphere 211's, the shop, ingot and box gachas, the event schedule | Augment / EXP Material Mission + the role (Global's role names), Melee / Ranged / Crest Weapon Limited Draws with the weapon names (glossary), "10-chain: 1 ★4+ guaranteed!!", Make-up ★4-5 … Draw Ticket, Ingot Mission (glossary), Box Draws, Apology Character Draws … |
| **Live gacha panels**: the pick-up images (1024×512) of every gacha open at the session's date (49 images) | the character pick-ups (tag, role, name; the skill blurb stays Japanese), the factor and pick-up weapons (names: Global's where it had them), the limited weapon gachas, the ticket gachas, the standard, apology, lucky-bag and Galaxy panels | From SO4!!, the role and name (glossary / Global's), Blade of Ruin …, Melee Weapon Limited Draws, ★N Limited Character / Weapon Ticket, Apology Character Draws with its notes … |
| 48 more scenes (`tutorial_base`, `topmenu_2`, `contact_list`, …) | the same sprites in their own atlases | copied by `tools/english_art/share_labels.py` |

**Shared sprites.** Every scene carries its own copy of the shared sprites (the Back button, the footer, the badges): 853 UI and TalkScene scenes in the download. `tools/english_art/share_labels.py` copies each label to every scene whose atlas has a sprite of the same name, size and nearly the same pixels (mean difference ≤ 4), marked `"_from": "<scene>"`; a scene's own labels win, and the copies are recomputed on each run. So 61 scene recipes cover 61 scenes from about 200 written labels. The full build takes about 4 s (one thread per recipe, up to 8; the bytes don't depend on the order).

Not done yet: the remaining scenes (the item, character and other menus are mostly labels from the master, which the machine translation fills; their sprites with text were not all found yet), and the `Image/` files (banners, tutorial pages: about 1,000 with text). A plain `Image/` file works the same way (a label without `sprites` is placed on the whole image) when it is ETC2 (RGBA8, RGB8, or the 199 punch-through RGB8A1 images, format 48: differential mode only, alpha < 128 transparent); the 431 JPEG images are not written (none of the live banners and panels is JPEG; the visible JPEG ones are backgrounds without text, so no JPEG library was added).

**Same bytes everywhere.** Two builds give identical files (the selftest), and the Windows build of `english-art` (MinGW) wrote the same bytes as the Linux one for all three scenes.

**Writing a recipe.** `build/tools/english_art/english-art --out DIR --png PNGDIR` (run from the checkout: the download `work/SOA-3.7.0-canonical-data.zip` and `standin-assets-en/recipes` by default) builds every recipe without a server and writes each edited atlas as PNG for review; `build/tools/aif2png/aif2png` renders a source scene's atlas, and its `.csv` gives the sprite rectangles. Unknown keys in a recipe are errors. A recipe's format:

```json
{"source": "UI/etc2/common.csf",
 "styles": {"footer": {"size": 18, "bold": 1, "fill": "#e4ffff", "glow": "#00b4ffd0", "glow_radius": 2,
                       "outline": "#0a4c8cc0", "outline_width": 1}},
 "labels": [{"jp": "ホーム", "text": "Home", "sprites": ["menubtn_home_on.png", "menubtn_home_off.png"],
             "box": [4, 77, 103, 23], "cover": [3, 76, 105, 25], "style": "footer"}]}
```

Busy banners get a **title band** instead of an exact repaint: the area is inpainted, then darkened (`"clear": "shade"`: the style's `clear_color` laid over the picture, its edges faded, the picture's own alpha kept, so a band never spills over a banner's transparent margin), then the English drawn on it. After the live banners, older ones follow by date, newest first (`tools/english_art/specs/dated_*.py`, `dated_2020_panels.py`): **every dated 2020 image of the download (298: banners and pick-up panels) has a recipe**. Still Japanese (2026-10-07): 40 dated 2016–2019 images, 63 `banner_*` and 33 `pickup_img_*` without a recipe (not all carry text), the 118 `tips_th_*` and 75 `tuto_pic*` pages; on the panels, the characters' quotes, the CV / illustrator credits and the small print stay Japanese (no English source for the quotes). The banner recipes are written by small scripts per layout family (`tools/english_art/specs/*.py`, plain python3), so a box is written once for all banners of a family.

A recipe has `"source"` (one file) or `"sources"` (several files that take the same labels, e.g. banners sharing a tag: one `-en` file each). Style keys: `size`, `bold`, `tracking`, `leading`, `squeeze` (percent), `fill`, `outline`, `outline_width`, `glow`, `glow_radius`, `shadow`, `shadow_dx`, `shadow_dy`, `clear` (`inpaint`, `fill`, `shade`, `none`), `clear_color`, `align` (`left`, `center`, `right`), `dx`, `dy`. A label takes its named style, then any style key of its own; `note` and keys starting with `_` are comments.

How measured: the scenes' members and sums from the decoded 3.7.0 files; the `home` session with `--lang en` (a scratch `CLanguage` switch until B1 landed) and the generated files in a `--standin-assets` directory: the `-en` scenes were fetched and drawn (`work/english/exec/art/`).

### 7.9 The derivation (spec)

How `tools/english_text.py` derives the English it does not commit (official, memory and template rows), and how it merges them with our committed rows. The server's C++ `-en` builder must reproduce `tools/english_text.py derive` **byte for byte**. The reference implementation is `tools/english_core.py` and `tools/english_text.py` (`Derived`, `finish`, `build`, `StoryDerived`, `story_finish`, `build_story`); where this text and the code disagree, the code is right and this text is a bug.

**Notation.** Regular expressions are Python `re` on `str`: `\d` and `\s` are **Unicode** classes (`\s` includes U+3000 and U+00A0), `\b` is a Unicode word boundary, and strings compare by code point (the same as UTF-8 byte order). "Master encoding" is a text with the two characters `\n` for a line break; `unesc` turns them into U+000A and `esc` back. Nothing else is escaped.

**Inputs.**
- JP: `select message_id, text_value from master_text` of `data/basmaster-3.7.0.sqlite3` (a NULL text is `""`). Every row is a candidate, `ja_sha1` = hex SHA-1 of its UTF-8 `text_value`.
- Global: `data/basmaster-gl.sqlite3`, `master_text` rows with `lang='en'` (`GL_EN[mid]`) and `lang='ja'` (`GL_JA[mid]`), by message_id. Memory iterates every `GL_JA` row.
- The font: the advances of `Font/etc2/font.fpk` (3.1): `adv[id & 0xFFFF] = xadvance`, records in file order (a later record with the same low 16 bits wins).
- Story: every row of every `Scenario/TS_*.msgp` of the download, files in name order, rows in file order; `text_value` has real newlines.

**Patterns.**

| Name | Pattern |
|---|---|
| `KANA` | `[぀-ヿ一-鿿]` (`has_kana`: a match anywhere) |
| `SPEC` | `%(?:\d+\$)?[-+#0]*\d*(?:\.\d+)?(?:ll\|l\|h)?[dusfxXc]` |
| `SPEC_STRICT` | `%[-+#0]*\d*(?:\.\d+)?(?:ll\|l\|h)?[dusfxXc]` |
| `GL_TOKEN` | `<NUM\|<STR\|<INSERT\|</INSERT\|<EMDASH>\|\[(?:G\|R\|Y\|B\|Blue\|Red\|Green\|Yellow\|White\|-)\]` |
| `GL_MARKUP` | `<NUM\|<STR\|<INSERT\|</INSERT\|<EMDASH>` |
| `TAG` | `<[^<>\n]{1,40}>` |
| `NUM` | `\d+(?:\.\d+)?` |
| `TEMPLATE_UNSAFE` | `January\|February\|March\|April\|May\|June\|July\|August\|September\|October\|November\|December\|\}(?:st\|nd\|rd\|th)\b` |
| `INSERT` | `<INSERT \d+>([^<>/]*)/([^<>]*)</INSERT>` |
| `NUMSTR` | `<(NUM\|STR) (\d+)>` |
| `STORY_TAG` (full match) | `<player>\|<font ?color=[^<>]*>\|<fontsize=[^<>]*>\|</font>` |

**1. Global's usable English** `gl_english(mid)`: `en = GL_EN[mid]`, `ja = GL_JA[mid]`; none when `en` is missing or empty, `has_kana(en)` and not `credit_form(en, ja)` (below), `en == ja`, `GL_TOKEN` matches `en`, or `SPEC_STRICT.findall(en) != SPEC_STRICT.findall(ja or "")` (ordered lists of the matched strings).

**Credits** (`credit_form(en, ja)`, rule **official-credit**, agent `en-bio` 2026-10-08): Global's illustrator credits keep the name as written and add its romanization, `太子\n\nTaishi`. `u = unesc(en)`, `i` its first `\n`: true when there is one, `ws_key(u[:i]) == ws_key(ja)` and non-empty, `ws_key(u[i:])` non-empty and `!has_kana(u[i:])`. 120 `*_prmsg_02` rows by id (`matched.tsv` rule official-credit) and, through the memory, 59 more rows with the same Japanese name; Global's marker rows (【未翻訳】…, 【N版】…, `Nルーム選択`, the `prmsg_10` 【メモ】 rows) stay out. Served exactly as Global wrote it (the font has the kanji); the profile shows it on one line (7.18).

**2. Official by id** (master): `gl_english(mid)` when `same_ja(GL_JA[mid], ja)` (both master encoding):
- `"id"`: `GL_JA[mid] == ja` exactly;
- `"id-ws"`: else, when `ws_key(ja)` is non-empty and `ws_key(GL_JA[mid]) == ws_key(ja)`. `ws_key(t)` = `unesc(t)` with every U+0009, U+000A, U+0020, U+00A0 and U+3000 removed (an explicit set, not `\s`). Global's `ja` often doubles a line break (`…\n\n…`) or lacks a trailing U+3000, so the same text missed its English (2026-10-07, agent `en-textclean-gl`: 57 rows, all `uimsg_*` dialogs but one, and 5 E3 rows). The served source stays `official`; `report` lists the rows with their rule in `matched.tsv`.
- A NULL `GL_JA[mid]` never matches.

**3. E3** (only when 2 gives nothing): `gl_token_english(mid)`: `en` present, `!has_kana(en)`, `en != GL_JA[mid]`, `GL_MARKUP` matches `en`, and `GL_TOKEN` does **not** match `GL_MARKUP.sub("", en.replace("</INSERT>", ""))` (only the matched prefixes are removed, e.g. `<NUM` of `<NUM 1>`); and `same_ja(GL_JA[mid], ja)` (2). Then `rewrite_tokens(en, ja)`:
1. every `<EMDASH>` → U+2015;
2. `INSERT` → its group 2 (the plural form);
3. `toks` = the integers of `NUMSTR` in order, `specs = SPEC_STRICT.findall(ja)`. If `toks` is non-empty: no `specs` → no candidate (reason "composition"); `sorted(toks) != [1..len(specs)]` → none; `toks` not ascending → none (reorder); else every `NUMSTR` match → `specs[n-1]`;
4. any `GL_MARKUP` left → none;
5. `fix_percent(en, ja)` (below);
6. `SPEC_STRICT.findall(en) != specs` → none.

A row with a reason is listed (`token-gaps.tsv`); it may still get memory (4).

**4. Memory** (only when 2 and 3 give nothing and `has_kana(ja)`; a row without kana is "neutral" and gets nothing more). Built once over every Global pair (`mid` of `GL_JA` with a non-empty `GL_JA[mid]` and `en = gl_english(mid)` not none):
- **Exact:** `exact[GL_JA[mid]][en] += 1`; and, when `k = ws_key(GL_JA[mid])` is non-empty, `exact_ws[k][en] += 1`.
- **Template:** `n = NFKC(GL_JA[mid])`, `nums = NUM.findall(n)`, `key = NUM.sub("\x00", n)`. Skip when `nums` is empty or has a repeated value, or when `sorted(NUM.findall(en)) != sorted(nums)` (string sort; `en` is not normalised). `t = NUM.sub(m → "{i}" where nums[i] == m, en)`; skip when `NUM` still matches `t` with every `\{\d+\}` removed, or `TEMPLATE_UNSAFE` matches `t`. Then `template[key][t] += 1`.
- **Choice:** per key, the English with the highest count, ties to the smallest string.
- **Lookup:** `exact[ja]` if present (kind `memory`). Else `exact_ws[ws_key(ja)]` if present (rule memory-ws, kind `memory`: the same text but for white space, 83 rows, e.g. `ピックアップ武器ガチャ　` with a trailing U+3000; listed in `matched.tsv`). Else `key, nums` of `NFKC(ja)` as above; if `nums` is non-empty and `template[key]` exists: replace each `{i}` with `nums[i]` (the NFKC digits), then `re.sub(r"\b1 (time|hit|day|turn|battle|mission)s\b", r"1 \1", flags=IGNORECASE)` (kind `template`).

**4b. Near** (rule **official-near**, only when 2, 3 and 4 give nothing and `has_kana(ja)`; agent `en-bio` 2026-10-08): `gl_english(mid)` when `GL_JA[mid]` is not NULL, `near_key(GL_JA[mid]) == near_key(ja)` and non-empty, and `set(NUM.findall(en)) == set(NUM.findall(NFKC(unesc(ja))))`. `near_key(t)`: `NFKC(unesc(t))` without the code points with `isspace()` and those of `、。,.・!?「」『』…`, then `str.replace` in this order: クリティカルダメージ → クリダメ, クリティカル発生率 → クリティカル率, ダメージ → ダメ, 秒間 → 秒, 付与する → 付与, の時に → 時, 時に → 時, 使用で → 使用時, ごとに → 毎, 毎に → 毎. Source `official` (40 rows, `matched.tsv` rule official-near; the classification of the rest in 7.18).

**5. Finishing a master candidate** (`finish`; derived sources official, memory, template):
1. `e = unesc(en)`; (our human rows: NFC first);
2. **fold**: per code point `c`: the table `— → ―` (U+2014 → U+2015), `– → -`, `‘ ’ → '`, `“ ” → "`, `• · → ・`, `™ ® → ""`, `€ → EUR`, U+00A0 → space; then, if the result is one code point, not `\n`/`\t` and not in `adv`: NFKD it and keep the code points that are in `adv`, or `?` if none;
3. `fix_percent`: only when `SPEC` matches `ja`: `re.sub(r"%%|(" + SPEC + r")|%", m → m if m == "%%" or a specifier else "%%", e)`;
4. **re-break** (derived sources only) when `unesc(ja)` contains a line break and `e` none: `e = rebreak(e, max(widest(unesc(ja)), 200))`;
5. the checks (6) against `jn = unesc(ja)` with tag mode `subset`, no glossary;
6. the result is `esc(e)`.

- **`width(line, tag_px)`**: the sum of `tag_px[tag]` over the `TAG` matches (story: `{"<player>": 120}`, master: none), plus, with every `TAG` match removed, `adv.get(cp, adv[0x3F])` per code point. `widest(text)` = the maximum over the `\n`-separated lines (0 for none).
- **`rebreak(text, budget, tag_px)`**:
  1. `text = re.sub(r"\s*\n\s*", " ", text)`;
  2. in each `TAG` match every space becomes U+0001;
  3. `words = text.split(" ")` (empty words kept);
  4. greedy: `cand = w` if `cur` is empty, else `cur + " " + w`; if `cur` is non-empty and `width(cand) > budget` (U+0001 counts as a normal code point; a tag's `tag_px` key has its spaces restored), emit `cur` and start `cur = w`, else `cur = cand`; at the end emit `cur` if non-empty;
  5. join with `\n`, U+0001 back to space.

**6. Checks** (a candidate passes when none fires; `jn` and `e` with real newlines). Each one, and whether it is hard for each source:

| Check | Fires when | Hard for |
|---|---|---|
| specifiers | `SPEC.findall(jn) != SPEC.findall(e)` (ordered), or they are equal and non-empty and `e` with every `SPEC` match and `%%` removed still contains `%` | all |
| positional | `%\d+\$` in `e` | all |
| tags | `sorted(TAG.findall(jn)) != sorted(TAG.findall(e))`; in mode `subset` it passes when `set(tags of e) ⊆ set(tags of jn)` and the number of tags starting with `<font` equals the number of `</font>` | all (subset for official, memory, template, human, reviewed; strict for machine) |
| kana | `has_kana(e)`, except a derived master candidate (official, memory, template) in the credit form `credit_form(e, jn)` | all |
| glyphs | any code point other than `\n`/`\t` not in `adv` | all |
| global_token | `GL_MARKUP` matches `e` | all |
| glossary | a glossary term of `jn` whose English is not used (`glossary_misses`) | machine, human, reviewed only (pre-checked: the committed rows already passed) |

Width is never a check for the master (reported only).

**7. The master merge**, per JP message_id. `ours` is `data/english/master-en.tsv`, rows already finished and checked; use a row only when its `ja_sha1` equals the JP row's. The first of these is served:
1. our `human` or `reviewed` row;
2. the derived candidate (official or E3; else memory or template; else official-near) when it passes;
3. our `machine` or `agent` row (`agent`: a row an AI agent wrote by hand, `english_text.py set --source agent`, its editor naming the agent and "needs a person's review"; ranked and checked exactly like `machine`, so it never replaces official, memory or template English; `review` turns it into `reviewed`).

So Global's English (official, E3, and the memory built from it) always wins over a machine row, and only a `human` or `reviewed` row may replace it; the server's `merge_master` / `merge_story` apply the same order. **Checked in T0** (`english-official`, `tools/check_english_official.py`, 2026-10-07): for every served master row and story line it derives Global's text independently of the merge (by id, id-ws, official-credit, E3, memory, memory-ws, template, official-near; story: by id, E3) and compares the served text modulo folding, `%%`, a story line's strip and white space / line breaks (a re-break is allowed, a reword is not). It fails on any machine row or Japanese served where Global's text passes its checks, and on a derived source whose text is not Global's; human rows (5, the composed fragments) and Global texts that fail a check (0) are counted. `--tables DIR` checks a written table instead, e.g. `soa-server --english-dump`'s. On the data of 2026-10-07: master 27,997 rows ok (id 19,144, id-ws 57, E3 38, memory 6,265, memory-ws 83, template 2,410), story 5,037 ok, 0 violations; the tables before id-ws / memory-ws had 145. On the data of 2026-10-08 (official-credit and official-near): master 28,216 ok (id 19,264, id-ws 57, E3 38, memory 6,324, memory-ws 83, template 2,410, near 40), story 5,037 ok, 0 violations, the same for `soa-server --english-dump`'s tables.

Rows of `ours` with an empty `ja_sha1` (new message_ids, the client strings) are served as they are. Output: one row per served message_id, sorted by message_id (code points), `message_id \t ja_sha1 \t en \t source` with the header `message_id\tja_sha1\ten\tsource`, `\n` line ends, a final `\n`; `en` in master encoding; no tab, CR or real newline in a field.

**8. The story.** Per line (`mid`, `ja` with real newlines, `ja_sha1` = SHA-1 of that text):
- **Official**: `gl_english(mid)` when `unesc(GL_JA[mid]) == ja` (exactly: id-ws would add no story line). Else **E3**: `gl_token_english(mid)` when `unesc(GL_JA[mid]) == ja`, through `rewrite_tokens(en, esc(ja))`. No memory or template for the story.
- **Finishing** (`story_finish`): `e = unesc(en)` (NFC for our human, reviewed and machine rows), fold, `str.strip()` (every code point with `isspace()` at both ends), `story_break(e)` (no `fix_percent`): for n = 1, 2, … (up to 24) `r = rebreak(e, b(n), {"<player>": 120})` with `b(n) = 480` for n ≤ 4 and `480 * (40 n - 10) // 150` (128 n − 32) above, the first `r` with at most n lines (else the last one; E13, 7.13); checks of 6 against `ja` with tag mode **strict** and no glossary for derived lines; then every `TAG` of `e` must fully match `STORY_TAG` (else `story_tag`, hard). For a source other than `machine`, a `tags` problem is dropped when there is no `story_tag` problem and the count of tags starting with `<font` equals the count of `</font>`. The result is `esc(e)`.
- **Merge**: as 7 with the committed `story-en/TS_xxxx.tsv` (our human/reviewed > official/E3 > our machine/agent).
- **Output**: per Scenario file with at least one served line, `story-en-full/<file>.tsv` in the format of 7, rows sorted by message_id.
- **Completeness** (`index.tsv`: `file, lines, need, english, complete`): `lines` = rows of the file, `need` = rows with `has_kana(ja)`, `english` = those of them served, `complete` = `yes` when `english == need`. A language-neutral line may be served (Global's English for `……`) without counting.

How measured: `derive` with the old story budget (407 px) reproduced the previously committed full tables byte for byte (a one-off comparison on 2026-10-07); `tests/test_english_text.py` checks that our committed rows are the full table's where they win.

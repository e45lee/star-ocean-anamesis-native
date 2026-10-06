# English text in the 3.7.0 client: where the text comes from, what English exists, how to deliver it

The experiment files (screenshots, the English-merged masters, font and string dumps) are in `work/english/` of the main checkout: local only, not committed (derived game data).

Investigation of 2026-10-06 (agent `english`), at the user's request: **how can translated English text get into the 3.7.0 client?** Nothing was changed in code or data; the plan built on these findings is [PLAN-english.md](PLAN-english.md). The official English is the Global master, described in [basmaster-gl.md](basmaster-gl.md); the Global voice files are in [global-voice-files.md](global-voice-files.md).

Ghidra addresses are ELF vaddr + 0x100000, as `tools/decomp_at.sh` takes them. Counts come from read-only queries over `data/basmaster-3.7.0.sqlite3`, `data/basmaster-gl.sqlite3`, `work/download-3.7.0`, the 3.7.0 APK and `work/libSOA-3.7.0.so`. Each section ends with "How measured". Scratch files (scripts, renders, screenshots) are outside the repo in `/home/fish/.claude/jobs/ac4802d9/tmp/english-*` and are not committed.

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
  - Every Scenario, Script, UI, Image and TalkScene member is ADLD XOR, encType 1. `adld::encrypt(name, plain, adld::kXor)` (`server/include/soaserver/adld.h`, test `cdn/adld-roundtrip`) and `soa_save.script.encrypt` produce it.
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

- **Line budgets.** The trial used the Japanese row's own widest line for multi-line master rows, and for the story the p99 widest JP story line, 407 px (max 483). JP story lines have 1–4 lines (5+ in 266 of 21,663). Global's official story English (EP1, `TS_3xxx`, `TS_5xxx`) re-broken at 407 px needs 5 or more lines in 675 of 4,893 lines (at 483 px: 281). So about one story line in ten needs a shorter wording or a smaller font: `<fontsize=…>` is a story tag the client already reads (3.3), an untested data-only option; the per-screen box widths still have to be measured (E7).
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
  - The story's Japanese is **not** in git (only in `work/download-3.7.0`). The story tables therefore hold `message_id`, a hash and our English, and no Japanese; tools read the Japanese from the download when they need it.
  - Our English is still a translation of the publisher's text: whether it goes into git, and whether release packages carry it (they never carry game files), is the user's call (PLAN-english.md M-Q5). The glossary of names is small and needed in any case.
  - Engine outputs before review (`raw-*.jsonl`), PO exports and the trial stay in `work/`.

**As built** (2026-10-06, agent `en-data`; PLAN-english.md E1, M1, E3). The tool is `tools/english_text.py`. Its shared library, also used by `tools/english_mt.py`, is `tools/english_core.py`. The test is `tests/test_english_text.py` (T0).

- **Files** in `data/english/`:
  - `master.tsv`: only `machine`, `human` and `reviewed` rows (columns as above).
  - `glossary.tsv`: Global's terms (`official`) are regenerated by every `build`; `human` and `machine` rows (M2's names: kind `name`) are kept. Per term a `human` row wins over `official`, which wins over `machine`; an empty `en` removes the term.
  - `client-strings.tsv`: `message_id, en, note`; the client's `port_en_*` strings, merged as `human` rows with an empty `ja_sha1`.
  - `master-en.tsv`: **generated** by `build`: `message_id, ja_sha1, en, source`, every row that ends up English, sorted. The server serves exactly this file. `build --check` (and the T0 pytest) fails when it, or the glossary's official rows, is stale.
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
  - `data/english/story-en/TS_xxxx.tsv`: **generated**, `message_id, ja_sha1, en, source`, for every file with any English.
  - `data/english/story-en/index.tsv`: **generated**, `file, lines, need, english, complete`.
    - `need` counts the lines with kana or kanji; language-neutral lines (`……`) need no row.
    - The server serves `TS_x-en.msgp` only when `complete` is `yes` (Q12).
- **The hash.** A story line's `ja_sha1` is the SHA-1 of the Scenario row's `text_value` exactly as the file holds it: UTF-8, with **real newlines**. This is unlike the master's two-character `\n`. `en` uses the two-character `\n`.
- **Where the Japanese comes from.** It is read from `work/download-3.7.0/Scenario` at build time. Without it, `build` and `build --check` skip the story part and say so, and the story pytests skip.
- **Candidates:** `human`/`reviewed` > official (Global by id, plus E3) > `machine`.
- **Checks:**
  - No Global token, every glyph in the font (after folding), no kana left.
  - Every tag must be one `ParseMessage` reads (`<player>`, `<font color=…>`, `<fontcolor=…>`, `<fontsize=…>`, `</font>`).
  - Tags must equal the Japanese line's exactly for `machine` rows.
  - Official and human lines may colour other words, or name `<player>` where the Japanese says 艦長, as long as `<font>` stays balanced. Without this, 16 EP1/`TS_5xxx` lines that no MT run translates would block their files.
- **Line breaking (E7, data side).** Every served line is re-broken at spaces to a message window of 407 px: the p99 widest JP story line, 7.5. `<player>` is counted as 120 px (an assumption: about 8 Latin letters).
  - 690 served official lines need 5 or more lines; `report` lists them in `story-long.tsv`.
  - Shorter wordings or `<fontsize=…>` are still open (E7).
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

Not done yet: the other scenes, and the `Image/` files (banners, tutorial pages: about 1,000 with text). A plain `Image/` file works the same way (a label without `sprites` is placed on the whole image) when it is ETC2; the 431 JPEG images would need a JPEG encoder.

**Same bytes everywhere.** Two builds give identical files (the selftest), and the Windows build of `english-art` (MinGW) wrote the same bytes as the Linux one for all three scenes.

**Writing a recipe.** `build/tools/english_art/english-art --out DIR --png PNGDIR` (run from the checkout: the download `work/download-3.7.0` and `standin-assets-en/recipes` by default) builds every recipe without a server and writes each edited atlas as PNG for review; `build/tools/aif2png/aif2png` renders a source scene's atlas, and its `.csv` gives the sprite rectangles. Unknown keys in a recipe are errors. A recipe's format:

```json
{"source": "UI/etc2/common.csf",
 "styles": {"footer": {"size": 18, "bold": 1, "fill": "#e4ffff", "glow": "#00b4ffd0", "glow_radius": 2,
                       "outline": "#0a4c8cc0", "outline_width": 1}},
 "labels": [{"jp": "ホーム", "text": "Home", "sprites": ["menubtn_home_on.png", "menubtn_home_off.png"],
             "box": [4, 77, 103, 23], "cover": [3, 76, 105, 25], "style": "footer"}]}
```

Style keys: `size`, `bold`, `tracking`, `leading`, `squeeze` (percent), `fill`, `outline`, `outline_width`, `glow`, `glow_radius`, `shadow`, `shadow_dx`, `shadow_dy`, `clear` (`inpaint`, `fill`, `none`), `clear_color`, `align` (`left`, `center`, `right`), `dx`, `dy`. A label takes its named style, then any style key of its own; `note` and keys starting with `_` are comments.

How measured: the scenes' members and sums from the decoded 3.7.0 files; the `home` session with `--lang en` (a scratch `CLanguage` switch until B1 landed) and the generated files in a `--standin-assets` directory: the `-en` scenes were fetched and drawn (`work/english/exec/art/`).

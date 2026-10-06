# English text in the 3.7.0 client: where the text comes from, what English exists, how to deliver it

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

How measured: the decoded node trees (`TextObjectData` `LabelText` / `ButtonText`); file-name categories, with samples rendered by `build/tools/aif2png` (sheets in `/home/fish/.claude/jobs/ac4802d9/tmp/english-assets/sheet_*.png`).

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

How measured: `/home/fish/.claude/jobs/ac4802d9/tmp/english-exp/merge.py`, which builds the experiment's master (filters below), plus the bucket query in the same directory's notes. The text memory maps each Global `ja` to its safe English and looks up every JP row the id merge didn't fill.

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

Shots are in `/home/fish/.claude/jobs/ac4802d9/tmp/english-exp/home-out/shots/`:

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

**Experiment 2: a long line.** Experiment 1's master, plus `uimsg_full_stamina` set to a 170-character English sentence without `\n`. In `/home/fish/.claude/jobs/ac4802d9/tmp/english-exp/wrap-out/shots/29-stamina.png` the sentence is **one line, centred, cut off at both window edges**. That confirms the decompile: no automatic wrap, and no shrink in this dialog.

The scripts and masters are in `/home/fish/.claude/jobs/ac4802d9/tmp/english-exp/`: `merge.py`, `basmaster-en.sqlite3`, `basmaster-wrap.sqlite3`, and the `soa-en` / `soa-wrap` wrappers.

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
- **Proof:** `/home/fish/.claude/jobs/ac4802d9/tmp/english-font/sample_gl_story.png` renders a Global English story line in the game font, with é ï – — drawn as `?`. The atlas and ASCII renders are in the same directory.

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
  - `<NUM n>` (55 times) and `<STR n>` (31 times) need rewriting as the JP row's printf specifiers in JP's argument order. For example, Global's `Present_box_1` "Day <NUM 2> <STR 1>" becomes "Day %2$d…". **3.7.0's printf has no positional arguments that we know of, so a reordered row needs rewording instead.**
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
  - StringDB ignores `CLanguage`, so text still goes through the served master.
  - This is a one-argument client change, but which loaders use `FileExistLanguage` must be checked first.
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
| Global `ja` older than JP (821 rows) | the English may describe old values (hit counts, shop names) | leave Japanese, or take it after review (question Q2) |
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

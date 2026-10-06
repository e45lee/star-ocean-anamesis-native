# The Global (English) master DB: `data/basmaster-gl.sqlite3`

The user added `data/basmaster-gl.sqlite3` in commit 91010c7. It is the decrypted master DB of the **Global (English) service** of STAR OCEAN: anamnesis. This note compares it with the two JP masters the project uses:

- `data/basmaster-3.7.0.sqlite3`: the last JP online build, used by the port and soa-server.
- `data/basmaster-3.8.0.sqlite3`: the JP offline build. <!-- 380-ok: comparison data -->

In this note, "GL" is the Global DB and "JP" is JP 3.7.0, unless a row says otherwise. Every number below comes from read-only `sqlite3` or Python queries against the three committed DBs, plus the 3.7.0 download's `Scenario/` files (`work/SOA-3.7.0-canonical-data.zip`) and the 3.7.0 client `work/libSOA-3.7.0.so`. Each section ends with a short "How measured" note.

**Summary**

- The DB is the **final Global master**, published after the service ended on 2019-11-06. It is the 1.5.0 client's data, 2 years and 2 major versions older than JP 3.7.0.
- It is not a drop-in 3.7.0 master: 79 of JP's tables are missing, and the 3.7.0 client fails on a missing table.
- Its value is **official English text**. It has 32,302 rows of real English across system texts and story texts. 20,102 of JP 3.7.0's 66,945 master texts and 5,505 of its 23,169 scenario lines have an official English translation.
- Because the client ignores the `lang` column, an English mode would put that text into the `ja` rows of the JP master and the JP scenario files.
- Of JP 3.7.0's 321 playable character variants, Global released 137; 75 more are in its data but were never released (scheduled after the end of service), and 109 never reached its data (section 6).

## 1. Identity

| Fact | Value | Source |
|---|---|---|
| Client version | `a_ver_android` / `a_ver_ios` / `a_ver_amazon` = **1.5.0** (JP: 3.7.0) | `master_global` |
| Store ids | Google Play `com.square_enix.android_googleplay.StarOceann`, Amazon `...soaww`, App Store `id1363042639` (JP: `...StarOceanj`, `...soaj`, `id1137043197`) | `master_global` `store_url_*` |
| Terms version | `kiyaku_version` 20180927 (JP: 20200319) | `master_global` |
| Closed beta end | `cbt_end` 2018/6/19 16:00 (JP: 2016/11/28) | `master_global` |
| Launch | 122 roles have `opened_at` in 2018-06. `uimsg_tittle_end` says "since its release in July 2018" | `master_role`, `master_text` |
| Gem sales ended | "The sale of Gems has ended on Aug. 5, 2019 10:00 p.m. (PT) / Aug. 6, 2019 5:00 (UTC)" | `master_text` `uimsg_shop_end` (en) |
| Final event period | 9 event reruns: `event_term` 2019-08-06 → 2019-11-06. They are Love Across the Stars, The Wedding I/II, Halloween Fun, Christmas Event, Master Must Be Punished, Swimsuit Summer 1/2 and Package Sent with Love. Their box gachas run 2019-08-06 14:30 → 2019-11-06 13:59:59 | `master_event_term`, `master_gacha` |
| Last tower | `tower_19`, 2019-10-29 14:00 → 2019-11-06 13:59:59 | `master_tower_area` |
| **End of service** | `s_end` = **2019/11/6 14:00:00** | `master_global` (GL-only key) |
| End-of-service message | "STAR OCEAN: ANAMNESIS has ended service as of Nov. 5, 2019 9:00 p.m.(PT) / Nov. 6, 2019 5:00 (UTC)." | `master_text` `uimsg_tittle_end` (en) |
| SQLite writer | header bytes 96-99 = 3027002 (**3.27.2**). JP 3.7.0: 3008010 (3.8.10) | file header |
| Master revision | Not recorded. There is no version table, `user_version` is 0, and no `master_global` key holds a revision | — |

The DB's times are **JST** like JP's: 2019-11-06 14:00 JST is the 05:00 UTC of the end-of-service message.

Is it the last Global master? Yes. It contains the end-of-service title message and the `s_end` key. 406 of 423 gachas, 855 of 901 banners and the last tower all close exactly at 2019-11-06 13:59:59.

Some rows carry dates after the service end. They are pre-scheduled rotations or staged content that never ran:

| Table | Rows dated after 2019-11-06 | Range |
|---|---:|---|
| `master_item_shop` | 885 | weekly sets, 2019-11-07 → 2020-01-14 |
| `master_role` | 99 | 2020-01-07 → 2020-07-23 |
| `master_role` | 62 | 2030-05-20 placeholder |
| `master_awaken` | 100 | 2020-08-13 |
| `master_exchange_shop` | 72 | monthly coin shops, 2019-11-26 → 2021-03-16 |
| `master_achievement` | 51 | 2019-12-24 → 2021-03-16. These rows are JP's 2019 windows, shifted. Example: JP 2019-06-27 → GL 2021-03-16 |

So "latest date in the DB = 2021-04-13" (`master_achievement.closed_at`) is a scheduling artefact. It doesn't mean the service ran that long. The JP master's latest content date is 2021-06-24 (`service_stop_day` 2021/06/24 14:30).

`master_global` keys:

- **112 shared keys.** All have the same `id` (CHash32 of the key). 86 have the same value and 26 differ. Examples:
  - `Player_Rank_max` 500 vs 900;
  - `login_bonus_reset_hour` 20 vs 4;
  - `gear_stock_max` 300 vs 500;
  - `factor_base_coefficient_of_rality0..4` 5/15/30/50/75 vs 20/40/60/80/90;
  - `extraction_facter_1/3`, `rare_factor_for_normal_gear`, `default_master_gear_barney_chance_group` (`def_test` vs `default`);
  - the `studio_move_*` camera values;
  - `stamp_kind` (`promo` vs `12`).
- **21 GL-only keys:**
  - `s_end`;
  - `Default_Character_4/5`;
  - `Profile_FileName_1..10`;
  - `story_2nd_newpart_start/end` (43142/43149);
  - `store_url_android/ios`;
  - `studio_camera_lower/upper_range`, `studio_move_left/right`.
- **70 JP-only keys:**
  - features GL never got: `deity_*`, `favor_*`, `mastery_*`, `universe_*`, `sphere_stamina_*`, `cheater_*`;
  - the newer `studio_*` cameras;
  - JP's end-of-service keys: `service_stop_day`, `pay_back_*`.

How measured: `select key, value from master_global` in both DBs, joined on `key`. The latest real dates come from `max(col)` over every `*_at` column with `col < '2025'`, then `group by opened_at, closed_at`. The texts come from `select text_value from master_text where lang='en' and message_id in ('uimsg_tittle_end','uimsg_shop_end')`.

## 2. Schema

- **Tables:**
  - GL has **97** tables; JP 3.7.0 and 3.8.0 have **176**. <!-- 380-ok: comparison data -->
  - **93 are shared.**
  - **4 are GL-only**: `master_item_boosted_rate` (50 rows), `master_item_level_max` (5), `master_series` (109) and `master_series_message` (7).
  - **83 are JP-only**: `master_sphere211*` (15), `master_world_map*` (8), `master_favor_*` (6), `master_gear*` (5), `master_deco_*` (4), `master_subscription*` (3), `master_event_ranking*` (3), the `master_assist_*`, `master_menu_*` and `master_universe_*` families, `master_training_*`, `master_world_boss*`, `master_time_bonus`, `master_banner_replace`, `master_config`, `master_scenario_library`, `master_selectpart` and others.
- **Column types:** no shared column has a different declared type. Only `master_enemy_base_parameter` has a different column order: JP inserted `barrier_hp_rate` and `burn`.
- **Columns:** 3.7.0 added columns to 37 shared tables. GL has columns that 3.7.0 dropped or renamed in 18 tables. The larger ones:

| Table | JP-only columns | GL-only columns |
|---|---|---|
| `master_gacha` | 18: `gacha_item_id*`, `table_name`, `gacha_category`, `day_limit_count`, `sale_bulk_*`, `reset_*`, `loop_count`, `universe_chip_flg`, `resource_replace_group_id*`, `displays_purchase_history`, `disable_show_pass_period`, `gacha_pickup_group_id*` | `description_message_id` |
| `master_person` | 17: `chant_effect_id*`, `voice_master_id*`, `menu_voice_*`, `home_voice_*`, `voice_switch_*`, `home3d_*`, `bunker_setup_id`, `studio_radius` | — |
| `master_role` | 12: `assist_skill_category_id*`, `master_deco_attach_enable_id*`, `master_mastery_step_type_id*`, `mastery_talent_slot`, `universe_chip_item_id*`, `viewer_effect_id*`, `genus_flag` | — |
| `master_stage_layout` | 16: `r1..r4_pos_x/y/z`, `r1..r4_angle_y` | — |
| `master_event_mission` | 9: `difficulty`, `talk_message_file`, `is_bighunt`, `is_show_factor`, `time_bonus_type_id*`, `evaluation_group_id*`, `add_common_se` | — |
| `master_enemy_party` | 9: `trans`, `member1..8_rare_pop` | — |
| `master_event_area` | 8: `event_type`, `event_id*`, `event_tab`, `master_banner_id*`, `resource_replace_group_id*` | `description_message_id`, `banner` |
| `master_item` | 7: `master_gear_id*`, `factor1..3_lock`, `max_gear_slot_num`, `max_inheritance_num` | — |
| `master_item_shop` | 8: `master_banner_id*`, `reset_*`, `loop_count`, `new_limit_*` | `thumbnail_frame_type`, `banner`, `price_fol` |
| `master_banner` | 6: `master_banner_replace_type_id*`, `target_content_*`, `form_add_type` | `url2` |
| `master_stamp` | `cue_id` | `short_message_id`, `animation_resource`, `voice_resource`, `sort_name_idx` |
| `master_replace_resource` | `replace_group_id*` | `campaign_id*` |

Other notes:

- In shared tables, GL stores an unset id as **0** and JP stores it as **NULL**. This affects about 30 `*_id` columns, e.g. `master_role.master_talent5_id`. The client parser treats both the same way (a nil value or 0 leaves the default 0).
- `master_text` has the same 9 columns in all three DBs: `id, serial_number, lang, message_id, text_value, text_kana, data_type, category_id, category_id_label`.
- `id = CHash32(id_label)` holds in every GL table with an `id_label`, with these exceptions:
  - 4 `master_banner` rows and 1 `master_campaign` row (JP has a similar `master_campaign` exception);
  - 6 small `master_item_*` tables whose ids are plain numbers.

**Would the 3.7.0 client accept it as its master? No.**

- **Missing tables.** The client loads records lazily (`SELECT * FROM master_x WHERE id=?`, docs/notes.md "Master-data loader"). It names **70 of the tables GL lacks** in its strings (`strings work/libSOA-3.7.0.so | grep '^master_'`). Examples: `master_sphere211*`, `master_world_map*`, `master_gear*`, `master_favor_*`, `master_menu_bgm`, `master_menu_voice`, `master_guide_information`, `master_universe_board`, `master_mastery_step`, `master_subscription*` and `master_scenario_library`. Querying a missing table makes `SQLiteDriver::_Prepare` fail, and a failing prepare **closes the master DB** (docs/notes.md).
- **Missing columns are tolerated.** `CParameterElementBase::Deserialize` matches columns by name hash, and an absent column keeps the `Initialize()` default. The `ParameterByQuery` path is the exception: it leaves an absent column as allocator garbage. That path serves `master_global` lookups, and 70 of its keys are JP-only.
- **The server can't use it either.** soa-server and soa-emu reference 115 master tables (`grep -rhoE 'master_[a-z0-9_]+' server emulator/src`). **45** of them are absent from GL. Examples: all `master_sphere211*`, `master_world_map*`, `master_gear*`, `master_favor_*`, `master_event_ranking*`, `master_subscription*`, `master_time_bonus`, `master_banner_replace` and `master_gacha_pickup`.
- GL is a different, older game version (1.5.0). The usable route is to **merge its texts into the JP master**, not to swap masters.

How measured:

- Tables: `pragma table_info` diffs over the table lists (`sqlite_master`).
- Client tables: the client's `master_*` strings intersected with JP's table names.
- Server tables: the grep above.
- `id` check: `id == CHash32(id_label)` with `soa_save.adld.chash32` over every table with an `id_label`.

## 3. Content

**Row counts.**

- Outside `master_text`, GL has **84,074** rows and JP 3.7.0 has **185,735**.
- In the 93 shared tables GL has 83,903 rows and JP has 149,314.
- **66,927 ids appear in both DBs.** After normalizing 0/NULL/'' and ignoring `serial_number`, `sort_name_idx` and `*_at`, **59,116 of them (88%) are identical** in every shared column.

So the ids are the same CHash32 ids for shared content. A role, item, mission, skill or factor has the same id in both regions.

| Table | GL | JP 3.7.0 | Shared ids | Identical | GL-only | JP-only |
|---|---:|---:|---:|---:|---:|---:|
| `master_role` | 482 | 737 | 479 | 271 | 3 | 258 |
| `master_person` | 695 | 917 | 683 | 666 | 12 | 234 |
| `master_item` | 1,422 | 8,353 | 1,321 | 1,266 | 101 | 7,032 |
| `master_mission` | 607 | 613 | 607 | 378 | 0 | 6 |
| `master_event_mission` | 840 | 1,803 | 799 | 687 | 41 | 1,004 |
| `master_skill` | 2,881 | 4,117 | 2,846 | 2,468 | 35 | 1,271 |
| `master_skill_parameter` | 3,070 | 4,581 | 3,031 | 2,795 | 39 | 1,550 |
| `master_factor` | 4,503 | 7,590 | 4,268 | 4,227 | 235 | 3,322 |
| `master_factor_seed` | 6,567 | 13,455 | 6,505 | 6,397 | 62 | 6,950 |
| `master_talent` | 1,962 | 3,163 | 1,741 | 1,693 | 221 | 1,422 |
| `master_weapon` | 996 | 1,324 | 988 | 988 | 8 | 336 |
| `master_enemy_party` | 6,132 | 7,621 | 5,266 | 5,199 | 866 | 2,355 |
| `master_mission_stage` | 6,481 | 8,006 | 5,357 | 5,249 | 1,124 | 2,649 |
| `master_achievement` | 1,897 | 5,628 | 1,628 | 1,337 | 269 | 4,000 |
| `master_gacha` | 423 | 2,281 | 106 | 0 | 317 | 2,175 |
| `master_banner` | 901 | 1,774 | 74 | 0 | 827 | 1,700 |
| `master_item_shop` | 5,790 | 293 | 24 | 0 | 5,766 | 269 |
| `master_tower_mission` | 450 | 450 | 450 | 450 | 0 | 0 |

Where shared rows differ, the cause is either balance or a different schedule:

- `master_role`: the talent, skill and awakening assignments differ (`master_talent1_id` in 112 rows, `awaken_id` in 72);
- `master_skill`: `power`, `hate`, `range_*` and icons;
- `master_skill_parameter`: `damage` in 214 rows;
- `master_mission`: `order_id` and `recommend_level`;
- `master_enemy_base_parameter`: `fog` in 1,272 of 1,279 rows;
- the schedule tables (`gacha`, `banner`, `item_set`, `exchange_shop`): Global's own rotations.

**Roster.** The counts are of `master_role` rows with `id_label LIKE 'role_%'`. JP also has 31 `check_r*` and `cp*` test rows.

| | GL | JP 3.7.0 |
|---|---:|---:|
| Playable roles | 482 | 706 |
| Roles released by 2019-11-06 (`opened_at <= s_end`) | 321 | all (latest `opened_at` 2021-05-06) |
| Characters (person code, e.g. `cp0303`) | 118 | 157 |
| — `cp` (Star Ocean characters) | 70 | 84 |
| — `cn` (anamnesis originals) | 18 | 18 |
| — `cc` (collaborations) | 28 | 49 |
| — `cm` | 2 | 6 |
| Characters released in Global | 89 | — |

Global-only characters: none. All 118 GL character codes exist in JP. The 3 GL-only roles are dummy test roles, `role_cp0408_b01a_6024_a/b/c` (ja `※ダミーミュリアA/B/C`).

29 characters are in the GL DB but were never released in Global: their roles are dated 2020 or the 2030 placeholder. Japanese names come from the master; English names come from names_en.json where it has them.

| Group | Characters |
|---|---|
| `cc` | `cc0003` 渚のリーンベル, `cc0007` カペル (Capell), `cc0008` アーヤ (Aya), `cc0009` シグムント (Sigmund), `cc0018` ゼファー, `cc0019` ヴァシュロン, `cc0020` さくら, `cc0021` エリカ, `cc0022` ジェミニ, `cc0023` ミカサ, `cc0024` リヴァイ, `cc0026` ジャック (Jack), `cc0027` リドリー (Ridley), `cc0028` ソル, `cc0029` エルフェルト |
| `cp` | `cp0010`/`cp0011` ティカ (Tika), `cp0013` Yrian, `cp0014` Welch, `cp0015` Caleen, `cp0016` Vulcan, `cp0017` Henri, `cp0018` Ricardo, `cp0019` Mastema, `cp0112` Pericci, `cp0211` Noel, `cp0308` Peppita, `cp0405` Bacchus, `cp0409` Arumat |

39 characters exist only in JP 3.7.0:

| Group | Characters |
|---|---|
| `cc` | `cc0030` クレス, `cc0031` ミント, `cc0032` アーチェ, `cc0033` チェスター, `cc0034` ダオス, `cc0035` 結城 理, `cc0036` 鳴上 悠, `cc0037` ジョーカー, `cc0038` ナビ, `cc0039` 芳澤かすみ, `cc0042` カイ, `cc0043` ディズィー, `cc0044` 天宮さくら, `cc0045` 東雲初穂, `cc0046` 望月あざみ, `cc0047` アナスタシア, `cc0048` クラリス, `cc0049` Alicia, `cc0050` Rufus, `cc0051` Valkyrie, `cc0052` Frei |
| `cm` | `cm405` Luther, `cm420` Transcended Lezard, `cm505` フィリア, `cm506` Gabriel |
| `cp` | `cp0003` Coro, `cp0020` Jivreth, `cp0021` Heath, `cp0022` Laevonia, `cp0023` Jeanne, `cp0103` Dorne, `cp0107` Ashlay, `cp0109` Ioshua, `cp0111` T'nique, `cp0113` Erys, `cp0206` Bowman, `cp0210` Ernest, `cp0307` Roger, `cp0309` Adray |

None of them has an official English name.

**Other Global-only content.** It is mostly schedule and test data:

- the Global gacha, banner and shop rotations (317 gachas, 827 banners, 5,766 shop rows);
- `test_event_*` areas;
- six `event_evoexp_*` areas ("Enhance & Augment Mission"). Their 18 missions also exist in JP; only the area grouping differs;
- 12 translated GL-only items, all test or dummy weapons except `itm_th_*` (Launch Coin, Ore, Enchanted Tablet);
- 14 GL-only titles (`title_scenario_*`);
- 269 GL-only achievements, 267 of them translated. Examples: the "SO Nth Anniversary" challenges, and missions such as "Lucifer's Descent" and "Facula Dragon Raid" at Misery levels.

How measured:

- Row counts and identity: for each shared table, a Python join on `id` over the shared columns, with 0/NULL/'' normalized and `serial_number`, `sort_name_idx` and `*_at` skipped.
- Roster: `master_role r JOIN master_person p ON p.id = r.master_person_id WHERE r.id_label LIKE 'role_%'`, grouped by `split(p.id_label,'_')[0]`, with names from `master_text`.
- GL-only content: `WHERE id NOT IN (SELECT id FROM j.<table>)` with the JP DB attached as `j`.

## 4. Text

### How the Global DB stores text

- `master_text` has 129,808 rows: **64,904 `en` and 64,904 `ja`**, with the same message_id set in both languages.
- `id = CHash32(lang + "_" + message_id)` for all 129,808 rows. JP also uses the `"ja_"` key.
- Unlike JP, GL keeps the **story text in the master**: 25,668 rows per language with `data_type = 'package'` and `category_id_label` `TS_<chapter>` or `NNNN_NNN`. JP ships these in `Scenario/TS_*.msgp`.
- The system rows are 39,204 per language.
- Both regions store newlines in `master_text` as the two characters `\n`. The scenario `.msgp` files use real newlines.

### Is `en` complete? No: about half of it is a copy of the Japanese

Untranslated rows are those whose `en` contains kana or kanji.

| | English | `en` = `ja` (kana/kanji) | `en` ≠ `ja` but has kana/kanji | Language-neutral (`en` = `ja`, no kana) | Empty |
|---|---:|---:|---:|---:|---:|
| System (39,204) | 21,753 | 16,888 | 202 | 360 | 1 |
| Story (25,668) | 11,429 | 13,496 | 1 | 774 | 0 |

- The untranslated rows match content that Global never released. Of the 321 roles released in Global, 317 have an English character name; the other 4 are dummy or test roles. Of the 161 staged roles, 8 have one.
- The 202 "has kana, differs" rows are mostly translated profiles that keep a Japanese credit, e.g. `エナミカツミ \n\nKatsumi Enami`.
- One `ja` placeholder is notable: `cp0111_b01a_prmsg_10` = `【メモ】英語版の声優名が入る項目です` ("memo: the English version's voice-actor name goes here").

### Does GL's `ja` equal JP 3.7.0's texts?

- **System texts.** 36,385 of GL's message_ids exist in JP 3.7.0's master. **34,868 (95.8%) have identical `ja`.** The 1,517 that differ are later JP edits: balance changes in `factor_*`/`seed_*` (e.g. 400 → 200 hits), renamed shops (`新…交換所`), and filled-in talent names (`アーチェ３` → `ハーフエルフの知恵`). GL's `ja` is therefore an older revision, not the canonical text.
- **Story texts.** 13,225 GL story ids exist in JP 3.7.0's Scenario files. **10,634 have identical Japanese after converting `\n`.** A raw comparison gives 3,317, only because of the newline encoding.
- JP 3.8.0's master contains 23,529 of GL's message_ids. <!-- 380-ok: comparison data -->

### Coverage of JP 3.7.0 by official English

"English" means the GL `en` text exists, has no kana or kanji, and isn't a language-neutral copy. Categories come from the JP table and column that references the message_id, or else from its prefix.

| Category | JP 3.7.0 ids | in GL | English | English, and GL `ja` = JP `ja` |
|---|---:|---:|---:|---:|
| Character names (`master_person`) | 862 | 659 | 374 | 374 |
| Character profile/home lines (`cpNNNN_*`, `ccNNNN_*`, …) | 6,908 | 4,428 | 1,824 | 1,799 |
| Skills (`master_skill`, `Attack*`) | 4,248 | 2,878 | 1,827 | 1,819 |
| Factors/talents (`master_factor*`, `master_talent`, `master_universe_talent`) | 22,356 | 11,760 | 7,726 | 7,532 |
| Items (`master_item`, `coin_*`, `item_*`) | 8,799 | 4,353 | 1,991 | 1,951 |
| Missions/areas/events | 3,705 | 2,701 | 1,517 | 1,447 |
| Achievements/titles | 9,245 | 5,658 | 2,920 | 2,542 |
| Gacha/shops/login bonus | 3,195 | 1,156 | 374 | 357 |
| Sphere 211 (`master_sphere211_*`) | 2,403 | 0 | 0 | 0 |
| Guide/help (`master_guide_information`) | 1,326 | 8 | 0 | 0 |
| UI (`uimsg_*`, `error_*`, `sys_*`, …) | 2,701 | 2,002 | 1,072 | 970 |
| Other | 1,197 | 782 | 477 | 474 |
| **Total** | **66,945** | **36,385** | **20,102 (30.0%)** | **19,265** |

Characters:

- **139 of JP's 324 playable persons** (`master_person` rows with a `role_%` role) have an official English name.
- **90 of JP's 157 characters** have an English name for at least one variant.
- 327 of the 706 JP roles have an English character name.

Story: the JP 3.7.0 Scenario files hold 23,169 lines (the 64 `Scenario/TS_*.msgp` of the download, read with `soa_save.download_tree.DownloadTree` and `soa_save.script.texts_from`).

| JP scenario group | Lines | English in GL |
|---|---:|---:|
| `TS_1000`-`TS_1100` (EP1 chapters 1-11) | 3,389 | 3,379 |
| `TS_2010`-`TS_2110`, `TS_2502_mik` (EP2) | 8,428 | 453 |
| `TS_3xxx` | 882 | 782 |
| `TS_5xxx` | 941 | 891 |
| `TS_6010`-`TS_6060` (EP3) | 5,330 | 0 |
| `TS_9996`, `TS_C129`, `TS_D*`, `TS_E*` | 4,199 | 0 |
| **Total** | 23,169 | **5,505** |

- Matching the remaining lines by identical Japanese text adds only 40 lines (5,545 in total).
- Global's EP2 text exists in the DB but is mostly untranslated: most `TS_20xx` rows have `en` = `ja`.
- Global's event stories, `TS_A*` and `TS_B*`, are 9,551 lines and 4,990 of them are English. They have **no counterpart** in the 3.7.0 download: only 35 lines match by text. Their events' `Script/*.msgp` files are also absent; the 1,134 unresolved dialogue references of the JP 3.7.0 scripts are groups 99/20/60, not these events. Using those English lines would need the events' script files, which are Global or older-JP assets not in the repo.

How measured: Python over `master_text`.

- Kana/kanji test: `[぀-ヿ一-鿿]`.
- Categories: `message_id` → the first JP table/column whose `*message_id` or `*message` column holds it, else its prefix.
- Scenario lines: `soa_save.script.load_texts`, with JP `\n` normalized to `\\n` for comparison.
- Script references: `SPEECH` and `MENUS` commands over the 598 `Script/*.msgp` files of the pack and the download.

## 5. Uses for this project (recommendations)

### (a) Official English names for soa_save

These are the official Global names compared with `soa_save/names_en.json` (fan wiki), over the 139 JP playable persons with an official name:

- **129 agree** with `english_name()`.
- **4 differ**:

| JP | Official (GL) | names_en.json |
|---|---|---|
| 渚のマリア (`cp0303_b04a`) | Seaside Maria | Summer Maria |
| 渚のミリー (`cp0102_b03a`) | Seaside Millie | Summer Millie |
| 涙目ウェルチ (`cp0508_b01b`) | Tearful Welch | Weepy Welch |
| 花嫁イヴリーシュ (`cp0002_b03a`) | Bride Eve | Bride Evelysse |

  The official title prefixes are 渚の = "Seaside" and 常夏の = "Summer"; the wiki maps both to "Summer". 涙目 is "Tearful". The other 28 official prefixes agree with the `titles` map.
- **6 have an official name but no names_en.json entry**: `cc0004` Rain, `cc0005` Fina, `cc0006` Lasswell, `cc0015` 2B, `cc0016` 9S and `cc0017` A2. names_en.json also has no entry for most other `cc` collaboration codes.
- No base character name differs.
- The 185 persons without an official name (39 JP-only characters, plus variants never released in Global) still depend on the wiki.

Suggested approach: look up the name in the GL DB by `name_message_id`, using `en` only if it has no kana or kanji. Fall back to names_en.json. Fix the two title entries in names_en.json: 渚の → Seaside, 涙目 → Tearful.

### (b) An English mode for the 3.7.0 client

The full investigation (font, line breaks, the other text sources, an experiment with the merged master) and a plan are in [english.md](english.md) and [PLAN-english.md](PLAN-english.md).

**How the client picks text.** It doesn't select by language at all:

- `StringDB::GetNativeString` (3.7.0 vaddr 0x16faaec) builds the key with `Format("%s_%s", "ja", id)` and looks up `CHash32` of it.
- `StringDB::GetList` uses the literal `"ja_%s"` in its `WHERE id IN (...)` query.
- The `lang` column is never read. Adding `en` rows (`id = CHash32("en_"+mid)`) to the JP master would change nothing.
- `CLanguage` exists:
  - `tLanguage`: 0 = `ja`, 1 = `en`, 0x100 = `""`, 0x101 = `none`;
  - `PostfixLanguageCodeFilepath` makes `name-<code>.ext`.
  - `CGame::OnInitialize` constructs it as `CLanguage(0x100)` for default, current and voice, and the `Current(tLanguage)` setter has **no callers**.
  - Code 0x100 is the empty string (file offset 0x28d2011 is a NUL), so `CGameResourceManager::FileExistLanguage` never adds a language suffix.
  - The only live setting is `BAS:VoiceLanguage` (`CUIUtility::SetVoiceLanguage`, from `EffectiveSetting`). It would look for `Voice_*-en.spk` files, and the 3.7.0 download has no `-en` files.
- In short, the client's language depends on nothing at runtime: it is Japanese by construction.

**So an English mode means rewriting the `ja` rows' `text_value`**, keeping their ids, in the master the client is served. The hook already exists:

- soa-server builds the served master in `make_served_master()` (server/src/cdn/served_master.cpp) by applying `apply_client_master()` overrides to a copy of `data/basmaster-3.7.0.sqlite3`. That code already applies "the 3.7.0 texts" (docs/server-rules.md#cdn).
- The port's in-process server applies the same overrides to the client's in-memory master.
- An opt-in `--english` (with a `SOA_ENGLISH` variable) could add one more override from `data/basmaster-gl.sqlite3`. It would be off by default and documented in server-rules.md with source label (a).

Rules for that merge:

1. **Take only safe rows.** Use English rows, i.e. without kana or kanji. Prefer rows where GL `ja` = JP `ja`: 19,265 ids. The other 837 English rows translate an older JP text, e.g. old hit counts in factor descriptions. Leave those Japanese, or merge them with a flag.
2. **Convert Global-only markup.** Global's formatter used its own tokens; the 3.7.0 client uses printf.
   - 55 translated rows have printf specifiers that differ from the JP row's.
     - 49 are UI templates that replace `%d`/`%s` with `<NUM n>`, `<STR n>` and `<INSERT n>singular/plural</INSERT>`. Examples: `uimsg_remain_days` "Days left: <NUM 1>", `Present_box_6` "Day <NUM 2> <STR 1>" (arguments reordered), `uimsg_follow_num`.
     - The other 6 are gacha odds lines that use `%.3f` where JP uses `%.5f`. The count and type are the same, so these are safe.
   - In all, 145 translated ids use a Global-only token: the `<NUM>`/`<STR>`/`<INSERT>` tokens, `<EMDASH>` (223 occurrences in all `en`), or colour tags such as `[G]`, `[R]` and `[Blue]`.
   - Each such row must be rewritten to the JP row's printf specifiers in JP's order, or left Japanese. A specifier mismatch is a crash risk.
3. **Story texts don't go in the master.** The 3.7.0 client reads dialogue from `Scenario/TS_*.msgp`. Each row has `id = CHash32("ja_"+mid)`, real newlines and `lang: ja`. An English mode would rewrite `text_value` in those files and serve them as CDN overlay members, re-encrypted with ADLD XOR (`soa_save.script.encrypt`). This would cover EP1 almost entirely (3,379/3,389), `TS_3xxx`/`TS_5xxx` mostly, and nothing of EP2 (453 lines), EP3 or the 3.7.0 events.
4. **Still Japanese after a merge:**
   - 46,843 of JP's 66,945 master texts have no English. They include the whole of Sphere 211 (2,403) and guide/help (1,326), and the world map, universe board, favor, gear and subscription texts: 3.x features Global never had.
   - Text baked into images: banners, UI textures, logos and `Image/` / `UI/` assets. Global's localized images were on its own CDN and aren't in this DB.
   - Voices.
   - Layout: the JP UI's fixed text boxes may clip or overflow longer English. This is untested.
   - The JP font is assumed to cover ASCII; this is also untested.

### (c) Other uses

- **Reference translations.** The GL DB is the official glossary for skill names (1,827), factor and talent descriptions (7,726), items (1,991) and missions (1,517). It's useful for docs, the save editor, and labelling the server's master-data rules in English.
- **Older balance data.** 1,517 `ja` texts and the differing rows in `master_skill`, `master_skill_parameter`, `master_role` and `master_factor` record a 2018-2019 balance state. That may interest anyone studying the JP balance history, but it isn't needed for the 3.7.0 restore.
- **Restorable Global-only content: essentially none.** There are no exclusive characters, the six `event_evoexp_*` areas reuse JP missions, and the GL-only rows are schedules and test data. The one candidate is Global's anniversary achievement and title set (269 achievements, 14 titles). Its texts are here, but it would need the server to define achievements that the 3.7.0 master doesn't have. Low value.
- **Global's story English** can be extracted for reading even where no 3.7.0 script plays it, e.g. by `soa_save.script` listings with an `en` text source. It is 11,429 lines in total, including 4,990 lines of the `TS_A*`/`TS_B*` event stories.
## 6. JP characters Global never released

Playable variants (`master_person` rows with a `role_%` row in `master_role`; each costume is its own variant; dummy/test rows dropped) of JP 3.7.0, by their state in the Global master: **137 released** in Global (earliest role `opened_at` before the end of service, 2019-11-06 14:00 JST), **75 in Global's data but never released** (scheduled after the end of service: 2020-01/02, 2020-07-23, or the placeholder 2030-05-20), **109 not in Global's data at all**. The NieR:Automata collab (2B, 9S, A2) is among the released.

How measured: `master_person` ⨝ `master_role` in both DBs, the name from `master_text` (`lang='ja'` in Global), the Global English name where it differs from the Japanese; JP date = the earliest role `opened_at` in 3.7.0, Global date = the same in the Global DB.

### 6.1 In Global's data, never released (75)

| Variant | JP name | JP release | Global scheduled | Global English name |
|---|---|---|---|---|
| `cc0003_b01a` | リーンベル | 2017-05-20 | 2030-05-20 | — |
| `cc0003_b02a` | リーンベル | 2017-05-20 | 2030-05-20 | — |
| `cc0007_b01a` | カペル | 2017-11-16 | 2030-05-20 | — |
| `cc0008_b01a` | アーヤ | 2017-11-16 | 2030-05-20 | — |
| `cc0009_b01a` | シグムント | 2017-11-16 | 2030-05-20 | — |
| `cc0003_b03a` | 渚のリーンベル | 2018-04-26 | 2030-05-20 | — |
| `cc0018_b01a` | ゼファー | 2018-04-26 | 2030-05-20 | — |
| `cc0019_b01a` | ヴァシュロン | 2018-04-26 | 2030-05-20 | — |
| `cp0412_b02a` | マフィア | 2018-05-20 | 2030-05-20 | — |
| `cp0503_b01b` | ユーイチ | 2018-05-20 | 2030-05-20 | — |
| `cp0301_b02a` | 花婿フェイト | 2018-05-31 | 2020-07-23 | — |
| `cp0402_b04a` | 花嫁レイミ | 2018-05-31 | 2020-07-23 | — |
| `cp0205_b03a` | 花嫁プリシス | 2018-06-14 | 2020-07-23 | — |
| `cp0312_b04a` | 花嫁クレア | 2018-06-14 | 2020-07-23 | — |
| `cp0005_b03a` | ヒーローベルダ | 2018-06-28 | 2020-07-23 | — |
| `cp0504_b02a` | ナースフィオーレ | 2018-06-28 | 2020-07-23 | — |
| `cp0112_b01a` | ペリシー | 2018-07-12 | 2020-07-23 | — |
| `cp0204_b02a` | 灼炎のアシュトン | 2018-07-12 | 2020-07-23 | — |
| `cp0102_b03a` | 渚のミリー | 2018-07-26 | 2020-07-23 | Seaside Millie |
| `cp0303_b04a` | 渚のマリア | 2018-07-26 | 2020-07-23 | Seaside Maria |
| `cp0002_b05a` | 渚のイヴリーシュ | 2018-08-09 | 2020-07-23 | — |
| `cp0101_b02a` | 渚のラティクス | 2018-08-09 | 2020-07-23 | — |
| `cp0202_b04a` | 渚のレナ | 2018-08-16 | 2020-07-23 | — |
| `cp0208_b02a` | 執事のレオン | 2018-08-30 | 2020-07-23 | — |
| `cp0302_b04a` | メイドのソフィア | 2018-08-30 | 2020-07-23 | — |
| `cp0010_b01a` | ティカ | 2018-09-03 | 2030-05-20 | — |
| `cp0013_b01a` | ユーイン | 2018-09-13 | 2020-07-23 | — |
| `cp0209_b02a` | 紅輝のオペラ | 2018-09-13 | 2020-07-23 | — |
| `cp0303_b05a` | 兎耳のマリア | 2018-09-27 | 2020-07-23 | — |
| `cp0310_b02a` | 兎耳のミラージュ | 2018-09-27 | 2020-07-23 | — |
| `cn0015_b01b` | 戦斧マルセル | 2018-10-11 | 2020-07-23 | — |
| `cp0014_b01a` | ウェルチ | 2018-10-11 | 2020-07-23 | — |
| `cp0205_b04a` | 操機のプリシス | 2018-10-18 | 2020-07-23 | — |
| `cp0305_b04a` | 堕天使ネル | 2018-10-25 | 2020-07-23 | — |
| `cp0306_b03a` | 狼アルベル | 2018-10-25 | 2020-07-23 | — |
| `cp0504_b04a` | 包帯フィオーレ | 2018-10-31 | 2020-07-23 | — |
| `cp0507_b02a` | かぼちゃリリア | 2018-10-31 | 2020-07-23 | — |
| `cn0002_b01b` | 斬刈ボリス | 2018-11-15 | 2020-07-23 | — |
| `cp0015_b01a` | カーリン | 2018-11-15 | 2020-07-23 | — |
| `cp0409_b01a` | エイルマット | 2018-11-15 | 2020-07-23 | — |
| `cp0005_b04a` | 歌星ベルダ | 2018-11-29 | 2020-07-23 | — |
| `cp0402_b05a` | 歌星レイミ | 2018-11-29 | 2020-07-23 | — |
| `cp0502_b04a` | 歌星ミキ | 2018-11-29 | 2020-07-23 | — |
| `cp0202_b05a` | 雪花レナ | 2018-12-13 | 2020-07-23 | — |
| `cp0204_b03a` | 雪空アシュトン | 2018-12-13 | 2020-07-23 | — |
| `cp0312_b05a` | 聖夜クレア | 2018-12-13 | 2020-07-23 | — |
| `cp0002_b06a` | 迎春イヴリーシュ | 2019-01-01 | 2020-07-23 | — |
| `cp0010_b02a` | 迎春ティカ | 2019-01-01 | 2020-07-23 | — |
| `cp0301_b03a` | ＳＲＦフェイト | 2019-01-10 | 2020-01-07 | — |
| `cp0302_b05a` | ＳＲＦソフィア | 2019-01-10 | 2020-01-07 | — |
| `cc0020_b01a` | さくら | 2019-01-17 | 2030-05-20 | — |
| `cc0021_b01a` | エリカ | 2019-01-17 | 2030-05-20 | — |
| `cc0022_b01a` | ジェミニ | 2019-01-17 | 2030-05-20 | — |
| `cp0015_b02a` | 甘狐のカーリン | 2019-02-01 | 2020-02-04 | — |
| `cp0112_b02a` | 天真のペリシー | 2019-02-01 | 2020-02-04 | — |
| `cp0404_b02a` | 凛花リムル | 2019-02-07 | 2020-01-21 | — |
| `cn0010_b01b` | メカギディオン | 2019-02-14 | 2020-07-23 | — |
| `cp0016_b01a` | ヴァルカ | 2019-02-14 | 2020-07-23 | — |
| `cp0017_b01a` | アンリ | 2019-02-14 | 2020-07-23 | — |
| `cp0405_b01a` | バッカス | 2019-02-14 | 2020-07-23 | — |
| `cc0023_b01a` | ミカサ | 2019-02-28 | 2030-05-20 | — |
| `cc0024_b01a` | リヴァイ | 2019-02-28 | 2030-05-20 | — |
| `cp0002_b07a` | 歌星イヴリーシュ | 2019-03-14 | 2020-01-14 | — |
| `cp0302_b06a` | 歌星ソフィア | 2019-03-14 | 2020-01-14 | — |
| `cp0201_b03a` | 蒼星のクロード | 2019-03-20 | 2030-05-20 | — |
| `cp0202_b06a` | 蒼星のレナ | 2019-03-20 | 2030-05-20 | — |
| `cc0026_b01a` | ジャック | 2019-03-28 | 2030-05-20 | — |
| `cc0027_b01a` | リドリー | 2019-03-28 | 2030-05-20 | — |
| `cp0011_b01a` | 刻星のティカ | 2019-04-11 | 2030-05-20 | — |
| `cp0018_b01a` | リカルド | 2019-04-11 | 2030-05-20 | — |
| `cc0028_b01a` | ソル | 2019-04-25 | 2030-05-20 | — |
| `cc0029_b01a` | エルフェルト | 2019-04-25 | 2030-05-20 | — |
| `cp0019_b01a` | マスティマ | 2019-05-01 | 2030-05-20 | — |
| `cp0211_b01a` | ノエル | 2019-05-09 | 2030-05-20 | — |
| `cp0308_b01a` | スフレ | 2019-05-09 | 2030-05-20 | — |

Only 2 of them have an English name in the Global master; the rest are Japanese copies.

### 6.2 Not in Global's data (109)

JP releases after Global's data was frozen (mostly May 2019 to May 2021). The four 2017-05-20 rows look like NPC or story variants rather than releases.

| Variant | JP name | JP release |
|---|---|---|
| `cm505_b01a` | フィリア | 2017-05-20 |
| `cp0003_b01a` | コロ | 2017-05-20 |
| `cp0010_b03a` | アイドル子ティカ | 2017-05-20 |
| `cp0111_b02a` | ティニーク（狼版） | 2017-05-20 |
| `cp0207_b03a` | トモカズ | 2019-05-25 |
| `cc0030_b01a` | クレス | 2019-05-25 |
| `cc0031_b01a` | ミント | 2019-05-25 |
| `cc0032_b01a` | アーチェ | 2019-06-06 |
| `cc0033_b01a` | チェスター | 2019-06-06 |
| `cc0034_b01a` | ダオス | 2019-06-13 |
| `cp0304_b02a` | 花婿クリフ | 2019-07-01 |
| `cp0310_b03a` | 花嫁ミラージュ | 2019-07-01 |
| `cp0206_b01a` | ボーマン | 2019-07-11 |
| `cp0305_b05a` | 真夏のネル | 2019-07-18 |
| `cp0401_b03a` | 真夏のエッジ | 2019-07-18 |
| `cp0011_b02a` | 真夏のティカ | 2019-07-31 |
| `cp0015_b03a` | 真夏のカーリン | 2019-07-31 |
| `cp0309_b01a` | アドレー | 2019-07-31 |
| `cp0109_b01a` | ヨシュア | 2019-08-15 |
| `cp0113_b01a` | エリス | 2019-08-15 |
| `cp0203_b02a` | ハンターセリーヌ | 2019-08-29 |
| `cp0408_b03a` | 花魁ミュリア | 2019-08-29 |
| `cp0208_b03a` | 蒼星のレオン | 2019-09-12 |
| `cp0212_b02a` | 蒼星のチサト | 2019-09-12 |
| `cp0016_b02a` | メイドヴァルカ | 2019-09-26 |
| `cp0504_b05a` | メイドフィオーレ | 2019-09-26 |
| `cc0035_b01a` | 結城 理 | 2019-10-10 |
| `cc0036_b01a` | 鳴上 悠 | 2019-10-10 |
| `cc0037_b01a` | ジョーカー | 2019-10-10 |
| `cc0038_b01a` | ナビ | 2019-10-24 |
| `cc0039_b01a` | 芳澤かすみ | 2019-10-24 |
| `cp0202_b07a` | 鏡宮のレナ | 2019-10-24 |
| `cp0205_b05a` | 魔改のプリシス | 2019-11-07 |
| `cp0403_b02a` | 祓魔師フェイズ | 2019-11-07 |
| `cp0002_b08a` | 魔女イヴリーシュ | 2019-11-14 |
| `cp0005_b05a` | 輪舞曲のベルダ | 2019-11-28 |
| `cp0011_b03a` | 円舞曲のティカ | 2019-11-28 |
| `cp0112_b03a` | 雪猫ペリシー | 2019-12-12 |
| `cp0303_b06a` | 銀雪マリア | 2019-12-12 |
| `cp0015_b04a` | 暁狐のカーリン | 2020-01-01 |
| `cp0402_b06a` | 鳳弓のレイミ | 2020-01-01 |
| `cp0305_b06a` | 華王妃ネル | 2020-01-23 |
| `cp0312_b06a` | 華王妃クレア | 2020-01-23 |
| `cc0042_b01a` | カイ | 2020-01-30 |
| `cc0043_b01a` | ディズィー | 2020-01-30 |
| `cp0113_b02a` | 天翼のエリス | 2020-02-13 |
| `cp0502_b05a` | 甘恋のミキ | 2020-02-13 |
| `cp0002_b09a` | 泉郷イヴリーシュ | 2020-02-27 |
| `cp0202_b08a` | 泉郷レナ | 2020-02-27 |
| `cp0301_b04a` | 神翼のフェイト | 2020-03-12 |
| `cc0044_b01a` | 天宮さくら | 2020-03-26 |
| `cc0045_b01a` | 東雲初穂 | 2020-03-26 |
| `cc0048_b01a` | クラリス | 2020-03-26 |
| `cc0046_b01a` | 望月あざみ | 2020-04-09 |
| `cc0047_b01a` | アナスタシア | 2020-04-09 |
| `cp0015_b05a` | 狐将のカーリン | 2020-04-30 |
| `cp0018_b03a` | 砲甲のリカルド | 2020-04-30 |
| `cp0019_b02a` | 賢神のマスティマ | 2020-05-14 |
| `cp0303_b07a` | 神翼のマリア | 2020-05-14 |
| `cp0305_b07a` | 斬鬼のネル | 2020-05-28 |
| `cp0306_b04a` | 鬼炎のアルベル | 2020-05-28 |
| `cp0011_b04a` | 花嫁ティカ | 2020-06-11 |
| `cp0015_b06a` | 花嫁カーリン | 2020-06-11 |
| `cn0008_b01b` | 魔鞭アンゲリカ | 2020-06-25 |
| `cp0021_b01a` | ヒース | 2020-06-25 |
| `cp0022_b01a` | ラヴァーニア | 2020-06-25 |
| `cc0049_b01a` | アリーシャ | 2020-07-09 |
| `cc0050_b01a` | ルーファス | 2020-07-09 |
| `cp0005_b06a` | 常夏のベルダ | 2020-07-30 |
| `cp0312_b07a` | 常夏のクレア | 2020-07-30 |
| `cp0013_b02a` | 真夏のユーイン | 2020-08-13 |
| `cp0014_b02a` | 真夏のウェルチ | 2020-08-13 |
| `cp0022_b02a` | 渚のラヴァーニア | 2020-08-27 |
| `cp0113_b03a` | 渚のエリス | 2020-08-27 |
| `cp0202_b09a` | 神星のレナ | 2020-09-10 |
| `cc0051_b01a` | ヴァルキリー | 2020-09-24 |
| `cm420_b02a` | 超越者レザード | 2020-09-24 |
| `cp0402_b07a` | メイドレイミ | 2020-10-08 |
| `cp0409_b02a` | 執事エイルマット | 2020-10-08 |
| `cp0303_b08a` | 吸血鬼マリア | 2020-10-22 |
| `cp0308_b02a` | 奇術師スフレ | 2020-10-22 |
| `cp0210_b01a` | エルネスト | 2020-10-29 |
| `cp0204_b04a` | 神龍のアシュトン | 2020-11-12 |
| `cp0003_b07a` | コロ | 2020-11-26 |
| `cp0202_b10a` | 歌星レナ | 2020-11-26 |
| `cp0301_b05a` | 歌星フェイト | 2020-11-26 |
| `cp0002_b10a` | 黒のイヴリーシュ | 2020-12-10 |
| `cp0015_b07a` | 雪狐カーリン | 2020-12-17 |
| `cp0305_b08a` | 聖夜ネル | 2020-12-17 |
| `cp0011_b05a` | 初春ティカ | 2021-01-01 |
| `cp0022_b03a` | 初夢ラヴァーニア | 2021-01-01 |
| `cp0402_b08a` | 神弓のレイミ | 2021-01-14 |
| `cm405_b02g` | ルシファー | 2021-01-21 |
| `cp0102_b04a` | 甘恋のミリー | 2021-01-28 |
| `cp0205_b06a` | 甘砲のプリシス | 2021-01-28 |
| `cc0010_b02a` | 粛清のフレイ | 2021-02-10 |
| `cc0052_b01a` | フレイア | 2021-02-10 |
| `cp0020_b01a` | ジヴェレーゼ | 2021-02-25 |
| `cp0023_b01a` | ジャンヌ | 2021-02-25 |
| `cp0302_b07a` | 神導のソフィア | 2021-03-11 |
| `cm506_b01a` | ガブリエル | 2021-03-18 |
| `cp0011_b06a` | 歌星ティカ | 2021-03-25 |
| `cp0015_b08a` | 歌星カーリン | 2021-03-25 |
| `cp0111_b01a` | ティニーク | 2021-04-08 |
| `cp0307_b01a` | ロジャー | 2021-04-08 |
| `cp0002_b11a` | すみリーシュ | 2021-04-22 |
| `cp0005_b07a` | シオリ | 2021-04-22 |
| `cp0103_b01a` | ドーン | 2021-05-06 |
| `cp0107_b01a` | アシュレイ | 2021-05-06 |

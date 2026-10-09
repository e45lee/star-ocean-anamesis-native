# The gacha presentation (3.7.0): result order and animation

What the 3.7.0 client shows after a draw reply (`Gacha`, `SaleGacha`, `GachaTicket`, `BoxGacha`, ...):
in which order the drawn units appear, which animation plays and what selects it, which assets it
loads, and what that means for the local server. Investigation of 2026-10-07 (agent `gacha-anim`).

Addresses are ELF virtual addresses of `work/libSOA-3.7.0.so` (Ghidra address = ELF + 0x100000,
`tools/decomp_at.sh`). Evidence labels as in [server-rules.md](server-rules.md#source-labels): (a)
master data, (b) client code, (c) outside knowledge, (d) assumption. Earlier notes on the same classes:
[notes.md](notes.md) "Gacha" (`CGachaManager`, the server data in `CParameterManager`).

## Answers in short

1. **Order: the reply's order, no sorting** (b). The 3D summon, the per-unit reveals and the result
   list all walk `GachaItems` (`CParameterManager+0x4fb8`) from the first entry to the last. Nothing
   sorts by rarity, by type, by new/duplicate, or moves the guaranteed slot. A single draw is the same
   path with one entry. The only thing the server decides is the order it sends; the local server sends
   draw order with the bulk-bonus draw last (d, `server/src/api/gacha/gacha.cpp`).
2. **Animation: one fixed 3D sequence on the gacha stage, coloured per unit by rarity** (b). The
   "tier" of a unit is 0 for ★1–3, 1 for ★4, 2 for ★5 and up; the opening (magic circle, summoner voice,
   SE) uses the highest tier of the draw; every unit gets its own disc, magic mark, reveal stage and
   reveal SE in its own tier. Characters appear as their 3D model with the role's gacha camera, weapons
   as the weapon held by the summoner. Then a 2D overlay per unit shows the art, rarity word, stars and
   name, plus "limit break" (`overLimit`) or "limit-break material" (`OverLimMat`) for duplicates. The
   only server-controlled switch is `is_mutation` (a fake-out: a unit first shown below its tier, then
   transformed); the banner picks the stage map through `master_gacha.resource_replace_group_id` (a + b).
   There is no effect/production master table and no random variant except the summoner's line for
   tiers 0–1 and the fake-out's starting tier.
3. **Server: nothing extra is needed for the normal presentation** (b). Rarity, new/duplicate, limit
   breaks and the camera all come from master data plus `duplication`, `LimitBreakCharacter` and
   `LimitBreakItem`, which the server already sends. `is_bonus` is never sent (the client reads it, no
   visible effect found); `is_mutation` is set since 2026-10-08 on 2 % of the drawn ★5 units
   (`master_global.gacha_mutation`, d; `--gacha-surprise PCT`, docs/server-rules.md#gacha-surprise).
   See [Server implications](#server).

<a id="order"></a>
## 1. Order

The draw reply fills `CParameterManager+0x4fb8`, a vector of `CGachaResultInfo` (0x188 bytes) in the
order of the `GachaItems` array (`DeserializeToInfo`, [notes.md](notes.md) "Gacha draws"). Its fields
(b: `CGachaResultInfo::Initialize` @0x13fc3c4 hashes the seven key names):

| offset | key | used by the presentation |
|---|---|---|
| +0x60 | `master_item_id` | the weapon / item of a non-character entry |
| +0x90 | `player_item_id` | result list |
| +0xc0 | `master_role_id` | 0 = not a character |
| +0xf0 | `player_character_id` | result list |
| +0x120 | `duplication` | 2D overlay mode, result list "NEW" |
| +0x150 | `is_mutation` | the fake-out (below) |
| +0x180 | `is_bonus` | sets a flag, no reader found (below) |

(`tools/fakeapi_fields.py` lists only the first six: `is_bonus` is short enough to be built inline,
without a string literal; other info classes may be short a field the same way.)

Every consumer copies this vector index by index:

- **3D summon** `CGachaManager::Initialize` @0x114bdd0: entry *i* (0x68 bytes at manager+0x08 + i·0x68)
  ← result *i*: kind (1 character if `master_role_id` ≠ 0, else 2), role, item, `duplication` → +0x28,
  `is_mutation` → +0x2b, `is_bonus` → +0x2c; the count at +0x470. Box gacha replies take the box
  results (`+0x73b8`) the same way (kind 1 character, 2 weapon, 0 other item). (b)
- **The discs and magic marks** (`CheckDisc` @0x1151cc8, `CheckMagicEffect` @0x1151ecc) go to fixed
  stage nodes by index (`disc_posi_NN`, `magicmark_posi_NN` from tables; a single draw uses
  `disc_posi_11` / `magicmark_posi_10`, the centre). (b)
- **Per-unit reveal** `Progress_Main` @0x114e988 sub-states 5–15: the current index (+0x478) starts at 0
  and goes +1 per `RequestNextChara`; after the last, the presentation ends. (b)
- **2D overlay and result list**: `CGacha::ProcProduction` @0x19bc610 first calls
  `CLimitOverCharacter::CreateGachaData` @0x1cef3bc → `CreateListGacha` @0x1cef498 →
  `CreateListGachaFromNormalResult` @0x1cefb08 (or `...FromBoxResult` @0x1cf00e0), which `push_back`s
  one `ResultData` (0xc0 bytes) per result in vector order; `CountLimiBreak` @0x1cedcf8 and
  `SetupLimitBreakItem` @0x1cede30 then annotate the duplicates in that order. The overlay of unit *i*
  is `GetResultData(i)` (`CGacha::Setup3DInsert2D` @0x19c5994 with `CGachaManager::Get2DWaitIndex`), so
  overlay and 3D unit always match. The result list (`CLimitOverCharacter::OpenResult` @0x1cec710 /
  `UpdateResult` @0x1cee5c4) places entry *i* into slot *i* (`pop1/window/node_chara` or `node_weapon`
  children, by the entry's type). (b)
- No `std::sort` or comparison is called in any of these (b: the decompiles).

So **the reply order is the display order**: the first `GachaItems` entry is the first disc, the
first reveal and the first slot of the result grid. For a 10-draw, the position of the ★5 is visible
three times (disc colour, reveal order, grid slot), so the order the server picks is what the player
sees. The live server's order is unknown (no source); the local server's is its (d) choice.

<a id="animation"></a>
## 2. The animation

### The sequence

`CGacha::ProcProduction` creates a `CGachaManager` (`TSingleton`, 0x4f8 bytes) with its own `CArena`
and drives it (states in [notes.md](notes.md) "The draw sequence"):

1. **Load** (`CGachaManager::Progress` @0x114d00c state 1, `LoadResource` @0x114d4f0): stage map
   `bg99_01` (or the banner's replacement, below), the summoner `Character/cp0002_b01b.asf` with
   `Motion/Gacha.apk`, cameras `Camera/gacha_camera_01..03.aaf`, the effects of the draw's tiers, each
   unit's camera `Camera/<gacha_camera>.aaf`, sound bank `Voice_UI_004`.
2. **Idle on the stage**: camera 01, summoner motion `gacha_cp0002_01.aaf`, effect `eo100_f01a`, SE
   0x2b; the 召喚開始 button (`Button_start`).
3. **Summon** (after the tap; `Progress_Main` sub-state 0): camera 02, `eo100_f01b` and the circle host
   `eo100_f02a`, the **draw-tier circle** `eo100_f03{a,b,c}` (by the overall tier), the opening SE
   44/45/46 (by the overall tier, table @0x26dcf20), summoner motion `gacha_cp0002_02.aaf`, and a
   summoner line: tier 2 → `cp0002_5406_GachaMagic_030`; tiers 0–1 → `cp0002_5404_GachaMagic_010` or
   `cp0002_5405_GachaMagic_020` at random (`Aska::Random(2)`).
4. **Discs** (sub-state 1, `CheckDisc`): one disc per unit, in order, at fixed effect frames
   (@0x26dcf38), effect `eo100_f04{a,b,c}` by the unit's tier.
5. **Magic marks** (sub-states 2–3): discs vanish; one mark per unit, `eo100_f05{a,b,c}` by tier.
6. Wait for the camera (sub-state 4), white fade.
7. **Per unit** (sub-states 5–15), index 0..n−1:
   - *character* (kind 1): the role's 3D model (`CBattleUtility::CreateCharacterByRole`, with its
     weapon) in gacha pose (animation 0x16), the role's own effect if `master_role.viewer_effect_id`
     is set (36 roles; entry +0x24 from role +0x1258), camera `Camera/<master_role.gacha_camera>.aaf`
     (`gacha_camera_03`, 8 roles `_04`), the **reveal stage** `eo100_f06{a,b,c}` by tier and the
     **reveal flash** `eo100_f07a`, the reveal SE 47/48/49 by tier (table @0x26dcf2c); after a delay the
     character's gacha voice (`master_person.gacha_voice_package`, `CUIVoiceManager::GetGachaVoicePackName`).
   - *weapon* (kind 2): the weapon (`CWeaponObject::InitializeByWeaponId`) attached to the summoner,
     who plays `<master_weapon_kind.viewer_motion>.aaf` (`WeaponDisplay` / `WeaponDisplay2`), camera
     `Camera/<master_weapon_kind.gacha_camera>.aaf` (`gacha_camera_03`, or `_03_W08Be` / `_03_W11Sc` /
     `_03_W13Th`), stage `eo100_f06{a,b,c}` and flash `eo100_f07a` as above.
   - *other item* (kind 0, box gachas only): no 3D, straight to the 2D overlay.
   - **2D overlay** (`CGacha::Setup3DInsert2D` @0x19c5994, animations named by
     `GetAnimationNameStart3DInsert2D` @0x19c6a9c, table @0x27aa729: `overLimit`, `OverLimMat`, `ChrIn`,
     `Rarity`, `ChrName`, `5star`, `4star`, `3star`, `2stars`, `1stars`): the character illustration (or
     the item icon), the rarity word, the stars, the name; for a duplicate first `overLimit` (with the
     new limit-break count in `Grade`, 1–9 as digits, 10 as `Image/word_10_01_rainbow.aif`) or, when it
     became limit-break material (`LimitBreakItem`), `OverLimMat`; then the stars SE 0x33/0x34/0x35.
   - Two taps per unit: the first (`Panel_tap` → `CGachaManager::OnTap`, sub-state 0xe → 0xf) ends the
     3D reveal and its voice and shows the 2D overlay; the second requests the next unit
     (`RequestNextChara`). (b; seen in the port, [Observed](#observed))
8. **End**: fade, teardown, `CLimitOverCharacter::OpenResult`: the result list (the grid with "NEW"
   badges, limit-break counts, then character chips / bonus pages).

Skips: a tap during steps 3–6 jumps to the first unit (`Progress_Main`: `+0x482` in sub-states 1–4);
`Button_allskip` (`CGachaManager::ForceExit`, +0x480) ends the whole presentation and opens the result
list. (b)

<a id="selection"></a>
### What selects it

| What | Decided by | Values | Evidence |
|---|---|---|---|
| unit tier (disc, mark, stage colour; reveal SE) | the unit's rarity: `master_role.rarity` (role +0x278) or `master_item.rarity` (item +0x118) | ★1–3 → 0 (`…a`), ★4 → 1 (`…b`), ★5/★6 → 2 (`…c`) | (b) `CheckGachaResult` @0x114c724, `RarityIndex` @0x1150fc0 |
| draw tier (circle `eo100_f03*`, opening SE, summoner line) | the highest tier among the units **without** `is_mutation` | as above | (b) `CheckGachaResult` (+0x474) |
| summoner line at tiers 0–1 | random | `GachaMagic_010` / `_020`, 50 % each | (b) `Progress_Main` sub-state 1 |
| the fake-out | `is_mutation` = true on the unit (server) | shown first at tier 0 (★5: tier 0 or 1, random), flash `eo100_f07b` + SE 0x32 instead of `f07a`, then the same unit again at its real tier; excluded from the draw tier | (b) `CheckGachaResult`, `Progress_Main` sub-states 9, 0xd, 0xe |
| character camera | `master_role.gacha_camera` | `gacha_camera_03` (729 roles), `gacha_camera_04` (8) | (a) + (b) `CheckGachaResult` (entry +0x4e) |
| character aura | `master_role.viewer_effect_id` | 36 roles | (a) + (b) entry +0x24 → `Progress_Main` sub-states 7–8 |
| weapon camera and summoner motion | `master_weapon_kind.gacha_camera`, `.viewer_motion` | see above | (a) + (b) `Progress_Main` sub-state 0xb |
| 2D background | the unit's rarity | ★1–3 `Image/BG2_R3.aif` + `BG3_R3`, ★4 `BG2_R4` + `BG3_R4`, ★5+ `BG2_R6` + `BG3_R6` | (b) `Setup3DInsert2D` |
| 2D rarity word | rarity and `master_role.rank` (role +0x2a8) | character: ★3 `rare`, ★4 rank 1 `super_blue` else `super_orange`, ★5+ rank 1/2/3 `galaxyrare_blue`/`_orange`/`_red`, rank 4/5 (aces, exceed) `galaxyrare_rainbow2`; weapon: ★1–3 `rare`, ★4 `super_orange`, ★5 `galaxyrare_rainbow2` | (b) `Setup3DInsert2D` @0x19c62e8.. |
| 2D stars | rarity | `1stars`..`4stars`, ★5 and ★6 both `5stars` | (b) |
| 2D mode | `duplication`, `LimitBreakItem` | new character (1), duplicate → `overLimit` (2), duplicate turned into material → `OverLimMat` (3), weapon/item (4) | (b) `Setup3DInsert2D` (+0x968), `ProcProduction` |
| limit-break count shown | `LimitBreakCharacter` before/after counts, assigned to the duplicates in order | `Grade` sprite | (b) `CountLimiBreak` |
| stage map | `master_gacha.resource_replace_group_id` → `master_replace_resource` (res_type 4) if its window contains now | `bg99_01`, or `bm0033_b01a` (`gachamap_20200514`, 2020-05-14 … 2030), `bm0014_b01i` (`gachamap_20210325`, 2021-03-25 … 04-08) | (a) + (b) `CGacha::SetSelectSceneChoice` @0x19b5d98 → `CResourceReplaceManager::SetReplaceGroupID` @0x1e52354 (filters rows by `IsEnableTime`), reset in `CGacha::ReturnSeriesList` |

Not involved: there is no `master_gacha_effect` / `master_gacha_production` table and no banner
column for the effect; the step-up number, the price and the pick-up flag don't change the
presentation; there is no movie (`Movie/`) in the draw. `master_global.gacha_mutation` (2) is not read
by the client (its key hash appears nowhere in the code), so it is a server parameter (a: the row;
d: its meaning, e.g. a mutation chance).

Not visible: `is_bonus` (+0x2c) only sets manager+0x484 (when the unit is ★5+); entries +0x29 / +0x2a
(the role is in `LimitBreakCharacter` / `LimitBreakItem`) and +0x2d (a weapon already owned) are set
by `CheckGachaResult`; `IsResultInDeity` (a rank-5 role in the result) sets `CGacha+0xbf0`. No reader
of these was found (a search for byte loads `ldrb [x, #off]` at those offsets finds only unrelated code; 32-bit loads at +0x484 / +0xbf0 exist in other code, e.g. copies of master elements, and were not checked one by one), so they change
nothing on screen as far as the code shows. (b, negative search)

<a id="assets"></a>
### Assets

All in the 3.7.0 download (checked 2026-10-07), so the presentation is complete:

| Asset | Files | Present |
|---|---|---|
| effects | `Effect/eo100_f01a`…`f07b.apk` (18; the code uses all but `f02b`) | all |
| summoner | `Character/cp0002_b01b.{acf,apk}`, `Motion/Gacha.apk` | yes |
| cameras | `Camera/gacha_camera_01..04.aaf`, `gacha_camera_03_W08Be/_W11Sc/_W13Th.aaf` | all 7 |
| stage maps | `BG/bg99_01`, `BG/bm0033_b01a`, `BG/bm0014_b01i` (`.aaf`/`.acf`) | all |
| 2D images | `Image/etc2/BG2_R3/R4/R6`, `BG3_R3/R4/R6` (`BG2_R5`, `BG3_R5`, `BG3_R7` also exist; no code path picks them), `rare`, `super_blue/_orange`, `galaxyrare_blue/_orange/_red/_rainbow2`, `word_10_01_rainbow` | all |
| UI layouts | `UI/etc2/gacha_main`, `gacha_top`, `gacha_top_anime`, `Gacha_Insert`, `gacha_result`, `gacha_result2`, ... `.csf` | present (which layout is the overlay: `Gacha_Insert` by name, d) |
| summoner lines | cues `cp0002_540{4,5,6}_GachaMagic_0{1,2,3}0`, played by name through `CSoundManager::PlaySe`; `LoadResource` adds `Voice_UI_004` (`Sound/Voice_UI_004.spk`, present) | the bank is present; that the cues are in it is (d) |
| character gacha voices | `Sound/<master_person.gacha_voice_package>.spk`: 231 distinct packages | 222 present; missing `Voice_GR_cp0012`, `_cp0202_09`, `_cm505`, `_cm405f`, `_cm427_`, `_cn0008`, `_cp0303_07`, `_cc0040`, `_cn0010`; 5 of them belong to drawable roles (in `data/gacha_pools.sqlite3`: `_cm405f`, `_cn0008`, `_cn0010`, `_cp0202_09`, `_cp0303_07`) |

The missing voice packages are a risk worth a test: sub-state 8 waits for `CSoundManager::IsLoading()`
to clear before the reveal, so if a missing package left the loader busy, the reveal of those 5 roles
would hang (d: not tested; the illustration and model files of every pool role are present,
[gacha-verify.md](gacha-verify.md)).

<a id="server"></a>
## 3. Server implications

What the presentation needs from a draw reply, and what the local server sends
(`server/src/api/gacha/gacha.cpp`):

| Field | Client use | Local server | Verdict |
|---|---|---|---|
| `GachaItems` order | display order everywhere | draw order; the bulk-bonus draw last (d) | correct by construction; the live order is unknown (c) |
| `master_role_id` / `master_item_id` | kind, rarity, camera, model | base roles, weapons | correct |
| `duplication` | 2D mode, NEW badge | 1 for a duplicate | correct |
| `LimitBreakCharacter` (before/after counts) | `overLimit` + `Grade` count | sent per character, steps assigned in order | correct |
| `LimitBreakItem` | `OverLimMat` | sent for duplicates beyond the max | correct |
| `is_mutation` | the fake-out | set on a drawn ★5 unit with `master_global.gacha_mutation` (2) % chance; `--gacha-surprise PCT` (0 = off) | (d): the rate and the ★5 restriction (docs/server-rules.md#gacha-surprise) |
| `is_bonus` | flag, no visible effect found | not sent (false) | harmless; for fidelity send `is_bonus` = true on the bonus draw (d) |

No server bug that changes the presentation was found. Suggestions (no code changed):

1. **`is_bonus`** on the bulk-bonus draw: `result["is_bonus"] = bonus;` next to `is_mutation` in
   `draw_weapon` / `add_drawn_role` (`gacha.cpp`, the `bonus` flag of the draw loop at line ~349). Wire
   fidelity only.
2. **`is_mutation`** (done 2026-10-08, the reading below; `gacha.cpp` `roll_surprise`): the live server evidently sent it for some ★5 draws (the client
   has a dedicated effect `eo100_f07b`, an SE and the `Debug_GachaMutation` API with
   `CGachaMutationTestResultInfo {content_id, content_type, is_mutation}`); a playable rule would set
   it on a small share of ★5 units, e.g. `master_global.gacha_mutation` (2) read as a percent (d). It
   only changes the show: the fake-out starts the circle at a lower tier, so a 10-draw whose only ★5 is
   a mutation looks like a ★4 draw until that unit transforms.
3. server-rules.md 4.3 described `is_mutation` as "a draw upgraded to a higher-rarity variant": the
   client shows it as a presentation of the same unit, with no rarity change (corrected there).

<a id="observed"></a>
## Observed: a 10-draw in the port (2026-10-07)

The `gacha` session (in-process server, `SEED_RNG` default, real clock) with its 10-draw replaced by a
burst of screenshots: `work/gacha-anim/burst_run.py` (local, not committed: `.venv/bin/python
work/gacha-anim/burst_run.py build/port/soa OUT SCRATCH`). Two runs drew the same units (names from `master_person.name_message_id` → `master_text`, a)
(`gacha_role_0001`, the standard banner, no stage replacement, so `bg99_01`). Shots in
`work/gacha-anim/run1/shots/` (the summon in detail) and `work/gacha-anim/run2/shots/` (every unit),
contact sheets `work/gacha-anim/sheet-summon.png`, `sheet-run2-units.png`, `sheet-run2-result.png`,
`result-grid-crop.png`; the reply `run2/packets/5-SaleGachaRes.msgp`.

The reply's `GachaItems`, in order, and what the screen showed:

| # | role (rarity, rank) | dup | 3D stage | 2D word / stars / extra |
|---|---|---|---|---|
| 0 | `role_cp0509_b01a_5011` ダリル (★5, 3) | 0 | purple galaxy (tier 2) | ギャラクシーレア (red) ★★★★★ |
| 1 | `role_cp0407_b01a_5025` サラ (★5, 3) | 1 | tier 2 | ギャラクシーレア ★★★★★ 限界突破 1 |
| 2 | `role_cn0005_b01a_3024` ロシェル (★3, 1) | 1 | blue (tier 0) | レア ★★★ 限界突破 1 |
| 3 | `role_cn0018_b01a_3033` ベルナール (★3, 1) | 1 | tier 0 | レア ★★★ 限界突破 1 |
| 4 | `role_cp0508_b01a_4024` ウェルチ (★4, 2) | 1 | gold (tier 1) | スーパーレア ★★★★ 限界突破 1 |
| 5 | `role_cn0004_b01a_3024` セス (★3, 1) | 1 | tier 0 | レア ★★★ 限界突破 1 |
| 6 | `role_cp0201_b01b_5074` 式服のクロード (★5, 3) | 0 | tier 2 | ギャラクシーレア ★★★★★ |
| 7 | `role_cn0003_b01b_3135` 豪剣ハインリヒ (★3, 1) | 1 | tier 0 | レア ★★★ 限界突破 1 |
| 8 | `role_cn0016_b01b_3084` 宝珠エレオノーレ (★3, 1) | 1 | tier 0 | レア ★★★ 限界突破 1 |
| 9 | `role_cp0508_b01a_4024` ウェルチ (★4, 2) | 1 | tier 1 | スーパーレア ★★★★ 限界突破 **2** |

- **Order confirmed**: the reveals came in exactly this order (`run2/shots/b-unitNN-*`: two taps per
  unit, the first ends the 3D reveal, the second the 2D overlay), and the result list
  (`16-gacha-result.png`) places them clockwise from the top in the same order (0 at the top, 9
  upper left). The two ウェルチ show limit break 1 then 2: `CountLimiBreak` hands the
  `LimitBreakCharacter` steps (0 → 2) to the duplicates in order.
- **Animation confirmed**: the draw has ★5s, so the summon used the tier-2 circle (red-orange,
  `b-summon-01..03`), the discs and the marks (`b-summon-03..07`); each unit's stage colour followed
  its own rarity (purple ★5, gold ★4, blue ★3); the rarity words and stars follow the table above
  (rank-3 ★5 → `galaxyrare_red`, rank-2 ★4 → `super_orange`, ★3 → `rare`); new units have no
  limit-break line, duplicates `overLimit` with the count.
- Not seen in this run: weapons, a single draw, `OverLimMat`, the stage replacement and the fake-out
  (the server never sends `is_mutation`).

# The 3D home character (3.7.0)

How the 3.7.0 client decides whether the home (お気に入り) character is shown as a 3D model or as a 2D illustration, what it loads for the 3D model, and how it picks motions, lines and voices. Written for the NieR:Automata collab characters (2B, 9S, A2), which 3.7.0 never shows in 3D; the port's `--home3d-all` debug option shows them anyway.

Evidence labels as in `docs/server-rules.md`: **(a)** master or asset data, **(b)** client code (3.7.0 `libSOA.so`, Ghidra addresses = ELF vaddr + 0x100000), **(d)** assumption or reading not fully checked. "Seen" marks what the port showed (`control/run.py home-character`, 2026-10-04).

## The decision: 3D or 2D

| Step | What decides | Evidence |
|---|---|---|
| 1. The home character | `CHome::GetAdjutant` @01aebe38: CParameterManager+0x8698 (the favor login bonus's character) if set, else +0xd08 (`Player.home_pc_id`), looked up among the owned characters by uid; no match: party set 1's first member (`docs/server-rules.md` "Home character") | (b) |
| 2. The player's 2D/3D setting | `CHome::Setup` copies CParameterManager+0xd38 (`Player.is_3d_home`) to CHome+0x3f4 (1 = 3D) | (b) |
| 3. The character's flag | `GetAdjutant` writes `!person.home3d_disable` (CMasterPerson+0x9a8) to CHome+0x3f7 ("3D allowed") and `home3d_file != ""` (person+0x9d8) to CHome+0x3f8 | (b) |
| 4. Forcing 2D | `CHome::Update` @01aeafa8: when 3D isn't allowed but the player's setting is 3D, CHome+0x3f4 = 0 (2D) and +0x3f5 = 1 (a switch is pending) | (b) |
| 5. The switch button | `Node_3_2d3d/2d3d` darkened (`SetButtonStateDarkEX(+0x3f7)`), its image `menubtn_2d3d_on.png` / `_off.png`. It sits in the 会話モード (interactive mode) footer ("2D/3D変更", next to お気に入り変更 and キャラデコ), not on the main home | (b); seen |
| 6. The pending switch | `CHome::Progress` state 2: with +0x3f5 set it sends `Home3DAnd2DSwitching(0)` (fid a092292c, `CErrorHandlerWrap::Auto`); the answer's lambda @01affa10 sets state 3 and +0x3f4 = CParameterManager+0xd38 (the answered `is_3d_home`); a failure returns to the title. Without an answer the home stays in state 0x10 (d: no other path out was found) | (b) |
| 7. 2D | the sprite `chara` shows `CUIUtility::FormHomeCharacterIllustFileName` = `Image/<short>_fv<NNx>.aif` (`GetCharaFile`, e.g. `Image/cc0015_fv01a.aif`), visible iff +0x3f4 is 0 (`CHome::Update`, `Progress`) | (b); seen |
| 8. 3D | `CHomeModelViewManager` loads the model and the Home3D parameters (below) | (b) |

No other gate was found: no device-spec check in the functions read (d), and studio mode (`InitializeStudioMode`, `CParameterUtility::IsOpenStudio`) is a separate path. The map is `master_home_message.bg3d_resource_name` of the current home message when set, else `bh01_01` (`CHomeModelViewManager::Initialize(u32, string, bool)` @01476958 / `Initialize(u32, bool)` @014772d8; catalog `master_home3d_map`) (b).

### The persons 3.7.0 shows in 2D only (`home3d_disable` = 1) (a)

| Person | Name | Roles |
|---|---|---|
| `cc0015_b01a` | 2B (NieR:Automata) | 2 |
| `cc0016_b01a` | 9S (NieR:Automata) | 2 |
| `cc0017_b01a` | A2 (NieR:Automata) | 2 |
| `cc0003_b01a`, `cc0003_b02a`, `cc0003_b03a` (渚の) | リーンベル | 2 each |
| `cc0007_b01a`, `cc0008_b01a`, `cc0009_b01a` | カペル, アーヤ, シグムント | 2 each |
| `cc0018_b01a`, `cc0019_b01a` | ゼファー, ヴァシュロン | 2 each |
| `cp0003_b07a` | コロ (a variant) | 6 |
| `cp0412_b02a`, `cp0503_b01b` | マフィア, ユーイチ | 2 each |
| `cc0003_b01a_2`, `cp0304_b01a_8` | dummies (no roles) | 0 |

All of them have a `home3d_file`, a `Parameter/Home3D/home3d_<file>.msgp` and a model: the data is there, only the flag holds them back (a). 901 persons have it 0 or unset.

## What the 3D home loads

| What | Rule | Evidence |
|---|---|---|
| The Home3D parameters | `CHomeModelViewManager::Request3DHomeData` @01477ee0 → `CHomeUtility::LoadHomeParameter` @014aec8c → `FindHomeParameterName` @014ae474: `Parameter/Home3D/home3d_<home3d_file>.msgp`. **The only existence check:** a missing file falls back to `home3d_male_common.msgp` / `home3d_female_common.msgp` by `role.gender` (else `person.sex`; 1 = male) | (b) |
| Dated rows | `CHomeUtility::GetHomeParameter` @014af0ec marks each row available iff `opened_at <= now` and not `closed_at < now` (server time) | (b) |
| The model | `SetupCharacter` @01477390 → `CHomeUtility::CreateCharacter` @014afab8: the person's `asf` / `acf` / `apk` | (b) |
| Row motions | each available row with a `motion_filename` (except `..stay_deco`): `master_home3d_motion_setting` by `id_label` = the motion name; found: `Motion/home_<setting.motion_filename>.apk`. **No setting row: the motion is skipped silently** | (b) |
| Blinks | no available `eye` / `eye2` row: `Motion/home_eye_blink_01.apk` / `_02.apk` | (b) |
| Mouth (lip sync) and facial anims | no available `mouth` row: the per-character `Motion/home_<short>.apk` (`<short>` = the person label's first token, e.g. `cp0002`); it holds `mouth`, `correction` and the facial anims | (b); (a) |
| T-pose | always `Motion/home_t_stance.apk`; `Progress_HomeTalk` @0147ccec case 8 starts `t_stance`, case 9 plays `correction` when the model has it | (b) |
| Facial effects | `LoadFacialEffect` @014782e4: each row's `facial_effect_filename`; `CreateEffectModel` @01478200: `Effect/eo101_f01a` ("homeEff"); blush on the cheek bones (`BlushEffectStart` @0148362c) | (b) |
| Home voices | `Progress_HomeTalk` case 8 adds the person's home voice pack (`CUIVoiceManager::AddResourcePackHome`) only when the rows name voices | (b) |
| Camera | `SetCameraPos` @01477a10: the height from the model plus `master_person.home3d_camera_height_offset`, the depth `home3d_camera_depth_offset`, the zoom from the aspect ratio (`docs/notes.md` "Orientation and the home camera") | (b) |

### A Home3D row (`CMasterHome3DElement::Initialize` @01288a84) (b)
`id`, `id_label` (`home3d_<file><category><NN>`), `motion_filename`, `facial_filename`, `facial_effect_filename`, `effect_delay_frame`, `scenario_id_low` / `_upper`, `weight`, `level_low` / `level_upper` (default 9999; the favor level gate), `no_skip`, `no_blink`, `no_lipsync`, `blend_frame` (45 when unset), `text_id`, `voice_id`, `not_lipsync_voice`, `voice_delay_frame`, `opened_at` / `closed_at`; `available` is computed. `master_home3d_motion_setting` overrides `no_skip`, `no_blink`, `no_lipsync`, `blend_frame` and the motion file name.

Categories (the label's suffix; `SetMotionNameList` @01478588, `GetMotion3DRecord` @014871b4): `stay`, `stay_long`, `reaction`, `talk`, `give`, `get`, `mouth`, `eye`, `eye2`, `stay_deco`.

### How motions and lines are picked (b)
- `GetRandomMotion` @014830a0: weighted among the category's rows that are available, weight > 0 and `level_low <= favor level <= level_upper` (the favor level from `SetLikeabilityLevel` @01478544).
- Idle: `PlayStayMotionRandom` @0147fb8c loops a `stay` row; after a `stay` ends, a counter (about 120 frames) then a 50% chance of `stay_long`, played once (d: the counter's exact meaning).
- A tap: `TapReactionMotionRandom` @01484a18, weighted among `talk` + `reaction` rows, never the same row twice in a row; its `text_id` goes to `CHome::PlayTalk` @01aef4e8 (the speech box), its `voice_id` to `PlayVoice` @01487ae8 (`CSoundManager::PlaySe`; empty: nothing plays). Tapping may also add favor (`UpdateFavorByTap`).
- Lip sync: `MouthMotion` @014816f4 adds the `mouth` anim while the voice plays; nothing when the mouth row's motion is empty. Eyes: `EyeMotion` @0148151c on a timer; nothing when the eye rows' motions are empty.
- `stay_deco`: weight 0 on the home and left out of the home's load; only the deco viewer (`CModelViewManager::SetupDecoStayMotion`) and the battle file list use it.
- **In 2D the manager still runs** (no model): it loads the Home3D rows, so a tap shows the row's `text_id` line (2B's `cc0015_b01a_hmmsg_01/02`) and plays its voice. Without a `home3d_file` the line comes from `master_home_message` instead (`CHome::PlayTalk(1,0,NULL)`).

### The home behaviour, frame by frame (b)
`CHomeModelViewManager::Progress_HomeTalk` @0147ccec (state 0xc, every frame; counters in game frames, advanced by `CTimeElement::DT`), on the HomeCharacter (`+0x28` the model):
- **Stay**: `PlayStayMotionRandom(hc, mode, blend)` @0147fb8c: mode 0 picks a `stay` row (`GetRandomMotion`) and starts it looped with `blend` frames of blending (a negative blend: the row's `blend_frame`); mode 1 picks a `stay_long` row, starts it once with 45 frames of blending, its `facial_filename` as an overwrite layer (`StartOverwriteAnimation`) and its facial effect (`BlushEffectStart` after `effect_delay_frame`); a mode above 1 is `Aska::Random(2)`. Each start re-arms the blink timer (the row's `no_blink` 0) or stops the eyes (`EyeMotionStop`), and the mouth (a voice playing and `no_lipsync` 0) or stops it.
- **Stay → stay_long**: once the stay motion has terminated (`IsAnimationTerminate`), a counter (+0x1028) counts to 121 frames; then `MouthMotionStop`, the counter restarts and `Random(2) == 1` plays `stay_long` (mode 1, blended by the stay row's `blend_frame`). When a stay_long ends (the counter is −1 while it plays), `PlayStayMotionRandom(99)`: stay or stay_long again, 50 % each, and the blush effect ends. (d) for a looped stay, "terminated" is read as its first pass having ended.
- **Blinks**: a timer (+0x102c, −1 = off) counts while it is below the current blink clip's length (+0x1030); past it, `Random(2) == 0` plays the `eye` row's clip (`EyeMotion` @0148151c, an additive layer that replaces the previous one) and resets the timer; otherwise the `eye2` row's clip, without resetting it. The clip length becomes the new interval. The clips: the rows' motions, else `home_eye_blink_01` / `_02`.
- **Mouth**: while a voice plays, a timer (+0x1034) restarts the mouth clip (`MouthMotion` @014816f4, an additive layer `home_<mouth>`) whenever it passes the clip's length (+0x1038); when the voice stops, `MouthMotionStop`. Nothing when the mouth row's motion is empty.
- **Taps**: `TapReactionMotionRandom` @01484a18: the `talk` and `reaction` rows whose motion is set, available, weight > 0 and favor level in [level_low, level_upper] (the debug flag +0x3200 skips the level check), except the row played last (+0x3288) unless the categories hold only one row; `HighPrecisionRandom() % (sum of weights)` against the cumulative weights. The row's text goes to the speech box, its voice to `PlayVoice`.

## 2B, 9S and A2 (a)

| | 2B `cc0015_b01a` | 9S `cc0016_b01a` | A2 `cc0017_b01a` | Evelysse `cp0002_b01a` (an ordinary character) |
|---|---|---|---|---|
| rows | 8 | 8 | 8 | 17 |
| stay_deco (unused on the home) | `home_deco_idle_f_a01` | `home_deco_idle_m_a01` | `home_deco_idle_f_a01` | |
| stay / stay_long | `home_idle_f_a51` / `_a52` | `home_idle_m_a01` / `_a51` | `home_idle_f_a51` / `_a52` | `home_idle_f_a01` / `home_long_idle_f_a01` |
| talk (weight 10 each) | `home_idle_f_a53` / `_a54` (idle variants), `cc0015_b01a_hmmsg_01/02`, no voice | `home_idle_m_a52` / `_a53`, `cc0016_b01a_hmmsg_01/02`, no voice | `home_idle_f_a53` / `_a54`, `cc0017_b01a_hmmsg_01/02`, no voice | 12 rows: emotion / generic / reaction motions, facial anims and effects, voices, favor gates |
| eye, mouth rows | present, empty motion: no blinks, no lip sync | same | same | none: `home_eye_blink_01/02`, `home_cp0002.apk` |
| home voice pack | none | none | none | `Voice_Home_cp0002` |
| `home3d_camera_height_offset` | 14 | -13 | 13.5 | |

So the collab characters' 3D home is minimal by design of the data: idle loops, two lines with an idle variant as the "talk" motion, no voice, no blinking, no mouth movement, and no per-character `Motion/home_cc00NN.apk` (none is needed: the empty mouth row stands in for it).

## In the port

- **Normal run:** with 2B, 9S or A2 as the home character the home shows the 2D illustration (`Image/cc0015_fv01a.aif` for 2B) and their lines. The client forces 2D and sends `Home3DAnd2DSwitching(0)`; the local server stores the mode (`player.is_3d_home`, schema version 12) and answers it, in-process through the port's FakeApiCaller route, and the home continues (`docs/server-rules.md#home-2d-3d`). Before that fix (seen 2026-10-04) the route returned a status without answering, the home never continued, and it stayed empty (no model, no illustration). The 会話モード 2D/3D変更 button switches an ordinary character between the model and the illustration the same way. The mode is the player's, one flag for every home character: after 2B forced 2D, another home character stays 2D until switched back. Checked by `control/run.py home-character` (2B: the request and the illustration; Evelysse: 2D and back).
- **`--home3d-all`** (debug; a flag of soa and soa-server): the local server clears `home3d_disable` in the client's master copy (`server/src/api/player/home.cpp`, `docs/client-changes.md`). Seen: 2B, 9S, A2 (and リーンベル) load their models (`Character/<p>.acf`, `Character/etc2/hi/<p>.asf`), the idle motions (`Motion/home_home_idle_*`) and `home_t_stance`; they stand and sway (no T-pose), a tap shows their lines with the idle-variant "talk" motion, no voice, no blinks, no lip sync, as the data says. The camera frames them like the other characters; no missing-file or load error in the log. 会話モード works.
- Session: `control/run.py home-character SOA OUT TMP [--home ROLE]... [--home3d-all] [--movie SECS]` (seed variants from `tools/make_test_seed.py --home`; `--movie` records the home by repeated `shot:` commands, about 12 frames a second, encoded with each frame's real duration).

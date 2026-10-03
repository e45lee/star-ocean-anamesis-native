> **History.** This is the 2026-09-30 plan (tracks A-D, waves 1-3) of the 3.8.0-based port. The port now runs the 3.7.0 client (tag `pre-rebase-370` is the old port); the current plan is [`port/PLAN.md`](../../port/PLAN.md) and the remaining work is [`port/REMAINING.md`](../../port/REMAINING.md).

# Plan: the remaining work (from 2026-09-30)

What's left after the overnight run of 2026-09-29/30. Details and evidence are in `docs/history/REMAINING.md` ("Status update 2026-09-30"). The long-range native roadmap is `REMAINING.md` §5; this plan covers the next waves.

## Where things stand
- **`--restore` plays the 3.7.0 game locally:**
  - Episode 1 campaign; party and growth; gear; gacha and shops; deep space; Sphere 211.
  - Events: lists, stories, rankings, world boss, and `--enable-events` by keyword.
  - The tutorial from a fresh state; rentals; the 3.7.0 home.
- **Native share of busy time under `--restore`: 65.3%.** Guest JIT is 10.3% and HLE imports 24.2%. 17,816 natives are registered.
- **Every session script prints PASS/FAIL.** Full selftest 534/534.
- **Status 2026-09-30 evening:** Waves 1 and 2 are merged (✅ below). The audit of mechanically translated code is `docs/history/AUDIT-9-30.md`.

## Working rules (unchanged)
- **Where fixes go:** server first; client changes are logged in `docs/client-changes.md`; rules are labelled (a)–(d); nothing about which assets exist is hard-coded; never commit real player ids.
- **How agents work:** one worktree per agent on `port/<name>`. Merge only committed, gated work (`tmp/merge.sh`, now refusing merges that don't start), with no tracked symlinks.
- **Memory:** each `soa` under 6 GB (9 GB for live-check runs), one `soa` per agent, builds at `-j4`–`-j6`, and the watchdog running (`merge-gating-lessons` memory).
- **The gate:** full selftest, smoke, and the restore / campaign / party / newplayer / home / rental / deepspace / events / tutorial sessions. Sphere 211 (about 17 minutes) only on the final gate. Run sessions in short batches, because background jobs have a time limit.

## Track A: gameplay gaps under `--restore` (server first)
| # | Item | Size | Risk |
|---|---|---|---|
| A1 | ✅ **done 2026-09-30** — Step-up series and box gachas on the gacha screen, including the イベントガチャ tab (**in progress**) | S | low |
| A2 | ✅ **done 2026-09-30** — Enabled events' exchange shops (アイテム交換所) opened with `--enable-events` | S | low |
| A3 | ✅ **done 2026-09-30** — Home: serve titles (`master_title*`), a local notice-board page (static text instead of the blank web view: client change, logged), the `CHome` tutorial after home | M | low |
| A4 | ✅ **done 2026-09-30** — Helpers: event NPC helpers' weapons (`master_npc_base_parameter.master_item_id`, via the client NPC model like the tutorial fix); the `CRentalBonus` popup | S | low |
| A5 | ✅ **done 2026-09-30** — Sphere 211 extras: rental slot, weekly challenge and achievements, season ranking rewards; add stamina heal, reroll and pause-menu continue to the session | M | low |
| A6 | ✅ **done 2026-09-30** — Deep space extras: coin-bought and subscription ships, deep-space achievements, daily and weekly limits | M | low |
| A7 | ✅ **done 2026-09-30** — Server rules: barney-chance effects, the favor-login-bonus limit key; re-verify gear removal in game | S | low |
| A8 | ✅ **done 2026-09-30** — Events: `GetPlayerDetailInfo`, ranking checked live if a ranking event's assets turn up (rerun `tools/event_coverage.py` after downloads) | S | low |
| A9 | World map (Episodes 2/3 map flow beyond the first story) | L | medium |
| A10 | Multiplayer as single-player with NPC or rental partners (`CMultiPlay3` stand-in) | L | medium |
| A11 | ✅ **done 2026-09-30** — Tower (`--restore-tower`): no other layout source exists; the floor list was blocked by missing banner rows (server-side stand-ins) and the tower menu not adding the common-resource scene (client change), not by the layout. Only `play_plate/0-3` get hidden stand-ins. `tower_session.sh`; docs/notes.md "Tower layout". | M | medium |

## Track B: native port (bit-exact, differential tests plus live checks)
| # | Item | Size | Risk |
|---|---|---|---|
| B1 | ✅ **done 2026-09-30** — **One shared live-check library.** Merge the copies in `battle_core_check.cpp`, `arena_rt.cpp`, `objbase_rt.cpp`, `particles_rt.cpp` and `battle_charobj*` into one harness with every fix found so far: stale stubs re-applied per check, lone-`B` callees followed, sret pattern fill, the undo log, freed-block snapshots, never-empty `only`, memory caps. Prerequisite for B2–B4. | M | low |
| B2 | ✅ **done 2026-09-30** — objbase: verify the 71 unregistered functions (`PlayAnimation` / `ProgressBlend` / `ProgressFrame` are the hot path). This needs a check mode for a chosen set, so nested callees get checked. Find the `SOA_OBJBASE_ALL` home crash by bisecting with `SOA_OBJBASE_SKIP`; explain `Callback_EndPostProgress`. | M | medium |
| B3 | ✅ **done 2026-09-30** — Particles: the excluded `RenderProcedure` (+0x1ac difference), the four render bodies no check reached, EmitMotion's first-attempt difference | S | low |
| B4 | ✅ **done 2026-09-30** — `CMissionMenu::Setup` / `ToMissionDetail`: the live check crashes (pc = ASCII); fix the harness, then register them with a `t.call370` oracle test. `CEffectManager::Remove` / `Release` differential tests. | S | low |
| B5 | ✅ **done 2026-09-30** — a2c: `fcvtmu` (`GetVelocityByAet`), plus whatever the next families need | S | low |
| B6 | Next families from a fresh profile: `CPartyManager`, the remaining battle glue, `CStageManager`, and the result screens | M | medium |
| B7 | HLE imports (24% of busy time): profile the GL / libc / pthread paths and cut overhead, e.g. batch GL state and native memcpy / strlen fast paths | M | medium |
| B8 | `REMAINING.md` §5 steps 2–3 (offline stubs for platform, store and polling; main loop and threads native), the road to `--no-jit` | L | medium |

## Track C: readability
- **Rewrite the hottest a2c transcriptions as readable C++.** Each keeps its live check at 0 mismatches.
  - Start with those added tonight: dynamics `CollisionAndConstraint` / `ADMJoint::PrepareCalc`, particles `Emit` / `Simulate`, arena collision, objbase once verified.
  - Then the old queue: models, render, containers, Cocos, about 1,300 functions.
- **Document** each family's layout as C++ structs as it's rewritten; that feeds §5 step 9.

## Track D: tests and tooling
| # | Item |
|---|---|
| D1 | ✅ **done 2026-09-30** — Resolve repo resources from the executable's location (`/proc/self/exe`), so `soa` works from any directory. Today the master DB, seed save and gacha pools are only found from the repo root. One helper replaces the scattered `../../` lists. |
| D2 | ✅ **done 2026-09-30** — A committed synthetic seed save (sanitized id `LOCAL00001`, no personal data), so server tests run in fresh checkouts |
| D3 | ✅ **done 2026-09-30** — Flaky tests: `ui/settings-misc` (a bool result's upper bits), `screen/a2c-live`, the older `event/interpreter-fuzz` and `battle/manager-progress`. **Found:** `ui/settings-misc` was a test bug: the int getters (`GetEffectAlpha`, `GetResolution*`, volumes, ...) load 4 bytes whatever the stored length, so for the tests' 1..3-byte values the upper bytes are heap garbage past the block (now masked). The other three failed only before the JIT-invalidation fixes (a682455, 83857c8: a stale JIT block bypassed the test's stubs, e.g. `new` / `gDoAssert`) or, for `screen/a2c-live`, before the shared live check (69b141f) and its oracle's .rodata string match; no failure in 20× filtered runs, 3 `selftest_screens.py` runs and 2 full runs. The `crResourceElementDirectFile` crash in `gacha_session.sh` is a missing-resource path: the offline APKs lack `UI/etc2/gacha_*.csf`, so the script now defaults `SOA_DOWNLOAD_DIR`. |
| D4 | ✅ **done 2026-09-30** — `tutorial_session.sh` name entry: the typed name doesn't land (the player becomes "Fayt"); fix the timing and check the name |
| D5 | Housekeeping: remove merged worktrees (by hand, after checking each for unmerged work); push `linux-port` when the user asks |
| D7 | **Per-battle growth (found by A5, 2026-09-30):** RSS grows about 0.7 GB per battle, and guest CPU contexts accumulate (one per host thread per nesting depth, kept until the thread exits). The Sphere 211 session hit the 256-context limit (`FATAL: out of exclusive-monitor processor slots`) in its 3rd–4th battle. `kMaxProcessors` was raised to 1024 as a stopgap. Find the root cause (threads per battle that never exit? JIT levels never released? caches per battle?) and fix it. **Done (d7-leak):** each context cost ~22 MB (16 MB of it dynarmic's fast-dispatch table, now released), and the guest saw 32 host CPUs, so it ran 62 engine workers that reached 4-6 levels each. With `--guest-cpus` defaulting to 8, the session peaks at 102 contexts / 2.3 GB, down from 230 / 6.4 GB after four battles. Diagnostic: `SOA_MEMSTATS` (README "Memory diagnostics"). |
| D8 | ✅ **done 2026-09-30** (fc60d60; map in `port/src/README.md`). **Source reorganisation (the user asked, 2026-09-30).** Done after Wave 3, with no branches in flight.
- Split the flat `port/src/native/` (361 files) into subsystem folders, with generated translations in `gen/` subfolders and shared check and runtime code in `native/common/`.
- Update every include, the generator output paths and the doc references.
- Add a `port/src/README.md` map.
- `soa --list-native` must be identical before and after, and the full gate must pass.
- Then clean up the merged worktrees. |
| D6 | A `--guest-report` mode and a per-wave profile (`REMAINING.md` §5 step 1) |

## Wave 3 (started 2026-09-30 evening)
- C-3: readable objbase (148 verified bodies).
- C-5: readable render hot spots (`ShadowManager::ShadowCasterCulling`, the `AofObject` render path, `LightManager::MakeLightContext`), per `AUDIT-9-30.md`.
- C-6: InfoBase and containers as C++ templates over the element type, replacing the generator-shaped translations.
- B6: next families from a fresh profile (`CPartyManager`, the remaining battle glue, `CStageManager`, the result screens).
- B7: HLE overhead (GL / libc / pthread paths).
- A11: tower layout research.
- D3: flaky tests, plus the `CResourceManager::crResourceElementDirectFile` crash seen in a checked `gacha_session.sh`.

## Suggested order
The user asked (2026-09-30) to prioritise the readable rewrite (Track C) alongside Wave 1.

1. **Wave 1**, after A1 lands; about 7 agents, all low risk:
   - A2 with A8;
   - A3;
   - A4 with A7;
   - B1 (the shared live-check library);
   - D1 with D2 with D4;
   - **C-1:** readable rewrites of the dynamics hot path (`CollisionAndConstraint`, `ADMJoint::PrepareCalc`, `StandardIK`, `FUN_024226dc`), checked by the existing dynamics live check at 0 mismatches;
   - **C-2:** readable rewrites of particles `Emit` / `Simulate` and arena collision (`CCollisionField::Progress`, hit tests), checked by the existing particle and arena live checks.
2. **Wave 2:**
   - B2, B3 and B4 on the shared harness;
   - **C-3:** readable objbase once verified;
   - **C-4:** the old a2c queue by heat: models, render, containers;
   - A5, A6;
   - B5 as needed;
   - a new profile, and update `REMAINING.md`.
3. **Wave 3:**
   - B6, B7;
   - more Track C (Cocos, screens);
   - A11 research (tower layout).
4. **Later:** A9 world map, A10 multiplayer stand-in, then B8 and the §5 roadmap towards `--no-jit`.

## Verification
- **Every merge:** the gate above.
- **Track A items:** a session or session step with screenshots, plus unit tests.
- **Track B/C items:** differential selftests plus the live check at 0 mismatches over the restore, events and home sessions, then a profile before and after.
- **After each wave:** update `REMAINING.md` numbers.

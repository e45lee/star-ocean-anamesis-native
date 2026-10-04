# Test clients on Mesa's llvmpipe (software GL)

An experiment (2026-10-03, approved by the user): run the headless test clients (`soa`, `soa-emu`,
`soa-viewer`) on Mesa's software rasterizer llvmpipe instead of the host GPU. The WSL host GPU
(NVIDIA through Mesa's d3d12 driver and WSLg) failed three times that day under many concurrent GL
clients ("D3D12: Removing Device.", `glx: failed to create drisw screen`, a crash in
`libnvwgf2umx.so`), killing test clients that were otherwise fine.

**Status: opt-in; the default stays the host GPU.** Recommendation at the end.

## The switch

`SOA_SLOT_SOFTWARE_GL=1` (harness only; the programs read nothing new), in the slot pool
([`control/soaslot.py`](../control/soaslot.py), [`control/README.md`](../control/README.md)):

```sh
tools/gate.sh T1 --git-diff main --software-gl      # one switch for a whole gate run
SOA_SLOT_SOFTWARE_GL=1 tests/diff/run.sh gacha       # tests/diff, the sessions, smoke
SOA_SLOT_SOFTWARE_GL=1 port/scripts/home_session.sh build/port/soa OUT TMP
control/soaslot.py run --software-gl -- timeout -k 10 600 build/port/soa ...   # a hand-started client
```

Every client launcher goes through the pool: `soaslot.acquire()` (control/soadrive's runs,
control/run.py's sessions, tests/diff, smoke.py, tools/gate.py), `soaslot.py run` and the shell's
`soaslot_take` (the emulator and viewer scripts, selftest_resilient.sh). With the switch on, each puts
the variables below in the environment the clients inherit; a soadrive `Run` also applies them
itself (when its caller holds the slot) and notes `software GL: ...` in its milestones. Every client
then logs `I/gl: window framebuffer: ... OpenGL ES 3.2 Mesa ..., llvmpipe (LLVM 20.1.2, 256 bits)`
(the host GPU: `OpenGL ES 3.1 ..., D3D12 (NVIDIA RTX PRO 4000 Blackwell)`).

**Which variables select llvmpipe here.** The runtime's GL is SDL2-owned ES contexts through X11
EGL (`SDL_HINT_VIDEO_X11_FORCE_EGL`, runtime `app/sdl_gl.cpp`). WSL's GPU driver is Mesa's d3d12
gallium driver, which loads through the same "software" (drisw) path as llvmpipe and is picked by
`GALLIUM_DRIVER=d3d12` (this machine's `~/.profile` exports it). So:

| Environment (SDL X11 EGL, ES 3.x context) | Renderer |
|---|---|
| the profile's (`GALLIUM_DRIVER=d3d12`) | D3D12 (NVIDIA), ES 3.1 |
| + `LIBGL_ALWAYS_SOFTWARE=1` | still D3D12 |
| `GALLIUM_DRIVER=llvmpipe` (with or without `LIBGL_ALWAYS_SOFTWARE=1`) | llvmpipe, ES 3.2 |
| no `GALLIUM_DRIVER` at all | llvmpipe (WSL's Mesa picks d3d12 only when told) |
| `MESA_LOADER_DRIVER_OVERRIDE=llvmpipe` or `swrast` (profile's `GALLIUM_DRIVER` kept) | no context (`EGL_BAD_MATCH`) |

The switch sets `GALLIUM_DRIVER=llvmpipe` (overriding the profile) and `LIBGL_ALWAYS_SOFTWARE=1`,
and `LP_NUM_THREADS=4` unless the caller set one (below). `EGL_PLATFORM` / `SDL_VIDEO_X11_FORCE_EGL`
are not needed (and `SDL_VIDEO_X11_FORCE_EGL=0` would break the EGL emulation, docs/environment.md).

## Measurements

The development machine: 32 cores, 45 GB, WSL2, Mesa 25.2.8, LLVM 20.1.2. Other agents' clients
were running during most runs (load noted); hw = host GPU, sw = llvmpipe. Times exclude the wait
for a slot. Raw outputs: `/home/fish/.claude/jobs/ac4802d9/tmp/swgl-*` (not committed).

### Per client

| | hw | sw, `LP_NUM_THREADS` 32 (Mesa's default: one per core) | sw, 4 (the switch's default) | sw, 2 |
|---|---|---|---|---|
| CPU (average over the runs, % of one core) | 70 | 400 | 280 | 195 |
| threads | 49 | 164 | 50 | 42 |
| RSS | 1.5 GB | 1.5 GB (+0.1) | same | same |
| fps, home screen with the 3D character, load 20-28 | 56-59 | 33 | 31 | 32 (p10 17) |
| fps, home session, quiet machine (load ~10) | 59.5 | | 50-51 (p10 33-35) | |
| fps, smoke (menus), quiet | 59.4 | 54-59 | 59.4 | |

- llvmpipe's cost is the 3D scenes (the home character with the hair shader, battles, the summon):
  the 2D menus stay near 60 fps. A sw client costs 3-4 cores where a hw client costs 0.7.
- Fewer rasterizer threads (4, 2) gave the same frame rate as 32 for two thirds / half the CPU: the
  frame time isn't rasterizer-bound (the per-thread load was ~10% each with 32), so 4 is the
  default. `SOA_OFFSCREEN_PRESENT=1` (no X11 present) didn't change the frame rate either (30.8 vs
  25-33).
- **sw frame rates fall with machine load** (a hw client's barely do): 50 fps quiet, 30 at load 25,
  20-24 (p10 7-11) with 12 sw clients at load 45-56.

### Wall times (per run, excluding the slot wait)

| Test | hw | sw | |
|---|---|---|---|
| smoke | 183 s (twice) | 178-187 s (three times) | PASS both |
| tests/diff gacha shard, per target | 244-247 s | 249-253 s | PASS both; 296 s in the sw gate run |
| tests/diff seeded flow, per target | 401-426 s | 403-421 s | PASS both, run side by side |
| home session (control/soadrive, after main's consolidation), quiet machine | 365 s | 359-367 s | PASS both |
| home session (the old shell script, before it), load 20-28 | 397-399 s, PASS 2/2 | FAIL 7/7 (2-17 destinations missed, one of them in a gate run) | see Correctness |

Most of a run is the game's own waits (server round trips, scenes, timers), so a client at 30-50 fps
finishes in the same time as one at 60, as long as the machine isn't saturated.

### Concurrency

- **12 tests/diff runs at once on sw** (the full seeded, tutorial and event flows plus the battle
  shard; 11 sw clients at the peak, the pool's other slot another agent's hw client): every run
  PASS; load peaked at 47 on the 32 cores, MemAvailable bottomed at ~18 GB; fps median 31.7, p10 11
  (20 during the peak); tutorial 740-781 s per target (hw reference 740-810), seeded 408-443, event
  381-414, battle 310-322 (hw reference 282). tests/diff waits for log lines and resends taps, so a
  slow client passes.
- **T2 on sw, 12 slots** (`tools/gate.sh T2 --software-gl`; 12 sw clients for most of the run, no
  other agent's): load 43-56, MemAvailable down to 18.7 GB, fps median 23.9, p10 11.4 (66% of the
  samples under 30). Wall 1,865 s (the measured hw T2: 1,503 s). The full tests/diff PASS (1,860 s;
  hw 1,050), but 6 of 16 port sessions FAILed, every one on a milestone not reached in time
  (session:home `follow` not within 60 s, growth `BoostCharacter` not within 30 s, party
  `UpdateHome` not within 30 s, events and tower `MissionStart` not within 60 s, restore-missions
  `ホーム -> home`): taps on a client drawing 10-20 fps that didn't take.
- **T2 on hw, the same build, right after** (12 hw clients for most of the run, 1-6 of other agents'
  slots taken at times): every test PASS; load peaked at 13.7, MemAvailable 24 GB; fps median 59.5,
  p10 51.8 (3% under 30). Wall 1,550 s; the full tests/diff 1,544 s (its 9 runs queue behind the
  sessions for the 12 slots, so its wall time depends on the order they got them).
- **T2 on sw, 8 slots** (`SOA_SLOTS=8`; 4-8 sw clients plus 2-8 other agents' hw clients, about 6 on
  average): load up to 43, fps median 29.6, p10 14.6. Wall 2,879 s. 8 FAIL: sessions events, home,
  rental, growth, deepspace, tower, restore-missions, and the full tests/diff (one tutorial target:
  `UpdateTutorial(7) (home) not within 120 s`, the failure tests/TIERS.md saw with 20 hw clients).
  Fewer slots didn't help while the machine was shared: the sw clients' frame rate follows the
  machine's load, not the pool's size.

### T1-style coverage on sw

`tools/gate.sh T0 smoke session:home session:restore shard:<x> emu:seeded viewer:boot --software-gl`
(the representative per-change set; every client's log names llvmpipe):

| Build | Result | Notes |
|---|---|---|
| before main's soadrive consolidation (shard:gacha) | all PASS but session:home (the old shell script: 17 of the destinations missed after lost taps); wall 1,106 s | load to 27 with other agents' clients; T0's port selftest on llvmpipe PASS (91 s) |
| after it (shard:battle) | **20 PASS** (T0 included); wall 441 s; shard:battle 438 s (measured on hw: 280), smoke 186, session:home 368, session:restore 280, emu:seeded 300, viewer:boot 39 | 8 sw clients, load to 27; fps median 35.8, p10 15.4 |

## Correctness

- **tests/diff's screenshot comparisons** (port vs emulator, both on llvmpipe): PASS in every flow and
  shard run (gacha, seeded, tutorial, event, battle), with RMSEs in the hw runs' range (e.g. seeded
  port-server: 0.001-0.04 on the compared screens, as on hw). Packets and the end state compare
  equal as on hw.
- **smoke against the committed baselines** (`tests/smoke-base`, made on the host GPU): PASS
  unchanged. The two screens that are pixel-exact on hw (the character list, the closed detail)
  score RMSE 0.0012 by smoke's measure; the others score as on hw (title 0.015 vs 0.016, character
  menu 0.024 vs 0.024, detail 0.011-0.012 vs 0.012, other 0.031 vs 0.031; the animated home screens
  0.05-0.11 vs 0.04-0.06, limit 0.12). No new baselines are needed; candidates
  from llvmpipe runs are in `swgl-smoke-sw1/`, `swgl-m-smoke-sw/` (tmp, not committed).
- **sw vs hw side by side** (smoke's screens, same build): identical to the eye. Per pixel:
  RMSE 0.003-0.005 on the static screens; 34-47% of the pixels differ, all but 0.15-0.66% by at
  most 8/255; the largest differences (25-35/255) are single pixels on anti-aliased edges and
  gradients (rounding). The home screens differ by the animation (the character's pose, the mascot's
  line) as two hw runs do.
- The guest sees the host's strings: `GL_RENDERER` "llvmpipe (LLVM 20.1.2, 256 bits)",
  `GL_VERSION` "OpenGL ES 3.2 Mesa ..." and GLSL ES 3.20 (hw: D3D12, ES 3.1, GLSL ES 3.10). Nothing
  in the game's output depended on it in these runs.
- **Taps lost at low frame rates (fixed 2026-10-03).** The failing sessions missed a step after a
  tap that didn't take: e.g. the stamina dialog's 閉じる, tapped 3 s after the dialog was fully
  shown, left it open on sw (old home script), and in T2 on 8 slots the growth session's tap on the
  first gear of the 武器カスタム list, 4 s after the list was shown, didn't select it (38 fps on
  average then). The control layer's `tap:` was a touch down, 80 ms, touch up. The mechanism
  (decompiled): `Framework::CTouchPanel::Progress` folds one logic frame's touch records into one
  drag state (`Aska::TouchPanel::SetDragBegin` 0, `SetDragEnd` 2), and
  `CCocosDirector::InputProgress` drops an "ended" with no touch begun, so a down and an up read
  in the same frame (a frame or hitch longer than 80 ms) never press a button; the Back key
  (`PadDroid::m_bBack`) is a level sampled per frame. Now `tap:`, `drag:` and `back` are paced
  by the game's frames (runtime/README.md, "Scripted taps": the up 3 presented frames after the
  guest read the down, at least 80 ms; the next command waits for the release).
  - **Deterministic before/after** (`frame-delay:200`, 4.9 fps, via `--do` on smoke): the fixed
    80 ms hold (`input-pacing:0`) FAILs smoke at the login (60 taps resent, the home never
    reached); paced, smoke PASSes (each tap held ~500 ms, 3 frames).
  - **Sessions on sw, `SOA_SLOTS=8`** (home, growth, party, rental, events, tower,
    restore-missions; the parent build and this one at once, 14 sw clients queued on the 8 slots
    shared with another agent's T2, load to 26, fps median 38-42, p10 17-21): the parent build
    10 of 14 PASS over two rounds (FAIL: growth twice, EvolutionCharacter / LimitBreakCharacter
    not within the time; home twice, 21 and 2 destinations missed); the paced build 13 of 14 and
    then 9 of 9 (a third round, plus two extra party runs). Its one FAIL, party's swipe to set 2,
    came from the first version holding a swipe still for 3 frames before the up (the page
    didn't turn); a drag of up to 300 ms now releases right after its last move, as before.

## Recommendation

**Don't make it the default for gate runs; keep it opt-in.** The default (host GPU) passed T2 with
12 clients at load 14; llvmpipe failed 6-8 of T2's sessions at 8 or 12 slots.

- llvmpipe renders correctly: every tests/diff comparison and smoke's committed baselines pass on
  it, and its screens differ from the GPU's only by small rounding differences on edges and gradients. Correctness is not the
  problem.
- Its cost is CPU: 3-4 cores per client (with `LP_NUM_THREADS=4`: ~2.8) against 0.7 on the GPU, so 12
  clients load the 32 cores to 45-56 and the frame rate falls to 10-25 fps. The tests that wait for
  log lines and resend taps (tests/diff, smoke, the soadrive sessions' tap-until steps) still pass;
  sessions with a blind tap after a `wait:` lost taps at those rates and failed until taps were
  paced by frames (above).
- **When to use it:** when the host GPU is failing (D3D12 device removed, GLX/drisw screens not
  created, crashes in `libnvwgf2umx.so`): `tools/gate.sh ... --software-gl` keeps T0/T1 and
  tests/diff runs going. It held for a T1-style run (8 sw clients, all PASS) and for 12 tests/diff
  runs at once (all PASS).
- **Slots:** with the switch on, `SOA_SLOTS=6` machine-wide, not 12. Each sw client needs ~3 cores,
  so 8 plus a build or the other agents' clients saturate the 32 cores; a sw client's frame rate
  follows the machine's load (T2 at 8 slots with ~6 other hw clients failed as at 12). Measured to
  pass: 8 sw clients of a T1-style run at load 27; 3 on a quiet machine. Not measured: T2 at 6.
- **To make it a viable default** (if the GPU failures keep coming): taps are now independent of
  the frame rate (done, above); re-measure T2 on sw with `SOA_SLOTS=8`, and convert any blind tap
  that still fails there to a tap-until step.

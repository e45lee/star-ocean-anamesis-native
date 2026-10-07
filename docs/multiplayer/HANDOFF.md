# Multiplayer handoff: start here

This is for whoever adds co-op multiplayer to the local server. It assumes none of the study's context.

Written 2026-10-03 by agent `multiplayer-study`, branch `port/multiplayer-study`. The analysis with the evidence is [`../multiplayer.md`](../multiplayer.md); this page is the map, the state of play, and the traps.

## What is here

| Path | What |
|---|---|
| [`../multiplayer.md`](../multiplayer.md) | The analysis, every claim labelled [confirmed]/[run]/[inferred]: client architecture (§1), wire (§2), what a server needs (§3), options and the staged plan (§4), experiments (§5), screenshots |
| [`prototype/`](prototype/README.md) | A working Python lobby and relay (`mp_proto.py`) plus the scripts that ran two clients: `mp_client.sh`, `make_player2.sh`, `mp_drive.sh`, `open-multiplay.patch`, `lobby_listen.py`. **The executable spec for the real implementation.** |
| [`wire/`](wire/) | `gen_wire_tables.py` → `wire-tables.md` (every FunctionID, Set serializer address, fixed size, parameters) and `multiplay_wire.inc` (the same as a C++ table, ready for `server/net/gen/`) |
| [`decomp/`](decomp/) | Excerpts of the 235 decompiled functions the study relied on, by topic (`framing`, `lobby_messages`, `battle_messages`, `manager`, `ownership`, `ui_flow`, `ui_lambdas`, `mission_api`), `symbols.tsv` (address, topic, symbol), and `extract.py` to regenerate them |
| [`captures/`](captures/) | Decoded, sanitized logs: the lobby probe's CreateRoom, a full two-player session (room, start, barriers, MissionEnd), ~6 s of relay battle traffic from both clients, the ownership trace |
| [`screenshots/`](screenshots/) | 27 shots from both clients, host and guest, plus `contact-sheet.png`. Captions are in multiplayer.md §5 "Screenshots". |

## State of play (2026-10-03)

**Works with the prototype and two unmodified 3.7.0 clients (soa-emu, headless):**
- multiplayer opened by the server (`is_open_multiplay` = 1);
- create room, room list, automatch, room-id search dialog;
- join: both players are in the room with their names and characters;
- the host starts with fillers;
- `MissionStartPush` per player;
- a 2-stage battle with each client playing its own character: the stage barriers, Snapshot/Message forwarding, AIParameter to the host, the same damage numbers on both screens;
- `MissionEnd` → `MissionEndPush` per player, and each player's Mission Result page;
- a guest disconnect mid-battle: the host takes over and finishes.

**Not done (the real work):**
- **No server code.** The lobby and relay exist only as the Python prototype.
- **The API side is canned.**
  - MissionStartRes and MissionEndRes bodies are captured from single-player runs and patched (party and owner ids).
  - Nothing is charged or credited in any server state.
  - The real relay must run the backend's MissionStart and MissionEnd per player.
- **soa-server is single-player.** Every device gets `LOCAL00001` (server/README.md). The experiment ran **one soa-server per client** and made player 2 by editing a state DB (`make_player2.sh`).
- **Not exercised:**
  - rush combo (arbitration invented);
  - MissionContinue (not answered);
  - stamps (the picker crashes soa-emu);
  - ExitRoom / kick / CloseRoom flows;
  - 3-4 players;
  - LAN;
  - the `soa` port (only soa-emu was used).

## The host-assignment finding (and fix)

- **Symptom.** In the first two-client runs, **both clients showed all four characters tagged HOST**, and both sent behaviour and parameters for all player characters.
- **Cause.**
  - The client decides ownership by an **owner id per battle character**: `CPartyManager::IsMultiplaySendCharacter(i)` @013a4e48 compares CCharacterObject+0x1068 of character i with that of the character in the client's own slot.
  - That id comes from MissionStartRes `BattleParameter.PlayerCharacter[i].player_id` ([inferred]; the copy wasn't traced, but changing `player_id` changed the behaviour).
  - Both clients were the same seeded player, and the canned body gave all four characters that id.
- **Rule.**
  - **Slot** (EnterRoomResult; the creator gets 0) decides host-only work: enemies, fillers, hate merge, MissionFailed.
  - **Owner ids** decide which player characters each client drives, and the HUD's HOST/GUEST tag.
  - Each player must have a **distinct numeric player id**. The client puts its own in PlayerDetailInfo+0x6c. The MissionStartRes for the room must give each character its owner's id: the players' leaders their players' ids, the fillers the host's id.
- **Verified.** [`captures/ownership-trace.txt`](captures/ownership-trace.txt):
  - the host sends characters 0, 2 and 3 and enemies 4-8;
  - the guest sends only character 1;
  - the HUD shows HOST/GUEST correctly on both screens (screenshots 18-21).

## Open questions and hypotheses

| Question | What was tried | Next |
|---|---|---|
| Is CCharacterObject+0x1068 exactly `PlayerCharacter.player_id`? | Behaviour changed when the ids changed (run 4 vs 3) | Trace the copy: `CBattleUtility::CreateCharacter` @013f1598 (decomp/ownership.c; called from `CPartyManager::SetupCharacter_Local` @013a4cfc) → CreateCharacterInfo (party entry +0xa8) → the CPersonStatusInfo field; or a watchpoint on +0x1068 |
| How are fillers chosen ("ホスト、ゲストのパーティキャラクターで補充")? | Prototype: host's party only, skipping duplicate uids | Find the server's side in the client's party UI (`CMultiPlay3::Server_BattleStart`, the fill dialog's caller) or decide (d) |
| Rush-combo arbitration (what the relay puts in SyncStartRushComboRes: target, ok, ride, u32) | Invented values; never triggered in the short fights | Decompile `OnSyncStartRushComboRes` @015a3028 / `OnStartRushComboRes` @015a2d6c (decomp/manager.c) and play a longer fight to trigger a rush |
| UpdatePlayerListResult's s8 and u64, EnterRoomResult's last i32, AutomatchResult's trailing i32 | Zeros / count; the UI was fine | Read `CUIMatchingNotify::OnUpdatePlayerListResult` and `UpdatePlayerListEx` (decomp/ui_flow.c) |
| Reward rules: `Multi_Player_Number_2/3/4` (1 / 1.5 / 2), `host_bonus` (all 0), guest stamina | Master values read; no client logic | Server rules (a)/(d) in docs/server-rules.md |
| The room ready flags and `multiplay_force_start_time` (6), `lobby_opened_time_max` (10) | Not exercised | `IsEnableBattleStart` @01d055a4, `Server_UpdatePlayerStatus` @01d05618 |
| RoomInfo+0x424 (public/private): 0 shows 非公開 | Seen in the UI | Set it from RoomCondition+0x16e |
| Stamp picker crash in soa-emu (`CStampUI::GetCsfFilePath()+0x448`) | Seen once; reproducible by tapping スタンプ in the room | Probably a missing stamp asset (`master_stamp` 290 rows) or an emulator gap; check the port too |
| Do 3-4 players and LAN work? | No | Same prototype; up to 3 soa-emu fit the process budget |

## Pitfalls hit (read before driving clients)

- **No Ninja, no SHA-1 on 4001 and the relay.**
  - Reuse GameRPC's header scramble (`server/net/wire.cpp` `scramble_header`) but **not** `encode_packet` (it appends SHA-1) and not `PacketReader::next` (it expects SHA-1).
  - No session, no keys.
  - Only the five 0x80 mission messages are encrypted, with a fixed ChaCha20 key and nonce, counter 0 per message (multiplayer.md §2).
- **Ports and addresses.**
  - The client always connects the lobby to `<lobby host>:4001`. soa-emu and soa (`--server HOST`) redirect 4001 with `--lobby HOST:PORT` (`platform370/src/net_370.cpp`).
  - **The in-process port (`--server inproc`) turns the redirect off**, so it cannot reach a lobby today (multiplayer.md §4(d)).
  - The relay address is taken verbatim from RoomInfo (+0x42a host string, +0x428 u16 port) and is **not** redirected: give a literal reachable IP (127.0.0.1 locally, the LAN IP for LAN) and the real port.
- **The lobby socket is short-lived.**
  - The client opens it when the party is confirmed and sends nothing until 募集開始 / search / automatch.
  - It closes it right after the reply, and after EnterRoomResult.
  - **No reply in 61 s** → 通信が切断されました.
- **Automatch on Error** retries about once a second for 30 s, then shows "見つかりませんでした".
- **The room UI polls** UpdatePlayerList every 2 s per client: expect log spam.
- **MessageRes is Message minus the sender i32**, and every entry offset must drop by 4: offsets are from the body start (`GetMessageRes` @01594658).
- **Ids and accounts.**
  - Two clients against one unmodified soa-server are the same player (`LOCAL00001`).
  - A body's `Player` object overwrites the client's player state: in run 2 the guest showed "Fayt" after a canned MissionEndRes.
  - Bodies must be per recipient.
  - **Never** commit the seed's numeric player id: the captures here replace it with `<P1-id>`; player 2's synthetic id is 1000000002.
- **Seeding.** soa-server seeds its state DB on the first login, not at startup. `make_player2.sh` runs `--wire-tool session` to trigger it.
- **The shared phone.**
  - `mp_client.sh` links the pre-downloaded phone (`scripts/shared-phone.sh`, work/phone-3.7.0): about 100-150 s from start to the mission map.
  - Two clients start at once fine.
  - The client fetches small missing assets through small download dialogs; `mp_client.sh` taps through them.
- **Taps get lost** during transitions. A lost tap leaves the client on another screen: in one run the host landed in ルームIDで検索 instead of ルームを作成.
  - Use generous waits.
  - Screenshot after each step, and check the screenshots before assuming a step happened.
  - Battle screenshots every 1.8 s cover a whole 1-05 fight: about 25 s, two stages.
- **Process hygiene.**
  - Kill only the PIDs you started (`$!`, or `pstree -p` of the script's PID).
  - Never `pgrep -f` loops.
  - The first session-script variant left soa-server running after its `finish` (the trap didn't run from inside the HOLD loop); `mp_client.sh` kills its own PIDs on exit.
- **SOA_TRACE.**
  - `SendAIParameter` can't be traced (PC-relative prologue).
  - `PackCharacterParameter*` are called on every client every 300 ms, so they prove nothing about ownership.
  - `IsMultiplaySendCharacter` is the one to trace. It slows the host to about 10 fps; fine.

## Recommended implementation order (server/)

Follow the layout `docs/history/PLAN-readability.md` built (`server/src/README.md`) and the state conventions of `docs/history/PLAN-schema.md` (`server/src/state/README.md`).

1. **Wire** (new files in `server/net/`: a `multiplay/` folder, or `multiplay_wire.{h,cpp}`):
   - header reuse without SHA-1;
   - ChaCha20 (test it against RFC 7539 §2.4.2, as the prototype did);
   - struct codecs for PlayerInfo, PlayerDetailInfo, RoomCondition, RoomInfo and Message lists, with `static_assert` sizes (0x70, 0x480, 0x1e8, 0x450);
   - the FID table from `wire/multiplay_wire.inc`. Better: regenerate it in `tools/` next to `api_wire.py` and put the output in `server/net/gen/`.
   - **Tests:** a differential codec selftest against the client's own `Set*`/`Get*` (as `port/src/native/api/wire_test.cpp` does for GameRPC), plus round-trips of the captured bytes in `captures/`.
2. **Lobby listener** (a new `lobby.{h,cpp}` in `server/net/`, an option like `--lobby-listen`): the room table (in memory; rooms don't need persistence), CreateRoom, GetRoomList (filter by condition, room-id string, page), Automatch, CloseRoom (multiplayer.md §3.1).
3. **Relay listener** (a new `relay.{h,cpp}` in `server/net/`, `--relay-listen`, `--relay-host`):
   - slots (creator = 0);
   - the room phase;
   - barriers;
   - forwarding (with the MessageRes rewrite);
   - DisconnectNodePush;
   - rush-combo arbitration (§3.2).
   - Port `mp_proto.py`'s logic one message at a time.
4. **Several players per soa-server**: the prerequisite for the API side.
   - One player per device UUID. The bridge already gets the UUID; MissionEnd carries it too.
   - The cheapest is **one state DB per player** behind a session → backend map, keeping every `api/<domain>` single-player.
   - Schema: no shared tables are needed for co-op itself. Follow lists would need them later (the 相互フォロー filter).
   - Seed new players from the same seed with `LOCAL0000N` and a distinct synthetic numeric id.
5. **The co-op API** (`server/src/api/missions/`, a `multiplay` part, or `api/multiplay/`):
   - `start_room_mission(room)` → per-player MissionStartRes: the room's mission, stamina, `multi_player_count`, PlayerCharacter[4] with **owner ids** (the host rule above), each owner's statuses from the server's own rules.
   - `end_room_mission(uuid, battle_log)` → that player's MissionEndRes.
   - MissionContinue for the host.
   - MultiMissionRestart answered like MissionRestart.
   - Every rule labelled (a)-(d) in docs/server-rules.md.
6. **`is_open_multiplay`** behind a server flag (e.g. `--multiplay`), off by default. Keep the default game unchanged (the smoke test, the replay corpus).
7. **The port.** Honour `--lobby` in in-process mode, or run the listeners in-process. Later.

**Test strategy.**
- **Unit:** codecs (differential against the client), ChaCha20 vectors, the room and relay state machines, owner-id composition.
- **Session** (`emulator/scripts/multiplay_session.sh`, built from `prototype/mp_client.sh` + `mp_drive.sh`): one soa-server, two soa-emu, player 2 made by the server. Assert from the server's packet log and the relay log, in order:
  - `CreateRoom`, `GetRoomList`, `EnterRoom` ×2 (slots 0 and 1, distinct player ids);
  - `StartMultiplay`, `MissionStartPush` ×2;
  - `StartBattleStage` ×2 per stage;
  - `MissionEnd` ×2 with distinct UUIDs → both players credited in `tools/server_state.py`.
  - Screenshots of both clients at room, loading, battle and result.
  - **Ownership:** SOA_TRACE `IsMultiplaySendCharacter` on both clients; the host sends 0 plus fillers plus enemies, the guest only its slot.
  - A second variant kills the guest mid-battle: DisconnectNodePush, and the host still reaches the result.
- **Gates:** per CLAUDE/brief, the emulator checks run because `server/` changes; the default `emulator_session.sh` must stay green (multiplayer off by default).

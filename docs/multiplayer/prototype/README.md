# Co-op lobby/relay prototype (reference, not product code)

These scripts took two unmodified 3.7.0 clients (soa-emu) through a whole co-op mission. Each client ran against its own soa-server, and they shared one lobby and relay: create a room, list it or automatch, join, start, a 2-stage battle in sync, MissionEnd, and the Mission Result on both. Screenshots: [`../screenshots/contact-sheet.png`](../screenshots/contact-sheet.png). Start with [`../HANDOFF.md`](../HANDOFF.md); the analysis: [`../../multiplayer.md`](../../multiplayer.md).

Use it as the starting point and executable spec for the real lobby and relay in soa-server (multiplayer.md §3 and §4, M1-M3). The real ones belong in `server/net` (C++, the GameRPC framing code, the backend in process); this Python is only the reference.

| File | What |
|---|---|
| `mp_proto.py` | The lobby and relay: LobbyProtocol and BattleProtocol framing, fixed-key ChaCha20, rooms and slots, barriers, forwarding, composing MissionStart and MissionEnd. About 330 lines, Python 3 + `msgpack`. |
| `mp_client.sh` | One client: its own soa-server (with `open-multiplay.patch`) and a headless soa-emu with `--lobby` pointed at the prototype. It logs in, opens the 1-05 mission detail and holds. |
| `make_player2.sh` | Builds player 2's soa-server state: numeric id 1000000002, `LOCAL00002`, name Player2, party leader Ashton. |
| `mp_drive.sh` | The taps for host-room, guest-join and battle on two held clients, with screenshots of both at the same moments. |
| `open-multiplay.patch` | The one-line soa-server change that sends `FooterMissionInfo.is_open_multiplay` = 1 when `MP_STUDY_OPEN` is set. **Not committed to the server**; apply it to a scratch build. |
| `lobby_listen.py` | The first probe: logs whatever the client sends to the lobby port. It answers nothing, so the client times out after 61 s. |
| (moved) | The FunctionID-table generator is [`../wire/`](../wire/); the decoded run logs and the ownership trace are [`../captures/`](../captures/). |

## Running it

Everything runs from a clean checkout. Paths are repo-relative, outputs go to directories you give, and the process budget is two soa-emu.

```sh
# 1. a soa-server that opens multiplayer (scratch: revert afterwards)
git apply docs/multiplayer/prototype/open-multiplay.patch && scripts/build.sh --target soa-server
cp build/server/soa-server /tmp/soa-server-mp && git checkout server/src/api_home.cpp && scripts/build.sh --target soa-server
export SOA_SERVER=/tmp/soa-server-mp

# 2. the MissionStartRes / MissionEndRes bodies the relay serves (it fakes the API side, see below):
#    play 1-05 once single-player per player with soa-server --log-packets, and keep
#    <n>-MissionStartRes.msgp and <n>-MissionEndRes.msgp (emulator/scripts/emulator_session.sh does this for
#    LOCAL00001; for player 2, mp_client.sh with its state, then シングルプレイ開始 by hand / soactl)
B=/tmp/mp-bodies   # start-p1.msgp end-p1.msgp start-p2.msgp end-p2.msgp

# 3. player 2's account
docs/multiplayer/prototype/make_player2.sh /tmp/mp/player2.sqlite3

# 4. the lobby and relay, then two clients (each ~2-3 minutes to the mission detail)
python3 -u docs/multiplayer/prototype/mp_proto.py --lobby-port 47001 --relay-port 47002 \
    --start-body 0=$B/start-p1.msgp --start-body 1=$B/start-p2.msgp \
    --end-body 0=$B/end-p1.msgp --end-body 1=$B/end-p2.msgp > /tmp/mp/proto.log &
docs/multiplayer/prototype/mp_client.sh /tmp/mp/host 47001 &
docs/multiplayer/prototype/mp_client.sh /tmp/mp/guest 47001 /tmp/mp/player2.sqlite3 &
#    wait until both print HOLD, then:
docs/multiplayer/prototype/mp_drive.sh /tmp/mp/host /tmp/mp/guest /tmp/mp/shots
# 5. stop: rm /tmp/mp/host/HOLD /tmp/mp/guest/HOLD; kill the mp_proto.py PID
```

- **Tracing.** `SOA_TRACE='_ZN13CPartyManager24IsMultiplaySendCharacterEi'` in the clients' environment logs the ownership decisions ([`../captures/ownership-trace.txt`](../captures/ownership-trace.txt)).
- **Taps get lost.** A tap during a screen transition is dropped. Check `mp_drive.sh`'s screenshots, and redo a step with `control/soactl.py FIFO tap:X:Y` if a client is on another screen.
- **Known crash:** opening the スタンプ (stamp) picker crashes soa-emu in `CStampUI::GetCsfFilePath` (host SIGSEGV in the emulator; not investigated). Don't tap it.

## What it implements

- **Framing.**
  - The 24-byte scrambled header, the same as GameRPC.
  - **No SHA-1 trailer.**
  - Raw struct bodies.
  - Flags 0x80 → the body is XORed with ChaCha20 (RFC 7539; the client's fixed key and nonce; counter 0 per message). The implementation is checked against the RFC test vector.
- **Lobby (answers):**
  - `CreateRoom`: allocates room ids from 1001 and writes the id string into RoomCondition+0x14e (the UI shows it as ルームID).
  - `GetRoomList`: open rooms with 1-3 players, paged.
  - `Automatch`: the first open room, else an `Error`. The client retries about once a second for 30 s, then shows "見つかりませんでした".
  - `CloseRoom`, and `EnterLobby` (never sent by 3.7.0).
  - It does **not** filter by mission, condition or mutual follow.
- **Relay, answered by the relay:**
  - `EnterRoom`: the first free slot.
  - `UpdatePlayerList`.
  - `UpdatePlayerStatus`: also pushes the list to everyone.
  - `ChangePublicRoom`.
  - `ExitRoom`.
  - `StartMultiplay`: StartMultiplayRes to all, then one `MissionStartPush` per player after 1 s.
  - `StartBattleStage` / `FinishBattleStage`: barriers over the connected slots.
  - Rush combo: echo StartRushComboRes. Sync*: `ok`, target 4, ride 0, flag 1 (invented values).
  - `MissionEnd` → `MissionEndPush` to the sender.
- **Relay, forwarded:**
  - `Snapshot` → `SnapshotRes` to the others.
  - `Message` → `MessageRes` to the others, with the sender slot dropped and every entry offset reduced by 4.
  - `AIParameter` → `AIParameterRes` to slot 0.
  - `Stamp` → `StampPush` to all.
- **Disconnect:** a closed relay socket frees the slot and pushes `DisconnectNodePush(slot)` to the others. The host then plays that character and finishes the mission (screenshots 26-27).
- **The relay's state machine** (per room):

  ```
  CreateRoom(lobby) ─▶ room{id, cond, slots[4]=empty}
  EnterRoom ─▶ slot = first free (creator: 0) ─▶ EnterRoomResult(slot, PDI[4], n); others ◀ UpdatePlayerListResult
  StartMultiplay(slot 0) ─▶ all ◀ StartMultiplayRes ─(1 s)─▶ each ◀ MissionStartPush(present[4], its body)
  per stage: all StartBattleStage ─▶ all ◀ StartBattleStageRes(present[4]) … all FinishBattleStage ─▶ all ◀ FinishBattleStageRes
  each MissionEnd ─▶ that client ◀ MissionEndPush(its body)
  socket closed ─▶ slot freed; others ◀ DisconnectNodePush(slot)
  ```

## Who is host: the rule

There are three pieces, and the client needs all three to agree (multiplayer.md §1.7):

1. **Slot.** EnterRoomResult's slot is stored at CMultiplayManager+0x3d8, and slot 0 is the host. Every host-only path tests `slot == 0`: enemies, NPC fillers, the AI hate merge, MissionFailed. The relay gives the room's creator slot 0 and joiners 1..3.
2. **Owner ids.** Each battle character carries its owner's numeric player id. The id comes from MissionStartRes `BattleParameter.PlayerCharacter[i].player_id` and ends up in the character object at +0x1068 (inferred; the copy wasn't traced).
   - `CPartyManager::IsMultiplaySendCharacter(i)` @013a4e48 sends character i when its owner id equals the owner id of the character in the client's own slot, or, for the host (slot 0), when it is an enemy or NPC, or its player is disconnected.
   - `SetDisconnectPlayer` uses the same comparison.
   - The HUD's HOST / GUEST tag follows the same owner id: characters owned by slot 0's player are tagged HOST. **[run]**
3. **The player id in PlayerDetailInfo+0x6c.** The client fills it from its own login (`CopyForMultiplay`). The relay uses it as the owner id when it composes the party.

**The bug in the first runs.** Both clients were the seeded `LOCAL00001` player, with the same numeric id. So in the canned MissionStartRes, all four characters had one owner:
- **both** clients treated every player character as their own;
- both sent behaviour and parameters for all four;
- the HUD tagged all four HOST on both screens.

**The fix**, server-side, with no client change:
- player 2 gets its own id (`make_player2.sh`);
- the relay composes each player's MissionStartRes with `PlayerCharacter = [slot 0's leader, slot 1's leader, …, host fillers]` and `player_id` = the owner's id: the players' ids for their leaders, the host's id for the fillers.

Result **[run, `../captures/ownership-trace.txt`]**:
- the host sends characters 0, 2 and 3 and the enemies 4-8;
- the guest sends only character 1, its Ashton;
- the HUD shows Fayt's leader and fillers as HOST and Ashton as GUEST, on both screens.

## What it fakes or skips

- **The API side is canned.**
  - MissionStartPush and MissionEndPush come from bodies captured in single-player runs.
  - The relay only rewrites the recipient's player id and the party.
  - Nothing is charged or credited: stamina, rewards and drops don't reach either server's state.
  - The real relay must call the backend's MissionStart and MissionEnd per player (multiplayer.md §3.3).
- **The fillers** are taken from the host's party only, skipping uids already in the party. The real rule ("ホスト、ゲストのパーティキャラクターで補充") is unknown.
- **No MissionContinue** (logged, not answered). No `ForceWinBattleStagePush`, `RSSIPush`, room timers or kick handling beyond ExitRoomRes.
- **Rush-combo arbitration is invented.** It was not exercised in the runs.
- **No validation:** full rooms, closed rooms and mismatched missions aren't checked. One process, threads, no persistence.

## Known limits and bugs

- **Both players must use the same mission**, because the bodies are per player, not per room. The bodies' mission must match the room's (1-05 in the runs).
- **`UpdatePlayerListResult`'s s8 / u64 and the extra fields of the Sync*Res replies** are zeros or guesses.
- **The lobby keeps rooms forever**, including empty ones; `GetRoomList` and `Automatch` skip empty and full rooms.
- **Room privacy is ignored.** RoomInfo+0x424 is left 0, which the UI shows as ルーム:非公開.

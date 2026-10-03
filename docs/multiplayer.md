# Multiplayer (co-op battles): how the client did it, and how to bring it back

STAR OCEAN: anamnesis had real-time co-op: up to four players, each bringing one character, playing one mission together. This document rebuilds that system from the 3.7.0 client. It then says what a server must do to emulate it and how to make it playable here.

Written 2026-10-02 by agent `multiplayer-study`, as an investigation: no production code changed. It extends [online-server.md](online-server.md), whose multiplayer lines (§2 table, §3 "Pushes", §8 "Multiplayer") were written before this study; where they disagree, this document wins (see "Corrections" at the end).

**Labels**, as in online-server.md:
- **[confirmed]**: read from the 3.7.0 decompile, strings or data.
- **[run]**: also observed with the unmodified 3.7.0 client (soa-emu) against a prototype lobby and relay (§5).
- **[inferred]**: follows from names, call structure or data, but the code wasn't followed all the way.
- **[unknown]**: not recoverable from the client.

**Addresses** are Ghidra addresses in `work/libSOA-3.7.0.so` (ELF vaddr + 0x100000). Decompiles: `work/decomp/multiplayer-study-*.resolved.c` (`proto`, `frame`, `peer`, `lobbyser`, `battleser`, `mgr`, `lobby-*`, `battle-*`); rebuild them with `tools/decomp.sh`. Everything else the study produced is committed under [`multiplayer/`](multiplayer/), with [`multiplayer/HANDOFF.md`](multiplayer/HANDOFF.md) as the entry point for whoever implements this:
- the prototype lobby and relay and the scripts that ran two clients: [`multiplayer/prototype/`](multiplayer/prototype/README.md);
- the screenshots: [`multiplayer/screenshots/`](multiplayer/screenshots/) and [`contact-sheet.png`](multiplayer/screenshots/contact-sheet.png);
- decoded captures: [`multiplayer/captures/`](multiplayer/captures/);
- the FunctionID tables and their generator: [`multiplayer/wire/`](multiplayer/wire/);
- the decompile excerpts with `symbols.tsv`: [`multiplayer/decomp/`](multiplayer/decomp/).

## Summary

- **Three connections.** The game RPC (443, encrypted) stays as it is. Two more connections use the same TCP RPC stack:
  - the **lobby**, `MultiplayRPC::LobbyProtocol` on `<lobby host>:4001`, for rooms: create, list or search, automatch, close;
  - a **battle relay**, `MO::BattleProtocol`, at the host:port that the lobby writes into each room's `RoomInfo`. It handles everything inside a room: enter and leave, the player list, ready, start, and then the whole battle.
- **The wire is simpler than GameRPC.**
  - It uses the same 24-byte scrambled header.
  - There is **no SHA-1 trailer and no Ninja cipher**. Bodies are raw C structs.
  - Five mission messages are XORed with **ChaCha20 under a key and nonce hard-coded in the client**.
- **No authentication on these connections.** **[confirmed]**
  - No session key or token is sent. Players are identified by the PlayerInfo they send and, for MissionEnd, by the device UUID.
- **The relay is a small game server, not a dumb pipe.**
  - It assigns the slots (0 = host).
  - It runs the stage barriers and arbitrates rush combos.
  - It **runs the API for the mission**: MissionStart and MissionEnd are not sent by co-op clients over GameRPC. Instead:
    - the relay pushes each player a MissionStartRes body (`MissionStartPush`);
    - each client sends its battle log to the relay (`MissionEnd`) and gets its MissionEndRes back (`MissionEndPush`).
- **Simulation is distributed and owner-authoritative.**
  - Each client simulates the whole battle.
  - Each client sends events and 300 ms parameter updates for the characters it owns: its own player character.
  - The host also owns the enemies, the NPC fillers and disconnected players' characters.
  - There is no lockstep and no host migration.
- **It already runs.** A ~330-line Python prototype lobby and relay ([`multiplayer/prototype/`](multiplayer/prototype/README.md)) took **two unmodified 3.7.0 clients** through the whole loop: soa-emu, each against its own soa-server with `is_open_multiplay` = 1, playing as two distinct players (host Fayt leading 渚のマリア, guest Player2 leading Ashton). **[run]**
  - Create a room, list it or automatch, join, start.
  - A 2-stage battle with each client playing its own character. Both screens show the same damage numbers at the same moments (screenshots 18/19).
  - Both clients reach their own Mission Result screens.
  - The MissionStart and MissionEnd bodies were canned per player (§5).
- **Who is host** (§1.7). Slot 0 from the relay **plus distinct player ids**.
  - The client groups battle characters by their owner's numeric player id (`PlayerCharacter[i].player_id`).
  - With two clients of the same player, both treat every player character as their own and all four are tagged HOST.
  - The relay must give each character its owner's id. This is fixed and verified (§5, screenshots).
- **Recommendation.**
  1. Lobby and relay as listeners inside `soa-server`.
  2. A soa-server that can serve several players, which today it cannot: every device is `LOCAL00001`.
  3. The relay calls the in-process backend for MissionStart and MissionEnd.
  - Staged plan and estimate: §4. About 2-3 agent-days to two real instances with real rewards. Most of the work is in the multi-player state, not the protocol.

## 1. The client's multiplayer architecture

### 1.1 Classes

| Class | Role | Evidence |
|---|---|---|
| `CMissionMenu` | Mission select. Its multi buttons call `ToMultiUI(eMode, cb)` @01ce6c1c. The buttons are `Button_multi` (mission detail: マルチプレイ開始), `Button_planet_multi` (この惑星のマルチプレイに参加), `Button_event_multi`, `Button_allplanet_multi` and `Button_automatching`. | [confirmed] |
| `CMultiPlay3` (`Game\UI\MultiPlay3.cpp`, 0xcbd0 bytes) | The multiplayer UI and its state machine: `StateInit` @01d00494, states 0..0x10, lambdas per state. It holds the room data (`tRoomData` at +0xb950) and the mode (+0xb728). | [confirmed] |
| `CUIMatchingNotify` (0x380) | Adapts both callback interfaces, `IMatchingNotify` (lobby) and `IMultiplayNotify` (relay), to `std::function` slots in CMultiPlay3. | [confirmed] |
| `CMultiplayManager` (0x3f8, singleton) | Owns `MatchingClient` (+0x40, the lobby `TARPCPeer<LobbyProtocolProxy>`) and the battle `TARPCPeer<BattleProtocolProxy>` (+0x48). In battle it runs `Progress` @015a43b8: parameter flushes, AI hate, barriers, rush combo. | [confirmed] |
| `IMultiplayManagerBase` / `TMultiplayManager<BattleProtocolProxy>` | Generic replication: a message queue (`SendMessages_`) and a snapshot store with full-then-diff images (`SendSnapshot_`, `FlushSendSnapshot` @022f7934). Both are flushed every 300 ms (`Init(300, 300)` @022f7540). | [confirmed] |
| `CBASMessageManager` + `CFieldMessage_*::SerializeMultiplay` | Battle events as replicated messages. There are 30 kinds: the CreateBehavior_* family (Move, MoveTo, NormalAttack, Skill, Magic, Guard, Avoid, Damage, Down, Abnormal, ExAttack, Order, Idle) and Behavior_CancelAction, BlowAway, ComboPlus, StartAssistSkill, StartFactor, StartTensionMaxMode, StartRushComboSetHeatUpBonus, ReceiveRecover, RequestRepop, RequestTrans(Sync), BunkerOrderBomb, plus the `Multiplay_*` parameter messages CharacterParameter, DamageUIParameter, SystemParameter and BattleTime. | [confirmed names] |

### 1.2 Phases and screens

These are the screens seen in the two-client run, with the code behind each.

1. **Mission detail.** It shows シングルプレイ開始 and **マルチプレイ開始** side by side. The mission map has a planet-wide この惑星のマルチプレイに参加.
   - `ToMultiUI` copies the selection into CParameterUI and creates `CMultiPlay3` with `InitializeEx(mode)` @01d041a4. **[confirmed, run]**
   - `ToMultiUI` stores planet +0x150, area +0x154, mission id +0x1a0, name +0x158 and party slot +0x1b0.
   - The modes are 0..8. The even "free" variants (2, 4, 6, 8) take area and planet from the room instead of the selection.
2. **"マルチプレイの遊び方を選択してください"** offers ルームを作成 / ルームに参加 / ルームIDで検索 / 戻る. No network traffic yet. **[run]**
3. **Party select.** You pick a party, and its **leader** is the character you bring.
   - Host: 決定.
   - Guest: 相互フォローのルームを検索 / ルームを全検索 / オートマッチング. **[run]**
4. **Lobby connect.**
   - `Server_InitializeCommon` @01d07f4c calls `CMultiplayManager::Initialize(lobbyHost, 4001, notify)`, then `InitMatchingClient` @015a3c34. It is TCP with keep-alive (1, 5, 6) and a 90 s UI timeout (+0xb920 = 0x5a).
   - **The client sends nothing on connect.** There is no EnterLobby and no handshake (`TProtocolSuite<LobbyProtocol>::Open` @015b50fc only checks flags). **[confirmed, run]**
5. **Host: ルーム作成.** This screen has slots 2-4 marked "フリーロールで募集" (recruit any role), ルーム:公開/非公開, a comment (30 characters), 相互フォロー限定で募集する and 募集開始.
   - 募集開始 → confirm → `Server_CreateRoomHost` @01d09868 → **CreateRoom**(PlayerInfo, RoomCondition).
   - The CreateRoomResult handler @01d1a588 calls `RoomInfo2RoomData`, then `InitBattleRPCClient(RoomInfo+0x42a host, RoomInfo+0x428 port)`, then **EnterRoom**(PlayerDetailInfo, RoomInfo+0x44c room id) on the relay. **[confirmed, run]**
   - With no reply, the client gives up after 61 s ("通信が切断されました") and closes the socket. **[run]**
6. **Guest: ルーム一覧.**
   - **GetRoomList**(PlayerInfo, cond, 0, 50) lists the rooms. Room-ID search puts the id string into RoomCondition+0x14e; **Automatch** returns one room.
   - Tapping a FREE slot of a room joins it. The lambda @01d1eb28 calls `InitBattleRPCClient(room+0x42a, room+0x428)`, then EnterRoom. **[confirmed, run]**
7. **After EnterRoomResult**, the client **closes the lobby connection** (`MatchingClient::ResetPeer`). Everything from here on uses the relay. **[confirmed, run: the lobby socket closed right after CreateRoomResult / GetRoomListResult]**
8. **In the room (メンバー募集中 / ルームに参加).**
   - Each client polls **UpdatePlayerList** every 2 s. **[run]**
   - Each client sends **UpdatePlayerStatus**(PDI, ready) when its party or readiness changes (`Server_UpdatePlayerStatus` @01d05618).
   - The host can send **ChangePublicRoom**, **ExitRoom**(1, slot) (kick, `Server_BanExitRoom`), **CloseRoom** (on the lobby) and stamps.
   - The room id is shown (ルームID: 1001) with クリップボードにコピー.
   - The host's **バトル開始** is disabled until a second player is in the room. The guest sees "ホストの開始を待っています". **[run]**
9. **Start.**
   - The host's `Server_BattleStart` @01d05d00 shows **"パーティメンバーが2人不足しています。ホスト、ゲストのパーティキャラクターで補充しミッションに出撃します"** with 2 players: the empty slots are filled from the host's and guests' parties. **[run]**
   - Then **StartMultiplay** → every client gets **StartMultiplayRes**(PDI[4], n) → `CPhase_Battle` → `InitMultiplayManager(PDI*)` @015a7cec. **[confirmed, run]**
10. **Battle.**
    - The loading screen shows the members with 準備中 until **MissionStartPush**.
    - Per stage: **StartBattleStage** → Res barrier → play (Snapshot / Message / AIParameter / Stamp / rush combo) → **FinishBattleStage** → Res barrier.
    - After the last stage, each client sends **MissionEnd** and gets **MissionEndPush**. **[confirmed, run]**
11. **Result.** The usual Mission Result pages, with 再戦 (rematch) and OK. The relay connections close after the result. **[run]**

### 1.3 What turns multiplayer on

- **`FooterMissionInfo.is_open_multiplay`.** This is the switch. The server's player responses carry it (CParameterManager+0x1ac8). **[confirmed, run]**
  - `CParameterUtility::IsOpenMulti(bool)` @01839aa8 returns it. With arg = true it also needs `view_status` bit 4 (CParameterManager+0xe08).
  - Its callers are `CMissionMenu::CreateMissonList` / `ShowState` / `Setup` and `CTutorialManager::GetViewTutorial` (tutorial 5 is shown only when multi is open).
  - With 1, the multi buttons appear and work. Our server sends 0 (`server/src/api/player/home_footer.cpp`, rule (d)).
- **The lobby host.** It is `ServerSelector::pServerAddressLobby` @015fa1f8: the lobby override (selector+0x20), else the game host. **[confirmed]**
  - The override comes from the **NoLoginStart** response's `data.LobbyPath`. Handler @018c459c → `IServerSelector::SetLobbyServer(LobbyPath)` at site 018c48d4.
  - **The port is fixed at 4001** (`Server_InitializeCommon` passes 0xfa1).
  - `LobbyProxyPath/Port` and `BattleProxyPath/Port` in the API schema have **no readers** in 3.7.0. **[confirmed]**
- **The relay address** comes only from the lobby's RoomInfo (host string at +0x42a, u16 port at +0x428). The client resolves the host itself. **[confirmed, run]**
- **Master data** (3.7.0 DB):
  - `master_global`: `lobby_opened_time_max` = 10 (`CMultiPlay3::GetLobbyOpenedMaxTime` @01d096b4), `multiplay_force_start_time` = 6, `Multi_Player_Number_2/3/4` = 1 / 1.5 / 2.
  - `master_battle_global`: `Battle_Multi_HpRate_2/3/4` and `Battle_Multi_DamageRate_2/3/4` = 10 / 20 / 30. These are the client-side scaling of enemy HP and damage by player count. **[confirmed values; consumers not traced]**
  - `master_mission.multi_ng` is NULL in all 613 rows, so every story mission allows multi. `master_event_mission.multi_ng` = 1 for 101 of 1,803 event missions.
  - `master_mission_drop.host_bonus` and `master_campaign_drop.host_bonus` exist but are 0 or NULL everywhere. `master_mission_stage.multi_rate_cut` = 1 for 3 rows.
  - MissionStartRes's `MissionParameter.multi_player_count` (docs/api.md) is the server's side of this.
- **Who is host.** The relay assigns slots in EnterRoomResult; slot 0 is the creator (inferred from the UI and from the host-only code paths, which test `slot == 0`). The mission menus also set the local KVS key `BAS:IsHost`, which `CUIUtility::IsMultiplayHost` reads (pause menu Continue, Order). **[confirmed key; slot-0 rule inferred]**

### 1.4 LobbyProtocol (port 4001)

FunctionIDs come from `LobbyProtocol::GetFunctionName` @022fadec (`proto` decompile). They agree with the FIDs the `Set*` serializers store to +0x30, and `LobbyProtocoledData::Deserialize` @022f8b64 accepts exactly these 13; anything else gives -0x3b8. The table was generated by [`multiplayer/wire/gen_wire_tables.py`](multiplayer/wire/README.md) (output: `wire-tables.md`, and `multiplay_wire.inc` for C++), the same way `tools/api_wire.py` builds the GameRPC tables.

Offsets are from the packet start: the body begins at +0x18. Sizes are whole packets. **[confirmed; run for CreateRoom, CreateRoomResult, GetRoomList, GetRoomListResult]**

| Message | FID | Dir | Body | Size |
|---|---|---|---|---|
| CreateRoom | `6a1b49a5` | C→S | PlayerInfo @18, RoomCondition @88 | 0x270 |
| CreateRoomResult | `eac42001` | S→C | RoomInfo @18. There is no status field; failures are kError. | 0x468 |
| GetRoomList | `2ddf640d` | C→S | PlayerInfo @18, RoomCondition @88, i32 begin @270, i32 end @274 (the client sends 0/50 and 0/10) | 0x278 |
| GetRoomListResult | `cc88678c` | S→C | u32 n @18, RoomInfo[n] @1c, i32, i32 | 0x24 + n·0x450 |
| Automatch | `e3a9a528` | C→S | PlayerInfo @18, RoomCondition @88 | 0x270 |
| AutomatchResult | `1fed00e2` | S→C | i64 Status @18, RoomInfo @20, i32 @470 | 0x474 |
| CloseRoom | `efe1edb6` | C→S | i32 room id @18, u32 0 @1c | 0x20 |
| CloseRoomResult | `e8fbdaaa` | S→C | i64 Status @18 | 0x20 |
| EnterLobby | `fb5d0d73` | C→S | PlayerInfo @18. **Never sent by 3.7.0** (no caller). | 0x88 |
| EnterLobbyResult | `4e466d87` | S→C | i64 Status @18 | 0x20 |
| UpdateRoomInfo | `a8efdd88` | C→S | RoomInfo @18. **Never sent** (no caller). | 0x468 |
| UpdateRoomInfoResult | `6b177840` | S→C | RoomInfo @18 | 0x468 |
| Error (ProtocolError) | `05aed673` | S→C | i64 Status @18, u32 failing FID @20 (shared with GameRPC and BattleProtocol) | 0x24 |
| (Invalid) | `7b1a9377` | — | — | — |

- Results carry no request id. `LobbyProtocolProxy::DispatchNotify` @021fb124 dispatches by FID.
- The header counter is echoed in our prototype; the client doesn't check it.

### 1.5 BattleProtocol (the relay)

There are 47 FunctionIDs plus kInvalid (`BattleProtocol::GetFunctionName` @0159afb0). `BattleProtocoledData::Deserialize` @01592760 accepts exactly these. Bodies are given from the body start (+0x18). "0x80" marks the five ChaCha20 messages (§2).

**Room phase** (these room messages live in BattleProtocol, not LobbyProtocol):

| Message | FID | Dir | Body | Size |
|---|---|---|---|---|
| EnterRoom | `43610d78` | C→S | PlayerDetailInfo, i32 room id | 0x49c |
| EnterRoomResult | `f6dec31d` | S→C | i32 slot, i64 Status, PDI[4], i32 player count (`GetEnterRoomResult` @015947fc) | 0x1228 |
| UpdatePlayerList | `bd96f882` | C→S | empty (polled every 2 s) | 0x18 |
| UpdatePlayerListResult | `a629dd36` | S→C | PDI[4], u16 count, s8, u64 | 0x1223 |
| UpdatePlayerStatus | `3764a958` | C→S | PDI (with +0x68 = slot), s8 ready | 0x499 |
| UpdatePlayerStatusRes | `5e3b82b4` | S→C | i64 Status | 0x20 |
| ChangePublicRoom / Res | `d4c82eca` / `d0a58e6d` | C→S / S→C | s8 / i64 Status | 0x19 / 0x20 |
| ExitRoom | `f2d53301` | C→S | u32 ExitType (< 3: 0 = leave, 1 = kick), i32 slot | 0x20 |
| ExitRoomRes / ExitRoomPush | `44ac9b5c` / `e5c49b5a` | S→C | u32 ExitType | 0x1c |
| StartMultiplay | `aeb31eca` | C→S (host) | empty | 0x18 |
| StartMultiplayRes | `948b0716` | S→all | PDI[4], u16 count. An entry with +0x6c ≠ 0 and +0x0 ≠ 0 marks that slot connected. | 0x121a |

**Battle phase:**

| Message | FID | Dir | Body | Size |
|---|---|---|---|---|
| MissionStartPush (0x80) | `399501b0` | S→each | u8 present[4], u32 len, MissionStartRes ASON → `CApiNotify::OnMissionStart` | 0x20 + len |
| StartBattleStage | `98905d95` | C→S | empty | 0x18 |
| StartBattleStageRes | `0f074e01` | S→all | u8 present[4] | 0x1c |
| FinishBattleStage / Res | `b24434d1` / `7309d699` | C→S / S→all | empty | 0x18 |
| ForceWinBattleStagePush | `8566caa5` | S→C | empty → `CBattleManager::ForceWinMultiBattle` @012c57a8 | 0x18 |
| Snapshot / SnapshotRes | `e0423298` / `3712ac8e` | C→S / S→others | u32 len, bytes (full image, then diffs) | 0x1c + len |
| Message | `c1f33acc` | C→S | i32 sender slot, u32 n, n × Message{u32 offset (from the body start), pad, u32 size, pad}, payloads (≤ 0x80 each, 4-aligned) | var |
| MessageRes | `57faa296` | S→others | the same **without the sender**: u32 n, entries, payloads. Offsets are again from the body start (`GetMessageRes` @01594658). | var |
| AIParameter / Res | `929765c3` / `16287e9b` | guest→S / S→host | u32 n, n × HateParameter{offset, i32 count, i32 player slot}, EnemyHate{i32 enemy slot, f32 hate} arrays | var |
| Stamp / StampPush | `a406ad38` / `38c5438d` | C→S / S→all | u32 stamp id / i32 slot, u32 id | 0x1c / 0x20 |
| StartRushCombo / Res | `bad35e28` / `62cd4997` | C→S / S→all | s8 slot (< 4), s8 target (4..11), f32 / s8, s8 | 0x1e / 0x1a |
| SyncStartRushCombo / Res | `a6fd1715` / `ebfee137` | C→S / S→all | s8 slot, u8 ok, f32 / s8, s8, u8 ok, u8 ride, f32, u32 | 0x1e / 0x24 |
| SyncFinishRushCombo / Res | `0214d5cf` / `bcacdd91` | C→S / S→all | f32, i32 / f32, i32, u8 | 0x20 / 0x21 |
| MissionEnd (0x80) | `8312a64c` | C→S (every player) | char uuid[36], i32 DeviceType, u32 len, CBattleLogInfo ASON (≤ 0x1000) | 0x44 + len |
| MissionEndPush (0x80) | `e2d23280` | S→that player | u32 len, MissionEndRes ASON → `CApiNotify::OnMissionEnd` | 0x1c + len |
| MissionContinue (0x80) | `755cba3d` | C→S (host) | char uuid[36], i32 DeviceType, u8 | 0x41 |
| MissionContinueRes (0x80) | `40db9f93` | S→C | u32 len, ASON → `CApiNotify::DeserializeToInfo` | 0x1c + len |
| DisconnectNodePush | `a2667cb1` | S→C | i32 slot, i32 → `CStageManager::SetDisconnectPlayer` | 0x20 |
| RSSIPush | `440ed5b8` | S→C | f32[4] (per-slot signal strength for the UI) | 0x28 |
| Error | `05aed673` | S→C | i64 Status, u32 FID | 0x24 |
| Reconnect | `b1533261` | (C→S) | i32 slot. **Never sent by 3.7.0.** | 0x1c |
| RequestProxy / Result | `f8697e7f` / `5528c22a` | (C→S) / S→C | u32 len, bytes, u16 port / i64 Status. **Never sent.** | 0x1e + len / 0x20 |
| Packet / PacketRes | `febe96fc` / `535410ce` | — | u32 n, n × Message, u32 blob len, blob, payloads. **Never sent.** | var |
| DebugMessage / Res | `10ce4f8f` / `c478bdba` | — | u32. **Never sent.** | 0x1c |

- "Never sent" means: no direct call, PLT call or GOT relocation reaches `Send<Name>` in the 3.7.0 lib (full disassembly scan). Reconnect and RequestProxy look like a planned or removed proxy/reconnect path. **[confirmed]**
- Several FIDs equal GameRPC FIDs. For example, `kMissionEnd` = `8312a64c` is the GameRPC MissionEnd request's FID, and `kError` = `05aed673` everywhere. So FIDs are hashes of the name, shared across the protocols. **[confirmed by equality]**

### 1.6 Structs

All are packed C structs, memcpy'd. **[confirmed offsets; field meanings partly inferred]**

**PlayerInfo (0x70)** is the first 0x70 bytes of PlayerDetailInfo. The client always passes `&PDI` where a PlayerInfo is expected. It is filled by `CMultiPlay3::Server_CreatePlayerInfo(…, partySlot)` @01d06348 and `CParameterPlayer::CopyForMultiplay` @017f856c.

| Off | Field |
|---|---|
| +00 | u64 leader character uid |
| +08 | u32 |
| +0c | u32 party-set id |
| +10 | u32 role hash |
| +14 | u32 role master value (+0x5a8) |
| +18 | u32 |
| +1c | i32 resource version |
| +20 | u32 |
| +24 | u32 mastery talent id |
| +28 | u32 mastery role id |
| +2c | u16 level |
| +2e | u16 0 |
| +30 | u8 rare-7 flag |
| +31 | char[0x30] player name |
| +61 | galaxy-pass flag |
| +62 | stats-maxed flag |
| +63..+66 | small flags; +65 is the favor level |
| +68 | u32 **room slot 0..3** (0 at create; server-assigned) |
| +6c | u32 **numeric player id** (non-zero = occupied) |

**PlayerDetailInfo (0x480)** = PlayerInfo plus the battle loadout:
- 3 × 0xc0 entries @0x74..0x2b4, each with a 0x80 string;
- the weapon @0x2b0 / 0x2b4;
- gear slots @0x2c4..;
- the support character @0x2dc..0x2e4;
- stats @0x2e8..0x334;
- u32[≤ 0x50] @0x33c;
- flags @0x47c / 0x47d.

It carries no session token.

**RoomCondition (0x1e8).** `Server_CreateRoomContdition` @01d06150 memsets it to 0 and sets defaults of -1 meaning "any".

| Off | Field |
|---|---|
| +08 | u32 type (1 = area mission) |
| +0c | planet id |
| +10 | area id |
| +14 | mission id |
| +18 | u32 bool |
| +20/+24/+28 | recruited role for slots 1..3 |
| +12c | u16 player rank |
| +12e | char[0x20] |
| +14e | char[0x20] **room-id string** (search key, shown as ルームID) |
| +16e | u8 private |
| +16f | char[] comment (UTF-8; the run's よろしくお願いします！ was there) |

**RoomInfo (0x450).** Read by `RoomInfo2RoomData` @01d07cc4.

| Off | Field |
|---|---|
| +000 | PlayerInfo[4] (a slot is occupied when +0x6c ≠ 0) |
| +1c0..+238 | unknown |
| +238 | RoomCondition |
| +420 | u32 |
| +424 | u8. The UI shows 非公開 when it is 0 (CParameterUI+0x1cf = !x). **[run]** |
| +428 | u16 **relay port** |
| +42a | char[0x22] **relay host** |
| +44c | i32 **room id** (EnterRoom and CloseRoom use it) |

### 1.7 Authority and timing

- **Slots.** Each client keeps its own slot at CMultiplayManager+0x3d8 (from EnterRoomResult) and per-slot connected flags at +0x3dc[4] (from StartMultiplayRes; cleared by DisconnectNodePush). Party indices 0..3 are the players and 4..11 the enemies. **[confirmed]**
- **Ownership** (`IsMultiplaySendCharacter` @013a4e48). **[confirmed]**
  - Every client owns its own player character.
  - **The host (slot 0) owns** the enemies, the NPC fillers and the characters of disconnected players.
  - `CBASMessageManager::AssortMessage` @014b6314 sends behaviour messages only for owned characters.
- **Who is host, and the owner-id rule.** **[confirmed code + run]**
  - The host is the client whose slot (CMultiplayManager+0x3d8, set from EnterRoomResult) is 0. Every host-only path tests that.
  - But ownership of the **player** characters is decided by an **owner id**. `IsMultiplaySendCharacter(i)` compares the int at CCharacterObject+0x1068 of character i with that of the character in the client's own slot. A match means "mine". Otherwise the character is the host's when it is an enemy or NPC, or its player is disconnected (+0x3dc[i] = 0). `CPartyManager::SetDisconnectPlayer` uses the same comparison.
  - The owner id is the character's `player_id` from MissionStartRes `BattleParameter.PlayerCharacter[i]`. This is [inferred] from the run, because the copy into +0x1068 wasn't traced.
  - The battle HUD's per-character **HOST / GUEST** tag follows it: a character is tagged HOST when its owner is slot 0's player. **[run]**
  - **Consequence.** Two clients logged in as the same player (both `LOCAL00001`), or a MissionStartRes that gives every character one `player_id`, make **every client own every player character**: both send behaviour and parameters for all four, and every character is tagged HOST on both screens. That is what the first two-client runs showed (all four tagged HOST).
  - **The server-side fix:**
    - each player has its own numeric id (it reaches the relay as PlayerDetailInfo+0x6c, from the client's login);
    - the relay composes MissionStartRes with `PlayerCharacter = [slot 0's leader, slot 1's leader, …, host fillers]`, each `player_id` = its owner's id (the host's for fillers).
  - **Verified** ([`captures/ownership-trace.txt`](multiplayer/captures/ownership-trace.txt), SOA_TRACE of `IsMultiplaySendCharacter`):
    - the host sends characters 0, 2 and 3 and enemies 4-8;
    - the guest sends only character 1;
    - the guest alone sends AIParameter;
    - the HUD tags Ashton GUEST and the rest HOST on both screens (screenshots 18-21).
- **What is replicated.**
  - Behaviour events (Message): moves, attacks, skills, damage reactions…
  - Every ≥ 300 ms (`CMultiplayManager::Progress` @015a43b8): **CharacterParameter** (16 bytes per player, 8 per enemy), which is how enemy HP comes from the host, and **DamageUIParameter** (≤ 12 × 8 bytes).
  - **Host only:** SystemParameter and BattleTime.
  - **Guests, every 2 s:** **AIParameter** (their hate on each enemy), which only the host applies (`OnAIParameterRes` @015a3670): the host's enemy AI targets players by everyone's hate.
  - Snapshots: a full image, then diffs, enabled only between StartBattleStageRes and the end of the stage. **[confirmed]**
- **No lockstep.** Damage to enemies is applied locally on every client, and the host's parameter updates correct it. **[inferred from the flow]**
- **Spinners.** The client shows a network spinner after 2.5 s with nothing received, and after 1.2 s waiting for a rush-combo sync.
- **Tick.** There is no fixed simulation tick on the wire: everything is the 300 ms flush. In the two-client run the relay forwarded 51 SnapshotRes and 48 MessageRes in about 20 s of battle. **[run]**
- **Stage barrier.** A stage is a wave. Each client sends StartBattleStage and waits for StartBattleStageRes (@015a2774); at the end it sends FinishBattleStage and waits for the Res (@015a2960).
  - In the run, the 2-stage mission produced two Start/Finish pairs per client, 8 s and 5 s apart, before MissionEnd. **[run]**
- **Rush combo.** It needs agreement.
  - Any client sends StartRushCombo.
  - The relay echoes StartRushComboRes, and clients queue the arrivals (@015a2d6c).
  - `Progress` checks `CanRushCombo(…, isHost)` and sends SyncStartRushCombo.
  - Everyone gets SyncStartRushComboRes (@015a3028), which carries the relay-decided target and ride flag.
  - SyncFinishRushCombo / Res (@015a3440) set the totals.
  - The relay's decision rule is **[unknown]**.
- **Disconnects.**
  - The relay pushes DisconnectNodePush(slot). The host takes over that player's character.
  - A relay error status (-0x3af / -0x3b4 in `IMultiplayNotify::OnProtocolError` @015a191c) sets the connection-lost flag, and the battle exits.
  - There is no host migration: nothing reassigns +0x3d8 in battle. **[inferred]**
  - Reconnect is never sent by 3.7.0.

### 1.8 How a battle starts and ends (the API side)

- **MissionStart.**
  - In co-op, `CStageManager::Progress` @013c7820 case 1 **skips `CallMissionStart`** when a CMultiplayManager exists. It waits for CMultiplayManager+0x3e4 instead, which `OnMissionStartPush` @015a219c sets after feeding the body to `CApiNotify::OnMissionStart`. **[confirmed, run]**
  - So the relay's side runs MissionStart for every player and pushes each player its own MissionStartRes body. That body covers: stamina, the drop tables, `BattleParameter.PlayerCharacter[4]` (the four characters in the battle), `multi_player_count` and the rest.
  - `present[i] = 0` shows player i as disconnected on the loading screen.
- **MissionEnd.**
  - On a win at the last stage, **every** client, guests included, calls `CMultiplayManager::SendMissionEnd` @015a6c80. It sends `BAS::GetUUID()`, `GetDeviceType()` and its own battle log.
  - The reply MissionEndPush goes to `CApiNotify::OnMissionEnd`, which sets +0x3e5; state 0x15 waits for it. **[confirmed, run]**
  - So rewards are computed **per player, from each player's own battle log**, by the server, and the UUID identifies the player.
- **Loss or timeout.** Only the client with slot 0 calls GameRPC **MissionFailed** (vtable +0x2a0, or Sphere211MissionFailed +0x4f0) over its normal API connection. The guests call nothing. **[confirmed code; slot 0 = host inferred]**
- **Continue** is host-only: the pause menu checks `IsMultiplayHost`. It goes through the relay (MissionContinue / Res). **[confirmed]**
- **MultiMissionRestart** (GameRPC `8c788f39`) is called when `GetMissionRestart()` = 2 (MissionRestart when it is 1). That mode is set by `CPhase_Login` / `CPhase_InterruptionResume`, and the reply is parsed by `OnMissionStart` @014bfd28. So it resumes an interrupted **co-op** mission after a restart of the app, through the normal API and not the relay. **[calls confirmed; purpose inferred]**
- **Host bonus.** The client has no logic for it. It would be server data inside each player's MissionEndRes; `host_bonus` columns exist in the drop tables but are all 0 or NULL in 3.7.0. **[confirmed absence in the client; server rule unknown]**
- **Enemy scaling by player count** is client-side (the `Battle_Multi_*Rate_N` globals). The reward multiplier `Multi_Player_Number_N` (1 / 1.5 / 2) is presumably server-side. **[inferred]**

## 2. The wire

| | GameRPC (443) | LobbyProtocol (4001) | BattleProtocol (relay) |
|---|---|---|---|
| Transport | TCP | TCP, keep-alive (1, 5, 6) | TCP, keep-alive (20, 2, 3) |
| Stack | `TPeer<TCP, TProtocolSuite<GameProtocol, NoProtocol<1>, NoProtocol<2>>>` | the same template with LobbyProtocol | the same with BattleProtocol |
| Header | 24 bytes, scrambled with the timestamp (wire bytes 0..7 = t bytes 6,4,3,0,7,1,2,5; fields XOR t): u32 size, u32 FID, u32 counter, u8 flags | **identical** (`_write_header` @022f92a0, `_read_header` @022f8ef4) | **identical** (@01593198, @01592dec) |
| Trailer | SHA-1 of the packet (`GameProtocol::Serialize` @0150d248 calls `Hash::SHA1`, len + 0x14) | **none**: `LobbyProtocol::Serialize` @022f8aa4 is a memcpy; size = 24 + body | **none** (@015926a0) |
| Body | RequestHeader + args, Ninja-encrypted (10 ciphers, session key from the bridge) | raw structs, plaintext; no `Set*` takes a Ninja | raw structs, plaintext, except the five 0x80 messages |
| Handshake / session | StartBridge → bridge POST → UpdateSession | **none**: no message on connect | **none**: EnterRoom is the first message |

- **Evidence that the trailer is absent and the framing identical.** The prototype parses the client's packets with the GameRPC header code minus the SHA-1, and every packet in the run parsed. The prototype's replies without a trailer were accepted. **[run]**
- **ChaCha20 on five messages.** MissionStartPush, MissionEnd, MissionEndPush, MissionContinue and MissionContinueRes set flags **0x80**, and their whole body is XORed with ChaCha20.
  - The algorithm is standard RFC 7539 (`CreateKeyStream` @0159b5ec).
  - **Key** (32 bytes, rodata @0281a93f): ``/r\'zp utw08[-=,'U*}_( V^IB{%I3`` followed by NUL, i.e. `2f725c277a702075747730385b2d3d2c27552a7d5f2820565e49427b25493300`.
  - **Nonce:** `A^#g2074RaJG`.
  - **Block counter:** reset to 0 for every message.
  - `InitBattleRPCClient` @015a7568 writes key, counter and nonce into the battle peer (+0x3c / +0x4c..+0x7c). They are **the same for every client and every connection**.
  - With 0x80 set, the receiver allocates twice the size and decrypts into the second half.
  - Our prototype's ChaCha20 matches the RFC test vector and decrypted the clients' MissionEnd (UUID, DeviceType 2, battle-log length) correctly. Its MissionStartPush and MissionEndPush were accepted. **[confirmed, run]**
- **Errors.** ProtocolError (`05aed673`: i64 status, u32 FID) is shared by all three protocols. Unknown FIDs fail with -0x3b8.
- **The relay address** comes from the room's RoomInfo (host string +0x42a, port +0x428).
  - Production ran it per room ("TCP host:port handed out per room"), so the lobby could place rooms on any relay machine.
  - The client connects to whatever address it is given. Our platform layer (`platform370/src/net_370.cpp`) only rewrites ports 443 and 4001, so a local relay must be given as a **literal reachable IP and real port**. That works as-is (the run used `127.0.0.1:<port>`). **[run]**

## 3. What a server needs to emulate

### 3.1 The lobby (port 4001; soa-emu / soa `--lobby HOST:PORT` already redirect it)

- **State:** a room table {id, RoomCondition, creator's PlayerInfo, members, open/private, relay address}.
- **Answer:**
  - **CreateRoom**: allocate an id, write the id string into RoomCondition+0x14e, and reply CreateRoomResult(RoomInfo with PlayerInfo[0] = the creator, the condition, relay host/port, room id).
  - **GetRoomList**(cond, begin, end): filter open rooms by the condition (mission/area/planet/type; `-1` = any; the room-id string for ルームIDで検索; the mutual-follow flag) and page them.
  - **Automatch**(cond): pick a room, or an Error when there is none.
  - **CloseRoom**: mark it closed.
- **EnterLobby and UpdateRoomInfo** can be answered trivially; 3.7.0 never sends them.
- **The lobby connection is short-lived:** the client closes it after EnterRoomResult. The lobby learns membership from the relay, in the same process.

### 3.2 The relay (one listener; rooms keyed by the room id in EnterRoom)

| Message | Relay action |
|---|---|
| EnterRoom | Assign the first free slot (0 = creator), set PDI+0x68, reply EnterRoomResult(slot, 0, PDI[4], count), push UpdatePlayerListResult to the others. Refuse a full or closed room with a non-zero status. |
| UpdatePlayerList | Reply UpdatePlayerListResult(PDI[4], count, s8, u64). |
| UpdatePlayerStatus | Store the PDI and its ready flag, reply Res(0), push the list to everyone. |
| ChangePublicRoom | Store it, reply Res(0). |
| ExitRoom | Reply ExitRoomRes. Kick: push ExitRoomPush to the kicked slot, free it, push the list. |
| StartMultiplay (host) | StartMultiplayRes(PDI[4], count) to all. Then **run MissionStart for each player** and push MissionStartPush(present[4], body) when ready. |
| StartBattleStage / FinishBattleStage | **Barrier**: when every connected slot has sent it, StartBattleStageRes(present[4]) / FinishBattleStageRes to all. |
| Snapshot | Forward as SnapshotRes to the others. |
| Message | Forward as MessageRes to the others, **dropping the sender and subtracting 4 from each entry offset**. |
| AIParameter | Forward as AIParameterRes to the host. |
| Stamp | StampPush(slot, id) to all. |
| StartRushCombo / SyncStart / SyncFinish | Echo StartRushComboRes to all. **Decide** the SyncStartRushComboRes (target, ok, ride) and SyncFinishRushComboRes for all. The real rule is unknown; first-come, ok = 1 works in principle. |
| MissionEnd | Map the UUID to the player, **run MissionEnd** with that battle log, and reply MissionEndPush(body) to that client. |
| MissionContinue | Run MissionContinue for the host and reply MissionContinueRes. |
| socket closed | Free the slot and push DisconnectNodePush(slot, 0) to the others. The host's client then drives that character. |

Optional: RSSIPush (a cosmetic signal bar), ForceWinBattleStagePush (a server-side "win now", e.g. for a time-out) and the room's start timers (`multiplay_force_start_time`, `lobby_opened_time_max`).

### 3.3 The API side

- **Several players in one soa-server.** This is the real prerequisite. Today every device gets `LOCAL00001` (server/README.md), with one state DB per server.
  - Co-op on one server needs one player per device UUID: the bridge already receives the UUID, and the relay's MissionEnd carries it.
  - Two ways: one state DB per player, which keeps every API module single-player and adds a session → backend map; or player ids in every table, a much larger change.
- **A multi MissionStart** (backend entry point). This is the existing MissionStart with these changes:
  - The mission comes from the room (RoomCondition+0x14), not from a request.
  - Stamina is charged per player (inferred).
  - `MissionParameter.multi_player_count` = the room's player count.
  - **`BattleParameter.PlayerCharacter[4]` = the room's characters:** each player's leader from its PDI, then fillers from the host's and guests' parties, as the client's dialog says ("ホスト、ゲストのパーティキャラクターで補充"). Their statuses come from the server's own status rules for each owner.
  - The same body for every player except the player-specific keys (Player, Wallet, stamina).
- **MissionEnd per player**, reusing the existing MissionEnd and battle-log decoding.
  - Rule decisions to label: the `Multi_Player_Number_N` reward multiplier (a), a host bonus (`host_bonus` columns are 0, so none (a)), and whether guests pay stamina (d).
- **MissionFailed** stays on GameRPC (the host only). **MultiMissionRestart** resumes an interrupted co-op mission as a single player: answer it like MissionRestart (d).
- **Follow, friends and the mutual-follow filter.** The 相互フォロー rooms filter needs the follow lists, and those need several players. Until then, ignore the flag (d).
- **`is_open_multiplay` = 1** (and `view_status` bit 4 where needed), only when the lobby is enabled.
- **`LobbyPath`** in NoLoginStart can point the client at any lobby host. It isn't needed locally, because the platform redirects port 4001.

### 3.4 Effort and risks

| Piece | Size (C++ in server/net + server/src) | Risk |
|---|---|---|
| Wire: header/framing reuse (no SHA-1), ChaCha20, struct codecs, FID tables generated like `tools/api_wire.py` | ~300 lines + tests | low: proven by the prototype |
| Lobby listener (room table, list, automatch, close) | ~250 lines | low |
| Relay listener (slots, barriers, forwarding, disconnects, rush combo) | ~600 lines | medium: the rush-combo arbitration rule is unknown; Message offset rewriting is [inferred] but ran |
| Multi-player soa-server (player per UUID, backend per player) | ~500-1000 lines, touching session/bridge/state | **high**: cross-cutting; every API module assumes one player and one state DB |
| Multi MissionStart (room party composition, statuses of other players' characters), MissionEnd per UUID, rules doc | ~400 lines + server-rules entries | medium: PlayerCharacter[4] composition and reward rules are partly (d) |
| Session scripts (two clients), selftests | ~300 lines | low-medium: timing of two GUIs, ≤ 3 game processes |

Total: about **2-3 agent-days** to two real instances with real rewards. Without multi-player state (two servers, one per client, and the relay calling each server's backend over a small admin RPC), it is about 1.5 days but architecturally worse.

Other risks:
- **Determinism and desync.** Damage is local on every client. Desyncs were handled by the host's parameter updates in production too, so nothing new is needed.
- **Old-bug faithfulness.** The production relay's exact replies (the u8/u32 extras in SyncStartRushComboRes and UpdatePlayerListResult's s8 / u64) are [unknown]. Zeros worked in the run.
- **The port's JIT speed.** Two `soa` instances, both under the JIT, may be slow. soa-emu is fine.

## 4. Ways to make it playable here

### (a) Several clients on one machine against one soa-server (lobby + relay inside it)

This is real co-op between real instances, and it is what §5 already did in prototype form: two soa-emu instances on one machine, each with its own soa-server and a shared Python lobby/relay.
- The client side needs **no changes**: soa-emu and soa (`--server HOST`) already have `--lobby`, and the relay address is a literal IP.
- The server side needs everything in §3.
- **Best for testing and the first milestones.**

### (b) LAN play between machines

The same server, bound to a LAN address:
- The lobby must hand out a relay host that every client can reach (the server's LAN IP, `--relay-host`).
- Each client runs `--server <lan-ip> --lobby <lan-ip>:<port>`.
- Nothing else differs; there is no NAT traversal because all traffic goes to the server. **Comes for free after (a).**

### (c) Single-player "multiplayer" with AI teammates

- **The client's own fillers.**
  - The client fills empty slots with party characters, run by the **host's AI**: they are NPC fillers, and the host owns them. **[run]**
  - But the client requires **at least two room members** to start: バトル開始 stays disabled while alone. **[run]**
- **Two cheap routes:**
  1. **A phantom guest.** The relay itself adds a second "player" to the room (a PDI built from another of the player's characters or a helper; no socket), so the host can start. In MissionStartPush it marks that slot **not present** (`present[i] = 0`), and/or pushes DisconnectNodePush for it at the first StartBattleStage.
     - The host then owns that character as a disconnected player's and its AI plays it.
     - The barriers wait only for connected slots.
     - This needs no second client and no client change, but it is effectively a single-player battle with multi scaling. **[inferred; untested]**
  2. **A headless bot client.** A real guest protocol driver: a program that speaks BattleProtocol, answers the barriers, sends AIParameter and plays a character by sending behaviour Messages.
     - This means re-implementing the battle's character control from `CFieldMessage_*` formats.
     - **Not worth it**: a second soa-emu is the better bot.
- Single-player battles with an AI helper already exist (the rental NPC stand-ins), so (c) is mainly for the co-op UI and rewards.

### (d) The in-process port (`soa`, default `--server inproc`)

- The lobby and relay are separate TCP peers in the client. FakeApiCaller replaces only the **API** caller; it does not touch `TARPCPeer<Lobby/BattleProtocolProxy>`.
- In-process mode turns the platform's network redirect **off** (`p370.net = !inproc`, port/src/main.cpp:364). So today the in-process client's lobby connect would do a real DNS lookup of `production-game.so-ana.com:4001` and fail. **[confirmed code]**
- **The port would connect to a soa-server lobby over TCP even in in-process mode** (or to the in-process server's own lobby listener). That needs two small changes:
  1. enable the redirect for port 4001 in in-process mode (`--lobby HOST:PORT` honoured with `inproc`);
  2. in-process co-op would also need the relay's MissionStart and MissionEnd to reach the same backend the FakeApiCaller uses.
  - The simplest is to run lobby and relay listeners **inside the soa process**, on the in-process server library, but co-op with another instance then needs that instance to reach this process's lobby.
- **Recommendation for the port:** co-op runs against a `soa-server` (soa `--server HOST --lobby …`). In-process mode stays single-player, or uses the phantom-guest route (c1) through in-process listeners later.

### Recommendation and staged plan

Build (a) inside soa-server, with (b) for free and (c1) as an option afterwards.

| Stage | Goal | Work | Evidence and test |
|---|---|---|---|
| **M0** (done) | Prove the protocol | Python prototype ([`multiplayer/prototype/`](multiplayer/prototype/README.md), §5): the starting point and executable spec for M1-M3 | Two soa-emu instances as two players: room, start, 2-stage battle, per-player MissionEnd, results; the host rule |
| **M1** | **Two soa-emu instances enter the same room and start the same mission** against one soa-server | `server/net`: lobby and relay listeners (`--lobby-listen`, `--relay-listen`, `--relay-host`), FID tables generated from the lib (an `api_wire.py`-style generator for the two protocols), ChaCha20, struct codecs. `is_open_multiplay` behind a server flag (`--multiplay`). **Multi-player state:** one player per device UUID (the second device gets `LOCAL00002`, seeded from the same seed). MissionStart for the room: the mission from the room, PlayerCharacter[4] from the members' PDIs plus fillers. | Selftests: the codecs against the client's own `Set*`/`Get*` (differential, as the `wire/` selftest does), the barrier/slot state machine. Session: `emulator/scripts/multiplay_session.sh`: two soa-emu, one soa-server, **host** create → **guest** ルームを全検索 → join slot → host バトル開始 → 出撃する; milestones from the server's packet log: `CreateRoom`, `EnterRoom` ×2, `StartMultiplay`, `MissionStartPush` ×2, `StartBattleStage` ×2. Screenshots of both loading screens. |
| **M2** | **The battle stays in sync** | Forwarding (Snapshot, Message with offset rewrite, AIParameter, Stamp), barriers, rush-combo arbitration, DisconnectNodePush on close | Session continues: per-stage barrier lines; both clients reach "Mission Complete" in the same stage count; kill the guest mid-battle → the host gets DisconnectNodePush and finishes. A relay log of message counts per kind; side-by-side screenshots mid-battle. |
| **M3** | **Rewards** | MissionEnd per UUID through the backend (each player's own battle log), MissionEndPush, reward rules (`Multi_Player_Number_N` (a), host bonus none (a), guest stamina (d)) in `docs/server-rules.md`; MissionFailed for the host; MultiMissionRestart as MissionRestart | Session: both Mission Result screens; the server state shows both players' rewards (`tools/server_state.py`, two players); a lost battle → only the host's MissionFailed. |
| M4 (optional) | LAN, the port, phantom guest | `--relay-host` docs; soa `--server` co-op; (c1) phantom guest behind a flag | A LAN run; a soa + soa-emu pair; a single-client co-op with the phantom guest |

**Test harness.** The prototype's `mp_client.sh`, `make_player2.sh` and `mp_drive.sh` ([`multiplayer/prototype/`](multiplayer/prototype/README.md)) are the template:
1. two clients that log in and stop at the mission detail (HOLD), the second with its own player;
2. a shared lobby/relay;
3. scripted taps:
   - host: マルチプレイ開始 527:905 → ルームを作成 364:527 → 決定 364:900 → 募集開始 527:948 → confirm 515:800 → バトル開始 140:948 → 出撃する 515:800;
   - guest: 527:905 → ルームに参加 364:648 → ルームを全検索 364:905 → FREE slot 284:497.

Each client takes about 100 s to the mission map from the shared phone. Two soa-emu instances fit the ≤ 3 game-process budget.

## 5. Experiments (2026-10-02 / 03)

- **The game binaries** were the worktree build (soa-emu, headless, 729x1296).
- **The only server change** was a scratch soa-server built with [`open-multiplay.patch`](multiplayer/prototype/open-multiplay.patch) (`is_open_multiplay = getenv("MP_STUDY_OPEN") != nullptr`; reverted at once, not committed).
- **The scripts** are committed in [`multiplayer/prototype/`](multiplayer/prototype/README.md). Runs 1-2 below used earlier scratch versions of them, with the same taps.
- **The screenshots** referenced as `NN` are in [`multiplayer/screenshots/`](multiplayer/screenshots/).

1. **`is_open_multiplay` = 1, with a logging listener on the lobby port** (`lobby_listen.py`; soa-emu `--lobby`; `run1/`).
   - The mission detail shows **マルチプレイ開始** and the map **この惑星のマルチプレイに参加** (`run1/mission-detail.png`), then the multiplay menu (`run1/mp2.png`), the party select (`mp4.png`) and ルーム作成 (`mp6.png`).
   - **The client opened the lobby connection when the party was confirmed and sent nothing** until 募集開始.
   - Then a 0x270-byte plaintext **CreateRoom** with flags 0 and no trailer.
   - With no reply, after 61 s the client closed the socket and showed 通信が切断されました (`mp11.png`).
   - No other traffic: no EnterLobby.
2. **The prototype lobby and relay** (`mp_proto.py`: lobby + relay + ChaCha20; the API side canned from an earlier single-player soa-server capture of 1-05: `canned-MissionStartRes.msgp`, `canned-MissionEndRes.msgp`). There were two soa-emu instances, each with its own scratch soa-server (both the seeded `LOCAL00001` player, which is why both show "Fayt"). Log: `proto.log`; screenshots `runA/`, `runB/`, `pair*.png`.
   - Host: CreateRoom → CreateRoomResult (relay 127.0.0.1:port, id 1001) → lobby closed → EnterRoom → EnterRoomResult(slot 0) → **メンバー募集中** with ルームID:1001, バトル開始 disabled. Then UpdatePlayerList every 2 s.
   - Guest: GetRoomList → **ルーム一覧** showing the host's room (`runB/join2.png`) → FREE slot → EnterRoom(slot 1).
   - Both rooms then showed two members (`pair1.png`): the guest "ホストの開始を待っています", the host バトル開始 enabled.
   - Host バトル開始 → **"パーティメンバーが2人不足しています…補充しミッションに出撃します"** (`runA/start1.png`) → 出撃する → StartMultiplay → StartMultiplayRes ×2 → MissionStartPush ×2 (0x80, ChaCha20).
   - Both loading screens showed STAGE 1/2 (`pair2.png`). Then:
     - StartBattleStage ×2 → Res, battle, FinishBattleStage ×2;
     - StartBattleStage ×2, FinishBattleStage ×2;
     - MissionEnd from each client (decrypted: the device UUID, DeviceType 2 and a 0xe71-byte battle log) → MissionEndPush.
   - **Both clients:** in battle with the four characters of the canned body (`pair3.png`: "Mission Complete" on the guest), then Mission Result (`pair4.png`, `pair5.png`), then the relay connections closed (the guest's close produced DisconnectNodePush to the host).
   - The relay forwarded 51 SnapshotRes and 48 MessageRes. No crashes.
   - **Caveats.**
     - The MissionStart and MissionEnd bodies were canned: no stamina was charged and nothing was credited in either server's state.
     - The party in battle was the canned single-player party (all four tagged HOST), not the room's characters. That led to the owner-id finding in run 4.
     - The rush-combo and AIParameter paths were exercised only as far as this short fight used them: AIParameter yes, rush combo not observed.
3. **Two distinct players** (2026-10-03).
   - Player 2 has its own state: numeric id 1000000002, `LOCAL00002`, name Player2, leader Ashton (`make_player2.sh`).
   - The guest joined by **automatch**: a searching dialog with a 30 s countdown that retries Automatch about once a second (09); "no party found" (10) when there is no room.
   - Both rooms show Fayt and Player2 with their own characters (13, 14).
   - In this run the bodies were still single-owner, so the HUD tagged everyone HOST, but **the guest played party slot 1**: its character was the one in that slot.
   - **A guest disconnect mid-battle** (its soa-emu killed in stage 2): the relay pushed DisconnectNodePush. The host's battle went on without a dialog, the host's client took over the character, and it finished the mission and reached the result (26, 27).
   - **Opening the スタンプ picker crashed soa-emu** (guest pc in `CStampUI::GetCsfFilePath()+0x448`, a host SIGSEGV in the emulator). Not investigated.
4. **The host fix** (run 4, the committed prototype). The relay composes each player's MissionStartRes with the room's party and owner ids (§1.7), and each player gets its own captured MissionEndRes.
   - **Result:**
     - the HUD tags Fayt's characters HOST and Ashton GUEST on both screens;
     - the same damage numbers at the same moments on both screens (18/19, 20/21);
     - the guest's victory pose is Ashton (23);
     - each player gets its own result page (24/25);
     - sender counts: only the guest (slot 1) sent AIParameter; the host sent 22 Messages and the guest 11.
   - Run 5 (the same, with SOA_TRACE on `IsMultiplaySendCharacter`) gave the ownership table in [`captures/ownership-trace.txt`](multiplayer/captures/ownership-trace.txt).
   - Run 6 (MP_VERBOSE) gave the decoded relay stream in [`captures/battle-relay-sample.log`](multiplayer/captures/battle-relay-sample.log). The host's snapshots carry 6 objects and the guest's 1.

### Screenshots

All from soa-emu (the unmodified 3.7.0 client, headless) with the prototype lobby and relay. The host is Fayt / LOCAL00001; the guest is Player2 / LOCAL00002. Each client has its own soa-server opened by `open-multiplay.patch`. Grid: [`contact-sheet.png`](multiplayer/screenshots/contact-sheet.png) (made with `tools/contact_sheet.py`).

| # | Shows | Run |
|---|---|---|
| 01 | Mission detail with マルチプレイ開始, and この惑星のマルチプレイに参加 on the map | 1 (logging probe) |
| 02 | The multiplayer mode menu: ルームを作成 / ルームに参加 / ルームIDで検索 | 3 |
| 03-05 | Host: party select (its leader is what it brings), ルーム作成 (recruit slots, public/private, comment, 相互フォロー限定), the 募集開始 confirmation | 4 |
| 06 | Host alone in メンバー募集中: ルームID:1001, バトル開始 disabled | 4 |
| 07 | No lobby reply: after 61 s 通信が切断されました | 1 |
| 08 | Guest party select (leader Ashton): 相互フォローのルームを検索 / ルームを全検索 / オートマッチング | 4 |
| 09, 10 | Automatch searching (countdown), and "no party found" | 3 |
| 11 | ルームIDで検索's room-id dialog | 3 |
| 12 | ルーム一覧 with the host's room | 4 |
| 13, 14 | The same room, host and guest view: Fayt and Player2 (Ashton); the guest waits for the host | 4 |
| 15 | Host バトル開始 with two players: "パーティメンバーが2人不足しています。ホスト、ゲストのパーティキャラクターで補充…" | 4 |
| 16, 17 | Loading STAGE 1/2: each side lists the other member as 準備中 | 4 |
| 18, 19 | Battle start, host and guest at the same moment: HOST/GUEST tags, the same damage numbers | 4 |
| 20, 21 | Stage 2, both views | 4 |
| 22, 23 | Mission Complete (host); the guest's victory pose is its own Ashton | 4 |
| 24, 25 | Mission Result, host and guest: each from its own (canned) MissionEndRes | 4 |
| 26, 27 | The guest killed mid-battle: the host's battle goes on (26) and ends at the result (27) | 3 (before the owner-id fix: all tagged HOST) |

## Corrections to online-server.md

- **§8.** The lobby (4001) carries only CreateRoom, GetRoomList, Automatch and CloseRoom (plus the never-sent EnterLobby and UpdateRoomInfo). **EnterRoom, ExitRoom, UpdatePlayerList, ChangePublicRoom, StartMultiplay and UpdatePlayerStatus are BattleProtocol messages on the relay.**
- **Neither protocol has GameRPC's SHA-1 trailer or Ninja cipher.** The relay's mission messages use a fixed-key ChaCha20.
- **§2 table.** The relay address row is now confirmed (RoomInfo +0x42a / +0x428). `LobbyProxyPath/Port` and `BattleProxyPath/Port` have no readers; `LobbyPath` is read from **NoLoginStart** (`SetLobbyServer`).
- **§8.** "The API server still ran MissionStart … MissionEnd" is wrong. In co-op, MissionStart and MissionEnd go **through the relay** (MissionStartPush / MissionEnd / MissionEndPush, ASON bodies the API parser reads), so the relay, or the server behind it, ran them per player. MissionFailed (host only) and MultiMissionRestart stay on GameRPC.

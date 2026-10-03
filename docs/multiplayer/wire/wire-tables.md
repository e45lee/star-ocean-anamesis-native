
### LobbyProtocol: 14 FunctionIDs

| Message | FunctionID | Set serializer (Ghidra) | body size (Set: +0x24) | parameters |
|---|---|---|---|---|
| Automatch | `e3a9a528` | @022fa9f4 | 0x270 | PlayerInfo const&, RoomCondition const& |
| AutomatchResult | `1fed00e2` | @022fabec | 0x474 | Status, RoomInfo const&, int |
| CloseRoom | `efe1edb6` | @022f9e80 | 0x20 | int, unsigned int |
| CloseRoomResult | `e8fbdaaa` | @022fa05c | 0x20 | Status |
| CreateRoom | `6a1b49a5` | @022f9aa4 | 0x270 | PlayerInfo const&, RoomCondition const& |
| CreateRoomResult | `eac42001` | @022f9c9c | 0x468 | RoomInfo const& |
| EnterLobby | `fb5d0d73` | @022f96e4 | 0x88 | PlayerInfo const& |
| EnterLobbyResult | `4e466d87` | @022f98c8 | 0x20 | Status |
| Error | `05aed673` | - | - |  |
| GetRoomList | `2ddf640d` | @022fa238 | 0x278 | PlayerInfo const&, RoomCondition const&, int, int |
| GetRoomListResult | `cc88678c` | @022fa45c | ? | RoomInfo const*, unsigned int, int, int |
| Invalid | `7b1a9377` | - | - |  |
| UpdateRoomInfo | `a8efdd88` | @022fa62c | 0x468 | RoomInfo const& |
| UpdateRoomInfoResult | `6b177840` | @022fa810 | 0x468 | RoomInfo const& |

### BattleProtocol: 48 FunctionIDs

| Message | FunctionID | Set serializer (Ghidra) | body size (Set: +0x24) | parameters |
|---|---|---|---|---|
| AIParameter | `929765c3` | @0159756c | ? | MO::HateParameter const*, unsigned int |
| AIParameterRes | `16287e9b` | @01597834 | ? | MO::HateParameter const*, unsigned int |
| ChangePublicRoom | `d4c82eca` | @0159a294 | 0x19 | signed char |
| ChangePublicRoomRes | `d0a58e6d` | @0159a46c | 0x20 | Status |
| DebugMessage | `10ce4f8f` | @01597afc | 0x1c | unsigned int |
| DebugMessageRes | `c478bdba` | @01597cd4 | 0x1c | unsigned int |
| DisconnectNodePush | `a2667cb1` | @0159abec | 0x20 | int, int |
| EnterRoom | `43610d78` | @015998fc | 0x49c | PlayerDetailInfo const&, int |
| EnterRoomResult | `f6dec31d` | @01599ae8 | 0x1228 | int, Status, PlayerDetailInfo const*, int |
| Error | `05aed673` | - | - |  |
| ExitRoom | `f2d53301` | @01599cf4 | 0x20 | ExitType, int |
| ExitRoomPush | `e5c49b5a` | @0159a0bc | 0x1c | ExitType |
| ExitRoomRes | `44ac9b5c` | @01599ee4 | 0x1c | ExitType |
| FinishBattleStage | `b24434d1` | @0159643c | 0x18 |  |
| FinishBattleStageRes | `7309d699` | @01596600 | 0x18 |  |
| ForceWinBattleStagePush | `8566caa5` | @015967c4 | 0x18 |  |
| Invalid | `7b1a9377` | - | - |  |
| Message | `c1f33acc` | @01598b98 | ? | int, Message const*, unsigned int |
| MessageRes | `57faa296` | @01598e88 | ? | Message const*, unsigned int |
| MissionContinue | `755cba3d` | @01595a30 | 0x41 | signed char const*, MO::DeviceType, unsigned char, ChaCha20* |
| MissionContinueRes | `40db9f93` | @01595cd4 | uVar1 | signed char const*, unsigned int, ChaCha20* |
| MissionEnd | `8312a64c` | @0159525c | uVar1 | signed char const*, MO::DeviceType, signed char const*, unsigned int, ChaCha20* |
| MissionEndPush | `e2d23280` | @01595668 | uVar1 | signed char const*, unsigned int, ChaCha20* |
| MissionStartPush | `399501b0` | @01594e88 | uVar1 | unsigned char const*, signed char const*, unsigned int, ChaCha20* |
| Packet | `febe96fc` | @01598230 | ? | Message const*, unsigned int, signed char const*, unsigned int |
| PacketRes | `535410ce` | @0159853c | ? | Message const*, unsigned int, signed char const*, unsigned int |
| RSSIPush | `440ed5b8` | @0159aa10 | 0x28 | float const* |
| Reconnect | `b1533261` | @0159adc8 | 0x1c | int |
| RequestProxy | `f8697e7f` | @01597eac | ? | signed char const*, unsigned int, unsigned short |
| RequestProxyResult | `5528c22a` | @01598054 | 0x20 | Status |
| Snapshot | `e0423298` | @01598848 | ? | signed char const*, unsigned int |
| SnapshotRes | `3712ac8e` | @015989fc | ? | signed char const*, unsigned int |
| Stamp | `a406ad38` | @01594ac8 | 0x1c | unsigned int |
| StampPush | `38c5438d` | @01594cac | 0x20 | int, unsigned int |
| StartBattleStage | `98905d95` | @0159609c | 0x18 |  |
| StartBattleStageRes | `0f074e01` | @01596260 | 0x1c | unsigned char const* |
| StartMultiplay | `aeb31eca` | @01599174 | 0x18 |  |
| StartMultiplayRes | `948b0716` | @01599338 | 0x121a | PlayerDetailInfo const*, unsigned short |
| StartRushCombo | `bad35e28` | @01596988 | 0x1e | signed char, signed char, float |
| StartRushComboRes | `62cd4997` | @01596b98 | 0x1a | signed char, signed char |
| SyncFinishRushCombo | `0214d5cf` | @01597194 | 0x20 | float, int |
| SyncFinishRushComboRes | `bcacdd91` | @0159737c | 0x21 | float, int, unsigned char |
| SyncStartRushCombo | `a6fd1715` | @01596d78 | 0x1e | signed char, unsigned char, float |
| SyncStartRushComboRes | `ebfee137` | @01596f7c | 0x24 | signed char, signed char, unsigned char, unsigned char, float, unsigned int |
| UpdatePlayerList | `bd96f882` | @01599528 | 0x18 |  |
| UpdatePlayerListResult | `a629dd36` | @015996ec | 0x1223 | PlayerDetailInfo const*, unsigned short, signed char, unsigned long |
| UpdatePlayerStatus | `3764a958` | @0159a648 | 0x499 | PlayerDetailInfo const&, signed char |
| UpdatePlayerStatusRes | `5e3b82b4` | @0159a834 | 0x20 | Status |

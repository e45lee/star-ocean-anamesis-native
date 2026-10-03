# Decompile excerpts (data, not code)

These are the Ghidra decompiles of `work/libSOA-3.7.0.so` (3.7.0) that the multiplayer study relied on, grouped by topic. `symbols.tsv` lists every function: Ghidra address (ELF vaddr + 0x100000), topic file, demangled name. They are read in [`../../multiplayer.md`](../../multiplayer.md) and [`../HANDOFF.md`](../HANDOFF.md).

| File | What |
|---|---|
| `framing.c` | Lobby/Battle/GameProtocol `Serialize` / `Deserialize` / `GetFunctionName`, the header scramble, `TProtocolSuite<Lobby>::Open` |
| `lobby_messages.c`, `battle_messages.c` | Every `Get*` deserializer (field offsets) and a few `Set*` serializers (e.g. `SetMissionEnd` with ChaCha20) |
| `manager.c` | `CMultiplayManager` (`InitBattleRPCClient` with the ChaCha20 key and nonce, `Progress`, the `On*` handlers, `SendMissionEnd`…) and `IMultiplayManagerBase` |
| `ownership.c` | `CPartyManager::IsMultiplaySendCharacter` (the owner-id rule), `SetupCharacter_Local`, `CBattleUtility::CreateCharacter`, `CUIUtility::IsMultiplayHost` |
| `ui_flow.c`, `ui_lambdas.c` | `CMultiPlay3` (`Server_*`, `RoomInfo2RoomData`…), `CMissionMenu::ToMultiUI`, `IsOpenMulti`, `CUIMatchingNotify`, `MatchingClient`, and the std::function lambda bodies (CreateRoomResult → InitBattleRPCClient → EnterRoom…) |
| `mission_api.c` | `CStageManager::CallMission*` |

**Regenerate.** The sources are `tools/decomp.sh multiplayer-study-<topic> '<regex>'` outputs (`work/decomp/multiplayer-study-*.resolved.c`). The regexes are the class and method names in `extract.py`'s TOPICS. The lambdas came from an analyzed Ghidra project copy (vtable slot +0x30 of each `std::function`). Then run:

```
python3 docs/multiplayer/decomp/extract.py [work/decomp] [LAMBDA_DECOMPILES...]
```

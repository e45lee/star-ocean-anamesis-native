# Wire tables: LobbyProtocol and BattleProtocol

`gen_wire_tables.py` reads the study's decompiles and the lib's dynamic symbols:
- the names and FunctionIDs from `<Proto>::GetFunctionName`;
- the FID store (+0x30) and fixed packet size (+0x24) from each `Set<Message>` serializer;
- the parameters from the `Set*` signature.

It writes:
- `wire-tables.md`: one table per protocol (14 + 48 entries, kError and kInvalid included);
- `multiplay_wire.inc`: the same as a C++ initializer list `{protocol, message, fid, set_addr, size}`, meant for `server/net/gen/` when the real lobby and relay are written. It can regenerate from `tools/` there, as `tools/api_wire.py` does for GameRPC.

Field layouts per message are in [`../../multiplayer.md`](../../multiplayer.md) §1.4-1.6.

```
tools/decomp.sh multiplayer-study-proto 'LobbyProtocol::GetFunctionName' 'BattleProtocol::GetFunctionName'
tools/decomp.sh multiplayer-study-lobbyser 'MultiplayRPC::LobbyProtocoledData::(Set|Get)'
tools/decomp.sh multiplayer-study-battleser 'MO::BattleProtocoledData::(Set|Get)'
python3 docs/multiplayer/wire/gen_wire_tables.py --inc docs/multiplayer/wire/multiplay_wire.inc > docs/multiplayer/wire/wire-tables.md
```

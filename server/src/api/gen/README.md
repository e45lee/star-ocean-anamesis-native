# api/gen: the replies' types, generated from the client

The handlers build the parts of a reply that are the client's info classes (`CBoostCharacterResultInfo`,
`CLimitBreakInfo`, `CUpdateCharacterInfo`, ...) as plain C++ structs, not as `Value` maps set key by key.
Each struct's `to_value` gives the map the handler puts into its reply's `data`. The bytes are the same as
the hand-built maps gave: the same keys in the same order, the same msgpack types. msgpack.h packs an
integer by its value, so a field's C++ width doesn't change the bytes.

| File | What | Made by |
|---|---|---|
| `client_infos.json` | the client's info classes as the wire sees them: per class its fields in its Initialize's order (the ASON key, the property's value type), its children (an info, `InfoBaseArray<T>`, `IInfoBaseMap<K, T>`, `InfoBaseValueArray<T>`), and CInfoManager's children (the keys of a reply's `data`) | `tools/gen_infos.py` (from the 3.7.0 lib under unicorn; it writes `port/src/native/info/gen/info_classes.h` in the same run) |
| `reply_types.txt` | what the server sends of each class: the keys in wire order, which are optional (`?`), a type sent other than the client's (`:u64`, `:bool`), keys the client's class doesn't read (`+id:u64`), a second shape of a class (`CStackItemInfo as UseStackItemInfo`) | by hand, from today's replies (`tools/reply_shapes.py`) |
| `reply_types.h`, `reply_types.cpp` | the structs and their `to_value` | `tools/gen_server_infos.py` |

The generator checks every key against the client's class. A key the class doesn't name must be marked
`+`. A type sent other than the client's must be one the client's `GetValue<T>` takes
(`port/src/native/params/params_parser.cpp`: a `u32` property takes a bool or a u64). It also lists, per
struct, the client's keys the server doesn't send. The containers are in `core/info_map.h`: `InfoMap<K, T>`
(an `IInfoBaseMap`: insertion order, keys sent as decimal text, as the `Value` maps did), `to_array`,
`to_map`.

T0 `generated` checks both generators (`tools/check_generated.py`).

## Converting a handler

1. Measure what it sends: `tools/reply_shapes.py --class CFooInfo` (it replays every corpus, or reads
   `--dir` outputs) prints each key order and type sent, keys that aren't the class's, and the client's
   keys never sent. Then read the handler: a key the corpora never show (a branch they miss) still
   belongs in the struct, in the place the code puts it.
2. Add the class to `reply_types.txt` in the order the code sends, then run `tools/gen_server_infos.py`.
   Fill the struct in the handler and set `data["Key"] = infos::to_value(x)` (or `to_map` / `to_array`
   for a container).
3. Prove it: `tools/server_replay_diff.sh <the parent's soa-server> build/server/soa-server` must be
   identical. A path no corpus covers gets a corpus line or a test that pins its shape (e.g.
   `growth/apis`: EvolutionResult), run against the old code too.

Not typed (yet): the envelope (`data` itself: `Time`, `Player`, `Wallet` from `base_data`, and the keys
the hooks add: `ext::player_load`, `ext::on_response`, the campaign's splice). Those stay `Value` maps. So
do the core's shared builders that other modules extend (`CPlayerInfo`, the `Item` list with
`ext::item_extra`, `StockItem`).

## Converted

| Family | Classes |
|---|---|
| growth (`api/growth/growth.cpp`) | CBoostCharacterResultInfo, CLimitBreakInfo, CEvolutionResultInfo (+ CUpdatePlayerCharacter, UseStackItemInfo), CAwakenResultInfo, CUpdateCharacterInfo, CPersonAddStatusResultInfo, CEquipWeaponResultInfo / CEquipAccessoryResultInfo (and their person and item infos) |

# ASON: the engine's MessagePack

`Aska::ASON` is the Aska engine's MessagePack library. It reads and writes every MessagePack in STAR OCEAN: anamnesis:
- game-server **reply bodies**, the `{"data": {...}, "status": n}` map;
- the MessagePack **payloads inside some requests**: the battle log and the SetCharacterDeco payload;
- master-data rows (`EntityObject::Serialize`), the msgp parameter files, event scripts, `version.bin` and the manifests.

This document is about what matters on the wire and to a server. The request and reply framing around it are in [api.md "Wire format"](api.md#wire-format), and transport and encryption in [online-server.md](online-server.md). The in-memory internals (work buffers, the unpacker context, quirks on malformed input) are in [notes.md "ASON (MessagePack) in detail"](notes.md#ason-messagepack-in-detail). ASON is ported natively in `port/src/native/params/ason.cpp` (layouts in `ason.h`).

Written 2026-09-29 by agent `api-wire-doc`.

Labels:
- **[run]**: bytes produced by running the client code in the selftest `wire/` (`port/src/native/api/wire_test.cpp`);
- **[code]**: read from the decompiled code (addresses are Ghidra addresses, of the offline build's lib where this was first read);
- **[unknown]**: not recoverable from the client.

## Encoding
ASON *is* MessagePack. The reader is msgpack-c's resumable unpacker (`template_execute`) with Aska's callbacks, and the writer is a straightforward packer. **[code]**, and the port's differential tests run them against the guest on every tag.

| Tag | Read as | Written for |
|---|---|---|
| `00`–`7f` positive fixint, `cc`–`cf` uint8–64 | uint (type 2) | uint and non-negative int values (smallest form) |
| `e0`–`ff` negative fixint, `d0`–`d3` int8–64 | int (type 3); **a non-negative value becomes uint (type 2)** | negative int values (smallest form) |
| `ca` float32 | double (type 4), widened | never written |
| `cb` float64 | double | every double, including C++ `float` fields widened by the serializer |
| `c0` nil, `c2` / `c3` false / true | nil (0), bool (1) | nil, bool |
| `a0`–`bf` fixstr, `d9` / `da` / `db` str8/16/32 | string (5), UTF-8 kept as bytes | strings (fixstr, str8, str16, str32) |
| `c4`–`c6` bin8/16/32 | bin (8) | bin |
| `c7`–`c9` ext8/16/32, `d4`–`d8` fixext | ext (9) with its type byte | ext (fixext when the length is 1/2/4/8/16) |
| `90`–`9f` fixarray, `dc` / `dd` array16/32 | array (6) | smallest header |
| `80`–`8f` fixmap, `de` / `df` map16/32 | map (7), entries {key, value}; **any key type** | smallest header; the client only writes string keys |
| `c1` | error | – |

Deviations from what one might assume:
- **Signedness is not preserved for non-negative numbers.** `d0 05` (int8 5) reads as uint 5, the same as `05`.
- **float32 is never produced.** Floats go out as float64. A server may send either.
- **No size limits** beyond memory. `DeserializeToInfo` sizes the work buffer `max(size × 4, 0x2000)`, and the buffer grows on demand. The battle-log request refuses a payload over 0x1000 bytes (below).
- **Several top-level objects** in one buffer become a root array (multi-root flag). A reply body should be exactly one map.
- **Strings, bin and ext are not copied.** They point into the received buffer, and only in "multibyte" mode do strings get a NUL-terminated copy, which name lookups need. Response parsing uses multibyte mode.
- Malformed-input quirks (empty fixstr, truncated containers) are in notes.md. A well-formed body never hits them.

## Object model
- **`AValue`** (0x20 bytes): `u32 type` at +0, then the payload.
  - bool: the low byte of +8; uint / int: +8; double: +8 (bits).
  - string: +8 raw bytes, +0x18 length, +0x10 the NUL-terminated copy (multibyte mode only).
  - array: +8 `AValue[count]`, +0x10 count.
  - map: +8 entries, +0x10 count. An entry (0x40 bytes) is a key `AValue` then a value `AValue`.
  - bin / ext: +8 data, +0x10 length; ext type at +0x14.
- **`AArray` / `AMap`** are the {items, count} views the game's parsers take: `Deserialize(AValue::AMap const*)`, `DeserializeArray(AValue::AArray const*)`.
  - `AMap::Get_(const char*)` compares against the multibyte copies.
  - `AMap::Get_(const AValue*)` compares by type and value.
- **`Aska::ASON`** (0x90 bytes) owns the tree. It has its root `AValue` at +0x60 and allocates containers from its own bump arenas.
  - `ASON::DeserializeBinary(data, size)` builds the tree.
  - `ASON::Serialize(buf, cap)` / `CalcSerializedSize()` write it back.

## How keys reach C++ fields (reply side)
`CApiNotify::On<Name>Res` → `DeserializeToInfo` → `ASON::DeserializeBinary` → `CParameterManager::Deserialize(root map)`. **[code]**
- **Top level.** Each registered parameter set takes its own key: `data` → the `CInfoManager` at `CParameterManager+0x600`, `status` → +0xb728, `Player` / `master_*` → those sets. Unknown keys are ignored.
- **Inside an info**, keys are matched by **`CHash32` of the key string**. `CHash32` is CRC-32, reflected, poly 0xEDB88320, seeded with the input length, no final XOR.
  - Each info registers its properties (`CParameterPropertyValue<T, N>` / `CParameterPropertyString<N>`) and child infos under the hash of their name.
  - `CParameterParser::GetParserValue(map, hash)` is a **linear scan that hashes every string key**. The first match wins. Non-string keys never match, and absent keys leave the field as it was.
  - So a server must spell the keys exactly: `level`, `stamina_update`, …
  - The names per class are in `port/fakeapi/fields.txt`; the keys per info in `port/fakeapi/schema.txt`.
- **Value conversion** (`CParameterParser::GetValue<T>`, notes "Master data in memory"):
  - a u32 / int / u64 field accepts uint, int, double (truncated, AArch64 `fcvtz*` saturation) and a numeric string (`istringstream`);
  - a bool field accepts only 0 or 1;
  - a u8 field given a string takes its **first character**;
  - a string field takes a string value.
- **Child infos.** A child whose value is a map goes to the child's `Deserialize(AMap)` (vtable +8). An array goes to `DeserializeArray(AArray)` (vtable +0). List infos (`Character`, `GachaItems`, `UpdateStockItem`, …) take an **array of element maps**, and sending one replaces the list.

### Id-keyed maps
The map infos (`IInfoBaseMap<K, T>`: `AddCharacter`, `MissionResultCharacter`, `MissionResultCharacterFavor`, `LimitBreakCharacter`, the `*Map` infos) take a **map keyed by id**. **[code]**: `IInfoBaseMap<u64, CPersonInfo>::DeserializeChild` @016417a4, `InfoBaseNumberMap<CPersonInfo>::ConvertParserValueToKey` @01641968, `InfoBaseMap<CSkillInfoArray>::ConvertParserValueToKey` @0162144c.
1. `DeserializeChild` first **clears** the map.
2. For each entry, `ConvertParserValueToKey(key)` computes the key:
   - a **uint** key is used as is;
   - a **string** key is parsed as a decimal number in `InfoBaseNumberMap<T>` (`istringstream >> u64`: leading white space skipped, digits up to the first other character; a non-number or a leading `-` gives 0, a number above 2^64-1 gives 2^64-1). In the label-keyed `InfoBaseMap<T>` (e.g. skills) the key is `CHash32` of the string;
   - any other type (negative int, nil, …) asserts "wrong key type" and gives key 0.
3. The element is found or created, then deserialized from the value: map → element vtable +8, array → +0.

`IInfoBaseMap::DeserializeArray` returns without doing anything, so **an array sent for a map info is silently ignored**. `{"2130706432": {...}}` and `{2130706432: {...}}` are equivalent. The local server uses the string form, as the old FakeApi files did.

## Request payloads (AsonSerializer)
Two requests carry an ASON payload as a `u32 len + bytes` argument, and both are built by `AsonSerializer::Serialize<T>(ASON*, T&, 0, 0x4000, 1)` followed by `ASON::Serialize`. **[code, run]**
- `AsonSerializer` walks the object with a visitor (`T::Accept<_Serializer<SerializerImpl>>`) twice: a prepare pass that counts entries, then `_AsonSerializer`, which fills the tree.
- Every object becomes a **map with string keys**. The values:
  - `u32` / `u64` → uint;
  - `int` → int, which a non-negative value re-encodes as uint;
  - `float` → **double (float64)**;
  - `bool` → bool;
  - `std::string` → str;
  - the obfuscated string properties (`CryptString`) are decoded first.
- An array field becomes an array of maps under the name its container reports (vtable +0x10).

### Battle log (MissionEnd, MissionFailed, Sphere211)
`CBattleLogInfo` (`CParameterManager+0x52d8`). The request lambdas @015dd1cc (MissionEnd), @015dd958 (MissionFailed), @015f72f8 and @015f7528 (Sphere211 end and fail) do:
1. `ASON()`;
2. `AsonSerializer::Serialize<CBattleLogInfo>(ason, log, 0, 0x4000, 1)`;
3. `CalcSerializedSize()`: if it's **> 0x1000, nothing is sent**;
4. `ASON::Serialize(buf, 0x1000)`;
5. `Send<Api>(…, buf, len, …)`.

`CMultiplayManager::SendMissionEnd` sends the same log to the co-op relay. **[code]**

The map has 33 keys, in this order **[run]** (`wire/battle-log`, a fresh `CBattleLogInfo` with a few values set; 603 bytes, map16):
- `is_defeat` (bool);
- `damage_total`, `damage_total_party`, `hit_max`, `hit_total`, `rush_cooperate`, `rush_count`, `battle_result`, `continue_count`, `mission_type` (u32);
- `abnormal_count_stun`, `_freeze`, `_poison`, `_paralysis`, `_seal`, `_curse`, `_fog`, `_burn`, `_debuff` (u32);
- `mission_time`, `mission_total_time`, `assist_cutin_count` (u32);
- `order_count_all`, `_invincible`, `_bunker`, `_heat_up`, `autoplay` (u32);
- then six arrays:
  - `PlayerCharacter`: `CPersonStatusInfo`, i.e. id (u64), player_id, player_level, player_name, master_role_id, weapon_item_id, accessory_item_id, level, exp, limit_break_count, skill1..3 {id, `_label`, `_level`}, hp, attack, intelligence, defence, hit, guard, ap, def_fire, def_water, def_wind, def_earth, def_thunder, def_light, def_dark, rush1, rush1_label, rush_skill1_factor_id, rush1_level, next_exp, weapon_id, master_weapon_kind_id, weapon_kind_id_label, weapon_master_item_id, accessory_master_item_id, weapon_limit_break_count, weapon_level, is_rarity_7;
  - `PlayerCharacterCheat`: {player_id, character_id};
  - `StageEnemyInfo`: {id, num};
  - `DefeatedEnemyInfo`: {id, num};
  - `CPlayerLogInfo`: {idx, disconnect, alive};
  - `BattleEvaluationInfo`: {evaluation_type, score}.
```
de 00 21                                   map16, 33 entries
  a9 69 73 5f 64 65 66 65 61 74  c2        "is_defeat": false
  ac 64 61 6d 61 67 65 5f 74 6f 74 61 6c  cd bc 52      "damage_total": uint16 48210
  b2 64 61 6d 61 67 65 5f 74 6f 74 61 6c 5f 70 61 72 74 79  cd bc 52   "damage_total_party": 48210
  a7 68 69 74 5f 6d 61 78  0c              "hit_max": 12
  a9 68 69 74 5f 74 6f 74 61 6c  39        "hit_total": 57
  …
  af 50 6c 61 79 65 72 43 68 61 72 61 63 74 65 72  90    "PlayerCharacter": []
  …
```
The client sends the party's **full computed status**: the same `CPersonStatusInfo` the server sends in `MissionStart`'s `BattleParameter.PlayerCharacter`. It also sends the enemies it saw and defeated, so the server had enough to sanity-check a result. What it checked is **[unknown]** (online-server.md section 5).

### SetCharacterDeco
`CCharacterDecoSendInfo` (`CParameterManager+0x8790`), serialized by `AsonSerializer::Serialize<CCharacterDecoSendInfo>` in the SetCharacterDeco request lambda. **[code]** for the keys and types; **[run]** `wire/deco-payload` serializes the live, empty object:
- `character_id` (u64), `hair_id` (u32), `pose_id` (u32);
- `CharacterDecoObject`, an array of `CCharacterDecoObjectInfo`:
  - `player_character_id` (u64), `index`, `master_deco_object_id`, `attach_type` (u32);
  - `attach_bone` (string);
  - `pos_x/y/z`, `rotate_x/y/z`, `slider_pos_x/y/z`, `slider_rotate_x/y/z`, `scale` (float → float64).
```
84                                          map(4)
  ac 63 68 61 72 61 63 74 65 72 5f 69 64  00      "character_id": 0
  a7 68 61 69 72 5f 69 64  00                     "hair_id": 0
  a7 70 6f 73 65 5f 69 64  00                     "pose_id": 0
  b3 43 68 61 72 61 63 74 65 72 44 65 63 6f 4f 62 6a 65 63 74  90   "CharacterDecoObject": []
```

## Our encoder (`server/include/soaserver/msgpack.h`)
The local server builds reply bodies with its own small encoder. It makes the same choices as the ASON writer:
- smallest integer forms;
- negative values as negative fixint or int8–64;
- doubles as float64;
- fixstr, str8, str16 or str32 by length;
- smallest array and map headers;
- string map keys, in insertion order.

**[run]** `wire/ason-roundtrip` encodes a response with nested maps, a list, an id-keyed map with a string key, a float, a negative int, a u64, a bool and nil. It feeds the bytes to the client's `ASON::DeserializeBinary`, re-serializes them with `ASON::Serialize`, and gets **byte-identical** output. The first bytes of that response, annotated (260 bytes in all):
```
82                                   map(2)
  a4 64 61 74 61                     "data"
  89                                 map(9)
    a4 54 69 6d 65  b3 32 30 32 31 … "Time": "2021-06-30 12:00:00"      (fixstr of 19: 0xa0 | 19 = 0xb3)
    a6 50 6c 61 79 65 72  85         "Player": map(5)
      a2 69 64  ce 07 5b cd 15         "id": uint32 123456789
      a4 6e 61 6d 65  a4 46 61 79 74   "name": "Fayt"
      a5 6c 65 76 65 6c  57            "level": 87                        (positive fixint)
      a3 66 6f 6c  ce 00 19 91 55      "fol": uint32 1675605
      ae 73 74 61 6d 69 6e 61 5f 75 70 64 61 74 65  b3 …   "stamina_update": "2021-06-30 11:58:00"
    b6 4d 69 73 73 69 6f 6e 52 65 73 75 6c 74 43 68 61 72 61 63 74 65 72  81   "MissionResultCharacter": map(1)
      aa 32 31 33 30 37 30 36 34 33 32   "2130706432"                      (id as a string key)
      82 a2 69 64 ce 7f 00 00 00 a5 6c 65 76 65 6c 3c   {"id": 2130706432, "level": 60}
    af 55 70 64 61 74 65 53 74 6f 63 6b 49 74 65 6d  91 82 …   "UpdateStockItem": [{"master_item_id": 3000000001, "count": 12}]
    a4 72 61 74 65  cb 3f f8 00 00 00 00 00 00      "rate": 1.5          (float64)
    a5 64 65 6c 74 61  d0 d8                        "delta": -40         (int8)
    a3 62 69 67  cf 11 22 33 44 55 66 77 88         "big": uint64 0x1122334455667788
    a4 66 6c 61 67  c3                              "flag": true
    a4 6e 6f 6e 65  c0                              "none": nil
  a6 73 74 61 74 75 73  00           "status": 0
```
Differences that don't matter to the client:
- Our decoder (`mp_decode`, used by server modules) turns integer map keys into decimal strings.
- The client never *sends* a map with integer keys.

## Open questions
- Whether the production server used the same encoder choices is **[unknown]**: the client accepts every standard form, so it didn't have to.
- The container name of every serialized array was read at run time only for the battle log and the deco payload. They are the only two request payloads.

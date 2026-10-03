# Committed test saves (sanitized)

Local-KVS saves (SharedPreferences XML, ChaCha20 like the game's; `python -m soa_save dump FILE` reads them) that the tests and tools of all three programs use. The port, `soa-server` and the 3.7.0 emulator all read these, not the untracked personal saves in `samples/` or `work/`.

| File | What | Used by |
|---|---|---|
| `seed/Game.xml` | A real 3.7.0 player at the end of service (rank 87, "Fayt"). `soa-server` / `soa` seed a new server state from it. | `server/src/state/seed.cpp` `real_seed_save()` (the default seed of `soa`, `soa-server` and so the emulator's sessions); `tests/test_kvs.py` |
| `client/Game.xml` | A client-side save with every character unlocked | the port's session scripts (`port/scripts/*_session.sh` install `client/Game.xml` through `phone370_client_save`, which clears its `BAS:DownloadEpisodeFlag`, 7 = Episodes 1-3, to 0 unless `SOA_EPISODE_PACKS=1`: the file itself keeps 7; port/scripts/phone370.sh); `tests/test_saves.py` |
| `client/Aska.xml` | The device store: version, crc, device UUID | as above |

## What was sanitized
- **`seed/Game.xml`** is `samples/Game.xml` with `BAS:PlayerID` set to `LOCAL00001`, the server's sanitized player id. Nothing else changed: a dump differs in that one entry.
- **`client/Game.xml`** already carried the placeholder `BAS:PlayerID` `AAAAAAAAAA`. It's unchanged, because the sessions' screenshot baselines were taken with it.
- **`client/Aska.xml`** has the device UUID replaced with `00000000-0000-4000-8000-000000000001`.

The remaining strings are game state: names, stage ids, the default chat comment.

**Re-checking:** compare a dump against the source save. Only the fields listed above may differ.

**Rule:** never commit a real player id, device UUID or account token, here or anywhere else (code, tests, docs, commit messages). Tests assert the sanitized values, not that they differ from real ones.

**Editing:** use `python -m soa_save set FILE KEY VALUE [--type str] -o OUT` to change a value. It re-encrypts correctly.

# server/tests: the server's unit tests and replay corpora

Run with `build/server/soa-server --selftest [FILTER] [--shuffle N]` (no game needed; `soa --selftest` runs the library's after its own). 91 tests today: 70 `server/…`, 7 `cdn/…`, 14 `net/…`. Each test's random seed comes from its name (`soaserver/testing.h` `seed_for`), so filtering, adding or moving tests doesn't change another test's inputs; `--shuffle N` runs them in a shuffled order to find tests that depend on what an earlier one left behind.

| Path | What |
|---|---|
| (library tests) | not here: since step R5 every library test lives beside the code it tests, in `../src/<folder>/*_tests.cpp` or at the end of its source file (e.g. `../src/core/modules_tests.cpp`, `../src/api/sphere211/sphere211_tests.cpp`; step R8 moved the 14 at the end of `../src/core/server.cpp` beside their domains). This folder keeps the cross-cutting ones: the wire layer's and the replay corpora |
| `net/` | the wire layer's tests (soa-server only): decoder round trips for every layout, the client's own request packets (`client_requests.txt`), HTTP, `net/loopback` (a whole session over loopback), `net/cdn-loopback`, `net/cdn-in-memory` |
| `ninja/` | the Ninja vectors (`ninja_vectors.txt`, 700 envelopes made by the client's own code) and their test; `ninja_check.*` a stand-alone cipher CLI; `tools/` the unicorn harness that regenerates the vectors (needs `work/`'s lib) |
| `replay/` | the replay corpora for `tools/server_replay_diff.sh` (RG4 of `server/PLAN-readability.md`): recorded request sequences replayed by two builds and compared ([replay/README.md](replay/README.md)) |

The library tests (`../src/`) use scratch servers: a state DB under `/tmp` seeded from the committed synthetic `port/server-data/test-seed.xml` with `data/basmaster-3.7.0.sqlite3` (`ext::with_scratch_server`, `soaserver/scratch.h`). Tests that need the game or the port are the port's: `port/src/native/api/zz_server_guest_test.cpp`, run by `soa --selftest "server/"`.

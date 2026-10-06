# server/src/testing: the library's test support

`testing.cpp`: the test registry and runner behind `soaserver/testing.h` (`NATIVE_TEST` in the library's sources, `soa-server --selftest [FILTER] [--shuffle N]`, and `soa --selftest` after the port's own tests). Seeds come from the test names (`seed_for`), so moving or filtering tests doesn't change their inputs; the run order is the link order (`../../CMakeLists.txt`: the sources by path).

`scratch.{h,cpp}`: the one scratch server the tests run on (`ScratchServer`: a `Server` on a fresh state DB under the platform temp dir (soa::temp_dir()), seeded from `server/tests/fixtures/test-seed.xml`, with the 3.7.0 master; `live` false), behind the library's own tests, `ext::with_scratch_server` (a module's tests: no gacha pools, the run's `--fail` / surprise options off) and `testing::Scratch` (`soaserver/scratch.h`, tests outside the library); `scratch_inputs` and `test_master`.

`module_test.h`: helpers for a module's tests on `ext::with_scratch_server`'s `ext::Ctx` (`module_test::call`: a registered handler with arguments; `master_id`: a master row by its id_label; `player_load_data`: a full-state player response with every `OnPlayerLoad` hook's keys). Used by the presents, daily, favor (step R16) and deep space (R18) tests; `api/growth/growth_tests.cpp` and `rules/rules_tests.cpp` still carry their own copies.

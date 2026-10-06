# api/settings: settings and account

| File | What |
|---|---|
| `config.{h,cpp}` | the options (設定 > その他設定 / バトル設定): **GetConfig** (`get_config`), **UpdateConfig** (`update_config`; `args::UpdateConfigArgs`), **ResetConfig** (`reset_config`); `ConfigInfoList` (`config_info_list`, CConfigInfoList) on every full player load (`load_config`: `OnPlayerLoad`); for other modules `settings::config_value` / `config_on` and the labels `kOneTimeStorage`, `kOneTimeStorageExceptGacha` (the one-time storage options) |
| `account.cpp` | **GetBirthYearMonth** / **UpdateBirthYearMonth** (`args::UpdateBirthYearMonthArgs`: the wire's "YYYY-MM"), **ReadExpirationInfo**, **SendGuideInformation**; `register_settings()`, the module's register function (its three parts in order) |
| `scenario_library.cpp` | **GetScenarioLibraryInfoList** (`library_missions`: the cleared story missions of an episode type) |
| `settings.h` | the parts' register functions |
| `settings_tests.cpp` | `settings/config`, `settings/birth-year-month`, `settings/read-marks`, `settings/scenario-library` |

Every handler and hook carries the 2.5 doc block.

**Hooks and their order** (`../../core/modules.cpp`; `soa-server --list-hooks`): `settings`, the last module: its seven APIs and its `OnPlayerLoad` (`ConfigInfoList`, after every other module's keys).

**State** (`server.sqlite3`; `../../state/schema.cpp` step 14): `config` (the options the player changed, by `master_config` id: value, type; no row: the master's default), `player.birth_year` / `birth_month` (NULL: never entered). The scenario library reads the core's `mission` and the campaign's `campaign_clear`.

**Rules**: docs/server-rules.md#settings-account (#settings, #account, #scenario-library).

**Proof and sessions**: the replay corpora `profile` (the options, the birth month, the read marks) and `campaign` (GetScenarioLibraryInfoList for Episode 1 and the world map); `port/scripts/settings_session.sh` (in-process and `--server`: 一時保管庫設定 kept over a restart and reset, シナリオライブラリ's chapters).

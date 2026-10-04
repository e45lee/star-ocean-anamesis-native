# api/presents: the present box and the achievements

| File | Module | What |
|---|---|---|
| `presents.{h,cpp}` | `presents` (core) | **PresentList** (the box: the unreceived presents with their line and deadline), **GetPresent / GetPresentArray** (receives them through `../../core/rewards.h` `grant`; PresentGetResult). `present_box_info` builds a CPresentBoxInfo (also the achievements' AddPresent) |
| `achievements.cpp` | `achievements` | **AchievementActiveList**, **AchievementReceive / AchievementListReceive / AchievementReceiveList**, the `Achievement` key of the full-state player responses (`OnPlayerLoad`), `ext::achievement_state` (the favor APIs' Achievement). `AchievementType`: the master_achievement types the server counts |
| `present_texts.cpp` | `present_texts` | the line the box shows for each present (`ext::present_text`: the present's stored `text`, else built from the `Present_box_*` / `Present_favor_1` texts; `ext::format_present`) |

**Hooks and their order** (`../../core/modules.cpp`; `soa-server --list-hooks`): the core's APIs register first (`presents`, `ext::add_core_api`); the `achievements` player-load hook runs second, right after `login_bonus` (`../daily/`) and before `daily`'s, so `Achievement` follows `LoginBonus` in the reply. `present_texts` registers only its table, last.

**State** (`server.sqlite3`; `../../../PLAN-schema.md` section 1): `presents` (`../../state/schema.cpp`: one row per present; `received_at` NULL while in the box; `text` the line stored with it (the login bonuses, the favor bonus; NULL: built from the reason), a table of its own, `present_texts`, until PLAN-schema S8; `content_id` NULL for the wallet types 3 / 4; `ext::add_present` writes them, MissionEnd's clear presents too, both through `ext::present_content_id`), `achievements` (the core's schema: id, progress (always written 0: progress is computed), received_at), and the counters the progress reads (`counters`, `core/ext.cpp` `ext::count`: `boost`, `limit_break`, `evolution*`, `weapon_boost`, `weapon_limit_break`, `accessory_boost`, `weapon_grade_up`, `exchange`; written by growth, items, shop). Progress also reads `gacha_history`, `mission`, `roster`, `player`, deep space's `ds_area` / `ds_log`, `favor`, and Sphere 211's state (`../sphere211/sphere211.h`).

**Rules**: docs/server-rules.md#presents-rules, docs/server-rules.md#present-list, docs/server-rules.md#present-box-lines, docs/server-rules.md#achievements, docs/server-rules.md#achievements-modules (under "Growth and economy"), "Favor achievements".

**Tests**: `presents_tests.cpp` (`presents/present-texts`), `achievements_tests.cpp` (`presents/favor-achievements`, `presents/achievement-chain`). **Sessions**: `port/scripts/restore_session.sh` (the box after a battle), `home_session.sh` (the 実績 screen), `deepspace_session.sh` (一括達成).

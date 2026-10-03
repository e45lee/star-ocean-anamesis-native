# api/daily: the login bonuses

| File | Module | What |
|---|---|---|
| `login_bonus.cpp` | `login_bonus` | the login bonus (`OnPlayerLoad`: LoginBonus, a page a login day into the present box) and the default `Player.tutorial_status`. Its page rule is `growth_rules::next_login_day` (`../../rules/growth_rules.{h,cpp}`) |
| `premium_and_favor_bonus.cpp` | `daily` | the premium login bonus (a pass = `Grant` content type 11; `OnPlayerLoad`: PremiumLoginBonus), the favor login bonus (`OnPlayerLoad`: FavorBonusContetsResultInfo, the favor Player keys) and **StaminaHealByFavor** |

The achievements are `../presents/achievements.cpp`.

**Hooks and their order** (`../../core/modules.cpp`; `soa-server --list-hooks`): `login_bonus`'s player-load hook is the first module hook (so its default `Player.tutorial_status` is set before the others read the Player map), then `achievements`', then `daily`'s.

**State**: `login_bonus` (id, day = the last page granted, last_at; the core's schema), `player.login_bonus_popup_pending` (a counters key before PLAN-schema S3), `premium_pass` and `favor_bonus_state` (`daily`'s schema); the presents go to `presents` (with their line in `text`; `../presents/`). The favor levels come from `../favor/favor.h`.

**Rules**: docs/server-rules.md "7. Login bonus", "Login bonus" (under "Growth and economy"), "Premium and favor login bonuses".

**Tests**: `daily_tests.cpp` (`daily/login-bonus`: day 1, no second grant, day 2; `daily/premium-favor-bonus`). **Sessions**: `port/scripts/restore_session.sh`, `restore_favor_session.sh`, `home_session.sh` (the login popup).

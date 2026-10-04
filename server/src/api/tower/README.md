# api/tower: the tower (試練の遺跡)

| File | Module | What |
|---|---|---|
| `tower.{h,cpp}` | `tower` (opt-in `--restore-tower`) | the tower lists (`lists`: `ActiveTowerMissionList`, `TowerSchedule`, `Player.tower_try_count`; each area's floors by `area_floors`), the stand-in banners (`standin_banner_image`, `area_banner_ok`, `client_banners`) |

- **Hooks, in their order** (`../../core/modules.cpp`; `soa-server --list-hooks`): `OnPlayerLoad` (`load_tower`: the lists on every full player state), `MissionResultExtra` (`tower_mission_result`: the lists again after a tower battle's MissionEnd, `MissionType::kTower`), `ClientMaster` (`client_tower_banners`: the stand-in `master_banner` rows in the client's master copy). Every hook does nothing without `--restore-tower`. No APIs: the battles are the core MissionStart / MissionEnd (`../missions/`) of `master_tower_mission` rows.
- **State:** none of its own; it reads `mission` (cleared floors) and `play` (the last floor played).
- **Rules:** docs/server-rules.md#tower; the client side: docs/client-changes.md "Tower".
- **Log lines scripts read:** `tower: N areas, N missions listed`, `tower: stand-in banner ...` (tower_session.sh).
- **Tests:** `tower_tests.cpp` (`tower/banner`, `tower/client-master`, `tower/lists`). **Proof:** the replay corpus `server/tests/replay/tower`. **Session:** `port/scripts/tower_session.sh`.

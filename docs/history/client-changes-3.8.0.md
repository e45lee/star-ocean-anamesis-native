# client-changes.md: the 3.8.0 port's notes (history)

Text moved out of `docs/client-changes.md` on 2026-10-01 (agent no380-docs), when the port had moved to the 3.7.0 client (tag `pre-rebase-370` is the 3.8.0 port). The full entries of the 3.8.0 port (the restore image, the restored login / tutorial groups, favorability, the home and menu workarounds, the story campaign's client hooks, the 3.7.0 texts insert) are in the history of `docs/client-changes.md` at that tag. The library differences are in `libsoa-3.7.0-vs-3.8.0.md`.

- **Entry format.** Each entry said "what the 3.8.0 code does"; the port's entries now describe the 3.7.0 code ("Guest behaviour").
- **`IApiCaller::EndMissionTalk`.** Before the rebase's revision 2 the 3.8.0 port did what the FakeApiCaller route's `h_end_mission_talk` does now from a `CEventScenario::Exit` hook (`restore_campaign.cpp`), 3.8.0 having dropped the request. 3.7.0's `CEventScenario::Exit` sends it itself.
- **The login popups.** Until H (2026-10-01) the in-process server also called `AddPopup(3)` itself: a 3.8.0-era workaround, since 3.8.0's login no longer armed the popups. 3.7.0's `CPhase_Login::Progress` arms them (mask 0x7b), and that call is gone.
- **The tower.** The 3.8.0 port's `IsOpenTowerMission` entry compared it with 3.8.0's; it returns 0 in both.
- **The save sync.** The 3.8.0 client showed the summary cached in its save (`Game.xml`) at home, over what the boot response (`NoLoginStart`) sent, and its `Load_PlayerInfo` also read `player_home_pc_roleid`; the server's `sync_save` was written for that.

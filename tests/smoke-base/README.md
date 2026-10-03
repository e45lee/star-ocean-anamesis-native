# Smoke baselines

The port's screenshot baselines for `port/scripts/smoke.sh` / `smoke.py` (title, home, character list, detail, other; 3.7.0 client, 729x1296), also used as `REF` by the home, restore, events and tower sessions and by `port/scripts/smoke_vs_emu.sh` (checked against `soa-emu`).

Committed 2026-10-03 (were untracked in `work/port-test/smoke-base/`). To re-baseline: run `port/scripts/smoke.sh build/port/soa OUT` without a baseline, check the screens against `smoke_vs_emu.sh`, then replace these files in one commit that says why.

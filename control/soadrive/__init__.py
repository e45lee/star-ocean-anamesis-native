"""soadrive: the driver library shared by the port (soa), the 3.7.0 emulator (soa-emu + soa-server)
and their tests (docs/history/PLAN-consolidate.md; control/README.md "soadrive").

  fifo        the control FIFO (send commands, wait for screenshots)
  proc        processes (timeout -k, PID, process group, RSS cap), free ports, repo_file
  milestones  waiting on logs: whole-file predicates, the LOG.pos cursor, poll, tap_until_log
  screens     RMSE, probes, settled screenshots
  popups      the login popups and the name dialog
  state       the server's state DB as data (tests/diff's comparison)
  ui370       the 3.7.0 UI's tap points by name
  targets     a client + server started fresh (emu, port-server, port-inproc) and the Run API flows drive
  prepared    prepared server states (a replay corpus cut at a request)
  flows/      named flows (tests/diff's flows and shards; the sessions compose them)

Callers: tests/diff (difftest.py), control/flowctl.py and soactl.py (thin CLIs), control/run.py
(the named sessions behind port/scripts/*_session.sh and emulator/scripts/*.sh).
"""

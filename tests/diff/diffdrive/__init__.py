"""diffdrive: the driver of the port-vs-emulator differential flows (tests/diff/).

Laid out the way control/PLAN-consolidate.md plans the shared driver library control/soadrive/
(proc, fifo, milestones, screens, state, ui370, targets, flows/), so that the flows can move there
unchanged once it exists: nothing here knows about tests/diff's report except compare.py.
"""

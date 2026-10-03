#!/usr/bin/env python3
# Moved to control/flowctl.py (the control layer shared by soa, soa-emu and soa-viewer).
# This stub forwards to it for scripts and branches that still use the old path; remove it once
# nothing does.
import os
import runpy
import sys

_new = os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", "..", "control", "flowctl.py")
sys.argv[0] = _new
runpy.run_path(os.path.normpath(_new), run_name="__main__")

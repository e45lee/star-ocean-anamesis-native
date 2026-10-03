// Port-only debugging/reachability hooks, driven from the --control FIFO (see port/README.md,
// "Reaching battle, gacha and the debug windows"). None of this is game behaviour; nothing
// happens unless a control command asks for it.
#pragma once
#include <string>

#include "core/cpu.h"

namespace soa::native::port_debug {

// Handles a control command ("phase:N", "call:SYMBOL[:ARG...]"); false if it isn't one.
// Commands are queued and run on the game thread from CPhase::Progress.
bool command(const std::string& cmd);

// Called by the CPhase::Progress wrapper (game thread, once per frame) before the phase runs.
void on_phase_progress(u64 phase_mgr);

}  // namespace soa::native::port_debug

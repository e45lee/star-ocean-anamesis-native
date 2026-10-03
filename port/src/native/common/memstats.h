#pragma once
// Memory diagnostics (--memstats / control "memstats"); see memstats.cpp.
#include "core/cpu.h"

namespace soa::native::memstats {

// options().memstats: 0 off, 1 a snapshot per phase change, S > 1 also every S seconds.
int mode();
// One snapshot to the log (I/memstats), labelled `why`. Game thread (it calls the guest heap's
// CalcFreeSize).
void log(const char* why);
// From the native CPhase::Progress (port_debug::on_phase_progress) with the current phase id.
void on_phase(u32 phase);

}  // namespace soa::native::memstats

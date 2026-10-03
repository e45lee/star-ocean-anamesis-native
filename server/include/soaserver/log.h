#pragma once
// The local server's log output (library code). The server formats its lines and hands them to a
// sink: soa installs one that forwards to its own log (port/src/native/api/server_adapters.cpp);
// without one (soa-server), lines go to stderr as "I/tag: message".
namespace soa::server {

enum class LogLevel { Trace, Debug, Info, Warn, Error };

// Writes one formatted line (no trailing newline).
using LogWriteFn = void (*)(LogLevel level, const char* tag, const char* msg);
// Whether lines of `level` are wanted at all (the server then skips formatting them).
using LogEnabledFn = bool (*)(LogLevel level);

// nullptr restores the default (stderr; Info and above).
void set_log_sink(LogWriteFn write, LogEnabledFn enabled = nullptr);

bool log_enabled(LogLevel level);
void log_write(LogLevel level, const char* tag, const char* fmt, ...) __attribute__((format(printf, 3, 4)));

}  // namespace soa::server

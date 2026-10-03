#pragma once
#include <cstdarg>
#include <cstdint>
#include <cstdio>
#include <cstdlib>

namespace soa {

enum class LogLevel { Trace, Debug, Info, Warn, Error };

extern LogLevel g_log_level;

void log_write(LogLevel lvl, const char* tag, const char* fmt, ...) __attribute__((format(printf, 3, 4)));
[[noreturn]] void fatal(const char* fmt, ...) __attribute__((format(printf, 1, 2)));

}  // namespace soa

#define LOGT(tag, ...) do { if (::soa::g_log_level <= ::soa::LogLevel::Trace) ::soa::log_write(::soa::LogLevel::Trace, tag, __VA_ARGS__); } while (0)
#define LOGD(tag, ...) do { if (::soa::g_log_level <= ::soa::LogLevel::Debug) ::soa::log_write(::soa::LogLevel::Debug, tag, __VA_ARGS__); } while (0)
#define LOGI(tag, ...) ::soa::log_write(::soa::LogLevel::Info, tag, __VA_ARGS__)
#define LOGW(tag, ...) ::soa::log_write(::soa::LogLevel::Warn, tag, __VA_ARGS__)
#define LOGE(tag, ...) ::soa::log_write(::soa::LogLevel::Error, tag, __VA_ARGS__)

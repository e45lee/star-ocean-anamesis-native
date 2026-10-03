#pragma once
// The LOG* spelling inside the server library (internal header): lines go to the embedder's sink
// (soaserver/log.h). Never include this next to the port's core/log.h.
#include "soaserver/log.h"

#define LOGT(tag, ...)                                                                                                                              \
    do {                                                                                                                                            \
        if (::soa::server::log_enabled(::soa::server::LogLevel::Trace)) ::soa::server::log_write(::soa::server::LogLevel::Trace, tag, __VA_ARGS__); \
    } while (0)
#define LOGD(tag, ...)                                                                                                                              \
    do {                                                                                                                                            \
        if (::soa::server::log_enabled(::soa::server::LogLevel::Debug)) ::soa::server::log_write(::soa::server::LogLevel::Debug, tag, __VA_ARGS__); \
    } while (0)
#define LOGI(tag, ...) ::soa::server::log_write(::soa::server::LogLevel::Info, tag, __VA_ARGS__)
#define LOGW(tag, ...) ::soa::server::log_write(::soa::server::LogLevel::Warn, tag, __VA_ARGS__)
#define LOGE(tag, ...) ::soa::server::log_write(::soa::server::LogLevel::Error, tag, __VA_ARGS__)

// The response envelope and the refusal path (core/response.h; port code, not guest behaviour).
#include "core/response.h"

#include <cstdarg>
#include <cstdio>

#include "core/log.h"

namespace soa::server::ext {

std::vector<u8> body(Value data, u32 status) {
    Value root = Value::object();
    root["data"] = std::move(data);
    root["status"] = status;
    return mp_encode(root);
}

std::vector<u8> with_player_state(Ctx& c) { return body(c.base_data()); }

std::vector<u8> refuse(Ctx& c, const char* method, const char* why, u32 code) {
    LOGW("server", "%s refused: %s (error %u)", method, why, code);
    c.set_error(code);
    return with_player_state(c);
}

}  // namespace soa::server::ext

namespace soa::server::ext {

std::vector<u8> refusef(Ctx& c, const char* method, ErrorCode code, const char* why_fmt, ...) {
    char why[512];
    va_list ap;
    va_start(ap, why_fmt);
    vsnprintf(why, sizeof why, why_fmt, ap);
    va_end(ap);
    return refuse(c, method, why, code);
}

}  // namespace soa::server::ext

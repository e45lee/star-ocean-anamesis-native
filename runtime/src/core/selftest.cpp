// Runtime self-test registry (see selftest.h).
#include "core/selftest.h"

#include <cstdarg>
#include <cstdio>

namespace soa {

static std::vector<RuntimeTest>& registry() {
    static std::vector<RuntimeTest> t;
    return t;
}

bool register_runtime_test(const RuntimeTest& t) {
    registry().push_back(t);
    return true;
}

const std::vector<RuntimeTest>& runtime_tests() { return registry(); }

void RuntimeTestContext::fail(const char* fmt, ...) {
    char buf[1024];
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(buf, sizeof buf, fmt, ap);
    va_end(ap);
    failures_++;
    report_failure(buf);
}

}  // namespace soa

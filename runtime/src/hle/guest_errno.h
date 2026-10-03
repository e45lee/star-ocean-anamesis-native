#pragma once
// errno values as the guest (Linux / bionic) numbers them. The host's are Linux's on Linux (the
// identity); MinGW's CRT and winpthreads number everything above ERANGE (34) differently
// (ETIMEDOUT 138, EDEADLK 36, ...): port/PLAN.md 5b.
#include <errno.h>

namespace soa {

#ifdef _WIN32
int guest_errno(int host);
#else
inline int guest_errno(int host) { return host; }
#endif

}  // namespace soa

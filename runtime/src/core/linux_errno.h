#pragma once
// errno as the guest (Linux / bionic) numbers it (port/PLAN.md 5b; code review 2026-10-06 R2).
//
// Host code (HLE imports, natives) sets the host's errno with the host's constants, the same code on
// both hosts. What the guest reads through __errno (guest_errno_location):
//   - Linux: the host's errno; the numbers are the same.
//   - Windows: the thread's own guest errno. MinGW's CRT and winpthreads number everything above
//     ERANGE (34) differently (ETIMEDOUT 138, ENOSYS 40, ...), so the thunk dispatch (core/cpu.cpp)
//     clears the CRT's errno before every host function the guest calls (an import, a native) and,
//     when the function set it, stores linux_errno(errno) as the guest's errno. A host function
//     that sets nothing leaves the guest's value alone, as a successful libc call does.
// Results that are error numbers (the pthread functions') are translated with linux_errno() too.
#include <errno.h>

namespace soa {

#ifdef _WIN32
int linux_errno(int host);
// A Winsock error (WSAGetLastError()) as the CRT's errno constant (EIO for the others).
int host_errno_of_wsa(int wsa);
#else
inline int linux_errno(int host) { return host; }
#endif

// The calling thread's guest errno: what __errno returns.
int* guest_errno_location();

}  // namespace soa

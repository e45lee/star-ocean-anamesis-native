#pragma once
// cpp-httplib (vcpkg cpp-httplib), included first in a translation unit (it includes winsock2.h,
// which must come before windows.h). On Windows the target compiles with _WIN32_WINNT=0x0A00
// (soa_httplib_win, cmake/flags.cmake), and mingw-w64's ws2tcpip.h (11.0) lacks the declaration of
// GetAddrInfoExCancel, which its libws2_32.a exports and httplib's non-blocking name lookup calls.
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
extern "C" INT WSAAPI GetAddrInfoExCancel(LPHANDLE lpHandle);
#endif
#include <httplib.h>

#pragma once
// NATIVE_TEST for the server library's own test sources (the port's spelling; see testing.h).
// Never include this next to port/src/native/common/test.h.
#include "soaserver/testing.h"

#define NATIVE_TEST(name) SOASERVER_TEST(name)

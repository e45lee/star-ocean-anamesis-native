#pragma once
// Is the libSOA.so being run the build the natives were made for?
//
// The natives and their generated tables (gen/<s>_addresses.h, api/gen/*.inc, params/gen/*.inc) hold
// 3.7.0 vaddrs: on another build a missing symbol would fail loudly, but a wrong vaddr would read or
// write the wrong memory. So soa compares the lib's sha256 with the one the tables were generated
// from (kLibSha256, native/common/gen/common_addresses.h) and refuses natives on a mismatch
// (main.cpp: only --natives none runs such a lib). A new build is a regeneration
// (tools/check_generated.py lists the generators).
#include <string>

namespace soa::native {

// The sha256 of the file at `path` (lowercase hex), or "" when it can't be read.
std::string file_sha256(const std::string& path);
// The sha256 the natives' tables were generated from.
const char* expected_lib_sha256();
// True when the file at `path` is that build; else false, with its sha256 in *got ("" unreadable).
bool lib_matches(const std::string& path, std::string* got = nullptr);

}  // namespace soa::native

#pragma once
// Crash reports end to end (crash_test.cpp), run from soaruntime_tests' main.
void run_crash_tests(void (*check)(bool ok, const char* what));
// soaruntime_tests --crash-demo overflow|null: crashes a guest thread (the child of those tests).
int run_crash_demo(const char* kind);

#pragma once
// The GDB stub's tests (gdbstub_test.cpp), run from soaruntime_tests' main.
void run_gdbstub_tests(void (*check)(bool ok, const char* what));
// soaruntime_tests --gdb-demo HOST:PORT [--fault] [--native] [--at-leaf] [--slow-park]: the test's
// guest loop with the stub listening (gdbstub_test.cpp says what each option does).
struct GdbDemoOptions {
    bool fault = false, native = false, at_leaf = false, slow_park = false;
};
int run_gdb_demo(const char* addr, const GdbDemoOptions& o);

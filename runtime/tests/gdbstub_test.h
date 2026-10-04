#pragma once
// The GDB stub's tests (gdbstub_test.cpp), run from soaruntime_tests' main.
void run_gdbstub_tests(void (*check)(bool ok, const char* what));
// soaruntime_tests --gdb-demo HOST:PORT [--fault] [--native]: the test's guest loop with the stub
// listening.
int run_gdb_demo(const char* addr, bool fault, bool native);

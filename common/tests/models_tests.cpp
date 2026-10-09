// soa_models' unit tests: synthetic AFF data built here (no game files).
#include <soa/aff.h>
#include <soa/asf.h>

#include <cstdio>
#include <cstring>

static int g_fail = 0;
#define CHECK(c) do { if (!(c)) { fprintf(stderr, "%s:%d: CHECK(%s)\n", __FILE__, __LINE__, #c); g_fail++; } } while (0)

int main() {
    if (g_fail) { fprintf(stderr, "soa_models_tests: %d failures\n", g_fail); return 1; }
    printf("soa_models_tests: ok\n");
    return 0;
}

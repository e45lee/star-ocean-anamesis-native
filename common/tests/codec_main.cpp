// soa_codec_tests: the unit tests of soa_codec (common/include/soa/: base64.h, prefs_xml.h). Each
// file's checks print "ok" / "FAIL" lines; the exit status is the number of failures.
#include <cstdio>
#include <string>

#include "codec_check.h"

int g_codec_failures = 0;
void codec_check(bool ok, const std::string& what) {
    fprintf(stderr, "%s  %s\n", ok ? "ok  " : "FAIL", what.c_str());
    if (!ok) g_codec_failures++;
}

void base64_tests();
void prefs_xml_tests();

int main() {
    base64_tests();
    prefs_xml_tests();
    fprintf(stderr, "%s (%d failures)\n", g_codec_failures ? "FAIL" : "all passed", g_codec_failures);
    return g_codec_failures;
}

"""tools/check_env_access.py, the T0 lint that keeps environment access in soa/env.h: calls are
found, comments and string literals aren't."""

import check_env_access as cea


def found(src):
    return [fn for _, fn in cea.violations("x.cpp", src)]


def test_calls_are_found():
    assert found('const char* e = getenv("SOA_X");') == ["getenv"]
    assert found('if (std::getenv ("A")) setenv("B", "1", 1);') == ["getenv", "setenv"]
    assert found('_putenv_s("A", "1"); SetEnvironmentVariableW(L"A", L"1");') == ["_putenv_s", "SetEnvironmentVariableW"]


def test_comments_and_strings_are_not():
    assert found('// getenv("SOA_X")\n/* setenv(a) */ int x;') == []
    assert found('t.fail("setenv (use RunOptions)"); char c = \'(\';') == []
    assert found('auto s = R"(getenv("X"))";') == []
    assert found('const char* n = "getenv(";  // a needle') == []
    assert found("my_getenv(x); env::env_str(\"A\");") == []


def test_line_numbers_survive_stripping():
    src = '/* a\n b */\n"x"\ngetenv("A");\n'
    assert list(cea.violations("x.cpp", src)) == [(4, "getenv")]


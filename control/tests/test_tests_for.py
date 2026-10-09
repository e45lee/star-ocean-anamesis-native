"""tools/tests_for.py's path rules on the committed tests/impact.json (pytest; no game, no build)."""

import tests_for


def names(*paths):
    return [t["name"] for t in tests_for.select(list(paths))[0]]


def test_docs_only_selects_nothing():
    assert names("docs/notes.md", "port/README.md") == []


def test_api_file_selects_a_covering_test():
    sel = names("server/src/api/gacha/gacha.cpp")
    assert "replay-parent" in sel
    assert any(n in sel for n in ("shard:gacha", "session:gacha", "diff-full"))


def test_server_core_is_broad():
    sel = names("server/src/core/server.cpp")
    assert "replay-parent" in sel and "shard:login" in sel and "shard:battle" in sel


def test_runtime_is_broad_with_smoke():
    sel = names("runtime/src/app/host.cpp")
    assert "smoke" in sel and "shard:login" in sel


def test_a_session_script_selects_itself():
    assert "session:growth" in names("port/scripts/growth_session.sh")


def test_a_check_with_an_area_selects_itself():
    assert names("data/english/master-en.tsv") == ["english-report"]
    assert "english-report" in names("tools/english_text.py")
    assert "english-report" not in names("tools/gate.py")


def test_a_session_module_selects_its_wrappers_test():
    sel = names("control/soadrive/sessions/battle.py")
    assert "session:battle" in sel and "shard:login" not in sel


def test_the_drivers_select_shards_smoke_and_a_session_per_program():
    sel = names("control/soadrive/targets.py")
    assert "shard:login" in sel and "smoke" in sel
    assert all(n in sel for n in tests_for.DRIVER_SESSIONS)


def test_declared_follows_a_wrapper_to_its_session():
    apis = {"MissionStart", "MissionEnd", "SaleGacha", "Login"}
    got = tests_for.declared("port/scripts/battle_session.sh build/port/soa {out} {tmp}", apis)
    assert {"MissionStart", "MissionEnd"} <= got


def test_the_comparison_tools_are_driver_changes():
    """The tools the drivers run at run time (the packet comparison behind every tests/diff verdict,
    the end-state check of every run) select the shards like the drivers themselves."""
    tools = tests_for.driver_tools()
    for t in ("tools/compare_packets.py", "tools/schema_inventory.py", "tools/compare_tutorial.py", "tools/make_test_seed.py"):
        assert t in tools
        sel = names(t)
        assert "shard:login" in sel and "smoke" in sel, (t, sel)
    assert "tools/gate.py" not in tools and "tools/tests_for.py" not in tools
    assert "shard:login" in names("tests/diff/compare.py")
    assert "shard:login" in names("soa_save/kvs.py")  # the drivers write the client saves with it


def test_the_negative_control_runs_when_the_drivers_change():
    assert "diff-negative" in names("tools/compare_packets.py")
    assert "diff-negative" not in names("runtime/src/app/host.cpp")


def test_regen_refuses_an_empty_api_list(tmp_path, monkeypatch):
    import pytest
    impact = tmp_path / "impact.json"
    impact.write_text("{}")
    monkeypatch.setattr(tests_for, "IMPACT", str(impact))
    monkeypatch.setattr(tests_for, "list_apis", lambda: {})  # a broken or missing soa-server
    with pytest.raises(SystemExit):
        tests_for.regen([])
    assert impact.read_text() == "{}"

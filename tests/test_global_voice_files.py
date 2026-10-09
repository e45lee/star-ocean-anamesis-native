"""tools/global_voice_files.py on a tiny synthetic Global master, JP master and download tree."""
import datetime
import sqlite3

import pytest


import global_voice_files as gv


def make_gl(path):
    c = sqlite3.connect(path)
    c.executescript("""
        create table master_text (id, serial_number, lang, message_id, text_value, text_kana, data_type,
                                  category_id, category_id_label);
        create table master_global (id, key, value);
        create table master_person (id, id_label, name_message_id, voice_parameter, voice_sound_package,
                                    gacha_voice_package, gacha_voice_queue);
        create table master_role (id, id_label, master_person_id, rarity, opened_at, master_skill1_id);
        create table master_event_area (id, id_label, voice_menu_pack_name, voice_menu_cue_min, voice_menu_cue_max);
        create table master_skill (id, id_label, se_sound_package, se_sound_package1);
        insert into master_global values (1, 's_end', '2019/11/6 14:00:00');
        -- a released character with an English voice actor
        insert into master_person values (10, 'cp0302_b01a', 'cp0302_b01a_message', 'voice_cp0302',
                                          'Voice_cp0302', 'Voice_GR_cp0302', 2021);
        insert into master_role values (100, 'role_cp0302_b01a', 10, 5, '2018-08-21 17:30:00', 7);
        -- a character in the data but scheduled after the end of service, no English VA
        insert into master_person values (11, 'cp0015_b01a', 'cp0015_b01a_message', 'voice_cp0015',
                                          'Voice_cp0015', 'Voice_GR_cp0015', 2021);
        insert into master_role values (101, 'role_cp0015_b01a', 11, 5, '2020-07-23 14:30:00', 0);
        -- an enemy
        insert into master_person values (12, 'cm129_b01c', 'cm129_b01c_message', 'voice_cm129', 'Voice_cm129',
                                          null, null);
        insert into master_event_area values (20, 'event_x', 'Voice_UI_100', 36001, 36003);
        insert into master_skill values (7, 'W16Ar_Rc05', null, 'Voice_cp0205');
        insert into master_text values (1, 1, 'en', 'cp0302_b01a_message', 'Sophia', null, 'system', 0, 'system');
        insert into master_text values (2, 1, 'ja', 'cp0302_b01a_message', 'ソフィア', null, 'system', 0, 'system');
        insert into master_text values (3, 1, 'en', 'cp0302_b01a_prmsg_10', 'Crystal Clarke', null, 'system', 0, 's');
        insert into master_text values (4, 1, 'en', 'cp0015_b01a_message', 'カーリン', null, 'system', 0, 'system');
        insert into master_text values (5, 1, 'ja', 'cp0015_b01a_message', 'カーリン', null, 'system', 0, 'system');
        insert into master_text values (6, 1, 'en', 'cp0015_b01a_prmsg_10', '【メモ】英語版の声優名が入る項目です',
                                        null, 'system', 0, 's');
        insert into master_text values (7, 1, 'ja', 'cm129_b01c_message', '敵', null, 'system', 0, 'system');
    """)
    c.commit()
    return c


def make_jp(path):
    c = sqlite3.connect(path)
    c.executescript("""
        create table master_person (id, id_label, voice_parameter, voice_sound_package, gacha_voice_package,
                                    home_voice_sound_package);
        create table master_role (id, id_label, master_person_id);
        insert into master_person values (1, 'cp0302_b01a', 'voice_cp0302', 'Voice_cp0302', 'Voice_GR_cp0302',
                                          'Voice_Home_cp0302');
        insert into master_role values (1, 'role_cp0302_b01a', 1);
    """)
    c.commit()
    return c


def run(tmp_path):
    make_gl(tmp_path / "gl.sqlite3").close()
    make_jp(tmp_path / "jp.sqlite3").close()
    dl = tmp_path / "dl"
    (dl / "Sound").mkdir(parents=True)
    (dl / "Parameter" / "Battle").mkdir(parents=True)
    (dl / "Sound" / "Voice_cp0302.spk").write_bytes(b"x")
    (dl / "Sound" / "Voice_cm129.spk").write_bytes(b"")  # zero size: not in hand
    (dl / "Parameter" / "Battle" / "voice_cp0302.msgp").write_bytes(b"x")
    txt, md = tmp_path / "out.txt", tmp_path / "out.md"
    gv.main(["--gl", str(tmp_path / "gl.sqlite3"), "--jp", str(tmp_path / "jp.sqlite3"), "--download", str(dl),
             "--apk", str(tmp_path / "none.apk"), "--txt", str(txt), "--md", str(md)])
    return txt.read_text().splitlines(), md.read_text()


def test_paths_and_en_companions(tmp_path):
    lines, _ = run(tmp_path)
    assert lines == sorted(set(lines))
    assert "Parameter/Battle/voice_cp0302.msgp" in lines
    assert "Sound/Voice_cp0302.spk" in lines and "Sound/Voice_GR_cp0302.spk" in lines
    assert "Sound/Voice_UI_100.spk" in lines and "Sound/Voice_cp0205.spk" in lines
    # the English dub only for the person with an English voice actor; never for the .msgp
    assert "Sound/Voice_cp0302-en.spk" in lines and "Sound/Voice_GR_cp0302-en.spk" in lines
    assert "Sound/Voice_cp0015-en.spk" not in lines and "Sound/Voice_cm129-en.spk" not in lines
    assert not any(x.endswith("-en.msgp") for x in lines)
    # the skill SE pack goes to the role that has the skill, so it gets an -en too
    assert "Sound/Voice_cp0205-en.spk" in lines


def test_markdown_status_and_presence(tmp_path):
    _, md = run(tmp_path)
    assert '<a id="ch-cp0302"></a>' in md and "(#ch-cp0302)" in md
    assert "### `cp0302` ソフィア / Sophia" in md
    assert "unreleased, scheduled 2020-07-23" in md and "released 2018-08-21" in md
    row = next(x for x in md.splitlines() if x.startswith("| `Sound/Voice_cp0302.spk`"))
    assert "| yes | download |" in row
    row = next(x for x in md.splitlines() if x.startswith("| `Sound/Voice_cm129.spk`"))
    assert "| no | no |" in row  # not named by JP, zero-size in the download
    row = next(x for x in md.splitlines() if x.startswith("| `Sound/Voice_cp0302-en.spk`"))
    assert "| no | no | (b)+(d) |" in row


def test_helpers():
    assert gv.en_companion("Sound/Voice_GR_cp0302_05.spk") == "Sound/Voice_GR_cp0302_05-en.spk"
    assert gv.is_language_pack("Sound/Voice_UI_100.spk")
    assert not gv.is_language_pack("Parameter/Battle/voice_cp0302.msgp")
    assert gv.norm("assets/builtin_data/Sound/etc2/hi/x.spk") == "Sound/x.spk"
    assert gv.parse_time("2019/11/6 14:00:00") == gv.parse_time("2019-11-06 14:00:00") == datetime.datetime(2019, 11, 6, 14)
    assert gv.parse_time(" 2019/1/2 ") == datetime.datetime(2019, 1, 2)
    assert gv.parse_time("") is None and gv.parse_time(None) is None
    with pytest.raises(ValueError):
        gv.parse_time("2019-11-06 14:00")
    assert gv.CODE.findall("TS_2014_090_0100_cp0003") == ["cp0003"]


def test_deterministic(tmp_path):
    (tmp_path / "a").mkdir()
    (tmp_path / "b").mkdir()
    a = run(tmp_path / "a")
    b = run(tmp_path / "b")
    assert a == b

"""The asset path rules: how a master column value becomes a file path, each with its evidence label
(docs/server-rules.md: (a) master data, (b) client-side evidence, (d) assumption) and a one-line
reason. Paths are logical: no ``etc2/`` quality folder (``display_path`` adds it for images)."""
from __future__ import annotations

from dataclasses import dataclass


@dataclass(frozen=True)
class PathRule:
    """A path template (``{}`` = the column value) with its evidence label and reason."""
    template: str
    label: str
    reason: str

    def path(self, name: str) -> str:
        return self.template.format(name)


IMAGE = PathRule("Image/{}.aif", "b", "libSOA 3.7.0 formats `Image/%s.aif` (docs/notes.md \"Image assets\")")
IMAGE_WITH_EXT = PathRule("Image/{}", "a", "master_stamp.resource_name already carries the extension")
SCRIPT = PathRule("Script/{}.msgp", "b", "CEventScenario::SetEventId formats `Script/%s.msgp`")
SCENARIO = PathRule("Scenario/{}.msgp", "b", "CEventScenario::SetEventId formats `Scenario/%s.msgp`")
BGM = PathRule("Sound/{}.aac", "d", "libSOA has `Sound/` and `.aac`; the concatenation is assumed")
SOUND_PACK = PathRule("Sound/{}.spk", "d", "libSOA has `Sound/` and `.spk`; the concatenation is assumed")
CHARACTER_MODEL = PathRule("Character/{}.asf", "b", "the person resource fields (docs/notes.md \"Characters\")")
CHARACTER_ANIMATION = PathRule("Character/{}.acf", "b", "the person resource fields")
MOTION_PACKAGE = PathRule("Motion/{}.apk", "b", "the person resource fields")
CHARACTER_PACKAGE = PathRule("Character/{}.apk", "b", "the person resource fields")
WEAPON_MODEL = PathRule("Weapon/{}.asf", "b", "docs/notes.md \"Resource names\"")
DECO_MODEL = PathRule("Deco/{}.asf", "b", "docs/notes.md \"Resource names\"")
DECO_ANIMATION = PathRule("Deco/{}.aaf", "b", "docs/notes.md \"Resource names\"")
UNIVERSE_CHIP = PathRule("Image/u_chip_{}.aif", "d", "from the names of the existing chips")

#: A battle map is three files; `battle_files` loads them in this order (b).
MAP_EXTENSIONS = ("asf", "aaf", "acf")
#: The part of a map's kind text naming the file, e.g. "gacha scene map (.asf)".
MAP_PART = {ext: f"(.{ext})" for ext in MAP_EXTENSIONS}


def map_files(map_name: str) -> list[tuple[str, str]]:
    """(extension, path) of a battle map's three files `BG/<map>.asf/.aaf/.acf` (b)."""
    return [(ext, f"BG/{map_name}.{ext}") for ext in MAP_EXTENSIONS]


#: The four person resource fields (b, docs/notes.md "Characters"):
#: (master_person column, rule, kind for an enemy, kind for a playable character).
PERSON_RESOURCES = (
    ("asf", CHARACTER_MODEL, "enemy model", "character model"),
    ("acf", CHARACTER_ANIMATION, "enemy animation set", "character animation set"),
    ("apk", MOTION_PACKAGE, "enemy motion package", "character motion package"),
    ("unique_apk", CHARACTER_PACKAGE, "enemy unique package", "character unique package"),
)

#: Character portraits `Image/<code>_<kind><variant>.aif` (d, from the names: 302 of 307 playable
#: persons have all five): (kind, what it is).
PORTRAIT_KINDS = (("fl", "full-figure art"), ("ic", "icon"), ("fv", "face"), ("cs", "cut-in / status art"),
                  ("ca", "card art"))
#: A person label `<code>_b<variant>` (`cp0010_b03a`); suffixed persons (`_2`) share the portraits.
PERSON_LABEL_RE = r"(c[pc]\d+)_b(\d+[a-z])"

#: Person voice columns -> Sound/<x>.spk (listed, never blocking).
PERSON_VOICE_PACKS = (("voice_sound_package", "battle voice pack"), ("menu_voice_sound_package", "menu voice pack"),
                      ("home_voice_sound_package", "home voice pack"),
                      ("home_voice_sound_package_sub", "home voice pack (sub)"),
                      ("gacha_voice_package", "gacha voice pack"))


def display_path(path: str) -> str:
    """The path as the download stores it: images live in the `etc2/` texture-format folder."""
    return path.replace("/", "/etc2/", 1) if path.startswith("Image/") else path


#: The document's "Path rules" table: (reference, file, label and evidence).
PATH_RULES_TABLE = (
    ("image columns (`bg_resource`, `master_banner.image`, `image1..4`, `image_resource`, `boss_icon`, `enemy_icon`)",
     "`Image/etc2/<name>.aif`",
     "(b): libSOA 3.7.0 has the format `Image/%s.aif`; docs/notes.md \"Image assets\": the "
     "game loads `\"Image/\" + name + \".aif\"`, the `etc2/` folder is the texture-format directory of the asset "
     "manager; the ADLD key is CHash32 of `Image/etc2/<name>.aif` (verified here: the size reader decrypts "
     "existing files with exactly that key). The join `master_gacha.banner_id` = `master_banner.id_label` is (a) "
     "and the list-banner use is (b) (docs/server-rules.md#enabling-events)"),
    ("`talk_event_id_label`, `talk_message_file`", "`Script/<x>.msgp`, `Scenario/<x>.msgp`",
     "(b): `EventScenario::CEventScenario::SetEventId` formats `Script/%s.msgp` and `Scenario/%s.msgp` "
     "(docs/notes.md; both strings are in libSOA 3.7.0)"),
    ("`master_mission_stage.master_map_id`", "`BG/<map>.asf` / `.aaf` / `.acf`",
     "(b): `battle_files` loads the three, the map first mapped through `master_replace_resource` res_type 4 "
     "(docs/notes.md \"Resource names\")"),
    ("enemy persons (`master_enemy_party` → `master_enemy_base_parameter` → `master_person`)",
     "`Character/<asf>.asf`, `Character/<acf>.acf`, `Motion/<apk>.apk`, `Character/<unique_apk>.apk`",
     "(a) the join; (b) the four person resource fields (docs/notes.md \"Characters\")"),
    ("`stage_bgm`, `voice_menu_pack_name`", "`Sound/<x>.aac`, `Sound/<x>.spk`",
     "(b) only partly: libSOA 3.7.0 has `Sound/`, `.aac` and `.spk`; (d) the concatenation, backed by the "
     "presence counts below"),
    ("`master_gacha.resource_replace_group_id`", "`BG/<replace_res>.*`",
     "(a) `master_replace_resource`; (b) `CResourceReplaceManager::GetResourceName(id, 4)` replaces the gacha "
     "map `bg99_01`"),
)


# ---------------------------------------------------------------- stand-ins
#: Would a made-up stand-in (like standin-assets/) make the thing usable? By path prefix / suffix;
#: the first match wins, anything else is 3D data.
STANDIN_VERDICTS = (
    (("Image/", ""), "yes (2D image)"),
    (("Sound/", ".aac"), "yes (any BGM)"),
    (("Sound/", ""), "partly (cue ids)"),
    (("Script/", ""), "partly (end scene)"),
    (("Scenario/", ""), "partly (text)"),
)
STANDIN_VERDICT_3D = "no (3D)"

STANDIN_LEGEND = ("Stand-in? **yes (2D image)**: a made-up image in the game's format shows in its place, as the "
                  "existing `standin-assets/` ones do; **yes (any BGM)**: another track under this name plays; "
                  "**partly (cue ids)**: a pack with the same cue ids (silent or borrowed lines) satisfies the "
                  "player; **partly (end scene)**: a minimal script that ends the scene lets the mission complete, "
                  "the story is lost; **partly (text)**: placeholder lines for the script's message ids; **no (3D)**: "
                  "a map, model or motion set, where a stand-in could only be another one under this name.")


def standin_verdict(path: str) -> str:
    """Would a made-up stand-in (like standin-assets/) plausibly make the thing usable?"""
    for (prefix, suffix), verdict in STANDIN_VERDICTS:
        if path.startswith(prefix) and path.endswith(suffix):
            return verdict
    return STANDIN_VERDICT_3D

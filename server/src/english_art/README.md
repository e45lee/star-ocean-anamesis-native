# english_art: the English UI art and the layout labels

The `-en` images the CDN serves with `--english` (PLAN-english.md Q4, E9; docs/english.md section 8):
the game's own scenes and images, rebuilt from the user's download with English text drawn over
the Japanese, from the committed recipes in `standin-assets-en/recipes/*.json`. No game art is in
git or in the packages. Public API: `soaserver/english_art.h` (`english_art::build`).

The same build gives the scenes with fixed Japanese labels their `-en` copy (docs/english.md 7.14,
docs/server-rules.md#english-labels): `Options::labels` (Japanese -> English, from
`data/english/labels.tsv` and the English tables: `english::resolve_labels`) is looked up in every
`UI/` and `TalkScene/` scene's node trees (`.msgp`); a scene with one is rewritten (the labels' `str`
values replaced in the raw msgpack stream, the ISF image laid out again) into one `-en` file with the
recipe's atlas edit when it has a recipe.

| File | What |
|---|---|
| `art.h` | the internal pieces: `Canvas`, `Font`, `Style`, `Label`, `Recipe`, the drawing functions |
| `build.cpp` | `build()` (recipes, sources, stamps, outputs) and `apply_recipe()` (decode, draw, re-encode the changed 4x4 blocks, ISF sum, SLZ, ADLD) |
| `render.cpp` | text in the game font (`\n` lines, bold, scale, squeeze / shrink), outline / glow / shadow, `inpaint` |
| `font.cpp` | `Font/etc2/font.fpk`: the glyph table and the page's alpha |
| `recipe.cpp` | the recipe JSON (nlohmann-json): strict keys, named styles |
| `labels.cpp` | the layout labels: `rewrite_labels`, a walk of the raw msgpack stream that replaces `LabelText` / `ButtonText` strings and copies every other byte |
| `labels_tests.cpp` | `--selftest english-art/labels`: the walk, the ISF repack, a build on a synthetic download |
| `english_art_tests.cpp` | `--selftest english-art/` |

The codecs (SLZ, ISF, AIF, ETC2 / EAC) are `common/` `soa/aska_image.h`, shared with `tools/aif2png`.
`build/tools/english_art/english-art --out DIR --png DIR [--labels TSV]` runs the build without a server, for writing recipes
(`--labels`: `soa-server --english-dump DIR`'s `labels-en.tsv`); `english-art --check-roundtrip` checks the label walk and
the ISF repack against every scene of the download (the same bytes back; not a gate: it needs the game files).

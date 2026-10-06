# english_art: the English UI art

The `-en` images the CDN serves with `--english` (PLAN-english.md Q4, E9; docs/english.md section 8):
the game's own scenes and images, rebuilt from the user's download with English text drawn over
the Japanese, from the committed recipes in `standin-assets-en/recipes/*.json`. No game art is in
git or in the packages. Public API: `soaserver/english_art.h` (`english_art::build`).

| File | What |
|---|---|
| `art.h` | the internal pieces: `Canvas`, `Font`, `Style`, `Label`, `Recipe`, the drawing functions |
| `build.cpp` | `build()` (recipes, sources, stamps, outputs) and `apply_recipe()` (decode, draw, re-encode the changed 4x4 blocks, ISF sum, SLZ, ADLD) |
| `render.cpp` | text in the game font (`\n` lines, bold, scale, squeeze / shrink), outline / glow / shadow, `inpaint` |
| `font.cpp` | `Font/etc2/font.fpk`: the glyph table and the page's alpha |
| `recipe.cpp` | the recipe JSON (nlohmann-json): strict keys, named styles |
| `english_art_tests.cpp` | `--selftest english-art/` |

The codecs (SLZ, ISF, AIF, ETC2 / EAC) are `common/` `soa/aska_image.h`, shared with `tools/aif2png`.
`build/tools/english_art/english-art --out DIR --png DIR` runs the build without a server, for writing recipes.

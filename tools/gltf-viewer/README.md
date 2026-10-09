# glTF viewer

A web viewer for the `.glb` files `tools/asf2gltf` writes (docs/notes.md "glTF export"), showing what
plain viewers can't: the game's own shaders, the animation set by role with the face layered, the
effect triggers and sound cues on a timeline, the PRS constraints evaluated live, and the home
behaviour replayed from the Home3D table. Not to be confused with `soa-viewer` (the offline client).

## Setup and use

```sh
tools/gltf-viewer/fetch-deps.py             # three.js 0.186.1 into work/tools/three-0.186.1/ (sha512 checked)
tools/gltf-viewer/serve.py                   # http://127.0.0.1:8642/ (this machine only)
```

Open the URL, then pick a model from `work/models/` (the list), the file picker, or drop a `.glb` on
the view; `?model=/work/models/seaside-maria/cp0303_b04a.glb` loads one at start, `&ui=0` hides the
panel (screenshots). No game file is in git or bundled: the page loads what is in `work/`.

**Dependencies.** three.js is pinned to 0.186.1 (`fetch-deps.py` holds the npm tarball's sha512; the
import map in `index.html` and `serve.py` name the same version). A fetch script rather than a
package.json: there is no node/npm on the Linux side here, and downloaded tools live in `work/tools/`.
The screenshot test uses Playwright (`requirements.txt`) and its headless Chromium, fetched into
`work/tools/ms-playwright/` by `fetch-deps.py --browser` (never into `$HOME`).

## What it shows

| Panel | |
|---|---|
| Materials | **the game's shaders** (`SOA_aska_shader`) or the **PBR fallback** (glTF metallic-roughness). MToon isn't offered: the game's character shaders are physically based (GGX, SH ambient, a shadow map; Marschner for hair), not toon-ramped (docs/notes.md). |
| Animation | the file's animations grouped by role (battle skills, battle, character viewer, home faces, blinks, home); play / pause / step / scrub in the game's frames (60 fps, `extras.fps`); a **face layer** (a facial expression, a blink or the mouth) over the body motion; the timeline marks the **effect triggers** (orange, `extras.effects`), **sound cues** (blue, `extras.sounds`) and the raw signals (grey); the animation's extras below. |
| Constraints | `SOA_aska_constraints` evaluated every frame after the keyframes, like `Aska::AafPRSConstraintController` (`constraints.js`; on/off). |
| Home | **home behaviour**: the stay loop, stay_long after 121 frames at 50 %, taps (weighted, favor-gated, never the same row twice), facial layers, blinks on the game's timer, the mouth clip while a line "plays", the line in a speech box (JP, or the English line); rules and addresses in `home.js` and docs/home3d.md. |
| Morph targets | a slider per target (`extras.targetNames`); an animation's weights channel overrides them. |
| Display | skeleton overlay, the **physics-driven joints** (`extras.physics_driven`: rest pose, the game's physics isn't in the file), camera presets (front, ¾, side, back, face, **game home**: the game's `SetCameraPos` rule, 15°, 5.5 m). |
| File | the asset, the extensions, the set and the Home3D summary. |

`KHR_animation_pointer` (material factors, `KHR_texture_transform` offset / scale / rotation, node
TRS, morph weights, `KHR_node_visibility`) and static `KHR_node_visibility` are applied by
`soa-gltf.js` (GLTFLoader skips pointer channels).

## The game's shaders in three.js (`aska-shader.js`)

Each material's captured vertex and fragment shaders run as a `THREE.ShaderMaterial` (GLSL ES 3.00)
almost unchanged: the version line and the attributes' layout locations go, the skinning palette
`camSkin` is enlarged to the skin's joints. The game's raw streams are rebuilt from the glTF
attributes, and the per-draw uniforms are computed each frame so the shader works in the game's world
space: `camSkin` = the three.js joint matrices mapped into the game's space (centimetres, x mirrored, the
placement's scale from the captured `cmWorld`), `cmWVS` = the game's world to three's clip space with the
shader's `z = 2z' − w` undone, `vcvWorldEyePos` = the camera. The scene's lighting and the material
constants are the capture's. The output goes to a half-float target and is shown × `cvHDRTransform.x`,
sRGB-encoded.

## Limits

- The engine's own textures (the shadow map, the BRDF table, a default F0) aren't in the file unless
  `asf2gltf` embeds them (`engine_textures`); the stand-ins are: shadow map 0 (lit, no self-shadow),
  others a dark neutral F0. The hair comes out lighter than in the game.
- The game's post pass (bloom, the final curve) isn't captured: × `cvHDRTransform.x`, then sRGB.
- A material's short pass before its lit one (the hair's alpha-tested pass) is drawn as a depth
  pre-pass with colour writes off (d).
- Morph targets don't reach the game's vertex shader (it has no morph inputs): the base shape in that
  mode.
- The home replay has no audio: a line's voice is taken to last as long as its motion; the random
  numbers are a seeded generator, not the game's.

## Test

`tests/test_gltf_viewer.py` builds a small glTF (a skinned box, a quad with a morph target, pointer and
visibility tracks, a point constraint, a game-style shader pair, two Home3D rows), loads it in headless
Chromium (SwiftShader) and checks what the viewer draws and computes; it skips when Playwright, the
browser or three.js is missing.

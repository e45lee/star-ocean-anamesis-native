# The hair shader (3.7.0)

How STAR OCEAN: anamnesis renders character hair: which shaders draw it, the lighting model, its inputs, how the
renderer drives it, and its permutations. The source is the 3.7.0 client (`work/libSOA-3.7.0.so`; Ghidra
addresses = ELF vaddr + 0x100000) and its shader cache `Shader/AHSLDiskCacheAdd`.

Labels: **(a)** data or strings in the game files, **(b)** decompiled code, **(d)** inferred.

## Answer in brief

- **The shader.** Hair materials (`m_hair`, `m_hair_2`, `m_hair_3`) use the material system's **"Marschner"**
  shading node (`askaMarschner`). Its fragment shaders are the 19 cache entries that declare
  `uniform vec4 eMARSCHNER_PRECALC0[3]`.
- **The lighting model.** Despite the name, it is not a full Marschner fiber BSDF. It is the real-time
  two-lobe **Kajiya-Kay / Scheuermann** approximation, with Marschner-style lobe roles:
  - Two specular lobes are computed against strand tangents shifted along the normal by a per-texel shift
    texture plus a material offset (the classic "specular shift").
  - Each lobe is `pow(sin²(T,H), n/2)`.
  - The primary (R) lobe is uncoloured and carries a Schlick-style Fresnel term.
  - The secondary (TRT) lobe is tinted by a colour constant (the "secondary specular colour").
  - Both lobes are scaled by `saturate(N·L / max(N·V, 0.07))` and normalised by `sqrt(n+1)/8`.
  - Diffuse is Lambert plus L1 spherical-harmonics ambient, scaled for energy by `1-2·F0`.
  - An ambient specular term is `SH · F0 · (1 + secondary colour)`.
  - Lighting is two-sided (the normal is flipped on back faces) and fog is exponential.
- **Transparency.** Hair is **punch-through, not alpha-blended**. Fragments are discarded against a 2×2
  ordered-dither threshold *and* the material's `cfAlphaThreshold`. Matching depth-only dither shaders exist
  for the Z-prepass and shadow passes.
- **The textures.** The hair texture is a **packed mask**: `.y` is the diffuse intensity and `.z` is the alpha.
  Hair colour comes entirely from material constants, which is how the deco-hair recolouring works.

## 1. Where the shaders live: the AHSL disk cache

**No GLSL source ships with the game, and no shader is generated at runtime.** Every material shader is a
precompiled GLSL ES 3.00 string in `Shader/AHSLDiskCacheAdd`.

- The file ships in two copies with identical contents. (a)
  - The APK's `assets/builtin_data/Shader/` copy is stored plain.
  - The 3.7.0 download's copy is ADLD-wrapped.
- The client loads the file in `CAddShaderCacheManager::Progress` (`0124ba64`), which calls
  `AHSLCacheManagerV2::AttachDiskCache(1, data)`. (b)
- `AHSLCacheManagerV2::RebuildL2Database` (`021af660`) indexes every entry by its shader key. (b)
- `BuildLinkedDiskCacheL2` (`021ad2a8`) unpacks each entry and calls
  `RenderDeviceGL::CreateShaderFromMemory`. (b)

`AHSLCompiler::*` (`LoadMain`, `Include`, `GenerateLightingCode`) and the `Shading/Pixel*` fragment names in
the lib are the authoring-side generator. (a) Its `.ahsl` sources are not shipped, and
`AHSLCacheManagerV2::SetPrebuiltBinary` is a stub. (b)

The GLSL text is machine-translated from D3D9-style shader model 3 code (d):

- registers become `Temp_N`;
- the output is `SV_TARGET0`;
- the inputs are `in_POSITION0`, `in_NORMAL0`, `in_BINORMAL0` and so on;
- the interpolants are `TexCoord0..4`.

The 8 KiB compression dictionary in the cache header contains D3D constant-table text (`ps_3_0`, `vs_3_0`,
`2.0.6534.1`). (a)

### Format

The decoder for this format is `tools/ahsl_extract.py`, and its docstring has the details.

- **The outer wrapper** is ADLD with the XOR flag, keyed on the name `Shader/AHSLDiskCacheAdd`, which hashes
  to the key `ab170d62`. (a, via `soa_save/adld.py`)
- **The file header** is `KPHS` with a section count. Sections start at 0x2020. (b: `RebuildL2Database`)
- **There are two sections**, each with an `AHSLFileCacheHeader` of 0x2020 bytes:
  - `3AHA` (`AHSLDISKCACHEMAGIC`) holds 1,523 shaders (221 VS, 1,302 PS).
  - `03LA` (`AHSLLINKEDDISKCACHEMAGIC`) holds 435 pre-linked programs as pairs of shader keys
    (`RenderDeviceData::ReadShaderLinkedCache` / `ReadLinkedKey`). (a/b)
  - Each header carries a version, which must match the device's (`IsValidFileCacheHeader`), and an 8 KiB LZ
    dictionary checked by CRC16. (b)
- **The entry header** is `u16 ?, u16 stored size, u16 unpacked size, u16 info offset, u16 ?, u8 flags,
  u8 ?`, followed at +0xC by the shader key (`ShaderKeyUtil`; `GetTarget` = `key[4]>>3 & 7`: 0 VS, 1 PS).
  (b)
- **Compression.** The first `info offset + 48` bytes are stored raw. The rest is
  `ShaderCompression::DecompressLZwordDic` (`022c75fc`), which is all 1,523 entries in this file. (b)
  - It works on 16-bit units.
  - A big-endian flag word covers 16 items, least-significant bit first.
  - A match is big-endian: `len-2` in the top nibble and a word distance in the low 12 bits.
  - A distance of 0 ends the stream.
  - Distances reaching before the start of the output read from the end of the 8 KiB dictionary.
- **The info block** has, at `+0x1a`, the offset of the code blob.
- **The code blob** is `u32 ?, u32 text offset`, followed by the constant list.
  `RenderDeviceData::CreateShaderConstantAssign` (`0227f424`) reads the constant list as (b):
  - a `u32` sampler mask, a `u16` skip and a `u16` count;
  - then records of `{u8 kind (0 engine "cv", 1 material "e"), u8 type, u16 registers, u16 id, u16 slot}`.
- **Material constant ids** index the name table at `0x2be89f0`. (a) Examples:
  - 5 = `eConstColor_Color_Color`;
  - 21 = `eMARSCHNER_COEF`;
  - 22 = `eMARSCHNER_PRECALC`;
  - 32 = `evHairCoef`.

### Usage

```sh
.venv/bin/python tools/ahsl_extract.py -o /tmp/ahsl                  # all 1523 entries + index.tsv + programs.tsv
.venv/bin/python tools/ahsl_extract.py -o /tmp/hair --grep MARSCHNER # just the hair shaders
```

Don't commit the dumps: they are game data.

## 2. Material system: the "Marschner" node and hair materials

Materials are Maya-style node graphs. (a) These name tables are in the lib:

- **Shading node types** (`0x2b4ab00`): `legacyKajiyaKay`, `legacyMarschner`, `askaMarschner`,
  `askaMarschnerFast`, `askaKajiyaKay`, `askaNonPhysicalKajiyaKay`, plus a separate `askaHair` node.
- **AHSL shading fragments** (`0x2bea190..`): `Shading/PixelMarschner`, `Shading/PixelReferenceMarschner`,
  `Shading/PixelNormalizedKajiyaKay`, `Shading/PixelKajiyaKay`, `Shading/PixelNormalizedMarschnerLambert`.
- **Node attribute names** (`0x2b4ad00`), the ones relevant to hair:
  - `specularColor`, `secondarySpecularColor`, `specularColor2`, `specularGain2`, `shininessRate2`;
  - `marschnerCoefficient`, `specularOffset`, `specularOffsetVector`;
  - the render-state attributes `punchThroughThreshold`, `alphaToCoverage`, `zPrepassOff`,
    `punchThroughZPrepass`, `ditherMode`, `casterPunchThrough`, `castsShadowsOff`, `receiveShadowsOff`.

The shipped cache contains only Marschner-family hair shaders. No GLSL references `evHairCoef`,
`eBlinn_Aniso_Coef` or `eMARSCHNER_COEF`, so the Kajiya-Kay node variants are unused in 3.7.0. (a)

**Hair materials are called `m_hair`, `m_hair_2` and `m_hair_3`.** (b)
`CDecoManager::ChangeHairColor` (`012fe900`) recolours exactly these three materials. For each one it sets
three attributes through the AsfHandler:

| node | attribute | value |
|---|---|---|
| `R:color20` | `color1` | colour pair at +0x30/+0x40 |
| `R:color21` | `color1` | colour pair at +0x70/+0x80 |
| `R:color_m_01` | `secondarySpecularColor` | colour pair at +0x50/+0x60 |

`CDecoManager::CreateDecoHair` fills those slots from `master_deco_hair`:

- `color` → RGB/255 with alpha 1, into +0x40 and +0x80;
- `secondary_specular_color` → +0x60.

`master_deco_hair` has 147 rows; `secondary_specular_color` is typically `16449023` = `#FAFDFF`. (a)

The character models (`Character/etc2/hi/*.asf`: ADLD, then SLZ, then zstd frames) contain `R:m_hair`,
`R:m_hairShape`, `R:color20`, `R:color_m_01` and the hair bones `R:X_hair_*`. (a) 319 Character files
mention `m_hair`. The node graph is stored in a compact binary form; the node type ids were not decoded.

### The material constants: COEF → PRECALC

A material's constant block comes from the model (`AFF::MaterialInfo`). `MaterialList::Activate`
(`02244c2c`) uploads it. (b)

- For every record it calls `AhslConst::AofConvertToNativeConstant(id, src, dst)` (`02454e30`).
- For id 21 (`eMARSCHNER_COEF`) that call returns 3. `Activate` then stores the raw COEF under id 21 and three
  derived vectors under id 22 (`eMARSCHNER_PRECALC`), which is what the shader reads.

With `COEF = (n1, n2, c, ·)` (b):

```
P0 = ( n1/2, n2/2, sqrt(n1+1)/8, c*sqrt(n2+1)/8 )
k  = 2/(n1/2 + n2/2 + 2);  m = ((sqrt(k)+1)/2)^2
P1 = ( sqrt((2/m - 2)*0.001), 0.95*(1 - 2k/(k+1)), 0, 1-c )   // unused by the 19 hair PS
f  = clamp(1 - 2c, 0, 1)
P2 = ( f, f, c, 1-c )
```

What the terms mean (d):

- `n1` and `n2` are the R and TRT shininess exponents. They are halved because `sin^n = (1-cos²)^(n/2)`.
- `sqrt(n+1)/8` is a cheap energy normalisation.
- `c` is the specular reflectance F0. It also weights the TRT lobe, and `1-2c` scales diffuse down.
- Probably `marschnerCoefficient` is the node attribute behind COEF (not traced).

## 3. Inputs

### Vertex shader (d: paired by interface)

The PS reads `TexCoord0.w`, `TexCoord1.xyz`, `TexCoord2`, `TexCoord3.xyzw` and `TexCoord4.xyz`. The skinned
VS family that writes exactly these is entries 143, 148, 171, 173, 175 and 182 (and their UV-shift twin 49).

The `03LA` link table does not list the hair PS keys, so the pairing comes from matching the interfaces
rather than from data. From entry 148:

```glsl
layout(location=0) in highp vec4 in_POSITION0;   // .w -> TexCoord0.w (per-vertex scalar; AO-like)
layout(location=1) in highp vec4 in_NORMAL0;
layout(location=2) in highp vec4 in_TEXCOORD0;   // .xy UV0 (texture), .zw UV1 (shift map in some variants)
layout(location=3) in highp vec4 in_BINORMAL0;   // the strand direction
layout(location=4) in highp vec4 in_BLENDINDICES0;
layout(location=5) in highp vec4 in_BLENDWEIGHT0; // 4-bone skinning from camSkin[186] (3 vec4 per bone)
uniform mat4 cmWVS; uniform vec4 cmWorld[3]; uniform vec3 vcvWorldEyePos;
...
TexCoord1.xyz = normalize(world normal);
TexCoord3.xyz = normalize(world binormal);           // hair tangent T = the mesh BINORMAL
TexCoord0.xyz = world position;
TexCoord4.xyz = normalize(vcvWorldEyePos - worldPos); // V
TexCoord3.w   = length(vcvWorldEyePos - worldPos);   // fog distance
```

Variants with `eamUVShiftMatrix[16]` animate UV0 (`SetUVShiftParam`).

### Fragment shader uniforms (a: entry 66's constant list, ids from §1)

| uniform | id | meaning |
|---|---|---|
| `cvLightContext0[5]` | cv 26 | `[1]` = light direction (the shader uses `-[1]` as L), `[2]` = light colour (d) |
| `cvSHAmbContext[8]` | cv 30 | L1 SH ambient: `N.x*[0] + N.y*[1] + N.z*[2] + [3]` |
| `cvFogCoef[4]` | cv 38 | `[0]` = (scale, density, bias), `[1]` = fog colour |
| `cvHDRTransform` | cv 31 | `.y` = output exposure scale |
| `cfAlphaThreshold` | cv 33 | punch-through threshold |
| `eConstColor_Color_Color0` | e 5 slot 0 | hair tint: `lerp(1, rgb, a)` |
| `eConstColor_Color_Color3` | e 5 slot 3 | `.xy` = shift offsets of the two lobes |
| `eConstColor_Color_Color4` | e 5 slot 4 | secondary specular (TRT) colour |
| `eMARSCHNER_PRECALC0[3]` | e 22 | P0..P2 above |
| `s0` | | mask: `.y` diffuse/albedo intensity, `.z` alpha |
| `s1` | | shift map: `.x` R-lobe shift, `.y` TRT-lobe shift |

Whether `color20` maps to `Color0` and `color_m_01` to `Color4` is (d). The roles match: `ChangeHairColor` sets
alpha 1, which turns the lerp into a full replacement, and "secondary specular colour" tints the TRT lobe.

The per-draw engine constants (`cv*`) are set by `RenderContextBase::SetShaderConstant_Pixel/_Vertex` and
`MaterialContext::Apply`. The material constants come from the `ShaderConstantManager` that `Activate`
filled. (b: names and call sites only)

## 4. The fragment shader

Entry 66 is the minimal permutation, shown here verbatim apart from the elisions:

```glsl
tmpvar_1 = texture (s0, TexCoord2.xy);  Temp_0.yz = tmpvar_1.yz;        // .y intensity, .z alpha
// 2x2 ordered dither: (x&1, y&1) -> 0, .75, .5, .25
Temp_1.xyz = fract(floor(gl_FragCoord.xyx) * 0.5) * 2.0;
Temp_0.x = (3*Temp_1.x + 2*Temp_1.y - 4*Temp_1.y*Temp_1.x) * 0.25;
if (gl_FrontFacing) tmpvar_2 = -1.0; else tmpvar_2 = 1.0;               // two-sided:
tmpvar_4 = (front) ? normalize(TexCoord1.xyz) : -normalize(TexCoord1.xyz);
Temp_0.w = dot (tmpvar_4, -(cvLightContext0[1].xyz));                   // N.L
Temp_1.w = clamp (Temp_0.w, 0.0, 1.0);
if ((-(Temp_1.w) < 0.0)) {
    Temp_2.x = dot (tmpvar_4, TexCoord4.xyz);                           // N.V
    Temp_0.w = clamp (Temp_0.w * (N.V >= 0.07 ? 1.0/N.V : 14.28571), 0.0, 1.0);
    Temp_3.xyz = normalize(-(cvLightContext0[1].xyz) + TexCoord4.xyz);  // H
    Temp_2.x = clamp (dot (Temp_3.xyz, TexCoord4.xyz), 0.0, 1.0);
    Temp_2.x = exp2((1.0 - Temp_2.x) * 8.65617 - 8.65617);              // ~ Schlick (1-V.H)^5
    Temp_2.x = Temp_2.x * (1.0 - eMARSCHNER_PRECALC0[2].z) + eMARSCHNER_PRECALC0[2].z;  // F
    Temp_2.x = (Temp_0.w * Temp_2.x);
    tmpvar_6 = texture (s1, TexCoord2.xy);
    Temp_2.yz = (tmpvar_6.xy + eConstColor_Color_Color3.xy);            // per-lobe shift
    Temp_5.xyz = normalize(tmpvar_4 * Temp_2.zzz + TexCoord3.xyz);      // T2 = T + N*shift2
    Temp_2.z = clamp (pow (abs(max (1.0 - dot(H,T2)*dot(H,T2), 0.0)), eMARSCHNER_PRECALC0[0].y), 0.0, 1.0);
    Temp_0.w = (Temp_0.w * Temp_2.z);                                   // TRT lobe
    Temp_4.xyz = normalize(tmpvar_4 * Temp_2.yyy + TexCoord3.xyz);      // T1 = T + N*shift1
    Temp_2.y = clamp (pow (abs(max (1.0 - dot(H,T1)*dot(H,T1), 0.0)), eMARSCHNER_PRECALC0[0].x), 0.0, 1.0);
    Temp_2.x = (Temp_2.x * Temp_2.y);                                   // R lobe (with Fresnel)
    Temp_2.yzw = Temp_0.www * cvLightContext0[2].xyz * (eMARSCHNER_PRECALC0[0].w * eConstColor_Color_Color4.xyz);
    Temp_3.xyz = (Temp_2.xxx * cvLightContext0[2].xyz) * eMARSCHNER_PRECALC0[0].zzz;
    Temp_2.xyz = (Temp_2.yzw + Temp_3.xyz);                             // specular
} else { Temp_2.xyz = vec3(0.0); }
// punch-through: discard if alpha <= dither + 0.125 or alpha <= cfAlphaThreshold
if (Temp_0.z - 0.125 - Temp_0.x <= 0.0 || cfAlphaThreshold - Temp_0.z >= 0.0) discard;
Temp_0.x = (Temp_0.y * TexCoord0.w);
Temp_1.xyz = (SH(N) /* cvSHAmbContext[0..3] */) * Temp_0.x;              // ambient * mask * vertex AO
Temp_3.xyz = Temp_1.xyz * eMARSCHNER_PRECALC0[2].xxx
           + Temp_1.www * cvLightContext0[2].xyz * eMARSCHNER_PRECALC0[2].yyy;  // diffuse light
Temp_4.xyz = eConstColor_Color_Color0.www * eConstColor_Color_Color0.xyz + 1.0 - eConstColor_Color_Color0.www;
Temp_0.xyw = Temp_0.yyy * Temp_4.xyz * Temp_3.xyz;                      // albedo * diffuse
Temp_1.xyz = Temp_1.xyz * (eMARSCHNER_PRECALC0[2].z * eConstColor_Color_Color4.xyz + eMARSCHNER_PRECALC0[2].z);
Temp_0.xyw = Temp_0.xyw + Temp_1.xyz + Temp_2.xyz;                      // + ambient spec + spec
// exponential fog with cvFogCoef, distance TexCoord3.w
SV_TARGET0.xyz = (Temp_0.xyw * cvHDRTransform.yyy);
SV_TARGET0.w = Temp_0.z;
```

Readable form (d, from the code above). Notation:

- `N` is the face-corrected normal.
- `T` is the world binormal.
- `V = TexCoord4`, `L = -cvLightContext0[1]`, `H = normalize(V+L)`.
- `E = cvLightContext0[2]`, `m = s0`, `sh = s1`.
- `F0 = P2.z`.

```
w    = sat( (N·L) / max(N·V, 0.07) )                       (only when N·L > 0)
F    = F0 + (1-F0) * exp2(-8.65617 * sat(V·H))
T1   = normalize(T + N*(sh.x + Color3.x)),   T2 = normalize(T + N*(sh.y + Color3.y))
R    = w * F * sat( (1-(T1·H)²)^(n1/2) )
TRT  = w *     sat( (1-(T2·H)²)^(n2/2) )
spec = E * ( R * sqrt(n1+1)/8  +  TRT * F0*sqrt(n2+1)/8 * Color4.rgb )
A    = SH(N) * m.y * vertexAO                              (vertexAO = in_POSITION0.w)
diff = m.y * lerp(1, Color0.rgb, Color0.a) * ( A*(1-2F0)₊ + sat(N·L)*E*(1-2F0)₊ )
out  = fog( diff + A*F0*(1 + Color4.rgb) + spec ) * cvHDRTransform.y,   alpha = m.z
```

Two details are quirks of the shader:

- The R lobe carries the Fresnel term and the TRT lobe does not.
- The ambient term applies `m.y` twice: once in `A`, and again in `diff`.

## 5. Permutations (a)

All 19 permutations share the same core: the two shifted lobes, the dither plus alpha-test, two-sided
lighting, SH ambient and fog. They differ along these axes:

| axis | what changes | entries |
|---|---|---|
| minimal | none of the axes below | 66, 235, 1487 (shift map on UV0 `xy` or UV1 `zw`) |
| colour effect | `cvColorMultiplier` / `cvColorOffset` applied before the alpha test (engine colour flashes) | 246, 1460, 11, 185, 264, 359, 428, 1355, 1356 |
| projector shadow | `eProjector_Projection_Matrix0`, `eProjector_TexSize0[3]`, `ePROJECTOR_FADECOEF0`. A 4-tap depth compare (PCF) on `s2` or `s3` that scales the direct light, faded by `ePROJECTOR_FADECOEF0.x * distance` | the 14 long ones (315–329 lines): 11, 12, 176, 185, 263, 264, 358, 359, 427, 428, 1289, 1290, 1355, 1356 |
| node layout | different `eConstColor` slots (Color1/2/5 instead of 3/4) and a different texture set. For example, 11 and 12 use `s1` as the mask and `s0` as two tint masks (`.x` blends Color0, `.z` blends Color1); their shift map is on `s2` with no offset constant, the TRT colour is Color5, and the shadow map is on `s3` | 11, 12, 358, 359, 427, 428, 1289, 1356 |

The engine builds the key from the material's node graph plus conditions:

- `ShaderNodeHandler::MakeShaderKey`, `MakeDirectShaderNodeShaders` (`020b569c`);
- `ShaderKeyUtil::GetConditionFlag`, `GetPerPixelLightCount`.

It then looks the key up in `AHSLCacheManagerV2::SearchOrCompile` (`021ac5ac`). (b) Only one directional
light is evaluated per pixel (`cvLightContext0`); the other lights are folded into the SH ambient. (d)

## 6. Passes and render state

- **Colour pass.** The hair is effectively opaque: coverage comes from `discard`. The shader writes the alpha
  (`SV_TARGET0.w = m.z`), but nothing found here sets a blend state for hair. (d: blend state not traced.)
  - The 2×2 dither turns a soft alpha edge into a screen-door pattern. A fragment survives only where
    `alpha > dither + 0.125`, with dither ∈ {0, .25, .5, .75}.
  - It also has to pass `alpha > cfAlphaThreshold`.
  - This matches the material attributes `ditherMode`, `punchThroughThreshold` and `alphaToCoverage`. (a)
- **Depth-only passes.** The cache has 20 tiny dither-and-alpha-test PS (~70 lines) that output
  `vec4(1,1,1,alpha)` and do no lighting. 11 of them take the alpha from `.z` of `s0` or `s1`, like the hair
  mask: entries 13, 172, 251, 288, 297, 357, 367, 426, 981, 1282, 1283. (a) They are probably the hair's
  `punchThroughZPrepass` / `casterPunchThrough` variants, from `ShaderNodeHandler::MakeZprepassShaderKey`,
  `MakePunchThroughDepthShaderKey` and `MakeColorShadowShaderKey`. (d)
- **Culling.** Hair is lit two-sided via `gl_FrontFacing`, which implies culling is off for hair cards. (d)
- **Sorting.** No sorting is needed for punch-through. No hair-specific sort was found. (d)

## 7. Open points

- **The VS↔PS pairing** is matched by interface only. A trace of `AHSLCacheManagerV2::AddToL1Cache` or
  `SearchOrCompile` keys while a character is on screen would confirm it. Match the logged key bytes against
  `index.tsv` (key at entry+0xC).
- **The COEF values and the node type ids** inside the `.asf` material blocks were not decoded. A per-character
  value table would need an AFF material parser.
- **Blend and cull state** for the hair batch come from `RenderPass` / `MaterialList` flags (`Activate` copies
  them from `MaterialInfo` +0x3c and similar fields). They were not traced.

// The game's own shaders (SOA_aska_shader, docs/notes.md "glTF export"): each material's captured vertex
// and fragment shaders run as a three.js ShaderMaterial (GLSL ES 3.00) with these changes only:
//  - the version line goes (three writes it) and the attributes lose their layout locations (three binds
//    by name); the skinning palette `camSkin` gets room for the mesh's joints (the game uploads a meshset's
//    palette, the glTF skin is the whole object's);
//  - the fragment shader's output goes through a display transform: times cvHDRTransform.x (undoing the
//    1/x it applies for the game's HDR target) and encoded to sRGB (d: the game's post pass isn't captured).
// The game's vertex shader reads its raw streams; here they are built from the glTF attributes
// (in_POSITION0 = position + _POSITION_W, in_NORMAL0, in_TEXCOORD0 = both UV sets, in_BINORMAL0 = tangent
// with the game's bitangent sign (the glTF's negated: the export mirrors), in_BLENDINDICES0 = the glTF
// joint index (the palette is the skin's joints here), in_BLENDWEIGHT0, in_COLOR0), and its per-draw
// uniforms are computed every frame so that it lands in the game's world space:
//   camSkin[3i..3i+2] = rows of G * modelMatrix * bindMatrixInverse * boneMatrix_i * bindMatrix (joint i,
//   applied to the glTF vertex: the vertex in the game's world), cmWorld = identity rows, cmWVS = the
//   game's world -> three's clip space (its z row adjusted for the shader's z = 2 z' - w), vcvWorldEyePos =
//   the camera in the game's world. G (three world -> the game's world) = S(the placement's scale) * K,
//   K = Mx * Root^-1 (Root: the converter's root node: centimetres -> metres, -Z front -> +Z).
// Uniforms of the material and the scene's lighting come from the capture (cvLightContext0, cvSHAmbContext,
// cvFogCoef, cvHDRTransform, the shadow projector, material constants); textures: the material's slots
// from the .glb, the engine's (shadow map, BRDF table, a default F0) from the file's engine_textures when
// present, else stand-ins (README "Limits"). Morph targets don't reach the game's vertex shader (it has no
// morph inputs): a model with them shows its base shape in this mode.
import * as THREE from 'three';

function adaptVertex(src, joints) {
  let s = src.replace(/^#version.*$/m, '');
  s = s.replace(/layout\s*\(\s*location\s*=\s*\d+\s*\)\s*in\s+/g, 'in ');
  s = s.replace(/uniform vec4 camSkin\[(\d+)\];/, (m, n) => `uniform vec4 camSkin[${Math.max(Number(n), 3 * joints)}];`);
  return s;
}

function adaptFragment(src) {
  let s = src.replace(/^#version.*$/m, '');
  s = s.replace(/layout\s*\(\s*location\s*=\s*0\s*\)\s*out\s+highp\s+vec4\s+SV_TARGET0\s*;/, 'layout(location = 0) out highp vec4 soaFragOut;');
  s = s.replace(/\bSV_TARGET0\b/g, 'soaOut');
  s = s.replace(/void\s+main\s*\(\s*\)/, 'vec4 soaOut;\nvoid soaGameMain()');
  s += `
uniform vec4 soaHDR;
uniform float soaDisplay;
void main() {
  soaGameMain();
  vec3 c = soaOut.rgb * (soaDisplay > 0.5 ? soaHDR.x : 1.0);
  c = clamp(c, 0.0, 1.0);
  c = mix(c * 12.92, 1.055 * pow(c, vec3(1.0 / 2.4)) - 0.055, step(0.0031308, c));
  soaFragOut = vec4(soaDisplay > 0.5 ? c : soaOut.rgb, soaOut.a);
}`;
  return s;
}

function uniformValue(u) {
  const v = u.captured;
  if (!v || !v.length) return null;
  const flat = Array.isArray(v[0]) ? v.flat() : v;
  if (u.type === 'mat4') return new THREE.Matrix4().fromArray(flat);  // as glGetUniform lists it (column-major)
  const vecs = [];
  for (let i = 0; i < flat.length; i += 4) vecs.push(new THREE.Vector4(flat[i], flat[i + 1] || 0, flat[i + 2] || 0, flat[i + 3] || 0));
  if (u.count && u.count > 1) {
    while (vecs.length < u.count) vecs.push(new THREE.Vector4());
    return vecs;
  }
  if (u.type === 'vec3') return new THREE.Vector3(flat[0], flat[1], flat[2]);
  if (u.type === 'vec2') return new THREE.Vector2(flat[0], flat[1]);
  if (u.type === 'float') return flat[0];
  return vecs[0];
}

function constTex(r, g, b, a) {
  const t = new THREE.DataTexture(new Uint8Array([r, g, b, a]), 1, 1, THREE.RGBAFormat);
  t.needsUpdate = true;
  return t;
}

// the game's raw streams from the glTF attributes (once per geometry)
function gameAttributes(geo) {
  if (geo.userData.soaGame) return;
  const n = geo.attributes.position.count;
  const pos = geo.attributes.position, nrm = geo.attributes.normal, uv = geo.attributes.uv, uv1 = geo.attributes.uv1;
  const tan = geo.attributes.tangent, pw = geo.attributes._position_w, col = geo.attributes.color;
  const ji = geo.attributes.skinIndex, jw = geo.attributes.skinWeight;
  const P = new Float32Array(n * 4), N = new Float32Array(n * 4), T = new Float32Array(n * 4), B = new Float32Array(n * 4);
  const I = new Float32Array(n * 4), W = new Float32Array(n * 4), C = new Float32Array(n * 4);
  for (let i = 0; i < n; i++) {
    P.set([pos.getX(i), pos.getY(i), pos.getZ(i), pw ? pw.getX(i) : 1], i * 4);
    if (nrm) N.set([nrm.getX(i), nrm.getY(i), nrm.getZ(i), 0], i * 4);
    T.set([uv ? uv.getX(i) : 0, uv ? uv.getY(i) : 0, uv1 ? uv1.getX(i) : 0, uv1 ? uv1.getY(i) : 0], i * 4);
    if (tan) B.set([tan.getX(i), tan.getY(i), tan.getZ(i), -tan.getW(i)], i * 4);
    if (ji) I.set([ji.getX(i), ji.getY(i), ji.getZ(i), ji.getW(i)], i * 4);
    if (jw) W.set([jw.getX(i), jw.getY(i), jw.getZ(i), jw.getW(i)], i * 4); else W[i * 4] = 1;
    C.set(col ? [col.getX(i), col.getY(i), col.getZ(i), col.itemSize > 3 ? col.getW(i) : 1] : [1, 1, 1, 1], i * 4);
  }
  for (const [name, arr] of [['in_POSITION0', P], ['in_NORMAL0', N], ['in_TEXCOORD0', T], ['in_BINORMAL0', B],
    ['in_BLENDINDICES0', I], ['in_BLENDWEIGHT0', W], ['in_COLOR0', C]]) geo.setAttribute(name, new THREE.BufferAttribute(arr, 4));
  geo.userData.soaGame = true;
}

const _m = new THREE.Matrix4();
const _a = new THREE.Matrix4();
const _v = new THREE.Vector3();

export class GameMaterials {
  constructor(model, renderer) {
    this.model = model;
    this.renderer = renderer;
    const json = model.json;
    const ext = json.extensions && json.extensions.SOA_aska_shader;
    this.shaders = ext ? ext.shaders : null;
    this.mode = 'pbr';
    this.meshes = [];  // {mesh, pbr, game}
    this.stand = { lit: constTex(0, 0, 0, 255), grey: constTex(128, 128, 128, 255), f0: constTex(10, 10, 10, 255) };
    this.G = new THREE.Matrix4();
    this.ready = false;
    if (this.shaders) this.build();
  }

  materialIndex(m) {
    const a = this.model.gltf.parser.associations.get(m);
    return a ? a.materials : undefined;
  }

  build() {
    const json = this.model.json;
    const parser = this.model.gltf.parser;
    this.model.gltf.scene.traverse((mesh) => {
      if (!mesh.isMesh || Array.isArray(mesh.material)) return;
      const mi = this.materialIndex(mesh.material);
      const def = mi !== undefined ? json.materials[mi] : null;
      const me = def && def.extensions && def.extensions.SOA_aska_shader;
      if (!me || !me.passes || !me.passes.length) return;
      // the lit pass: the one with the longest fragment shader; a short one before it (the hair's and the
      // punch's alpha-tested pass) is drawn first as a depth pre-pass (colour writes off: d)
      const passes = me.passes.filter((p) => this.shaders[p.vertexShader] && this.shaders[p.fragmentShader]);
      if (!passes.length) return;
      const main = passes.reduce((a, b) => (this.shaders[b.fragmentShader].glsl.length > this.shaders[a.fragmentShader].glsl.length ? b : a));
      gameAttributes(mesh.geometry);
      const game = this.passMaterial(mesh, me, main);
      const pre = [];
      for (const p of passes) {
        if (p === main) continue;
        const m = this.passMaterial(mesh, me, p);
        m.colorWrite = false;
        m.transparent = false;
        m.depthWrite = true;
        let clone;
        if (mesh.isSkinnedMesh) {
          clone = new THREE.SkinnedMesh(mesh.geometry, m);
          clone.bind(mesh.skeleton, mesh.bindMatrix);
        } else clone = new THREE.Mesh(mesh.geometry, m);
        clone.name = `${mesh.name} (pre-pass)`;
        clone.visible = false;
        clone.renderOrder = -1;
        clone.frustumCulled = false;
        clone.userData.soaPrepassOf = mesh;
        mesh.add(clone);
        pre.push({ mesh: clone, game: m });
      }
      this.meshes.push({ mesh, pbr: mesh.material, game, pre });
    });
    this.ready = this.meshes.length > 0;
  }

  passMaterial(mesh, me, pass) {
    const parser = this.model.gltf.parser;
    const vs = this.shaders[pass.vertexShader], fs = this.shaders[pass.fragmentShader];
    const joints = mesh.isSkinnedMesh ? mesh.skeleton.bones.length : 1;
    const uniforms = { soaHDR: { value: new THREE.Vector4(1, 1, 0, 1) }, soaDisplay: { value: 1 } };
    const textures = me.textures || [];
    for (const [name, u] of Object.entries(pass.uniforms || {})) {
      if (u.type && u.type.startsWith('sampler')) {
        const slot = u.texture_slot;
        uniforms[name] = { value: this.stand.grey };
        if (slot !== undefined && textures[slot]) {
          parser.getDependency('texture', textures[slot].index).then((t) => {
            const tex = t.clone();
            tex.colorSpace = textures[slot].srgb ? THREE.SRGBColorSpace : THREE.NoColorSpace;
            tex.needsUpdate = true;
            uniforms[name].value = tex;
          });
        } else if (me.engine_textures && me.engine_textures[name] !== undefined) {
          parser.getDependency('texture', me.engine_textures[name]).then((t) => { uniforms[name].value = t; });
        } else {
          uniforms[name].value = this.standIn(name, fs.glsl);
        }
        continue;
      }
      let v = uniformValue(u);
      if (name === 'eamUVShiftMatrix' && !v) {  // identity rows per UV slot
        v = Array.from({ length: u.count || 16 }, (_, k) => (k % 2 === 0 ? new THREE.Vector4(1, 0, 0, 1) : new THREE.Vector4(0, 1, 0, 1)));
      }
      if (name === 'camSkin') v = Array.from({ length: Math.max(u.count || 0, 3 * joints) }, () => new THREE.Vector4());
      if (name === 'cmWorld') v = [new THREE.Vector4(1, 0, 0, 0), new THREE.Vector4(0, 1, 0, 0), new THREE.Vector4(0, 0, 1, 0)];
      if (name === 'cmWVS') v = new THREE.Matrix4();
      if (name === 'vcvWorldEyePos') v = new THREE.Vector3();
      uniforms[name] = { value: v !== null ? v : (u.count > 1 ? Array.from({ length: u.count }, () => new THREE.Vector4()) : new THREE.Vector4()) };
    }
    if (uniforms.cvHDRTransform) uniforms.soaHDR.value = uniforms.cvHDRTransform.value;
    const st = pass.state || {};
    const blend = /^blend 1 (\S+) (\S+)/.exec(st.blend || '');
    const cull = /^cull 1 0x405/.test(st.cull || '');
    const game = new THREE.ShaderMaterial({
      glslVersion: THREE.GLSL3,
      vertexShader: adaptVertex(vs.glsl, joints),
      fragmentShader: adaptFragment(fs.glsl),
      uniforms,
      // the game culls its back faces (GL_BACK with clockwise fronts); the glTF triangles are its
      // triangles mirrored, so three's FrontSide culls the same faces
      side: cull ? THREE.FrontSide : THREE.DoubleSide,
      transparent: !!blend,
      depthWrite: !/depthwrite 0/.test(st.depth || ''),
    });
    if (blend) {
      game.blending = THREE.CustomBlending;
      game.blendSrc = blend[1] === '0x302' ? THREE.SrcAlphaFactor : THREE.OneFactor;
      game.blendDst = blend[2] === '0x1' ? THREE.OneFactor : THREE.OneMinusSrcAlphaFactor;
    }
    game.name = `${mesh.material.name} (game shader, program ${pass.program})`;
    return game;
  }

  // soaDisplay 1: each draw encodes its own output (a single draw shown alone); 0: raw linear output into
  // the viewer's float target, encoded once by its post pass (the right sum for blended draws)
  setDisplay(on) {
    for (const e of this.meshes) for (const g of [e.game, ...e.pre.map((p) => p.game)]) g.uniforms.soaDisplay.value = on ? 1 : 0;
  }

  hdrScale() {
    for (const e of this.meshes) if (e.game.uniforms.cvHDRTransform) return e.game.uniforms.cvHDRTransform.value.x || 1;
    return 1;
  }

  standIn(name, glsl) {
    // the shadow map is the sampler read through the projector (eProjector_*): 0 = nothing in front, lit
    const re = new RegExp(`texture \\(${name}, Temp_\\d\\.y[zx]\\)`);
    if (/eProjector/.test(glsl) && re.test(glsl)) return this.stand.lit;
    return this.stand.f0;
  }

  setMode(mode) {
    this.mode = mode;
    if (mode === 'game' && !this.ready) return false;
    for (const e of this.meshes) {
      e.mesh.material = mode === 'game' ? e.game : e.pbr;
      for (const p of e.pre) p.mesh.visible = mode === 'game';
    }
    return true;
  }

  describe() {
    if (!this.shaders) return 'no SOA_aska_shader in this file (asf2gltf --shaders): PBR only';
    let engine = 0;
    for (const m of this.model.json.materials || []) {
      const e = m.extensions && m.extensions.SOA_aska_shader;
      if (e && e.engine_textures) engine += Object.keys(e.engine_textures).length;
    }
    return `${this.meshes.length} primitives with the game's shaders (${this.shaders.length} GLSL sources); engine textures: ` +
      (engine ? 'from the file' : 'stand-ins (shadow map lit, BRDF / F0 neutral)');
  }

  // The placement's scale: of the captured cmWorld matrices the one closest to a scaled identity (a rigid
  // object at the model's root: Maria's pareo, 1.063); no rotation (d).
  placementScale() {
    let best = null, bestErr = Infinity;
    for (const m of this.model.json.materials || []) {
      const p = m.extensions && m.extensions.SOA_aska_shader && m.extensions.SOA_aska_shader.passes;
      const cw = p && p[0].uniforms && p[0].uniforms.cmWorld && p[0].uniforms.cmWorld.captured;
      if (!cw || cw.length < 3) continue;
      const d = (cw[0][0] + cw[1][1] + cw[2][2]) / 3;
      let err = 0;
      for (let i = 0; i < 3; i++) for (let j = 0; j < 3; j++) err += Math.abs(cw[i][j] - (i === j ? d : 0));
      if (err < bestErr) { bestErr = err; best = d; }
    }
    return best || 1;
  }

  // Per frame, before rendering: the per-draw uniforms of every game material.
  update(camera) {
    if (this.mode !== 'game' || !this.ready) return;
    const json = this.model.json;
    const rootIndex = (json.scenes[json.scene || 0].nodes || [])[0];
    const root = (this.model.maps.nodes.get(rootIndex) || [])[0];
    if (!root) return;
    if (this.scale === undefined) this.scale = this.placementScale();
    const s = this.scale;
    this.G.makeScale(-s, s, s).multiply(_m.copy(root.matrixWorld).invert());
    const Ginv = this.G.clone().invert();
    camera.updateMatrixWorld();
    // clip = P * V * G^-1 * world_game; the shader's z = 2 z' - w, so row 2 gives (z + w) / 2
    const clip = new THREE.Matrix4().multiplyMatrices(camera.projectionMatrix, camera.matrixWorldInverse).multiply(Ginv);
    const e = clip.elements;  // column-major
    for (let c = 0; c < 4; c++) e[c * 4 + 2] = (e[c * 4 + 2] + e[c * 4 + 3]) / 2;
    const wvs = clip.clone().transpose();  // the game's dot(cmWVS[k], p) reads rows as columns
    const eye = _v.setFromMatrixPosition(camera.matrixWorld).applyMatrix4(this.G);
    const all = [];
    for (const e of this.meshes) { all.push({ mesh: e.mesh, game: e.game }); for (const p of e.pre) all.push({ mesh: e.mesh, game: p.game }); }
    for (const { mesh, game } of all) {
      const u = game.uniforms;
      if (u.cmWVS) u.cmWVS.value.copy(wvs);
      if (u.vcvWorldEyePos) u.vcvWorldEyePos.value.copy(eye);
      if (u.camSkin) {
        const arr = u.camSkin.value;
        if (mesh.isSkinnedMesh) {
          mesh.skeleton.update();
          const bm = mesh.skeleton.boneMatrices;
          // G * modelMatrix * bindMatrixInverse * boneMatrix_i * bindMatrix
          const pre = new THREE.Matrix4().multiplyMatrices(this.G, mesh.matrixWorld).multiply(mesh.bindMatrixInverse);
          for (let i = 0; i < mesh.skeleton.bones.length && 3 * i + 2 < arr.length; i++) {
            _a.fromArray(bm, i * 16);
            const m = new THREE.Matrix4().multiplyMatrices(pre, _a).multiply(mesh.bindMatrix);
            const me = m.elements;
            for (let r = 0; r < 3; r++) arr[3 * i + r].set(me[r], me[4 + r], me[8 + r], me[12 + r]);
          }
        } else {
          const m = new THREE.Matrix4().multiplyMatrices(this.G, mesh.matrixWorld);
          const me = m.elements;
          for (let r = 0; r < 3; r++) arr[r].set(me[r], me[4 + r], me[8 + r], me[12 + r]);
        }
      }
      game.uniformsNeedUpdate = true;
    }
  }
}

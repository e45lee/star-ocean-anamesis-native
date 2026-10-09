// The viewer for asf2gltf's .glb files (tools/gltf-viewer/README.md): the model with the game's shaders
// (SOA_aska_shader) or the PBR fallback, the animation set by role with a face layer, the timeline of
// effect triggers and sound cues, morph targets, KHR_animation_pointer / KHR_node_visibility, the PRS
// constraints evaluated live (SOA_aska_constraints), the skeleton and the physics-driven joints, camera
// presets, and the home behaviour replayed from the Home3D table (extras.soa_home3d).
import * as THREE from 'three';
import { OrbitControls } from 'three/addons/controls/OrbitControls.js';
import { loadSoaGltf, applyPointer } from './soa-gltf.js';
import { ClipSampler, RestPose, applyLayers } from './soa-anim.js';
import { Constraints } from './constraints.js';
import { GameMaterials } from './aska-shader.js';
import { HomeBehaviour } from './home.js';

const $ = (id) => document.getElementById(id);
const view = $('view');
const renderer = new THREE.WebGLRenderer({ antialias: true, preserveDrawingBuffer: true });
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
renderer.outputColorSpace = THREE.SRGBColorSpace;
view.prepend(renderer.domElement);
const scene = new THREE.Scene();
scene.background = new THREE.Color(0x2a2e36);
const camera = new THREE.PerspectiveCamera(30, 1, 0.01, 2000);
camera.position.set(0, 1.2, 4);
const controls = new OrbitControls(camera, renderer.domElement);
controls.target.set(0, 1, 0);
controls.update();
// PBR lighting after the game's home scene (a warm key light from the front-left above, a cool ambient)
scene.add(new THREE.HemisphereLight(0xc8d4ff, 0x404048, 1.2));
const key = new THREE.DirectionalLight(0xfff0f8, 2.2);
key.position.set(1.5, 3, 4);
scene.add(key);
const grid = new THREE.GridHelper(4, 8, 0x445066, 0x30343c);
scene.add(grid);

// The game's shaders write linear light scaled by 1 / cvHDRTransform.x into a float target that the game's
// post pass shows; here: a half-float target, then x * cvHDRTransform.x, clamped, sRGB-encoded (d: the
// game's post pass (bloom, tone curve) isn't captured). The grid and the overlays are drawn after it.
const gameTarget = new THREE.WebGLRenderTarget(1, 1, { type: THREE.HalfFloatType, samples: 4 });
const postScene = new THREE.Scene();
const postCamera = new THREE.OrthographicCamera(-1, 1, 1, -1, 0, 1);
const postMat = new THREE.ShaderMaterial({
  glslVersion: THREE.GLSL3,
  uniforms: { src: { value: gameTarget.texture }, hdr: { value: 1 }, bg: { value: new THREE.Color() } },
  vertexShader: 'out vec2 vUv; void main() { vUv = uv; gl_Position = vec4(position.xy, 0.0, 1.0); }',
  fragmentShader: `in vec2 vUv; uniform sampler2D src; uniform float hdr; uniform vec3 bg; layout(location = 0) out vec4 o;
    vec3 enc(vec3 c) { c = clamp(c, 0.0, 1.0); return mix(c * 12.92, 1.055 * pow(c, vec3(1.0 / 2.4)) - 0.055, step(0.0031308, c)); }
    void main() { vec4 t = texture(src, vUv); vec3 c = t.rgb * hdr; o = vec4(mix(enc(bg), enc(c), clamp(t.a, 0.0, 1.0)), 1.0); }`,
  depthTest: false, depthWrite: false,
});
postScene.add(new THREE.Mesh(new THREE.PlaneGeometry(2, 2), postMat));

function renderView() {
  if (!(state.matMode === 'game' && state.game && state.game.ready)) {
    renderer.render(scene, camera);
    return;
  }
  const size = renderer.getDrawingBufferSize(new THREE.Vector2());
  if (gameTarget.width !== size.x || gameTarget.height !== size.y) gameTarget.setSize(size.x, size.y);
  const gridWas = grid.visible;
  grid.visible = false;  // (the post pass would brighten it; it isn't drawn in the game's mode)
  const hidden = [...state.helpers].filter((o) => o.visible);
  for (const o of hidden) o.visible = false;
  const bgc = scene.background;
  scene.background = null;
  renderer.setClearColor(0x000000, 0);
  renderer.setRenderTarget(gameTarget);
  renderer.clear();
  state.game.setDisplay(false);
  renderer.render(scene, camera);
  renderer.setRenderTarget(null);
  scene.background = bgc;
  postMat.uniforms.hdr.value = state.game.hdrScale();
  postMat.uniforms.bg.value.copy(bgc);  // (a three Color holds linear values)
  renderer.render(postScene, postCamera);
  for (const o of hidden) o.visible = true;
  grid.visible = gridWas;
  if (hidden.length) {
    const autoClear = renderer.autoClear;
    renderer.autoClear = false;
    const keep = scene.children.filter((c) => !hidden.includes(c) && c.visible);
    for (const c of keep) c.visible = false;
    scene.background = null;
    renderer.render(scene, camera);
    scene.background = bgc;
    for (const c of keep) c.visible = true;
    renderer.autoClear = autoClear;
  }
}

const state = {
  model: null, rest: null, samplers: new Map(), anim: -1, face: -1, time: 0, playing: false, speed: 1, loop: true,
  fps: 60, constraints: null, game: null, home: null, helpers: [], matMode: 'pbr',
};
window.soaViewer = state;  // for the headless test and the console

function resize() {
  const w = view.clientWidth, h = view.clientHeight;
  renderer.setSize(w, h, false);
  camera.aspect = w / Math.max(h, 1);
  camera.updateProjectionMatrix();
}
window.addEventListener('resize', resize);
resize();

function sampler(i) {
  if (i < 0 || !state.model) return null;
  if (!state.samplers.has(i)) state.samplers.set(i, new ClipSampler(state.model.gltf.animations[i], state.model.gltf.scene));
  return state.samplers.get(i);
}

function animExtras(i) {
  const a = state.model && state.model.json.animations && state.model.json.animations[i];
  return (a && a.extras) || {};
}

function clipFps(i) {
  const e = animExtras(i);
  return e.fps || state.fps;
}

// ---- loading ----
async function load(source, label) {
  setStatus(`loading ${label} …`);
  try {
    const model = await loadSoaGltf(source);
    if (state.model) {
      scene.remove(state.model.gltf.scene);
      for (const h of state.helpers) scene.remove(h);
      state.helpers = [];
    }
    if (state.home) state.home.stop();
    state.model = model;
    state.samplers = new Map();
    state.anim = -1;
    state.face = -1;
    state.time = 0;
    scene.add(model.gltf.scene);
    model.gltf.scene.updateMatrixWorld(true);
    state.rest = new RestPose(model.gltf.scene);
    state.constraints = new Constraints(model);
    state.game = new GameMaterials(model, renderer);
    state.home = new HomeBehaviour(model, state, hooksForHome());
    state.label = label;
    fillModelInfo();
    fillAnimations();
    fillMorphs();
    fillNodes();
    applyMaterialMode();
    setCamera('front');
    setStatus('');
    window.soaViewerReady = true;
  } catch (e) {
    console.error(e);
    setStatus(`cannot load ${label}: ${e.message || e}`);
    window.soaViewerError = String(e && e.stack || e);
  }
}

function setStatus(s) { state.status = s; }

function fillModelInfo() {
  const j = state.model.json;
  const ex = state.model.gltf.userData || {};
  const src = (j.asset.extras && j.asset.extras.source) || '';
  const used = (j.extensionsUsed || []).join(', ');
  $('modelinfo').textContent = `${state.label}\n${src}  ·  ${(j.nodes || []).length} nodes, ${(j.meshes || []).length} meshes, ` +
    `${(j.materials || []).length} materials, ${(j.animations || []).length} animations${used ? '\nextensions: ' + used : ''}`;
  $('modelinfo').style.whiteSpace = 'pre-wrap';
  const file = { asset: j.asset, extensionsUsed: j.extensionsUsed, extras: ex.soa_set ? { soa_set: ex.soa_set } : ex };
  if (ex.soa_home3d) file.soa_home3d = { rows: ex.soa_home3d.rows.length, clips: ex.soa_home3d.clips, camera: ex.soa_home3d.camera, rules: ex.soa_home3d.rules };
  $('fileinfo').textContent = JSON.stringify(file, null, 1);
  $('home').disabled = !ex.soa_home3d;
  $('tap').disabled = !ex.soa_home3d;
}

const ROLE_ORDER = ['battle/skill', 'battle', 'viewer', 'home/face', 'home/eye', 'home', ''];
function roleGroup(role) {
  for (const r of ROLE_ORDER) if (role.startsWith(r)) return r || 'other';
  return 'other';
}

function fillAnimations() {
  const sel = $('anims'), face = $('face');
  sel.innerHTML = '';
  face.innerHTML = '<option value="">none</option>';
  const groups = new Map();
  (state.model.json.animations || []).forEach((a, i) => {
    const role = (a.extras && a.extras.role) || '';
    const g = roleGroup(role);
    if (!groups.has(g)) groups.set(g, []);
    groups.get(g).push([i, a.name || `animation ${i}`]);
    if (g === 'home/face' || g === 'home/eye') face.add(new Option(a.name, i));
  });
  for (const g of ROLE_ORDER.map((r) => r || 'other')) {
    if (!groups.has(g)) continue;
    const og = document.createElement('optgroup');
    og.label = { 'battle/skill': 'battle: skills', battle: 'battle', viewer: 'character viewer', 'home/face': 'home: faces',
      'home/eye': 'home: blinks', home: 'home', other: 'other' }[g];
    for (const [i, n] of groups.get(g)) og.appendChild(new Option(n, i));
    sel.appendChild(og);
  }
  if (sel.options.length) {
    // start on the home stay motion, else the battle idle, else the first
    const anims = state.model.json.animations || [];
    let first = anims.findIndex((a) => a.extras && a.extras.role === 'home/stay');
    if (first < 0) first = anims.findIndex((a) => a.extras && a.extras.role === 'battle/idle');
    if (first < 0) first = Number(sel.options[0].value);
    sel.value = String(first);
    selectAnim(first);
  } else {
    selectAnim(-1);
  }
}

function fillMorphs() {
  const box = $('morphs');
  box.innerHTML = '';
  state.model.gltf.scene.traverse((o) => {
    if (!o.morphTargetInfluences || !o.morphTargetInfluences.length) return;
    const names = (o.userData && o.userData.targetNames) || (o.parent && o.parent.userData.targetNames) || [];
    o.morphTargetInfluences.forEach((w, k) => {
      const l = document.createElement('span');
      l.textContent = `${o.name}: ${names[k] || k}`;
      const r = document.createElement('input');
      r.type = 'range'; r.min = 0; r.max = 1; r.step = 0.01; r.value = w;
      r.oninput = () => {
        o.morphTargetInfluences[k] = Number(r.value);
        // the rest pose keeps the slider's value (an animation's weights channel still overrides it)
        const it = state.rest.items.find((x) => x.o === o);
        if (it && it.m) it.m[k] = Number(r.value);
      };
      box.append(l, r);
    });
  });
  if (!box.children.length) box.innerHTML = '<span class="dim">none</span>';
}

function fillNodes() {
  // nodes the file hides (KHR_node_visibility) or marks physics-driven
  const j = state.model.json;
  const hidden = [], physics = [];
  (j.nodes || []).forEach((n, i) => {
    if (n.extensions && n.extensions.KHR_node_visibility && n.extensions.KHR_node_visibility.visible === false) hidden.push(n.name || i);
    if (n.extras && n.extras.physics_driven) physics.push(n.name || i);
  });
  $('nodes').textContent = `${hidden.length} nodes hidden (KHR_node_visibility)${hidden.length ? ': ' + hidden.slice(0, 8).join(', ') : ''}; ` +
    `${physics.length} physics-driven joints (rest pose: the game's physics isn't in the file)`;
}

// ---- animation selection and playback ----
function selectAnim(i) {
  state.anim = i;
  state.time = 0;
  const e = animExtras(i);
  const clip = i >= 0 ? state.model.gltf.animations[i] : null;
  const fps = clipFps(i);
  const frames = clip ? Math.round(clip.duration * fps) : 0;
  $('scrub').max = frames;
  $('flen').textContent = clip ? `/ ${frames} @ ${fps}` : '';
  const shown = { ...e };
  for (const k of ['channels', 'not_exported']) if (shown[k]) shown[k] = `(${Array.isArray(shown[k]) ? shown[k].length : Object.keys(shown[k]).length} entries)`;
  $('animinfo').textContent = clip ? JSON.stringify(shown, null, 1) : '';
  drawTimeline();
}

function frameNow() { return Math.round(state.time * clipFps(state.anim)); }

function drawTimeline() {
  const c = $('timeline');
  const w = c.clientWidth || 300, h = c.clientHeight || 34;
  c.width = w; c.height = h;
  const g = c.getContext('2d');
  g.clearRect(0, 0, w, h);
  const clip = state.anim >= 0 ? state.model.gltf.animations[state.anim] : null;
  if (!clip) return;
  const fps = clipFps(state.anim), frames = Math.max(1, clip.duration * fps);
  const x = (f) => 2 + (w - 4) * f / frames;
  const e = animExtras(state.anim);
  g.fillStyle = '#555b66';
  for (const s of e.signals || []) for (const k of s.keys || []) g.fillRect(x(k.frame), h - 6, 1, 5);
  g.fillStyle = '#6cb6ff';
  for (const s of e.sounds || []) g.fillRect(x(s.frame) - 1, 13, 3, 9);
  g.fillStyle = '#ffb86c';
  for (const ef of e.effects || []) for (const f of ef.frames || []) g.fillRect(x(f) - 1, 2, 3, 10);
  g.fillStyle = '#ffffff';
  g.fillRect(x(state.time * fps), 0, 1, h);
}

$('timeline').addEventListener('click', (ev) => {
  const clip = state.anim >= 0 ? state.model.gltf.animations[state.anim] : null;
  if (!clip) return;
  const r = ev.target.getBoundingClientRect();
  state.time = Math.max(0, Math.min(1, (ev.clientX - r.left) / r.width)) * clip.duration;
});

function step(dt) {
  if (!state.model) return;
  if (state.home && state.home.active) {
    state.home.update(dt);  // the home behaviour drives its own layers
  } else {
    const clip = state.anim >= 0 ? state.model.gltf.animations[state.anim] : null;
    if (clip && state.playing) {
      state.time += dt * state.speed;
      if (state.time > clip.duration) state.time = state.loop ? state.time % Math.max(clip.duration, 1e-6) : clip.duration;
    }
    const layers = [];
    if (clip) layers.push({ sampler: sampler(state.anim), time: state.time, weight: 1 });
    if (state.face >= 0) {
      const fc = state.model.gltf.animations[state.face];
      // a facial expression holds its pose: its own clock, looped over its length
      layers.push({ sampler: sampler(state.face), time: fc.duration > 0 ? state.time % fc.duration : 0, weight: 1, overwrite: true });
    }
    applyLayers(state.rest, layers);
    if (clip) applyPointer(state.model, state.anim, state.time);
    if (state.face >= 0) applyPointer(state.model, state.face, state.time);
  }
  state.model.gltf.scene.updateMatrixWorld(true);
  if ($('constraints').checked && state.constraints) state.constraints.apply(state.home && state.home.active ? state.home.bodyAnim() : state.anim, frameNow());
  if (state.game && state.matMode === 'game') state.game.update(camera);
}

// ---- UI wiring ----
$('anims').onchange = () => { if (state.home) state.home.stop(); selectAnim(Number($('anims').value)); };
$('face').onchange = () => { state.face = $('face').value === '' ? -1 : Number($('face').value); };
$('play').onclick = () => { state.playing = !state.playing; };
$('prev').onclick = () => { state.playing = false; state.time = Math.max(0, (frameNow() - 1) / clipFps(state.anim)); };
$('next').onclick = () => { state.playing = false; state.time = (frameNow() + 1) / clipFps(state.anim); };
$('frame').onchange = () => { state.playing = false; state.time = Number($('frame').value) / clipFps(state.anim); };
$('scrub').oninput = () => { state.playing = false; state.time = Number($('scrub').value) / clipFps(state.anim); };
$('speed').onchange = () => { state.speed = Number($('speed').value); };
$('loop').onchange = () => { state.loop = $('loop').checked; };
for (const r of document.querySelectorAll('input[name=mat]')) r.onchange = () => { state.matMode = r.value; applyMaterialMode(); };
$('skeleton').onchange = updateHelpers;
$('physics').onchange = updateHelpers;
$('grid').onchange = () => { grid.visible = $('grid').checked; };
for (const b of document.querySelectorAll('[data-cam]')) b.onclick = () => setCamera(b.dataset.cam);
$('home').onclick = () => { if (!state.home) return; if (state.home.active) state.home.stop(); else state.home.start(); };
$('tap').onclick = () => { if (state.home) state.home.tap(); };
$('favor').onchange = () => { if (state.home) state.home.favor = Number($('favor').value); };

function applyMaterialMode() {
  if (!state.game) return;
  const ok = state.game.setMode(state.matMode);
  $('matinfo').textContent = state.game.describe();
  if (!ok && state.matMode === 'game') {
    state.matMode = 'pbr';
    document.querySelector('input[name=mat][value=pbr]').checked = true;
  }
}

function updateHelpers() {
  for (const h of state.helpers) scene.remove(h);
  state.helpers = [];
  if (!state.model) return;
  if ($('skeleton').checked) {
    const h = new THREE.SkeletonHelper(state.model.gltf.scene);
    h.material.depthTest = false;
    h.material.transparent = true;
    h.renderOrder = 10;
    state.helpers.push(h);
  }
  if ($('physics').checked) {
    const geo = new THREE.SphereGeometry(0.008, 8, 6);
    const mat = new THREE.MeshBasicMaterial({ color: 0xff8040, depthTest: false });
    state.model.gltf.scene.traverse((o) => {
      if (o.userData && o.userData.physics_driven) {
        const m = new THREE.Mesh(geo, mat);
        m.renderOrder = 11;
        m.userData.follow = o;
        state.helpers.push(m);
      }
    });
  }
  for (const h of state.helpers) scene.add(h);
}

function boneByName(name) {
  let found = null;
  state.model.gltf.scene.traverse((o) => { if (!found && o.name === name) found = o; });
  return found;
}

function setCamera(kind) {
  if (!state.model) return;
  const box = new THREE.Box3();
  state.model.gltf.scene.traverse((o) => {
    let vis = true;
    for (let p = o; p; p = p.parent) vis = vis && p.visible;
    if (!(o.isMesh && vis)) return;
    let b;
    if (o.isSkinnedMesh) { o.computeBoundingBox(); b = o.boundingBox.clone().applyMatrix4(o.matrixWorld); } else {
      o.geometry.computeBoundingBox();
      b = o.geometry.boundingBox.clone().applyMatrix4(o.matrixWorld);
    }
    if (b.max.y - b.min.y < 50 && b.max.y - b.min.y > 0.02) box.union(b);  // not scenery, not a collapsed mesh
  });
  if (box.isEmpty()) box.set(new THREE.Vector3(-1, 0, -1), new THREE.Vector3(1, 2, 1));
  const c = box.getCenter(new THREE.Vector3()), size = box.getSize(new THREE.Vector3());
  let target = c.clone(), dist = Math.max(size.y, size.x * 1.6) / (2 * Math.tan(THREE.MathUtils.degToRad(camera.fov / 2))) * 1.1;
  let az = 0, el = 0.08;
  if (camera.fov !== 30) { camera.fov = 30; camera.updateProjectionMatrix(); }
  if (kind === 'three-quarter') az = 35;
  if (kind === 'side') az = 90;
  if (kind === 'back') az = 180;
  if (kind === 'face') {
    const head = boneByName('Head') || boneByName('head');
    if (head) { head.getWorldPosition(target); target.y += 0.06; }
    dist = 0.6;
  }
  if (kind === 'home' && state.home) {
    const cam = state.home.cameraPreset(camera);
    if (cam) { target = cam.target; dist = cam.distance; el = cam.elevation; }
  }
  const a = THREE.MathUtils.degToRad(az);
  camera.position.set(target.x + Math.sin(a) * Math.cos(el) * dist, target.y + Math.sin(el) * dist, target.z + Math.cos(a) * Math.cos(el) * dist);
  controls.target.copy(target);
  controls.update();
}

function hooksForHome() {
  return {
    sampler, line: (text) => {
      const l = $('line');
      l.style.display = text ? 'block' : 'none';
      l.textContent = text || '';
    },
    info: (text) => { $('homeinfo').textContent = text; },
    apply: (layers) => applyLayers(state.rest, layers),
    english: () => $('en').checked,
  };
}

// ---- files ----
$('file').onchange = async () => {
  const f = $('file').files[0];
  if (f) load(await f.arrayBuffer(), f.name);
};
view.addEventListener('dragover', (e) => { e.preventDefault(); $('drop').classList.add('on'); });
view.addEventListener('dragleave', () => $('drop').classList.remove('on'));
view.addEventListener('drop', async (e) => {
  e.preventDefault();
  $('drop').classList.remove('on');
  const f = e.dataTransfer.files[0];
  if (f) load(await f.arrayBuffer(), f.name);
});
$('models').onchange = () => { if ($('models').value) load($('models').value, $('models').value); };
fetch('/models.json').then((r) => r.ok ? r.json() : []).then((list) => {
  for (const m of list) $('models').add(new Option(`${m.name} (${(m.bytes / 1048576).toFixed(1)} MB)`, m.url));
}).catch(() => {});
const params = new URLSearchParams(location.search);
if (params.get('ui') === '0') { $('side').style.display = 'none'; resize(); }  // the view alone (screenshots)
if (params.get('model')) load(params.get('model'), params.get('model'));
if (params.get('anim') !== null) state.wantAnim = params.get('anim');

// ---- loop ----
const clock = new THREE.Timer();
function frame() {
  clock.update();
  const dt = Math.min(clock.getDelta(), 0.1);
  step(dt);
  for (const h of state.helpers) if (h.userData.follow) h.userData.follow.getWorldPosition(h.position);
  renderView();
  const f = frameNow();
  if (document.activeElement !== $('frame')) $('frame').value = f;
  $('scrub').value = f;
  drawTimeline();
  const shown = state.home && state.home.active ? state.home.bodyAnim() : state.anim;
  $('hud').textContent = (state.status || '') + (state.model && shown >= 0 ? `${state.model.json.animations[shown].name}  frame ${f}` : '') +
    (state.home && state.home.active ? `\n${state.home.hud()}` : '');
  requestAnimationFrame(frame);
}
requestAnimationFrame(frame);

// for the headless test: render a given animation frame synchronously
window.soaRenderAt = (anim, frameNo, cam) => {
  if (anim !== undefined && anim !== null) selectAnim(Number(anim));
  state.playing = false;
  state.time = (frameNo || 0) / clipFps(state.anim);
  if (cam) setCamera(cam);
  step(0);
  renderView();
  return true;
};
window.soaSetMaterialMode = (m) => { state.matMode = m; applyMaterialMode(); return state.game ? state.game.describe() : ''; };
window.soaSetFace = (i) => { state.face = i; };
// for the headless test: advance the clock by whole game frames (playing), then draw
window.soaAdvance = (frames) => {
  const was = state.playing;
  state.playing = true;
  for (let i = 0; i < frames; i++) step(1 / 60);
  state.playing = was;
  renderView();
  return { frame: frameNow(), hud: state.home && state.home.active ? state.home.hud() : '', log: state.home && state.home.log ? state.home.log.slice() : [] };
};
window.soaHome = (cmd) => {
  if (!state.home) return 'no model';
  if (cmd === 'start') state.home.start();
  else if (cmd === 'tap') state.home.tap();
  else if (cmd === 'stop') state.home.stop();
  return state.home.active ? state.home.hud() : 'inactive';
};
// for the headless test: load a glTF given as text (a .gltf with data: URIs)
window.soaLoadText = (text, label) => { window.soaViewerReady = false; window.soaViewerError = ''; load(new TextEncoder().encode(text).buffer, label || 'test.gltf'); };

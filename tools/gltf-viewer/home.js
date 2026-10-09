// The home behaviour replayed from the file's Home3D table (extras.soa_home3d; the rules and their
// addresses: docs/home3d.md "The home behaviour, frame by frame"):
//  - stay: a stay row looped; once it has played through, a counter runs to 121 frames, then
//    Random(2) == 1 plays a stay_long row (45 frames of blending, once, its facial anim layered); after it,
//    stay or stay_long again, 50 % each (PlayStayMotionRandom @0147fb8c, Progress_HomeTalk @0147ccec);
//  - a tap: a talk / reaction row, weighted, gated by favor level and date, never the same row twice in a
//    row (TapReactionMotionRandom @01484a18), blended in over its blend_frame, its facial anim as an
//    overwrite layer, its line in the speech box; afterwards stay or stay_long as after a stay_long (d);
//  - blinks: a timer against the current blink clip's length, eye or eye2 at random (EyeMotion @0148151c),
//    stopped while a row with no_blink plays;
//  - mouth: while the line's voice "plays" the mouth clip restarts each time it ends (MouthMotion @014816f4);
//    no audio here: the voice is taken to last as long as the row's motion (d), and not_lipsync_voice /
//    no_lipsync rows keep the mouth still.
// Random numbers: a seeded generator (the game's Aska::Random / HighPrecisionRandom aren't reproduced).
import * as THREE from 'three';

const FPS = 60;

function rng(seed) {
  let s = seed >>> 0;
  return () => { s = (s * 1664525 + 1013904223) >>> 0; return s / 4294967296; };
}

export class HomeBehaviour {
  constructor(model, state, hooks) {
    this.model = model;
    this.state = state;
    this.hooks = hooks;
    this.table = (model.gltf.userData || {}).soa_home3d || null;
    this.active = false;
    this.favor = 5;
    this.date = '2021/03/30 00:00:00';  // the service's last days (d): the rows open then
    this.random = rng(20260409);
    this.byName = new Map();
    (model.json.animations || []).forEach((a, i) => this.byName.set(a.name, i));
  }

  anim(name) { return name && this.byName.has(name) ? this.byName.get(name) : -1; }

  clipFrames(i) { return i < 0 ? 0 : this.model.gltf.animations[i].duration * FPS; }

  available(r) {
    if (r.opened_at && r.opened_at > this.date) return false;
    if (r.closed_at && r.closed_at < this.date) return false;
    return true;
  }

  rows(cats) { return (this.table ? this.table.rows : []).filter((r) => cats.includes(r.category)); }

  // GetRandomMotion @014830a0: weighted among available rows with weight > 0 in the favor range
  pick(rows, exclude) {
    let list = rows.filter((r) => r.motion && this.available(r) && r.weight > 0 &&
      this.favor >= (r.level_low || 0) && this.favor <= (r.level_upper === undefined ? 9999 : r.level_upper));
    if (exclude !== undefined && list.length > 1) list = list.filter((r) => r.id !== exclude);
    const sum = list.reduce((s, r) => s + r.weight, 0);
    if (!sum) return null;
    let x = Math.floor(this.random() * sum);
    for (const r of list) { if (x < r.weight) return r; x -= r.weight; }
    return list[list.length - 1];
  }

  start() {
    if (!this.table) return;
    this.active = true;
    this.body = [];
    this.face = null;
    this.blink = { timer: 0, interval: 0, layer: null };
    this.mouth = null;
    this.voice = null;
    this.lastTap = undefined;
    this.log = [];
    this.playStay(0, 0);
  }

  stop() {
    this.active = false;
    if (this.hooks.line) this.hooks.line('');
  }

  bodyAnim() { const b = this.body && this.body[this.body.length - 1]; return b ? b.anim : -1; }

  setBody(row, anim, blend, loop, kind) {
    this.body.push({ anim, time: 0, weight: this.body.length ? 0 : 1, blend: Math.max(blend, 0), loop, kind, row, age: 0 });
    this.face = row && row.facial ? { anim: this.anim(row.facial), time: 0 } : null;
    this.note(`${kind}: ${row ? row.id_label : ''} ${this.model.json.animations[anim] ? this.model.json.animations[anim].name : '?'} (blend ${blend})`);
  }

  // PlayStayMotionRandom: mode 0 stay (blend: the given frames, or the row's), 1 stay_long (45), >1 Random(2)
  playStay(mode, blend) {
    if (mode > 1) mode = this.random() < 0.5 ? 0 : 1;
    const row = this.pick(this.rows([mode === 0 ? 'stay' : 'stay_long'])) ||
      this.rows([mode === 0 ? 'stay' : 'stay_long']).find((r) => r.motion);
    if (!row) { if (mode === 1) return this.playStay(0, blend); return; }
    const a = this.anim(row.motion);
    if (a < 0) return;
    this.setBody(row, a, mode === 0 ? (blend < 0 ? row.blend_frame : blend) : 45, mode === 0, mode === 0 ? 'stay' : 'stay_long');
    this.stayCounter = mode === 0 ? 0 : -1;
    this.eyesFor(row);
    this.mouth = null;
  }

  eyesFor(row) {
    if (row && row.no_blink) { this.blink.timer = -1; this.blink.layer = null; } else if (this.blink.timer < 0) this.blink.timer = 0;
  }

  tap() {
    if (!this.table) return;
    if (!this.active) this.start();
    const row = this.pick(this.rows(['talk', 'reaction']), this.lastTap);
    if (!row) { this.note('tap: no row available'); return; }
    this.lastTap = row.id;
    const a = this.anim(row.motion);
    if (a < 0) return;
    this.setBody(row, a, row.blend_frame || 45, false, 'tap');
    this.stayCounter = -1;
    this.eyesFor(row);
    const en = this.hooks.english && this.hooks.english();
    const text = (en && row.text_en) || row.text_ja || row.text_id || '';
    this.voice = { row, left: this.clipFrames(a) };
    this.hooks.line(`${text}${row.voice_id ? `\n♪ ${row.voice_id}` : ''}${row.facial_effect_filename ? `  ✦ ${row.facial_effect_filename}` : ''}`);
    const lipsync = !row.no_lipsync && !row.not_lipsync_voice;
    this.mouth = lipsync && this.table.clips && this.anim(this.table.clips.mouth) >= 0 ? { anim: this.anim(this.table.clips.mouth), time: 0, timer: 0, len: 0 } : null;
  }

  note(s) {
    this.log.push(s);
    if (this.log.length > 8) this.log.shift();
    if (this.hooks.info) this.hooks.info(this.log.join('\n'));
  }

  update(dt) {
    const frames = dt * FPS;
    const clips = this.table.clips || {};
    // body slots: the newest fades in over its blend frames; the older ones drop out once it is full
    for (const b of this.body) { b.time += dt; b.age += frames; }
    const top = this.body[this.body.length - 1];
    if (top) {
      top.weight = top.blend > 0 ? Math.min(1, top.age / top.blend) : 1;
      for (const b of this.body) if (b !== top) b.weight = 1 - top.weight;
      if (top.weight >= 1) this.body = [top];
      const len = this.model.gltf.animations[top.anim].duration;
      const ended = top.time >= len;
      if (top.loop && ended) { top.time %= Math.max(len, 1e-6); top.passes = (top.passes || 0) + 1; }
      // Progress_HomeTalk: the stay counter after the stay has played through
      if (top.kind === 'stay' && top.passes > 0 && this.stayCounter >= 0) {
        if (this.stayCounter < 121) this.stayCounter += frames;
        else {
          this.stayCounter = 0;
          this.mouth = null;
          if (this.random() < 0.5) this.playStay(1, top.row ? top.row.blend_frame : 45);
        }
      } else if (!top.loop && ended && top.kind !== 'stay') {
        this.hooks.line('');
        this.voice = null;
        this.playStay(99, -1);
      }
    }
    // blinks
    const b = this.blink;
    if (b.timer >= 0) {
      if (b.timer > b.interval) {
        const which = this.random() < 0.5 ? 'eye' : 'eye2';
        const a = this.anim(clips[which]);
        if (a >= 0) { b.layer = { anim: a, time: 0 }; b.interval = this.clipFrames(a); }
        if (which === 'eye') b.timer = 0;
      } else b.timer += frames;
    }
    if (b.layer) b.layer.time += dt;
    // mouth while the voice plays
    if (this.voice) {
      this.voice.left -= frames;
      if (this.voice.left <= 0) { this.voice = null; this.mouth = null; }
    }
    if (this.mouth) {
      if (this.mouth.timer > this.mouth.len) { this.mouth.time = 0; this.mouth.timer = 0; this.mouth.len = this.clipFrames(this.mouth.anim); } else this.mouth.timer += frames;
      this.mouth.time += dt;
    }
    if (this.face) this.face.time += dt;
    // the layers: body slots (blended like AafBlendManager), then the facial overwrite, blink, mouth
    const s = this.hooks.sampler;
    const layers = this.body.map((x) => ({ sampler: s(x.anim), time: x.time, weight: x.weight }));
    if (this.face && this.face.anim >= 0) {
      const fl = this.model.gltf.animations[this.face.anim].duration;
      layers.push({ sampler: s(this.face.anim), time: Math.min(this.face.time, fl), weight: 1, overwrite: true });
    }
    if (b.layer && b.timer >= 0) {
      const bl = this.model.gltf.animations[b.layer.anim].duration;
      layers.push({ sampler: s(b.layer.anim), time: Math.min(b.layer.time, bl), weight: 1, overwrite: true });
    }
    if (this.mouth) layers.push({ sampler: s(this.mouth.anim), time: this.mouth.time, weight: 1, overwrite: true });
    this.state.layers = layers;
    this.hooks.apply(layers);
    if (top) this.state.time = top.time;
  }

  hud() {
    const top = this.body && this.body[this.body.length - 1];
    return `home: ${top ? top.kind + ' ' + (top.row ? top.row.id_label : '') : '-'}  counter ${Math.round(this.stayCounter)}  ` +
      `blink ${this.blink && this.blink.timer >= 0 ? Math.round(this.blink.timer) + '/' + Math.round(this.blink.interval) : 'off'}` +
      `${this.mouth ? '  mouth' : ''}  favor ${this.favor}`;
  }

  // the game's home camera (SetCameraPos @01477a10): the map's camera1, 550 cm in front at the aim
  // height, 15 degrees; aim height (portrait 9:16) = person height + home3d_camera_height_offset - 40 cm
  cameraPreset(camera) {
    const c = this.table ? this.table.camera || {} : {};
    const a = camera.aspect / 0.5625;
    const aim = 90 + (c.height || 160) + (c.height_offset || 0) + (1 - 0.1 * (a - 1)) * -130;
    camera.fov = 15;
    camera.updateProjectionMatrix();
    return { target: new THREE.Vector3(0, aim / 100, 0), distance: 5.5 + (c.depth_offset || 0) / 100, elevation: 0 };
  }
}

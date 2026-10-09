// Loading asf2gltf's .glb with three.js' GLTFLoader, plus what GLTFLoader leaves out:
//  - KHR_animation_pointer channels (GLTFLoader skips channels without a node): sampled here and written
//    to the materials / nodes they point at (material factors, KHR_texture_transform, node visibility,
//    node TRS and morph weights);
//  - KHR_node_visibility (static and animated);
//  - the file's vendor data, kept as parsed JSON for the other modules (SOA_aska_shader, SOA_aska_constraints,
//    the extras: docs/notes.md "glTF export").
import * as THREE from 'three';
import { GLTFLoader } from 'three/addons/loaders/GLTFLoader.js';

// A KHR_animation_pointer channel: its sampler evaluated by hand (the values are few).
class PointerChannel {
  constructor(pointer, times, values, size, interpolation) {
    this.pointer = pointer;
    this.times = times;
    this.values = values;
    this.size = size;
    this.interpolation = interpolation || 'LINEAR';
    this.out = new Float32Array(size);
    this.targets = [];
  }

  evaluate(t) {
    const { times, values, size, out } = this;
    const n = times.length;
    const cubic = this.interpolation === 'CUBICSPLINE';
    const stride = cubic ? 3 * size : size;
    const at = (k, c) => values[k * stride + (cubic ? size : 0) + c];
    if (n === 0) return out;
    if (t <= times[0] || n === 1) {
      for (let c = 0; c < size; c++) out[c] = at(0, c);
      return out;
    }
    if (t >= times[n - 1]) {
      for (let c = 0; c < size; c++) out[c] = at(n - 1, c);
      return out;
    }
    let k = 0;
    while (k < n - 2 && times[k + 1] <= t) k++;
    const t0 = times[k], t1 = times[k + 1], dt = t1 - t0;
    const s = dt > 0 ? (t - t0) / dt : 0;
    if (this.interpolation === 'STEP') {
      for (let c = 0; c < size; c++) out[c] = at(k, c);
    } else if (cubic) {  // glTF 2.0 Appendix C: Hermite with tangents scaled by the interval
      const s2 = s * s, s3 = s2 * s;
      for (let c = 0; c < size; c++) {
        const p0 = at(k, c), p1 = at(k + 1, c);
        const m0 = values[k * stride + 2 * size + c] * dt, m1 = values[(k + 1) * stride + c] * dt;
        out[c] = (2 * s3 - 3 * s2 + 1) * p0 + (s3 - 2 * s2 + s) * m0 + (-2 * s3 + 3 * s2) * p1 + (s3 - s2) * m1;
      }
    } else {
      for (let c = 0; c < size; c++) out[c] = at(k, c) + (at(k + 1, c) - at(k, c)) * s;
      if (size === 4 && /\/rotation$/.test(this.pointer)) {  // a quaternion: slerp
        const q0 = new THREE.Quaternion().fromArray(values, k * stride);
        const q1 = new THREE.Quaternion().fromArray(values, (k + 1) * stride);
        q0.slerp(q1, s).toArray(out);
      }
    }
    return out;
  }
}

// glTF's KHR_texture_transform order (T * R * S), as GLTFLoader's own extension sets it.
export function setTextureTransform(tex, offset, scale, rotation) {
  if (!tex) return;
  if (offset) tex.offset.set(offset[0], offset[1]);
  if (scale) tex.repeat.set(scale[0], scale[1]);
  if (rotation !== undefined) tex.rotation = rotation;
  const c = Math.cos(tex.rotation), s = Math.sin(tex.rotation);
  tex.matrix.set(tex.repeat.x * c, tex.repeat.y * s, tex.offset.x,
    -tex.repeat.x * s, tex.repeat.y * c, tex.offset.y, 0, 0, 1);
  tex.matrixAutoUpdate = false;
}

const TEXTURE_SLOTS = {
  'pbrMetallicRoughness/baseColorTexture': ['map'],
  'pbrMetallicRoughness/metallicRoughnessTexture': ['roughnessMap', 'metalnessMap'],
  emissiveTexture: ['emissiveMap'],
  normalTexture: ['normalMap'],
  occlusionTexture: ['aoMap'],
};

// The three.js objects a pointer writes, and how.
function resolvePointer(pointer, maps) {
  const p = pointer.split('/').slice(1);
  const out = [];
  if (p[0] === 'materials') {
    const mats = maps.materials.get(Number(p[1])) || [];
    const rest = p.slice(2).join('/');
    for (const m of mats) {
      if (rest === 'pbrMetallicRoughness/baseColorFactor') {
        out.push((v) => { m.color.setRGB(v[0], v[1], v[2]); m.opacity = v[3]; m.userData.soaBaseColor = Array.from(v); });
      } else if (rest === 'emissiveFactor') {
        out.push((v) => { m.emissive.setRGB(v[0], v[1], v[2]); m.userData.soaEmissive = Array.from(v); });
      } else if (rest === 'alphaCutoff') {
        out.push((v) => { m.alphaTest = v[0]; });
      } else if (rest === 'pbrMetallicRoughness/metallicFactor') {
        out.push((v) => { m.metalness = v[0]; });
      } else if (rest === 'pbrMetallicRoughness/roughnessFactor') {
        out.push((v) => { m.roughness = v[0]; });
      } else if (rest === 'extensions/KHR_materials_emissive_strength/emissiveStrength') {
        out.push((v) => { m.emissiveIntensity = v[0]; });
      } else {
        const tt = rest.match(/^(.*)\/extensions\/KHR_texture_transform\/(offset|scale|rotation)$/);
        if (tt && TEXTURE_SLOTS[tt[1]]) {
          for (const slot of TEXTURE_SLOTS[tt[1]]) {
            out.push((v) => {
              const tex = m[slot];
              if (!tex) return;
              if (tt[2] === 'offset') setTextureTransform(tex, v, null, undefined);
              else if (tt[2] === 'scale') setTextureTransform(tex, null, v, undefined);
              else setTextureTransform(tex, null, null, v[0]);
              m.userData.soaUV = m.userData.soaUV || {};
              m.userData.soaUV[tt[2]] = Array.from(v);
            });
          }
        }
      }
    }
  } else if (p[0] === 'nodes') {
    const objs = maps.nodes.get(Number(p[1])) || [];
    const rest = p.slice(2).join('/');
    for (const o of objs) {
      if (rest === 'extensions/KHR_node_visibility/visible') out.push((v) => { o.visible = v[0] !== 0; });
      else if (rest === 'translation') out.push((v) => o.position.fromArray(v));
      else if (rest === 'rotation') out.push((v) => o.quaternion.fromArray(v));
      else if (rest === 'scale') out.push((v) => o.scale.fromArray(v));
      else if (rest === 'weights') {
        out.push((v) => o.traverse((c) => {
          if (c.morphTargetInfluences) for (let i = 0; i < v.length; i++) c.morphTargetInfluences[i] = v[i];
        }));
      }
    }
  }
  return out;
}

function accessorArray(attr) {
  // BufferAttribute.getX denormalizes normalized integer accessors (the glTF rules)
  const n = attr.count, size = attr.itemSize, out = new Float32Array(n * size);
  for (let i = 0; i < n; i++) for (let c = 0; c < size; c++) out[i * size + c] = attr.getComponent(i, c);
  return out;
}

// The three.js objects of each glTF node and material (GLTFLoader's associations; a material can have
// clones, e.g. for skinning or vertex colours).
function buildMaps(gltf) {
  const parser = gltf.parser;
  const nodes = new Map(), materials = new Map();
  const add = (map, k, v) => { if (!map.has(k)) map.set(k, []); if (!map.get(k).includes(v)) map.get(k).push(v); };
  gltf.scene.traverse((o) => {
    const a = parser.associations.get(o);
    if (a && a.nodes !== undefined) add(nodes, a.nodes, o);
    const mats = o.material ? (Array.isArray(o.material) ? o.material : [o.material]) : [];
    for (const m of mats) {
      const am = parser.associations.get(m);
      if (am && am.materials !== undefined) add(materials, am.materials, m);
    }
  });
  return { nodes, materials };
}

// Loads URL (or an ArrayBuffer) and returns {gltf, json, maps, pointer: [per animation: channels]}.
export async function loadSoaGltf(source, onProgress) {
  const loader = new GLTFLoader();
  const gltf = typeof source === 'string'
    ? await loader.loadAsync(source, onProgress)
    : await loader.parseAsync(source, '');
  const json = gltf.parser.json;
  const maps = buildMaps(gltf);
  // static KHR_node_visibility
  (json.nodes || []).forEach((n, i) => {
    const vis = n.extensions && n.extensions.KHR_node_visibility;
    if (vis && vis.visible === false) for (const o of maps.nodes.get(i) || []) o.visible = false;
  });
  const pointer = [];
  for (let a = 0; a < (json.animations || []).length; a++) {
    const def = json.animations[a];
    const list = [];
    for (const ch of def.channels) {
      const ext = ch.target.extensions && ch.target.extensions.KHR_animation_pointer;
      if (ch.target.node !== undefined || !ext) continue;
      const smp = def.samplers[ch.sampler];
      const input = await gltf.parser.getDependency('accessor', smp.input);
      const output = await gltf.parser.getDependency('accessor', smp.output);
      const times = accessorArray(input);
      const values = accessorArray(output);
      const cubic = smp.interpolation === 'CUBICSPLINE';
      const size = values.length / times.length / (cubic ? 3 : 1);
      const pc = new PointerChannel(ext.pointer, times, values, size, smp.interpolation);
      pc.targets = resolvePointer(ext.pointer, maps);
      list.push(pc);
    }
    pointer.push(list);
  }
  return { gltf, json, maps, pointer };
}

// Writes animation `index`'s pointer channels at time t.
export function applyPointer(model, index, t) {
  for (const pc of model.pointer[index] || []) {
    const v = pc.evaluate(t);
    for (const f of pc.targets) f(v);
  }
}

// Animation layers evaluated like the game's AafBlendManager (docs/notes.md "Models and animation"): the
// first layer sets the values it keys, every later one blends over what is there with its weight
// (_CalcNotify::Handler: SetValues for the first slot, BlendValues(w / (sum + w)) for the next). A layer
// is a glTF animation (a THREE.AnimationClip from GLTFLoader) sampled with three.js' own interpolants
// (LINEAR, STEP, and GLTFLoader's CUBICSPLINE), so the values are the file's; only the layering is ours.
import * as THREE from 'three';

const _q0 = new THREE.Quaternion();
const _q1 = new THREE.Quaternion();

// One clip bound to a scene: per track, the property binding and an interpolant.
export class ClipSampler {
  constructor(clip, root) {
    this.clip = clip;
    this.tracks = [];
    for (const track of clip.tracks) {
      const binding = new THREE.PropertyBinding(root, track.name);
      binding.bind();
      if (!binding.targetObject) continue;  // a node the scene doesn't have
      const size = track.getValueSize();
      const result = new Float32Array(size);
      const interp = track.createInterpolant(result);
      this.tracks.push({ name: track.name, binding, interp, result, size,
        quat: track.ValueTypeName === 'quaternion', current: new Float32Array(size),
        discrete: track.getInterpolation() === THREE.InterpolateDiscrete });
    }
    this.names = new Set(this.tracks.map((t) => t.name));
  }

  // Writes the clip at time t (seconds) with weight w (1: overwrite) into the bound properties; tracks
  // named in `skip` are left alone (a layer above owns them).
  apply(t, w = 1, skip = null) {
    for (const tr of this.tracks) {
      if (skip && skip.has(tr.name)) continue;
      const v = tr.interp.evaluate(t);
      if (w >= 1) {
        tr.binding.setValue(v, 0);
        continue;
      }
      if (w <= 0) continue;
      tr.binding.getValue(tr.current, 0);
      if (tr.quat) {
        _q0.fromArray(tr.current);
        _q1.fromArray(v);
        _q0.slerp(_q1, w);
        _q0.toArray(tr.current);
      } else if (tr.discrete) {
        if (w >= 0.5) tr.current.set(v);
      } else {
        for (let i = 0; i < tr.size; i++) tr.current[i] += (v[i] - tr.current[i]) * w;
      }
      tr.binding.setValue(tr.current, 0);
    }
  }
}

// The rest pose of everything an animation may touch: every node's TRS and every mesh's morph weights,
// restored before the layers are applied (a property no layer keys stays at rest, as in the game, where
// the controllers only write what they animate).
export class RestPose {
  constructor(root) {
    this.items = [];
    root.traverse((o) => {
      this.items.push({ o, p: o.position.clone(), q: o.quaternion.clone(), s: o.scale.clone(), v: o.visible,
        m: o.morphTargetInfluences ? o.morphTargetInfluences.slice() : null });
    });
  }

  restore() {
    for (const it of this.items) {
      it.o.position.copy(it.p);
      it.o.quaternion.copy(it.q);
      it.o.scale.copy(it.s);
      if (it.m) for (let i = 0; i < it.m.length; i++) it.o.morphTargetInfluences[i] = it.m[i];
    }
  }
}

// A stack of layers: [{sampler, time, weight, overwrite}] applied bottom to top. `overwrite` layers
// (the game's facial and additive clips: StartOverwriteAnimation / StartAddAnimation, docs/home3d.md)
// replace what they key; the others are body slots blended like AafBlendManager.
export function applyLayers(rest, layers) {
  rest.restore();
  let sum = 0;
  for (const l of layers) {
    if (!l.sampler || l.weight <= 0) continue;
    if (l.overwrite) {
      l.sampler.apply(l.time, l.weight);
      continue;
    }
    if (sum === 0) l.sampler.apply(l.time, 1);
    else l.sampler.apply(l.time, l.weight / (sum + l.weight));
    sum += l.weight;
  }
}

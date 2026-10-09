// The animations' PRS constraints (SOA_aska_constraints, docs/notes.md "Animations (AAF) for tools"),
// evaluated live the way the game does after the keyframes (Aska::AafPRSConstraintController, 3.7.0):
//  - point, all axes (SetPoint @024217a8): the target's world position becomes
//    sum_i (w_i / sum w) * (ParentWorld_i * (localPosition_i + sourceOffset_i) + offset.xyz * offset.w);
//    with an axis mask (SetPointAxis @02421a00) only the masked components change;
//  - orient, all axes (SetOrient @02421d54): acc starts as identity; per source with the running weight
//    sum s >= 1e-6, acc = slerp(acc, normalize(WorldRotation_i) (x) Euler(offset), w_i / s); the target's
//    world matrix becomes R(acc) * S(its world scale) at its world position;
//    with an axis mask (SetOrientAxis @02422104) the target's world Euler angles (Rz Ry Rx) are replaced
//    per masked axis by offset + sum_i (w_i / sum w) * Euler_i;
//  - the target's local transform follows from its new world matrix (MakeTransformParamEx).
// Sources the game can't find (an authoring tool's pointer instead of a name) don't count.
// The core works in the game's space (model space: centimetres, left-handed, column vectors); the viewer
// converts the glTF nodes (mirrored in x, under the root that scales to metres and turns to +Z).
import * as THREE from 'three';

const _m = new THREE.Matrix4();
const _v = new THREE.Vector3();
const _q = new THREE.Quaternion();
const _s = new THREE.Vector3();

// Euler (radians) -> quaternion as Quaternion::CreateFromEuler(x, y, z): Rz * Ry * Rx (@02057cec).
export function quatFromEuler(x, y, z) {
  return new THREE.Quaternion().setFromEuler(new THREE.Euler(x, y, z, 'ZYX'));
}

// Point: sources [{parentWorld: Matrix4, local: Vector3, offset: Vector3, weight}], the constraint's
// offset [x, y, z, w], axes (bit 0 x, 1 y, 2 z), the target's world matrix. Returns the new world
// position, or null when the weights sum below 1e-6 (the game leaves the target alone).
export function evalPoint(sources, offset, axes, targetWorld) {
  let sum = 0;
  for (const s of sources) sum += s.weight;
  if (sum < 1e-6) return null;
  const out = new THREE.Vector3();
  for (const s of sources) {
    const p = _v.copy(s.local).add(s.offset).applyMatrix4(s.parentWorld);
    const k = (1 / sum) * s.weight;
    out.x += (offset[0] * offset[3] + p.x) * k;
    out.y += (offset[1] * offset[3] + p.y) * k;
    out.z += (offset[2] * offset[3] + p.z) * k;
  }
  if (axes !== 7 && axes !== undefined) {
    const cur = new THREE.Vector3().setFromMatrixPosition(targetWorld);
    if (!(axes & 1)) out.x = cur.x;
    if (!(axes & 2)) out.y = cur.y;
    if (!(axes & 4)) out.z = cur.z;
  }
  return out;
}

// Orient: sources [{world: Matrix4, weight}]; returns the target's new world matrix (or null).
export function evalOrient(sources, offset, axes, targetWorld) {
  const pos = new THREE.Vector3(), rot = new THREE.Quaternion(), scl = new THREE.Vector3();
  targetWorld.decompose(pos, rot, scl);
  if (axes === 7 || axes === undefined) {
    const off = quatFromEuler(offset[0], offset[1], offset[2]);
    const acc = new THREE.Quaternion();
    let sum = 0;
    for (const s of sources) {
      sum += s.weight;
      if (sum < 1e-6) continue;
      s.world.decompose(_v, _q, _s);
      _q.normalize().multiply(off);  // source (x) offset (Hamilton product, as the game's)
      acc.slerp(_q, s.weight / sum);
    }
    if (sum < 1e-6) return null;
    return new THREE.Matrix4().compose(pos, acc, scl);
  }
  // per axis, through Euler angles (Quaternion::CalcEuler: read as the inverse of CreateFromEuler)
  const sums = [0, 0, 0];
  for (const s of sources) for (let a = 0; a < 3; a++) if (axes & (1 << a)) sums[a] += s.weight;
  const e = new THREE.Euler().setFromQuaternion(rot, 'ZYX');
  const acc = [offset[0], offset[1], offset[2]];
  let any = false;
  for (const s of sources) {
    s.world.decompose(_v, _q, _s);
    const se = new THREE.Euler().setFromQuaternion(_q.normalize(), 'ZYX');
    const comp = [se.x, se.y, se.z];
    for (let a = 0; a < 3; a++) if ((axes & (1 << a)) && sums[a] > 0) { acc[a] += (1 / sums[a]) * comp[a] * s.weight; any = true; }
  }
  if (!any) return null;
  const ex = (axes & 1) ? acc[0] : e.x, ey = (axes & 2) ? acc[1] : e.y, ez = (axes & 4) ? acc[2] : e.z;
  return new THREE.Matrix4().compose(pos, quatFromEuler(ex, ey, ez), scl);
}

// The viewer's side: the definitions of each animation, the glTF nodes, the conversions.
export class Constraints {
  constructor(model) {
    this.model = model;
    const json = model.json;
    this.defs = (json.animations || []).map((a) => ((a.extensions && a.extensions.SOA_aska_constraints) || {}).constraints || []);
    this.node = (i) => (model.maps.nodes.get(i) || [])[0];
    // three world -> game model space: K = Mx * Root^-1 (Root: the converter's root node, cm -> m and -Z -> +Z)
    const rootIndex = (json.scenes[json.scene || 0].nodes || [])[0];
    this.root = this.node(rootIndex);
    this.mx = new THREE.Matrix4().makeScale(-1, 1, 1);
    this.applied = 0;
    this.skipped = 0;
  }

  K() {
    return new THREE.Matrix4().copy(this.mx).multiply(_m.copy(this.root.matrixWorld).invert());
  }

  // game world matrix of a three object: Wg = K * W3 * Mx
  gameWorld(o, K) { return new THREE.Matrix4().copy(K).multiply(o.matrixWorld).multiply(this.mx); }

  live(anim) {
    return (this.defs[anim] || []).filter((d) => d.sources.some((s) => s.node_index !== undefined && s.weight > 0));
  }

  apply(anim) {
    if (anim < 0 || !this.root) return;
    const list = this.defs[anim] || [];
    if (!list.length) return;
    const K = this.K(), Kinv = K.clone().invert();
    this.applied = 0;
    for (const d of list) {
      const target = this.node(d.target_index);
      if (!target) continue;
      const srcs = [];
      for (const s of d.sources) {
        const o = s.node_index !== undefined ? this.node(s.node_index) : null;
        if (!o) continue;  // not found by the game either: skipped
        if (d.mode === 'point') {
          const local = o.position.clone();
          local.x = -local.x;  // the glTF translation is mirrored in x
          local.multiplyScalar(1);  // (centimetres: the nodes below the root keep the game's units)
          const pw = o.parent ? this.gameWorld(o.parent, K) : new THREE.Matrix4();
          srcs.push({ parentWorld: pw, local, offset: new THREE.Vector3(...(s.offset || [0, 0, 0])), weight: s.weight });
        } else {
          srcs.push({ world: this.gameWorld(o, K), weight: s.weight });
        }
      }
      const tw = this.gameWorld(target, K);
      let newWorld = null;
      if (d.mode === 'point') {
        const p = evalPoint(srcs, d.offset, d.axes, tw);
        if (p) newWorld = tw.clone().setPosition(p);
      } else if (d.mode === 'orient') {
        newWorld = evalOrient(srcs, d.offset, d.axes, tw);
      }
      if (!newWorld) continue;
      // back to three: W3 = K^-1 * Wg * Mx; local = parentW3^-1 * W3 (the local scale kept)
      const w3 = new THREE.Matrix4().copy(Kinv).multiply(newWorld).multiply(this.mx);
      const local = new THREE.Matrix4().copy(target.parent.matrixWorld).invert().multiply(w3);
      const keep = target.scale.clone();
      local.decompose(target.position, target.quaternion, _s);
      target.scale.copy(keep);
      target.updateMatrixWorld(true);
      this.applied++;
    }
  }
}

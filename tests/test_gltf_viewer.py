"""The glTF viewer (tools/gltf-viewer/) in a headless browser, on a small glTF this test builds (no game
files): it loads without errors and draws; a KHR_animation_pointer track recolours the material; a
KHR_node_visibility track hides a node; a morph weights channel moves a vertex; a joint rotation
moves the skinned box; the SOA_aska_constraints point constraint moves its target onto its source
(and the orient / per-axis rules of constraints.js, on numbers worked out by hand); the SOA_aska_shader
path compiles a game-style shader pair (palette skinning through camSkin, the z = 2 z' - w output) and
draws its colour; the Home3D replay picks its rows and shows the line.

Needs playwright (requirements.txt), its headless Chromium in work/tools/ms-playwright and three.js in
work/tools/three-<version>/ (tools/gltf-viewer/fetch-deps.py --browser); skipped when they are missing.
"""
import base64
import importlib.util
import io
import json
import math
import os
import struct
import threading

import pytest

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BROWSERS = os.path.join(REPO, "work", "tools", "ms-playwright")


def _serve_module():
    spec = importlib.util.spec_from_file_location("gltf_viewer_serve", os.path.join(REPO, "tools", "gltf-viewer", "serve.py"))
    m = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m


def _requirements():
    try:
        import playwright.sync_api  # noqa: F401
    except ImportError:
        return "playwright isn't installed (requirements.txt)"
    serve = _serve_module()
    if not os.path.exists(os.path.join(REPO, "work", "tools", f"three-{serve.THREE_VERSION}", "package", "build", "three.module.js")):
        return "three.js isn't fetched (tools/gltf-viewer/fetch-deps.py)"
    if not os.path.isdir(BROWSERS) or not any(n.startswith("chromium") for n in os.listdir(BROWSERS)):
        return "no headless Chromium in work/tools/ms-playwright (tools/gltf-viewer/fetch-deps.py --browser)"
    return None


SKIP = _requirements()
pytestmark = pytest.mark.skipif(SKIP is not None, reason=SKIP or "")


# ---- the synthetic glTF ----
class Buf:
    def __init__(self):
        self.data = bytearray()
        self.views, self.accessors = [], []

    def add(self, fmt, values, type_, comp=5126, count=None, minmax=False, target=None):
        while len(self.data) % 4:
            self.data.append(0)
        off = len(self.data)
        raw = struct.pack("<" + fmt * len(values), *values)
        self.data += raw
        v = {"buffer": 0, "byteOffset": off, "byteLength": len(raw)}
        if target:
            v["target"] = target
        self.views.append(v)
        n = {"SCALAR": 1, "VEC2": 2, "VEC3": 3, "VEC4": 4}[type_]
        a = {"bufferView": len(self.views) - 1, "componentType": comp, "count": count or len(values) // n, "type": type_}
        if minmax:
            a["min"] = [min(values[i::n]) for i in range(n)]
            a["max"] = [max(values[i::n]) for i in range(n)]
        self.accessors.append(a)
        return len(self.accessors) - 1


def mat_root():
    # the converter's root: scale 0.01, turned 180 degrees about y (column-major 4x4)
    return [-0.01, 0, 0, 0, 0, 0.01, 0, 0, 0, 0, -0.01, 0, 0, 0, 0, 1]


def inv_root_translate(tx, ty, tz):
    # inverse of Root * T(tx, ty, tz) (Root = diag(-0.01, 0.01, -0.01)): T(-t) * diag(-100, 100, -100)
    return [-100, 0, 0, 0, 0, 100, 0, 0, 0, 0, -100, 0, -tx, -ty, -tz, 1]


VS = """#version 300 es
layout(location=0) in highp vec4 in_POSITION0;
layout(location=1) in highp vec4 in_BLENDINDICES0;
layout(location=2) in highp vec4 in_BLENDWEIGHT0;
uniform vec4 camSkin[6];
uniform mat4 cmWVS;
uniform vec4 cmWorld[3];
void main ()
{
  highp ivec4 i = ivec4(floor(in_BLENDINDICES0 * vec4(3.0, 3.0, 3.0, 3.0)));
  highp vec4 p = vec4(in_POSITION0.xyz, 1.0);
  highp vec4 r0 = in_BLENDWEIGHT0.xxxx * camSkin[i.x] + in_BLENDWEIGHT0.yyyy * camSkin[i.y];
  highp vec4 r1 = in_BLENDWEIGHT0.xxxx * camSkin[i.x + 1] + in_BLENDWEIGHT0.yyyy * camSkin[i.y + 1];
  highp vec4 r2 = in_BLENDWEIGHT0.xxxx * camSkin[i.x + 2] + in_BLENDWEIGHT0.yyyy * camSkin[i.y + 2];
  highp vec4 w = vec4(dot(r0, p), dot(r1, p), dot(r2, p), 1.0);
  w = vec4(dot(cmWorld[0], w), dot(cmWorld[1], w), dot(cmWorld[2], w), 1.0);
  gl_Position.x = dot(cmWVS[0], w);
  gl_Position.y = dot(cmWVS[1], w);
  highp float z = dot(cmWVS[2], w);
  highp float ww = dot(cmWVS[3], w);
  gl_Position.z = (-(ww) + (z * 2.0));
  gl_Position.w = ww;
}"""

FS = """#version 300 es
precision highp float;
layout(location=0) out highp vec4 SV_TARGET0;
uniform vec4 cvHDRTransform;
uniform vec4 eConstColor_Color_Color0;
void main ()
{
  SV_TARGET0.xyz = (eConstColor_Color_Color0.xyz * cvHDRTransform.yyy);
  SV_TARGET0.w = 1.0;
}"""


def build_gltf():
    b = Buf()
    # the box: x, z +-0.4 m, y 0..2 m (world, metres at bind); two joints at y = 0 and y = 1 m
    xs, ys, zs = (-0.4, 0.4), (0.0, 1.0, 2.0), (-0.4, 0.4)
    pos, joints, weights = [], [], []
    for y in ys:
        for x in xs:
            for z in zs:
                pos += [x, y, z]
                j = 0 if y < 0.5 else 1
                joints += [j, 0, 0, 0]
                weights += [1.0, 0.0, 0.0, 0.0]
    idx = []
    def quad(a, bb, c, d):
        idx.extend([a, bb, c, a, c, d])
    for layer in range(2):
        o = layer * 4
        n = o + 4
        # vertex order per layer: (x-,z-), (x-,z+), (x+,z-), (x+,z+); the four sides, both windings
        for (a, c) in ((0, 1), (1, 3), (3, 2), (2, 0)):
            quad(o + a, o + c, n + c, n + a)
            quad(o + a, n + a, n + c, o + c)
    normals = []
    for i in range(0, len(pos), 3):
        l = math.hypot(pos[i], pos[i + 2]) or 1
        normals += [pos[i] / l, 0.0, pos[i + 2] / l]
    a_pos = b.add("f", pos, "VEC3", minmax=True, target=34962)
    a_nrm = b.add("f", normals, "VEC3", target=34962)
    a_j = b.add("H", joints, "VEC4", comp=5123, target=34962)
    a_w = b.add("f", weights, "VEC4", target=34962)
    a_idx = b.add("H", idx, "SCALAR", comp=5123, target=34963)
    # the quad (node "Hidden", 1 m to the right): a morph target lifts it by 0.5 m
    qpos = [-20, -20, 0, 20, -20, 0, 20, 20, 0, -20, 20, 0]  # (centimetres: under the root)
    a_qpos = b.add("f", qpos, "VEC3", minmax=True, target=34962)
    a_qidx = b.add("H", [0, 1, 2, 0, 2, 3], "SCALAR", comp=5123, target=34963)
    a_qmorph = b.add("f", [0, 0.5, 0] * 4, "VEC3", minmax=True)
    ibm = b.add("f", inv_root_translate(0, 0, 0) + inv_root_translate(0, 100, 0), "SCALAR", count=2)
    b.accessors[ibm]["type"] = "MAT4"
    # animation 0: joint 1 turns 90 degrees about z over 1 s; the colour pointer (STEP: red, then green at
    # 0.5 s); the visibility pointer (STEP: hidden from 0.75 s); the morph weights (LINEAR 0 -> 1)
    t2 = b.add("f", [0.0, 1.0], "SCALAR", minmax=True)
    s45 = math.sin(math.pi / 4)
    rot = b.add("f", [0, 0, 0, 1, 0, 0, s45, s45], "VEC4")
    tcol = b.add("f", [0.0, 0.5], "SCALAR", minmax=True)
    col = b.add("f", [1, 0, 0, 1, 0, 1, 0, 1], "VEC4")
    tvis = b.add("f", [0.0, 0.75], "SCALAR", minmax=True)
    vis = b.add("B", [1, 0], "SCALAR", comp=5121)
    wts = b.add("f", [0.0, 1.0], "SCALAR")
    root = 0
    nodes = [
        {"name": "asf2gltf_root", "matrix": mat_root(), "children": [1, 4, 5, 6]},
        {"name": "Joint0", "children": [2]},
        {"name": "Joint1", "translation": [0, 100, 0]},
        {"name": "Box", "mesh": 0, "skin": 0},
        {"name": "Target", "translation": [0, 0, 0]},
        {"name": "Source", "translation": [-50, 30, 20]},
        {"name": "Hidden", "mesh": 1, "translation": [-100, 100, 0]},
    ]
    doc = {
        "asset": {"version": "2.0", "generator": "tests/test_gltf_viewer.py", "extras": {"source": "synthetic"}},
        "extensionsUsed": ["KHR_animation_pointer", "KHR_node_visibility", "SOA_aska_constraints", "SOA_aska_shader"],
        "scene": 0, "scenes": [{"nodes": [root, 3]}], "nodes": nodes,
        "meshes": [
            {"name": "box", "primitives": [{"attributes": {"POSITION": a_pos, "NORMAL": a_nrm, "JOINTS_0": a_j, "WEIGHTS_0": a_w},
                                            "indices": a_idx, "material": 0}]},
            {"name": "quad", "primitives": [{"attributes": {"POSITION": a_qpos}, "indices": a_qidx, "material": 1,
                                             "targets": [{"POSITION": a_qmorph}]}], "weights": [0.0],
             "extras": {"targetNames": ["lift"]}},
        ],
        "skins": [{"joints": [1, 2], "inverseBindMatrices": ibm}],
        "materials": [
            {"name": "red", "pbrMetallicRoughness": {"baseColorFactor": [1, 0, 0, 1], "metallicFactor": 0, "roughnessFactor": 1},
             "doubleSided": True,
             "extensions": {"SOA_aska_shader": {"textures": [], "passes": [{
                 "program": 1, "vertexShader": 0, "fragmentShader": 1, "state": {"blend": "blend 0", "cull": "cull 0", "depth": "depthwrite 1"},
                 "uniforms": {"camSkin": {"type": "vec4", "count": 6, "engine": "per draw"}, "cmWVS": {"type": "mat4", "engine": "per draw"},
                              "cmWorld": {"type": "vec4", "count": 3, "engine": "per draw", "captured": [[1, 0, 0, 0], [0, 1, 0, 0], [0, 0, 1, 0]]},
                              "cvHDRTransform": {"type": "vec4", "engine": "the scene", "captured": [[1, 1, 0, 1]]},
                              "eConstColor_Color_Color0": {"type": "vec4", "captured": [0, 0, 1, 1]}}}]}}},
            {"name": "blue", "pbrMetallicRoughness": {"baseColorFactor": [0, 0, 1, 1]}, "emissiveFactor": [0, 0, 1], "doubleSided": True},
        ],
        "animations": [
            {"name": "test anim", "samplers": [
                {"input": t2, "output": rot, "interpolation": "LINEAR"},
                {"input": tcol, "output": col, "interpolation": "STEP"},
                {"input": tvis, "output": vis, "interpolation": "STEP"},
                {"input": t2, "output": wts, "interpolation": "LINEAR"}],
             "channels": [
                {"sampler": 0, "target": {"node": 2, "path": "rotation"}},
                {"sampler": 1, "target": {"path": "pointer", "extensions": {"KHR_animation_pointer": {"pointer": "/materials/0/pbrMetallicRoughness/baseColorFactor"}}}},
                {"sampler": 2, "target": {"path": "pointer", "extensions": {"KHR_animation_pointer": {"pointer": "/nodes/6/extensions/KHR_node_visibility/visible"}}}},
                {"sampler": 3, "target": {"node": 6, "path": "weights"}}],
             "extras": {"role": "battle/idle", "fps": 60, "effects": [{"effect": "ef_test", "frames": [10], "node": "Joint1"}],
                        "sounds": [{"frame": 20, "kind": "character", "package": "Test", "cue": 1}]},
             "extensions": {"SOA_aska_constraints": {"constraints": [
                 {"target": "Target", "target_index": 4, "kind": "prs", "mode": "point", "axes": 7, "offset": [0, 0, 0, 1],
                  "sources": [{"node": "Source", "node_index": 5, "weight": 1.0}, {"weight": 0.0, "unresolved": "00000000"}]}]}}},
        ],
        "extensions": {"SOA_aska_shader": {"shaders": [{"stage": "vertex", "glsl": VS}, {"stage": "fragment", "glsl": FS}]}},
        "extras": {"soa_home3d": {"schema": "soa_home3d/1", "clips": {}, "camera": {"height": 170},
                                  "rows": [{"id": 1, "id_label": "home3d_teststay", "category": "stay", "motion": "test anim", "weight": 0, "blend_frame": 45},
                                           {"id": 2, "id_label": "home3d_testtalk01", "category": "talk", "motion": "test anim", "weight": 10,
                                            "blend_frame": 10, "text_ja": "こんにちは", "text_en": "Hello", "voice_id": "v_test"}]}},
    }
    doc["accessors"] = b.accessors
    doc["bufferViews"] = b.views
    doc["buffers"] = [{"byteLength": len(b.data), "uri": "data:application/octet-stream;base64," + base64.b64encode(bytes(b.data)).decode()}]
    return json.dumps(doc)


# ---- the browser ----
@pytest.fixture(scope="module")
def page():
    os.environ["PLAYWRIGHT_BROWSERS_PATH"] = BROWSERS
    from playwright.sync_api import sync_playwright
    serve = _serve_module()
    srv = serve.make_server(0)
    threading.Thread(target=srv.serve_forever, daemon=True).start()
    with sync_playwright() as p:
        browser = p.chromium.launch(args=["--use-angle=swiftshader", "--enable-unsafe-swiftshader", "--ignore-gpu-blocklist"])
        pg = browser.new_page(viewport={"width": 400, "height": 600})
        errors = []
        pg.on("pageerror", lambda e: errors.append(str(e)))
        pg.on("console", lambda m: errors.append(m.text) if m.type == "error" else None)
        pg.goto(f"http://127.0.0.1:{srv.server_address[1]}/tools/gltf-viewer/?ui=0")
        pg.wait_for_function("typeof window.soaLoadText === 'function'")
        pg.evaluate("t => window.soaLoadText(t, 'synthetic.gltf')", build_gltf())
        pg.wait_for_function("window.soaViewerReady || window.soaViewerError", timeout=60000)
        assert not pg.evaluate("window.soaViewerError"), pg.evaluate("window.soaViewerError")
        pg.errors = errors
        yield pg
        browser.close()
    srv.shutdown()


def shot(pg):
    from PIL import Image
    return Image.open(io.BytesIO(pg.locator("#view canvas").screenshot())).convert("RGB")


def count(img, pred):
    return sum(1 for p in img.get_flattened_data() if pred(p))


def test_draws_and_pointer_colour(page):
    page.evaluate("window.soaSetMaterialMode('pbr'); window.soaRenderAt(0, 0, 'front')")
    reds = count(shot(page), lambda p: p[0] > 50 and p[1] < 30 and p[2] < 30)
    assert reds > 500, "the box (red at frame 0) isn't drawn"
    page.evaluate("window.soaRenderAt(0, 36, null)")  # 0.6 s: the STEP pointer track made it green
    img = shot(page)
    assert count(img, lambda p: p[1] > 50 and p[0] < 30 and p[2] < 30) > 500, "KHR_animation_pointer baseColorFactor not applied"
    assert count(img, lambda p: p[0] > 50 and p[1] < 30 and p[2] < 30) < 50


def test_visibility_and_morph(page):
    page.evaluate("window.soaRenderAt(0, 30, null)")
    vis = page.evaluate("(() => { let o; window.soaViewer.model.gltf.scene.traverse(x => { if (x.name === 'Hidden') o = x; }); return o.visible; })()")
    w = page.evaluate("(() => { let w; window.soaViewer.model.gltf.scene.traverse(x => { if (x.morphTargetInfluences) w = x.morphTargetInfluences[0]; }); return w; })()")
    assert vis is True
    assert abs(w - 0.5) < 1e-3, f"morph weight at 0.5 s: {w}"
    page.evaluate("window.soaRenderAt(0, 50, null)")
    vis = page.evaluate("(() => { let o; window.soaViewer.model.gltf.scene.traverse(x => { if (x.name === 'Hidden') o = x; }); return o.visible; })()")
    assert vis is False, "KHR_node_visibility pointer track not applied"


def test_joint_rotation(page):
    page.evaluate("window.soaRenderAt(0, 60, null)")
    q = page.evaluate("(() => { let o; window.soaViewer.model.gltf.scene.traverse(x => { if (x.name === 'Joint1') o = x; }); return o.quaternion.toArray(); })()")
    assert abs(q[2] - math.sin(math.pi / 4)) < 1e-4 and abs(q[3] - math.cos(math.pi / 4)) < 1e-4


def test_point_constraint(page):
    page.evaluate("window.soaRenderAt(0, 10, null)")
    t, s = page.evaluate("""(() => { const n = {}; window.soaViewer.model.gltf.scene.traverse(x => { n[x.name] = x; });
        const a = n.Target.getWorldPosition(n.Target.position.clone()), b = n.Source.getWorldPosition(n.Source.position.clone());
        return [a.toArray(), b.toArray()]; })()""")
    for i in range(3):
        assert abs(t[i] - s[i]) < 1e-5, f"constraint target {t} != source {s}"


def test_constraint_rules(page):
    # the game-space rules on hand-made numbers: point = weighted (parentWorld * (local + offset)) + offset;
    # orient = slerp chain of source (x) Euler(offset); per-axis orient keeps the unmasked angles
    r = page.evaluate("""(async () => {
        const THREE = await import('three');
        const c = await import('/tools/gltf-viewer/constraints.js');
        const I = new THREE.Matrix4();
        const p = c.evalPoint([
            { parentWorld: new THREE.Matrix4().makeTranslation(10, 0, 0), local: new THREE.Vector3(1, 2, 3), offset: new THREE.Vector3(0, 0, 1), weight: 1 },
            { parentWorld: I, local: new THREE.Vector3(0, 0, 0), offset: new THREE.Vector3(0, 0, 0), weight: 3 }],
            [1, 0, 0, 2], 7, I);
        const pa = c.evalPoint([{ parentWorld: I, local: new THREE.Vector3(5, 6, 7), offset: new THREE.Vector3(), weight: 1 }],
            [0, 0, 0, 1], 2, new THREE.Matrix4().makeTranslation(1, 1, 1));
        const qz = new THREE.Quaternion().setFromAxisAngle(new THREE.Vector3(0, 0, 1), Math.PI / 2);
        const o = c.evalOrient([{ world: new THREE.Matrix4().makeRotationFromQuaternion(qz), weight: 1 }], [0, 0, 0, 1], 7, I);
        const q = new THREE.Quaternion().setFromRotationMatrix(o);
        const o2 = c.evalOrient([{ world: new THREE.Matrix4().makeRotationFromQuaternion(qz), weight: 1 }], [0.1, 0, 0, 1], 4,
            new THREE.Matrix4().makeRotationX(0.3));
        const e2 = new THREE.Euler().setFromRotationMatrix(o2, 'ZYX');
        return { p: p.toArray(), pa: pa.toArray(), q: q.toArray(), e2: [e2.x, e2.y, e2.z] };
    })()""")
    # (10 + 1, 2, 3 + 1) * 1/4 + (0, 0, 0) * 3/4, plus offset.xyz * w = (2, 0, 0)
    assert r["p"] == pytest.approx([11 / 4 + 2, 2 / 4, 4 / 4], abs=1e-6)
    assert r["pa"] == pytest.approx([1, 6, 1], abs=1e-6)  # only y (axes = 2)
    assert r["q"] == pytest.approx([0, 0, math.sin(math.pi / 4), math.cos(math.pi / 4)], abs=1e-6)
    assert r["e2"] == pytest.approx([0.3, 0, math.pi / 2], abs=1e-5)  # z replaced (offset.z 0 + 90 deg), x kept


def test_game_shader(page):
    desc = page.evaluate("window.soaSetMaterialMode('game')")
    assert "1 primitives with the game's shaders" in desc, desc
    page.evaluate("window.soaRenderAt(0, 0, 'front')")
    img = shot(page)
    blue = count(img, lambda p: p[2] > 200 and p[0] < 60 and p[1] < 60)
    assert blue > 500, "the game-style shader pair didn't draw its constant colour"
    page.evaluate("window.soaSetMaterialMode('pbr')")
    assert not [e for e in page.errors if "Shader Error" in e or "program not valid" in e], page.errors[:3]


def test_home(page):
    page.evaluate("window.soaHome('start')")
    r = page.evaluate("window.soaAdvance(5)")
    assert r["hud"].startswith("home: stay home3d_teststay"), r
    page.evaluate("window.soaHome('tap')")
    r = page.evaluate("window.soaAdvance(5)")
    assert "tap: home3d_testtalk01" in r["log"][-1], r
    line = page.evaluate("document.getElementById('line').textContent")
    assert "こんにちは" in line and "v_test" in line
    page.evaluate("window.soaHome('stop')")


def test_no_page_errors(page):
    assert not [e for e in page.errors if "error" in e.lower()], page.errors[:5]

#!/usr/bin/env -S sh -c 'exec "${0%/*}/../py" "$0" "$@"'
"""Replay one of the game's draws with the shaders an asf2gltf .glb carries (SOA_aska_shader) and
compare it with the game's own framebuffer: the proof that the extension holds what the game draws.

    .venv/bin/python tools/asf2gltf/shader_replay.py --glb MODEL.glb --raw RAWDIR --probe DUMP/probe_N \\
        --material NAME --meshset OBJECT_K [-o OUTDIR]

Inputs:
  --glb       asf2gltf ... --shaders DUMP: the material's SOA_aska_shader passes (GLSL, uniform map,
              state) and its slot textures;
  --raw       asf2gltf ... --raw-out RAWDIR: the meshset as the game's vertex shader reads it;
  --probe     a draw probed in the game (soa, SOA_GL_DRAW_DUMP=DUMP SOA_GL_DRAW_PROBE=<texture hash>):
              probe_N.txt (program, viewport), probe_N_uniforms.txt, probe_N_before/_after.f32 (the
              framebuffer around the draw), probe_N_unit<u>.bin (the bound textures).
Renders the draw twice into a float target that starts as the game's "before" frame:
  game-textures: every unit from the game's own textures (the shaders, uniforms and vertices proven);
  gltf-textures: the material's slots from the .glb, the material uniforms from its constants through
                 the extension's map, the engine's (lighting, shadow map, tables) as captured.
Compares each with the game's "after" frame on the pixels the game's draw changed; writes the images
and report.txt to OUTDIR. Needs moderngl (an EGL context: headless).
"""
import argparse
import io
import json
import os
import re
import struct
import sys

import moderngl
import numpy as np
from PIL import Image

GL_SRGB8_ALPHA8 = 0x8C43
DEPTH_FUNCS = {"0x201": "<", "0x202": "==", "0x203": "<=", "0x204": ">", "0x205": "!=", "0x206": ">=", "0x207": "1", "0x200": "0"}
FLOAT_FORMATS = {0x881A, 0x8814, 0x822D, 0x822E, 0x822F, 0x8230, 0x8C3A, 0x881B}


def load_glb(path):
    d = open(path, "rb").read()
    n = struct.unpack_from("<I", d, 12)[0]
    j = json.loads(d[20:20 + n])
    return j, d[20 + n + 8:]


def glb_image(j, binary, tex_index):
    img = j["images"][j["textures"][tex_index]["source"]]
    bv = j["bufferViews"][img["bufferView"]]
    o = bv.get("byteOffset", 0)
    return Image.open(io.BytesIO(binary[o:o + bv["byteLength"]])).convert("RGBA")


def read_uniforms(path):
    u = {}
    for line in open(path):
        m = re.match(r"(\S+) 0x([0-9a-f]+) = (.*)", line.strip())
        if m:
            u[m.group(1)] = (int(m.group(2), 16), [float(x) for x in m.group(3).split()])
    return u


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--glb", required=True)
    ap.add_argument("--raw", required=True)
    ap.add_argument("--probe", required=True, help="DUMP/probe_N (without a suffix)")
    ap.add_argument("--material", required=True, help="the glTF material's name, e.g. m_faceShape_0")
    ap.add_argument("--meshset", required=True, help="OBJECT_K, e.g. m_faceShape_0 (the --raw-out files)")
    ap.add_argument("-o", "--out", default=".")
    ap.add_argument("--front-face", choices=("cw", "ccw"), help="override the captured front face")
    ap.add_argument("--depth", help="override the captured depth function (<=, >=, ...)")
    a = ap.parse_args()
    os.makedirs(a.out, exist_ok=True)

    info = open(a.probe + ".txt").read()
    vp = [int(x) for x in re.search(r"viewport (\d+) (\d+) (\d+) (\d+)", info).groups()]
    program = int(re.search(r"program (\d+)", info).group(1))
    W, H = vp[2], vp[3]
    before = np.fromfile(a.probe + "_before.f32", dtype="<f4").reshape(H, W, 4)
    after = np.fromfile(a.probe + "_after.f32", dtype="<f4").reshape(H, W, 4)
    mask = np.any(before[:, :, :3] != after[:, :, :3], axis=2)
    uni = read_uniforms(a.probe + "_uniforms.txt")
    units = {}
    for line in open(a.probe + "_units.txt"):
        f = line.rstrip("\n").split("\t")
        w, h = (int(x) for x in f[2].split("x"))
        units[int(f[0])] = {"w": w, "h": h, "fmt": int(f[3], 16), "kind": f[4], "file": f"{a.probe}_unit{f[0]}.bin"}

    j, binary = load_glb(a.glb)
    mat = next(m for m in j["materials"] if m["name"] == a.material)
    ext = mat["extensions"]["SOA_aska_shader"]
    shaders = j["extensions"]["SOA_aska_shader"]["shaders"]
    p = next((p for p in ext["passes"] if p["program"] == program), None)
    if p is None:
        sys.exit(f"the material has no pass with program {program}: {[q['program'] for q in ext['passes']]}")
    vs, fs = shaders[p["vertexShader"]]["glsl"], shaders[p["fragmentShader"]]["glsl"]

    meta = json.load(open(os.path.join(a.raw, a.meshset + ".json")))
    nel = len(meta["elements"])
    verts = np.fromfile(os.path.join(a.raw, a.meshset + ".f32"), dtype="<f4").reshape(meta["vertices"], nel, 4)
    idx = np.fromfile(os.path.join(a.raw, a.meshset + ".u32"), dtype="<u4")
    usage_of = {"in_POSITION0": ("POSITION", 0), "in_NORMAL0": ("NORMAL", 0), "in_TEXCOORD0": ("TEXCOORD", 0),
                "in_BINORMAL0": ("TANGENT", 0), "in_BLENDINDICES0": ("JOINTS", 0), "in_BLENDWEIGHT0": ("WEIGHTS", 0),
                "in_COLOR0": ("COLOR", 0)}

    ctx = moderngl.create_standalone_context(backend="egl", require=330)
    prog = ctx.program(vertex_shader=vs, fragment_shader=fs)
    buffers = []
    for name in p["attributes"]:
        if name not in prog:
            continue
        usage, index = usage_of.get(name, (None, 0))
        col = next((i for i, e in enumerate(meta["elements"]) if e["usage"] == usage and e["index"] == index), None)
        data = verts[:, col, :] if col is not None else np.zeros((meta["vertices"], 4), "f4")
        buffers.append((ctx.buffer(np.ascontiguousarray(data, dtype="f4").tobytes()), "4f", name))
    ibo = ctx.buffer(idx.astype("u4").tobytes())
    vao = ctx.vertex_array(prog, buffers, index_buffer=ibo, index_element_size=4)

    def game_texture(u):
        t = units[u]
        if t["kind"] == "unread":  # (the EAC formats can't be read back: decoded from the file, like the glTF's)
            return gltf_texture(u)
        if t["kind"] == "rgba-f32":
            data = np.fromfile(t["file"], dtype="<f4")
            tex = ctx.texture((t["w"], t["h"]), 4, data.tobytes(), dtype="f4")
        else:
            data = np.fromfile(t["file"], dtype="u1")
            tex = ctx.texture((t["w"], t["h"]), 4, data.tobytes(), internal_format=GL_SRGB8_ALPHA8 if t["fmt"] == GL_SRGB8_ALPHA8 else None)
        return tex

    def gltf_texture(slot):
        e = ext["textures"][slot]
        im = glb_image(j, binary, e["index"])
        # the game samples top-down rows as uploaded (its v runs down the image): no flip
        return ctx.texture(im.size, 4, im.tobytes(), internal_format=GL_SRGB8_ALPHA8 if e.get("srgb") else None)

    def uniform_value(name, gltf):
        if gltf and name in p["uniforms"]:
            m = p["uniforms"][name]
            if "constant" in m:  # the value from the material's own constants, through the map
                c = m["constant"][0]
                for k in mat["extras"]["asf_constants"]:
                    if k["id"] == c["id"] and k["index"] == c["index"]:
                        return k["values"][c["element"]]
            if m.get("material") == "header +0x1b / 255":
                return None  # (the header byte isn't in the glTF material: the captured value)
        return None

    def render(gltf):
        st = p["state"]
        fbo = ctx.framebuffer(color_attachments=[ctx.texture((W, H), 4, dtype="f4")], depth_attachment=ctx.depth_texture((W, H)))
        fbo.use()
        func = a.depth or DEPTH_FUNCS.get(re.search(r"func (0x[0-9a-f]+)", st["depth"]).group(1) if "func" in st["depth"] else "0x203", "<=")
        fbo.clear(depth=0.0 if ">" in func else 1.0)  # (the game's depth is reversed: GEQUAL, cleared to 0)
        fbo.color_attachments[0].write(np.ascontiguousarray(before).tobytes())  # (the game's frame before the draw)
        textures = []
        for u in range(8):
            name = f"s{u}"
            if name not in prog or u not in units:
                continue
            slot_in_material = u < len(ext["textures"]) and "index" in ext["textures"][u]
            tex = gltf_texture(u) if gltf and slot_in_material else game_texture(u)
            float_tex = units[u]["kind"] == "rgba-f32"
            tex.filter = (moderngl.NEAREST, moderngl.NEAREST) if float_tex else (moderngl.LINEAR_MIPMAP_LINEAR, moderngl.LINEAR)
            if not float_tex:
                tex.build_mipmaps()
            tex.use(u)
            prog[name].value = u
            textures.append(tex)
        for name, (ty, vals) in uni.items():
            base = name.split("[")[0]
            if base not in prog or base.startswith("s") and base[1:].isdigit():
                continue
            v = uniform_value(base, gltf) or vals
            u_ = prog[base]
            if "[" in name:
                k = int(name[name.index("[") + 1:-1])
                arr = list(u_.value) if u_.array_length > 1 else None
                if arr is None:
                    continue
                arr[k] = tuple(v[:len(arr[k])]) if isinstance(arr[k], tuple) else v[0]
                u_.value = arr
            else:
                cur = u_.value
                if isinstance(cur, tuple):
                    if ty == 0x8B5C:  # mat4: the capture lists the GLSL matrix's columns
                        u_.write(np.array(v, "f4").tobytes())
                    else:
                        u_.value = tuple(v[:len(cur)])
                else:
                    u_.value = v[0]
        blend = st["blend"].split()
        if blend[1] == "1":
            ctx.enable(moderngl.BLEND)
            ctx.blend_func = (int(blend[2], 16), int(blend[3], 16))
        else:
            ctx.disable(moderngl.BLEND)
        cull = st["cull"].split()
        ctx.front_face = a.front_face or ("cw" if "front 0x900" in st["cull"] else "ccw")
        if cull[1] == "1":
            ctx.enable(moderngl.CULL_FACE)
            ctx.cull_face = "back" if cull[2] == "0x405" else "front"
        else:
            ctx.disable(moderngl.CULL_FACE)
        if "test 0" in st["depth"]:
            ctx.disable(moderngl.DEPTH_TEST)
        else:
            ctx.enable(moderngl.DEPTH_TEST)
            ctx.depth_func = func
        fbo.depth_mask = st["depth"].startswith("depthwrite 1")
        vao.render(moderngl.TRIANGLES)
        out = np.frombuffer(fbo.color_attachments[0].read(), dtype="f4").reshape(H, W, 4)
        for t in textures:
            t.release()
        return out

    report = [f"probe {a.probe}: program {program}, {mask.sum()} pixels changed by the game's draw"]
    imgs = {"game": after}
    for label, gltf in (("game-textures", False), ("gltf-textures", True)):
        try:
            out = render(gltf)
        except Exception as e:  # (reported, the other run still goes)
            report.append(f"{label}: failed: {e}")
            continue
        imgs[label] = out
        d = np.abs(out[:, :, :3] - after[:, :, :3])[mask]
        q = np.abs(np.round(np.clip(out[:, :, :3], 0, 1) * 255) - np.round(np.clip(after[:, :, :3], 0, 1) * 255))[mask]
        report.append(f"{label}: on those pixels: max |diff| {d.max():.6f}, mean {d.mean():.6f}; in 8-bit: "
                      f"{(q.max(axis=1) == 0).mean() * 100:.2f}% equal, {(q.max(axis=1) <= 1).mean() * 100:.2f}% within 1, "
                      f"{(q.max(axis=1) <= 4).mean() * 100:.2f}% within 4")
    ys, xs = np.nonzero(mask)
    x0, x1, y0, y1 = xs.min(), xs.max() + 1, ys.min(), ys.max() + 1
    strip = []
    for k in ("game", "game-textures", "gltf-textures"):
        if k in imgs:
            crop = np.clip(imgs[k][y0:y1, x0:x1, :3], 0, 1)[::-1]
            strip.append((np.round(crop * 255)).astype("u1"))
    if strip:
        Image.fromarray(np.concatenate(strip, axis=1)).save(os.path.join(a.out, "replay.png"))
        if "game-textures" in imgs:
            diff = np.abs(imgs["game-textures"][y0:y1, x0:x1, :3] - after[y0:y1, x0:x1, :3]).max(axis=2)[::-1]
            Image.fromarray(np.round(np.clip(diff * 20, 0, 1) * 255).astype("u1")).save(os.path.join(a.out, "diff-x20.png"))
    report.append("replay.png: the game's frame | replay with the game's textures | replay with the glTF's (crop of the draw)")
    open(os.path.join(a.out, "report.txt"), "w").write("\n".join(report) + "\n")
    print("\n".join(report))


if __name__ == "__main__":
    main()

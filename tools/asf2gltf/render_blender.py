"""Renders a .glb (asf2gltf's output) with Blender's glTF importer: the proof that the files load in
Blender and the pictures for the comparison with the game (docs/notes.md "glTF export").

    blender -b -P tools/asf2gltf/render_blender.py -- IN.glb OUT.png [--anim NAME] [--frame F]
            [--frames F0,F1,..] [--view front|side|back|three-quarter] [--size WxH] [--engine EEVEE|CYCLES|WORKBENCH]
            [--target NODE] [--center X,Y,Z] [--follow BONE] [--distance D] [--fov DEG] [--elevation DEG] [--hide NAME,..] [--log]
            [--clip END] [--no-cull]

Blender's glTF importer needs numpy: a distribution Blender that runs on the system Python (Ubuntu's
blender 4.0) finds it through PYTHONPATH=.venv/lib/python3.12/site-packages (the checkout's venv has
numpy, requirements.txt).

Without --anim: the rest pose. --face NAME layers a facial animation (held) under --anim. --anim plays the named glTF animation (Blender's action of that name) at --frame (scene frames at
the file's rate; glTF seconds * fps); --frames writes one picture per frame, OUT with _NNN before
its extension. The camera looks at the model's bounding box (or the node --target) from the --view
side, portrait by default (the game is a portrait game). --log prints what the importer made
(objects, armature bones, actions and their frame ranges, materials) for the report.
"""
import math
import os
import sys

import bpy
from mathutils import Vector


def args():
    a = sys.argv[sys.argv.index("--") + 1:] if "--" in sys.argv else []
    o = {"face": None, "anim": None, "frame": None, "frames": None, "view": "front", "size": (540, 960), "engine": "EEVEE",
         "target": None, "distance": None, "fov": 30.0, "elevation": 5.0, "log": False, "center": None, "hide": [], "follow": None, "no_cull": False, "clip": None}
    pos = []
    i = 0
    while i < len(a):
        k = a[i]
        if k == "--anim": o["anim"] = a[i + 1]; i += 2
        elif k == "--face": o["face"] = a[i + 1]; i += 2
        elif k == "--frame": o["frame"] = float(a[i + 1]); i += 2
        elif k == "--frames": o["frames"] = [float(x) for x in a[i + 1].split(",")]; i += 2
        elif k == "--view": o["view"] = a[i + 1]; i += 2
        elif k == "--size": w, h = a[i + 1].split("x"); o["size"] = (int(w), int(h)); i += 2
        elif k == "--engine": o["engine"] = a[i + 1]; i += 2
        elif k == "--target": o["target"] = a[i + 1]; i += 2
        elif k == "--distance": o["distance"] = float(a[i + 1]); i += 2
        elif k == "--fov": o["fov"] = float(a[i + 1]); i += 2
        elif k == "--elevation": o["elevation"] = float(a[i + 1]); i += 2
        elif k == "--log": o["log"] = True; i += 1
        elif k == "--center": o["center"] = [float(x) for x in a[i + 1].split(",")]; i += 2
        elif k == "--hide": o["hide"] = a[i + 1].split(","); i += 2
        elif k == "--no-cull": o["no_cull"] = True; i += 1
        elif k == "--follow": o["follow"] = a[i + 1]; i += 2
        elif k == "--clip": o["clip"] = float(a[i + 1]); i += 2
        else: pos.append(k); i += 1
    o["in"], o["out"] = pos[0], pos[1]
    return o


def bbox(objs):
    lo, hi = Vector((1e9, 1e9, 1e9)), Vector((-1e9, -1e9, -1e9))
    dg = bpy.context.evaluated_depsgraph_get()
    for ob in objs:
        if ob.type != "MESH":
            continue
        ev = ob.evaluated_get(dg)
        me = ev.to_mesh()
        for v in me.vertices:
            w = ev.matrix_world @ v.co
            lo = Vector(map(min, lo, w))
            hi = Vector(map(max, hi, w))
        ev.to_mesh_clear()
    return lo, hi


def main():
    o = args()
    bpy.ops.wm.read_factory_settings(use_empty=True)
    # the armature's rest = the glTF nodes' transforms (not a bind pose guessed from the inverse bind
    # matrices): a pose bone at identity is then the node's rest, e.g. Maria's Zoption keeps its 0.001 scale
    bpy.ops.import_scene.gltf(filepath=o["in"], guess_original_bind_pose=False)
    sc = bpy.context.scene
    if o["log"]:
        for ob in sc.objects:
            extra = ""
            if ob.type == "ARMATURE":
                extra = f" bones {len(ob.data.bones)}"
            print(f"LOG object {ob.name} {ob.type}{extra}")
        for act in bpy.data.actions:
            print(f"LOG action {act.name} frames {act.frame_range[0]:.1f}-{act.frame_range[1]:.1f} fcurves {len(act.fcurves)}")
        for m in bpy.data.materials:
            print(f"LOG material {m.name}")
    for ob in sc.objects:  # start from the rest pose: no action, every pose bone at identity
        if ob.animation_data:
            for tr in ob.animation_data.nla_tracks:
                tr.mute = True
            ob.animation_data.action = None
        if ob.pose:
            for pb in ob.pose.bones:
                pb.location = (0, 0, 0)
                pb.rotation_quaternion = (1, 0, 0, 0)
                pb.scale = (1, 1, 1)
    if o["anim"]:
        # the importer keeps each glTF animation as an action per object (named "<animation>_<object>",
        # truncated) on the objects' NLA tracks. The requested one plays on its track (held); --face NAME
        # is the active action, evaluated over it: the facial animation replaces the joints it keys, as
        # the game's expression layer does
        found = 0
        for ob in sc.objects:
            ad = ob.animation_data
            if not ad:
                continue
            face = None
            for tr in ad.nla_tracks:
                body = False
                for st in tr.strips:
                    if st.action and st.action.name.startswith(o["anim"]):
                        body = True
                        st.extrapolation = "HOLD"
                    if o["face"] and st.action and st.action.name.startswith(o["face"]):
                        face = st.action
                tr.mute = not body
                found += body
            ad.action = face
        if not found:
            raise SystemExit(f"no animation {o['anim']}: {sorted(set(a.name for a in bpy.data.actions))[:20]}")
    if o["no_cull"]:
        for m in bpy.data.materials:
            m.use_backface_culling = False
    for ob in sc.objects:  # --hide: objects whose name starts with one of these
        if any(ob.name.startswith(h) for h in o["hide"]):
            ob.hide_render = True
    frames = o["frames"] or [o["frame"] if o["frame"] is not None else sc.frame_current]
    res = sc.render
    res.resolution_x, res.resolution_y = o["size"]
    res.film_transparent = False
    try:
        res.engine = {"EEVEE": "BLENDER_EEVEE", "CYCLES": "CYCLES", "WORKBENCH": "BLENDER_WORKBENCH"}[o["engine"]]
    except Exception:
        res.engine = "BLENDER_WORKBENCH"
    if res.engine == "CYCLES":
        sc.cycles.samples = 16
    world = bpy.data.worlds.new("w") if not sc.world else sc.world
    sc.world = world
    world.use_nodes = True
    bg = world.node_tree.nodes.get("Background")
    # lighting after the game's home scene (cvLightContext0 / cvSHAmbContext of her draws, docs/notes.md
    # "Materials"): a strong key light from the camera's side and a bright, slightly blue ambient;
    # no filmic curve (the game's output is albedo * light, clipped)
    if bg:
        bg.inputs[0].default_value = (0.62, 0.64, 0.72, 1)
        bg.inputs[1].default_value = 1.0
    try:
        sc.view_settings.view_transform = "Standard"
        sc.view_settings.look = "None"
    except Exception:
        pass
    sun = bpy.data.objects.new("sun", bpy.data.lights.new("sun", "SUN"))
    sun.data.energy = 3.5
    sun.data.color = (1.0, 0.93, 1.0)
    sc.collection.objects.link(sun)
    cam = bpy.data.objects.new("cam", bpy.data.cameras.new("cam"))
    sc.collection.objects.link(cam)
    sc.camera = cam
    cam.data.angle = math.radians(o["fov"])
    if o["clip"]:  # the far plane in metres (Blender's default, 100 m, cuts a battle background's distant parts)
        cam.data.clip_end = o["clip"]
    for i, f in enumerate(frames):
        sc.frame_set(int(math.floor(f)), subframe=f - math.floor(f))
        follow = None
        if o["follow"]:  # a bone of the armature: the camera aims at it every frame
            for ob in sc.objects:
                if ob.type == "ARMATURE" and o["follow"] in ob.pose.bones:
                    follow = ob.matrix_world @ ob.pose.bones[o["follow"]].head
        if follow is not None:
            c = follow
            size = 1.0
        elif o["center"]:  # glTF metres (x, y up, z) -> Blender (x, -z, y)
            cx, cy, cz = o["center"]
            c = Vector((cx, -cz, cy))
            size = 1.0
        elif o["target"] and o["target"] in sc.objects:
            c = sc.objects[o["target"]].matrix_world.translation
            lo, hi = bbox([x for x in sc.objects])
            size = (hi - lo).length
        else:
            lo, hi = bbox([x for x in sc.objects if not x.hide_render])
            c = (lo + hi) / 2
            size = max(hi.z - lo.z, (hi.x - lo.x) * 1.8)
        d = o["distance"] or size / (2 * math.tan(cam.data.angle / 2)) * 1.15
        az = {"front": 0, "three-quarter": 35, "side": 90, "back": 180}[o["view"]]
        el = math.radians(o["elevation"])
        # glTF +Z (the model's front) is Blender -Y
        direction = Vector((math.sin(math.radians(az)) * math.cos(el), -math.cos(math.radians(az)) * math.cos(el), math.sin(el)))
        cam.location = c + direction * d
        cam.rotation_euler = (c - cam.location).to_track_quat("-Z", "Y").to_euler()
        # the key light shines from the camera's side, 25 degrees to the left and 30 above
        ld = Vector((math.sin(math.radians(az - 25)) * math.cos(el + 0.5), -math.cos(math.radians(az - 25)) * math.cos(el + 0.5), math.sin(el + 0.5)))
        sun.rotation_euler = (-ld).to_track_quat("-Z", "Y").to_euler()
        out = o["out"]
        if len(frames) > 1:
            base, ext = os.path.splitext(out)
            out = f"{base}_{i:03d}{ext}"
        res.filepath = out
        bpy.ops.render.render(write_still=True)
        print(f"LOG wrote {out} frame {f}")


main()

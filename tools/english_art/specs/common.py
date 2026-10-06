"""Helpers of the banner recipe scripts (tools/english_art/specs/*.py): each script writes the
standin-assets-en/recipes/<banner>.json of a family of Image/ banners that share a layout, so the
boxes are written once per family. Run a script with any python3 (no dependencies); then
build/tools/english_art/english-art --png DIR to review. docs/english.md section 8."""
import json, os
R = os.path.join(os.path.dirname(os.path.dirname(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))), "standin-assets-en", "recipes") + os.sep
def write(name, note, styles, labels, sources=None):
    r = {"note": note}
    if sources: r["sources"] = [f"Image/etc2/{s}.aif" for s in sources]
    else: r["source"] = f"Image/etc2/{name}.aif"
    r["styles"] = styles; r["labels"] = labels
    open(R + name + '.json', 'w').write(json.dumps(r, ensure_ascii=False, indent=1) + "\n")
def L(jp, en, box, style, cover=None, **kw):
    d = {"jp": jp, "text": en, "box": box, "style": style}
    if cover: d["cover"] = cover
    d.update(kw); return d

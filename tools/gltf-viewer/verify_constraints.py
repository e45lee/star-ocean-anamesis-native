#!/usr/bin/env -S sh -c 'exec "${0%/*}/../py" "$0" "$@"'
"""The proof that the viewer evaluates the PRS constraints as the game does: every evaluation the game
made in a live run (the selftest anim/aaf-constraint-dump, SOA_AAF_CONSTRAINT_DUMP=FILE.jsonl:
port/scripts/selftest_live.sh SOA OUT TMP anim/aaf-constraint --at battle) is recomputed by
tools/gltf-viewer/constraints.js (evalPoint / evalOrient, in a headless browser) from the same inputs
(the sources' world matrices, local positions, parents, the definition) and compared with the target's
world matrix the game computed.

    tools/gltf-viewer/verify_constraints.py FILE.jsonl [--tolerance 1e-3]

Prints per kind the number of evaluations, the largest difference (translation in centimetres for
point, matrix elements for orient) and FAIL lines; exit 1 on any difference above the tolerance. The
game computes in single precision, the viewer in double: the differences are rounding.
Needs playwright and its Chromium, and three.js (tools/gltf-viewer/fetch-deps.py --browser).
"""
import argparse
import importlib.util
import json
import os
import sys
import threading

REPO = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))

JS = """async (records) => {
  const THREE = await import('three');
  const c = await import('/tools/gltf-viewer/constraints.js');
  const M = (a) => new THREE.Matrix4().set(...a);  // rows, as the game stores them
  const out = [];
  for (const r of records) {
    const before = M(r.before), after = M(r.after);
    let got = null, err = null;
    if (r.kind.startsWith('point')) {
      const srcs = r.sources.filter((s) => s.world).map((s) => ({
        parentWorld: s.parent ? M(s.parent) : new THREE.Matrix4(), local: new THREE.Vector3(...s.local),
        offset: new THREE.Vector3(...s.offset), weight: s.weight }));
      const p = c.evalPoint(srcs, r.offset, r.kind === 'point' ? 7 : r.axes, before);
      if (p) {
        const want = new THREE.Vector3().setFromMatrixPosition(after);
        got = p.toArray();
        err = Math.max(...p.clone().sub(want).toArray().map(Math.abs));
      }
    } else {
      const srcs = r.sources.filter((s) => s.world).map((s) => ({ world: M(s.world), weight: s.weight }));
      const m = c.evalOrient(srcs, r.offset, r.kind === 'orient' ? 7 : r.axes, before);
      if (m) {
        got = m.toArray();
        err = Math.max(...m.elements.map((v, i) => Math.abs(v - after.elements[i])));
      }
    }
    out.push({ kind: r.kind, err, got });
  }
  return out;
}"""


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("dump")
    ap.add_argument("--tolerance", type=float, default=1e-3)
    a = ap.parse_args()
    records = [json.loads(l) for l in open(a.dump) if l.strip()]
    spec = importlib.util.spec_from_file_location("gltf_viewer_serve", os.path.join(REPO, "tools", "gltf-viewer", "serve.py"))
    serve = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(serve)
    srv = serve.make_server(0)
    threading.Thread(target=srv.serve_forever, daemon=True).start()
    os.environ.setdefault("PLAYWRIGHT_BROWSERS_PATH", os.path.join(REPO, "work", "tools", "ms-playwright"))
    from playwright.sync_api import sync_playwright
    with sync_playwright() as p:
        b = p.chromium.launch(args=["--use-angle=swiftshader", "--enable-unsafe-swiftshader"])
        pg = b.new_page()
        pg.goto(f"http://127.0.0.1:{srv.server_address[1]}/tools/gltf-viewer/?ui=0")
        pg.wait_for_function("typeof window.soaLoadText === 'function'")
        res = pg.evaluate(JS, records)
        b.close()
    srv.shutdown()
    stats, bad = {}, 0
    for i, r in enumerate(res):
        s = stats.setdefault(r["kind"], {"n": 0, "max": 0.0, "skipped": 0})
        if r["err"] is None:
            s["skipped"] += 1  # the weights sum below 1e-6: the game leaves the target alone
            continue
        s["n"] += 1
        s["max"] = max(s["max"], r["err"])
        if r["err"] > a.tolerance:
            bad += 1
            if bad <= 10:
                print(f"FAIL record {i} ({r['kind']}): difference {r['err']:.3g}")
    for k, s in sorted(stats.items()):
        print(f"{k}: {s['n']} evaluations, largest difference {s['max']:.3g}" + (f", {s['skipped']} with no weight" if s["skipped"] else ""))
    print("PASS" if not bad else f"FAIL: {bad} of {len(res)} above {a.tolerance}")
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())

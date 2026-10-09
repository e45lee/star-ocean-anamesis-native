#!/usr/bin/env -S sh -c 'exec "${0%/*}/../py" "$0" "$@"'
"""Serves the glTF viewer (tools/gltf-viewer/) on this machine only.

    tools/gltf-viewer/serve.py [--port 8642] [--models DIR]

Then open the printed URL (http://127.0.0.1:8642/); add ?model=URL to load one model at start, e.g.
?model=/work/models/seaside-maria/cp0303_b04a.glb. The page also opens a .glb by file picker or
drag-and-drop, and lists the models under --models (default work/models/) at /models.json.

Serves the checkout read-only from its root: the page, three.js from work/tools/three-<version>/
(tools/gltf-viewer/fetch-deps.py fetches it) and the .glb files under work/. Binds 127.0.0.1 only.
"""
import argparse
import functools
import http.server
import json
import os
import sys

REPO = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
THREE_VERSION = "0.186.1"  # tools/gltf-viewer/fetch-deps.py, index.html's import map


class Handler(http.server.SimpleHTTPRequestHandler):
    models_dir = os.path.join(REPO, "work", "models")
    extensions_map = {**http.server.SimpleHTTPRequestHandler.extensions_map,
                      ".js": "text/javascript", ".mjs": "text/javascript", ".glb": "model/gltf-binary",
                      ".gltf": "model/gltf+json", ".wasm": "application/wasm"}

    def do_GET(self):
        path = self.path.split("?", 1)[0]
        if path == "/":
            self.send_response(302)
            self.send_header("Location", "/tools/gltf-viewer/" + (("?" + self.path.split("?", 1)[1]) if "?" in self.path else ""))
            self.end_headers()
            return
        if path == "/models.json":
            body = json.dumps(self.list_models()).encode()
            self.send_response(200)
            self.send_header("Content-Type", "application/json")
            self.send_header("Content-Length", str(len(body)))
            self.end_headers()
            self.wfile.write(body)
            return
        super().do_GET()

    def list_models(self):
        out = []
        root = os.path.realpath(self.models_dir)
        for d, _, files in os.walk(root):
            for f in sorted(files):
                if f.endswith(".glb") or f.endswith(".gltf"):
                    full = os.path.join(d, f)
                    rel = os.path.relpath(full, os.path.realpath(REPO))
                    if rel.startswith(".."):  # outside the checkout (work/ is a link in a worktree)
                        rel = os.path.join("work", "models", os.path.relpath(full, root))
                    out.append({"url": "/" + rel.replace(os.sep, "/"), "name": os.path.relpath(full, root),
                                "bytes": os.path.getsize(full)})
        return sorted(out, key=lambda m: m["name"])

    def end_headers(self):
        self.send_header("Cache-Control", "no-cache")
        super().end_headers()

    def log_message(self, fmt, *args):
        if os.environ.get("SOA_VIEWER_LOG"):
            super().log_message(fmt, *args)


def make_server(port, models_dir=None):
    """The server (tests/test_gltf_viewer.py starts one on port 0)."""
    h = functools.partial(Handler, directory=REPO)
    if models_dir:
        Handler.models_dir = models_dir
    return http.server.ThreadingHTTPServer(("127.0.0.1", port), h)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--port", type=int, default=8642)
    ap.add_argument("--models", default=os.path.join(REPO, "work", "models"), help="the directory /models.json lists")
    a = ap.parse_args()
    if not os.path.exists(os.path.join(REPO, "work", "tools", f"three-{THREE_VERSION}", "package", "build", "three.module.js")):
        print(f"serve.py: three.js {THREE_VERSION} is missing: run tools/gltf-viewer/fetch-deps.py", file=sys.stderr)
        return 1
    srv = make_server(a.port, a.models)
    print(f"glTF viewer: http://127.0.0.1:{srv.server_address[1]}/  (Ctrl-C stops)")
    try:
        srv.serve_forever()
    except KeyboardInterrupt:
        pass
    return 0


if __name__ == "__main__":
    sys.exit(main())

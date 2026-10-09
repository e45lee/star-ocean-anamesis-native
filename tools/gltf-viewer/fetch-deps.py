#!/usr/bin/env -S sh -c 'exec "${0%/*}/../py" "$0" "$@"'
"""Fetches the glTF viewer's dependencies into work/tools/ (never into the repository or $HOME).

    tools/gltf-viewer/fetch-deps.py            three.js (pinned below) into work/tools/three-<version>/
    tools/gltf-viewer/fetch-deps.py --browser  also Playwright's headless Chromium into work/tools/ms-playwright/
                                               (for tests/test_gltf_viewer.py; playwright itself is in
                                               requirements.txt)

three.js comes from the npm registry's tarball, checked against the sha512 the registry publishes for
that version (recorded here), and unpacked to work/tools/three-<version>/package/. The viewer's
import map (tools/gltf-viewer/index.html) and tools/gltf-viewer/serve.py name the same version: change
all three together. There is no node/npm on the Linux side of this machine, hence a script rather
than a package.json.
"""
import argparse
import base64
import hashlib
import io
import os
import subprocess
import sys
import tarfile
import urllib.request

REPO = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(__file__)), "..", ".."))
THREE_VERSION = "0.186.1"
THREE_SHA512 = "blFeqb49wRCSGUGj7gtpfnSGHy2lwDk94RhUmS1c/hTby70kvChbWpkJ4Pm1390LqzzvTmzgXKHPEafJwCb8jA=="
THREE_URL = f"https://registry.npmjs.org/three/-/three-{THREE_VERSION}.tgz"
TOOLS = os.path.join(REPO, "work", "tools")
THREE_DIR = os.path.join(TOOLS, f"three-{THREE_VERSION}")
BROWSERS = os.path.join(TOOLS, "ms-playwright")


def three_present():
    return os.path.exists(os.path.join(THREE_DIR, "package", "build", "three.module.js"))


def fetch_three():
    if three_present():
        print(f"three.js {THREE_VERSION}: already in {THREE_DIR}")
        return
    print(f"three.js {THREE_VERSION}: {THREE_URL}")
    data = urllib.request.urlopen(THREE_URL, timeout=120).read()
    got = base64.b64encode(hashlib.sha512(data).digest()).decode()
    if got != THREE_SHA512:
        raise SystemExit(f"fetch-deps: three-{THREE_VERSION}.tgz: sha512 {got} is not the recorded {THREE_SHA512}")
    os.makedirs(THREE_DIR, exist_ok=True)
    with tarfile.open(fileobj=io.BytesIO(data), mode="r:gz") as t:
        t.extractall(THREE_DIR, filter="data")
    print(f"three.js {THREE_VERSION}: unpacked into {THREE_DIR}/package")


def fetch_browser():
    env = dict(os.environ, PLAYWRIGHT_BROWSERS_PATH=BROWSERS)
    print(f"Chromium (headless shell) for Playwright: into {BROWSERS}")
    subprocess.run([sys.executable, "-m", "playwright", "install", "chromium-headless-shell"], env=env, check=True)


def main():
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--browser", action="store_true", help="also Playwright's headless Chromium (the screenshot test)")
    a = ap.parse_args()
    fetch_three()
    if a.browser:
        fetch_browser()


if __name__ == "__main__":
    main()

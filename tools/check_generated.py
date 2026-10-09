#!/usr/bin/env python3
"""Fails when a generated source is stale against the 3.7.0 lib (T0 `generated`).

    tools/check_generated.py [--lib LIB]

Runs every generator of a committed file that is built into the programs, in `--check` mode, in
parallel, against the same lib:
  - tools/gen_addresses.py --check            port/src/native/*/gen/*_addresses.h (and kLibSha256)
  - tools/gen_fakeapi_tables.py --check       port/src/native/api/gen/fakeapi_tables.inc
  - tools/gen_params_instantiations.py --check port/src/native/params/gen/params_instantiations.inc
  - tools/gen_particles_instantiations.py --check port/src/native/particles/gen/particles_instantiations.inc
  - tools/gen_master_elements.py --check     port/src/native/master/gen/master_elements.h
  - tools/gen_infos.py --check                port/src/native/info/gen/info_classes.h and
                                              server/src/api/gen/client_infos.json
  - tools/gen_server_infos.py --check         server/src/api/gen/reply_types.{h,cpp} (from that JSON)
  - tools/api_wire.py --check                 port/src/native/api/gen/wire_table.inc and
                                              server/net/gen/wire_decode.inc
The lib: --lib, else work/libSOA-3.7.0.so, else lib/arm64-v8a/libSOA.so extracted from the 3.7.0 APK
in apk/ (a temporary copy). It must be the build the files are stamped with (genlib.KNOWN 3.7.0). A new
generator of a built file belongs in GENERATORS (and in port/src/native/README.md "Generated tables").
"""
import argparse
import os
import subprocess
import sys
import tempfile
import zipfile
from concurrent.futures import ThreadPoolExecutor

HERE = os.path.dirname(os.path.abspath(__file__))
sys.path.insert(0, HERE)
import genlib  # noqa: E402

REPO = genlib.REPO
APK = os.path.join(REPO, "apk", "STAR+OCEAN+-anamnesis-_3.7.0_APKPure.apk")
LIB_ENTRY = "lib/arm64-v8a/libSOA.so"  # (common/include/soa/install.h kLibEntry)

GENERATORS = [
    ["tools/gen_addresses.py", "--check"],
    ["tools/gen_fakeapi_tables.py", "--check", "port/src/native/api/gen/fakeapi_tables.inc"],
    ["tools/gen_params_instantiations.py", "--check", "port/src/native/params/gen/params_instantiations.inc"],
    ["tools/gen_particles_instantiations.py", "--check", "port/src/native/particles/gen/particles_instantiations.inc"],
    ["tools/gen_master_elements.py", "--check", "port/src/native/master/gen/master_elements.h"],
    ["tools/gen_infos.py", "--check", "port/src/native/info/gen/info_classes.h", "--check-json", "server/src/api/gen/client_infos.json"],
    ["tools/gen_server_infos.py", "--check"],
    ["tools/api_wire.py", "--check"],
]


def find_lib(tmp):
    if os.path.exists(genlib.LIB_370):
        return genlib.LIB_370
    with zipfile.ZipFile(APK) as z:
        out = os.path.join(tmp, "libSOA-3.7.0.so")
        with z.open(LIB_ENTRY) as src, open(out, "wb") as dst:
            while b := src.read(1 << 20):
                dst.write(b)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lib")
    a = ap.parse_args()
    with tempfile.TemporaryDirectory(prefix="soa-check-generated-") as tmp:
        lib = a.lib or find_lib(tmp)
        if genlib.version(lib) != "3.7.0":
            sys.exit(f"{lib}: not the 3.7.0 lib (sha256 {genlib.sha256(lib)}): the generated files are 3.7.0's")
        env = dict(os.environ, SOA_LIB=os.path.abspath(lib))
        py = sys.executable

        def run(cmd):
            argv = [py, os.path.join(REPO, cmd[0]), "--lib", lib, *cmd[1:]] if cmd[0] != "tools/api_wire.py" \
                else [py, os.path.join(REPO, cmd[0]), *cmd[1:]]  # (api_wire.py takes the lib from SOA_LIB)
            r = subprocess.run(argv, cwd=REPO, env=env, capture_output=True, text=True)
            return cmd, r

        bad = 0
        with ThreadPoolExecutor(len(GENERATORS)) as ex:
            for cmd, r in ex.map(run, GENERATORS):
                out = (r.stdout + r.stderr).strip()
                status = "ok" if r.returncode == 0 else "STALE / FAILED"
                print(f"{' '.join(cmd)}: {status}")
                if r.returncode:
                    bad += 1
                    print("    " + out.replace("\n", "\n    "))
        if bad:
            print(f"{bad} generated file set(s) stale: run the generator(s) without --check and commit the result")
            sys.exit(1)


if __name__ == "__main__":
    main()

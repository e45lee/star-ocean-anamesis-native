"""Repository-relative locations. Large/derived files live under work/ (git-ignored)."""
import pathlib

REPO = pathlib.Path(__file__).resolve().parent.parent
# Game build these tools target; derived data files are versioned with it.
GAME_VERSION = "3.8.0"
APK_DIR = REPO / "apk"
WORK = REPO / "work"
SAMPLES = REPO / "samples"


def xapk() -> pathlib.Path:
    found = sorted(APK_DIR.glob("*.xapk"))
    if not found:
        raise FileNotFoundError(f"no .xapk in {APK_DIR} (the APKPure download; README 'Game files')")
    return found[0]

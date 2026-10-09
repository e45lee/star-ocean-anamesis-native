#!/usr/bin/env -S sh -c 'exec "${0%/*}/py" "$0" "$@"'
"""Contact sheet: screenshots in a labelled grid, one PNG.

  tools/contact_sheet.py [options] ITEM... -o OUT.png

ITEM is an image (labelled with its file name, without the extension) or a section heading
"@Text": a heading starts a new row and is printed across the sheet. Images keep their order.

Options:
  -o OUT        the sheet to write (PNG)
  --cols N      tiles per row (default 6)
  --tile W      tile width in pixels (default 360; the height follows the first image's aspect,
                each image is fitted into the tile with its own aspect kept)
  --title TEXT  a title line at the top
  --max-width W refuse a sheet wider than W (default 4000): lower --tile or --cols instead

Needs Pillow (requirements.txt): .venv/bin/python tools/contact_sheet.py ...
Example (emulator/scripts/summer_demo.sh):
  tools/contact_sheet.py --title "Summer demo" "@1. Launch" OUT/0*.png "@2. Event" OUT/1*.png -o OUT/grid.png
"""
import argparse
import os
import sys

from PIL import Image, ImageDraw, ImageFont

BG = (24, 26, 32)
FG = (235, 235, 235)
HEAD_FG = (120, 200, 255)
FONT_PATHS = [
    "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
    "/usr/share/fonts/TTF/DejaVuSans.ttf",
    "/usr/share/fonts/dejavu/DejaVuSans.ttf",
]


# for text beyond ASCII (Japanese headings, file names): a font with CJK glyphs
CJK_FONT_PATHS = [
    "/usr/share/fonts/opentype/ipafont-gothic/ipag.ttf",
    "/usr/share/fonts/opentype/noto/NotoSansCJK-Regular.ttc",
    "/usr/share/fonts/noto-cjk/NotoSansCJK-Regular.ttc",
    "/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf",
]


def font(size, text=""):
    paths = FONT_PATHS
    if not text.isascii():
        paths = CJK_FONT_PATHS + FONT_PATHS
    for p in paths:
        if os.path.exists(p):
            return ImageFont.truetype(p, size)
    return ImageFont.load_default(size=size)


def text_height(f, s="Ag"):
    box = f.getbbox(s)
    return box[3] - box[1]


def fit_label(draw, f, text, width):
    """text, shortened with an ellipsis until it fits width."""
    if draw.textlength(text, font=f) <= width:
        return text
    while text and draw.textlength(text + "…", font=f) > width:
        text = text[:-1]
    return text + "…"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("items", nargs="+")
    ap.add_argument("-o", "--out", required=True)
    ap.add_argument("--cols", type=int, default=6)
    ap.add_argument("--tile", type=int, default=360)
    ap.add_argument("--title")
    ap.add_argument("--max-width", type=int, default=4000)
    a = ap.parse_args()

    # Rows: a heading row or a row of up to --cols images.
    rows, cur = [], []
    for it in a.items:
        if it.startswith("@"):
            if cur:
                rows.append(("images", cur))
                cur = []
            rows.append(("heading", it[1:]))
            continue
        if not os.path.isfile(it):
            sys.exit(f"contact_sheet: no such image: {it}")
        cur.append(it)
        if len(cur) == a.cols:
            rows.append(("images", cur))
            cur = []
    if cur:
        rows.append(("images", cur))
    images = [p for kind, r in rows if kind == "images" for p in r]
    if not images:
        sys.exit("contact_sheet: no images")

    pad, tw = 8, a.tile
    with Image.open(images[0]) as im0:
        th = round(tw * im0.height / im0.width)
    label_size, head_size, title_size = max(12, tw // 20), max(18, tw // 11), max(22, tw // 9)
    label_f, head_f, title_f = font(label_size), font(head_size), font(title_size)
    label_h, head_h, title_h = text_height(label_f) + 10, text_height(head_f) + 24, text_height(title_f) + 28
    width = pad + a.cols * (tw + pad)
    if width > a.max_width:
        sys.exit(f"contact_sheet: {width} px wide is over --max-width {a.max_width}: lower --tile or --cols")
    height = pad + (title_h if a.title else 0)
    for kind, _ in rows:
        height += head_h if kind == "heading" else th + label_h + pad

    sheet = Image.new("RGB", (width, height), BG)
    d = ImageDraw.Draw(sheet)
    y = pad
    if a.title:
        d.text((pad, y + 6), a.title, font=font(title_size, a.title), fill=FG)
        y += title_h
    for kind, r in rows:
        if kind == "heading":
            d.text((pad, y + 12), r, font=font(head_size, r), fill=HEAD_FG)
            d.line((pad, y + head_h - 4, width - pad, y + head_h - 4), fill=HEAD_FG, width=2)
            y += head_h
            continue
        for i, p in enumerate(r):
            x = pad + i * (tw + pad)
            with Image.open(p) as im:
                im = im.convert("RGB")
                im.thumbnail((tw, th), Image.LANCZOS)
                sheet.paste(im, (x + (tw - im.width) // 2, y + (th - im.height) // 2))
            name = os.path.splitext(os.path.basename(p))[0]
            f = font(label_size, name)
            d.text((x, y + th + 4), fit_label(d, f, name, tw), font=f, fill=FG)
        y += th + label_h + pad
    sheet.save(a.out, optimize=True)
    print(f"{a.out}: {len(images)} images, {width}x{height}")


if __name__ == "__main__":
    main()

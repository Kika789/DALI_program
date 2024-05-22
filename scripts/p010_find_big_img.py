#!/usr/bin/env python3

# print info about images in a directory tree

import os
from pathlib import Path
from PIL import Image

script_dir = Path(__file__).parent.resolve()
# print(script_dir)

def find_big_img(path: Path):
    for child in sorted(path.iterdir()):
        if child.is_dir():
            find_big_img(child)
        elif child.is_file() and child.suffix in ['.jpg', '.png']:
            # relative path
            rel_child = child.relative_to(script_dir.parent)
            # print(f'opening: {rel_child}:')
            with Image.open(child) as img:
                width, height = img.size
                # get size on disk
                size = os.path.getsize(child)
                size_mB = size / 1024 / 1024
                dpi = img.info.get('dpi')
                if dpi is None:
                    print(f"*** no dpi: {rel_child}")
                else:
                    dpi_x, dpi_y = dpi
                    print(f'dpi:({dpi_x:3.0f}, {dpi_y:3.0f}) {width:4d}x{height:4d} {int(size/1024):5_d}kB  {rel_child}: ')


if __name__ == '__main__':
    path = script_dir.parent
    find_big_img(path)


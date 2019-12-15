from PIL import Image
import sys
import os
from lz77 import compress


def convert_tile_row(im, x, y):
    row = [im.getpixel((x+i,y)) for i in range(8)]
    colors = list(sorted(set(row)))

    bg_color = 0
    fg_color = 15

    assert(len(colors) <= 2)
    if len(colors) == 1:
        fg_color = 0
        bg_color = colors[0]
    else:
        fg_color = colors[0]
        bg_color = colors[1]

    bits = ['1' if row[i]==fg_color else '0' for i in range(8)]
    return (int("".join(bits),2), bg_color+fg_color*16)

def convert_tile(im, x, y):
    row = [convert_tile_row(im, x, y+i) for i in range(8)]
    return ([i[0] for i in row], [i[1] for i in row])

def convert_screen(im):
    patterns = []
    colors = []
    for y in range(0, int(im.height/8)):
        for x in range(0, int(im.width/8)):
            pattern, color = convert_tile(im, x*8, y*8)
            patterns.extend(pattern)
            colors.extend(color)
    return patterns, colors

def print_static_table(data, name):
    print("static const uint8_t {0}[] = {{".format(name), end='')
    print(", ".join([str(row) for row in data]), end='')
    print("};")


if len(sys.argv) < 2:
    sys.exit("Missing arguments")

# convert screen
name = os.path.splitext(os.path.basename(sys.argv[1]))[0]
im = Image.open(sys.argv[1])
assert(im.size == (128, 128) or im.size == (256, 192))
assert(im.mode == "P")
patterns, colors = convert_screen(im)
sys.stderr.write("pat_{0}\n".format(name))
cpatterns = compress(patterns)
sys.stderr.write("col_{0}\n".format(name))
ccolors = compress(colors)

# export table
print_static_table(cpatterns, "pat_" + name)
print("")
print_static_table(ccolors, "col_" + name)

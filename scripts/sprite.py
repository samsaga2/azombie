from PIL import Image
import sys
import os

if len(sys.argv) < 2:
    sys.exit("Missing arguments")

name = os.path.splitext(os.path.basename(sys.argv[1]))[0]
im = Image.open(sys.argv[1])
assert(im.size == (8, 8))
assert(im.mode == "P")
pattern = []
for y in range(8):
    row = 0
    for x in range(8):
        pixel = im.getpixel((x, y))
        assert(pixel >= 0)
        assert(pixel <= 15)
        if pixel != 0:
            row = row + (1<<(7-x))
    pattern.append(row)
print("static const uint8_t pat_{0}[] = {{".format(name), end='')
print(", ".join([str(row) for row in pattern]), end='')
print("};")

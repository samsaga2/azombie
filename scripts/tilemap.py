from tmxreader import *
import sys
import os
import lz77

if len(sys.argv) < 2:
    sys.exit("Missing arguments")

name = os.path.splitext(os.path.basename(sys.argv[1]))[0]

parser = TileMapParser()
tilemap = parser.parse_decode(sys.argv[1])
layer_name = next(iter(tilemap.named_layers))
layer = tilemap.named_layers[layer_name]
assert(layer.width == 32)
assert(layer.height == 24)

tilemap = []
for y in range(0, layer.height):
    for x in range(0, layer.width):
        tile = layer.content2D[x][y] - 1
        tilemap.append(tile)
ctilemap = lz77.compress(tilemap)

print("static const uint8_t tilemap_{0}[] = {{".format(name), end='')
print(", ".join([str(tile) for tile in ctilemap]), end='')
print("};")


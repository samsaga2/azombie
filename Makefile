SDCC_FLAGS = -mz80 --no-std-crt0 --allow-unsafe-read --no-xinit-opt --opt-code-speed --max-allocs-per-node 100000 --nostdlib --code-loc 0x4020 --data-loc 0xc000 --code-size 0x2000 -I include --fomit-frame-pointer --std-c99 --disable-warning 85
SDCC = sdcc $(SDCC_FLAGS)
SPRITE = python3 scripts/sprite.py
SCREEN = python3 scripts/screen.py
TILEMAP = python3 scripts/tilemap.py

OBJS = crt0msx.32k.4000.rel main.rel msxhal.rel video.rel sprites.rel debug.rel input.rel player.rel uncompress.rel tiles.rel level_test.rel

all: clean bin/k5link sprites screens tilemaps out.rom run

sprites:
	$(SPRITE) resources/player_idle.png > pat_player_idle.h
	$(SPRITE) resources/player_right.png > pat_player_right.h
	$(SPRITE) resources/player_left.png > pat_player_left.h
	$(SPRITE) resources/player_stick_left.png > pat_player_stick_left.h
	$(SPRITE) resources/player_stick_right.png > pat_player_stick_right.h

screens:
	$(SCREEN) resources/tiles.png > scr_tiles.h

tilemaps:
	$(TILEMAP) resources/test.tmx > tilemap_test.h

out.rom: $(OBJS)
	./bin/k5link $(OBJS)

%.rel: src/%.c
	$(SDCC) -c $<

%.rel: src/%.s
	sdasz80 -o $@ $<

run:
	cat out.rom.areas.map
	openmsx -carta out.rom -script scripts/start.tcl

bin/k5link: util/k5link.cc
	-@mkdir -p bin
	g++ $< -o $@

clean:
	rm -f *.rel *.ihx *.lst *.map *.lk *.sym *.noi *.asm *.rom


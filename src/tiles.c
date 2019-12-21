#include "tiles.h"
#include "video.h"
#include "uncompress.h"
#include "bios.h"

#define NAME_TABLE    0x1800
#define PATTERN_TABLE 0x0000
#define COLOR_TABLE   0x2000

char offscreen[32 * 24];

void tiles_clear() {
    __asm
    xor a
    ld hl,#NAME_TABLE
    ld bc,#32*24
    call FILVRM
    __endasm;
}

void tiles_uncompress(char *patterns, char* colors) {
    // uncompress char pattern
    video_set_write_addr(PATTERN_TABLE);
    uncompress_to_vram(patterns);
    video_set_write_addr(PATTERN_TABLE+256*8);
    uncompress_to_vram(patterns);
    video_set_write_addr(PATTERN_TABLE+256*8*2);
    uncompress_to_vram(patterns);

    // uncompress char colors
    video_set_write_addr(COLOR_TABLE);
    uncompress_to_vram(colors);
    video_set_write_addr(COLOR_TABLE+256*8);
    uncompress_to_vram(colors);
    video_set_write_addr(COLOR_TABLE+256*8*2);
    uncompress_to_vram(colors);
}

char tiles_get(uint8_t x, uint8_t y) {
    __asm
    ld iy,#2
    add iy,sp
    ld l,1(iy)
    ld h,#0
    add hl,hl
    add hl,hl
    add hl,hl
    add hl,hl
    add hl,hl
    ld c,0(iy)
    ld b,#0
    add hl,bc
    ld bc,#_offscreen
    add hl,bc
    ld l,(hl)
    __endasm;
}

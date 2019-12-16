#include "video.h"
#include "bios.h"
#include "uncompress.h"

void video_init() {
    __asm
    /* color 15,0,0 */
    ld hl,#0xf3e9
    ld (hl),#15
    inc hl
    ld (hl),#0
    inc hl
    ld (hl),#0
    call CHGCLR
    /* screen 2 */
    call INIGRP
    /* disable key sound */
    xor a
    ld (0xf3db),a
    __endasm;
}

void video_set_write_addr(int addr) __z88dk_fastcall {
    __asm
    call SETWRT
    __endasm;
}

void video_uncompress_tiles(char *patterns, char* colors) {
    // uncompress char pattern
    video_set_write_addr(0x0000);
    uncompress_to_vram(patterns);
    video_set_write_addr(0x0000+256*8);
    uncompress_to_vram(patterns);
    video_set_write_addr(0x0000+256*8*2);
    uncompress_to_vram(patterns);

    // uncompress char colors
    video_set_write_addr(0x2000);
    uncompress_to_vram(colors);
    video_set_write_addr(0x2000+256*8);
    uncompress_to_vram(colors);
    video_set_write_addr(0x2000+256*8*2);
    uncompress_to_vram(colors);
}

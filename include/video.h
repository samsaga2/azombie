#pragma once

#include "msxhal.h"

USING_PAGE_A(video);

void video_init();

inline void video_sync() {
    __asm
    halt
    __endasm;
}

void video_set_write_addr(int addr) __z88dk_fastcall ;

void video_uncompress_tiles(char *patterns, char* colors);

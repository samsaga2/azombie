#pragma once

#include "msxhal.h"

USING_PAGE_A(video);

enum {
      SPR_ATTR_Y = 0,
      SPR_ATTR_X = 1,
      SPR_ATTR_PATTERN = 2,
      SPR_ATTR_COLOR = 3,
      NUM_SPR_ATTR
};

#define NUM_SPRITES 32

extern uint8_t spr_attributes[NUM_SPR_ATTR * NUM_SPRITES];

void video_init();
void video_spr_update();
void video_spr_define(uint8_t index, char *ptr, uint8_t size);

inline void video_sync() {
    __asm
    halt
    __endasm;
}

inline void video_set_write_addr(int addr) __z88dk_fastcall {
    __asm
    call SETWRT
    __endasm;
}

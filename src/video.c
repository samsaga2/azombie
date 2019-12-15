#include "video.h"
#include "bios.h"

#define SPRATR 0x1b00

uint8_t spr_attributes[NUM_SPR_ATTR * NUM_SPRITES];

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

void video_spr_clear() {
    __asm
    ld hl,#_spr_attributes
    ld de,#_spr_attributes+1
    ld bc,#4*32-1
    ldir
    __endasm;
}

void video_spr_update() {
    __asm
    ld hl,#_spr_attributes
    ld de,#SPRATR
    ld bc,#32*4
    jp LDIRVM
    __endasm;
}

void video_spr_define(uint8_t index, char *ptr, uint8_t size) {
    __asm
    ld iy,#2
    add iy,sp
    ld a,0(iy)
    call CALPAT
    ex de,hl

    ld l,1(iy)
    ld h,2(iy)
    ld b,#0
    ld c,3(iy)
    call LDIRVM
    __endasm;
}

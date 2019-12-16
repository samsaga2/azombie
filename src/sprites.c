#include "sprites.h"
#include "bios.h"

#define SPRATR 0x1b00

uint8_t spr_attributes[NUM_SPR_ATTR * NUM_SPRITES];

void spr_clear() {
    __asm
    ld hl,#_spr_attributes
    ld de,#_spr_attributes+1
    ld bc,#4*32-1
    ldir
    __endasm;
}

void spr_update() {
    __asm
    ld hl,#_spr_attributes
    ld de,#SPRATR
    ld bc,#32*4
    jp LDIRVM
    __endasm;
}

void spr_define(uint8_t index, char *ptr, uint8_t size) {
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

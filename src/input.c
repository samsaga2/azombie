#include "input.h"

#define KEYS 0xfbe5

char input_get_key_row(char row) __z88dk_fastcall {
  __asm
  ld de,#KEYS
  add hl,de
  ld a,(hl)
  ld l,a
  __endasm;
}

char input_chget() __z88dk_fastcall {
  __asm
  call CHGET
  ld l,a
  __endasm;
}

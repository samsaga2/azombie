#include "video.h"
#include "bios.h"

void video_init() {
  __asm
  /* color 0,0,15 */
  ld hl,#0xf3e9
  xor a
  ld (hl),a
  inc hl
  ld (hl),a
  inc hl
  ld (hl),a
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

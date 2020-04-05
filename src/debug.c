#include "debug.h"

void dbg_breakpoint() {
  __asm
  in a,(0x2e)
  __endasm;
}

void dbg_print(int i) {
  __asm
  ld a,#0x60
  out (0x2e),a
  ld a,h
  out (0x2f),a

  ld a,#0x60
  out (0x2e),a
  ld a,l
  out (0x2f),a

  ld a,#0x23
  out (0x2e),a
  ld a,#13
  out (0x2f),a
  __endasm;
}

#include "utils.h"
#include "debug.h"

static int seed1;
static int seed2;

void random_init() {
  seed1 = 1;
  seed2 = 1000;
}

// https://wikiti.brandonw.net/index.php?title=Z80_Routines:Math:Random
// Combined LFSR/LCG, 16-bit seeds
int random() {
  __asm
  ld hl,(#_seed1)
  ld b,h
  ld c,l
  add hl,hl
  add hl,hl
  inc l
  add hl,bc
  ld (#_seed1),hl
  ld hl,(#_seed2)
  add hl,hl
  sbc a,a
  and #0b00101101
  xor l
  ld l,a
  ld (#_seed2),hl
  add hl,bc
  __endasm;
}

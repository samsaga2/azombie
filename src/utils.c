#include "utils.h"

int rand_seed;

int random() {
  __asm
  ld hl,(#_rand_seed)
  ld c,l
  ld b,h
  add hl,hl
  add hl,bc
  add hl,hl
  add hl,bc
  add hl,hl
  add hl,bc
  add hl,hl
  add hl,hl
  add hl,hl
  add hl,hl
  add hl,bc
  inc h
  inc hl
  ld (#_rand_seed),hl
  __endasm;
}

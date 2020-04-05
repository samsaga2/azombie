#include "uncompress.h"

char buffer[512];

void uncompress_to_vram(char* src) __z88dk_fastcall {
  __asm
  // bc=token count
  ld c,(hl)
  inc hl
  ld b,(hl)
  inc hl

  // de=(buffer+256) & 0xff00 (256 bytes alignment)
  ld de,#_buffer
  inc d
  ld e,#0

  // uncompress loop
loop:
  // a=len
  ld a,(hl)
  inc hl
  or a
  jp z,nextchar

  push bc
  ld b,a                  // b=back reference len
  ld c,(hl)               // c=back reference offset
  inc hl
  push hl
  // hl=offset=(de-backoffset) mod 256
  ld a,e
  sub c
  ld l,a
  ld h,d

  // copy back reference
backref:
  ld a,(hl)
  inc l                   // hl=hl mod 256
  ld (de),a
  inc e                   // de=de mod 256
  out (0x98),a
  djnz backref
  pop hl
  pop bc

nextchar:
  // a=next char
  ld a,(hl)
  inc hl

  // write nextchar
  out (0x98),a
  ld (de),a
  inc e

  // end?
  dec bc
  ld a,c
  or b
  jp nz,loop
  __endasm;
}

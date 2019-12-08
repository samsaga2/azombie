#include "msxhal.h"
#include "video.h"

USING_PAGE_A(main);

void main() {
  msxhal_init();
  video_init();

  video_spr_define(0, 0, 32);
  spr_attributes[SPR_ATTR_Y] = 80;
  spr_attributes[SPR_ATTR_X] = 80;
  spr_attributes[SPR_ATTR_PATTERN] = 0;
  spr_attributes[SPR_ATTR_COLOR] = 15;
  video_spr_update();

  while(1) {
      spr_attributes[SPR_ATTR_X]++;
      video_spr_update();
      __asm
      halt
      __endasm;
  }
}

#include "msxhal.h"
#include "video.h"
#include "tiles.h"
#include "level.h"

USING_PAGE_A(main);

#include "../scr_tiles.h"

void main() {
  msxhal_init();
  video_init();

  FAST_LOAD_PAGE_C(level);
  level_init();
  /* FAST_LOAD_PAGE_C(player); */
  /* player_init(); */

  while(1) {
    /* player_update(); */
    video_sync();
  }
}

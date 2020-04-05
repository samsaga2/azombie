#include "msxhal.h"
#include "video.h"
#include "tiles.h"
#include "level.h"
#include "player.h"
#include "input.h"

USING_PAGE_A(main);

#include "../scr_tiles.h"

void random_level() {
  FAST_LOAD_PAGE_C(level);
  level_random();
  FAST_LOAD_PAGE_C(player);
  player_init();
  tiles_draw_offscreen();
}

void main() {
  msxhal_init();
  video_init();

  FAST_LOAD_PAGE_C(level);
  level_init();
  random_level();

  while(1) {
    char key = input_chget();
    if(key == ' ')
      random_level();
    player_update(key);
    video_sync();
    tiles_draw_offscreen();
  }
}

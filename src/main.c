#include "msxhal.h"
#include "video.h"
#include "tiles.h"
#include "level.h"
#include "player.h"
#include "input.h"
#include "utils.h"

USING_PAGE_A(main);

#include "../scr_tiles.h"

void random_level() {
  FAST_LOAD_PAGE_C(player);
  player_init();
  FAST_LOAD_PAGE_C(level);
  level_random();
  tiles_draw_offscreen();
}

void main() {
  msxhal_init();
  video_init();
  random_init();

  FAST_LOAD_PAGE_C(level);
  level_init();
  random_level();

  while(1) {
    char key = input_chget();
    int action = player_update(key);
    video_sync();
    tiles_draw_offscreen();

    if(key == ' ')
      action = ACTION_STAIRS_DOWN;

    switch(action) {
    case ACTION_STAIRS_DOWN:
      random_level();
      break;
    }
  }
}

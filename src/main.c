#include "msxhal.h"
#include "video.h"
#include "tiles.h"
#include "level.h"
#include "player.h"
#include "input.h"
#include "utils.h"
#include "pathfinding.h"
#include "debug.h"

USING_PAGE_A(main);

#include "../scr_tiles.h"

void random_level() {
  FAST_LOAD_PAGE_C(player);
  player_init();
  FAST_LOAD_PAGE_C(level);
  level_random();
  tiles_draw_offscreen();
}


void move_enemies() {
  // calcuate pathfinding destination
  FAST_LOAD_PAGE_C(pathfinding);
  int dest = (unsigned int)(player_pos - offscreen);
  pathfinding_calculate(dest);

  // move enemies
  char* o = offscreen;
  for(int pos = 0; pos < 32*24; pos++, o++) {
    if(*o == 148) {
      int next_pos = pathfinding_next_pos(pos);
      if(next_pos != dest && offscreen[next_pos] == 145) {
        *o = 145;
        offscreen[next_pos] = 255;
      } else {
        // TODO damage to player
      }
    }
  }

  // draw enemies
  o = offscreen;
  for(int pos = 0; pos < 32*24; pos++,o++) {
    if(*o == 255)
      *o = 148;
  }
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
    move_enemies();
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

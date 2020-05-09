#include "player.h"
#include "tiles.h"
#include "debug.h"

char player_sprite, player_bg;
char *player_pos;

void player_init() {
  player_pos = offscreen + 1 + 32;
  player_sprite = 0;
  player_bg = 145;
  *player_pos = 132;
}

int player_update(char key) {
  int dir = 0;

  // input keys
  switch(key) {
  case 0x1e:
    dir = -32;
    break;
  case 0x1f:
    dir = 32;
    break;
  case 0x1d:
    dir = -1;
    break;
  case 0x1c:
    dir = 1;
    break;
  }

  // do player movement
  int action = ACTION_NONE;
  char next_tile = *(player_pos + dir);
  switch(next_tile) {
  case 145:
  case 165:
  case 181:
    // no obstacle
    break;
  case 180:
    action = ACTION_STAIRS_DOWN;
    break;
  case 164:
    // open door
    *(player_pos + dir) = 165;
    return;
  case 167:
  case 168:
  case 169:
    // push vessel
    if(*(player_pos + dir + dir) == 145) {
      *(player_pos + dir) = 145;
      *(player_pos + dir + dir) = next_tile;
    } else
      // cannot push it
      dir = 0;
    break;
  default:
    // obstacle, no player movement this turn
    dir = 0;
    break;
  }

  // update player pos
  *player_pos = player_bg;
  player_pos += dir;
  player_bg = *player_pos;
  *player_pos = 132 + player_sprite;
  player_sprite = (player_sprite + 1) & 1;

  return action;
}

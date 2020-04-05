#include "player.h"
#include "tiles.h"
#include "debug.h"

char player_x, player_y, player_sprite, player_bg;

void player_init() {
  player_x = 1;
  player_y = 1;
  player_sprite = 0;
  player_bg = 145;
  offscreen[player_x + player_y * 32] = 132;
}

void player_update(char key) {
  char *o = offscreen + player_x + player_y * 32;

  switch(key) {
  case 0x1e:
    // move
    if(*(o-32) == 145 || *(o-32) == 165)
      player_y--;
    // open door
    if(*(o-32) == 164) {
      *(o-32) = 165;
      return;
    }
    break;
  case 0x1f:
    // move
    if(*(o+32) == 145 || *(o+32) == 165)
      player_y++;
    // open door
    if(*(o+32) == 164) {
      *(o+32) = 165;
      return;
    }
    break;
  case 0x1d:
    // move
    if(*(o-1) == 145 || *(o-1) == 164)
      player_x--;
    break;
  case 0x1c:
    // move
    if(*(o+1) == 145 || *(o+1) == 164)
      player_x++;
    break;
  }

  *o = player_bg;
  o = offscreen + player_x + player_y * 32;
  player_bg = *o;
  *o = 132 + player_sprite;
  player_sprite = (player_sprite + 1) & 1;
}

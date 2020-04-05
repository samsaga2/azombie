#include "level.h"
#include "tiles.h"
#include "utils.h"
#include "bios.h"
#include "../scr_tiles.h"
#include "debug.h"

#define MAX_DEPTH 5
#define ROOM_MARGIN 2
#define MIN_ROOM_SIZE ROOM_MARGIN*2

void level_set_borders() {
  // make space
  for(int i = 0; i < 32*24; i++)
    offscreen[i] = 145;

  // left & right
  for(int i = 32; i < 32*23; i+=32) {
    offscreen[i] = 144;
    offscreen[i+31] = 147;
  }

  // top & bottom
  for(int i = 0; i < 32; i++) {
    offscreen[i] = 129;
    offscreen[i+32*23] = 129;
  }

  // corners
  offscreen[0] = 128;
  offscreen[31] = 131;
  offscreen[23*32] = 160;
  offscreen[23*32+31] = 163;
}

void level_gen_hroom(int left, int top, int right, int bottom, int depth);

void level_gen_vroom(int left, int top, int right, int bottom, int depth) {
  if(depth == MAX_DEPTH)
    return;

  // room size
  int width = right - left;
  int height = bottom - top;
  if(width <= MIN_ROOM_SIZE || height <= MIN_ROOM_SIZE)
    return;
  
  // random split
  int mid = random()&31;
  while(mid >= height-ROOM_MARGIN*2) {
    mid -= height-ROOM_MARGIN*2;
  }
  mid += ROOM_MARGIN;

  char *o = offscreen + (top+(int)mid)*32 + left;
  for(int i = 0; i <= width; i++)
    *o++ = 127;

  // create more rooms
  level_gen_hroom(left, top, right, top+mid, depth+1);
  level_gen_hroom(left, top+mid+1, right, bottom, depth+1);

  // create a door
  char mid_door = mid/2+1;
  while(mid_door > width-MIN_ROOM_SIZE)
    mid_door -= width-MIN_ROOM_SIZE;
  int offset = (top+(int)mid)*32 + left + (int)mid_door;
  if(offscreen[offset-32] != 0 || offscreen[offset+32] != 0)
    offset++;
  offscreen[offset] = 'V';
}

void level_gen_hroom(int left, int top, int right, int bottom, int depth) {
  if(depth == MAX_DEPTH)
    return;

  // room size
  int width = right - left;
  int height = bottom - top;
  if(width <= MIN_ROOM_SIZE || height <= MIN_ROOM_SIZE)
    return;
  
  // random split
  int mid = random()&31;
  while(mid > width-ROOM_MARGIN*2) mid -= width-ROOM_MARGIN*2;
  mid += ROOM_MARGIN;

  char *o = offscreen + top*32 + left + (int)mid;
  for(int i = 0; i <= height; i++, o += 32)
    *o = 127;

  // create more rooms
  level_gen_vroom(left, top, left+mid, bottom, depth + 1);
  level_gen_vroom(left+mid+1, top, right, bottom, depth + 1);

  // create a door
  char mid_door = mid/2+1;
  while(mid_door > height-MIN_ROOM_SIZE)
    mid_door -= height-MIN_ROOM_SIZE;
  int offset = top*32 + left + (int)mid + 32*(int)mid_door;
  if(offscreen[offset-1] != 0 || offscreen[offset+1] != 0)
    offset+=32;
  offscreen[offset] = 'H';
}

void level_obstructed_doors() {
  char *o = offscreen;
  for(int i = 0; i < 32*24; i++, o++) {
    // obstructed h door
    if(*o == 'H' && *(o-32) != 0 && *(o+32) != 0) {
      if(*(o-32-1) == 145 && *(o-32+1) == 145) {
        *o = 127;
        *(o-32) = 'H';
      } else {
        *o = 127;
        *(o+32) = 'H';
      }
    }

    // obstructed v door
    if(*o == 'V' && *(o-1) != 0 && *(o+1) != 0) {
      if(*(o-32-1) == 145 && *(o+32-1) == 145) {
        *o = 127;
        *(o-1) = 'V';
      } else {
        *o = 127;
        *(o+1) = 'V';
      }
    }
  }
}

void level_decorate() {
  char l, r, t, b;
  char *o = offscreen;
  for(int i = 0; i < 32*24; i++, o++) {
    switch(*o) {
    case 'V':
      // vertical door horizontal split
      *o = 164;
      break;
    case 'H':
      // horizontal door vertical split
      *o = 145;
      break;
    case 144:
      // left vertical + horizontal
      if(*(o+1) != 145)
        *o = 192;
      break;
    case 147:
      // right vertical + horizontal
      if(*(o-1) != 145)
        *o = 193;
      break;
    case 127:
      l = *(o-1) != 145;
      r = *(o+1) != 145;
      t = *(o-32) != 145;
      b = *(o+32) != 145;
      if(l && r && !t && !b)
        // horizontal wall
        *o = 129;
      else if(t && b && !l && !r)
        // vertical wall
        *o = 144;
      else if(r && b)
        // right-bottom turn
        *o = 192;
      else if(l && b)
        // left-bottom turn
        *o = 144;
      else if(l && r)
        // continue horizontal wall
        *o = 129;
      else if(t || b)
        // continue vertical wall
        *o = 144;

      // horizontal door gap
      if(*o == 144) {
        if(*(o-32) == 145)
          *o = 179;
        else if(*(o+32) == 'H')
          *o = 177;
      }

      break;
    }
  }
}

void level_init() {
  random();
  random();
  random();
  random();
  tiles_uncompress(pat_tiles, col_tiles);
  level_set_borders();
  level_gen_vroom(1, 1, 30, 22, 0);
  level_obstructed_doors();
  level_decorate();
  tiles_draw_offscreen();
}

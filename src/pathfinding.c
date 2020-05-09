#include "pathfinding.h"
#include "tiles.h"

unsigned char distance[32 * 24];

#define NOCALC 0
#define SOLID 255

void pathfinding_clear() {
  for(int i = 0; i < 32*24; i++)
    distance[i] = offscreen[i] == 145 ? NOCALC : SOLID;
}

void pathfinding_iterate(char* curr_dist, unsigned char len) {
  *curr_dist = len;

  if(len == 255)
    return;
  len++;

  if(*(curr_dist-1) == NOCALC)
    pathfinding_iterate(curr_dist-1, len);
  if(*(curr_dist+1) == NOCALC)
    pathfinding_iterate(curr_dist+1, len);
  if(*(curr_dist-32) == NOCALC)
    pathfinding_iterate(curr_dist-32, len);
  if(*(curr_dist+32) == NOCALC)
    pathfinding_iterate(curr_dist+32, len);
}

void pathfinding_clear_no_calculated() {
  char *d = distance;
  for(int i = 0; i < 32*24; i++, d++)
    if(*d == NOCALC)
      *d = SOLID;
}

void pathfinding_calculate(int pos) {
  pathfinding_clear();
  pathfinding_iterate(distance + pos, 1);
  pathfinding_clear_no_calculated();
}

int pathfinding_next_pos(int pos) {
  unsigned char l = distance[pos-1];
  unsigned char r = distance[pos+1];
  unsigned char t = distance[pos-32];
  unsigned char b = distance[pos+32];

  if(l != SOLID && l < r && l < b && l < t)
    return pos-1;
  if(r != SOLID && r < l && r < b && r < t)
    return pos+1;
  if(t != SOLID && t < b)
    return pos-32;
  if(b != SOLID)
    return pos+32;
  return pos;
}

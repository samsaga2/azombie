#pragma once

#include "msxhal.h"

USING_PAGE_A(tiles);

extern char offscreen[32 * 24];

void tiles_uncompress(char *patterns, char* colors);

char tiles_get(uint8_t x, uint8_t y);

void tiles_draw_offscreen();

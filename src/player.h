#pragma once

#include "msxhal.h"

USING_PAGE_C(player);

extern char *player_pos;
extern char player_bg;

enum { ACTION_NONE, ACTION_STAIRS_DOWN };

void player_init();
int player_update(char key);

#pragma once

#include "msxhal.h"

USING_PAGE_C(pathfinding);

void pathfinding_calculate(int pos);

int pathfinding_next_pos(int pos);

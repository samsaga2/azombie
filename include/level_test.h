#pragma once

#include "msxhal.h"

USING_PAGE_C(level_test);

void level_test_init();

char level_get(uint8_t x, uint8_t y);

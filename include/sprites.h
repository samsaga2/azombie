#pragma once

#include "msxhal.h"

USING_PAGE_A(sprites);

enum {
      SPR_ATTR_Y = 0,
      SPR_ATTR_X = 1,
      SPR_ATTR_PATTERN = 2,
      SPR_ATTR_COLOR = 3,
      NUM_SPR_ATTR
};

#define NUM_SPRITES 32

extern uint8_t spr_attributes[NUM_SPR_ATTR * NUM_SPRITES];

void spr_update();
void spr_define(uint8_t index, char *ptr, uint8_t size);

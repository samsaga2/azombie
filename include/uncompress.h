#pragma once

#include "msxhal.h"

USING_PAGE_A(uncompress);

void uncompress_to_vram(char *src) __z88dk_fastcall;

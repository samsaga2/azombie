#pragma once

#include "msxhal.h"

USING_PAGE_A(input);

/* KEY MATRIX:

  bit  7     6     5     4     3     2     1     0
  ----------------------------------------------------
  0   7 &    6 ^   5 %   4 $   3 #   2 @   1 !   0 )
  1   ; :    ] }   [ {   \ |   = +   - _   9 (   8 *
  2   B      A     acent / ?   . >   , <   `     ' "
  3   J      I     H     G     F     E     D     C
  4   R      Q     P     O     N     M     L     K
  5   Z      Y     X     W     V     U     T     S
  6   F3     F2    F1    CODE  CAPS  GRAPH CTRL  SHIFT
  7   RET    SEL   BS    STOP  TAB   ESC   F5    F4
  8   Right  Down  Up    Left  DEL   INS   HOME  SPACE
  9   NUM4   NUM3  NUM2  NUM1  NUM0  NUM/  NUM+  NUM*
  10  NUM.   NUM,  NUM-  NUM9  NUM8  NUM7  NUM6  NUM5
*/

char input_get_key_row(char row) __z88dk_fastcall;

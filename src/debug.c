#include "debug.h"

void dbg_breakpoint() {
    __asm
    in a,(0x2e)
    __endasm;
}

#include "level_test.h"
#include "../tilemap_test.h"
#include "uncompress.h"
#include "video.h"
#include "bios.h"
#include "tiles.h"

void level_test_init() {
    video_set_write_addr(0x1800);
    uncompress_to_vram(tilemap_test);

    // copy screen to ram
    __asm
    ld bc,#32*24
    ld de,#_offscreen
    ld hl,#0x1800
    call LDIRMV
    __endasm;
}

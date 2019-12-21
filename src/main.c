#include "msxhal.h"
#include "video.h"
#include "player.h"
#include "sprites.h"
#include "tiles.h"
#include "level_test.h"

USING_PAGE_A(main);

#include "../scr_tiles.h"

void main() {
    msxhal_init();
    video_init();

    tiles_clear();
    tiles_uncompress(pat_tiles, col_tiles);

    FAST_LOAD_PAGE_C(level_test);
    level_test_init();
    FAST_LOAD_PAGE_C(player);
    player_init();

    while(1) {
        player_update();
        spr_update();
        video_sync();
    }
}

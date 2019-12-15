#include "msxhal.h"
#include "video.h"
#include "player.h"

USING_PAGE_A(main);

#include "../scr_tiles.h"

void main() {
    msxhal_init();
    video_init();

    video_uncompress_tiles(pat_tiles, col_tiles);

    FAST_LOAD_PAGE_C(player);
    player_init();

    while(1) {
        player_update();
        video_spr_update();
        video_sync();
    }
}

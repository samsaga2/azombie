#include "player.h"
#include "input.h"
#include "sprites.h"
#include "tiles.h"
#include "debug.h"

#include "../pat_player_idle.h"
#include "../pat_player_right.h"
#include "../pat_player_left.h"
#include "../pat_player_stick_right.h"
#include "../pat_player_stick_left.h"

enum {
      STATE_IDLE,
      STATE_RIGHT,
      STATE_LEFT,
      STATE_STICK_RIGHT,
      STATE_STICK_LEFT
};

char state;

unsigned int x, y;
int speed_x, speed_y;

void player_init() {
    // init player
    x = 80 << 8;
    y = 80 << 8;
    speed_x = 0;
    speed_y = 0;


    // setup player sprite
    spr_define(0, pat_player_idle, 8);
    spr_attributes[SPR_ATTR_Y] = x >> 8;
    spr_attributes[SPR_ATTR_X] = y >> 8;
    spr_attributes[SPR_ATTR_PATTERN] = 0;
    spr_attributes[SPR_ATTR_COLOR] = 14;
    spr_update();
    state = STATE_IDLE;
}

void player_update() {
    char keys_row = input_get_key_row(8);

    // move x
    if((keys_row & (1<<7)) == 0) {
        if(speed_x < 1024)
            speed_x += 256;
    } else if((keys_row & (1<<4)) == 0) {
        if(speed_x > -1024)
            speed_x -= 256;
    } else if(speed_x > 0)
        speed_x -= 128;
    else if(speed_x < 0)
        speed_x += 128;

    // update y
    char tl_y = tiles_get(x >> 8 >> 3, ((y >> 8) - 1) >> 3);
    char tr_y = tiles_get(((x >> 8) + 7) >> 3, ((y >> 8) - 1) >> 3);
    char bl_y = tiles_get(x >> 8 >> 3, ((y >> 8) + 8) >> 3);
    char br_y = tiles_get(((x >> 8) + 7) >> 3, ((y >> 8) + 8) >> 3);

    if(bl_y != 0 || br_y != 0) {
        y = ((y>>8) & (255-7)) << 8;

        if((keys_row & (1<<5)) == 0)
            speed_y =- 900;
        else
            speed_y = 0;
    } else if(speed_y < 1024) {
        if((keys_row & (1<<7)) == 0) {
            char br_x = tiles_get(((x >> 8) + 11) >> 3, ((y >> 8) + 7) >> 3);
            if(br_x != 0) {
                speed_y += 32;
                if(state != STATE_STICK_RIGHT) {
                    state = STATE_STICK_RIGHT;
                    spr_define(0, pat_player_stick_right, 8);
                }
            } else
                speed_y += 128;
        } else if((keys_row & (1<<4)) == 0) {
            char bl_x = tiles_get(((x >> 8) - 4) >> 3, ((y >> 8) + 7) >> 3);
            if(bl_x != 0) {
                speed_y += 32;
                if(state != STATE_STICK_LEFT) {
                    state = STATE_STICK_LEFT;
                    spr_define(0, pat_player_stick_left, 8);
                }
            } else
                speed_y += 128;
        } else
            speed_y += 128;
    }

    if(speed_y < 0 && (tl_y != 0 || tr_y != 0)) {
        y = (((y>>8) + 4) & (255-7)) << 8;
        speed_y = 0;
    } else
        y += speed_y;

    spr_attributes[SPR_ATTR_Y] = (y>>8) - 1;

    // update x
    if(speed_x != 0) {
        x += speed_x;
        char tl_x = tiles_get(((x >> 8) - 1) >> 3, y >> 8 >> 3);
        char tr_x = tiles_get(((x >> 8) + 7) >> 3, y >> 8 >> 3);
        char bl_x = tiles_get(((x >> 8) - 1) >> 3, ((y >> 8) + 7) >> 3);
        char br_x = tiles_get(((x >> 8) + 7) >> 3, ((y >> 8) + 7) >> 3);

        if(speed_x < 0) {
            if(tl_x != 0 || bl_x != 0) {
                x -= speed_x;
                x = ((x>>8) & (255-7)) << 8;
                speed_x = 0;
            }
        } else if(tr_x != 0 || br_x != 0) {
            x = ((x>>8) & (255-7)) << 8;
            speed_x = 0;
        }

        spr_attributes[SPR_ATTR_X] = x>>8;
        if(speed_x < 0) {
            if(state != STATE_LEFT) {
                state = STATE_LEFT;
                spr_define(0, pat_player_left, 8);
            }
        } else if(speed_x > 0) {
            if(state != STATE_RIGHT) {
                state = STATE_RIGHT;
                spr_define(0, pat_player_right, 8);
            }
        }
    } else if(state != STATE_IDLE) {
        state = STATE_IDLE;
        spr_define(0, pat_player_idle, 8);
    }
}

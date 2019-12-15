#include "player.h"
#include "input.h"
#include "video.h"

#include "../pat_player_idle.h"
#include "../pat_player_right.h"
#include "../pat_player_left.h"

enum {
      STATE_IDLE,
      STATE_RIGHT,
      STATE_LEFT
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
    video_spr_define(0, player_idle, 8);
    spr_attributes[SPR_ATTR_Y] = x >> 8;
    spr_attributes[SPR_ATTR_X] = y >> 8;
    spr_attributes[SPR_ATTR_PATTERN] = 0;
    spr_attributes[SPR_ATTR_COLOR] = 15;
    video_spr_update();
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

    // update x
    if(speed_x != 0) {
        x += speed_x;
        spr_attributes[SPR_ATTR_X] = x>>8;
        if(speed_x < 0) {
            if(state != STATE_LEFT) {
                state = STATE_LEFT;
                video_spr_define(0, player_left, 8);
            }
        } else if(speed_x > 0) {
            if(state != STATE_RIGHT) {
                state = STATE_RIGHT;
                video_spr_define(0, player_right, 8);
            }
        }
    } else if(state != STATE_IDLE) {
        state = STATE_IDLE;
        video_spr_define(0, player_idle, 8);
    }

    // move y
    y += speed_y;
    if(y >= 80 << 8) {
        y = 80 << 8;
        if(speed_y == 0 && (keys_row & (1<<5)) == 0)
            speed_y = -1024;
        else
            speed_y = 0;
    } else {
        if(speed_y < 0 && (keys_row & (1<<5)) == 0)
            speed_y += 60;
        else if((keys_row & (1<<6)) == 0)
            speed_y += 2048;
        else
            speed_y += 256;
    }
    spr_attributes[SPR_ATTR_Y] = y>>8;
}

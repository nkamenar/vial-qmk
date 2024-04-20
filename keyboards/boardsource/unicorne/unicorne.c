// Copyright 2023 jack (@waffle87)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "unicorne.h"

enum custom_keycodes {
    USER_FANTASIE_IMPROMPTU = QK_KB_0,
    AC_TOGG_CUSTOM,
    FF_PRELUDE_KEY,
    IMPERIAL_MARCH_KEY,
    COIN_SOUND_KEY,
    ONE_UP_SOUND_KEY,
    ZELDA_PUZZLE_KEY,
    MARIO_MUSHROOM_KEY,
};

static uint16_t key_timer;
static void refresh_rgb(void);
static void check_rgb_timeout(void);
bool is_rgb_timeout = false;

void refresh_rgb() {
  key_timer = timer_read();
  if (is_rgb_timeout) {
    is_rgb_timeout = false;
    oled_on();
    rgb_matrix_enable_noeeprom();
  }
}

void check_rgb_timeout() {
  if (!is_rgb_timeout && timer_elapsed(key_timer) > RGBLIGHT_TIMEOUT) {
    oled_off();
    rgb_matrix_disable_noeeprom();
    is_rgb_timeout = true;
  }
}

void housekeeping_task_user(void) {
  #ifdef RGBLIGHT_TIMEOUT
  check_rgb_timeout();
  #endif
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record) {
  #ifdef RGBLIGHT_TIMEOUT
  if (record->event.pressed) refresh_rgb();
  #endif
}

void post_encoder_update_user(uint8_t index, bool clockwise) {
  #ifdef RGBLIGHT_TIMEOUT
  refresh_rgb();
  #endif
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;
    }
    return rotation;
}

bool oled_task_kb(void) {
    if (!oled_task_user()) {
        return false;
    }
    if (is_keyboard_master()) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_raw(layer_zero, sizeof(layer_zero));
                break;
            case 1:
                oled_write_raw(layer_one, sizeof(layer_one));
                break;
            case 2:
                oled_write_raw(layer_two, sizeof(layer_two));
                break;
            case 3:
                oled_write_raw(layer_three, sizeof(layer_three));
                break;
        }
    } else {
        oled_write_raw(logo, sizeof(logo));
    }
    return true;
}

#endif // OLED_ENABLE


#ifdef AUDIO_ENABLE

float qwerty_song[][2] = SONG(QWERTY_SOUND);
float colemak_song[][2] = SONG(COLEMAK_SOUND);
float fantasie_impromptu[][2] = SONG(FANTASIE_IMPROMPTU);
float ff_prelude[][2] = SONG(USER_FF_PRELUDE);
float imperial_march[][2] = SONG(USER_IMPERIAL_MARCH);
float coin_sound[][2] = SONG(USER_COIN_SOUND);
float one_up_sound[][2] = SONG(USER_ONE_UP_SOUND);
float zelda_puzzle[][2] = SONG(USER_ZELDA_PUZZLE);
float mario_mushroom[][2] = SONG(USER_MARIO_MUSHROOM);

layer_state_t layer_state_set_user(layer_state_t state) {

    switch (get_highest_layer(state)) {
        case 0:
            PLAY_SONG(qwerty_song);
            break;
        case 1:
            PLAY_SONG(colemak_song);
            break;
        case 7:
            PLAY_SONG(zelda_puzzle);
            break;
    }
    return state;
}

#endif // AUDIO_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        #ifdef AUDIO_ENABLE
        case USER_FANTASIE_IMPROMPTU:
            if (record->event.pressed) {
                PLAY_SONG(fantasie_impromptu);
            }
            return false;
        case FF_PRELUDE_KEY:
            if (record->event.pressed) {
                PLAY_SONG(ff_prelude);
            }
            return false;
        case IMPERIAL_MARCH_KEY:
            if (record->event.pressed) {
                PLAY_SONG(imperial_march);
            }
            return false;
        case COIN_SOUND_KEY:
            if (record->event.pressed) {
                PLAY_SONG(coin_sound);
            }
            return false;
        case ONE_UP_SOUND_KEY:
            if (record->event.pressed) {
                PLAY_SONG(one_up_sound);
            }
            return false;
        case ZELDA_PUZZLE_KEY:
            if (record->event.pressed) {
                PLAY_SONG(zelda_puzzle);
            }
            return false;
        case MARIO_MUSHROOM_KEY:
            if (record->event.pressed) {
                PLAY_SONG(mario_mushroom);
            }
            return false;
        #endif // AUDIO_ENABLE
        case AC_TOGG_CUSTOM:
            if (record->event.pressed) {
                autocorrect_toggle();
            }
            return false;
    }
    return true;
}

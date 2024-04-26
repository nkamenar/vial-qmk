/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

#define VIAL_KEYBOARD_UID \
    { 0x73, 0xFD, 0x11, 0x1F, 0x7F, 0x19, 0xC9, 0x33 }

#define VIAL_UNLOCK_COMBO_ROWS \
    { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS \
    { 0, 1 }

#ifndef EEPROM_ENABLE
    #define EEPROM_ENABLE yes
#endif
#define FORCE_NKRO

#define RGB_MATRIX_LED_COUNT 54
#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_ALPHAS_MODS
#define RGB_MATRIX_DEFAULT_HUE 138
#define RGB_MATRIX_DEFAULT_SAT 255
#define RGB_MATRIX_DEFAULT_VAL 150
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGBLIGHT_TIMEOUT (1000 * 60 * 5)
#define OLED_TIMEOUT (1000 * 60 * 5)
#define SPLIT_OLED_ENABLE

#define DYNAMIC_KEYMAP_LAYER_COUNT 7

#undef STARTUP_SONG
#define STARTUP_SONG SONG(STARTUP_SOUND)

#define SPLIT_POINTING_ENABLE
#define POINTING_DEVICE_RIGHT
#define TAPPING_TERM 175

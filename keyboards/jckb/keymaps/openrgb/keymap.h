#pragma once

#ifndef KEYMAP_H
#define KEYMAP_H

#include QMK_KEYBOARD_H

enum layers{
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN
};



#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)

extern const uint16_t PROGMEM keymaps[4][MATRIX_ROWS][MATRIX_COLS];

void matrix_init_user(void);
void matrix_scan_user(void);
bool process_record_user(uint16_t keycode, keyrecord_t *record);

#endif

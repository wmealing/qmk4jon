
#include QMK_KEYBOARD_H

#pragma once

#ifndef KEYMAP_H
#define KEYMAP_H

void matrix_init_user(void);
void matrix_scan_user(void);

bool process_record_user(uint16_t keycode, keyrecord_t *record);


#endif 

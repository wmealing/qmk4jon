/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

#define NA NO_LED

/* RGB Positioning */
led_config_t g_led_config = { {
    {   0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, NA, 14 },
    {  15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 },
    {  31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, NA, 45 },
    {  46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, NA, 58, NA, 59 },
    {  60, NA, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, NA },
    {  74, 75, 76, 77, NA, NA, 78, NA, NA, 79, 80, 81, 82, 83, 84, 85 }
}, {
    { 0,  0 }, { 18,  0 }, { 33,  0}, { 48,  0 }, { 62,  0 }, { 81,  0 }, { 95,  0 }, { 110,  0 }, { 125,  0 }, { 143,  0 }, { 158,  0 }, { 173,  0 }, { 187,  0 }, { 205,  0 },              { 224,  0 },
    { 0, 15 }, { 15, 15 }, { 29, 15}, { 44, 15 }, { 59, 15 }, { 73, 15 }, { 88, 15 }, { 103, 15 }, { 117, 15 }, { 132, 15 }, { 147, 15 }, { 161, 15 }, { 176, 15 }, { 191, 15 }, { 205, 15 }, { 224, 15 },
    { 4, 28 }, { 22, 28 }, { 37, 28}, { 51, 28 }, { 66, 28 }, { 81, 28 }, { 95, 28 }, { 110, 28 }, { 125, 28 }, { 139, 28 }, { 154, 28 }, { 169, 28 }, { 183, 28 }, { 207, 36 },              { 224, 28 },
    { 6, 40 }, { 26, 40 }, { 40, 40}, { 55, 40 }, { 70, 40 }, { 84, 40 }, { 99, 40 }, { 114, 40 }, { 128, 40 }, { 143, 40 }, { 158, 40 }, { 172, 40 },              { 187, 40 },              { 224, 40 },
    { 9, 52 },             { 33, 52}, { 48, 52 }, { 62, 52 }, { 77, 52 }, { 92, 52 }, { 106, 52 }, { 121, 52 }, { 136, 52 }, { 150, 52 }, { 165, 52 }, { 180, 52 }, { 194, 52 }, { 209, 52 },             
    { 2, 64 }, { 18, 64 }, { 35, 64}, { 51, 64 },                         { 92, 64 },                           { 134, 64 }, { 150, 64 }, { 165, 64 }, { 180, 64 }, { 194, 64 }, { 209, 64 }, { 224, 64 }
}, {
    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1,
    9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4,    1,
    1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1,   
    1, 1, 1, 1,       4,       1, 1, 1, 1, 1, 1, 1
} };

#endif

#ifdef AUDIO_ENABLE
void keyboard_pre_init_kb(void) {
    // ensure pin is set and enabled pre-audio init
    setPinOutput(SPEAKER_SHUTDOWN);
    writePinHigh(SPEAKER_SHUTDOWN);
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    // set pin based on active status
    writePin(SPEAKER_SHUTDOWN, audio_is_on());
    keyboard_post_init_user();
}

void audio_on_user(void) {
    writePinHigh(SPEAKER_SHUTDOWN);
}

void audio_off_user(void) {
    // needs a delay or it runs right after play note.
    wait_ms(200);
    writePinLow(SPEAKER_SHUTDOWN);
}
#endif

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (!dip_switch_update_user(index, active)) {
        return false;
    }
    if (index == 0) {
        default_layer_set(1UL << (active ? 2 : 0));
    }
    return true;
}
#endif


#if defined(RGB_MATRIX_ENABLE) && defined(CAPS_LOCK_LED_INDEX)

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_user(keycode, record)) {
        return false;
    }
    switch (keycode) {
#    ifdef RGB_MATRIX_ENABLE
        case RGB_TOG:
            if (record->event.pressed) {
                switch (rgb_matrix_get_flags()) {
                    case LED_FLAG_ALL: {
                        rgb_matrix_set_flags(LED_FLAG_NONE);
                        rgb_matrix_set_color_all(0, 0, 0);
                    } break;
                    default: {
                        rgb_matrix_set_flags(LED_FLAG_ALL);
                    } break;
                }
            }
            if (!rgb_matrix_is_enabled()) {
                rgb_matrix_set_flags(LED_FLAG_ALL);
                rgb_matrix_enable();
            }
            return false;
#    endif
    }
    return true;
}

bool rgb_matrix_indicators_advanced_kb(uint8_t led_min, uint8_t led_max) {
    if (!rgb_matrix_indicators_advanced_user(led_min, led_max)) {
        return false;
    }
    // RGB_MATRIX_INDICATOR_SET_COLOR(index, red, green, blue);

    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 255, 255, 255);
    } else {
        if (!rgb_matrix_get_flags()) {
            RGB_MATRIX_INDICATOR_SET_COLOR(CAPS_LOCK_LED_INDEX, 0, 0, 0);
        }
    }
    return true;
}

#endif

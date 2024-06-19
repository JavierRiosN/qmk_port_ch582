/*
Copyright 2024 JavierRiosN <https://github.com/JavierRiosN>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "extra_keycode.h"
/*
enum custrom_keycodes {
    KC_LAYERD = QK_KB,
    KC_LAYERI
};
*/


#ifdef TAP_DANCE_ENABLE
// If Tap Dance functionality is enabled on rules.cmake, then wee define it
// We define 6 Tap Dance actions, they are pretty self-explanatory:
//    1. TD_ESC_SFT - One key tap sends ESC, two key sends Left Shift
//    2. TD_ENT_CTL - One key tap sends ENTER, two key sends Left Control
//    3. TD_TAB_ALT - One key tap sends TAB, two key sends Left ALT
//    4. TD_BT3_SFT - One key tap sends Mouse Button 3, two key taps sends Left Shift
//    5. TD_SPC_CTL - One key tap sends Space, two key taps sends Left Control
//    6. TD_ESC_ALT - One Key tap sends ESC, tow key taps sends Left Alt
// 
// First, we need to declar de enum so we can call the TD by name
enum {
    TD_ESC_SFT,
    TD_ENT_ALT,
    TD_TAB_CTL,
    TD_BT3_SFT,
    TD_SPC_CTL,
    TD_ESC_ALT,
};

// Define Tap Dance actions acording to its enum number
tap_dance_action_t tap_dance_actions[] = {
    [TD_BT3_SFT] = ACTION_TAP_DANCE_DOUBLE(KC_MS_BTN3, KC_LSFT),
    [TD_SPC_CTL] = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_LCTL),
    [TD_ESC_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_LALT),
    [TD_ESC_SFT] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_LSFT),
    [TD_ENT_ALT] = ACTION_TAP_DANCE_DOUBLE(KC_ENT, KC_LALT),
    [TD_TAB_CTL] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, KC_LCTL),
};

#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_16e4(
                    KC_A,            KC_B,               KC_C,            KC_DEL, 
                    KC_G,            KC_R,               KC_S,            TT(2), 
                    KC_X,            KC_Y,               KC_Z,            TT(1),

                    CTL_T(KC_ESC),  ALT_T(KC_MUTE),      SFT_T(KC_SPC),   KC_MS_BTN3),
    [1] = LAYOUT_16e4(
                    KC_D,            KC_E,               KC_F,            KC_BSPC,
                    KC_N,            KC_O,               KC_T,            TT(3),
                    KC_ENT,          KC_SPC,             KC_MS_BTN3,      _______,

                    CTL_T(KC_ENT),   ALT_T(KC_MPLY),     SFT_T(KC_TAB),   KC_MS_BTN2),
    [2] = LAYOUT_16e4(
                    KC_P7,           KC_P8,              KC_P9,           KC_P0,
                    KC_P4,           KC_P5,              KC_P6,           _______,
                    KC_P1,           KC_P2,              KC_P3,           _______,

                    KC_PSLS,         KC_EJCT,            _______,         _______),
    [3] = LAYOUT_16e4(
                    RGB_M_P,         RGB_M_B,            RGB_M_R,         RGB_M_SW,
                    RGB_M_SN,        RGB_M_K,            RGB_M_X,         _______,
                    RGB_M_G,         RGB_M_T,            _______,         _______,

                    RGB_TOG,         _______,            _______,         _______)
};

#ifdef ENCODER_MAP_ENABLE

const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { 
        ENCODER_CCW_CW(KC_LAYERD,   KC_LAYERI),                  // Define Macros 0 and 1 to CTL+Z and CTL+SFT+Z (Undo, Redo)
        ENCODER_CCW_CW(KC_VOLD,     KC_VOLU), 
        ENCODER_CCW_CW(KC_UP,       KC_DOWN), 
        ENCODER_CCW_CW(KC_WH_D,     KC_WH_U)
    },
    [1] = { 
        ENCODER_CCW_CW(KC_TRNS,     KC_TRNS), 
        ENCODER_CCW_CW(KC_MPRV,     KC_MNXT), 
        ENCODER_CCW_CW(KC_LEFT,     KC_RIGHT), 
        ENCODER_CCW_CW(KC_PGDN,     KC_PGUP) 
    },
    [2] = { 
        ENCODER_CCW_CW(KC_TRNS,     KC_TRNS), 
        ENCODER_CCW_CW(KC_MS_L,     KC_MS_R), 
        ENCODER_CCW_CW(KC_LBRC,     KC_RBRC), 
        ENCODER_CCW_CW(KC_PMNS,     KC_PPLS) 
    },
    [3] = { 
        ENCODER_CCW_CW(KC_TRNS,     KC_TRNS), 
        ENCODER_CCW_CW(RGB_RMOD,    RGB_MOD), 
        ENCODER_CCW_CW(RGB_HUD,     RGB_HUI), 
        ENCODER_CCW_CW(RGB_SAD,     RGB_SAI) 
    }
};
#endif

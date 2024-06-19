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

#pragma once

#include "quantum.h"

// clang-format off
#define LAYOUT_16e4( \
	K000, K001, K002, K003,\
    K004, K005, K006, K007,\
    K008, K009, K010, K011,\
    K012, K013, K014, K015 \
) \
{ \
    { K000, K001, K002, K003,   \
      K004, K005, K006, K007,   \
      K008, K009, K010, K011,   \
      K012, K013, K014, K015 }  \
}

// LED Indicators parameters
#define INDICATORS_ENABLED          true                    // Are there keys that will be used to indicate Caps and Num lock state?
#define INDICATORS_HSV_HUE          0                       // Direct RBG color. If not specified, then the effect speed will be used to
                                                            // generate a HUE value adding it to the main color's HUE so you can change it
                                                            // directly in VIA on the fly.
#define CAPS_IND_INDEX              11                      // Capslock indicator at bottom left key
#define NUMP_IND_INDEX              10                      // Numlock indicator bottom left 2nd key
#define NUMP_IND_REVERSE            true                    // If your keyboard has numpad, is better to indicate only when is disabled so
                                                            // there's no many lights always on. Change to false to normal behavior.


// Define the keycode, `QK_KB` avoids collisions with existing keycodes.
// Default code in QMK needs to be QK_USER_0, buy VIA starts CUSTOM(0)
// on QK_KB keycode
enum custom_keycodes {
    KC_LAYERD                       = QK_KB,                // Layer- keycode. Best used in a CCW encoder
    KC_LAYERI                                               // Layer+ keycode. Best used in a CW encoder
};

// Layer indicator parameters
#define LAYER_IND_ENABLED           true                    // Active layer number indicator enabled?
#define LAYER_IND_COLOR             HSV_SPRINGGREEN         // Active layer indictator color. Use a HSV color so we can use the same matrix bright


// If there's DYNAMIC_KEYMAP_LAYER_COUNT defined, we take it
// otherwise, we set to 4 that is QMK's layers count default
#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#define LAYER_CYCLE_END             DYNAMIC_KEYMAP_LAYER_COUNT
#else
#define LAYER_CYCLE_END             4
#endif

bool cycle_layer(int8_t step, bool pressed);                // Function to change layer
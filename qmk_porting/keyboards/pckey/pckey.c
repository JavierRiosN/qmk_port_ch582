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

// The following functions will be available only if the keyboard has
// RGB matrix enabled. See the rules.cmake file.
#ifdef RGB_MATRIX_ENABLE
/* clang-format off */
led_config_t g_led_config = {
	{
		{
            3,      2,      1,      0, 
            4,      5,      6,      7, 
            11,     10,     9,      8,
            NO_LED, NO_LED, NO_LED, NO_LED
        }

	}, {
		{ 0,   0}, { 75,  0}, {149,  0}, {224,  0},
		{224, 32}, {149, 32}, { 75, 32}, {  0, 32},
		{ 0,  64}, { 75, 64}, {149, 64}, {224, 64}
	}, {
		4, 4, 4, 4,
		4, 4, 4, 1,
		1, 4, 4, 4
	}
};
/* clang-format on */

/* Activates keys indicators for Caps and Num lock state
 * We use a HUE value to preserve the matrix SAT and VAL 
 * this way the color could harmonize with the matrix color settings
 * and can be changed from VIA on the fly
 */
bool rgb_matrix_indicators_user(void) {
#ifdef INDICATORS_ENABLED
    HSV hsv  = rgb_matrix_config.hsv;                   // Get the main effect color
    hsv.v   += 50;                                      // Make the indicators a little bit brighter

#ifdef INDICATORS_HSV_HUE                               // If there is a direct HUE value defined, use it
    hsv.h    = INDICATORS_HSV_HUE;

#else                                                   // If there's not a direct HUE, use the effect speed
    hsv.h   += rgb_matrix_config.speed;                 // We add the speed value to the Hue.
                                                        // In VIA you can change the Effect speed to chage this color
#endif // INDICTATORS_HSV_HUE

    RGB rgb_indicator_color = hsv_to_rgb(hsv);          // Convert the HSV to RGB so we can use it in rg_matrix_set_color()
    
    if (host_keyboard_led_state().caps_lock)
        rgb_matrix_set_color(CAPS_IND_INDEX, 
                             rgb_indicator_color.r, 
                             rgb_indicator_color.g, 
                             rgb_indicator_color.b);

#if NUMP_IND_REVERSE
    if (!host_keyboard_led_state().num_lock)
#else
    if (host_keyboard_led_state().num_lock)
#endif
        rgb_matrix_set_color(NUMP_IND_INDEX, 
                             rgb_indicator_color.r, 
                             rgb_indicator_color.g, 
                             rgb_indicator_color.b);
#endif // INDICATORS_ENABLED

    return true;
}

/* Indicates the active layer on the top keys.
 * We will be using the first four keys in a binary arrange so we can represent unto 16 layer numbers
 * So, the indictators will activate like this:
 * O O O O = Layer 0        O O O * = Layer 1        O O * O = Layer 2        O O * * = Layer 3
 * O * O O = Layer 4        O * O * = Layer 5        O * * O = Layer 6        O * * * = Layer 7
 * and so on...
 */
#ifdef LAYER_IND_ENABLED

bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {                    // If there's user function, first run it and exit
        return false;
    }

    uint8_t layer = get_highest_layer(layer_state);         // Get the current layer activated
    uint8_t mask = 1U << 7;                                 // Bitwise mask to get binary layer number

    uint8_t i = 0;
    for (i = 0; i < 8; i++) {
        if (layer & mask) {
            rgb_matrix_set_color(7 - i, LAYER_IND_COLOR);   // 7 -i because we're looping binary numbers in reverse
        }
        layer <<= 1;                                        // eliminates the last bit because it has been processed
    }
//        rgb_matrix_set_color(layer -1, RGB_SPRINGGREEN);  // Activate the indicator on the same key number that the layer number

    return true;
}
#endif // LAYER_IND_ENABLED

#endif // RGB_MATRIX_ENABLED



// Add the Layer+ and Layer- behaviour on custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    switch (keycode) {
        case KC_LAYERI:
            return cycle_layer(1, record->event.pressed);   // Increment the layer number by 1

        case KC_LAYERD:
            return cycle_layer(-1, record->event.pressed);  // Decrement the layer number by 1

        // Process other keycodes normally
        default:
            return true;
    }
}

// Change the active layer given a step of 1 or -1 to foward and backward respectively
// pressed is a keyrecord value so we can run only when the key is pressed,
bool cycle_layer(int8_t step, bool pressed) {

    int8_t layer = get_highest_layer(layer_state);

    // We only do something on key pressed, otherwise let QMK process it
    if (pressed) {

        if (layer > LAYER_CYCLE_END) {
            layer = 0;
        } else if (layer == 0 && step == -1) {
            layer = LAYER_CYCLE_END;
        }

        layer_move(layer + step);

        return true;

    } else {
        return false;
    }
}
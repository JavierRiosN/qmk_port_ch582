/*
Copyright 2022 Huckies <https://github.com/Huckies>
Copyright 2023 OctopusZ <https://github.com/OctopusZ>
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

/* USB Device descriptor parameter */
#define VENDOR_ID    0x68A8
#define PRODUCT_ID   0x1688
#define DEVICE_VER   0x0001
#define MANUFACTURER pckey
#define PRODUCT      pckey016

// JRPad 16E4 Matrix
#define MATRIX_ROWS 1
#define MATRIX_COLS 16

#define DIRECT_PINS                 \
    {                               \
         B8,  B17,  B16,  B15,      \
         A1,   A2,   A3,   B9,      \
         A4,   A5,   A6,   A0,      \
                                    \
        B14,   B4,   B7,   B0       \
    }

// Change this number to define the number of layer available in VIA
#define DYNAMIC_KEYMAP_LAYER_COUNT 8

#define DIODE_DIRECTION       COL2ROW

// Row and Column of Boot magic key. 
// Puts the keyboard on bootload mode when you press it and plug keyboard
#define BOOTMAGIC_LITE_ROW    0
#define BOOTMAGIC_LITE_COLUMN 0

// Encoders tends to not work with combo if these are not defined
#define PERMISSIVE_HOLD
#define HOLD_ON_OTHER_KEY_PRESS

#ifdef ENCODER_ENABLE
// Encoders pins for CCW
#define ENCODERS_PAD_A          \
    {                           \
        B13,  B2,  B6, B20      \
    }
// Encoders pins for CW
#define ENCODERS_PAD_B          \
    {                           \
        B12,  B3, B5,  B21      \
    }
#define ENCODER_RESOLUTION 4
#endif

#ifdef RGB_MATRIX_ENABLE
#define WS2812_EN_PIN   B18
#define WS2812_EN_LEVEL 1

//#define RGB_MATRIX_DEFAULT_MODE RGB_MATRIX_SOLID_REACTIVE
#define RGBLED_NUM                    12
#define RGB_MATRIX_LED_COUNT          RGBLED_NUM
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100
#define RGB_MATRIX_STARTUP_VAL        RGB_MATRIX_MAXIMUM_BRIGHTNESS
#define RGB_MATRIX_HUE_STEP           5
#define RGB_MATRIX_SAT_STEP           4 
#define RGB_MATRIX_VAL_STEP           4
#define RGB_MATRIX_SPD_STEP           5

#define RGB_DISABLE_WHEN_USB_SUSPENDED

// RGB Matrix Modes enum
#define ENABLE_RGB_MATRIX_SOLID_COLOR
#define ENABLE_RGB_MATRIX_ALPHAS_MODS
#define ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#define ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_BREATHING
#define ENABLE_RGB_MATRIX_BAND_SAT
#define ENABLE_RGB_MATRIX_BAND_VAL
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#define ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#define ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
#define ENABLE_RGB_MATRIX_CYCLE_ALL
#define ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#define ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#define ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#define ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#define ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#define ENABLE_RGB_MATRIX_DUAL_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_BEACON
#define ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#define ENABLE_RGB_MATRIX_FLOWER_BLOOMING
#define ENABLE_RGB_MATRIX_RAINDROPS
#define ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
#define ENABLE_RGB_MATRIX_HUE_BREATHING
#define ENABLE_RGB_MATRIX_HUE_PENDULUM
#define ENABLE_RGB_MATRIX_HUE_WAVE
#define ENABLE_RGB_MATRIX_PIXEL_FRACTAL
#define ENABLE_RGB_MATRIX_PIXEL_FLOW
#define ENABLE_RGB_MATRIX_PIXEL_RAIN
#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
#define ENABLE_RGB_MATRIX_DIGITAL_RAIN
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_RGB_MATRIX_SPLASH
#define ENABLE_RGB_MATRIX_MULTISPLASH
#define ENABLE_RGB_MATRIX_SOLID_SPLASH
#define ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 10

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
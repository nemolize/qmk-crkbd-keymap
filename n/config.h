/*
This is the c configuration file for the keymap

Copyright 2019 Masaru Nemoto <mnemoto.dev@gmail.com>
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

//#define USE_MATRIX_I2C

/* Select hand configuration */

#if !(MASTER_LEFT || MASTER_RIGHT || EE_HANDS)
#define MASTER_LEFT
//#define MASTER_RIGHT
//#define EE_HANDS
#endif

//#define SSD1306OLED

#define USE_SERIAL_PD2

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 100
//#define RETRO_TAPPING    // Tap even if TAPPING_TERM has expired
//#define PERMISSIVE_HOLD  // Always the modified output
//#define PREVENT_STUCK_MODIFIERS
//#define TAP_DANCE_ENABLE
//#undef IGNORE_MOD_TAP_INTERRUPT

//#define ONESHOT_TIMEOUT 0
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION
//#define LINK_TIME_OPTIMIZATION_ENABLE

#undef RGBLED_NUM
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 27
#define RGBLIGHT_LIMIT_VAL 120
#define RGBLIGHT_HUE_STEP 10
#define RGBLIGHT_SAT_STEP 17
#define RGBLIGHT_VAL_STEP 17

#define MOUSEKEY_FRAMERATE 144
#define MOUSEKEY_CURSOR_FORCE 288
#define MOUSEKEY_CURSOR_MASS 1
#define MOUSEKEY_CURSOR_FRICTION 24
#define MOUSEKEY_WHEEL_FRAMERATE 24
#define MOUSEKEY_WHEEL_FORCE 1
#define MOUSEKEY_WHEEL_MASS 1
#define MOUSEKEY_WHEEL_FRICTION 6

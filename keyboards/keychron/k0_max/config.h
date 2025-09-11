/* Copyright 2025 @ Keychron (https://www.keychron.com)
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

#pragma once

// Matrix scan shift register configuration
#define HC595_STCP A2
#define HC595_SHCP A3
#define HC595_DS A1
#define HC595_START_INDEX 0
#define HC595_END_INDEX 4

/* Encoder Configuration */
#define ENCODER_DEFAULT_POS 0x3
#define ENCODER_MAP_KEY_DELAY 2
#define ENCODER_PULL_UP_DISABLE

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 1

#if defined(RGB_MATRIX_ENABLE) || defined(LK_WIRELESS_ENABLE)
/* SPI configuration */
#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7
#endif

#ifdef RGB_MATRIX_ENABLE
/* RGB Matrix driver configuration */
#    define DRIVER_COUNT 1
#    define RGB_MATRIX_LED_COUNT 26

#    define DRIVER_CS_PINS \
        { B6 }
#    define SNLED23751_SPI_DIVISOR 16

#    define RGB_MATRIX_DRIVER_LOAD_ENABLE
/* Set LED driver current */
#    define SNLED27351_CURRENT_TUNE \
        { 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40 }

/* Set to infinit, which is use in USB mode by default */
#    define RGB_MATRIX_TIMEOUT RGB_MATRIX_TIMEOUT_INFINITE
/* Turn off backlight on low brightness to save power */
#    define RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 48
#    define RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE

/* Indications */
#    define NUM_LOCK_INDEX 5
#    define LOW_BAT_IND_INDEX \
        { 23 }

#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#endif

#ifdef LK_WIRELESS_ENABLE
/* Hardware configuration */
#    define P24G_MODE_SELECT_PIN C14
#    define BT_MODE_SELECT_PIN C15

#    define LKBT51_RESET_PIN B0
#    define LKBT51_INT_INPUT_PIN B1
#    define LKBT51_INT_OUTPUT_PIN A4

#    define USB_POWER_SENSE_PIN A9
#    define USB_POWER_CONNECTED_LEVEL 0

#    define BAT_LOW_LED_PIN A0
#    define BAT_LOW_LED_PIN_ON_STATE 1

#    define BT_HOST_DEVICES_COUNT 3

#    if defined(RGB_MATRIX_ENABLE)

#        define SNLED27351_SDB_PIN B7

#        define BT_INDCATION_LED_MATRIX_LIST \
            { 0, 1, 2 }

#        define P24G_INDICATION_LED_MATRIX_INDEX 3

/* Backlit disable timeout when keyboard is disconnected(unit: second) */
#        define DISCONNECTED_BACKLIGHT_DISABLE_TIMEOUT 40
/* Backlit disable timeout when keyboard is connected(unit: second) */
#        define CONNECTED_BACKLIGHT_DISABLE_TIMEOUT 600
/* Reinit LED driver on tranport changed */
#        define REINIT_LED_DRIVER 1

#        define LOW_POWER_MODE PM_STOP1
#    endif

/* Keep USB connection in blueooth mode */
#    define KEEP_USB_CONNECTION_IN_WIRELESS_MODE

/* Enable bluetooth NKRO */
//#    define WIRELESS_NKRO_ENABLE
#endif

/* Factory test keys */
#define FN_KEY_1 MO(1)
#define FN_BL_TRIG_KEY KC_PMNS
#define BL_CYCLE_KEY KC_MPLY
#define FN_Z_KEY UG_SATD
#define FN_J_KEY UG_HUED

#define MATRIX_IO_DELAY 10

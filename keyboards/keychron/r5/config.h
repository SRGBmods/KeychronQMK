/* Copyright 2025 ~ 2026 @ Keychron (https://www.keychron.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "eeconfig_kb.h"

/* Indication LEDs */
#define LED_MAC_OS_PIN C7
#define LED_WIN_OS_PIN C6
#define LED_OS_PIN_ON_STATE 0

/* I2C Driver Configuration */
#define I2C1_SCL_PIN B8
#define I2C1_SDA_PIN B9
#define I2C1_CLOCK_SPEED 400000
#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2
#define I2C1_OPMODE OPMODE_I2C

/* EEPROM Configuration */
#define EXTERNAL_EEPROM_BYTE_COUNT 3072
#define EXTERNAL_EEPROM_PAGE_SIZE 32
#define EXTERNAL_EEPROM_WRITE_TIME 4
#define EXTERNAL_EEPROM_I2C_BASE_ADDRESS 0b10100010

/* 74HC95 Driver Configuration */
#define HC595_STCP C2
#define HC595_SHCP C1
#define HC595_DS C3
#define HC595_START_INDEX 10
#define HC595_END_INDEX 17
#define HC595_OFFSET_INDEX 0

/* USB DP control pin */
#define DP_PULLUP_CONTROL_PIN B10

/* RGB Matrix configuration */
#if defined(RGB_MATRIX_ENABLE)
#    define SPI_DRIVER SPIDQ
#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7
#    define SNLED27351_SELECT_PINS \
        { C5, A3 }
#    define SNLED27351_SDB_PIN A2
#    define SNLED27351_SPI_DIVISOR 16
#endif

#ifdef LK_WIRELESS_ENABLE
/* Hardware configuration */
#    define P24G_MODE_SELECT_PIN A10
#    define BT_MODE_SELECT_PIN A9

#    define LKBT51_RESET_PIN C4
#    define WIRELESS_TO_MCU_INT_PIN B1
#    define MCU_TO_WIRELESS_INT_PIN A4

#    define USB_POWER_SENSE_PIN B0
#    define USB_POWER_CONNECTED_LEVEL 0

#    define BAT_CHARGING_PIN B13
#    define BAT_CHARGING_LEVEL 0

#    define BAT_LOW_LED_PIN A8
#    define BAT_LOW_LED_PIN_ON_STATE 0

#    define BT_HOST_DEVICES_COUNT 3
#    define BT_INDICATION_LED_ON_STATE 0

#    define BT_INDICATION_LED_PIN_LIST \
        { C8, C8, C8 }

#    define P24G_LED_PIN C9
#    define BT_LED_PIN C8

#    if defined(RGB_MATRIX_ENABLE)

#        define BT_INDCATION_LED_MATRIX_LIST \
            { 19, 20, 21 }

#        define P24G_INDICATION_LED_INDEX 22

#        define BAT_LEVEL_LED_LIST \
            { 19, 20, 21, 22, 23, 24, 25, 26, 27, 28 }

/* Reinit LED driver on tranport changed */
#        define LED_DRIVER_REINIT_ON_TRANSPORT_CHANGE
#    endif

/* Keep USB connection in wireless mode */
#    define KEEP_USB_CONNECTION_IN_WIRELESS_MODE
/* Enable wireless NKRO */
#    define WIRELESS_NKRO_ENABLE

#endif

/* OS toggle configuration*/
#define KEYCOMBO_OS_SELECT_ENABLE
#define WIN_BASE_LAYER 0
#define MAC_BASE_LAYER 2

/* Win key lock configuration */
#define WIN_LOCK_HOLD_TIME 3000
#define GUI_TOGGLE_INDICATION_ENABLE

/* Factory test keys */
#define FN_KEY_1 MO(1)
#define FN_KEY_2 MO(3)

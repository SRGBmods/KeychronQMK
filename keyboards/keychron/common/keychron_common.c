/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#endif
#ifdef RETAIL_DEMO_ENABLE
#    include "retail_demo.h"
#endif
#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#    include "wireless.h"
#endif
#ifdef LED_MATRIX_ENABLE
#    include "led_matrix.h"
#endif

bool     is_siri_active = false;
uint32_t siri_timer     = 0;

static uint8_t mac_keycode[4] = {
    KC_LOPT,
    KC_ROPT,
    KC_LCMD,
    KC_RCMD,
};

// clang-format off
static key_combination_t key_comb_list[] = {
    {2, {KC_LWIN, KC_TAB}},
    {2, {KC_LWIN, KC_E}},
    {3, {KC_LSFT, KC_LCMD, KC_4}},
    {2, {KC_LWIN, KC_C}},
#ifdef WIN_LOCK_SCREEN_ENABLE
    {2, {KC_LWIN, KC_L}},
#endif
#ifdef MAC_LOCK_SCREEN_ENABLE
    {3, {KC_LCTL, KC_LCMD, KC_Q}},
#endif
};
// clang-format on

void keychron_common_init(void) {
#ifdef SNAP_CLICK_ENABLE
    extern void snap_click_init(void);
    snap_click_init();
#endif
#if defined(RGB_MATRIX_ENABLE) && defined(KEYCHRON_RGB_ENABLE)
    extern void eeconfig_init_custom_rgb(void);
    eeconfig_init_custom_rgb();
#endif
#ifdef LK_WIRELESS_ENABLE
#    ifdef P2P4_MODE_SELECT_PIN
    palSetLineMode(P2P4_MODE_SELECT_PIN, PAL_MODE_INPUT);
#    endif
#    ifdef BT_MODE_SELECT_PIN
    palSetLineMode(BT_MODE_SELECT_PIN, PAL_MODE_INPUT);
#    endif
#    ifdef BAT_LOW_LED_PIN
    writePin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);
#    endif

    lkbt51_init(false);
    wireless_init();
#endif

#ifdef ENCODER_ENABLE
    encoder_cb_init();
#endif
}

bool process_record_keychron_common(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_MCTRL:
            if (record->event.pressed) {
                register_code(KC_MISSION_CONTROL);
            } else {
                unregister_code(KC_MISSION_CONTROL);
            }
            return false; // Skip all further processing of this key
        case KC_LNPAD:
            if (record->event.pressed) {
                register_code(KC_LAUNCHPAD);
            } else {
                unregister_code(KC_LAUNCHPAD);
            }
            return false; // Skip all further processing of this key
        case KC_LOPTN:
        case KC_ROPTN:
        case KC_LCMMD:
        case KC_RCMMD:
            if (record->event.pressed) {
                register_code(mac_keycode[keycode - KC_LOPTN]);
            } else {
                unregister_code(mac_keycode[keycode - KC_LOPTN]);
            }
            return false; // Skip all further processing of this key
        case KC_SIRI:
            if (record->event.pressed) {
                if (!is_siri_active) {
                    is_siri_active = true;
                    register_code(KC_LCMD);
                    register_code(KC_SPACE);
                }
                siri_timer = timer_read32();
            } else {
                // Do something else when release
            }
            return false; // Skip all further processing of this key
        case KC_TASK:
        case KC_FILE:
        case KC_SNAP:
        case KC_CTANA:
#ifdef WIN_LOCK_SCREEN_ENABLE
        case KC_WLCK:
#endif
#ifdef MAC_LOCK_SCREEN_ENABLE
        case KC_MLCK:
#endif
            if (record->event.pressed) {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    register_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            } else {
                for (uint8_t i = 0; i < key_comb_list[keycode - KC_TASK].len; i++) {
                    unregister_code(key_comb_list[keycode - KC_TASK].keycode[i]);
                }
            }
            return false; // Skip all further processing of this key
#ifdef LED_MATRIX_ENABLE
        case BL_SPI:
            led_matrix_increase_speed();
            break;
        case BL_SPD:
            led_matrix_decrease_speed();
            break;
#endif
        default:
            return true; // Process all other keycodes normally
    }
    return true;
}

void keychron_common_task(void) {
    if (is_siri_active && timer_elapsed32(siri_timer) > 500) {
        unregister_code(KC_LCMD);
        unregister_code(KC_SPACE);
        is_siri_active = false;
        siri_timer     = 0;
    }
}

#ifdef ENCODER_ENABLE
static void encoder_pad_cb(void *param) {
    uint8_t index = (uint32_t)param;
    encoder_inerrupt_read(index);
}

void encoder_cb_init(void) {
    pin_t encoders_pad_a[] = ENCODERS_PAD_A;
    pin_t encoders_pad_b[] = ENCODERS_PAD_B;
    for (uint32_t i = 0; i < NUM_ENCODERS; i++) {
        palEnableLineEvent(encoders_pad_a[i], PAL_EVENT_MODE_BOTH_EDGES);
        palEnableLineEvent(encoders_pad_b[i], PAL_EVENT_MODE_BOTH_EDGES);
        palSetLineCallback(encoders_pad_a[i], encoder_pad_cb, (void *)i);
        palSetLineCallback(encoders_pad_b[i], encoder_pad_cb, (void *)i);
    }
}
#endif

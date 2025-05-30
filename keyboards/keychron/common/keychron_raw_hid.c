/* Copyright 2024 @ Keychron (https://www.keychron.com)
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
#include "keychron_raw_hid.h"
#include "raw_hid.h"
#include "version.h"
#include "language.h"
#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#endif
#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#endif
#ifdef ANANLOG_MATRIX
#    include "analog_matrix.h"
#endif
#ifdef DYNAMIC_DEBOUNCE_ENABLE
#    include "keychron_debounce.h"
#endif
#ifdef SNAP_CLICK_ENABLE
#    include "snap_click.h"
#endif
#ifdef LK_WIRELESS_ENABLE
#    include "wireless.h"
#endif

extern void dfu_info_rx(uint8_t *data, uint8_t length);

void get_support_feature(uint8_t *data) {
    data[0] = 0;
    data[1] = FEATURE_DEFAULT_LAYER
#ifdef KC_BLUETOOTH_ENABLE
              | FEATURE_BLUETOOTH
#endif
#ifdef LK_WIRELESS_ENABLE
              | FEATURE_BLUETOOTH | FEATURE_P24G
#endif
#ifdef ANANLOG_MATRIX
              | FEATURE_ANALOG_MATRIX
#endif
#ifdef INFO_CHAGNED_NOTIFY_ENABLE
              | FEATURE_INFO_CHAGNED_NOTIFY
#endif
#ifdef DYNAMIC_DEBOUNCE_ENABLE
              | FEATURE_DYNAMIC_DEBOUNCE
#endif
#ifdef SNAP_CLICK_ENABLE
              | FEATURE_SNAP_CLICK
#endif
#ifdef KEYCHRON_RGB_ENABLE
              | FEATURE_KEYCHRON_RGB
#endif
        ;
}

void get_firmware_version(uint8_t *data) {
    uint8_t i = 0;
    data[i++] = 'v';
    if ((DEVICE_VER & 0xF000) != 0) itoa((DEVICE_VER >> 12), (char *)&data[i++], 16);
    itoa((DEVICE_VER >> 8) & 0xF, (char *)&data[i++], 16);
    data[i++] = '.';
    itoa((DEVICE_VER >> 4) & 0xF, (char *)&data[i++], 16);
    data[i++] = '.';
    itoa(DEVICE_VER & 0xF, (char *)&data[i++], 16);
    data[i++] = ' ';
    memcpy(&data[i], QMK_BUILDDATE, sizeof(QMK_BUILDDATE));
    i += sizeof(QMK_BUILDDATE);
}


__attribute__((weak)) void kc_rgb_matrix_rx(uint8_t *data, uint8_t length) {}

bool kc_raw_hid_rx(uint8_t *data, uint8_t length) {
    switch (data[0]) {
        case KC_GET_PROTOCOL_VERSION:
            data[1] = PROTOCOL_VERSION;
            data[2] = 0;
            data[3] = QMK_COMMAND_SET;
            break;

        case KC_GET_FIRMWARE_VERSION:
            get_firmware_version(&data[1]);
            break;

        case KC_GET_SUPPORT_FEATURE:
            get_support_feature(&data[1]);
            break;

        case KC_GET_DEFAULT_LAYER:
            data[1] = get_highest_layer(default_layer_state);
            break;

        case 0xA7:
            switch (data[1]) {
                case MISC_GET_PROTOCOL_VER:
                    data[2] = 0;
                    data[3] = MISC_PROTOCOL_VERSION & 0xFF;
                    data[4] = (MISC_PROTOCOL_VERSION >> 8) & 0xFF;
                    data[5] = MISC_DFU_INFO | MISC_LANGUAGE
#ifdef DYNAMIC_DEBOUNCE_ENABLE
                            | MISC_DEBOUNCE
#endif
#ifdef SNAP_CLICK_ENABLE
                            | MISC_SNAP_CLICK
#endif
#ifdef LK_WIRELESS_ENABLE
                            | MISC_WIRELESS_LPM
#endif
#ifdef HSUSB_8K_ENABLE
                            | MISC_REPORT_REATE
#endif
                            ;
                    break;

                case DFU_INFO_GET:
                    dfu_info_rx(data, length);
                    break;
                case LANGUAGE_GET ... LANGUAGE_SET:
                    language_rx(data, length);
                    break;

#if defined(DYNAMIC_DEBOUNCE_ENABLE)
                case DEBOUNCE_GET ... DEBOUNCE_SET:
                    debounce_rx(data, length);
                    break;
#endif
#if defined(SNAP_CLICK_ENABLE)
                case SNAP_CLICK_GET_INFO ... SNAP_CLICK_SAVE:
                    snap_click_rx(data, length);
                    break;
#endif
#if defined(LK_WIRELESS_ENABLE) && defined(EECONFIG_BASE_WIRELESS_CONFIG)
                case WIRELESS_LPM_GET ... WIRELESS_LPM_SET:
                    wireless_raw_hid_rx(data, length);
                    break;
#endif
#if defined(HSUSB_8K_ENABLE)
                case REPORT_RATE_GET ... REPORT_RATE_SET:
                    report_rate_hid_rx(data, length);
                    break;
#endif
                default:
                    data[0] = 0xFF;
                    data[1] = 0;
                    break;
            }
            break;

#if defined(KEYCHRON_RGB_ENABLE)
        case 0xA8:
            kc_rgb_matrix_rx(data, length);
            break;
#endif

#ifdef ANANLOG_MATRIX
        case 0xA9:
            analog_matrix_rx(data, length);
            return true;
#endif
#ifdef LK_WIRELESS_ENABLE
        case 0xAA:
            lkbt51_dfu_rx(data, length);
            return true;

#endif
#ifdef FACTORY_TEST_ENABLE
        case 0xAB:
            factory_test_rx(data, length);
            return true;

#endif
        default:
            return false;
    }

    raw_hid_send(data, length);
    return true;
}

#if defined(VIA_ENABLE)
bool via_command_kb(uint8_t *data, uint8_t length) {
    return kc_raw_hid_rx(data, length);
}
#else
void raw_hid_receive(uint8_t *data, uint8_t length) {
    kc_raw_hid_rx(data, length);
}
#endif

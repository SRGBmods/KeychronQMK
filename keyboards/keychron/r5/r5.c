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

#include "keychron.h"

#define POWER_ON_LED_DURATION 3000
#define CHARGED_INDICATION_DELAY_TIME 2000

static uint32_t power_on_indicator_timer;
static uint32_t charged_ind_delay_timer = 0;

#ifdef LK_WIRELESS_ENABLE
pin_t bt_led_pins[] = BT_INDICATION_LED_PIN_LIST;
#endif

void keyboard_post_init_kb(void) {
    power_on_indicator_timer = timer_read32();

    gpio_set_pin_output_push_pull(BT_LED_PIN);
    gpio_set_pin_output_push_pull(P24G_LED_PIN);
    gpio_set_pin_output_push_pull(LED_WIN_OS_PIN);
    gpio_set_pin_output_push_pull(LED_MAC_OS_PIN);
    gpio_write_pin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
    gpio_write_pin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);

    keychron_common_init();
    keyboard_post_init_user();
}

void os_indicator_task(void) {
    if (get_highest_layer(default_layer_state) == MAC_BASE_LAYER) {
        gpio_write_pin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
        gpio_write_pin(LED_MAC_OS_PIN, LED_OS_PIN_ON_STATE);
    }
    if (get_highest_layer(default_layer_state) == WIN_BASE_LAYER) {
        gpio_write_pin(LED_WIN_OS_PIN, LED_OS_PIN_ON_STATE);
        gpio_write_pin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);
    }
}

void battery_charging_indicator_task(void) {
    if (usb_power_connected()) {
        indicator_enable_direct_led_off(false);

        if (indicator_is_running()) {
            if (get_transport() == TRANSPORT_BLUETOOTH) {
                gpio_write_pin(P24G_LED_PIN, !BT_INDICATION_LED_ON_STATE);
                gpio_write_pin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
            } else if (get_transport() == TRANSPORT_P2P4) {
                gpio_write_pin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
            }
        } else {
            /* Turn off blue LED used by Bluetooth */
            gpio_write_pin(BT_LED_PIN, !BT_INDICATION_LED_ON_STATE);

            if (gpio_read_pin(BAT_CHARGING_PIN) == 0) {
                /* Charging */
                charged_ind_delay_timer = 0;
                gpio_write_pin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);
                gpio_write_pin(P24G_LED_PIN, !BT_INDICATION_LED_ON_STATE);
            } else {
                /* Charging complete */
                if (charged_ind_delay_timer == 0) {
                    charged_ind_delay_timer = timer_read32();
                }

                if (charged_ind_delay_timer && (timer_elapsed32(charged_ind_delay_timer) > CHARGED_INDICATION_DELAY_TIME)) {
                    charged_ind_delay_timer = 0;
                    gpio_write_pin(P24G_LED_PIN, BT_INDICATION_LED_ON_STATE);
                    gpio_write_pin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
                }
            }
        }
    } else {
        /* Not charging */
        charged_ind_delay_timer = 0;
        indicator_enable_direct_led_off(true);

        if (get_transport() != TRANSPORT_USB) {
            if (!indicator_is_running()) {
                gpio_write_pin(P24G_LED_PIN, !BT_INDICATION_LED_ON_STATE);
                gpio_write_pin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
            }
        }
    }
}

void power_on_indicator_task(void) {
    if (power_on_indicator_timer) {
        if (timer_elapsed32(power_on_indicator_timer) > POWER_ON_LED_DURATION) {
            power_on_indicator_timer = 0;

            if (!host_keyboard_led_state().caps_lock) {
                gpio_write_pin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
            }
            gpio_write_pin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
            gpio_write_pin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);
#ifdef LK_WIRELESS_ENABLE
            gpio_write_pin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
            gpio_write_pin(BT_LED_PIN, !BT_INDICATION_LED_ON_STATE);
            gpio_write_pin(P24G_LED_PIN, !BT_INDICATION_LED_ON_STATE);
            if (get_transport() != TRANSPORT_P2P4) {
                for (uint8_t i = 0; i < sizeof(bt_led_pins) / sizeof(pin_t); i++)
                    gpio_write_pin(bt_led_pins[i], !BT_INDICATION_LED_ON_STATE);
            }
            if (get_transport() != TRANSPORT_BLUETOOTH) {
                gpio_write_pin(P24G_LED_PIN, !BT_INDICATION_LED_ON_STATE);
            }
#endif

        } else {
            gpio_write_pin(LED_CAPS_LOCK_PIN, LED_PIN_ON_STATE);
            gpio_write_pin(LED_WIN_OS_PIN, LED_OS_PIN_ON_STATE);
            gpio_write_pin(LED_MAC_OS_PIN, LED_OS_PIN_ON_STATE);
#ifdef LK_WIRELESS_ENABLE
            gpio_write_pin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);
            gpio_write_pin(BT_LED_PIN, BT_INDICATION_LED_ON_STATE);
            gpio_write_pin(P24G_LED_PIN, BT_INDICATION_LED_ON_STATE);
            if (get_transport() != TRANSPORT_P2P4) {
                for (uint8_t i = 0; i < sizeof(bt_led_pins) / sizeof(pin_t); i++)
                    gpio_write_pin(bt_led_pins[i], BT_INDICATION_LED_ON_STATE);
            }
            if (get_transport() != TRANSPORT_BLUETOOTH) {
                gpio_write_pin(P24G_LED_PIN, BT_INDICATION_LED_ON_STATE);
            }
#endif
        }
    }
}

void keychron_task_kb(void) {
    power_on_indicator_task();
    battery_charging_indicator_task();

    if (battery_is_critical_low()) {
        gpio_write_pin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
        gpio_write_pin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);
    } else {
        os_indicator_task();
    }
}

#ifdef LK_WIRELESS_ENABLE
bool lpm_is_kb_idle(void) {
    return power_on_indicator_timer == 0 && !backlight_indicator_is_active();
}

void lpm_enter_low_power_kb(void) {
    gpio_write_pin(BT_LED_PIN, !BT_INDICATION_LED_ON_STATE);
    gpio_write_pin(P24G_LED_PIN, !BT_INDICATION_LED_ON_STATE);
    gpio_write_pin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);

    if (wireless_get_state() == WT_SUSPEND) {
        gpio_write_pin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
        gpio_write_pin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);
    }
}
#endif

void suspend_power_down_keychron_kb(void) {
    if (get_transport() == TRANSPORT_USB) {
        gpio_write_pin(LED_WIN_OS_PIN, !LED_OS_PIN_ON_STATE);
        gpio_write_pin(LED_MAC_OS_PIN, !LED_OS_PIN_ON_STATE);
    }
    suspend_power_down_user();
}

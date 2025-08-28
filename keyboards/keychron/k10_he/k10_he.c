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

#include "quantum.h"
#include "keychron_common.h"
#ifdef FACTORY_TEST_ENABLE
#    include "factory_test.h"
#endif
#ifdef LK_WIRELESS_ENABLE
#    include "lkbt51.h"
#    include "wireless.h"
#    include "lpm.h"
#    include "transport.h"
#endif

#ifndef POWER_ON_LED_DURATION
#    define POWER_ON_LED_DURATION 3000
#endif

static uint32_t power_on_indicator_timer;

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    if (index == 0) {
        default_layer_set(1UL << (active ? 0 : 2));
    }
    dip_switch_update_user(index, active);
#    if defined(LED_WIN_PIN) && defined(LED_MAC_PIN)
    if (active == 0) {
        writePin(LED_WIN_PIN, !LED_OS_PIN_ON_STATE);
        writePin(LED_MAC_PIN, LED_OS_PIN_ON_STATE);
    } else if (active == 1) {
        writePin(LED_WIN_PIN, LED_OS_PIN_ON_STATE);
        writePin(LED_MAC_PIN, !LED_OS_PIN_ON_STATE);
    }
#    endif
    return true;
}
#endif

void keyboard_post_init_kb(void) {
    setPinOutputPushPull(LED_WIN_PIN);
    setPinOutputPushPull(LED_MAC_PIN);
    writePin(LED_WIN_PIN, !LED_OS_PIN_ON_STATE);
    writePin(LED_MAC_PIN, !LED_OS_PIN_ON_STATE);

#ifdef LK_WIRELESS_ENABLE
    setPinInput(P2P4_MODE_SELECT_PIN);
    setPinInput(BT_MODE_SELECT_PIN);

    lkbt51_init(false);
    wireless_init();
#    ifdef BAT_LOW_LED_PIN
    setPinOutputPushPull(BAT_LOW_LED_PIN);
    writePin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);
#    endif
#endif

    power_on_indicator_timer = timer_read32();
    keyboard_post_init_user();
}

bool keychron_task_kb(void) {
    if (power_on_indicator_timer) {
        if (timer_elapsed32(power_on_indicator_timer) > POWER_ON_LED_DURATION) {
            power_on_indicator_timer = 0;
#ifdef BAT_LOW_LED_PIN
            writePin(BAT_LOW_LED_PIN, !BAT_LOW_LED_PIN_ON_STATE);
#endif
            if (!host_keyboard_led_state().caps_lock) {
                setPinOutput(LED_CAPS_LOCK_PIN);
                writePin(LED_CAPS_LOCK_PIN, !LED_PIN_ON_STATE);
            }
            if (!host_keyboard_led_state().num_lock) {
                setPinOutput(LED_NUM_LOCK_PIN);
                writePin(LED_NUM_LOCK_PIN, !LED_PIN_ON_STATE);
            }
#if defined(LED_WIN_PIN) && defined(LED_MAC_PIN)
            if (readPin(B14) == 0) {
                writePin(LED_MAC_PIN, !LED_OS_PIN_ON_STATE);
            } else if (readPin(B14) == 1) {
                writePin(LED_WIN_PIN, !LED_OS_PIN_ON_STATE);
            }
#endif

        } else {
#ifdef BAT_LOW_LED_PIN
            writePin(BAT_LOW_LED_PIN, BAT_LOW_LED_PIN_ON_STATE);
#endif
            setPinOutput(LED_CAPS_LOCK_PIN);
            writePin(LED_CAPS_LOCK_PIN, LED_PIN_ON_STATE);
            setPinOutput(LED_NUM_LOCK_PIN);
            writePin(LED_NUM_LOCK_PIN, LED_PIN_ON_STATE);
#if defined(LED_WIN_PIN) && defined(LED_MAC_PIN)
            writePin(LED_WIN_PIN, LED_OS_PIN_ON_STATE);
            writePin(LED_MAC_PIN, LED_OS_PIN_ON_STATE);
#endif
        }
    }
    return true;
}

#ifdef LK_WIRELESS_ENABLE
bool lpm_is_kb_idle(void) {
    return power_on_indicator_timer == 0 && !factory_reset_indicating();
}
#endif

void enter_power_mode_kb(pm_t mode) {
    if (wireless_get_state() == WT_SUSPEND || wireless_get_state() == WT_DISCONNECTED) {
        writePin(LED_WIN_PIN, !LED_OS_PIN_ON_STATE);
        writePin(LED_MAC_PIN, !LED_OS_PIN_ON_STATE);
    }
}

void suspend_power_down_kb(void) {
    if (get_transport() == TRANSPORT_USB) {
        writePin(LED_WIN_PIN, !LED_OS_PIN_ON_STATE);
        writePin(LED_MAC_PIN, !LED_OS_PIN_ON_STATE);
    }

    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    if (get_transport() == TRANSPORT_USB) {
        dip_switch_read(true);
    }
    suspend_wakeup_init_user();
}

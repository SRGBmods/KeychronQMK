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

#include "quantum.h"

void eeconfig_init_kb(void) {
    keymap_config.raw  = eeconfig_read_keymap();
    keymap_config.nkro = 1;
    eeconfig_update_keymap(keymap_config.raw);
    eeconfig_init_user();
}

void keyboard_post_init_kb(void) {
    setPinOutputPushPull(LED_WIN_LOCK_PIN);

    keyboard_post_init_user();
}

void housekeeping_task_kb() {
    writePin(LED_WIN_LOCK_PIN, keymap_config.no_gui ? LED_WIN_LOCK_PIN_ON_STATE : !LED_WIN_LOCK_PIN_ON_STATE);
}

void suspend_power_down_kb(void) {
    writePin(LED_WIN_LOCK_PIN, !LED_WIN_LOCK_PIN_ON_STATE);

    suspend_power_down_user();
}

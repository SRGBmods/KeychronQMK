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

#include "sn3734-spi.h"
#include <string.h>
#include "spi_master.h"
#include "wait.h"
#include "gpio.h"

#ifndef SN3734_SWS
#    define SN3734_SWS SN3734_SWS_ALL
#endif

#ifndef SN2734_SCALING
#    define SN2734_SCALING \
        { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF }
#endif

#ifndef SN3734_SRS
#    define SN3734_SRS SN3734_PWM_FREQUENCY_6K_HZ
#endif

#ifndef SN3734_SWPDR
#    define SN3734_SWPDR SN3734_SWPDR_2V0
#endif

#ifndef SN3734_CSPUR
#    define SN3734_CSPUR SN3734_CSPUR_PVCC_MINUS_2V0
#endif

#ifndef SN3734_GLOBAL_CURRENT
#    define SN3734_GLOBAL_CURRENT 0xFF
#endif

#define SN3734_WRITE (0 << 7)
#define SN3734_READ (1 << 7)
#define SN3734_ID (0b110 << 4)

#define SN3734_DRIVER_COUNT (sizeof(cs_pins) / sizeof(pin_t))

#ifdef DRIVER_CS_PINS
pin_t cs_pins[] = DRIVER_CS_PINS;
#else
error "no DRIVER_CS_PINS defined"
#endif

typedef struct sn3734_driver_t {
    uint8_t pwm_buffer[SN3734_PWM_REGISTER_COUNT];
    bool    pwm_buffer_dirty;
    bool    led_control_buffer_dirty;
} PACKED sn3734_driver_t;

sn3734_driver_t driver_buffers[SN3734_DRIVER_COUNT] = {{
    .pwm_buffer       = {0},
    .pwm_buffer_dirty = false,
}};

// uint8_t g_pwm_buffer[SN3734_DRIVER_COUNT][SN3734_PWM_REGISTER_COUNT];
// bool    g_pwm_buffer_update_required[SN3734_DRIVER_COUNT]        = {false};
// bool    g_scaling_registers_update_required[SN3734_DRIVER_COUNT] = {false};

bool sn3734_write(uint8_t index, uint8_t page, uint8_t reg, uint8_t *data, uint16_t len) {
    static uint8_t spi_transfer_buffer[2] = {0};

    if (index > ARRAY_SIZE(((pin_t[])DRIVER_CS_PINS)) - 1) return false;

    if (!spi_start(cs_pins[index], false, 0, SN3734_SPI_DIVISOR)) {
        spi_stop();
        return false;
    }

    spi_transfer_buffer[0] = SN3734_WRITE | SN3734_ID | (page & 0x0F);
    spi_transfer_buffer[1] = reg;

    if (spi_transmit(spi_transfer_buffer, 2) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }

    if (spi_transmit(data, len) != SPI_STATUS_SUCCESS) {
        spi_stop();
        return false;
    }

    spi_stop();
    return true;
}

bool sn3734_write_register(uint8_t index, uint8_t page, uint8_t reg, uint8_t data) {
    return sn3734_write(index, page, reg, &data, 1);
}

void sn3734_write_pwm_buffer(uint8_t index) {
    sn3734_write(index, SN3734_PWM_PAGE, SN3734_PWM_PAGE_PWM_START, driver_buffers[index].pwm_buffer, SN3734_PWM_PAGE_REGISTER_COUNT);
    sn3734_write(index, SN3734_FUNC_PAGE, SN3734_FUNC_PAGE_PWM_START, driver_buffers[index].pwm_buffer + SN3734_PWM_PAGE_REGISTER_COUNT, SN3734_FUNC_PAGE_REGISTER_COUNT);
}

void sn3734_init_drivers(void) {
#if defined(SN3734_SDB_PIN)
    gpio_set_pin_output_push_pull(SN3734_SDB_PIN);
    gpio_write_pin_high(SN3734_SDB_PIN);
#endif

    spi_init();

    for (uint8_t i = 0; i < SN3734_DRIVER_COUNT; i++)
        sn3734_init(i);
}

void sn3734_init(uint8_t index) {
    gpio_set_pin_output_push_pull(cs_pins[index]);
    gpio_write_pin_low(cs_pins[index]);

    // Reset all registers
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_RESET, 0xAE);
    // Set to normal mode
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_CONFIGURATION, SN3734_NORMAL_MODE | SN3734_PWM_MODE_8 | SN3734_SWS);
    // Set Golbal Current Control Register
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_GLOBAL_CURRENT, SN3734_GLOBAL_CURRENT);
    // Set Pull up & Down for SWx CSy
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_PULLDOWNUP, SN3734_SWPDR | SN3734_CSPUR);
    // Set Scan rate frequencY
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_SRS, (SN3734_SRS & 0b111));

    // Set Scaling register
    uint8_t scaling_reg[SCALING_REG_LEN] = SN2734_SCALING;
    sn3734_write(index, SN3734_FUNC_PAGE, SN3734_SCALING_START, scaling_reg, SCALING_REG_LEN);

    // Wait 10ms to ensure the device has woken up.
    wait_ms(10);
}

void sn3734_set_color(int index, uint8_t red, uint8_t green, uint8_t blue) {
    sn3734_led_t led;
    if (index >= 0 && index < SN3734_LED_COUNT) {
        memcpy_P(&led, (&g_sn3734_leds[index]), sizeof(led));
#ifndef SN3734_FORCE_UPDATE_BUFFER
        if (driver_buffers[led.driver].pwm_buffer[led.r] == red && driver_buffers[led.driver].pwm_buffer[led.g] == green && driver_buffers[led.driver].pwm_buffer[led.b] == blue) {
            return;
        }
#endif
        driver_buffers[led.driver].pwm_buffer[led.r] = red;
        driver_buffers[led.driver].pwm_buffer[led.g] = green;
        driver_buffers[led.driver].pwm_buffer[led.b] = blue;
        driver_buffers[led.driver].pwm_buffer_dirty  = true;
    }
}

void sn3734_set_color_all(uint8_t red, uint8_t green, uint8_t blue) {
    for (int i = 0; i < SN3734_LED_COUNT; i++) {
        sn3734_set_color(i, red, green, blue);
    }
}

float sn3734_get_load_ratio(void) {
    uint32_t totalBuf = 0;
    for (uint8_t i = 0; i < SN3734_DRIVER_COUNT; i++)
        for (uint16_t j = 0; j < SN3734_PWM_REGISTER_COUNT; j++)
            totalBuf += driver_buffers[i].pwm_buffer[j];

    return (float)totalBuf / (0xFF * 3 * SN3734_LED_COUNT);
}

void sn3734_update_pwm_buffers(uint8_t index) {
    if (driver_buffers[index].pwm_buffer_dirty) {
        sn3734_write_pwm_buffer(index);
        sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_PWM_UPDATE, 0);
        driver_buffers[index].pwm_buffer_dirty = false;
    }
}

void sn3734_flush(void) {
    for (uint8_t i = 0; i < SN3734_DRIVER_COUNT; i++)
        sn3734_update_pwm_buffers(i);
}

void sn3734_shutdown(void) {
#if defined(SN3734_SDB_PIN)
    gpio_write_pin_low(SN3734_SDB_PIN);
#else
    for (uint8_t i = 0; i < SN3734_DRIVER_COUNT; i++)
        sn3734_sw_shutdown(i);
#endif
}

void sn3734_exit_shutdown(void) {
#if defined(SN3734_SDB_PIN)
    gpio_write_pin_high(SN3734_SDB_PIN);
#else
    for (uint8_t i = 0; i < SN3734_DRIVER_COUNT; i++)
        sn3734_sw_return_normal(i);
#endif
}

void sn3734_sw_return_normal(uint8_t index) {
    // Setting LED driver to normal mode
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_CONFIGURATION, SN3734_NORMAL_MODE | SN3734_PWM_MODE_8 | SN3734_SWS);
}

void sn3734_sw_shutdown(uint8_t index) {
    // Setting LED driver to shutdown mode
    sn3734_write_register(index, SN3734_FUNC_PAGE, SN3734_FUNC_REG_CONFIGURATION, SN3734_SHUT_DOWN_MODE | SN3734_PWM_MODE_8 | SN3734_SWS);
}

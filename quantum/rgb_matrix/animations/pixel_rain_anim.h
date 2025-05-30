// Copyright 2022 @filterpaper
// SPDX-License-Identifier: GPL-2.0+

#ifdef ENABLE_RGB_MATRIX_PIXEL_RAIN
RGB_MATRIX_EFFECT(PIXEL_RAIN)
#    ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

static uint32_t rain_wait_timer = 0;

void PIXEL_RAIN_init(void) {
    rain_wait_timer = 0;
}

bool PIXEL_RAIN(effect_params_t* params) {

    inline uint32_t interval(void) {
        return 500 / scale16by8(qadd8(rgb_matrix_config.speed, 16), 16);
    }

    inline void rain_pixel(uint8_t led_index) {
        if (!HAS_ANY_FLAGS(g_led_config.flags[led_index], params->flags)) {
            return;
        }
        HSV hsv = (random8() & 2) ? (HSV){0, 0, 0} : (HSV){random8(), random8_min_max(127, 255), rgb_matrix_config.hsv.v};
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_region_set_color(params->region, led_index, rgb.r, rgb.g, rgb.b);
        rain_wait_timer = g_rgb_timer + interval();
    }

    RGB_MATRIX_USE_LIMITS(led_min, led_max);
    if (g_rgb_timer > rain_wait_timer) {
        rain_pixel(random8_max(RGB_MATRIX_LED_COUNT));
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#    endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif     // ENABLE_RGB_MATRIX_PIXEL_RAIN

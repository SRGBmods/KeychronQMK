/* Copyright 2024 ~ 2025 @ Keychron (https://www.keychron.com)
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

// clang-format off
#ifdef LED_MATRIX_ENABLE
const snled27351_led_t g_snled27351_leds[LED_MATRIX_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  LED address
 *   |  | */
    {0, CB6_CA1},
    {0, CB6_CA2},
    {0, CB6_CA3},
    {0, CB6_CA4},
    {0, CB6_CA5},
    {0, CB6_CA6},
    {0, CB6_CA7},
    {0, CB6_CA8},
    {0, CB6_CA9},
    {0, CB6_CA10},
    {0, CB6_CA11},
    {0, CB6_CA12},
    {0, CB6_CA13},
    {0, CB6_CA15},
    {0, CB6_CA16},
    {0, CB1_CA8},

    {0, CB5_CA1},
    {0, CB5_CA2},
    {0, CB5_CA3},
    {0, CB5_CA4},
    {0, CB5_CA5},
    {0, CB5_CA6},
    {0, CB5_CA7},
    {0, CB5_CA8},
    {0, CB5_CA9},
    {0, CB5_CA10},
    {0, CB5_CA11},
    {0, CB5_CA12},
    {0, CB5_CA13},
    {0, CB5_CA14},
    {0, CB6_CA14},
    {0, CB5_CA15},
    {0, CB5_CA16},
    {0, CB1_CA9},

    {0, CB4_CA1},
    {0, CB4_CA2},
    {0, CB4_CA3},
    {0, CB4_CA4},
    {0, CB4_CA5},
    {0, CB4_CA6},
    {0, CB4_CA7},
    {0, CB4_CA8},
    {0, CB4_CA9},
    {0, CB4_CA10},
    {0, CB4_CA11},
    {0, CB4_CA12},
    {0, CB4_CA13},
    {0, CB4_CA14},
    {0, CB4_CA15},
    {0, CB4_CA16},
    {0, CB1_CA6},

    {0, CB3_CA1},
    {0, CB3_CA2},
    {0, CB3_CA3},
    {0, CB3_CA4},
    {0, CB3_CA5},
    {0, CB3_CA6},
    {0, CB3_CA7},
    {0, CB3_CA8},
    {0, CB3_CA9},
    {0, CB3_CA10},
    {0, CB3_CA11},
    {0, CB3_CA12},
    {0, CB3_CA14},

    {0, CB2_CA1},
    {0, CB2_CA3},
    {0, CB2_CA4},
    {0, CB2_CA5},
    {0, CB2_CA6},
    {0, CB2_CA7},
    {0, CB2_CA8},
    {0, CB2_CA9},
    {0, CB2_CA10},
    {0, CB2_CA11},
    {0, CB2_CA12},
    {0, CB2_CA13},
    {0, CB2_CA14},
    {0, CB2_CA16},

    {0, CB1_CA1},
    {0, CB1_CA2},
    {0, CB1_CA3},
    {0, CB1_CA4},
    {0, CB1_CA7},
    {0, CB1_CA10},
    {0, CB1_CA11},
    {0, CB1_CA12},
    {0, CB1_CA13},
    {0, CB1_CA14},
    {0, CB1_CA15},
    {0, CB1_CA16},
    {0, CB2_CA15},
};

#define __ NO_LED

led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        { 0,  30,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15 },
        { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 31, 32, 33 },
        { 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50 },
        { 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, __, 63, __, __, __ },
        { 64, __, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, __, 77, __ },
        { 78, 79, 80, 81, __, __, 82, __, __, 83, 84, 85, 86, 87, 88, 89, 90 },
    },
    {
        // LED Index to Physical Position
        {0,  0},           {22,  0}, {35,  0}, {50,  0}, {63,  0}, {82,  0}, {95,  0}, {108,  0}, {121,  0}, {141,  0}, {154,  0}, {167,  0}, {180,  0},            {193,  0}, {206,  0}, {224,  0},
        {0, 14}, {13, 14}, {22, 14}, {35, 14}, {50, 14}, {63, 14}, {76, 14}, {89, 14}, {102, 14}, {115, 14}, {128, 14}, {141, 14}, {154, 14}, {165, 14}, {176, 14}, {193, 14}, {206, 14}, {224, 14},
        {5, 26}, {15, 26}, {29, 26}, {43, 26}, {57, 26}, {71, 26}, {83, 26}, {97, 26}, {110, 26}, {123, 26}, {136, 26}, {149, 26}, {162, 26}, {176, 32},            {193, 26}, {206, 26}, {224, 26},
        {6, 39}, {16, 39}, {29, 39}, {42, 39}, {55, 39}, {68, 39}, {81, 39}, {94, 39}, {107, 39}, {120, 39}, {133, 39}, {146, 39}, {173, 39},
        {8, 51},           {23, 51}, {36, 51}, {50, 51}, {63, 51}, {76, 51}, {89, 51}, {102, 51}, {115, 51}, {128, 51}, {141, 51}, {154, 51}, {173, 51},                       {206, 51},
        {2, 64}, {14, 64}, {23, 64}, {36, 64},                     {76, 64},                      {114, 64}, {128, 64}, {147, 64}, {167, 64}, {180, 64},            {193, 64}, {206, 64}, {224, 64}
    },
    {
        // LED Index to Flag
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,    1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1,    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,       1,
        1, 1, 1, 1,       1,       1, 1, 1, 1, 1,    1, 1, 1
    },
};
#endif

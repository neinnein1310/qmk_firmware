/* Copyright 2021 HorrorTroll <https://github.com/HorrorTroll>
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

// OLED animation
#include "lib/wave.c"
#include "lib/logo.c"

#ifdef OLED_ENABLE
    uint16_t startup_timer; 

    oled_rotation_t oled_init_user(oled_rotation_t rotation) {
        startup_timer = timer_read();

        return rotation;
    }

    static void render_layer_info(void) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("       QWERTY        "), false);
                break;
            case 1:
                oled_write_P(PSTR("      Function       "), false);
                break;
            default:
                oled_write_P(PSTR("      Undefined      "), false);
        }
    }

    static void render_layer_number(void) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("0"), false);
                break;
            case 1:
                oled_write_P(PSTR("1"), false);
                break;
            default:
                oled_write_P(PSTR("X"), false);
        }
    }

    bool oled_task_user(void) {
        static bool finished_logo = false;

        if ((timer_elapsed(startup_timer) < 5000) && !finished_logo) {
            render_logo();
        } else {
            finished_logo = true;

            led_t led_usb_state = host_keyboard_led_state();

            render_layer_info();

            // sleep if it has been long enough since we last got a char
            if (timer_elapsed32(wave_sleep) > OLED_TIMEOUT) {
                oled_off();
            } else {
                oled_on();
            }
            // time for the next frame?
            if (timer_elapsed(wave_timer) > FRAME_TIMEOUT) {
                wave_timer = timer_read();
                render_frame();
            }

            oled_set_cursor(0, 3);
            oled_write_P(led_usb_state.caps_lock ? PSTR("Caps  ") : PSTR("      "), false);
            oled_write_P(PSTR("Layer: "), false);
            render_layer_number();
            oled_write_P(led_usb_state.scroll_lock ? PSTR(" Scroll") : PSTR("       "), false);
        }

        return true;
    }
#endif

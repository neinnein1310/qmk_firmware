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
                oled_write_P(PSTR("QWERTY "), false);
                break;
            case 1:
                oled_write_P(PSTR("Function "), false);
                break;
            default:
                oled_write_P(PSTR("Undefined "), false);
        }
    }

    static void render_layer_number(void) {
        switch (get_highest_layer(layer_state)) {
            case 0:
                oled_write_P(PSTR("0  "), false);
                break;
            case 1:
                oled_write_P(PSTR("1"), false);
                break;
            default:
                oled_write_P(PSTR("X  "), false);
        }
    }

    bool oled_task_user(void) {
        static bool finished_logo = false;

        if ((timer_elapsed(startup_timer) < 5000) && !finished_logo) {
            render_logo();
        } else {
            finished_logo = true;

            led_t led_usb_state = host_keyboard_led_state();

            oled_write_P(led_usb_state.caps_lock ? PSTR("Caps Lock\n") : PSTR("---------\n"), false);
            oled_write_P(led_usb_state.scroll_lock ? PSTR("Scroll Lock\n") : PSTR("-----------\n"), false);

            oled_write_P(PSTR("\n"), false);

            render_layer_info();
            oled_write_P(PSTR("Layer: "), false);
            render_layer_number();
        }

        return true;
    }
#endif

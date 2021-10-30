/* Copyright 2019 Danny Nguyen <danny@keeb.io>
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

enum custom_keycodes
{
    HELP,
    GAME_BOT,

};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
        | Knob 1: Vol Dn/Up |      | Knob 2: Page Dn/Up |
        | Press: Mute       | Home | Press: Play/Pause  |
        | Hold: Layer 2     | Up   | RGB Mode           |
        | Left              | Down | Right              |
     */
    [0] = LAYOUT(
        KC_MUTE, MO(1), KC_MPLY,
        HYPR(KC_1), HYPR(KC_2), HYPR(KC_3),
        HYPR(KC_4), HYPR(KC_5), HYPR(KC_6)
    ),
    /*
        | RESET          | N/A  | Media Stop |
        | Held: Layer 2  | Home | RGB Mode   |
        | Media Previous | End  | Media Next |
     */
    [1] = LAYOUT(
        RESET  , _______, KC_STOP,
        _______, KC_HOME, RGB_MOD,
        GAME_BOT, KC_END , KC_MNXT
    ),
};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (!clockwise) {
            tap_code(KC__VOLUP);
        } else {
            tap_code(KC__VOLDOWN);
        }
    }
    else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch(keycode) {
        case(HELP):
            if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_DOWN(X_LCTRL));
            SEND_STRING(SS_DOWN(X_LGUI));
            SEND_STRING(SS_DOWN(X_RALT));
            SEND_STRING(SS_DOWN(X_RSHIFT));
            SEND_STRING("1");
            SEND_STRING(SS_UP(X_LCTRL));
            SEND_STRING(SS_UP(X_LGUI));
            SEND_STRING(SS_UP(X_RALT));
            SEND_STRING(SS_UP(X_RSHIFT));
            // SEND_STRING(SS_LCTL(SS_LALT(SS_LGUI("1"))));
            // SEND_STRING(""SS_LGUI("t"));
            SEND_STRING(SS_DELAY(1000)"Help"SS_TAP(X_ENTER)SS_TAP(X_TAB)"Help"SS_TAP(X_ENTER));
            SEND_STRING(SS_TAP(X_ESC));
        } else {
            // when keycode QMKBEST is released
        }
        break;
        case GAME_BOT:
        if (record->event.pressed) {
            SEND_STRING(SS_DOWN(X_RALT));
            SEND_STRING(SS_TAP(X_ENTER));
            SEND_STRING(SS_UP(X_RALT));
            SEND_STRING(SS_DELAY(1000)"r"SS_DELAY(300));
            SEND_STRING(SS_DOWN(X_RALT));
            SEND_STRING(SS_TAP(X_ENTER));
            SEND_STRING(SS_UP(X_RALT));
        }
    }
    return true;
}

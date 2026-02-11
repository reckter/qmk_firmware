/* Copyright 2015-2017 Jack Humbert
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

enum planck_layers
{
  _QWERTY,
  _DVORAK,
  _GAMING,
  _LOWER,
  _RAISE,
  _SUPER,
  _UMLAUT,
  _ADJUST,
  _MOUSE,
  _SETTING,
};

enum planck_keycodes
{
  QWERTY = SAFE_RANGE,
  DVORAK,
  GAMING,
  BACKLIT,
  EXT_PLV,

  // for switching unicode
  OS_LIN,
  OS_WIN,
  OS_MAC,

  // umlauts
  UC_AE,
  UC_OE,
  UC_UE,

  // macro in game "Bots are stupid"
  MACRO_RST,

  //songs
  SONG_MARCH,
  SONG_ALL_STAR,
};

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SUPER MO(_SUPER)
#define UMLAUT MO(_UMLAUT)

#define UC_EUR UC(0x20AC)
#define UE_SZ UC(0x00DF)

#include "gpio.h"

void keyboard_pre_init_user(void) {
    gpio_set_pin_output(24);
    gpio_write_pin_high(24);
}

void keyboard_post_init_user(void) {
  set_unicode_input_mode(UNICODE_MODE_MACOS);
}

uint8_t middle_led_r = 0;
uint8_t middle_led_g = 0;
uint8_t middle_led_b = 0;

void set_middle_led(uint8_t r, uint8_t g, uint8_t b)
{
  middle_led_r = r;
  middle_led_g = g;
  middle_led_b = b;
}

void disable_led(int code)
{
  // rgb_matrix_set_color(code, 0, 0, 0);
}

void dissable_leds(int leds[], int length)
{
  for (int i = 0; i < length; i++)
  {
    disable_led(leds[i]);
  }
}

bool rgb_matrix_indicators_user(void)
{
  uint8_t new_layer = get_highest_layer(layer_state);
  switch (new_layer)
  {
  case _DVORAK:
    break;
  case _RAISE:
    disable_led(14);
    disable_led(15);
    disable_led(16);
    disable_led(19);
    disable_led(20);
    disable_led(21);
    break;
  case _LOWER:
    disable_led(2);
    disable_led(3);
    disable_led(4);
    disable_led(14);
    disable_led(15);
    disable_led(16);
    disable_led(26);
    disable_led(27);
    disable_led(28);
    disable_led(39);
    break;
  case _ADJUST:
    break;
  case _SUPER:
    disable_led(1);
    disable_led(2);
    disable_led(3);
    disable_led(4);
    disable_led(13);
    disable_led(14);
    disable_led(15);
    disable_led(16);
    disable_led(25);
    disable_led(26);
    disable_led(27);
    disable_led(28);
    disable_led(19);
    disable_led(20);
    disable_led(21);
    disable_led(22);
    break;
  case _UMLAUT:
    disable_led(13);
    disable_led(14);
    disable_led(16);
    disable_led(22);
    break;
  case _MOUSE:
    disable_led(19);
    disable_led(20);
    disable_led(21);
    disable_led(22);
    disable_led(7);
    disable_led(8);
    disable_led(9);
    disable_led(10);
    disable_led(14);
    disable_led(15);
    disable_led(16);
    break;
  case _SETTING:
    disable_led(1);
    disable_led(3);
    disable_led(14);
    disable_led(25);
    disable_led(27);
    break;
  case _GAMING:
    disable_led(3);
    disable_led(14);
    disable_led(15);
    disable_led(16);
    break;
  }
  return false;
}

// Corne layout: LAYOUT_split_3x6_3
// 6 columns x 3 rows per half + 3 thumb keys per half = 42 keys total
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* GAMING
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |                    |   N  |   M  |   ,  |   .  |   /  |Enter |
     * `-----------------------------------------|                    |-----------------------------------------'
     *                      | GUI  |Lower | Space|                    |Space |Raise | Alt  |
     *                      `--------------------'                    `--------------------'
     */
    [_GAMING] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,      KC_Y,  KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,      KC_H,  KC_J,    KC_K,    KC_L,    KC_SCLN, TG(_SETTING),
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,      KC_N,  KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                   KC_LGUI, LOWER, KC_SPC,    KC_SPC, RAISE, KC_RALT
    ),

    /* QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bksp |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Esc  |   A  |   S  |   D  |   F  |   G  |                    |   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |                    |   N  |   M  |   ,  |   .  |   /  |Enter |
     * `-----------------------------------------|                    |-----------------------------------------'
     *                      | GUI  |Lower | Space|                    |Space |Raise | Alt  |
     *                      `--------------------'                    `--------------------'
     */
    [_QWERTY] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,      KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F, KC_G,      KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,      KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
                                   KC_LGUI, LOWER, KC_SPC,    KC_SPC, RAISE, KC_RALT
    ),

    /* Dvorak (with home row mods: O=Alt, E=Ctrl, U=Cmd | H=Cmd, T=Ctrl, N=Alt)
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | Tab  |   '  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  | Bksp |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Esc  |   A  | O/Alt|E/Ctrl|U/Cmd |   I  |                    |   D  |H/Cmd |T/Ctrl| N/Alt|   S  |//Uml |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |Super |   ;  |   Q  |   J  |   K  |   X  |                    |   B  |   M  |   W  |   V  |   Z  |Enter |
     * `-----------------------------------------|                    |-----------------------------------------'
     *                      | CMD  | Shift|Lower |                    |Raise | Space| CMD  |
     *                      `--------------------'                    `--------------------'
     */
    [_DVORAK] = LAYOUT_split_3x6_3(
        KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,   KC_Y,       KC_F,   KC_G,    KC_C,   KC_R,    KC_L,  KC_BSPC,
        KC_ESC,  KC_A,    LALT_T(KC_O), LCTL_T(KC_E), LGUI_T(KC_U), KC_I,       KC_D,   RGUI_T(KC_H), RCTL_T(KC_T), RALT_T(KC_N), KC_S,  LT(_UMLAUT, KC_SLSH),
        SUPER,   KC_SCLN, KC_Q,    KC_J,    KC_K,   KC_X,       KC_B,   KC_M,    KC_W,   KC_V,    KC_Z,  KC_ENT,
                                   KC_LGUI, KC_LSFT, LOWER,     RAISE,  KC_SPC,  KC_RGUI
    ),

    /* Lower
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |   1  |   2  |   3  |   %  |                    |   &  |   {  |   }  |   *  |      | Bksp |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |   4  |   5  |   6  |   0  |                    |   =  |   (  |   )  |   +  |   -  |  |   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |   7  |   8  |   9  |      |                    |   `  |   ~  | Home | End  |      |      |
     * `-----------------------------------------|                    |-----------------------------------------'
     *                      |   0  |      |      |                    |      |      | Play |
     *                      `--------------------'                    `--------------------'
     */
    [_LOWER] = LAYOUT_split_3x6_3(
        _______, _______, KC_1,    KC_2,    KC_3,    KC_PERC,    KC_AMPR, KC_LCBR, KC_RCBR, KC_ASTR, _______, KC_BSPC,
        _______,  _______, KC_4,    KC_5,    KC_6,    KC_0,      KC_EQL,  KC_LPRN, KC_RPRN, KC_PLUS, KC_MINS, KC_PIPE,
        _______, _______, KC_7,    KC_8,    KC_9,    _______,    KC_GRV,  S(KC_GRV), KC_HOME, KC_END, _______, _______,
                                   KC_0,    _______, _______,    _______, _______, KC_MPLY
    ),

    /* Raise
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |   `  |Macro |   &  |   $  |   €  |      |                    |      |   [  |   ]  |      |      | Bksp |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Del  |      |      |      |      |      |                    |      |   !  |   @  |   #  |   _  |  \   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |   `  | NUBS |PgUp  |PgDn  |      |
     * `-----------------------------------------|                    |-----------------------------------------'
     *                      |      |      |      |                    |      |      | Play |
     *                      `--------------------'                    `--------------------'
     */
    [_RAISE] = LAYOUT_split_3x6_3(
        KC_GRV,  MACRO_RST, _______, _______, _______,  _______,    _______, KC_LBRC, KC_RBRC, _______, _______, KC_BSPC,
        KC_DEL,  _______,   KC_AMPR, KC_DLR,  UC_EUR,  _______,    _______, KC_EXLM, KC_AT,   KC_HASH, KC_UNDS, KC_BSLS,
        _______, _______,   _______, _______, _______, _______,    _______, KC_GRV,  KC_NUBS, KC_PGUP, KC_PGDN, _______,
                                     _______, _______, _______,    _______, _______, KC_MPLY
    ),

    /* Umlauts
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |  ä   |  ö   |      |  ü   |      |                    |      |      |      |      |  ß   |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * `-----------------------------------------|                    |-----------------------------------------'
     *                      |      |      |      |                    |      |      |      |
     *                      `--------------------'                    `--------------------'
     */
    [_UMLAUT] = LAYOUT_split_3x6_3(
        _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
        _______, UC_AE,   UC_OE,   _______, UC_UE,   _______,    _______, _______, _______, _______, UE_SZ,   _______,
        _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______,    _______, _______, _______
    ),

    /* Super
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |   `  |  F1  |  F2  |  F3  |  F4  |      |                    |      |Mouse |Setng |      |      | Bksp |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Del  |  F5  |  F6  |  F7  |  F8  | Ctrl |                    |      | Left | Down |  Up  |Right |  \   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |  F9  |  F10 |  F11 |  F12 |      |                    |      |      |      |      |      |      |
     * `-----------------------------------------|                    |-----------------------------------------'
     *                      |      |      |      |                    | Alt  | GUI  |      |
     *                      `--------------------'                    `--------------------'
     */
    [_SUPER] = LAYOUT_split_3x6_3(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   HYPR(KC_P), _______, TO(_MOUSE), TO(_SETTING), _______, _______, KC_BSPC,
        KC_DEL,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_VOLU,    _______, KC_LEFT,    KC_DOWN,      KC_UP,   KC_RGHT, KC_BSLS,
        _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_VOLD,    _______, _______,    _______,      _______, _______, _______,
                                   _______, _______, _______,    KC_LALT, KC_LGUI,    _______
    ),

    /* Adjust (Lower + Raise)
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      | Boot |      |RGBTog|RGBMod|RGBHui|                    |RGBHud|RGBSai|RGBSad|RGBVai|RGBVad| Del  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |AU_ON |AU_OFF|AGNorm|                    |AGSwap|Qwerty|      |Dvorak|      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |MU_ON |MU_OFF|      |                    |      |      |      |      |      |      |
     * `-----------------------------------------|                    |-----------------------------------------'
     *                      |      |      |      |                    |      |      |      |
     *                      `--------------------'                    `--------------------'
     */
    [_ADJUST] = LAYOUT_split_3x6_3(
        _______, QK_BOOT, _______, RM_TOGG, RM_NEXT, RM_HUEU,    RM_HUED, RM_SATU, RM_SATD, RM_VALU, RM_VALD, KC_DEL,
        _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM,    AG_SWAP, QWERTY,  XXXXXXX, DVORAK,  XXXXXXX, _______,
        _______, _______, _______, MU_ON,   MU_OFF,  _______,    _______, _______, _______, _______, _______, _______,
                                   _______, _______, _______,    _______, _______, _______
    ),

    /* Mouse
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |WhlLft|WhlDn |WhlUp |WhlRgt|      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Exit |      |      | Btn2 | Btn1 |      |                    |      |MsLeft|MsDown| MsUp |MsRght|      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * `-----------------------------------------|                    |-----------------------------------------'
     *                      |      |      |      |                    |      |      |      |
     *                      `--------------------'                    `--------------------'
     */
    [_MOUSE] = LAYOUT_split_3x6_3(
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, MS_WHLL, MS_WHLD, MS_WHLU, MS_WHLR, XXXXXXX,
        TG(_MOUSE), XXXXXXX, XXXXXXX, MS_BTN2, MS_BTN1, XXXXXXX,    XXXXXXX, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, XXXXXXX,
        XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                      XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX
    ),

    /* Setting
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |OSLin |OSMac |OSWin |      |Gaming|                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Exit |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |RGBRnb|RGBBrt|RGBSwl|RGBSnk|RGBKnt|                    |      |      |      |      |      |      |
     * `-----------------------------------------|                    |-----------------------------------------'
     *                      |      |      |      |                    |      |      |      |
     *                      `--------------------'                    `--------------------'
     */
    [_SETTING] = LAYOUT_split_3x6_3(
        XXXXXXX,      OS_LIN,           OS_MAC,           OS_WIN,         XXXXXXX,        TG(_GAMING),    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        TG(_SETTING), SONG_MARCH,       SONG_ALL_STAR,    XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX,      RGB_MODE_RAINBOW, RGB_MODE_BREATHE, RGB_MODE_SWIRL, RGB_MODE_SNAKE, RGB_MODE_KNIGHT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                                          XXXXXXX,        XXXXXXX,        XXXXXXX,        XXXXXXX, XXXXXXX, XXXXXXX
    ),
};

#ifdef AUDIO_ENABLE
float plover_song[][2] = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

layer_state_t layer_state_set_user(layer_state_t state)
{
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

uint16_t get_unicode_hex_for_keypress(int uppercase, uint16_t keycode)
{
  // Uppercase letters
  if (uppercase)
  {
    switch (keycode)
    {
    case UC_AE:
      return 0x00c4;
    case UC_OE:
      return 0x00d6;
    case UC_UE:
      return 0x00dc;
    }
  }
  else
  {
    switch (keycode)
    {
    case UC_AE:
      return 0x00e4;
    case UC_OE:
      return 0x00f6;
    case UC_UE:
      return 0x00fc;
    }
  }
  return 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  switch (keycode)
  {
  case QWERTY:
    if (record->event.pressed)
    {
      set_single_persistent_default_layer(_QWERTY);
      set_middle_led(255, 0, 0);
    }
    return false;
  case DVORAK:
    if (record->event.pressed)
    {
      set_single_persistent_default_layer(_DVORAK);
      set_middle_led(0, 0, 0);
    }
    return false;
  case BACKLIT:
    if (record->event.pressed)
    {
      register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
      backlight_step();
#endif
    }
    break;

  // switch unicode input mode
  case OS_LIN:
    if (record->event.pressed) {
      set_unicode_input_mode(UNICODE_MODE_LINUX);
    }
    return false;
  case OS_WIN:
    if (record->event.pressed) {
      set_unicode_input_mode(UNICODE_MODE_WINCOMPOSE);
    }
    return false;
  case OS_MAC:
    if (record->event.pressed) {
      set_unicode_input_mode(UNICODE_MODE_MACOS);
    }
    return false;

  // macros for umlauts (needs to be a macro, so we can capitalise it)
  case UC_AE:
  case UC_OE:
  case UC_UE:
    if (record->event.pressed)
    {
      uint8_t upper = get_mods() & MOD_MASK_SHIFT;
      unicode_input_start();
      register_hex(get_unicode_hex_for_keypress(upper, keycode));
      unicode_input_finish();
    }
    return false;
  case SONG_MARCH:
    return false;
  case SONG_ALL_STAR:
    return false;
  case MACRO_RST:
    if (record->event.pressed)
    {
      SEND_STRING(SS_DOWN(X_RALT));
      SEND_STRING(SS_TAP(X_ENTER));
      SEND_STRING(SS_UP(X_RALT));
      SEND_STRING(SS_DELAY(1000)"r"SS_DELAY(300));
      SEND_STRING(SS_DOWN(X_RALT));
      SEND_STRING(SS_TAP(X_ENTER));
      SEND_STRING(SS_UP(X_RALT));
    }
    return false;
  }
  return true;
}

bool music_mask_user(uint16_t keycode)
{
  switch (keycode)
  {
  case RAISE:
  case LOWER:
    return false;
  default:
    return true;
  }
}

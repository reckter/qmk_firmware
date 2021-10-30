/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
//  * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


#include QMK_KEYBOARD_H
#include "muse.h"
#include "process_unicode_common.h"
#include "action_layer.h"
#include "keymap_german.h"

#ifdef VELOCIKEY_ENABLE
#include "velocikey.h"
#else
#define VLK_TOG KC_NO
#endif
// songs

//float unicode_linux[][2] = SONG(UNICODE_LINUX);
//float unicode_windows[][2] = SONG(UNICODE_WINDOWS);
//float unicode_mac[][2] = SONG(NUMBER_ONE);
//float imperial_march[][2] = SONG(IMPERIAL_MARCH);
//float all_star[][2] = SONG(ALL_STAR);
//

extern keymap_config_t keymap_config;

enum planck_layers
{
  _QWERTY,
  _DVORAK,
  _GAMING,

  _LOWER,
  _RAISE,
  _SUPER,
  _SHORTCUTS,
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

  //songs
  SONG_MARCH,
  SONG_ALL_STAR,

  // dynamic macros; this needs to be at the end of the keycode enum
  DYNAMIC_MACRO_RANGE,
};

// needs to be below the keycode table apparently
#include "dynamic_macro.h"

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SUPER MO(_SUPER)
#define UMLAUT MO(_UMLAUT)

#define UC_EUR UC(0x20AC)
#define UE_SZ UC(0x00DF)


void matrix_init_user()
{
  set_unicode_input_mode(UC_OSX);
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
//  rgb_matrix_set_color(code, 0, 0, 0);
}

void dissable_leds(int leds[], int length)
{
  for (int i = 0; i < length; i++)
  {
    disable_led(leds[i]);
  }
}

void rgb_matrix_indicators_user(void)
{
//  rgb_matrix_set_color(42, middle_led_r, middle_led_g, middle_led_b);

#ifdef VELOCIKEY_ENABLE
  if (velocikey_enabled()) {
      uint8_t rows = ((36 - velocikey_match_speed(0, 36)) / 3);
      for (uint8_t i = rows + 1 ; i < 12; i++) {
        disable_led(i);
        disable_led(i + 12);
        disable_led(i + 2 * 12);
      }
      uint8_t extra_keys = ((36 - velocikey_match_speed(0, 36)) % 3);
      for (uint8_t i = extra_keys; i <= 2; i++) {
          disable_led(rows + i * 12);
      }
  }
  #endif
/*
  uint8_t new_layer = biton32(layer_state);
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

    rgb_matrix_set_color(42, 0, 255, 0);
    break;
  case _GAMING:

    disable_led(3);
    disable_led(14);
    disable_led(15);
    disable_led(16);

    rgb_matrix_set_color(42, 0, 0, 100);
  }
  */
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* GAMING
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   1  |  Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O   | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   2  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   3  |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
    [_GAMING] = LAYOUT_gergo(
        KC_TAB, KC_1, KC_Q, KC_W, KC_E, KC_R,                                            KC_T, KC_Y, KC_U, KC_I, KC_O, KC_BSPC, \
        KC_ESC, KC_2, KC_A, KC_S, KC_D, KC_F,  _______,                         _______, KC_G, KC_H, KC_J, KC_K, KC_L, TG(_SETTING), \
        KC_LSFT, KC_3, KC_Z, KC_X, KC_C, KC_V, _______, _______,       _______, _______, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_ENT, \
              KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, RAISE, KC_LEFT, KC_RGHT \
        ),

/* QWERTY
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
    [_QWERTY] = LAYOUT_gergo(
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                             KC_Y,  KC_U, KC_I, KC_O, KC_P, KC_BSPC, \
        KC_ESC, KC_A, KC_S, KC_D, KC_F, KC_G, _______,                           _______, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, \
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, _______, _______,        _______, _______, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, \
                        KC_LALT, KC_LGUI, LOWER, KC_LSFT, KC_SPC, RAISE, KC_LEFT, _______),

    /* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |    Space    |Raise |Umlaut| Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
    [_DVORAK] = LAYOUT_gergo(
        KC_TAB, KC_QUOT,    KC_COMM,    KC_DOT, KC_P, KC_Y,                                     KC_F, KC_G, KC_C, KC_R, KC_L, KC_BSPC, \
        KC_ESC, KC_A,       KC_O,       KC_E,   KC_U, KC_I, _______,                     _______, KC_D, KC_H, KC_T, KC_N, KC_S, LT(_UMLAUT, KC_SLSH), \
        SUPER,  KC_SCLN,    KC_Q,       KC_J,   KC_K, KC_X, KC_LCTL, HYPR(KC_P),   _______, _______, KC_B, KC_M, KC_W, KC_V, KC_Z, KC_ENT, \
                                        KC_LGUI, KC_LSFT, LOWER, KC_LALT,       KC_LCTL, RAISE, KC_SPC, KC_LCTL ),
//        MO(_SHORTCUTS), KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_LSFT, KC_SPC, RAISE, UMLAUT, KC_DOWN, KC_UP, KC_RGHT),

    /* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |TS_spk|   1  |   2  |   3  |   %  |   ^  |   {  |   }  |   *  |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |   4  |   5  |   6  |   0  |   =  |   (  |   )  |   +  |   -  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |   7  |   8  |   9  |1pwFIl|      |   §  |  `   | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |   0  |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
    [_LOWER] = LAYOUT_gergo(
            KC_TILD,    HYPR(KC_T), KC_1,    KC_2, KC_3,    KC_PERC,                                       KC_CIRC, KC_LCBR,   KC_RCBR,    KC_ASTR, _______, KC_BSPC, \
            KC_DEL,     _______,    KC_4,    KC_5, KC_6,    KC_0,       _______,                  _______, KC_EQL,  KC_LPRN,   KC_RPRN,    KC_PLUS, KC_MINS, KC_PIPE, \
            _______,    _______,    KC_7,    KC_8, KC_9,    HYPR(KC_P), _______, _______, _______, _______, _______, S(KC_GRV), S(KC_NUBS), KC_HOME, KC_END,  _______, \
                _______, _______,    _______, _______,   KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY),

    /* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |rec d1|rec d2|endRec|      |      |      |   [  |   ]  |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |      |  &   |  $   |  €   |      |      |   !  |   }  |   ]  |   -  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   ±  |   ~  |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
    [_RAISE] = LAYOUT_gergo(
                KC_GRV, DYN_REC_START1, DYN_REC_START2, DYN_REC_STOP, _______, _______,                                           _______, KC_LBRC, KC_RBRC, _______, _______, KC_BSPC, \
                KC_DEL, _______,  KC_AMPR,  KC_DLR,  UC_EUR, _______, _______,                                           _______, _______, KC_EXLM, KC_AT,   KC_HASH, KC_UNDS, KC_BSLS, \
                _______,  DYN_MACRO_PLAY1, DYN_MACRO_PLAY2, _______, _______, _______, _______, _______,       _______,  _______, _______, KC_GRV,  KC_NUBS, KC_PGUP, KC_PGDN, _______, \
                _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY),

    /* Umlauts
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  ä   |  ö   |      |  ü   |      |      |      |      |      |  ß   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
/*    [_UMLAUT] = LAYOUT_gergo(
//            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//        _______, UC_AE, UC_OE, _______, UC_UE, _______, _______, _______, _______, _______, UE_SZ, _______, \
//        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
//
*/
    /* Super
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F5  |  F6  |  F7  |  F8  | ctrl |      | Left | Down |  Up  |Right |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |  alt | gui  | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
    [_SUPER] = LAYOUT_gergo(
        KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, _______,                                                _______, TO(_MOUSE), TO(_SETTING), _______, _______, KC_BSPC, \
        KC_DEL, KC_F5, KC_F6, KC_F7, KC_F8, KC_LCTL, _______,                              _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_BSLS, \
        _______, KC_F9, KC_F10, KC_F11, KC_F12, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______, _______, \
         _______, _______, _______,  KC_LALT, KC_LGUI, _______,  _______, _______),

    /* Super
 * ,-----------------------------------------------------------------------------------.
 * |   `  |  F1  |  F2  |  F3  |  F4  |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F5  |  F6  |  F7  |  F8  | ctrl |      | Left | Down |  Up  |Right |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F9  |  F10 |  F11 |  F12 |      |      |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |  alt | gui  | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
/*    [_SHORTCUTS] = LAYOUT_gergo(
//            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//            _______, _______, _______, _______, _______, _______, _______, LALT(KC_H), LALT(KC_J), LALT(KC_K), LALT(KC_L), _______, \
//            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),
*/
    /* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+--A----+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
    [_ADJUST] = LAYOUT_gergo(
        _______, RESET, DEBUG, RGB_TOG, RGB_MOD, RGB_HUI,                                              RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD, KC_DEL, \
        _______, _______, MU_MOD, AU_ON, AU_OFF, AG_NORM, _______,                             _______, AG_SWAP, QWERTY, XXXXXXX, DVORAK, XXXXXXX, _______, \
        _______, MUV_DE, MUV_IN, MU_ON,  MU_OFF,  MI_ON,    MI_OFF, _______,     _______, _______, TERM_ON, TERM_OFF,  _______, _______, _______, \
        _______, _______, _______, _______, _______, _______, _______, _______,  ),

    /* Mouse
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |Sright|S up  |S down|S left|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | exit |      |      |M btn2|M btn1|      |      |Mright|M up  |M down|M left|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
/*    [_MOUSE] = LAYOUT_gergo(
//      _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
//      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, XXXXXXX, \
//      TG(_MOUSE), XXXXXXX, XXXXXXX, KC_MS_BTN2, KC_MS_BTN1, XXXXXXX, XXXXXXX, KC_MS_LEFT, KC_MS_DOWN, KC_MS_UP, KC_MS_RIGHT, XXXXXXX, \
//      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
//      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX ),
*/
    /* Setting
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |Sright|S up  |S down|S left|      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | exit |      |      |M btn2|M btn1|      |      |Mright|M up  |M down|M left|      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
    [_SETTING] = LAYOUT_gergo(
          XXXXXXX,      OS_LIN,     OS_MAC,  OS_WIN, VLK_TOG, TG(_GAMING),                                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
          TG(_SETTING), SONG_MARCH, SONG_ALL_STAR, XXXXXXX, XXXXXXX, _______,                                 _______,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
          XXXXXXX,      RGB_MODE_RAINBOW,    RGB_MODE_BREATHE, RGB_MODE_SWIRL, RGB_MODE_SNAKE, RGB_MODE_KNIGHT, _______,  _______,     _______,  _______,XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

};

#ifdef AUDIO_ENABLE
float plover_song[][2] = SONG(PLOVER_SOUND);
float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
#endif

uint32_t layer_state_set_user(uint32_t state)
{
  uint32_t new_layer = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  return new_layer;
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
      break;
    case UC_OE:
      return 0x00d6;
      break;
    case UC_UE:
      return 0x00dc;
      break;
    }
  }
  else
  {
    switch (keycode)
    {
    case UC_AE:
      return 0x00e4;
      break;
    case UC_OE:
      return 0x00f6;
      break;
    case UC_UE:
      return 0x00fc;
      break;
    }
  }
  return 0;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
  if (!process_record_dynamic_macro(keycode, record))
  {
    return false;
  }
  switch (keycode)
  {
  case QWERTY:
    if (record->event.pressed)
    {
      print("mode just switched to qwerty and this is a huge string\n");
      set_single_persistent_default_layer(_QWERTY);
      set_middle_led(255, 0, 0);
    }
    return false;
    break;
  case DVORAK:
    if (record->event.pressed)
    {
      set_single_persistent_default_layer(_DVORAK);
      set_middle_led(0, 0, 0);
    }
    return false;
    break;
  case BACKLIT:
    if (record->event.pressed)
    {
      register_code(KC_RSFT);
#ifdef BACKLIGHT_ENABLE
      backlight_step();
#endif
#ifdef KEYBOARD_planck_rev5
      PORTE &= ~(1 << 6);
#endif
    }
    else
    {
      unregister_code(KC_RSFT);
#ifdef KEYBOARD_planck_rev5
      PORTE |= (1 << 6);
#endif
    }
    return false;
    break;

    // switch unicode input mode
  case OS_LIN:
    set_unicode_input_mode(UC_LNX);
#ifdef AUDIO_ENABLE
    PLAY_SONG(unicode_linux);
#endif
    return false;
    break;
  case OS_WIN:
    set_unicode_input_mode(UC_WIN);
#ifdef AUDIO_ENABLE
    PLAY_SONG(unicode_windows);
#endif
    return false;
    break;
  case OS_MAC:
    set_unicode_input_mode(UC_OSX);
#ifdef AUDIO_ENABLE
    PLAY_SONG(unicode_mac);
#endif
    return false;
    break;

    // macros for umlauts (needs to be a macro, so we can capitalise it)
  case UC_AE:
  case UC_OE:
  case UC_UE:
    if (record->event.pressed)
    {
      uint8_t upper = keyboard_report->mods & MOD_BIT(KC_LSFT);
      unicode_input_start();
      register_hex(get_unicode_hex_for_keypress(upper, keycode));
      unicode_input_finish();
    }
    return false;
    break;
  case SONG_MARCH:
#ifdef AUDIO_ENABLE
    PLAY_SONG(imperial_march);
#endif
    return false;
    break;
  case SONG_ALL_STAR:
#ifdef AUDIO_ENABLE
    PLAY_SONG(all_star);
#endif
    return false;
    break;
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

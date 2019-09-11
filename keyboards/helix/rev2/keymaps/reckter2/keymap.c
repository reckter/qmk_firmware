#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
#include "lufa.h"
#include "split_util.h"
#endif
#ifdef AUDIO_ENABLE
  #include "audio.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

enum layer_number
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

enum custom_keycodes
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

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#include "dynamic_macro.h"

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SUPER MO(_SUPER)
#define UMLAUT MO(_UMLAUT)
#define KC_LEAD KC_NO
#define VLK_TOG KC_NO

#define UC_EUR UC(0x20AC)
#define UE_SZ UC(0x00DF)

#define LEADER_TIMEOUT 300
// LEADER_EXTERNS();

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO
//Macros

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
    [_GAMING] = LAYOUT( \
        KC_TAB,  KC_1,    KC_Q,    KC_W,    KC_E,  KC_R,   KC_T,                   KC_Y,  KC_U,    KC_I,    KC_O,   KC_BSPC, \
        KC_ESC,  KC_2,    KC_A,    KC_S,    KC_D,  KC_F,   KC_G,                   KC_H,  KC_J,    KC_K,    KC_L,   TG(_SETTING), \
        KC_LSFT, KC_3,    KC_Z,    KC_X,    KC_C,  KC_V,   KC_B,                   KC_N,  KC_M,    KC_COMM, KC_DOT, KC_ENT, \
        KC_LEAD, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT),

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
    [_QWERTY] = LAYOUT( \
        KC_TAB,  KC_Q,   KC_W,     KC_E,    KC_R,  KC_T,                   KC_Y,   KC_U,  KC_I,    KC_O,    KC_P,    KC_BSPC, \
        KC_ESC,  KC_A,   KC_S,     KC_D,    KC_F,  KC_G,                   KC_H,   KC_J,  KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
        KC_LSFT, KC_Z,   KC_X,     KC_C,    KC_V,  KC_B,                   KC_N,   KC_M,  KC_COMM, KC_DOT,  KC_SLSH, KC_ENT, \
        KC_LEAD, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_SPC, KC_SPC, KC_SPC, KC_SPC, RAISE, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT),

    /* Dvorak
 * ,-----------------------------------------.             ,-----------------------------------------.
 * | Tab  |   "  |   ,  |   .  |   P  |   Y  |             |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |             |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |             |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * | Brite| Ctrl | Alt  | GUI  |Lower |shift |umlaut|shift | Space|Raise |Umlaut| Down |  Up  |Right |
 * `-------------------------------------------------------------------------------------------------'
 */
    [_DVORAK] = LAYOUT( \
                  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,  KC_Y,                     KC_F,   KC_G,  KC_C,   KC_R,    KC_L,  KC_BSPC, \
                 KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,  KC_I,                     KC_D,   KC_H,  KC_T,   KC_N,    KC_S,  KC_SLSH, \
                 SUPER,   KC_SCLN, KC_Q,    KC_J,    KC_K,  KC_X,                     KC_B,   KC_M,  KC_W,   KC_V,    KC_Z,  KC_ENT, \
                 KC_LEAD, KC_LCTL, KC_LALT, KC_LGUI, LOWER, KC_LSFT, UMLAUT, KC_LSFT, KC_SPC, RAISE, UMLAUT, KC_DOWN, KC_UP, KC_RGHT),

    /* Lower
 * ,-----------------------------------------.             ,-----------------------------------------.
 * |   ~  |TS_spk|   1  |   2  |   3  |   %  |             |   ^  |   &  |   *  |      |      | Bksp |
 * |------+------+------+------+------+------|             |-----+------+------+------+------+------|
 * | Del  |      |   4  |   5  |   6  |   0  |             |   $  |   !  |   @  |   #  |   _  |  |   |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |      |   7  |   8  |   9  |1pwFil|             |      |ISO ~ |ISO | | Home | End  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |   0  |      |      |      \      |      |      | Next | Vol- | Vol+ | Play |
 * `-------------------------------------------------------------------------------------------------'
 */
    [_LOWER] = LAYOUT( \
              KC_TILD, HYPR(KC_T), KC_1,    KC_2, KC_3,    KC_PERC,                         KC_CIRC, KC_LCBR,   KC_RCBR,    KC_ASTR, _______, KC_BSPC, \
              KC_DEL,    _______,    KC_4,    KC_5, KC_6,    KC_0,                            KC_EQL,  KC_LPRN,   KC_RPRN,    KC_PLUS, KC_MINS, KC_PIPE, \
              _______,   _______,    KC_7,    KC_8, KC_9,    HYPR(KC_P),                      _______, S(KC_GRV), S(KC_NUBS), KC_HOME, KC_END,  _______, \
              _______,   _______,    _______, KC_0, _______, _______,    _______, _______,    _______, _______,   KC_MNXT,    KC_VOLD, KC_VOLU, KC_MPLY),

    /* Raise
 * ,-----------------------------------------.             ,-----------------------------------------.
 * |   `  |rec d1|rec d2|endRec|  €   |      |             |      |playd1|playd2|      |      | Bksp |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * | Del  |      |  [   |  {   |  (   |  +   |             |  =   |   )  |   }  |   ]  |   -  |  \   |
 * |------+------+------+------+------+------|             |------+------+------+------+------+------|
 * |      |      |      |      |      |      |             |      |ISO # |ISO / |Pg Up |Pg Dn |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
 * `-------------------------------------------------------------------------------------------------'
 */
    [_RAISE] = LAYOUT( \
                KC_GRV,   DYN_REC_START1,    DYN_REC_START2,   DYN_REC_STOP, _______, _______,                   _______, KC_LBRC, KC_RBRC, _______, _______, KC_BSPC, \
                KC_DEL,   _______,           KC_AMPR,          KC_DLR,       UC_EUR,  _______,                   _______, KC_EXLM, KC_AT,   KC_HASH, KC_UNDS, KC_BSLS, \
                _______,  DYN_MACRO_PLAY1,   DYN_MACRO_PLAY2,  _______,      _______, _______,                   _______, KC_GRV,  KC_NUBS, KC_PGUP, KC_PGDN, _______, \
                _______, _______,            _______,          _______,      _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY),

    /* Umlauts
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+----- --------+------+------+------+------+------|
 * |      |  ä   |  ö   |      |  ü   |      |      |      |      |      |  ß   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
    [_UMLAUT] = LAYOUT( \
                   _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
                  _______, UC_AE,   UC_OE,   _______, UC_UE,   _______,                   _______, _______, _______, _______, UE_SZ,   _______, \
                  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
                  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______),

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
    [_SUPER] = LAYOUT( \
                KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   _______,                   _______, TO(_MOUSE), TO(_SETTING), _______, _______, KC_BSPC, \
                KC_DEL,  KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_LCTL,                   _______, KC_LEFT,    KC_DOWN,      KC_UP,   KC_RGHT, KC_BSLS, \
                _______, KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,                   _______, _______,    _______,      _______, _______, _______, \
                _______, _______, _______, _______, _______, _______, _______, _______, KC_LALT, KC_LGUI,    _______,      _______, _______, _______),

    /* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      | Reset|      |      |      |      |      |      |      |      |      |  Del |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|AGswap|Qwerty|      |Dvorak|      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |Voice-|Voice+|Mus on|Musoff|MIDIon|MIDIof|      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
    [_ADJUST] = LAYOUT( \
                  _______, RESET,  DEBUG,   RGB_TOG, RGB_MOD, RGB_HUI,                   RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI,  RGB_VAD, KC_DEL, \
                 _______, _______, MU_MOD,  AU_ON,   AU_OFF,  AG_NORM,                   AG_SWAP, QWERTY,  XXXXXXX, DVORAK,   XXXXXXX, _______, \
                 _______, MUV_DE,  MUV_IN,  MU_ON,   MU_OFF,  MI_ON,                     MI_OFF,  TERM_ON, TERM_OFF, _______, _______, _______, \
                 _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______),

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
    [_MOUSE] = LAYOUT( \
      XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,                   XXXXXXX, KC_MS_WH_LEFT, KC_MS_WH_DOWN, KC_MS_WH_UP, KC_MS_WH_RIGHT, XXXXXXX, \
      TG(_MOUSE), XXXXXXX, XXXXXXX, KC_MS_BTN2, KC_MS_BTN1, XXXXXXX,                   XXXXXXX, KC_MS_LEFT,    KC_MS_DOWN,    KC_MS_UP,    KC_MS_RIGHT,    XXXXXXX, \
      XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX,                   XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX, \
      XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX,       XXXXXXX,     XXXXXXX,        XXXXXXX),

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
 *
 *
 */
    [_SETTING] = LAYOUT( \
                  XXXXXXX,      OS_LIN,              OS_MAC,           OS_WIN,         VLK_TOG,        TG(_GAMING),                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                  TG(_SETTING), SONG_MARCH,          SONG_ALL_STAR,    XXXXXXX,        XXXXXXX,        XXXXXXX,                           XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                  XXXXXXX,      RGB_MODE_RAINBOW,    RGB_MODE_BREATHE, RGB_MODE_SWIRL, RGB_MODE_SNAKE, RGB_MODE_KNIGHT,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
                  XXXXXXX,      XXXXXXX,             XXXXXXX,          XXXXXXX,        XXXXXXX,        XXXXXXX,         XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX),

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_plover[][2]     = SONG(PLOVER_SOUND);
float tone_plover_gb[][2]  = SONG(PLOVER_GOODBYE_SOUND);
float music_scale[][2]     = SONG(MUSIC_SCALE_SOUND);
#endif

// define variables for reactive RGB
bool TOG_STATUS = false;
int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    #ifdef RGBLIGHT_ENABLE
      //rgblight_mode(RGB_current_mode);
    #endif
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
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


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_qwerty);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_SONG(tone_dvorak);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
          //not sure how to have keyboard check mode and set it to a variable, so my work around
          //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            //rgblight_mode(RGBLIGHT_MODE_SNAKE + 1);
          #endif
        }
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
        //   rgblight_mode(RGB_current_mode);   // revert RGB to initial mode prior to RGB mode change
        #endif
        TOG_STATUS = false;
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        //not sure how to have keyboard check mode and set it to a variable, so my work around
        //uses another variable that would be set to true after the first time a reactive key is pressed.
        if (TOG_STATUS) { //TOG_STATUS checks is another reactive key currently pressed, only changes RGB mode if returns false
        } else {
          TOG_STATUS = !TOG_STATUS;
          #ifdef RGBLIGHT_ENABLE
            // rgblight_mode(RGBLIGHT_MODE_SNAKE);
          #endif
        }
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        #ifdef RGBLIGHT_ENABLE
        //   rgblight_mode(RGB_current_mode);  // revert RGB to initial mode prior to RGB mode change
        #endif
        layer_off(_RAISE);
        TOG_STATUS = false;
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
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
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
  }
  return true;
}

void matrix_init_user(void) {
    #ifdef AUDIO_ENABLE
        startup_user();
    #endif
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}


#ifdef AUDIO_ENABLE

void startup_user()
{
    _delay_ms(20); // gets rid of tick
}

void shutdown_user()
{
    _delay_ms(150);
    stop_all_notes();
}

void music_on_user(void)
{
    music_scale_user();
}

void music_scale_user(void)
{
    PLAY_SONG(music_scale);
}

#endif


//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// hook point for 'led_test' keymap
//   'default' keymap's led_test_init() is empty function, do nothing
//   'led_test' keymap's led_test_init() force rgblight_mode_noeeprom(RGBLIGHT_MODE_RGB_TEST);
__attribute__ ((weak))
void led_test_init(void) {}

void matrix_scan_user(void) {
     led_test_init();
     iota_gfx_task();  // this is what updates the display continuously
}

void matrix_update(struct CharacterMatrix *dest,
                          const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

//assign the right code to your layers for OLED display
#define L_BASE 0
#define L_LOWER (1<<_LOWER)
#define L_RAISE (1<<_RAISE)
#define L_ADJUST (1<<_ADJUST)
#define L_ADJUST_TRI (L_ADJUST|L_RAISE|L_LOWER)

static void render_logo(struct CharacterMatrix *matrix) {

  static char logo[]={
    0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
    0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
    0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,
    0};
  matrix_write(matrix, logo);
  //matrix_write_P(&matrix, PSTR(" Split keyboard kit"));
}



void render_status(struct CharacterMatrix *matrix) {

  // Render to mode icon
  static char logo[][2][3]={{{0x95,0x96,0},{0xb5,0xb6,0}},{{0x97,0x98,0},{0xb7,0xb8,0}}};
  if(keymap_config.swap_lalt_lgui==false){
    matrix_write(matrix, logo[0][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[0][1]);
  }else{
    matrix_write(matrix, logo[1][0]);
    matrix_write_P(matrix, PSTR("\n"));
    matrix_write(matrix, logo[1][1]);
  }

  // Define layers here, Have not worked out how to have text displayed for each layer. Copy down the number you see and add a case for it below
  char buf[40];
  snprintf(buf,sizeof(buf), "Undef-%ld", layer_state);
  matrix_write_P(matrix, PSTR("\nLayer: "));
    switch (layer_state ) {
        case L_BASE:
           matrix_write_P(matrix, PSTR("Default"));
           break;
        case L_RAISE:
           matrix_write_P(matrix, PSTR("Raise"));
           break;
        case L_LOWER:
           matrix_write_P(matrix, PSTR("Lower"));
           break;
        case L_ADJUST:
        case L_ADJUST_TRI:
           matrix_write_P(matrix, PSTR("Adjust"));
           break;
        case 256:
           matrix_write_P(matrix, PSTR("Mouse"));
          break;
        case 32:
           matrix_write_P(matrix, PSTR("F + move"));
          break;
        case 512:
           matrix_write_P(matrix, PSTR("Settings"));
          break;
        case 64:
           matrix_write_P(matrix, PSTR("Umlaut"));
           break;
        case 4:
           matrix_write_P(matrix, PSTR("Gaming"));
           break;
        case 516:
           matrix_write_P(matrix, PSTR("Setting - Gaming"));
           break;
        default:
           matrix_write(matrix, buf);
    }

  // Host Keyboard LED Status
  char led[40];
    snprintf(led, sizeof(led), "\n%s  %s  %s",
            (host_keyboard_leds() & (1<<USB_LED_NUM_LOCK)) ? "NUMLOCK" : "       ",
            (host_keyboard_leds() & (1<<USB_LED_CAPS_LOCK)) ? "CAPS" : "    ",
            (host_keyboard_leds() & (1<<USB_LED_SCROLL_LOCK)) ? "SCLK" : "    ");
  matrix_write(matrix, led);
}


void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;

#if DEBUG_TO_SCREEN
  if (debug_enable) {
    return;
  }
#endif

  matrix_clear(&matrix);
  if(is_master){
    render_status(&matrix);
  }else{
    render_logo(&matrix);
  }
  matrix_update(&display, &matrix);
}

#endif

/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

// clang-format off

enum layers{
    DVOR,
    QWER,
    NUMS,
    ARWS,
    BOOT,
    WIN_BASE,
    WIN_FN
};

#define KC_TASK LGUI(KC_TAB)
#define KC_FLXP LGUI(KC_E)
#define KC_DESL LCTL(KC_LEFT)
#define KC_DESR LCTL(KC_RGHT)
#define GRAVE_MODS  (MOD_BIT(KC_LSFT)|MOD_BIT(KC_RSFT)|MOD_BIT(KC_LGUI)|MOD_BIT(KC_RGUI)|MOD_BIT(KC_LALT)|MOD_BIT(KC_RALT))
#define TG_NUM_LOCK (TG(NUMS))
#define TG_QWER (TG(QWER))

bool num_lock_active = false; // flag to indicate whether the layer is active
bool qwer_active = false;
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TG_NUM_LOCK:
            if (record->event.pressed) {
                num_lock_active = !num_lock_active; // toggle the flag
            }
            break;
        case TG_QWER:
            if (record->event.pressed) {
                qwer_active = !qwer_active; // toggle the flag
            }
            break;
    }
    return true;
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (host_keyboard_led_state().caps_lock) {
        RGB_MATRIX_INDICATOR_SET_COLOR(78, 220, 14, 0); // assuming caps lock is at led #5
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(78, 0, 0, 0);
    }
    if (num_lock_active) {
        RGB_MATRIX_INDICATOR_SET_COLOR(11, 220, 14, 0); // assuming layer indicator is at led #6
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(11, 0, 0, 0);
    }
    if (qwer_active) {
        RGB_MATRIX_INDICATOR_SET_COLOR(14, 14, 168, 0); // assuming layer indicator is at led #6
    } else {
        RGB_MATRIX_INDICATOR_SET_COLOR(14, 0, 0, 0);
    }
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DVOR] = LAYOUT_ansi_89(
        KC_MUTE,  LT(BOOT, KC_ESC),   KC_BRID,  KC_BRIU,  _______,  _______,  _______,   _______,  _______,  _______,  KC_DESL,  KC_DESR,  TG_NUM_LOCK, _______, _______, TG_QWER,
        KC_MPLY,  KC_DLR,   KC_AMPR,  KC_LBRC,  KC_LCBR,  KC_RCBR,  KC_LPRN,   KC_EQL,   KC_ASTR,  KC_RPRN,  KC_PLUS,  KC_RBRC,  KC_EXLM,  KC_HASH,  KC_BSPC,            KC_DEL,
        LCMD(KC_P), KC_TAB, KC_SCLN,  KC_COMM,  KC_DOT,   KC_P,     KC_Y,      KC_F,     KC_G,     KC_C,     KC_R,     KC_L,     KC_SLSH,  KC_AT,    KC_BSLS,            KC_PGUP,
        _______,  KC_LOPT,  KC_A,     KC_O,     KC_E,     KC_U,     KC_I,      KC_D,     KC_H,     KC_T,     KC_N,     KC_S,     KC_MINS,            KC_ENT,             KC_PGDN,
        _______,  KC_LSFT,  KC_QUOT,  KC_Q,     KC_J,     KC_K,     KC_X, KC_X, KC_B,    KC_M,     KC_W,     KC_V,     KC_Z,            KC_RSFT,               KC_UP,
        _______,  KC_CAPS,  KC_LCTL,            KC_LOPT,  KC_LCMD,   KC_SPC,   LT(ARWS, KC_SPC),  KC_RCMD,                                           KC_LEFT,  KC_DOWN,  KC_RGHT),

    [QWER] = LAYOUT_ansi_89(
        KC_MUTE,  LT(BOOT, KC_ESC),   KC_BRID,  KC_BRIU,  _______,  _______,  _______,   _______,  _______,  _______,  KC_DESL,  KC_DESR,  KC_NO,    _______,  _______,  _______,
        KC_MPLY,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_DEL,
        LCMD(KC_P), KC_TAB, KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGUP,
        _______,  KC_LOPT,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_PGDN,
        _______,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
        _______,  KC_CAPS,  KC_LCTL,            KC_LOPT,  KC_LCMD,  KC_SPC,                        KC_SPC,             KC_RCMD,                      KC_LEFT,  KC_DOWN,  KC_RGHT),
    
    [NUMS] = LAYOUT_ansi_89(
        _______,  _______,            _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______, _______,
        _______,  _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______, _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    [ARWS] = LAYOUT_ansi_89(
        _______,  _______,            _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  KC_UP,  _______,  _______,  _______,  _______,  _______,            RGB_MOD,
        _______,  _______,  _______, _______,  _______,  _______,  _______,   _______,  KC_LEFT,  KC_DOWN,  KC_RGHT,  _______,  _______,            _______,            RGB_RMOD,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  RGB_VAI,
        _______,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      RGB_HUD,  RGB_VAD,  RGB_HUI),

    [BOOT] = LAYOUT_ansi_89(
        _______,  _______,            _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  QK_BOOT,  _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,  _______,  _______, _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    // [] = LAYOUT_ansi_89(
    //     _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    //     _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    //     _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,            _______,
    //     _______,  _______,  _______, _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,            _______,            _______,
    //     _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    //     _______,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                      _______,  _______,  _______),

    [WIN_BASE] = LAYOUT_ansi_89(
        KC_MUTE,  KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,     KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_INS,             KC_DEL,
        _______,  KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,      KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,            KC_PGUP,
        _______,  KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,            KC_PGDN,
        _______,  KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,      KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,             KC_HOME,
        _______,  KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,      KC_B,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,
        _______,  KC_LCTL,  KC_LWIN,            KC_LALT,  KC_SPC,  MO(WIN_FN),                     KC_SPC,             KC_RALT,                      KC_LEFT,  KC_DOWN,  KC_RGHT),

    [WIN_FN] = LAYOUT_ansi_89(
        RGB_TOG,  _______,  KC_BRID,  KC_BRIU,  KC_TASK,  KC_FLXP,  RGB_VAD,   RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,   KC_VOLU,  _______,            _______,
        _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,  RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,   _______,  _______,  _______,  _______,  _______,  _______,   _______,  _______,            _______,
        _______,  _______,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,   _______,  _______,  _______,  _______,  _______,  _______,             _______,            _______,
        _______,  _______,            _______,  _______,  _______,  _______,   _______,  _______,  NK_TOGG,  _______,  _______,  _______,   _______,  _______,  _______,
        _______,  _______,  _______,            _______,  _______,  _______,                       _______,            _______,                       _______,  _______,  _______),
};


const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t dollar_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_DLR, KC_TILD);
const key_override_t one_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_AMPR, KC_1);
const key_override_t two_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LBRC, KC_2);
const key_override_t three_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LCBR, KC_3);
const key_override_t four_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_RCBR, KC_4);
const key_override_t five_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_LPRN, KC_5);
const key_override_t six_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_EQL, KC_6);
const key_override_t seven_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_ASTR, KC_7);
const key_override_t eight_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_RPRN, KC_8);
const key_override_t nine_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_PLUS, KC_9);
const key_override_t zero_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_RBRC, KC_0);
const key_override_t exclm_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_EXLM, KC_PERC);
const key_override_t hash_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_HASH, KC_GRV);
// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&delete_key_override,
    &dollar_key_override,
    &one_key_override,
    &two_key_override,
    &three_key_override,
    &four_key_override,
    &five_key_override,
    &six_key_override,
    &seven_key_override,
    &eight_key_override,
    &nine_key_override,
    &zero_key_override,
    &exclm_key_override,
    &hash_key_override,
	NULL // Null terminate the array of overrides!
};

#if defined(ENCODER_ENABLE) && defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][1][2] = {
    [DVOR]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [QWER] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [NUMS]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [ARWS]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [BOOT]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },
    [WIN_BASE] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [WIN_FN]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) }
};
#endif // ENCODER_MAP_ENABLE

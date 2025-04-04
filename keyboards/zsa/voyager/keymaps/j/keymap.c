// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// qmk compile -kb zsa/voyager -km j
// press bootloader button on keyboard
// qmk flash -kb zsa/voyager -km j


/*
    (
        _______,     _______,       _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,     _______,       _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,     _______,       _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,     _______,       _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,                        _______,        _______
    )
*/


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,            _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_Y,           KC_F,           KC_G,           _______,                        _______,            KC_C,           KC_R,           KC_L,           _______,        _______,
           KC_P,    KC_A,           KC_O,           KC_E,           KC_U,           KC_I,                           KC_D,               KC_H,           KC_T,           KC_N,           KC_S,           KC_Z,
          MO(2),    KC_Q,           KC_K,           KC_X,           KC_B,           _______,                        _______,            KC_M,           KC_W,           KC_V,           KC_J,           MO(1),
                                                                    LT(1,KC_ENT),   CTL_T(KC_TAB),                  SFT_T(KC_BSPC),     LT(2,KC_SPC)
    ),
    [1] = LAYOUT(
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_1,           KC_2,           KC_3,           _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_4,           KC_5,           KC_6,           KC_0,                           _______,        KC_HOME,        KC_UP,          KC_END,         _______,        _______,
        _______,    _______,        KC_7,           KC_8,           KC_9,           _______,                        _______,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       _______,        _______,
                                                                    _______,        _______,                        _______,        _______
    ),
    [2] = LAYOUT(
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        _______,        KC_DOT,         KC_COMM,        _______,                        _______,        KC_PLUS,        KC_MINUS,       KC_AT,          _______,        _______,
        _______,    _______,        KC_LPRN,        KC_RPRN,        KC_LCBR,        KC_RCBR,                        KC_EQL,         KC_ASTR,        KC_SLSH,        KC_PERC,        KC_DLR,         KC_TILD,
        _______,    _______,        KC_LBRC,        KC_RBRC,        KC_LT,          KC_GT,                          _______,        KC_AMPR,        KC_EXLM,        KC_HASH,        KC_QUES,        _______,
                                                                    _______,        _______,                        _______,        _______
    )

};


#define DIV 3
#define ADD 10

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {

    // ===========================
    // ===== Left keyboard =======
    // ===========================

    // Pinky Nodifiers
    rgb_matrix_set_color(18, 100 / DIV + ADD, 70 / DIV + ADD, 30 / DIV + ADD);

    // Pinky
    rgb_matrix_set_color(12, 170 / DIV + ADD, 170 / DIV + ADD, 50 / DIV + ADD);
    rgb_matrix_set_color(19, 170 / DIV + ADD, 170 / DIV + ADD, 50 / DIV + ADD);
    rgb_matrix_set_color(13, 170, 170, 50);

    // Ring
    rgb_matrix_set_color(8,  220 / DIV + ADD, 50 / DIV + ADD, 50 / DIV + ADD);
    rgb_matrix_set_color(14, 220, 50, 50);
    rgb_matrix_set_color(20, 220 / DIV + ADD, 50 / DIV + ADD, 50 / DIV + ADD);

    // Middle
    rgb_matrix_set_color(9,  50 / DIV + ADD, 50 / DIV + ADD, 220 / DIV + ADD);
    rgb_matrix_set_color(15, 50, 50, 220);
    rgb_matrix_set_color(21, 50 / DIV + ADD, 50 / DIV + ADD, 220 / DIV + ADD);

    // Index
    rgb_matrix_set_color(10,  200 / DIV + ADD, 90 / DIV + ADD, 160 / DIV + ADD);
    rgb_matrix_set_color(16,  200, 90, 160);
    rgb_matrix_set_color(17,  200 / DIV + ADD, 90 / DIV + ADD, 160 / DIV + ADD);
    rgb_matrix_set_color(22,  200 / DIV + ADD, 90 / DIV + ADD, 160 / DIV + ADD);

    // ===========================
    // ===== Right keyboard ======
    // ===========================

    // Index
    rgb_matrix_set_color(33,  200 / DIV + ADD, 90 / DIV + ADD, 160 / DIV + ADD);
    rgb_matrix_set_color(38,  200 / DIV + ADD, 90 / DIV + ADD, 160 / DIV + ADD);
    rgb_matrix_set_color(39,  200, 90, 160);
    rgb_matrix_set_color(45,  200 / DIV + ADD, 90 / DIV + ADD, 160 / DIV + ADD);

    // Middle
    rgb_matrix_set_color(34,  50 / DIV + ADD, 50 / DIV + ADD, 220 / DIV + ADD);
    rgb_matrix_set_color(40,  50, 50, 220);
    rgb_matrix_set_color(46,  50 / DIV + ADD, 50 / DIV + ADD, 220 / DIV + ADD);

    // Ring
    rgb_matrix_set_color(35,  220 / DIV + ADD, 50 / DIV + ADD, 50 / DIV + ADD);
    rgb_matrix_set_color(41,  220, 50, 50);
    rgb_matrix_set_color(47,  220 / DIV + ADD, 50 / DIV + ADD, 50 / DIV + ADD);

    // Pinky
    rgb_matrix_set_color(43,  170 / DIV + ADD, 170 / DIV + ADD, 50 / DIV + ADD);
    rgb_matrix_set_color(42,  170, 170, 50);
    rgb_matrix_set_color(48,  170 / DIV + ADD, 170 / DIV + ADD, 50 / DIV + ADD);

    // Pinky Nodifiers
    rgb_matrix_set_color(49, 100 / DIV + ADD, 70 / DIV + ADD, 30 / DIV + ADD);


    uint8_t active_layer = biton32(layer_state);
    if (active_layer == 0) {
        rgb_matrix_set_color(5, 0, 0, 0);
    } else if (active_layer == 1) {
        rgb_matrix_set_color(5, 200 / DIV + ADD, 100 / DIV + ADD, 100 / DIV + ADD);
    } else if (active_layer == 2) {
        rgb_matrix_set_color(5, 100 / DIV + ADD, 100 / DIV + ADD, 200 / DIV + ADD);
    }

    return true;
}
#endif
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#ifndef TAPPING_TERM
    #define TAPPING_TERM 200  // tune to taste
#endif

// qmk compile -kb zsa/voyager -km j
// press bootloader button on keyboard
// qmk flash -kb zsa/voyager -km j


// also edited: zsa/voyager/rules.mk

/*
    (
        _______,     _______,       _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,     _______,       _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,     _______,       _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,     _______,       _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,                        _______,        _______
    )
*/


// Homerow mods
#define HM_A LSFT_T(KC_A)  // Shift
#define HM_O LCTL_T(KC_O) // Ctrl
#define HM_E LALT_T(KC_E) // Alt / Option
#define HM_U LGUI_T(KC_U) // Command

#define HM_H RSFT_T(KC_H)
#define HM_T RCTL_T(KC_T)
#define HM_N RALT_T(KC_N) // Alt / Option
#define HM_S RGUI_T(KC_S)

// Toprow mods
// #define HM_Y LGUI_T(KC_Y) // Command
// #define HM_F LALT_T(KC_F) // Alt
// #define HM_G LCTL_T(KC_G) // Ctrl

// #define HM_C RCTL_T(KC_C)
// #define HM_R RALT_T(KC_R)
// #define HM_L RGUI_T(KC_L)


// Custom keycodes
enum custom_keycodes {
    Y_PARENS = SAFE_RANGE,  // tap: y, hold: ()
    F_BRACKS,               // tap: f, hold: []
    G_BRACES,               // tap: g, hold: {}
    DOT_COMMA,              // tap: ., hold: ,
    DASH_SLASH,             // tap: -, hold: /
};

// Per-key timers
static uint16_t y_timer = 0;
static uint16_t f_timer = 0;
static uint16_t g_timer = 0;
static uint16_t dot_timer = 0;
static uint16_t dash_timer = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case Y_PARENS:
            if (record->event.pressed) {
                y_timer = timer_read();
                return false; // we’ll decide what to send on release/hold
            } else {
                if (timer_elapsed(y_timer) < TAPPING_TERM) {
                    tap_code(KC_Y); // tap = letter
                } else {
                    // hold = ()
                    send_string("()" SS_TAP(X_LEFT));
                }
                return false;
            }
        case F_BRACKS:
            if (record->event.pressed) {
                f_timer = timer_read();
                return false;
            } else {
                if (timer_elapsed(f_timer) < TAPPING_TERM) {
                    tap_code(KC_F);
                } else {
                    send_string("[]" SS_TAP(X_LEFT));
                }
                return false;
            }
        case G_BRACES:
            if (record->event.pressed) {
                g_timer = timer_read();
                return false;
            } else {
                if (timer_elapsed(g_timer) < TAPPING_TERM) {
                    tap_code(KC_G);
                } else {
                    send_string("{}" SS_TAP(X_LEFT));
                }
                return false;
            }
        case DOT_COMMA:
            if (record->event.pressed) {
                dot_timer = timer_read();
                return false;
            } else {
                if (timer_elapsed(dot_timer) < TAPPING_TERM) {
                    tap_code(KC_DOT);    // short tap -> "."
                } else {
                    tap_code(KC_COMM);   // long hold -> ","
                }
                return false;
            }
        case DASH_SLASH:
            if (record->event.pressed) {
                dash_timer = timer_read();
                return false;
            } else {
                if (timer_elapsed(dash_timer) < TAPPING_TERM) {
                    tap_code(KC_MINS);   // short tap -> "-"
                } else {
                    tap_code(KC_SLSH);   // long hold -> "/"
                }
                return false;
            }
    }
    return true;
}




const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // ───────────────────────────── Base (0) ─────────────────────────────
    // Bottom row change: add MO(4) on left (extra left-hand layer), MO(3) on right.
    [0] = LAYOUT(
        UG_TOGG,    OSM(MOD_LSFT),  OSM(MOD_LCTL),  OSM(MOD_LALT),  OSM(MOD_LGUI),  KC_ENT,                         _______,            _______,        _______,        _______,        _______,        _______,
        KC_TAB,     KC_ESC,         Y_PARENS,       F_BRACKS,       G_BRACES,       DOT_COMMA,                      KC_Q,               KC_C,           KC_R,           KC_L,           _______,        _______,
        KC_P,       HM_A,           HM_O,           HM_E,           HM_U,           KC_I,                           KC_D,               HM_H,           HM_T,           HM_N,           HM_S,           KC_Z,
        MO(2),      MO(4),          KC_K,           KC_X,           KC_B,           DASH_SLASH,                     KC_J,               KC_M,           KC_W,           KC_V,           MO(1),          MO(3),
                                                                    MO(5),          KC_DEL,                         KC_BSPC,            KC_SPC
    ),

    // ───────────────────── Right-hand layer 1 (R‑Nav/Arrows) ─────────────────────
    // LEFT SIDE = transparent; RIGHT SIDE = nav/edit block (only the right hand changes).
    [1] = LAYOUT(
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        KC_ENT,         KC_UP,          KC_PGUP,        _______,        _______,
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       _______,        _______,
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        KC_HOME,        KC_END,         KC_PGDN,        _______,        _______,
                                                                    _______,        _______,                        _______,        _______
    ),

    // ───────────────────── Left-hand layer 2 (L‑Symbols) ─────────────────────
    // LEFT SIDE = symbols; RIGHT SIDE = transparent.
    [2] = LAYOUT(
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_GRV,         KC_DOT,         KC_COMM,        KC_SCLN,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_LPRN,        KC_RPRN,        KC_LCBR,        KC_RCBR,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_LBRC,        KC_RBRC,        KC_LT,          KC_GT,                          _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,                        _______,        _______
    ),

    // ─────────────── Right-hand layer 3 (R‑F‑keys/Media) ───────────────
    // LEFT SIDE = transparent; RIGHT SIDE = F-keys + media.
    [3] = LAYOUT(
        _______,    _______,        _______,        _______,        _______,        _______,                        KC_F1,          KC_F2,          KC_F3,          KC_F4,          KC_F5,          KC_F6,
        _______,    _______,        _______,        _______,        _______,        _______,                        KC_F7,          KC_F8,          KC_F9,          KC_F10,         KC_F11,         KC_F12,
        _______,    _______,        _______,        _______,        _______,        _______,                        KC_MPRV,        KC_MPLY,        KC_MNXT,        KC_VOLU,        KC_MUTE,        KC_TILD,
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        KC_MUTE,        KC_VOLD,        KC_VOLU,        _______,        _______,
                                                                    _______,        _______,                        _______,        _______
    ),

    // ─────────────── Left-hand layer 4 (L‑Numbers/Extras) ───────────────
    // LEFT SIDE = numbers & math; RIGHT SIDE = transparent.
    [4] = LAYOUT(
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_1,           KC_2,           KC_3,           KC_PLUS,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_4,           KC_5,           KC_6,           KC_EQL,                         _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_7,           KC_8,           KC_9,           KC_0,                           _______,        _______,        _______,        _______,        _______,        _______,
                                                                    KC_SEMICOLON,   KC_QUOTE,                       _______,        _______
    ),

    [5] = LAYOUT(
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_1,           KC_2,           KC_3,           KC_PLUS,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_4,           KC_5,           KC_6,           KC_EQL,                         _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_7,           KC_8,           KC_9,           KC_0,                           _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,                        _______,        _______
    ),
};


#define DIV 3
#define DIV_2 4
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
    rgb_matrix_set_color(11,   200 / DIV_2 + ADD, 90 / DIV_2 + ADD, 160 / DIV_2 + ADD);
    rgb_matrix_set_color(16,  200, 90, 160);
    rgb_matrix_set_color(17,  200 / DIV + ADD, 90 / DIV + ADD, 160 / DIV + ADD);
    rgb_matrix_set_color(22,  200 / DIV + ADD, 90 / DIV + ADD, 160 / DIV + ADD);
    rgb_matrix_set_color(23,  200 / DIV_2 + ADD, 90 / DIV_2 + ADD, 160 / DIV_2 + ADD);

    // ===========================
    // ===== Right keyboard ======
    // ===========================

    // Index
    rgb_matrix_set_color(32,  200 / DIV_2 + ADD, 90 / DIV_2 + ADD, 160 / DIV_2 + ADD);
    rgb_matrix_set_color(33,  200 / DIV + ADD,   90 / DIV + ADD, 160 / DIV + ADD);
    rgb_matrix_set_color(38,  200 / DIV + ADD,   90 / DIV + ADD, 160 / DIV + ADD);
    rgb_matrix_set_color(39,  200, 90, 160);
    rgb_matrix_set_color(44,  200 / DIV_2 + ADD, 90 / DIV_2 + ADD, 160 / DIV_2 + ADD);
    rgb_matrix_set_color(45,  200 / DIV + ADD,   90 / DIV + ADD, 160 / DIV + ADD);

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
        rgb_matrix_set_color(26, 0, 0, 0);
    } else if (active_layer == 1) {
        rgb_matrix_set_color(26, 200 / DIV + ADD, 100 / DIV + ADD, 100 / DIV + ADD);
    } else if (active_layer == 2) {
        rgb_matrix_set_color(5, 100 / DIV + ADD, 100 / DIV + ADD, 200 / DIV + ADD);
    }

    return true;
}
#endif
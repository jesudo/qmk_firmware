// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define ONESHOT_TIMEOUT 600        // cancels after 600 ms if you don't hit a key
#define ONESHOT_TAP_TOGGLE 2       // double‑tap a one‑shot to latch; tap once to clear

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

enum {
    TD_SPC_TAB = 0,
    TD_BSPC_WORD,
};

typedef enum {
    SINGLE_TAP,
    SINGLE_HOLD,
    DOUBLE_TAP,
    DOUBLE_HOLD,
    MORE_TAPS
} td_hold_state_t;

static td_hold_state_t dance_state;
static td_hold_state_t cur_dance(tap_dance_state_t *state);

void td_bspc_finished(tap_dance_state_t *state, void *user_data);
void td_bspc_reset(tap_dance_state_t *state, void *user_data);


#ifdef TAP_DANCE_ENABLE
tap_dance_action_t tap_dance_actions[] = {
    [TD_SPC_TAB]   = ACTION_TAP_DANCE_DOUBLE(KC_SPC, KC_TAB),
    [TD_BSPC_WORD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_bspc_finished, td_bspc_reset),
};
#endif


static td_hold_state_t cur_dance(tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->pressed) {
            return SINGLE_HOLD;
        } else {
            return SINGLE_TAP;
        }
    } else if (state->count == 2) {
        if (state->pressed) {
            return DOUBLE_HOLD;
        } else {
            return DOUBLE_TAP;
        }
    }
    return MORE_TAPS;
}

void td_bspc_finished(tap_dance_state_t *state, void *user_data) {
    dance_state = cur_dance(state);

    if (dance_state == SINGLE_TAP) {
        tap_code(KC_BSPC);
    } else if (dance_state == SINGLE_HOLD) {
        register_code(KC_BSPC);       // holds until reset → autorepeat backspace
    } else if (dance_state == DOUBLE_TAP) {
        tap_code(KC_DEL);             // delete
    } else if (dance_state == DOUBLE_HOLD) {
        register_code(KC_DEL);        // holds until reset → autorepeat delete
    } else {
        // 3+ taps: do nothing (or pick a behavior if you want)
    }
}

void td_bspc_reset(tap_dance_state_t *state, void *user_data) {
    if (dance_state == SINGLE_HOLD) {
        unregister_code(KC_BSPC);
    } else if (dance_state == DOUBLE_HOLD) {
        unregister_code(KC_DEL);
    }
    dance_state = SINGLE_TAP;
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // ───────────────────────────── Base (0) ─────────────────────────────
    // Bottom row change: add MO(4) on left (extra left-hand layer), MO(3) on right.
    // Right thumb: Tap Dance Space/Tab.
    [0] = LAYOUT(
        OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), OSL(3),        OSM(MOD_LSFT),  KC_ENT,                         _______,            _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_Y,           KC_F,           KC_G,           _______,                        KC_J,               KC_C,           KC_R,           KC_L,           _______,        _______,
           KC_P,    KC_A,           KC_O,           KC_E,           KC_U,           KC_I,                           KC_D,               KC_H,           KC_T,           KC_N,           KC_S,           KC_Z,
          MO(2),    MO(4),          KC_K,           KC_X,           KC_B,           _______,                        KC_Q,               KC_M,           KC_W,           KC_V,           MO(1),          MO(3),
                                                                    MO(5),          KC_LGUI,                        KC_BSPC,            KC_SPC
    ),

    // ───────────────────── Right-hand layer 1 (R‑Nav/Arrows) ─────────────────────
    // LEFT SIDE = transparent; RIGHT SIDE = nav/edit block (only the right hand changes).
    [1] = LAYOUT(
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        KC_HOME,        KC_UP,          KC_END,         KC_PGUP,        KC_DEL,
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        KC_LEFT,        KC_DOWN,        KC_RIGHT,       KC_PGDN,        KC_BSPC,
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
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
        _______,    _______,        KC_1,           KC_2,           KC_3,           KC_MINS,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_4,           KC_5,           KC_6,           KC_EQL,                         _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_7,           KC_8,           KC_9,           KC_0,                           _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,                        _______,        _______
    ),
    [5] = LAYOUT(
        _______,    _______,        _______,        _______,        _______,        _______,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_1,           KC_2,           KC_3,           KC_MINS,                        _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_4,           KC_5,           KC_6,           KC_EQL,                         _______,        _______,        _______,        _______,        _______,        _______,
        _______,    _______,        KC_7,           KC_8,           KC_9,           KC_0,                           _______,        _______,        _______,        _______,        _______,        _______,
                                                                    _______,        _______,                        _______,        _______
    ),
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
#include QMK_KEYBOARD_H

#include "oneshot.h"
#include "swapper.h"

#define HOME G(KC_LEFT)
#define END G(KC_RGHT)
#define FWD G(KC_RBRC)
#define BACK G(KC_LBRC)
#define TABL G(S(KC_LBRC))
#define TABR G(S(KC_RBRC))
#define SPCL A(G(KC_LEFT))
#define SPC_R A(G(KC_RGHT))
#define LA_SYM MO(SYM)
#define LA_NAV MO(NAV)
#define APP_SCH G(KC_K) // cmd-k is used in a lot of apps as a search

enum layers {
    DEF,
    SYM,
    NAV,
    NUM,
};

enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,  // Switch to next window         (cmd-tab)
    SW_LANG, // Switch to next input language (ctl-spc)
};

enum combos {
  // default layer
  COMBO_CUT,
  COMBO_COPY,
  COMBO_PASTE,
  COMBO_BRACKET_OPEN,
  COMBO_BRACKET_CLOSE,
  COMBO_CURLY_OPEN,
  COMBO_CURLY_CLOSE,
  COMBO_PAREN_OPEN,
  COMBO_PAREN_CLOSE,
  COMBO_SEMI,

  // symbol layer
  /* COMBO_PERCENT, */
  /* COMBO_PLUS, */
  /* COMBO_BSLASH, */

  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM PB_combo[] = {KC_P, KC_B, COMBO_END};
const uint16_t PROGMEM TG_combo[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM D_DOT_combo[] = {KC_D, KC_DOT, COMBO_END};
const uint16_t PROGMEM WR_combo[] = {KC_W, KC_R, COMBO_END};
const uint16_t PROGMEM FS_combo[] = {KC_F, KC_S, COMBO_END};
const uint16_t PROGMEM PT_combo[] = {KC_P, KC_T, COMBO_END};
const uint16_t PROGMEM JM_combo[] = {KC_J, KC_M, COMBO_END};
const uint16_t PROGMEM LN_combo[] = {KC_L, KC_N, COMBO_END};
const uint16_t PROGMEM UE_combo[] = {KC_U, KC_E, COMBO_END};
const uint16_t PROGMEM YI_combo[] = {KC_Y, KC_I, COMBO_END};
const uint16_t PROGMEM NH_combo[] = {KC_N, KC_H, COMBO_END};

combo_t key_combos[] = {
  // default
  [COMBO_CUT] = COMBO(D_DOT_combo, G(KC_X)),
  [COMBO_COPY] = COMBO(TG_combo, G(KC_C)),
  [COMBO_PASTE] = COMBO(PB_combo, G(KC_V)),

  [COMBO_BRACKET_OPEN] = COMBO(WR_combo, KC_LBRC),
  [COMBO_CURLY_OPEN] = COMBO(FS_combo, KC_LCBR),
  [COMBO_PAREN_OPEN] = COMBO(PT_combo, KC_LPRN),
  [COMBO_PAREN_CLOSE] = COMBO(LN_combo, KC_RPRN),
  [COMBO_CURLY_CLOSE] = COMBO(UE_combo, KC_RCBR),
  [COMBO_BRACKET_CLOSE] = COMBO(YI_combo, KC_RBRC),

  [COMBO_SEMI] = COMBO(NH_combo, KC_SCLN),
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_lilactown(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_Z,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_COMM, KC_V,    KC_C,    KC_D,    KC_DOT,  KC_SCLN, KC_H,    KC_K,    KC_X,    KC_QUOT,
                                   LA_NAV,  KC_SPC,  KC_LSFT, LA_SYM
    ),

    [SYM] = LAYOUT_lilactown(
        KC_ESC,  KC_CIRC, KC_SCLN, KC_COLN, KC_TILD, KC_GRV,  KC_COMM, KC_DOT,  KC_DQT,  KC_QUOT,
        KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,  KC_HASH, OS_SHFT, OS_CMD,  OS_ALT,  OS_CTRL,
        KC_PLUS, KC_PERC, KC_AT,   KC_SLSH, KC_PERC, KC_BSLS, KC_EXLM, KC_AMPR, KC_QUES, XXXXXXX,
                                   _______, _______, _______, _______
    ),

    [NAV] = LAYOUT_lilactown(
        KC_TAB,  SW_WIN,  TABL,    TABR,    G(KC_N),   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
        OS_CTRL, OS_ALT,  OS_CMD,  OS_SHFT, G(KC_GRV), KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,
        SPCL,    SPC_R,   KC_VOLD, KC_VOLU, XXXXXXX,   XXXXXXX, APP_SCH, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______, _______
    ),

    [NUM] = LAYOUT_lilactown(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        OS_CTRL, OS_ALT,  OS_CMD,  OS_SHFT, KC_F11,  KC_F10,  OS_SHFT, OS_CMD,  OS_ALT,  OS_CTRL,
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,
                                   _______, _______, _______, _______
    ),
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case LA_SYM:
    case LA_NAV:
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_lang_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_lang_active, KC_LCTL, KC_SPC, SW_LANG,
        keycode, record
    );

    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, SYM, NAV, NUM);
}

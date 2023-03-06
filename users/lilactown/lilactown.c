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
  PB_PASTE,
  TG_COPY,
  DV_CUT,

  PT_Z,
  TD_V,

  LN_SCLN,
  NH_K,

  // nav layer
  NAV_TAB_NEW,
  NAV_WIN_SWITCH,
  NAV_WIN_NEW,

  /* NAV_TAB_CLOSE, */
  NAV_TAB_FIRST,
  NAV_TAB_LAST,

  // sym layer
  SYM_PLUS,
  SYM_PERC,

  SYM_EXCL,
  COMBO_LENGTH
};

uint16_t COMBO_LEN = COMBO_LENGTH; // remove the COMBO_COUNT define and use this instead!

const uint16_t PROGMEM pb_combo[] = {KC_P, KC_B, COMBO_END};
const uint16_t PROGMEM tg_combo[] = {KC_T, KC_G, COMBO_END};
const uint16_t PROGMEM dv_combo[] = {KC_D, KC_V, COMBO_END};

const uint16_t PROGMEM pt_combo[] = {KC_P, KC_T, COMBO_END};
const uint16_t PROGMEM td_combo[] = {KC_T, KC_D, COMBO_END};

const uint16_t PROGMEM ln_combo[] = {KC_L, KC_N, COMBO_END};
const uint16_t PROGMEM nh_combo[] = {KC_N, KC_H, COMBO_END};


// nav layer
const uint16_t PROGMEM nav_tab_first[] = {TABL, OS_SHFT, COMBO_END};
const uint16_t PROGMEM nav_tab_last[] = {TABR, KC_HYPR, COMBO_END};
const uint16_t PROGMEM nav_tab_new[] = {TABL, TABR, COMBO_END};
const uint16_t PROGMEM nav_win_switch[] = {OS_SHFT, KC_HYPR, COMBO_END};
const uint16_t PROGMEM nav_win_new[] = {KC_VOLU, KC_VOLD, COMBO_END};

// sym layer
const uint16_t PROGMEM unds_slsh_combo[] = {KC_UNDS, KC_SLSH, COMBO_END};
const uint16_t PROGMEM rparen_shift_combo[] = {KC_RPRN, OS_SHFT, COMBO_END};
/* const uint16_t PROGMEM shift_bsls_combo[] = {OS_SHFT, KC_BSLS, COMBO_END}; */

combo_t key_combos[] = {
  [PB_PASTE] = COMBO(pb_combo, G(KC_V)),
  [TG_COPY] = COMBO(tg_combo, G(KC_C)),
  [DV_CUT] = COMBO(dv_combo, G(KC_X)),

  [PT_Z] = COMBO(pt_combo, KC_Z),
  [TD_V] = COMBO(td_combo, KC_V),

  [LN_SCLN] = COMBO(ln_combo, KC_SCLN),
  [NH_K] = COMBO(nh_combo, KC_K),


  //
  // nav layer
  //

  // horizontal
  [NAV_TAB_NEW] = COMBO(nav_tab_new, G(KC_T)),
  [NAV_WIN_SWITCH] = COMBO(nav_win_switch, G(KC_GRV)),
  [NAV_WIN_NEW] = COMBO(nav_win_new, G(KC_N)),

  // vertical
  [NAV_TAB_FIRST] = COMBO(nav_tab_first, G(KC_1)),
  [NAV_TAB_LAST] = COMBO(nav_tab_last, G(KC_9)),


  //
  // sym layer
  //

  /* [UNDS_SLSH_PERC] = COMBO(unds_slsh_combo, KC_PERC), */
  // TODO excl
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [DEF] = LAYOUT_lilactown(
        KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,
        KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SCLN,
                                   LA_NAV,  KC_SPC,  KC_LSFT,  LA_SYM
    ),

    [SYM] = LAYOUT_lilactown(
        KC_ESC,  KC_LBRC, KC_LCBR, KC_LPRN, KC_TILD, KC_CIRC, KC_RPRN, KC_RCBR, KC_RBRC, KC_GRV,
        KC_MINS, KC_ASTR, KC_EQL,  KC_UNDS, KC_DLR,  KC_HASH, OS_SHFT,  OS_CMD, OS_ALT,  OS_CTRL,
        KC_PLUS, KC_PIPE, KC_AT,   KC_SLSH, KC_PERC, XXXXXXX, KC_BSLS, KC_AMPR, KC_QUES, KC_EXLM,
                                   _______, _______, _______, _______
    ),

    [NAV] = LAYOUT_lilactown(
        KC_TAB,  SW_WIN,  XXXXXXX,   TABL,    TABR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_BSPC,
        OS_CTRL, OS_ALT,  OS_CMD,  OS_SHFT, KC_HYPR, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_ENT,
        SPCL,    SPC_R,   XXXXXXX, KC_VOLD, KC_VOLU, APP_SCH, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______, _______
    ),

    [NUM] = LAYOUT_lilactown(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
        OS_CTRL, OS_ALT,  OS_CMD,  OS_SHFT, KC_F11,  KC_F10,  OS_SHFT, OS_CMD,  OS_ALT,  OS_CTRL,
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_F1,   KC_F2,  KC_F3,   KC_F4,   KC_F5,
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

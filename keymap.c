#include QMK_KEYBOARD_H

/* keyboard diff */
#ifdef KEYBOARD_keychron_v4
#define HAS_MAC
#define ENABLE_MATRIX
#define _LAYOUT LAYOUT_ansi_61
#endif

#ifdef KEYBOARD_keychron_k9_pro_ansi_rgb
#define HAS_MAC
#define ENABLE_BLUETOOTH
#define ENABLE_MATRIX
#define _LAYOUT LAYOUT_61_ansi
#define KC_BTU BT_USB
#define KC_BT1 BT_HST1
#define KC_BT2 BT_HST2
#define KC_BT3 BT_HST3
#define KC_BT4 XXXXXXX
#define MS_BTN1 KC_BTN1
#define MS_BTN2 KC_BTN2
#define MS_UP KC_MS_U
#define MS_DOWN KC_MS_D
#define MS_LEFT KC_MS_L
#define MS_RGHT KC_MS_R
#define MS_WHLU KC_WH_U
#define MS_WHLD KC_WH_D
#define MS_WHLL KC_WH_L
#define MS_WHLR KC_WH_R
#define RM_TOGG RGB_TOG
#define RM_NEXT RGB_MOD
#define RM_SPDU RGB_SPI
#define RM_VALU RGB_VAI
#define RM_SATU RGB_SAI
#define RM_HUEU RGB_HUI
#endif

#ifdef KEYBOARD_keychron_k12_pro_ansi_white
#define HAS_MAC
#define ENABLE_BLUETOOTH
#define _LAYOUT LAYOUT_61_ansi
#define KC_BTU BT_USB
#define KC_BT1 BT_HST1
#define KC_BT2 BT_HST2
#define KC_BT3 BT_HST3
#define KC_BT4 XXXXXXX
#define MS_BTN1 KC_BTN1
#define MS_BTN2 KC_BTN2
#define MS_UP KC_MS_U
#define MS_DOWN KC_MS_D
#define MS_LEFT KC_MS_L
#define MS_RGHT KC_MS_R
#define MS_WHLU KC_WH_U
#define MS_WHLD KC_WH_D
#define MS_WHLL KC_WH_L
#define MS_WHLR KC_WH_R
#define RM_TOGG BL_TOGG
#define RM_NEXT BL_STEP
#define RM_SPDU RGB_SPI
#define RM_VALU BL_UP
#define RM_SATU BL_DOWN
#define RM_HUEU RGB_HUI
#endif

#ifdef KEYBOARD_annepro2_c18
#define ENABLE_BLUETOOTH
#define _LAYOUT LAYOUT_60_ansi
#define KC_BTU KC_AP2_USB
#define KC_BT1 KC_AP2_BT1
#define KC_BT2 KC_AP2_BT2
#define KC_BT3 KC_AP2_BT3
#define KC_BT4 KC_AP2_BT4
#endif

#ifdef KEYBOARD_qk61
#include "common/rdmctmzt_common.h"
#define ENABLE_BLUETOOTH
#define _LAYOUT LAYOUT_60_ansi
#define KC_BTU MD_USB
#define KC_BT1 MD_BLE1
#define KC_BT2 MD_BLE2
#define KC_BT3 MD_BLE3
#define KC_BT4 MD_24G
#endif

#ifndef ENABLE_BLUETOOTH
#define KC_BTU XXXXXXX
#define KC_BT1 XXXXXXX
#define KC_BT2 XXXXXXX
#define KC_BT3 XXXXXXX
#define KC_BT4 XXXXXXX
#endif

/* func declare */
bool fn_process_super_space(uint16_t keycode, keyrecord_t *record);
void fn_td_tap_hold_finished(tap_dance_state_t *state, void *user_data);
void fn_td_tap_hold_reset(tap_dance_state_t *state, void *user_data);
void fn_td_tap_hold_release(tap_dance_state_t *state, void *user_data);
bool pre_odd_space(uint16_t keycode, keyrecord_t *record);

/* static */
#define ACT_TD_TAP_HOLD(once, irq_tap, tap, hold) { \
    .fn = {NULL, fn_td_tap_hold_finished, fn_td_tap_hold_reset, fn_td_tap_hold_release}, \
    .user_data = (void *)&((td_tap_hold_t){(once), (irq_tap), (tap), (hold), 0}) \
}
#define ODD_IDX(KC) ((KC) - ODD_BG - 1)

enum layers {
#ifdef HAS_MAC
    _MAC,
#endif
    _BASE,
    _FN1,
    _FN2,
    _TN1,
    _TN2,
    _TN3,
    _FNX,
    _FNY,
};

enum td_names {
    TD_TH_LC_F1, /* tap hold lctrl F1 */
};

enum odd_keycodes {
    ODD_BG = SAFE_RANGE,
    KC_ODD_SPACE,
    ODD_ED
};

typedef bool (*odd_fn_t)(uint16_t keycode, keyrecord_t *record);

typedef struct {
    char once; /* hold process only tap once, 0/1 */
    char irq_tap; /* use tap for interrupted, 0/1 */
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} td_tap_hold_t;

typedef struct {
    odd_fn_t pre;
    odd_fn_t process;
    odd_fn_t post;
} odd_action_t;

tap_dance_action_t tap_dance_actions[] = {
    [TD_TH_LC_F1] = ACT_TD_TAP_HOLD(1, 0, C(KC_F1), KC_LCTL),
};

odd_action_t odd_actions[] = {
    [ODD_IDX(KC_ODD_SPACE)] = {pre_odd_space, NULL, NULL},
};

const uint16_t PROGMEM mkcbhp[] = {COMBO_END};
combo_t key_combos[] = {
    COMBO(mkcbhp, 0),
};

uint16_t g_odd_space_time;
uint16_t g_odd_space_type;



/* keymaps */
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
#if defined(HAS_MAC)
    [_MAC] = _LAYOUT(
        KC_ESC,  KC_1,    KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
        KC_TAB,  KC_Q,    KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A,    KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,
        KC_LCTL, KC_LOPT, KC_LCMD,                KC_SPC,                    KC_RCMD, XXXXXXX, XXXXXXX, KC_RCTL
    ),
#endif
    [_BASE] = _LAYOUT(
        LT(_FN1,KC_GRAVE),   KC_1,     KC_2, KC_3, KC_4, KC_5, KC_6,    KC_7, KC_8, KC_9,    KC_0,    KC_MINS,          KC_EQL,           KC_BSPC,
        MT(MOD_LCTL,KC_TAB), KC_Q,     KC_W, KC_E, KC_R, KC_T, KC_Y,    KC_U, KC_I, KC_O,    KC_P,    KC_LBRC,          KC_RBRC,          KC_BSLS,
        KC_ESC,              KC_A,     KC_S, KC_D, KC_F, KC_G, KC_H,    KC_J, KC_K, KC_L,    KC_SCLN, KC_QUOT,                            KC_ENT,
        KC_LSFT,                       KC_Z, KC_X, KC_C, KC_V, KC_B,    KC_N, KC_M, KC_COMM, KC_DOT,  KC_SLSH,                            RSFT_T(KC_UP),
        TD(TD_TH_LC_F1),     MO(_FN2), KC_LGUI,                KC_ODD_SPACE,                 KC_RALT, LT(_FN1,KC_LEFT), LT(_FN2,KC_DOWN), LT(_FNX,KC_RIGHT)
    ),
    [_FN1] = _LAYOUT(
        XXXXXXX, KC_BT1,  KC_BT2,  KC_BT3,  KC_BT4,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        KC_BTU,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RM_HUEU, RM_SATU, RM_VALU,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, RM_SPDU,          RM_NEXT,
        KC_LSFT,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          RM_TOGG,
        XXXXXXX, XXXXXXX, KC_PSCR,                            KC_LSFT,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_FN2] = _LAYOUT(
        MS_WHLU, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,      KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
        MS_WHLD, MS_WHLL, MS_WHLR, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_HOME, KC_END,  XXXXXXX,
        KC_VOLD, KC_VOLU, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,    KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,XXXXXXX, KC_PGUP,          KC_PSCR,
        KC_MPRV,          KC_MNXT, XXXXXXX, XXXXXXX, C(S(KC_V)), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PGDN,          XXXXXXX,
        KC_MUTE, XXXXXXX, KC_MPLY,                               XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    // TO layer
    [_TN1] = _LAYOUT(
        KC_BSPC, KC_KP_SLASH, KC_KP_ASTERISK, KC_KP_MINUS, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_7,    KC_8,        KC_9,           KC_KP_PLUS,  _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_4,    KC_5,        KC_6,           KC_KP_PLUS,  _______,  _______, MS_LEFT, MS_DOWN, MS_UP,   MS_RGHT, MS_BTN2, _______,          _______,
        KC_1,                 KC_2,           KC_3,        KC_ENTER, _______, _______, _______, _______, _______, _______, _______,          _______,
        KC_DOT,  KC_0,        KC_0,                                           MS_BTN1,                            _______, _______, _______, LT(_FNY, KC_RIGHT)
    ),
    [_TN2] = _LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, LT(_FNY, KC_RIGHT)
    ),
    [_TN3] = _LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        KC_P,    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        KC_LCTL, _______, _______,                            KC_SPACE,                           _______, _______, _______, LT(_FNY, KC_RIGHT)
    ),
    [_FNX] = _LAYOUT(
        KC_CAPS, TO(_TN1), XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, DF(_RTSA), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, TO(_TN2),
        XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          TO(_TN3),
        XXXXXXX,           XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
        XXXXXXX, XXXXXXX,  XXXXXXX,                              XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
    ),
    [_FNY] = _LAYOUT( // should be last
        KC_ESC,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,   XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX,
        XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,              XXXXXXX,
        XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, DF(_BASE), TO(_BASE), XXXXXXX
    ),


    /* TEMPLATE:
        #0
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
            XXXXXXX,          XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,          XXXXXXX,
            XXXXXXX, XXXXXXX, XXXXXXX,                            XXXXXXX,                            XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
        #1
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
            _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
            _______, _______, _______,                            _______,                            _______, _______, _______, _______
    */
};


/* user custom */
bool pre_process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case ODD_BG ... ODD_ED:
            if (odd_actions[ODD_IDX(keycode)].pre) {
                return odd_actions[ODD_IDX(keycode)].pre(keycode, record);
            }
            break;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    static char shift_sign = 0;
    switch (keycode) {
        case ODD_BG ... ODD_ED:
            if (odd_actions[ODD_IDX(keycode)].process) {
                return odd_actions[ODD_IDX(keycode)].process(keycode, record);
            }
            break;
        case KC_LSFT:
            if (record->event.pressed) {
                /* start count */
                shift_sign = 1;
            } else if (shift_sign) { /* release */
                /* count result: only press&release shift */
                g_odd_space_time = record->event.time;
                g_odd_space_type = keycode;
                shift_sign = 0;
            }
            break;
        default:
            shift_sign = 0;
            g_odd_space_type = 0;
    }
    return true;
}

void post_process_record_user(uint16_t keycode, keyrecord_t *record)
{
    switch (keycode) {
        case ODD_BG ... ODD_ED:
            if (odd_actions[ODD_IDX(keycode)].post) {
                odd_actions[ODD_IDX(keycode)].post(keycode, record);
            }
            break;
    }
}

#ifdef ENABLE_MATRIX
layer_state_t layer_state_set_user(layer_state_t state) {
    rgb_matrix_set_color_all(0, 0, 0);
    switch (get_highest_layer(state)) {
        case _TN1:
            rgb_matrix_set_color(13, 0, 0, 5);
            break;
        case _TN2:
            rgb_matrix_set_color(27, 0, 5, 5);
            break;
        case _TN3:
            rgb_matrix_set_color(40, 0, 5, 5);
            break;
    }
    return state;
}
#endif


/* func define */
/**
 * MT: 有按键irq时，等待release，如果超过TAPPING_TERM还不松，判断为hold。如果提前松了，判断为tap
 * TD: 有按键irq时，立即处理finished，无法等待完整的窗口，想要达到MT的效果，需要其他处理逻辑的帮助
 */
void fn_td_tap_hold_finished(tap_dance_state_t *state, void *user_data)
{
    td_tap_hold_t *tap_hold = (td_tap_hold_t *)user_data;
    if (state->count > 1
            || (state->interrupted && tap_hold->irq_tap)) {
        tap_hold->held = tap_hold->tap;
    } else {
        tap_hold->held = tap_hold->hold;
    }
    register_code16(tap_hold->held);
}

void fn_td_tap_hold_reset(tap_dance_state_t *state, void *user_data)
{
    td_tap_hold_t *tap_hold = (td_tap_hold_t *)user_data;
    if (!tap_hold->held) return;
    /* hold */
    unregister_code16(tap_hold->held);
    tap_hold->held = 0;
}

void fn_td_tap_hold_release(tap_dance_state_t *state, void *user_data)
{
    td_tap_hold_t *tap_hold = (td_tap_hold_t *)user_data;
    /* speed up tap */
    if (!state->finished) {
        tap_code16(tap_hold->tap);
        if (tap_hold->once) state->finished = 1;
    }
}

static void pre_odd_space_light(int on)
{
#ifdef ENABLE_MATRIX
    if (on) {
        rgb_matrix_set_color(41, 0, 5, 5);
    }
    else {
        rgb_matrix_set_color(41, 0, 0, 0);
    }
#endif
}

bool pre_odd_space(uint16_t keycode, keyrecord_t *record)
{
    static uint16_t now_kc = MT(MOD_LALT, KC_SPC);
    static uint16_t release_time;
    static uint8_t light_on;
    if (record->event.pressed) {
        if (timer_elapsed(g_odd_space_time) < TAPPING_TERM) {
            switch (g_odd_space_type) {
                case KC_LSFT:
                    now_kc = MT(MOD_LSFT, KC_SPC);
                    pre_odd_space_light(light_on=1);
                    break;
            }
        } else if (timer_elapsed(release_time) >= TAPPING_TERM) {
            // MT finish
            now_kc = MT(MOD_LALT, KC_SPC);
        }
    } else {
        release_time = record->event.time;
        if (light_on) {
            pre_odd_space_light(light_on=0);
        }
    }
    record->keycode = now_kc;
    return true;
}

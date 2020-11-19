#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE 0
#define _FN1 1

#define LY_SP LT(_FN1, KC_SPC)
#define LCA_ESC LCA_T(KC_ESC)
#define LCA_SFT LCA_T(KC_RSFT)
#define FL_SCRN LCA(KC_ENT)
#define LCAG_SF LCAG_T(KC_LSFT)
#define DSK_LFT LCTL(KC_LEFT)
#define DSK_RHT LCTL(KC_RGHT)

#define BASE_COLOR HSV_BLUE
#define FN_COLOR 33, 163, 255
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  ITERM,
  SPOT,
  SAFARI,
  SLACK,
  MSGS,
  GSTAT,
  SSHKFKA,
  SSHPPLE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_65_with_macro(
    KC_MUTE, KC_SLEP, KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_DEL,  KC_BSPC, KC_HOME, \
    ITERM,   SAFARI,  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, KC_PGUP, \
    SSHKFKA, SSHPPLE, KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT,  KC_PGDN, \
    MSGS,    SPOT,    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_END, \
    GSTAT,   SLACK,   TT(_FN1),KC_LCTL, KC_LALT, KC_LGUI, LY_SP,            MO(_FN1),LY_SP,  KC_RGUI, KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
  ),

  [_FN1] = LAYOUT_65_with_macro(
    RGB_TOG, _______, KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,  KC_BSPC, RESET, \
    RGB_SAI, RGB_HUI, _______, _______, _______, KC_UP,   _______, _______, _______, _______, _______, KC_MPRV, KC_MPLY, KC_MNXT, _______, _______, EEP_RST, \
    RGB_M_K, RGB_VAI, LCA_ESC, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, DSK_LFT, KC_BRMD, KC_BRMU, DSK_RHT, _______, _______, FL_SCRN, DEBUG, \
    RGB_M_P, RGB_M_B, LCAG_SF, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, LCA_SFT, _______, _______, \
    RGB_M_R, RGB_M_X, _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______
  )
};

void keyboard_post_init_user(void) {
  rgblight_sethsv_noeeprom(HSV_GOLD);
}

void encoder_update_user(uint8_t index, bool clockwise) 
{
    if (index == 0) 
	{
		switch(biton32(layer_state)) {
		case _FN1:
        	if (clockwise) 
				rgblight_step();
			else 
				rgblight_step_reverse();
		break;
		default:
        	if (clockwise) 
        	    tap_code(KC_VOLU);
			else 
        	    tap_code(KC_VOLD);
	 	break;	
		}
    }
}

void update_led(void) {
    switch (biton32(layer_state)) {
    case _BASE:
        rgblight_sethsv_noeeprom(BASE_COLOR);
        break;
    case _FN1:
        rgblight_sethsv_noeeprom(FN_COLOR);
        break;
    default:
        rgblight_sethsv_noeeprom(HSV_GOLD);
    }
}

uint32_t layer_state_set_user(uint32_t state) {
  update_led();
  return state;
}

void led_set_user(uint8_t usb_led) {
  update_led();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record)
{
    if (record->event.pressed)
    {
        switch(keycode) 
        {
            case ITERM:
                SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)));
                _delay_ms(100);
                SEND_STRING("iterm");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_ENTER));
                break;
            case SPOT:
                SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)));
                _delay_ms(100);
                SEND_STRING("spotify");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_ENTER));
                break;
            case SAFARI:
                SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)));
                _delay_ms(100);
                SEND_STRING("safari");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_ENTER));
                break;
            case SLACK:
                SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)));
                _delay_ms(100);
                SEND_STRING("slack");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_ENTER));
                break;
            case MSGS: 
                SEND_STRING(SS_LGUI(SS_TAP(X_SPACE)));
                _delay_ms(100);
                SEND_STRING("messages");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_ENTER));
                break;
            case SSHKFKA:
                SEND_STRING("ssh kafka");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_ENTER));
                break;
            case SSHPPLE:
                SEND_STRING("ssh penelope");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_ENTER));
                break;
            case GSTAT:
                SEND_STRING("git status");
                _delay_ms(100);
                SEND_STRING(SS_TAP(X_ENTER));
                break;
        }

    }
    return true;
}

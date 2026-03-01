// license:BSD-3-Clause
// copyright-holders:Aaron Giles
/***************************************************************************

    inpttype.ipp

    Array of core-defined input types and default mappings.

***************************************************************************/

#include "util/language.h"


/***************************************************************************
    BUILT-IN CORE MAPPINGS
***************************************************************************/

namespace {

#define CORE_INPUT_TYPES_P1 \
		CORE_INPUT_TYPES_BEGIN(p1) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  JOYSTICK_UP,         N_p("input-name", "%p Up"),                  input_seq(KEYCODE_UP, input_seq::or_code, JOYCODE_Y_UP_SWITCH_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  JOYSTICK_DOWN,       N_p("input-name", "%p Down"),                input_seq(KEYCODE_DOWN, input_seq::or_code, JOYCODE_Y_DOWN_SWITCH_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  JOYSTICK_LEFT,       N_p("input-name", "%p Left"),                input_seq(KEYCODE_LEFT, input_seq::or_code, JOYCODE_X_LEFT_SWITCH_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  JOYSTICK_RIGHT,      N_p("input-name", "%p Right"),               input_seq(KEYCODE_RIGHT, input_seq::or_code, JOYCODE_X_RIGHT_SWITCH_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  BUTTON1,             N_p("input-name", "%p Button 1"),            input_seq(KEYCODE_A, input_seq::or_code, JOYCODE_BUTTON1_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  BUTTON2,             N_p("input-name", "%p Button 2"),            input_seq(KEYCODE_S, input_seq::or_code, JOYCODE_BUTTON2_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  BUTTON3,             N_p("input-name", "%p Button 3"),            input_seq(KEYCODE_D, input_seq::or_code, JOYCODE_BUTTON3_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  BUTTON4,             N_p("input-name", "%p Button 4"),            input_seq(KEYCODE_Z, input_seq::or_code, JOYCODE_BUTTON4_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  BUTTON5,             N_p("input-name", "%p Button 5"),            input_seq(KEYCODE_C, input_seq::or_code, JOYCODE_BUTTON5_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  BUTTON6,             N_p("input-name", "%p Button 6"),            input_seq(KEYCODE_X, input_seq::or_code, JOYCODE_BUTTON6_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  START,               N_p("input-name", "%p Start"),               input_seq(KEYCODE_1, input_seq::or_code, JOYCODE_START_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  SELECT,              N_p("input-name", "%p Select"),              input_seq(KEYCODE_5, input_seq::or_code, JOYCODE_SELECT_INDEXED(0)) ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_P1_MAHJONG \
		CORE_INPUT_TYPES_BEGIN(p1_mahjong) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_A,           N_p("input-name", "%p Mahjong A"),           input_seq(KEYCODE_A_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_B,           N_p("input-name", "%p Mahjong B"),           input_seq(KEYCODE_B_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_C,           N_p("input-name", "%p Mahjong C"),           input_seq(KEYCODE_C_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_D,           N_p("input-name", "%p Mahjong D"),           input_seq(KEYCODE_D_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_E,           N_p("input-name", "%p Mahjong E"),           input_seq(KEYCODE_E_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_F,           N_p("input-name", "%p Mahjong F"),           input_seq(KEYCODE_F_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_G,           N_p("input-name", "%p Mahjong G"),           input_seq(KEYCODE_G_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_H,           N_p("input-name", "%p Mahjong H"),           input_seq(KEYCODE_H_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_I,           N_p("input-name", "%p Mahjong I"),           input_seq(KEYCODE_I_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_J,           N_p("input-name", "%p Mahjong J"),           input_seq(KEYCODE_J_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_K,           N_p("input-name", "%p Mahjong K"),           input_seq(KEYCODE_K_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_L,           N_p("input-name", "%p Mahjong L"),           input_seq(KEYCODE_L_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_M,           N_p("input-name", "%p Mahjong M"),           input_seq(KEYCODE_M_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_N,           N_p("input-name", "%p Mahjong N"),           input_seq(KEYCODE_N_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_O,           N_p("input-name", "%p Mahjong O"),           input_seq(KEYCODE_O_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_P,           N_p("input-name", "%p Mahjong P"),           input_seq(KEYCODE_COLON_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_Q,           N_p("input-name", "%p Mahjong Q"),           input_seq(KEYCODE_Q_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_KAN,         N_p("input-name", "%p Mahjong Kan"),         input_seq(KEYCODE_LCONTROL_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_PON,         N_p("input-name", "%p Mahjong Pon"),         input_seq(KEYCODE_LALT_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_CHI,         N_p("input-name", "%p Mahjong Chi"),         input_seq(KEYCODE_SPACE_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_REACH,       N_p("input-name", "%p Mahjong Reach"),       input_seq(KEYCODE_LSHIFT_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_RON,         N_p("input-name", "%p Mahjong Ron"),         input_seq(KEYCODE_Z_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_FLIP_FLOP,   N_p("input-name", "%p Mahjong Flip Flop"),   input_seq(KEYCODE_Y_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_BET,         N_p("input-name", "%p Mahjong Bet"),         input_seq(KEYCODE_3_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_SCORE,       N_p("input-name", "%p Mahjong Take Score"),  input_seq(KEYCODE_RCONTROL_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_DOUBLE_UP,   N_p("input-name", "%p Mahjong Double Up"),   input_seq(KEYCODE_RSHIFT_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_BIG,         N_p("input-name", "%p Mahjong Big"),         input_seq(KEYCODE_ENTER_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_SMALL,       N_p("input-name", "%p Mahjong Small"),       input_seq(KEYCODE_BACKSPACE_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  1, PLAYER1,  MAHJONG_LAST_CHANCE, N_p("input-name", "%p Mahjong Last Chance"), input_seq(KEYCODE_RALT_INDEXED(0)) ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_P2 \
		CORE_INPUT_TYPES_BEGIN(p2) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  JOYSTICK_UP,         N_p("input-name", "%p Up"),                  input_seq(KEYCODE_UP, input_seq::or_code, JOYCODE_Y_UP_SWITCH_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  JOYSTICK_DOWN,       N_p("input-name", "%p Down"),                input_seq(KEYCODE_DOWN, input_seq::or_code, JOYCODE_Y_DOWN_SWITCH_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  JOYSTICK_LEFT,       N_p("input-name", "%p Left"),                input_seq(KEYCODE_LEFT, input_seq::or_code, JOYCODE_X_LEFT_SWITCH_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  JOYSTICK_RIGHT,      N_p("input-name", "%p Right"),               input_seq(KEYCODE_RIGHT, input_seq::or_code, JOYCODE_X_RIGHT_SWITCH_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  BUTTON1,             N_p("input-name", "%p Button 1"),            input_seq(KEYCODE_A, input_seq::or_code, JOYCODE_BUTTON1_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  BUTTON2,             N_p("input-name", "%p Button 2"),            input_seq(KEYCODE_S, input_seq::or_code, JOYCODE_BUTTON2_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  BUTTON3,             N_p("input-name", "%p Button 3"),            input_seq(KEYCODE_D, input_seq::or_code, JOYCODE_BUTTON3_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  BUTTON4,             N_p("input-name", "%p Button 4"),            input_seq(KEYCODE_Z, input_seq::or_code, JOYCODE_BUTTON4_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  BUTTON5,             N_p("input-name", "%p Button 5"),            input_seq(KEYCODE_C, input_seq::or_code, JOYCODE_BUTTON5_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  BUTTON6,             N_p("input-name", "%p Button 6"),            input_seq(KEYCODE_X, input_seq::or_code, JOYCODE_BUTTON6_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  START,               N_p("input-name", "%p Start"),               input_seq(KEYCODE_2, input_seq::or_code, JOYCODE_START_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  SELECT,              N_p("input-name", "%p Select"),              input_seq(KEYCODE_6, input_seq::or_code, JOYCODE_SELECT_INDEXED(1)) ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_P2_MAHJONG \
		CORE_INPUT_TYPES_BEGIN(p2_mahjong) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_A,           N_p("input-name", "%p Mahjong A"),           input_seq(KEYCODE_A_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_B,           N_p("input-name", "%p Mahjong B"),           input_seq(KEYCODE_B_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_C,           N_p("input-name", "%p Mahjong C"),           input_seq(KEYCODE_C_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_D,           N_p("input-name", "%p Mahjong D"),           input_seq(KEYCODE_D_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_E,           N_p("input-name", "%p Mahjong E"),           input_seq(KEYCODE_E_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_F,           N_p("input-name", "%p Mahjong F"),           input_seq(KEYCODE_F_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_G,           N_p("input-name", "%p Mahjong G"),           input_seq(KEYCODE_G_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_H,           N_p("input-name", "%p Mahjong H"),           input_seq(KEYCODE_H_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_I,           N_p("input-name", "%p Mahjong I"),           input_seq(KEYCODE_I_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_J,           N_p("input-name", "%p Mahjong J"),           input_seq(KEYCODE_J_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_K,           N_p("input-name", "%p Mahjong K"),           input_seq(KEYCODE_K_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_L,           N_p("input-name", "%p Mahjong L"),           input_seq(KEYCODE_L_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_M,           N_p("input-name", "%p Mahjong M"),           input_seq(KEYCODE_M_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_N,           N_p("input-name", "%p Mahjong N"),           input_seq(KEYCODE_N_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_O,           N_p("input-name", "%p Mahjong O"),           input_seq(KEYCODE_O_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_P,           N_p("input-name", "%p Mahjong P"),           input_seq(KEYCODE_COLON_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_Q,           N_p("input-name", "%p Mahjong Q"),           input_seq(KEYCODE_Q_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_KAN,         N_p("input-name", "%p Mahjong Kan"),         input_seq(KEYCODE_LCONTROL_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_PON,         N_p("input-name", "%p Mahjong Pon"),         input_seq(KEYCODE_LALT_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_CHI,         N_p("input-name", "%p Mahjong Chi"),         input_seq(KEYCODE_SPACE_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_REACH,       N_p("input-name", "%p Mahjong Reach"),       input_seq(KEYCODE_LSHIFT_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_RON,         N_p("input-name", "%p Mahjong Ron"),         input_seq(KEYCODE_Z_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_FLIP_FLOP,   N_p("input-name", "%p Mahjong Flip Flop"),   input_seq(KEYCODE_Y_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_BET,         N_p("input-name", "%p Mahjong Bet"),         input_seq(KEYCODE_3_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_SCORE,       N_p("input-name", "%p Mahjong Take Score"),  input_seq(KEYCODE_RCONTROL_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_DOUBLE_UP,   N_p("input-name", "%p Mahjong Double Up"),   input_seq(KEYCODE_RSHIFT_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_BIG,         N_p("input-name", "%p Mahjong Big"),         input_seq(KEYCODE_ENTER_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_SMALL,       N_p("input-name", "%p Mahjong Small"),       input_seq(KEYCODE_BACKSPACE_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  2, PLAYER2,  MAHJONG_LAST_CHANCE, N_p("input-name", "%p Mahjong Last Chance"), input_seq(KEYCODE_RALT_INDEXED(1)) ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_P3 \
		CORE_INPUT_TYPES_BEGIN(p3) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  JOYSTICK_UP,         N_p("input-name", "%p Up"),                  input_seq(JOYCODE_Y_UP_SWITCH_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  JOYSTICK_DOWN,       N_p("input-name", "%p Down"),                input_seq(JOYCODE_Y_DOWN_SWITCH_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  JOYSTICK_LEFT,       N_p("input-name", "%p Left"),                input_seq(JOYCODE_X_LEFT_SWITCH_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  JOYSTICK_RIGHT,      N_p("input-name", "%p Right"),               input_seq(JOYCODE_X_RIGHT_SWITCH_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  BUTTON1,             N_p("input-name", "%p Button 1"),            input_seq(JOYCODE_BUTTON1_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  BUTTON2,             N_p("input-name", "%p Button 2"),            input_seq(JOYCODE_BUTTON2_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  BUTTON3,             N_p("input-name", "%p Button 3"),            input_seq(JOYCODE_BUTTON3_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  BUTTON4,             N_p("input-name", "%p Button 4"),            input_seq(JOYCODE_BUTTON4_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  BUTTON5,             N_p("input-name", "%p Button 5"),            input_seq(JOYCODE_BUTTON5_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  BUTTON6,             N_p("input-name", "%p Button 6"),            input_seq(JOYCODE_BUTTON6_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  START,               N_p("input-name", "%p Start"),               input_seq(JOYCODE_START_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  SELECT,              N_p("input-name", "%p Select"),              input_seq(JOYCODE_SELECT_INDEXED(2)) ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_P3_MAHJONG \
		CORE_INPUT_TYPES_BEGIN(p3_mahjong) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_A,           N_p("input-name", "%p Mahjong A"),           input_seq(KEYCODE_A_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_B,           N_p("input-name", "%p Mahjong B"),           input_seq(KEYCODE_B_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_C,           N_p("input-name", "%p Mahjong C"),           input_seq(KEYCODE_C_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_D,           N_p("input-name", "%p Mahjong D"),           input_seq(KEYCODE_D_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_E,           N_p("input-name", "%p Mahjong E"),           input_seq(KEYCODE_E_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_F,           N_p("input-name", "%p Mahjong F"),           input_seq(KEYCODE_F_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_G,           N_p("input-name", "%p Mahjong G"),           input_seq(KEYCODE_G_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_H,           N_p("input-name", "%p Mahjong H"),           input_seq(KEYCODE_H_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_I,           N_p("input-name", "%p Mahjong I"),           input_seq(KEYCODE_I_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_J,           N_p("input-name", "%p Mahjong J"),           input_seq(KEYCODE_J_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_K,           N_p("input-name", "%p Mahjong K"),           input_seq(KEYCODE_K_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_L,           N_p("input-name", "%p Mahjong L"),           input_seq(KEYCODE_L_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_M,           N_p("input-name", "%p Mahjong M"),           input_seq(KEYCODE_M_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_N,           N_p("input-name", "%p Mahjong N"),           input_seq(KEYCODE_N_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_O,           N_p("input-name", "%p Mahjong O"),           input_seq(KEYCODE_O_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_P,           N_p("input-name", "%p Mahjong P"),           input_seq(KEYCODE_COLON_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_Q,           N_p("input-name", "%p Mahjong Q"),           input_seq(KEYCODE_Q_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_KAN,         N_p("input-name", "%p Mahjong Kan"),         input_seq(KEYCODE_LCONTROL_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_PON,         N_p("input-name", "%p Mahjong Pon"),         input_seq(KEYCODE_LALT_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_CHI,         N_p("input-name", "%p Mahjong Chi"),         input_seq(KEYCODE_SPACE_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_REACH,       N_p("input-name", "%p Mahjong Reach"),       input_seq(KEYCODE_LSHIFT_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_RON,         N_p("input-name", "%p Mahjong Ron"),         input_seq(KEYCODE_Z_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_FLIP_FLOP,   N_p("input-name", "%p Mahjong Flip Flop"),   input_seq(KEYCODE_Y_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_BET,         N_p("input-name", "%p Mahjong Bet"),         input_seq(KEYCODE_3_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_SCORE,       N_p("input-name", "%p Mahjong Take Score"),  input_seq(KEYCODE_RCONTROL_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_DOUBLE_UP,   N_p("input-name", "%p Mahjong Double Up"),   input_seq(KEYCODE_RSHIFT_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_BIG,         N_p("input-name", "%p Mahjong Big"),         input_seq(KEYCODE_ENTER_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_SMALL,       N_p("input-name", "%p Mahjong Small"),       input_seq(KEYCODE_BACKSPACE_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  3, PLAYER3,  MAHJONG_LAST_CHANCE, N_p("input-name", "%p Mahjong Last Chance"), input_seq(KEYCODE_RALT_INDEXED(2)) ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_P4 \
		CORE_INPUT_TYPES_BEGIN(p4) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  JOYSTICK_UP,         N_p("input-name", "%p Up"),                  input_seq(JOYCODE_Y_UP_SWITCH_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  JOYSTICK_DOWN,       N_p("input-name", "%p Down"),                input_seq(JOYCODE_Y_DOWN_SWITCH_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  JOYSTICK_LEFT,       N_p("input-name", "%p Left"),                input_seq(JOYCODE_X_LEFT_SWITCH_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  JOYSTICK_RIGHT,      N_p("input-name", "%p Right"),               input_seq(JOYCODE_X_RIGHT_SWITCH_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  BUTTON1,             N_p("input-name", "%p Button 1"),            input_seq(JOYCODE_BUTTON1_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  BUTTON2,             N_p("input-name", "%p Button 2"),            input_seq(JOYCODE_BUTTON2_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  BUTTON3,             N_p("input-name", "%p Button 3"),            input_seq(JOYCODE_BUTTON3_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  BUTTON4,             N_p("input-name", "%p Button 4"),            input_seq(JOYCODE_BUTTON4_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  BUTTON5,             N_p("input-name", "%p Button 5"),            input_seq(JOYCODE_BUTTON5_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  BUTTON6,             N_p("input-name", "%p Button 6"),            input_seq(JOYCODE_BUTTON6_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  START,               N_p("input-name", "%p Start"),               input_seq(JOYCODE_START_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  SELECT,              N_p("input-name", "%p Select"),              input_seq(JOYCODE_SELECT_INDEXED(3)) ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_P4_MAHJONG \
		CORE_INPUT_TYPES_BEGIN(p4_mahjong) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_A,           N_p("input-name", "%p Mahjong A"),           input_seq(KEYCODE_A_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_B,           N_p("input-name", "%p Mahjong B"),           input_seq(KEYCODE_B_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_C,           N_p("input-name", "%p Mahjong C"),           input_seq(KEYCODE_C_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_D,           N_p("input-name", "%p Mahjong D"),           input_seq(KEYCODE_D_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_E,           N_p("input-name", "%p Mahjong E"),           input_seq(KEYCODE_E_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_F,           N_p("input-name", "%p Mahjong F"),           input_seq(KEYCODE_F_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_G,           N_p("input-name", "%p Mahjong G"),           input_seq(KEYCODE_G_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_H,           N_p("input-name", "%p Mahjong H"),           input_seq(KEYCODE_H_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_I,           N_p("input-name", "%p Mahjong I"),           input_seq(KEYCODE_I_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_J,           N_p("input-name", "%p Mahjong J"),           input_seq(KEYCODE_J_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_K,           N_p("input-name", "%p Mahjong K"),           input_seq(KEYCODE_K_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_L,           N_p("input-name", "%p Mahjong L"),           input_seq(KEYCODE_L_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_M,           N_p("input-name", "%p Mahjong M"),           input_seq(KEYCODE_M_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_N,           N_p("input-name", "%p Mahjong N"),           input_seq(KEYCODE_N_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_O,           N_p("input-name", "%p Mahjong O"),           input_seq(KEYCODE_O_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_P,           N_p("input-name", "%p Mahjong P"),           input_seq(KEYCODE_COLON_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_Q,           N_p("input-name", "%p Mahjong Q"),           input_seq(KEYCODE_Q_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_KAN,         N_p("input-name", "%p Mahjong Kan"),         input_seq(KEYCODE_LCONTROL_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_PON,         N_p("input-name", "%p Mahjong Pon"),         input_seq(KEYCODE_LALT_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_CHI,         N_p("input-name", "%p Mahjong Chi"),         input_seq(KEYCODE_SPACE_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_REACH,       N_p("input-name", "%p Mahjong Reach"),       input_seq(KEYCODE_LSHIFT_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_RON,         N_p("input-name", "%p Mahjong Ron"),         input_seq(KEYCODE_Z_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_FLIP_FLOP,   N_p("input-name", "%p Mahjong Flip Flop"),   input_seq(KEYCODE_Y_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_BET,         N_p("input-name", "%p Mahjong Bet"),         input_seq(KEYCODE_3_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_SCORE,       N_p("input-name", "%p Mahjong Take Score"),  input_seq(KEYCODE_RCONTROL_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_DOUBLE_UP,   N_p("input-name", "%p Mahjong Double Up"),   input_seq(KEYCODE_RSHIFT_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_BIG,         N_p("input-name", "%p Mahjong Big"),         input_seq(KEYCODE_ENTER_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_SMALL,       N_p("input-name", "%p Mahjong Small"),       input_seq(KEYCODE_BACKSPACE_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  4, PLAYER4,  MAHJONG_LAST_CHANCE, N_p("input-name", "%p Mahjong Last Chance"), input_seq(KEYCODE_RALT_INDEXED(3)) ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_START \
		CORE_INPUT_TYPES_BEGIN(start) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    START1,              N_p("input-name", "1 Player Start"),         input_seq(KEYCODE_1, input_seq::or_code, JOYCODE_START_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    START2,              N_p("input-name", "2 Players Start"),        input_seq(KEYCODE_2, input_seq::or_code, JOYCODE_START_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    START3,              N_p("input-name", "3 Players Start"),        input_seq(JOYCODE_START_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    START4,              N_p("input-name", "4 Players Start"),        input_seq(JOYCODE_START_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    START5,              N_p("input-name", "5 Players Start"),        input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    START6,              N_p("input-name", "6 Players Start"),        input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    START7,              N_p("input-name", "7 Players Start"),        input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    START8,              N_p("input-name", "8 Players Start"),        input_seq() ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_COIN \
		CORE_INPUT_TYPES_BEGIN(coin) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    COIN1,               N_p("input-name", "Coin 1"),                 input_seq(KEYCODE_5, input_seq::or_code, JOYCODE_SELECT_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    COIN2,               N_p("input-name", "Coin 2"),                 input_seq(KEYCODE_6, input_seq::or_code, JOYCODE_SELECT_INDEXED(1)) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    COIN3,               N_p("input-name", "Coin 3"),                 input_seq(KEYCODE_7, input_seq::or_code, JOYCODE_SELECT_INDEXED(2)) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    COIN4,               N_p("input-name", "Coin 4"),                 input_seq(KEYCODE_8, input_seq::or_code, JOYCODE_SELECT_INDEXED(3)) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    BILL1,               N_p("input-name", "Bill 1"),                 input_seq() ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_SERVICE \
		CORE_INPUT_TYPES_BEGIN(service) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    SERVICE1,            N_p("input-name", "Service 1"),              input_seq(KEYCODE_0) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    SERVICE2,            N_p("input-name", "Service 2"),              input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    SERVICE3,            N_p("input-name", "Service 3"),              input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    SERVICE4,            N_p("input-name", "Service 4"),              input_seq() ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_TILT \
		CORE_INPUT_TYPES_BEGIN(tilt) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    TILT1,               N_p("input-name", "Tilt 1"),                 input_seq(KEYCODE_T) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    TILT2,               N_p("input-name", "Tilt 2"),                 input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    TILT3,               N_p("input-name", "Tilt 3"),                 input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    TILT4,               N_p("input-name", "Tilt 4"),                 input_seq() ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_OTHER \
		CORE_INPUT_TYPES_BEGIN(other) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    POWER_ON,            N_p("input-name", "Power On"),               input_seq(KEYCODE_F1) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    POWER_OFF,           N_p("input-name", "Power Off"),              input_seq(KEYCODE_F2) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    SERVICE,             N_p("input-name", "Service"),                input_seq(KEYCODE_0) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    TILT,                N_p("input-name", "Tilt"),                   input_seq(KEYCODE_T) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    INTERLOCK,           N_p("input-name", "Door Interlock"),         input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    MEMORY_RESET,        N_p("input-name", "Memory Reset"),           input_seq(KEYCODE_F1) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    VOLUME_DOWN,         N_p("input-name", "Volume Down"),            input_seq(KEYCODE_MINUS) ) \
		INPUT_PORT_DIGITAL_TYPE(  0, OTHER,    VOLUME_UP,           N_p("input-name", "Volume Up"),              input_seq(KEYCODE_EQUALS) ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_UI \
		CORE_INPUT_TYPES_BEGIN(ui) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_ON_SCREEN_DISPLAY, N_p("input-name", "On Screen Display"),      input_seq(KEYCODE_TILDE, input_seq::not_code, KEYCODE_LSHIFT, input_seq::not_code, KEYCODE_RSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_DEBUG_BREAK,       N_p("input-name", "Break in Debugger"),      input_seq(KEYCODE_TILDE, input_seq::not_code, KEYCODE_LSHIFT, input_seq::not_code, KEYCODE_RSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_CONFIGURE,         N_p("input-name", "Config Menu"),            input_seq(KEYCODE_TAB) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_PAUSE,             N_p("input-name", "Pause"),                  input_seq(KEYCODE_P, input_seq::not_code, KEYCODE_LSHIFT, input_seq::not_code, KEYCODE_RSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_PAUSE_SINGLE,      N_p("input-name", "Pause - Single Step"),    input_seq(KEYCODE_P, KEYCODE_LSHIFT, input_seq::or_code, KEYCODE_P, KEYCODE_RSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_REWIND_SINGLE,     N_p("input-name", "Rewind - Single Step"),   input_seq(KEYCODE_TILDE, KEYCODE_LSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_RESET_MACHINE,     N_p("input-name", "Reset Machine"),          input_seq(KEYCODE_F3, KEYCODE_LSHIFT, input_seq::or_code, KEYCODE_F3, KEYCODE_RSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_SOFT_RESET,        N_p("input-name", "Soft Reset"),             input_seq(KEYCODE_9) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_SHOW_GFX,          N_p("input-name", "Show Decoded Graphics"),  input_seq(KEYCODE_F4) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_FRAMESKIP_DEC,     N_p("input-name", "Frameskip Dec"),          input_seq(KEYCODE_F8) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_FRAMESKIP_INC,     N_p("input-name", "Frameskip Inc"),          input_seq(KEYCODE_F9) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_THROTTLE,          N_p("input-name", "Throttle"),               input_seq(KEYCODE_LALT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_FAST_FORWARD,      N_p("input-name", "Fast Forward"),           input_seq(KEYCODE_BACKSPACE) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_SHOW_FPS,          N_p("input-name", "Show FPS"),               input_seq(KEYCODE_LALT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_SNAPSHOT,          N_p("input-name", "Save Snapshot"),          input_seq(KEYCODE_F12, input_seq::not_code, KEYCODE_LSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_RECORD_MNG,        N_p("input-name", "Record MNG"),             input_seq(KEYCODE_F12, KEYCODE_LSHIFT, input_seq::not_code, KEYCODE_LCONTROL) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_RECORD_AVI,        N_p("input-name", "Record AVI"),             input_seq(KEYCODE_F12, KEYCODE_LSHIFT, KEYCODE_LCONTROL) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_TOGGLE_CHEAT,      N_p("input-name", "Toggle Cheat"),           input_seq(KEYCODE_F6) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_UP,                N_p("input-name", "UI Up"),                  input_seq(KEYCODE_UP, input_seq::or_code, JOYCODE_Y_UP_SWITCH_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_DOWN,              N_p("input-name", "UI Down"),                input_seq(KEYCODE_DOWN, input_seq::or_code, JOYCODE_Y_DOWN_SWITCH_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_LEFT,              N_p("input-name", "UI Left"),                input_seq(KEYCODE_LEFT, input_seq::or_code, JOYCODE_X_LEFT_SWITCH_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_RIGHT,             N_p("input-name", "UI Right"),               input_seq(KEYCODE_RIGHT, input_seq::or_code, JOYCODE_X_RIGHT_SWITCH_INDEXED(0)) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_HOME,              N_p("input-name", "UI Home"),                input_seq(KEYCODE_HOME) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_END,               N_p("input-name", "UI End"),                 input_seq(KEYCODE_END) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_PAGE_UP,           N_p("input-name", "UI Page Up"),             input_seq(KEYCODE_PGUP) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_PAGE_DOWN,         N_p("input-name", "UI Page Down"),           input_seq(KEYCODE_PGDN) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_FOCUS_NEXT,        N_p("input-name", "UI Focus Next"),          input_seq(KEYCODE_TAB, input_seq::not_code, KEYCODE_LSHIFT, input_seq::not_code, KEYCODE_RSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_FOCUS_PREV,        N_p("input-name", "UI Focus Previous"),      input_seq(KEYCODE_TAB, KEYCODE_LSHIFT, input_seq::or_code, KEYCODE_TAB, KEYCODE_RSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_SELECT,            N_p("input-name", "UI Select"),              input_seq(KEYCODE_ENTER, input_seq::not_code, KEYCODE_LALT, input_seq::not_code, KEYCODE_RALT, input_seq::or_code, JOYCODE_BUTTON1_INDEXED(0), input_seq::or_code, KEYCODE_ENTER_PAD) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_CANCEL,            N_p("input-name", "UI Cancel"),              input_seq(KEYCODE_ESC) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_DISPLAY_COMMENT,   N_p("input-name", "UI Display Comment"),     input_seq(KEYCODE_SPACE) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_CLEAR,             N_p("input-name", "UI Clear"),               input_seq(KEYCODE_DEL) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_ZOOM_IN,           N_p("input-name", "UI Zoom In"),             input_seq(KEYCODE_EQUALS) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_ZOOM_OUT,          N_p("input-name", "UI Zoom Out"),            input_seq(KEYCODE_MINUS) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_ZOOM_DEFAULT,      N_p("input-name", "UI Default Zoom"),        input_seq(KEYCODE_0) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_PREV_GROUP,        N_p("input-name", "UI Previous Group"),      input_seq(KEYCODE_OPENBRACE) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_NEXT_GROUP,        N_p("input-name", "UI Next Group"),          input_seq(KEYCODE_CLOSEBRACE) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_ROTATE,            N_p("input-name", "UI Rotate"),              input_seq(KEYCODE_R) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_SHOW_PROFILER,     N_p("input-name", "Show Profiler"),          input_seq(KEYCODE_F11, KEYCODE_LSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_TOGGLE_UI,         N_p("input-name", "UI Toggle"),              input_seq(KEYCODE_SCRLOCK, input_seq::not_code, KEYCODE_LSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_RELEASE_POINTER,   N_p("input-name", "UI Release Pointer"),     input_seq(KEYCODE_RCONTROL, KEYCODE_RALT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_PASTE,             N_p("input-name", "UI Paste Text"),          input_seq(KEYCODE_SCRLOCK, KEYCODE_LSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_SAVE_STATE,        N_p("input-name", "Save State"),             input_seq(KEYCODE_7) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_LOAD_STATE,        N_p("input-name", "Load State"),             input_seq(KEYCODE_8) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_TAPE_START,        N_p("input-name", "UI (First) Tape Start"),  input_seq(KEYCODE_F2, input_seq::not_code, KEYCODE_LSHIFT, input_seq::not_code, KEYCODE_RSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_TAPE_STOP,         N_p("input-name", "UI (First) Tape Stop"),   input_seq(KEYCODE_F2, KEYCODE_LSHIFT) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_DATS,              N_p("input-name", "UI External DAT View"),   input_seq(KEYCODE_LALT, KEYCODE_D) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_FAVORITES,         N_p("input-name", "UI Add/Remove favorite"), input_seq(KEYCODE_LALT, KEYCODE_F) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_EXPORT,            N_p("input-name", "UI Export List"),         input_seq(KEYCODE_LALT, KEYCODE_E) ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       UI_AUDIT,             N_p("input-name", "UI Audit Media"),         input_seq(KEYCODE_F1, input_seq::not_code, KEYCODE_LSHIFT, input_seq::not_code, KEYCODE_RSHIFT) ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_OSD \
		CORE_INPUT_TYPES_BEGIN(osd) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_1,               nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_2,               nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_3,               nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_4,               nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_5,               nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_6,               nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_7,               nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_8,               nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_9,               nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_10,              nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_11,              nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_12,              nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_13,              nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_14,              nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_15,              nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, UI,       OSD_16,              nullptr,                     input_seq() ) \
		CORE_INPUT_TYPES_END()

#define CORE_INPUT_TYPES_INVALID \
		CORE_INPUT_TYPES_BEGIN(invalid) \
		INPUT_PORT_DIGITAL_TYPE( 0, INVALID,  UNKNOWN,             nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, INVALID,  UNUSED,              nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, INVALID,  SPECIAL,             nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, INVALID,  OTHER,               nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, INVALID,  ADJUSTER,            nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, INVALID,  DIPSWITCH,           nullptr,                     input_seq() ) \
		INPUT_PORT_DIGITAL_TYPE( 0, INVALID,  CONFIG,              nullptr,                     input_seq() ) \
		CORE_INPUT_TYPES_END()


ATTR_COLD void emplace_core_digital_type(std::vector<input_type_entry> &typelist, ioport_type type, ioport_group group, int player, const char *token, const char *name, input_seq seq)
{
	typelist.emplace_back(type, group, (player == 0) ? player : (player - 1), token, name, seq);
}

// instantiate the contruct functions
#define CORE_INPUT_TYPES_BEGIN(_name) \
		ATTR_COLD inline void emplace_core_types_##_name(std::vector<input_type_entry> &typelist) \
		{
#define INPUT_PORT_DIGITAL_TYPE(_player, _group, _type, _name, _seq) \
		emplace_core_digital_type(typelist, IPT_##_type, IPG_##_group, _player, (_player == 0) ? #_type : ("P" #_player "_" #_type), _name, _seq);
#define CORE_INPUT_TYPES_END() \
		}
CORE_INPUT_TYPES_P1
CORE_INPUT_TYPES_P1_MAHJONG
CORE_INPUT_TYPES_P2
CORE_INPUT_TYPES_P2_MAHJONG
CORE_INPUT_TYPES_P3
CORE_INPUT_TYPES_P3_MAHJONG
CORE_INPUT_TYPES_P4
CORE_INPUT_TYPES_P4_MAHJONG
CORE_INPUT_TYPES_START
CORE_INPUT_TYPES_COIN
CORE_INPUT_TYPES_SERVICE
CORE_INPUT_TYPES_TILT
CORE_INPUT_TYPES_OTHER
CORE_INPUT_TYPES_UI
CORE_INPUT_TYPES_OSD
CORE_INPUT_TYPES_INVALID
#undef CORE_INPUT_TYPES_BEGIN
#undef INPUT_PORT_DIGITAL_TYPE
#undef INPUT_PORT_ANALOG_TYPE
#undef CORE_INPUT_TYPES_END


// make a count function so we don't have to reallocate the vector
#define CORE_INPUT_TYPES_BEGIN(_name)
#define INPUT_PORT_DIGITAL_TYPE(_player, _group, _type, _name, _seq) + 1
#define INPUT_PORT_ANALOG_TYPE(_player, _group, _type, _name, _seq, _decseq, _incseq) + 1
#define CORE_INPUT_TYPES_END()
constexpr size_t core_input_types_count()
{
	return 0
			CORE_INPUT_TYPES_P1
			CORE_INPUT_TYPES_P1_MAHJONG
			CORE_INPUT_TYPES_P2
			CORE_INPUT_TYPES_P2_MAHJONG
			CORE_INPUT_TYPES_P3
			CORE_INPUT_TYPES_P3_MAHJONG
			CORE_INPUT_TYPES_P4
			CORE_INPUT_TYPES_P4_MAHJONG
			CORE_INPUT_TYPES_START
			CORE_INPUT_TYPES_COIN
			CORE_INPUT_TYPES_SERVICE
			CORE_INPUT_TYPES_TILT
			CORE_INPUT_TYPES_OTHER
			CORE_INPUT_TYPES_UI
			CORE_INPUT_TYPES_OSD
			CORE_INPUT_TYPES_INVALID
			;
}
#undef CORE_INPUT_TYPES_BEGIN
#undef INPUT_PORT_DIGITAL_TYPE
#undef INPUT_PORT_ANALOG_TYPE
#undef CORE_INPUT_TYPES_END


ATTR_COLD inline void emplace_core_types(std::vector<input_type_entry> &typelist)
{
	typelist.reserve(core_input_types_count());

	emplace_core_types_p1(typelist);
	emplace_core_types_p1_mahjong(typelist);
	emplace_core_types_p2(typelist);
	emplace_core_types_p2_mahjong(typelist);
	emplace_core_types_p3(typelist);
	emplace_core_types_p3_mahjong(typelist);
	emplace_core_types_p4(typelist);
	emplace_core_types_p4_mahjong(typelist);
	emplace_core_types_start(typelist);
	emplace_core_types_coin(typelist);
	emplace_core_types_service(typelist);
	emplace_core_types_tilt(typelist);
	emplace_core_types_other(typelist);
	emplace_core_types_ui(typelist);
	emplace_core_types_osd(typelist);
	emplace_core_types_invalid(typelist);
}

} // anonymous namespace

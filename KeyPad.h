/*
 * KeyPad.h
 *
 *  Created on: Aug 15, 2023
 *      Author: Ahmed Abdelmotelb Ali
 */

#ifndef HAL_KEYPAD_KEYPAD_H_
#define HAL_KEYPAD_KEYPAD_H_

#include "DIO.h"
#include <avr/delay.h>


#define ROW_PORT  GROUP_B
#define COL_PORT  GROUP_B

#define ROW0  4
#define ROW1  5
#define ROW2  6
#define ROW3  7

#define COL0 0
#define COL1 1
#define COL2 2
#define COL3 3

# define STD_TYPES_OK					1
# define STD_TYPES_NOK					0
#define KPD_u8_KEY_NOT_PRESSED        0xff





/**
 * @brief : this function Set The PINS DIRECTION
 */
void KeyPad_vInit();
u8 KeyPad_getKeyPressed();
#define Not_pressed		'\0'


#endif /* HAL_KEYPAD_KEYPAD_H_ */

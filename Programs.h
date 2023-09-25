/*
 * IncFile1.h
 *
 * Created: 9/3/2023 12:56:20 PM
 *  Author: Ahmed Abdelmotelb Ali
 */ 


#ifndef Programs_H_
#define Programs_H_
#include "DIO.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "LCD.h"
#include "KeyPad.h"
#define BEEF_DEFROST_RATE 30
#define CHICKEN_DEFROST_RATE 12
#define sw3_1		GROUP_D
#define sw1_2		GROUP_D
#define sw2_0		GROUP_D
#define LED		    GROUP_C
void init_servo();
void External_LED_line_Init();
void Buzzer_Init(void); // to intialize the buzzer
void External_Button_Init(void); // to intialize the push button
void SW1_Interrupt(void); //for SW1 interrupt conditions
void SW3_Interrupt(void); //for SW2 interrupt condition
void Program_A(void) ; //for popcorn
void Program_B_or_C(uint8_t key); //for beef and chicken
void Program_D(void); //for others
void Program_Finish(void); //the finishing program is for LEDs and buzzer in the end
uint8_t Oven_Ready(void); //to check if the door is closed and SW2 is pressed
void Turn_on_LEDs(void); //to turn on the three LEDs in the microcontroller
void Turn_off_LEDs(void); //to turn off the three LEDs in the microcontroller
void tuneBuzzer(void); //a function to use the buzzer
#endif /* INCFILE1_H_ */
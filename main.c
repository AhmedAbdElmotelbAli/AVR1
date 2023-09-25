/*
 * assignment_AVR_Ahmed Abdelmotelb Ali.c
 *
 * Created: 8/23/2023 2:49:44 PM
 * Author : Ahmed Abdelmotelb Ali
 */ 

#include <avr/io.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "KeyPad.h"
#include "LCD.h"
#include "DIO.h"
#include "INT.h"
#include "Programs.h"
#include "TIMER.h"

int main(void)
{
	init_servo();
    KeyPad_vInit();
	 LCD_vidInit();
	 External_LED_line_Init();
	 Buzzer_Init(); //intialize the buzzer
	 External_Button_Init(); //initialize the external button
	 INT_vInitINT1();
	 INT_vInitINT0();
     INT_vSetCallBackToINT0(SW1_Interrupt);
	 INT_vSetCallBackToINT1(SW3_Interrupt); 
	  uint8_t choice;
	  uint8_t i =0;//flag for printing begining word
	while (1)
	{
		if(i == 0)
		 LCD_vidWriteString("Choose program(A-B-C-D)",strlen("Choose program(A-B-C-D)"));
		 i=1;
		choice = KeyPad_getKeyPressed();
		switch(choice) //keypad input from the user to choose which program to execute
			{
				 case 'A': //if user presses on key A then  make microwave execute  Program_A for popcorn
				 i=0;
				 Program_A();
				 break; //break statement prevents executing more than 1 program in a single run
				 case 'B': //if user presses on key B then  make microwave execute  Program_B for beef
				 i=0;
				 Program_B_or_C('B') ;
				 break;
				 case 'C': //if user presses on key C then  make microwave execute  Program_C for chicken
				 i=0;
				 Program_B_or_C('C') ;
				 break;
				 case  'D': //if user presses on key D then  make microwave execute  Program_D for other food
				 i=0;
				 Program_D() ;
				 break;
	 
		   }
				
	}
			return 0;
}


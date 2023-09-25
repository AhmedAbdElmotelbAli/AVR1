/*
a * KeyPad.c
 *
 *  Created on: Aug 15, 2023
 *      Author: Ahmed Abdelmotelb
 */

#include "KeyPad.h"

u8 KeyMap[4][4]={
		{'7','4','1','c'},
		{'8','5','2','0'},
		{'9','6','3','='},	
		{'A','B','C','D'}
};


void KeyPad_vInit(){
	//SET COLS PIN TO BE OUTPUT
	setPinDir(COL_PORT,COL0,OUTPUT);
	setPinDir(COL_PORT,COL1,OUTPUT);
	setPinDir(COL_PORT,COL2,OUTPUT);
	setPinDir(COL_PORT,COL3,OUTPUT);

	//SET COLS TO BE HIGH
	setPinVal(COL_PORT,COL0,HIGH);
	setPinVal(COL_PORT,COL1,HIGH);
	setPinVal(COL_PORT,COL2,HIGH);
	setPinVal(COL_PORT,COL3,HIGH);

	//SET ROWS TO BE INPUT
	setPinDir(ROW_PORT,ROW0,INPUT);
	setPinDir(ROW_PORT,ROW1,INPUT);
	setPinDir(ROW_PORT,ROW2,INPUT);
	setPinDir(ROW_PORT,ROW3,INPUT);


	//SET ROWS  PULL UP
	setPinVal(ROW_PORT,ROW0,HIGH);
	setPinVal(ROW_PORT,ROW1,HIGH);
	setPinVal(ROW_PORT,ROW2,HIGH);
	setPinVal(ROW_PORT,ROW3,HIGH);

}


u8 KeyPad_getKeyPressed(){
	u8 c=Not_pressed;
	for(u8 col=0+COL0; col<=COL3;col++){
		setPinVal(COL_PORT,col,LOW);
		for(u8 row=0+ROW0;row<=ROW3;row++){
			if(getPinVal(ROW_PORT,row)==0){

				while(getPinVal(ROW_PORT,row)==0);
				_delay_ms(20);

				setPinVal(COL_PORT,col,HIGH);
				c=KeyMap[row-ROW0][col-COL0];
				return c;
			}
		}
		setPinVal(COL_PORT,col,HIGH);
	}
	return c;
}

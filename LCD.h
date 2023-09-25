#ifndef LCD_H
#define LCD_H
#include "DIO.h"
#include <avr/delay.h>



#define DATA_PINS  GROUP_A
#define CTRL_PINS  GROUP_C
#define EN 7
#define RW 6
#define RS 5

//define some command


#define FUNC_SET1 0x30  //8-bit 1-line operation mode
#define FUNC_SET2 0x38  //8-bit 2-lines operation mode
#define CLR_CMD 0x01    //clear the display command 


///DISPALY ON/OFF - CURSOR ON/OFF COMMANDS
#define DIS_OFF_CURS_OFF		0x08
#define DIS_ON_CURS_OFF			0x0C
#define DIS_ON_CURS_ON			0x0E
#define DIS_ON_CURS_BLINK		0x0F
#define shift_display_left	    0x18
#define shift_display_right	    0x1D

#define RET_HOME            0x02          /* return cursor to first position on first line                   */
#define ENTRY_MODE          0x06          // shift cursor from left to right on read/write


#define ROW_1               0x80        //Address of the first row
#define ROW_2               0xC0        //Address of the Second row

#define CGRAM               0x40
#define Shift_R				1
#define Shift_l				0

/**
 * @brief : Initalization function for the LCD
 * 
 */
void LCD_vidInit(void);

/**
 * @brief : this function is to send commands to the lcd
 * @param CMD : the command that we want the lcd to perform
 */
void LCD_vidSendCMD(u8 CMD);

/**
 * @brief : This fucntion display 1 character in LCD 
 * 
 * @param char : the char i want to display on LCD
 */

void LCD_vidSendChar(u8 chr);

/**
 * @brief :this funtion ,moves the cursor and AC position without changing or deleting 
 *          the content of the DDRAM
 * 
 * @param row   the row to go FIRST OR SECOND
 * @param col   col to go we have 16 col from 0 to 15
 */
void LCD_gotoRowCol(u8 row,u8 col);

/**
 * @brief :this function displays a whole string on screen
 * 
 * @param str : the string to be displayed
 */

void LCD_DisplayStr(u8* str);

/**
 * @brief :this function convert interger 4 bytes number to string of charaters and display it
 * 
 * @param number : the number to be displayed
 */
void LCD_DisplayInt(u32 number);
/**
 * @brief :this function shift to String
 * 
 * @param number : move 
 */
void LCD_shiftStr(u8 numberOfMove,u8 shift);


/**
 * @brief  this function stores a given pattern in the CGRAM at a gvien Index
 * 
 * @param pattern  pattern to be stored
 * @param CGRAM_index index in the CGRAM to be stored at
 */
void LCD_StoreCustomChr (u8* pattern , u8 CGRAM_index);

/**
 * @brief this fucntion displays custome charcter stored before at this given cgram address
 * 
 * @param CGRAM_index  cgram index where the charcter to be displayed
 */
void LCD_DisplayCustomeChar(u8 CGRAM_index);






void LCD_vidCountDown(int16_t timer, uint8_t isStandardForm);



// Take 4-digit input from the user and return the input.
uint16_t LCD_u16TakeInput(void);


#endif

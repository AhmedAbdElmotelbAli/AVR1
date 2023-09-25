#include "LCD.h"

void LCD_vidInit(void){
    //set data pins direction to be output pins
    setGrpDir(DATA_PINS,0xFF);
    //set CTRL pins to be output pins
    setPinDir(CTRL_PINS,RS,HIGH);
    setPinDir(CTRL_PINS,RW,HIGH);
    setPinDir(CTRL_PINS,EN,HIGH);

    //set 30 ms delay (required by the data sheet)
    _delay_ms(30);

    //Send Command Function Set
    //Intialized in 8-bit mode operation , 2-Lines 5x7 Dot Font
    LCD_vidSendCMD(FUNC_SET2);
    //delay after send command
    _delay_ms(1);



    LCD_vidSendCMD(DIS_ON_CURS_BLINK);
    //delay after send command
    _delay_ms(1);



    //CLEAR THE LCD
    LCD_vidSendCMD(CLR_CMD);
    //delay after send command
    _delay_ms(10);


    //Send Command :configure the cursor and the Address counter to auto incremnted
    //after display and shift from left to right
    LCD_vidSendCMD(ENTRY_MODE);
    //delay after send command
    _delay_ms(10);

}

void LCD_vidSendCMD(u8 CMD){
    //write commands on data pins
    setGrpVal(DATA_PINS,CMD);

    //SET COMMAND MODE
    setPinVal(CTRL_PINS,RS,LOW);

    //CHOOSE WRITE MODE
    setPinVal(CTRL_PINS,RW,LOW);


    //make falling edge for en
    setPinVal(CTRL_PINS,EN,HIGH);
    _delay_ms(2);
    setPinVal(CTRL_PINS,EN,LOW);

    //Delay to settele
    _delay_ms(10);
}


void LCD_vidSendChar(u8 Chr){
    //write data on data pins
    setGrpVal(DATA_PINS,Chr);

    //SET DATA MODE
    setPinVal(CTRL_PINS,RS,HIGH);

    //CHOOSE WRITE MODE
    setPinVal(CTRL_PINS,RW,LOW);


    //make falling edge for en
    setPinVal(CTRL_PINS,EN,HIGH);
    _delay_ms(2);
    setPinVal(CTRL_PINS,EN,LOW);

    //Delay to settele
    _delay_ms(50);
}


void LCD_gotoRowCol(u8 row,u8 col){

    //only 15 cols
    if(col>=0&&col<16){
        switch (row)
        {
        case ROW_1:
            /* code */
            LCD_vidSendCMD(ROW_1+col);
            break;
        case ROW_2:
            LCD_vidSendCMD(ROW_2+col);
            break;
        default:
            break;
        }
    }
}


void LCD_DisplayStr(u8* str)
{
	while(*str != '\0')
	{
        //send char by char
		LCD_vidSendChar(*str);
		str++;
	}
}

void LCD_shiftStr(u8 numberOfMove,u8 shift)
{
	u8 move= numberOfMove;
	switch(shift)
	{
	case Shift_l :
	while(move)
		{
			move--;
			LCD_vidSendCMD(shift_display_left);
			_delay_ms(500);
		}
	break;
	case Shift_R :
	while(move)
		{
			move--;
			LCD_vidSendCMD(shift_display_right);
			_delay_ms(500);
		}
	break;
	
	}
}




void LCD_DisplayInt(u32 number){

	u8 arr_new[11];		//The max value of u32 has ten digits
	u8 arr1[11], i = 0, j;
	if(number == 0)
	{
		LCD_DisplayStr("0");
		return;
	}

	while(number != 0)
	{
		arr1[i] = (number % 10) + 0x30;
		number /= 10;
		i++;
	}

	i--;
	j = 0;
	while(i < 11) //After it reaches zero
	{
		arr_new[j] = arr1[i];
		j++;
		i--;
	}

	arr_new[j] = '\0';

	LCD_DisplayStr(arr_new);
    
}


void LCD_vidWriteString(unsigned char* string, uint8_t stringSize) {
	uint8_t i;
	for (i = 0; i < stringSize; i++) {
		if (i == 16) LCD_gotoRowCol(ROW_2,0);
		LCD_vidSendChar(string[i]);
	}
}


void LCD_StoreCustomChr (u8* pattern , u8 CGRAM_index)
{
   
    if (CGRAM_index < 8){
     
       LCD_vidSendCMD(CGRAM+CGRAM_index*8);
    }
    for (u8 i = 0 ; i < 8 ; i++){
        LCD_vidSendChar(pattern[i]);

    }
    LCD_vidSendCMD(RET_HOME);
}



void LCD_DisplayCustomeChar(u8 CGRAM_index){
    LCD_vidSendChar(CGRAM_index);
}
	
void printTimer(uint8_t* timer) {
		// Loop 4 times as the timer consist of 4 digits.
		uint8_t i;
		LCD_gotoRowCol(ROW_2 , 3) ;				// To take the input in the bottom-right corner of the screen and keep the already wirtten data unchaged.
		for (i = 0; i < 4; i++) {
			if (i == 2)   LCD_vidSendChar(':');
			LCD_vidSendChar(timer[i]);
		}
	}
void LCD_vidCountDown(int16_t timer, uint8_t isStandardForm)
{
/* 
	you have to input the time as minutesSeconds, ex: 1234 is 12 minutes 34 seconds , 123 is 1 minutes 23 seconds
	or as a minutes only format as its converted by the MinToTimerStandard function ex:4.5 becomes 430.
*/ 
	int8_t min, sec;
	
	if (isStandardForm == 0) {
		timer = ((timer / 60) * 100) + (timer % 60); // Converting the seconds form to standard form needed here.
	}

	min = timer / 100, sec = (int16_t)timer % 100; 		// divide the lower 2 digits to seconds and upper 2 digits to minutes
					
	while (min > -1) { 									// keeps looping till the minutes reach 0
		while (sec > -1) { 								// keeps looping till the seconds reach 0
			int8_t temp = min;
			
			LCD_gotoRowCol(ROW_2, 3);						// To count in the bottom-right corner of the screen and keep the already wirtten data unchaged.
			LCD_vidSendChar((temp / 10) + '0');
			LCD_vidSendChar((temp % 10) + '0');
			LCD_vidSendChar(':');
			if (sec < 10) { 							// If the seconds are in the units write a 0 before it
				LCD_vidSendChar('0');
				LCD_vidSendChar(sec + '0');
			}
			else { 										// If not write the string normally
				int8_t temp = sec;
				LCD_vidSendChar((temp / 10) + '0');
				LCD_vidSendChar((temp % 10) + '0');
			}
			
			_delay_ms(1000); 					// wait a second to decrement a unit digit in the seconds			
			sec--; 
			LCD_gotoRowCol(ROW_1, 1);
		}
		sec = 59;										// set the seconds to a whole minute
		min--;
	}
	

}
uint16_t convertTimerToInt(uint8_t* timer){
	uint8_t i;
	uint16_t timerInt = 0;
	for (i = 0; i < 4; i++) {
		uint16_t currentDigit = timer[i] - '0';
		if (i == 0)
		timerInt += (currentDigit * 1000);
		else if (i == 1)
		timerInt += (currentDigit * 100);
		else if (i == 2)
		timerInt += (currentDigit * 10);
		else if (i == 3)
		timerInt += currentDigit;
	}
	return timerInt;
}
void shiftTimerLeft(uint8_t* timer) {
	uint8_t i;
	for (i = 1; i < 4; i++) {
		timer[i - 1] = timer[i];
	}
}
uint16_t validateInput(uint8_t* timer){
	// If the user inputed a valid number the function returns it, else it returns 0.
	uint8_t i;
	uint16_t timerInt = 0;
	uint16_t temp_validator = 0;
	
	// Check for letters.
	for(i = 0 ; i < 4; i++){
		if(timer[i] < '0' || timer[i] > '9')
		return timerInt;
	}
	
	// Ensure that seconds <= 59.
	if(timer[2] > '5')
	return timerInt;
	
	// Ensure that timer in range (1 sec to 30 min)
	temp_validator = convertTimerToInt(timer);
	if( temp_validator < 1 || temp_validator > 3000)
	return timerInt;
	else
	timerInt = temp_validator;
	
	return timerInt;
}
uint16_t LCD_u16TakeInput(void){
/* 
	 This function takes 4-digit (numbers) input from the user for example (1, 2, 3, 4)
	 Important note(1): user must enter the numbers from left to right 1 -> 2 -> 3 -> 4 
	 this produces the number 1234 which is 12 minutes and 34 seconds.
	 Important note(2): the 4-digit input must be less than or equal 3000, if bigger 
	 the function returns 0.
*/
		uint16_t timerInt = 0;
	 	uint8_t i;
		uint8_t currentInput;
		uint16_t InputResult; 
		
	// Create a timer.
	uint8_t timer[4] = {'0', '0', '0', '0'};
	
	// Print the current status of the timer to the screen [ 00:00 ].
	printTimer(timer);

	// Loop 4 times to read from the keypad.

	for (i = 0; i < 4; i++) {
		uint8_t pressedButton = '\0';
		
		// Wait till the user press a button
		while (pressedButton == '\0') {
			pressedButton = KeyPad_getKeyPressed();
		}

		// Convert pressedButton to char to print on the screen, then add it to the right most cell in the timer.
		currentInput = pressedButton ;
		timer[3] = currentInput;

		// Print the timer with the new input on the LCD. 
		// For example the user pressed 1 >>>> screen shows [ 00:01 ]
		
		printTimer(timer);

		// Shift the timer digits left to take the next input except for the last iteration.
		if (i < 3)
			shiftTimerLeft(timer);
	}
	
	InputResult = validateInput(timer);
	return InputResult;
}

/*
 * CFile1.c
 *
 * Created: 9/3/2023 1:00:23 PM
 *  Author:Ahmed Abdelmotelb Ali 
 */ 
#include "programs.h"
#include "TIMER.h"
#include "LCD.h"
uint8_t isCooking=0 ;

void init_servo(){
	setPinDir(GROUP_D,5,OUTPUT);
	Timer1_vInit(TIMER_PRESCALER_8,TIMER_FAST_PWM_ICR1_MODE,0,TIMER_OC1A_PWM_NON_INV,0,CHANNEL_A);
	Timer1_vSetICR1(2000);	
}
void stop_servo(){
	Timer1_setOCR1x(0,CHANNEL_A);
}
void rotate_servo(){
			//ROTATE ACW
		   Timer1_setOCR1x(1000,CHANNEL_A);
			_delay_ms(200);
			//SET TO 0 POSITION
			Timer1_setOCR1x(0,CHANNEL_A);
			_delay_ms(200);
     		//ROTAE CW
			Timer1_setOCR1x(1000,CHANNEL_A);
	    	_delay_ms(200);
	
}
void workservo(){
	rotate_servo();
	rotate_servo();	
    rotate_servo();
}
void External_LED_line_Init()
{
	
	int i;
for(i = 1 ; i<= 3 ; i++ ){
	setPinDir(LED, i, HIGH); //output
	setPinVal(LED, i, LOW);//activate pull up resistor of pin
	}

}
void External_Button_Init()
{

	setPinDir(sw2_0, 0, LOW); //input
	setPinVal(sw2_0, 0, HIGH);//activate pull up resistor of pin

}
void Buzzer_Init()
{
	setPinDir(GROUP_C, 0, 1); //output

}




void Program_A()
{
	
	LCD_vidSendCMD(CLR_CMD);
	LCD_vidWriteString("Popcorn", strlen("Popcorn")); //display popcorn on LCD
	_delay_ms(2000);

	while(Oven_Ready() == 0); //wait until oven is ready (door closed and SW2 pressed)
	isCooking = 1 ;
	Turn_on_LEDs() ;
	workservo();
	LCD_vidCountDown(100,1); //wait for 1 minute (input entered in format (1:00) which is the standard form
	
	Program_Finish() ; //finsihing  program for microwave
}

void Program_B_or_C(uint8_t key) //this program works for choices B or C
{
	
	uint8_t defrost_rate ; //in minutes per kilogram
	uint16_t kilograms = '\0'; //the button entered represents the number of kilograms
	LCD_vidSendCMD(CLR_CMD);
	Repeat:  if(key == 'B') //in case keypad button 'B' is pressed ,
	{
		
		LCD_vidWriteString("Beef Weight?" , strlen("Beef Weight?") ); //then display the beef weight
		defrost_rate = BEEF_DEFROST_RATE; //set the defrost_rate to be 0.5
	}
	else if(key == 'C') //in case keypad button 'C' is pressed ,
	{
		LCD_vidWriteString("Chicken Weight?" , strlen("Chicken Weight?")); //then display the beef weight
		defrost_rate =  CHICKEN_DEFROST_RATE ; //set the defrost_rate to be 0.2
	}
	while(kilograms =='\0'){ //wait until user presses a valid button
		kilograms = KeyPad_getKeyPressed();
	}
	// only read 1 character as the valid number of kilograms are from 1 till 9 , print Err if this character is incorrect
	if( kilograms >= '1' && kilograms <='9' )
	{
		//any integer between 1 and 9 is accepted
		LCD_vidSendCMD(CLR_CMD);
		LCD_vidSendChar(kilograms) ; //write the number of kilograms entered
		_delay_ms(2000); //2 seconds delay
		while(Oven_Ready() == 0) ; //must wait until door is closed and SW2 is pressed
		isCooking = 1;
		Turn_on_LEDs() ;
		LCD_vidSendCMD(CLR_CMD);
		workservo();
		LCD_vidCountDown(defrost_rate * (kilograms-'0'),0); //time to wait in seconds
	}
	else{ //invalid number of kilograms
		LCD_vidSendCMD(CLR_CMD);
		LCD_vidWriteString("Err", strlen("Err")  );
		_delay_ms(2000);
		kilograms = '\0';
		LCD_vidSendCMD(CLR_CMD);
		goto Repeat ;
	}
	Program_Finish() ; //finsihing  program for microwave
}

void Program_D() //for other kinds of food
{
	
	
	u8 numberOfMove=4;
	uint16_t  timer  ;
	LCD_vidSendCMD(CLR_CMD);
	LCD_vidWriteString("Cooking time?", strlen("Cooking time?") );
	LCD_vidSendCMD(CLR_CMD);
	do{
		LCD_vidSendCMD(CLR_CMD);
		LCD_vidWriteString("(1 till 30:00)",strlen("(1 till 30:00)"));
		LCD_shiftStr(numberOfMove,Shift_l);
		LCD_shiftStr(numberOfMove,Shift_R);
		timer = LCD_u16TakeInput() ; //user must enter a valid time (1 till 30:00)
	}while(timer == 0);
	if(getPinVal(sw1_2,3) == LOW)
	LCD_vidSendCMD(CLR_CMD); //switch 1 pressed to clear LCD
	while(Oven_Ready() == 0) ; //wait until door is closed and switch 2 is pressed then the LEDs are on and the countdown starts
	isCooking = 1 ;
	Turn_on_LEDs() ;
	workservo();
	LCD_vidCountDown(timer,1)  ; //time is entered in standard form
	Program_Finish() ; //finishing  program for microwave
}

void Program_Finish() //terminating program of the microwave. this is always executed after programs A or B or C or D
{
	uint8_t i;
	isCooking = 0;
	LCD_vidSendCMD(CLR_CMD); //clear the LCD
	stop_servo();
	LCD_vidWriteString("Done",4);
	Turn_off_LEDs(); //turn off the LEDs
	for(i = 0 ; i < 3 ; i++ )
	{
		Turn_on_LEDs(); //turning the LEDs on and off should make them blink
		tuneBuzzer(); //sound the buzzer and wait for 1 second between blinking periods
		Turn_off_LEDs();
		tuneBuzzer(); //sound the buzzer and wait for 1 second between blinking periods
	}
	LCD_vidSendCMD(CLR_CMD); //clear the LCD
}
uint8_t Oven_Ready() //to check if door is closed and SW2 is pressed(cooking conditions)
{
	//getPinVal(sw3_1, 2) &&
	return (/* getPinVal(GROUP_D, 2) &&*/!getPinVal(GROUP_D, 0) ) ; //external switch connected to port D pin 0 and SW2 (switch 3 being up and switch 2 being down)
}

void Turn_on_LEDs() //turn on the three LEDs
{
	uint8_t i;
	PORTC|=0x0E ;
	_delay_ms(1000);
}

void Turn_off_LEDs() //turn off the Three LEDs
{
	uint8_t i;
	for(i = 1 ; i<= 3 ; i++ )
	setPinVal(GROUP_C ,i , LOW) ;
}
void tuneBuzzer(void) //buzzer function explained in the header
{
	uint16_t i;
	for(i = 0; i < 500;i++){
		setPinVal(GROUP_C,0,1);
		_delay_ms(1);
		setPinVal(GROUP_C,0,0);
		_delay_ms(1);
	}
}
void SW3_Interrupt()
{
	Timer1_setOCR1x(0,CHANNEL_A);
	while(isCooking && ! getPinVal(PORTD , 2) ){
		_delay_ms(500);
		if (getPinVal(PORTD , 2)==1)
		{
			Timer1_setOCR1x(200,CHANNEL_A);
			break;
		}
		}   //if in cooking state and door is open
		Timer1_setOCR1x(200,CHANNEL_A);
	
}
void SW1_Interrupt()
{
	Timer1_setOCR1x(0,CHANNEL_A);
	
	while(1) //pause loop
	{
		
		Turn_off_LEDs();
		_delay_ms(700);
		if(getPinVal(GROUP_D,2) == LOW) //if SW1 is pressed again
		{
			Turn_on_LEDs();
			LCD_vidSendCMD(CLR_CMD);
			 
		}
		if(getPinVal(GROUP_D,0) == LOW && getPinVal(GROUP_D,3) == HIGH )
		{//if SW2 is pressed again resume cooking and door is closed
			Turn_on_LEDs();
			Turn_off_LEDs();
			Turn_on_LEDs();
			Timer1_setOCR1x(200,CHANNEL_A);
			break;
		}
	}
}


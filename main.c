/*
 * GccApplication2.c
 *
 * Created: 7/24/2023 11:25:55 PM
 * Author : Ahmed Abdelmotelb Ali Abdelmotelb mohamed zedan
 */ 

#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
	// init switch
	DDRD&=~(1<<3);//PD2
	PORTD|=(1<<3);//PD2
	//init pin
	DDRB|=0x01;//red pin as output 
	DDRB|=0x02;//green pin as output
	
	
    /* Replace with your application code */
    while (1) 
    {
		if(!(PIND&(1<<3)))	// IF 0 SWITCH PUSH 	
		{
			PORTB&=~0x01;//off red
			PORTB |=0x02;//on green
    }else{
		PORTB |=0x01;//turn red
		
		PORTB &=~0x02;//off green
	}
	_delay_ms(1000);
		}
	
}


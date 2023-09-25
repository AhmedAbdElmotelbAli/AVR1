#include "DIO.h"

void setPinDir(u8 group,u8 pin,u8 dir){
	switch(dir){
	case OUTPUT:
		switch(group){
		case GROUP_A:
			SET_BIT(DDRA,pin);
			break;
		case GROUP_B:
			SET_BIT(DDRB,pin);
			break;
		case GROUP_C:
			SET_BIT(DDRC,pin);
			break;
		case GROUP_D:
			SET_BIT(DDRD,pin);
			break;
		}
		break;
	case INPUT:
		switch(group){
		case GROUP_A:
			CLR_BIT(DDRA,pin);
			break;
		case GROUP_B:
			CLR_BIT(DDRB,pin);
			break;
		case GROUP_C:
			CLR_BIT(DDRC,pin);
			break;
		case GROUP_D:
			CLR_BIT(DDRD,pin);
			break;
		}
		break;
	}
}

void setPinVal(u8 group,u8 pin,u8 dir){
	switch(dir){
	case HIGH:
		switch(group){
		case GROUP_A:
			SET_BIT(PORTA,pin);
			break;
		case GROUP_B:
			SET_BIT(PORTB,pin);
			break;
		case GROUP_C:
			SET_BIT(PORTC,pin);
			break;
		case GROUP_D:
			SET_BIT(PORTD,pin);
			break;
		}
		break;
	case LOW:
		switch(group){
		case GROUP_A:
			CLR_BIT(PORTA,pin);
			break;
		case GROUP_B:
			CLR_BIT(PORTB,pin);
			break;
		case GROUP_C:
			CLR_BIT(PORTC,pin);
			break;
		case GROUP_D:
			CLR_BIT(PORTD,pin);
			break;
		}
		break;
	}
}

u8 getPinVal(u8 group,u8 pin){
	switch(group){
	case GROUP_A:
		return GET_BIT(PINA,pin);
	case GROUP_B:
		return GET_BIT(PINB,pin);
	case GROUP_C:
		return GET_BIT(PINC,pin);
	case GROUP_D:
		return GET_BIT(PIND,pin);
	}
}

void setGrpDir(u8 group,u8 val){
	switch (group)
	{
	case GROUP_A:
		/* code */
		DDRA=val;
		break;
	case GROUP_B:
		/* code */
		DDRB=val;
		break;
	case GROUP_C:
		/* code */
		DDRC=val;
		break;
	case GROUP_D:
		/* code */
		DDRD=val;
		break;


	default:
		break;
	}
}

void setGrpVal(u8 group,u8 val){
		switch (group)
	{
	case GROUP_A:
		/* code */
		PORTA=val;
		break;
	case GROUP_B:
		/* code */
		PORTB=val;
		break;
	case GROUP_C:
		/* code */
		PORTC=val;
		break;
	case GROUP_D:
		/* code */
		PORTD=val;
		break;


	default:
		break;
	}
}

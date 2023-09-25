/*
 * INT.c
 *
 *  Created on: Aug 16, 2023
 *      Author: Ahmed Abdelmotelb Ali
 */
#include "INT.h"

static volatile void (*ptrToINT0)(void) = ((void*)0);
static volatile void (*ptrToINT1)(void) = ((void*)0);



void INT_vENGlobINT(){
	SET_BIT(SREG,7);
}

void INT_vDisGlobINT(){
	CLR_BIT(SREG,7);
}




void INT_vInitINT0(){

	//SET INT0 PIN TO INPUT
	setPinDir(GROUP_D,2,INPUT);

	//ACtvate Pull UP
	setPinVal(GROUP_D,2,HIGH);


#if   INT0_TRIG_MODE == LOW_LEVEL

	//Set tiggering mode
	CLR_BIT(MCUCR,ISC00);
	CLR_BIT(MCUCR,ISC01);


#elif INT0_TRIG_MODE == IOC
	//Set tiggering mode
	SET_BIT(MCUCR,ISC00);
	CLR_BIT(MCUCR,ISC01);


#elif INT0_TRIG_MODE == FALL_EDGE
	//Set tiggering mode
	CLR_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC01);


#elif INT0_TRIG_MODE == RISS_EDGE
	//Set tiggering mode
	SET_BIT(MCUCR,ISC00);
	SET_BIT(MCUCR,ISC01);

#endif
	//PIE
	INT_vEN_INT0();

	//GIE
	INT_vENGlobINT();


}

void INT_vEN_INT0(){
	SET_BIT(GICR,INT0);
}

void INT_vDisINT0(){
	CLR_BIT(GICR,INT0);
}

void INT_vSetCallBackToINT0(void(*ptrToFunc)(void)){
	ptrToINT0=ptrToFunc;
}


/*
SAME AS ISR
/// FUNCTION TO HANDLE ISR FUNCTION
void __vector_1(void) __attribute__((signal,used));
void __vector_1(void)
{
	if(ptrToINT0!=((void*)0)){
		ptrToINT0();
	}
}
*/

ISR(INT0_vect)
{
	if(ptrToINT0!=((void*)0)){
		ptrToINT0();
	}
}




void INT_vInitINT1(){
	//SET INT0 PIN TO INPUT
	setPinDir(GROUP_D,3,INPUT);

	//ACtvate Pull UP
	setPinVal(GROUP_D,3,HIGH);


#if   INT1_TRIG_MODE == LOW_LEVEL

	//Set tiggering mode
	CLR_BIT(MCUCR,ISC10);
	CLR_BIT(MCUCR,ISC11);


#elif INT1_TRIG_MODE == IOC
	//Set tiggering mode
	SET_BIT(MCUCR,ISC10);
	CLR_BIT(MCUCR,ISC11);


#elif INT1_TRIG_MODE == FALL_EDGE
	//Set tiggering mode
	CLR_BIT(MCUCR,ISC10);
	SET_BIT(MCUCR,ISC11);


#elif INT1_TRIG_MODE == RISS_EDGE
	//Set tiggering mode
	SET_BIT(MCUCR,ISC10);
	SET_BIT(MCUCR,ISC11);

#endif
	//PIE
	INT_vEN_INT1();

	//GIE
	INT_vENGlobINT();

}

void INT_vEN_INT1(){
	SET_BIT(GICR,INT1);
}

void INT_vDisINT1(){
	CLR_BIT(GICR,INT1);
}


void INT_vSetCallBackToINT1(void(*ptrToFunc)(void)){
	ptrToINT1=ptrToFunc;
}

ISR(INT1_vect)
{
	if(ptrToINT1!=((void*)0)){
		ptrToINT1();
	}
}




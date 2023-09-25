/*
 * INT.h
 *
 *  Created on: Aug 16, 2023
 *      Author: fathi
 */

#ifndef MCAL_INT_INT_H_
#define MCAL_INT_INT_H_

#include <avr/interrupt.h>
#include "DIO.h"

#define LOW_LEVEL 0
#define IOC       1
#define FALL_EDGE 2
#define RISS_EDGE 3


#define INT0_TRIG_MODE FALL_EDGE

#define INT1_TRIG_MODE FALL_EDGE

//FOR ALL INTs
void INT_vENGlobINT();

void INT_vDisGlobINT();


//INT0

void INT_vInitINT0();

void INT_vEN_INT0();

void INT_vDisINT0();


void INT_vSetCallBackToINT0(void(*ptrToFunc)(void));



//INT1
void INT_vInitINT1();

void INT_vEN_INT1();

void INT_vDisINT1();


void INT_vSetCallBackToINT1(void(*ptrToFunc)(void));





#endif /* MCAL_INT_INT_H_ */

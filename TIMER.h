/*
 * TIMER.h
 *
 *  Created on: Aug 21, 2023
 *      Author: Ahmed Abdelmotelb Ali
 */
#ifndef MCAL_TIMERS_TIMER_H_
#define MCAL_TIMERS_TIMER_H_


#include <avr/io.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"



/************** TIMER0 MODES **************/

#define TIMER_OVF_MODE			0
#define TIMER_PHASE_PWM_MODE    1
#define TIMER_CTC_MODE 			2
#define TIMER_FAST_PWM_MODE     3
#define TIMER_FAST_PWM_ICR1_MODE  14



/************* TIMER OCx MODES**********/
#define TIMER_OCx_DIS   0x00
#define TIMER_OCx_TOG   0x10
#define TIMER_OCx_CLR   0x20
#define TIMER_OCx_SET   0x30

#define TIMER_OCx_PWM_NON_INV 0x20
#define TIMER_OCx_PWM_INV     0x30







/************** TIMER PRESCALER **************/
#define TIMER_STOP_TIMER           0
#define TIMER_PRESCALER_1          1
#define TIMER_PRESCALER_8          2
#define TIMER_PRESCALER_64         3
#define TIMER_PRESCALER_256        4
#define TIMER_PRESCALER_1024       5
#define TIMER_PRESCALER_T0         6
#define TIMER_PRESCALER_T1         7


/************ Timer 0 ***********/
void Timer0_vInit(u8 PreScaler,u8 MODE,u8 PreLoadVal,u8 OC0_MODE,u8 CMP_MatchVal);

void setTCNT0(u8 preload_value);

void clearTCNT0(void);

void setOCR0(u8 value);


void Timer0_vClosePIE(u8 MODE);

void Timer0_vOpenPIE(u8 MODE);


void Timer0_vDisT0();

void Timer0_OVF_setCallBack(void(*ptrToFunc)(void));

void Timer0_CTC_setCallBack(void(*ptrToFunc)(void));



/************ Timer 1 ***********/
#define CHANNEL_A 0
#define CHANNEL_B 1

#define TIMER_ICU_MODE 4


#define TIMER_OC1A_DIS   0x00
#define TIMER_OC1A_TOG   0x40
#define TIMER_OC1A_CLR   0x80
#define TIMER_OC1A_SET   0xC0
#define TIMER_OC1A_PWM_NON_INV 0x80
#define TIMER_OC1A_PWM_INV     0xC0

#define FALLING 0
#define RISSING 1



void Timer1_vInit(u8 PreScaler,u8 MODE,u16 PreLoadVal,u8 OC0_MODE,u8 CMP_MatchVal,u8 Ch);

void Timer1_setTCNT1(u16);
void Timer1_setOCR1x(u16,u8);

void Timer1_OpenPIE(u8 MODE, u8 Ch);
void Timer1_vSetEdge(u8);
void Timer1_ClosePIE(u8,u8);

void Timer1_OVF_setCallBack(void(*ptrToFunc)(void));

void Timer1_CMPA_setCallBack(void(*ptrToFunc)(void));

void Timer1_CMPB_setCallBack(void(*ptrToFunc)(void));

void Timer1_CAPT_setCallBack(void(*ptrToFunc)(void));

void Timer1_vSetICR1(u16 val);






#endif /* MCAL_TIMERS_TIMER_H_ */

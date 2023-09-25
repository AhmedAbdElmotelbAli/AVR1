#include"TIMER.h"

#include<avr/interrupt.h>

static volatile void(*ptrToT0_OVF)(void)=((void*)0);
static volatile void(*ptrToT0_CTC)(void)=((void*)0);



void Timer0_vInit(u8 PreScaler,u8 MODE,u8 PreLoadVal,u8 OC0_MODE,u8 CMP_MatchVal){
	/**
	 * 1st step : configure the mode
	 * 2nd step : configure FOC0
	 * 3rd step : configure OC0 Pin if CTC
	 * 4th step : Set PreLoad Val if needed
	 * 5th step : set OCR value if CTC
	 * 6th step : Enable INT
	 * 7th step : Enable GIE
	 * 8th step : Set prescaler
	 */

	switch(MODE){
	case TIMER_OVF_MODE:

		//Configure ovf mode
		CLR_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);

		//set preload
		setTCNT0(PreLoadVal);


		break;
	case TIMER_CTC_MODE:

		//Configure CTC mode
		CLR_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);

		//set FOC0
		SET_BIT(TCCR0,FOC0);

		//SET OC0 MODE
		TCCR0=(TCCR0&0xCF)|(OC0_MODE&0x30);

		//SET OCR0
		setOCR0(CMP_MatchVal);
		break;

	case TIMER_FAST_PWM_MODE :
		//Configure FAST PWM mode
		SET_BIT(TCCR0,WGM00);
		SET_BIT(TCCR0,WGM01);

		//CLR FOC0 IN PWM MODES
		CLR_BIT(TCCR0,FOC0);

		//SET OC0 MODE
		TCCR0=(TCCR0&0xCF)|(OC0_MODE&0x30);

		//SET DUTY VALUE
		setOCR0(CMP_MatchVal);

		break;
	case TIMER_PHASE_PWM_MODE:

		//Configure PHASE CORRECT mode
		SET_BIT(TCCR0,WGM00);
		CLR_BIT(TCCR0,WGM01);

		//CLR FOC0 IN PWM MODES
		CLR_BIT(TCCR0,FOC0);

		//SET OC0 MODE
		TCCR0=(TCCR0&0xCF)|(OC0_MODE&0x30);


		//SET DUTY VALUE
		setOCR0(CMP_MatchVal);


		break;

	}
	//EN PIE
	Timer0_vOpenPIE(MODE);

	//EN GIE
	SET_BIT(SREG,7);

	//Set PreScaler
	TCCR0=(TCCR0&0xF8)|(PreScaler&7);

}

void setTCNT0(u8 PreLoadVal){
	TCNT0=PreLoadVal;
}

void setOCR0(u8 value){
	OCR0=value;
}


void Timer0_vOpenPIE(u8 MODE){
	switch(MODE){
	case TIMER_OVF_MODE:
		SET_BIT(TIMSK,TOIE0);
		break;
	default :
		SET_BIT(TIMSK,OCIE0);
		break;
	}
}

void Timer0_vClosePIE(u8 MODE){
	switch(MODE){
	case TIMER_OVF_MODE:
		CLR_BIT(TIMSK,TOIE0);
		break;
	default :
		CLR_BIT(TIMSK,OCIE0);
		break;
	}
}

void clearTCNT0(void){
	TCNT0=0;
}

void Timer0_vDisT0(){
	TCCR0=0;
}



void Timer0_OVF_setCallBack(void(*ptrToFunc)(void)){
	ptrToT0_OVF=ptrToFunc;
}

void Timer0_CTC_setCallBack(void(*ptrToFunc)(void)){
	ptrToT0_CTC=ptrToFunc;
}


ISR(TIMER0_OVF_vect){

	if(ptrToT0_OVF)
		ptrToT0_OVF();
}

ISR(TIMER0_COMP_vect){

	if(ptrToT0_CTC)
		ptrToT0_CTC();
}

/**********************TIMER 1 ***************************/

static volatile void(*ptrToT1_OVF)(void)=((void*)0);
static volatile void(*ptrToT1_CAPT)(void)=((void*)0);
static volatile void(*ptrToT1_CMPA)(void)=((void*)0);
static volatile void(*ptrToT1_CMPB)(void)=((void*)0);

void Timer1_vInit(u8 PreScaler,u8 MODE,u16 PreLoadVal,u8 OC1_MODE,u8 CMP_MatchVal,u8 Ch){
	/**
	 * 1st step : configure the mode
	 * 2nd step : configure FOC0
	 * 3rd step : configure OC1 Pin if CTC
	 * 4th step : Set PreLoad Val if needed
	 * 5th step : set OCR value if CTC
	 * 6th step : Enable INT
	 * 7th step : Enable GIE
	 * 8th step : Set prescaler
	 */

	CLR_BIT(SREG,7);

	switch(MODE){
	case  TIMER_OVF_MODE:
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);

		Timer1_setTCNT1(PreLoadVal);
		break;
		////////////////////////////////////////////
		////////////////////////////////////////////

	case TIMER_CTC_MODE:

		//MODE 4
		CLR_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);

		switch(Ch){
		case CHANNEL_A:
			//FOCA
			SET_BIT(TCCR1A,FOC1A);

			//SET OC1A OPTIONS
			TCCR1A=(TCCR1A&0x3F)|(OC1_MODE&0xC0);

			break;
		case CHANNEL_B:
			//FOCA
			SET_BIT(TCCR1A,FOC1B);

			//SET OC1A OPTIONS
			TCCR1A=(TCCR1A&0xCF)|(OC1_MODE&0x30);
			break ;
		}
		Timer1_setOCR1x(CMP_MatchVal,Ch);
		break;

		////////////////////////////////////////////
		////////////////////////////////////////////

	case TIMER_FAST_PWM_MODE:

		//MODE 5 with TOP 0x00FF
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		switch(Ch){
		case CHANNEL_A:
			//FOCA
			CLR_BIT(TCCR1A,FOC1A);

			//SET OC1A OPTIONS
			TCCR1A=(TCCR1A&0x3F)|(OC1_MODE&0xC0);

			break;
		case CHANNEL_B:
			//FOCA
			CLR_BIT(TCCR1A,FOC1B);

			//SET OC1A OPTIONS
			TCCR1A=(TCCR1A&0xCF)|(OC1_MODE&0x30);
			break ;
		}
		Timer1_setOCR1x(CMP_MatchVal,Ch);
		break;
		////////////////////////////////////////////

		////////////////////////////////////////////
	case  TIMER_PHASE_PWM_MODE:

		//MODE 1 with TOP 0x00FF
		SET_BIT(TCCR1A,WGM10);
		CLR_BIT(TCCR1A,WGM11);
		CLR_BIT(TCCR1B,WGM12);
		CLR_BIT(TCCR1B,WGM13);
		switch(Ch){
		case CHANNEL_A:
			//FOCA
			CLR_BIT(TCCR1A,FOC1A);

			//SET OC1A OPTIONS
			TCCR1A=(TCCR1A&0x3F)|(OC1_MODE&0xC0);

			break;
		case CHANNEL_B:
			//FOCA
			CLR_BIT(TCCR1A,FOC1B);

			//SET OC1A OPTIONS
			TCCR1A=(TCCR1A&0xCF)|(OC1_MODE&0x30);
			break ;
		}
		Timer1_setOCR1x(CMP_MatchVal,Ch);
		break;
		/****************************************************/
		/***************************************************/
	case TIMER_FAST_PWM_ICR1_MODE:
		//MODE FAST PWM 14 with TOP ICR1
		CLR_BIT(TCCR1A,WGM10);
		SET_BIT(TCCR1A,WGM11);
		SET_BIT(TCCR1B,WGM12);
		SET_BIT(TCCR1B,WGM13);

		switch(Ch){
		case CHANNEL_A:
			//FOCA
			CLR_BIT(TCCR1A,FOC1A);

			//SET OC1A OPTIONS
			TCCR1A=(TCCR1A&0x3F)|(OC1_MODE&0xC0);

			break;
		case CHANNEL_B:
			//FOCA
			CLR_BIT(TCCR1A,FOC1B);

			//SET OC1A OPTIONS
			TCCR1A=(TCCR1A&0xCF)|(OC1_MODE&0x30);
			break;
		}
		Timer1_setOCR1x(CMP_MatchVal,Ch);
		break;
	}
	//PIE
	Timer1_OpenPIE(MODE,0);

	//GIE
	SET_BIT(SREG,7);


	//SET PRESCALER
	TCCR1B=(TCCR1B&0xF8)|(PreScaler&0x07);
}

void Timer1_vSetICR1(u16 val){
	ICR1=val;
}

void Timer1_setOCR1x(u16 val,u8 ch){
	switch(ch){
	case CHANNEL_A:
		OCR1A=val;
		break;
	case CHANNEL_B:
		OCR1B=val;
		break;
	}
}

void Timer1_setTCNT1(u16 val){
	TCNT1=val;
}



void Timer1_OpenPIE(u8 MODE, u8 Ch){
	switch(MODE){
	case TIMER_OVF_MODE :
		SET_BIT(TIMSK,TOIE1);
		break;
	case TIMER_ICU_MODE:
		SET_BIT(TIMSK,TICIE1);
		break;
	default :
		switch(Ch){
		case CHANNEL_A:
			SET_BIT(TIMSK,OCIE1A);
			break;
		case CHANNEL_B:
			SET_BIT(TIMSK,OCIE1B);
			break;
		}
	}
}

void Timer1_vSetEdge(u8 edge){
	switch(edge){
	case FALLING:
		CLR_BIT(TCCR1B,ICES1);
		break;
	case RISSING:
		SET_BIT(TCCR1B,ICES1);
	}
}


void Timer1_ClosePIE(u8 MODE,u8 Ch ){
	switch(MODE){
	case TIMER_OVF_MODE :
		CLR_BIT(TIMSK,TOIE1);
		break;
	case TIMER_ICU_MODE:
		CLR_BIT(TIMSK,TICIE1);
		break;
	default :
		switch(Ch){
		case CHANNEL_A:
			CLR_BIT(TIMSK,OCIE1A);
			break;
		case CHANNEL_B:
			CLR_BIT(TIMSK,OCIE1B);
			break;
		}
	}
}




void Timer1_OVF_setCallBack(void(*ptrToFunc)(void)){
	ptrToT1_OVF =ptrToFunc;
}

void Timer1_CAPT_setCallBack(void(*ptrToFunc)(void)){
	ptrToT1_CAPT = ptrToFunc;
}


void Timer1_CMPA_setCallBack(void(*ptrToFunc)(void)){
	ptrToT1_CMPA=ptrToFunc;
}
void Timer1_CMPB_setCallBack(void(*ptrToFunc)(void)){
	ptrToT1_CMPB=ptrToFunc;

}


ISR(TIMER1_OVF_vect){
	if(ptrToT1_OVF){
		ptrToT1_OVF();
	}
}


ISR(TIMER1_CAPT_vect){
	if(ptrToT1_CAPT){
		ptrToT1_CAPT();
	}
}

ISR(TIMER1_COMPA_vect){
	if(ptrToT1_CMPA){
		ptrToT1_CMPA();
	}
}

ISR(TIMER1_COMPB_vect){
	if(ptrToT1_CMPB){
		ptrToT1_CMPB();
	}
}




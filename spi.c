 /******************************************************************************
 *
 * Module: SPI
 * File Name: spi_edit.c
 * Description: Source file for the SPI AVR driver
 *
 *******************************************************************************/

#include "spi.h"
#include "avr/io.h"
#include "DIO.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/

void SPI_initMaster(SPI_Prescaler prescaler,u8 DoubleSpeed)
{
	/******** Configure SPI Master Pins *********
	 * SS(PB4)
	 * MOSI(PB5)
	 * MISO(PB6)
	 * SCK(PB7)
	 ********************************************/
		DDRB |= (1<<MOSI)|(1<<SCK)|(1<<SS);	// Make MOSI, SCK, SS as Output pin
		DDRB &= ~(1<<MISO);			// Make MISO pin as input pin
		SS_Disable;
	
		



    /************************** SPCR Description **************************
     * Disable SPI Interrupt
     * Enable SPI Driver
     * Transmit the MSB first
     * Enable Master
     * SCK is low when idle
     * Sample Data with the raising edge
     * Choose SPI clock = Fosc/4
     ***********************************************************************/
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<CPOL)|(1<<CPHA);	// Enable SPI in master mode with Fosc/4
    
   


     /******** Configure normal or double speed mode ********/
     if (DoubleSpeed == NormalSpeedmode)
     {
	     SPSR&=0b11111110;
	     
     }
     else if (DoubleSpeed == DoubleSpeedmode)
     {
	     SPSR|=0x01;
     }
     switch(prescaler)
     {
	     case prescaler_4:
	     SPCR&=0b11111100;
	     break;
	     case prescaler_16:
	     SPCR=(1<<0);
	     break;
	     case prescaler_64:
	     
	     SPCR=(1<<1);
	     break;
	     case prescaler_128:
	     SPCR=(1<<0)|(1<<1);
	     break;
     }



}

void SPI_initSlave(SPI_Prescaler prescaler,u8 DoubleSpeed)
{
	
	/******** Configure SPI Slave Pins *********
	 * SS(PB4)
	 * MOSI(PB5)
	 * MISO(PB6)
	 * SCK(PB7)
	 ********************************************/
     DDRB &= ~((1<<MOSI)|(1<<SCK)|(1<<SS));  // Make MOSI, SCK, SS as input pins
     DDRB |= (1<<MISO);			// Make MISO pin as output pin




	/************************** SPCR Description **************************
	 * Disable SPI Interrupt
	 * Enable SPI Driver
	 * Transmit the MSB first
	 * Disable Master
	 * SCK is low when idle
	 * Sample Data with the raising edge
	 * Choose SPI clock = Fosc/4
	 ***********************************************************************/
		SPCR = (1<<SPE)|(1<<CPOL)|(1<<CPHA);			//Enable SPI in slave mode

    /******** Configure normal or double speed mode ********/
    if (DoubleSpeed == NormalSpeedmode)
    {
	    SPSR&=0b11111110;
	    
    }
    else if (DoubleSpeed == DoubleSpeedmode)
    {
	    SPSR|=0x01;
    }
    switch(prescaler)
    {
	    case prescaler_4:
	    SPCR&=0b11111100;
	    break;
	    case prescaler_16:
	    SPCR=(1<<0);
	    break;
	    case prescaler_64:
	    
	    SPCR=(1<<1);
	    break;
	    case prescaler_128:
	    SPCR=(1<<0)|(1<<1);
	    break;
    }


}

u8 SPI_sendReceiveByte(u8 dataTran)
{
	
		SPDR=dataTran;//send Byte
		while((GET_BIT(SPSR,7))==0){}//check flag of tran
		//read Byte
		return SPDR;
}

void SPI_send(u8 data)
{
	SPDR = data;
	while(!GET_BIT(SPSR,SPIF));
}
void SPI_SlaveSend(u8 data)
{
	SPDR = data;
}

u8 SPI_receive(void)
{
	/* Wait for reception complete */
	while(GET_BIT(SPSR,7)==0);
	/* Return data register */
	return SPDR;
	
}

void SPI_sendString(const u8 *str)
{
		while(*str != '\0')
		{
			//send Byte by Byte
			SPI_send(*str);
			str++;
		}
	

}
void SPI_SlaveSendString(const u8 *str)
{
	while(*str != '\0')
	{
		//send Byte by Byte
		SPI_SlaveSend(*str);
		str++;
	}
	

}

void SPI_receiveString(u8 *str)
{
	int i=0;
	while(*str != '\0')
	{
		//send Byte by Byte
		str[i]=SPI_receive();
		i++;
	}
	str[i]="\0";

}

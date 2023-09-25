 /******************************************************************************
 *
 * Module: SPI
 * File Name: spi_edit.h
 * Description: Header file for the SPI AVR driver
 *
 *******************************************************************************/

#ifndef SPI_H_
#define SPI_H_

#include "std_types.h"
#include "BIT_MATH.h"

/*******************************************************************************
 *                                Definitions                                  *
 *******************************************************************************/
/*
 * Default SPI data value used in case we need to receive a byte from the other device,
 * without need to send a data to it
 */
#define DoubleSpeedmode 1
#define NormalSpeedmode 1
#define MOSI DDB5
#define MISO DDB6
#define SCK DDB7
#define SS DDB4
#define SS_Enable PORTB &= ~(1<<PORTB4)
#define SS_Disable PORTB |= (1<<PORTB4)
#define SPI_DEFAULT_DATA_VALUE 0xFF

//#define SPI_DOUBLE_SPEED_Mode

#ifdef SPI_DOUBLE_SPEED_Mode

typedef enum {
	prescaler_2 = 0, prescaler_8, prescaler_32, prescaler_64
}SPI_Prescaler;

#endif

#ifndef SPI_DOUBLE_SPEED_Mode

typedef enum {
	prescaler_4 = 0, prescaler_16, prescaler_64, prescaler_128
}SPI_Prescaler;

#endif

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

void SPI_initMaster(SPI_Prescaler prescaler,u8 DoubleSpeed);

void SPI_initSlave(SPI_Prescaler prescaler,u8 DoubleSpeed);

u8 SPI_sendReceiveByte(u8 dataTran);

void SPI_send(u8 data);

void SPI_SlaveSend(u8 data);

u8 SPI_receive(void);

void SPI_sendString(const u8 *str);

void SPI_SlaveSendString(const u8 *str);

void SPI_receiveString(u8 *str);

#endif

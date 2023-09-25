#ifndef DIO_H
#define DIO_H

#include <avr/io.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"


#define INPUT 0
#define OUTPUT 1

#define LOW 0
#define HIGH 1

#define GROUP_A 0
#define GROUP_B 1
#define GROUP_C 2
#define GROUP_D 3



void setPinDir(u8 group,u8 pin,u8 dir);

void setPinVal(u8 group,u8 pin,u8 val);

u8 getPinVal(u8 group,u8 pin);

void setGrpDir(u8 group,u8 val);

void setGrpVal(u8 group,u8 val);






#endif

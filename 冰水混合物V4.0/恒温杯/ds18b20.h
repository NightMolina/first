#ifndef _DS18B20_H__
#define _DS18B20_H__

#include <STC15.h>
#include <intrins.h>
#include "UART.h"
void ds18b20_write_byte(unsigned char dat);
unsigned char ds18b20_read_byte(void);
void ds18b20_convert(void);
float ds18b20_readtemp(void);
void Delay100ms();
#endif
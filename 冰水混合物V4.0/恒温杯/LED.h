#ifndef __LED_H_
#define __LED_H_

#include <STC15.h>

sbit Red 	= P0^2;
sbit Blue 	= P0^3;


void LED_Red(unsigned char p);
void LED_Blue(unsigned char p);


#endif
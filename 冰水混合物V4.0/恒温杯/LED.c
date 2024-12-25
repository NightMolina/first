#include "LED.h"

void LED_Init(void){
	P0M0 &= ~0x0e; P0M1 &= ~0x0e; 
}

void LED_Red(unsigned char p){
	if(p)
		Red = 0;
	else
		Red = 1;
}
void LED_Blue(unsigned char p){
	if(p)
		Blue = 0;
	else
		Blue = 1;
}



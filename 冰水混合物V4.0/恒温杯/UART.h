#ifndef _UART_H__
#define _UART_H__

#include <STC15.h>
#include <stdio.h>


void 					UartInit					(void);
void 					Send_Byte					(unsigned char s);
char 					putchar						(char c);
#endif
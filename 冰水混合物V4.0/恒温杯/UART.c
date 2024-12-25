#include "UART.h"

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器时钟1T模式
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD &= 0x0F;		//设置定时器模式
	TL1 = 0xE0;			//设置定时初始值
	TH1 = 0xFE;			//设置定时初始值
	ET1 = 0;			//禁止定时器中断
	TR1 = 1;			//定时器1开始计时
	
}


void Serial_ser() interrupt 4
{
	if(TI){
		TI = 0 ;
	}
	if(RI){
		RI = 0;
	}
}
void Send_Byte(unsigned char s)
{
	SBUF = s;
	while(!TI);
	TI=0;
}


char putchar(char c)
{
 	 Send_Byte(c);
 	return c;
}
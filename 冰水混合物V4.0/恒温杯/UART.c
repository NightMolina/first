#include "UART.h"

void UartInit(void)		//9600bps@11.0592MHz
{
	SCON = 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��ʱ��1Tģʽ
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD &= 0x0F;		//���ö�ʱ��ģʽ
	TL1 = 0xE0;			//���ö�ʱ��ʼֵ
	TH1 = 0xFE;			//���ö�ʱ��ʼֵ
	ET1 = 0;			//��ֹ��ʱ���ж�
	TR1 = 1;			//��ʱ��1��ʼ��ʱ
	
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
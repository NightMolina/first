#include "Delay.h"

// ����ʱ��Ϊ11.0592MHz
#define FOSC 11059200L
#define T1MS (65536-FOSC/12/1000) // 1ms��ʱ��ֵ


void Delay_ms(unsigned int ms){
	
	while(ms--)
	{
		TMOD &= 0xF0;		
		TMOD |= 0x01;		//��ʱ��0,����ģʽ1
		TH0 = 0xFC;			//����ֵ
		TL0 = 0x66;			//��ʱ1ms
		TF0 = 0;			//��������־
		TR0 = 1;			//������ʱ��0
		EA=0;				//���ж�(ʹ�ò�ѯ��ʽ)
		ET0=0;				//��T0�ж�
		while(TF0 == 0);	//����ȴ�
		TR0 = 0;			//��ͣ��ʱ��
	}


}

void Delay_us(unsigned char us){
	while (us--){
	_nop_();_nop_();_nop_();		
	}

}
void Delayms(unsigned int nms){		//@11.0592MHz

	unsigned char data i, j;
	while(nms--){
	i = 11;
	j = 190;
	do
	{
		while (--j);
	} while (--i);
	}
}

#include "Delay.h"

// 设置时钟为11.0592MHz
#define FOSC 11059200L
#define T1MS (65536-FOSC/12/1000) // 1ms定时初值


void Delay_ms(unsigned int ms){
	
	while(ms--)
	{
		TMOD &= 0xF0;		
		TMOD |= 0x01;		//定时器0,工作模式1
		TH0 = 0xFC;			//至初值
		TL0 = 0x66;			//定时1ms
		TF0 = 0;			//清除溢出标志
		TR0 = 1;			//开启定时器0
		EA=0;				//关中断(使用查询方式)
		ET0=0;				//关T0中断
		while(TF0 == 0);	//溢出等待
		TR0 = 0;			//暂停定时器
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

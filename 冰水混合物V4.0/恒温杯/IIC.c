#include "iic.h"
 
 
//总线引脚定义
sbit SDA = P0^1;  /* 数据线 */
sbit SCL = P0^0;  /* 时钟线 */
//延迟函数
void IIC_Delay(unsigned char i)//延时一段时间
{
  while(i--)
	{
		_nop_();
		_nop_();
	}		
}
//开始信号
void IIC_Start(void)
{
    SDA = 1;
    SCL = 1;//当SCL为高电平的时候，SDA线上由高到低的跳变被定义为起始条件
    IIC_Delay(5);
    SDA = 0;
    IIC_Delay(5);
    SCL = 0;	
}
 
//停止信号
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;//SCL为高电平的时候，SDA线上由低到高的跳变被定义为停止条件；
    IIC_Delay(5);
    SDA = 1;
    IIC_Delay(5);
}
 
//等待应答信号（作用很大）
bit IIC_WaitAck(void)
{
    bit ackbit;
	
    SCL  = 1;
    IIC_Delay(5);
    ackbit = SDA;
    SCL = 0;
    IIC_Delay(5);
    return ackbit;
}
 
//通过I2C总线发送数据
void IIC_SendByte(unsigned char byt)
{
    unsigned char i;
 
    for(i=0; i<8; i++)
    {
        SCL  = 0;
        IIC_Delay(5);
        if(byt & 0x80) SDA  = 1;
        else SDA  = 0;
        IIC_Delay(5);
        SCL = 1;
        byt <<= 1;
        IIC_Delay(5);
    }
    SCL  = 0;  
}
 
//从I2C总线上接收数据
unsigned char IIC_RecByte(void)
{
	unsigned char i, da;
	for(i=0; i<8; i++)
	{   
		SCL = 1;
		IIC_Delay(5);
		da <<= 1;
		if(SDA) da |= 1;
		SCL = 0;
		IIC_Delay(5);
	}
	return da;    
}
#include "iic.h"
 
 
//�������Ŷ���
sbit SDA = P0^1;  /* ������ */
sbit SCL = P0^0;  /* ʱ���� */
//�ӳٺ���
void IIC_Delay(unsigned char i)//��ʱһ��ʱ��
{
  while(i--)
	{
		_nop_();
		_nop_();
	}		
}
//��ʼ�ź�
void IIC_Start(void)
{
    SDA = 1;
    SCL = 1;//��SCLΪ�ߵ�ƽ��ʱ��SDA�����ɸߵ��͵����䱻����Ϊ��ʼ����
    IIC_Delay(5);
    SDA = 0;
    IIC_Delay(5);
    SCL = 0;	
}
 
//ֹͣ�ź�
void IIC_Stop(void)
{
    SDA = 0;
    SCL = 1;//SCLΪ�ߵ�ƽ��ʱ��SDA�����ɵ͵��ߵ����䱻����Ϊֹͣ������
    IIC_Delay(5);
    SDA = 1;
    IIC_Delay(5);
}
 
//�ȴ�Ӧ���źţ����úܴ�
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
 
//ͨ��I2C���߷�������
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
 
//��I2C�����Ͻ�������
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
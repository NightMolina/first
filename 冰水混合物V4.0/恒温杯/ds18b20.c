#include "ds18b20.h"

sbit DS18B20_PIN = P1^0;


void Delay500us()		//@11.0592MHz
{
	unsigned char data i, j;

	_nop_();
	_nop_();
	i = 6;
	j = 93;
	do
	{
		while (--j);
	} while (--i);
}

void Delay80us()		//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	_nop_();
	i = 218;
	while (--i);
}

void Delay10us()		//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 25;
	while (--i);
}
void Delay50us()		//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	_nop_();
	_nop_();
	i = 135;
	while (--i);
}
void Delay5us()		//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 11;
	while (--i);
}
void Delay100ms()		//@11.0592MHz
{
	unsigned char data i, j, k;

	_nop_();
	_nop_();
	i = 5;
	j = 52;
	k = 195;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}


unsigned char ds18b20_reset() {
	
	unsigned char presence;
	DS18B20_PIN = 1;
	DS18B20_PIN = 0;
	Delay500us();
	DS18B20_PIN = 1;
	Delay80us();
	presence = DS18B20_PIN;
	Delay500us();
    return presence;
}

void ds18b20_write_bit(unsigned char dat) {
    DS18B20_PIN = 0;
	Delay10us();
	DS18B20_PIN = dat ;
	Delay50us();
	DS18B20_PIN = 1;
	
}

unsigned char ds18b20_read_bit(void) {
    unsigned char dat;
	DS18B20_PIN = 0;
	Delay5us();
	DS18B20_PIN = 1;
	Delay5us();
	dat = DS18B20_PIN;
	Delay50us();
    return dat;
}
void ds18b20_write_byte(unsigned char dat){
	unsigned char i;
	for(i = 0; i<8;i++){
		ds18b20_write_bit(dat&(0x01<<i));
	}
}
unsigned char ds18b20_read_byte(void){
	unsigned char i,byte=0x00;
	for(i=0;i<8;i++){
		if(ds18b20_read_bit()) 
			byte |=(0x01<<i);
	}
	return byte;
}
void ds18b20_convert(void){
	ds18b20_reset();
	ds18b20_write_byte(0xCC);
	ds18b20_write_byte(0x44);	
}

float ds18b20_readtemp(void){
	unsigned char tlsb,tmsb;
	int temp;
	float tt;
	ds18b20_reset();
	ds18b20_write_byte(0xCC);
	ds18b20_write_byte(0xBE);	
	
	tlsb = ds18b20_read_byte();
	tmsb = ds18b20_read_byte();
	
	temp = (tmsb<<8)|tlsb;

	tt = (int)((temp / 16.0) * 10 + 0.5) / 10.0;
	
	return tt;	
}

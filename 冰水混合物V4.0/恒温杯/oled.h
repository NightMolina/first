#ifndef _oled_H__
#define _oled_H__
 
 
#include <STC15.h>
#include "iic.h"
#include "oled_fong.h"
#include <math.h>
 
 
void OLED_Init(void);
void Xianshi_Tupian(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[]);
void Xianshi_24X24(unsigned char x, y,unsigned char ch[]);
void Xianshi_16X16(unsigned char x, y,unsigned char ch[]);
 void Xianshi_32X32(unsigned char x, y);
void Xianshi_6X8(unsigned char x, y,unsigned char ch[]);
void Xianshi_8X16(unsigned char x, y,unsigned char ch[]);
void OLED_Clear(void);
void DS18B20_ShowTemp(unsigned char x, y,float f_temp);


#endif
#include "oled.h"

void delay(unsigned int z)
{
	unsigned int i,j;
	for(i=z;i>0;i--)
	for(j=114;j>0;j--);
}
 
/* 发送指令函数 */
void write_cmd(cmd)
{
	IIC_Start();
	IIC_SendByte(0x78);
	IIC_WaitAck();
	IIC_SendByte(0x00);
	IIC_WaitAck();
	IIC_SendByte(cmd);
	IIC_WaitAck();
	IIC_Stop();
}
/* 发送数据函数 */
void write_dat(dat)
{
	IIC_Start();
	IIC_SendByte(0x78);
	IIC_WaitAck();
	IIC_SendByte(0x40);
	IIC_WaitAck();
	IIC_SendByte(dat);
	IIC_WaitAck();
	IIC_Stop();
}
 
//坐标设置
void Set_add(unsigned char x, unsigned char y) //x表示列（0~127），y表示页（0~7）
{ 	
	write_cmd(0xb0+y);                        //设置页地址（0~7）
	write_cmd(((x&0xf0)>>4)|0x10);             //设置显示位置—列高地址
	write_cmd((x&0x0f));                        //设置显示位置—列低地址
}   
 
/*********************OLED初始化************************************/
void OLED_Init(void)
{
	delay(500);//初始化之前的延时很重要！
	write_cmd(0xae);//--turn off oled panel
	write_cmd(0x00);//---set low column address
	write_cmd(0x10);//---set high column address
	write_cmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	write_cmd(0x81);//--set contrast control register
	write_cmd(0xcf); // Set SEG Output Current Brightness
	write_cmd(0xa1);//--Set SEG/Column Mapping     0xa0左右反置 0xa1正常
	write_cmd(0xc8);//Set COM/Row Scan Direction   0xc0上下反置 0xc8正常
	write_cmd(0xa6);//--set normal display
	write_cmd(0xa8);//--set multiplex ratio(1 to 64)
	write_cmd(0x3f);//--1/64 duty
	write_cmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	write_cmd(0x00);//-not offset
	write_cmd(0xd5);//--set display clock divide ratio/oscillator frequency
	write_cmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	write_cmd(0xd9);//--set pre-charge period
	write_cmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	write_cmd(0xda);//--set com pins hardware configuration
	write_cmd(0x12);
	write_cmd(0xdb);//--set vcomh
	write_cmd(0x40);//Set VCOM Deselect Level
	write_cmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	write_cmd(0x02);//
	write_cmd(0x8d);//--set Charge Pump enable/disable
	write_cmd(0x14);//--set(0x10) disable
	write_cmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	write_cmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	write_cmd(0xaf);//--turn on oled panel
	write_cmd(0x00); //初始清屏
	Set_add(0,0);
} 
 
 
//清屏函数,清完屏,整个屏幕是黑色的!和没点亮一样!!!
//先选中页，初始位置，然后128列全部清零
void OLED_Clear(void)  
{  
	unsigned int i,n;		    
	for(i=0;i<8;i++)  
	{  
		write_cmd (0xb0+i); //选中页地址（0~7）
		write_cmd (0x00);   //选中显示位置—列低地址
		write_cmd (0x10);   //选中显示位置—列高地址   
		for(n=0;n<128;n++)  //选中所有像素点
		    write_dat(0);   //关闭像素点
	} //更新显示
}

 
//图片显示函数，显示BMP图片128×64起始点坐标
 
/*  x0、x1:显示数据的列位置；
      x0：数据的初始位置          刚开始在哪一列打印出来
			x1：数据的最后的位置        在哪一列打印结束
		y0、y1：显示的页位置
		  y0：数据的初始页位置（行）；刚开始在哪一行打印出来
			y1:数据的最后的位置（行）   在哪一行打印结束
 
		BMP[]:需要打印的数据
*/
void Xianshi_Tupian(unsigned char x0, unsigned char y0,unsigned char x1, unsigned char y1,unsigned char BMP[])
{ 	
 unsigned int j=0;
 unsigned char x,y;
  
  if(y1%8==0) 
		y=y1/8;      
  else 
		y=y1/8+1;
	for(y=y0;y<y1;y++)
	{
			Set_add(x0,y);
			for(x=x0;x<x1;x++)
			{      
					write_dat(BMP[j++]);	    	
			}
	}
}
 
//打印T=
 void Xianshi_32X32(unsigned char x, y)
{
	unsigned char c=0,i=0,j=0;
	while (j<2)
	{
		if(x>120){x=0;y+=4;}		
		for(c=0;c<8;c++){		
		Set_add(x,y+c);     //一共两页，第一页
		for(i=0;i<16;i++)
		write_dat(F32X32[j][i+c*16]);
		}		
		x+=16;
		j++;
	}
}

 void Xianshi_16X16(unsigned char x, y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y+=4;}
		
		Set_add(x,y);     //一共两页，第一页
		for(i=0;i<8;i++)
		write_dat(F16X16[c][i]);
		 
		Set_add(x,y+1);   //一共两页，第二页
		for(i=0;i<8;i++)     
		write_dat(F16X16[c][i+8]);
		
		x+=8;
		j++;
	}
}
 void Xianshi_24X24(unsigned char x, y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y+=4;}
		
		Set_add(x,y);     //一共两页，第一页
		for(i=0;i<12;i++)
		write_dat(F24X24[c][i]);
		 
		Set_add(x,y+1);   //一共两页，第二页
		for(i=0;i<12;i++)     
		write_dat(F24X24[c][i+12]);
		
		Set_add(x,y+2);   //一共两页，第二页
		for(i=0;i<12;i++)     
		write_dat(F24X24[c][i+24]);		
		
		x+=12;
		j++;
	}
}
/* 6X8显示 */
//可以自己找出来数据对应的数组
/***************功能描述：显示6*8一组标准ASCII字符串	显示的坐标（x,y），y为页范围0～7****************/
void Xianshi_6X8(unsigned char x, y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>126){x=0;y++;}
		
		Set_add(x,y);
		for(i=0;i<6;i++)
		write_dat(F6x8[c][i]);
		x+=6;
		j++;
	}
}
 
/* 8X16显示 */
//可以自己找出来数据对应的数组
/*******************功能描述：显示8*16一组标准ASCII字符串	 显示的坐标（x,y），y为页范围0～7****************/
//ch[]:想要输入的数据，会自动在F8X16[]中寻找出来并发送给OLED
void Xianshi_8X16(unsigned char x, y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		
		Set_add(x,y);     //一共两页，第一页
		for(i=0;i<8;i++)
		write_dat(F8X16[c*16+i]);
		 
		Set_add(x,y+1);   //一共两页，第二页
		for(i=0;i<8;i++)     
		write_dat(F8X16[c*16+i+8]);
		
		x+=8;
		j++;
	}
}

void DS18B20_ShowTemp(unsigned char x, y,float f_temp){
	int d_temp;	
	unsigned char a[4],i,j=0,c;
	if(f_temp<0)  //打印负号 -
	{
		for(c=0;c<8;c++){		
			Set_add(x,y+c);     //一共两页，第一页
			for(i=0;i<16;i++)
				write_dat(F32X32[2][i+c*16]);
		}
	}
	else //清楚 - 号
	{
		for(c=0;c<8;c++){		
			Set_add(x,y+c);     //一共两页，第一页
			for(i=0;i<16;i++)
				write_dat(F32X32[18][i+c*16]);
		}
	}
	x+=16;
	
	d_temp = (int)(fabs(f_temp) * 10); //四舍五入，取一位小数
//	d_temp = 236;
	a[0] =(d_temp / 100) + 5;		//打印温度十位
	a[1] =(d_temp / 10 % 10) + 5;	//打印温度个位
	a[2] = 4;						//打印小数点 '.'
	a[3] =(d_temp % 10) + 5;		//打印温度十分位

	if(a[0]==5)
	{
		for(c=0;c<8;c++){		
			Set_add(x,y+c);     //一共两页，第一页
			for(i=0;i<16;i++)
				write_dat(~(F32X32[a[18]][i+c*16]));
		}
		x+=16;
		j++;
	}
	while (j<4)
	{
		
		if(x>120){x=0;y++;}

		for(c=0;c<8;c++){		
			Set_add(x,y+c);     //一共两页，第一页
			for(i=0;i<16;i++)
				write_dat(F32X32[a[j]][i+c*16]);
		}
		
		x+=16;
		j++;
	}
	for(c=0;c<8;c++){		
			Set_add(x,y+c);     //一共两页，第一页
			for(i=0;i<16;i++)
				write_dat(F32X32[17][i+c*16]);
		}	
	x+=16;	
	for(c=0;c<8;c++){		
			Set_add(x,y+c);     //一共两页，第一页
			for(i=0;i<16;i++)
				write_dat(F32X32[16][i+c*16]);
		}
}









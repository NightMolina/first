#include "oled.h"

void delay(unsigned int z)
{
	unsigned int i,j;
	for(i=z;i>0;i--)
	for(j=114;j>0;j--);
}
 
/* ����ָ��� */
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
/* �������ݺ��� */
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
 
//��������
void Set_add(unsigned char x, unsigned char y) //x��ʾ�У�0~127����y��ʾҳ��0~7��
{ 	
	write_cmd(0xb0+y);                        //����ҳ��ַ��0~7��
	write_cmd(((x&0xf0)>>4)|0x10);             //������ʾλ�á��иߵ�ַ
	write_cmd((x&0x0f));                        //������ʾλ�á��е͵�ַ
}   
 
/*********************OLED��ʼ��************************************/
void OLED_Init(void)
{
	delay(500);//��ʼ��֮ǰ����ʱ����Ҫ��
	write_cmd(0xae);//--turn off oled panel
	write_cmd(0x00);//---set low column address
	write_cmd(0x10);//---set high column address
	write_cmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	write_cmd(0x81);//--set contrast control register
	write_cmd(0xcf); // Set SEG Output Current Brightness
	write_cmd(0xa1);//--Set SEG/Column Mapping     0xa0���ҷ��� 0xa1����
	write_cmd(0xc8);//Set COM/Row Scan Direction   0xc0���·��� 0xc8����
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
	write_cmd(0x00); //��ʼ����
	Set_add(0,0);
} 
 
 
//��������,������,������Ļ�Ǻ�ɫ��!��û����һ��!!!
//��ѡ��ҳ����ʼλ�ã�Ȼ��128��ȫ������
void OLED_Clear(void)  
{  
	unsigned int i,n;		    
	for(i=0;i<8;i++)  
	{  
		write_cmd (0xb0+i); //ѡ��ҳ��ַ��0~7��
		write_cmd (0x00);   //ѡ����ʾλ�á��е͵�ַ
		write_cmd (0x10);   //ѡ����ʾλ�á��иߵ�ַ   
		for(n=0;n<128;n++)  //ѡ���������ص�
		    write_dat(0);   //�ر����ص�
	} //������ʾ
}

 
//ͼƬ��ʾ��������ʾBMPͼƬ128��64��ʼ������
 
/*  x0��x1:��ʾ���ݵ���λ�ã�
      x0�����ݵĳ�ʼλ��          �տ�ʼ����һ�д�ӡ����
			x1�����ݵ�����λ��        ����һ�д�ӡ����
		y0��y1����ʾ��ҳλ��
		  y0�����ݵĳ�ʼҳλ�ã��У����տ�ʼ����һ�д�ӡ����
			y1:���ݵ�����λ�ã��У�   ����һ�д�ӡ����
 
		BMP[]:��Ҫ��ӡ������
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
 
//��ӡT=
 void Xianshi_32X32(unsigned char x, y)
{
	unsigned char c=0,i=0,j=0;
	while (j<2)
	{
		if(x>120){x=0;y+=4;}		
		for(c=0;c<8;c++){		
		Set_add(x,y+c);     //һ����ҳ����һҳ
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
		
		Set_add(x,y);     //һ����ҳ����һҳ
		for(i=0;i<8;i++)
		write_dat(F16X16[c][i]);
		 
		Set_add(x,y+1);   //һ����ҳ���ڶ�ҳ
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
		
		Set_add(x,y);     //һ����ҳ����һҳ
		for(i=0;i<12;i++)
		write_dat(F24X24[c][i]);
		 
		Set_add(x,y+1);   //һ����ҳ���ڶ�ҳ
		for(i=0;i<12;i++)     
		write_dat(F24X24[c][i+12]);
		
		Set_add(x,y+2);   //һ����ҳ���ڶ�ҳ
		for(i=0;i<12;i++)     
		write_dat(F24X24[c][i+24]);		
		
		x+=12;
		j++;
	}
}
/* 6X8��ʾ */
//�����Լ��ҳ������ݶ�Ӧ������
/***************������������ʾ6*8һ���׼ASCII�ַ���	��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
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
 
/* 8X16��ʾ */
//�����Լ��ҳ������ݶ�Ӧ������
/*******************������������ʾ8*16һ���׼ASCII�ַ���	 ��ʾ�����꣨x,y����yΪҳ��Χ0��7****************/
//ch[]:��Ҫ��������ݣ����Զ���F8X16[]��Ѱ�ҳ��������͸�OLED
void Xianshi_8X16(unsigned char x, y,unsigned char ch[])
{
	unsigned char c=0,i=0,j=0;
	while (ch[j]!='\0')
	{
		c =ch[j]-32;
		if(x>120){x=0;y++;}
		
		Set_add(x,y);     //һ����ҳ����һҳ
		for(i=0;i<8;i++)
		write_dat(F8X16[c*16+i]);
		 
		Set_add(x,y+1);   //һ����ҳ���ڶ�ҳ
		for(i=0;i<8;i++)     
		write_dat(F8X16[c*16+i+8]);
		
		x+=8;
		j++;
	}
}

void DS18B20_ShowTemp(unsigned char x, y,float f_temp){
	int d_temp;	
	unsigned char a[4],i,j=0,c;
	if(f_temp<0)  //��ӡ���� -
	{
		for(c=0;c<8;c++){		
			Set_add(x,y+c);     //һ����ҳ����һҳ
			for(i=0;i<16;i++)
				write_dat(F32X32[2][i+c*16]);
		}
	}
	else //��� - ��
	{
		for(c=0;c<8;c++){		
			Set_add(x,y+c);     //һ����ҳ����һҳ
			for(i=0;i<16;i++)
				write_dat(F32X32[18][i+c*16]);
		}
	}
	x+=16;
	
	d_temp = (int)(fabs(f_temp) * 10); //�������룬ȡһλС��
//	d_temp = 236;
	a[0] =(d_temp / 100) + 5;		//��ӡ�¶�ʮλ
	a[1] =(d_temp / 10 % 10) + 5;	//��ӡ�¶ȸ�λ
	a[2] = 4;						//��ӡС���� '.'
	a[3] =(d_temp % 10) + 5;		//��ӡ�¶�ʮ��λ

	if(a[0]==5)
	{
		for(c=0;c<8;c++){		
			Set_add(x,y+c);     //һ����ҳ����һҳ
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
			Set_add(x,y+c);     //һ����ҳ����һҳ
			for(i=0;i<16;i++)
				write_dat(F32X32[a[j]][i+c*16]);
		}
		
		x+=16;
		j++;
	}
	for(c=0;c<8;c++){		
			Set_add(x,y+c);     //һ����ҳ����һҳ
			for(i=0;i<16;i++)
				write_dat(F32X32[17][i+c*16]);
		}	
	x+=16;	
	for(c=0;c<8;c++){		
			Set_add(x,y+c);     //һ����ҳ����һҳ
			for(i=0;i<16;i++)
				write_dat(F32X32[16][i+c*16]);
		}
}









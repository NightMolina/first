#include "pid.h"

#define T_MAX 500L
#define T_MIN -500L

float stdTemp = 0.0;
float temp;
float Kp = 2000, Ki = 20, Kd = 100;      // 120 18 100
static float Delta;
static long tPWM = 70L;
//Ŀǰ�ȶ�nPWMΪ47


void PWM_PID(void){
	static float nDelta,LDelta;
	long P,D;

	Delta = temp-stdTemp;
	LED();
	if(Delta>0.5){ //�²����0.5�����ٽ���
		nPWM = 90L;
	}
	else if(Delta < -0.5)//�¶ȵ���-1.0����������
	{
		nPWM = 30L;
	}
	
	else
	{
		if(Delta > 0){
			P = (long)(Delta * Kp);
			nDelta +=Delta * Ki;
			if(nDelta > T_MAX) nDelta = T_MAX;
			if(nDelta < T_MIN) nDelta = T_MIN;
			D = (long)((Delta - LDelta)*Kd);
			LDelta = Delta;
			nPWM = tPWM + P/100L + (long)(fabs(nDelta)/100) + D/100L;	
		}
		else
		{
			P = (long)(fabs(Delta) * Kp);
			nDelta +=Delta * Ki;
			if(nDelta > T_MAX) nDelta = T_MAX;
			if(nDelta < T_MIN) nDelta = T_MIN;
			D = (long)(fabs(Delta - LDelta)*Kd);
			LDelta = Delta;
			nPWM = tPWM - P/100L - (long)(fabs(nDelta)/100) - D/100L;
		}
	}
	if((nDelta == T_MAX||nDelta==T_MIN)&&(fabs(Delta)<0.4)) {
		nDelta = 0;
		tPWM = nPWM; 
	}
}
void LED(void){
	static int n;
	if(fabs(Delta)<0.3)
		n++;
	else
		n = 0;
	if(fabs(Delta)<0.3&&n>10)
	{
		LED_Red(1);
		LED_Blue(0);
		n = 100;
	}
	else
	{
		
		LED_Red(0);
		LED_Blue(1);	
	}

}

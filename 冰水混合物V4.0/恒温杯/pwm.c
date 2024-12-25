#include "pwm.h"
#include "intrins.h"

#define FOSC    11059200L

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define CCP_S0 0x10                 //P_SW1.4
#define CCP_S1 0x20                 //P_SW1.5
#define DUTY nPWM
//unsigned long nPWM;
unsigned long CYCLE = 22118;     //����PWM����(���ֵΪ32767)
//unsigned long DUTY = 20L;         //����ռ�ձ�

void PWM_Init(void)
{
    P3M0 = 0x00;
    P3M1 = 0x00;

    P_SW2 |= 0x80;                	//ʹ�ܷ���XSFR
    PWMCFG = 0x00;                  //����PWM�������ʼ��ƽΪ�͵�ƽ
    PWMCKS = 0x04;                  //ѡ��PWM��ʱ��ΪFosc/(0+1)
    PWMC = CYCLE;                   //����PWM����
    PWM2T1 = 0x0000;                //����PWM2��1�η�ת��PWM����
    PWM2T2 = CYCLE * DUTY / 100;    //����PWM2��2�η�ת��PWM����
                                    //ռ�ձ�Ϊ(PWM2T2-PWM2T1)/PWMC
    PWM2CR = 0x00;                  //ѡ��PWM2�����P3.7,��ʹ��PWM2�ж�
    PWMCR = 0x01;                   //ʹ��PWM�ź����
    PWMCR |= 0x80;                  //ʹ��PWMģ��
    P_SW2 &= ~0x80;
}


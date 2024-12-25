#include "pwm.h"
#include "intrins.h"

#define FOSC    11059200L

typedef unsigned char BYTE;
typedef unsigned int WORD;

#define CCP_S0 0x10                 //P_SW1.4
#define CCP_S1 0x20                 //P_SW1.5
#define DUTY nPWM
//unsigned long nPWM;
unsigned long CYCLE = 22118;     //定义PWM周期(最大值为32767)
//unsigned long DUTY = 20L;         //定义占空比

void PWM_Init(void)
{
    P3M0 = 0x00;
    P3M1 = 0x00;

    P_SW2 |= 0x80;                	//使能访问XSFR
    PWMCFG = 0x00;                  //配置PWM的输出初始电平为低电平
    PWMCKS = 0x04;                  //选择PWM的时钟为Fosc/(0+1)
    PWMC = CYCLE;                   //设置PWM周期
    PWM2T1 = 0x0000;                //设置PWM2第1次反转的PWM计数
    PWM2T2 = CYCLE * DUTY / 100;    //设置PWM2第2次反转的PWM计数
                                    //占空比为(PWM2T2-PWM2T1)/PWMC
    PWM2CR = 0x00;                  //选择PWM2输出到P3.7,不使能PWM2中断
    PWMCR = 0x01;                   //使能PWM信号输出
    PWMCR |= 0x80;                  //使能PWM模块
    P_SW2 &= ~0x80;
}


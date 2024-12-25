#include <STC15.h>
#include "ds18b20.h"
#include "UART.h"
#include "Delay.h"
#include "oled.h"
#include "PWM.h"
#include "pid.h"
#include "LED.h"
float oledt[4];
unsigned long nPWM;
extern float temp;

void main() {
	float T = 0.0;
	P0M0 = 0x00; P0M1 = 0x00; //GPIO初始化，设置为准双向口
	OLED_Init();
	OLED_Clear();	
//	Xianshi_32X32(0,0);
	PWM_Init();
	UartInit();
	printf("ds18b20 test\r\n");

	Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); 
	Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); 
	Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); 
	Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); Delay100ms(); 

    while (1) {
		
		PWM_Init();
		ds18b20_convert();
		Delay100ms(); 
        temp = ds18b20_readtemp();
		T = 0.0;
		if((temp>=0.1||temp<=-0.1)&&(fabs(T-temp)>0.1)) T = temp;
		
		DS18B20_ShowTemp(0,0,T);
		
		PWM_PID();
		
	printf("Temp = %.1f	", temp);
	printf("PWM = %ld\r\n",nPWM);

    }
}




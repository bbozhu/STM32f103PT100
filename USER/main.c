#include "max31865.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"


int main(void)
{	
	float temp1;
	float temp2;
	float temp3;
	u16 t;
	char CS_Selectted = 1;
	
	SystemInit();
	delay_init();
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	MAX31865_Init(CS_Selectted);
	MAX31865_Cfg(CS_Selectted);
	
	printf("MAX31865 test\r\n");
	while(1)
	{
		MAX31865_Init(1);
		MAX31865_Cfg(1);
		temp1=MAX31865_GetTemp(1);
		if((int)temp1 == 998){
				printf("temp1%d not connected!\r\n",1);
		}
		else {
				printf("temp1=%.3f\r\n",temp1);
		}		
		
		MAX31865_Init(2);
		MAX31865_Cfg(2);
		temp2=MAX31865_GetTemp(2);
		if((int)temp2 == 998){
				printf("temp2%d not connected!\r\n",2);
		}
		else {
				printf("temp2=%.3f\r\n",temp2);
		}				
		
		MAX31865_Init(3);
		MAX31865_Cfg(3);
		temp3 = MAX31865_GetTemp(3);
		if((int)temp3 == 998){
				printf("temp3%d not connected!\r\n",3);
		}
		else {
				printf("temp3=%.3f\r\n",temp3);
		}				
		
		delay_ms(1000);
	}

}




















































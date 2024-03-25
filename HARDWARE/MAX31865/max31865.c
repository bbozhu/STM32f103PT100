#include "max31865.h"
#include "math.h"
#include "usart.h"
#include "delay.h"
/* MAX31865 ��ʼ�� */
void MAX31865_Init(char CS_Selectted)
{
	GPIO_InitTypeDef GPIO_InitStructure ;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOA,ENABLE);

	switch (CS_Selectted)
	{
		case 1:
			GPIO_InitStructure.GPIO_Pin = MAX31865_CS1|MAX31865_SCLK|MAX31865_SDI;//���
			break;
		case 2:
			GPIO_InitStructure.GPIO_Pin = MAX31865_CS2|MAX31865_SCLK|MAX31865_SDI;//���
			break;
		case 3:
			GPIO_InitStructure.GPIO_Pin = MAX31865_CS3|MAX31865_SCLK|MAX31865_SDI;//���
			break;
		default:
			break;					 
			
	}
	
//	GPIO_InitStructure.GPIO_Pin = MAX31865_CS|MAX31865_SCLK|MAX31865_SDI;
	
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;//�������
	GPIO_Init(MAX31865_CONTROL_PORT,&GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = MAX31865_SDO|MAX31865_DRDY;//SDO���������DRDYת��״̬����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//��������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//50����
	GPIO_Init(MAX31865_CONTROL_PORT,&GPIO_InitStructure);
	
	switch (CS_Selectted)
	{
		case 1:
				MAX31865_CS1_CLR;
				MAX31865_CS2_SET;
				MAX31865_CS3_SET;
				break;
		case 2:
				MAX31865_CS1_SET;
				MAX31865_CS2_CLR;
				MAX31865_CS3_SET;
				break;
		case 3:
				MAX31865_CS1_SET;
				MAX31865_CS2_SET;
				MAX31865_CS3_CLR;		
				break;
		default:
				break;				
	}

	MAX31865_SCLK_SET;//ʱ����1
}


/* MAX31865 д�Ĵ��� 
addr:�Ĵ�����ַ
data:����
*/
void MAX31865_Write(unsigned char addr, unsigned char data, char CS_Selectted)
{
	unsigned char i;
	// MAX31865_CS_CLR;// Ƭѡ
	switch (CS_Selectted)
	{
		case 1:
				MAX31865_CS1_CLR;
				MAX31865_CS2_SET;
				MAX31865_CS3_SET;
				break;
		case 2:
				MAX31865_CS1_SET;
				MAX31865_CS2_CLR;
				MAX31865_CS3_SET;
				break;
		case 3:
				MAX31865_CS1_SET;
				MAX31865_CS2_SET;
				MAX31865_CS3_CLR;		
				break;
		default:
				break;				
	}
	
	for(i=0;i<8;i++)  //д��ַ
	{
		MAX31865_SCLK_CLR;//ʱ������
		if(addr&0x80) MAX31865_SDI_SET;
		else MAX31865_SDI_CLR;
		MAX31865_SCLK_SET;
		addr<<=1;
	}
	for(i=0;i<8;i++)  //д����
	{
		MAX31865_SCLK_CLR;
		if(data&0x80) MAX31865_SDI_SET;
		else MAX31865_SDI_CLR;
		MAX31865_SCLK_SET;
		data<<=1;
	}
	MAX31865_CS1_SET;
	MAX31865_CS2_SET;
	MAX31865_CS3_SET;
}

/* MAX31865 ���Ĵ��� 
addr:�Ĵ�����ַ
*/
unsigned char MAX31865_Read(unsigned char addr, char CS_Selectted)
{
	unsigned char i;
	unsigned char data=0;
	
	switch (CS_Selectted)
	{
		case 1:
				MAX31865_CS1_CLR;
				MAX31865_CS2_SET;
				MAX31865_CS3_SET;
				break;
		case 2:
				MAX31865_CS1_SET;
				MAX31865_CS2_CLR;
				MAX31865_CS3_SET;
				break;
		case 3:
				MAX31865_CS1_SET;
				MAX31865_CS2_SET;
				MAX31865_CS3_CLR;		
				break;
		default:
				break;				
	}
	
	for(i=0;i<8;i++)  //д��ַ
	{
		MAX31865_SCLK_CLR;
		if(addr&0x80) MAX31865_SDI_SET;
		else MAX31865_SDI_CLR;
		MAX31865_SCLK_SET;
		addr<<=1;
	}
	for(i=0;i<8;i++)  //������
	{
		MAX31865_SCLK_CLR;
		data<<=1;		
		MAX31865_SCLK_SET;		
		if(MAX31865_SDO_READ) data|=0x01;
		else data|=0x00;
	}
	MAX31865_CS1_SET;
	MAX31865_CS2_SET;
	MAX31865_CS3_SET;
	return data;
}

/* MAX31865 ����*/
void MAX31865_Cfg(char CS_Selectted)
{
	MAX31865_Write(0x80, 0xD3, CS_Selectted); //BIAS ON,�Զ���4�ߣ�50HZ  �����ļ��޸����߻�������
}

/* MAX31865 ��ȡ�¶� */
float MAX31865_GetTemp(char CS_Selectted)
{ 
	unsigned int data;
	float Rt;
	float Rt0 = 1000;  //PT100	
	float Z1,Z2,Z3,Z4,temp;
	float a = 3.9083e-3;
	float b = -5.775e-7;
	float rpoly;

//	MAX31865_Write(0x80, 0xD3);
	data=MAX31865_Read(0x01, CS_Selectted)<<8;
	data|=MAX31865_Read(0x02, CS_Selectted);
	data>>=1;  //ȥ��Faultλ
	printf("Read=0x%02X\r\n",data);
	Rt=(float)data/32768.0*RREF;
	
	printf("Rt=0x%.1f\r\n",Rt);
	
	Z1 = -a;
  Z2 = a*a-4*b;
  Z3 = 4*b/Rt0;
  Z4 = 2*b;

  temp = Z2+Z3*Rt;
  temp = (sqrt(temp)+Z1)/Z4;
  
  if(temp>=0) return temp;

  rpoly = Rt;
  temp = -242.02;
  temp += 2.2228 * rpoly;
  rpoly *= Rt;  // square
  temp += 2.5859e-3 * rpoly;
  rpoly *= Rt;  // ^3
  temp -= 4.8260e-6 * rpoly;
  rpoly *= Rt;  // ^4
  temp -= 2.8183e-8 * rpoly;
  rpoly *= Rt;  // ^5
  temp += 1.5243e-10 * rpoly;

  return temp;
}




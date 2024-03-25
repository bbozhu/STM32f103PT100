#include "ULN2003.h"
#include "delay.h"
 

void ULN2003_GPIO_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 GPIO_InitTypeDef  GPIO_InitStructurez;
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //ʹ��PA�˿�ʱ��
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��PB�˿�ʱ��

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3;				 // �˿�����
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);					 //�����趨������ʼ��GPIO
	
 GPIO_InitStructurez.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 // �˿�����
 GPIO_InitStructurez.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 GPIO_InitStructurez.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
 GPIO_Init(GPIOB, &GPIO_InitStructurez);					 //�����趨������ʼ��GPIO
 
 
}










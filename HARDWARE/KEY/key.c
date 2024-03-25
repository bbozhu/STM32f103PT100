#include "key.h"
#include "delay.h"

void KEY_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 GPIO_InitTypeDef  GPIO_InitStructureZZ;
	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_12|GPIO_Pin_15;				 //KEY 端口配置
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		                           //GPIO_Mode_IPU上拉       GPIO_Mode_IPD下拉
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
 GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //
 
	GPIO_InitStructureZZ.GPIO_Pin =GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStructureZZ.GPIO_Mode =GPIO_Mode_IPU;
	GPIO_InitStructureZZ.GPIO_Speed =GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructureZZ);	  				

}


//低电平触发按键
u8 KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1;  //支持连按		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==0||KEY4==0||KEY5==0||KEY6==0))
	{
		delay_ms(10);//去抖动 
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
		else if(KEY2==0)return 3;
		else if(KEY3==0)return 4;
		else if(KEY4==0)return 5;
		else if(KEY5==0)return 6;
		else if(KEY6==0)return 7;
	}
	else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1&&KEY4==1&&KEY5==1&&KEY6==1)key_up=1; 	    
 	return 0;// 无按键按下
}



//void KEY_Init(void)
//{
// 
// GPIO_InitTypeDef  GPIO_InitStructure;
// GPIO_InitTypeDef  GPIO_InitStructureZZ;
//	
// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	
// RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
//	
// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;				 //KEY 端口配置
// GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 		                           //GPIO_Mode_IPU上拉       GPIO_Mode_IPD下拉
// GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO口速度为50MHz
// GPIO_Init(GPIOA, &GPIO_InitStructure);	  				 //
// 
//	GPIO_InitStructureZZ.GPIO_Pin =GPIO_Pin_13|GPIO_Pin_14;
//	GPIO_InitStructureZZ.GPIO_Mode =GPIO_Mode_IPD;
//	GPIO_InitStructureZZ.GPIO_Speed =GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_InitStructureZZ);	  				

//}
//u8 KEY_Scan(u8 mode)
//{	 
//	static u8 key_up=1;//按键按松开标志
//	if(mode)key_up=1;  //支持连按		  
//	if(key_up&&(KEY0==1))//||KEY1==1||KEY2==1||KEY3==1||KEY4==1||KEY5==1
//	{
//		delay_ms(10);//去抖动 
//		key_up=0;
//		if(KEY0==1)return 1;
////		else if(KEY1==1)return 2;
////		else if(KEY2==1)return 3;
////		else if(KEY3==1)return 4;
////		else if(KEY4==1)return 5;
////		else if(KEY5==1)return 6;
//	}
//	else if(KEY0==0)//&&KEY1==0&&KEY2==0&&KEY3==0&&KEY4==0&&KEY5==0
//	key_up=1; 	    
// 	return 0;// 无按键按下
//}





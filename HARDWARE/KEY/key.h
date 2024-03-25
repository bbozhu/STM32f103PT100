#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"

#define KEY0 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_8)
#define KEY1 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_15)
#define KEY2 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_12)
#define KEY3 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13)
#define KEY4 GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_14)
#define KEY5 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15)
#define KEY6 GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)

void KEY_Init(void);
u8 KEY_Scan(u8 mode);
void EXTIZZ_Init(void);
#endif







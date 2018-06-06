#include <stm32f10x.h>
#include <stdlib.h>
#include <arm_math.h>
#include "Polar_IT.h"

//用户所有的共享变量在这里定义，并在相应这个C文件里实现，通用的数据开关在这里定义
#ifndef __INCLUDELIST_H__
#define __INCLUDELIST_H__
//编译开关定义
#define USE_ITRRUPT //使用中断
#define USE_EXTI //使用外部中断

//函数返回状态定义
#define OK (uint8_t) 1
#define NOTOK (uint8_t)0


 
//NVIC中断分配表 不用请将其关闭
#ifdef USE_ITRRUPT 
#define NVIC_Channel_NUM 1 //申请的中断数
extern IRQn_Type NVIC_Channel_Table[NVIC_Channel_NUM];
extern NVIC_PriorityTable[NVIC_Channel_NUM];
extern NVIC_SubPriorityTable[NVIC_Channel_NUM];
#endif

#ifdef USE_EXTI
#define EXTI_NUM 1//外部中断数
extern TriggerType TriggerTable[EXTI_NUM];
extern uint32_t LineTable[EXTI_NUM];
extern  GPIO_TypeDef *EXTIPortTable[EXTI_NUM];
#endif

#endif
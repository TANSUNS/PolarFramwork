#include <stm32f10x.h>

#ifndef __POLAR_IT_H__
#define __POLAR_IT_H__

/** 
* @file         Polar_IT.h
* @brief        NVIC基本中断组件
* @details    该部分包含，嵌套中断向量函数定义
* @author       唐俊 
* @date     2018/6/5 
* @version  1.0 
* @par Copyright (c):  
*       Advanced Studios 
* @par History:          
*   version: 唐俊, 6/5, 1.0\n 
*/

extern uint8_t GroupInterruptInit(IRQn_Type *ChannelTable,int *PriorityTable,int *SubPriorityTable);
extern uint8_t SigleInterruptRegister(IRQn_Type ChannelTable,int PriorityTable,int SubPriorityTable);  //该函数只能在设置完优先级等级后才能使用
extern uint8_t PrioritySet(uint32_t MaxPriority);
extern uint8_t ResetChannel(IRQn_Type Channel,int Priority,int SubPriority);
extern void CloseInterrupt(IRQn_Type Channel);
extern void CloseAllInterrupt(IRQn_Type *ChannelTable);
extern void OpenInterrupt(IRQn_Type Channel);
extern void OpenAllInterrupt(IRQn_Type *ChannelTable);
static uint8_t PeriphInterruptInit(void);


#endif
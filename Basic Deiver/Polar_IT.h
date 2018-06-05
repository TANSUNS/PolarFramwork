#include <stm32f10x.h>

#ifndef __POLAR_IT_H__
#define __POLAR_IT_H__

extern uint8_t GroupInterruptInit(IRQn_Type *ChannelTable,u8 *PriorityTable,u8 *SubPriorityTable);
extern uint8_t SigleInterruptRegister((IRQn_Type ChannelTable,u8 PriorityTable,u8 SubPriorityTable);  //该函数只能在设置完优先级等级后才能使用
extern uint8_t PrioritySet(uint32_t MaxPriority);
uint8_t ReSetChannel(IRQn_Type Channel,u8 Priority,u8 SubPriority);
extern void CloseInterrupt(IRQn_Type Channel);
extern void CloseAllInterrupt(void);
extern void OpenInterrupt(IRQn_Type Channel);
extern void OpenAllInterrupt(IRQn_Type *ChannelTable);
static uint8_t PeriphInterruptInit(void);


#endif
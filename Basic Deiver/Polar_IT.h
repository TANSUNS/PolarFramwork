#include <stm32f10x.h>

#ifndef __POLAR_IT_H__
#define __POLAR_IT_H__

extern uint8_t InterruptInit(IRQn_Type *ChannelTable,u8 *PriorityTable,u8 *SubPriorityTable);
uint8_t ReSetChannel(IRQn_Type Channel,u8 Priority,u8 SubPriority);
extern void CloseInterrupt(IRQn_Type Channel);
extern void CloseAllInterrupt(void);
extern void OpenInterrupt(IRQn_Type Channel);
extern void OpenAllInterrupt(IRQn_Type *ChannelTable);
static uint8_t PeriphInterruptInit(void);


#endif
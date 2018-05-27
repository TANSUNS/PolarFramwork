#icnlude <stm32f10x.h>

#ifndef __POLAR_IT_H__
#define __POLAR_IT_H__

extern uint8_t InterruptInit(u8 *ChannalTable,u8 *PriorityTable,u8 *SubPriorityTable);
extern uint8_t CloseInterrupt(u8 Channal);
extern uint8_t OpenInterrupt(u8 Channal);
static uint8_t PeriphInterruptInit(void);


#endif
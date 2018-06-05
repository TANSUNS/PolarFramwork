#include "IncludeList.h"

//全局变量实现
#ifdef USE_ITRRUPT//中断表
IRQn_Type NVIC_Channel_Table[NVIC_Channel_NUM];

NVIC_PriorityTable[NVIC_Channel_NUM];

NVIC_SubPriorityTable[NVIC_Channel_NUM];
#endif


#ifdef USE_EXTI //外部中断表
#define EXTI_NUM 1//外部中断数
extern TriggerType TriggerTable[EXTI_NUM];
extern uint32_t LineTable[EXTI_NUM];
extern  GPIO_TypeDef *EXTIPortTable[EXTI_NUM];
#endif
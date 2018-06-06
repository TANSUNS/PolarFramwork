#include "Polar_IT.h"
#ifndef __POLAR_EXTI_H__
#define __POLAR_EXTI_H__

typedef enum{RISE,FALL} TriggerType; //上升沿出发或者下降沿触发

static void EXTI_GPIO_Config(GPIO_TypeDef *s,GPIO_InitTypeDef G);

extern uint8_t EXTI_Config(TriggerType *Trigger,uint32_t *Line,GPIO_TypeDef *(*GPIOXTable));

extern void EXTI_FastConfig(GPIO_TypeDef *GPIOx,uint16_t Pin,TriggerType Trigger);  //该函数只能在设置完优先级等级后才能使用

extern uint8_t EXTICheckFlag(uint32_t Line);

extern uint8_t ClearEXTIFlag(uint32_t Line);

#endif

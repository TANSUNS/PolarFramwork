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

void delay_ms(u32 time)  
{  
  u32 i=8000*time;  
  while(i--);  
}  

*uint8_t TEST_8_Bit(uint8_t Data)
{
    uint8_t *p;
    int mmp;
    p=malloc(sizeof(uint8_t)*8);

    for(mmp=0;mmp<8;mmp++)
    {
        p[mmp]=Data&(1<<mmp);
    }
    return p;
}
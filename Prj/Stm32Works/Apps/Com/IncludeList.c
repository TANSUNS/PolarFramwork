#include "IncludeList.h"

//全局变量实现
#ifdef USE_ITRRUPT//中断表
IRQn_Type NVIC_Channel_Table[NVIC_Channel_NUM]={EXTI3_IRQn}; //中断通道表

uint32_t NVIC_PriorityTable[NVIC_Channel_NUM]={1};   //中断优先级表

uint32_t NVIC_SubPriorityTable[NVIC_Channel_NUM]={0}; //中断次优先级表
#endif


#ifdef USE_EXTI //外部中断表
#define EXTI_NUM 1//外部中断数
extern TriggerType TriggerTable[EXTI_NUM]={RISE};  //外部中断触发表
extern uint32_t LineTable[EXTI_NUM]={EXTI_Line3};       //中断线表
extern  GPIO_TypeDef *EXTIPortTable[EXTI_NUM]={GPIOF}; //中断端口表
#endif


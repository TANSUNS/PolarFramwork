#include "stm32f10x.h"
#include "Polar.h"

int main(void)
{
  GroupInterruptInit( NVIC_Channel_Table,NVIC_PriorityTable,NVIC_SubPriorityTable);
  CLK_SET(GPIOA);
  Fast_OutputSet(GPIOA,GPIO_Pin_0);
  Fast_OutputSet(GPIOA,GPIO_Pin_1);
  Fast_OutputSet(GPIOA,GPIO_Pin_2);
  GPIO_OUT(GPIOA,GPIO_Pin_0,Bit_SET);
  while(1)
  {
  }
  return 1;
}

void EXTI3_IT_Function(void)
  {
    if(EXTICheckFlag(EXTI_Line3)==OK)
  {
      OUT_TOGGLE(GPIOA,GPIO_Pin_0);
    ClearEXTIFlag(EXTI_Line3);
}
  
}
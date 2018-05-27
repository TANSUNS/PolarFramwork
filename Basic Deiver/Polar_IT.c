#include <stm32f10x.h>
#include <Polar_IT.h>

extern uint8_t InterruptInit(u8 *ChannelTable,u8 *PriorityTable,u8 *SubPriorityTable)
{
    int TableLength;
    u8 Max=0;
    int i;
    NVIC_InitTypeDef N;

    TableLength=sizeof(ChannelTable)/sizeof(u8);
    for(i=0;i<TableLength;i++)
    {
        if(PriorityTable[i]>=Max)
        {
            Max=PriorityTable;
            continue;
        }
    }
//开始设置中断组别
    if(Max==0)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    if(Max>0||Max<=2)
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    if(Max>2||Max<=4)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    if(Max>4||Max<=8)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
    if(Max>8||Max<=16)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    if(Max>16)
    return 0;

//开始逐个设置
N.NVIC_IRQChannelCmd=ENABLE;
for(i=0;i<TableLength;i++)
{
    N.NVIC_IRQChannel=ChannelTable[i];
    N.NVIC_IRQChannelPreemptionPriority=PriorityTable[i];
    N.NVIC_IRQChannelSubPriority=SubPriorityTable[i];
    NVIC_Init(&N);
}
PeriphInterruptInit();
return 1;
}

CloseInterrupt(u8 Channel)
{
     NVIC_InitTypeDef N;
    N.NVIC_IRQChannel=Channel;
    N.NVIC_IRQChannelCmd=DISABLE;
    NVIC_Init(&N);
    return 1;
  
}

 uint8_t OpenInterrupt(u8 Channal,u8 Priority,u8 SubPriority)
{
    N.NVIC_IRQChannelCmd=ENABLE;
    N.NVIC_IRQChannel=Channel;
    N.NVIC_IRQChannelPreemptionPriority=Priority;
    N.NVIC_IRQChannelSubPriority=SubPriority;
    NVIC_Init(&N);
    return 1;

}

uint8_t PeriphInterruptInit(void)
{
    //用户需要在这里填写PPP_Config函数，并在stm32f10x_it中添加自己的中断处理函数。
}
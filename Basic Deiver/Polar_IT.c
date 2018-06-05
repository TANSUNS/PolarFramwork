#include <stm32f10x.h>
#include <Polar_IT.h>


extern uint8_t GroupInterruptInit(IRQn_Type *ChannelTable,u8 *PriorityTable,u8 *SubPriorityTable)
{
    int TableLength;
    u8 Max=0;
    int i;
    NVIC_InitTypeDef N;

    TableLength=sizeof(ChannelTable)/sizeof(ChannelTable[0]);
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

void CloseInterrupt(IRQn_Type Channel)
{
    NVIC_DisableIRQ(Channel);

}

void CloseAllInterrupt(IRQn_Type *ChannelTable)
{
    int SIZE=sizeof(ChannelTable)/sizeof(ChannelTable[0]);
    for(int i=0;i<SIZE;i++)
    {
          NVIC_DisableIRQ(ChannelTable[i]);
    }
}

void OpenInterrupt(IRQn_Type Channel)
{
     NVIC_EnableIRQ(Channel);
}

void OpenAllInterrupt(IRQn_Type *ChannelTable)
{
    int SIZE=sizeof(ChannelTable)/sizeof(ChannelTable[0]);
    for(int i=0;i<SIZE;i++)
    {
          NVIC_EnableIRQ(ChannelTable[i]);
    }

}

extern uint8_t PrioritySet(uint32_t MaxPriority)
{
    if(MaxPriority==0)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
    if(MaxPriority>0||MaxPriority<=2)
     NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
    if(MaxPriority>2||MaxPriority<=4)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    if(MaxPriority>4||MaxPriority<=8)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
    if(MaxPriority>8||MaxPriority<=16)
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
    if(MaxPriority>16)
    return 0;
    else
    return 1;


}

Uint8_t SigleInterruptRegister((IRQn_Type ChannelTable,u8 PriorityTable,u8 SubPriorityTable)
{
    NVIC_InitTypeDef N;
    N.NVIC_IRQChannelCmd=ENABLE;
    N.NVIC_IRQChannel=ChannelTable;
    N.NVIC_IRQChannelPreemptionPriority=PriorityTable;
    N.NVIC_IRQChannelSubPriority=SubPriorityTable;
    NVIC_Init(&N);
    return 1;
}
 uint8_t ReSetChannel(u8 Channal,u8 Priority,u8 SubPriority)
{
    NVIC_InitTypeDef N;
    N.NVIC_IRQChannelCmd=ENABLE;//
    N.NVIC_IRQChannel=Channel;
    N.NVIC_IRQChannelPreemptionPriority=Priority;
    N.NVIC_IRQChannelSubPriority=SubPriority;
    NVIC_Init(&N);
    return 1;

}


uint8_t PeriphInterruptInit()
{
    //用户需要在这里填写PPP_Config函数，即外设中断允许函数，并在stm32f10x_it中添加自己的中断处理函数。
}
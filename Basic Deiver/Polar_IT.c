#include <stm32f10x.h>
#include <Polar_IT.h>
/** 
* @file         Polar_IT.c
* @brief        NVIC基本中断组件
* @details    该部分包含，嵌套中断向量的设定和中断线的开关
* @author       唐俊 
* @date     2018/6/5 
* @version  1.0 
* @par Copyright (c):  
*       Advanced Studios 
* @par History:          
*   version: 唐俊, 6/5, 1.0\n 
*/


/** 
 * @brief  完成NVIC的设置
 * @details 通过传入通道参数组，优先级参数组合次优先级参数组，实现中断向量的设置。内部自动识别中断组别，不需要自己设置中断组别
 * @param[in]   *ChannelTable  通道参数列表，推荐使用IncludeList中的数组实现，其可在STM32F10X文件中查询得到
 * @param[in]      *PriorityTable 优先级参数列表，可选值为0-16，与通道参数列表参数一一对应   
 * @param[in]       *SubPriorityTable 次优先级列表，最大值和优先级列表互补，体现为同等级下的抢占优先
 * @param[out]  无 
 * @retval  1  成功 
 * @retval  0   错误  
 * @par 标识符 
 *      保留 
 * @par 其它 
 *      无 
 * @par 修改日志 
 *      唐俊于2018-6-5创建 
 */  
extern uint8_t GroupInterruptInit(IRQn_Type *ChannelTable,int *PriorityTable,int *SubPriorityTable)
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
            Max=PriorityTable[i];
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
    if(Max>16||Max<0)
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

/** 
 * @brief  关闭中断
 * @details 关闭某一个特定通道中断
 * @param[in]  Channel  通道参数其可在STM32F10X文件中查询得到
 * @param[out]  无 
 * @par 标识符 
 *      保留 
 * @par 其它 
 *      无 
 * @par 修改日志 
 *      唐俊于2018-6-5创建 
 */  
void CloseInterrupt(IRQn_Type Channel)
{
    NVIC_DisableIRQ(Channel);

}

/** 
 * @brief  关闭所有中断
 * @details 关闭通道参数列表中的所有中断中断
 * @param[in]  *ChannelTable  通道参数列表，推荐使用IncludeList中的数组实现，其可在STM32F10X文件中查询得到
 * @param[out]  无 
 * @par 标识符 
 *      保留 
 * @par 其它 
 *      无 
 * @par 修改日志 
 *      唐俊于2018-6-5创建 
 */  
void CloseAllInterrupt(IRQn_Type *ChannelTable)
{
    int SIZE=sizeof(ChannelTable)/sizeof(ChannelTable[0]);
    for(int i=0;i<SIZE;i++)
    {
          NVIC_DisableIRQ(ChannelTable[i]);
    }
}
/** 
 * @brief  打开中断
 * @details 打开某一个特定通道中断
 * @param[in]  Channel  通道参数其可在STM32F10X文件中查询得到
 * @param[out]  无 
 * @par 标识符 
 *      保留 
 * @par 其它 
 *      无 
 * @par 修改日志 
 *      唐俊于2018-6-5创建 
 */  
void OpenInterrupt(IRQn_Type Channel)
{
     NVIC_EnableIRQ(Channel);
}

/** 
 * @brief  打开所有中断
 * @details 打开通道参数列表中的所有中断中断
 * @param[in]  *ChannelTable  通道参数列表，推荐使用IncludeList中的数组实现，其可在STM32F10X文件中查询得到
 * @param[out]  无 
 * @par 标识符 
 *      保留 
 * @par 其它 
 *      无 
 * @par 修改日志 
 *      唐俊于2018-6-5创建 
 */  
void OpenAllInterrupt(IRQn_Type *ChannelTable)
{
    int SIZE=sizeof(ChannelTable)/sizeof(ChannelTable[0]);
    for(int i=0;i<SIZE;i++)
    {
          NVIC_EnableIRQ(ChannelTable[i]);
    }

}

/** 
 * @brief  独立设置NVIC优先级
 * @details 当不使用列表进行初始化时，使用该函数完成NVIC优先级的设置，不可与GroupInterruptInit同时调用
 * @param[in]  MaxPriority 最大优先级为16，最小为零
 * @param[out]  无 
 * @par 标识符 
 *      保留 
 * @par 其它 
 *      无 
 * @par 修改日志 
 *      唐俊于2018-6-5创建 
 */  

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
    if(MaxPriority>16||MaxPriority<0)
    return 0;
    else
    return 1;


}

/** 
 * @brief  独立注册NVIC
 * @details 当不使用列表进行初始化时，使用该函数完成NVIC的设置，调用前应先设置优先级组
 * @param[in] Channel 注册NVIC的通道，其值可以在STM32F10X.H中查询
 * @param[in] PriorityTable 这个通道的优先级，不可超过设置优先级的最大值
 * @param[in] SubPriorityTable 这个通道的次优先级，不可超过次优先级的最大值
 * @retval  1  成功 
 * @retval  0   错误 
 * @par 标识符 
 *      保留 
 * @par 其它 
 *      无 
 * @par 修改日志 
 *      唐俊于2018-6-5创建 
 */  

uint8_t SigleInterruptRegister(IRQn_Type Channel,int PriorityTable,int SubPriorityTable)
{
    NVIC_InitTypeDef N;
    N.NVIC_IRQChannelCmd=ENABLE;
    N.NVIC_IRQChannel=Channel;
    N.NVIC_IRQChannelPreemptionPriority=PriorityTable;
    N.NVIC_IRQChannelSubPriority=SubPriorityTable;
    NVIC_Init(&N);
    return 1;
}
/** 
 * @brief  重置NVIC
 * @details 当不使用列表进行初始化已经完成后，使用该函数完成已经注册的NVIC的重置工作
 * @param[in] Channel 注册NVIC的通道，其值可以在STM32F10X.H中查询
 * @param[in] PriorityTable 这个通道的优先级，不可超过设置优先级的最大值
 * @param[in] SubPriorityTable 这个通道的次优先级，不可超过次优先级的最大值
 * @retval  1  成功 
 * @retval  0   错误 
 * @par 标识符 
 *      保留 
 * @par 其它 
 *      无 
 * @par 修改日志 
 *      唐俊于2018-6-5创建 
 */  
uint8_t ResetChannel(IRQn_Type Channel,int Priority,int SubPriority) 
{
    NVIC_InitTypeDef N;
    N.NVIC_IRQChannelCmd=ENABLE;
    N.NVIC_IRQChannel=Channel;
    N.NVIC_IRQChannelPreemptionPriority=Priority;
    N.NVIC_IRQChannelSubPriority=SubPriority;
    NVIC_Init(&N);
    return 1;

}

/** 
 * @brief  外设中断初始化
 * @details 相关外设部分的初始化，用户需要在这里填写PPP_Config函数，即外设中断允许函数，并在stm32f10x_it中添加自己的中断处理函数。
 * @retval  1  成功 
 * @retval  0   错误 
 * @par 标识符 
 *      保留 
 * @par 其它 
 *      无 
 * @par 修改日志 
 *      唐俊于2018-6-5创建 
 */  
uint8_t PeriphInterruptInit()
{
}